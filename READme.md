# 🎯 Toy C Compiler

A comprehensive Toy C Compiler implemented as part of a compiler design project. This compiler performs complete compilation pipeline including lexical analysis, syntax parsing, semantic analysis, and intermediate code generation (Three-Address Code) for a substantial subset of the C programming language.

## 📋 Table of Contents
- [Features](#-features-implemented)
- [Architecture](#-compiler-architecture)
- [Installation](#-installation--usage)
- [Examples](#-example-programs-tested)
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
  * Return value handling
  * Return statements
* ✅ **Pointers**
  * Address-of operations (`&var`)
  * Dereference operations (`*ptr`)
  * Pointer arithmetic

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

## 🏗️ Compiler Architecture

### Pipeline Stages
```
Source Code (.c)
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
Output: AST (DOT), TAC, Symbol Table
```

### Key Components

1. **Lexer** (`lexer.l`): Tokenizes input source code
2. **Parser** (`parser.y`): Builds AST using grammar rules
3. **AST** (`ast.h/cpp`): Tree representation of program structure
4. **Symbol Table** (`symbol.h/cpp`): Manages identifiers and their attributes
5. **Semantic Analyzer** (`semantic.h/cpp`): Type checking and validation
6. **Code Generator** (`codegen.h/cpp`): Converts AST to TAC
7. **TAC Generator** (`tac.h/cpp`): Manages intermediate code instructions

---

## 🛠️ Installation & Usage

### Prerequisites
```bash
# Install required tools
sudo apt-get install flex bison g++ graphviz
```

### Build
```bash
# Clone the repository
git clone 
cd toy-c-compiler

# Build the compiler
make clean
make
```

### Usage
```bash
# Compile a C source file
./compiler input.c

# Output files generated:
# - ast.dot         (AST visualization)
# - output.tac      (Three-address code)
# - Console output  (Symbol table, errors, TAC)
```

### Visualize AST
```bash
# Generate PNG from DOT file
dot -Tpng ast.dot -o ast.png
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

---

## 📊 Compilation Statistics

The compiler provides detailed statistics:
- Total TAC instructions generated
- Symbol table entries by scope
- Error and warning counts
- AST node count

---

## 🚧 Current Limitations

* ⚠️ No optimization passes (constant folding, dead code elimination)
* ⚠️ Limited pointer arithmetic validation
* ⚠️ No support for dynamic memory allocation (`malloc`, `free`)
* ⚠️ No file I/O operations (`fopen`, `fread`, etc.)
* ⚠️ Variadic functions parsed but not fully validated
* ⚠️ No support for function pointers
* ⚠️ Limited support for string operations

---

## 🔮 Future Enhancements

### Short Term
* [ ] Constant folding and constant propagation
* [ ] Dead code elimination
* [ ] Copy propagation optimization
* [ ] Common subexpression elimination

### Medium Term
* [ ] Target code generation (x86/ARM assembly)
* [ ] Register allocation
* [ ] Peephole optimization
* [ ] Control flow graph (CFG) generation

### Long Term
* [ ] Full C standard library support
* [ ] Dynamic memory management
* [ ] File I/O operations
* [ ] Function pointers and callbacks
* [ ] Advanced type system (const, volatile, restrict)
* [ ] Inline functions
* [ ] Preprocessor macro expansion

---

## 📚 Testing

The compiler has been extensively tested with:
- ✅ 50+ test cases covering all features
- ✅ Nested control structures (5+ levels deep)
- ✅ Complex expressions with operator precedence
- ✅ Recursive function calls
- ✅ Multi-dimensional arrays (up to 4D)
- ✅ Error handling and recovery
- ✅ Edge cases (empty functions, zero initialization)

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
- Parsing techniques (LL, LR)
- Semantic analysis and type systems
- Intermediate code generation
- Code optimization principles

---



**⭐ If you found this project helpful, please consider giving it a star!**