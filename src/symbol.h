#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <map>

// =========================
// Forward Declaration
// =========================
class Symbol;

// =========================
// Scope Class
// =========================
class Scope {
public:
    int level;
    Scope* parent;
    std::unordered_map<std::string, Symbol*> symbols;

    Scope(int lvl, Scope* p = nullptr);
    ~Scope();

    bool add_symbol(Symbol* symbol);
    Symbol* lookup(const std::string& name);
    void print();
};

// =========================
// Symbol Class
// =========================
class Symbol {
public:
    std::string name;
    std::string kind;          // variable, function, parameter, class, etc.
    std::string symbol_type;   // e.g., "int", "float", "MyClass"
    std::string base_type;     // For arrays/pointers
    int scope_level;
    int line_number;
    int offset;

    // Semantic attributes
    std::vector<std::string> param_types;   // For function parameters
    int param_count;
    bool is_array;
    std::vector<int> array_dims;
    int pointer_level;
    bool is_initialized;
    bool is_used;

    // For struct/class
    std::map<std::string, Symbol*> members;

    // Function params or class members
    std::vector<Symbol*> parameters;

    Symbol(const std::string& name, const std::string& kind,
           const std::string& base_type, int scope, int line);

    ~Symbol();

    void add_parameter(Symbol* param);
    void add_member(Symbol* member);
    void print(int depth = 0);
};

// =========================
// Symbol Table Class
// =========================
class SymbolTable {
private:
    Scope* current_scope;
    Scope* global_scope;

public:
    SymbolTable();
    ~SymbolTable();

    void enter_scope();
    void exit_scope();
    bool add_symbol(Symbol* symbol);
    Symbol* lookup(const std::string& name);
    Symbol* lookup_current_scope(const std::string& name);
    void print_table();
    void print_all_scopes();

    int get_current_scope_level() const {
        return current_scope ? current_scope->level : 0;
    }

private:
    void check_unused_variables(Scope* scope);
};

#endif // SYMBOL_H
