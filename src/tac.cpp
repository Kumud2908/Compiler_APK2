#include "tac.h"
#include <sstream>
#include <iomanip>

// TACInstruction implementation
void TACInstruction::print() const {
    std::cout << toString() << std::endl;
}
std::string TACInstruction::toString() const {
    std::stringstream ss;
    
    // Handle labels
    if (!label.empty()) {
        ss << label << ":";
        return ss.str();
    }
    
    // Handle different instruction formats
    if (op == "=") {
        ss << "    " << result << " = " << arg1;
    }
    else if (op == "*=") {  // ← ADD THIS CASE
        ss << "    *" << result << " = " << arg1;
    }
    else if (op == "goto") {
        ss << "    goto " << result;
    }
    else if (op == "if") {
        ss << "    if " << arg1 << " goto " << result;
    }
    else if (op == "ifFalse") {
        ss << "    ifFalse " << arg1 << " goto " << result;
    }
    else if (op == "param") {
        ss << "    param " << arg1;
    }
    else if (op == "call") {
        if (!result.empty()) {
            ss << "    " << result << " = call " << arg1 << ", " << arg2;
        } else {
            ss << "    call " << arg1 << ", " << arg2;
        }
    }
else if (op == "call*") {
    if (!result.empty()) {
        ss << "    " << result << " = call* " << arg1 << ", " << arg2;
    } else {
        ss << "    call* " << arg1 << ", " << arg2;
    }
}
    else if (op == "return") {
        if (!arg1.empty()) {
            ss << "    return " << arg1;
        } else {
            ss << "    return";
        }
    }
    else if (op == "[]") {
        ss << "    " << result << " = " << arg1 << "[" << arg2 << "]";
        
    }
    else if (op == "[]=") {
       
        ss << "    " << result << "[" << arg1 << "] = " << arg2;
    }
    //  Handle unary operators
    else if (op == "unary-" || op == "unary+" || op == "unary!" || op == "unary~") {
        ss << "    " << result << " = " << op.substr(5) << arg1;
    }
    else if (op == "&" && arg2.empty()) {
        ss << "    " << result << " = &" << arg1;
    }
    else if (op == "*" && arg2.empty()) {
        ss << "    " << result << " = *" << arg1;
    }
    else if (op == "!" && arg2.empty()) {
        ss << "    " << result << " = !" << arg1;
    }
    else if (op == ".") {
    ss << "    " << result << " = " << arg1 << "." << arg2;
}
  else if (op == ".=") {
        //  Swap the order to match the storage format
        ss << "    " << result << "." << arg1 << " = " << arg2;
    }
else if (op == "ref") {
    ss << "    " << result << " = &" << arg1;
}
    else {
        // Binary operations
        ss << "    " << result << " = " << arg1 << " " << op << " " << arg2;
    }

    
    return ss.str();
}

// TACGenerator implementation
std::string TACGenerator::new_temp() {
    return "t" + std::to_string(temp_counter++);
}

std::string TACGenerator::new_label() {
    return "L" + std::to_string(label_counter++);
}

void TACGenerator::add_instruction(const TACInstruction& instr) {
    instructions.push_back(instr);
}

void TACGenerator::add_instruction(const std::string& op, const std::string& arg1,
                                   const std::string& arg2, const std::string& result) {
    instructions.push_back(TACInstruction(op, arg1, arg2, result));
}

void TACGenerator::add_label(const std::string& label) {
    instructions.push_back(TACInstruction("", "", "", "", label));
}

void TACGenerator::generate_load(const std::string &target, const std::string &addr) {
    add_instruction("*", addr, "", target);  
}

void TACGenerator::generate_load(const std::string &target, const std::string &addr, int element_size) {
    TACInstruction instr("*", addr, "", target);
    instr.comment = "size=" + std::to_string(element_size);
    instructions.push_back(instr);
}

void TACGenerator::generate_store(const std::string& address, const std::string& value) {
    add_instruction("*=", value, "", address);
}

void TACGenerator::generate_store(const std::string& address, const std::string& value, int element_size) {
    TACInstruction instr("*=", value, "", address);
    instr.comment = "size=" + std::to_string(element_size);
    instructions.push_back(instr);
}

void TACGenerator::generate_address_of(const std::string &var, const std::string &target) {
    add_instruction("&", var, "", target);  
}
void TACGenerator::generate_assignment(const std::string& dest, const std::string& src) {
    add_instruction("=", src, "", dest);
}

void TACGenerator::generate_binary_op(const std::string& op, const std::string& arg1,
                                      const std::string& arg2, const std::string& result) {
    add_instruction(op, arg1, arg2, result);
}

void TACGenerator::generate_unary_op(const std::string& op, const std::string& arg,
                                     const std::string& result) {
    add_instruction(op, arg, "", result);
}

void TACGenerator::generate_goto(const std::string& label) {
    add_instruction("goto", "", "", label);
}

void TACGenerator::generate_if_goto(const std::string& condition, const std::string& label) {
    add_instruction("if", condition, "", label);
}

void TACGenerator::generate_if_false_goto(const std::string& condition, const std::string& label) {
    add_instruction("ifFalse", condition, "", label);
}

void TACGenerator::generate_param(const std::string& param) {
    add_instruction("param", param, "", "");
}

void TACGenerator::generate_call(const std::string& func, int num_params, const std::string& result) {
    add_instruction("call", func, std::to_string(num_params), result);
}

void TACGenerator::generate_return(const std::string& value) {
    add_instruction("return", value, "", "");
}

void TACGenerator::generate_array_access(const std::string& array, const std::string& index,
                                         const std::string& result) {
    // result = array[index]
    add_instruction("[]", array, index, result);
}

void TACGenerator::generate_array_store(const std::string& array, const std::string& index,
                                        const std::string& value) {
    // array[index] = value
    add_instruction("[]=", index, value, array);
}

void TACGenerator::print() const {
    std::cout << "\n=== THREE ADDRESS CODE ===" << std::endl;
    for (const auto& instr : instructions) {
        instr.print();
    }
    std::cout << "\nTotal instructions: " << instructions.size() << std::endl;
}

void TACGenerator::generate_struct_load(const std::string& structVar,
                                        const std::string& member,
                                        const std::string& result) {
    // result = structVar.member
    add_instruction(".", structVar, member, result);
}

void TACGenerator::generate_struct_store(const std::string& structVar,
                                         const std::string& member,
                                         const std::string& value) {
    // structVar.member = value
    add_instruction(".=", member, value, structVar);
}
void TACGenerator::generate_indirect_call(const std::string& func_ptr, int num_params, const std::string& result) {
    add_instruction("call*", func_ptr, std::to_string(num_params), result);
}
void TACGenerator::generate_reference_decl(const std::string& ref_name, const std::string& target_var) {
    // Create reference: ref_name becomes alias for target_var
    // In TAC, we'll treat references as addresses that are automatically dereferenced
    add_instruction("ref", target_var, "", ref_name);
}