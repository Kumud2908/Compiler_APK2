%{
#include "ast.h"
#include "symbol.h"
#include "semantic.h"
#include "tac.h"
#include "codegen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
  // Include your AST header

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

void yyerror(const char* s);

int syntax_errors = 0;
int parse_success = 1;
bool has_semantic_errors = false;


/* External declarations for lexer's token table */
typedef struct {
    char token[256];
    char token_type[64];
} TokenEntry;

extern TokenEntry token_table[];
extern int token_count;
extern int errors;
extern void print_token_table();


/* Global AST root */
ASTNode* root = NULL;
ASTNode* current_node = NULL;

SymbolTable* symbol_table = NULL;

/* AST helper functions */
ASTNode* create_node(const char* name, const char* lexeme = "") {
    return new ASTNode(name, lexeme, yylineno);
}

void push_node(ASTNode* node) {
    if (!root) {
        root = node;
    }
    if (current_node) {
        current_node->addChild(node);
    }
    current_node = node;
}

void pop_node() {
    if (current_node && current_node->parent) {
        current_node = current_node->parent;
    }
}

std::vector<std::string> parser_type_names;

void parser_add_type_name(const char* name) {
    parser_type_names.push_back(name);
}
int parser_is_type_name(const char* name) {
    for (const auto& type : parser_type_names) {
        if (type == name) {        
            return 1;
        }
    }
    return 0;
}
std::string extract_dec_name(ASTNode* node) {
    if (!node) return "unknown";
    
    // If current node has identifier, use it
    if (!node->lexeme.empty() && node->lexeme != "default") {
        return node->lexeme;
    }
    
    // For typedefs, we mainly care about DirectDeclarator
    if (node->name == "DirectDeclarator" && !node->lexeme.empty()) {
        return node->lexeme;
    }
    
    // Search in immediate children (no deep recursion needed for typedef names)
    for (size_t i = 0; i < node->children.size(); i++) {
        ASTNode* child = node->children[i];
        if (!child) continue;
        
        if (!child->lexeme.empty() && child->lexeme != "default") {
            return child->lexeme;
        }
    }
    
    return "unknown";
}
void collect_typedef_names(ASTNode* init_decl_list) {
    if (!init_decl_list) return;
    
    for (size_t i = 0; i < init_decl_list->children.size(); i++) {  // ← size_t
        ASTNode* init_decl = init_decl_list->children[i];
        if (!init_decl || init_decl->name != "InitDeclarator") continue;
        
        for (size_t j = 0; j < init_decl->children.size(); j++) {   // ← size_t
            ASTNode* decl = init_decl->children[j];
            if (!decl) continue;
            
            std::string name = extract_dec_name(decl);       // ← FIXED NAME
            if (!name.empty() && name != "unknown") {
                parser_add_type_name(name.c_str());
                printf("Added typedef name: %s\n", name.c_str());
            }
        }
    }
}

char current_type[64] = "int";
int in_function_params = 0;
int in_typedef_declaration = 0;

%}

%union {
    char* str;
    int num;
    ASTNode* node;
}

/* Token declarations */
%token <str> AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO
%token <str> DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF
%token <str> INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC
%token <str> STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
%token <str> NULL_TOKEN NULLPTR

/* C++ Keywords */
%token <str> CLASS PRIVATE PROTECTED PUBLIC VIRTUAL FRIEND INLINE
%token <str> OPERATOR OVERLOAD TEMPLATE THIS NEW DELETE NAMESPACE
%token <str> USING TRY CATCH THROW BOOL TRUE FALSE
%token <str> TYPEDEF_NAME

/* Identifiers and Literals */
%token <str> ID NUM FLOAT_LIT CHAR_LIT STRING_LIT

/* Operators */
%token <str> PLUS MINUS MUL DIV MOD
%token <str> ASSIGN PLUS_EQ MINUS_EQ MUL_EQ DIV_EQ MOD_EQ
%token <str> INC DEC
%token <str> EQ NE LT GT LE GE
%token <str> AND OR NOT
%token <str> BIT_AND BIT_OR BIT_XOR BIT_NOT LSHIFT RSHIFT
%token <str> AND_EQ OR_EQ XOR_EQ LSHIFT_EQ RSHIFT_EQ
%token <str> ARROW DOT SCOPE
%token <str> UNTIL

/* Punctuation */
%token <str> SEMI COMMA QUESTION COLON
%token <str> LPAREN RPAREN LBRACE RBRACE
%token <str> LBRACKET RBRACKET
%token <str> ELLIPSIS

/* Special */
%token <str> PREP NEWLINE END ERROR

%token DESTRUCTOR

/* Precedence and associativity */
%right ASSIGN PLUS_EQ MINUS_EQ MUL_EQ DIV_EQ MOD_EQ AND_EQ OR_EQ XOR_EQ LSHIFT_EQ RSHIFT_EQ
%right QUESTION COLON
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left EQ NE
%left LT GT LE GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left MUL DIV MOD
%right NOT BIT_NOT UMINUS UPLUS  /* Prefix operators */
%left INC DEC  /* Postfix operators - higher precedence than binary */
%left DOT ARROW
%left LBRACKET RBRACKET LPAREN RPAREN

%nonassoc IF_WITHOUT_ELSE
%nonassoc ELSE 

%start program

%type <str> type_keyword struct_or_union assignment_operator unary_operator
%type <node> program translation_unit external_declaration function_definition
%type <node> declaration declaration_specifiers storage_class_specifier type_specifier
%type <node> struct_or_union_specifier enum_specifier init_declarator_list init_declarator
%type <node> declarator pointer direct_declarator parameter_list parameter_declaration
%type <node> abstract_declarator direct_abstract_declarator type_name
%type <node> initializer initializer_list compound_statement block_item_list block_item
%type <node> statement labeled_statement expression_statement selection_statement
%type <node> iteration_statement jump_statement expression assignment_expression
%type <node> conditional_expression logical_or_expression logical_and_expression
%type <node> inclusive_or_expression exclusive_or_expression and_expression
%type <node> equality_expression relational_expression shift_expression
%type <node> additive_expression multiplicative_expression cast_expression
%type <node> unary_expression postfix_expression primary_expression constant
%type <node> string_literal argument_expression_list
%type <node> struct_declaration_list struct_declaration struct_declarator_list struct_declarator
%type <node> enumerator_list enumerator for_init_statement range_based_for
%type <node> preprocessor_directive

%%

program:
    translation_unit {
        $$ = $1;
    }
    ;

translation_unit:
    external_declaration {
        $$ = create_node("TranslationUnit");
        $$->addChild($1);
        root = $$;
    }
    | translation_unit external_declaration {
        $$ = $1;
        $$->addChild($2);
    }
    ;

external_declaration:
    function_definition {
        $$ = $1;
    }
    | declaration {
        $$ = $1;
    }
    | preprocessor_directive {
        $$ = $1;
    }
    ;

preprocessor_directive:
    PREP { $$ = create_node("Preprocessor", $1); }
    ;

function_definition:
    declaration_specifiers declarator compound_statement {
        $$ = create_node("FunctionDefinition");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        in_typedef_declaration = 0;
    }
    | declarator compound_statement {
        $$ = create_node("FunctionDefinition");
        $$->addChild($1);
        $$->addChild($2);
        in_typedef_declaration = 0;
    }
    ;

declaration:
    declaration_specifiers init_declarator_list SEMI {
        $$ = create_node("Declaration");
        $$->addChild($1);
        $$->addChild($2);
	if (in_typedef_declaration) {
            collect_typedef_names($2);
        }

        in_typedef_declaration = 0;
    }
    | declaration_specifiers SEMI {
        $$ = create_node("Declaration");
        $$->addChild($1);
        in_typedef_declaration = 0;
    }
    ;

declaration_specifiers:
    storage_class_specifier {
        $$ = create_node("DeclarationSpecifiers");
        $$->addChild($1);
    }
    | storage_class_specifier declaration_specifiers {
        $$ = create_node("DeclarationSpecifiers");
        $$->addChild($1);
        $$->addChild($2);
    }
    | type_specifier {
        $$ = create_node("DeclarationSpecifiers");
        $$->addChild($1);
    }
    | type_specifier declaration_specifiers {
        $$ = create_node("DeclarationSpecifiers");
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

storage_class_specifier:
    TYPEDEF {
        $$ = create_node("StorageClass", "typedef");
        in_typedef_declaration = 1;
    }
    | STATIC { $$ = create_node("StorageClass", "static"); }
    | EXTERN { $$ = create_node("StorageClass", "extern"); }
    | REGISTER { $$ = create_node("StorageClass", "register"); }
    | AUTO { $$ = create_node("StorageClass", "auto"); }
    ;

type_specifier:
    type_keyword {
        $$ = create_node("TypeSpecifier", $1);
        strcpy(current_type, $1);
    }
    | struct_or_union_specifier { $$ = $1; }
    | enum_specifier { $$ = $1; }
    | TYPEDEF_NAME {  // ← Now conflict-free!
        $$ = create_node("TypeSpecifier", $1);
        strcpy(current_type, $1);
    }
    ;

type_keyword:
    VOID { $$ = strdup("void"); }
    | CHAR { $$ = strdup("char"); }
    | SHORT { $$ = strdup("short"); }
    | INT { $$ = strdup("int"); }
    | LONG { $$ = strdup("long"); }
    | FLOAT { $$ = strdup("float"); }
    | DOUBLE { $$ = strdup("double"); }
    | SIGNED { $$ = strdup("signed"); }
    | UNSIGNED { $$ = strdup("unsigned"); }
    | BOOL { $$ = strdup("bool"); }
    ;

struct_or_union_specifier:
    struct_or_union ID LBRACE struct_declaration_list RBRACE {
        $$ = create_node("StructOrUnionSpecifier");
        $$->addChild(create_node("StructOrUnion", $1));
        $$->addChild(create_node("Identifier", $2));
        $$->addChild($4);
        parser_add_type_name($2);
    }
    | struct_or_union TYPEDEF_NAME LBRACE struct_declaration_list RBRACE {  // ← ADD THIS
        $$ = create_node("StructOrUnionSpecifier");
        $$->addChild(create_node("StructOrUnion", $1));
        $$->addChild(create_node("Identifier", $2));
        $$->addChild($4);
        parser_add_type_name($2);
    }
    | struct_or_union LBRACE struct_declaration_list RBRACE {
        $$ = create_node("StructOrUnionSpecifier");
        $$->addChild(create_node("StructOrUnion", $1));
        $$->addChild($3);
    }
    | struct_or_union ID {
        $$ = create_node("StructOrUnionSpecifier");
        $$->addChild(create_node("StructOrUnion", $1));
        $$->addChild(create_node("Identifier", $2));
        parser_add_type_name($2);
    }
    | struct_or_union TYPEDEF_NAME {  // ← ADD THIS
        $$ = create_node("StructOrUnionSpecifier");
        $$->addChild(create_node("StructOrUnion", $1));
        $$->addChild(create_node("Identifier", $2));
        parser_add_type_name($2);
    }
    ;

struct_or_union:
    STRUCT { $$ = strdup("struct"); }
    | UNION { $$ = strdup("union"); }
    ;

struct_declaration_list:
    struct_declaration {
        $$ = create_node("StructDeclarationList");
        $$->addChild($1);
    }
    | struct_declaration_list struct_declaration {
        $$ = $1;
        $$->addChild($2);
    }
    ;

struct_declaration:
    type_specifier struct_declarator_list SEMI {
        $$ = create_node("StructDeclaration");
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

struct_declarator_list:
    struct_declarator {
        $$ = create_node("StructDeclaratorList");
        $$->addChild($1);
    }
    | struct_declarator_list COMMA struct_declarator {
        $$ = $1;
        $$->addChild($3);
    }
    ;

struct_declarator:
    declarator { $$ = $1; }
    ;

enum_specifier:
    ENUM ID LBRACE enumerator_list RBRACE {
        $$ = create_node("EnumSpecifier");
        $$->addChild(create_node("Identifier", $2));
        $$->addChild($4);
        parser_add_type_name($2);
    }
    | ENUM TYPEDEF_NAME LBRACE enumerator_list RBRACE {  // ← ADD THIS
        $$ = create_node("EnumSpecifier");
        $$->addChild(create_node("Identifier", $2));
        $$->addChild($4);
        parser_add_type_name($2);
    }
    | ENUM LBRACE enumerator_list RBRACE {
        $$ = create_node("EnumSpecifier");
        $$->addChild($3);
    }
    | ENUM ID {
        $$ = create_node("EnumSpecifier");
        $$->addChild(create_node("Identifier", $2));
        parser_add_type_name($2);
    }
    | ENUM TYPEDEF_NAME {  // ← ADD THIS
        $$ = create_node("EnumSpecifier");
        $$->addChild(create_node("Identifier", $2));
        parser_add_type_name($2);
    }
    ;

enumerator_list:
    enumerator {
        $$ = create_node("EnumeratorList");
        $$->addChild($1);
    }
    | enumerator_list COMMA enumerator {
        $$ = $1;
        $$->addChild($3);
    }
    ;

enumerator:
    ID {
        $$ = create_node("Enumerator", $1);
    }
    | ID ASSIGN assignment_expression {
        $$ = create_node("Enumerator", $1);
        $$->addChild($3);
    }
    ;

init_declarator_list:
    init_declarator {
        $$ = create_node("InitDeclaratorList");
        $$->addChild($1);
    }
    | init_declarator_list COMMA init_declarator {
        $$ = $1;
        $$->addChild($3);
    }
    ;

init_declarator:
    declarator {
        $$ = create_node("InitDeclarator");
        $$->addChild($1);
    }
    | declarator ASSIGN initializer {
        $$ = create_node("InitDeclarator");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

declarator:
    pointer direct_declarator {
        $$ = create_node("Declarator");
        $$->addChild($1);
        $$->addChild($2);
    }
    | direct_declarator {
        $$ = $1;
    }
    | BIT_AND direct_declarator {    
        $$ = create_node("ReferenceDeclarator");
        $$->addChild($2);
    }
    | pointer BIT_AND direct_declarator {    
        $$ = create_node("ReferenceDeclarator");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

pointer:
    MUL {
        $$ = create_node("Pointer");
    }
    | MUL pointer {
        $$ = create_node("Pointer");
        $$->addChild($2);
    }
    ;

direct_declarator:
    ID {
        $$ = create_node("DirectDeclarator", $1);
    }
    | LPAREN declarator RPAREN {
        $$ = $2;
    }
    | direct_declarator LBRACKET assignment_expression RBRACKET {
        $$ = create_node("ArrayDeclarator");
        $$->addChild($1);
        $$->addChild($3);
    }
    | direct_declarator LBRACKET RBRACKET {
        $$ = create_node("ArrayDeclarator");
        $$->addChild($1);
    }
    | direct_declarator LPAREN {
        in_function_params = 1;
    } parameter_list RPAREN {
        $$ = create_node("FunctionDeclarator");
        $$->addChild($1);
        $$->addChild($4);
        in_function_params = 0;
    }
    | direct_declarator LPAREN RPAREN {
        $$ = create_node("FunctionDeclarator");
        $$->addChild($1);
        in_function_params = 0;
    }
    ;

parameter_list:
    parameter_declaration {
        $$ = create_node("ParameterList");
        $$->addChild($1);
    }
    | parameter_list COMMA parameter_declaration {
        $$ = $1;
        $$->addChild($3);
    }
    | parameter_list COMMA ELLIPSIS {
        $$ = $1;
        $$->addChild(create_node("Ellipsis"));
    }
    ;

parameter_declaration:
    declaration_specifiers declarator {
        $$ = create_node("ParameterDeclaration");
        $$->addChild($1);
        $$->addChild($2);
    }
    | declaration_specifiers abstract_declarator {
        $$ = create_node("ParameterDeclaration");
        $$->addChild($1);
        $$->addChild($2);
    }
    | declaration_specifiers {
        $$ = create_node("ParameterDeclaration");
        $$->addChild($1);
    }
    ;

abstract_declarator:
    pointer {
        $$ = create_node("AbstractDeclarator");
        $$->addChild($1);
    }
    | pointer direct_abstract_declarator {
        $$ = create_node("AbstractDeclarator");
        $$->addChild($1);
        $$->addChild($2);
    }
    | direct_abstract_declarator {
        $$ = create_node("AbstractDeclarator");
        $$->addChild($1);
    }
    | BIT_AND {    /* ADD THIS RULE */
        $$ = create_node("ReferenceDeclarator");
    }
    | BIT_AND direct_abstract_declarator {   
        $$ = create_node("ReferenceDeclarator");
        $$->addChild($2);
    }
    | pointer BIT_AND {    /* ADD THIS RULE */
        $$ = create_node("ReferenceDeclarator");
        $$->addChild($1);
    }
    | pointer BIT_AND direct_abstract_declarator {   
        $$ = create_node("ReferenceDeclarator");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

direct_abstract_declarator:
    LPAREN abstract_declarator RPAREN {
        $$ = $2;
    }
    | LBRACKET RBRACKET {
        $$ = create_node("ArrayAbstractDeclarator");
    }
    | LBRACKET assignment_expression RBRACKET {
        $$ = create_node("ArrayAbstractDeclarator");
        $$->addChild($2);
    }
    | direct_abstract_declarator LBRACKET RBRACKET {
        $$ = create_node("ArrayAbstractDeclarator");
        $$->addChild($1);
    }
    | direct_abstract_declarator LBRACKET assignment_expression RBRACKET {
        $$ = create_node("ArrayAbstractDeclarator");
        $$->addChild($1);
        $$->addChild($3);
    }
    | LPAREN RPAREN {
        $$ = create_node("FunctionAbstractDeclarator");
    }
    | LPAREN parameter_list RPAREN {
        $$ = create_node("FunctionAbstractDeclarator");
        $$->addChild($2);
    }
    | direct_abstract_declarator LPAREN RPAREN {
        $$ = create_node("FunctionAbstractDeclarator");
        $$->addChild($1);
    }
    | direct_abstract_declarator LPAREN parameter_list RPAREN {
        $$ = create_node("FunctionAbstractDeclarator");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

type_name:
    type_specifier {
        $$ = create_node("TypeName");
        $$->addChild($1);
    }
    | type_specifier abstract_declarator {
        $$ = create_node("TypeName");
        $$->addChild($1);
        $$->addChild($2);
    }
    ;

initializer:
    assignment_expression {
        $$ = create_node("Initializer");
        $$->addChild($1);
    }
    | LBRACE initializer_list RBRACE {
        $$ = create_node("InitializerList");
        $$->addChild($2);
    }
    | LBRACE initializer_list COMMA RBRACE {
        $$ = create_node("InitializerList");
        $$->addChild($2);
    }

    ;

initializer_list:
    initializer {
        $$ = create_node("InitializerList");
        $$->addChild($1);
    }
    | initializer_list COMMA initializer {
        $$ = $1;
        $$->addChild($3);
    }
    ;

compound_statement:
    LBRACE RBRACE {
        $$ = create_node("CompoundStatement");
    }
    | LBRACE block_item_list RBRACE {
        $$ = create_node("CompoundStatement");
        $$->addChild($2);
    }
    ;

block_item_list:
    block_item {
        $$ = create_node("BlockItemList");
        $$->addChild($1);
    }
    | block_item_list block_item {
        $$ = $1;
        $$->addChild($2);
    }
    ;

block_item:
    declaration {
        $$ = create_node("BlockItem");
        $$->addChild($1);
    }
    | statement {
        $$ = create_node("BlockItem");
        $$->addChild($1);
    }
    ;

statement:
    labeled_statement { $$ = $1; }
    | expression_statement { $$ = $1; }
    | compound_statement { $$ = $1; }
    | selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; }
    | jump_statement { $$ = $1; }
    ;

labeled_statement:
    ID COLON statement {
        $$ = create_node("LabeledStatement", $1);
        $$->addChild($3);
    }
    | CASE assignment_expression COLON statement {
        $$ = create_node("CaseStatement");
        $$->addChild($2);
        $$->addChild($4);
    }
    | DEFAULT COLON statement {
        $$ = create_node("DefaultStatement");
        $$->addChild($3);
    }
    ;

expression_statement:
    expression SEMI {
        $$ = create_node("ExpressionStatement");
        $$->addChild($1);
    }
    | SEMI {
        $$ = create_node("EmptyStatement");
    }
    ;

selection_statement:
    IF LPAREN expression RPAREN statement %prec IF_WITHOUT_ELSE {
        $$ = create_node("IfStatement");
        $$->addChild($3);
        $$->addChild($5);
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = create_node("IfStatement");
        $$->addChild($3);
        $$->addChild($5);
        $$->addChild($7);
    }
    | SWITCH LPAREN expression RPAREN statement {
        $$ = create_node("SwitchStatement");
        $$->addChild($3);
        $$->addChild($5);
    }
    ;

iteration_statement:
    WHILE LPAREN expression RPAREN statement {
        $$ = create_node("WhileStatement");
        $$->addChild($3);
        $$->addChild($5);
    }
    | DO statement WHILE LPAREN expression RPAREN SEMI {
        $$ = create_node("DoWhileStatement");
        $$->addChild($2);
        $$->addChild($5);
    }
    | UNTIL LPAREN expression RPAREN statement {  
        $$ = create_node("UntilStatement");
        $$->addChild($3);
        $$->addChild($5);
    }
    | FOR LPAREN for_init_statement expression_statement RPAREN statement {
        $$ = create_node("ForStatement");
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($6);
    }
    | FOR LPAREN for_init_statement expression_statement expression RPAREN statement {
        $$ = create_node("ForStatement");
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->addChild($7);
    }
    | FOR LPAREN range_based_for RPAREN statement {
        $$ = create_node("RangeBasedForStatement");
        $$->addChild($3);
        $$->addChild($5);
    }
    ;

for_init_statement:
    expression_statement {
        $$ = create_node("ForInitStatement");
        $$->addChild($1);
    }
    | declaration {
        $$ = create_node("ForInitStatement");
        $$->addChild($1);
    }
    ;

range_based_for:
    declaration_specifiers ID COLON expression {
        $$ = create_node("RangeBasedFor");
        $$->addChild($1);
        $$->addChild(create_node("Identifier", $2));
        $$->addChild($4);
    }
    | declaration_specifiers BIT_AND ID COLON expression {
        $$ = create_node("RangeBasedFor");
        $$->addChild($1);
        $$->addChild(create_node("Reference"));
        $$->addChild(create_node("Identifier", $3));
        $$->addChild($5);
    }
    ;

jump_statement:
    GOTO ID SEMI {
        $$ = create_node("GotoStatement", $2);
    }
    | CONTINUE SEMI {
        $$ = create_node("ContinueStatement");
    }
    | BREAK SEMI {
        $$ = create_node("BreakStatement");
    }
    | RETURN expression SEMI {
        $$ = create_node("ReturnStatement");
        $$->addChild($2);
    }
    | RETURN SEMI {
        $$ = create_node("ReturnStatement");
    }
    ;

expression:
    assignment_expression {
        $$ = $1;
    }
    | expression COMMA assignment_expression {
        $$ = create_node("CommaExpression");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

assignment_expression:
    conditional_expression {
        $$ = $1;
    }
    | unary_expression assignment_operator assignment_expression {
        $$ = create_node("AssignmentExpression", $2);
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

assignment_operator:
    ASSIGN { $$ = strdup("="); }
    | PLUS_EQ { $$ = strdup("+="); }
    | MINUS_EQ { $$ = strdup("-="); }
    | MUL_EQ { $$ = strdup("*="); }
    | DIV_EQ { $$ = strdup("/="); }
    | MOD_EQ { $$ = strdup("%="); }
    | AND_EQ { $$ = strdup("&="); }
    | OR_EQ { $$ = strdup("|="); }
    | XOR_EQ { $$ = strdup("^="); }
    | LSHIFT_EQ { $$ = strdup("<<="); }
    | RSHIFT_EQ { $$ = strdup(">>="); }
    ;

conditional_expression:
    logical_or_expression {
        $$ = $1;
    }
    | logical_or_expression QUESTION expression COLON conditional_expression {
        $$ = create_node("ConditionalExpression");
        $$->addChild($1);
        $$->addChild($3);
        $$->addChild($5);
    }
    ;

logical_or_expression:
    logical_and_expression {
        $$ = $1;
    }
    | logical_or_expression OR logical_and_expression {
        $$ = create_node("LogicalOrExpression", "||");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

logical_and_expression:
    inclusive_or_expression {
        $$ = $1;
    }
    | logical_and_expression AND inclusive_or_expression {
        $$ = create_node("LogicalAndExpression","&&");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

inclusive_or_expression:
    exclusive_or_expression {
        $$ = $1;
    }
    | inclusive_or_expression BIT_OR exclusive_or_expression {
        $$ = create_node("InclusiveOrExpression","|");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

exclusive_or_expression:
    and_expression {
        $$ = $1;
    }
    | exclusive_or_expression BIT_XOR and_expression {
        $$ = create_node("ExclusiveOrExpression","^");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

and_expression:
    equality_expression {
        $$ = $1;
    }
    | and_expression BIT_AND equality_expression {
        $$ = create_node("AndExpression","&");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

equality_expression:
    relational_expression {
        $$ = $1;
    }
    | equality_expression EQ relational_expression {
        $$ = create_node("EqualityExpression", "==");
        $$->addChild($1);
        $$->addChild($3);
    }
    | equality_expression NE relational_expression {
        $$ = create_node("EqualityExpression", "!=");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

relational_expression:
    shift_expression {
        $$ = $1;
    }
    | relational_expression LT shift_expression {
        $$ = create_node("RelationalExpression", "<");
        $$->addChild($1);
        $$->addChild($3);
    }
    | relational_expression GT shift_expression {
        $$ = create_node("RelationalExpression", ">");
        $$->addChild($1);
        $$->addChild($3);
    }
    | relational_expression LE shift_expression {
        $$ = create_node("RelationalExpression", "<=");
        $$->addChild($1);
        $$->addChild($3);
    }
    | relational_expression GE shift_expression {
        $$ = create_node("RelationalExpression", ">=");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

shift_expression:
    additive_expression {
        $$ = $1;
    }
    | shift_expression LSHIFT additive_expression {
        $$ = create_node("ShiftExpression", "<<");
        $$->addChild($1);
        $$->addChild($3);
    }
    | shift_expression RSHIFT additive_expression {
        $$ = create_node("ShiftExpression", ">>");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

additive_expression:
    multiplicative_expression {
        $$ = $1;
    }
    | additive_expression PLUS multiplicative_expression {
        $$ = create_node("AdditiveExpression", "+");
        $$->addChild($1);
        $$->addChild($3);
    }
    | additive_expression MINUS multiplicative_expression {
        $$ = create_node("AdditiveExpression", "-");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

multiplicative_expression:
    cast_expression {
        $$ = $1;
    }
    | multiplicative_expression MUL cast_expression {
        $$ = create_node("MultiplicativeExpression", "*");
        $$->addChild($1);
        $$->addChild($3);
    }
    | multiplicative_expression DIV cast_expression {
        $$ = create_node("MultiplicativeExpression", "/");
        $$->addChild($1);
        $$->addChild($3);
    }
    | multiplicative_expression MOD cast_expression {
        $$ = create_node("MultiplicativeExpression", "%");
        $$->addChild($1);
        $$->addChild($3);
    }
    ;

cast_expression:
    unary_expression {
        $$ = $1;
    }
    | LPAREN type_name RPAREN cast_expression {
        $$ = create_node("CastExpression");
        $$->addChild($2);
        $$->addChild($4);
    }
    ;

unary_expression:
    postfix_expression {
        $$ = $1;
    }
    | INC unary_expression {
        $$ = create_node("UnaryExpression", "++");
        $$->addChild($2);
    }
    | DEC unary_expression {
        $$ = create_node("UnaryExpression", "--");
        $$->addChild($2);
    }
    | unary_operator cast_expression {
        $$ = create_node("UnaryExpression", $1);
        $$->addChild($2);
    }
    | SIZEOF unary_expression {
        $$ = create_node("SizeOfExpression");
        $$->addChild($2);
    }
    | SIZEOF LPAREN type_name RPAREN {
        $$ = create_node("SizeOfExpression");
        $$->addChild($3);
    }
    ;

unary_operator:
    BIT_AND { $$ = strdup("&"); }
    | MUL { $$ = strdup("*"); }
    | PLUS { $$ = strdup("+"); }
    | MINUS { $$ = strdup("-"); }
    | BIT_NOT { $$ = strdup("~"); }
    | NOT { $$ = strdup("!"); }
    ;

postfix_expression:
    primary_expression {
        $$ = $1;
    }
    | postfix_expression LBRACKET expression RBRACKET {
        $$ = create_node("ArraySubscript");
        $$->addChild($1);
        $$->addChild($3);
    }
    | postfix_expression LPAREN argument_expression_list RPAREN {
        $$ = create_node("FunctionCall");
        $$->addChild($1);
        $$->addChild($3);
    }
    | postfix_expression LPAREN RPAREN {
        $$ = create_node("FunctionCall");
        $$->addChild($1);
    }
    | postfix_expression DOT ID {
        $$ = create_node("MemberAccess", ".");
        $$->addChild($1);
        $$->addChild(create_node("Identifier", $3));
    }
    | postfix_expression ARROW ID {
        $$ = create_node("MemberAccess", "->");
        $$->addChild($1);
        $$->addChild(create_node("Identifier", $3));
    }
    | postfix_expression INC {
        $$ = create_node("PostfixExpression", "++");
        $$->addChild($1);
    }
    | postfix_expression DEC {
        $$ = create_node("PostfixExpression", "--");
        $$->addChild($1);
    }
    ;

primary_expression:
    ID {
        $$ = create_node("Identifier", $1);
    }
    | constant {
        $$ = $1;
    }
    | string_literal {
        $$ = $1;
    }
    | LPAREN expression RPAREN {
        $$ = $2;
    }
    ;

string_literal:
    STRING_LIT {
        $$ = create_node("StringLiteral", $1);
    }
    | string_literal STRING_LIT {
        $$ = create_node("StringLiteral");
        $$->addChild($1);
        $$->addChild(create_node("StringLiteral", $2));
    }
    ;

argument_expression_list:
    assignment_expression {
        $$ = create_node("ArgumentList");
        $$->addChild($1);
    }
    | argument_expression_list COMMA assignment_expression {
        $$ = $1;
        $$->addChild($3);
    }
    ;

constant:
    NUM { $$ = create_node("Constant", $1); }
    | FLOAT_LIT { $$ = create_node("Constant", $1); }
    | CHAR_LIT { $$ = create_node("Constant", $1); }
    | TRUE { $$ = create_node("Constant", "true"); }
    | FALSE { $$ = create_node("Constant", "false"); }
    | NULL_TOKEN { $$ = create_node("Constant", "NULL"); }           // ← Use NULL directly
    | NULLPTR { $$ = create_node("Constant", "nullptr"); }  
    ;

%%

void yyerror(const char* s) {
    syntax_errors++;
    parse_success = 0;
    printf("SYNTAX ERROR at line %d: %s\n", yylineno, s);
    if (yytext) {
        printf("Near token: '%s'\n", yytext);
    }
}
int main(int argc, char* argv[]) {
    
    symbol_table = new SymbolTable();

    FILE* file = stdin;
    
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    printf("C/C++ Syntax Analyzer with AST\n");
    printf("==============================\n\n");
    
    int result = yyparse();
    
    if (file != stdin) {
        fclose(file);
    }
    
    if (syntax_errors == 0 && result == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        
        // SEMANTIC ANALYSIS
        printf("\n=== SEMANTIC ANALYSIS ===\n");
        has_semantic_errors = false;  // Reset flag
        
        SemanticAnalyzer analyzer(symbol_table);
        analyzer.analyze(root);
        
        // Print symbol table
        symbol_table->print_table();

        
        // CHECK THE FLAG
        if (has_semantic_errors) {
            printf("\n");
            printf("==================================================\n");
            printf("COMPILATION FAILED\n");
            printf("==================================================\n");
            printf("Semantic errors found (see above)\n");
            printf("Code generation has been skipped.\n");
            printf("Please fix the errors and recompile.\n");
            printf("==================================================\n");
            
            // Clean up and exit
            if (root) delete root;
            delete symbol_table;
            return 1;
        }
        
        printf("\n Semantic analysis passed with no errors.\n");
        
        // THREE ADDRESS CODE GENERATION
        printf("\n=== CODE GENERATION ===\n");
        TACGenerator tac_gen;
        CodeGenerator code_gen(&tac_gen);
        
        code_gen.generate(root);
        tac_gen.print();
        
        // Print AST
        if (root) {
            printf("\n=== ABSTRACT SYNTAX TREE ===\n");
            root->printTree();
            
            // Generate DOT file
            std::ofstream dotFile("ast.dot");
            if (dotFile.is_open()) {
                int nodeId = 0;
                dotFile << "digraph AST {\n";
                root->generateDOT(dotFile, nodeId);
                dotFile << "}\n";
                dotFile.close();
                printf("\nAST DOT file generated: ast.dot\n");
            }
            
            // Generate TAC output file
            std::ofstream tacFile("output.tac");
            if (tacFile.is_open()) {
                for (const auto& instr : tac_gen.get_instructions()) {
                    tacFile << instr.toString() << std::endl;
                }
                tacFile.close();
                printf("TAC file generated: output.tac\n");
            }
            
            printf("\n");
            printf("==================================================\n");
            printf("COMPILATION SUCCESSFUL\n");
            printf("==================================================\n");
        }
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Total syntax errors: %d\n", syntax_errors);
        
        if (root) delete root;
        delete symbol_table;
        return 1;
    }
    
    // Clean up
    if (root) delete root;
    delete symbol_table;
    
    return 0;
}