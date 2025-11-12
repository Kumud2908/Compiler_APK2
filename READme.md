# 🎯 C/C++ Compiler with MIPS Assembly Generation

A comprehensive C/C++ compiler implemented as part o* ✅ **Pointers**
  * Pointer declaration and initialization
  * Pointer dereferencing (`*ptr`)
  * Address-of operator (`&var`)
  * Pointer arithmetic (add, subtract)
  * Multi-level pointers (`**`, `***`, etc.)
  * Array-to-pointer decay (implicit conversion)
  * **Function pointers** with indirect calls
  * Function pointer assignment and invocationmpiler design project. This compiler performs a complete compilation pipeline including lexical analysis, syntax parsing, semantic analysis, intermediate code generation (Three-Address Code), and **MIPS assembly code generation** with SPIM simulator support for a substantial subset of the C/C++ programming language.

## 📋 Table of Contents
- [Features](#-features-implemented)
- [Architecture](#-compiler-architecture)
- [Installation](#-installation--usage)
- [MIPS Code Generation](#-mips-assembly-generation)
- [Examples](#-example-programs-tested)
- [Testing Results](#-testing-results)
- [Known Issues](#-known-issues--limitations)
- [Future Work](#-future-enhancements)

---

## 🚀 Features Implemented


### 🔤 Lexical Analysis
* ✅ Tokenization of C source code
* ✅ Recognition of all C keywords (`int`, `if`, `while`, `struct`, etc.)
* ✅ Support for identifiers, constants, operators.
* ✅ Preprocessor directive handling (`#include`, `#define`)
* ✅ String and character literal processing

### 🌳 Syntax Analysis (Parser)
* ✅ Complete Abstract Syntax Tree (AST) generation
* ✅ AST visualization via DOT file generation
* ✅ Detailed syntax error reporting
* ✅ Support for complex nested expressions and statements

### 🧠 Semantic Analysis
* ✅ **Symbol Table Management**
  * Multi-scope symbol table with scope stack
  * Function scope tracking
  * Variable, function, struct, union, enum, and typedef tracking
* ✅ **Type Checking**
  * Expression type inference
  * Assignment type compatibility
  * Function parameter type validation
  * Return statement type checking
  * Implicit type conversions (arithmetic promotions)
* ✅ **Error Detection**
  * Undefined variable/function usage
  * Type mismatch in assignments and operations
  * Redeclaration errors
  * Invalid break/continue usage (outside loops)
  * Missing return statements in non-void functions
  * Goto label validation (undefined/unused labels)
* ✅ **Advanced Validations**
  * Division by zero detection (constant expressions)
  * Recursion detection and tracking
  * Array bounds checking (where statically determinable)
  * Function call argument count validation
  * Pointer operation safety checks

### 🎯 Control Flow Constructs
* ✅ **Conditional Statements**
  * `if`, `if-else`, nested `if-else-if` chains
  * Ternary operator (`? :`)
* ✅ **Loops**
  * `for` loops (with init, condition, increment)
  * `while` loops
  * `do-while` loops
  * Nested loops (multi-dimensional)
* ✅ **Jump Statements**
  * `break` (with proper loop/switch validation)
  * `continue` (with proper loop validation)
  * `goto` with labels (forward and backward jumps)
  * `return` statements (with type validation)
* ✅ **Switch-Case**
  * `switch` statements with multiple `case` blocks
  * `default` case handling
  * Fall-through behavior support

### 🔢 Operators & Expressions
* ✅ **Arithmetic Operators**: `+`, `-`, `*`, `/`, `%`
* ✅ **Relational Operators**: `<`, `>`, `<=`, `>=`, `==`, `!=`
* ✅ **Logical Operators**: `&&`, `||`, `!`
* ✅ **Bitwise Operators**: `&`, `|`, `^`, `~`, `<<`, `>>`
* ✅ **Assignment Operators**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, etc.
* ✅ **Increment/Decrement**: `++`, `--` (both prefix and postfix)
* ✅ **Pointer Operators**: `*` (dereference), `&` (address-of)
* ✅ **Member Access**: `.` (struct member), `->` (pointer to struct)
* ✅ **Array Subscript**: `[]` (with multi-dimensional support)
* ✅ **Ternary Operator**: `? :`
* ✅ **Comma Operator**: `,`

### 📦 Data Types & Structures

#### Basic Types
* ✅ `int`, `char`, `float`, `double`
* ✅ `short`, `long`, `long long`
* ✅ `signed` and `unsigned` variants
* ✅ `void` (for functions)

#### Complex Types
* ✅ **Arrays**
  * Single-dimensional arrays
  * Multi-dimensional arrays (2D, 3D, etc.)
  * Array initialization with nested braces
  * Flattened index calculation for multi-dimensional access
* ✅ **Pointers**
  * Pointer declaration and initialization
  * Pointer dereferencing (`*ptr`)
  * Address-of operator (`&var`)
  * Pointer arithmetic
  * Multi-level pointers (`**`, `***`, etc.)
* ✅ **Structures (`struct`)**
  * Structure definition and member declaration
  * Structure variable declaration
  * Member access (`.` operator)
  * Pointer to structure (`->` operator)
  * Nested structures
* ✅ **Unions (`union`)**
  * Union definition and usage
  * Member access validation
* ✅ **Enumerations (`enum`)**
  * Enum definition with constants
  * Automatic and explicit value assignment
* ✅ **Typedef**
  * User-defined type aliases
  * Typedef resolution in type checking

#### Storage Classes
* ✅ `static` variables (function-scoped)
* ✅ `extern` declarations
* ✅ Default storage class handling

### 🔧 Functions

* ✅ **Function Definitions**
  * Return type specification
  * Parameter lists with types
  * Function body with local scope
* ✅ **Function Declarations (Prototypes)**
  * Forward declarations
  * Parameter type checking
* ✅ **Function Calls**
  * Argument passing
  * Return value handling
  * Parameter count validation
  * Parameter type checking
* ✅ **Recursive Functions**
  * Direct recursion support
  * Recursion detection and tracking
* ✅ **Variadic Functions**
  * `...` parameter support (parsing only)
  * `printf`, `scanf` with variable arguments

### 🧱 Three-Address Code (TAC) Generation

The compiler generates optimized intermediate code (TAC) for:

* ✅ **Expressions**
  * Binary operations with temporary variable allocation
  * Unary operations (negation, logical NOT, bitwise NOT)
  * Complex nested expressions
  * Short-circuit evaluation for logical operators
* ✅ **Assignments**
  * Simple variable assignments
  * Compound assignments (`+=`, `-=`, etc.)
  * Array element assignments
  * Structure member assignments
  * Multi-dimensional array assignments with index flattening
* ✅ **Control Flow**
  * Conditional jumps (`if`, `ifFalse`)
  * Unconditional jumps (`goto`)
  * Label generation and placement
  * Loop constructs with proper jump targets
* ✅ **Arrays**
  * Single-dimensional array access (`a[i]`)
  * Multi-dimensional array access with flattened indexing (`a[i][j]` → `a[i*cols + j]`)
  * Array initialization (including nested initializers)
* ✅ **Structures**
  * Member load operations (`result = struct.member`)
  * Member store operations (`struct.member = value`)
* ✅ **Functions**
  * Parameter passing (`param` instructions)
  * Function calls (`call` instruction)
  * **Indirect function calls** (`call*` for function pointers)
  * Return value handling
  * Return statements
* ✅ **Pointers**
  * Address-of operations (`&var`)
  * Dereference operations (`*ptr`)
  * Pointer arithmetic
  * Pointer store operations (`*ptr = value`)
  * Function pointer handling

#### TAC Features
* ✅ Temporary variable allocation and management
* ✅ Label generation for control flow
* ✅ TAC output file generation (`output.tac`)
* ✅ Human-readable TAC formatting
* ✅ Instruction counting and statistics

### 📤 Output Generation

* ✅ **Abstract Syntax Tree (AST)**
  * Tree structure visualization in console
  * DOT file generation for Graphviz
  * Node-level information (name, lexeme, line number)
* ✅ **Symbol Table**
  * Scope-wise symbol listing
  * Symbol type and attributes
  * Function signatures with parameters
  * Struct/Union member details
* ✅ **TAC File**
  * Formatted intermediate code output
  * Instruction-level comments (where applicable)
* ✅ **MIPS Assembly Code**
  * Complete MIPS assembly generation (`output.s`)
  * SPIM-compatible output format
  * Function prologue/epilogue generation
  * Register allocation and spilling
  * Data section with proper alignment

### 🛡️ Error Handling

* ✅ **Syntax Errors**
  * Detailed error messages with line numbers
  * Error recovery for continued parsing
* ✅ **Semantic Errors**
  * Type mismatch detection
  * Undefined symbol usage
  * Redeclaration errors
  * Invalid operations (e.g., break outside loop)
  * Compilation halts if semantic errors found
* ✅ **Warnings**
  * Unused variables (optional)
  * Type conversion warnings
  * Compilation continues with warnings

---

## 🖥️ MIPS Assembly Generation

### Overview
The compiler generates complete MIPS assembly code that can be executed on the SPIM simulator. The MIPS generator (`mips.h/cpp`) translates TAC instructions into MIPS assembly with advanced features:

### Features

#### Register Management
* ✅ **Dynamic Register Allocation**
  * 10 temporary registers (`$t0-$t9`)
  * 8 saved registers (`$s0-$s7`)
  * Intelligent register allocation for variables and temporaries
  * Register spilling to stack when registers are exhausted
  * Register reuse optimization

#### Function Support
* ✅ **Function Call Convention**
  * Proper function prologue/epilogue generation
  * Stack frame management
  * Argument passing via `$a0-$a3` registers
  * Additional arguments passed on stack
  * Return values via `$v0`
  * Callee-saved register preservation
  * Return address (`$ra`) and frame pointer (`$fp`) handling

* ✅ **Function Pointers**
  * Function address loading with `la` instruction
  * Indirect calls using `jalr` (jump and link register)
  * Function pointer arrays and assignment
  * Proper function label prefixing (`func_` prefix)

#### Memory Operations
* ✅ **Data Section Generation**
  * Global variable allocation
  * String literal storage
  * Array space allocation
  * Proper `.align 2` directives for word alignment
  * Static variable initialization

* ✅ **Memory Access**
  * Load word (`lw`), half-word (`lh`), byte (`lb`)
  * Store word (`sw`), half-word (`sh`), byte (`sb`)
  * Array indexing with offset calculation
  * Multi-dimensional array flattening
  * Pointer dereferencing

#### Control Flow
* ✅ **Conditional Branches**
  * `beq`, `bne`, `blt`, `ble`, `bgt`, `bge`
  * Short-circuit evaluation for logical operators
  * Proper label generation and resolution

* ✅ **Unconditional Jumps**
  * `j` (jump) for goto statements
  * `jal` (jump and link) for function calls
  * `jalr` (jump and link register) for function pointers
  * `jr $ra` for function returns

#### Arithmetic & Logic
* ✅ **Integer Operations**
  * Addition (`add`, `addi`), Subtraction (`sub`)
  * Multiplication (`mul`), Division (`div`)
  * Modulo (`div` + `mfhi`)
  * Bitwise AND, OR, XOR, NOT
  * Shift left/right (`sll`, `srl`, `sra`)

* ✅ **Comparison Operations**
  * Set less than (`slt`, `slti`)
  * Equality comparison using `beq`/`bne`
  * Logical negation using `xor` with 1

#### Advanced Features
* ✅ **Variable Name Safety**
  * Automatic prefixing of conflicting variable names
  * Protection against MIPS instruction name conflicts
  * Single/double-letter variable name handling
  * Variable name mapping table

* ✅ **Printf Support**
  * String literal printing (character-by-character)
  * Integer formatting (`%d`)
  * Float formatting (`%.2f`) with precision
  * Character formatting (`%c`)
  * Newline handling

* ✅ **Stack Management**
  * Automatic stack space calculation
  * Register spilling with offset tracking
  * Parameter saving on stack
  * Local variable allocation

### MIPS Code Structure
```mips
.data
    # Global variables, arrays, strings
    str_0: .asciiz "Hello\n"
    array: .space 40

.text
.globl main

func_add:
    # Function prologue
    addi $sp, $sp, -56
    sw $ra, 52($sp)
    # ... function body ...
    # Function epilogue
    lw $ra, 52($sp)
    addi $sp, $sp, 56
    jr $ra

main:
    # Main program
    # ... code ...
    li $v0, 10
    syscall  # Exit
```

### SPIM Compatibility
* ✅ Generates SPIM-compatible assembly
* ✅ Uses SPIM syscalls (1=print_int, 10=exit, 11=print_char)
* ✅ Proper exception handling setup
* ✅ Compatible with `/usr/lib/spim/exceptions.s`

---

## 🏗️ Compiler Architecture

### Pipeline Stages
```
Source Code (.c/.cpp)
    ↓
┌─────────────────────────┐
│   Lexical Analysis      │  → Tokens
│   (Flex/Lex)            │
└─────────────────────────┘
    ↓
┌─────────────────────────┐
│   Syntax Analysis       │  → Abstract Syntax Tree (AST)
│   (Bison/Yacc)          │
└─────────────────────────┘
    ↓
┌─────────────────────────┐
│   Semantic Analysis     │  → Symbol Table, Type Checking
│   (Custom Analyzer)     │     Error Detection
└─────────────────────────┘
    ↓ (If no errors)
┌─────────────────────────┐
│   Code Generation       │  → Three-Address Code (TAC)
│   (TAC Generator)       │
└─────────────────────────┘
    ↓
┌─────────────────────────┐
│   MIPS Code Generation  │  → MIPS Assembly (.s)
│   (MIPS Generator)      │
└─────────────────────────┘
    ↓
Output: AST (DOT), TAC, MIPS Assembly
    ↓
┌─────────────────────────┐
│   SPIM Simulator        │  → Program Execution
│   (Runtime)             │
└─────────────────────────┘
```

### Key Components

1. **Lexer** (`lexer.l`): Tokenizes input source code
2. **Parser** (`parser.y`): Builds AST using grammar rules
3. **AST** (`ast.h/cpp`): Tree representation of program structure
4. **Symbol Table** (`symbol.h/cpp`): Manages identifiers and their attributes
5. **Semantic Analyzer** (`semantic.h/cpp`): Type checking and validation
6. **Code Generator** (`codegen.h/cpp`): Converts AST to TAC
7. **TAC Generator** (`tac.h/cpp`): Manages intermediate code instructions
8. **MIPS Generator** (`mips.h/cpp`): Translates TAC to MIPS assembly

---

## 🛠️ Installation & Usage

### Prerequisites
```bash
# Install required tools
sudo apt-get install flex bison g++ graphviz spim
```

### Build
```bash
# Clone the repository
git clone <repository-url>
cd Compiler_APK2

# Build the compiler
make clean
make
```

### Usage
```bash
# Compile a C/C++ source file
./compiler input.c

# Output files generated:
# - ast.dot         (AST visualization)
# - output.tac      (Three-address code)
# - output.s        (MIPS assembly)
# - Console output  (Symbol table, errors, TAC)

# Run the generated MIPS code in SPIM
spim -file output.s

# Or use the shell script for quick testing
./run.sh input.c
```

### Visualize AST
```bash
# Generate PNG from DOT file
dot -Tpng ast.dot -o ast.png
```

### Running Tests
```bash
# Run all test cases
cd test_passed
for file in *.cpp *.c; do
    echo "Testing $file..."
    ../compiler "$file" && spim -file ../output.s
done
```

---

## 🧩 Example Programs Tested

### 1. Fibonacci (Recursive)
```c
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}
```

### 2. Multi-Dimensional Arrays
```c
int main() {
    int a[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = i * 3 + j;
        }
    }
    return 0;
}
```

### 3. Structures and Pointers
```c
struct Point {
    int x;
    int y;
};

int main() {
    struct Point p;
    p.x = 10;
    p.y = 20;
    return p.x + p.y;
}
```

### 4. Goto with Labels
```c
int main() {
    int x = 0;
start:
    if (x >= 5)
        goto end;
    x++;
    goto start;
end:
    return 0;
}
```

### 5. Switch-Case
```c
int main() {
    int x = 2;
    switch(x) {
        case 1:
            printf("One\n");
            break;
        case 2:
            printf("Two\n");
            break;
        default:
            printf("Other\n");
    }
    return 0;
}
```

### 6. Static Variables
```c
int counter() {
    static int count = 0;
    count++;
    return count;
}
```

### 7. Matrix Operations
```c
int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    
    // Matrix multiplication
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return 0;
}
```

### 8. Function Pointers (Array)
```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int main() {
    int (*ops[2])(int, int) = {add, sub};
    printf("%d\n", ops[0](5, 2));  // Outputs: 7
    printf("%d\n", ops[1](5, 2));  // Outputs: 3
    return 0;
}
```

### 9. Function Pointer Assignment
```c
#include <stdio.h>

int multiply(int a, int b) { return a * b; }

int main() {
    int (*operation)(int, int);
    operation = multiply;
    printf("Result: %d\n", operation(10, 5));  // Outputs: 50
    return 0;
}
```

---

## 📊 Compilation Statistics

The compiler provides detailed statistics:
- Total TAC instructions generated
- Symbol table entries by scope
- Error and warning counts
- AST node count
- MIPS instructions generated
- Register allocation statistics

---

## 🚧 Known Issues & Limitations

### Current Limitations
* ⚠️ **Float arithmetic** - Uses integer instructions (add/sub) instead of floating-point (add.s/sub.s)
  * Printf supports `%.2f` format but calculations are integer-based
  * Requires TAC type tracking and FPU register usage
* ⚠️ **Array initialization** - Some initializer values show as 0 instead of actual values
  * Need proper data section initialization for nested arrays
* ⚠️ **Variable name conflicts** - Fixed with automatic `var_` prefix for MIPS instruction conflicts
  * Single/double letter variables that match MIPS mnemonics get prefixed
* ⚠️ No optimization passes (constant folding, dead code elimination)
* ⚠️ Limited pointer arithmetic validation in edge cases
* ⚠️ No support for dynamic memory allocation (`malloc`, `free`)
* ⚠️ No file I/O operations (`fopen`, `fread`, etc.)
* ⚠️ Variadic functions parsed but not fully validated/implemented
* ⚠️ No support for C++ classes/objects (this is a C compiler primarily)
* ⚠️ Limited support for string operations

### Fixed Issues ✅
* ✅ **Function pointers** - Now fully supported with `jalr` instruction
  * Function pointer arrays work correctly
  * Function pointer assignment and invocation functional
* ✅ **SPIM variable conflicts** - Variables like `b`, `a`, etc. now prefixed automatically
* ✅ **Multi-dimensional arrays** - Proper index flattening and MIPS generation
* ✅ **Pointer operations** - Array-to-pointer decay implemented

---

## 🔮 Future Enhancements

### Short Term
* [ ] Fix float arithmetic (add.s, sub.s, mul.s, div.s instructions)
* [ ] Fix array initialization in data section
* [ ] Constant folding and constant propagation
* [ ] Dead code elimination
* [ ] Copy propagation optimization
* [ ] Common subexpression elimination

### Medium Term
* [ ] Advanced register allocation algorithms (graph coloring)
* [ ] Peephole optimization
* [ ] Control flow graph (CFG) generation
* [ ] Data flow analysis
* [ ] Loop optimizations (unrolling, invariant code motion)
* [ ] Function inlining

### Long Term
* [ ] Full C standard library support
* [ ] Dynamic memory management (malloc/free)
* [ ] File I/O operations
* [ ] Advanced function pointer support (returning function pointers)
* [ ] Full C++ class support
* [ ] Advanced type system (const, volatile, restrict)
* [ ] Template support (C++)
* [ ] Preprocessor macro expansion
* [ ] Multiple target architectures (x86, ARM)

---

## 📚 Testing

The compiler has been extensively tested with:
- ✅ Comprehensive test suite covering all features
- ✅ Nested control structures (5+ levels deep)
- ✅ Complex expressions with operator precedence
- ✅ Recursive function calls
- ✅ Multi-dimensional arrays (up to 4D)
- ✅ **Function pointers** (arrays and assignment) ⭐
- ✅ Error handling and recovery
- ✅ Edge cases (empty functions, zero initialization)
- ✅ MIPS assembly validation on SPIM simulator

### Test Environment
- **Lexer**: Flex 2.6.4
- **Parser**: Bison 3.8.2
- **Compiler**: GCC 11.4.0 with C++11
- **Simulator**: SPIM 8.0
- **OS**: Linux Ubuntu 22.04

### Quick Test
```bash
# Test a simple program
./compiler input.c && spim -file output.s
```

---

## 🤝 Contributing

This is an academic project, but suggestions and improvements are welcome!

1. Fork the repository
2. Create a feature branch
3. Make your changes with tests
4. Submit a pull request

---

## 📜 License

Educational/Academic Use

---

## 👨‍💻 Author

**Compiler Design Project (2025)**

Built as part of a comprehensive study in compiler construction, covering:
- Formal language theory
- Parsing techniques (LL, LR, LALR)
- Semantic analysis and type systems
- Intermediate code generation (Three-Address Code)
- Target code generation (MIPS assembly)
- Register allocation and management
- Code optimization principles
- Runtime system design

### Recent Updates (November 2025)
- ✅ Added complete MIPS assembly generation
- ✅ Implemented function pointer support
- ✅ Fixed SPIM variable name conflicts
- ✅ Added indirect function call support with `jalr`
- ✅ Improved register allocation with spilling
- ✅ Enhanced printf formatting support
- ✅ Added array-to-pointer decay semantics

---

**⭐ If you found this project helpful, please consider giving it a star!**