#include "symbol.h"
#include <sstream>

// Scope implementation (mostly same)
Scope::Scope(int lvl, Scope* p) : level(lvl), parent(p) {}

Scope::~Scope() {
    for (auto& entry : symbols) {
        delete entry.second;
    }
}

bool Scope::add_symbol(Symbol* symbol) {
    if (!symbol) return false;
    
    if (symbols.find(symbol->name) != symbols.end()) {
        delete symbol;
        return false;
    }
    
    symbols[symbol->name] = symbol;
    return true;
}

Symbol* Scope::find_symbol(const std::string& name) {
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

// Enhanced Symbol implementation
Symbol::Symbol(const std::string& name, const std::string& sym_type, 
               const std::string& base_type, int scope, int line)
    : name(name), symbol_type(sym_type), base_type(base_type), 
      scope_level(scope), line_number(line) {}

std::string Symbol::get_full_type() const {
    std::stringstream ss;
    
    // Add base type
    ss << base_type;
    
    // Add pointer asterisks
    if (is_pointer) {
        for (int i = 0; i < pointer_level; i++) {
            ss << "*";
        }
    }
    
    // Add array dimensions
    if (is_array && !array_dimensions.empty()) {
        for (int dim : array_dimensions) {
            ss << "[";
            if (dim >= 0) {
                ss << dim;
            }
            ss << "]";
        }
    }
    
    // For functions, add parameter types
    if (symbol_type == "function" && !parameters.empty()) {
        ss << "(";
        for (size_t i = 0; i < parameters.size(); i++) {
            if (i > 0) ss << ", ";
            ss << parameters[i]->get_full_type();
        }
        ss << ")";
    }
    
    return ss.str();
}

bool Symbol::is_type_compatible(const Symbol* other) const {
    if (!other) return false;
    
    // Basic type compatibility
    if (base_type != other->base_type) {
        // TODO: Add type promotion rules (char->int, etc.)
        return false;
    }
    
    // Pointer level must match
    if (is_pointer != other->is_pointer || pointer_level != other->pointer_level) {
        return false;
    }
    
    // Array dimensions must match
    if (is_array != other->is_array) {
        return false;
    }
    
    if (is_array && array_dimensions != other->array_dimensions) {
        // Allow assignment between compatible arrays (some leniency needed)
        // For now, strict matching
        return false;
    }
    
    return true;
}

bool Symbol::is_assignable_to(const Symbol* other) const {
    if (!other) return false;
    
    // Basic type compatibility
    if (!is_type_compatible(other)) {
        // TODO: Add implicit conversion rules
        return false;
    }
    
    // Additional assignment rules can go here
    // e.g., const correctness, etc.
    
    return true;
}

void Symbol::add_parameter(Symbol* param) {
    if (param) parameters.push_back(param);
}

void Symbol::add_member(Symbol* member) {
    if (member) members.push_back(member);
}

void Symbol::add_enumerator(const std::string& name, int value) {
    enumerators.push_back(std::make_pair(name, value));
    next_enum_value = value + 1;  // Set next value for auto-increment
}

void Symbol::print(int depth) {
    std::string indent(depth * 2, ' ');
    
    std::cout << indent << symbol_type << " '" << name << "' : " << get_full_type();
    std::cout << " (scope: " << scope_level << ", line: " << line_number << ")" << std::endl;
    
    // Print parameters for functions
    for (auto param : parameters) {
        param->print(depth + 1);
    }
    
    // Print members for structs/unions
    for (auto member : members) {
        member->print(depth + 1);
    }
}

// SymbolTable implementation (same as before)
SymbolTable::SymbolTable() {
    global_scope = new Scope(0);
    current_scope = global_scope;	
}

SymbolTable::~SymbolTable() {
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

Symbol* SymbolTable::find_symbol(const std::string& name) {
    Scope* scope = current_scope;
    while (scope) {
        Symbol* sym = scope->find_symbol(name);
        if (sym) return sym;
        scope = scope->parent;
    }
    return nullptr;
}

Symbol* SymbolTable::find_symbol_current_scope(const std::string& name) {
    return current_scope->find_symbol(name);
}

void SymbolTable::print_table() {
    std::cout << "\n=== SYMBOL TABLE (ACTIVE SCOPES) ===" << std::endl;
    
    std::vector<Scope*> active_scopes;
    Scope* scope = current_scope;
    while (scope) {
        active_scopes.push_back(scope);
        scope = scope->parent;
    }
    
    for (int i = active_scopes.size() - 1; i >= 0; i--) {
        active_scopes[i]->print();
    }
}