%{

#include "ast.h"        // Include this FIRST
#include "../build/parser.tab.hpp" // Include this SECOND
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* TYpe DEf identfication */
extern int parser_is_type_name(const char* name);

/* Global variables */
int line = 1;
int col = 1;
int errors = 0;

/* Token collection */
typedef struct {
    char token[256];
    char token_type[64];
} TokenEntry;

TokenEntry token_table[10000];
int token_count = 0;

void add_token(const char* token, const char* type) {
    if (token_count < 10000) {
        strncpy(token_table[token_count].token, token, 255);
        strncpy(token_table[token_count].token_type, type, 63);
        token_table[token_count].token[255] = '\0';
        token_table[token_count].token_type[63] = '\0';
        token_count++;
    }
    printf("Token: %-20s Type: %-15s\n", token, type);
}

void print_token_table() {
    printf("\n=== TOKEN TABLE ===\n");
    printf("%-20s %-15s\n", "Token", "Token_Type");
    printf("%-20s %-15s\n", "-----", "----------");
    for (int i = 0; i < token_count; i++) {
        printf("%-20s %-15s\n", token_table[i].token, token_table[i].token_type);
    }
    printf("\nTotal tokens: %d\n", token_count);
    printf("Lexical errors: %d\n", errors);
}

/* Function prototypes */
void error(const char* msg);
void move(const char* text);
char* make_string(const char* text);

%}

/* Flex options */
%option noyywrap
%option yylineno

/* Start conditions for comments and strings */
%x COMMENT
%x STRING_STATE
%x CLASS_NAME   

/* Regular expressions for patterns */
DIGIT           [0-9]
LETTER          [a-zA-Z_]
ALNUM           [a-zA-Z0-9_]
HEXDIGIT        [0-9a-fA-F]
OCTDIGIT        [0-7]
SPACE           [ \t\r]
NEWLINE         \n

/* Number patterns */
INTEGER         {DIGIT}+
HEX_NUM         0[xX]{HEXDIGIT}+
OCT_NUM         0{OCTDIGIT}+
FLOAT_NUM       {DIGIT}+\.{DIGIT}+([eE][+-]?{DIGIT}+)?
FLOAT_EXP       {DIGIT}+[eE][+-]?{DIGIT}+
FLOAT_DOT       \.{DIGIT}+([eE][+-]?{DIGIT}+)?

/* Identifier pattern */
ID_PATTERN      {LETTER}{ALNUM}*

%%

    /* C Keywords */
"auto"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return AUTO; }
"break"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return BREAK; }
"case"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return CASE; }
"char"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return CHAR; }
"const"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return CONST; }
"continue"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return CONTINUE; }
"default"       { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return DEFAULT; }
"do"            { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return DO; }
"double"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return DOUBLE; }
"else"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return ELSE; }
"enum"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return ENUM; }
"extern"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return EXTERN; }
"float"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return FLOAT; }
"for"           { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return FOR; }
"goto"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return GOTO; }
"if"            { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return IF; }
"int"           { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return INT; }
"long"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return LONG; }
"register"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return REGISTER; }
"return"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return RETURN; }
"short"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return SHORT; }
"signed"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return SIGNED; }
"sizeof"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return SIZEOF; }
"static"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return STATIC; }
"struct"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return STRUCT; }
"switch"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return SWITCH; }
"typedef"       { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return TYPEDEF; }
"union"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return UNION; }
"unsigned"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return UNSIGNED; }
"void"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return VOID; }
"NULL"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return NULL_TOKEN; }
"nullptr"       { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return NULLPTR; }


"volatile"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return VOLATILE; }
"while"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return WHILE; }

    /* C++ Keywords */
"class"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return CLASS; }

<CLASS_NAME>{ID_PATTERN} {
    add_token(yytext, "CLASS_NAME");  // Tag as class name
    move(yytext);
    yylval.str = make_string(yytext);
    BEGIN(INITIAL);  // Return to normal scanning
    return ID;       // Or define a CLASS_NAME token if you want a separate type
}

"private"       { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return PRIVATE; }
"protected"     { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return PROTECTED; }
"public"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return PUBLIC; }
"virtual"       { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return VIRTUAL; }
"friend"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return FRIEND; }
"inline"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return INLINE; }
"operator"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return OPERATOR; }
"overload"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return OVERLOAD; }
"template"      { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return TEMPLATE; }
"this"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return THIS; }
"new"           { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return NEW; }
"delete"        { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return DELETE; }
"namespace"     { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return NAMESPACE; }
"using"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return USING; }
"try"           { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return TRY; }
"catch"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return CATCH; }
"throw"         { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return THROW; }
"bool"          { add_token(yytext, "KEYWORD"); move(yytext); yylval.str = make_string(yytext); return BOOL; }
"true"          { add_token(yytext, "BOOLEAN_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return TRUE; }
"false"         { add_token(yytext, "BOOLEAN_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return FALSE; }
"~"{ID_PATTERN} {
    add_token(yytext, "DESTRUCTOR");
    move(yytext);
    yylval.str = make_string(yytext);
    return DESTRUCTOR;
}


{ID_PATTERN}    { 
    /* Check if it's a typedef name FIRST */
    if (parser_is_type_name(yytext)) {
        add_token(yytext, "TYPEDEF_NAME");  // ← Add this line
        move(yytext); 
        yylval.str = make_string(yytext); 
        return TYPEDEF_NAME;  // ← Return immediately
    }
        
    add_token(yytext, "IDENTIFIER"); 
    move(yytext); 
    yylval.str = make_string(yytext); 
    return ID; 
}

    /* Integer literals */
{HEX_NUM}[lL]?          { add_token(yytext, "INTEGER_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return NUM; }
{OCT_NUM}[lL]?          { add_token(yytext, "INTEGER_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return NUM; }
{INTEGER}[lL]?          { add_token(yytext, "INTEGER_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return NUM; }

    /* Floating point literals */
{FLOAT_NUM}[fFlL]?      { add_token(yytext, "FLOAT_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return FLOAT_LIT; }
{FLOAT_EXP}[fFlL]?      { add_token(yytext, "FLOAT_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return FLOAT_LIT; }
{FLOAT_DOT}[fFlL]?      { add_token(yytext, "FLOAT_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return FLOAT_LIT; }

    /* Character literals */
'(\\.|[^'\\])'              { add_token(yytext, "CHARACTER_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return CHAR_LIT; }
'(\\[0-7]{1,3})'            { add_token(yytext, "CHARACTER_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return CHAR_LIT; }
'(\\x{HEXDIGIT}{1,2})'      { add_token(yytext, "CHARACTER_CONSTANT"); move(yytext); yylval.str = make_string(yytext); return CHAR_LIT; }



    /* Unterminated character literal */
'([^'\\]|\\.|\\[0-7]{1,3}|\\x{HEXDIGIT}{1,2})*$ {
    move(yytext);
    error("Unterminated character literal");
    return ERROR;
}

    /* String literals */
\"([^"\n\\]|\\.)*\"     { 
    add_token(yytext, "STRING_LITERAL"); 
    move(yytext); 
    yylval.str = make_string(yytext); 
    return STRING_LIT; 
}


    /* Comments */
"/*"                        { move(yytext); BEGIN(COMMENT); }
<COMMENT>{
    "*/"                    { move(yytext); BEGIN(INITIAL); }
    {NEWLINE}               { line++; col = 1; }
    <<EOF>>                 { error("Unterminated comment at EOF"); BEGIN(INITIAL); return ERROR; }
    .                       { move(yytext); }
}

"//".*                      { move(yytext); /* Single line comment - ignore */ }

    /* Operators */
"++"            { add_token(yytext, "POSTFIX_OP"); move(yytext); yylval.str = make_string(yytext); return INC; }
"--"            { add_token(yytext, "POSTFIX_OP"); move(yytext); yylval.str = make_string(yytext); return DEC; }
"+="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return PLUS_EQ; }
"-="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return MINUS_EQ; }
"*="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return MUL_EQ; }
"/="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return DIV_EQ; }
"%="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return MOD_EQ; }
"&="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return AND_EQ; }
"|="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return OR_EQ; }
"^="            { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return XOR_EQ; }
"<<="           { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return LSHIFT_EQ; }
">>="           { add_token(yytext, "ASSIGN_OP"); move(yytext); yylval.str = make_string(yytext); return RSHIFT_EQ; }
"=="            { add_token(yytext, "RELATIONAL_OP"); move(yytext); yylval.str = make_string(yytext); return EQ; }
"!="            { add_token(yytext, "RELATIONAL_OP"); move(yytext); yylval.str = make_string(yytext); return NE; }
"<="            { add_token(yytext, "RELATIONAL_OP"); move(yytext); yylval.str = make_string(yytext); return LE; }
">="            { add_token(yytext, "RELATIONAL_OP"); move(yytext); yylval.str = make_string(yytext); return GE; }
"&&"            { add_token(yytext, "LOGICAL_OP"); move(yytext); yylval.str = make_string(yytext); return AND; }
"||"            { add_token(yytext, "LOGICAL_OP"); move(yytext); yylval.str = make_string(yytext); return OR; }
"<<"            { add_token(yytext, "SHIFT_OP"); move(yytext); yylval.str = make_string(yytext); return LSHIFT; }
">>"            { add_token(yytext, "SHIFT_OP"); move(yytext); yylval.str = make_string(yytext); return RSHIFT; }
"->"            { add_token(yytext, "ARROW"); move(yytext); yylval.str = make_string(yytext); return ARROW; }
"::"            { add_token(yytext, "SCOPE"); move(yytext); yylval.str = make_string(yytext); return SCOPE; }
"+"             { add_token(yytext, "ARITHMETIC_OP"); move(yytext); yylval.str = make_string(yytext); return PLUS; }
"-"             { add_token(yytext, "ARITHMETIC_OP"); move(yytext); yylval.str = make_string(yytext); return MINUS; }
"*"             { add_token(yytext, "ARITHMETIC_OP"); move(yytext); yylval.str = make_string(yytext); return MUL; }
"/"             { add_token(yytext, "ARITHMETIC_OP"); move(yytext); yylval.str = make_string(yytext); return DIV; }
"%"             { add_token(yytext, "ARITHMETIC_OP"); move(yytext); yylval.str = make_string(yytext); return MOD; }
"="             { add_token(yytext, "ASSIGN"); move(yytext); yylval.str = make_string(yytext); return ASSIGN; }
"<"             { add_token(yytext, "RELATIONAL_OP"); move(yytext); yylval.str = make_string(yytext); return LT; }
">"             { add_token(yytext, "RELATIONAL_OP"); move(yytext); yylval.str = make_string(yytext); return GT; }
"!"             { add_token(yytext, "LOGICAL_OP"); move(yytext); yylval.str = make_string(yytext); return NOT; }
"&"             { add_token(yytext, "BITWISE_OP"); move(yytext); yylval.str = make_string(yytext); return BIT_AND; }
"|"             { add_token(yytext, "BITWISE_OP"); move(yytext); yylval.str = make_string(yytext); return BIT_OR; }
"^"             { add_token(yytext, "BITWISE_OP"); move(yytext); yylval.str = make_string(yytext); return BIT_XOR; }
"~"             { add_token(yytext, "BITWISE_OP"); move(yytext); yylval.str = make_string(yytext); return BIT_NOT; }
"..."           { add_token(yytext, "ELLIPSIS"); move(yytext); yylval.str = make_string(yytext); return ELLIPSIS; }
"."             { add_token(yytext, "DOT"); move(yytext); yylval.str = make_string(yytext); return DOT; }

    /* Punctuation */
";"             { add_token(yytext, "SEMICOLON"); move(yytext); yylval.str = make_string(yytext); return SEMI; }
","             { add_token(yytext, "COMMA"); move(yytext); yylval.str = make_string(yytext); return COMMA; }
"?"             { add_token(yytext, "TERNARY_OP"); move(yytext); yylval.str = make_string(yytext); return QUESTION; }
":"             { add_token(yytext, "COLON"); move(yytext); yylval.str = make_string(yytext); return COLON; }
"("             { add_token(yytext, "LPAREN"); move(yytext); yylval.str = make_string(yytext); return LPAREN; }
")"             { add_token(yytext, "RPAREN"); move(yytext); yylval.str = make_string(yytext); return RPAREN; }
"{"             { add_token(yytext, "LBRACE"); move(yytext); yylval.str = make_string(yytext); return LBRACE; }
"}"             { add_token(yytext, "RBRACE"); move(yytext); yylval.str = make_string(yytext); return RBRACE; }
"["             { add_token(yytext, "LBRACKET"); move(yytext); yylval.str = make_string(yytext); return LBRACKET; }
"]"             { add_token(yytext, "RBRACKET"); move(yytext); yylval.str = make_string(yytext); return RBRACKET; }

    /* Preprocessor directives */
^{SPACE}*#{SPACE}*.*$ { add_token(yytext, "PREPROCESSOR"); move(yytext); yylval.str = make_string(yytext); return PREP; }

    /* Whitespace */
{SPACE}+        { move(yytext); /* Ignore whitespace */ }
{NEWLINE}       { line++; col = 1; }

    /* Invalid characters */
.               { 
    move(yytext); 
    char msg[100];
    sprintf(msg, "Invalid character: '%c' (ASCII: %d)", yytext[0], yytext[0]);
    error(msg);
    return ERROR;
}

%%

/* Function implementations */
void error(const char* msg) {
    printf("LEXICAL ERROR at Line %d, Col %d: %s\n", line, col, msg);
    errors++;
}

void move(const char* text) {
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') {
            line++;
            col = 1;
        } else if (text[i] == '\t') {
            col += 4; // Tab width = 4
        } else {
            col++;
        }
    }
}

char* make_string(const char* text) {
    char* str = (char*)malloc(strlen(text) + 1);  // ADD CAST HERE
    if (str) {
        strcpy(str, text);
    }
    return str;
}
