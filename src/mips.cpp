#include "mips.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

MIPSGenerator::MIPSGenerator(const std::vector<TACInstruction>& tac) 
    : tac_instructions(tac), stack_offset(0), spill_offset(0), frame_size(0), 
      in_function(false), last_div_reg1(""), last_div_reg2(""), 
      current_instruction_index(0), string_counter(0) {
    
    // Initialize temporary registers pool
    temp_regs = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};
    
    // Initialize saved registers pool
    saved_regs = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7"};
}

// Compute liveness: find last use of each variable
void MIPSGenerator::compute_liveness() {
    var_last_use.clear();
    
    for (size_t i = 0; i < tac_instructions.size(); i++) {
        const auto& instr = tac_instructions[i];
        
        // Skip labels and certain operations
        if (!instr.label.empty()) {
            continue;
        }
        
        // Check arg1 usage (operands)
        if (!instr.arg1.empty() && !is_number(instr.arg1) && !is_label(instr.arg1) && 
            instr.arg1.front() != '"' && instr.arg1.front() != '\'') {
            var_last_use[instr.arg1] = i;
        }
        
        // Check arg2 usage (operands)
        if (!instr.arg2.empty() && !is_number(instr.arg2) && !is_label(instr.arg2) &&
            instr.arg2.front() != '"' && instr.arg2.front() != '\'') {
            var_last_use[instr.arg2] = i;
        }
        
        // For param and return, the variable is used
        if (instr.op == "param" || instr.op == "return") {
            if (!instr.arg1.empty() && !is_number(instr.arg1) && instr.arg1.front() != '"') {
                var_last_use[instr.arg1] = i;
            }
        }
    }
}

// Free registers for variables that are no longer needed
void MIPSGenerator::free_dead_registers() {
    dead_after_use.clear();
    
    for (auto it = reg_contents.begin(); it != reg_contents.end(); ) {
        const std::string& var = it->second;
        
        // Check if this variable's last use was the current instruction
        if (var_last_use.find(var) != var_last_use.end() && 
            var_last_use[var] == current_instruction_index) {
            
            // This variable is dead after this instruction
            std::string reg = it->first;
            
            // Only free temporary variables (not user variables or function parameters)
            if (is_temporary(var) && var.find("temp_literal") != 0) {
                var_to_reg.erase(var);
                it = reg_contents.erase(it);
                // Don't print comment for normal cleanup
                continue;
            }
        }
        ++it;
    }
}

void MIPSGenerator::generate(const std::string& output_filename) {
    output_file.open(output_filename);
    
    if (!output_file.is_open()) {
        std::cerr << "Error: Cannot open output file " << output_filename << std::endl;
        return;
    }
    
    // Print header to terminal
    std::cout << "\n=== MIPS ASSEMBLY CODE ===" << std::endl;
    
    emit_comment("==============================================");
    emit_comment("  MIPS Assembly Code");
    emit_comment("  Generated from Three-Address Code");
    emit_comment("==============================================");
    output_file << std::endl;
    
    // Compute liveness information before generating code
    compute_liveness();
    
    // First pass: collect data section info
    for (const auto& instr : tac_instructions) {
        if (instr.op == "param" && instr.arg1.front() == '"') {
            add_string_literal(instr.arg1);
        }
        // Collect arrays from address-of operations
        if (instr.op == "&" && instr.arg2.empty()) {
            std::string var_name = instr.arg1;
            // Check if we already allocated this array
            bool already_allocated = false;
            for (const auto& line : data_section) {
                if (line.find(var_name + ":") == 0) {
                    already_allocated = true;
                    break;
                }
            }
            if (!already_allocated) {
                // Use size from metadata if available, otherwise default
                int size = (array_sizes.find(var_name) != array_sizes.end()) ? array_sizes[var_name] : 400;
                add_global_variable(var_name, size);
            }
        }
    }
    
    emit_data_section();
    emit_text_section();
    
    output_file.close();
    
    // Now read and print the generated file to terminal
    std::ifstream display_file(output_filename);
    if (display_file.is_open()) {
        std::string line;
        while (std::getline(display_file, line)) {
            std::cout << line << std::endl;
        }
        display_file.close();
    }
    
    std::cout << "\nMIPS file generated: " << output_filename << std::endl;
}

void MIPSGenerator::emit_data_section() {
    output_file << ".data" << std::endl;
    
    // Emit string literals with alignment
    for (const auto& entry : string_literals) {
        output_file << ".align 2" << std::endl;  // Word-align before each string
        output_file << entry.second << ": .asciiz " << entry.first << std::endl;
    }
    
    // Add newline for scanf
    output_file << ".align 2" << std::endl;
    output_file << "newline: .asciiz \"\\n\"" << std::endl;
    
    // Emit data section entries (arrays, global/static variables)
    // These already have .align 2 from add_global_variable
    for (const auto& line : data_section) {
        output_file << line << std::endl;
    }
    
    // Emit global/static variables if any (backward compatibility)
    for (const auto& var : global_vars) {
        // Only emit if not already in data_section
        // Check both original name and safe name
        std::string safe_name = get_mips_var_name(var);
        bool found = false;
        for (const auto& line : data_section) {
            if (line.find(var + ":") == 0 || line.find(safe_name + ":") == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            output_file << ".align 2" << std::endl;
            output_file << safe_name << ": .word 0" << std::endl;
        }
    }
    
    output_file << std::endl;
}

void MIPSGenerator::emit_text_section() {
    output_file << ".text" << std::endl;
    output_file << ".globl main" << std::endl;
    output_file << std::endl;
    
    current_instruction_index = 0;
    for (size_t i = 0; i < tac_instructions.size(); i++) {
        current_instruction_index = i;
        translate_instruction(tac_instructions[i]);
        // After processing each instruction, free registers for dead variables
        free_dead_registers();
    }
}

void MIPSGenerator::translate_instruction(const TACInstruction& instr) {
    // Skip empty instructions
    if (instr.op.empty() && instr.label.empty()) {
        return;
    }
    
    // Handle labels (including function labels)
    if (!instr.label.empty()) {
        // Check if it's a function label using the function_names set
        if (function_names.find(instr.label) != function_names.end()) {
            // Function label
            translate_function_label(instr);
        } else {
            // Jump label (goto target or compiler-generated)
            translate_label(instr);
        }
        return;
    }
    
    // Handle different operations
    if (instr.op == "=") {
        translate_assignment(instr);
    }
    else if (instr.op == "*=") {
        // Pointer store: *address = value
        translate_pointer_store(instr);
    }
    // Check unary operators BEFORE binary to avoid conflicts
    else if (instr.op == "*" && instr.arg2.empty()) {
        translate_dereference(instr);
    }
    else if (instr.op == "&" && instr.arg2.empty()) {
        translate_address_of(instr);
    }
    else if (instr.op == "++" || instr.op == "--") {
        translate_unary_op(instr);
    }
    // Now check binary operators
    else if (instr.op == "+" || instr.op == "-" || instr.op == "*" || 
             instr.op == "/" || instr.op == "%") {
        translate_binary_op(instr);
    }
    else if (instr.op == "&" || instr.op == "|" || instr.op == "^") {
        translate_bitwise_op(instr);
    }
    else if (instr.op == "<<" || instr.op == ">>") {
        translate_shift_op(instr);
    }
    else if (instr.op == "~" || instr.op == "!" || instr.op == "uminus" ||
             instr.op == "unary-" || instr.op == "unary+" || instr.op == "unary!") {
        translate_unary_op(instr);
    }
    else if (instr.op == "<" || instr.op == ">" || instr.op == "<=" || 
             instr.op == ">=" || instr.op == "==" || instr.op == "!=") {
        translate_relational_op(instr);
    }
    else if (instr.op == "&&" || instr.op == "||") {
        translate_logical_op(instr);
    }
    else if (instr.op == "goto") {
        translate_goto(instr);
    }
    else if (instr.op == "if" || instr.op == "ifFalse") {
        translate_conditional_jump(instr);
    }
    else if (instr.op == "param") {
        translate_param(instr);
    }
    else if (instr.op == "call*") {
        translate_indirect_call(instr);
    }
    else if (instr.op == "call") {
        translate_call(instr);
    }
    else if (instr.op == "return") {
        translate_return(instr);
    }
    else if (instr.op == "return_struct_word") {
        // Store a word of the struct being returned
        // arg1 = temp with value, arg2 = word index (0, 1, 2...)
        std::string src_reg = get_register(instr.arg1);
        int word_index = std::stoi(instr.arg2);
        // Use $v0, $v1 for first two words, then stack for more
        if (word_index == 0) {
            emit("move $v0, " + src_reg);
        } else if (word_index == 1) {
            emit("move $v1, " + src_reg);
        } else {
            // Store to stack (caller should allocate space)
            int offset = (word_index - 2) * 4;
            emit("sw " + src_reg + ", " + std::to_string(offset) + "($sp)");
        }
    }
    else if (instr.op == "param_decl") {
        // Parameter declaration - add to current_func_params in order
        if (!instr.arg1.empty()) {
            current_func_params.push_back(instr.arg1);
            
            // If this is a struct parameter by value, we need to initialize it from multiple args
            // arg2 contains the type
            if (!instr.arg2.empty() && instr.arg2.find("struct ") == 0 && instr.arg2.back() != '*') {
                // This is a struct by value - it was passed as multiple words
                // We need to reconstruct it as a local variable
                std::string param_name = instr.arg1;
                
                // For now, mark it as a special case - it will be loaded from argument registers
                // when first accessed (just like regular parameters)
                emit_comment("Parameter " + param_name + " is struct " + instr.arg2);
            }
        }
    }
    else if (instr.op == "[]" || instr.op == "[]=") {
        translate_array_access(instr);
    }
}

void MIPSGenerator::translate_label(const TACInstruction& instr) {
    output_file << instr.label << ":" << std::endl;
}

void MIPSGenerator::translate_function_label(const TACInstruction& instr) {
    std::string func_name = instr.label;
    
    current_function = func_name;
    in_function = true;
    param_list.clear();
    param_regs.clear();
    var_offsets.clear();
    var_to_reg.clear();  // Clear register mappings for new function
    reg_contents.clear(); // Clear register contents tracking
    spilled_to_stack.clear();  // Clear spill tracking
    stack_offset = 0;
    spill_offset = 0;  // Reset spill offset for new function
    current_func_params.clear();  // Clear parameters
    
    // NOTE: Parameter detection is now handled by param_decl instructions in TAC
    // The old code that scanned forward to detect parameters is no longer needed
    /*
    // Detect function parameters: variables used before being assigned in this function
    // Scan forward from current instruction to find parameters
    if (func_name != "main") {
        std::unordered_set<std::string> assigned;
        for (size_t i = current_instruction_index + 1; i < tac_instructions.size(); i++) {
            const auto& inst = tac_instructions[i];
            // Stop at next function label
            if (!inst.label.empty() && inst.op.empty()) break;
            
            // Check if arg1 is used before assigned
            if (!inst.arg1.empty() && !is_number(inst.arg1) && !is_temporary(inst.arg1) && 
                inst.arg1.front() != '"' && inst.arg1.front() != '\'') {
                if (assigned.find(inst.arg1) == assigned.end()) {
                    // Used before assigned - it's a parameter
                    if (std::find(current_func_params.begin(), current_func_params.end(), inst.arg1) == current_func_params.end()) {
                        current_func_params.push_back(inst.arg1);
                    }
                }
            }
            
            // Check if arg2 is used before assigned
            if (!inst.arg2.empty() && !is_number(inst.arg2) && !is_temporary(inst.arg2) && 
                inst.arg2.front() != '"' && inst.arg2.front() != '\'') {
                if (assigned.find(inst.arg2) == assigned.end()) {
                    if (std::find(current_func_params.begin(), current_func_params.end(), inst.arg2) == current_func_params.end()) {
                        current_func_params.push_back(inst.arg2);
                    }
                }
            }
            
            // For pointer stores (*=), check the result as a parameter too
            if (inst.op == "*=" && !inst.result.empty() && !is_number(inst.result) && 
                !is_temporary(inst.result) && inst.result.front() != '"' && inst.result.front() != '\'') {
                if (assigned.find(inst.result) == assigned.end()) {
                    if (std::find(current_func_params.begin(), current_func_params.end(), inst.result) == current_func_params.end()) {
                        current_func_params.push_back(inst.result);
                    }
                }
            }
            
            // Mark result as assigned
            if (!inst.result.empty() && !is_temporary(inst.result)) {
                assigned.insert(inst.result);
            }
        }
    }
    */
    
    output_file << std::endl;
    emit_comment("Function: " + func_name);
    
    // Add prefix to user functions to avoid conflicts with MIPS instructions
    std::string label_name = func_name;
    if (func_name != "main") {
        label_name = "func_" + func_name;
    }
    output_file << label_name << ":" << std::endl;
    
    // Allocate stack space for potential spills (reserve 256 bytes for spill area)
    if (func_name == "main") {
        emit_comment("Reserve stack space for register spills");
        emit("addi $sp, $sp, -256");
    }
    
    // Only emit prologue for non-main functions
    if (func_name != "main") {
        emit_function_prologue(func_name);
        
        // Map parameters to saved stack locations
        // We'll detect parameter usage and save them as needed
        // For now, mark that $a0-$a3 are on stack at offsets
        // This will be loaded on first use of parameter variables
    }
}

void MIPSGenerator::emit_function_prologue(const std::string& func_name) {
    emit_comment("Function prologue");
    
    // Allocate stack frame - need more space for callee-saved registers
    emit("addi $sp, $sp, -56");  // 32 + 24 for $s0-$s7
    emit("sw $ra, 52($sp)");     // Save return address
    emit("sw $fp, 48($sp)");     // Save frame pointer
    emit("addi $fp, $sp, 56");   // Set new frame pointer
    
    // Save parameter registers $a0-$a3 (in case function is recursive)
    emit("sw $a0, 44($sp)");
    emit("sw $a1, 40($sp)");
    emit("sw $a2, 36($sp)");
    emit("sw $a3, 32($sp)");
    
    // Save callee-saved registers $s0-$s7 (they may be used and must be preserved)
    emit("sw $s0, 28($sp)");
    emit("sw $s1, 24($sp)");
    emit("sw $s2, 20($sp)");
    emit("sw $s3, 16($sp)");
    emit("sw $s4, 12($sp)");
    emit("sw $s5, 8($sp)");
    emit("sw $s6, 4($sp)");
    emit("sw $s7, 0($sp)");
    
    frame_size = 56;
}

void MIPSGenerator::emit_function_epilogue() {
    emit_comment("Function epilogue");
    // Restore callee-saved registers
    emit("lw $s0, 28($sp)");
    emit("lw $s1, 24($sp)");
    emit("lw $s2, 20($sp)");
    emit("lw $s3, 16($sp)");
    emit("lw $s4, 12($sp)");
    emit("lw $s5, 8($sp)");
    emit("lw $s6, 4($sp)");
    emit("lw $s7, 0($sp)");
    
    emit("lw $fp, 48($sp)");
    emit("lw $ra, 52($sp)");
    emit("addi $sp, $sp, 56");
    emit("jr $ra");
}

void MIPSGenerator::translate_assignment(const TACInstruction& instr) {
    // result = arg1
    std::string dest_reg = get_register(instr.result);
    
    if (is_number(instr.arg1)) {
        // Integer literal
        emit("li " + dest_reg + ", " + instr.arg1);
    } else if (instr.arg1.length() >= 3 && instr.arg1.front() == '\'' && instr.arg1.back() == '\'') {
        // Character literal: 'A'
        char ch = instr.arg1[1];  // Get the character between quotes
        emit("li " + dest_reg + ", " + std::to_string((int)ch));  // Load ASCII value
    } else if (instr.arg1.find('.') != std::string::npos && is_float_number(instr.arg1)) {
        // Float literal: 3.14
        emit_comment("Float value: " + instr.arg1 + " (stored as integer representation)");
        // For now, store float bits as integer (proper float support needs FPU registers)
        float f = std::stof(instr.arg1);
        int bits = *reinterpret_cast<int*>(&f);
        emit("li " + dest_reg + ", " + std::to_string(bits));
    } else if (function_names.find(instr.arg1) != function_names.end()) {
        // Assigning a function pointer - load address of function label
        emit("la " + dest_reg + ", func_" + instr.arg1);
    } else {
        // Variable assignment - may need type conversion
        std::string src_reg = get_register(instr.arg1);
        std::string dest_type = get_variable_type(instr.result);
        std::string src_type = get_variable_type(instr.arg1);
        
        emit("move " + dest_reg + ", " + src_reg);
        
        // Handle type conversions
        if (dest_type == "char" && src_type != "char") {
            // Truncate to 8 bits: mask with 0xFF
            emit_comment("Truncate int to char");
            emit("andi " + dest_reg + ", " + dest_reg + ", 0xFF");
        } else if (dest_type != "char" && src_type == "char") {
            // Sign extend from 8 bits: shift left 24, shift right 24 (arithmetic)
            emit_comment("Sign extend char to int");
            emit("sll " + dest_reg + ", " + dest_reg + ", 24");
            emit("sra " + dest_reg + ", " + dest_reg + ", 24");
        }
    }
}

void MIPSGenerator::translate_binary_op(const TACInstruction& instr) {
    // result = arg1 op arg2
    std::string dest_reg = get_register(instr.result);
    std::string reg1, reg2;
    bool reg1_is_temp_literal = false;
    bool reg2_is_temp_literal = false;
    
    // Load first operand
    if (is_number(instr.arg1)) {
        reg1 = allocate_temp_register();
        reg_contents[reg1] = "temp_literal";  // Mark as in-use
        emit("li " + reg1 + ", " + instr.arg1);
        reg1_is_temp_literal = true;
    } else if (is_char_literal(instr.arg1)) {
        reg1 = allocate_temp_register();
        reg_contents[reg1] = "temp_literal";  // Mark as in-use
        emit("li " + reg1 + ", " + std::to_string(get_char_value(instr.arg1)));
        reg1_is_temp_literal = true;
    } else {
        reg1 = get_register(instr.arg1);
    }
    
    // Load second operand
    if (is_number(instr.arg2)) {
        reg2 = allocate_temp_register();
        reg_contents[reg2] = "temp_literal";  // Mark as in-use
        emit("li " + reg2 + ", " + instr.arg2);
        reg2_is_temp_literal = true;
    } else if (is_char_literal(instr.arg2)) {
        reg2 = allocate_temp_register();
        reg_contents[reg2] = "temp_literal";  // Mark as in-use
        emit("li " + reg2 + ", " + std::to_string(get_char_value(instr.arg2)));
        reg2_is_temp_literal = true;
    } else {
        reg2 = get_register(instr.arg2);
    }
    
    // Perform operation
    if (instr.op == "+") {
        emit("add " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "-") {
        emit("sub " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "*") {
        emit("mul " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "/") {
        // Check if we can reuse previous div result
        if (last_div_reg1 == instr.arg1 && last_div_reg2 == instr.arg2) {
            emit_comment("Reusing previous div result");
            emit("mflo " + dest_reg);
        } else {
            emit("div " + reg1 + ", " + reg2);
            emit("mflo " + dest_reg);
            last_div_reg1 = instr.arg1;
            last_div_reg2 = instr.arg2;
        }
    }
    else if (instr.op == "%") {
        // Check if we can reuse previous div result
        if (last_div_reg1 == instr.arg1 && last_div_reg2 == instr.arg2) {
            emit_comment("Reusing previous div result");
            emit("mfhi " + dest_reg);
        } else {
            emit("div " + reg1 + ", " + reg2);
            emit("mfhi " + dest_reg);
            last_div_reg1 = instr.arg1;
            last_div_reg2 = instr.arg2;
        }
    }
    
    // Free temporary literal registers immediately after use
    if (reg1_is_temp_literal) {
        reg_contents.erase(reg1);
    }
    if (reg2_is_temp_literal) {
        reg_contents.erase(reg2);
    }
}

void MIPSGenerator::translate_bitwise_op(const TACInstruction& instr) {
    std::string dest_reg = get_register(instr.result);
    std::string reg1 = get_register(instr.arg1);
    std::string reg2 = get_register(instr.arg2);
    
    if (instr.op == "&") {
        emit("and " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "|") {
        emit("or " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "^") {
        emit("xor " + dest_reg + ", " + reg1 + ", " + reg2);
    }
}

void MIPSGenerator::translate_shift_op(const TACInstruction& instr) {
    std::string dest_reg = get_register(instr.result);
    std::string reg1 = get_register(instr.arg1);
    
    if (instr.op == "<<") {
        if (is_number(instr.arg2)) {
            emit("sll " + dest_reg + ", " + reg1 + ", " + instr.arg2);
        } else {
            std::string reg2 = get_register(instr.arg2);
            emit("sllv " + dest_reg + ", " + reg1 + ", " + reg2);
        }
    }
    else if (instr.op == ">>") {
        if (is_number(instr.arg2)) {
            emit("srl " + dest_reg + ", " + reg1 + ", " + instr.arg2);
        } else {
            std::string reg2 = get_register(instr.arg2);
            emit("srlv " + dest_reg + ", " + reg1 + ", " + reg2);
        }
    }
}

void MIPSGenerator::translate_unary_op(const TACInstruction& instr) {
    std::string dest_reg = get_register(instr.result);
    
    // Handle operand - could be number or variable
    std::string src_reg;
    if (is_number(instr.arg1)) {
        src_reg = allocate_temp_register();
        emit("li " + src_reg + ", " + instr.arg1);
    } else {
        src_reg = get_register(instr.arg1);
    }
    
    if (instr.op == "~") {
        emit("nor " + dest_reg + ", " + src_reg + ", $zero");
    }
    else if (instr.op == "!") {
        emit("seq " + dest_reg + ", " + src_reg + ", $zero");
    }
    else if (instr.op == "unary-" || instr.op == "uminus") {
        emit("sub " + dest_reg + ", $zero, " + src_reg);
    }
    else if (instr.op == "unary+") {
        emit("move " + dest_reg + ", " + src_reg);
    }
    else if (instr.op == "++") {
        emit("addi " + dest_reg + ", " + src_reg + ", 1");
    }
    else if (instr.op == "--") {
        emit("addi " + dest_reg + ", " + src_reg + ", -1");
    }
}

void MIPSGenerator::translate_relational_op(const TACInstruction& instr) {
    std::string dest_reg = get_register(instr.result);
    std::string reg1, reg2;
    
    // Load first operand
    if (is_number(instr.arg1)) {
        reg1 = allocate_temp_register();
        emit("li " + reg1 + ", " + instr.arg1);
    } else if (is_char_literal(instr.arg1)) {
        reg1 = allocate_temp_register();
        emit("li " + reg1 + ", " + std::to_string(get_char_value(instr.arg1)));
    } else {
        reg1 = get_register(instr.arg1);
    }
    
    // Load second operand
    if (is_number(instr.arg2)) {
        reg2 = allocate_temp_register();
        emit("li " + reg2 + ", " + instr.arg2);
    } else if (is_char_literal(instr.arg2)) {
        reg2 = allocate_temp_register();
        emit("li " + reg2 + ", " + std::to_string(get_char_value(instr.arg2)));
    } else {
        reg2 = get_register(instr.arg2);
    }
    
    if (instr.op == "<") {
        emit("slt " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == ">") {
        emit("sgt " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "<=") {
        emit("sle " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == ">=") {
        emit("sge " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "==") {
        emit("seq " + dest_reg + ", " + reg1 + ", " + reg2);
    }
    else if (instr.op == "!=") {
        emit("sne " + dest_reg + ", " + reg1 + ", " + reg2);
    }
}

void MIPSGenerator::translate_logical_op(const TACInstruction& instr) {
    std::string dest_reg = get_register(instr.result);
    std::string reg1 = get_register(instr.arg1);
    std::string reg2 = get_register(instr.arg2);
    
    if (instr.op == "&&") {
        std::string temp = allocate_temp_register();
        emit("sne " + temp + ", " + reg1 + ", $zero");
        emit("sne " + dest_reg + ", " + reg2 + ", $zero");
        emit("and " + dest_reg + ", " + temp + ", " + dest_reg);
    }
    else if (instr.op == "||") {
        std::string temp = allocate_temp_register();
        emit("or " + temp + ", " + reg1 + ", " + reg2);
        emit("sne " + dest_reg + ", " + temp + ", $zero");
    }
}

void MIPSGenerator::translate_goto(const TACInstruction& instr) {
    emit("j " + instr.result);
}

void MIPSGenerator::translate_conditional_jump(const TACInstruction& instr) {
    std::string cond_reg = get_register(instr.arg1);
    std::string label = instr.result;
    
    if (instr.op == "if") {
        emit("bne " + cond_reg + ", $zero, " + label);
    }
    else if (instr.op == "ifFalse") {
        emit("beq " + cond_reg + ", $zero, " + label);
    }
}

void MIPSGenerator::translate_param(const TACInstruction& instr) {
    // Save parameter value to avoid register reuse issues
    std::string param_val = instr.arg1;
    param_list.push_back(param_val);
    
    // Get the current register holding the value and save it to a temporary saved register
    // This preserves the value until the function call
    std::string src_reg;
    if (is_number(param_val)) {
        // For immediate values, just store the value itself
        param_regs.push_back("");  // Empty string means use immediate
    } else if (is_char_literal(param_val)) {
        // Character literal - store the value itself
        param_regs.push_back("");  // Empty string means use immediate
    } else if (param_val.front() == '"') {
        // String literal - load its address
        auto it = string_literals.find(param_val);
        if (it != string_literals.end()) {
            std::string label = it->second;
            std::string save_reg = allocate_saved_register();
            emit("la " + save_reg + ", " + label);
            emit_comment("Save string param " + label + " to " + save_reg);
            param_regs.push_back(save_reg);
        } else {
            // Fallback if not found
            param_regs.push_back("");
        }
    } else if (array_dims.find(param_val) != array_dims.end()) {
        // Array parameter - pass address of array
        std::string save_reg = allocate_saved_register();
        if (var_offsets.find(param_val) != var_offsets.end()) {
            // Stack-allocated array
            int offset = var_offsets[param_val];
            emit("addi " + save_reg + ", $sp, " + std::to_string(offset));
            emit_comment("Save array address " + param_val + " to " + save_reg);
        } else if (global_vars.find(param_val) != global_vars.end() || 
                   static_vars.find(param_val) != static_vars.end()) {
            // Global/static array
            emit("la " + save_reg + ", " + param_val);
            emit_comment("Save array address " + param_val + " to " + save_reg);
        }
        param_regs.push_back(save_reg);
    } else {
        src_reg = get_register(param_val);
        // Allocate a saved register to hold this parameter
        std::string save_reg = allocate_saved_register();
        emit("move " + save_reg + ", " + src_reg);
        emit_comment("Save param " + param_val + " to " + save_reg);
        param_regs.push_back(save_reg);
    }
}

void MIPSGenerator::translate_call(const TACInstruction& instr) {
    // result = call func, arg_count
    std::string func_name = instr.arg1;
    int num_params = std::stoi(instr.arg2);  // Number of parameters to use
    
    emit_comment("Call " + func_name);
    
    // Handle special functions
    if (func_name == "printf") {
        handle_printf();
    }
    else if (func_name == "scanf") {
        handle_scanf();
    }
    else {
        // Pass only the LAST num_params arguments (ignore earlier accumulated ones)
        pass_arguments(num_params);
        
        // Call function - add prefix for user functions
        std::string call_label = func_name;
        if (func_name != "main" && func_name != "printf" && func_name != "scanf") {
            call_label = "func_" + func_name;
        }
        emit("jal " + call_label);
        
        // After function call, invalidate temporary register mappings
        // since $t registers are caller-saved and may be modified
        std::vector<std::string> to_remove;
        for (const auto& entry : var_to_reg) {
            if (entry.second[1] == 't') {  // $t0-$t9 registers
                to_remove.push_back(entry.first);
            }
        }
        for (const auto& var : to_remove) {
            std::string reg = var_to_reg[var];
            var_to_reg.erase(var);
            reg_contents.erase(reg);
        }
        
        // Store return value - use saved register to preserve across future calls
        if (!instr.result.empty()) {
            std::string result_reg = allocate_saved_register();
            var_to_reg[instr.result] = result_reg;
            reg_contents[result_reg] = instr.result;
            emit("move " + result_reg + ", $v0");
        }
        
        // Remove the params that were just used (last num_params)
        if (num_params > 0 && param_list.size() >= (size_t)num_params) {
            param_list.erase(param_list.end() - num_params, param_list.end());
            if (param_regs.size() >= (size_t)num_params) {
                param_regs.erase(param_regs.end() - num_params, param_regs.end());
            }
        }
    }
    
    // For printf/scanf, also remove their used params
    if (func_name == "printf" || func_name == "scanf") {
        if (num_params > 0 && param_list.size() >= (size_t)num_params) {
            param_list.erase(param_list.end() - num_params, param_list.end());
            if (param_regs.size() >= (size_t)num_params) {
                param_regs.erase(param_regs.end() - num_params, param_regs.end());
            }
        }
    }
}

void MIPSGenerator::pass_arguments(int num_params) {
    // Only use the LAST num_params from param_list
    int start_index = param_list.size() > (size_t)num_params ? param_list.size() - num_params : 0;
    
    // Pass up to 4 arguments in $a0-$a3
    for (size_t i = start_index; i < param_list.size() && (i - start_index) < 4; i++) {
        std::string arg_reg = "$a" + std::to_string(i - start_index);
        
        if (is_number(param_list[i])) {
            emit("li " + arg_reg + ", " + param_list[i]);
        }
        else if (is_char_literal(param_list[i])) {
            // Character literal - load its ASCII value
            int char_val = get_char_value(param_list[i]);
            emit("li " + arg_reg + ", " + std::to_string(char_val));
        }
        else if (param_list[i].front() == '"') {
            // String literal
            std::string str_label = string_literals[param_list[i]];
            emit("la " + arg_reg + ", " + str_label);
        }
        else {
            // Use the saved register from param_regs (which was allocated in translate_param)
            // If param_regs[i] is empty, it means we should use get_register for immediate values
            if (!param_regs[i].empty()) {
                emit("move " + arg_reg + ", " + param_regs[i]);
            } else {
                std::string src_reg = get_register(param_list[i]);
                emit("move " + arg_reg + ", " + src_reg);
            }
        }
    }
    
    // Additional arguments go on stack (for future)
    // TODO: Handle more than 4 arguments
}

void MIPSGenerator::translate_indirect_call(const TACInstruction& instr) {
    // result = call* func_ptr, arg_count
    // func_ptr is in arg1, arg_count is in arg2
    std::string func_ptr_var = instr.arg1;
    int num_params = std::stoi(instr.arg2);
    
    emit_comment("Indirect call through " + func_ptr_var);
    
    // Get the register holding the function pointer
    std::string func_ptr_reg = get_register(func_ptr_var);
    
    // Pass arguments (same as regular call)
    pass_arguments(num_params);
    
    // Call through the function pointer using jalr
    emit("jalr " + func_ptr_reg);
    
    // After function call, invalidate temporary register mappings
    std::vector<std::string> to_remove;
    for (const auto& entry : var_to_reg) {
        if (entry.second[1] == 't') {  // $t0-$t9 registers
            to_remove.push_back(entry.first);
        }
    }
    for (const auto& var : to_remove) {
        std::string reg = var_to_reg[var];
        var_to_reg.erase(var);
        reg_contents.erase(reg);
    }
    
    // Store return value
    if (!instr.result.empty()) {
        std::string result_reg = allocate_saved_register();
        var_to_reg[instr.result] = result_reg;
        reg_contents[result_reg] = instr.result;
        emit("move " + result_reg + ", $v0");
    }
    
    // Remove the used params
    if (num_params > 0 && param_list.size() >= (size_t)num_params) {
        param_list.erase(param_list.end() - num_params, param_list.end());
        if (param_regs.size() >= (size_t)num_params) {
            param_regs.erase(param_regs.end() - num_params, param_regs.end());
        }
    }
}

void MIPSGenerator::print_literal_string(const std::string& text) {
    // Print literal text character by character, handling escape sequences
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        
        // Check for escape sequences
        if (c == '\\' && i + 1 < text.length()) {
            char next = text[i + 1];
            if (next == 'n') {
                // Print newline
                emit("li $v0, 11");  // print_char
                emit("li $a0, 10");  // newline character
                emit("syscall");
                i++;  // Skip the 'n'
                continue;
            } else if (next == 't') {
                // Print tab
                emit("li $v0, 11");  // print_char
                emit("li $a0, 9");   // tab character
                emit("syscall");
                i++;  // Skip the 't'
                continue;
            } else if (next == '\\') {
                // Print backslash
                emit("li $v0, 11");  // print_char
                emit("li $a0, 92");  // backslash character
                emit("syscall");
                i++;  // Skip the second backslash
                continue;
            }
        }
        
        // Print regular character
        emit("li $v0, 11");  // syscall for print_char
        emit("li $a0, " + std::to_string(static_cast<int>(c)));
        emit("syscall");
    }
}

void MIPSGenerator::handle_printf() {
    // For SPIM, use syscalls
    if (param_list.empty()) return;
    
    // Format string should be the FIRST of the params for this printf call
    // We need to figure out how many params this printf has
    // For now, assume format string is at param_list[0] if it's a string literal
    std::string format;
    int format_index = -1;
    
    // Find the format string (should be a string literal starting with ")
    for (int i = param_list.size() - 1; i >= 0; i--) {
        if (!param_list[i].empty() && param_list[i].front() == '"') {
            format = param_list[i];
            format_index = i;
            break;
        }
    }
    
    if (format_index < 0) return;  // No format string found
    
    // Remove surrounding quotes from format string
    if (format.front() == '"' && format.back() == '"') {
        format = format.substr(1, format.length() - 2);
    }
    
    int param_index = format_index + 1;  // Start from after format string
    
    // Parse format string and print accordingly
    size_t pos = 0;
    while (pos < format.length()) {
        // Find next format specifier
        size_t percent_pos = format.find('%', pos);
        
        if (percent_pos == std::string::npos) {
            // No more format specifiers, print remaining literal text
            if (pos < format.length()) {
                std::string remaining = format.substr(pos);
                print_literal_string(remaining);
            }
            break;
        }
        
        // Print literal text before this format specifier
        if (percent_pos > pos) {
            std::string literal = format.substr(pos, percent_pos - pos);
            print_literal_string(literal);
        }
        
        // Check what comes after %
        if (percent_pos + 1 < format.length()) {
            char spec = format[percent_pos + 1];
            
            if (spec == 'd') {
                // Print integer
                emit_comment("Print integer");
                emit("li $v0, 1");  // Syscall for print_int
                
                if ((size_t)param_index < param_list.size()) {
                    if (is_number(param_list[param_index])) {
                        emit("li $a0, " + param_list[param_index]);
                    } else if (is_char_literal(param_list[param_index])) {
                        // Character literal - print its ASCII value
                        emit("li $a0, " + std::to_string(get_char_value(param_list[param_index])));
                    } else {
                        // Use the saved register from param_regs
                        if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                            emit("move $a0, " + param_regs[param_index]);
                        } else {
                            // Fallback (shouldn't happen)
                            std::string reg = get_register(param_list[param_index]);
                            emit("move $a0, " + reg);
                        }
                    }
                    param_index++;
                }
                emit("syscall");
                
                pos = percent_pos + 2;
            }
            else if (spec == 's') {
                // Print string
                emit_comment("Print string");
                emit("li $v0, 4");  // Syscall for print_string
                if ((size_t)param_index < param_list.size()) {
                    if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                        emit("move $a0, " + param_regs[param_index]);
                    } else {
                        std::string reg = get_register(param_list[param_index]);
                        emit("move $a0, " + reg);
                    }
                    param_index++;
                }
                emit("syscall");
                pos = percent_pos + 2;
            }
            else if (spec == 'c') {
                // Print character
                emit_comment("Print character");
                emit("li $v0, 11");  // Syscall for print_char
                if ((size_t)param_index < param_list.size()) {
                    if (is_number(param_list[param_index])) {
                        emit("li $a0, " + param_list[param_index]);
                    } else if (is_char_literal(param_list[param_index])) {
                        emit("li $a0, " + std::to_string(get_char_value(param_list[param_index])));
                    } else {
                        if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                            emit("move $a0, " + param_regs[param_index]);
                        } else {
                            std::string reg = get_register(param_list[param_index]);
                            emit("move $a0, " + reg);
                        }
                    }
                    param_index++;
                }
                emit("syscall");
                pos = percent_pos + 2;
            }
            else if (spec == 'f' || spec == '.' || (spec >= '0' && spec <= '9')) {
                // Handle %f, %.Xf, or other float format specifiers
                emit_comment("Print float");
                
                // Skip precision specifiers like .2 in %.2f
                size_t spec_end = percent_pos + 1;
                while (spec_end < format.length() && 
                       (format[spec_end] == '.' || (format[spec_end] >= '0' && format[spec_end] <= '9'))) {
                    spec_end++;
                }
                
                // Check if it ends with 'f'
                if (spec_end < format.length() && format[spec_end] == 'f') {
                    // Print the float value using SPIM syscall 2
                    emit_comment("Print float");
                    emit("li $v0, 2");  // Syscall for print_float
                    
                    if ((size_t)param_index < param_list.size()) {
                        if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                            // The value is in an integer register as IEEE 754 bits
                            // Move to coprocessor 1 (FPU) register $f12
                            emit("mtc1 " + param_regs[param_index] + ", $f12");
                            // Note: mtc1 preserves bit pattern, so IEEE 754 value is now in $f12
                        } else {
                            std::string reg = get_register(param_list[param_index]);
                            emit("mtc1 " + reg + ", $f12");
                        }
                        param_index++;
                    }
                    emit("syscall");
                    pos = spec_end + 1;
                } else if (spec == 'f') {
                    // Just %f without precision
                    emit_comment("Print float");
                    emit("li $v0, 2");
                    
                    if ((size_t)param_index < param_list.size()) {
                        if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                            emit("mtc1 " + param_regs[param_index] + ", $f12");
                        } else {
                            std::string reg = get_register(param_list[param_index]);
                            emit("mtc1 " + reg + ", $f12");
                        }
                        param_index++;
                    }
                    emit("syscall");
                    pos = percent_pos + 2;
                } else {
                    pos = percent_pos + 1;
                }
            }
            else {
                pos = percent_pos + 1;
            }
        } else {
            break;
        }
    }
}

void MIPSGenerator::handle_scanf() {
    // For SPIM scanf - reads input and stores to addresses
    if (param_list.size() < 2) return;
    
    std::string format = param_list[0];
    // Remove surrounding quotes from format string
    if (format.front() == '"' && format.back() == '"') {
        format = format.substr(1, format.length() - 2);
    }
    
    int param_index = 1;  // Start from param_list[1] (after format string)
    
    // Parse format string for input specifiers
    size_t pos = 0;
    while (pos < format.length() && (size_t)param_index < param_list.size()) {
        size_t percent_pos = format.find('%', pos);
        
        if (percent_pos == std::string::npos) {
            break;
        }
        
        // Check what comes after %
        if (percent_pos + 1 < format.length()) {
            char spec = format[percent_pos + 1];
            
            if (spec == 'd') {
                // Read integer
                emit_comment("Read integer from user");
                emit("li $v0, 5");  // Syscall for read_int
                emit("syscall");
                
                // Store to address - param should be a register holding address
                if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                    emit("sw $v0, 0(" + param_regs[param_index] + ")");
                } else if ((size_t)param_index < param_list.size()) {
                    // Fallback - shouldn't happen with proper param handling
                    std::string addr_reg = get_register(param_list[param_index]);
                    emit("sw $v0, 0(" + addr_reg + ")");
                }
                param_index++;
                pos = percent_pos + 2;
            }
            else if (spec == 'c') {
                // Read character
                emit_comment("Read character from user");
                emit("li $v0, 12");  // Syscall for read_char
                emit("syscall");
                
                // Store to address
                if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                    emit("sb $v0, 0(" + param_regs[param_index] + ")");
                } else if ((size_t)param_index < param_list.size()) {
                    std::string addr_reg = get_register(param_list[param_index]);
                    emit("sb $v0, 0(" + addr_reg + ")");
                }
                param_index++;
                pos = percent_pos + 2;
            }
            else if (spec == 's') {
                // Read string - more complex, need buffer address and max length
                emit_comment("Read string from user");
                emit("li $v0, 8");  // Syscall for read_string
                
                // Address in $a0, max length in $a1
                if ((size_t)param_index < param_regs.size() && !param_regs[param_index].empty()) {
                    emit("move $a0, " + param_regs[param_index]);
                } else if ((size_t)param_index < param_list.size()) {
                    std::string addr_reg = get_register(param_list[param_index]);
                    emit("move $a0, " + addr_reg);
                }
                emit("li $a1, 256");  // Max 256 characters
                emit("syscall");
                
                param_index++;
                pos = percent_pos + 2;
            }
            else {
                pos = percent_pos + 1;
            }
        } else {
            break;
        }
    }
}

void MIPSGenerator::translate_return(const TACInstruction& instr) {
    if (current_function == "main") {
        // For main function in SPIM, put return value in $v0 first, then exit
        if (!instr.arg1.empty()) {
            if (is_number(instr.arg1)) {
                emit("li $v0, " + instr.arg1);
            } else if (is_char_literal(instr.arg1)) {
                emit("li $v0, " + std::to_string(get_char_value(instr.arg1)));
            } else {
                std::string src_reg = get_register(instr.arg1);
                emit("move $v0, " + src_reg);
            }
        }
        emit_comment("Restore stack and exit program");
        emit("addi $sp, $sp, 256");  // Restore stack pointer
        emit("li $v0, 10");  // Exit syscall
        emit("syscall");
    } else {
        // Regular function return - value in $v0
        if (!instr.arg1.empty()) {
            if (is_number(instr.arg1)) {
                emit("li $v0, " + instr.arg1);
            } else if (is_char_literal(instr.arg1)) {
                emit("li $v0, " + std::to_string(get_char_value(instr.arg1)));
            } else {
                std::string src_reg = get_register(instr.arg1);
                emit("move $v0, " + src_reg);
            }
        }
        
        emit_function_epilogue();
    }
}

void MIPSGenerator::translate_array_access(const TACInstruction& instr) {
    if (instr.op == "[]=") {
        // Array store: array[index] = value
        // result = array name, arg1 = index, arg2 = value
        std::string array_name = instr.result;
        std::string index_val = instr.arg1;
        std::string value_str = instr.arg2;
        
        // Get element size from array_element_types
        int element_size = 4; // default
        if (array_element_types.find(array_name) != array_element_types.end()) {
            std::string elem_type = array_element_types[array_name];
            if (elem_type == "char") element_size = 1;
            else if (elem_type == "short") element_size = 2;
            else if (elem_type == "int" || elem_type == "float") element_size = 4;
            else if (elem_type == "double" || elem_type == "long") element_size = 8;
        }
        
        // Allocate array in data section if needed
        if (array_sizes.find(array_name) == array_sizes.end()) {
            // Calculate size from array_dims
            int total_size = element_size;
            if (array_dims.find(array_name) != array_dims.end()) {
                for (int dim : array_dims[array_name]) {
                    total_size *= dim;
                }
            }
            array_sizes[array_name] = total_size;
            add_global_variable(array_name, total_size);
        }
        
        // Calculate byte offset
        std::string offset_reg = allocate_temp_register();
        reg_contents[offset_reg] = "temp_offset";  // Mark as in-use
        if (is_number(index_val)) {
            int byte_offset = std::stoi(index_val) * element_size;
            emit("li " + offset_reg + ", " + std::to_string(byte_offset));
        } else {
            std::string index_reg = get_register(index_val);
            std::string elem_size_reg = allocate_temp_register();
            reg_contents[elem_size_reg] = "temp_elem_size";
            emit("li " + elem_size_reg + ", " + std::to_string(element_size));
            emit("mul " + offset_reg + ", " + index_reg + ", " + elem_size_reg);
            reg_contents.erase(elem_size_reg);  // Free this temp
        }
        
        // Get array base address (use safe name for global arrays)
        std::string base_reg = allocate_temp_register();
        reg_contents[base_reg] = "temp_base";  // Mark as in-use
        std::string safe_array_name = get_mips_var_name(array_name);
        emit("la " + base_reg + ", " + safe_array_name);
        
        // Calculate element address
        std::string addr_reg = allocate_temp_register();
        reg_contents[addr_reg] = "temp_addr";  // Mark as in-use
        emit("add " + addr_reg + ", " + base_reg + ", " + offset_reg);
        
        // Free base and offset registers
        reg_contents.erase(base_reg);
        reg_contents.erase(offset_reg);
        
        // Get value to store
        std::string value_reg;
        bool value_is_temp = false;
        if (is_number(value_str)) {
            value_reg = allocate_temp_register();
            reg_contents[value_reg] = "temp_value";
            emit("li " + value_reg + ", " + value_str);
            value_is_temp = true;
        } else if (is_char_literal(value_str)) {
            value_reg = allocate_temp_register();
            reg_contents[value_reg] = "temp_value";
            emit("li " + value_reg + ", " + std::to_string(get_char_value(value_str)));
            value_is_temp = true;
        } else {
            value_reg = get_register(value_str);
        }
        
        // Store value
        if (element_size == 1) {
            emit("sb " + value_reg + ", 0(" + addr_reg + ")");
        } else if (element_size == 2) {
            emit("sh " + value_reg + ", 0(" + addr_reg + ")");
        } else {
            emit("sw " + value_reg + ", 0(" + addr_reg + ")");
        }
        
        // Free temporary registers
        reg_contents.erase(addr_reg);
        if (value_is_temp) {
            reg_contents.erase(value_reg);
        }
    } else if (instr.op == "[]") {
        // Array load: result = array[index]
        // op="[]", arg1=array, arg2=index, result=result
        std::string array_name = instr.arg1;
        std::string index_val = instr.arg2;
        std::string result_var = instr.result;
        
        // Get element size
        int element_size = 4; // default
        if (array_element_types.find(array_name) != array_element_types.end()) {
            std::string elem_type = array_element_types[array_name];
            if (elem_type == "char") element_size = 1;
            else if (elem_type == "short") element_size = 2;
            else if (elem_type == "int" || elem_type == "float") element_size = 4;
            else if (elem_type == "double" || elem_type == "long") element_size = 8;
        }
        
        // Calculate byte offset
        std::string offset_reg = allocate_temp_register();
        reg_contents[offset_reg] = "temp_offset";
        if (is_number(index_val)) {
            int byte_offset = std::stoi(index_val) * element_size;
            emit("li " + offset_reg + ", " + std::to_string(byte_offset));
        } else {
            std::string index_reg = get_register(index_val);
            std::string elem_size_reg = allocate_temp_register();
            reg_contents[elem_size_reg] = "temp_elem_size";
            emit("li " + elem_size_reg + ", " + std::to_string(element_size));
            emit("mul " + offset_reg + ", " + index_reg + ", " + elem_size_reg);
            reg_contents.erase(elem_size_reg);
        }
        
        // Get array base address (use safe name)
        std::string base_reg = allocate_temp_register();
        reg_contents[base_reg] = "temp_base";
        std::string safe_array_name = get_mips_var_name(array_name);
        emit("la " + base_reg + ", " + safe_array_name);
        
        // Calculate element address
        std::string addr_reg = allocate_temp_register();
        reg_contents[addr_reg] = "temp_addr";
        emit("add " + addr_reg + ", " + base_reg + ", " + offset_reg);
        
        // Free base and offset
        reg_contents.erase(base_reg);
        reg_contents.erase(offset_reg);
        
        // Load value
        std::string result_reg = get_register(result_var);
        if (element_size == 1) {
            emit("lbu " + result_reg + ", 0(" + addr_reg + ")");
        } else if (element_size == 2) {
            emit("lhu " + result_reg + ", 0(" + addr_reg + ")");
        } else {
            emit("lw " + result_reg + ", 0(" + addr_reg + ")");
        }
        
        // Free addr register
        reg_contents.erase(addr_reg);
    }
}

void MIPSGenerator::translate_address_of(const TACInstruction& instr) {
    // result = &var
    // Get the address of a variable or array
    std::string result_reg = get_register(instr.result);
    std::string var_name = instr.arg1;
    
    // Check if this is a stack variable (local variable)
    if (var_offsets.find(var_name) != var_offsets.end()) {
        // It's a local variable on the stack
        int offset = var_offsets[var_name];
        // Load address: result = $sp + offset
        if (offset == 0) {
            emit("move " + result_reg + ", $sp");
        } else if (offset > 0) {
            emit("addi " + result_reg + ", $sp, " + std::to_string(offset));
        } else {
            emit("addi " + result_reg + ", $sp, " + std::to_string(offset));
        }
        return;
    }
    
    // Check if this is a known array with size already calculated
    int alloc_size = 4; // default for scalar variables
    if (array_sizes.find(var_name) != array_sizes.end()) {
        alloc_size = array_sizes[var_name];
    }
    
    // Allocate the array/variable in data section if not already done
    // (for global/static variables only)
    if (global_vars.find(var_name) == global_vars.end() && 
        static_vars.find(var_name) == static_vars.end()) {
        add_global_variable(var_name, alloc_size);
    }
    
    // Load address of the array/variable (use safe name)
    std::string safe_var_name = get_mips_var_name(var_name);
    emit("la " + result_reg + ", " + safe_var_name);
}

void MIPSGenerator::translate_dereference(const TACInstruction& instr) {
    // result = *ptr
    std::string ptr_reg = get_register(instr.arg1);
    std::string result_reg = get_register(instr.result);
    
    // Check for element size hint in comment
    int element_size = 4; // default
    if (!instr.comment.empty() && instr.comment.find("size=") == 0) {
        element_size = std::stoi(instr.comment.substr(5));
    }
    
    // Use appropriate load instruction based on size
    if (element_size == 1) {
        emit("lbu " + result_reg + ", 0(" + ptr_reg + ")");  // load byte unsigned
    } else if (element_size == 2) {
        emit("lhu " + result_reg + ", 0(" + ptr_reg + ")");  // load halfword unsigned
    } else {
        emit("lw " + result_reg + ", 0(" + ptr_reg + ")");   // load word
    }
}

void MIPSGenerator::translate_pointer_store(const TACInstruction& instr) {
    // *address = value  (stored as op="*=", arg1=value, result=address)
    std::string addr_reg = get_register(instr.result);
    
    // Get the value to store
    std::string value_reg;
    if (is_number(instr.arg1)) {
        value_reg = allocate_temp_register();
        emit("li " + value_reg + ", " + instr.arg1);
    } else if (is_char_literal(instr.arg1)) {
        value_reg = allocate_temp_register();
        emit("li " + value_reg + ", " + std::to_string(get_char_value(instr.arg1)));
    } else if (function_names.find(instr.arg1) != function_names.end()) {
        // Storing a function address - load address of function label
        value_reg = allocate_temp_register();
        emit("la " + value_reg + ", func_" + instr.arg1);
    } else {
        value_reg = get_register(instr.arg1);
    }
    
    // Check for element size hint in comment
    int element_size = 4; // default
    if (!instr.comment.empty() && instr.comment.find("size=") == 0) {
        element_size = std::stoi(instr.comment.substr(5));
    }
    
    // Use appropriate store instruction based on size
    if (element_size == 1) {
        emit("sb " + value_reg + ", 0(" + addr_reg + ")");  // store byte
    } else if (element_size == 2) {
        emit("sh " + value_reg + ", 0(" + addr_reg + ")");  // store halfword
    } else {
        emit("sw " + value_reg + ", 0(" + addr_reg + ")");  // store word
    }
}

std::string MIPSGenerator::get_register(const std::string& var) {
    // Check if already in a register
    if (var_to_reg.find(var) != var_to_reg.end()) {
        return var_to_reg[var];
    }
    
    // Check if this variable was spilled to stack - if so, we need to reload it
    bool was_spilled = (spilled_to_stack.find(var) != spilled_to_stack.end());
    int spill_stack_offset = was_spilled ? spilled_to_stack[var] : 0;
    
    // Don't use argument registers for temporaries (t0, t1, etc.)
    if (is_temporary(var)) {
        std::string reg = allocate_temp_register();
        var_to_reg[var] = reg;
        reg_contents[reg] = var;  // Track what's in this register
        
        // If this variable was spilled to stack, reload it
        if (was_spilled) {
            emit_comment("Reloading " + var + " from stack");
            emit("lw " + reg + ", " + std::to_string(spill_stack_offset) + "($sp)");
            spilled_to_stack.erase(var);  // No longer spilled
        }
        
        return reg;
    }
    
    // Check if this variable is a function parameter by checking current_func_params
    if (current_function != "main" && in_function && !is_temporary(var)) {
        // Check if var is in current_func_params list
        auto it = std::find(current_func_params.begin(), current_func_params.end(), var);
        if (it != current_func_params.end()) {
            // This is a parameter - load from saved stack location
            int param_index = std::distance(current_func_params.begin(), it);
            if (param_index < 4) {
                std::string reg = allocate_temp_register();
                var_to_reg[var] = reg;
                reg_contents[reg] = var;
                
                // Load from saved parameter location on stack (adjusted for new frame size)
                int stack_offset = 44 - (param_index * 4);  // $a0 at 44($sp), $a1 at 40($sp), etc.
                emit_comment("Loading parameter " + var + " from stack");
                emit("lw " + reg + ", " + std::to_string(stack_offset) + "($sp)");
                
                return reg;
            }
        }
    }
    
    // Allocate new register
    std::string reg = allocate_temp_register();
    var_to_reg[var] = reg;
    reg_contents[reg] = var;  // Track what's in this register
    
    // If this variable was spilled to stack, reload it
    if (was_spilled) {
        emit_comment("Reloading " + var + " from stack");
        emit("lw " + reg + ", " + std::to_string(spill_stack_offset) + "($sp)");
        spilled_to_stack.erase(var);  // No longer spilled
    }
    
    return reg;
}

std::string MIPSGenerator::allocate_temp_register() {
    // First, try to find an unused register from ALL available registers
    // Check temp registers ($t0-$t9)
    for (const auto& reg : temp_regs) {
        if (reg_contents.find(reg) == reg_contents.end()) {
            return reg;
        }
    }
    
    // Check saved registers ($s0-$s7)
    for (const auto& reg : saved_regs) {
        if (reg_contents.find(reg) == reg_contents.end()) {
            return reg;
        }
    }
    
    // All registers in use - need to spill
    // Find the best candidate to spill: prefer variables whose last use has passed
    // or temporary literals. Use "furthest next use" heuristic.
    std::string best_reg_to_spill = "";
    std::string best_var_to_spill = "";
    int furthest_use = -1;  // Track furthest next use
    
    // Search for a variable that won't be used again soon
    for (const auto& entry : reg_contents) {
        const std::string& reg = entry.first;
        const std::string& var = entry.second;
        
        // Prefer temporary literals (they're usually immediate values that won't be reused)
        if (var.find("temp_literal") == 0) {
            best_reg_to_spill = reg;
            best_var_to_spill = var;
            break;
        }
        
        // Check when this variable will be used next
        int next_use = (var_last_use.find(var) != var_last_use.end()) ? 
                       var_last_use[var] : -1;  // -1 means never used again
        
        // If already used (last use < current), it's a good candidate
        if (next_use < current_instruction_index) {
            best_reg_to_spill = reg;
            best_var_to_spill = var;
            break;  // Perfect candidate - already dead
        }
        
        // Otherwise, prefer spilling the variable whose next use is furthest away
        if (next_use > furthest_use) {
            furthest_use = next_use;
            best_reg_to_spill = reg;
            best_var_to_spill = var;
        }
    }
    
    // If we didn't find a good candidate, just use round-robin on temp registers
    if (best_reg_to_spill.empty()) {
        static int fallback_index = 0;
        best_reg_to_spill = "$t" + std::to_string(fallback_index % 10);
        fallback_index++;
        if (reg_contents.find(best_reg_to_spill) != reg_contents.end()) {
            best_var_to_spill = reg_contents[best_reg_to_spill];
        }
    }
    
    // Spill the chosen register
    if (!best_var_to_spill.empty()) {
        // Save the value to stack before spilling
        emit_comment("Spilling " + best_var_to_spill + " to stack");
        emit("sw " + best_reg_to_spill + ", " + std::to_string(spill_offset) + "($sp)");
        
        // Track where we spilled it
        spilled_to_stack[best_var_to_spill] = spill_offset;
        spill_offset += 4;  // Each spilled variable takes 4 bytes
        
        // Remove from register mappings
        var_to_reg.erase(best_var_to_spill);
        reg_contents.erase(best_reg_to_spill);
    }
    
    return best_reg_to_spill;
}

std::string MIPSGenerator::allocate_saved_register() {
    static int reg_index = 0;
    std::string reg = "$s" + std::to_string(reg_index % 8);
    reg_index++;
    return reg;
}

void MIPSGenerator::emit(const std::string& instruction) {
    output_file << "    " << instruction << std::endl;
}

void MIPSGenerator::emit_comment(const std::string& comment) {
    output_file << "    # " << comment << std::endl;
}

bool MIPSGenerator::is_number(const std::string& str) {
    if (str.empty()) return false;
    size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    return std::all_of(str.begin() + start, str.end(), ::isdigit);
}

bool MIPSGenerator::is_char_literal(const std::string& str) {
    return str.length() >= 3 && str.front() == '\'' && str.back() == '\'';
}

int MIPSGenerator::get_char_value(const std::string& str) {
    if (is_char_literal(str)) {
        return (int)str[1];  // Get ASCII value of character between quotes
    }
    return 0;
}

bool MIPSGenerator::is_temporary(const std::string& var) {
    return var.length() >= 2 && var[0] == 't' && isdigit(var[1]);
}

int MIPSGenerator::get_type_size(const std::string& type) {
    if (type == "char") return 1;
    if (type == "short") return 2;
    if (type == "int") return 4;
    if (type == "long") return 8;
    return 4; // default to int
}

bool MIPSGenerator::is_float_number(const std::string& str) {
    if (str.empty()) return false;
    size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    bool has_dot = false;
    for (size_t i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            if (has_dot) return false;  // Multiple dots
            has_dot = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return has_dot;  // Must have at least one dot
}

void MIPSGenerator::add_string_literal(const std::string& str) {
    if (string_literals.find(str) == string_literals.end()) {
        std::string label = "str_" + std::to_string(string_counter++);
        string_literals[str] = label;
    }
}

void MIPSGenerator::spill_register(const std::string& reg) {
    // TODO: Implement register spilling
}

void MIPSGenerator::load_variable(const std::string& var, const std::string& reg) {
    // TODO: Implement variable loading from stack
}

void MIPSGenerator::store_variable(const std::string& var, const std::string& reg) {
    // TODO: Implement variable storing to stack
}

int MIPSGenerator::get_variable_offset(const std::string& var) {
    if (var_offsets.find(var) == var_offsets.end()) {
        stack_offset += 4;
        var_offsets[var] = -stack_offset;
    }
    return var_offsets[var];
}

int MIPSGenerator::allocate_stack_space(int bytes) {
    stack_offset += bytes;
    return -stack_offset;
}

void MIPSGenerator::free_register(const std::string& reg) {
    // TODO: Implement register freeing
}

bool MIPSGenerator::is_register(const std::string& name) {
    return name.length() >= 2 && name[0] == '$';
}

bool MIPSGenerator::is_label(const std::string& str) {
    return str.length() >= 1 && str[0] == 'L' && isdigit(str[1]);
}

void MIPSGenerator::save_callee_saved_regs() {
    // TODO: Save $s0-$s7 if used
}

void MIPSGenerator::restore_callee_saved_regs() {
    // TODO: Restore $s0-$s7 if used
}

// Helper function to create safe variable names for MIPS (avoid instruction name conflicts)
std::string safe_var_name(const std::string& var) {
    // Check if variable name might conflict with MIPS instructions
    // Single letter names and common instruction mnemonics need prefixing
    if (var.length() <= 2 || 
        var == "add" || var == "sub" || var == "mul" || var == "div" ||
        var == "and" || var == "or" || var == "xor" || var == "sll" ||
        var == "srl" || var == "lw" || var == "sw" || var == "lb" ||
        var == "sb" || var == "beq" || var == "bne" || var == "j" || var == "b") {
        return "var_" + var;
    }
    return var;
}

// Get the actual name to use in MIPS code (handles variable name mapping)
std::string MIPSGenerator::get_mips_var_name(const std::string& var) {
    // Check if this variable has a mapped safe name
    auto it = variable_name_map.find(var);
    if (it != variable_name_map.end()) {
        return it->second;
    }
    return var;
}

void MIPSGenerator::add_global_variable(const std::string& var, int size) {
    if (global_vars.find(var) == global_vars.end()) {
        global_vars.insert(var);
        // Add alignment BEFORE the variable declaration
        data_section.push_back(".align 2");
        // Add to data section with safe name
        std::string safe_name = safe_var_name(var);
        std::string data_line = safe_name + ": .space " + std::to_string(size);
        data_section.push_back(data_line);
        
        // Store mapping from original name to safe name
        if (safe_name != var) {
            variable_name_map[var] = safe_name;
        }
    }
}

void MIPSGenerator::add_static_variable(const std::string& var, int size) {
    if (static_vars.find(var) == static_vars.end()) {
        static_vars.insert(var);
        // Add alignment BEFORE the variable declaration
        data_section.push_back(".align 2");
        std::string safe_name = safe_var_name(var);
        std::string data_line = safe_name + ": .space " + std::to_string(size);
        data_section.push_back(data_line);
        
        // Store mapping
        if (safe_name != var) {
            variable_name_map[var] = safe_name;
        }
    }
}

void MIPSGenerator::set_array_metadata(const std::unordered_map<std::string, std::vector<int>>& dims,
                                        const std::unordered_map<std::string, std::string>& types) {
    this->array_dims = dims;
    this->array_element_types = types;
    
    // Calculate proper array sizes based on dimensions and element type
    for (const auto& entry : dims) {
        const std::string& array_name = entry.first;
        const std::vector<int>& dimensions = entry.second;
        
        // Calculate total elements
        int total_elements = 1;
        for (int dim : dimensions) {
            total_elements *= dim;
        }
        
        // Get element size
        int element_size = 4; // default to int
        if (types.find(array_name) != types.end()) {
            element_size = get_type_size(types.at(array_name));
        }
        
        // Total size in bytes
        array_sizes[array_name] = total_elements * element_size;
        
        // Pre-allocate global arrays in data section
        // Arrays will be global if they're not allocated on stack (checked later)
        // For now, add all arrays to data section; local ones will be allocated on stack instead
        if (global_vars.find(array_name) == global_vars.end() && 
            static_vars.find(array_name) == static_vars.end()) {
            add_global_variable(array_name, total_elements * element_size);
        }
    }
}

void MIPSGenerator::set_variable_types(const std::unordered_map<std::string, std::string>& types) {
    this->variable_types = types;
}

void MIPSGenerator::set_function_names(const std::unordered_set<std::string>& names) {
    this->function_names = names;
}

std::string MIPSGenerator::get_variable_type(const std::string& var) {
    if (variable_types.find(var) != variable_types.end()) {
        return variable_types[var];
    }
    // Check if it's an array element type
    if (array_element_types.find(var) != array_element_types.end()) {
        return array_element_types[var];
    }
    return "int"; // default
}


