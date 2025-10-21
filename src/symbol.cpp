#include "symbol.h"

// Scope implementation
Scope::Scope(int lvl, Scope* p) : level(lvl), parent(p) {}

Scope::~Scope() {
    for (auto& entry : symbols) {
        delete entry.second;
    }
}

bool Scope::add_symbol(Symbol* symbol) {
    if (!symbol) return false;
    
    if (symbols.find(symbol->name) != symbols.end()) {
        std::cout << "SYMBOL ERROR: Redeclaration of '" << symbol->name 
                  << "' in scope " << level << std::endl;
        delete symbol;
        return false;
    }
    
    symbols[symbol->name] = symbol;
    return true;
}

Symbol* Scope::lookup(const std::string& name) {
    auto it = symbols.find(name);
    return (it != symbols.end()) ? it->second : nullptr;
}

void Scope::print() {
    std::cout << "Scope " << level << ":" << std::endl;
    for (auto& entry : symbols) {
        entry.second->print(1);
    }
    if (symbols.empty()) {
        std::cout << "  (empty)" << std::endl;
    }
}

// Symbol implementation
Symbol::Symbol(const std::string& name, const std::string& sym_kind, 
               const std::string& data_type, int scope, int line)
    : name(name), 
      kind(sym_kind),           // "variable", "function", etc.
      symbol_type(data_type),   // "int", "int*", "float*", etc.
      base_type(data_type),     // Same as symbol_type for now
      scope_level(scope), 
      line_number(line),
      offset(0),
      param_count(0),
      is_array(false),
      pointer_level(0),
      is_initialized(false),
      is_used(false) {}

void Symbol::add_parameter(Symbol* param) {
    if (param) parameters.push_back(param);
}

void Symbol::add_member(Symbol* member) {
    if (member) members.emplace(member->name, member);
}

void Symbol::print(int depth) {
    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << symbol_type << " '" << name << "' : " << base_type;
    std::cout << " (scope: " << scope_level << ", line: " << line_number << ")" << std::endl;
    
    for (auto param : parameters) param->print(depth + 1);
    for (auto &member : members) member.second->print(depth + 1);
}

// SymbolTable implementation
SymbolTable::SymbolTable() {
    global_scope = new Scope(0);
    current_scope = global_scope;
}

SymbolTable::~SymbolTable() {
    // Safe deletion - only delete global scope
    // Other scopes are already deleted when exit_scope is called
    if (global_scope) {
        delete global_scope;
    }
}

void SymbolTable::enter_scope() {
    Scope* new_scope = new Scope(current_scope->level + 1, current_scope);
    current_scope = new_scope;
}

void SymbolTable::exit_scope() {
    if (current_scope != global_scope) {
        Scope* old_scope = current_scope;
        current_scope = current_scope->parent;
        delete old_scope;
    }
}

bool SymbolTable::add_symbol(Symbol* symbol) {
    return current_scope->add_symbol(symbol);
}

Symbol* SymbolTable::lookup(const std::string& name) {
    Scope* scope = current_scope;
    while (scope) {
        Symbol* sym = scope->lookup(name);
        if (sym) return sym;
        scope = scope->parent;
    }
    return nullptr;
}

Symbol* SymbolTable::lookup_current_scope(const std::string& name) {
    return current_scope->lookup(name);
}

void SymbolTable::print_table() {
    std::cout << "\n=== SYMBOL TABLE (ACTIVE SCOPES) ===" << std::endl;
    
    // Collect active scope hierarchy
    std::vector<Scope*> active_scopes;
    Scope* scope = current_scope;
    while (scope) {
        active_scopes.push_back(scope);
        scope = scope->parent;
    }
    
    // Print global first (reverse order)
    for (int i = active_scopes.size() - 1; i >= 0; i--) {
        active_scopes[i]->print();
    }
}

void SymbolTable::print_all_scopes() {
    print_table();
}

// Symbol destructor
Symbol::~Symbol() {
    for (auto& param : parameters) {
        delete param;
    }
    for (auto& member : members) {
        delete member.second;
    }
}