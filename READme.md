# C/C++ Compiler with MIPS Assembly Generation

A comprehensive compiler implementation that translates C/C++ source code into MIPS assembly, featuring complete lexical analysis, syntax parsing, semantic validation, intermediate code generation, and executable MIPS output compatible with the SPIM simulator.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Installation & Usage](#installation--usage)
- [Language Support](#language-support)
- [MIPS Code Generation](#mips-code-generation)
- [Examples](#examples)
- [Testing](#testing)

---

## Overview

This compiler implements a complete compilation pipeline from C/C++ source code to executable MIPS assembly. The project demonstrates fundamental compiler design principles including lexical analysis, syntax parsing, semantic validation, intermediate representation, and target code generation.

**Key Highlights:**
- Full compilation pipeline with multiple intermediate representations
- SPIM-compatible MIPS assembly output
- Comprehensive semantic analysis and type checking
- Advanced features: function pointers, multi-level pointers, references
- 22 test cases with 100% pass rate

---

## Features

### Core Language Constructs

#### Control Flow
- **Conditional Statements**
  - if-else statements with nested support
  - Ternary operator (? :)
  - switch-case with default and fall-through
  
- **Loops**
  - for loops with initialization, condition, and increment
  - while loops
  - do-while loops
  - until loops (custom extension)
  - Nested loop support
  
- **Jump Statements**
  - goto with labeled targets
  - break (loop and switch termination)
  - continue (loop iteration skip)
  - return statements with type validation

#### Operators
- **Arithmetic**: +, -, *, /, % (modulo)
- **Relational**: <, >, <=, >=, ==, !=
- **Logical**: && (AND), || (OR), ! (NOT)
- **Bitwise**: &, |, ^, ~, <<, >>
- **Assignment**: =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
- **Increment/Decrement**: ++ and -- (prefix and postfix)
- **Pointer**: * (dereference), & (address-of)
- **Member Access**: . (direct), -> (pointer)

#### Data Types & Structures

**Basic Types**
- int, char, short, long, long long
- signed and unsigned variants
- void (for function returns)

**Complex Types**
- **Arrays**: Single and multi-dimensional with initialization support
- **Pointers**: Single and multi-level (**, ***, etc.)
- **Structures**: Definition, member access, nested structures
- **Unions**: Shared memory allocation for multiple members
- **Enumerations**: Named integer constants with auto/explicit values
- **Typedef**: User-defined type aliases
- **References**: C++ reference types (&)

**Storage Classes**
- static keyword (function-scoped variables)

#### Functions
- Function declarations and definitions
- Parameter passing (by value and by pointer)
- Return values with type checking
- Recursive function calls
- Function pointers (direct and indirect calls)
- Standard I/O: printf and scanf

### Compiler Features

#### Lexical Analysis
- Complete tokenization of C/C++ source
- Keyword, identifier, and operator recognition
- String and character literal handling
- Preprocessor directive support (#include, #define)

#### Syntax Analysis
- Abstract Syntax Tree (AST) construction
- Grammar-based parsing with Bison
- Detailed syntax error reporting
- AST visualization via DOT format

#### Semantic Analysis
- Multi-scope symbol table management
- Type checking and inference
- Function signature validation
- Array bounds checking (static)
- Pointer operation validation
- Break/continue/goto validation
- Duplicate declaration detection
- Undefined symbol detection
- Type compatibility verification

#### Code Generation
- Three-Address Code (TAC) intermediate representation
- MIPS assembly generation
- Register allocation with spilling
- Stack frame management
- Function prologue/epilogue generation
- Label management for control flow

---

## Architecture

### Compilation Pipeline

```
Source Code (.c/.cpp)
         ↓
    [Lexer (Flex)]  ──→  Tokens
         ↓
   [Parser (Bison)] ──→  Abstract Syntax Tree
         ↓
 [Semantic Analyzer] ──→  Type-checked AST + Symbol Table
         ↓
  [TAC Generator]   ──→  Three-Address Code
         ↓
  [MIPS Generator]  ──→  MIPS Assembly (.s)
         ↓
   [SPIM Simulator] ──→  Execution
```

### Key Components

| Component | File | Description |
|-----------|------|-------------|
| **Lexer** | lexer.l | Tokenizes source code using Flex |
| **Parser** | parser.y | Builds AST using Bison grammar |
| **AST** | ast.h/cpp | Tree representation of program |
| **Symbol Table** | symbol.h/cpp | Manages scopes and symbols |
| **Semantic Analyzer** | semantic.h/cpp | Type checking and validation |
| **Code Generator** | codegen.h/cpp | Converts AST to TAC |
| **TAC** | tac.h/cpp | Intermediate representation |
| **MIPS Generator** | mips.h/cpp | MIPS assembly generation |

---

## Installation & Usage

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install flex bison g++ spim graphviz

# Fedora/RHEL
sudo dnf install flex bison gcc-c++ spim graphviz
```

### Build

```bash
# Clone repository
git clone <repository-url>
cd Compiler_APK2-master

# Build compiler
make clean
make
```

### Usage

```bash
# Compile a source file
./compiler program.c

# Generated outputs:
# - ast.dot      (AST visualization)
# - output.tac   (Three-address code)
# - output.s     (MIPS assembly)

# Execute in SPIM
spim -file output.s

# Run automated tests
./run.sh
```

### AST Visualization

```bash
# Generate AST diagram
dot -Tpng ast.dot -o ast.png
```

---

## Language Support

### Supported Features

#### Arithmetic & Logic
```c
int result = (a + b) * c / d % e;
int compare = (x > y) && (z <= w);
int bitwise = (p & q) | (r ^ s);
```

#### Control Flow
```c
// if-else
if (x > 0) {
    printf("Positive\n");
} else if (x < 0) {
    printf("Negative\n");
} else {
    printf("Zero\n");
}

// switch-case
switch (choice) {
    case 1: printf("One\n"); break;
    case 2: printf("Two\n"); break;
    default: printf("Other\n");
}

// Loops
for (int i = 0; i < 10; i++) { }
while (condition) { }
do { } while (condition);

// Jump statements
goto label;
break;
continue;
label: statement;
```

#### Arrays
```c
// Single-dimensional
int arr[10] = {1, 2, 3, 4, 5};

// Multi-dimensional
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
```

#### Pointers
```c
// Single-level pointers
int x = 10;
int *p = &x;
*p = 20;

// Multi-level pointers
int **pp = &p;
int ***ppp = &pp;
printf("%d\n", ***ppp);

// Array of pointers
int *arr[5];
```

#### Structures
```c
struct Point {
    int x;
    int y;
};

struct Point p = {10, 20};
struct Point *ptr = &p;
printf("%d %d\n", p.x, ptr->y);
```

#### Unions
```c
union Data {
    int i;
    char c;
};

union Data d;
d.i = 42;
```

#### Enumerations
```c
enum Color { RED, GREEN, BLUE };
enum Status { PENDING = 10, APPROVED = 20 };
```

#### Typedef
```c
typedef int Integer;
typedef struct Point Point;
Integer x = 5;
```

#### References (C++)
```c
int x = 10;
int &ref = x;
ref = 20;  // Modifies x
```

#### Functions
```c
// Function declaration
int factorial(int n);

// Recursive function
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Function pointers
int add(int a, int b) { return a + b; }
int (*operation)(int, int) = add;
int result = operation(5, 3);

// Array of function pointers
int (*ops[3])(int, int) = {add, sub, mul};
```

#### Static Variables
```c
int counter() {
    static int count = 0;
    return ++count;
}
```

#### I/O Operations
```c
int x;
scanf("%d", &x);
printf("Value: %d\n", x);
printf("Character: %c\n", 'A');
```

---

## MIPS Code Generation

### Features

#### Register Management
- 10 temporary registers ($t0-$t9)
- 8 saved registers ($s0-$s7)
- Intelligent allocation and spilling
- Register reuse optimization

#### Function Calls
- Proper calling convention
- Stack frame management
- Argument passing ($a0-$a3 and stack)
- Return values ($v0)
- Saved register preservation
- Function pointers via jalr

#### Memory Operations
- Load/Store: lw, sw, lh, sh, lb, sb
- Array indexing with offset calculation
- Multi-dimensional array flattening
- Pointer dereferencing
- Static variable allocation

#### Control Flow
- Conditional branches: beq, bne, blt, bge, etc.
- Unconditional jumps: j, jal, jalr, jr
- Label generation and resolution
- Short-circuit evaluation

#### Optimizations
- Variable name conflict resolution
- Dead register elimination
- Constant propagation
- Stack space optimization

### MIPS Output Structure

```mips
.data
    # Static variables
    str_0: .asciiz "Hello, World!\n"
    global_var: .word 0
    array: .space 40

.text
.globl main

func_example:
    # Prologue
    addi $sp, $sp, -32
    sw $ra, 28($sp)
    sw $s0, 24($sp)
    
    # Function body
    # ...
    
    # Epilogue
    lw $s0, 24($sp)
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    jr $ra

main:
    # Main program
    # ...
    
    # Exit
    li $v0, 10
    syscall
```

---

## Examples

### Example 1: Fibonacci (Recursive)
```c
#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n = 10;
    printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
    return 0;
}
```

### Example 2: Matrix Multiplication
```c
#include <stdio.h>

int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2];
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    printf("Result:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
```

### Example 3: Linked List with Structures
```c
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

int main() {
    struct Node n1, n2, n3;
    
    n1.data = 10;
    n1.next = &n2;
    
    n2.data = 20;
    n2.next = &n3;
    
    n3.data = 30;
    n3.next = 0;
    
    struct Node *ptr = &n1;
    while (ptr != 0) {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
    
    return 0;
}
```

### Example 4: Function Pointers
```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main() {
    int (*operations[3])(int, int);
    operations[0] = add;
    operations[1] = subtract;
    operations[2] = multiply;
    
    int x = 10, y = 5;
    printf("Add: %d\n", operations[0](x, y));
    printf("Subtract: %d\n", operations[1](x, y));
    printf("Multiply: %d\n", operations[2](x, y));
    
    return 0;
}
```

### Example 5: Multi-level Pointers
```c
#include <stdio.h>

int main() {
    int value = 42;
    int *p = &value;
    int **pp = &p;
    int ***ppp = &pp;
    
    printf("Direct: %d\n", value);
    printf("*p: %d\n", *p);
    printf("**pp: %d\n", **pp);
    printf("***ppp: %d\n", ***ppp);
    
    ***ppp = 100;
    printf("Modified: %d\n", value);
    
    return 0;
}
```

### Example 6: Enumerations and Unions
```c
#include <stdio.h>

enum Day { MON, TUE, WED, THU, FRI };

union Number {
    int i;
    char c;
};

int main() {
    enum Day today = WED;
    printf("Day: %d\n", today);
    
    union Number num;
    num.i = 65;
    printf("Integer: %d\n", num.i);
    printf("Character: %c\n", num.c);
    
    return 0;
}
```

---

## Testing

### Test Suite

The compiler includes comprehensive test coverage:

| Test Category | Test Files | Features Tested |
|--------------|------------|-----------------|
| **Arrays** | test_arrays_comprehensive.cpp | Single/multi-dimensional, initialization |
| **Pointers** | test_pointers_basic.cpp, test_multilevel_pointers.cpp | Single, multi-level, array of pointers |
| **Structures** | test_struct_basic.cpp, test_struct_nested.cpp | Member access, nesting |
| **Functions** | test_functions_basic.cpp, test_recursion.cpp | Calls, recursion |
| **Function Pointers** | test_functions_pointers.cpp | Direct, indirect calls |
| **Control Flow** | test_loops_*.cpp, test_goto.cpp | for, while, do-while, goto |
| **Switch** | test_switch_basic.cpp | case, default, break |
| **Operators** | test_operators.cpp | Arithmetic, logical, bitwise |
| **Break/Continue** | test_break_continue.cpp | Loop control |
| **Enum** | test_enum.cpp | Named constants |
| **Union** | test_union.cpp | Shared memory |
| **Typedef** | test_typedef.cpp | Type aliases |
| **Static** | test_static.cpp | Static variables |
| **References** | test_references_*.cpp | C++ references |

```

### Running Tests

```bash
# Run all tests
./run.sh

# Test individual file
./compiler test/test_pointers_basic.cpp
spim -file output.s

# Compare with GCC
gcc test/test_pointers_basic.cpp -o gcc_output
./gcc_output
```

### Test Environment

- **Operating System**: Linux Ubuntu 22.04
- **Lexer**: Flex 2.6.4
- **Parser**: Bison 3.8.2
- **C++ Compiler**: GCC 11.4.0 (C++11)
- **MIPS Simulator**: SPIM 8.0

---
