#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <map>
#include <utility>

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
    Symbol* lookup(const std::string& name) { return find_symbol(name); }
    void print();
};

class Symbol {
public:
    // YOUR EXISTING FIELDS
    std::string name;
    std::string symbol_type;
    std::string base_type;
    int scope_level;
    int line_number;
    bool is_pointer;
    int pointer_level;
    bool is_array;
    std::vector<int> array_dimensions;
    std::vector<std::pair<std::string, int>> enumerators;
    int next_enum_value;
    int const_value;
    std::string enum_type;
    std::vector<Symbol*> parameters;
    std::vector<Symbol*> members;
    bool is_complete;

    // ADD THESE NEW FIELDS - THEY WERE MISSING!
    bool is_initialized;
    bool is_used;
    bool has_return_statement;
    bool is_recursive;
    bool in_call_chain;
    int offset;

    Symbol(const std::string& name, const std::string& sym_type, 
           const std::string& base_type, int scope, int line);
    
    std::string get_full_type() const;
    bool is_type_compatible(const Symbol* other) const;
    bool is_assignable_to(const Symbol* other) const;
    void add_parameter(Symbol* param);
    void add_member(Symbol* member);
    void add_enumerator(const std::string& name, int value);
    void print(int depth = 0);
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

    void check_unused_variables();
};

#endif
