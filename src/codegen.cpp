#include "codegen.h"
#include <iostream>
#include <unordered_map>

// =======================================================
//  CodeGenerator: generate TAC from AST
// =======================================================

void CodeGenerator::generate(ASTNode* root) {
    if (!root) return;
    generate_node(root);
}

void CodeGenerator::generate_node(ASTNode* node) {
    if (!node) return;
    
    if (node->name == "TranslationUnit") {
        for (auto child : node->children) generate_node(child);
    }
    else if (node->name == "FunctionDefinition") {
        generate_function_definition(node);
    }
    else if (node->name == "Declaration") {
        generate_declaration(node);
    }
}

// =======================================================
//  Function Definitions
// =======================================================
void CodeGenerator::generate_function_definition(ASTNode* node) {
    if (!node) return;
    
    std::string func_name = "unknown";
    for (auto child : node->children) {
        if (child->name == "Declarator" || child->name == "FunctionDeclarator") {
            func_name = extract_declarator_name(child);
            break;
        }
    }
    
    current_function_name = func_name;
    std::cerr << "DEBUG: current_function_name = " << current_function_name << std::endl; // ✅ ADD THIS
    
    tac->add_label(func_name);
    
    for (auto child : node->children) {
        if (child->name == "CompoundStatement") {
            generate_compound_statement(child);
        }
    }
    

}
// =======================================================
//  Compound / Statements
// =======================================================

void CodeGenerator::generate_compound_statement(ASTNode* node) {
    if (!node) return;
    
    for (auto child : node->children) {
        if (child->name == "BlockItemList") {
            for (auto item : child->children) {
                if (item->name == "BlockItem") {
                    for (auto stmt : item->children) {
                        if (stmt->name == "Declaration") generate_declaration(stmt);
                        else generate_statement(stmt);
                    }
                }
            }
        }
    }
}

void CodeGenerator::generate_statement(ASTNode* node) {
    if (!node) return;
    
    if (node->name == "ExpressionStatement" || node->name == "EmptyStatement") {
        generate_expression_statement(node);
    }
    else if (node->name == "CompoundStatement") generate_compound_statement(node);
    else if (node->name == "IfStatement") generate_if_statement(node);
    else if (node->name == "WhileStatement") generate_while_statement(node);
    else if (node->name == "ForStatement") generate_for_statement(node);
    else if (node->name == "DoWhileStatement") generate_do_while_statement(node);
    else if (node->name == "SwitchStatement") generate_switch_statement(node);
    else if (node->name == "BreakStatement") generate_break_statement(node);
    else if (node->name == "ContinueStatement") generate_continue_statement(node);
    else if (node->name == "CaseStatement") generate_case_statement(node);
    else if (node->name == "GotoStatement") generate_goto_statement(node);
    else if (node->name == "LabeledStatement") generate_labeled_statement(node);
    else if (node->name == "DefaultStatement") generate_default_statement(node);
    else if (node->name == "ReturnStatement") generate_return_statement(node);
}

void CodeGenerator::generate_goto_statement(ASTNode* node) {
    tac->generate_goto(node->lexeme);  // lexeme contains the label name "skip"
}

void CodeGenerator::generate_labeled_statement(ASTNode* node) {
    tac->add_label(node->lexeme);  // This should add "skip:"
    
    // Generate the statement after the label
    if (!node->children.empty()) {
        generate_statement(node->children[0]);
    }
}

void CodeGenerator::generate_expression_statement(ASTNode* node) {
    if (!node) return;
    for (auto child : node->children) generate_expression(child);
}

// =======================================================
//  Expression Handling
// =======================================================

std::string CodeGenerator::generate_expression(ASTNode* node) {
    if (!node) return "";

    // Identifier
if (node->name == "Identifier") {
    std::string var_name = node->lexeme;
    std::string static_var = get_static_variable_name(var_name);
    
    // If this identifier refers to a static variable, use the mangled name
    if (static_variables.find(static_var) != static_variables.end()) {
        return static_var;
    }
    
    auto it = enum_constants.find(var_name);
    if (it != enum_constants.end()) {
        std::cout << "DEBUG: Resolved enum constant " << var_name << " = " << it->second << std::endl;
        return it->second;  // Return the numeric value
    }
    
    return var_name;
}


    // Constant
    if (node->name == "Constant") return node->lexeme;

    // String literal
    if (node->name == "StringLiteral") return node->lexeme;

    // TypeName - ignore for TAC
    if (node->name == "TypeName") {
        return "";
    }

    // Cast Expression
    if (node->name == "CastExpression") {
        if (node->children.size() >= 2) {
            // children[0] = TypeName (ignore for TAC)
            // children[1] = expression being casted
            return generate_expression(node->children[1]);
        }
        if (node->children.size() == 1) {
            return generate_expression(node->children[0]);
        }
        return "";
    }

    // ✅ STRUCT MEMBER ACCESS (must be before AssignmentExpression)
    if (node->name == "MemberAccess" || node->name == "StructMemberAccess") {
        std::string base = generate_expression(node->children[0]); // e.g., 'p'
        std::string field = node->children[1]->lexeme;            // e.g., 'x'
        std::string temp = tac->new_temp();
        tac->generate_struct_load(base, field, temp);
        return temp;
    }

    // Assignment Expression
    if (node->name == "AssignmentExpression") {
        if (node->children.size() >= 2) {
            ASTNode* lhs_node = node->children[0];
            std::string rhs = generate_expression(node->children[1]);


        if (lhs_node->name == "UnaryExpression" && lhs_node->lexeme == "*") {
            std::string pointer = generate_expression(lhs_node->children[0]);
            tac->generate_store(pointer, rhs);  // *pointer = value
            return rhs;
        }
            
            // ✅ CHECK IF LHS IS STRUCT MEMBER ACCESS
            if (lhs_node->name == "MemberAccess" || lhs_node->name == "StructMemberAccess") {
                std::string base = generate_expression(lhs_node->children[0]); // e.g., 'p'
                std::string field = lhs_node->children[1]->lexeme;            // e.g., 'x'
                
                if (node->lexeme == "=") {
                    tac->generate_struct_store(base, field, rhs);
                    return base;
                } else {
                    // Compound assignment: p.x += value
                    std::string temp_load = tac->new_temp();
                    tac->generate_struct_load(base, field, temp_load);
                    
                    std::string temp_result = tac->new_temp();
                    std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                    tac->generate_binary_op(op, temp_load, rhs, temp_result);
                    
                    tac->generate_struct_store(base, field, temp_result);
                    return base;
                }
            }
            
            // ✅ CHECK IF LHS IS ARRAY SUBSCRIPT
            if (lhs_node->name == "ArraySubscript") {
                // Check if multi-dimensional
                if (lhs_node->children[0]->name == "ArraySubscript") {
                    // Multi-dimensional array assignment
                    std::string base_array = get_base_array_name(lhs_node);
                    std::vector<std::string> indices;
                    collect_array_indices(lhs_node, indices);
                    
                    if (array_dims.find(base_array) != array_dims.end()) {
                        const auto& dims = array_dims[base_array];
                        
                        // Calculate flattened index
                        std::string offset = indices[0];
                        for (size_t i = 1; i < indices.size(); ++i) {
                            std::string t_mul = tac->new_temp();
                            tac->generate_binary_op("*", offset, std::to_string(dims[i]), t_mul);
                            
                            std::string t_add = tac->new_temp();
                            tac->generate_binary_op("+", t_mul, indices[i], t_add);
                            offset = t_add;
                        }
                        
                        if (node->lexeme == "=") {
                            tac->generate_array_store(base_array, offset, rhs);
                            return base_array;
                        } else {
                            // Compound assignment
                            std::string temp_load = tac->new_temp();
                            tac->generate_array_access(base_array, offset, temp_load);
                            
                            std::string temp_result = tac->new_temp();
                            std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                            tac->generate_binary_op(op, temp_load, rhs, temp_result);
                            
                            tac->generate_array_store(base_array, offset, temp_result);
                            return base_array;
                        }
                    }
                }
                
                // Simple 1D array assignment
                std::string array_base = generate_expression(lhs_node->children[0]);
                std::string index = generate_expression(lhs_node->children[1]);
                
                if (node->lexeme == "=") {
                    tac->generate_array_store(array_base, index, rhs);
                    return array_base;
                } else {
                    // Compound assignment: a[i] += value
                    std::string temp_load = tac->new_temp();
                    tac->generate_array_access(array_base, index, temp_load);
                    
                    std::string temp_result = tac->new_temp();
                    std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                    tac->generate_binary_op(op, temp_load, rhs, temp_result);
                    
                    tac->generate_array_store(array_base, index, temp_result);
                    return array_base;
                }
            }
            
            // Regular variable assignment
            std::string lhs = generate_expression(lhs_node);
            
            if (node->lexeme == "=") {
                tac->generate_assignment(lhs, rhs);
                return lhs;
            } else {
                std::string temp = tac->new_temp();
                std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                tac->generate_binary_op(op, lhs, rhs, temp);
                tac->generate_assignment(lhs, temp);
                return lhs;
            }
        }
        return "";
    }

    // Binary operations
    if (node->name == "AdditiveExpression" || node->name == "MultiplicativeExpression" ||
        node->name == "RelationalExpression" || node->name == "EqualityExpression" ||
        node->name == "LogicalAndExpression" || node->name == "LogicalOrExpression" ||
        node->name == "ShiftExpression" || node->name == "AndExpression" ||
        node->name == "ExclusiveOrExpression" || node->name == "InclusiveOrExpression") {
        
        if (node->children.size() >= 2) {
            std::string arg1 = generate_expression(node->children[0]);
            std::string arg2 = generate_expression(node->children[1]);
            std::string result = tac->new_temp();
            tac->generate_binary_op(node->lexeme, arg1, arg2, result);
            return result;
        }
    }

    // Unary operations
    if (node->name == "UnaryExpression" && node->children.size() >= 1) {
        std::string arg = generate_expression(node->children[0]);
        std::string result = tac->new_temp();

        if (node->lexeme == "&") {
            tac->generate_address_of(arg, result); // address-of operator
        }
        else if (node->lexeme == "*") {
            tac->generate_load(result, arg); // dereference operator
        }
        else if (node->lexeme == "+" || node->lexeme == "-" || 
                 node->lexeme == "!" || node->lexeme == "~") {
            tac->generate_unary_op("unary" + node->lexeme, arg, result);
        }
        else {
            // fallback safety
            tac->generate_binary_op(node->lexeme, arg, "", result);
        }

        return result;
    }

    // Postfix ++ / --
    if (node->name == "PostfixExpression") {
        if (node->lexeme == "++" || node->lexeme == "--") {
            std::string var = generate_expression(node->children[0]);
            std::string temp = tac->new_temp();
            tac->generate_assignment(temp, var);
            std::string one = "1";
            std::string op = (node->lexeme == "++") ? "+" : "-";
            tac->generate_binary_op(op, var, one, var);
            return temp;
        }
    }

// Function call
if (node->name == "FunctionCall") {
    std::string func_name = generate_expression(node->children[0]);
    int param_count = 0;
    
    if (node->children.size() > 1 && node->children[1]->name == "ArgumentList") {
        for (auto arg : node->children[1]->children) {
            std::string param = generate_expression(arg);
            
            
            tac->generate_param(param);
            param_count++;
        }
    }
    
    // Handle void vs non-void functions
    if (is_void_function(func_name)) {
        tac->generate_call(func_name, param_count);
        return "";
    } else {
        std::string result = tac->new_temp();
        tac->generate_call(func_name, param_count, result);
        return result;
    }
}

    // Array subscript (flattened for multi-dimensional arrays)
    if (node->name == "ArraySubscript") {
        // Check if this is a nested array subscript (e.g., a[i][j])
        if (node->children[0]->name == "ArraySubscript") {
            // This is a multi-dimensional array access
            std::string base_array = get_base_array_name(node);
            
            // Collect all indices from innermost to outermost
            std::vector<std::string> indices;
            collect_array_indices(node, indices);
            
            // Check if we have dimension information
            if (array_dims.find(base_array) != array_dims.end()) {
                const auto& dims = array_dims[base_array];
                
                // Calculate flattened index: i * dims[1] + j for a[i][j]
                std::string offset = indices[0];
                for (size_t i = 1; i < indices.size(); ++i) {
                    std::string t_mul = tac->new_temp();
                    tac->generate_binary_op("*", offset, std::to_string(dims[i]), t_mul);
                    
                    std::string t_add = tac->new_temp();
                    tac->generate_binary_op("+", t_mul, indices[i], t_add);
                    offset = t_add;
                }
                
                std::string result = tac->new_temp();
                tac->generate_array_access(base_array, offset, result);
                return result;
            }
        }
        
        // Simple 1D array or couldn't determine dimensions
        std::string array_name = generate_expression(node->children[0]);
        std::string index_val = generate_expression(node->children[1]);
        std::string result = tac->new_temp();
        tac->generate_array_access(array_name, index_val, result);
        return result;
    }

    // Conditional expression (ternary)
    if (node->name == "ConditionalExpression" && node->children.size() >= 3) {
        std::string cond = generate_expression(node->children[0]);
        std::string label_true = tac->new_label();
        std::string label_false = tac->new_label();
        std::string label_end = tac->new_label();
        std::string result = tac->new_temp();
        
        tac->generate_if_false_goto(cond, label_false);
        tac->add_label(label_true);
        std::string true_val = generate_expression(node->children[1]);
        tac->generate_assignment(result, true_val);
        tac->generate_goto(label_end);
        tac->add_label(label_false);
        std::string false_val = generate_expression(node->children[2]);
        tac->generate_assignment(result, false_val);
        tac->add_label(label_end);
        return result;
    }

    // Recursively handle single child
    if (node->children.size() == 1) return generate_expression(node->children[0]);
    
    return "";
}



// =======================================================
//  Statement Types
// =======================================================

void CodeGenerator::generate_if_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    std::string cond = generate_expression(node->children[0]);
    std::string label_false = tac->new_label();
    std::string label_end = tac->new_label();

    tac->generate_if_false_goto(cond, label_false);
    generate_statement(node->children[1]);

    if (node->children.size() >= 3) {
        tac->generate_goto(label_end);
        tac->add_label(label_false);
        generate_statement(node->children[2]);
        tac->add_label(label_end);
    } else {
        tac->add_label(label_false);
    }
}

void CodeGenerator::generate_while_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    std::string label_start = tac->new_label();
    std::string label_end = tac->new_label();
    
    std::string old_break = current_break_label;
    std::string old_continue = current_continue_label;
    current_break_label = label_end;
    current_continue_label = label_start;

    tac->add_label(label_start);
    std::string cond = generate_expression(node->children[0]);
    tac->generate_if_false_goto(cond, label_end);
    generate_statement(node->children[1]);
    tac->generate_goto(label_start);
    tac->add_label(label_end);
    
    current_break_label = old_break;
    current_continue_label = old_continue;
}

void CodeGenerator::generate_for_statement(ASTNode* node) {
    if (!node || node->children.size() < 3) return;
    
    if (node->children[0]->name == "ForInitStatement") {
        for (auto child : node->children[0]->children) {
            if (child->name == "Declaration") generate_declaration(child);
            else generate_expression(child);
        }
    }
    
    std::string label_start = tac->new_label();
    std::string label_end = tac->new_label();
    std::string label_increment = tac->new_label();
    
    std::string old_break = current_break_label;
    std::string old_continue = current_continue_label;
    current_break_label = label_end;
    current_continue_label = label_increment;

    tac->add_label(label_start);
    if (node->children[1]->name == "ExpressionStatement") {
        for (auto child : node->children[1]->children) {
            std::string cond = generate_expression(child);
            if (!cond.empty()) tac->generate_if_false_goto(cond, label_end);
        }
    }
    
    int body_index = (node->children.size() == 4) ? 3 : 2;
    generate_statement(node->children[body_index]);
    
    tac->add_label(label_increment);
    if (node->children.size() == 4) generate_expression(node->children[2]);
    
    tac->generate_goto(label_start);
    tac->add_label(label_end);
    
    current_break_label = old_break;
    current_continue_label = old_continue;
}

void CodeGenerator::generate_return_statement(ASTNode* node) {
    if (!node) return;
    if (node->children.size() > 0) {
        std::string ret_val = generate_expression(node->children[0]);
        tac->generate_return(ret_val);
    } else {
        tac->generate_return();
    }
}

void CodeGenerator::generate_do_while_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    std::string label_start = tac->new_label();
    std::string label_end = tac->new_label();
    
    std::string old_break = current_break_label;
    std::string old_continue = current_continue_label;
    current_break_label = label_end;
    current_continue_label = label_start;

    tac->add_label(label_start);
    generate_statement(node->children[0]);  // body
    std::string cond = generate_expression(node->children[1]);  // condition
    tac->generate_if_goto(cond, label_start);
    tac->add_label(label_end);
    
    current_break_label = old_break;
    current_continue_label = old_continue;
}

void CodeGenerator::generate_switch_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string switch_var = generate_expression(node->children[0]);
    std::string end_label = tac->new_label();
    
    std::string old_break = current_break_label;
    current_break_label = end_label;
    
    // Generate the switch body (which contains case/default statements)
    generate_statement(node->children[1]);
    
    tac->add_label(end_label);
    current_break_label = old_break;
}

void CodeGenerator::generate_case_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    // For simplicity, just generate a label and the statement
    std::string case_label = tac->new_label();
    tac->add_label(case_label);
    
    // Generate the statement after the case
    generate_statement(node->children[1]);
}

void CodeGenerator::generate_default_statement(ASTNode* node) {
    if (!node || node->children.size() < 1) return;
    
    std::string default_label = tac->new_label();
    tac->add_label(default_label);
    
    generate_statement(node->children[0]);
}

void CodeGenerator::generate_break_statement(ASTNode* node) {
    if (!current_break_label.empty()) {
        tac->generate_goto(current_break_label);
    }
}

void CodeGenerator::generate_continue_statement(ASTNode* node) {
    if (!current_continue_label.empty()) {
        tac->generate_goto(current_continue_label);
    }
}

// =======================================================
//  Declaration + Array Tracking
// =======================================================

// Recursive helper to flatten array initializers
void CodeGenerator::flatten_array_initialization(const std::string &array_name,
                                                 const std::vector<int> &dims,
                                                 ASTNode* init_node,
                                                 std::vector<std::string> indices) {
    if (!init_node) return;

    if (init_node->name == "InitializerList") {
        for (size_t i = 0; i < init_node->children.size(); ++i) {
            std::vector<std::string> new_indices = indices;
            new_indices.push_back(std::to_string(i));
            flatten_array_initialization(array_name, dims, init_node->children[i], new_indices);
        }
    } else if (init_node->name == "Initializer") {
        flatten_array_initialization(array_name, dims, init_node->children[0], indices);
    } else {
        // Leaf constant
        std::string value = generate_expression(init_node);

        // Compute flattened index
        std::string offset;
        for (size_t i = 0; i < indices.size(); ++i) {
            std::string term = indices[i];
            for (size_t j = i + 1; j < dims.size(); ++j) {
                term = tac->new_temp();
                tac->generate_binary_op("*", indices[i], std::to_string(dims[j]), term);
            }
            if (offset.empty())
                offset = term;
            else {
                std::string tmp = tac->new_temp();
                tac->generate_binary_op("+", offset, term, tmp);
                offset = tmp;
            }
        }

        // Assign value to flattened array
        tac->generate_array_store(array_name, offset, value);
    }
}
void CodeGenerator::generate_declaration(ASTNode* node) {
    if (!node) return;
    for (auto child : node->children) {
        if (child->name == "DeclarationSpecifiers") {
            for (auto spec : child->children) {
                if (spec->name == "EnumSpecifier") {
                    process_enum_declaration(spec);
                }
            }
        }
    }
    bool is_static = is_static_declaration(node);
    
    for (auto child : node->children) {
        if (!child) continue;
        
        if (child->name == "InitDeclaratorList") {
            for (auto init_decl : child->children) {
                if (!init_decl || init_decl->name != "InitDeclarator") continue;

                // Extract variable name and initializer for THIS declaration
                std::string var_name;
                ASTNode* init_node = nullptr;
                bool is_array = false;
                std::vector<int> dims;
                
                // Get declarator (variable name)
                if (init_decl->children.size() > 0) {
                    var_name = extract_declarator_name(init_decl->children[0]);
                    
                    // Check if it's an array
                    dims = extract_array_dimensions(init_decl->children[0]);
                    if (!dims.empty()) {
                        is_array = true;
                    }
                }
                
                // Get initializer if present
                if (init_decl->children.size() > 1) {
                    init_node = init_decl->children[1];
                }
                
                if (var_name.empty()) continue;
                
                // Handle static variables
                if (is_static) {
                    std::string static_var = get_static_variable_name(var_name);
                    
                    std::cerr << "DEBUG: Found static variable: " << var_name << " -> " << static_var << std::endl;
                    
                    // Check if already initialized BEFORE doing anything
                    if (static_variables.find(static_var) != static_variables.end()) {
                        std::cerr << "DEBUG: Skipping re-initialization of " << static_var << std::endl;
                        continue;  // Skip to next declaration
                    }
                    
                    // Mark as initialized IMMEDIATELY, before generating any TAC
                    static_variables.insert(static_var);
                    
                    std::cerr << "DEBUG: Initializing " << static_var << " for the first time" << std::endl;
                    
                    // Now generate initialization code (only happens once)
                    if (is_array) {
                        array_dims[static_var] = dims;
                        
                        if (init_node) {
                            flatten_array_initialization(static_var, dims, init_node, {});
                        } else {
                            // Zero-initialize static array
                            int total_size = 1;
                            for (int d : dims) total_size *= d;
                            
                            for (int i = 0; i < total_size; ++i) {
                                tac->generate_array_store(static_var, std::to_string(i), "0");
                            }
                        }
                    } else {
                        // Regular static variable
                        if (init_node) {
                            std::string init_val = generate_expression(init_node);
                            tac->generate_assignment(static_var, init_val);
                        } else {
                            // Initialize to 0
                            tac->generate_assignment(static_var, "0");
                        }
                    }
                }
                // Handle regular (non-static) variables
                else {
                    if (is_array) {
                        array_dims[var_name] = dims;
                        
                        if (init_node) {
                            flatten_array_initialization(var_name, dims, init_node, {});
                        }
                    } else {
                        // Regular variable initialization
                        if (init_node) {
                            std::string init_val = generate_expression(init_node);
                            tac->generate_assignment(var_name, init_val);
                        }
                    }
                }
            }  // End of init_decl loop
        }
    }
}


// =======================================================
//  Utility Functions
// =======================================================

std::string CodeGenerator::extract_declarator_name(ASTNode* node) {
    if (!node) return "";
    if (!node->lexeme.empty() && node->lexeme != "default") return node->lexeme;
    for (auto child : node->children) {
        std::string name = extract_declarator_name(child);
        if (!name.empty()) return name;
    }
    return "";
}

// ===== Array Helpers =====

// Helper to get the base array name from nested subscripts
std::string CodeGenerator::get_base_array_name(ASTNode* node) {
    if (!node) return "";
    
    if (node->name == "Identifier") {
        return node->lexeme;
    }
    
    if (node->name == "ArraySubscript" && node->children.size() > 0) {
        return get_base_array_name(node->children[0]);
    }
    
    return "";
}

// Helper to collect all array indices in order
void CodeGenerator::collect_array_indices(ASTNode* node, std::vector<std::string>& indices) {
    if (!node || node->name != "ArraySubscript") return;
    
    // Recurse to inner subscript first
    if (node->children[0]->name == "ArraySubscript") {
        collect_array_indices(node->children[0], indices);
    }
    
    // Then add this level's index
    if (node->children.size() > 1) {
        std::string index = generate_expression(node->children[1]);
        indices.push_back(index);
    }
}

int CodeGenerator::getArrayNumCols(const std::string &name) {
    auto it = array_dims.find(name);
    if (it == array_dims.end()) return -1;
    const std::vector<int>& dims = it->second;
    if (dims.empty()) return -1;
    return dims.back(); // last dimension = columns
}

std::vector<int> CodeGenerator::extract_array_dimensions(ASTNode* node) {
    std::vector<int> dims;
    if (!node) return dims;
    if (node->name == "ArrayDeclarator") {
        for (auto child : node->children) {
            if (!child) continue;
            if (child->name == "Constant") {
                try { dims.push_back(std::stoi(child->lexeme)); } catch (...) {}
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
// =======================================================
//  Static Variable Helpers
// =======================================================

bool CodeGenerator::is_static_declaration(ASTNode* node) {
    if (!node) return false;
    
    // Check if any child node has "static" storage class
    for (auto child : node->children) {
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            for (auto spec : child->children) {
                // ✅ CHANGED: Check for "StorageClass" instead of "StorageClassSpecifier"
                if (spec && spec->name == "StorageClass" && 
                    spec->lexeme == "static") {
                    return true;
                }
            }
        }
    }
    return false;
}
bool CodeGenerator::is_array(ASTNode* node) {
    if (!node) return false;
    
    // Case 1: Direct array identifier
    if (node->name == "Identifier") {
        // Check if we have array dimensions stored for this variable
        return array_dims.find(node->lexeme) != array_dims.end();
    }
    
    // Case 2: Array declarator in declarations
    if (node->name == "ArrayDeclarator") {
        return true;
    }
    
    // Case 3: Check children recursively
    for (auto child : node->children) {
        if (is_array(child)) return true;
    }
    
    return false;
}
bool CodeGenerator::is_void_function(const std::string& func_name) {
    if (!symbol_table) return false;  // Fallback if no symbol table
    
    Symbol* sym = symbol_table->find_symbol(func_name);
    if (sym && sym->symbol_type == "function") {
        return sym->base_type == "void";
    }
    
    // Fallback for known library functions
    return func_name == "printf" || func_name == "scanf";
}
std::string CodeGenerator::get_static_variable_name(const std::string& var_name) {
    // Create a unique name for static variable: function_name.var_name
    return current_function_name + "." + var_name;
}

void CodeGenerator::process_enum_declaration(ASTNode* node) {
    if (!node || node->name != "EnumSpecifier") return;
    
    int current_value = 0;
    
    // Find the EnumeratorList
    for (auto child : node->children) {
        if (child->name == "EnumeratorList") {
            for (auto enumerator : child->children) {
                if (enumerator->name == "Enumerator") {
                    std::string enum_name = enumerator->lexeme;
                    
                    // Check if this enumerator has an explicit value
                    if (!enumerator->children.empty() && 
                        enumerator->children[0]->name == "Constant") {
                        current_value = std::stoi(enumerator->children[0]->lexeme);
                    }
                    
                    // Store the enum constant
                    enum_constants[enum_name] = std::to_string(current_value);
                    std::cout << "DEBUG: Enum constant " << enum_name << " = " << current_value << std::endl;
                    
                    current_value++;  // Auto-increment for next enumerator
                }
            }
        }
    }
}