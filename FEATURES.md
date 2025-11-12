# Compiler Features Documentation

## Table of Contents
1. [MIPS Code Generation](#mips-code-generation)
2. [Function Pointers](#function-pointers)
3. [Register Allocation](#register-allocation)
4. [Memory Management](#memory-management)
5. [Control Flow](#control-flow)
6. [Type System](#type-system)

---

## MIPS Code Generation

### Overview
The compiler generates SPIM-compatible MIPS assembly code from Three-Address Code (TAC). All generated code can be executed on the SPIM simulator.

### Architecture
```
TAC Instruction → MIPS Generator → MIPS Assembly
                     ↓
              Register Allocator
                     ↓
              Stack Manager
                     ↓
              Label Resolver
```

### Supported Instructions

#### Arithmetic Operations
```mips
add  $t0, $t1, $t2    # Addition
sub  $t0, $t1, $t2    # Subtraction
mul  $t0, $t1, $t2    # Multiplication
div  $t1, $t2         # Division (result in $lo, remainder in $hi)
mflo $t0              # Get quotient
mfhi $t0              # Get remainder
```

#### Logical Operations
```mips
and  $t0, $t1, $t2    # Bitwise AND
or   $t0, $t1, $t2    # Bitwise OR
xor  $t0, $t1, $t2    # Bitwise XOR
nor  $t0, $t1, $t2    # Bitwise NOR
sll  $t0, $t1, 2      # Shift left logical
srl  $t0, $t1, 2      # Shift right logical
sra  $t0, $t1, 2      # Shift right arithmetic
```

#### Memory Operations
```mips
lw   $t0, 0($t1)      # Load word
sw   $t0, 0($t1)      # Store word
lb   $t0, 0($t1)      # Load byte
sb   $t0, 0($t1)      # Store byte
lh   $t0, 0($t1)      # Load halfword
sh   $t0, 0($t1)      # Store halfword
la   $t0, label       # Load address
```

#### Control Flow
```mips
beq  $t0, $t1, label  # Branch if equal
bne  $t0, $t1, label  # Branch if not equal
blt  $t0, $t1, label  # Branch if less than
ble  $t0, $t1, label  # Branch if less than or equal
bgt  $t0, $t1, label  # Branch if greater than
bge  $t0, $t1, label  # Branch if greater than or equal
j    label            # Jump
jal  label            # Jump and link (function call)
jalr $t0              # Jump and link register (indirect call)
jr   $ra              # Jump register (return)
```

---

## Function Pointers

### Implementation

#### 1. Function Pointer Declaration
```c
int (*func_ptr)(int, int);
```

**TAC Generated:**
```
func_ptr = declaration
```

**MIPS Generated:**
```mips
# Space allocated in data section or stack
```

#### 2. Function Pointer Assignment
```c
func_ptr = add;
```

**TAC Generated:**
```
operation = add
```

**MIPS Generated:**
```mips
la $t0, func_add      # Load address of function
# Store in variable's location
```

#### 3. Function Pointer Array
```c
int (*ops[2])(int, int) = {add, sub};
```

**TAC Generated:**
```
t0 = &ops
*t0 = add
t1 = t0 + 4
*t1 = sub
```

**MIPS Generated:**
```mips
la   $t0, ops         # Get array address
la   $t1, func_add    # Load function address
sw   $t1, 0($t0)      # Store in array[0]
la   $t2, func_sub    # Load function address
sw   $t2, 4($t0)      # Store in array[1]
```

#### 4. Indirect Function Call
```c
result = func_ptr(5, 2);
```

**TAC Generated:**
```
param 5
param 2
t0 = call* func_ptr, 2
```

**MIPS Generated:**
```mips
lw   $t0, func_ptr    # Load function pointer
li   $a0, 5           # First argument
li   $a1, 2           # Second argument
jalr $t0              # Indirect call
move $t1, $v0         # Get return value
```

### Function Pointer Features
- ✅ Function pointer variables
- ✅ Function pointer arrays
- ✅ Function pointer assignment
- ✅ Indirect function calls via `jalr`
- ✅ Return value handling
- ✅ Multiple parameters support
- ⚠️ Function pointers returning function pointers (complex cases not fully supported)

---

## Register Allocation

### Available Registers

#### Temporary Registers (Caller-saved)
```
$t0-$t9  (10 registers)
```
- Used for intermediate computations
- Not preserved across function calls
- First choice for temporary variables

#### Saved Registers (Callee-saved)
```
$s0-$s7  (8 registers)
```
- Preserved across function calls
- Used when temporaries are exhausted
- Saved/restored in function prologue/epilogue

#### Argument Registers
```
$a0-$a3  (4 registers)
```
- Used for passing first 4 function arguments
- Additional arguments passed on stack

#### Return Value Registers
```
$v0-$v1  (2 registers)
```
- $v0: Primary return value
- $v1: Secondary return value (not currently used)

### Allocation Strategy

#### 1. Variable Assignment
```c
int x = 10;
```

**Process:**
1. Check if variable already has a register → Use it
2. Look for free temporary register → Allocate
3. Look for free saved register → Allocate
4. All registers full → Spill least-recently-used

**MIPS:**
```mips
li $t0, 10           # Allocate $t0 for x
```

#### 2. Register Spilling
When all registers are in use:

**TAC:**
```
t0 = a + b
t1 = c + d
... (many operations)
t20 = x + y  # More temps than available registers
```

**MIPS:**
```mips
# Spill $t0 to stack
sw   $t0, 0($sp)
# Use $t0 for new variable
add  $t0, $t1, $t2
```

#### 3. Register Reloading
When spilled variable is needed again:

**MIPS:**
```mips
# Reload from stack
lw   $t0, 0($sp)
add  $t1, $t0, $t2
```

### Optimization Techniques
- **Live Range Analysis**: Track when variables are last used
- **Register Reuse**: Reuse registers from dead variables
- **Spill Minimization**: Prefer spilling variables not used soon
- **Caller/Callee Save**: Use appropriate register class

---

## Memory Management

### Stack Layout

```
High Address
┌─────────────────┐
│  Arguments 5+   │  (Additional args beyond $a0-$a3)
├─────────────────┤
│  Return Addr    │  $ra (saved)
├─────────────────┤
│  Frame Pointer  │  $fp (saved)
├─────────────────┤
│  Args 0-3       │  $a0-$a3 (saved)
├─────────────────┤
│  Saved Regs     │  $s0-$s7
├─────────────────┤
│  Spilled Vars   │  Temporary storage
├─────────────────┤
│  Local Vars     │  Function locals
└─────────────────┘
Low Address (Current $sp)
```

### Function Prologue
```mips
func_name:
    addi $sp, $sp, -56    # Allocate stack frame
    sw   $ra, 52($sp)     # Save return address
    sw   $fp, 48($sp)     # Save frame pointer
    addi $fp, $sp, 56     # Set new frame pointer
    sw   $a0, 44($sp)     # Save arg 0
    sw   $a1, 40($sp)     # Save arg 1
    sw   $a2, 36($sp)     # Save arg 2
    sw   $a3, 32($sp)     # Save arg 3
    sw   $s0, 28($sp)     # Save $s0
    # ... save other $s registers
```

### Function Epilogue
```mips
    # ... restore $s registers
    lw   $s0, 28($sp)
    lw   $fp, 48($sp)     # Restore frame pointer
    lw   $ra, 52($sp)     # Restore return address
    addi $sp, $sp, 56     # Deallocate stack frame
    jr   $ra              # Return
```

### Data Section

```mips
.data
.align 2                  # Word alignment
str_0: .asciiz "Hello\n"  # String literal
.align 2
global_var: .word 0       # Global variable
.align 2
array: .space 40          # Array (10 integers)
```

### Variable Name Mapping

The compiler automatically handles MIPS instruction conflicts:

```c
int a = 5;    // 'a' conflicts with 'a' (pseudo-instruction)
int b = 10;   // 'b' conflicts with 'b' (branch)
```

**MIPS Generated:**
```mips
.data
var_a: .word 5    # Prefixed with 'var_'
var_b: .word 10   # Prefixed with 'var_'
```

---

## Control Flow

### If-Else Statements

**C Code:**
```c
if (x > 5) {
    y = 10;
} else {
    y = 20;
}
```

**MIPS Generated:**
```mips
    lw   $t0, x
    li   $t1, 5
    ble  $t0, $t1, else_label
    li   $t2, 10
    sw   $t2, y
    j    end_if
else_label:
    li   $t2, 20
    sw   $t2, y
end_if:
```

### While Loops

**C Code:**
```c
while (i < 10) {
    sum += i;
    i++;
}
```

**MIPS Generated:**
```mips
while_start:
    lw   $t0, i
    li   $t1, 10
    bge  $t0, $t1, while_end
    lw   $t2, sum
    add  $t2, $t2, $t0
    sw   $t2, sum
    addi $t0, $t0, 1
    sw   $t0, i
    j    while_start
while_end:
```

### Switch Statements

**C Code:**
```c
switch(x) {
    case 1: y = 10; break;
    case 2: y = 20; break;
    default: y = 0;
}
```

**MIPS Generated:**
```mips
    lw   $t0, x
    li   $t1, 1
    beq  $t0, $t1, case_1
    li   $t1, 2
    beq  $t0, $t1, case_2
    j    default_case
case_1:
    li   $t2, 10
    sw   $t2, y
    j    switch_end
case_2:
    li   $t2, 20
    sw   $t2, y
    j    switch_end
default_case:
    sw   $zero, y
switch_end:
```

---

## Type System

### Supported Types

| Type           | Size (bytes) | MIPS Load | MIPS Store |
|----------------|--------------|-----------|------------|
| char           | 1            | lb        | sb         |
| short          | 2            | lh        | sh         |
| int            | 4            | lw        | sw         |
| long           | 4            | lw        | sw         |
| pointer        | 4            | lw        | sw         |
| float*         | 4            | lw        | sw         |
| double*        | 8            | lw/lw     | sw/sw      |

*Note: Float/double use integer instructions currently (FPU not implemented)

### Type Conversions

#### Implicit Conversions
```c
char c = 65;
int i = c;    // char → int (sign extension)
```

**MIPS:**
```mips
lb   $t0, c         # Load byte (sign-extended)
sw   $t0, i         # Store as int
```

#### Explicit Conversions
```c
int i = 1000;
char c = (char)i;   // Truncate to 8 bits
```

**MIPS:**
```mips
lw   $t0, i
andi $t0, $t0, 0xFF  # Mask to 8 bits
sb   $t0, c
```

### Array-to-Pointer Decay

```c
int arr[10];
int *ptr = arr;  // Implicit conversion
```

**Semantic Analysis:** Allows assignment of array type to pointer type

**MIPS:**
```mips
la   $t0, arr      # Load array address
sw   $t0, ptr      # Store as pointer
```

---

## Printf Support

### Format Specifiers

| Specifier | Type    | Implementation |
|-----------|---------|----------------|
| %d        | int     | syscall 1      |
| %c        | char    | syscall 11     |
| %.2f      | float   | Integer + formatting |
| %s        | string  | Character loop |

### Example

**C Code:**
```c
printf("Value: %d\n", x);
```

**MIPS Generated:**
```mips
# Print "Value: "
li   $v0, 11
li   $a0, 86      # 'V'
syscall
li   $v0, 11
li   $a0, 97      # 'a'
syscall
# ... (more characters)

# Print integer
li   $v0, 1       # print_int syscall
lw   $a0, x
syscall

# Print newline
li   $v0, 11
li   $a0, 10      # '\n'
syscall
```

---

## Error Handling

### Compilation Errors
- Syntax errors with line numbers
- Semantic errors (type mismatches, undefined variables)
- Symbol redeclaration errors
- Invalid control flow (break outside loop)

### Runtime Protections
- Stack overflow protection (fixed stack size)
- Register spilling prevents register exhaustion
- Proper function return handling
- Memory alignment enforcement

---

## Performance Characteristics

### Time Complexity
- **Lexing**: O(n) where n = source length
- **Parsing**: O(n)
- **Semantic Analysis**: O(n)
- **TAC Generation**: O(n)
- **MIPS Generation**: O(m) where m = TAC instructions
- **Overall**: O(n + m) ≈ O(n)

### Space Complexity
- **Symbol Table**: O(v) where v = number of variables
- **AST**: O(n)
- **TAC**: O(m)
- **MIPS Code**: O(m)
- **Register Allocation**: O(r) where r = register count (constant)

### Optimization Opportunities
- Constant folding
- Dead code elimination
- Common subexpression elimination
- Register allocation (graph coloring)
- Peephole optimization
- Loop unrolling

---

## Limitations & Future Work

### Current Limitations
1. **Float Arithmetic**: Uses integer instructions (no FPU)
2. **Array Initialization**: Some initializer values not properly loaded
3. **No Optimization**: Code is unoptimized
4. **Single Translation Unit**: No linking support
5. **Limited Standard Library**: Only printf supported

### Planned Enhancements
1. **FPU Support**: Use .s/.d instructions for floats/doubles
2. **Optimization Passes**: Implement standard optimizations
3. **Better Register Allocation**: Graph coloring algorithm
4. **Linker Support**: Multiple file compilation
5. **Expanded Library**: More standard functions

---

*Last Updated: November 12, 2025*
