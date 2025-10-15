#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symbol.h"
#include <string>

class SemanticAnalyzer {
private:
    SymbolTable* symbol_table;
    std::string current_base_type;
    bool in_function_params;
    
public:
    SemanticAnalyzer(SymbolTable* table);
    void analyze(ASTNode* root);
    
private:
    void traverse(ASTNode* node);
    std::string extract_base_type(ASTNode* decl_specifiers);
    std::string extract_declarator_name(ASTNode* declarator);
    std::string extract_function_name(ASTNode* declarator);
    
    void process_declaration(ASTNode* node);
    void process_function(ASTNode* node);
    void process_function_parameters(ASTNode* declarator);
    void process_struct_or_union(ASTNode* node);
    void process_enum(ASTNode* node);
    void process_parameter(ASTNode* param_decl);
    void process_variable(ASTNode* declarator, const std::string& base_type);

    std::string extract_base_type_from_node(ASTNode* node);
    std::string extract_struct_member_name(ASTNode* node);
    void process_function_parameters(ASTNode* declarator, Symbol* func_sym);
    void process_parameter(ASTNode* param_decl, Symbol* func_sym);
};

#endif