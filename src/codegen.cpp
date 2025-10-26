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
    
    for (auto child : node->children) {
        if (!child) continue;
        
        // ✅ NEW: Process struct/union definitions FIRST
        if (child->name == "Declaration") {
            for (auto decl_spec : child->children) {
                if (decl_spec->name == "DeclarationSpecifiers") {
                    for (auto spec : decl_spec->children) {
                        if (spec->name == "StructOrUnionSpecifier") {
                            // Get type name
                            std::string type_name = "";
                            for (auto id : spec->children) {
                                if (id->name == "Identifier") {
                                    type_name = id->lexeme;
                                    break;
                                }
                            }
                            if (!type_name.empty()) {
                                process_struct_union_definition(spec, type_name);
                            }
                        }
                    }
                }
            }
        }
        
        // Handle function definitions
        if (child->name == "FunctionDefinition") {
            // Collect return type first
            std::string func_name = "unknown";
            std::string return_type = "int";
            
            for (auto grandchild : child->children) {
                if (grandchild->name == "DeclarationSpecifiers") {
                    return_type = extract_type_from_decl_specifiers(grandchild);
                }
                else if (grandchild->name == "FunctionDeclarator" || 
                         grandchild->name == "Declarator") {
                    func_name = extract_declarator_name(grandchild);
                }
            }
            
            if (func_name != "unknown") {
                function_return_types[func_name] = return_type;
            }
            
            // Generate function code
            generate_function_definition(child);
            continue;
        }
        
        // Handle declarations
        if (child->name == "Declaration") {
            generate_declaration(child);
            continue;
        }
        
        // Handle enum definitions
        if (child->name == "EnumSpecifier") {
            process_enum_declaration(child);
            continue;
        }
        
        // For TranslationUnit and other nodes, traverse deeper
        generate_node(child);
    }
}

std::string CodeGenerator::extract_type_from_decl_specifiers(ASTNode* decl_specifiers) {
    if (!decl_specifiers) return "int";
    
    for (auto child : decl_specifiers->children) {
        if (child->name == "TypeSpecifier") {
            return child->lexeme;
        }
    }
    
    return "int";
}

// ✅ NEW: Process struct/union definitions to track member offsets
void CodeGenerator::process_struct_union_definition(ASTNode* node, const std::string& type_name) {
    if (!node || type_name.empty()) return;
    
    bool is_union = false;
    
    // Check if union or struct
    for (auto child : node->children) {
        if (child->name == "StructOrUnion" && child->lexeme == "union") {
            is_union = true;
            break;
        }
    }
    
    int offset = 0;
    
    // Process members
    for (auto child : node->children) {
        if (child->name == "StructDeclarationList") {
            for (auto decl : child->children) {
                if (decl->name == "StructDeclaration") {
                    
                    // Get member type for size
                    int member_size = 4; // default
                    for (auto spec : decl->children) {
                        if (spec->name == "TypeSpecifier") {
                            if (spec->lexeme == "char") member_size = 1;
                            else if (spec->lexeme == "short") member_size = 2;
                            else if (spec->lexeme == "int") member_size = 4;
                            else if (spec->lexeme == "long") member_size = 8;
                        }
                    }
                    
                    // Get member names
                    for (auto spec : decl->children) {
                        if (spec->name == "StructDeclaratorList") {
                            for (auto declarator : spec->children) {
                                std::string member_name = extract_declarator_name(declarator);
                                
                                if (!member_name.empty()) {
                                    member_offsets[type_name + "." + member_name] = is_union ? 0 : offset;
                                    
                                    // Only increment offset for structs
                                    if (!is_union) {
                                        // Handle arrays
                                        std::vector<int> dims = extract_array_dimensions(declarator);
                                        int total_size = member_size;
                                        for (int dim : dims) total_size *= dim;
                                        
                                        offset += total_size;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
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
    else if (node->name == "UntilStatement") generate_until_statement(node);
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
    tac->generate_goto(node->lexeme);
}

void CodeGenerator::generate_labeled_statement(ASTNode* node) {
    tac->add_label(node->lexeme);
    
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
        
        if (static_variables.find(static_var) != static_variables.end()) {
            return static_var;
        }
        
        auto it = enum_constants.find(var_name);
        if (it != enum_constants.end()) {
            return it->second;
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
            return generate_expression(node->children[1]);
        }
        if (node->children.size() == 1) {
            return generate_expression(node->children[0]);
        }
        return "";
    }

    // ✅ STRUCT MEMBER ACCESS - READ (with offset support)
    if (node->name == "MemberAccess" || node->name == "StructMemberAccess") {
        std::string base = generate_expression(node->children[0]);
        std::string field = node->children[1]->lexeme;
        
        std::string addr_temp = tac->new_temp();
        tac->generate_address_of(base, addr_temp);
        
        // ✅ Get offset
        auto it = variable_types.find(base);
        int offset = 0;
        if (it != variable_types.end()) {
            std::string key = it->second + "." + field;
            auto offset_it = member_offsets.find(key);
            if (offset_it != member_offsets.end()) {
                offset = offset_it->second;
            }
        }
        
        std::string result_temp = tac->new_temp();
        
        if (offset == 0) {
            tac->generate_load(result_temp, addr_temp);
        } else {
            std::string offset_addr = tac->new_temp();
            tac->generate_binary_op("+", addr_temp, std::to_string(offset), offset_addr);
            tac->generate_load(result_temp, offset_addr);
        }
        
        return result_temp;
    }

    // Assignment Expression
    if (node->name == "AssignmentExpression") {
        if (node->children.size() >= 2) {
            ASTNode* lhs_node = node->children[0];
            std::string rhs = generate_expression(node->children[1]);

            // Handle pointer dereference assignment
            if (lhs_node->name == "UnaryExpression" && lhs_node->lexeme == "*") {
                std::string pointer = generate_expression(lhs_node->children[0]);
                tac->generate_store(pointer, rhs);
                return rhs;
            }
            
            // ✅ STRUCT MEMBER ACCESS - WRITE (with offset support)
            if (lhs_node->name == "MemberAccess" || lhs_node->name == "StructMemberAccess") {
                std::string base = generate_expression(lhs_node->children[0]);
                std::string field = lhs_node->children[1]->lexeme;
                
                if (node->lexeme == "=") {
                    std::string addr_temp = tac->new_temp();
                    tac->generate_address_of(base, addr_temp);
                    
                    // ✅ Get offset
                    auto it = variable_types.find(base);
                    int offset = 0;
                    if (it != variable_types.end()) {
                        std::string key = it->second + "." + field;
                        auto offset_it = member_offsets.find(key);
                        if (offset_it != member_offsets.end()) {
                            offset = offset_it->second;
                        }
                    }
                    
                    if (offset == 0) {
                        tac->generate_store(addr_temp, rhs);
                    } else {
                        std::string offset_addr = tac->new_temp();
                        tac->generate_binary_op("+", addr_temp, std::to_string(offset), offset_addr);
                        tac->generate_store(offset_addr, rhs);
                    }
                    
                    return base;
                } else {
                    // Compound assignment
                    std::string addr_temp = tac->new_temp();
                    tac->generate_address_of(base, addr_temp);
                    
                    // ✅ Get offset
                    auto it = variable_types.find(base);
                    int offset = 0;
                    if (it != variable_types.end()) {
                        std::string key = it->second + "." + field;
                        auto offset_it = member_offsets.find(key);
                        if (offset_it != member_offsets.end()) {
                            offset = offset_it->second;
                        }
                    }
                    
                    std::string effective_addr = addr_temp;
                    if (offset != 0) {
                        effective_addr = tac->new_temp();
                        tac->generate_binary_op("+", addr_temp, std::to_string(offset), effective_addr);
                    }
                    
                    std::string temp_load = tac->new_temp();
                    tac->generate_load(temp_load, effective_addr);
                    
                    std::string temp_result = tac->new_temp();
                    std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                    tac->generate_binary_op(op, temp_load, rhs, temp_result);
                    
                    tac->generate_store(effective_addr, temp_result);
                    return base;
                }
            }
            
            // Array subscript assignment
            if (lhs_node->name == "ArraySubscript") {
                std::string index = generate_expression(lhs_node->children[1]);
                
                // Multi-dimensional array
                if (lhs_node->children[0]->name == "ArraySubscript") {
                    std::string base_array = get_base_array_name(lhs_node);
                    std::vector<std::string> indices;
                    collect_array_indices(lhs_node, indices);
                    
                    if (array_dims.find(base_array) != array_dims.end()) {
                        const auto& dims = array_dims[base_array];
                        
                        // ✅ CORRECT: Multi-dimensional offset calculation
                        std::string offset = "0";
                        
                        for (size_t i = 0; i < indices.size(); ++i) {
                            // Calculate stride for this dimension
                            int stride = 1;
                            for (size_t j = i + 1; j < dims.size(); ++j) {
                                stride *= dims[j];
                            }
                            
                            if (stride == 1) {
                                if (offset == "0") {
                                    offset = indices[i];
                                } else {
                                    std::string temp = tac->new_temp();
                                    tac->generate_binary_op("+", offset, indices[i], temp);
                                    offset = temp;
                                }
                            } else {
                                std::string term = tac->new_temp();
                                tac->generate_binary_op("*", indices[i], std::to_string(stride), term);
                                
                                if (offset == "0") {
                                    offset = term;
                                } else {
                                    std::string temp = tac->new_temp();
                                    tac->generate_binary_op("+", offset, term, temp);
                                    offset = temp;
                                }
                            }
                        }
                        
                        // Convert to byte offset
                        std::string byte_offset = tac->new_temp();
                        tac->generate_binary_op("*", offset, "4", byte_offset);
                        
                        std::string base_addr = tac->new_temp();
                        tac->generate_address_of(base_array, base_addr);
                        
                        std::string final_addr = tac->new_temp();
                        tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
                        
                        if (node->lexeme == "=") {
                            tac->generate_store(final_addr, rhs);
                            return base_array;
                        } else {
                            // Compound assignment
                            std::string temp_load = tac->new_temp();
                            tac->generate_load(temp_load, final_addr);
                            
                            std::string temp_result = tac->new_temp();
                            std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                            tac->generate_binary_op(op, temp_load, rhs, temp_result);
                            
                            tac->generate_store(final_addr, temp_result);
                            return base_array;
                        }
                    }
                }
                
                // Regular 1D array
                std::string array_base = generate_expression(lhs_node->children[0]);
                
                std::string byte_offset = tac->new_temp();
                tac->generate_binary_op("*", index, "4", byte_offset);
                
                std::string base_addr = tac->new_temp();
                tac->generate_address_of(array_base, base_addr);
                
                std::string final_addr = tac->new_temp();
                tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
                
                if (node->lexeme == "=") {
                    tac->generate_store(final_addr, rhs);
                    return array_base;
                } else {
                    // Compound assignment
                    std::string temp_load = tac->new_temp();
                    tac->generate_load(temp_load, final_addr);
                    
                    std::string temp_result = tac->new_temp();
                    std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                    tac->generate_binary_op(op, temp_load, rhs, temp_result);
                    
                    tac->generate_store(final_addr, temp_result);
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
            tac->generate_address_of(arg, result);
        }
        else if (node->lexeme == "*") {
            tac->generate_load(result, arg);
        }
        else if (node->lexeme == "+" || node->lexeme == "-" || 
                 node->lexeme == "!" || node->lexeme == "~") {
            tac->generate_unary_op("unary" + node->lexeme, arg, result);
        }
        else {
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
        
        if (is_void_function(func_name)) {
            tac->generate_call(func_name, param_count);
            return "";
        } else {
            std::string result = tac->new_temp();
            tac->generate_call(func_name, param_count, result);
            return result;
        }
    }

    // Array subscript
    if (node->name == "ArraySubscript") {
        // Multi-dimensional
        if (node->children[0]->name == "ArraySubscript") {
            std::string base_array = get_base_array_name(node);
            std::vector<std::string> indices;
            collect_array_indices(node, indices);
            
            if (array_dims.find(base_array) != array_dims.end()) {
                const auto& dims = array_dims[base_array];
                
                // ✅ CORRECT: Multi-dimensional offset calculation
                std::string offset = "0";
                
                for (size_t i = 0; i < indices.size(); ++i) {
                    // Calculate stride for this dimension
                    int stride = 1;
                    for (size_t j = i + 1; j < dims.size(); ++j) {
                        stride *= dims[j];
                    }
                    
                    if (stride == 1) {
                        if (offset == "0") {
                            offset = indices[i];
                        } else {
                            std::string temp = tac->new_temp();
                            tac->generate_binary_op("+", offset, indices[i], temp);
                            offset = temp;
                        }
                    } else {
                        std::string term = tac->new_temp();
                        tac->generate_binary_op("*", indices[i], std::to_string(stride), term);
                        
                        if (offset == "0") {
                            offset = term;
                        } else {
                            std::string temp = tac->new_temp();
                            tac->generate_binary_op("+", offset, term, temp);
                            offset = temp;
                        }
                    }
                }
                
                // Convert to byte offset and load
                std::string byte_offset = tac->new_temp();
                tac->generate_binary_op("*", offset, "4", byte_offset);
                
                std::string base_addr = tac->new_temp();
                tac->generate_address_of(base_array, base_addr);
                
                std::string final_addr = tac->new_temp();
                tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
                
                std::string result = tac->new_temp();
                tac->generate_load(result, final_addr);
                return result;
            }
        }
        
        // Simple 1D array
        std::string index_val = generate_expression(node->children[1]);

        // Array member of struct/union
        if (node->children[0]->name == "MemberAccess" || 
            node->children[0]->name == "StructMemberAccess") {
            
            std::string base = generate_expression(node->children[0]->children[0]);
            std::string addr_temp = tac->new_temp();
            tac->generate_address_of(base, addr_temp);
            
            std::string result = tac->new_temp();
            
            if (index_val == "0") {
                tac->generate_load(result, addr_temp);
            } else {
                std::string offset_temp = tac->new_temp();
                tac->generate_binary_op("+", addr_temp, index_val, offset_temp);
                tac->generate_load(result, offset_temp);
            }
            
            return result;
        } else {
            std::string array_name = generate_expression(node->children[0]);
        
            std::string byte_offset = tac->new_temp();
            tac->generate_binary_op("*", index_val, "4", byte_offset);
            
            std::string base_addr = tac->new_temp();
            tac->generate_address_of(array_name, base_addr);
            
            std::string final_addr = tac->new_temp();
            tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
            
            std::string result = tac->new_temp();
            tac->generate_load(result, final_addr);
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
void CodeGenerator::generate_until_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string old_break = current_break_label;
    std::string old_continue = current_continue_label;
    
    std::string condition_label = tac->new_label();
    std::string end_label = tac->new_label();
    
    current_break_label = end_label;
    current_continue_label = condition_label;
    tac->add_label(condition_label);
    std::string condition_temp = generate_expression(node->children[0]);
    tac->generate_if_goto(condition_temp, end_label);
    
    // Loop body
    generate_statement(node->children[1]);
    tac->generate_goto(condition_label);
    tac->add_label(end_label);
    current_break_label = old_break;
    current_continue_label = old_continue;
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
    generate_statement(node->children[0]);
    std::string cond = generate_expression(node->children[1]);
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
    
    generate_statement(node->children[1]);
    
    tac->add_label(end_label);
    current_break_label = old_break;
}

void CodeGenerator::generate_case_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string case_label = tac->new_label();
    tac->add_label(case_label);
    
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

std::string CodeGenerator::flatten_array_initialization(const std::string &array_name,
                                                       const std::vector<int> &dims,
                                                       ASTNode* init_node,
                                                       std::vector<int> indices,
                                                       std::string base_temp) {
    if (!init_node) return base_temp;

    if (init_node->name == "InitializerList") {
        // Compute base address on first call
        if (base_temp.empty()) {
            base_temp = tac->new_temp();
            tac->generate_address_of(array_name, base_temp);
        }
        
        // ✅ FIX: Check if this InitializerList has InitializerList children or Initializer children
        bool has_initlist_children = false;
        bool has_initializer_children = false;
        
        for (auto child : init_node->children) {
            if (child) {
                if (child->name == "InitializerList") has_initlist_children = true;
                if (child->name == "Initializer") has_initializer_children = true;
            }
        }
        
        // If only one InitializerList child, it's a wrapper - skip it
        if (has_initlist_children && !has_initializer_children && init_node->children.size() == 1) {
            return flatten_array_initialization(array_name, dims, init_node->children[0], indices, base_temp);
        }
        // If multiple InitializerList children (no Initializer), it's a dimension boundary
        else if (has_initlist_children && !has_initializer_children) {
            for (size_t i = 0; i < init_node->children.size(); ++i) {
                if (init_node->children[i]->name == "InitializerList") {
                    std::vector<int> new_indices = indices;
                    new_indices.push_back(i);
                    base_temp = flatten_array_initialization(array_name, dims, init_node->children[i], new_indices, base_temp);
                }
            }
        }
        // If has Initializer children, it's the value level
        else if (has_initializer_children) {
            for (size_t i = 0; i < init_node->children.size(); ++i) {
                std::vector<int> new_indices = indices;
                new_indices.push_back(i);
                base_temp = flatten_array_initialization(array_name, dims, init_node->children[i], new_indices, base_temp);
            }
        }
        
        return base_temp;
    }
    else if (init_node->name == "Initializer") {
        // ✅ Initializer is just a wrapper - don't add index, just recurse
        return flatten_array_initialization(array_name, dims, init_node->children[0], indices, base_temp);
    }
    else {
        // Leaf - actual value
        std::string value = generate_expression(init_node);
        
        // ✅ FIX: Use only the last dims.size() indices
        std::vector<int> actual_indices;
        if (indices.size() >= dims.size()) {
            actual_indices.assign(indices.end() - dims.size(), indices.end());
        } else {
            actual_indices = indices;
        }
        
        // Calculate flat offset using row-major order
        int flat_index = 0;
        for (size_t i = 0; i < actual_indices.size(); ++i) {
            int stride = 1;
            for (size_t j = i + 1; j < dims.size(); ++j) {
                stride *= dims[j];
            }
            flat_index += actual_indices[i] * stride;
        }
        
        // Store using base + offset
        int byte_offset = flat_index * 4; // sizeof(int) = 4
        
        if (byte_offset == 0) {
            tac->generate_store(base_temp, value);
        } else {
            std::string element_addr = tac->new_temp();
            tac->generate_binary_op("+", base_temp, std::to_string(byte_offset), element_addr);
            tac->generate_store(element_addr, value);
        }
        
        return base_temp;
    }
}


void CodeGenerator::generate_declaration(ASTNode* node) {
    if (!node) return;
    
    // ✅ NEW: Get type name for this declaration
    std::string type_name = "";
    for (auto child : node->children) {
        if (child->name == "DeclarationSpecifiers") {
            for (auto spec : child->children) {
                if (spec->name == "EnumSpecifier") {
                    process_enum_declaration(spec);
                }
                if (spec->name == "StructOrUnionSpecifier") {
                    for (auto id : spec->children) {
                        if (id->name == "Identifier") {
                            type_name = id->lexeme;
                            break;
                        }
                    }
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

                std::string var_name;
                ASTNode* init_node = nullptr;
                bool is_array = false;
                std::vector<int> dims;
                
                if (init_decl->children.size() > 0) {
                    var_name = extract_declarator_name(init_decl->children[0]);
                    
                    dims = extract_array_dimensions(init_decl->children[0]);
                    if (!dims.empty()) {
                        is_array = true;
                    }
                }
                
                if (init_decl->children.size() > 1) {
                    init_node = init_decl->children[1];
                }
                
                if (var_name.empty()) continue;
                
                // ✅ NEW: Track variable type
                if (!type_name.empty()) {
                    variable_types[var_name] = type_name;
                }
                
                if (is_static) {
                    std::string static_var = get_static_variable_name(var_name);
                    
                    if (static_variables.find(static_var) != static_variables.end()) {
                        continue;
                    }
                    
                    static_variables.insert(static_var);
                    
                    if (is_array) {
                        array_dims[static_var] = dims;
                        
                        if (init_node) {
                            std::vector<int> empty_indices;
std::string empty_base;
flatten_array_initialization(var_name, dims, init_node, empty_indices, empty_base);
                        } else {
                            int total_size = 1;
                            for (int d : dims) total_size *= d;
                            
                            for (int i = 0; i < total_size; ++i) {
                                tac->generate_array_store(static_var, std::to_string(i), "0");
                            }
                        }
                    } else {
                        if (init_node) {
                            std::string init_val = generate_expression(init_node);
                            tac->generate_assignment(static_var, init_val);
                        } else {
                            tac->generate_assignment(static_var, "0");
                        }
                    }
                } else {
                    if (is_array) {
                        array_dims[var_name] = dims;
                        
                        if (init_node) {
                            std::vector<int> empty_indices;
std::string empty_base;
flatten_array_initialization(var_name, dims, init_node, empty_indices, empty_base);
                        }
                    } else {
                        if (init_node) {
                            std::string init_val = generate_expression(init_node);
                            tac->generate_assignment(var_name, init_val);
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

void CodeGenerator::collect_array_indices(ASTNode* node, std::vector<std::string>& indices) {
    if (!node || node->name != "ArraySubscript") return;
    
    if (node->children[0]->name == "ArraySubscript") {
        collect_array_indices(node->children[0], indices);
    }
    
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
    return dims.back();
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
    
    for (auto child : node->children) {
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            for (auto spec : child->children) {
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
    
    if (node->name == "Identifier") {
        return array_dims.find(node->lexeme) != array_dims.end();
    }
    
    if (node->name == "ArrayDeclarator") {
        return true;
    }
    
    for (auto child : node->children) {
        if (is_array(child)) return true;
    }
    
    return false;
}
// Add this in codegen.cpp (after the existing functions)
int CodeGenerator::get_type_size(const std::string& type) {
    if (type == "char") return 1;
    if (type == "short") return 2;
    if (type == "int") return 4;
    if (type == "long") return 8;
    return 4; // default
}
bool CodeGenerator::is_void_function(const std::string& func_name) {
    if (func_name == "printf" || func_name == "scanf") return false;
    auto it = function_return_types.find(func_name);
    return it != function_return_types.end() && it->second == "void";
}

std::string CodeGenerator::get_static_variable_name(const std::string& var_name) {
    return current_function_name + "." + var_name;
}

void CodeGenerator::process_enum_declaration(ASTNode* node) {
    if (!node || node->name != "EnumSpecifier") return;
    
    int current_value = 0;
    
    for (auto child : node->children) {
        if (child->name == "EnumeratorList") {
            for (auto enumerator : child->children) {
                if (enumerator->name == "Enumerator") {
                    std::string enum_name = enumerator->lexeme;
                    
                    if (!enumerator->children.empty() && 
                        enumerator->children[0]->name == "Constant") {
                        current_value = std::stoi(enumerator->children[0]->lexeme);
                    }
                    
                    enum_constants[enum_name] = std::to_string(current_value);
                    
                    current_value++;
                }
            }
        }
    }
}