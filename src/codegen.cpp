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
    
    tac->add_label(func_name);
    
    for (auto child : node->children) {
        if (child->name == "CompoundStatement") {
            generate_compound_statement(child);
        }
    }
    
    tac->generate_return();
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
    else if (node->name == "DoWhileStatement") generate_do_while_statement(node);  // ✅ ADD
    else if (node->name == "SwitchStatement") generate_switch_statement(node);      // ✅ ADD
    else if (node->name == "BreakStatement") generate_break_statement(node);        // ✅ ADD
    else if (node->name == "ContinueStatement") generate_continue_statement(node);  // ✅ ADD
    else if (node->name == "CaseStatement") generate_case_statement(node);          // ✅ ADD
    else if (node->name == "DefaultStatement") generate_default_statement(node);    // ✅ ADD
    else if (node->name == "ReturnStatement") generate_return_statement(node);
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
    if (node->name == "Identifier") return node->lexeme;

    // Constant
    if (node->name == "Constant") return node->lexeme;

    // String literal
    if (node->name == "StringLiteral") return node->lexeme;

  
    if (node->name == "TypeName") {
        return "";
    }

   
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


    // Assignment Expression
    if (node->name == "AssignmentExpression") {
        if (node->children.size() >= 2) {
            std::string lhs = generate_expression(node->children[0]);
            std::string rhs = generate_expression(node->children[1]);
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
    else if (node->lexeme == "+"
          || node->lexeme == "-"
          || node->lexeme == "!"
          || node->lexeme == "~") {
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
        std::string result = tac->new_temp();
        tac->generate_call(func_name, param_count, result);
        return result;
    }

    // =======================================================
    //  ✅ Fixed Array Subscript: handles arr[i][j]
    // =======================================================
   // Array subscript (flattened for multi-dimensional arrays)
if (node->name == "ArraySubscript") {
    std::string array_name = generate_expression(node->children[0]);
    ASTNode* index_node = node->children[1];

    // Generate TAC for index expression
    std::string index_val = generate_expression(index_node);

    // Flattened index computation if array is multidimensional
    if (array_dims.find(array_name) != array_dims.end()) {
        const auto& dims = array_dims[array_name];
        std::string offset = index_val;

        // Walk up the parent ArraySubscript nodes for higher dimensions
        ASTNode* current = node->parent;
        int dim_level = dims.size() - 1;
        while (current && current->name == "ArraySubscript" && dim_level > 0) {
            std::string prev_index = generate_expression(current->children[1]);
            std::string t_mul = tac->new_temp();
            tac->generate_binary_op("*", prev_index, std::to_string(dims[dim_level]), t_mul);

            std::string t_sum = tac->new_temp();
            tac->generate_binary_op("+", t_mul, offset, t_sum);
            offset = t_sum;

            current = current->parent;
            dim_level--;
        }

        std::string result = tac->new_temp();
        tac->generate_array_access(array_name, offset, result);
        return result;
    } else {
        // Fallback for 1D array
        std::string result = tac->new_temp();
        tac->generate_array_access(array_name, index_val, result);
        return result;
    }
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
    
    // ✅ ADD THESE:
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
    
    // ✅ ADD THESE:
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
    std::string label_increment = tac->new_label();  // ✅ ADD THIS
    
    // ✅ ADD THESE:
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
    
    tac->add_label(label_increment);  // ✅ ADD THIS
    if (node->children.size() == 4) generate_expression(node->children[2]);
    
    tac->generate_goto(label_start);
    tac->add_label(label_end);
    
    // ✅ ADD THESE:
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

    // Handle variable initialization
    for (auto child : node->children) {
        if (child->name == "InitDeclaratorList") {
            for (auto init_decl : child->children) {
                if (init_decl->name == "InitDeclarator") {
                    ASTNode* declarator = init_decl->children[0];

                    // Extract variable/array name
                    std::string var_name = extract_declarator_name(declarator);
                    if (var_name.empty()) continue;

                    // Store array dimensions if present
                    std::vector<int> dims = extract_array_dimensions(declarator);
                    if (!dims.empty()) {
                        array_dims[var_name] = dims;
                    }

                    // Handle initialization
                    if (init_decl->children.size() >= 2) {
                        ASTNode* init_val_node = init_decl->children[1];

                        // If it's a simple scalar initialization
                        if (dims.empty()) {
                            std::string init_val = generate_expression(init_val_node);
                            if (!init_val.empty()) {
                                tac->generate_assignment(var_name, init_val);
                            }
                        } else {
                            // Array initialization (flatten multi-dimensional)
                            flatten_array_initialization(var_name, dims, init_val_node, {});
                        }
                    }
                }
            }
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

// Add these member variables to your CodeGenerator class header:
// std::string current_break_label;
// std::string current_continue_label;

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


