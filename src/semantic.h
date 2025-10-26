#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symbol.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_set>

class SemanticAnalyzer {
private:
    SymbolTable* symbol_table;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    bool in_function_params;
    std::string current_base_type;
    int error_count;
    
    // ADD ONLY THESE CONTEXT TRACKING VARIABLES (no redundant maps):
    int loop_depth = 0;
    int switch_depth = 0;
    std::string current_function_name;
    std::string current_function_return_type;
    
    // KEEP ONLY THESE SEPARATE TRACKERS (not in symbol table):
    std::unordered_map<std::string, bool> declared_labels;
    std::unordered_map<std::string, bool> used_labels;
    std::unordered_set<std::string> case_values_in_switch;
    bool has_default_in_switch = false;
    int warning_count = 0;
    void check_function_pointer_operations(ASTNode* node);
    void check_function_pointer_arithmetic(ASTNode* node);
    void validate_function_pointer_type(ASTNode* node, const std::string& func_ptr_name);
    
    void check_null_function_pointer_call(ASTNode* node);
    void check_function_pointer_comparison(ASTNode* node);
    void check_function_pointer_array(ASTNode* node, const std::string& type_name);
     
     void check_void_function_pointer(Symbol* func_ptr_sym);
     void check_function_pointer_parameter(Symbol* param_sym, ASTNode* param_node);
     void check_function_pointer_dereference(ASTNode* node) ;
     void check_function_pointer_return(ASTNode* node) ;
     void check_function_pointer_assignment(ASTNode* node);
     

    



public:
    SemanticAnalyzer(SymbolTable* table);
    void analyze(ASTNode* root);
    
    // Your existing methods
    int getErrorCount() const { return error_count; }
    void reportError(const std::string& message, ASTNode* node = nullptr);
    
    // ADD THESE NEW METHODS for advanced validation:
    void print_summary();
    void report_warning(const std::string& message, ASTNode* node = nullptr);
    int get_error_count() const {
        return errors.size();
    }
    
    int get_warning_count() const {
        return warnings.size();
    }
    
    bool has_errors() const {
        return !errors.empty();
    }
    
    const std::vector<std::string>& get_errors() const {
        return errors;
    }
    
    const std::vector<std::string>& get_warnings() const {
        return warnings;
    }

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
    void process_typedef(ASTNode* declaration);
    std::string extract_typedef_name(ASTNode* init_decl_list);

    // ========== NEW VALIDATION METHODS ==========
    
    // Type System
    std::string get_expression_type(ASTNode* expr);
    bool types_compatible(const std::string& type1, const std::string& type2);
    bool is_numeric_type(const std::string& type);
    bool is_integer_type(const std::string& type);
    bool is_pointer_type(const std::string& type);
    int get_pointer_level(const std::string& type);

    std::string resolve_typedef(const std::string& type_name);
    
    // Initialization & Assignment
    bool has_initializer(ASTNode* init_declarator);
    void check_initialization(ASTNode* init_declarator, const std::string& declared_type);
    void check_declaration_initialization(ASTNode* declaration);
    void check_assignment(ASTNode* node);
    bool is_struct_union_type(const std::string& type);
    bool is_incomplete_type(const std::string& type);
    
    // Function Analysis
    void check_function_call(ASTNode* node);

    void check_return_statement(ASTNode* node);
    void detect_recursion(const std::string& caller, const std::string& callee);
    
    // Control Flow
    void check_break_continue(ASTNode* node);
    void check_switch_statement(ASTNode* node);
    void check_case_statement(ASTNode* node);
    void check_loop_condition(ASTNode* node);
    void check_if_condition(ASTNode* node);
    
    // Operations
    void check_binary_operation(ASTNode* node);
    void check_unary_operation(ASTNode* node);
    void check_division_by_zero(ASTNode* node);
    void check_modulo_operation(ASTNode* node);
    
    // Memory Operations
    void check_array_access(ASTNode* node);
    void check_array_dimensions(const std::string& array_name, int access_dims, ASTNode* node);
    void check_pointer_operations(ASTNode* node);
    
    // Labels
    void check_goto_statement(ASTNode* node);
    void check_label_statement(ASTNode* node);
    
    // Class support
    void process_class(ASTNode* node);
};

#endif