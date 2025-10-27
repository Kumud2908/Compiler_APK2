#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "tac.h"
#include "symbol.h" 
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class CodeGenerator {
private:
    TACGenerator* tac;

    //  Track static variables
    std::unordered_set<std::string> static_variables;
    std::string current_function_name;



    // Store array dimensions: array name -> list of dimensions
    std::unordered_map<std::string, std::string> function_return_types;
    std::unordered_map<std::string, std::string> enum_constants;
    std::unordered_map<std::string, std::vector<int>> array_dims;
    std::unordered_map<std::string, std::string> references;

std::unordered_map<std::string, int> member_offsets;        // "TypeName.member" -> offset
std::unordered_map<std::string, std::string> variable_types; // "var" -> "TypeName"

void process_struct_union_definition(ASTNode* node, const std::string& type_name);

    // Expression code generation - returns the variable holding the result
    std::string generate_expression(ASTNode* node);
  
    std::string current_break_label;
    std::string current_continue_label;
    bool is_void_function(const std::string& func_name);

    // Statement code generation
    void generate_statement(ASTNode* node);
    void generate_compound_statement(ASTNode* node);
    void generate_if_statement(ASTNode* node);
    void generate_while_statement(ASTNode* node);
    void generate_for_statement(ASTNode* node);
    void generate_return_statement(ASTNode* node);
    void generate_expression_statement(ASTNode* node);
    void generate_load(const std::string &target, const std::string &addr);
    void generate_address_of(const std::string &var, const std::string &target);

    void process_enum_declaration(ASTNode* node);

    std::string flatten_array_initialization(const std::string &array_name, const std::vector<int> &dims, ASTNode *init_node, std::vector<int> indices, std::string base_temp);

    // Declaration code generation
    void generate_declaration(ASTNode* node);
    void generate_function_definition(ASTNode* node);
std::string generate_member_address(ASTNode* node);

    // Helper functions
    std::string get_identifier_name(ASTNode* node);
    std::string extract_declarator_name(ASTNode* node);

    // ===== New array helpers =====
    int getArrayNumCols(const std::string &name);
    std::vector<int> extract_array_dimensions(ASTNode* node);
    std::string extract_type_from_decl_specifiers(ASTNode* decl_specifiers);

 int get_type_size(const std::string& type);

    //  Static variable helpers
    bool is_array(ASTNode* node);
    bool is_static_declaration(ASTNode* node);
    std::string get_static_variable_name(const std::string& var_name);

public:
    CodeGenerator(TACGenerator* generator) 
        : tac(generator) {}

    void generate(ASTNode* root);
    void generate_node(ASTNode* node);
    void generate_do_while_statement(ASTNode* node);
    void generate_until_statement(ASTNode* node);
    void generate_switch_statement(ASTNode* node);
    void generate_case_statement(ASTNode* node);
    void generate_default_statement(ASTNode* node);
    void generate_break_statement(ASTNode* node);
    void generate_continue_statement(ASTNode* node);
     std::string get_base_array_name(ASTNode* node);

    void generate_goto_statement(ASTNode* node);
    void generate_labeled_statement(ASTNode* node);

    void collect_array_indices(ASTNode* node, std::vector<std::string>& indices);

};

#endif // CODEGEN_H