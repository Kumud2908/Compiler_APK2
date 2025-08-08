Instructions
Write a lexical analyzer that will tokenize your source language into lexemes. You can use lex, flex if your implementation language is C/C++. Please use PLY if your implementation language is python.

Expected output: 
If the input program contains all the valid tokens, print a table with two columns, token and lexeme. For example, please see the table below.

Lexeme	Token
if	keyword
foo	identifier

If the input program has a lexical error, then report all the lexical errors in your input program.

Expected deliveries:
 src directory: This will contain your lex/flex/python file, which can tokenize your source language.
 test directory: Minimum 5 test cases that can test all the features you are implementing.
 makefile: File that contains recipe for compiling your lex/flex file into the executable
 run.sh: script file, which will take your executable as input and run over all the test cases in the test directory.

 parts to be implemented:-

 basic:-
 All arithmetic and logical operator
if-else
for loop
while loop
do while loop
switch cases
array (integer and char)
pointers
structure
printf and scanf
function call with arguments
goto, break and continue
static keywords

advanced:-

 funtion call with variable arguments 
 typedef 
 enum union


 ** we are not adding multi line comments
 