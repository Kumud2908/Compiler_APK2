#include "semantic.h"
#include <iostream>
#include <algorithm>  


SemanticAnalyzer::SemanticAnalyzer(SymbolTable* table) 
    : symbol_table(table), in_function_params(false), error_count(0) {
    if (!symbol_table) {
        std::cerr << "ERROR: SymbolTable is null!" << std::endl;
    }
}

void SemanticAnalyzer::reportError(const std::string& message, ASTNode* node) {
    error_count++;
    
    if (node && node->line_number > 0) {
        std::cout << "Line " << node->line_number << ": SEMANTIC ERROR: " << message << std::endl;
    } else {
        std::cout << "SEMANTIC ERROR: " << message << std::endl;
    }
}

void SemanticAnalyzer::check_identifier_usage(ASTNode* node) {
    if (!node || (node->name != "Identifier" && node->name != "IDENTIFIER")) return;
    
    std::string identifier = node->lexeme;
    if (identifier.empty() || identifier == "default") return;
    
    // Skip if we're in a declaration context
    if (node->parent && (node->parent->name == "DirectDeclarator" || 
                         node->parent->name == "StructDeclarator" ||
                         node->parent->name == "ParameterDeclaration"||
			 node->parent->name == "EnumSpecifier"||
			 node->parent->name == "MemberAccess")) {
        return;
    }
    
    Symbol* symbol = symbol_table->find_symbol(identifier);

    if (symbol) {
        std::cout << "[Identifier] '" << identifier << "' found: " 
                  << symbol->get_full_type() << " (scope: " << symbol->scope_level 
                  << ", type: " << symbol->symbol_type << ")" << std::endl;
    } else {
        std::cout << "[Identifier] '" << identifier << "' NOT FOUND in symbol table" << std::endl;
    }

    if (!symbol) {
        reportError("Undeclared identifier: '" + identifier + "'", node);
    }
}

bool SemanticAnalyzer::is_valid_type(const std::string& type) {
    // Basic built-in types
    if (type == "int" || type == "char" || type == "float" || type == "double" || 
        type == "void" || type == "short" || type == "long" || type == "signed" || 
        type == "unsigned" || type == "bool") {
        return true;
    }
    
    // Check if it's a struct/enum that we've seen (just the name)
    Symbol* type_symbol = symbol_table->find_symbol(type);
    if (type_symbol && (type_symbol->symbol_type == "struct" || 
                        type_symbol->symbol_type == "union" || 
                        type_symbol->symbol_type == "enum")) {
        return true;
    }
    
    // Check for struct/union types like "struct Point" 
    if (type.find("struct ") == 0) {
        std::string type_name = type.substr(7); // Remove "struct "
        Symbol* struct_symbol = symbol_table->find_symbol(type_name);
        if (struct_symbol && struct_symbol->symbol_type == "struct") {
            return true;
        }
        // Also allow if we haven't seen it yet (forward declaration)
        return true;
    }
    else if (type.find("union ") == 0) {
        std::string type_name = type.substr(6); // Remove "union "
        Symbol* union_symbol = symbol_table->find_symbol(type_name);
        if (union_symbol && union_symbol->symbol_type == "union") {
            return true;
        }
        // Also allow if we haven't seen it yet (forward declaration)
        return true;
    }
    else if (type.find("enum ") == 0) {
        return true; // Allow enum types
    }
    
    return false;
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
    error_count = 0;
    traverse(root);
    std::cout << "=== SEMANTIC ANALYSIS COMPLETED ===" << std::endl;
    
    if (error_count > 0) {
        std::cout << "Found " << error_count << " semantic error(s)" << std::endl;
    } else {
        std::cout << "No semantic errors found" << std::endl;
    }
}

void SemanticAnalyzer::traverse(ASTNode* node) {
    if (!node || node->processed) return;

    std::cout << "TRAVERSE: " << node->name;
    if (!node->lexeme.empty() && node->lexeme != "default") {
        std::cout << " '" << node->lexeme << "'";
    }
    std::cout << " at line " << node->line_number << std::endl;

    node->processed = true;

    if (node->name == "Declaration") {
        if (is_function_declaration(node)) {
            process_function_declaration(node);  // Handle function declarations
        } else {
            process_declaration(node);           // Handle variable declarations
        }
    }
    else if (node->name == "FunctionDefinition") {
        process_function(node);
        return;
    }
    else if (node->name == "StructOrUnionSpecifier") {
        bool is_top_level = true;
        ASTNode* parent = node->parent;
        while (parent) {
            if (parent->name == "StructDeclaration") {
                is_top_level = false;  // This is a type reference in member declaration
                break;
            }
            parent = parent->parent;
        }
        
        if (is_top_level) {
            process_struct_or_union(node);
        }
        // If nested, skip processing - it's just a type reference
        return;
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
                      << "] Entering block at line " << node->line_number << std::endl;
            
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
    else if (node->name == "Identifier" || node->name == "IDENTIFIER") {
        check_identifier_usage(node);
    }
    else if (node->name == "MemberAccess") {  // ADD THIS LINE
        check_member_access(node);            // ADD THIS LINE
    }

    // Normal traversal for other nodes
    for (size_t i = 0; i < node->children.size(); i++) {
        if (node->children[i]) traverse(node->children[i]);
    }
}

void SemanticAnalyzer::process_declaration(ASTNode* node) {
    if (!node) return;
    
    std::string base_type = "int";
    bool type_found = false;
    
    // Extract base type
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            base_type = extract_base_type(child);
            type_found = true;
            
            if (!is_valid_type(base_type)) {
                reportError("Unknown type: '" + base_type + "'", child);
            }
            break;
        }
    }
    
    if (!type_found) {
        reportError("Declaration missing type specifier", node);
        return;
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
                        
                        // ADD FunctionDeclarator to handle function pointers
                        if (decl->name == "DirectDeclarator" || decl->name == "ArrayDeclarator" || 
                            decl->name == "Declarator" || decl->name == "FunctionDeclarator") {
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
    bool return_type_found = false;
    
    // Extract return type and function name
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            return_type = extract_base_type(child);
            return_type_found = true;
            
            if (!is_valid_type(return_type)) {
                reportError("Invalid return type: '" + return_type + "'", child);
            }
        }
        else if (child->name == "Declarator" || child->name == "FunctionDeclarator") {
            func_name = extract_function_name(child);
        }
    }
    
    if (!return_type_found) {
        reportError("Function missing return type", node);
    }
    
    if (func_name == "unknown") {
        reportError("Function has no name", node);
        return;
    }
    
    std::cout << "[Scope " << symbol_table->get_current_scope_level() 
              << "] Found function at line " << node->line_number
              << ": " << func_name << " : " << return_type << std::endl;
    
    // Check if function already exists
    Symbol* existing = symbol_table->find_symbol(func_name);
    Symbol* func_sym;
    
    if (existing && existing->symbol_type == "function") {
        // Function already declared - use existing symbol
        std::cout << "[Info] Function '" << func_name << "' definition found for declaration" << std::endl;
        func_sym = existing;
    } else {
        // Create new function symbol
        func_sym = new Symbol(func_name, "function", return_type, 
                             symbol_table->get_current_scope_level(), node->line_number);
        
        // Add to CURRENT scope (should be global)
        if (!symbol_table->add_symbol(func_sym)) {
            reportError("Failed to add function '" + func_name + "' to symbol table", node);
            delete func_sym;
            return;
        }
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
                    process_parameter(param, func_sym);
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
                            process_parameter(param, func_sym);
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
    bool has_members = false;

    // Check if this is a complete definition (has members) or forward declaration
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "StructOrUnion") {
            specifier_type = child->lexeme;
        }
        else if ((child->name == "Identifier" || child->name == "IDENTIFIER") && 
                !child->lexeme.empty() && child->lexeme != "default") {
            type_name = child->lexeme;
        }
        else if (child->name == "StructDeclarationList") {
            has_members = true;  // This is a complete definition
        }
    }
    
    std::string symbol_type = (specifier_type == "union") ? "union" : "struct";
    
    // Check if this struct already exists
    Symbol* existing = symbol_table->find_symbol(type_name);
    Symbol* type_sym = nullptr;

    if (existing && existing->symbol_type == symbol_type) {
        // Struct already exists
        if (has_members) {
            // This is a definition - complete the existing struct
            if (existing->is_complete) {
                reportError(symbol_type + " '" + type_name + "' already defined", node);
                return;
            }
            type_sym = existing;  // Use existing symbol to complete it
            std::cout << "[Info] Completing " << symbol_type << " '" << type_name << "'" << std::endl;
        } else {
            // This is another forward declaration - ignore
            std::cout << "[Info] " << symbol_type << " '" << type_name << "' already declared" << std::endl;
            return;
        }
    } else {
        // Create new symbol
        type_sym = new Symbol(type_name, symbol_type, symbol_type, 
                             symbol_table->get_current_scope_level(), node->line_number);
        type_sym->is_complete = has_members;  // ← FIX: Complete only if it has members
        
        if (!symbol_table->add_symbol(type_sym)) {
            reportError("Cannot add " + symbol_type + " '" + type_name + "' to symbol table", node);
            delete type_sym;
            return;
        }
    }

    // PROCESS MEMBERS only if this is a complete definition
    if (has_members) {
        for (size_t i = 0; i < node->children.size(); i++) {
            ASTNode* child = node->children[i];
            if (!child) continue;
            
            if (child->name == "StructDeclarationList") {
                for (size_t j = 0; j < child->children.size(); j++) {
                    ASTNode* struct_decl = child->children[j];
                    if (!struct_decl || struct_decl->name != "StructDeclaration") continue;
                    
                    // Extract base type for all members in this declaration
                    std::string member_base_type = "int";
                    for (size_t k = 0; k < struct_decl->children.size(); k++) {
                        ASTNode* decl_child = struct_decl->children[k];
                        if (!decl_child) continue;
                        
                        if (decl_child->name == "TypeSpecifier") {
                            member_base_type = extract_base_type_from_node(decl_child);
                            break;
                        }
                        else if (decl_child->name == "StructOrUnionSpecifier") {
                            // Handle struct/union types in member declarations
                            std::string spec_type = "struct";
                            std::string t_name = "anonymous";
                            
                            for (size_t m = 0; m < decl_child->children.size(); m++) {
                                ASTNode* spec_child = decl_child->children[m];
                                if (!spec_child) continue;
                                
                                if (spec_child->name == "StructOrUnion") {
                                    spec_type = spec_child->lexeme;
                                }
                                else if ((spec_child->name == "Identifier" || spec_child->name == "IDENTIFIER") && 
                                        !spec_child->lexeme.empty() && spec_child->lexeme != "default") {
                                    t_name = spec_child->lexeme;
                                }
                            }
                            member_base_type = spec_type + " " + t_name;
                            break;
                        }
                    }
                    
                    // Process each member in StructDeclaratorList
                    for (size_t k = 0; k < struct_decl->children.size(); k++) {
                        ASTNode* decl_child = struct_decl->children[k];
                        if (!decl_child || decl_child->name != "StructDeclaratorList") continue;
                        
                        for (size_t m = 0; m < decl_child->children.size(); m++) {
                            ASTNode* member_decl = decl_child->children[m];
                            if (!member_decl) continue;
                            
                            process_struct_member(member_decl, member_base_type, type_sym, specifier_type);
                        }
                    }
                }
            }
        }
        
        type_sym->is_complete = true;  // Mark as complete after processing members
        std::cout << "[" << specifier_type << " " << type_name << "] Completed with " 
                  << type_sym->members.size() << " members" << std::endl;
    } else {
        // Forward declaration - symbol is already created with is_complete = false
        std::cout << "[" << specifier_type << " " << type_name << "] Forward declared" << std::endl;
    }
}

// NEW METHOD: Process individual struct members with enhanced type extraction
void SemanticAnalyzer::process_struct_member(ASTNode* member_decl, const std::string& base_type, 
                                           Symbol* struct_sym, const std::string& struct_type) {
    if (!member_decl || !struct_sym) return;
    
    std::string member_name = extract_declarator_name(member_decl);
    if (member_name == "unknown") return;
    
    // Create member symbol with basic type
    Symbol* member_sym = new Symbol(member_name, "member", base_type,
                                   struct_sym->scope_level, 0);
    
    // Extract enhanced type information (pointers, arrays, etc.)
    extract_type_info(member_decl, member_sym);
    
    struct_sym->add_member(member_sym);
    std::cout << "[" << struct_type << " " << struct_sym->name << "] Added member: " 
              << member_name << " : " << member_sym->get_full_type() << std::endl;
}


void SemanticAnalyzer::process_enum(ASTNode* node) {
    std::cout << "DEBUG: process_enum ENTERED for node at line " << node->line_number << std::endl;
    
    if (!node || !symbol_table) {
        std::cout << "DEBUG: process_enum - null node or symbol_table" << std::endl;
        return;
    }
    
    
    std::cout << "DEBUG: process_enum CONTINUING..." << std::endl;
    
    std::cout << "DEBUG: Processing EnumSpecifier at line " << node->line_number << std::endl;
    
    std::string enum_name = "anonymous";
    std::vector<std::pair<std::string, int>> enumerators;
    int next_value = 0;
    
    // The node IS the EnumSpecifier, so look directly in its children
    std::cout << "DEBUG: EnumSpecifier has " << node->children.size() << " children:" << std::endl;
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        std::cout << "DEBUG:   Child " << i << ": " << child->name << " lexeme='" << child->lexeme << "'" << std::endl;
        
        if ((child->name == "Identifier" || child->name == "IDENTIFIER") && 
            !child->lexeme.empty() && child->lexeme != "default") {
            enum_name = child->lexeme;
            std::cout << "DEBUG:   Found enum name: " << enum_name << std::endl;
        }
        else if (child->name == "EnumeratorList") {
            std::cout << "DEBUG:   Found EnumeratorList, extracting..." << std::endl;
            enumerators = extract_enumerators(child, next_value);
            std::cout << "DEBUG:   Extracted " << enumerators.size() << " enumerators" << std::endl;
        }
    }
    
    // Check if enum already exists
    Symbol* existing = symbol_table->find_symbol(enum_name);
    if (existing && existing->symbol_type == "enum") {
        reportError("Enum '" + enum_name + "' already declared", node);
        return;
    }
    
    // Create enum symbol
    Symbol* enum_sym = new Symbol(enum_name, "enum", "enum", 
                                 symbol_table->get_current_scope_level(), node->line_number);
    
    // Add all enumerators to the enum symbol and current scope
    for (const auto& enumerator : enumerators) {
        enum_sym->add_enumerator(enumerator.first, enumerator.second);
        
        // Add enumerator as constant to current scope
        Symbol* const_sym = new Symbol(enumerator.first, "constant", "int",
                                      symbol_table->get_current_scope_level(), node->line_number);
        
        if (!symbol_table->add_symbol(const_sym)) {
            // Enumerator already exists - this might be okay in some cases
            delete const_sym;
        } else {
            std::cout << "[Enum " << enum_name << "] Added enumerator: " 
                      << enumerator.first << " = " << enumerator.second << std::endl;
        }
    }
    
    // Add enum to symbol table
    if (!symbol_table->add_symbol(enum_sym)) {
        reportError("Failed to add enum '" + enum_name + "' to symbol table", node);
        delete enum_sym;
    } else {
        std::cout << "[Enum] Created: " << enum_name << " with " 
                  << enumerators.size() << " enumerators" << std::endl;
    }
}

std::vector<std::pair<std::string, int>> SemanticAnalyzer::extract_enumerators(ASTNode* enumerator_list, int& next_value) {
    std::vector<std::pair<std::string, int>> enumerators;
    
    if (!enumerator_list || enumerator_list->name != "EnumeratorList") {
        std::cout << "DEBUG: extract_enumerators: Not an EnumeratorList" << std::endl;
        return enumerators;
    }
    
    std::cout << "DEBUG: EnumeratorList has " << enumerator_list->children.size() << " children" << std::endl;
    
    for (size_t i = 0; i < enumerator_list->children.size(); i++) {
        ASTNode* enumerator_node = enumerator_list->children[i];
        if (!enumerator_node || enumerator_node->name != "Enumerator") {
            std::cout << "DEBUG:   Child " << i << " is not an Enumerator" << std::endl;
            continue;
        }
        
        std::cout << "DEBUG:   Processing Enumerator: lexeme='" << enumerator_node->lexeme << "'" << std::endl;
        
        std::string enumerator_name = "unknown";
        int enumerator_value = next_value; // Default to auto-increment
        
        // The Enumerator node should have the name as its lexeme
        if (!enumerator_node->lexeme.empty() && enumerator_node->lexeme != "default") {
            enumerator_name = enumerator_node->lexeme;
            std::cout << "DEBUG:     Enumerator name: " << enumerator_name << std::endl;
        }
        
        // Look for Constant child for explicit value
        std::cout << "DEBUG:     Enumerator has " << enumerator_node->children.size() << " children" << std::endl;
        for (size_t j = 0; j < enumerator_node->children.size(); j++) {
            ASTNode* child = enumerator_node->children[j];
            if (!child) continue;
            
            std::cout << "DEBUG:       Child " << j << ": " << child->name << " lexeme='" << child->lexeme << "'" << std::endl;
            
            if (child->name == "Constant") {
                // Explicit value assigned
                try {
                    enumerator_value = std::stoi(child->lexeme);
                    std::cout << "DEBUG:       Explicit value: " << enumerator_value << std::endl;
                } catch (const std::exception& e) {
                    // If not a number, use current auto-increment value
                    enumerator_value = next_value;
                    std::cout << "DEBUG:       Invalid constant, using auto-increment: " << enumerator_value << std::endl;
                }
            }
        }
        
        if (enumerator_name != "unknown") {
            enumerators.push_back(std::make_pair(enumerator_name, enumerator_value));
            next_value = enumerator_value + 1; // Update for next enumerator
            std::cout << "DEBUG:     Added enumerator: " << enumerator_name << " = " << enumerator_value << std::endl;
        }
    }
    
    std::cout << "DEBUG: Total enumerators extracted: " << enumerators.size() << std::endl;
    return enumerators;
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
                                      symbol_table->get_current_scope_level(), param_decl->line_number);
        if (!symbol_table->add_symbol(param_sym)) {
            reportError("Parameter '" + param_name + "' already declared", param_decl);
        } else {
            std::cout << "[Scope " << symbol_table->get_current_scope_level() 
                      << "] Added parameter at line " << param_decl->line_number
                      << ": " << param_name << " : " << param_type << std::endl;
        }
    }
}

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
                                           symbol_table->get_current_scope_level(), param_decl->line_number);
        
        // Add to scope for semantic checking and variable resolution
        if (!symbol_table->add_symbol(scope_param_sym)) {
            reportError("Parameter '" + param_name + "' already declared", param_decl);
        } else {
            std::cout << "[Scope " << symbol_table->get_current_scope_level() 
                      << "] Added parameter at line " << param_decl->line_number
                      << ": " << param_name << " : " << param_type << std::endl;
        }
        
        // Create a SEPARATE symbol for function parameter list (type info only)
        if (func_sym) {
            Symbol* func_param_sym = new Symbol(param_name, "parameter", param_type,
                                              func_sym->scope_level, 0);
            func_sym->add_parameter(func_param_sym);
            std::cout << "[Function " << func_sym->name << "] Added parameter info: " 
                      << param_name << " : " << param_type << std::endl;
        }
    }
}

void SemanticAnalyzer::process_variable(ASTNode* declarator, const std::string& base_type) {
    if (!declarator || !symbol_table) return;
    
    std::string var_name = extract_declarator_name(declarator);
    
    if (var_name == "unknown" || var_name.empty()) {
        reportError("Variable declaration has no name", declarator);
        return;
    }
    
    // Create symbol with basic type
    std::string symbol_type = in_function_params ? "parameter" : "variable";
    Symbol* var_sym = new Symbol(var_name, symbol_type, base_type,
                                symbol_table->get_current_scope_level(), declarator->line_number);
    
    // Extract enhanced type information
    extract_type_info(declarator, var_sym);
    
    std::cout << "[Scope " << symbol_table->get_current_scope_level() 
              << "] Added " << symbol_type << " at line " << declarator->line_number
              << ": " << var_name << " : " << var_sym->get_full_type() << std::endl;
    
    if (!symbol_table->add_symbol(var_sym)) {
        reportError("Variable '" + var_name + "' already declared in this scope", declarator);
        delete var_sym;
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
    
    // Handle FunctionDeclarator
    if (declarator->name == "FunctionDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "DirectDeclarator" || child->name == "Declarator") {
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



bool SemanticAnalyzer::is_function_declaration(ASTNode* declaration_node) {
    if (!declaration_node) return false;
    
    // Simple check: look for ParameterList in the declaration
    for (size_t i = 0; i < declaration_node->children.size(); i++) {
        ASTNode* child = declaration_node->children[i];
        if (!child) continue;
        
        if (child->name == "InitDeclaratorList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* init_decl = child->children[j];
                if (!init_decl || init_decl->name != "InitDeclarator") continue;
                
                // Check if any declarator has parameters
                for (size_t k = 0; k < init_decl->children.size(); k++) {
                    ASTNode* decl = init_decl->children[k];
                    if (!decl) continue;
                    
                    // Skip function pointers (they have Pointer inside FunctionDeclarator)
                    if (is_function_pointer(decl)) {
                        continue; // Skip function pointers
                    }
                    
                    if (has_parameter_list(decl)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// ADD THIS HELPER METHOD:
bool SemanticAnalyzer::is_function_pointer(ASTNode* node) {
    if (!node) return false;
    
    if (node->name == "FunctionDeclarator") {
        // Look for Declarator with Pointer inside FunctionDeclarator
        for (size_t i = 0; i < node->children.size(); i++) {
            ASTNode* child = node->children[i];
            if (!child) continue;
            
            if (child->name == "Declarator") {
                // Check if Declarator has Pointer
                for (size_t j = 0; j < child->children.size(); j++) {
                    if (child->children[j] && child->children[j]->name == "Pointer") {
                        return true; // This is a function pointer
                    }
                }
            }
        }
    }
    return false;
}


void SemanticAnalyzer::process_function_declaration(ASTNode* node) {
    if (!node || !symbol_table) return;
    
    std::string func_name = "unknown";
    std::string return_type = "int";
    
    // Extract return type and function name (same logic as process_function)
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            return_type = extract_base_type(child);
        }
        else if (child->name == "InitDeclaratorList") {
            // Extract function name from declarators
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* init_decl = child->children[j];
                if (!init_decl) continue;
                
                for (size_t k = 0; k < init_decl->children.size(); k++) {
                    ASTNode* decl = init_decl->children[k];
                    func_name = extract_declarator_name(decl);
                    if (func_name != "unknown") break;
                }
                if (func_name != "unknown") break;
            }
        }
    }
    
    if (func_name == "unknown") {
        reportError("Function declaration has no name", node);
        return;
    }
    
    // Check if function already exists
    Symbol* existing = symbol_table->find_symbol(func_name);
    
    if (existing) {
        if (existing->symbol_type == "function") {
            // Function already declared - this is normal for multiple declarations
            std::cout << "[Info] Function '" << func_name << "' already declared" << std::endl;
            // Don't create a new symbol or add to table
        } else {
            reportError("Symbol '" + func_name + "' already declared as different kind", node);
        }
    } else {
        // Create new function symbol
        Symbol* func_sym = new Symbol(func_name, "function", return_type,
                                     symbol_table->get_current_scope_level(), node->line_number);
        
        // Process parameters for type information ONLY
        for (size_t i = 0; i < node->children.size(); i++) {
            ASTNode* child = node->children[i];
            if (!child) continue;
            
            if (child->name == "InitDeclaratorList") {
                process_function_parameters(child);  // Use the version that doesn't add to symbol table
            }
        }
        
        // Add to symbol table
        if (!symbol_table->add_symbol(func_sym)) {
            reportError("Failed to add function declaration '" + func_name + "'", node);
            delete func_sym;
        } else {
            std::cout << "[Declaration] Function: " << func_name << " : " << return_type << std::endl;
        }
    }
}

bool SemanticAnalyzer::has_parameter_list(ASTNode* node) {
    if (!node) return false;
    
    if (node->name == "ParameterList" || node->name == "ParameterTypeList") {
        return true;
    }
    
    for (size_t i = 0; i < node->children.size(); i++) {
        if (has_parameter_list(node->children[i])) {
            return true;
        }
    }
    return false;
}


// New helper method to extract type information
void SemanticAnalyzer::extract_type_info(ASTNode* declarator, Symbol* symbol) {
    if (!declarator || !symbol) return;
    
    // Handle Declarator node (contains Pointer + DirectDeclarator)
    if (declarator->name == "Declarator") {
        extract_pointer_info(declarator, symbol);
        
        // Find the inner DirectDeclarator or ArrayDeclarator
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "DirectDeclarator" || child->name == "ArrayDeclarator") {
                extract_type_info(child, symbol);
            }
        }
    }
    // Handle ArrayDeclarator
    else if (declarator->name == "ArrayDeclarator") {
    // Check if this is pointer-to-array (has Declarator with Pointer inside ArrayDeclarator)
    	bool is_pointer_to_array = false;
    
    	for (size_t i = 0; i < declarator->children.size(); i++) {
        	ASTNode* child = declarator->children[i];
        	if (!child) continue;
        
        	if (child->name == "Declarator") {
            // This is pointer-to-array case: int (*arr_ptr)[10]
           	 extract_pointer_info(child, symbol);
           	 is_pointer_to_array = true;
            
            // Extract the name from inner DirectDeclarator
           	 for (size_t j = 0; j < child->children.size(); j++) {
            	    if (child->children[j] && child->children[j]->name == "DirectDeclarator") {
              	      extract_type_info(child->children[j], symbol);
                	}
            	}
        	}
    	}
    
    	if (!is_pointer_to_array) {
        // Normal array case
        	symbol->is_array = true;
        	extract_array_dimensions(declarator, symbol);
        
        // Find the inner declarator
    	    for (size_t i = 0; i < declarator->children.size(); i++) {
        	    ASTNode* child = declarator->children[i];
        	    if (!child) continue;
            
            	if (child->name == "DirectDeclarator" || child->name == "ArrayDeclarator") {
                	extract_type_info(child, symbol);
            	}
        	}
    } else {
        // For pointer-to-array, extract array dimensions from the ArrayDeclarator itself
        symbol->is_array = true;
        extract_array_dimensions(declarator, symbol);
    }
}
    // Handle FunctionDeclarator (for function pointers)
    else if (declarator->name == "FunctionDeclarator") {
        // Check if this is a function pointer (has Pointer inside Declarator)
        bool is_func_ptr = false;
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "Declarator") {
                extract_pointer_info(child, symbol);
                is_func_ptr = symbol->is_pointer; // Will be true if we found pointers
                
                // Extract the name from inner DirectDeclarator
                for (size_t j = 0; j < child->children.size(); j++) {
                    if (child->children[j] && child->children[j]->name == "DirectDeclarator") {
                        extract_type_info(child->children[j], symbol);
                    }
                }
            }
        }
        
        if (is_func_ptr) {
            // This is a function pointer variable
            symbol->symbol_type = "variable";
            // TODO: Extract function parameter types for the function pointer
        } else {
            // This is a function declaration
            symbol->symbol_type = "function";
        }
    }
}

// Extract pointer information from nested Pointer nodes
void SemanticAnalyzer::extract_pointer_info(ASTNode* declarator, Symbol* symbol) {
    if (!declarator || !symbol) return;
    
    // Count nested Pointer nodes
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        if (child->name == "Pointer") {
            symbol->is_pointer = true;
            symbol->pointer_level++;
            
            // Check for nested pointers (int** etc.)
            for (size_t j = 0; j < child->children.size(); j++) {
                if (child->children[j] && child->children[j]->name == "Pointer") {
                    extract_pointer_info(child, symbol);
                }
            }
        }
    }
}

// Extract array dimensions from nested ArrayDeclarator nodes
void SemanticAnalyzer::extract_array_dimensions(ASTNode* array_declarator, Symbol* symbol) {
    if (!array_declarator || !symbol || array_declarator->name != "ArrayDeclarator") return;
    
    // Look for Constant children for array dimensions
    for (size_t i = 0; i < array_declarator->children.size(); i++) {
        ASTNode* child = array_declarator->children[i];
        if (!child) continue;
        
        if (child->name == "Constant" && !child->lexeme.empty() && child->lexeme != "default") {
            try {
                int dimension = std::stoi(child->lexeme);
                symbol->array_dimensions.push_back(dimension);
            } catch (const std::exception& e) {
                // If not a number, treat as incomplete array (size 0 or -1)
                symbol->array_dimensions.push_back(-1);
            }
        }
    }
    
    // If no Constant found, it's an incomplete array
    if (symbol->array_dimensions.empty()) {
        symbol->array_dimensions.push_back(-1);
    }
    
    // Reverse dimensions because they're stored outermost first in AST
    // but we want innermost first for type representation
    std::reverse(symbol->array_dimensions.begin(), symbol->array_dimensions.end());
}
void SemanticAnalyzer::check_member_access(ASTNode* node) {
    if (!node || node->name != "MemberAccess") return;
    if (node->children.size() < 2) return;
    
    ASTNode* struct_node = node->children[0];  // p
    ASTNode* member_node = node->children[1];  // x
    
    if (!struct_node || !member_node) return;
    
    // Find the struct variable
    Symbol* struct_var = symbol_table->find_symbol(struct_node->lexeme);
    if (!struct_var) return;
    
    // Get struct type name and clean it
    std::string struct_type_name = struct_var->base_type;
    std::string clean_struct_name = struct_type_name;
    if (struct_type_name.find("struct ") == 0) {
        clean_struct_name = struct_type_name.substr(7);
    } else if (struct_type_name.find("union ") == 0) {
        clean_struct_name = struct_type_name.substr(6);
    }
    
    // Find the struct type definition
    Symbol* struct_type = symbol_table->find_symbol(clean_struct_name);
    if (!struct_type || !struct_type->is_complete) return;
    
    // Check if member exists
    std::string member_name = member_node->lexeme;
    for (auto member : struct_type->members) {
        if (member->name == member_name) {
            std::cout << "[Member Access] " << struct_node->lexeme << "." << member_name << std::endl;
            return;
        }
    }
}