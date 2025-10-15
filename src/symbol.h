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
    std::string symbol_type;
    std::string base_type;
    std::string type_kind;    // "struct", "union", "enum", "basic", ""
    int scope_level;
    int line_number;
    
    std::vector<Symbol*> parameters;
    std::vector<Symbol*> members;
    
    Symbol(const std::string& name, const std::string& sym_type, 
           const std::string& base_type, int scope, int line);
    
    void add_parameter(Symbol* param);
    void add_member(Symbol* member);
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
};

#endif

