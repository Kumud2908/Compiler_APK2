
// ============================================================================
// semantic.cpp - Complete implementation
// ============================================================================

#include "semantic.h"
#include <iostream>
#include <sstream>
#include <algorithm>

SemanticAnalyzer::SemanticAnalyzer(SymbolTable* table) 
    : symbol_table(table), in_function_params(false), 
      loop_depth(0), switch_depth(0), has_default_in_switch(false),
      error_count(0), warning_count(0) {
    if (!symbol_table) {
        std::cerr << "ERROR: SymbolTable is null!" << std::endl;
    }
}

void SemanticAnalyzer::analyze(ASTNode* root) {
    if (!root) {
        std::cerr << "WARNING: analyze() called with null root" << std::endl;
        return;
    }
    
    std::cout << "\n=== SEMANTIC ANALYSIS STARTED ===" << std::endl;
    traverse(root);
    
    // Post-analysis checks
    // Check for unused labels (goto targets)
    for (const auto& label : used_labels) {
        if (declared_labels.find(label.first) == declared_labels.end()) {
            report_error("Label '" + label.first + "' used but not declared");
        }
    }
    
    // Check for declared but unused labels (warning)
    for (const auto& label : declared_labels) {
        if (used_labels.find(label.first) == used_labels.end()) {
            report_warning("Label '" + label.first + "' declared but never used");
        }
    }
    
    std::cout << "=== SEMANTIC ANALYSIS COMPLETED ===" << std::endl;
    print_summary();
}

void SemanticAnalyzer::traverse(ASTNode* node) {
    if (!node || node->processed) return;
    node->processed = true;

    // ========== CRITICAL SEMANTIC CHECKS ==========
    
    // 1. CHECK UNDECLARED IDENTIFIERS
    if (node->name == "Identifier" && !in_function_params) {
        check_undeclared_identifier(node);
    }
    
    // 2. CHECK BREAK/CONTINUE VALIDITY
    if (node->name == "BreakStatement" || node->name == "ContinueStatement") {
        check_break_continue(node);
    }
    
    // 3. CHECK CASE/DEFAULT STATEMENTS
    if (node->name == "CaseStatement") {
        check_case_statement(node);
    }
    if (node->name == "DefaultStatement") {
        if (switch_depth == 0) {
            report_error("'default' statement outside switch", node);
        } else if (has_default_in_switch) {
            report_error("Duplicate 'default' statement in switch", node);
        } else {
            has_default_in_switch = true;
        }
    }
    
    // 4. CHECK GOTO STATEMENTS
    if (node->name == "GotoStatement") {
        check_goto_statement(node);
    }
    
    // 5. CHECK LABELED STATEMENTS
    if (node->name == "LabeledStatement") {
        check_label_statement(node);
    }
    
    // 6. CHECK FUNCTION CALLS
    if (node->name == "FunctionCall") {
        check_function_call(node);
    }
    
    // 7. CHECK ASSIGNMENTS
    if (node->name == "AssignmentExpression") {
        check_assignment(node);
    }
    
    // 8. CHECK BINARY OPERATIONS
    if (node->name == "AdditiveExpression" || node->name == "MultiplicativeExpression" ||
        node->name == "RelationalExpression" || node->name == "EqualityExpression" ||
        node->name == "LogicalAndExpression" || node->name == "LogicalOrExpression") {
        check_binary_operation(node);
    }
    
    // 9. CHECK UNARY OPERATIONS
    if (node->name == "UnaryExpression") {
        check_unary_operation(node);
    }
    
    // 10. CHECK RETURN STATEMENTS
    if (node->name == "ReturnStatement") {
        check_return_statement(node);
    }
    
    // 11. CHECK ARRAY ACCESS
    if (node->name == "ArraySubscript") {
        check_array_access(node);
    }
    
    // 12. CHECK MEMBER ACCESS
    if (node->name == "MemberAccess") {
        check_member_access(node);
    }
    
    // 13. CHECK CAST EXPRESSIONS
    if (node->name == "CastExpression") {
        check_cast_validity(node);
    }
    
    // 14. CHECK IF CONDITIONS
    if (node->name == "IfStatement") {
        if (node->children.size() > 0) {
            check_if_condition(node->children[0]);
        }
    }
    
    // 15. CHECK SWITCH STATEMENTS
    if (node->name == "SwitchStatement") {
        check_switch_statement(node);
    }
    
    // Track loop depth
    if (node->name == "WhileStatement" || node->name == "DoWhileStatement" || 
        node->name == "ForStatement") {
        loop_depth++;
        if (node->children.size() > 0) {
            check_loop_condition(node->children[0]);
        }
    }
    
    // Track switch depth
    if (node->name == "SwitchStatement") {
        switch_depth++;
        case_values_in_switch.clear();
        has_default_in_switch = false;
    }

    // ========== EXISTING PROCESSING ==========
    if (node->name == "Declaration") {
        process_declaration(node);
    }
    else if (node->name == "FunctionDefinition") {
        process_function(node);
        return;
    }
    else if (node->name == "StructOrUnionSpecifier") {
        process_struct(node);
    }
    else if (node->name == "EnumSpecifier") {
        process_enum(node);
    }
    else if (node->name == "CompoundStatement") {
        bool is_function_body = (node->parent && node->parent->name == "FunctionDefinition");
        
        if (!is_function_body) {
            symbol_table->enter_scope();
            for (size_t i = 0; i < node->children.size(); i++) {
                if (node->children[i]) traverse(node->children[i]);
            }
            symbol_table->exit_scope();
            return;
        }
    }

    // Traverse children
    for (size_t i = 0; i < node->children.size(); i++) {
        if (node->children[i]) traverse(node->children[i]);
    }
    
    // Exit tracking
    if (node->name == "WhileStatement" || node->name == "DoWhileStatement" || 
        node->name == "ForStatement") {
        loop_depth--;
    }
    
    if (node->name == "SwitchStatement") {
        switch_depth--;
    }
}

// ============================================================================
// SEMANTIC CHECK IMPLEMENTATIONS
// ============================================================================

void SemanticAnalyzer::check_undeclared_identifier(ASTNode* node) {
    if (!node || node->lexeme.empty()) return;
    
    Symbol* sym = symbol_table->lookup(node->lexeme);
    if (!sym) {
        report_error("Undeclared identifier '" + node->lexeme + "'", node);
    }
}

void SemanticAnalyzer::check_function_call(ASTNode* node) {
    if (!node || node->children.empty()) return;
    
    ASTNode* func_id = node->children[0];
    if (!func_id || func_id->name != "Identifier") return;
    
    std::string func_name = func_id->lexeme;
    
    // Check if function exists
    Symbol* func_sym = symbol_table->lookup(func_name);
    if (!func_sym) {
        report_error("Undeclared function '" + func_name + "'", node);
        return;
    }
    
    if (func_sym->kind != "function") {
        report_error("'" + func_name + "' is not a function", node);
        return;
    }
    
    // Check for recursion
    if (!current_function_name.empty()) {
        if (func_name == current_function_name) {
            std::cout << "[RECURSION DETECTED] Function '" << func_name 
                      << "' calls itself (direct recursion)" << std::endl;
            recursive_functions.insert(func_name);
        }
        
        // Check for indirect recursion
        if (functions_in_call_chain.find(func_name) != functions_in_call_chain.end()) {
            std::cout << "[RECURSION DETECTED] Indirect recursion involving '" 
                      << func_name << "'" << std::endl;
            recursive_functions.insert(func_name);
        }
    }
    
    // TODO: Check argument count and types (requires storing function signatures)
}

void SemanticAnalyzer::check_assignment(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string lhs_type = get_expression_type(node->children[0]);
    std::string rhs_type = get_expression_type(node->children[1]);
    
    if (lhs_type == "unknown" || rhs_type == "unknown") return;
    
    // Check pointer level compatibility
    int lhs_ptr_level = get_pointer_level(lhs_type);
    int rhs_ptr_level = get_pointer_level(rhs_type);
    
    if (lhs_ptr_level != rhs_ptr_level) {
        report_error("Pointer level mismatch in assignment: cannot assign '" + 
                    rhs_type + "' to '" + lhs_type + "'", node);
        return;
    }
    
    if (!types_compatible(lhs_type, rhs_type)) {
        report_warning("Implicit type conversion in assignment: '" + 
                      rhs_type + "' to '" + lhs_type + "'", node);
    }
}

void SemanticAnalyzer::check_binary_operation(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string left_type = get_expression_type(node->children[0]);
    std::string right_type = get_expression_type(node->children[1]);
    
    if (left_type == "unknown" || right_type == "unknown") return;
    
    // Check division by zero for constant expressions
    if (node->name == "MultiplicativeExpression" && node->lexeme == "/") {
        check_division_by_zero(node);
    }
    
    // Check modulo operations
    if (node->name == "MultiplicativeExpression" && node->lexeme == "%") {
        check_modulo_operation(node);
    }
    
    // Check pointer arithmetic
    if (is_pointer_type(left_type) || is_pointer_type(right_type)) {
        if (node->name == "AdditiveExpression") {
            // pointer + int or pointer - int is OK
            // pointer - pointer is OK
            if (is_pointer_type(left_type) && is_pointer_type(right_type)) {
                if (node->lexeme != "-") {
                    report_error("Invalid pointer arithmetic: can only subtract pointers", node);
                }
            } else if (is_pointer_type(right_type) && node->lexeme == "+") {
                // int + pointer is OK
            } else if (!is_integer_type(right_type) && !is_pointer_type(right_type)) {
                report_error("Invalid pointer arithmetic: can only add/subtract integers", node);
            }
        } else {
            report_error("Invalid operation on pointer type", node);
        }
    }
    
    // Check if operands are numeric for arithmetic operations
    if (node->name == "AdditiveExpression" || node->name == "MultiplicativeExpression") {
        if (!is_numeric_type(left_type) && !is_pointer_type(left_type)) {
            report_error("Arithmetic operation requires numeric type, got '" + left_type + "'", node);
        }
        if (!is_numeric_type(right_type) && !is_pointer_type(right_type)) {
            report_error("Arithmetic operation requires numeric type, got '" + right_type + "'", node);
        }
    }
}

void SemanticAnalyzer::check_unary_operation(ASTNode* node) {
    if (!node || node->children.empty()) return;
    
    std::string operand_type = get_expression_type(node->children[0]);
    std::string op = node->lexeme;
    
    if (op == "*") {
        // Dereference - must be pointer
        if (!is_pointer_type(operand_type)) {
            report_error("Cannot dereference non-pointer type '" + operand_type + "'", node);
        }
    } else if (op == "&") {
        // Address-of - operand must be lvalue
        // TODO: Check if operand is lvalue
    } else if (op == "++" || op == "--") {
        // Increment/decrement - must be numeric or pointer
        if (!is_numeric_type(operand_type) && !is_pointer_type(operand_type)) {
            report_error("Increment/decrement requires numeric or pointer type", node);
        }
    }
}

void SemanticAnalyzer::check_return_statement(ASTNode* node) {
    if (current_function_return_type.empty()) {
        report_error("Return statement outside function", node);
        return;
    }
    
    function_has_return[current_function_name] = true;
    
    bool has_value = node->children.size() > 0;
    
    if (current_function_return_type == "void" && has_value) {
        report_error("Void function '" + current_function_name + 
                    "' should not return a value", node);
    } else if (current_function_return_type != "void" && !has_value) {
        report_warning("Non-void function '" + current_function_name + 
                      "' should return a value", node);
    } else if (has_value) {
        std::string return_type = get_expression_type(node->children[0]);
        if (!types_compatible(current_function_return_type, return_type)) {
            report_warning("Return type mismatch: expected '" + 
                          current_function_return_type + "', got '" + return_type + "'", node);
        }
    }
}

void SemanticAnalyzer::check_array_access(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    // Get array name
    std::string array_name;
    ASTNode* array_node = node->children[0];
    if (array_node->name == "Identifier") {
        array_name = array_node->lexeme;
    }
    
    // Check if index is integer type
    std::string index_type = get_expression_type(node->children[1]);
    if (!is_integer_type(index_type)) {
        report_error("Array subscript must be integer type, got '" + index_type + "'", node);
    }
    
    // Check array dimensions
    if (!array_name.empty() && array_dimensions.find(array_name) != array_dimensions.end()) {
        // Count access dimensions
        int access_dims = 1;
        ASTNode* parent = node->parent;
        while (parent && parent->name == "ArraySubscript") {
            access_dims++;
            parent = parent->parent;
        }
        check_array_dimensions(array_name, access_dims, node);
    }
    
    // TODO: Bounds checking for constant indices
}

void SemanticAnalyzer::check_array_dimensions(const std::string& array_name, 
                                               int access_dims, ASTNode* node) {
    auto it = array_dimensions.find(array_name);
    if (it == array_dimensions.end()) return;
    
    int declared_dims = it->second.size();
    if (access_dims > declared_dims) {
        report_error("Too many array subscripts for '" + array_name + 
                    "': array has " + std::to_string(declared_dims) + 
                    " dimension(s), accessing with " + std::to_string(access_dims), node);
    }
}

void SemanticAnalyzer::check_member_access(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string object_type = get_expression_type(node->children[0]);
    std::string member_name = node->children[1]->lexeme;
    
    // Check if object is struct/union/class
    Symbol* type_sym = symbol_table->lookup(object_type);
    if (!type_sym || (type_sym->kind != "struct" && type_sym->kind != "class")) {
        report_error("Member access requires struct/union/class type", node);
        return;
    }
    
    // TODO: Check if member exists in struct/class
    // Requires storing struct/class member information
}

void SemanticAnalyzer::check_break_continue(ASTNode* node) {
    if (loop_depth == 0 && switch_depth == 0) {
        report_error("'" + node->name + "' statement not within loop or switch", node);
    } else if (node->name == "ContinueStatement" && loop_depth == 0) {
        report_error("'continue' statement not within loop", node);
    }
}

void SemanticAnalyzer::check_goto_statement(ASTNode* node) {
    if (!node || node->lexeme.empty()) return;
    used_labels[node->lexeme] = true;
}

void SemanticAnalyzer::check_label_statement(ASTNode* node) {
    if (!node || node->lexeme.empty()) return;
    
    if (declared_labels.find(node->lexeme) != declared_labels.end()) {
        report_error("Duplicate label '" + node->lexeme + "'", node);
    } else {
        declared_labels[node->lexeme] = true;
    }
}

void SemanticAnalyzer::check_case_statement(ASTNode* node) {
    if (switch_depth == 0) {
        report_error("'case' statement outside switch", node);
        return;
    }
    
    if (node->children.size() > 0) {
        // Check for duplicate case values (only for constants)
        ASTNode* case_expr = node->children[0];
        if (case_expr->name == "Constant") {
            std::string case_value = case_expr->lexeme;
            if (case_values_in_switch.find(case_value) != case_values_in_switch.end()) {
                report_error("Duplicate case value '" + case_value + "' in switch", node);
            } else {
                case_values_in_switch.insert(case_value);
            }
        }
    }
}

void SemanticAnalyzer::check_switch_statement(ASTNode* node) {
    if (!node || node->children.empty()) return;
    
    std::string switch_expr_type = get_expression_type(node->children[0]);
    if (!is_integer_type(switch_expr_type)) {
        report_warning("Switch expression should be integer type, got '" + 
                      switch_expr_type + "'", node);
    }
}

void SemanticAnalyzer::check_loop_condition(ASTNode* node) {
    if (!node) return;
    
    std::string cond_type = get_expression_type(node);
    // Condition should be boolean or numeric
    if (cond_type != "unknown" && !is_numeric_type(cond_type) && cond_type != "bool") {
        report_warning("Loop condition should be boolean or numeric type", node);
    }
}

void SemanticAnalyzer::check_if_condition(ASTNode* node) {
    if (!node) return;
    
    std::string cond_type = get_expression_type(node);
    if (cond_type != "unknown" && !is_numeric_type(cond_type) && cond_type != "bool") {
        report_warning("Condition should be boolean or numeric type", node);
    }
}

void SemanticAnalyzer::check_division_by_zero(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    ASTNode* divisor = node->children[1];
    if (divisor->name == "Constant" && divisor->lexeme == "0") {
        report_error("Division by zero", node);
    }
}

void SemanticAnalyzer::check_modulo_operation(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string left_type = get_expression_type(node->children[0]);
    std::string right_type = get_expression_type(node->children[1]);
    
    if (!is_integer_type(left_type) || !is_integer_type(right_type)) {
        report_error("Modulo operation requires integer operands", node);
    }
    
    ASTNode* divisor = node->children[1];
    if (divisor->name == "Constant" && divisor->lexeme == "0") {
        report_error("Modulo by zero", node);
    }
}

void SemanticAnalyzer::check_cast_validity(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    // Get target type from TypeName node
    // Get source type from expression
    // Check if cast is valid
    // TODO: Implement cast validity checking
}

// ============================================================================
// TYPE CHECKING HELPERS
// ============================================================================

std::string SemanticAnalyzer::get_expression_type(ASTNode* expr) {
    if (!expr) return "unknown";
    
    if (expr->name == "Identifier") {
        return get_identifier_type(expr->lexeme);
    }
    
    if (expr->name == "Constant") {
        if (expr->lexeme.find('.') != std::string::npos || 
            expr->lexeme.find('f') != std::string::npos) {
            return "float";
        }
        if (expr->lexeme == "true" || expr->lexeme == "false") {
            return "bool";
        }
        return "int";
    }
    
    if (expr->name == "StringLiteral") {
        return "char*";
    }
    
    // Binary operations
    if (expr->name == "AdditiveExpression" || expr->name == "MultiplicativeExpression") {
        std::string left_type = get_expression_type(expr->children[0]);
        std::string right_type = get_expression_type(expr->children[1]);
        
        // Result type promotion
        if (left_type == "float" || right_type == "float") return "float";
        if (left_type == "double" || right_type == "double") return "double";
        return "int";
    }
    
    // Relational/Equality operations return bool
    if (expr->name == "RelationalExpression" || expr->name == "EqualityExpression" ||
        expr->name == "LogicalAndExpression" || expr->name == "LogicalOrExpression") {
        return "bool";
    }
    
    // Unary operations
    if (expr->name == "UnaryExpression") {
        if (expr->lexeme == "*") {
            // Dereference - remove one pointer level
            std::string operand_type = get_expression_type(expr->children[0]);
            if (operand_type.find('*') != std::string::npos) {
                return operand_type.substr(0, operand_type.length() - 1);
            }
        } else if (expr->lexeme == "&") {
            // Address-of - add one pointer level
            std::string operand_type = get_expression_type(expr->children[0]);
            return operand_type + "*";
        }
        return get_expression_type(expr->children[0]);
    }
    
    // Function call
    if (expr->name == "FunctionCall" && expr->children.size() > 0) {
        std::string func_name = expr->children[0]->lexeme;
        Symbol* func_sym = symbol_table->lookup(func_name);
        if (func_sym) {
            return func_sym->symbol_type;
        }
    }
    
    // Array subscript
    if (expr->name == "ArraySubscript" && expr->children.size() > 0) {
        return get_expression_type(expr->children[0]);
    }
    
    return "unknown";
}

std::string SemanticAnalyzer::get_identifier_type(const std::string& name) {
    Symbol* sym = symbol_table->lookup(name);
    return sym ? sym->symbol_type : "unknown";
}

int SemanticAnalyzer::get_pointer_level(const std::string& type) {
    return std::count(type.begin(), type.end(), '*');
}

bool SemanticAnalyzer::types_compatible(const std::string& type1, const std::string& type2) {
    if (type1 == type2) return true;
    
    // Check pointer levels
    if (get_pointer_level(type1) != get_pointer_level(type2)) {
        return false;
    }
    
    // Allow implicit numeric conversions
    if (is_numeric_type(type1) && is_numeric_type(type2)) {
        return true;
    }
    
    return false;
}

bool SemanticAnalyzer::is_numeric_type(const std::string& type) {
    std::string base_type = type;
    // Remove pointer indicators
    size_t star_pos = type.find('*');
    if (star_pos != std::string::npos) {
        base_type = type.substr(0, star_pos);
    }
    
    return base_type == "int" || base_type == "float" || base_type == "double" ||
           base_type == "long" || base_type == "short" || base_type == "char";
}

bool SemanticAnalyzer::is_integer_type(const std::string& type) {
    std::string base_type = type;
    size_t star_pos = type.find('*');
    if (star_pos != std::string::npos) {
        base_type = type.substr(0, star_pos);
    }
    
    return base_type == "int" || base_type == "long" || base_type == "short" || 
           base_type == "char" || base_type == "unsigned" || base_type == "signed";
}

bool SemanticAnalyzer::is_pointer_type(const std::string& type) {
    return type.find('*') != std::string::npos;
}

// ============================================================================
// EXISTING METHODS (from your original code)
// ============================================================================

void SemanticAnalyzer::process_declaration(ASTNode* node) {
    if (!node) return;
    
    std::string base_type = "int";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            base_type = extract_base_type(child);
            break;
        }
    }
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "InitDeclaratorList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* init_decl = child->children[j];
                if (!init_decl) continue;
                
                if (init_decl->name == "InitDeclarator") {
                    for (size_t k = 0; k < init_decl->children.size(); k++) {
                        ASTNode* decl = init_decl->children[k];
                        if (!decl) continue;
                        
                        if (decl->name == "Declarator" || decl->name == "DirectDeclarator") {
                            process_variable(decl, base_type);
                        }
                    }
                }
            }
        }
    }
}

void SemanticAnalyzer::process_function(ASTNode* node) {
    if (!node || !symbol_table) return;
    
    std::string func_name = "unknown";
    std::string return_type = "int";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            return_type = extract_base_type(child);
        }
        else if (child->name == "Declarator" || child->name == "FunctionDeclarator") {
            func_name = extract_function_name(child);
        }
    }
    
    std::cout << "[Scope " << symbol_table->get_current_scope_level() 
              << "] Found function: " << func_name << " : " << return_type << std::endl;
    
    // Check for redeclaration
    Symbol* existing = symbol_table->lookup_current_scope(func_name);
    if (existing) {
        report_error("Redeclaration of function '" + func_name + "'", node);
    }
    
    Symbol* func_sym = new Symbol(func_name, "function", return_type, 
                                 symbol_table->get_current_scope_level(), 0);
    symbol_table->add_symbol(func_sym);
    
    // Set function context
    current_function_name = func_name;
    current_function_return_type = return_type;
    function_has_return[func_name] = false;
    functions_in_call_chain.insert(func_name);
    
    symbol_table->enter_scope();
    
    in_function_params = true;
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "Declarator" || child->name == "FunctionDeclarator") {
            process_function_parameters(child);
        }
    }
    in_function_params = false;
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "CompoundStatement") {
            traverse(child);
        }
    }
    
    // Check if non-void function has return
    if (return_type != "void" && !function_has_return[func_name]) {
        report_warning("Non-void function '" + func_name + 
                      "' may not return a value in all paths", node);
    }
    
    symbol_table->exit_scope();
    
    // Clear function context
    functions_in_call_chain.erase(func_name);
    current_function_name = "";
    current_function_return_type = "";
}

void SemanticAnalyzer::process_function_parameters(ASTNode* declarator) {
    if (!declarator) return;
    
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        if (child->name == "DirectDeclarator") {
            process_function_parameters(child);
        }
        else if (child->name == "ParameterList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* param = child->children[j];
                if (param && param->name == "ParameterDeclaration") {
                    process_parameter(param);
                }
            }
        }
        else if (child->name == "ParameterTypeList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* param_list = child->children[j];
                if (!param_list) continue;
                
                if (param_list->name == "ParameterList") {
                    for (size_t k = 0; k < param_list->children.size(); k++) {
                        ASTNode* param = param_list->children[k];
                        if (param && param->name == "ParameterDeclaration") {
                            process_parameter(param);
                        }
                    }
                }
            }
        }
    }
}

void SemanticAnalyzer::process_parameter(ASTNode* param_decl) {
    if (!param_decl || !symbol_table) return;
    
    std::string param_type = "int";
    std::string param_name = "unknown";
    
    for (size_t i = 0; i < param_decl->children.size(); i++) {
        ASTNode* child = param_decl->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            param_type = extract_base_type(child);
        }
        else if (child->name == "Declarator" || child->name == "DirectDeclarator") {
            param_name = extract_declarator_name(child);
        }
    }
    
    if (param_name != "unknown") {
        Symbol* param_sym = new Symbol(param_name, "parameter", param_type,
                                      symbol_table->get_current_scope_level(), 0);
        if (symbol_table->add_symbol(param_sym)) {
            std::cout << "[Scope " << symbol_table->get_current_scope_level() 
                      << "] Added parameter: " << param_name << " : " << param_type << std::endl;
        }
    }
}

void SemanticAnalyzer::process_variable(ASTNode* declarator, const std::string& base_type) {
    if (!declarator || !symbol_table) return;
    
    std::string var_name = extract_declarator_name(declarator);
    
    if (var_name == "unknown" || var_name.empty()) return;
    
    // Check for redeclaration in current scope
    Symbol* existing = symbol_table->lookup_current_scope(var_name);
    if (existing && !in_function_params) {
        report_error("Redeclaration of variable '" + var_name + "'", declarator);
        return;
    }
    
    // Track array dimensions
    std::vector<int> dims = extract_array_dimensions(declarator);
    if (!dims.empty()) {
        array_dimensions[var_name] = dims;
        std::cout << "[ARRAY] " << var_name << " dimensions: ";
        for (int d : dims) std::cout << d << " ";
        std::cout << std::endl;
    }
    
    // Track pointer levels
    int ptr_level = count_pointer_levels(declarator);
    if (ptr_level > 0) {
        pointer_levels[var_name] = ptr_level;
        std::cout << "[POINTER] " << var_name << " pointer level: " << ptr_level << std::endl;
    }
    
    std::string symbol_type = in_function_params ? "parameter" : "variable";
    std::string full_type = base_type + std::string(ptr_level, '*');
    
    Symbol* var_sym = new Symbol(var_name, symbol_type, full_type,
                                symbol_table->get_current_scope_level(), 0);
    
    if (symbol_table->add_symbol(var_sym)) {
        std::cout << "[Scope " << symbol_table->get_current_scope_level() 
                  << "] Added " << symbol_type << ": " << var_name << " : " << full_type << std::endl;
    }
}

void SemanticAnalyzer::process_struct(ASTNode* node) {
    if (!node || !symbol_table) return;
    
    std::string struct_name = "anonymous";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if ((child->name == "Identifier" || child->name == "IDENTIFIER") && 
            !child->lexeme.empty() && child->lexeme != "default") {
            struct_name = child->lexeme;
            break;
        }
    }
    
    Symbol* struct_sym = new Symbol(struct_name, "struct", "struct", 
                                   symbol_table->get_current_scope_level(), 0);
    symbol_table->add_symbol(struct_sym);
}

void SemanticAnalyzer::process_enum(ASTNode* node) {
    if (!node || !symbol_table) return;
    
    std::string enum_name = "anonymous";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if ((child->name == "Identifier" || child->name == "IDENTIFIER") && 
            !child->lexeme.empty() && child->lexeme != "default") {
            enum_name = child->lexeme;
            break;
        }
    }
    
    Symbol* enum_sym = new Symbol(enum_name, "enum", "enum", 
                                 symbol_table->get_current_scope_level(), 0);
    symbol_table->add_symbol(enum_sym);
}

std::string SemanticAnalyzer::extract_function_name(ASTNode* declarator) {
    if (!declarator) return "unknown";
    
    if (!declarator->lexeme.empty() && declarator->lexeme != "default") {
        return declarator->lexeme;
    }
    
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        if (child->name == "DirectDeclarator") {
            if (!child->lexeme.empty() && child->lexeme != "default") {
                return child->lexeme;
            }
            
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* grandchild = child->children[j];
                if (!grandchild) continue;
                
                if (!grandchild->lexeme.empty() && grandchild->lexeme != "default") {
                    return grandchild->lexeme;
                }
            }
        }
    }
    return "unknown";
}

std::string SemanticAnalyzer::extract_declarator_name(ASTNode* declarator) {
    if (!declarator) return "unknown";
    
    if (!declarator->lexeme.empty() && declarator->lexeme != "default") {
        return declarator->lexeme;
    }
    
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        std::string result = extract_declarator_name(child);
        if (result != "unknown") {
            return result;
        }
    }
    
    return "unknown";
}

std::string SemanticAnalyzer::extract_base_type(ASTNode* decl_specifiers) {
    if (!decl_specifiers) return "int";
    
    for (size_t i = 0; i < decl_specifiers->children.size(); i++) {
        ASTNode* child = decl_specifiers->children[i];
        if (!child) continue;
        
        if (child->name == "TypeSpecifier") {
            if (!child->lexeme.empty() && child->lexeme != "default") {
                return child->lexeme;
            }
            
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* type_child = child->children[j];
                if (!type_child) continue;
                
                if (!type_child->lexeme.empty() && type_child->lexeme != "default") {
                    return type_child->lexeme;
                }
            }
        }
    }
    return "int";
}

// ============================================================================
// UTILITY HELPERS
// ============================================================================

std::vector<int> SemanticAnalyzer::extract_array_dimensions(ASTNode* node) {
    std::vector<int> dims;
    if (!node) return dims;
    
    if (node->name == "ArrayDeclarator") {
        for (auto child : node->children) {
            if (!child) continue;
            if (child->name == "Constant") {
                try {
                    dims.push_back(std::stoi(child->lexeme));
                } catch (...) {}
            } else {
                auto sub = extract_array_dimensions(child);
                dims.insert(dims.end(), sub.begin(), sub.end());
            }
        }
    } else {
        for (auto c : node->children) {
            auto sub = extract_array_dimensions(c);
            dims.insert(dims.end(), sub.begin(), sub.end());
        }
    }
    return dims;
}

int SemanticAnalyzer::count_pointer_levels(ASTNode* node) {
    if (!node) return 0;
    
    int count = 0;
    if (node->name == "Pointer") {
        count = 1;
        for (auto child : node->children) {
            count += count_pointer_levels(child);
        }
    } else {
        for (auto child : node->children) {
            count += count_pointer_levels(child);
        }
    }
    return count;
}

// ============================================================================
// ERROR REPORTING
// ============================================================================

void SemanticAnalyzer::report_error(const std::string& message, ASTNode* node) {
    std::cerr << "SEMANTIC ERROR: " << message;
    if (node) {
        std::cerr << " [at node: " << node->name << "]";
    }
    std::cerr << std::endl;
    error_count++;
}

void SemanticAnalyzer::report_warning(const std::string& message, ASTNode* node) {
    std::cout << "WARNING: " << message;
    if (node) {
        std::cout << " [at node: " << node->name << "]";
    }
    std::cout << std::endl;
    warning_count++;
}

void SemanticAnalyzer::print_summary() {
    std::cout << "\n=== SEMANTIC ANALYSIS SUMMARY ===" << std::endl;
    std::cout << "Errors: " << error_count << std::endl;
    std::cout << "Warnings: " << warning_count << std::endl;
    
    if (!recursive_functions.empty()) {
        std::cout << "\n[RECURSIVE FUNCTIONS DETECTED]:" << std::endl;
        for (const auto& func : recursive_functions) {
            std::cout << "  - " << func << std::endl;
        }
    }
    
    std::cout << "=================================" << std::endl;
}