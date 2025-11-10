#include "codegen.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <algorithm>

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

// Process struct/union definitions to track member offsets
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
                    
                    // Get member type for size and type tracking
                    std::string member_type = "int"; // default
                    int member_size = 4; // default
                    
                    for (auto spec : decl->children) {
                        if (spec->name == "TypeSpecifier") {
                            member_type = spec->lexeme;
                            if (spec->lexeme == "char") member_size = 1;
                            else if (spec->lexeme == "short") member_size = 2;
                            else if (spec->lexeme == "int") member_size = 4;
                            else if (spec->lexeme == "long") member_size = 8;
                        }
                        // Check for nested struct
                        else if (spec->name == "StructOrUnionSpecifier") {
                            for (auto sub : spec->children) {
                                if (sub->name == "Identifier") {
                                    member_type = sub->lexeme;
                                    member_size = 4; // struct/union reference size (could calculate actual size)
                                    break;
                                }
                            }
                        }
                    }
                    
                    // Get member names
                    for (auto spec : decl->children) {
                        if (spec->name == "StructDeclaratorList") {
                            for (auto declarator : spec->children) {
                                std::string member_name = extract_declarator_name(declarator);
                                
                                if (!member_name.empty()) {
                                    member_offsets[type_name + "." + member_name] = is_union ? 0 : offset;
                                    
                                    // Store member type for nested struct lookups
                                    variable_types[type_name + "." + member_name] = member_type;
                                    
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
    
    // Pre-pass: collect variables whose addresses are taken
    address_taken_vars.clear();
    for (auto child : node->children) {
        if (child->name == "CompoundStatement") {
            collect_address_taken_vars(child);
        }
    }
    
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
        auto ref_it = references.find(var_name);
        if (ref_it != references.end()) {
            std::string result = tac->new_temp();
            tac->generate_load(result, var_name);
            return result;
        }
        std::string static_var = get_static_variable_name(var_name);
        
        if (static_variables.find(static_var) != static_variables.end()) {
            return static_var;
        }
        
        auto it = enum_constants.find(var_name);
        if (it != enum_constants.end()) {
            return it->second;
        }
        
        // Check if this is an address-taken variable (stored as single-element array)
        if (address_taken_vars.find(var_name) != address_taken_vars.end()) {
            // Load from array index 0
            std::string result = tac->new_temp();
            tac->generate_array_access(var_name, "0", result);
            return result;
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

    // STRUCT MEMBER ACCESS - READ (with offset support)
    if (node->name == "MemberAccess" || node->name == "StructMemberAccess") {
        // Use generate_member_address to get the address without loading
        std::string member_addr = generate_member_address(node);
        
        if (member_addr.empty()) {
            // Fallback to old method if generate_member_address failed
            std::string base = generate_expression(node->children[0]);
            std::string field = node->children[1]->lexeme;
            
            std::string addr_temp = tac->new_temp();
            tac->generate_address_of(base, addr_temp);
            
            // Get offset
            auto it = variable_types.find(base);
            int offset = 0;
            if (it != variable_types.end()) {
                std::string key = it->second + "." + field;
                auto offset_it = member_offsets.find(key);
                if (offset_it != member_offsets.end()) {
                    offset = offset_it->second;
                }
            }
            
            if (offset != 0) {
                std::string offset_addr = tac->new_temp();
                tac->generate_binary_op("+", addr_temp, std::to_string(offset), offset_addr);
                member_addr = offset_addr;
            } else {
                member_addr = addr_temp;
            }
        }
        
        // Load the value from the member address
        std::string result_temp = tac->new_temp();
        tac->generate_load(result_temp, member_addr);
        
        return result_temp;
    }

    // Assignment Expression
    if (node->name == "AssignmentExpression") {
        if (node->children.size() >= 2) {
            ASTNode* lhs_node = node->children[0];
            std::string rhs = generate_expression(node->children[1]);

            if (lhs_node->name == "Identifier") {
                std::string lhs_name = lhs_node->lexeme;
                auto ref_it = references.find(lhs_name);
                if (ref_it != references.end()) {
                    tac->generate_store(lhs_name, rhs);
                    return rhs;
                }
            }

            // Handle pointer dereference assignment
            if (lhs_node->name == "UnaryExpression" && lhs_node->lexeme == "*") {
                std::string pointer = generate_expression(lhs_node->children[0]);
                tac->generate_store(pointer, rhs);
                return rhs;
            }
            
            // STRUCT MEMBER ACCESS - WRITE (with offset support)
            if (lhs_node->name == "MemberAccess" || lhs_node->name == "StructMemberAccess") {
                if (node->lexeme == "=") {
                    // Use generate_member_address for proper nested struct handling
                    std::string member_addr = generate_member_address(lhs_node);
                    
                    if (!member_addr.empty()) {
                        tac->generate_store(member_addr, rhs);
                    } else {
                        // Fallback to old method
                        std::string base = generate_expression(lhs_node->children[0]);
                        std::string field = lhs_node->children[1]->lexeme;
                        
                        std::string addr_temp = tac->new_temp();
                        tac->generate_address_of(base, addr_temp);
                        
                        // Get offset
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
                    }
                    
                    return rhs;
                } else {
                    // Compound assignment (+=, -=, etc.)
                    std::string member_addr = generate_member_address(lhs_node);
                    
                    if (member_addr.empty()) {
                        // Fallback
                        return rhs;
                    }
                    
                    std::string temp_load = tac->new_temp();
                    tac->generate_load(temp_load, member_addr);
                    
                    std::string temp_result = tac->new_temp();
                    std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                    tac->generate_binary_op(op, temp_load, rhs, temp_result);
                    
                    tac->generate_store(member_addr, temp_result);
                    return temp_result;
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
                        
                        // CORRECT: Multi-dimensional offset calculation
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
                        
                        // Determine element size
                        int element_size = 4;
                        ASTNode* base_node = lhs_node->children[0];
                        while (base_node && base_node->name == "ArraySubscript") {
                            base_node = base_node->children[0];
                        }
                        if (base_node && base_node->symbol && base_node->symbol->is_array) {
                            element_size = get_type_size(base_node->symbol->base_type);
                        } else if (array_element_types.find(base_array) != array_element_types.end()) {
                            element_size = get_type_size(array_element_types[base_array]);
                        }
                        
                        // Convert to byte offset using element size
                        std::string byte_offset = tac->new_temp();
                        tac->generate_binary_op("*", offset, std::to_string(element_size), byte_offset);
                        
                        std::string base_addr = tac->new_temp();
                        tac->generate_address_of(base_array, base_addr);
                        
                        std::string final_addr = tac->new_temp();
                        tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
                        
                        if (node->lexeme == "=") {
                            tac->generate_store(final_addr, rhs, element_size);
                            return base_array;
                        } else {
                            // Compound assignment
                            std::string temp_load = tac->new_temp();
                            tac->generate_load(temp_load, final_addr, element_size);
                            
                            std::string temp_result = tac->new_temp();
                            std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                            tac->generate_binary_op(op, temp_load, rhs, temp_result);
                            
                            tac->generate_store(final_addr, temp_result, element_size);
                            return base_array;
                        }
                    }
                }
                
                // Regular 1D array
                ASTNode* array_node = lhs_node->children[0];
                std::string base_addr;
                std::string array_base;
                
                // Check if this is a struct member array
                if (array_node->name == "MemberAccess" || array_node->name == "StructMemberAccess") {
                    // Get address of the array member directly
                    base_addr = generate_member_address(array_node);
                    array_base = array_node->children[1]->lexeme; // for element size lookup
                } else {
                    // Regular array
                    array_base = generate_expression(array_node);
                    base_addr = tac->new_temp();
                    tac->generate_address_of(array_base, base_addr);
                }
                
                // Determine element size from symbol
                int element_size = 4;
                if (array_node && array_node->symbol && array_node->symbol->is_array) {
                    element_size = get_type_size(array_node->symbol->base_type);
                } else if (array_element_types.find(array_base) != array_element_types.end()) {
                    element_size = get_type_size(array_element_types[array_base]);
                }
                
                std::string byte_offset = tac->new_temp();
                tac->generate_binary_op("*", index, std::to_string(element_size), byte_offset);
                
                std::string final_addr = tac->new_temp();
                tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
                
                if (node->lexeme == "=") {
                    tac->generate_store(final_addr, rhs, element_size);
                    return array_base;
                } else {
                    // Compound assignment
                    std::string temp_load = tac->new_temp();
                    tac->generate_load(temp_load, final_addr, element_size);
                    
                    std::string temp_result = tac->new_temp();
                    std::string op = node->lexeme.substr(0, node->lexeme.length() - 1);
                    tac->generate_binary_op(op, temp_load, rhs, temp_result);
                    
                    tac->generate_store(final_addr, temp_result, element_size);
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
            
            // Special handling for pointer arithmetic
            if (node->name == "AdditiveExpression" && (node->lexeme == "+" || node->lexeme == "-")) {
                // Check if this is pointer arithmetic (ptr + int or ptr - int)
                bool arg1_is_pointer = false;
                bool arg2_is_pointer = false;
                int element_size = 4;
                
                // Check if arg1 is a pointer
                if (variable_types.find(arg1) != variable_types.end()) {
                    std::string type = variable_types[arg1];
                    if (type.find('*') != std::string::npos) {
                        arg1_is_pointer = true;
                        // Extract base type to get element size
                        size_t star_pos = type.find('*');
                        std::string base_type = type.substr(0, star_pos);
                        element_size = get_type_size(base_type);
                    }
                }
                
                // Check if arg2 is a pointer
                if (variable_types.find(arg2) != variable_types.end()) {
                    std::string type = variable_types[arg2];
                    if (type.find('*') != std::string::npos) {
                        arg2_is_pointer = true;
                    }
                }
                
                // If one is pointer and other is integer, scale the integer by element size
                if (arg1_is_pointer && !arg2_is_pointer) {
                    // ptr + int or ptr - int: scale arg2 by element_size
                    if (element_size != 1) {
                        std::string scaled_offset = tac->new_temp();
                        tac->generate_binary_op("*", arg2, std::to_string(element_size), scaled_offset);
                        tac->generate_binary_op(node->lexeme, arg1, scaled_offset, result);
                        return result;
                    }
                } else if (!arg1_is_pointer && arg2_is_pointer && node->lexeme == "+") {
                    // int + ptr: scale arg1 by element_size
                    if (element_size != 1) {
                        std::string scaled_offset = tac->new_temp();
                        tac->generate_binary_op("*", arg1, std::to_string(element_size), scaled_offset);
                        tac->generate_binary_op("+", scaled_offset, arg2, result);
                        return result;
                    }
                }
            }
            
            // Regular binary operation
            tac->generate_binary_op(node->lexeme, arg1, arg2, result);
            return result;
        }
    }

    // Unary operations
    if (node->name == "UnaryExpression" && node->children.size() >= 1) {
        std::string result = tac->new_temp();

        if (node->lexeme == "&") {
            // Special case: &(array_subscript) should compute address, not load value
            if (node->children[0]->name == "ArraySubscript") {
                // Generate address computation directly without dereferencing
                ASTNode* array_node = node->children[0];
                
                // Get the base array
                ASTNode* base = array_node;
                std::vector<ASTNode*> indices;
                
                // Collect all dimensions
                while (base->name == "ArraySubscript" && base->children.size() >= 2) {
                    indices.push_back(base->children[1]);  // index
                    base = base->children[0];  // go deeper
                }
                std::reverse(indices.begin(), indices.end());
                
                std::string array_name = base->lexeme;
                
                // Generate address calculation
                std::string base_addr = tac->new_temp();
                tac->generate_address_of(array_name, base_addr);
                
                // For 1D array
                if (indices.size() == 1) {
                    std::string index_val = generate_expression(indices[0]);
                    int element_size = 4;  // default
                    
                    // Try to get element size from symbol
                    if (array_node->symbol && array_node->symbol->is_array) {
                        element_size = get_type_size(array_node->symbol->base_type);
                    } 
                    // Try to get from array_element_types map
                    else if (array_element_types.find(array_name) != array_element_types.end()) {
                        element_size = get_type_size(array_element_types[array_name]);
                    }
                    
                    std::string byte_offset = tac->new_temp();
                    tac->generate_binary_op("*", index_val, std::to_string(element_size), byte_offset);
                    tac->generate_binary_op("+", base_addr, byte_offset, result);
                }
                // For 2D array
                else if (indices.size() == 2) {
                    // offset = (row * num_cols + col) * element_size
                    std::string row_val = generate_expression(indices[0]);
                    std::string col_val = generate_expression(indices[1]);
                    
                    int num_cols = array_dims[array_name][1];
                    int element_size = 4;
                    if (array_node->symbol && array_node->symbol->is_array) {
                        element_size = get_type_size(array_node->symbol->base_type);
                    }
                    
                    std::string row_offset = tac->new_temp();
                    tac->generate_binary_op("*", row_val, std::to_string(num_cols), row_offset);
                    std::string linear_index = tac->new_temp();
                    tac->generate_binary_op("+", row_offset, col_val, linear_index);
                    std::string byte_offset = tac->new_temp();
                    tac->generate_binary_op("*", linear_index, std::to_string(element_size), byte_offset);
                    tac->generate_binary_op("+", base_addr, byte_offset, result);
                }
            } else {
                // Check if taking address of an address-taken variable
                if (node->children[0]->name == "Identifier") {
                    std::string var_name = node->children[0]->lexeme;
                    if (address_taken_vars.find(var_name) != address_taken_vars.end()) {
                        // For address-taken variables (single-element arrays), 
                        // just get the array base address
                        tac->generate_address_of(var_name, result);
                        return result;
                    }
                }
                
                // Regular variable/expression
                std::string arg = generate_expression(node->children[0]);
                tac->generate_address_of(arg, result);
            }
        }
        else if (node->lexeme == "*") {
            std::string arg = generate_expression(node->children[0]);
            
            // Get element size for proper load instruction
            int element_size = 4; // default to int/pointer size
            
            // If dereferencing an identifier (variable), check its type
            if (node->children[0]->name == "Identifier") {
                std::string var_name = node->children[0]->lexeme;
                
                // Check if it's a pointer to char, use size 1
                if (variable_types.find(var_name) != variable_types.end()) {
                    std::string type = variable_types[var_name];
                    
                    // For pointer types like "char*", extract base type
                    if (type.find("char*") != std::string::npos || 
                        type.find("char *") != std::string::npos) {
                        element_size = 1;
                    } else if (type.find("short*") != std::string::npos || 
                              type.find("short *") != std::string::npos) {
                        element_size = 2;
                    }
                }
            }
            
            tac->generate_load(result, arg, element_size);
        }
        else if (node->lexeme == "+" || node->lexeme == "-" || 
                 node->lexeme == "!" || node->lexeme == "~") {
            std::string arg = generate_expression(node->children[0]);
            tac->generate_unary_op("unary" + node->lexeme, arg, result);
        }
        else {
            std::string arg = generate_expression(node->children[0]);
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
// Function call
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
    
    // SIMPLE FIX: Check if it's a direct function name or indirect
    bool is_indirect_call = true;
    
    // Direct function calls: if child[0] is an Identifier and it's a known function
    if (node->children[0]->name == "Identifier") {
        std::string called_name = node->children[0]->lexeme;
        if (function_return_types.find(called_name) != function_return_types.end() || 
            called_name == "printf" || called_name == "scanf") {
            is_indirect_call = false;
        }
    }
    
    if (is_void_function(func_name) && !is_indirect_call) {
        tac->generate_call(func_name, param_count);
        return "";
    } else {
        std::string result = tac->new_temp();
        if (is_indirect_call) {
            tac->generate_indirect_call(func_name, param_count, result);
        } else {
            tac->generate_call(func_name, param_count, result);
        }
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
                
                // Determine element size
                int element_size = 4; // default
                if (array_element_types.find(base_array) != array_element_types.end()) {
                    element_size = get_type_size(array_element_types[base_array]);
                }
                
                // CORRECT: Multi-dimensional offset calculation
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
                
                // Convert to byte offset using element size
                std::string byte_offset = tac->new_temp();
                tac->generate_binary_op("*", offset, std::to_string(element_size), byte_offset);
                
                std::string base_addr = tac->new_temp();
                tac->generate_address_of(base_array, base_addr);
                
                std::string final_addr = tac->new_temp();
                tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
                
                std::string result = tac->new_temp();
                tac->generate_load(result, final_addr, element_size);
                return result;
            }
        }
        
        // Simple 1D array
        std::string index_val = generate_expression(node->children[1]);

        // Array member of struct/union
        if (node->children[0]->name == "MemberAccess" || 
            node->children[0]->name == "StructMemberAccess") {
            
            // Use generate_member_address to get the address of the array member
            std::string member_addr = generate_member_address(node->children[0]);
            
            if (member_addr.empty()) {
                // Fallback
                std::string base = generate_expression(node->children[0]->children[0]);
                std::string addr_temp = tac->new_temp();
                tac->generate_address_of(base, addr_temp);
                member_addr = addr_temp;
            }
            
            // Calculate element address: member_addr + (index * element_size)
            int element_size = 4; // default int size
            if (node->children[0]->symbol) {
                element_size = get_type_size(node->children[0]->symbol->base_type);
            }
            
            std::string byte_offset = tac->new_temp();
            tac->generate_binary_op("*", index_val, std::to_string(element_size), byte_offset);
            
            std::string element_addr = tac->new_temp();
            tac->generate_binary_op("+", member_addr, byte_offset, element_addr);
            
            std::string result = tac->new_temp();
            tac->generate_load(result, element_addr);
            
            return result;
        } else {
            // Get array name and check symbol for type information
            ASTNode* array_node = node->children[0];
            std::string array_name = generate_expression(array_node);
            
            // Determine element size based on array type from symbol
            int element_size = 4; // default
            if (array_node && array_node->symbol && array_node->symbol->is_array) {
                element_size = get_type_size(array_node->symbol->base_type);
            } else if (array_element_types.find(array_name) != array_element_types.end()) {
                // Fallback to our tracking
                element_size = get_type_size(array_element_types[array_name]);
            }
        
            std::string byte_offset = tac->new_temp();
            tac->generate_binary_op("*", index_val, std::to_string(element_size), byte_offset);
            
            std::string base_addr = tac->new_temp();
            tac->generate_address_of(array_name, base_addr);
            
            std::string final_addr = tac->new_temp();
            tac->generate_binary_op("+", base_addr, byte_offset, final_addr);
            
            std::string result = tac->new_temp();
            tac->generate_load(result, final_addr, element_size);
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
    std::string label_condition = tac->new_label();
    std::string label_end = tac->new_label();
    
    std::string old_break = current_break_label;
    std::string old_continue = current_continue_label;
    current_break_label = label_end;
    current_continue_label = label_condition;  // Continue jumps to condition check

    tac->add_label(label_start);
    generate_statement(node->children[0]);
    
    tac->add_label(label_condition);  // Condition check label
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
    
    // Extract statements from the switch body
    std::vector<ASTNode*> statements;
    ASTNode* switch_body = node->children[1];
    
    if (switch_body->name == "CompoundStatement" && switch_body->children.size() > 0) {
        ASTNode* block_list = switch_body->children[0];  // BlockItemList
        if (block_list && block_list->name == "BlockItemList") {
            for (auto* block_item : block_list->children) {
                if (block_item && block_item->name == "BlockItem" && block_item->children.size() > 0) {
                    statements.push_back(block_item->children[0]);
                }
            }
        }
    }
    
    // First pass: collect all case values and labels
    std::vector<std::pair<std::string, std::string>> case_list;  // <value, label>
    std::string default_label = "";
    
    // Helper to recursively collect cases from nested CaseStatements
    std::function<void(ASTNode*, std::string&)> collect_cases = [&](ASTNode* stmt, std::string& current_label) {
        if (stmt->name == "CaseStatement" && stmt->children.size() >= 1) {
            std::string case_value = generate_expression(stmt->children[0]);
            if (current_label.empty()) {
                current_label = tac->new_label();
            }
            case_list.push_back({case_value, current_label});
            
            // Check if the body is another case (fallthrough)
            if (stmt->children.size() >= 2 && stmt->children[1]->name == "CaseStatement") {
                // Continue with same label for next case
                collect_cases(stmt->children[1], current_label);
            } else {
                // Reset label for next case group
                current_label = "";
            }
        } else if (stmt->name == "DefaultStatement") {
            if (default_label.empty()) {
                default_label = tac->new_label();
            }
        }
    };
    
    for (auto* stmt : statements) {
        std::string label = "";
        collect_cases(stmt, label);
    }
    
    // Generate comparison logic for each case
    for (const auto& case_pair : case_list) {
        std::string temp = tac->new_temp();
        tac->generate_binary_op("==", switch_var, case_pair.first, temp);
        tac->generate_if_goto(temp, case_pair.second);
    }
    
    // If no case matched, jump to default or end
    if (!default_label.empty()) {
        tac->generate_goto(default_label);
    } else {
        tac->generate_goto(end_label);
    }
    
    // Second pass: generate the actual case bodies with their labels
    int case_index = 0;
    bool in_case = false;
    
    // Helper to find the innermost non-case statement in nested cases
    std::function<ASTNode*(ASTNode*)> find_innermost_body = [&](ASTNode* stmt) -> ASTNode* {
        if (stmt->name == "CaseStatement" && stmt->children.size() >= 2) {
            if (stmt->children[1]->name == "CaseStatement") {
                // Nested case, go deeper
                return find_innermost_body(stmt->children[1]);
            } else {
                // Found the actual body
                return stmt->children[1];
            }
        } else if (stmt->name == "DefaultStatement" && stmt->children.size() >= 1) {
            return stmt->children[0];
        }
        return nullptr;
    };
    
    // Helper to emit labels for nested cases
    std::function<void(ASTNode*, bool&)> emit_case_labels = [&](ASTNode* stmt, bool& label_emitted) {
        if (stmt->name == "CaseStatement") {
            if (case_index < static_cast<int>(case_list.size())) {
                // Only emit the label once for the whole fallthrough group
                if (!label_emitted) {
                    tac->add_label(case_list[case_index].second);
                    label_emitted = true;
                }
                case_index++;
            }
            // Check for nested case
            if (stmt->children.size() >= 2 && stmt->children[1]->name == "CaseStatement") {
                emit_case_labels(stmt->children[1], label_emitted);
            }
        } else if (stmt->name == "DefaultStatement") {
            tac->add_label(default_label);
        }
    };
    
    for (auto* stmt : statements) {
        if (stmt->name == "CaseStatement") {
            // Emit labels for this case and any nested cases
            bool label_emitted = false;
            emit_case_labels(stmt, label_emitted);
            
            in_case = true;
            
            // Find and generate the innermost body
            ASTNode* body = find_innermost_body(stmt);
            if (body) {
                if (body->name == "BlockItem" && body->children.size() > 0) {
                    ASTNode* inner = body->children[0];
                    if (inner->name == "Declaration") {
                        generate_declaration(inner);
                    } else {
                        generate_statement(inner);
                    }
                } else if (body->name != "CaseStatement" && body->name != "DefaultStatement") {
                    generate_statement(body);
                }
            }
        } else if (stmt->name == "DefaultStatement") {
            // Default case starts
            tac->add_label(default_label);
            in_case = true;
            
            // Generate the statement after default
            if (stmt->children.size() >= 1) {
                ASTNode* body = stmt->children[0];
                if (body->name == "BlockItem" && body->children.size() > 0) {
                    ASTNode* inner = body->children[0];
                    if (inner->name == "Declaration") {
                        generate_declaration(inner);
                    } else {
                        generate_statement(inner);
                    }
                } else {
                    generate_statement(body);
                }
            }
        } else if (in_case) {
            // Continue generating statements for current case
            generate_statement(stmt);
        }
    }
    
    tac->add_label(end_label);
    current_break_label = old_break;
}

void CodeGenerator::generate_case_statement(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string case_label = tac->new_label();
    tac->add_label(case_label);
    
    // The second child can be either a statement or a BlockItem containing a declaration
    ASTNode* body = node->children[1];
    if (body->name == "BlockItem" && body->children.size() > 0) {
        ASTNode* stmt = body->children[0];
        if (stmt->name == "Declaration") {
            generate_declaration(stmt);
        } else {
            generate_statement(stmt);
        }
    } else {
        generate_statement(body);
    }
}

void CodeGenerator::generate_default_statement(ASTNode* node) {
    if (!node || node->children.size() < 1) return;
    
    std::string default_label = tac->new_label();
    tac->add_label(default_label);
    
    // The child can be either a statement or a BlockItem containing a declaration
    ASTNode* body = node->children[0];
    if (body->name == "BlockItem" && body->children.size() > 0) {
        ASTNode* stmt = body->children[0];
        if (stmt->name == "Declaration") {
            generate_declaration(stmt);
        } else {
            generate_statement(stmt);
        }
    } else {
        generate_statement(body);
    }
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
        
        // Check if this InitializerList has InitializerList children or Initializer children
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
        // Initializer is just a wrapper - don't add index, just recurse
        return flatten_array_initialization(array_name, dims, init_node->children[0], indices, base_temp);
    }
    else {
        // Leaf - actual value
        std::string value = generate_expression(init_node);
        
        // Use only the last dims.size() indices
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
        int element_size = 4; // default
        if (array_element_types.find(array_name) != array_element_types.end()) {
            element_size = get_type_size(array_element_types[array_name]);
        }
        int byte_offset = flat_index * element_size;
        
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
    
    // Get type name for this declaration
    std::string type_name = "";
    std::string base_type = "int"; // default
    for (auto child : node->children) {
        if (child->name == "DeclarationSpecifiers") {
            for (auto spec : child->children) {
                if (spec->name == "TypeSpecifier") {
                    base_type = spec->lexeme; // int, char, short, long, etc
                }
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
		bool is_reference = false;
                bool is_pointer = false;
                std::vector<int> dims;
                
                if (init_decl->children.size() > 0) {
                    var_name = extract_declarator_name(init_decl->children[0]);

                    // Check if it's a pointer declaration
                    if (init_decl->children[0]->name == "Declarator") {
                        for (auto decl_child : init_decl->children[0]->children) {
                            if (decl_child->name == "Pointer") {
                                is_pointer = true;
                                break;
                            }
                        }
                    }

                    if (init_decl->children[0]->name == "ReferenceDeclarator") {
                        is_reference = true;
                        // Get the actual variable name from child
                        if (!init_decl->children[0]->children.empty()) {
                            var_name = extract_declarator_name(init_decl->children[0]->children[0]);
                        }
                    }
                    
                    dims = extract_array_dimensions(init_decl->children[0]);
                    if (!dims.empty()) {
                        is_array = true;
                    }
                }
                
                if (init_decl->children.size() > 1) {
                    init_node = init_decl->children[1];
                }
                
                if (var_name.empty()) continue;
                
                // Store pointer type information
                if (is_pointer) {
                    variable_types[var_name] = base_type + "*";
                }
                if (is_reference && init_node) {
                        if (init_node->name == "MemberAccess" || init_node->name == "StructMemberAccess") {
        std::string member_addr = generate_member_address(init_node);
        tac->generate_assignment(var_name, member_addr);  // ref = address_of_member
        references[var_name] = member_addr;
    } else {
        // For regular variables, get address
        std::string target_addr = tac->new_temp();
        tac->generate_address_of(generate_expression(init_node), target_addr);
        tac->generate_assignment(var_name, target_addr);
        references[var_name] = target_addr;
    }
    continue;
                }
                
                //  Track variable type
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
                        array_element_types[static_var] = base_type; // Store element type
                        
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
                    // Check if this variable has its address taken
                    bool needs_memory = address_taken_vars.find(var_name) != address_taken_vars.end();
                    
                    if (is_array) {
                        array_dims[var_name] = dims;
                        array_element_types[var_name] = base_type; // Store element type
                        
                        if (init_node) {
                            std::vector<int> empty_indices;
std::string empty_base;
flatten_array_initialization(var_name, dims, init_node, empty_indices, empty_base);
                        }
                    } else if (needs_memory) {
                        // Treat address-taken scalar as single-element array
                        array_dims[var_name] = {1}; // Single element
                        array_element_types[var_name] = base_type;
                        
                        if (init_node) {
                            std::string init_val = generate_expression(init_node);
                            // Store to array index 0
                            tac->generate_array_store(var_name, "0", init_val);
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
std::string CodeGenerator::generate_member_address(ASTNode* node) {
    if (!node || node->children.size() < 2) return "";
    
    std::string field = node->children[1]->lexeme;
    std::string base_addr;
    std::string base_type;
    
    // Handle nested member access: o.in.a -> recursively get address of o.in
    if (node->children[0]->name == "MemberAccess" || node->children[0]->name == "StructMemberAccess") {
        // Recursively get the address of the nested member
        base_addr = generate_member_address(node->children[0]);
        
        // Get the type of the nested member - need to find the struct that contains the member
        // For p.addr.houseNo: node->children[0] is "p.addr"
        //   We need to find that "addr" is of type "Address"
        
        // Navigate to find the base variable and member
        std::string parent_base_var;
        std::string parent_field = node->children[0]->children[1]->lexeme;
        
        ASTNode* deepest = node->children[0]->children[0];
        while (deepest && (deepest->name == "MemberAccess" || deepest->name == "StructMemberAccess")) {
            deepest = deepest->children[0];
        }
        if (deepest && deepest->name == "Identifier") {
            parent_base_var = deepest->lexeme;
        }
        
        // Find the type of the parent struct
        auto var_type_it = variable_types.find(parent_base_var);
        if (var_type_it != variable_types.end()) {
            std::string parent_struct_type = var_type_it->second;
            std::string key = parent_struct_type + "." + parent_field;
            
            // Look up the type of this member
            auto member_type_it = variable_types.find(key);
            if (member_type_it != variable_types.end()) {
                base_type = member_type_it->second;
            }
        }
    }
    else if (node->children[0]->name == "Identifier") {
        // Simple case: base is just an identifier
        std::string base_var = node->children[0]->lexeme;
        
        // Get base address of the struct
        base_addr = tac->new_temp();
        tac->generate_address_of(base_var, base_addr);
        
        // Get the type from symbol or variable_types map
        if (node->children[0]->symbol) {
            base_type = node->children[0]->symbol->base_type;
        } else {
            auto it = variable_types.find(base_var);
            if (it != variable_types.end()) {
                base_type = it->second;
            }
        }
    }
    else {
        // Handle other complex expressions
        return "";
    }
    
    // Get member offset using base_type
    int offset = 0;
    if (!base_type.empty()) {
        std::string key = base_type + "." + field;
        auto offset_it = member_offsets.find(key);
        if (offset_it != member_offsets.end()) {
            offset = offset_it->second;
        }
    }
    
    // Calculate member address: base_addr + offset
    if (offset == 0) {
        return base_addr;
    } else {
        std::string member_addr = tac->new_temp();
        tac->generate_binary_op("+", base_addr, std::to_string(offset), member_addr);
        return member_addr;
    }
}

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

void CodeGenerator::collect_address_taken_vars(ASTNode* node) {
    if (!node) return;
    
    // Check if this is an address-of operation on an identifier
    if (node->name == "UnaryExpression" && node->lexeme == "&") {
        if (node->children.size() > 0 && node->children[0]->name == "Identifier") {
            std::string var_name = node->children[0]->lexeme;
            address_taken_vars.insert(var_name);
        }
    }
    
    // Recursively check all children
    for (auto child : node->children) {
        collect_address_taken_vars(child);
    }
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