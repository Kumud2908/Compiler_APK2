#include "semantic.h"
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer(SymbolTable* table) 
    : symbol_table(table), in_function_params(false) {
    if (!symbol_table) {
        std::cerr << "ERROR: SymbolTable is null!" << std::endl;
    }
}

void SemanticAnalyzer::analyze(ASTNode* root) {
    if (!root) {
        std::cerr << "WARNING: analyze() called with null root" << std::endl;
        return;
    }
    if (!symbol_table) {
        std::cerr << "ERROR: Cannot analyze - symbol_table is null" << std::endl;
        return;
    }
    
    std::cout << "=== SEMANTIC ANALYSIS STARTED ===" << std::endl;
    traverse(root);
    std::cout << "=== SEMANTIC ANALYSIS COMPLETED ===" << std::endl;
}

void SemanticAnalyzer::traverse(ASTNode* node) {
    if (!node || node->processed) return;

    node->processed = true;

    if (node->name == "Declaration") {
        process_declaration(node);
    }
    else if (node->name == "FunctionDefinition") {
        process_function(node);
        return;
    }
    else if (node->name == "StructOrUnionSpecifier") {
        process_struct_or_union(node);
    }
    else if (node->name == "EnumSpecifier") {
        process_enum(node);
    }
    else if (node->name == "CompoundStatement") {
        // Check if this is directly under a FunctionDefinition
        bool is_function_body = (node->parent && node->parent->name == "FunctionDefinition");
        
        if (!is_function_body) {
            // Normal block - create scope
            int old_scope = symbol_table->get_current_scope_level();
            symbol_table->enter_scope();
            std::cout << "[Scope " << old_scope << "->" << symbol_table->get_current_scope_level() 
                      << "] Entering block" << std::endl;
            
            for (size_t i = 0; i < node->children.size(); i++) {
                if (node->children[i]) traverse(node->children[i]);
            }
            
            std::cout << "[Scope " << symbol_table->get_current_scope_level() << "->" << old_scope 
                      << "] Exiting block" << std::endl;
            symbol_table->exit_scope();
            return;
        } else {
            // Function body - no extra scope, just traverse children
            for (size_t i = 0; i < node->children.size(); i++) {
                if (node->children[i]) traverse(node->children[i]);
            }
            return;
        }
    }

    // Normal traversal for other nodes
    for (size_t i = 0; i < node->children.size(); i++) {
        if (node->children[i]) traverse(node->children[i]);
    }
}

void SemanticAnalyzer::process_declaration(ASTNode* node) {
    if (!node) return;
    
    std::string base_type = "int";
    
    // Extract base type
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            base_type = extract_base_type(child);
            break;
        }
    }
    
    // Look for variable declarators
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
                        
                        if (decl->name == "DirectDeclarator" || decl->name == "ArrayDeclarator" || decl->name == "Declarator") {
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
    
    // Extract return type and function name
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
    
    // Create function symbol FIRST
    Symbol* func_sym = new Symbol(func_name, "function", return_type, 
                                 symbol_table->get_current_scope_level(), 0);
    
    // Add function to CURRENT scope (should be global)
    if (!symbol_table->add_symbol(func_sym)) {
        std::cout << "ERROR: Failed to add function '" << func_name << "' to symbol table" << std::endl;
        delete func_sym;
        return;
    }
    
    // NOW enter function scope for parameters
    symbol_table->enter_scope();
    std::cout << "[Scope " << symbol_table->get_current_scope_level() - 1 << "->" 
              << symbol_table->get_current_scope_level() << "] Entering function scope for " << func_name << std::endl;
    
    // Process parameters AND store them in function symbol
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "Declarator" || child->name == "FunctionDeclarator") {
            process_function_parameters(child, func_sym);
        }
    }
    
    // Process function body in the SAME scope
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "CompoundStatement") {
            traverse(child);  // Body shares scope with parameters
        }
    }
    
    std::cout << "[Scope " << symbol_table->get_current_scope_level() << "->" 
              << symbol_table->get_current_scope_level() - 1 << "] Exiting function scope for " << func_name << std::endl;
    symbol_table->exit_scope();
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

// ADD this overloaded version - KEEP the existing one above it
void SemanticAnalyzer::process_function_parameters(ASTNode* declarator, Symbol* func_sym) {
    if (!declarator) return;
    
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        if (child->name == "DirectDeclarator") {
            process_function_parameters(child, func_sym);
        }
        else if (child->name == "ParameterList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* param = child->children[j];
                if (param && param->name == "ParameterDeclaration") {
                    process_parameter(param, func_sym);  // PASS func_sym
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
                            process_parameter(param, func_sym);  // PASS func_sym
                        }
                    }
                }
            }
        }
    }
}

std::string SemanticAnalyzer::extract_function_name(ASTNode* declarator) {
    if (!declarator) return "unknown";
    
    // Check current node first
    if (!declarator->lexeme.empty() && declarator->lexeme != "default") {
        return declarator->lexeme;
    }
    
    // Look for DirectDeclarator with lexeme
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        if (child->name == "DirectDeclarator") {
            if (!child->lexeme.empty() && child->lexeme != "default") {
                return child->lexeme;
            }
            
            // Search recursively in DirectDeclarator's children
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

void SemanticAnalyzer::process_struct_or_union(ASTNode* node) {
    if (!node || !symbol_table) return;
    
    std::string specifier_type = "struct"; // default
    std::string type_name = "anonymous";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "StructOrUnion") {
            specifier_type = child->lexeme; // "struct" or "union"
        }
        else if ((child->name == "Identifier" || child->name == "IDENTIFIER") && 
                !child->lexeme.empty() && child->lexeme != "default") {
            type_name = child->lexeme;
            break;
        }
    }
    
    std::string symbol_type = (specifier_type == "union") ? "union" : "struct";
    Symbol* type_sym = new Symbol(type_name, symbol_type, symbol_type, 
                                 symbol_table->get_current_scope_level(), 0);
    
    // PROCESS MEMBERS (same as before)
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "StructDeclarationList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* struct_decl = child->children[j];
                if (!struct_decl || struct_decl->name != "StructDeclaration") continue;
                
                // Extract member info (same as before)
                std::string member_type = "int";
                std::string member_name = "unknown";
                
                for (size_t k = 0; k < struct_decl->children.size(); k++) {
                    ASTNode* decl_child = struct_decl->children[k];
                    if (!decl_child) continue;
                    
                    if (decl_child->name == "TypeSpecifier") {
                        member_type = extract_base_type_from_node(decl_child);
                    }
                    else if (decl_child->name == "StructDeclaratorList") {
                        // Enhanced member extraction with array support
                        for (size_t m = 0; m < decl_child->children.size(); m++) {
                            ASTNode* member_decl = decl_child->children[m];
                            if (!member_decl) continue;
                            
                            if (member_decl->name == "DirectDeclarator") {
                                member_name = extract_declarator_name(member_decl);
                            }
                            else if (member_decl->name == "ArrayDeclarator") {
                                member_name = extract_declarator_name(member_decl);
                                
                                // Extract array dimensions
                                std::string dimensions;
                                ASTNode* current = member_decl;
                                
                                while (current && current->name == "ArrayDeclarator") {
                                    for (size_t n = 0; n < current->children.size(); n++) {
                                        ASTNode* dim_child = current->children[n];
                                        if (dim_child && dim_child->name == "Constant" && !dim_child->lexeme.empty()) {
                                            if (!dimensions.empty()) dimensions += ",";
                                            dimensions += dim_child->lexeme;
                                        }
                                    }
                                    bool found_inner = false;
                                    for (size_t n = 0; n < current->children.size(); n++) {
                                        if (current->children[n] && current->children[n]->name == "ArrayDeclarator") {
                                            current = current->children[n];
                                            found_inner = true;
                                            break;
                                        }
                                    }
                                    if (!found_inner) break;
                                }
                                
                                if (!dimensions.empty()) {
                                    member_type += "[" + dimensions + "]";
                                } else {
                                    member_type += "[]";
                                }
                            }
                        }
                    }
                }
                
                if (member_name != "unknown") {
                    Symbol* member_sym = new Symbol(member_name, "member", member_type,
                                                  type_sym->scope_level, 0);
                    type_sym->add_member(member_sym);
                    std::cout << "[" << specifier_type << " " << type_name << "] Added member: " 
                              << member_name << " : " << member_type << std::endl;
                }
            }
        }
    }
    
    symbol_table->add_symbol(type_sym);
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

// ADD this overloaded version - KEEP the existing one above it
void SemanticAnalyzer::process_parameter(ASTNode* param_decl, Symbol* func_sym) {
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
        // Create SEPARATE symbols for scope and function info
        Symbol* scope_param_sym = new Symbol(param_name, "parameter", param_type,
                                           symbol_table->get_current_scope_level(), 0);
        
        // Add to scope for semantic checking and variable resolution
        if (symbol_table->add_symbol(scope_param_sym)) {
            std::cout << "[Scope " << symbol_table->get_current_scope_level() 
                      << "] Added parameter: " << param_name << " : " << param_type << std::endl;
        } else {
            // If add fails, clean up (shouldn't happen with proper scope management)
            delete scope_param_sym;
        }
        
        // Create a SEPARATE symbol for function parameter list (type info only)
        if (func_sym) {
            Symbol* func_param_sym = new Symbol(param_name, "parameter", param_type,
                                              func_sym->scope_level, 0);  // Use function's scope level
            func_sym->add_parameter(func_param_sym);
            std::cout << "[Function " << func_sym->name << "] Added parameter info: " 
                      << param_name << " : " << param_type << std::endl;
        }
    }
}
void SemanticAnalyzer::process_variable(ASTNode* declarator, const std::string& base_type) {
    if (!declarator || !symbol_table) return;
    
    std::string var_name = extract_declarator_name(declarator);
    std::string final_type = base_type;
    
    // Handle pointer types
    if (declarator->name == "Declarator") {
        // Check if it has Pointer children
        for (size_t i = 0; i < declarator->children.size(); i++) {
            if (declarator->children[i] && declarator->children[i]->name == "Pointer") {
                final_type = base_type + "*";
                break;
            }
        }
    }
    // Handle array types - EXTRACT DIMENSIONS
    else if (declarator->name == "ArrayDeclarator") {
        std::string dimensions;
        ASTNode* current = declarator;
        
        // Extract dimensions from nested ArrayDeclarators
        while (current && current->name == "ArrayDeclarator") {
            for (size_t i = 0; i < current->children.size(); i++) {
                ASTNode* child = current->children[i];
                if (child && child->name == "Constant" && !child->lexeme.empty()) {
                    if (!dimensions.empty()) dimensions += ",";
                    dimensions += child->lexeme;
                }
            }
            // Move to inner ArrayDeclarator for multi-dimensional arrays
            bool found_inner = false;
            for (size_t i = 0; i < current->children.size(); i++) {
                if (current->children[i] && current->children[i]->name == "ArrayDeclarator") {
                    current = current->children[i];
                    found_inner = true;
                    break;
                }
            }
            if (!found_inner) break;
        }
        
        if (!dimensions.empty()) {
            final_type = base_type + "[" + dimensions + "]";
        } else {
            final_type = base_type + "[]";
        }
    }
    
    if (var_name == "unknown" || var_name.empty()) {
        return;
    }
    
    std::string symbol_type = in_function_params ? "parameter" : "variable";
    Symbol* var_sym = new Symbol(var_name, symbol_type, final_type,
                                symbol_table->get_current_scope_level(), 0);
    
    if (symbol_table->add_symbol(var_sym)) {
        std::cout << "[Scope " << symbol_table->get_current_scope_level() 
                  << "] Added " << symbol_type << ": " << var_name << " : " << final_type << std::endl;
    }
}
std::string SemanticAnalyzer::extract_declarator_name(ASTNode* declarator) {
    if (!declarator) return "unknown";
    
    // If current node has identifier, use it
    if (!declarator->lexeme.empty() && declarator->lexeme != "default") {
        return declarator->lexeme;
    }
    
    // Handle Declarator node (wrapper for Pointer + DirectDeclarator)
    if (declarator->name == "Declarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            // Look for DirectDeclarator inside Declarator
            if (child->name == "DirectDeclarator") {
                std::string name = extract_declarator_name(child);
                if (name != "unknown") return name;
            }
        }
    }
    
    // Handle ArrayDeclarator - search in its children
    if (declarator->name == "ArrayDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            // ArrayDeclarator can have DirectDeclarator OR another ArrayDeclarator as first child
            if (child->name == "DirectDeclarator" || child->name == "ArrayDeclarator") {
                std::string name = extract_declarator_name(child);
                if (name != "unknown") return name;
            }
        }
    }
    
    // Search recursively in children
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
            // Check TypeSpecifier's own lexeme
            if (!child->lexeme.empty() && child->lexeme != "default") {
                return child->lexeme;
            }
            
            // Check TypeSpecifier's children
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* type_child = child->children[j];
                if (!type_child) continue;
                
                if (!type_child->lexeme.empty() && type_child->lexeme != "default") {
                    return type_child->lexeme;
                }
            }
        }
        else if (child->name == "StructOrUnionSpecifier") {
            // Extract struct/union type and name
            std::string specifier_type = "struct"; // default
            std::string type_name = "anonymous";
            
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* struct_child = child->children[j];
                if (!struct_child) continue;
                
                if (struct_child->name == "StructOrUnion") {
                    specifier_type = struct_child->lexeme; // "struct" or "union"
                }
                else if (struct_child->name == "Identifier") {
                    type_name = struct_child->lexeme;
                }
            }
            
            // Return the full type: "struct Point" or "union Data"
            return specifier_type + " " + type_name;
        }
    }
    return "int";
}
// Helper function to extract base type from TypeSpecifier node directly
std::string SemanticAnalyzer::extract_base_type_from_node(ASTNode* node) {
    if (!node) return "int";
    
    // Check current node's lexeme
    if (!node->lexeme.empty() && node->lexeme != "default") {
        return node->lexeme;
    }
    
    // Check children
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (!child->lexeme.empty() && child->lexeme != "default") {
            return child->lexeme;
        }
    }
    return "int";
}

// Helper function to extract member name from StructDeclaratorList
std::string SemanticAnalyzer::extract_struct_member_name(ASTNode* node) {
    if (!node) return "unknown";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        // Struct members can be DirectDeclarator or ArrayDeclarator
        if (child->name == "DirectDeclarator" || child->name == "ArrayDeclarator") {
            return extract_declarator_name(child);
        }
    }
    return "unknown";
}
