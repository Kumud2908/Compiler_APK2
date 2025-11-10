#ifndef TAC_H
#define TAC_H

#include <string>
#include <vector>
#include <iostream>

// Three-Address Code Instruction
class TACInstruction {
public:
    std::string op;        // Operation: +, -, *, /, =, etc.
    std::string arg1;      // First argument
    std::string arg2;      // Second argument
    std::string result;    // Result
    std::string label;     // Label for jumps
     std::string comment; // ✅ NEW: for comments

    TACInstruction(const std::string& operation = "", 
                   const std::string& a1 = "", 
                   const std::string& a2 = "", 
                   const std::string& res = "",
                   const std::string& lbl = "")
        : op(operation), arg1(a1), arg2(a2), result(res), label(lbl) {}
    
    void print() const;
    std::string toString() const;
};

// Three-Address Code Generator
class TACGenerator {
private:
    std::vector<TACInstruction> instructions;
    int temp_counter;
    int label_counter;
    
public:
    TACGenerator() : temp_counter(0), label_counter(0) {}


   // NEW: Add comment to TAC
    void add_comment(const std::string& comment); 
    
    
    // Temporary variable generation
    std::string new_temp();
    
    // Label generation
    std::string new_label();
    
    // Add instruction
    void add_instruction(const TACInstruction& instr);
    void add_instruction(const std::string& op, const std::string& arg1,
                        const std::string& arg2, const std::string& result);
    
    // Label insertion
    void add_label(const std::string& label);
    
    // Assignment
    void generate_assignment(const std::string& dest, const std::string& src);
    
    // Binary operations
    void generate_binary_op(const std::string& op, const std::string& arg1,
                           const std::string& arg2, const std::string& result);
    
    // Unary operations
    void generate_unary_op(const std::string& op, const std::string& arg,
                          const std::string& result);
    
    // Jumps
    void generate_goto(const std::string& label);
    void generate_if_goto(const std::string& condition, const std::string& label);
    void generate_if_false_goto(const std::string& condition, const std::string& label);
    
    // Function calls
    void generate_param(const std::string& param);
    void generate_call(const std::string& func, int num_params, const std::string& result = "");
    void generate_return(const std::string& value = "");
    
    // Array access
    void generate_array_access(const std::string& array, const std::string& index,
                              const std::string& result);
    void generate_array_store(const std::string& array, const std::string& index,
                             const std::string& value);


    void generate_load(const std::string &target, const std::string &addr);
    void generate_load(const std::string &target, const std::string &addr, int element_size);
    void generate_store(const std::string& address, const std::string& value);
    void generate_store(const std::string& address, const std::string& value, int element_size);
    void generate_address_of(const std::string &var, const std::string &target) ;
     void generate_struct_load(const std::string &target, const std::string &base, const std::string &member);
    void generate_struct_store(const std::string &base, const std::string &member, const std::string &value);
// Add to TACGenerator class:
void generate_reference_decl(const std::string& ref_name, const std::string& target_var);
void generate_indirect_call(const std::string& func_ptr, int num_params, const std::string& result = "");
    
    // Print all instructions
    void print() const;
    
    // Get instructions
    const std::vector<TACInstruction>& get_instructions() const { return instructions; }
    
    // Clear instructions
    void clear() { instructions.clear(); temp_counter = 0; label_counter = 0; }
    
};

#endif // TAC_H