# Lexical Analyzer Project Specification

## Objective
Create a lexical analyzer that tokenizes a given source program into lexemes and their corresponding tokens.

---

## Implementation Options
- C / C++ → Use lex or flex
- Python → Use PLY (Python Lex-Yacc)

---

## Expected Output

### ✅ Valid Program
If the source program contains only valid tokens, print a table with two columns:

Lexeme   | Token
---------|---------
if       | keyword
foo      | identifier

### ❌ Invalid Program
If the program contains lexical errors, report ALL the lexical errors found in the input program.

---

## Directory Structure
project/
│
├── src/           # Contains your .l/.lex/.py lexical analyzer source file
│
├── test/          # Contains at least 5 test cases (covering all features)
│
├── Makefile       # Recipe to compile the lex/flex code into an executable
│
└── run.sh         # Script to run the analyzer on all test cases

---

## Features to Implement

### Basic Features
Your lexical analyzer must recognize tokens for:
- Arithmetic operators: +, -, *, /, %
- Logical operators: &&, ||, !
- Control flow keywords:
  - if, else
  - for, while, do while
  - switch, case
- Data structures:
  - Arrays (int arr[], char arr[])
  - Pointers (int *ptr)
  - Structures (struct)
- Input/Output: printf, scanf
- Function calls with arguments
- Branching/Loop control:
  - goto
  - break, continue
- Storage class specifier:
  - static

### Advanced Features (Optional Bonus)
- Function calls with variable arguments (e.g., printf("...", var1, var2, ...))
- typedef
- enum
- union

---

## Notes
- Multiline comments (/* ... */) are NOT required.
- Test cases must ensure comprehensive coverage of all features.
- Lexical errors must be detected and reported without halting after the first error.

---

### Input:
if (a > 5) {
printf("Hello");
}

### Output:
Lexeme   | Token
---------|---------
if       | keyword
(        | lparen
a        | identifier
>        | operator
5        | number
)        | rparen
{        | lbrace
printf   | function
(        | lparen
"Hello"  | string
)        | rparen
;        | semicolon
}        | rbrace