// semantic.h - Complete header with all semantic checks

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symbol.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>

class SemanticAnalyzer {
private:
    SymbolTable* symbol_table;
    bool in_function_params;


    // Add these tracking maps
    std::set<std::string> initialized_variables;
    std::map<std::string, bool> variable_initialized;
    
    // Context tracking
    std::string current_function_name;
    std::string current_function_return_type;
    int loop_depth;
    int switch_depth;
    
    // Recursive function tracking
    std::set<std::string> recursive_functions;
    std::set<std::string> functions_in_call_chain;
    
    // Return statement tracking
    std::map<std::string, bool> function_has_return;
    
    // Array dimension tracking
    std::map<std::string, std::vector<int>> array_dimensions;
    
    // Pointer level tracking
    std::map<std::string, int> pointer_levels;
    
    // Label tracking (for goto)
    std::map<std::string, bool> declared_labels;
    std::map<std::string, bool> used_labels;
    
    // Switch case tracking
    std::set<std::string> case_values_in_switch;
    bool has_default_in_switch;
    
    // Error tracking
    int error_count;
    int warning_count;

    // Helper methods
    void process_declaration(ASTNode* node);
    void process_function(ASTNode* node);
    void process_function_parameters(ASTNode* declarator);
    void process_parameter(ASTNode* param_decl);
    void process_variable(ASTNode* declarator, const std::string& base_type);
    void process_struct(ASTNode* node);
    void process_enum(ASTNode* node);
    
    std::string extract_function_name(ASTNode* declarator);
    std::string extract_declarator_name(ASTNode* declarator);
    std::string extract_base_type(ASTNode* decl_specifiers);
    std::vector<int> extract_array_dimensions(ASTNode* node);
    int count_pointer_levels(ASTNode* node);
    

    
    // Type checking
    std::string get_expression_type(ASTNode* expr);
    std::string get_identifier_type(const std::string& name);
    int get_pointer_level(const std::string& type);
    bool types_compatible(const std::string& type1, const std::string& type2);
    bool is_numeric_type(const std::string& type);
    bool is_integer_type(const std::string& type);
    bool is_pointer_type(const std::string& type);
    
    // Semantic checks
    void check_undeclared_identifier(ASTNode* node);
    void check_redeclaration(const std::string& name, ASTNode* node);
    void check_function_call(ASTNode* node);
    void check_assignment(ASTNode* node);
    void check_binary_operation(ASTNode* node);
    void check_unary_operation(ASTNode* node);
    void check_return_statement(ASTNode* node);
    void check_array_access(ASTNode* node);
    void check_array_dimensions(const std::string& array_name, int access_dims, ASTNode* node);
    void check_pointer_operations(ASTNode* node);
    void check_member_access(ASTNode* node);
    void check_break_continue(ASTNode* node);
    void check_goto_statement(ASTNode* node);
    void check_label_statement(ASTNode* node);
    void check_case_statement(ASTNode* node);
    void check_switch_statement(ASTNode* node);
    void check_loop_condition(ASTNode* node);
    void check_if_condition(ASTNode* node);
    void check_division_by_zero(ASTNode* node);
    void check_modulo_operation(ASTNode* node);
    void check_cast_validity(ASTNode* node);
    void detect_recursion(const std::string& caller, const std::string& callee);
    
    // Error reporting
    void report_error(const std::string& message, ASTNode* node = nullptr);
    void report_warning(const std::string& message, ASTNode* node = nullptr);

    bool has_initializer(ASTNode* init_declarator);
    void process_class(ASTNode* node);
     void check_initialization(ASTNode* init_declarator, const std::string& declared_type);

public:
    SemanticAnalyzer(SymbolTable* table);
    void analyze(ASTNode* root);
    void traverse(ASTNode* node);
    void print_summary();
    bool has_errors() { return error_count > 0; }
};

#endif // SEMANTIC_H
