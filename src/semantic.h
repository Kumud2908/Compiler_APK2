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
    int error_count;
    
public:
    SemanticAnalyzer(SymbolTable* table);
    void analyze(ASTNode* root);
    
    int getErrorCount() const { return error_count; }
    void reportError(const std::string& message, ASTNode* node = nullptr);
    
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
    
    void check_identifier_usage(ASTNode* node);
    void check_member_access(ASTNode* node);
    bool is_valid_type(const std::string& type);
    
    // ADDED THESE 2 METHODS:
    bool is_function_declaration(ASTNode* declaration_node);
    void process_function_declaration(ASTNode* node);

    bool has_parameter_list(ASTNode* node);  

    void extract_type_info(ASTNode* declarator, Symbol* symbol);
    void extract_pointer_info(ASTNode* declarator, Symbol* symbol);
    void extract_array_dimensions(ASTNode* array_declarator, Symbol* symbol);
    void process_struct_member(ASTNode* member_decl, const std::string& base_type, 
                              Symbol* struct_sym, const std::string& struct_type);
    bool is_function_pointer(ASTNode* node);
    std::vector<std::pair<std::string, int>> extract_enumerators(ASTNode* enumerator_list, int& next_value);


    };

#endif