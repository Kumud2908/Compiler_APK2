/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include "ast.h"
#include "symbol.h"
#include "semantic.h"
#include "tac.h"
#include "codegen.h"
#include "mips.h"

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


#line 200 "build/parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_AUTO = 3,                       /* AUTO  */
  YYSYMBOL_BREAK = 4,                      /* BREAK  */
  YYSYMBOL_CASE = 5,                       /* CASE  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_CONST = 7,                      /* CONST  */
  YYSYMBOL_CONTINUE = 8,                   /* CONTINUE  */
  YYSYMBOL_DEFAULT = 9,                    /* DEFAULT  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_DOUBLE = 11,                    /* DOUBLE  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_ENUM = 13,                      /* ENUM  */
  YYSYMBOL_EXTERN = 14,                    /* EXTERN  */
  YYSYMBOL_FLOAT = 15,                     /* FLOAT  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_GOTO = 17,                      /* GOTO  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_INT = 19,                       /* INT  */
  YYSYMBOL_LONG = 20,                      /* LONG  */
  YYSYMBOL_REGISTER = 21,                  /* REGISTER  */
  YYSYMBOL_RETURN = 22,                    /* RETURN  */
  YYSYMBOL_SHORT = 23,                     /* SHORT  */
  YYSYMBOL_SIGNED = 24,                    /* SIGNED  */
  YYSYMBOL_SIZEOF = 25,                    /* SIZEOF  */
  YYSYMBOL_STATIC = 26,                    /* STATIC  */
  YYSYMBOL_STRUCT = 27,                    /* STRUCT  */
  YYSYMBOL_SWITCH = 28,                    /* SWITCH  */
  YYSYMBOL_TYPEDEF = 29,                   /* TYPEDEF  */
  YYSYMBOL_UNION = 30,                     /* UNION  */
  YYSYMBOL_UNSIGNED = 31,                  /* UNSIGNED  */
  YYSYMBOL_VOID = 32,                      /* VOID  */
  YYSYMBOL_VOLATILE = 33,                  /* VOLATILE  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_NULL_TOKEN = 35,                /* NULL_TOKEN  */
  YYSYMBOL_NULLPTR = 36,                   /* NULLPTR  */
  YYSYMBOL_CLASS = 37,                     /* CLASS  */
  YYSYMBOL_PRIVATE = 38,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 39,                 /* PROTECTED  */
  YYSYMBOL_PUBLIC = 40,                    /* PUBLIC  */
  YYSYMBOL_VIRTUAL = 41,                   /* VIRTUAL  */
  YYSYMBOL_FRIEND = 42,                    /* FRIEND  */
  YYSYMBOL_INLINE = 43,                    /* INLINE  */
  YYSYMBOL_OPERATOR = 44,                  /* OPERATOR  */
  YYSYMBOL_OVERLOAD = 45,                  /* OVERLOAD  */
  YYSYMBOL_TEMPLATE = 46,                  /* TEMPLATE  */
  YYSYMBOL_THIS = 47,                      /* THIS  */
  YYSYMBOL_NEW = 48,                       /* NEW  */
  YYSYMBOL_DELETE = 49,                    /* DELETE  */
  YYSYMBOL_NAMESPACE = 50,                 /* NAMESPACE  */
  YYSYMBOL_USING = 51,                     /* USING  */
  YYSYMBOL_TRY = 52,                       /* TRY  */
  YYSYMBOL_CATCH = 53,                     /* CATCH  */
  YYSYMBOL_THROW = 54,                     /* THROW  */
  YYSYMBOL_BOOL = 55,                      /* BOOL  */
  YYSYMBOL_TRUE = 56,                      /* TRUE  */
  YYSYMBOL_FALSE = 57,                     /* FALSE  */
  YYSYMBOL_TYPEDEF_NAME = 58,              /* TYPEDEF_NAME  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_NUM = 60,                       /* NUM  */
  YYSYMBOL_FLOAT_LIT = 61,                 /* FLOAT_LIT  */
  YYSYMBOL_CHAR_LIT = 62,                  /* CHAR_LIT  */
  YYSYMBOL_STRING_LIT = 63,                /* STRING_LIT  */
  YYSYMBOL_PLUS = 64,                      /* PLUS  */
  YYSYMBOL_MINUS = 65,                     /* MINUS  */
  YYSYMBOL_MUL = 66,                       /* MUL  */
  YYSYMBOL_DIV = 67,                       /* DIV  */
  YYSYMBOL_MOD = 68,                       /* MOD  */
  YYSYMBOL_ASSIGN = 69,                    /* ASSIGN  */
  YYSYMBOL_PLUS_EQ = 70,                   /* PLUS_EQ  */
  YYSYMBOL_MINUS_EQ = 71,                  /* MINUS_EQ  */
  YYSYMBOL_MUL_EQ = 72,                    /* MUL_EQ  */
  YYSYMBOL_DIV_EQ = 73,                    /* DIV_EQ  */
  YYSYMBOL_MOD_EQ = 74,                    /* MOD_EQ  */
  YYSYMBOL_INC = 75,                       /* INC  */
  YYSYMBOL_DEC = 76,                       /* DEC  */
  YYSYMBOL_EQ = 77,                        /* EQ  */
  YYSYMBOL_NE = 78,                        /* NE  */
  YYSYMBOL_LT = 79,                        /* LT  */
  YYSYMBOL_GT = 80,                        /* GT  */
  YYSYMBOL_LE = 81,                        /* LE  */
  YYSYMBOL_GE = 82,                        /* GE  */
  YYSYMBOL_AND = 83,                       /* AND  */
  YYSYMBOL_OR = 84,                        /* OR  */
  YYSYMBOL_NOT = 85,                       /* NOT  */
  YYSYMBOL_BIT_AND = 86,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 87,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 88,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 89,                   /* BIT_NOT  */
  YYSYMBOL_LSHIFT = 90,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 91,                    /* RSHIFT  */
  YYSYMBOL_AND_EQ = 92,                    /* AND_EQ  */
  YYSYMBOL_OR_EQ = 93,                     /* OR_EQ  */
  YYSYMBOL_XOR_EQ = 94,                    /* XOR_EQ  */
  YYSYMBOL_LSHIFT_EQ = 95,                 /* LSHIFT_EQ  */
  YYSYMBOL_RSHIFT_EQ = 96,                 /* RSHIFT_EQ  */
  YYSYMBOL_ARROW = 97,                     /* ARROW  */
  YYSYMBOL_DOT = 98,                       /* DOT  */
  YYSYMBOL_SCOPE = 99,                     /* SCOPE  */
  YYSYMBOL_UNTIL = 100,                    /* UNTIL  */
  YYSYMBOL_SEMI = 101,                     /* SEMI  */
  YYSYMBOL_COMMA = 102,                    /* COMMA  */
  YYSYMBOL_QUESTION = 103,                 /* QUESTION  */
  YYSYMBOL_COLON = 104,                    /* COLON  */
  YYSYMBOL_LPAREN = 105,                   /* LPAREN  */
  YYSYMBOL_RPAREN = 106,                   /* RPAREN  */
  YYSYMBOL_LBRACE = 107,                   /* LBRACE  */
  YYSYMBOL_RBRACE = 108,                   /* RBRACE  */
  YYSYMBOL_LBRACKET = 109,                 /* LBRACKET  */
  YYSYMBOL_RBRACKET = 110,                 /* RBRACKET  */
  YYSYMBOL_ELLIPSIS = 111,                 /* ELLIPSIS  */
  YYSYMBOL_PREP = 112,                     /* PREP  */
  YYSYMBOL_NEWLINE = 113,                  /* NEWLINE  */
  YYSYMBOL_END = 114,                      /* END  */
  YYSYMBOL_ERROR = 115,                    /* ERROR  */
  YYSYMBOL_DESTRUCTOR = 116,               /* DESTRUCTOR  */
  YYSYMBOL_UMINUS = 117,                   /* UMINUS  */
  YYSYMBOL_UPLUS = 118,                    /* UPLUS  */
  YYSYMBOL_IF_WITHOUT_ELSE = 119,          /* IF_WITHOUT_ELSE  */
  YYSYMBOL_YYACCEPT = 120,                 /* $accept  */
  YYSYMBOL_program = 121,                  /* program  */
  YYSYMBOL_translation_unit = 122,         /* translation_unit  */
  YYSYMBOL_external_declaration = 123,     /* external_declaration  */
  YYSYMBOL_preprocessor_directive = 124,   /* preprocessor_directive  */
  YYSYMBOL_function_definition = 125,      /* function_definition  */
  YYSYMBOL_declaration = 126,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 127,   /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 128,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 129,           /* type_specifier  */
  YYSYMBOL_type_keyword = 130,             /* type_keyword  */
  YYSYMBOL_struct_or_union_specifier = 131, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 132,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 133,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 134,       /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 135,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 136,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 137,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 138,          /* enumerator_list  */
  YYSYMBOL_enumerator = 139,               /* enumerator  */
  YYSYMBOL_init_declarator_list = 140,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 141,          /* init_declarator  */
  YYSYMBOL_declarator = 142,               /* declarator  */
  YYSYMBOL_pointer = 143,                  /* pointer  */
  YYSYMBOL_direct_declarator = 144,        /* direct_declarator  */
  YYSYMBOL_145_1 = 145,                    /* $@1  */
  YYSYMBOL_parameter_list = 146,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 147,    /* parameter_declaration  */
  YYSYMBOL_abstract_declarator = 148,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 149, /* direct_abstract_declarator  */
  YYSYMBOL_type_name = 150,                /* type_name  */
  YYSYMBOL_initializer = 151,              /* initializer  */
  YYSYMBOL_initializer_list = 152,         /* initializer_list  */
  YYSYMBOL_compound_statement = 153,       /* compound_statement  */
  YYSYMBOL_block_item_list = 154,          /* block_item_list  */
  YYSYMBOL_block_item = 155,               /* block_item  */
  YYSYMBOL_statement = 156,                /* statement  */
  YYSYMBOL_labeled_statement = 157,        /* labeled_statement  */
  YYSYMBOL_expression_statement = 158,     /* expression_statement  */
  YYSYMBOL_selection_statement = 159,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 160,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 161,       /* for_init_statement  */
  YYSYMBOL_range_based_for = 162,          /* range_based_for  */
  YYSYMBOL_jump_statement = 163,           /* jump_statement  */
  YYSYMBOL_expression = 164,               /* expression  */
  YYSYMBOL_assignment_expression = 165,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 166,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 167,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 168,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 169,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 170,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 171,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 172,           /* and_expression  */
  YYSYMBOL_equality_expression = 173,      /* equality_expression  */
  YYSYMBOL_relational_expression = 174,    /* relational_expression  */
  YYSYMBOL_shift_expression = 175,         /* shift_expression  */
  YYSYMBOL_additive_expression = 176,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 177, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 178,          /* cast_expression  */
  YYSYMBOL_unary_expression = 179,         /* unary_expression  */
  YYSYMBOL_unary_operator = 180,           /* unary_operator  */
  YYSYMBOL_postfix_expression = 181,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 182,       /* primary_expression  */
  YYSYMBOL_string_literal = 183,           /* string_literal  */
  YYSYMBOL_argument_expression_list = 184, /* argument_expression_list  */
  YYSYMBOL_constant = 185                  /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1895

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  120
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  223
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  373

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   374


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   219,   219,   225,   230,   237,   240,   243,   249,   253,
     260,   269,   279,   287,   291,   296,   300,   308,   312,   313,
     314,   315,   319,   323,   324,   325,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   345,   352,   359,   364,
     370,   379,   380,   384,   388,   395,   403,   407,   414,   418,
     424,   430,   434,   439,   447,   451,   458,   461,   468,   472,
     479,   483,   491,   496,   499,   503,   511,   514,   521,   524,
     527,   532,   536,   536,   544,   552,   556,   560,   567,   572,
     577,   584,   588,   593,   597,   600,   604,   608,   616,   619,
     622,   626,   630,   635,   638,   642,   646,   654,   658,   666,
     670,   674,   678,   686,   690,   697,   700,   707,   711,   718,
     722,   729,   730,   731,   732,   733,   734,   738,   742,   747,
     754,   758,   767,   771,   777,   782,   788,   796,   801,   806,
     811,   817,   824,   832,   836,   843,   849,   859,   862,   865,
     868,   872,   878,   881,   889,   892,   900,   901,   902,   903,
     904,   905,   906,   907,   908,   909,   910,   914,   917,   926,
     929,   937,   940,   948,   951,   959,   962,   970,   973,   981,
     984,   989,   997,  1000,  1005,  1010,  1015,  1023,  1026,  1031,
    1039,  1042,  1047,  1055,  1058,  1063,  1068,  1076,  1079,  1087,
    1090,  1094,  1098,  1102,  1106,  1113,  1114,  1115,  1116,  1117,
    1118,  1122,  1125,  1130,  1135,  1139,  1144,  1149,  1153,  1160,
    1163,  1166,  1169,  1175,  1178,  1186,  1190,  1197,  1198,  1199,
    1200,  1201,  1202,  1203
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "AUTO", "BREAK",
  "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE",
  "ENUM", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INT", "LONG",
  "REGISTER", "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT",
  "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", "VOID", "VOLATILE", "WHILE",
  "NULL_TOKEN", "NULLPTR", "CLASS", "PRIVATE", "PROTECTED", "PUBLIC",
  "VIRTUAL", "FRIEND", "INLINE", "OPERATOR", "OVERLOAD", "TEMPLATE",
  "THIS", "NEW", "DELETE", "NAMESPACE", "USING", "TRY", "CATCH", "THROW",
  "BOOL", "TRUE", "FALSE", "TYPEDEF_NAME", "ID", "NUM", "FLOAT_LIT",
  "CHAR_LIT", "STRING_LIT", "PLUS", "MINUS", "MUL", "DIV", "MOD", "ASSIGN",
  "PLUS_EQ", "MINUS_EQ", "MUL_EQ", "DIV_EQ", "MOD_EQ", "INC", "DEC", "EQ",
  "NE", "LT", "GT", "LE", "GE", "AND", "OR", "NOT", "BIT_AND", "BIT_OR",
  "BIT_XOR", "BIT_NOT", "LSHIFT", "RSHIFT", "AND_EQ", "OR_EQ", "XOR_EQ",
  "LSHIFT_EQ", "RSHIFT_EQ", "ARROW", "DOT", "SCOPE", "UNTIL", "SEMI",
  "COMMA", "QUESTION", "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "ELLIPSIS", "PREP", "NEWLINE", "END", "ERROR",
  "DESTRUCTOR", "UMINUS", "UPLUS", "IF_WITHOUT_ELSE", "$accept", "program",
  "translation_unit", "external_declaration", "preprocessor_directive",
  "function_definition", "declaration", "declaration_specifiers",
  "storage_class_specifier", "type_specifier", "type_keyword",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "enumerator_list", "enumerator", "init_declarator_list",
  "init_declarator", "declarator", "pointer", "direct_declarator", "$@1",
  "parameter_list", "parameter_declaration", "abstract_declarator",
  "direct_abstract_declarator", "type_name", "initializer",
  "initializer_list", "compound_statement", "block_item_list",
  "block_item", "statement", "labeled_statement", "expression_statement",
  "selection_statement", "iteration_statement", "for_init_statement",
  "range_based_for", "jump_statement", "expression",
  "assignment_expression", "assignment_operator", "conditional_expression",
  "logical_or_expression", "logical_and_expression",
  "inclusive_or_expression", "exclusive_or_expression", "and_expression",
  "equality_expression", "relational_expression", "shift_expression",
  "additive_expression", "multiplicative_expression", "cast_expression",
  "unary_expression", "unary_operator", "postfix_expression",
  "primary_expression", "string_literal", "argument_expression_list",
  "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-255)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     289,  -255,  -255,  -255,    17,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,   -46,   -45,   -12,  -255,    30,   289,  -255,  -255,  -255,
    -255,    49,  1808,  1808,  -255,  -255,    26,  -255,   -58,    39,
     -63,   -52,   -42,   -24,  -255,   -63,   -62,  -255,  -255,  -255,
     118,  -255,   -54,  -255,  -255,   -35,   -11,  1837,   522,  -255,
     -45,   -63,    42,  1168,   -24,   -24,    82,   -77,  -255,  -255,
    -255,   -12,  1434,  -255,  1837,  1837,   -12,  1029,  -255,    59,
     429,    80,    84,   808,    86,   114,   106,  1590,  1684,   123,
     131,  -255,  -255,  -255,  -255,   128,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  1731,  1731,  -255,  -255,  -255,   156,  -255,
    1121,  -255,  -255,    49,  -255,   628,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,   139,  -255,  -255,   -66,   161,   182,   193,
     192,    41,   144,   152,   181,    71,  -255,   180,   429,    67,
    -255,   219,  -255,   -63,  -255,  1808,  -255,  -255,   186,     9,
      14,   429,   -24,  -255,  -255,   221,  1324,  -255,  -255,  1058,
    1080,   155,  -255,  -255,  -255,  -255,  -255,   194,  -255,   734,
     263,   961,   198,   429,  -255,   158,  1121,  -255,   429,   429,
     808,   429,  -255,  -255,   429,    40,   199,   -19,  -255,  -255,
    -255,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,   429,  -255,  -255,  -255,  -255,   247,   248,  1486,
     429,  -255,     5,    55,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,    19,  -255,  -255,  -255,   -12,   734,  -255,  -255,
     206,  -255,    54,  -255,  1637,   211,  -255,    56,  -255,   216,
      61,    68,  -255,    69,    75,   415,  1220,   -53,  -255,    77,
     429,  -255,  -255,   161,   127,   182,   193,   192,    41,   144,
     144,   152,   152,   152,   152,   181,   181,    71,    71,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,    81,   -51,   -48,
     393,  -255,   -47,  -255,   347,  -255,  1379,  -255,  -255,  -255,
    -255,   429,   220,   -36,  1538,   808,   808,  -255,   808,   808,
     808,    77,  -255,   107,   217,  -255,   215,    75,    77,   908,
    1272,  -255,   429,   429,  -255,  -255,   -48,  -255,  -255,  -255,
    -255,   110,   429,   222,   808,   112,  -255,   315,  -255,  -255,
    -255,  -255,  -255,  -255,    77,  -255,   115,  -255,   218,  -255,
    -255,   228,   229,   429,  -255,   808,   808,  -255,  -255,  -255,
     229,  -255,  -255
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    21,    27,    32,     0,    19,    31,    29,    30,    20,
      28,    33,    18,    41,    17,    42,    34,    26,    35,    25,
      68,    66,     0,     0,     8,     0,     2,     3,     7,     5,
       6,     0,    13,    15,    22,    23,     0,    24,     0,     0,
      63,    53,    52,     0,    67,    64,     0,     1,     4,    12,
       0,    58,    60,    14,    16,    40,    39,     0,     0,    10,
       0,    62,    72,     0,     0,     0,    56,     0,    54,    69,
      11,     0,     0,     9,     0,     0,     0,     0,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   222,   223,   220,   221,   209,   217,   218,   219,   213,
     197,   198,   196,     0,     0,   200,   195,   199,     0,   123,
       0,   105,   109,     0,   113,     0,   107,   110,   111,   112,
     114,   115,   116,     0,   142,   144,   157,   159,   161,   163,
     165,   167,   169,   172,   177,   180,   183,   187,     0,   189,
     201,   211,   210,    65,    74,     0,   209,    71,     0,     0,
       0,     0,     0,    51,    59,    60,     0,    61,    99,     0,
       0,     0,    46,    48,    38,    44,   139,     0,   138,     0,
       0,     0,     0,     0,   141,     0,     0,   193,     0,     0,
       0,     0,   190,   191,     0,    97,     0,     0,   106,   108,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   192,   187,   207,   208,     0,     0,     0,
       0,   214,    80,     0,    75,    70,    50,    49,    57,    55,
     102,   103,     0,    37,    36,    45,     0,     0,   121,   120,
       0,   134,     0,   133,     0,     0,   137,     0,   140,     0,
       0,     0,   117,     0,    84,     0,     0,    81,    98,    83,
       0,   212,   143,   160,     0,   162,   164,   166,   168,   170,
     171,   173,   174,   175,   176,   178,   179,   181,   182,   184,
     185,   186,   145,   206,   205,   204,   215,     0,     0,    84,
       0,    78,    81,    79,     0,    73,     0,   100,    47,   119,
     118,     0,    68,     0,     0,     0,     0,   194,     0,     0,
       0,    85,    93,     0,     0,    89,     0,    86,    82,     0,
       0,   188,     0,     0,   203,   202,    86,    77,    76,   101,
     104,     0,     0,    68,     0,     0,   132,   124,   126,   127,
     129,    94,    88,    90,    87,    95,     0,    91,     0,   158,
     216,     0,   135,     0,   130,     0,     0,    96,    92,   128,
     136,   131,   125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -255,  -255,  -255,   306,  -255,  -255,   -37,     8,  -255,    -7,
    -255,  -255,  -255,   190,   -55,  -255,    88,  -255,   202,   183,
    -255,   262,     1,   -17,   -22,  -255,  -140,    32,  -169,  -254,
     162,  -150,  -255,    -9,  -255,   224,   -81,  -255,  -164,  -255,
    -255,  -255,  -255,  -255,   -84,   -44,  -255,    10,  -255,   145,
     146,   148,   149,   154,    72,   -72,    83,    87,  -129,    -2,
    -255,  -255,  -255,  -255,  -255,  -255
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    25,    26,    27,    28,    29,    30,   232,    32,    33,
      34,    35,    36,    77,    78,   161,   162,    37,    67,    68,
      50,    51,   155,    39,    40,   145,   323,   234,   324,   269,
     186,   157,   242,   114,   115,   116,   117,   118,   119,   120,
     121,   254,   255,   122,   123,   124,   222,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   297,   142
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    38,   170,   175,    44,   233,   241,   253,    31,   223,
     321,    20,    20,   328,    20,    72,   268,    61,   192,   148,
      21,   112,   165,   343,    46,   152,   187,    38,   158,    59,
      47,   153,    52,   327,    31,    66,   167,   193,   143,   336,
      53,    54,    62,    73,    69,   321,    63,    20,   328,    58,
      76,   191,   265,    58,    21,    64,   266,   300,   300,   335,
      23,   266,   266,   303,    20,    65,   113,    76,    76,    23,
      76,    21,    74,   354,    22,    41,    42,   163,   112,   289,
     290,   291,   354,   191,    55,    56,   177,   271,   249,   257,
     314,   299,   187,    23,   260,   261,    75,   187,    20,   262,
     263,   182,   183,   185,   165,   165,    21,   238,    20,   274,
     300,   152,   158,   312,   266,    21,   152,   236,   198,   199,
      21,   306,   237,   113,    43,    60,   264,   307,   281,   282,
     283,   284,   248,    57,   251,    22,   224,   208,   209,   210,
     313,   331,   225,   226,    23,   265,   298,   272,   144,   266,
      49,   151,    76,    76,    23,    49,   340,   304,   191,    23,
     166,   305,   316,   191,   227,   228,   310,   318,   267,   185,
     191,   191,   229,   172,   319,   320,   230,   113,   292,   252,
     265,   168,   329,   333,   266,   296,   330,   334,   169,   356,
     224,   171,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   304,
     309,   173,   191,   351,   191,   302,   361,   304,   365,    70,
      71,   367,   326,   200,   201,   202,   203,   341,   178,   191,
     345,   332,   180,   301,   346,   347,   179,   348,   349,   350,
     190,   191,   204,   205,   194,   206,   207,   163,   267,   211,
     212,   213,   214,   215,   216,   113,   245,   246,   362,   258,
     191,   184,   158,   364,   159,   160,   149,   150,   224,   195,
     279,   280,   217,   218,   219,   220,   221,    45,   197,   370,
      61,   196,   231,   302,   371,   372,   358,   285,   286,   360,
      72,    45,     1,   287,   288,     2,   235,   250,   247,   256,
       3,    46,     4,     5,     6,   270,   293,   294,     7,     8,
       9,   311,    10,    11,   143,    12,    13,   315,    14,    15,
      16,    17,   317,   352,   342,   353,   363,   366,   368,   369,
     224,   191,    48,   154,   308,   239,   338,   273,   259,   189,
     275,     0,   359,   276,    18,   277,     0,    19,    20,     0,
       1,   278,     0,     2,     0,    21,     0,     0,     3,     0,
       4,     5,     6,     0,     0,     0,     7,     8,     9,     0,
      10,    11,     0,    12,    13,    22,    14,    15,    16,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,     0,     1,     0,     0,     2,
       0,    24,    18,     0,     3,    19,     4,     5,     6,     0,
       0,     0,     7,     8,     9,     0,    10,    11,     1,    12,
      13,     2,    14,    15,    16,    17,     3,     0,     4,     5,
       6,     0,     0,     0,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,    14,    15,    16,    17,    18,     0,
       0,    19,    20,     0,    88,     0,     0,     0,   337,    21,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
      18,     0,     0,    19,     0,     0,     0,     0,     0,   299,
       0,    21,     0,     0,     0,    93,    94,     0,   146,    96,
      97,    98,    99,   100,   101,   102,     0,     0,   300,   322,
       0,   264,   266,     0,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,     0,     0,   107,     0,
     265,   322,     0,     0,   266,     1,    79,    80,     2,     0,
      81,    82,    83,     3,   110,     4,     5,     6,    84,    85,
      86,     7,     8,     9,    87,    10,    11,    88,    12,    13,
      89,    14,    15,    16,    17,     0,    90,    91,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,    93,    94,
      19,    95,    96,    97,    98,    99,   100,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,     0,
       0,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,   109,     0,     0,     0,   110,     0,    58,
     111,     1,    79,    80,     2,     0,    81,    82,    83,     3,
       0,     4,     5,     6,    84,    85,    86,     7,     8,     9,
      87,    10,    11,    88,    12,    13,    89,    14,    15,    16,
      17,     0,    90,    91,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,    93,    94,    19,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,     0,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     0,     0,   110,     0,    58,   188,     1,    79,    80,
       2,     0,    81,    82,    83,     3,     0,     4,     5,     6,
      84,    85,    86,     7,     8,     9,    87,    10,    11,    88,
      12,    13,    89,    14,    15,    16,    17,     0,    90,    91,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      93,    94,    19,    95,    96,    97,    98,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,     0,    79,    80,     0,     0,    81,    82,    83,   105,
     106,     0,     0,   107,    84,    85,    86,     0,     0,     0,
      87,     0,     0,    88,   108,   109,    89,     0,     0,   110,
       0,    58,    90,    91,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,    94,     0,    95,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,     0,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     1,     0,   110,     2,    58,     0,     0,     0,     3,
       0,     4,     5,     6,     0,     0,     0,     7,     8,     9,
       0,    10,    11,     0,    12,    13,     0,    14,    15,    16,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     1,     0,    19,     2,     0,     0,
       0,     0,     3,     0,     4,     5,     6,     0,     0,     0,
       7,     8,     9,     0,    10,    11,    88,    12,    13,     0,
      14,    15,    16,    17,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   355,     0,    18,    93,    94,    19,
     146,    96,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,     0,     0,     0,     2,   103,   104,     0,     0,
       3,     0,     4,     0,     6,     0,   105,   106,     7,     8,
     107,     0,    10,    11,     0,     0,    13,     0,     0,    15,
      16,    17,   109,     0,     2,     0,   110,     0,     0,     3,
       0,     4,     0,     6,     0,     0,     0,     7,     8,     0,
       0,    10,    11,     0,    18,    13,     2,    19,    15,    16,
      17,     3,     0,     4,     0,     6,     0,     0,     0,     7,
       8,     0,     0,    10,    11,     0,     0,    13,     0,     0,
      15,    16,    17,    18,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     0,     0,
       0,     0,     3,     0,     4,    18,     6,   164,    19,     0,
       7,     8,     0,     0,    10,    11,    88,     0,    13,     0,
       0,    15,    16,    17,     0,     0,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,   243,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    93,    94,    19,
     146,    96,    97,    98,    99,   100,   101,   102,   244,     0,
       0,     0,     0,    88,     0,     0,   103,   104,     0,     0,
       0,     0,     0,    91,    92,     0,   105,   106,     0,     0,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,    94,   110,   146,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,    88,     0,     0,     0,     0,
       0,     0,     0,   105,   106,    91,    92,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,     0,    93,    94,   147,   146,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
       0,     0,     0,     0,     0,   103,   104,    88,     0,     0,
       0,     0,     0,     0,     0,   105,   106,    91,    92,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,     0,    93,    94,
     325,   146,    96,    97,    98,    99,   100,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,    88,
       0,     0,     0,     0,     0,     0,     0,   105,   106,    91,
      92,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,     0,     0,
      93,    94,   357,   146,    96,    97,    98,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,     0,     0,     0,    88,     0,     0,     0,     0,   105,
     106,     0,     0,   107,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,   156,   240,     0,     0,    93,    94,     0,   146,    96,
      97,    98,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,   103,   104,     0,     0,     0,    88,
       0,     0,     0,     0,   105,   106,     0,     0,   107,    91,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,   156,   339,     0,     0,
      93,    94,     0,   146,    96,    97,    98,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,    88,     0,     0,     0,     0,     0,     0,     0,   105,
     106,    91,    92,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,   156,    93,    94,     0,   146,    96,    97,    98,    99,
     100,   101,   102,     0,     0,     0,     0,     0,     0,     0,
       0,   103,   104,    88,     0,     0,     0,     0,     0,     0,
       0,   105,   106,    91,    92,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   295,     0,    93,    94,     0,   146,    96,    97,
      98,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,    88,     0,     0,     0,     0,
       0,     0,     0,   105,   106,    91,    92,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   344,     0,    93,    94,     0,   146,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
       0,     0,    88,     0,     0,   103,   104,     0,     0,     0,
       0,     0,    91,    92,     0,   105,   106,     0,     0,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,     0,    93,    94,   110,   146,    96,    97,    98,
      99,   100,   101,   102,     0,     0,     0,     0,     0,    88,
       0,     0,   103,   104,     0,     0,     0,     0,     0,    91,
      92,     0,   105,   106,     0,     0,   107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   109,     0,
      93,    94,   110,   146,    96,    97,    98,    99,   100,   101,
     102,     0,     0,     0,     0,     0,    88,     0,     0,   103,
     104,     0,     0,     0,     0,     0,    91,    92,     0,   105,
     106,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,   176,
     146,    96,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   104,     0,     0,
       0,     1,     0,     0,     2,     0,   105,   106,     0,     3,
     107,     4,     5,     6,     0,     0,     0,     7,     8,     9,
       0,    10,    11,     0,    12,    13,   181,    14,    15,    16,
      17,     0,     0,     2,     0,     0,     0,     0,     3,     0,
       4,     0,     6,     0,     0,     0,     7,     8,     0,     0,
      10,    11,     0,    18,    13,     0,    19,    15,    16,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,     0,     0,    19
};

static const yytype_int16 yycheck[] =
{
      22,     0,    83,    87,    21,   145,   156,   171,     0,   138,
     264,    59,    59,   267,    59,    69,   185,    39,    84,    63,
      66,    58,    77,    59,    23,   102,   110,    26,    72,    38,
       0,   108,    31,    86,    26,    59,    80,   103,    60,    86,
      32,    33,   105,    52,   106,   299,   109,    59,   302,   107,
      57,   102,   105,   107,    66,   107,   109,   105,   105,   110,
     105,   109,   109,   232,    59,   107,    58,    74,    75,   105,
      77,    66,   107,   327,    86,    58,    59,    76,   115,   208,
     209,   210,   336,   102,    58,    59,    88,   106,   169,   173,
     254,    86,   176,   105,   178,   179,   107,   181,    59,   180,
     184,   103,   104,   110,   159,   160,    66,   151,    59,   193,
     105,   102,   156,    59,   109,    66,   102,   108,    77,    78,
      66,   102,   108,   115,   107,    86,    86,   108,   200,   201,
     202,   203,   169,   107,   171,    86,   138,    66,    67,    68,
      86,   270,    75,    76,   105,   105,   230,   191,   106,   109,
     101,    69,   159,   160,   105,   101,   306,   102,   102,   105,
     101,   106,   106,   102,    97,    98,   247,   106,   185,   176,
     102,   102,   105,    59,   106,   106,   109,   169,   222,   171,
     105,   101,   105,   102,   109,   229,   109,   106,   104,   329,
     192,   105,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   102,
     247,   105,   102,   106,   102,   232,   106,   102,   106,   101,
     102,   106,   266,    79,    80,    81,    82,   311,   105,   102,
     314,   104,   104,   232,   315,   316,   105,   318,   319,   320,
     101,   102,    90,    91,    83,    64,    65,   246,   265,    69,
      70,    71,    72,    73,    74,   247,   101,   102,   342,   101,
     102,   105,   306,   344,    74,    75,    64,    65,   270,    87,
     198,   199,    92,    93,    94,    95,    96,   299,    86,   363,
     302,    88,    63,   300,   365,   366,   330,   204,   205,   333,
      69,   313,     3,   206,   207,     6,   110,    34,   104,   101,
      11,   300,    13,    14,    15,   106,    59,    59,    19,    20,
      21,   105,    23,    24,   336,    26,    27,   106,    29,    30,
      31,    32,   106,   106,   104,   110,   104,    12,   110,   101,
     332,   102,    26,    71,   246,   152,   304,   192,   176,   115,
     194,    -1,   332,   195,    55,   196,    -1,    58,    59,    -1,
       3,   197,    -1,     6,    -1,    66,    -1,    -1,    11,    -1,
      13,    14,    15,    -1,    -1,    -1,    19,    20,    21,    -1,
      23,    24,    -1,    26,    27,    86,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,    -1,     3,    -1,    -1,     6,
      -1,   112,    55,    -1,    11,    58,    13,    14,    15,    -1,
      -1,    -1,    19,    20,    21,    -1,    23,    24,     3,    26,
      27,     6,    29,    30,    31,    32,    11,    -1,    13,    14,
      15,    -1,    -1,    -1,    19,    20,    21,    -1,    23,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    55,    -1,
      -1,    58,    59,    -1,    25,    -1,    -1,    -1,   111,    66,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    66,    -1,    -1,    -1,    56,    57,    -1,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,   105,   106,
      -1,    86,   109,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,    -1,
     105,   106,    -1,    -1,   109,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,   105,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,    -1,    -1,    -1,   105,    -1,   107,
     108,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,
      -1,    -1,    -1,   105,    -1,   107,   108,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,     4,     5,    -1,    -1,     8,     9,    10,    85,
      86,    -1,    -1,    89,    16,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,   100,   101,    28,    -1,    -1,   105,
      -1,   107,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,
      -1,     3,    -1,   105,     6,   107,    -1,    -1,    -1,    11,
      -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,    21,
      -1,    23,    24,    -1,    26,    27,    -1,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,     3,    -1,    58,     6,    -1,    -1,
      -1,    -1,    11,    -1,    13,    14,    15,    -1,    -1,    -1,
      19,    20,    21,    -1,    23,    24,    25,    26,    27,    -1,
      29,    30,    31,    32,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,    75,    76,    -1,    -1,
      11,    -1,    13,    -1,    15,    -1,    85,    86,    19,    20,
      89,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,    30,
      31,    32,   101,    -1,     6,    -1,   105,    -1,    -1,    11,
      -1,    13,    -1,    15,    -1,    -1,    -1,    19,    20,    -1,
      -1,    23,    24,    -1,    55,    27,     6,    58,    30,    31,
      32,    11,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,
      20,    -1,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,
      30,    31,    32,    55,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    13,    55,    15,   108,    58,    -1,
      19,    20,    -1,    -1,    23,    24,    25,    -1,    27,    -1,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,   108,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    75,    76,    -1,    -1,
      -1,    -1,    -1,    35,    36,    -1,    85,    86,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,   105,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    35,    36,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,    -1,    -1,    56,    57,   110,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    35,    36,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    56,    57,
     110,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    35,
      36,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,
      56,    57,   110,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    89,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,   107,   108,    -1,    -1,    56,    57,    -1,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,    -1,   107,   108,    -1,    -1,
      56,    57,    -1,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    35,    36,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,   107,    56,    57,    -1,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    35,    36,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,    -1,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    35,    36,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,    -1,    56,    57,    -1,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    85,    86,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    56,    57,   105,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    85,    86,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      56,    57,   105,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    35,    36,    -1,    85,
      86,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,   105,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,    -1,
      -1,     3,    -1,    -1,     6,    -1,    85,    86,    -1,    11,
      89,    13,    14,    15,    -1,    -1,    -1,    19,    20,    21,
      -1,    23,    24,    -1,    26,    27,   105,    29,    30,    31,
      32,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    -1,    -1,    19,    20,    -1,    -1,
      23,    24,    -1,    55,    27,    -1,    58,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    11,    13,    14,    15,    19,    20,    21,
      23,    24,    26,    27,    29,    30,    31,    32,    55,    58,
      59,    66,    86,   105,   112,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   137,   142,   143,
     144,    58,    59,   107,   143,   144,   142,     0,   123,   101,
     140,   141,   142,   127,   127,    58,    59,   107,   107,   153,
      86,   144,   105,   109,   107,   107,    59,   138,   139,   106,
     101,   102,    69,   153,   107,   107,   129,   133,   134,     4,
       5,     8,     9,    10,    16,    17,    18,    22,    25,    28,
      34,    35,    36,    56,    57,    59,    60,    61,    62,    63,
      64,    65,    66,    75,    76,    85,    86,    89,   100,   101,
     105,   108,   126,   127,   153,   154,   155,   156,   157,   158,
     159,   160,   163,   164,   165,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   185,   144,   106,   145,    59,   110,   165,   138,
     138,    69,   102,   108,   141,   142,   107,   151,   165,   133,
     133,   135,   136,   142,   108,   134,   101,   165,   101,   104,
     156,   105,    59,   105,   101,   164,   105,   179,   105,   105,
     104,   105,   179,   179,   105,   129,   150,   164,   108,   155,
     101,   102,    84,   103,    83,    87,    88,    86,    77,    78,
      79,    80,    81,    82,    90,    91,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    92,    93,    94,
      95,    96,   166,   178,   179,    75,    76,    97,    98,   105,
     109,    63,   127,   146,   147,   110,   108,   108,   165,   139,
     108,   151,   152,   108,   108,   101,   102,   104,   126,   156,
      34,   126,   127,   158,   161,   162,   101,   164,   101,   150,
     164,   164,   156,   164,    86,   105,   109,   143,   148,   149,
     106,   106,   165,   169,   164,   170,   171,   172,   173,   174,
     174,   175,   175,   175,   175,   176,   176,   177,   177,   178,
     178,   178,   165,    59,    59,   106,   165,   184,   164,    86,
     105,   142,   143,   148,   102,   106,   102,   108,   136,   126,
     156,   105,    59,    86,   158,   106,   106,   106,   106,   106,
     106,   149,   106,   146,   148,   110,   165,    86,   149,   105,
     109,   178,   104,   102,   106,   110,    86,   111,   147,   108,
     151,   164,   104,    59,   106,   164,   156,   156,   156,   156,
     156,   106,   106,   110,   149,   106,   146,   110,   165,   167,
     165,   106,   164,   104,   156,   106,    12,   106,   110,   101,
     164,   156,   156
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   120,   121,   122,   122,   123,   123,   123,   124,   125,
     125,   126,   126,   127,   127,   127,   127,   128,   128,   128,
     128,   128,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   131,
     131,   132,   132,   133,   133,   134,   135,   135,   136,   137,
     137,   137,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   142,   142,   143,   143,   144,   144,
     144,   144,   145,   144,   144,   146,   146,   146,   147,   147,
     147,   148,   148,   148,   148,   148,   148,   148,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   150,   150,   151,
     151,   151,   151,   152,   152,   153,   153,   154,   154,   155,
     155,   156,   156,   156,   156,   156,   156,   157,   157,   157,
     157,   157,   158,   158,   159,   159,   159,   160,   160,   160,
     160,   160,   160,   161,   161,   162,   162,   163,   163,   163,
     163,   163,   164,   164,   165,   165,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   167,   167,   168,
     168,   169,   169,   170,   170,   171,   171,   172,   172,   173,
     173,   173,   174,   174,   174,   174,   174,   175,   175,   175,
     176,   176,   176,   177,   177,   177,   177,   178,   178,   179,
     179,   179,   179,   179,   179,   180,   180,   180,   180,   180,
     180,   181,   181,   181,   181,   181,   181,   181,   181,   182,
     182,   182,   182,   183,   183,   184,   184,   185,   185,   185,
     185,   185,   185,   185
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       2,     3,     2,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     4,     2,
       2,     1,     1,     1,     2,     3,     1,     3,     1,     5,
       5,     4,     2,     2,     1,     3,     1,     3,     1,     3,
       1,     3,     2,     1,     2,     3,     1,     2,     1,     3,
       4,     3,     0,     5,     3,     1,     3,     3,     2,     2,
       1,     1,     2,     1,     1,     2,     2,     3,     3,     2,
       3,     3,     4,     2,     3,     3,     4,     1,     2,     1,
       3,     4,     2,     1,     3,     2,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     4,     4,
       3,     3,     2,     1,     5,     7,     5,     5,     7,     5,
       6,     7,     5,     1,     1,     4,     5,     3,     2,     2,
       3,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     4,     1,
       2,     2,     2,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     3,     3,     3,     2,     2,     1,
       1,     1,     3,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: translation_unit  */
#line 219 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1976 "build/parser.tab.cpp"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 225 "src/parser.y"
                         {
        (yyval.node) = create_node("TranslationUnit");
        (yyval.node)->addChild((yyvsp[0].node));
        root = (yyval.node);
    }
#line 1986 "build/parser.tab.cpp"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 230 "src/parser.y"
                                            {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1995 "build/parser.tab.cpp"
    break;

  case 5: /* external_declaration: function_definition  */
#line 237 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2003 "build/parser.tab.cpp"
    break;

  case 6: /* external_declaration: declaration  */
#line 240 "src/parser.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2011 "build/parser.tab.cpp"
    break;

  case 7: /* external_declaration: preprocessor_directive  */
#line 243 "src/parser.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2019 "build/parser.tab.cpp"
    break;

  case 8: /* preprocessor_directive: PREP  */
#line 249 "src/parser.y"
         { (yyval.node) = create_node("Preprocessor", (yyvsp[0].str)); }
#line 2025 "build/parser.tab.cpp"
    break;

  case 9: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 253 "src/parser.y"
                                                         {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 2037 "build/parser.tab.cpp"
    break;

  case 10: /* function_definition: declarator compound_statement  */
#line 260 "src/parser.y"
                                    {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 2048 "build/parser.tab.cpp"
    break;

  case 11: /* declaration: declaration_specifiers init_declarator_list SEMI  */
#line 269 "src/parser.y"
                                                     {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
	if (in_typedef_declaration) {
            collect_typedef_names((yyvsp[-1].node));
        }

        in_typedef_declaration = 0;
    }
#line 2063 "build/parser.tab.cpp"
    break;

  case 12: /* declaration: declaration_specifiers SEMI  */
#line 279 "src/parser.y"
                                  {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        in_typedef_declaration = 0;
    }
#line 2073 "build/parser.tab.cpp"
    break;

  case 13: /* declaration_specifiers: storage_class_specifier  */
#line 287 "src/parser.y"
                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2082 "build/parser.tab.cpp"
    break;

  case 14: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 291 "src/parser.y"
                                                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2092 "build/parser.tab.cpp"
    break;

  case 15: /* declaration_specifiers: type_specifier  */
#line 296 "src/parser.y"
                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2101 "build/parser.tab.cpp"
    break;

  case 16: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 300 "src/parser.y"
                                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2111 "build/parser.tab.cpp"
    break;

  case 17: /* storage_class_specifier: TYPEDEF  */
#line 308 "src/parser.y"
            {
        (yyval.node) = create_node("StorageClass", "typedef");
        in_typedef_declaration = 1;
    }
#line 2120 "build/parser.tab.cpp"
    break;

  case 18: /* storage_class_specifier: STATIC  */
#line 312 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "static"); }
#line 2126 "build/parser.tab.cpp"
    break;

  case 19: /* storage_class_specifier: EXTERN  */
#line 313 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "extern"); }
#line 2132 "build/parser.tab.cpp"
    break;

  case 20: /* storage_class_specifier: REGISTER  */
#line 314 "src/parser.y"
               { (yyval.node) = create_node("StorageClass", "register"); }
#line 2138 "build/parser.tab.cpp"
    break;

  case 21: /* storage_class_specifier: AUTO  */
#line 315 "src/parser.y"
           { (yyval.node) = create_node("StorageClass", "auto"); }
#line 2144 "build/parser.tab.cpp"
    break;

  case 22: /* type_specifier: type_keyword  */
#line 319 "src/parser.y"
                 {
        (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str));
        strcpy(current_type, (yyvsp[0].str));
    }
#line 2153 "build/parser.tab.cpp"
    break;

  case 23: /* type_specifier: struct_or_union_specifier  */
#line 323 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2159 "build/parser.tab.cpp"
    break;

  case 24: /* type_specifier: enum_specifier  */
#line 324 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2165 "build/parser.tab.cpp"
    break;

  case 25: /* type_specifier: TYPEDEF_NAME  */
#line 325 "src/parser.y"
                   {  // ← Now conflict-free!
        (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str));
        strcpy(current_type, (yyvsp[0].str));
    }
#line 2174 "build/parser.tab.cpp"
    break;

  case 26: /* type_keyword: VOID  */
#line 332 "src/parser.y"
         { (yyval.str) = strdup("void"); }
#line 2180 "build/parser.tab.cpp"
    break;

  case 27: /* type_keyword: CHAR  */
#line 333 "src/parser.y"
           { (yyval.str) = strdup("char"); }
#line 2186 "build/parser.tab.cpp"
    break;

  case 28: /* type_keyword: SHORT  */
#line 334 "src/parser.y"
            { (yyval.str) = strdup("short"); }
#line 2192 "build/parser.tab.cpp"
    break;

  case 29: /* type_keyword: INT  */
#line 335 "src/parser.y"
          { (yyval.str) = strdup("int"); }
#line 2198 "build/parser.tab.cpp"
    break;

  case 30: /* type_keyword: LONG  */
#line 336 "src/parser.y"
           { (yyval.str) = strdup("long"); }
#line 2204 "build/parser.tab.cpp"
    break;

  case 31: /* type_keyword: FLOAT  */
#line 337 "src/parser.y"
            { (yyval.str) = strdup("float"); }
#line 2210 "build/parser.tab.cpp"
    break;

  case 32: /* type_keyword: DOUBLE  */
#line 338 "src/parser.y"
             { (yyval.str) = strdup("double"); }
#line 2216 "build/parser.tab.cpp"
    break;

  case 33: /* type_keyword: SIGNED  */
#line 339 "src/parser.y"
             { (yyval.str) = strdup("signed"); }
#line 2222 "build/parser.tab.cpp"
    break;

  case 34: /* type_keyword: UNSIGNED  */
#line 340 "src/parser.y"
               { (yyval.str) = strdup("unsigned"); }
#line 2228 "build/parser.tab.cpp"
    break;

  case 35: /* type_keyword: BOOL  */
#line 341 "src/parser.y"
           { (yyval.str) = strdup("bool"); }
#line 2234 "build/parser.tab.cpp"
    break;

  case 36: /* struct_or_union_specifier: struct_or_union ID LBRACE struct_declaration_list RBRACE  */
#line 345 "src/parser.y"
                                                             {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-4].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2246 "build/parser.tab.cpp"
    break;

  case 37: /* struct_or_union_specifier: struct_or_union TYPEDEF_NAME LBRACE struct_declaration_list RBRACE  */
#line 352 "src/parser.y"
                                                                         {  // ← ADD THIS
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-4].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2258 "build/parser.tab.cpp"
    break;

  case 38: /* struct_or_union_specifier: struct_or_union LBRACE struct_declaration_list RBRACE  */
#line 359 "src/parser.y"
                                                            {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2268 "build/parser.tab.cpp"
    break;

  case 39: /* struct_or_union_specifier: struct_or_union ID  */
#line 364 "src/parser.y"
                         {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-1].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2279 "build/parser.tab.cpp"
    break;

  case 40: /* struct_or_union_specifier: struct_or_union TYPEDEF_NAME  */
#line 370 "src/parser.y"
                                   {  // ← ADD THIS
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-1].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2290 "build/parser.tab.cpp"
    break;

  case 41: /* struct_or_union: STRUCT  */
#line 379 "src/parser.y"
           { (yyval.str) = strdup("struct"); }
#line 2296 "build/parser.tab.cpp"
    break;

  case 42: /* struct_or_union: UNION  */
#line 380 "src/parser.y"
            { (yyval.str) = strdup("union"); }
#line 2302 "build/parser.tab.cpp"
    break;

  case 43: /* struct_declaration_list: struct_declaration  */
#line 384 "src/parser.y"
                       {
        (yyval.node) = create_node("StructDeclarationList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2311 "build/parser.tab.cpp"
    break;

  case 44: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 388 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2320 "build/parser.tab.cpp"
    break;

  case 45: /* struct_declaration: type_specifier struct_declarator_list SEMI  */
#line 395 "src/parser.y"
                                               {
        (yyval.node) = create_node("StructDeclaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2330 "build/parser.tab.cpp"
    break;

  case 46: /* struct_declarator_list: struct_declarator  */
#line 403 "src/parser.y"
                      {
        (yyval.node) = create_node("StructDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2339 "build/parser.tab.cpp"
    break;

  case 47: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 407 "src/parser.y"
                                                     {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2348 "build/parser.tab.cpp"
    break;

  case 48: /* struct_declarator: declarator  */
#line 414 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2354 "build/parser.tab.cpp"
    break;

  case 49: /* enum_specifier: ENUM ID LBRACE enumerator_list RBRACE  */
#line 418 "src/parser.y"
                                          {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2365 "build/parser.tab.cpp"
    break;

  case 50: /* enum_specifier: ENUM TYPEDEF_NAME LBRACE enumerator_list RBRACE  */
#line 424 "src/parser.y"
                                                      {  // ← ADD THIS
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2376 "build/parser.tab.cpp"
    break;

  case 51: /* enum_specifier: ENUM LBRACE enumerator_list RBRACE  */
#line 430 "src/parser.y"
                                         {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2385 "build/parser.tab.cpp"
    break;

  case 52: /* enum_specifier: ENUM ID  */
#line 434 "src/parser.y"
              {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2395 "build/parser.tab.cpp"
    break;

  case 53: /* enum_specifier: ENUM TYPEDEF_NAME  */
#line 439 "src/parser.y"
                        {  // ← ADD THIS
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2405 "build/parser.tab.cpp"
    break;

  case 54: /* enumerator_list: enumerator  */
#line 447 "src/parser.y"
               {
        (yyval.node) = create_node("EnumeratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2414 "build/parser.tab.cpp"
    break;

  case 55: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 451 "src/parser.y"
                                       {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2423 "build/parser.tab.cpp"
    break;

  case 56: /* enumerator: ID  */
#line 458 "src/parser.y"
       {
        (yyval.node) = create_node("Enumerator", (yyvsp[0].str));
    }
#line 2431 "build/parser.tab.cpp"
    break;

  case 57: /* enumerator: ID ASSIGN assignment_expression  */
#line 461 "src/parser.y"
                                      {
        (yyval.node) = create_node("Enumerator", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2440 "build/parser.tab.cpp"
    break;

  case 58: /* init_declarator_list: init_declarator  */
#line 468 "src/parser.y"
                    {
        (yyval.node) = create_node("InitDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2449 "build/parser.tab.cpp"
    break;

  case 59: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 472 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2458 "build/parser.tab.cpp"
    break;

  case 60: /* init_declarator: declarator  */
#line 479 "src/parser.y"
               {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2467 "build/parser.tab.cpp"
    break;

  case 61: /* init_declarator: declarator ASSIGN initializer  */
#line 483 "src/parser.y"
                                    {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2477 "build/parser.tab.cpp"
    break;

  case 62: /* declarator: pointer direct_declarator  */
#line 491 "src/parser.y"
                              {
        (yyval.node) = create_node("Declarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2487 "build/parser.tab.cpp"
    break;

  case 63: /* declarator: direct_declarator  */
#line 496 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2495 "build/parser.tab.cpp"
    break;

  case 64: /* declarator: BIT_AND direct_declarator  */
#line 499 "src/parser.y"
                                {    
        (yyval.node) = create_node("ReferenceDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2504 "build/parser.tab.cpp"
    break;

  case 65: /* declarator: pointer BIT_AND direct_declarator  */
#line 503 "src/parser.y"
                                        {    
        (yyval.node) = create_node("ReferenceDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2514 "build/parser.tab.cpp"
    break;

  case 66: /* pointer: MUL  */
#line 511 "src/parser.y"
        {
        (yyval.node) = create_node("Pointer");
    }
#line 2522 "build/parser.tab.cpp"
    break;

  case 67: /* pointer: MUL pointer  */
#line 514 "src/parser.y"
                  {
        (yyval.node) = create_node("Pointer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2531 "build/parser.tab.cpp"
    break;

  case 68: /* direct_declarator: ID  */
#line 521 "src/parser.y"
       {
        (yyval.node) = create_node("DirectDeclarator", (yyvsp[0].str));
    }
#line 2539 "build/parser.tab.cpp"
    break;

  case 69: /* direct_declarator: LPAREN declarator RPAREN  */
#line 524 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2547 "build/parser.tab.cpp"
    break;

  case 70: /* direct_declarator: direct_declarator LBRACKET assignment_expression RBRACKET  */
#line 527 "src/parser.y"
                                                                {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2557 "build/parser.tab.cpp"
    break;

  case 71: /* direct_declarator: direct_declarator LBRACKET RBRACKET  */
#line 532 "src/parser.y"
                                          {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2566 "build/parser.tab.cpp"
    break;

  case 72: /* $@1: %empty  */
#line 536 "src/parser.y"
                               {
        in_function_params = 1;
    }
#line 2574 "build/parser.tab.cpp"
    break;

  case 73: /* direct_declarator: direct_declarator LPAREN $@1 parameter_list RPAREN  */
#line 538 "src/parser.y"
                            {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        in_function_params = 0;
    }
#line 2585 "build/parser.tab.cpp"
    break;

  case 74: /* direct_declarator: direct_declarator LPAREN RPAREN  */
#line 544 "src/parser.y"
                                      {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        in_function_params = 0;
    }
#line 2595 "build/parser.tab.cpp"
    break;

  case 75: /* parameter_list: parameter_declaration  */
#line 552 "src/parser.y"
                          {
        (yyval.node) = create_node("ParameterList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2604 "build/parser.tab.cpp"
    break;

  case 76: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 556 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2613 "build/parser.tab.cpp"
    break;

  case 77: /* parameter_list: parameter_list COMMA ELLIPSIS  */
#line 560 "src/parser.y"
                                    {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild(create_node("Ellipsis"));
    }
#line 2622 "build/parser.tab.cpp"
    break;

  case 78: /* parameter_declaration: declaration_specifiers declarator  */
#line 567 "src/parser.y"
                                      {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2632 "build/parser.tab.cpp"
    break;

  case 79: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 572 "src/parser.y"
                                                 {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2642 "build/parser.tab.cpp"
    break;

  case 80: /* parameter_declaration: declaration_specifiers  */
#line 577 "src/parser.y"
                             {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2651 "build/parser.tab.cpp"
    break;

  case 81: /* abstract_declarator: pointer  */
#line 584 "src/parser.y"
            {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2660 "build/parser.tab.cpp"
    break;

  case 82: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 588 "src/parser.y"
                                         {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2670 "build/parser.tab.cpp"
    break;

  case 83: /* abstract_declarator: direct_abstract_declarator  */
#line 593 "src/parser.y"
                                 {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2679 "build/parser.tab.cpp"
    break;

  case 84: /* abstract_declarator: BIT_AND  */
#line 597 "src/parser.y"
              {    /* ADD THIS RULE */
        (yyval.node) = create_node("ReferenceDeclarator");
    }
#line 2687 "build/parser.tab.cpp"
    break;

  case 85: /* abstract_declarator: BIT_AND direct_abstract_declarator  */
#line 600 "src/parser.y"
                                         {   
        (yyval.node) = create_node("ReferenceDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2696 "build/parser.tab.cpp"
    break;

  case 86: /* abstract_declarator: pointer BIT_AND  */
#line 604 "src/parser.y"
                      {    /* ADD THIS RULE */
        (yyval.node) = create_node("ReferenceDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2705 "build/parser.tab.cpp"
    break;

  case 87: /* abstract_declarator: pointer BIT_AND direct_abstract_declarator  */
#line 608 "src/parser.y"
                                                 {   
        (yyval.node) = create_node("ReferenceDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2715 "build/parser.tab.cpp"
    break;

  case 88: /* direct_abstract_declarator: LPAREN abstract_declarator RPAREN  */
#line 616 "src/parser.y"
                                      {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2723 "build/parser.tab.cpp"
    break;

  case 89: /* direct_abstract_declarator: LBRACKET RBRACKET  */
#line 619 "src/parser.y"
                        {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
    }
#line 2731 "build/parser.tab.cpp"
    break;

  case 90: /* direct_abstract_declarator: LBRACKET assignment_expression RBRACKET  */
#line 622 "src/parser.y"
                                              {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2740 "build/parser.tab.cpp"
    break;

  case 91: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET RBRACKET  */
#line 626 "src/parser.y"
                                                   {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2749 "build/parser.tab.cpp"
    break;

  case 92: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET assignment_expression RBRACKET  */
#line 630 "src/parser.y"
                                                                         {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2759 "build/parser.tab.cpp"
    break;

  case 93: /* direct_abstract_declarator: LPAREN RPAREN  */
#line 635 "src/parser.y"
                    {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
    }
#line 2767 "build/parser.tab.cpp"
    break;

  case 94: /* direct_abstract_declarator: LPAREN parameter_list RPAREN  */
#line 638 "src/parser.y"
                                   {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2776 "build/parser.tab.cpp"
    break;

  case 95: /* direct_abstract_declarator: direct_abstract_declarator LPAREN RPAREN  */
#line 642 "src/parser.y"
                                               {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2785 "build/parser.tab.cpp"
    break;

  case 96: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_list RPAREN  */
#line 646 "src/parser.y"
                                                              {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2795 "build/parser.tab.cpp"
    break;

  case 97: /* type_name: type_specifier  */
#line 654 "src/parser.y"
                   {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2804 "build/parser.tab.cpp"
    break;

  case 98: /* type_name: type_specifier abstract_declarator  */
#line 658 "src/parser.y"
                                         {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2814 "build/parser.tab.cpp"
    break;

  case 99: /* initializer: assignment_expression  */
#line 666 "src/parser.y"
                          {
        (yyval.node) = create_node("Initializer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2823 "build/parser.tab.cpp"
    break;

  case 100: /* initializer: LBRACE initializer_list RBRACE  */
#line 670 "src/parser.y"
                                     {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2832 "build/parser.tab.cpp"
    break;

  case 101: /* initializer: LBRACE initializer_list COMMA RBRACE  */
#line 674 "src/parser.y"
                                           {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2841 "build/parser.tab.cpp"
    break;

  case 102: /* initializer: LBRACE RBRACE  */
#line 678 "src/parser.y"
                    {
        (yyval.node) = create_node("InitializerList");
        /* Empty initializer list */
    }
#line 2850 "build/parser.tab.cpp"
    break;

  case 103: /* initializer_list: initializer  */
#line 686 "src/parser.y"
                {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2859 "build/parser.tab.cpp"
    break;

  case 104: /* initializer_list: initializer_list COMMA initializer  */
#line 690 "src/parser.y"
                                         {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2868 "build/parser.tab.cpp"
    break;

  case 105: /* compound_statement: LBRACE RBRACE  */
#line 697 "src/parser.y"
                  {
        (yyval.node) = create_node("CompoundStatement");
    }
#line 2876 "build/parser.tab.cpp"
    break;

  case 106: /* compound_statement: LBRACE block_item_list RBRACE  */
#line 700 "src/parser.y"
                                    {
        (yyval.node) = create_node("CompoundStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2885 "build/parser.tab.cpp"
    break;

  case 107: /* block_item_list: block_item  */
#line 707 "src/parser.y"
               {
        (yyval.node) = create_node("BlockItemList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2894 "build/parser.tab.cpp"
    break;

  case 108: /* block_item_list: block_item_list block_item  */
#line 711 "src/parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2903 "build/parser.tab.cpp"
    break;

  case 109: /* block_item: declaration  */
#line 718 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2912 "build/parser.tab.cpp"
    break;

  case 110: /* block_item: statement  */
#line 722 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2921 "build/parser.tab.cpp"
    break;

  case 111: /* statement: labeled_statement  */
#line 729 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2927 "build/parser.tab.cpp"
    break;

  case 112: /* statement: expression_statement  */
#line 730 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2933 "build/parser.tab.cpp"
    break;

  case 113: /* statement: compound_statement  */
#line 731 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2939 "build/parser.tab.cpp"
    break;

  case 114: /* statement: selection_statement  */
#line 732 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2945 "build/parser.tab.cpp"
    break;

  case 115: /* statement: iteration_statement  */
#line 733 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2951 "build/parser.tab.cpp"
    break;

  case 116: /* statement: jump_statement  */
#line 734 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2957 "build/parser.tab.cpp"
    break;

  case 117: /* labeled_statement: ID COLON statement  */
#line 738 "src/parser.y"
                       {
        (yyval.node) = create_node("LabeledStatement", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2966 "build/parser.tab.cpp"
    break;

  case 118: /* labeled_statement: CASE assignment_expression COLON statement  */
#line 742 "src/parser.y"
                                                 {
        (yyval.node) = create_node("CaseStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2976 "build/parser.tab.cpp"
    break;

  case 119: /* labeled_statement: CASE assignment_expression COLON declaration  */
#line 747 "src/parser.y"
                                                   {
        (yyval.node) = create_node("CaseStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        ASTNode* blockItem = create_node("BlockItem");
        blockItem->addChild((yyvsp[0].node));
        (yyval.node)->addChild(blockItem);
    }
#line 2988 "build/parser.tab.cpp"
    break;

  case 120: /* labeled_statement: DEFAULT COLON statement  */
#line 754 "src/parser.y"
                              {
        (yyval.node) = create_node("DefaultStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2997 "build/parser.tab.cpp"
    break;

  case 121: /* labeled_statement: DEFAULT COLON declaration  */
#line 758 "src/parser.y"
                                {
        (yyval.node) = create_node("DefaultStatement");
        ASTNode* blockItem = create_node("BlockItem");
        blockItem->addChild((yyvsp[0].node));
        (yyval.node)->addChild(blockItem);
    }
#line 3008 "build/parser.tab.cpp"
    break;

  case 122: /* expression_statement: expression SEMI  */
#line 767 "src/parser.y"
                    {
        (yyval.node) = create_node("ExpressionStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3017 "build/parser.tab.cpp"
    break;

  case 123: /* expression_statement: SEMI  */
#line 771 "src/parser.y"
           {
        (yyval.node) = create_node("EmptyStatement");
    }
#line 3025 "build/parser.tab.cpp"
    break;

  case 124: /* selection_statement: IF LPAREN expression RPAREN statement  */
#line 777 "src/parser.y"
                                                                {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3035 "build/parser.tab.cpp"
    break;

  case 125: /* selection_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 782 "src/parser.y"
                                                           {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3046 "build/parser.tab.cpp"
    break;

  case 126: /* selection_statement: SWITCH LPAREN expression RPAREN statement  */
#line 788 "src/parser.y"
                                                {
        (yyval.node) = create_node("SwitchStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3056 "build/parser.tab.cpp"
    break;

  case 127: /* iteration_statement: WHILE LPAREN expression RPAREN statement  */
#line 796 "src/parser.y"
                                             {
        (yyval.node) = create_node("WhileStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3066 "build/parser.tab.cpp"
    break;

  case 128: /* iteration_statement: DO statement WHILE LPAREN expression RPAREN SEMI  */
#line 801 "src/parser.y"
                                                       {
        (yyval.node) = create_node("DoWhileStatement");
        (yyval.node)->addChild((yyvsp[-5].node));
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 3076 "build/parser.tab.cpp"
    break;

  case 129: /* iteration_statement: UNTIL LPAREN expression RPAREN statement  */
#line 806 "src/parser.y"
                                               {  
        (yyval.node) = create_node("UntilStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3086 "build/parser.tab.cpp"
    break;

  case 130: /* iteration_statement: FOR LPAREN for_init_statement expression_statement RPAREN statement  */
#line 811 "src/parser.y"
                                                                          {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3097 "build/parser.tab.cpp"
    break;

  case 131: /* iteration_statement: FOR LPAREN for_init_statement expression_statement expression RPAREN statement  */
#line 817 "src/parser.y"
                                                                                     {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3109 "build/parser.tab.cpp"
    break;

  case 132: /* iteration_statement: FOR LPAREN range_based_for RPAREN statement  */
#line 824 "src/parser.y"
                                                  {
        (yyval.node) = create_node("RangeBasedForStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3119 "build/parser.tab.cpp"
    break;

  case 133: /* for_init_statement: expression_statement  */
#line 832 "src/parser.y"
                         {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3128 "build/parser.tab.cpp"
    break;

  case 134: /* for_init_statement: declaration  */
#line 836 "src/parser.y"
                  {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3137 "build/parser.tab.cpp"
    break;

  case 135: /* range_based_for: declaration_specifiers ID COLON expression  */
#line 843 "src/parser.y"
                                               {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3148 "build/parser.tab.cpp"
    break;

  case 136: /* range_based_for: declaration_specifiers BIT_AND ID COLON expression  */
#line 849 "src/parser.y"
                                                         {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild(create_node("Reference"));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3160 "build/parser.tab.cpp"
    break;

  case 137: /* jump_statement: GOTO ID SEMI  */
#line 859 "src/parser.y"
                 {
        (yyval.node) = create_node("GotoStatement", (yyvsp[-1].str));
    }
#line 3168 "build/parser.tab.cpp"
    break;

  case 138: /* jump_statement: CONTINUE SEMI  */
#line 862 "src/parser.y"
                    {
        (yyval.node) = create_node("ContinueStatement");
    }
#line 3176 "build/parser.tab.cpp"
    break;

  case 139: /* jump_statement: BREAK SEMI  */
#line 865 "src/parser.y"
                 {
        (yyval.node) = create_node("BreakStatement");
    }
#line 3184 "build/parser.tab.cpp"
    break;

  case 140: /* jump_statement: RETURN expression SEMI  */
#line 868 "src/parser.y"
                             {
        (yyval.node) = create_node("ReturnStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3193 "build/parser.tab.cpp"
    break;

  case 141: /* jump_statement: RETURN SEMI  */
#line 872 "src/parser.y"
                  {
        (yyval.node) = create_node("ReturnStatement");
    }
#line 3201 "build/parser.tab.cpp"
    break;

  case 142: /* expression: assignment_expression  */
#line 878 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3209 "build/parser.tab.cpp"
    break;

  case 143: /* expression: expression COMMA assignment_expression  */
#line 881 "src/parser.y"
                                             {
        (yyval.node) = create_node("CommaExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3219 "build/parser.tab.cpp"
    break;

  case 144: /* assignment_expression: conditional_expression  */
#line 889 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3227 "build/parser.tab.cpp"
    break;

  case 145: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 892 "src/parser.y"
                                                                 {
        (yyval.node) = create_node("AssignmentExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3237 "build/parser.tab.cpp"
    break;

  case 146: /* assignment_operator: ASSIGN  */
#line 900 "src/parser.y"
           { (yyval.str) = strdup("="); }
#line 3243 "build/parser.tab.cpp"
    break;

  case 147: /* assignment_operator: PLUS_EQ  */
#line 901 "src/parser.y"
              { (yyval.str) = strdup("+="); }
#line 3249 "build/parser.tab.cpp"
    break;

  case 148: /* assignment_operator: MINUS_EQ  */
#line 902 "src/parser.y"
               { (yyval.str) = strdup("-="); }
#line 3255 "build/parser.tab.cpp"
    break;

  case 149: /* assignment_operator: MUL_EQ  */
#line 903 "src/parser.y"
             { (yyval.str) = strdup("*="); }
#line 3261 "build/parser.tab.cpp"
    break;

  case 150: /* assignment_operator: DIV_EQ  */
#line 904 "src/parser.y"
             { (yyval.str) = strdup("/="); }
#line 3267 "build/parser.tab.cpp"
    break;

  case 151: /* assignment_operator: MOD_EQ  */
#line 905 "src/parser.y"
             { (yyval.str) = strdup("%="); }
#line 3273 "build/parser.tab.cpp"
    break;

  case 152: /* assignment_operator: AND_EQ  */
#line 906 "src/parser.y"
             { (yyval.str) = strdup("&="); }
#line 3279 "build/parser.tab.cpp"
    break;

  case 153: /* assignment_operator: OR_EQ  */
#line 907 "src/parser.y"
            { (yyval.str) = strdup("|="); }
#line 3285 "build/parser.tab.cpp"
    break;

  case 154: /* assignment_operator: XOR_EQ  */
#line 908 "src/parser.y"
             { (yyval.str) = strdup("^="); }
#line 3291 "build/parser.tab.cpp"
    break;

  case 155: /* assignment_operator: LSHIFT_EQ  */
#line 909 "src/parser.y"
                { (yyval.str) = strdup("<<="); }
#line 3297 "build/parser.tab.cpp"
    break;

  case 156: /* assignment_operator: RSHIFT_EQ  */
#line 910 "src/parser.y"
                { (yyval.str) = strdup(">>="); }
#line 3303 "build/parser.tab.cpp"
    break;

  case 157: /* conditional_expression: logical_or_expression  */
#line 914 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3311 "build/parser.tab.cpp"
    break;

  case 158: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 917 "src/parser.y"
                                                                             {
        (yyval.node) = create_node("ConditionalExpression");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3322 "build/parser.tab.cpp"
    break;

  case 159: /* logical_or_expression: logical_and_expression  */
#line 926 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3330 "build/parser.tab.cpp"
    break;

  case 160: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 929 "src/parser.y"
                                                      {
        (yyval.node) = create_node("LogicalOrExpression", "||");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3340 "build/parser.tab.cpp"
    break;

  case 161: /* logical_and_expression: inclusive_or_expression  */
#line 937 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3348 "build/parser.tab.cpp"
    break;

  case 162: /* logical_and_expression: logical_and_expression AND inclusive_or_expression  */
#line 940 "src/parser.y"
                                                         {
        (yyval.node) = create_node("LogicalAndExpression","&&");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3358 "build/parser.tab.cpp"
    break;

  case 163: /* inclusive_or_expression: exclusive_or_expression  */
#line 948 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3366 "build/parser.tab.cpp"
    break;

  case 164: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 951 "src/parser.y"
                                                             {
        (yyval.node) = create_node("InclusiveOrExpression","|");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3376 "build/parser.tab.cpp"
    break;

  case 165: /* exclusive_or_expression: and_expression  */
#line 959 "src/parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3384 "build/parser.tab.cpp"
    break;

  case 166: /* exclusive_or_expression: exclusive_or_expression BIT_XOR and_expression  */
#line 962 "src/parser.y"
                                                     {
        (yyval.node) = create_node("ExclusiveOrExpression","^");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3394 "build/parser.tab.cpp"
    break;

  case 167: /* and_expression: equality_expression  */
#line 970 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3402 "build/parser.tab.cpp"
    break;

  case 168: /* and_expression: and_expression BIT_AND equality_expression  */
#line 973 "src/parser.y"
                                                 {
        (yyval.node) = create_node("AndExpression","&");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3412 "build/parser.tab.cpp"
    break;

  case 169: /* equality_expression: relational_expression  */
#line 981 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3420 "build/parser.tab.cpp"
    break;

  case 170: /* equality_expression: equality_expression EQ relational_expression  */
#line 984 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "==");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3430 "build/parser.tab.cpp"
    break;

  case 171: /* equality_expression: equality_expression NE relational_expression  */
#line 989 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "!=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3440 "build/parser.tab.cpp"
    break;

  case 172: /* relational_expression: shift_expression  */
#line 997 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3448 "build/parser.tab.cpp"
    break;

  case 173: /* relational_expression: relational_expression LT shift_expression  */
#line 1000 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3458 "build/parser.tab.cpp"
    break;

  case 174: /* relational_expression: relational_expression GT shift_expression  */
#line 1005 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3468 "build/parser.tab.cpp"
    break;

  case 175: /* relational_expression: relational_expression LE shift_expression  */
#line 1010 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3478 "build/parser.tab.cpp"
    break;

  case 176: /* relational_expression: relational_expression GE shift_expression  */
#line 1015 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3488 "build/parser.tab.cpp"
    break;

  case 177: /* shift_expression: additive_expression  */
#line 1023 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3496 "build/parser.tab.cpp"
    break;

  case 178: /* shift_expression: shift_expression LSHIFT additive_expression  */
#line 1026 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", "<<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3506 "build/parser.tab.cpp"
    break;

  case 179: /* shift_expression: shift_expression RSHIFT additive_expression  */
#line 1031 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", ">>");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3516 "build/parser.tab.cpp"
    break;

  case 180: /* additive_expression: multiplicative_expression  */
#line 1039 "src/parser.y"
                              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3524 "build/parser.tab.cpp"
    break;

  case 181: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 1042 "src/parser.y"
                                                         {
        (yyval.node) = create_node("AdditiveExpression", "+");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3534 "build/parser.tab.cpp"
    break;

  case 182: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 1047 "src/parser.y"
                                                          {
        (yyval.node) = create_node("AdditiveExpression", "-");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3544 "build/parser.tab.cpp"
    break;

  case 183: /* multiplicative_expression: cast_expression  */
#line 1055 "src/parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3552 "build/parser.tab.cpp"
    break;

  case 184: /* multiplicative_expression: multiplicative_expression MUL cast_expression  */
#line 1058 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "*");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3562 "build/parser.tab.cpp"
    break;

  case 185: /* multiplicative_expression: multiplicative_expression DIV cast_expression  */
#line 1063 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "/");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3572 "build/parser.tab.cpp"
    break;

  case 186: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 1068 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "%");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3582 "build/parser.tab.cpp"
    break;

  case 187: /* cast_expression: unary_expression  */
#line 1076 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3590 "build/parser.tab.cpp"
    break;

  case 188: /* cast_expression: LPAREN type_name RPAREN cast_expression  */
#line 1079 "src/parser.y"
                                              {
        (yyval.node) = create_node("CastExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3600 "build/parser.tab.cpp"
    break;

  case 189: /* unary_expression: postfix_expression  */
#line 1087 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3608 "build/parser.tab.cpp"
    break;

  case 190: /* unary_expression: INC unary_expression  */
#line 1090 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "++");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3617 "build/parser.tab.cpp"
    break;

  case 191: /* unary_expression: DEC unary_expression  */
#line 1094 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "--");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3626 "build/parser.tab.cpp"
    break;

  case 192: /* unary_expression: unary_operator cast_expression  */
#line 1098 "src/parser.y"
                                     {
        (yyval.node) = create_node("UnaryExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3635 "build/parser.tab.cpp"
    break;

  case 193: /* unary_expression: SIZEOF unary_expression  */
#line 1102 "src/parser.y"
                              {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3644 "build/parser.tab.cpp"
    break;

  case 194: /* unary_expression: SIZEOF LPAREN type_name RPAREN  */
#line 1106 "src/parser.y"
                                     {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3653 "build/parser.tab.cpp"
    break;

  case 195: /* unary_operator: BIT_AND  */
#line 1113 "src/parser.y"
            { (yyval.str) = strdup("&"); }
#line 3659 "build/parser.tab.cpp"
    break;

  case 196: /* unary_operator: MUL  */
#line 1114 "src/parser.y"
          { (yyval.str) = strdup("*"); }
#line 3665 "build/parser.tab.cpp"
    break;

  case 197: /* unary_operator: PLUS  */
#line 1115 "src/parser.y"
           { (yyval.str) = strdup("+"); }
#line 3671 "build/parser.tab.cpp"
    break;

  case 198: /* unary_operator: MINUS  */
#line 1116 "src/parser.y"
            { (yyval.str) = strdup("-"); }
#line 3677 "build/parser.tab.cpp"
    break;

  case 199: /* unary_operator: BIT_NOT  */
#line 1117 "src/parser.y"
              { (yyval.str) = strdup("~"); }
#line 3683 "build/parser.tab.cpp"
    break;

  case 200: /* unary_operator: NOT  */
#line 1118 "src/parser.y"
          { (yyval.str) = strdup("!"); }
#line 3689 "build/parser.tab.cpp"
    break;

  case 201: /* postfix_expression: primary_expression  */
#line 1122 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3697 "build/parser.tab.cpp"
    break;

  case 202: /* postfix_expression: postfix_expression LBRACKET expression RBRACKET  */
#line 1125 "src/parser.y"
                                                      {
        (yyval.node) = create_node("ArraySubscript");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3707 "build/parser.tab.cpp"
    break;

  case 203: /* postfix_expression: postfix_expression LPAREN argument_expression_list RPAREN  */
#line 1130 "src/parser.y"
                                                                {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3717 "build/parser.tab.cpp"
    break;

  case 204: /* postfix_expression: postfix_expression LPAREN RPAREN  */
#line 1135 "src/parser.y"
                                       {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 3726 "build/parser.tab.cpp"
    break;

  case 205: /* postfix_expression: postfix_expression DOT ID  */
#line 1139 "src/parser.y"
                                {
        (yyval.node) = create_node("MemberAccess", ".");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3736 "build/parser.tab.cpp"
    break;

  case 206: /* postfix_expression: postfix_expression ARROW ID  */
#line 1144 "src/parser.y"
                                  {
        (yyval.node) = create_node("MemberAccess", "->");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3746 "build/parser.tab.cpp"
    break;

  case 207: /* postfix_expression: postfix_expression INC  */
#line 1149 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "++");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3755 "build/parser.tab.cpp"
    break;

  case 208: /* postfix_expression: postfix_expression DEC  */
#line 1153 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "--");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3764 "build/parser.tab.cpp"
    break;

  case 209: /* primary_expression: ID  */
#line 1160 "src/parser.y"
       {
        (yyval.node) = create_node("Identifier", (yyvsp[0].str));
    }
#line 3772 "build/parser.tab.cpp"
    break;

  case 210: /* primary_expression: constant  */
#line 1163 "src/parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3780 "build/parser.tab.cpp"
    break;

  case 211: /* primary_expression: string_literal  */
#line 1166 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3788 "build/parser.tab.cpp"
    break;

  case 212: /* primary_expression: LPAREN expression RPAREN  */
#line 1169 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3796 "build/parser.tab.cpp"
    break;

  case 213: /* string_literal: STRING_LIT  */
#line 1175 "src/parser.y"
               {
        (yyval.node) = create_node("StringLiteral", (yyvsp[0].str));
    }
#line 3804 "build/parser.tab.cpp"
    break;

  case 214: /* string_literal: string_literal STRING_LIT  */
#line 1178 "src/parser.y"
                                {
        (yyval.node) = create_node("StringLiteral");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild(create_node("StringLiteral", (yyvsp[0].str)));
    }
#line 3814 "build/parser.tab.cpp"
    break;

  case 215: /* argument_expression_list: assignment_expression  */
#line 1186 "src/parser.y"
                          {
        (yyval.node) = create_node("ArgumentList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3823 "build/parser.tab.cpp"
    break;

  case 216: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 1190 "src/parser.y"
                                                           {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3832 "build/parser.tab.cpp"
    break;

  case 217: /* constant: NUM  */
#line 1197 "src/parser.y"
        { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3838 "build/parser.tab.cpp"
    break;

  case 218: /* constant: FLOAT_LIT  */
#line 1198 "src/parser.y"
                { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3844 "build/parser.tab.cpp"
    break;

  case 219: /* constant: CHAR_LIT  */
#line 1199 "src/parser.y"
               { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3850 "build/parser.tab.cpp"
    break;

  case 220: /* constant: TRUE  */
#line 1200 "src/parser.y"
           { (yyval.node) = create_node("Constant", "true"); }
#line 3856 "build/parser.tab.cpp"
    break;

  case 221: /* constant: FALSE  */
#line 1201 "src/parser.y"
            { (yyval.node) = create_node("Constant", "false"); }
#line 3862 "build/parser.tab.cpp"
    break;

  case 222: /* constant: NULL_TOKEN  */
#line 1202 "src/parser.y"
                 { (yyval.node) = create_node("Constant", "NULL"); }
#line 3868 "build/parser.tab.cpp"
    break;

  case 223: /* constant: NULLPTR  */
#line 1203 "src/parser.y"
              { (yyval.node) = create_node("Constant", "nullptr"); }
#line 3874 "build/parser.tab.cpp"
    break;


#line 3878 "build/parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1206 "src/parser.y"


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
            
            // Generate MIPS assembly
            printf("\n=== MIPS ASSEMBLY GENERATION ===\n");
            MIPSGenerator mips_gen(tac_gen.get_instructions());
            // Pass array metadata from codegen to MIPS generator
            mips_gen.set_array_metadata(code_gen.array_dims, code_gen.array_element_types);
            // Pass variable types for type conversions
            mips_gen.set_variable_types(code_gen.variable_types);
            // Pass function names to distinguish from goto labels
            mips_gen.set_function_names(code_gen.function_names);
            // Pass static variables with their initial values
            mips_gen.set_static_variables(code_gen.static_var_init_values);
            mips_gen.generate("output.s");
            
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
