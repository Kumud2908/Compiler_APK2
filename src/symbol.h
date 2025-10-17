#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

// Forward declaration
class Symbol;

class Scope {
public:
    int level;
    Scope* parent;
    std::unordered_map<std::string, Symbol*> symbols;
    
    Scope(int lvl, Scope* p = nullptr);
    ~Scope();
    
    bool add_symbol(Symbol* symbol);
    Symbol* find_symbol(const std::string& name);
    void print();
};

class Symbol {
public:
    std::string name;
    std::string symbol_type;  // "function", "variable", "struct", "typedef", etc.
    std::string base_type;    // "int", "char", "struct_name", etc.
    
    // Enhanced type information
    bool is_pointer = false;
    int pointer_level = 0;    // for multiple pointers (int**)
    bool is_array = false;
    std::vector<int> array_dimensions;  // -1 for incomplete arrays
    
    // For functions
    std::vector<Symbol*> parameters;
    std::string return_type;
    
    // For structs/unions
    std::vector<Symbol*> members;
    bool is_complete = false;  // for forward declarations

    // FOR ENUMS - ADD THESE:
    std::vector<std::pair<std::string, int>> enumerators;  // (name, value)
    int next_enum_value = 0;

    
    // Common fields
    int scope_level;
    int line_number;
    
    Symbol(const std::string& name, const std::string& sym_type, 
           const std::string& base_type, int scope, int line);
    
    // Type information methods
    std::string get_full_type() const;
    bool is_type_compatible(const Symbol* other) const;
    bool is_assignable_to(const Symbol* other) const;
    
    void add_parameter(Symbol* param);
    void add_member(Symbol* member);
    void print(int depth = 0);

    void add_enumerator(const std::string& name, int value); 
};

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
    Symbol* find_symbol(const std::string& name);
    Symbol* find_symbol_current_scope(const std::string& name);
    void print_table();
    void print_all_scopes();
    
    int get_current_scope_level() const { 
        return current_scope ? current_scope->level : 0; 
    }
};

#endif