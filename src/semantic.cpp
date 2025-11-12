#include "semantic.h"
#include <iostream>
#include <functional>
#include <algorithm>  

#include <unordered_set>
int semantic_error_count = 0;
bool semantic_ok = true;

static const std::unordered_set<std::string> builtin_functions = {
    "printf", "scanf", "gets", "puts", "fopen", "fclose", "fread", "fwrite",
    "malloc", "free", "exit", "strlen", "strcpy", "strcmp", "strcat", "atoi",
    "atof", "sprintf", "fprintf", "fscanf", "getchar", "putchar"
};

SemanticAnalyzer::SemanticAnalyzer(SymbolTable* table) 
    : symbol_table(table), in_function_params(false), error_count(0),
      loop_depth(0), switch_depth(0), current_function_name(""), 
      current_function_return_type("") {
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
     extern bool has_semantic_errors;
    has_semantic_errors = true;
}

void SemanticAnalyzer::check_identifier_usage(ASTNode* node) {
    if (!node || (node->name != "Identifier" && node->name != "IDENTIFIER")) return;
    
    std::string identifier = node->lexeme;
    if (identifier.empty() || identifier == "default") return;
    
    // Handle NULL/nullptr
    if (identifier == "NULL" || identifier == "nullptr") {
        return;
    }
    
    // Skip if we're in a declaration context
    if (node->parent && (node->parent->name == "DirectDeclarator" || 
                         node->parent->name == "StructDeclarator" ||
                         node->parent->name == "ParameterDeclaration"||
                         node->parent->name == "EnumSpecifier"||
                         node->parent->name == "MemberAccess")) {
        return;
    }
    
    Symbol* symbol = symbol_table->find_symbol(identifier);

    // Attach symbol to node for codegen to use
    if (symbol) {
        node->symbol = symbol;
    }

    // ADD STANDARD LIBRARY CHECK
    if (!symbol && builtin_functions.find(identifier) != builtin_functions.end()) {

        return; // Don't report error for standard library functions
    }

    if (symbol) {
        if (symbol->symbol_type == "variable" && !symbol->is_initialized) {
            // Don't warn for arrays - they can be initialized element by element
            if (symbol->is_array) {
                return;
            }
            
            // Check if this identifier is being written to (not read from)
            bool is_being_written = false;
            ASTNode* parent = node->parent;
            
            // 1. Check if it's in a ForInitStatement (for loop initializer)
            ASTNode* ancestor = parent;
            while (ancestor) {
                if (ancestor->name == "ForInitStatement") {
                    is_being_written = true;
                    break;
                }
                ancestor = ancestor->parent;
            }
            
            // 2. Check if it's the operand of ++/-- (unary increment/decrement)
            if (!is_being_written && parent && parent->name == "UnaryExpression") {
                if (parent->lexeme == "++" || parent->lexeme == "--") {
                    is_being_written = true;
                }
                // Also check for postfix increment/decrement (PostfixExpression)
            }
            if (!is_being_written && parent && parent->name == "PostfixExpression") {
                if (parent->lexeme == "++" || parent->lexeme == "--") {
                    is_being_written = true;
                }
            }
            
            // 3. Check if it's the LHS of any assignment (=, +=, -=, etc.)
            if (!is_being_written && parent && parent->name == "AssignmentExpression") {
                if (parent->children.size() >= 2 && parent->children[0] == node) {
                    is_being_written = true;
                }
            }
            
            // 4. Check if it's part of an array subscript on the LHS of assignment
            if (!is_being_written && parent && parent->name == "ArraySubscript") {
                // Traverse up to find if this ArraySubscript is on LHS of assignment
                ancestor = parent;
                while (ancestor && ancestor->name == "ArraySubscript") {
                    ancestor = ancestor->parent;
                }
                if (ancestor && ancestor->name == "AssignmentExpression" && 
                    ancestor->children.size() >= 2) {
                    ASTNode* lhs = ancestor->children[0];
                    // Check if our node is part of the LHS subtree
                    if (lhs == parent || contains_node(lhs, node)) {
                        is_being_written = true;
                    }
                }
            }
            
            // 5. Check if it's in a declaration with initializer
            if (!is_being_written) {
                ancestor = parent;
                while (ancestor) {
                    if (ancestor->name == "InitDeclarator" && ancestor->children.size() > 1) {
                        is_being_written = true;
                        break;
                    }
                    ancestor = ancestor->parent;
                }
            }
            
            if (!is_being_written) {
                report_warning("Variable '" + identifier + "' may be uninitialized", node);
            }
        }

    } else {
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

    if (type_symbol && type_symbol->symbol_type == "typedef") {
        return true;
    }

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

bool SemanticAnalyzer::contains_node(ASTNode* root, ASTNode* target) {
    if (!root || !target) return false;
    if (root == target) return true;
    
    for (auto child : root->children) {
        if (contains_node(child, target)) {
            return true;
        }
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
    warning_count = 0;  // Initialize this too
    
    // Reset function context
    current_function_name = "";
    current_function_return_type = "";
    
    traverse(root);
    
    std::cout << "=== SEMANTIC ANALYSIS COMPLETED ===" << std::endl;
    std::cout << "Found " << error_count << " semantic error(s)" << std::endl;
    std::cout << "Found " << warning_count << " warning(s)" << std::endl;
}

void SemanticAnalyzer::traverse(ASTNode* node) {
    if (!node) {
        std::cout << "WARNING: traverse called with null node" << std::endl;
        return;
    }
    
    if (node->processed) return;


    node->processed = true;

    // Handle FunctionDefinition FIRST - this sets context before processing children
    if (node->name == "FunctionDefinition") {
        process_function(node);
        return; // process_function already traverses children with proper context
    }

    // Handle other special nodes that need processing
    if (node->name == "StructOrUnionSpecifier") {
        bool is_top_level = true;
        ASTNode* parent = node->parent;
        while (parent) {
            if (parent->name == "StructDeclaration") {
                is_top_level = false;
                break;
            }
            parent = parent->parent;
        }
        
        if (is_top_level) {
            process_struct_or_union(node);
            
        }
    }
    else if (node->name == "EnumSpecifier") {
        process_enum(node);
       
    }

    // Handle scope-changing constructs
    if (node->name == "WhileStatement" || node->name == "DoWhileStatement" ||node->name == "UntilStatement" || 
        node->name == "ForStatement") {
        loop_depth++;
        if (node->children.size() > 0) {
            check_loop_condition(node->children[0]);
        }
    }
    
    if (node->name == "SwitchStatement") {
        switch_depth++;
        case_values_in_switch.clear();
        has_default_in_switch = false;
        if (node->children.size() > 0) {
            check_switch_statement(node);
        }
    }

    // SEMANTIC CHECKS (consolidated - no duplicates)
    if (node->name == "AssignmentExpression") {
        check_assignment(node);
        check_function_pointer_assignment(node);
    }
    else if (node->name == "FunctionCall") {
        check_function_call(node);
        check_function_pointer_call(node);

    }
    else if (node->name == "ReturnStatement") {

        check_return_statement(node);
    }
    else if (node->name == "BreakStatement" || node->name == "ContinueStatement") {
        check_break_continue(node);
    }
    else if (node->name == "ArraySubscript") {
        check_array_access(node);
    }
    else if (node->name == "CaseStatement") {
        check_case_statement(node);
    }
    else if (node->name == "GotoStatement") {
        check_goto_statement(node);
    }
    else if (node->name == "LabeledStatement") {
        check_label_statement(node);
    }
    else if (node->name == "AdditiveExpression" || node->name == "MultiplicativeExpression" ||
             node->name == "RelationalExpression" || node->name == "EqualityExpression" ||
             node->name == "LogicalAndExpression" || node->name == "LogicalOrExpression") {
        check_binary_operation(node);
    }
    else if (node->name == "UnaryExpression") {
        check_unary_operation(node);
        
    }
    else if (node->name == "IfStatement" && node->children.size() > 0) {
        check_if_condition(node->children[0]);
    }
    else if (node->name == "MemberAccess") {
        check_member_access(node);
    }
    else if (node->name == "Declaration") {
        // Check initialization in declarations
        if (is_function_declaration(node)) {
            process_function_declaration(node);
        } else {
            process_declaration(node);
            // Also check initialization types
            check_declaration_initialization(node);
        }
    }

    // Handle ForStatement scope properly
    if (node->name == "ForStatement") {
        bool needs_scope = false;
        for (auto child : node->children) {
            if (child && child->name == "ForInitStatement") {
                for (auto init_child : child->children) {
                    if (init_child && init_child->name == "Declaration") {
                        needs_scope = true;
                        break;
                    }
                }
                break;
            }
        }
        
        if (needs_scope) {
            symbol_table->enter_scope();
            
            for (auto child : node->children) {
                if (child) traverse(child);
            }
            
            symbol_table->exit_scope();
            
            if (loop_depth > 0) loop_depth--;
            return;
        }
    }

    // Handle CompoundStatement scopes
    if (node->name == "CompoundStatement") {
        bool is_function_body = (node->parent && node->parent->name == "FunctionDefinition");
        
        if (!is_function_body) {
            symbol_table->enter_scope();
            
            for (size_t i = 0; i < node->children.size(); i++) {
                if (node->children[i]) traverse(node->children[i]);
            }
            
            symbol_table->exit_scope();
            return;
        }
        // If it's a function body, continue to process children normally
    }

    // Handle Identifier usage
    if (node->name == "Identifier" || node->name == "IDENTIFIER") {
        check_identifier_usage(node);
    }

    // Normal traversal for other nodes
    for (size_t i = 0; i < node->children.size(); i++) {
        if (node->children[i]) traverse(node->children[i]);
    }

    // Decrement depths when leaving loop/switch nodes
    if ((node->name == "WhileStatement" || node->name == "DoWhileStatement" ||node->name == "UntilStatement" || 
         node->name == "ForStatement") && loop_depth > 0) {
        loop_depth--;
    }
    if (node->name == "SwitchStatement" && switch_depth > 0) {
        switch_depth--;
        case_values_in_switch.clear();
        has_default_in_switch = false;
    }

}

void SemanticAnalyzer::process_declaration(ASTNode* node) {
    if (!node) return;

    bool is_typedef = false;
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* spec_child = child->children[j];
                if (spec_child && spec_child->name == "StorageClass" && 
                    spec_child->lexeme == "typedef") {
                    is_typedef = true;
                    break;
                }
            }
        }
    }
    
    if (is_typedef) {
        process_typedef(node);
        return;  // Don't process as regular declaration
    }
    
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
                    // Check if this InitDeclarator has an initializer
                    bool has_init = (init_decl->children.size() > 1);
                    
                    for (size_t k = 0; k < init_decl->children.size(); k++) {
                        ASTNode* decl = init_decl->children[k];
                        if (!decl) continue;
                        
                        // ADD FunctionDeclarator to handle function pointers
                        if (decl->name == "DirectDeclarator" || decl->name == "ArrayDeclarator" || 
                            decl->name == "Declarator" || decl->name == "FunctionDeclarator"||decl->name == "ReferenceDeclarator") {
                            process_variable(decl, base_type);
                            
                            // Mark as initialized if has initializer
                            if (has_init && decl->symbol) {
                                decl->symbol->is_initialized = true;
                            }
                        }
                    }
                    
                    // Also check initialization compatibility
                    if (has_init) {
                        // Get the full type including pointer level from the symbol
                        std::string full_type = base_type;
                        if (init_decl->children.size() > 0 && init_decl->children[0]->symbol) {
                            full_type = init_decl->children[0]->symbol->get_full_type();
                        }
                        check_initialization(init_decl, full_type);
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
    bool returns_function_pointer = false;

    
    
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
    else if (child->name == "ReferenceDeclarator") {
        func_name = extract_function_name(child);
        return_type += "&";  // Add reference to return type
    }

        else if (child->name == "Declarator" || child->name == "FunctionDeclarator") {
            func_name = extract_function_name(child);
 
            
            if (child->name == "FunctionDeclarator") {
                // Check if this is a function returning a function pointer
                for (size_t j = 0; j < child->children.size(); j++) {
                    ASTNode* grandchild = child->children[j];
                    if (!grandchild) continue;
                    
                    if (grandchild->name == "Declarator") {
                        // This is a function returning a function pointer
                        returns_function_pointer = true;
                        
                        // Use the OUTER FunctionDeclarator (the current child) to build the return type
                        // NOT the inner one
                        return_type = build_function_pointer_return_type(child, return_type);
                        break;
                    }
                }
            }
        }
    }
    
    if (!return_type_found) {
        reportError("Function missing return type", node);
    }
    
    if (func_name == "unknown") {
        reportError("Function has no name", node);
        return;
    }
    

    
    // SET FUNCTION CONTEXT - ADD THIS
    std::string previous_function = current_function_name;
    std::string previous_return_type = current_function_return_type;
    current_function_name = func_name;
    current_function_return_type = return_type;
    
    // Check if function already exists
    Symbol* existing = symbol_table->find_symbol(func_name);
    Symbol* func_sym;
    
    if (existing && existing->symbol_type == "function") {
        // Function already declared - use existing symbol
        func_sym = existing;
        
        // Update return type if this is a function pointer return
        if (returns_function_pointer) {
            func_sym->return_type = return_type;
        }
    } else {
        // Create new function symbol
        func_sym = new Symbol(func_name, "function", return_type, 
                             symbol_table->get_current_scope_level(), node->line_number);
        
        // Store the full return type for function pointer returns
        if (returns_function_pointer) {
            func_sym->return_type = return_type;
        }
        
        // Add to CURRENT scope (should be global)
        if (!symbol_table->add_symbol(func_sym)) {
            reportError("Failed to add function '" + func_name + "' to symbol table", node);
            delete func_sym;
            
            // RESTORE CONTEXT ON ERROR - ADD THIS
            current_function_name = previous_function;
            current_function_return_type = previous_return_type;
            return;
        }
    }
    node->symbol = func_sym;
    
    // Check if this is a function definition (has CompoundStatement body)
    bool has_body = false;
    for (size_t i = 0; i < node->children.size(); i++) {
        if (node->children[i] && node->children[i]->name == "CompoundStatement") {
            has_body = true;
            break;
        }
    }
    
    // If this is a definition and parameters already exist (from forward declaration),
    // clear them so we don't add duplicates
    if (has_body && !func_sym->parameters.empty()) {
        for (Symbol* param : func_sym->parameters) {
            delete param;
        }
        func_sym->parameters.clear();
    }
    
    // NOW enter function scope for parameters
    symbol_table->enter_scope();
    
    // Process parameters AND store them in function symbol
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "Declarator" || child->name == "FunctionDeclarator"||child->name == "ReferenceDeclarator") {
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
    
    symbol_table->exit_scope();
    
    current_function_name = previous_function;
    current_function_return_type = previous_return_type;
}
std::string SemanticAnalyzer::build_function_pointer_return_type(ASTNode* func_declarator, const std::string& base_type) {
    if (!func_declarator || func_declarator->name != "FunctionDeclarator") {
        return base_type;
    }
    
    // Build function pointer type: int(*)(params)
    std::string result = base_type + "(*)(";
    
    
    // Extract parameters from ParameterList
    for (size_t i = 0; i < func_declarator->children.size(); i++) {
        ASTNode* child = func_declarator->children[i];
        if (!child) continue;
        
        if (child->name == "ParameterList") {
           
            // Handle empty parameter list - should be empty, not "void"
            if (child->children.empty()) {
                // Empty parameter list means it takes no parameters
                // Leave it empty: int(*)()

            } else {
                // Extract each parameter
                for (size_t j = 0; j < child->children.size(); j++) {
                    ASTNode* param_node = child->children[j];
                    if (!param_node || param_node->name != "ParameterDeclaration") continue;
                    
                    if (j > 0) result += ", ";
                    
                    // Extract parameter type from DeclarationSpecifiers
                    std::string param_type = "int";
                    for (size_t k = 0; k < param_node->children.size(); k++) {
                        ASTNode* param_child = param_node->children[k];
                        if (!param_child) continue;
                        
                        if (param_child->name == "DeclarationSpecifiers") {
                            param_type = extract_base_type(param_child);
                            
                            break;
                        }
                    }
                    result += param_type;
                }
            }
            break;
        }
    }
    
    // If no ParameterList found at all, it means no parameters specified
    // In C, this means it takes an unspecified number of parameters, not void
    // So we leave it empty: int(*)()

    result += ")";
    return result;
}
void SemanticAnalyzer::process_function_parameters(ASTNode* declarator) {
    if (!declarator) return;

    if (declarator->name == "ReferenceDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "FunctionDeclarator") {
                process_function_parameters(child);
                return;
            }
        }
    }

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
    
    if (declarator->name == "ReferenceDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "FunctionDeclarator") {
                process_function_parameters(child, func_sym);
                return;
            }
        }
    }

    
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        if (child->name == "DirectDeclarator") {
            process_function_parameters(child, func_sym);
        }
        else if (child->name == "FunctionDeclarator") {
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
    if (declarator->name == "ReferenceDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "FunctionDeclarator") {
                std::string name = extract_function_name(child);
                if (name != "unknown") return name;
            }
        }
    }
    
    // Handle FunctionDeclarator - search for DirectDeclarator with name
    if (declarator->name == "FunctionDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            // Look for DirectDeclarator with name
            if (child->name == "DirectDeclarator") {
                if (!child->lexeme.empty() && child->lexeme != "default") {
                    return child->lexeme;
                }
            }
            // Look for Declarator that contains DirectDeclarator
            else if (child->name == "Declarator") {
                for (size_t j = 0; j < child->children.size(); j++) {
                    ASTNode* grandchild = child->children[j];
                    if (!grandchild) continue;
                    
                    if (grandchild->name == "DirectDeclarator" && 
                        !grandchild->lexeme.empty() && grandchild->lexeme != "default") {
                        return grandchild->lexeme;
                    }
                    // Handle nested FunctionDeclarator
                    else if (grandchild->name == "FunctionDeclarator") {
                        std::string name = extract_function_name(grandchild);
                        if (name != "unknown") return name;
                    }
                }
            }
        }
    }
    
    // Handle Declarator node
    if (declarator->name == "Declarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "DirectDeclarator") {
                if (!child->lexeme.empty() && child->lexeme != "default") {
                    return child->lexeme;
                }
            }
            // Handle nested FunctionDeclarator inside Declarator
            else if (child->name == "FunctionDeclarator") {
                std::string name = extract_function_name(child);
                if (name != "unknown") return name;
            }
        }
    }
    
    // Search recursively in children
    for (size_t i = 0; i < declarator->children.size(); i++) {
        ASTNode* child = declarator->children[i];
        if (!child) continue;
        
        std::string result = extract_function_name(child);
        if (result != "unknown") {
            return result;
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
        } else {            
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

        Symbol* typedef_sym = new Symbol(type_name, "typedef", symbol_type,
                                       symbol_table->get_current_scope_level(), node->line_number);
        if (!symbol_table->add_symbol(typedef_sym)) {
            // Type name might already exist - that's fine
            delete typedef_sym;
        }     }
    node->symbol = type_sym;

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
                        
                        if (decl_child->name == "TypeSpecifier" || decl_child->name == "EnumSpecifier") {
    				member_base_type = extract_base_type(decl_child);  // returns "enum Color" 
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
       
    } 
}

// NEW METHOD: Process individual struct members with enhanced type extraction
void SemanticAnalyzer::process_struct_member(ASTNode* member_decl, const std::string& base_type, 
                                           Symbol* struct_sym, const std::string& struct_type) {
    if (!member_decl || !struct_sym) return;
    
    std::string member_name = extract_declarator_name(member_decl);
    if (member_name == "unknown") return;
    

    if (is_incomplete_type(base_type)) {
        reportError("field '" + member_name + "' has incomplete type '" + base_type + "'", member_decl);
        return; // Don't process further
    }

    // Create member symbol with basic type
    Symbol* member_sym = new Symbol(member_name, "member", base_type,
                                   struct_sym->scope_level, 0);
    
    // Extract enhanced type information (pointers, arrays, etc.)
    extract_type_info(member_decl, member_sym);
    member_decl->symbol = member_sym;
    struct_sym->add_member(member_sym);
}

void SemanticAnalyzer::process_enum(ASTNode* node) {

    
    if (!node || !symbol_table) {
        return;
    }
    
    std::string enum_name = "anonymous";
    std::vector<std::pair<std::string, int>> enumerators;
    int next_value = 0;
    bool has_enumerators = false;

    // Extract enum name and check if it has enumerators
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if ((child->name == "Identifier" || child->name == "IDENTIFIER") && 
            !child->lexeme.empty() && child->lexeme != "default") {
            enum_name = child->lexeme;
        }
        else if (child->name == "EnumeratorList") {
            has_enumerators = true;
            enumerators = extract_enumerators(child, next_value);
        }
    }
    
    // Check if enum already exists
    Symbol* existing = symbol_table->find_symbol(enum_name);
    
    if (existing && existing->symbol_type == "enum") {

        if (has_enumerators) {
            // Check if this is completing a forward declaration
            if (existing->is_complete) {
                reportError("Enum '" + enum_name + "' already declared", node);
                return;
            } else {
                // Complete the forward declaraition
                
                // Add enumerators to the existing enum symbol
                for (const auto& enumerator : enumerators) {
                    existing->add_enumerator(enumerator.first, enumerator.second);
                    
                    // Create enum constant symbol
                    Symbol* const_sym = new Symbol(enumerator.first, "enum_constant", "int",
                                                  symbol_table->get_current_scope_level(), node->line_number);
                    const_sym->const_value = enumerator.second;
                    const_sym->enum_type = enum_name;
                    
                    if (!symbol_table->add_symbol(const_sym)) {
                        reportError("Enumerator '" + enumerator.first + "' already declared", node);
                        delete const_sym;
                    }                 }
                
                // Mark the enum as complete
                existing->is_complete = true;
                
                // === ADD THIS: Associate existing symbol with AST node ===
                node->symbol = existing;
                
               
            }
        } else {
            // Another forward declaration - ignore
            // === ADD THIS: Still associate the existing symbol ===
            node->symbol = existing;
           
        }
        return;
    }
    
    if (!has_enumerators) {
   
        Symbol* enum_sym = new Symbol(enum_name, "enum", "int", 
                                     symbol_table->get_current_scope_level(), node->line_number);
        
        if (!symbol_table->add_symbol(enum_sym)) {
            reportError("Failed to add enum '" + enum_name + "' to symbol table", node);
            delete enum_sym;
        } else {
            // === ADD THIS: Associate symbol with AST node on success ===
            node->symbol = enum_sym;
           
        }

        return;
    }
    
    // Complete enum definition
    Symbol* enum_sym = new Symbol(enum_name, "enum", "int", 
                                 symbol_table->get_current_scope_level(), node->line_number);

    enum_sym->is_complete = true;

    // Add enumerators to the enum symbol and current scope

    for (const auto& enumerator : enumerators) {

        enum_sym->add_enumerator(enumerator.first, enumerator.second);
        
        // Create enum constant symbol
        Symbol* const_sym = new Symbol(enumerator.first, "enum_constant", "int",
                                      symbol_table->get_current_scope_level(), node->line_number);
        const_sym->const_value = enumerator.second;
        const_sym->enum_type = enum_name;
        

        if (!symbol_table->add_symbol(const_sym)) {
            reportError("Enumerator '" + enumerator.first + "' already declared", node);
            delete const_sym;
        }
    }
    
    // Add enum to symbol table

    if (!symbol_table->add_symbol(enum_sym)) {
        reportError("Failed to add enum '" + enum_name + "' to symbol table", node);
        delete enum_sym;
    } else {
        // === ADD THIS: Associate symbol with AST node on success ===
        node->symbol = enum_sym;

    }
    

    Symbol* typedef_sym = new Symbol(enum_name, "typedef", "int",
                                   symbol_table->get_current_scope_level(), node->line_number);
    if (!symbol_table->add_symbol(typedef_sym)) {
        delete typedef_sym;
    }
}

std::vector<std::pair<std::string, int>> SemanticAnalyzer::extract_enumerators(ASTNode* enumerator_list, int& next_value) {
    std::vector<std::pair<std::string, int>> enumerators;
    
    if (!enumerator_list || enumerator_list->name != "EnumeratorList") {
        report_warning("[WARNING] extract_enumerators called with invalid node");
        return enumerators;
    }
    
    for (size_t i = 0; i < enumerator_list->children.size(); i++) {
        ASTNode* enumerator_node = enumerator_list->children[i];
        if (!enumerator_node || enumerator_node->name != "Enumerator") continue;
        
        std::string enumerator_name = "unknown";
        int enumerator_value = next_value;
        
        // Get enumerator name
        if (!enumerator_node->lexeme.empty() && enumerator_node->lexeme != "default") {
            enumerator_name = enumerator_node->lexeme;
        } else {
            // Try to get name from children
            for (size_t j = 0; j < enumerator_node->children.size(); j++) {
                ASTNode* child = enumerator_node->children[j];
                if (child && !child->lexeme.empty() && child->lexeme != "default") {
                    enumerator_name = child->lexeme;
                    break;
                }
            }
        }
        
        if (enumerator_name == "unknown") {
            report_warning("[WARNING] Could not extract enumerator name");
            continue;
        }
        
        // Look for explicit value
        for (size_t j = 0; j < enumerator_node->children.size(); j++) {
            ASTNode* child = enumerator_node->children[j];
            if (!child) continue;
            
            if (child->name == "Constant") {
                try {
                    enumerator_value = std::stoi(child->lexeme);
                } catch (const std::exception& e) {
                    enumerator_value = next_value;
                }
            }
            // Handle unary expressions like -1, +5
            else if (child->name == "UnaryExpression") {
                if ((child->lexeme == "-" || child->lexeme == "uminus") && 
                    !child->children.empty() && 
                    child->children[0]->name == "Constant") {
                    try {
                        enumerator_value = -std::stoi(child->children[0]->lexeme);
                    } catch (const std::exception& e) {
                        enumerator_value = next_value;
                    }
                } else if (child->lexeme == "+" && 
                           !child->children.empty() && 
                           child->children[0]->name == "Constant") {
                    try {
                        enumerator_value = std::stoi(child->children[0]->lexeme);
                    } catch (const std::exception& e) {
                        enumerator_value = next_value;
                    }
                }
            }
        }
        
        enumerators.push_back(std::make_pair(enumerator_name, enumerator_value));
        next_value = enumerator_value + 1;
    }
    
    return enumerators;
}
bool SemanticAnalyzer::is_incomplete_type(const std::string& type) {
    // Handle struct/union types
    if (type.find("struct ") == 0) {
        std::string struct_name = type.substr(7);
        Symbol* struct_sym = symbol_table->find_symbol(struct_name);
        return !struct_sym || !struct_sym->is_complete;
    }
    else if (type.find("union ") == 0) {
        std::string union_name = type.substr(6);
        Symbol* union_sym = symbol_table->find_symbol(union_name);
        return !union_sym || !union_sym->is_complete;
    }
    else if (type.find("enum ") == 0) {
        std::string enum_name = type.substr(5);
        Symbol* enum_sym = symbol_table->find_symbol(enum_name);

        return !enum_sym || !enum_sym->is_complete;
    }
    
    // Arrays with unknown size are incomplete
    if (type.find('[') != std::string::npos && type.find("[]") != std::string::npos) {
        return true;
    }
    
    // void is incomplete (except in function return types)
    if (type == "void") {
        return true;
    }
    
    return false;
}
void SemanticAnalyzer::process_typedef(ASTNode* declaration) {
    if (!declaration || !symbol_table) return;
    
    std::string base_type = "int";

    // Extract base type FIRST
    for (size_t i = 0; i < declaration->children.size(); i++) {
        ASTNode* child = declaration->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            base_type = extract_base_type(child);

            break;
        }
    }
    
    if (!is_valid_type(base_type)) {
        return;
    }
    
    // Process ALL declarators in InitDeclaratorList
    for (size_t i = 0; i < declaration->children.size(); i++) {
        ASTNode* child = declaration->children[i];
        if (!child || child->name != "InitDeclaratorList") continue;
        
        // Process each InitDeclarator
        for (size_t j = 0; j < child->children.size(); j++) {
            ASTNode* init_decl = child->children[j];
            if (!init_decl || init_decl->name != "InitDeclarator") continue;
            
            // Extract name from this declarator
            std::string typedef_name = "unknown";
            ASTNode* declarator_node = nullptr;  // === ADD THIS ===
            
            for (size_t k = 0; k < init_decl->children.size(); k++) {
                ASTNode* decl = init_decl->children[k];
                if (!decl) continue;
                
                typedef_name = extract_declarator_name(decl);
                if (typedef_name != "unknown") {
                    declarator_node = decl;  // === ADD THIS: Save the declarator node ===
                    break;
                }
            }
            
            if (typedef_name != "unknown") {
                // Create symbol for EACH typedef name
                Symbol* typedef_sym = new Symbol(typedef_name, "typedef", base_type,
                                               symbol_table->get_current_scope_level(), 
                                               declaration->line_number);
                
                // Extract type info if needed
                if (declarator_node) {  // === USE THE SAVED NODE ===
                    extract_type_info(declarator_node, typedef_sym);

                    declarator_node->symbol = typedef_sym;
                }
                
                if (!symbol_table->add_symbol(typedef_sym)) {
                    reportError("Typedef '" + typedef_name + "' already declared", declaration);
                    delete typedef_sym;

                    if (declarator_node) declarator_node->symbol = nullptr;
                } else {

                }
            }
        }
    }
}

std::string SemanticAnalyzer::extract_typedef_name(ASTNode* init_decl_list) {
    if (!init_decl_list) return "unknown";
    
    for (size_t i = 0; i < init_decl_list->children.size(); i++) {
        ASTNode* init_decl = init_decl_list->children[i];
        if (!init_decl || init_decl->name != "InitDeclarator") continue;
        
        // Use your existing extract_declarator_name but search ALL children
        for (size_t j = 0; j < init_decl->children.size(); j++) {
            ASTNode* decl = init_decl->children[j];
            if (!decl) continue;
            
            // Just use your existing function - it should handle ArrayDeclarator
            std::string name = extract_declarator_name(decl);
            if (name != "unknown") {
                return name;
            }
        }
    }
    return "unknown";
}

void SemanticAnalyzer::process_parameter(ASTNode* param_decl) {
    if (!param_decl || !symbol_table) return;
    
    std::string base_type = "int";
    std::string param_name = "unknown";
    ASTNode* declarator_node = nullptr;
    
    for (size_t i = 0; i < param_decl->children.size(); i++) {
        ASTNode* child = param_decl->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            base_type = extract_base_type(child);
        }
        else if (child->name == "Declarator" || child->name == "DirectDeclarator" || 
                 child->name == "FunctionDeclarator" || child->name == "ArrayDeclarator" ||
                 child->name == "ReferenceDeclarator") {
            param_name = extract_declarator_name(child);
            declarator_node = child;
        }
    }
    
    if (param_name != "unknown") {
        // Create symbol with base type first
        Symbol* param_sym = new Symbol(param_name, "parameter", base_type,
                                      symbol_table->get_current_scope_level(), param_decl->line_number);
        
        // EXTRACT FULL TYPE INFO
        if (declarator_node) {
            extract_type_info(declarator_node, param_sym);
        }
        
        // Get the FULL type after extraction
        std::string full_type = param_sym->get_full_type();
        
        // Update to full type
        param_sym->base_type = full_type;
        param_sym->pointer_level = 0;
        
        declarator_node->symbol = param_sym;
        

        
        if (!symbol_table->add_symbol(param_sym)) {
            reportError("Parameter '" + param_name + "' already declared", param_decl);
            declarator_node->symbol = nullptr;
            delete param_sym;
        } 
    }
}

void SemanticAnalyzer::process_parameter(ASTNode* param_decl, Symbol* func_sym) {
    if (!param_decl || !symbol_table) return;
    
    std::string base_type = "int";
    std::string param_name = "unknown";
    ASTNode* declarator_node = nullptr;
    
    // Extract base type and find declarator
    for (size_t i = 0; i < param_decl->children.size(); i++) {
        ASTNode* child = param_decl->children[i];
        if (!child) continue;
        
        if (child->name == "DeclarationSpecifiers") {
            base_type = extract_base_type(child);
        }
        else if (child->name == "Declarator" || child->name == "DirectDeclarator" || 
                 child->name == "FunctionDeclarator" || child->name == "ArrayDeclarator" ||
                 child->name == "ReferenceDeclarator") {
            param_name = extract_declarator_name(child);
            declarator_node = child;
        }
    }
    
    if (param_name != "unknown") {
        // Create symbol with base type first
        Symbol* param_sym = new Symbol(param_name, "parameter", base_type,
                                      symbol_table->get_current_scope_level(), param_decl->line_number);
        
        // EXTRACT FULL TYPE INFO (including pointers, arrays, etc.)
        if (declarator_node) {
            extract_type_info(declarator_node, param_sym);
        }
        
        // Get the FULL type after extraction (now includes pointers)
        std::string full_type = param_sym->get_full_type();
        
        // Update the symbol's type to the full type
        param_sym->base_type = full_type;
        param_sym->pointer_level = 0; // Reset since it's now in base_type
        
        declarator_node->symbol = param_sym;
        
        
        // Add to current scope
        if (!symbol_table->add_symbol(param_sym)) {
            reportError("Parameter '" + param_name + "' already declared", param_decl);
            declarator_node->symbol = nullptr;
            delete param_sym;
        }
        // Add to function parameter list with FULL type
        if (func_sym) {
            Symbol* func_param_sym = new Symbol(param_name, "parameter", full_type,
                                              func_sym->scope_level, 0);
            func_sym->add_parameter(func_param_sym);
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
    
    // If this is a FunctionDeclarator, extract parameters for function pointers
    if (declarator->name == "FunctionDeclarator" && var_sym->is_function_pointer) {
        extract_function_pointer_parameters(declarator, var_sym);
    }
    
    declarator->symbol = var_sym;
    
    
    if (!symbol_table->add_symbol(var_sym)) {
        reportError("Variable '" + var_name + "' already declared in this scope", declarator);
        declarator->symbol = nullptr; 
        delete var_sym;
    }

    if (var_sym->is_reference) {
        // Check if parent is InitDeclarator with initializer
        ASTNode* parent = declarator->parent;
        bool has_init = false;
        
        if (parent && parent->name == "InitDeclarator" && parent->children.size() > 1) {
            has_init = true;
        }
        
        if (!has_init) {
            reportError("Reference '" + var_name + "' must be initialized", declarator);
        }
    }

}
void SemanticAnalyzer::extract_function_pointer_parameters(ASTNode* func_declarator, Symbol* func_ptr_sym) {
    if (!func_declarator || !func_ptr_sym || func_declarator->name != "FunctionDeclarator") return;
    
    // Look for ParameterList in the FunctionDeclarator
    for (size_t i = 0; i < func_declarator->children.size(); i++) {
        ASTNode* child = func_declarator->children[i];
        if (!child) continue;
        
        if (child->name == "ParameterList") {
            // Process parameters
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* param_node = child->children[j];
                if (!param_node || param_node->name != "ParameterDeclaration") continue;
                
                std::string param_type = "int";
                
                // Extract parameter type from DeclarationSpecifiers
                for (size_t k = 0; k < param_node->children.size(); k++) {
                    ASTNode* param_child = param_node->children[k];
                    if (!param_child) continue;
                    
                    if (param_child->name == "DeclarationSpecifiers") {
                        param_type = extract_base_type(param_child);
                        break;
                    }
                }
                
                // Create parameter symbol
                Symbol* param_sym = new Symbol("", "parameter", param_type,
                                              func_ptr_sym->scope_level, 0);
                func_ptr_sym->add_parameter(param_sym);

            }
            break;
        }
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
	        else if (child->name == "DeclarationSpecifiers") {

            std::string result = extract_base_type(child);  // Recursive call
            if (result != "int") {
                return result;
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
        else if (child->name == "EnumSpecifier") {  // ← ADDED THIS CASE
            // Extract enum type and name
            std::string type_name = "anonymous";
            
            for (size_t j = 0; j < child->children.size(); j++) {
                ASTNode* enum_child = child->children[j];
                if (!enum_child) continue;
                
                if ((enum_child->name == "Identifier" || enum_child->name == "IDENTIFIER") && 
                    !enum_child->lexeme.empty() && enum_child->lexeme != "default") {
                    type_name = enum_child->lexeme;
                    break;
                }
            }
            
            return "enum " + type_name;
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
           
        } else {
            reportError("Symbol '" + func_name + "' already declared as different kind", node);
        }
    } else {
        // Create new function symbol
        Symbol* func_sym = new Symbol(func_name, "function", return_type,
                                     symbol_table->get_current_scope_level(), node->line_number);
        
        // Process parameters for type information and store them in function symbol
        for (size_t i = 0; i < node->children.size(); i++) {
            ASTNode* child = node->children[i];
            if (!child) continue;
            
            if (child->name == "InitDeclaratorList") {
                // Find the declarator with parameters
                for (size_t j = 0; j < child->children.size(); j++) {
                    ASTNode* init_decl = child->children[j];
                    if (!init_decl) continue;
                    
                    for (size_t k = 0; k < init_decl->children.size(); k++) {
                        ASTNode* decl = init_decl->children[k];
                        if (!decl) continue;
                        
                        // Extract parameters WITHOUT adding to symbol table (just for function signature)
                        extract_function_parameters_for_declaration(decl, func_sym);
                    }
                }
            }
        }
        
        // Add to symbol table
        if (!symbol_table->add_symbol(func_sym)) {
            reportError("Failed to add function declaration '" + func_name + "'", node);
            delete func_sym;
        } 
    }
}

void SemanticAnalyzer::extract_function_parameters_for_declaration(ASTNode* declarator, Symbol* func_sym) {
    if (!declarator || !func_sym) return;
    
    // Navigate through declarator to find ParameterList
    if (declarator->name == "Declarator" || declarator->name == "DirectDeclarator" ||
        declarator->name == "FunctionDeclarator") {
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "ParameterList") {
                // Process each parameter and add to function symbol
                for (size_t j = 0; j < child->children.size(); j++) {
                    ASTNode* param = child->children[j];
                    if (!param || param->name != "ParameterDeclaration") continue;
                    
                    std::string param_type = "int";
                    std::string param_name = "";
                    
                    // Extract parameter type
                    for (size_t k = 0; k < param->children.size(); k++) {
                        ASTNode* param_child = param->children[k];
                        if (!param_child) continue;
                        
                        if (param_child->name == "DeclarationSpecifiers") {
                            param_type = extract_base_type(param_child);
                        }
                        else if (param_child->name == "Declarator" || 
                                 param_child->name == "DirectDeclarator" ||
                                 param_child->name == "AbstractDeclarator") {
                            param_name = extract_declarator_name(param_child);
                            
                            // Extract pointer info
                            Symbol temp_sym(param_name.empty() ? "param" : param_name, 
                                          "parameter", param_type, 0, 0);
                            extract_type_info(param_child, &temp_sym);
                            param_type = temp_sym.get_full_type();
                        }
                    }
                    
                    // Add parameter to function symbol
                    Symbol* param_sym = new Symbol(param_name.empty() ? "param" : param_name, 
                                                   "parameter", param_type, 0, 0);
                    func_sym->add_parameter(param_sym);
                }
                // Don't recurse into ParameterList children - we already processed them above
            }
            else {
                // Recursively search in children
                extract_function_parameters_for_declaration(child, func_sym);
            }
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
    
    if (declarator->name == "ReferenceDeclarator") {
        symbol->is_reference = true;

        
        // Process pointer if present (reference to pointer)
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "Pointer") {
                extract_pointer_info(child, symbol);
            } else if (child->name == "DirectDeclarator" || child->name == "ArrayDeclarator") {
                extract_type_info(child, symbol);
            }
        }
        return;
    }
    
    if (declarator->name == "Declarator") {
        extract_pointer_info(declarator, symbol);
        
        if (declarator->parent && declarator->parent->name == "FunctionDeclarator") {

            symbol->is_function_pointer = true;
            symbol->return_type = symbol->base_type;
        }
        
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
    // Handle FunctionDeclarator (for function pointers AND regular functions)
    else if (declarator->name == "FunctionDeclarator") {
        
        // Check if this FunctionDeclarator contains a Declarator with Pointer (function pointer)
        bool has_pointer_declarator = false;
        for (size_t i = 0; i < declarator->children.size(); i++) {
            ASTNode* child = declarator->children[i];
            if (!child) continue;
            
            if (child->name == "Declarator") {
                // This is a function pointer: int (*func_ptr)(int, int)
                has_pointer_declarator = true;
                extract_type_info(child, symbol); // Process the inner Declarator
                break;
            }
        }
        
        if (!has_pointer_declarator) {
            // This is a regular function declaration: int add(int, int)
            symbol->symbol_type = "function";
            
            // Extract parameters for the function
            extract_function_pointer_parameters(declarator, symbol);
        } 
    }
    // Handle DirectDeclarator
    else if (declarator->name == "DirectDeclarator") {
        // Just extract the name if needed
        std::string name = extract_declarator_name(declarator);
        if (name != "unknown" && symbol->name == "unknown") {
            symbol->name = name;
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
                
                //  VALIDATE EACH DIMENSION
                if (dimension <= 0) {
                    if (dimension == 0) {
                        reportError("Zero-length array dimension for '" + symbol->name + "'", child);
                    } else {
                        reportError("Negative array dimension '" + child->lexeme + "' for '" + symbol->name + "'", child);
                    }
                    dimension = 1; // Use safe default
                }
                
                symbol->array_dimensions.push_back(dimension);
            } catch (const std::exception& e) {
                // If not a number, treat as incomplete array
                symbol->array_dimensions.push_back(-1);
            }
        }
    }
    
    // If no Constant found, it's an incomplete array
    if (symbol->array_dimensions.empty()) {
        symbol->array_dimensions.push_back(-1);
    }


    
    // Reverse dimensions because they're stored outermost first in AST
    std::reverse(symbol->array_dimensions.begin(), symbol->array_dimensions.end());
}
void SemanticAnalyzer::check_member_access(ASTNode* node) {
    if (!node || node->name != "MemberAccess") return;
    if (node->children.size() < 2) return;
    
    ASTNode* struct_node = node->children[0];
    ASTNode* member_node = node->children[1];
    
    if (!struct_node || !member_node) return;
    
    // Get the struct type using existing type system
    std::string struct_type = get_expression_type(struct_node);
    

    
    // RESOLVE TYPEDEF to get the actual struct type
    std::string resolved_type = resolve_typedef(struct_type);
    
    
    // FIX: Handle pointer types for -> operator
    std::string operator_used = node->lexeme; // Should be "." or "->"
    
    if (is_pointer_type(resolved_type)) {
        // It's a pointer - check which operator is used
        if (operator_used == ".") {
            reportError("Member access on pointer type '" + struct_type + 
                       "' requires '->' operator, not '.'", node);
            return;
        }
        // For -> operator, dereference the pointer
        // Remove the trailing '*' to get the base type
        size_t last_star = resolved_type.rfind('*');
        if (last_star != std::string::npos) {
            resolved_type = resolved_type.substr(0, last_star);
        }

    } else {
        // It's not a pointer - check which operator is used
        if (operator_used == "->") {
            reportError("'->' operator can only be used on pointer types, not '" + 
                       struct_type + "'. Did you mean '.'?", node);
            return;
        }
    }
    
    // Check if it's actually a struct/union type
    if (!is_struct_union_type(resolved_type)) {
        // ADDITIONAL CHECK: Maybe it's a direct struct name without "struct " prefix
        Symbol* type_sym = symbol_table->find_symbol(struct_type);
        
        if (!type_sym || (type_sym->symbol_type != "struct" && 
                          type_sym->symbol_type != "union")) {
            reportError("Member access on non-struct/union type '" + struct_type + "'", node);
            return;
        }
        
        // Found it as a struct/union symbol
        std::string member_name = member_node->lexeme;
        bool member_found = false;
        
        for (auto member : type_sym->members) {
            if (member->name == member_name) {
                member_found = true;
                break;
            }
        }
        
        if (!member_found) {
            reportError("Struct/union '" + struct_type + "' has no member '" + member_name + "'", node);
        }        
        return;
    }
    
    // Extract struct name from "struct Name" or "union Name"
    std::string struct_name = resolved_type.substr(resolved_type.find(' ') + 1);
    
    // Find the struct type definition
    Symbol* struct_sym = symbol_table->find_symbol(struct_name);
    if (!struct_sym) {
        reportError("Unknown struct/union type '" + resolved_type + "'", node);
        return;
    }
    
    if (!struct_sym->is_complete) {
        reportError("Incomplete struct/union type '" + resolved_type + "'", node);
        return;
    }
    
    // Check if member exists
    std::string member_name = member_node->lexeme;
    bool member_found = false;
    for (auto member : struct_sym->members) {
        if (member->name == member_name) {
            member_found = true;
            break;
        }
    }
    
    if (!member_found) {
        reportError("Struct/union '" + resolved_type + "' has no member '" + member_name + "'", node);
    }
}

bool SemanticAnalyzer::has_initializer(ASTNode* init_declarator) {
    if (!init_declarator || init_declarator->name != "InitDeclarator") return false;
    return init_declarator->children.size() > 1; // Has initializer if >1 child
}

void SemanticAnalyzer::check_initialization(ASTNode* init_declarator, const std::string& declared_type) {
    if (!init_declarator || init_declarator->children.size() < 2) return;

    std::string var_name = extract_declarator_name(init_declarator->children[0]);
    Symbol* var_sym = symbol_table->find_symbol(var_name);
    
    // References MUST be initialized


    ASTNode* initializer = init_declarator->children[1];
    if (!initializer) return;

    ASTNode* init_expr = nullptr;
    if (initializer->name == "Initializer" && initializer->children.size() > 0) {
        init_expr = initializer->children[0];
    } else {
        init_expr = initializer;
    }
    
    if (!init_expr) return;
    if (var_sym && var_sym->is_reference) {
        // Reference found - initialization is required

    if (init_expr->name == "UnaryExpression" && init_expr->lexeme == "*") {
        report_warning("Reference bound to dereferenced pointer - may be NULL", init_declarator);
    }
    }

        if (declared_type.find('&') != std::string::npos && init_expr->name == "Constant") {
            reportError("Cannot bind non-const lvalue reference to rvalue", init_declarator);
            return;
        }

    if (init_expr->name == "StringLiteral") {
        Symbol* var_sym = symbol_table->find_symbol(var_name);
        if (var_sym && var_sym->is_array && var_sym->base_type == "char") {
            // char array initialized with string literal - always valid
            return;
        }
    }


    std::string init_type = get_expression_type(init_expr);
    std::string resolved_declared = resolve_typedef(declared_type);
    if (var_sym && var_sym->is_array) {

        
        if (init_type.find("initializer_list") != std::string::npos) {
            // Array initialized with list - this is valid
            return;
        }
    }
    
    
    if (init_type == "unknown" || declared_type == "unknown") return;

    // Special cases that are always valid
    if (init_type == "initializer_list" && 
        (resolved_declared.find("struct ") == 0 || resolved_declared.find("union ") == 0)) {
        return; // Struct initializer
    }

    // MAIN CHECK: Use the same logic as assignment
    if (!types_compatible(declared_type, init_type)) {
        reportError("Incompatible types in initialization: cannot convert '" + 
                   init_type + "' to '" + declared_type + "'", init_declarator);
    }
    // Only warn for numeric conversions
    else if (declared_type != init_type && 
             is_numeric_type(resolved_declared) && 
             is_numeric_type(init_type)) {
        report_warning("Implicit type conversion in initialization: '" + 
                      init_type + "' to '" + declared_type + "'", init_declarator);
    }
}

void SemanticAnalyzer::check_assignment(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string lhs_type = get_expression_type(node->children[0]);
    std::string rhs_type = get_expression_type(node->children[1]);
    
    if (lhs_type == "unknown" || rhs_type == "unknown") return;

    
    // Check pointer level compatibility
    int lhs_ptr_level = get_pointer_level(lhs_type);
    int rhs_ptr_level = get_pointer_level(rhs_type);

    if (lhs_type.find('(') != std::string::npos && rhs_type.find('(') != std::string::npos) {
        return; // Allow all function pointer assignments for now
    }
    
    if (lhs_ptr_level != rhs_ptr_level) {
        bool is_address_of = false;
        if (node->children[1]->name == "UnaryExpression" && 
            node->children[1]->lexeme == "&") {
            is_address_of = true;
        }
        
        if (!is_address_of) {
            reportError("Pointer level mismatch in assignment: cannot assign '" + 
                        rhs_type + "' to '" + lhs_type + "'", node);
            return;
        }
    }


    if (is_struct_union_type(lhs_type) && is_struct_union_type(rhs_type)) {
        if (lhs_type != rhs_type) {
            reportError("Incompatible struct/union types in assignment", node);
        }
        return;
    }
    
    // Check type compatibility
    if (!types_compatible(lhs_type, rhs_type)) {
        reportError("Incompatible types in assignment: cannot assign '" + 
                   rhs_type + "' to '" + lhs_type + "'", node);
        return;
    }
    
    // Only warn for implicit conversions between compatible numeric types
    if (lhs_type != rhs_type && is_numeric_type(lhs_type) && is_numeric_type(rhs_type)) {
        report_warning("Implicit type conversion in assignment: '" + 
                      rhs_type + "' to '" + lhs_type + "'", node);
    }
    
    // Mark LHS as initialized after assignment
    if (node->children[0]->name == "Identifier") {
        std::string var_name = node->children[0]->lexeme;
        Symbol* sym = symbol_table->find_symbol(var_name);
        if (sym) sym->is_initialized = true;
    }
    // Also mark arrays as initialized when assigning to array elements
    else if (node->children[0]->name == "ArraySubscript") {
        ASTNode* array_node = node->children[0];
        // Find the base array identifier
        while (array_node && array_node->name == "ArraySubscript") {
            if (array_node->children.size() > 0) {
                array_node = array_node->children[0];
            } else {
                break;
            }
        }
        if (array_node && array_node->name == "Identifier") {
            std::string var_name = array_node->lexeme;
            Symbol* sym = symbol_table->find_symbol(var_name);
            if (sym) sym->is_initialized = true;
        }
    }
}


void SemanticAnalyzer::check_function_call(ASTNode* node) {
    if (!node || node->children.empty()) return;
    
    ASTNode* func_id = node->children[0];
    if (!func_id || func_id->name != "Identifier") return;
    
    std::string func_name = func_id->lexeme;
    Symbol* func_sym = symbol_table->find_symbol(func_name);

    if (func_sym && func_sym->is_function_pointer) {
        return; // Allow function pointer calls
    }

    if (func_sym && func_sym->symbol_type == "function" && 
        func_sym->get_full_type().find("(*)") != std::string::npos) {
        return;
    }

    if (!func_sym && builtin_functions.find(func_name) == builtin_functions.end()) {
        reportError("Undeclared function '" + func_name + "'", node);
    }
    
    if (func_sym && func_sym->symbol_type != "function") {
        reportError("'" + func_name + "' is not a function", node);
        return;
    }
    if (func_sym && func_sym->symbol_type == "function") {
        // Extract arguments from ArgumentList
        std::vector<std::string> arg_types;
        if (node->children.size() > 1) {
            ASTNode* arg_list = node->children[1];
            if (arg_list && arg_list->name == "ArgumentList") {
                for (auto arg : arg_list->children) {
                    arg_types.push_back(get_expression_type(arg));
                }
            }
        }
        
        // Check parameter count
        if (arg_types.size() != func_sym->parameters.size()) {
            reportError("Function '" + func_name + "' expects " + 
                       std::to_string(func_sym->parameters.size()) + " arguments, got " +
                       std::to_string(arg_types.size()), node);
            return;
        }
        
        // Check each argument type
        for (size_t i = 0; i < arg_types.size(); i++) {
            std::string param_type = func_sym->parameters[i]->get_full_type();
            std::string arg_type = arg_types[i];
            
            if (!types_compatible(param_type, arg_type)) {
                reportError("Argument " + std::to_string(i + 1) + " type mismatch: expected '" +
                           param_type + "', got '" + arg_type + "'", node);
            }
        }
    }
    
    // Recursion detection
    if (!current_function_name.empty() && func_sym) {
        if (func_name == current_function_name) {
            func_sym->is_recursive = true;        }
        
        if (func_sym->in_call_chain) {
            func_sym->is_recursive = true;

        }
    }
}

void SemanticAnalyzer::check_return_statement(ASTNode* node) {
    if (current_function_name.empty()) {
        reportError("Return statement outside function", node);
        return;
    }
    
    
    // Mark function as having return statement
    Symbol* func_sym = symbol_table->find_symbol(current_function_name);
    if (func_sym) {
        func_sym->has_return_statement = true;
    }
    
    bool has_value = (node->children.size() > 0);
    
    if (current_function_return_type == "void") {
        if (has_value) {
            reportError("Void function '" + current_function_name + 
                       "' should not return a value", node);
        }
    } else {
        if (!has_value) {
            report_warning("Non-void function '" + current_function_name + 
                          "' should return a value", node);
        } else {
            std::string return_type = get_expression_type(node->children[0]);

            if (current_function_return_type.find('&') != std::string::npos) {
                // Function returns a reference - check what we're returning
                ASTNode* return_expr = node->children[0];
                if (return_expr->name == "Identifier") {
                    std::string var_name = return_expr->lexeme;
                    Symbol* var_sym = symbol_table->find_symbol(var_name);
                    
                    if (var_sym && var_sym->scope_level > func_sym->scope_level) {
                        // Returning reference to variable in inner scope (local)
                        reportError("Returning reference to local variable '" + var_name + 
                                   "' which will be destroyed", node);
                    }
                }
            }

            std::string expected_type = current_function_return_type;
            if (expected_type.find('&') != std::string::npos) {
                // For reference returns, remove the '&' for type comparison
                expected_type = expected_type.substr(0, expected_type.find('&'));
            }
            
            if (!types_compatible(current_function_return_type, return_type)) {
                report_warning("Return type mismatch: expected '" + 
                              current_function_return_type + "', got '" + return_type + "'", node);
            }
        }
    }
}

void SemanticAnalyzer::detect_recursion(const std::string& caller, const std::string& callee) {
    Symbol* caller_sym = symbol_table->find_symbol(caller);
    Symbol* callee_sym = symbol_table->find_symbol(callee);
    
    if (caller_sym && callee_sym) {
        if (caller == callee) {
            caller_sym->is_recursive = true;
        } else if (callee_sym->in_call_chain) {
            caller_sym->is_recursive = true;
            callee_sym->is_recursive = true;
        }
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
            if (is_pointer_type(left_type) && is_pointer_type(right_type)) {
                if (node->lexeme != "-") {
                    reportError("Invalid pointer arithmetic: can only subtract pointers", node);
                }
            else if (is_pointer_type(left_type) && !is_integer_type(right_type)) {
                reportError("Pointer arithmetic requires integer operand, got '" + right_type + "'", node);
            }
            else if (is_pointer_type(right_type) && !is_integer_type(left_type)) {
                reportError("Pointer arithmetic requires integer operand, got '" + left_type + "'", node);
            }
            }
        } else {
            reportError("Invalid operation on pointer type", node);
        }
    }
}

void SemanticAnalyzer::check_unary_operation(ASTNode* node) {
    if (!node || node->children.empty()) return;

    std::string operand_type = get_expression_type(node->children[0]);
    std::string op = node->lexeme;

    if (op == "*") {
        // Resolve typedef before checking if it's a pointer
        std::string resolved_type = resolve_typedef(operand_type);
        if (!is_pointer_type(resolved_type)) {
            reportError("Cannot dereference non-pointer type '" + operand_type + "'", node);
        }
    } else if (op == "&") {
        if (node->children[0]->name != "Identifier" && 
            node->children[0]->name != "ArraySubscript" &&
            node->children[0]->name != "MemberAccess") {
            reportError("Operand of '&' must be an lvalue", node);
        }
    } else if (op == "++" || op == "--") {
        if (!is_numeric_type(operand_type) && !is_pointer_type(operand_type)) {
            reportError("Increment/decrement requires numeric or pointer type", node);
        }
        // Mark variable as initialized after increment/decrement
        if (node->children[0]->name == "Identifier") {
            std::string var_name = node->children[0]->lexeme;
            Symbol* sym = symbol_table->find_symbol(var_name);
            if (sym) {
                sym->is_initialized = true;
            }
        }
    }
}

void SemanticAnalyzer::check_division_by_zero(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    ASTNode* divisor = node->children[1];
    if (divisor->name == "Constant" && divisor->lexeme == "0") {
        reportError("Division by zero", node);
    }
}

void SemanticAnalyzer::check_modulo_operation(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    std::string left_type = get_expression_type(node->children[0]);
    std::string right_type = get_expression_type(node->children[1]);
    
    if (!is_integer_type(left_type) || !is_integer_type(right_type)) {
        reportError("Modulo operation requires integer operands", node);
    }
    
    ASTNode* divisor = node->children[1];
    if (divisor->name == "Constant" && divisor->lexeme == "0") {
        reportError("Modulo by zero", node);
    }
}

void SemanticAnalyzer::check_goto_statement(ASTNode* node) {
    if (!node || node->lexeme.empty()) return;
    used_labels[node->lexeme] = true;
}

void SemanticAnalyzer::check_label_statement(ASTNode* node) {
    if (!node || node->lexeme.empty()) return;
    
    if (declared_labels.find(node->lexeme) != declared_labels.end()) {
        reportError("Duplicate label '" + node->lexeme + "'", node);
    } else {
        declared_labels[node->lexeme] = true;
    }
}

// Add these missing methods at the end of your semantic.cpp file:

std::string SemanticAnalyzer::get_expression_type(ASTNode* expr) {
    if (!expr) return "unknown";

    // Identifier - use symbol's full type
    if (expr->name == "Identifier") {
        Symbol* sym = symbol_table->find_symbol(expr->lexeme);

        if (sym) {
            // ENUM CONSTANT FIX: Return specific enum type instead of just "int"
            if (sym->symbol_type == "enum_constant" && !sym->enum_type.empty()) {
                return "enum " + sym->enum_type;  // "enum Color", not "int"
            }
        // For arrays, return the full array type with dimensions
        // This allows ArraySubscript handling to properly strip dimensions
        // e.g., "int[2][3]" subscripted becomes "int[3]", then "int"
        if (sym->is_array) {
            return sym->get_full_type();  // Returns "int[2][3]" format
        }

            if (sym->symbol_type == "function") {

                // Build function pointer type: return_type(*)()
                std::string func_ptr_type = sym->base_type + "(*)";
                
                // Add parameters
                if (!sym->parameters.empty()) {
                    func_ptr_type += "(";
                    for (size_t i = 0; i < sym->parameters.size(); i++) {
                        if (i > 0) func_ptr_type += ", ";
                        func_ptr_type += sym->parameters[i]->base_type;
                        // Add pointer levels
                        for (int j = 0; j < sym->parameters[i]->pointer_level; j++) {
                            func_ptr_type += "*";
                        }
                    }
                    func_ptr_type += ")";
                } else {
                    func_ptr_type += "()";
                }
                
                return func_ptr_type;
            }

        if (sym->is_reference) {
            std::string type = sym->base_type;
            for (int i = 0; i < sym->pointer_level; i++) {
                type += "*";
            }
            return type;
        }
            return sym->get_full_type();
        }
        return "unknown";
    }

    // Constants
    if (expr->name == "Constant") {
        std::string value = expr->lexeme;
        
        if (value.find('.') != std::string::npos) {
            if (value.back() == 'f' || value.back() == 'F') {
                return "float";
            }
            return "double";  // Default for decimal numbers
        }
        if (value == "true" || value == "false") {
            return "bool";
        }
        return "int";  // Default for integer constants
    }
    if (expr->name == "InitializerList") {
        if (expr->children.empty()) return "initializer_list";
        
        // Get type of first element to determine list type
        std::string first_type = get_expression_type(expr->children[0]);
        return "initializer_list<" + first_type + ">";
    }

    // ADD BRACED INIT LIST HANDLING  
    if (expr->name == "Initializer" && expr->children.size() > 0) {
        return get_expression_type(expr->children[0]);
    }
    // Handle ArraySubscript
    if (expr->name == "ArraySubscript" && expr->children.size() >= 2) {
        std::string array_type = get_expression_type(expr->children[0]);
        
        // If array decays to pointer, get the base type
        if (is_pointer_type(array_type)) {
            // Remove one level of pointer to get element type
            size_t last_star = array_type.rfind('*');
            if (last_star != std::string::npos) {
                std::string element_type = array_type.substr(0, last_star);
                return element_type;
            }
        }
        
        // Handle direct array types like "int[3]" or "int[2][3]"
        if (array_type.find('[') != std::string::npos) {
            // Find the first bracket
            size_t first_bracket = array_type.find('[');
            // Find the matching closing bracket
            size_t closing_bracket = array_type.find(']', first_bracket);
            
            if (closing_bracket != std::string::npos) {
                // Extract base type before brackets
                std::string base_type = array_type.substr(0, first_bracket);
                
                // Check if there are more dimensions after this one
                if (closing_bracket + 1 < array_type.length() && array_type[closing_bracket + 1] == '[') {
                    // Multi-dimensional: remove first dimension, keep the rest
                    // e.g., "int[2][3]" becomes "int[3]"
                    std::string remaining_dims = array_type.substr(closing_bracket + 1);
                    return base_type + remaining_dims;
                } else {
                    // Single dimension remaining: just return base type
                    // e.g., "int[3]" becomes "int"
                    return base_type;
                }
            }
        }
        
        return "unknown";
    }


// Handle member access
if (expr->name == "MemberAccess" && expr->children.size() >= 2) {
    std::string struct_type = get_expression_type(expr->children[0]);
    std::string member_name = expr->children[1]->lexeme;
    std::string operator_used = expr->lexeme;  // "." or "->"
    
    // Resolve typedef
    std::string resolved_type = resolve_typedef(struct_type);
    
    // If using -> operator, dereference the pointer type
    if (operator_used == "->" && is_pointer_type(resolved_type)) {
        // Remove trailing '*' to get the base type
        size_t last_star = resolved_type.rfind('*');
        if (last_star != std::string::npos) {
            resolved_type = resolved_type.substr(0, last_star);
            // Trim any trailing whitespace
            while (!resolved_type.empty() && resolved_type.back() == ' ') {
                resolved_type.pop_back();
            }
        }
    }
    
    // Try to find the struct symbol
    Symbol* struct_sym = nullptr;
    
    if (is_struct_union_type(resolved_type)) {
        // Extract struct name from "struct Name"
        std::string struct_name = resolved_type.substr(resolved_type.find(' ') + 1);
        struct_sym = symbol_table->find_symbol(struct_name);
    } else {
        // Direct struct name (typedef'd or already resolved)
        struct_sym = symbol_table->find_symbol(resolved_type);
        if (!struct_sym) {
            // Try with "struct " prefix
            struct_sym = symbol_table->find_symbol("struct " + resolved_type);
        }
    }
    
    if (struct_sym) {
        // Find the member and return its type
        for (auto member : struct_sym->members) {
            if (member->name == member_name) {
                return member->get_full_type();
            }
        }
    }
    
    return "unknown";
}

    // String literals
    if (expr->name == "StringLiteral") {
        return "char*";
    }

    // Unary operations
    if (expr->name == "UnaryExpression" && !expr->children.empty()) {
        std::string operand_type = get_expression_type(expr->children[0]);
        std::string op = expr->lexeme;

        if (op == "*") {
            // Dereference pointer
            if (is_pointer_type(operand_type)) {
                size_t star_pos = operand_type.rfind('*');
                return operand_type.substr(0, star_pos);
            }
        } else if (op == "&") {
            // Address-of: resolve typedef first to get the actual type
            std::string resolved_type = resolve_typedef(operand_type);
            return resolved_type + "*";
        }
        return operand_type;
    }

    // Binary operations
    if (!expr->children.empty()) {
        std::string left_type = get_expression_type(expr->children[0]);
        std::string right_type = expr->children.size() > 1 ? get_expression_type(expr->children[1]) : "unknown";

        if (expr->name == "AdditiveExpression" || expr->name == "MultiplicativeExpression") {
            // Handle pointer arithmetic: ptr + int = ptr, ptr - int = ptr
            if (expr->name == "AdditiveExpression") {
                bool left_is_pointer = is_pointer_type(left_type);
                bool right_is_pointer = is_pointer_type(right_type);
                
                if (left_is_pointer && !right_is_pointer) {
                    // ptr + int or ptr - int = ptr
                    return left_type;
                } else if (!left_is_pointer && right_is_pointer) {
                    // int + ptr = ptr (only for addition)
                    if (expr->lexeme == "+") {
                        return right_type;
                    }
                } else if (left_is_pointer && right_is_pointer) {
                    // ptr - ptr = int (ptrdiff_t)
                    if (expr->lexeme == "-") {
                        return "int";
                    }
                }
            }
            
            // Regular arithmetic
            if (left_type == "float" || right_type == "float") return "float";
            if (left_type == "double" || right_type == "double") return "double";
            return "int";
        }

        if (expr->name == "RelationalExpression" || expr->name == "EqualityExpression" ||
            expr->name == "LogicalAndExpression" || expr->name == "LogicalOrExpression") {
            return "bool";
        }
    }

    // Function call
    if (expr->name == "FunctionCall" && !expr->children.empty()) {
        Symbol* func_sym = symbol_table->find_symbol(expr->children[0]->lexeme);
        if (func_sym) return func_sym->base_type; // Return type
    }

    return "unknown";
}

bool SemanticAnalyzer::types_compatible(const std::string& type1, const std::string& type2) {
    if (type1 == type2) return true;
    
    
    // RESOLVE TYPEDEFS
    std::string resolved_type1 = resolve_typedef(type1);
    std::string resolved_type2 = resolve_typedef(type2);
    
    if (resolved_type1 == resolved_type2) return true;
   
    

    if (is_struct_union_type(type1) && is_struct_union_type(type2)) {
        return type1 == type2; // Only same exact types are compatible
    }

    std::string base_type1 = resolved_type1;
    std::string base_type2 = resolved_type2;
    
    if (base_type1.find('&') != std::string::npos) {
        base_type1 = base_type1.substr(0, base_type1.find('&'));
    }
    if (base_type2.find('&') != std::string::npos) {
        base_type2 = base_type2.substr(0, base_type2.find('&'));
    }
    
    // After stripping references, check if base types match
    if (base_type1 == base_type2) return true;


// FUNCTION TO FUNCTION POINTER COMPATIBILITY (FIX)
if ((resolved_type1.find("(*)") != std::string::npos && 
     resolved_type2.find('(') != std::string::npos) ||
    (resolved_type2.find("(*)") != std::string::npos && 
     resolved_type1.find('(') != std::string::npos)) {
    return true; // Allow all function to function pointer assignments
}

    if (resolved_type1.find("enum ") == 0 && resolved_type2.find("enum ") == 0) {
        // Extract enum names and compare
        std::string enum1_name = resolved_type1.substr(5); // Remove "enum "
        std::string enum2_name = resolved_type2.substr(5); // Remove "enum "
        if (enum1_name == enum2_name) return true;
	else return false;
    }

    // ADD ENUM COMPATIBILITY - enum types are compatible with int and their own enum constants
    if ((resolved_type1.find("enum ") == 0 && is_integer_type(resolved_type2)) ||
        (resolved_type2.find("enum ") == 0 && is_integer_type(resolved_type1))) {
        return true; // enum and int are compatible
    }
    
    // Check if both are the same enum type (even if one is resolved and one isn't)

    
    // POINTER COMPATIBILITY CHECK
    if (is_pointer_type(resolved_type1) && is_pointer_type(resolved_type2)) {
        // void* is compatible with any pointer
        if (resolved_type1 == "void*" || resolved_type2 == "void*") {
            return true;
        }
        
        // Strip trailing '*' to get base types
        std::string base1 = resolved_type1;
        std::string base2 = resolved_type2;
        
        while (!base1.empty() && base1.back() == '*') {
            base1.pop_back();
        }
        while (!base2.empty() && base2.back() == '*') {
            base2.pop_back();
        }
        
        // Trim trailing whitespace
        while (!base1.empty() && base1.back() == ' ') {
            base1.pop_back();
        }
        while (!base2.empty() && base2.back() == ' ') {
            base2.pop_back();
        }
        
        // Check if base types are the same
        if (base1 == base2) {
            return true; // Same pointer types (e.g., struct Point* and struct Point*)
        }
        
        // Different pointer types are incompatible
        return false;
    }
    
    // Handle numeric conversions
    if (is_numeric_type(resolved_type1) && is_numeric_type(resolved_type2)) {
        return true;
    }
    
    // Handle integer to bool
    if ((resolved_type1 == "bool" && is_integer_type(resolved_type2)) || 
        (resolved_type2 == "bool" && is_integer_type(resolved_type1))) {
        return true;
    }
    
    return false;
}
bool SemanticAnalyzer::is_struct_union_type(const std::string& type) {
    return type.find("struct ") == 0 || type.find("union ") == 0;
}

std::string SemanticAnalyzer::resolve_typedef(const std::string& type_name) {
    // If it's not a simple identifier, return as-is
    if (type_name.empty() ||
        type_name.find(' ') != std::string::npos || 
        type_name.find('*') != std::string::npos ||
        type_name.find('(') != std::string::npos ||
        type_name.find('[') != std::string::npos) {
        return type_name;
    }
    
    // Check if this is a typedef
    Symbol* sym = symbol_table->find_symbol(type_name);
    if (sym && sym->symbol_type == "typedef") {
        // For function pointers, use get_full_type() to preserve the function signature
        if (sym->is_function_pointer) {
            std::string full_type = sym->get_full_type();
            return full_type;
        }
        
        // For pointer typedefs, include the pointer level
        if (sym->is_pointer && sym->pointer_level > 0) {
            std::string result = sym->base_type;
            for (int i = 0; i < sym->pointer_level; i++) {
                result += "*";
            }
            return result;
        }
        
        // For regular typedefs, just return base_type
        return sym->base_type;
    }
    
    return type_name;
}

bool SemanticAnalyzer::is_numeric_type(const std::string& type) {
    std::string base_type = type;
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
    
    // ADD ENUM CHECK
    if (type.find("enum ") == 0) {
        return true; // enum types are integer types
    }
    
    return base_type == "int" || base_type == "long" || base_type == "short" || 
           base_type == "char" || base_type == "unsigned" || base_type == "signed";
}

bool SemanticAnalyzer::is_pointer_type(const std::string& type) {
    return type.find('*') != std::string::npos;
}

int SemanticAnalyzer::get_pointer_level(const std::string& type) {
    return std::count(type.begin(), type.end(), '*');
}

void SemanticAnalyzer::check_array_access(ASTNode* node) {
    if (!node || node->children.size() < 2) return;
    
    // Check if index is integer type
    std::string index_type = get_expression_type(node->children[1]);
    if (!is_integer_type(index_type)) {
        reportError("Array subscript must be integer type, got '" + index_type + "'", node);
    }
    
    // Get array name for dimension checking
    std::string array_name;
    ASTNode* array_node = node->children[0];
    if (array_node->name == "Identifier") {
        array_name = array_node->lexeme;
    }
    
    if (!array_name.empty()) {
        // Count access dimensions
        int access_dims = 1;
        ASTNode* parent = node->parent;
        while (parent && parent->name == "ArraySubscript") {
            access_dims++;
            parent = parent->parent;
        }
        
        // Check both too many AND too few dimensions
        check_array_dimensions(array_name, access_dims, node);
    }
}

void SemanticAnalyzer::check_array_dimensions(const std::string& array_name, int access_dims, ASTNode* node) {
    Symbol* array_sym = symbol_table->find_symbol(array_name);
    if (!array_sym || !array_sym->is_array) return;
    
    int declared_dims = array_sym->array_dimensions.size();
    
    if (access_dims > declared_dims) {
        reportError("Too many array subscripts for '" + array_name + 
                   "': array has " + std::to_string(declared_dims) + 
                   " dimension(s), accessing with " + std::to_string(access_dims), node);
    }
    else if (access_dims < declared_dims) {
        // ADD THIS CHECK FOR TOO FEW SUBSCRIPTS
        reportError("Too few array subscripts for '" + array_name + 
                   "': array has " + std::to_string(declared_dims) + 
                   " dimension(s), accessing with " + std::to_string(access_dims), node);
    }
    if (access_dims == declared_dims && declared_dims > 1) {
        // For multidimensional arrays, validate each subscript
        ASTNode* current = node;
        for (int i = 0; i < access_dims && current; i++) {
            if (current->children.size() > 1) {
                ASTNode* subscript = current->children[1];
                std::string subscript_type = get_expression_type(subscript);
                if (!is_integer_type(subscript_type)) {
                    reportError("Array subscript must be integer type, got '" + subscript_type + "'", subscript);
                }
            }
            // Move to outer array access if nested
            current = (current->children.size() > 0) ? current->children[0] : nullptr;
        }
    }
}
void SemanticAnalyzer::check_pointer_operations(ASTNode* node) {
    // Basic pointer operation validation
    if (!node) return;
    
    // This can be expanded based on specific pointer operations
    // Currently handled in check_unary_operation and check_binary_operation
}

void SemanticAnalyzer::check_break_continue(ASTNode* node) {
    if (loop_depth == 0 && switch_depth == 0) {
        reportError("'" + node->name + "' statement not within loop or switch", node);
    } else if (node->name == "ContinueStatement" && loop_depth == 0) {
        reportError("'continue' statement not within loop", node);
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

void SemanticAnalyzer::check_case_statement(ASTNode* node) {
    if (switch_depth == 0) {
        reportError("'case' statement outside switch", node);
        return;
    }
    
    if (node->children.size() > 0) {
        ASTNode* case_expr = node->children[0];
        if (case_expr->name == "Constant") {
            std::string case_value = case_expr->lexeme;
            if (case_values_in_switch.find(case_value) != case_values_in_switch.end()) {
                reportError("Duplicate case value '" + case_value + "' in switch", node);
            } else {
                case_values_in_switch.insert(case_value);
            }
        }
    }
}

void SemanticAnalyzer::check_loop_condition(ASTNode* node) {
    if (!node) return;

    if (node->name == "AssignmentExpression") {
        report_warning("Assignment in loop condition - did you mean '=='?", node);
    }
    for (auto child : node->children) {
        check_loop_condition(child); // Recursive call
    }
    std::string cond_type = get_expression_type(node);
    if (cond_type != "unknown" && !is_numeric_type(cond_type) && cond_type != "bool") {
        report_warning("Loop condition should be boolean or numeric type", node);
    }
}

void SemanticAnalyzer::check_if_condition(ASTNode* node) {
    if (!node) return;
    if (node->name == "AssignmentExpression") {
        report_warning("Assignment in if condition - did you mean '=='?", node);
    }
    std::string cond_type = get_expression_type(node);
    if (cond_type != "unknown" && !is_numeric_type(cond_type) && cond_type != "bool") {
        report_warning("Condition should be boolean or numeric type", node);
    }
}

void SemanticAnalyzer::process_class(ASTNode* node) {
    if (!node || !symbol_table) return;
    
    std::string class_name = "anonymous";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (child->name == "Identifier" && !child->lexeme.empty()) {
            class_name = child->lexeme;
            break;
        }
    }
    
    
    Symbol* class_sym = new Symbol(class_name, "class", "class", 
                                   symbol_table->get_current_scope_level(), 0);
    symbol_table->add_symbol(class_sym);
    
    // Process class members
    symbol_table->enter_scope();
    
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (child && child->name == "ClassDeclarationList") {
            for (size_t j = 0; j < child->children.size(); j++) {
                traverse(child->children[j]);
            }
        }
    }
    
    symbol_table->exit_scope();
}

void SemanticAnalyzer::check_declaration_initialization(ASTNode* declaration) {
    if (!declaration) return;
    
    for (size_t i = 0; i < declaration->children.size(); i++) {
        ASTNode* child = declaration->children[i];
        if (!child || child->name != "InitDeclaratorList") continue;
        
        for (size_t j = 0; j < child->children.size(); j++) {
            ASTNode* init_decl = child->children[j];
            if (!init_decl || init_decl->name != "InitDeclarator") continue;
            
            // Get variable name
            std::string var_name = extract_declarator_name(init_decl);
            if (var_name == "unknown") continue;
            
            // Use symbol table as source of truth for the type
            Symbol* sym = symbol_table->find_symbol(var_name);
            if (!sym) continue;
            
            check_initialization(init_decl, sym->get_full_type());
        }
    }
}

// Fix the report_warning method
void SemanticAnalyzer::report_warning(const std::string& message, ASTNode* node) {
    warning_count++;  // Make sure you have this member variable
    
    if (node && node->line_number > 0) {
        std::cout << "Line " << node->line_number << ": WARNING: " << message << std::endl;
    } else {
        std::cout << "WARNING: " << message << std::endl;
    }
}



// ============================================
// ADDITIONAL SEMANTIC CHECKS FOR FUNCTION POINTERS
// ============================================

void SemanticAnalyzer::check_function_pointer_assignment(ASTNode* node) {
    if (!node || node->name != "AssignmentExpression" || node->children.size() < 2) return;
    
    ASTNode* lhs = node->children[0];
    
    if (lhs->name == "Identifier") {
        Symbol* lhs_sym = symbol_table->find_symbol(lhs->lexeme);
        
        if (lhs_sym && lhs_sym->is_function_pointer) {
            // Mark as initialized
            lhs_sym->is_initialized = true;
        }
    }
}

// 3. Simple function pointer call check
void SemanticAnalyzer::check_function_pointer_call(ASTNode* node) {
    if (!node || node->name != "FunctionCall" || node->children.empty()) return;
    
    ASTNode* func_node = node->children[0];
    if (func_node->name == "Identifier") {
        Symbol* sym = symbol_table->find_symbol(func_node->lexeme);
        if (sym && sym->is_function_pointer && !sym->is_initialized) {
            report_warning("Function pointer '" + func_node->lexeme + "' may be uninitialized", node);
        }
    }
}