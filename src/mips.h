#ifndef MIPS_H
#define MIPS_H

#include "tac.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

class MIPSGenerator {
private:
    std::vector<TACInstruction> tac_instructions;
    std::ofstream output_file;
    
    // ===== Register Management =====
    std::unordered_map<std::string, std::string> var_to_reg;  // Variable -> Register mapping
    std::vector<std::string> temp_regs;                        // $t0-$t9 available
    std::vector<std::string> saved_regs;                       // $s0-$s7 available
    std::unordered_set<std::string> used_regs;                // Registers currently in use
    std::unordered_map<std::string, std::string> reg_contents; // Register -> Variable
    std::unordered_map<std::string, int> spilled_to_stack;    // Variable -> stack offset (for spilled vars)
    
    // ===== Memory Management =====
    int stack_offset;                                          // Current stack pointer offset
    int spill_offset;                                          // Offset for spilled variables
    std::unordered_map<std::string, int> var_offsets;         // Variable -> Stack offset
    std::unordered_map<std::string, int> local_var_size;      // Variable -> Size in bytes
    std::unordered_map<std::string, int> array_sizes;         // Array name -> Total size
    std::unordered_map<std::string, std::vector<int>> array_dims; // Array -> dimensions
    std::unordered_map<std::string, std::string> array_element_types; // Array -> element type (int, char, etc)
    std::unordered_map<std::string, std::string> variable_types; // Variable -> type (int, char, etc)
    
    // ===== Function Management =====
    std::string current_function;
    int frame_size;                                            // Current function's stack frame
    std::vector<std::string> param_list;                       // Parameters for current call
    std::vector<std::string> param_regs;                       // Saved registers holding param values
    std::vector<std::string> current_func_params;              // Parameters of current function
    bool in_function;                                          // Currently in function body
    
    // ===== Optimization tracking =====
    std::string last_div_reg1;                                 // Last dividend register
    std::string last_div_reg2;                                 // Last divisor register
    int current_instruction_index;                             // Current TAC instruction being processed
    
    // ===== Liveness Analysis =====
    std::unordered_map<std::string, int> var_last_use;        // Variable -> last instruction index where used
    std::unordered_set<std::string> dead_after_use;            // Variables that can be freed after current instruction
    
    // ===== Label Tracking =====
    std::unordered_set<std::string> defined_labels;
    std::unordered_set<std::string> function_names;  // Function names for proper label handling
    
    // ===== Data Section =====
    std::vector<std::string> data_section;                     // Global/static data
    std::unordered_map<std::string, std::string> string_literals; // String -> Label
    std::unordered_map<std::string, std::string> variable_name_map; // Original var name -> Safe MIPS name
    int string_counter;
    std::unordered_set<std::string> static_vars;               // Static variable names
    std::unordered_set<std::string> global_vars;               // Global variable names
    
public:
    MIPSGenerator(const std::vector<TACInstruction>& tac);
    void generate(const std::string& output_filename);
    void set_array_metadata(const std::unordered_map<std::string, std::vector<int>>& dims,
                            const std::unordered_map<std::string, std::string>& types);
    void set_variable_types(const std::unordered_map<std::string, std::string>& types);
    void set_function_names(const std::unordered_set<std::string>& names);
    
private:
    // ===== Core Generation =====
    void emit_data_section();
    void emit_text_section();
    void translate_instruction(const TACInstruction& instr);
    void compute_liveness();  // NEW: Analyze when variables are last used
    void free_dead_registers();  // NEW: Free registers for dead variables
    
    // ===== Register Allocation =====
    std::string get_register(const std::string& var);
    void free_register(const std::string& reg);
    std::string allocate_temp_register();
    std::string allocate_saved_register();
    void spill_register(const std::string& reg);
    void load_to_register(const std::string& var, const std::string& reg);
    void save_from_register(const std::string& var, const std::string& reg);
    bool is_register(const std::string& name);
    
    // ===== Memory Operations =====
    void load_variable(const std::string& var, const std::string& reg);
    void store_variable(const std::string& var, const std::string& reg);
    int get_variable_offset(const std::string& var);
    int allocate_stack_space(int bytes);
    
    // ===== Instruction Translation =====
    void translate_assignment(const TACInstruction& instr);
    void translate_binary_op(const TACInstruction& instr);
    void translate_unary_op(const TACInstruction& instr);
    void translate_relational_op(const TACInstruction& instr);
    void translate_logical_op(const TACInstruction& instr);
    void translate_bitwise_op(const TACInstruction& instr);
    void translate_shift_op(const TACInstruction& instr);
    void translate_goto(const TACInstruction& instr);
    void translate_conditional_jump(const TACInstruction& instr);
    void translate_label(const TACInstruction& instr);
    void translate_function_label(const TACInstruction& instr);
    void translate_param(const TACInstruction& instr);
    void translate_call(const TACInstruction& instr);
    void translate_indirect_call(const TACInstruction& instr);
    void translate_return(const TACInstruction& instr);
    void translate_array_access(const TACInstruction& instr);
    void translate_pointer_op(const TACInstruction& instr);
    void translate_address_of(const TACInstruction& instr);
    void translate_dereference(const TACInstruction& instr);
    void translate_pointer_store(const TACInstruction& instr);
    
    // ===== Function Handling =====
    void emit_function_prologue(const std::string& func_name);
    void emit_function_epilogue();
    void pass_arguments(int num_params);
    void save_callee_saved_regs();
    void restore_callee_saved_regs();
    
    // ===== Helper Functions =====
    void emit(const std::string& instruction);
    void emit_comment(const std::string& comment);
    bool is_number(const std::string& str);
    bool is_float_number(const std::string& str);
    bool is_char_literal(const std::string& str);
    int get_char_value(const std::string& str);
    bool is_temporary(const std::string& var);
    bool is_label(const std::string& str);
    std::string get_mips_op(const std::string& tac_op);
    int get_type_size(const std::string& type);
    
    // ===== Data Section Helpers =====
    void add_string_literal(const std::string& str);
    void add_global_variable(const std::string& var, int size);
    void add_static_variable(const std::string& var, int size);
    std::string get_variable_type(const std::string& var);
    std::string get_mips_var_name(const std::string& var);
    
    // ===== Special Instruction Handlers =====
    void handle_printf();
    void handle_scanf();
    void handle_syscall(const std::string& func_name);
    void print_literal_string(const std::string& text);

    bool is_temp_register(const std::string& reg) const;
    bool is_saved_register(const std::string& reg) const;
    void clear_temp_registers();
};

#endif // MIPS_H
