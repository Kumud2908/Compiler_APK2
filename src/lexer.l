%{
#include <stdio.h>
#include <string.h>

int line_num = 1;

void print_token(const char *token, const char *lexeme) {
    printf("%-20s %s\n", token, lexeme);
}
%}

%%
[ \t]+                  ; // Ignore spaces/tabs
\n                      { line_num++; }
"//".*                  { print_token("COMMENT", yytext); }


"#include"[ \t]*"<"[^>]+">"   { print_token("SYSTEM_LIBRARY", yytext); }
"#include"[ \t]*\"[^\"]+\"    { print_token("USER_LIBRARY", yytext); }

"using"[ \t]+"namespace"[ \t]+[a-zA-Z_][a-zA-Z0-9_]*[ \t]*";" {
    print_token("USING_NAMESPACE", yytext);
}

"if"                    { print_token("IF_KEYWORD", yytext); }
"else"                  { print_token("ELSE_KEYWORD", yytext); }
"for"                   { print_token("FOR_KEYWORD", yytext); }
"while"                 { print_token("WHILE_KEYWORD", yytext); }
"do"                    { print_token("DO_KEYWORD", yytext); }
"switch"                { print_token("SWITCH_KEYWORD", yytext); }
"case"                  { print_token("CASE_KEYWORD", yytext); }
"default"               { print_token("DEFAULT_KEYWORD", yytext); }
"break"                 { print_token("BREAK_KEYWORD", yytext); }
"continue"              { print_token("CONTINUE_KEYWORD", yytext); }
"goto"                  { print_token("GOTO_KEYWORD", yytext); }
"static"                { print_token("STATIC_KEYWORD", yytext); }

"typedef"               { print_token("TYPEDEF_KEYWORD", yytext); }
"enum"                  { print_token("ENUM_KEYWORD", yytext); }
"union"                 { print_token("UNION_KEYWORD", yytext); }
"struct"                { print_token("STRUCT_KEYWORD", yytext); }

"printf"                { print_token("PRINTF_FUNC", yytext); }
"scanf"                 { print_token("SCANF_FUNC", yytext); }

"int"                   { print_token("TYPE_INT", yytext); }
"char"                  { print_token("TYPE_CHAR", yytext); }
"float"                 { print_token("TYPE_FLOAT", yytext); }
"double"                { print_token("TYPE_DOUBLE", yytext); }
"void"                  { print_token("TYPE_VOID", yytext); }
"bool"                  { print_token("TYPE_BOOL", yytext); }
"unsigned"              { print_token("TYPE_UNSIGNED", yytext); }
"long"                  { print_token("TYPE_LONG", yytext); }
"short"                 { print_token("TYPE_SHORT", yytext); }

"return"                { print_token("RETURN_KEYWORD", yytext); }

"=="                    { print_token("EQ_OP", yytext); }
"!="                    { print_token("NEQ_OP", yytext); }
"<="                    { print_token("LE_OP", yytext); }
">="                    { print_token("GE_OP", yytext); }
"&&"                    { print_token("LOGICAL_AND", yytext); }
"\|\|"                  { print_token("LOGICAL_OR", yytext); }
"!"                     { print_token("LOGICAL_NOT", yytext); }


"\+\+"                  { print_token("INCREMENT_OP", yytext); }
"--"                    { print_token("DECREMENT_OP", yytext); }
"\+="                   { print_token("PLUS_ASSIGN", yytext); }
"-="                    { print_token("MINUS_ASSIGN", yytext); }
"\*="                   { print_token("MULT_ASSIGN", yytext); }
"/="                    { print_token("DIV_ASSIGN", yytext); }
"%="                    { print_token("MOD_ASSIGN", yytext); }

"+"                     { print_token("PLUS_OP", yytext); }
"-"                     { print_token("MINUS_OP", yytext); }
"*"                     { print_token("MULT_OP", yytext); }
"/"                     { print_token("DIV_OP", yytext); }
"%"                     { print_token("MOD_OP", yytext); }
"="                     { print_token("ASSIGN_OP", yytext); }
"<"                     { print_token("LT_OP", yytext); }
">"                     { print_token("GT_OP", yytext); }

"&"                     { print_token("ADDRESS_OP", yytext); }
"\.\.\."                { print_token("ELLIPSIS_OP", yytext); } 
"\."                    { print_token("DOT_OP", yytext); }
"->"                    { print_token("ARROW_OP", yytext); }
","                     { print_token("COMMA", yytext); }
";"                     { print_token("SEMICOLON", yytext); }
":"                     { print_token("COLON", yytext); }
"\("                    { print_token("LPAREN", yytext); }
"\)"                    { print_token("RPAREN", yytext); }
"\{"                    { print_token("LBRACE", yytext); }
"\}"                    { print_token("RBRACE", yytext); }
"\["                    { print_token("LBRACKET", yytext); }
"\]"                    { print_token("RBRACKET", yytext); }

[0-9]+                  { print_token("INTEGER_LITERAL", yytext); }
[0-9]+"."[0-9]+         { print_token("FLOAT_LITERAL", yytext); }
\"([^\\\"]|\\.)*\"      { print_token("STRING_LITERAL", yytext); }
\'([^\\\']|\\.)\'       { print_token("CHAR_LITERAL", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  { print_token("IDENTIFIER", yytext); }



.                       { print_token("UNKNOWN", yytext); }
%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
    printf("%-20s %s\n", "Token", "Lexeme");
    printf("--------------------------------\n");
    yylex();
    return 0;
}
