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


#line 199 "build/parser.tab.cpp"

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
  YYSYMBOL_SEMI = 100,                     /* SEMI  */
  YYSYMBOL_COMMA = 101,                    /* COMMA  */
  YYSYMBOL_QUESTION = 102,                 /* QUESTION  */
  YYSYMBOL_COLON = 103,                    /* COLON  */
  YYSYMBOL_LPAREN = 104,                   /* LPAREN  */
  YYSYMBOL_RPAREN = 105,                   /* RPAREN  */
  YYSYMBOL_LBRACE = 106,                   /* LBRACE  */
  YYSYMBOL_RBRACE = 107,                   /* RBRACE  */
  YYSYMBOL_LBRACKET = 108,                 /* LBRACKET  */
  YYSYMBOL_RBRACKET = 109,                 /* RBRACKET  */
  YYSYMBOL_ELLIPSIS = 110,                 /* ELLIPSIS  */
  YYSYMBOL_PREP = 111,                     /* PREP  */
  YYSYMBOL_NEWLINE = 112,                  /* NEWLINE  */
  YYSYMBOL_END = 113,                      /* END  */
  YYSYMBOL_ERROR = 114,                    /* ERROR  */
  YYSYMBOL_DESTRUCTOR = 115,               /* DESTRUCTOR  */
  YYSYMBOL_UMINUS = 116,                   /* UMINUS  */
  YYSYMBOL_UPLUS = 117,                    /* UPLUS  */
  YYSYMBOL_IF_WITHOUT_ELSE = 118,          /* IF_WITHOUT_ELSE  */
  YYSYMBOL_YYACCEPT = 119,                 /* $accept  */
  YYSYMBOL_program = 120,                  /* program  */
  YYSYMBOL_translation_unit = 121,         /* translation_unit  */
  YYSYMBOL_external_declaration = 122,     /* external_declaration  */
  YYSYMBOL_preprocessor_directive = 123,   /* preprocessor_directive  */
  YYSYMBOL_function_definition = 124,      /* function_definition  */
  YYSYMBOL_declaration = 125,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 126,   /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 127,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 128,           /* type_specifier  */
  YYSYMBOL_type_keyword = 129,             /* type_keyword  */
  YYSYMBOL_struct_or_union_specifier = 130, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 131,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 132,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 133,       /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 134,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 135,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 136,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 137,          /* enumerator_list  */
  YYSYMBOL_enumerator = 138,               /* enumerator  */
  YYSYMBOL_init_declarator_list = 139,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 140,          /* init_declarator  */
  YYSYMBOL_declarator = 141,               /* declarator  */
  YYSYMBOL_pointer = 142,                  /* pointer  */
  YYSYMBOL_direct_declarator = 143,        /* direct_declarator  */
  YYSYMBOL_144_1 = 144,                    /* $@1  */
  YYSYMBOL_parameter_list = 145,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 146,    /* parameter_declaration  */
  YYSYMBOL_abstract_declarator = 147,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 148, /* direct_abstract_declarator  */
  YYSYMBOL_type_name = 149,                /* type_name  */
  YYSYMBOL_initializer = 150,              /* initializer  */
  YYSYMBOL_initializer_list = 151,         /* initializer_list  */
  YYSYMBOL_compound_statement = 152,       /* compound_statement  */
  YYSYMBOL_block_item_list = 153,          /* block_item_list  */
  YYSYMBOL_block_item = 154,               /* block_item  */
  YYSYMBOL_statement = 155,                /* statement  */
  YYSYMBOL_labeled_statement = 156,        /* labeled_statement  */
  YYSYMBOL_expression_statement = 157,     /* expression_statement  */
  YYSYMBOL_selection_statement = 158,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 159,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 160,       /* for_init_statement  */
  YYSYMBOL_range_based_for = 161,          /* range_based_for  */
  YYSYMBOL_jump_statement = 162,           /* jump_statement  */
  YYSYMBOL_expression = 163,               /* expression  */
  YYSYMBOL_assignment_expression = 164,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 165,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 166,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 167,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 168,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 169,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 170,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 171,           /* and_expression  */
  YYSYMBOL_equality_expression = 172,      /* equality_expression  */
  YYSYMBOL_relational_expression = 173,    /* relational_expression  */
  YYSYMBOL_shift_expression = 174,         /* shift_expression  */
  YYSYMBOL_additive_expression = 175,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 176, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 177,          /* cast_expression  */
  YYSYMBOL_unary_expression = 178,         /* unary_expression  */
  YYSYMBOL_unary_operator = 179,           /* unary_operator  */
  YYSYMBOL_postfix_expression = 180,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 181,       /* primary_expression  */
  YYSYMBOL_string_literal = 182,           /* string_literal  */
  YYSYMBOL_argument_expression_list = 183, /* argument_expression_list  */
  YYSYMBOL_constant = 184                  /* constant  */
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1674

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  119
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  213
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  355

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   373


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
     115,   116,   117,   118
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   217,   217,   223,   228,   235,   238,   241,   247,   251,
     258,   267,   277,   285,   289,   294,   298,   306,   310,   311,
     312,   313,   317,   321,   322,   323,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   343,   350,   357,   362,
     368,   377,   378,   382,   386,   393,   401,   405,   412,   416,
     422,   428,   432,   437,   445,   449,   456,   459,   466,   470,
     477,   481,   489,   494,   500,   503,   510,   513,   516,   521,
     525,   525,   533,   541,   545,   549,   556,   561,   566,   573,
     577,   582,   589,   592,   595,   599,   603,   608,   611,   615,
     619,   627,   631,   639,   643,   647,   655,   659,   666,   669,
     676,   680,   687,   691,   698,   699,   700,   701,   702,   703,
     707,   711,   716,   723,   727,   733,   738,   744,   752,   757,
     762,   768,   775,   783,   787,   794,   800,   810,   813,   816,
     819,   823,   829,   832,   840,   843,   851,   852,   853,   854,
     855,   856,   857,   858,   859,   860,   861,   865,   868,   877,
     880,   888,   891,   899,   902,   910,   913,   921,   924,   932,
     935,   940,   948,   951,   956,   961,   966,   974,   977,   982,
     990,   993,   998,  1006,  1009,  1014,  1019,  1027,  1030,  1038,
    1041,  1045,  1049,  1053,  1057,  1064,  1065,  1066,  1067,  1068,
    1069,  1073,  1076,  1081,  1086,  1090,  1095,  1100,  1104,  1111,
    1114,  1117,  1120,  1126,  1129,  1137,  1141,  1148,  1149,  1150,
    1151,  1152,  1153,  1154
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
  "LSHIFT_EQ", "RSHIFT_EQ", "ARROW", "DOT", "SCOPE", "SEMI", "COMMA",
  "QUESTION", "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "ELLIPSIS", "PREP", "NEWLINE", "END", "ERROR", "DESTRUCTOR",
  "UMINUS", "UPLUS", "IF_WITHOUT_ELSE", "$accept", "program",
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

#define YYPACT_NINF (-165)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     189,  -165,  -165,  -165,    -9,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,   -38,   -48,  -165,    19,   189,  -165,  -165,  -165,  -165,
     -43,  1616,  1616,  -165,  -165,    -7,  -165,   -71,   -35,   -64,
     -61,   -31,    36,  -165,   -22,  -165,  -165,  -165,    23,  -165,
     -15,  -165,  -165,    -6,    63,    47,   419,  -165,   -64,    25,
     972,    36,    36,   108,   -59,  -165,  -165,  -165,   -48,  1189,
    -165,    47,    47,   -48,   819,  -165,    91,  1437,    96,    95,
     598,   101,   152,   110,  1345,  1483,   113,   131,  -165,  -165,
    -165,  -165,   134,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    1529,  1529,  -165,  -165,  -165,  -165,   926,  -165,  -165,   -43,
    -165,   524,  -165,  -165,  -165,  -165,  -165,  -165,  -165,    89,
    -165,  -165,   -69,   171,   184,   174,   188,   116,   161,   132,
     166,   119,  -165,   417,  1437,   175,  -165,   215,  -165,  -165,
    1616,  -165,  -165,   172,     6,    13,  1437,    36,  -165,  -165,
     211,  1189,  -165,  -165,   841,   870,   133,  -165,  -165,  -165,
    -165,  -165,   179,  -165,   598,   250,   737,   185,  1437,  -165,
     145,   926,  -165,  1437,  1437,   598,  1437,  -165,  -165,   -49,
     183,    21,  -165,  -165,  -165,  1437,  1437,  1437,  1437,  1437,
    1437,  1437,  1437,  1437,  1437,  1437,  1437,  1437,  1437,  1437,
    1437,  1437,  1437,  1437,  1437,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  1437,  -165,  -165,  -165,
    -165,   227,   232,  1241,  1437,  -165,   -32,    24,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,    14,  -165,  -165,  -165,   -48,
     598,  -165,   190,  -165,    97,  -165,  1391,   187,  -165,    50,
    -165,   191,    52,    57,  -165,   360,  1027,     4,  -165,    64,
    1437,  -165,  -165,   171,    30,   184,   174,   188,   116,   161,
     161,   132,   132,   132,   132,   166,   166,   119,   119,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,    69,   -72,   306,
    -165,   -16,  -165,   284,  -165,  1137,  -165,  -165,  -165,  1437,
     199,   242,  1293,   598,   598,  -165,   598,   598,  -165,    70,
     201,  -165,   209,    64,   686,  1082,  -165,  1437,  1437,  -165,
    -165,  -165,  -165,  -165,  -165,    75,  1437,   219,   598,    77,
    -165,   311,  -165,  -165,  -165,  -165,  -165,  -165,    83,  -165,
     222,  -165,  -165,   224,   233,  1437,  -165,   598,   598,  -165,
    -165,  -165,   233,  -165,  -165
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    21,    27,    32,     0,    19,    31,    29,    30,    20,
      28,    33,    18,    41,    17,    42,    34,    26,    35,    25,
      66,    64,     0,     8,     0,     2,     3,     7,     5,     6,
       0,    13,    15,    22,    23,     0,    24,     0,     0,    63,
      53,    52,     0,    65,     0,     1,     4,    12,     0,    58,
      60,    14,    16,    40,    39,     0,     0,    10,    62,    70,
       0,     0,     0,    56,     0,    54,    67,    11,     0,     0,
       9,     0,     0,     0,     0,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   212,   213,
     210,   211,   199,   207,   208,   209,   203,   187,   188,   186,
       0,     0,   190,   185,   189,   114,     0,    98,   102,     0,
     106,     0,   100,   103,   104,   105,   107,   108,   109,     0,
     132,   134,   147,   149,   151,   153,   155,   157,   159,   162,
     167,   170,   173,   177,     0,   179,   191,   201,   200,    72,
       0,   199,    69,     0,     0,     0,     0,     0,    51,    59,
      60,     0,    61,    93,     0,     0,     0,    46,    48,    38,
      44,   129,     0,   128,     0,     0,     0,     0,     0,   131,
       0,     0,   183,     0,     0,     0,     0,   180,   181,    91,
       0,     0,    99,   101,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   182,   177,   197,
     198,     0,     0,     0,     0,   204,    78,     0,    73,    68,
      50,    49,    57,    55,    96,     0,    37,    36,    45,     0,
       0,   112,     0,   124,     0,   123,     0,     0,   127,     0,
     130,     0,     0,     0,   110,     0,     0,    79,    92,    81,
       0,   202,   133,   150,     0,   152,   154,   156,   158,   160,
     161,   163,   164,   165,   166,   168,   169,   171,   172,   174,
     175,   176,   135,   196,   195,   194,   205,     0,     0,     0,
      76,    79,    77,     0,    71,     0,    94,    47,   111,     0,
      66,     0,     0,     0,     0,   184,     0,     0,    87,     0,
       0,    83,     0,    80,     0,     0,   178,     0,     0,   193,
     192,    75,    74,    95,    97,     0,     0,     0,     0,     0,
     122,   115,   117,   118,    88,    82,    84,    89,     0,    85,
       0,   148,   206,     0,   125,     0,   120,     0,     0,    90,
      86,   119,   126,   121,   116
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,   303,  -165,  -165,   -47,     7,  -165,    10,
    -165,  -165,  -165,   181,   -68,  -165,   102,  -165,   198,   193,
    -165,   279,     0,   -19,   -34,  -165,  -135,    55,  -158,  -164,
     178,  -143,  -165,   -24,  -165,   239,   -79,  -165,  -156,  -165,
    -165,  -165,  -165,  -165,   -70,   -57,  -165,    34,  -165,   167,
     164,   165,   168,   169,    72,   149,    68,    76,   -93,   -54,
    -165,  -165,  -165,  -165,  -165,  -165
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    24,    25,    26,    27,    28,    29,   226,    31,    32,
      33,    34,    35,    74,    75,   156,   157,    36,    64,    65,
      48,    49,   150,    38,    39,   140,   309,   228,   310,   259,
     180,   152,   235,   110,   111,   112,   113,   114,   115,   116,
     117,   246,   247,   118,   119,   120,   216,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   287,   138
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   165,    43,   143,    58,   227,   160,    30,   234,   108,
     245,    20,   153,    57,   170,   186,    20,    21,    21,    45,
     162,   258,    44,    21,    20,    37,    70,    20,    21,   185,
      50,   172,    30,   187,    21,    56,   181,   320,    51,    52,
      59,   217,   147,    20,    60,    61,   177,   178,   148,    40,
      41,    53,    54,     2,    69,   255,    22,    47,     3,   256,
       4,    22,     6,   109,   108,    73,     7,     8,   292,    22,
      10,    11,   289,   158,    13,    62,   256,    15,    16,    17,
     218,    73,    73,    66,    73,   241,   160,   160,   289,   232,
     302,    56,   256,   313,   153,    63,   254,    42,   249,    55,
      71,   181,    18,   252,   253,    19,   181,   147,   255,   279,
     280,   281,   256,   230,   147,   295,   179,   264,   109,   243,
     231,   296,   185,    67,    68,   293,   261,   313,   262,   294,
     139,   185,   218,   317,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   185,   324,   185,   288,   304,   300,   306,   185,   282,
     257,   298,   307,    21,    73,    73,   286,   316,   314,    72,
     318,   293,   315,   244,   319,   334,   185,   146,   185,   338,
     343,   179,   347,   301,   293,   202,   203,   204,   349,   184,
     185,   161,     1,   192,   193,     2,   163,    47,   164,   312,
       3,    22,     4,     5,     6,   166,   218,   291,     7,     8,
       9,   167,    10,    11,   168,    12,    13,   173,    14,    15,
      16,    17,   198,   199,   330,   331,   290,   332,   333,   325,
     200,   201,   329,   238,   239,   174,   257,   175,   153,   158,
     194,   195,   196,   197,    18,   250,   185,    19,    20,   346,
     219,   220,   154,   155,   188,    21,   344,    58,   340,   144,
     145,   342,   190,   218,   269,   270,   275,   276,   353,   354,
     291,   189,   221,   222,   191,   352,   277,   278,   225,   223,
      69,   229,   240,   224,   242,   248,   283,     1,   260,    44,
       2,   284,   303,    22,   299,     3,   305,     4,     5,     6,
      23,   327,   326,     7,     8,     9,   335,    10,    11,     1,
      12,    13,     2,    14,    15,    16,    17,     3,   336,     4,
       5,     6,   345,   348,   351,     7,     8,     9,    46,    10,
      11,   350,    12,    13,   185,    14,    15,    16,    17,    18,
     233,   297,    19,   271,   272,   273,   274,   149,   322,   251,
     183,   341,   265,   263,   266,     0,     0,     0,   267,     0,
     268,    18,     0,     1,    19,    20,     2,     0,     0,     0,
       0,     3,    21,     4,     5,     6,     0,     0,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,    14,
      15,    16,    17,     0,   321,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     289,   308,     0,     0,   256,    18,     0,     0,    19,     0,
       0,     0,     1,    76,    77,     2,    21,    78,    79,    80,
       3,     0,     4,     5,     6,    81,    82,    83,     7,     8,
       9,    84,    10,    11,    85,    12,    13,    86,    14,    15,
      16,    17,     0,    87,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,   255,   308,     0,     0,   256,     0,
       0,     0,     0,     0,    18,    90,    91,    19,    92,    93,
      94,    95,    96,    97,    98,    99,   205,   206,   207,   208,
     209,   210,     0,     0,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,   102,   103,     0,     0,   104,   211,
     212,   213,   214,   215,     0,     0,     0,     0,     0,   105,
       0,     0,     0,   106,     0,    56,   107,     1,    76,    77,
       2,     0,    78,    79,    80,     3,     0,     4,     5,     6,
      81,    82,    83,     7,     8,     9,    84,    10,    11,    85,
      12,    13,    86,    14,    15,    16,    17,     0,    87,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      90,    91,    19,    92,    93,    94,    95,    96,    97,    98,
      99,     0,     0,     0,     0,     0,     0,     0,     0,   100,
     101,     0,    76,    77,     0,     0,    78,    79,    80,   102,
     103,     0,     0,   104,    81,    82,    83,     0,     0,     0,
      84,     0,     0,    85,   105,     0,    86,     0,   106,     0,
      56,   182,    87,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    91,     0,    92,    93,    94,
      95,    96,    97,    98,    99,     0,     0,     0,     0,     0,
       0,     0,     0,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,   102,   103,     0,     0,   104,     0,     1,
       0,     0,     2,     0,     0,     0,     0,     3,   105,     4,
       5,     6,   106,     0,    56,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,    14,    15,    16,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    18,     0,     2,    19,     0,     0,     0,     3,     0,
       4,     5,     6,     0,     0,     0,     7,     8,     9,     0,
      10,    11,    85,    12,    13,     0,    14,    15,    16,    17,
       0,     0,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   337,    18,    90,    91,    19,   141,    93,    94,    95,
      96,    97,    98,    99,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   103,     0,     2,   104,     0,     0,     0,
       3,     0,     4,     0,     6,     0,     0,   105,     7,     8,
       0,   106,    10,    11,     0,     0,    13,     2,     0,    15,
      16,    17,     3,     0,     4,     0,     6,     0,     0,     0,
       7,     8,     0,     0,    10,    11,     0,     0,    13,     0,
       0,    15,    16,    17,    18,     0,     2,    19,     0,     0,
       0,     3,     0,     4,     0,     6,     0,     0,     0,     7,
       8,     0,     0,    10,    11,     0,    18,    13,     0,    19,
      15,    16,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,   159,     0,    19,     0,
       0,     0,     2,     0,     0,     0,     0,     3,     0,     4,
       0,     6,     0,     0,     0,     7,     8,     0,   236,    10,
      11,    85,     0,    13,     0,     0,    15,    16,    17,     0,
       0,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   237,     0,     0,
       0,    18,    90,    91,    19,   141,    93,    94,    95,    96,
      97,    98,    99,     0,     0,     0,     0,    85,     0,     0,
       0,   100,   101,     0,     0,     0,     0,    88,    89,     0,
       0,   102,   103,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,    91,
     106,   141,    93,    94,    95,    96,    97,    98,    99,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
       0,     0,    85,     0,     0,     0,     0,   102,   103,     0,
       0,   104,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,     0,     0,     0,
       0,   142,     0,    90,    91,     0,   141,    93,    94,    95,
      96,    97,    98,    99,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,     0,     0,    85,     0,     0,
       0,     0,   102,   103,     0,     0,   104,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,     0,   311,     0,    90,    91,
       0,   141,    93,    94,    95,    96,    97,    98,    99,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
       0,     0,    85,     0,     0,     0,     0,   102,   103,     0,
       0,   104,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,     0,     0,     0,
       0,   339,     0,    90,    91,     0,   141,    93,    94,    95,
      96,    97,    98,    99,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,    85,     0,     0,     0,     0,     0,
       0,     0,   102,   103,    88,    89,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,   151,   323,    90,    91,     0,   141,    93,
      94,    95,    96,    97,    98,    99,     0,     0,     0,     0,
       0,     0,     0,     0,   100,   101,    85,     0,     0,     0,
       0,     0,     0,     0,   102,   103,    88,    89,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,     0,   151,     0,    90,    91,     0,
     141,    93,    94,    95,    96,    97,    98,    99,     0,     0,
       0,     0,     0,     0,     0,     0,   100,   101,    85,     0,
       0,     0,     0,     0,     0,     0,   102,   103,    88,    89,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,   285,     0,     0,    90,
      91,     0,   141,    93,    94,    95,    96,    97,    98,    99,
       0,     0,     0,     0,     0,     0,     0,     0,   100,   101,
      85,     0,     0,     0,     0,     0,     0,     0,   102,   103,
      88,    89,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,   328,     0,
       0,    90,    91,     0,   141,    93,    94,    95,    96,    97,
      98,    99,     0,     0,     0,     0,    85,     0,     0,     0,
     100,   101,     0,     0,     0,     0,    88,    89,     0,     0,
     102,   103,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   169,     0,    90,    91,   106,
     141,    93,    94,    95,    96,    97,    98,    99,     0,     0,
       0,     0,    85,     0,     0,     0,   100,   101,     0,     0,
       0,     0,    88,    89,     0,     0,   102,   103,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,     0,    90,    91,   106,   141,    93,    94,    95,
      96,    97,    98,    99,     0,     0,     0,     0,    85,     0,
       0,     0,   100,   101,     0,     0,     0,     0,    88,    89,
       0,     0,   102,   103,     0,     0,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
      91,   106,   141,    93,    94,    95,    96,    97,    98,    99,
       0,     0,     0,     0,    85,     0,     0,     0,   100,   101,
       0,     0,     0,     0,    88,    89,     0,     0,   102,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,   171,   141,    93,
      94,    95,    96,    97,    98,    99,     0,     0,     0,     0,
       0,     0,     0,     0,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,   102,   103,     0,     0,   104,     1,
       0,     0,     2,     0,     0,     0,     0,     3,     0,     4,
       5,     6,     0,   176,     0,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,    14,    15,    16,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,    19
};

static const yytype_int16 yycheck[] =
{
       0,    80,    21,    60,    38,   140,    74,     0,   151,    56,
     166,    59,    69,    37,    84,    84,    59,    66,    66,     0,
      77,   179,    22,    66,    59,    25,    50,    59,    66,   101,
      30,    85,    25,   102,    66,   106,   106,   109,    31,    32,
     104,   134,   101,    59,   108,   106,   100,   101,   107,    58,
      59,    58,    59,     6,    69,   104,   104,   100,    11,   108,
      13,   104,    15,    56,   111,    55,    19,    20,   226,   104,
      23,    24,   104,    73,    27,   106,   108,    30,    31,    32,
     134,    71,    72,   105,    74,   164,   154,   155,   104,   146,
     246,   106,   108,   257,   151,    59,   175,   106,   168,   106,
     106,   171,    55,   173,   174,    58,   176,   101,   104,   202,
     203,   204,   108,   107,   101,   101,   106,   187,   111,   166,
     107,   107,   101,   100,   101,   101,   105,   291,   185,   105,
     105,   101,   186,   103,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   101,   295,   101,   224,   105,    59,   105,   101,   216,
     179,   240,   105,    66,   154,   155,   223,   260,   104,   106,
     101,   101,   108,   166,   105,   105,   101,    69,   101,   314,
     105,   171,   105,    86,   101,    66,    67,    68,   105,   100,
     101,   100,     3,    77,    78,     6,   100,   100,   103,   256,
      11,   104,    13,    14,    15,   104,   260,   226,    19,    20,
      21,    59,    23,    24,   104,    26,    27,   104,    29,    30,
      31,    32,    90,    91,   303,   304,   226,   306,   307,   299,
      64,    65,   302,   100,   101,   104,   255,   103,   295,   239,
      79,    80,    81,    82,    55,   100,   101,    58,    59,   328,
      75,    76,    71,    72,    83,    66,   326,   291,   315,    61,
      62,   318,    88,   317,   192,   193,   198,   199,   347,   348,
     289,    87,    97,    98,    86,   345,   200,   201,    63,   104,
      69,   109,   103,   108,    34,   100,    59,     3,   105,   289,
       6,    59,   105,   104,   104,    11,   105,    13,    14,    15,
     111,    59,   103,    19,    20,    21,   105,    23,    24,     3,
      26,    27,     6,    29,    30,    31,    32,    11,   109,    13,
      14,    15,   103,    12,   100,    19,    20,    21,    25,    23,
      24,   109,    26,    27,   101,    29,    30,    31,    32,    55,
     147,   239,    58,   194,   195,   196,   197,    68,   293,   171,
     111,   317,   188,   186,   189,    -1,    -1,    -1,   190,    -1,
     191,    55,    -1,     3,    58,    59,     6,    -1,    -1,    -1,
      -1,    11,    66,    13,    14,    15,    -1,    -1,    -1,    19,
      20,    21,    -1,    23,    24,    -1,    26,    27,    -1,    29,
      30,    31,    32,    -1,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,    -1,    -1,   108,    55,    -1,    -1,    58,    -1,
      -1,    -1,     3,     4,     5,     6,    66,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    69,    70,    71,    72,
      73,    74,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,    92,
      93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,   100,
      -1,    -1,    -1,   104,    -1,   106,   107,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,     4,     5,    -1,    -1,     8,     9,    10,    85,
      86,    -1,    -1,    89,    16,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,   100,    -1,    28,    -1,   104,    -1,
     106,   107,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    89,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,   100,    13,
      14,    15,   104,    -1,   106,    19,    20,    21,    -1,    23,
      24,    -1,    26,    27,    -1,    29,    30,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    55,    -1,     6,    58,    -1,    -1,    -1,    11,    -1,
      13,    14,    15,    -1,    -1,    -1,    19,    20,    21,    -1,
      23,    24,    25,    26,    27,    -1,    29,    30,    31,    32,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,     6,    89,    -1,    -1,    -1,
      11,    -1,    13,    -1,    15,    -1,    -1,   100,    19,    20,
      -1,   104,    23,    24,    -1,    -1,    27,     6,    -1,    30,
      31,    32,    11,    -1,    13,    -1,    15,    -1,    -1,    -1,
      19,    20,    -1,    -1,    23,    24,    -1,    -1,    27,    -1,
      -1,    30,    31,    32,    55,    -1,     6,    58,    -1,    -1,
      -1,    11,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,
      20,    -1,    -1,    23,    24,    -1,    55,    27,    -1,    58,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,   107,    -1,    58,    -1,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    13,
      -1,    15,    -1,    -1,    -1,    19,    20,    -1,   107,    23,
      24,    25,    -1,    27,    -1,    -1,    30,    31,    32,    -1,
      -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    35,    36,    -1,
      -1,    85,    86,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
     104,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    89,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,   109,    -1,    56,    57,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    89,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,    -1,   109,    -1,    56,    57,
      -1,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    89,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,    -1,    -1,
      -1,   109,    -1,    56,    57,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    35,    36,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,    56,    57,    -1,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    35,    36,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,    -1,    56,    57,    -1,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    35,    36,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,    -1,    -1,    56,
      57,    -1,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      35,    36,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,    -1,
      -1,    56,    57,    -1,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      75,    76,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,
      85,    86,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    56,    57,   104,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    75,    76,    -1,    -1,
      -1,    -1,    35,    36,    -1,    -1,    85,    86,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   100,    -1,    56,    57,   104,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    35,    36,
      -1,    -1,    85,    86,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,   104,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    75,    76,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    85,    86,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,   104,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    13,
      14,    15,    -1,   104,    -1,    19,    20,    21,    -1,    23,
      24,    -1,    26,    27,    -1,    29,    30,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    11,    13,    14,    15,    19,    20,    21,
      23,    24,    26,    27,    29,    30,    31,    32,    55,    58,
      59,    66,   104,   111,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   136,   141,   142,   143,
      58,    59,   106,   142,   141,     0,   122,   100,   139,   140,
     141,   126,   126,    58,    59,   106,   106,   152,   143,   104,
     108,   106,   106,    59,   137,   138,   105,   100,   101,    69,
     152,   106,   106,   128,   132,   133,     4,     5,     8,     9,
      10,    16,    17,    18,    22,    25,    28,    34,    35,    36,
      56,    57,    59,    60,    61,    62,    63,    64,    65,    66,
      75,    76,    85,    86,    89,   100,   104,   107,   125,   126,
     152,   153,   154,   155,   156,   157,   158,   159,   162,   163,
     164,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   184,   105,
     144,    59,   109,   164,   137,   137,    69,   101,   107,   140,
     141,   106,   150,   164,   132,   132,   134,   135,   141,   107,
     133,   100,   164,   100,   103,   155,   104,    59,   104,   100,
     163,   104,   178,   104,   104,   103,   104,   178,   178,   128,
     149,   163,   107,   154,   100,   101,    84,   102,    83,    87,
      88,    86,    77,    78,    79,    80,    81,    82,    90,    91,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    92,    93,    94,    95,    96,   165,   177,   178,    75,
      76,    97,    98,   104,   108,    63,   126,   145,   146,   109,
     107,   107,   164,   138,   150,   151,   107,   107,   100,   101,
     103,   155,    34,   125,   126,   157,   160,   161,   100,   163,
     100,   149,   163,   163,   155,   104,   108,   142,   147,   148,
     105,   105,   164,   168,   163,   169,   170,   171,   172,   173,
     173,   174,   174,   174,   174,   175,   175,   176,   176,   177,
     177,   177,   164,    59,    59,   105,   164,   183,   163,   104,
     141,   142,   147,   101,   105,   101,   107,   135,   155,   104,
      59,    86,   157,   105,   105,   105,   105,   105,   105,   145,
     147,   109,   164,   148,   104,   108,   177,   103,   101,   105,
     109,   110,   146,   107,   150,   163,   103,    59,   105,   163,
     155,   155,   155,   155,   105,   105,   109,   105,   145,   109,
     164,   166,   164,   105,   163,   103,   155,   105,    12,   105,
     109,   100,   163,   155,   155
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   119,   120,   121,   121,   122,   122,   122,   123,   124,
     124,   125,   125,   126,   126,   126,   126,   127,   127,   127,
     127,   127,   128,   128,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   131,   131,   132,   132,   133,   134,   134,   135,   136,
     136,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   142,   142,   143,   143,   143,   143,
     144,   143,   143,   145,   145,   145,   146,   146,   146,   147,
     147,   147,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   149,   149,   150,   150,   150,   151,   151,   152,   152,
     153,   153,   154,   154,   155,   155,   155,   155,   155,   155,
     156,   156,   156,   157,   157,   158,   158,   158,   159,   159,
     159,   159,   159,   160,   160,   161,   161,   162,   162,   162,
     162,   162,   163,   163,   164,   164,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   166,   166,   167,
     167,   168,   168,   169,   169,   170,   170,   171,   171,   172,
     172,   172,   173,   173,   173,   173,   173,   174,   174,   174,
     175,   175,   175,   176,   176,   176,   176,   177,   177,   178,
     178,   178,   178,   178,   178,   179,   179,   179,   179,   179,
     179,   180,   180,   180,   180,   180,   180,   180,   180,   181,
     181,   181,   181,   182,   182,   183,   183,   184,   184,   184,
     184,   184,   184,   184
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
       1,     3,     2,     1,     1,     2,     1,     3,     4,     3,
       0,     5,     3,     1,     3,     3,     2,     2,     1,     1,
       2,     1,     3,     2,     3,     3,     4,     2,     3,     3,
       4,     1,     2,     1,     3,     4,     1,     3,     2,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     1,     5,     7,     5,     5,     7,
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
#line 217 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1921 "build/parser.tab.cpp"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 223 "src/parser.y"
                         {
        (yyval.node) = create_node("TranslationUnit");
        (yyval.node)->addChild((yyvsp[0].node));
        root = (yyval.node);
    }
#line 1931 "build/parser.tab.cpp"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 228 "src/parser.y"
                                            {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1940 "build/parser.tab.cpp"
    break;

  case 5: /* external_declaration: function_definition  */
#line 235 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1948 "build/parser.tab.cpp"
    break;

  case 6: /* external_declaration: declaration  */
#line 238 "src/parser.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1956 "build/parser.tab.cpp"
    break;

  case 7: /* external_declaration: preprocessor_directive  */
#line 241 "src/parser.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1964 "build/parser.tab.cpp"
    break;

  case 8: /* preprocessor_directive: PREP  */
#line 247 "src/parser.y"
         { (yyval.node) = create_node("Preprocessor", (yyvsp[0].str)); }
#line 1970 "build/parser.tab.cpp"
    break;

  case 9: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 251 "src/parser.y"
                                                         {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 1982 "build/parser.tab.cpp"
    break;

  case 10: /* function_definition: declarator compound_statement  */
#line 258 "src/parser.y"
                                    {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 1993 "build/parser.tab.cpp"
    break;

  case 11: /* declaration: declaration_specifiers init_declarator_list SEMI  */
#line 267 "src/parser.y"
                                                     {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
	if (in_typedef_declaration) {
            collect_typedef_names((yyvsp[-1].node));
        }

        in_typedef_declaration = 0;
    }
#line 2008 "build/parser.tab.cpp"
    break;

  case 12: /* declaration: declaration_specifiers SEMI  */
#line 277 "src/parser.y"
                                  {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        in_typedef_declaration = 0;
    }
#line 2018 "build/parser.tab.cpp"
    break;

  case 13: /* declaration_specifiers: storage_class_specifier  */
#line 285 "src/parser.y"
                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2027 "build/parser.tab.cpp"
    break;

  case 14: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 289 "src/parser.y"
                                                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2037 "build/parser.tab.cpp"
    break;

  case 15: /* declaration_specifiers: type_specifier  */
#line 294 "src/parser.y"
                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2046 "build/parser.tab.cpp"
    break;

  case 16: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 298 "src/parser.y"
                                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2056 "build/parser.tab.cpp"
    break;

  case 17: /* storage_class_specifier: TYPEDEF  */
#line 306 "src/parser.y"
            {
        (yyval.node) = create_node("StorageClass", "typedef");
        in_typedef_declaration = 1;
    }
#line 2065 "build/parser.tab.cpp"
    break;

  case 18: /* storage_class_specifier: STATIC  */
#line 310 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "static"); }
#line 2071 "build/parser.tab.cpp"
    break;

  case 19: /* storage_class_specifier: EXTERN  */
#line 311 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "extern"); }
#line 2077 "build/parser.tab.cpp"
    break;

  case 20: /* storage_class_specifier: REGISTER  */
#line 312 "src/parser.y"
               { (yyval.node) = create_node("StorageClass", "register"); }
#line 2083 "build/parser.tab.cpp"
    break;

  case 21: /* storage_class_specifier: AUTO  */
#line 313 "src/parser.y"
           { (yyval.node) = create_node("StorageClass", "auto"); }
#line 2089 "build/parser.tab.cpp"
    break;

  case 22: /* type_specifier: type_keyword  */
#line 317 "src/parser.y"
                 {
        (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str));
        strcpy(current_type, (yyvsp[0].str));
    }
#line 2098 "build/parser.tab.cpp"
    break;

  case 23: /* type_specifier: struct_or_union_specifier  */
#line 321 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2104 "build/parser.tab.cpp"
    break;

  case 24: /* type_specifier: enum_specifier  */
#line 322 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2110 "build/parser.tab.cpp"
    break;

  case 25: /* type_specifier: TYPEDEF_NAME  */
#line 323 "src/parser.y"
                   {  // ← Now conflict-free!
        (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str));
        strcpy(current_type, (yyvsp[0].str));
    }
#line 2119 "build/parser.tab.cpp"
    break;

  case 26: /* type_keyword: VOID  */
#line 330 "src/parser.y"
         { (yyval.str) = strdup("void"); }
#line 2125 "build/parser.tab.cpp"
    break;

  case 27: /* type_keyword: CHAR  */
#line 331 "src/parser.y"
           { (yyval.str) = strdup("char"); }
#line 2131 "build/parser.tab.cpp"
    break;

  case 28: /* type_keyword: SHORT  */
#line 332 "src/parser.y"
            { (yyval.str) = strdup("short"); }
#line 2137 "build/parser.tab.cpp"
    break;

  case 29: /* type_keyword: INT  */
#line 333 "src/parser.y"
          { (yyval.str) = strdup("int"); }
#line 2143 "build/parser.tab.cpp"
    break;

  case 30: /* type_keyword: LONG  */
#line 334 "src/parser.y"
           { (yyval.str) = strdup("long"); }
#line 2149 "build/parser.tab.cpp"
    break;

  case 31: /* type_keyword: FLOAT  */
#line 335 "src/parser.y"
            { (yyval.str) = strdup("float"); }
#line 2155 "build/parser.tab.cpp"
    break;

  case 32: /* type_keyword: DOUBLE  */
#line 336 "src/parser.y"
             { (yyval.str) = strdup("double"); }
#line 2161 "build/parser.tab.cpp"
    break;

  case 33: /* type_keyword: SIGNED  */
#line 337 "src/parser.y"
             { (yyval.str) = strdup("signed"); }
#line 2167 "build/parser.tab.cpp"
    break;

  case 34: /* type_keyword: UNSIGNED  */
#line 338 "src/parser.y"
               { (yyval.str) = strdup("unsigned"); }
#line 2173 "build/parser.tab.cpp"
    break;

  case 35: /* type_keyword: BOOL  */
#line 339 "src/parser.y"
           { (yyval.str) = strdup("bool"); }
#line 2179 "build/parser.tab.cpp"
    break;

  case 36: /* struct_or_union_specifier: struct_or_union ID LBRACE struct_declaration_list RBRACE  */
#line 343 "src/parser.y"
                                                             {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-4].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2191 "build/parser.tab.cpp"
    break;

  case 37: /* struct_or_union_specifier: struct_or_union TYPEDEF_NAME LBRACE struct_declaration_list RBRACE  */
#line 350 "src/parser.y"
                                                                         {  // ← ADD THIS
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-4].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2203 "build/parser.tab.cpp"
    break;

  case 38: /* struct_or_union_specifier: struct_or_union LBRACE struct_declaration_list RBRACE  */
#line 357 "src/parser.y"
                                                            {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2213 "build/parser.tab.cpp"
    break;

  case 39: /* struct_or_union_specifier: struct_or_union ID  */
#line 362 "src/parser.y"
                         {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-1].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2224 "build/parser.tab.cpp"
    break;

  case 40: /* struct_or_union_specifier: struct_or_union TYPEDEF_NAME  */
#line 368 "src/parser.y"
                                   {  // ← ADD THIS
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-1].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2235 "build/parser.tab.cpp"
    break;

  case 41: /* struct_or_union: STRUCT  */
#line 377 "src/parser.y"
           { (yyval.str) = strdup("struct"); }
#line 2241 "build/parser.tab.cpp"
    break;

  case 42: /* struct_or_union: UNION  */
#line 378 "src/parser.y"
            { (yyval.str) = strdup("union"); }
#line 2247 "build/parser.tab.cpp"
    break;

  case 43: /* struct_declaration_list: struct_declaration  */
#line 382 "src/parser.y"
                       {
        (yyval.node) = create_node("StructDeclarationList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2256 "build/parser.tab.cpp"
    break;

  case 44: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 386 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2265 "build/parser.tab.cpp"
    break;

  case 45: /* struct_declaration: type_specifier struct_declarator_list SEMI  */
#line 393 "src/parser.y"
                                               {
        (yyval.node) = create_node("StructDeclaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2275 "build/parser.tab.cpp"
    break;

  case 46: /* struct_declarator_list: struct_declarator  */
#line 401 "src/parser.y"
                      {
        (yyval.node) = create_node("StructDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2284 "build/parser.tab.cpp"
    break;

  case 47: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 405 "src/parser.y"
                                                     {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2293 "build/parser.tab.cpp"
    break;

  case 48: /* struct_declarator: declarator  */
#line 412 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2299 "build/parser.tab.cpp"
    break;

  case 49: /* enum_specifier: ENUM ID LBRACE enumerator_list RBRACE  */
#line 416 "src/parser.y"
                                          {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2310 "build/parser.tab.cpp"
    break;

  case 50: /* enum_specifier: ENUM TYPEDEF_NAME LBRACE enumerator_list RBRACE  */
#line 422 "src/parser.y"
                                                      {  // ← ADD THIS
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
        parser_add_type_name((yyvsp[-3].str));
    }
#line 2321 "build/parser.tab.cpp"
    break;

  case 51: /* enum_specifier: ENUM LBRACE enumerator_list RBRACE  */
#line 428 "src/parser.y"
                                         {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2330 "build/parser.tab.cpp"
    break;

  case 52: /* enum_specifier: ENUM ID  */
#line 432 "src/parser.y"
              {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2340 "build/parser.tab.cpp"
    break;

  case 53: /* enum_specifier: ENUM TYPEDEF_NAME  */
#line 437 "src/parser.y"
                        {  // ← ADD THIS
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
        parser_add_type_name((yyvsp[0].str));
    }
#line 2350 "build/parser.tab.cpp"
    break;

  case 54: /* enumerator_list: enumerator  */
#line 445 "src/parser.y"
               {
        (yyval.node) = create_node("EnumeratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2359 "build/parser.tab.cpp"
    break;

  case 55: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 449 "src/parser.y"
                                       {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2368 "build/parser.tab.cpp"
    break;

  case 56: /* enumerator: ID  */
#line 456 "src/parser.y"
       {
        (yyval.node) = create_node("Enumerator", (yyvsp[0].str));
    }
#line 2376 "build/parser.tab.cpp"
    break;

  case 57: /* enumerator: ID ASSIGN assignment_expression  */
#line 459 "src/parser.y"
                                      {
        (yyval.node) = create_node("Enumerator", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2385 "build/parser.tab.cpp"
    break;

  case 58: /* init_declarator_list: init_declarator  */
#line 466 "src/parser.y"
                    {
        (yyval.node) = create_node("InitDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2394 "build/parser.tab.cpp"
    break;

  case 59: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 470 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2403 "build/parser.tab.cpp"
    break;

  case 60: /* init_declarator: declarator  */
#line 477 "src/parser.y"
               {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2412 "build/parser.tab.cpp"
    break;

  case 61: /* init_declarator: declarator ASSIGN initializer  */
#line 481 "src/parser.y"
                                    {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2422 "build/parser.tab.cpp"
    break;

  case 62: /* declarator: pointer direct_declarator  */
#line 489 "src/parser.y"
                              {
        (yyval.node) = create_node("Declarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2432 "build/parser.tab.cpp"
    break;

  case 63: /* declarator: direct_declarator  */
#line 494 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2440 "build/parser.tab.cpp"
    break;

  case 64: /* pointer: MUL  */
#line 500 "src/parser.y"
        {
        (yyval.node) = create_node("Pointer");
    }
#line 2448 "build/parser.tab.cpp"
    break;

  case 65: /* pointer: MUL pointer  */
#line 503 "src/parser.y"
                  {
        (yyval.node) = create_node("Pointer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2457 "build/parser.tab.cpp"
    break;

  case 66: /* direct_declarator: ID  */
#line 510 "src/parser.y"
       {
        (yyval.node) = create_node("DirectDeclarator", (yyvsp[0].str));
    }
#line 2465 "build/parser.tab.cpp"
    break;

  case 67: /* direct_declarator: LPAREN declarator RPAREN  */
#line 513 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2473 "build/parser.tab.cpp"
    break;

  case 68: /* direct_declarator: direct_declarator LBRACKET assignment_expression RBRACKET  */
#line 516 "src/parser.y"
                                                                {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2483 "build/parser.tab.cpp"
    break;

  case 69: /* direct_declarator: direct_declarator LBRACKET RBRACKET  */
#line 521 "src/parser.y"
                                          {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2492 "build/parser.tab.cpp"
    break;

  case 70: /* $@1: %empty  */
#line 525 "src/parser.y"
                               {
        in_function_params = 1;
    }
#line 2500 "build/parser.tab.cpp"
    break;

  case 71: /* direct_declarator: direct_declarator LPAREN $@1 parameter_list RPAREN  */
#line 527 "src/parser.y"
                            {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        in_function_params = 0;
    }
#line 2511 "build/parser.tab.cpp"
    break;

  case 72: /* direct_declarator: direct_declarator LPAREN RPAREN  */
#line 533 "src/parser.y"
                                      {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        in_function_params = 0;
    }
#line 2521 "build/parser.tab.cpp"
    break;

  case 73: /* parameter_list: parameter_declaration  */
#line 541 "src/parser.y"
                          {
        (yyval.node) = create_node("ParameterList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2530 "build/parser.tab.cpp"
    break;

  case 74: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 545 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2539 "build/parser.tab.cpp"
    break;

  case 75: /* parameter_list: parameter_list COMMA ELLIPSIS  */
#line 549 "src/parser.y"
                                    {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild(create_node("Ellipsis"));
    }
#line 2548 "build/parser.tab.cpp"
    break;

  case 76: /* parameter_declaration: declaration_specifiers declarator  */
#line 556 "src/parser.y"
                                      {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2558 "build/parser.tab.cpp"
    break;

  case 77: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 561 "src/parser.y"
                                                 {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2568 "build/parser.tab.cpp"
    break;

  case 78: /* parameter_declaration: declaration_specifiers  */
#line 566 "src/parser.y"
                             {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2577 "build/parser.tab.cpp"
    break;

  case 79: /* abstract_declarator: pointer  */
#line 573 "src/parser.y"
            {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2586 "build/parser.tab.cpp"
    break;

  case 80: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 577 "src/parser.y"
                                         {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2596 "build/parser.tab.cpp"
    break;

  case 81: /* abstract_declarator: direct_abstract_declarator  */
#line 582 "src/parser.y"
                                 {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2605 "build/parser.tab.cpp"
    break;

  case 82: /* direct_abstract_declarator: LPAREN abstract_declarator RPAREN  */
#line 589 "src/parser.y"
                                      {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2613 "build/parser.tab.cpp"
    break;

  case 83: /* direct_abstract_declarator: LBRACKET RBRACKET  */
#line 592 "src/parser.y"
                        {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
    }
#line 2621 "build/parser.tab.cpp"
    break;

  case 84: /* direct_abstract_declarator: LBRACKET assignment_expression RBRACKET  */
#line 595 "src/parser.y"
                                              {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2630 "build/parser.tab.cpp"
    break;

  case 85: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET RBRACKET  */
#line 599 "src/parser.y"
                                                   {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2639 "build/parser.tab.cpp"
    break;

  case 86: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET assignment_expression RBRACKET  */
#line 603 "src/parser.y"
                                                                         {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2649 "build/parser.tab.cpp"
    break;

  case 87: /* direct_abstract_declarator: LPAREN RPAREN  */
#line 608 "src/parser.y"
                    {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
    }
#line 2657 "build/parser.tab.cpp"
    break;

  case 88: /* direct_abstract_declarator: LPAREN parameter_list RPAREN  */
#line 611 "src/parser.y"
                                   {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2666 "build/parser.tab.cpp"
    break;

  case 89: /* direct_abstract_declarator: direct_abstract_declarator LPAREN RPAREN  */
#line 615 "src/parser.y"
                                               {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2675 "build/parser.tab.cpp"
    break;

  case 90: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_list RPAREN  */
#line 619 "src/parser.y"
                                                              {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2685 "build/parser.tab.cpp"
    break;

  case 91: /* type_name: type_specifier  */
#line 627 "src/parser.y"
                   {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2694 "build/parser.tab.cpp"
    break;

  case 92: /* type_name: type_specifier abstract_declarator  */
#line 631 "src/parser.y"
                                         {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2704 "build/parser.tab.cpp"
    break;

  case 93: /* initializer: assignment_expression  */
#line 639 "src/parser.y"
                          {
        (yyval.node) = create_node("Initializer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2713 "build/parser.tab.cpp"
    break;

  case 94: /* initializer: LBRACE initializer_list RBRACE  */
#line 643 "src/parser.y"
                                     {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2722 "build/parser.tab.cpp"
    break;

  case 95: /* initializer: LBRACE initializer_list COMMA RBRACE  */
#line 647 "src/parser.y"
                                           {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2731 "build/parser.tab.cpp"
    break;

  case 96: /* initializer_list: initializer  */
#line 655 "src/parser.y"
                {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2740 "build/parser.tab.cpp"
    break;

  case 97: /* initializer_list: initializer_list COMMA initializer  */
#line 659 "src/parser.y"
                                         {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2749 "build/parser.tab.cpp"
    break;

  case 98: /* compound_statement: LBRACE RBRACE  */
#line 666 "src/parser.y"
                  {
        (yyval.node) = create_node("CompoundStatement");
    }
#line 2757 "build/parser.tab.cpp"
    break;

  case 99: /* compound_statement: LBRACE block_item_list RBRACE  */
#line 669 "src/parser.y"
                                    {
        (yyval.node) = create_node("CompoundStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2766 "build/parser.tab.cpp"
    break;

  case 100: /* block_item_list: block_item  */
#line 676 "src/parser.y"
               {
        (yyval.node) = create_node("BlockItemList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2775 "build/parser.tab.cpp"
    break;

  case 101: /* block_item_list: block_item_list block_item  */
#line 680 "src/parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2784 "build/parser.tab.cpp"
    break;

  case 102: /* block_item: declaration  */
#line 687 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2793 "build/parser.tab.cpp"
    break;

  case 103: /* block_item: statement  */
#line 691 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2802 "build/parser.tab.cpp"
    break;

  case 104: /* statement: labeled_statement  */
#line 698 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2808 "build/parser.tab.cpp"
    break;

  case 105: /* statement: expression_statement  */
#line 699 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2814 "build/parser.tab.cpp"
    break;

  case 106: /* statement: compound_statement  */
#line 700 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2820 "build/parser.tab.cpp"
    break;

  case 107: /* statement: selection_statement  */
#line 701 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2826 "build/parser.tab.cpp"
    break;

  case 108: /* statement: iteration_statement  */
#line 702 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2832 "build/parser.tab.cpp"
    break;

  case 109: /* statement: jump_statement  */
#line 703 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2838 "build/parser.tab.cpp"
    break;

  case 110: /* labeled_statement: ID COLON statement  */
#line 707 "src/parser.y"
                       {
        (yyval.node) = create_node("LabeledStatement", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2847 "build/parser.tab.cpp"
    break;

  case 111: /* labeled_statement: CASE assignment_expression COLON statement  */
#line 711 "src/parser.y"
                                                 {
        (yyval.node) = create_node("CaseStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2857 "build/parser.tab.cpp"
    break;

  case 112: /* labeled_statement: DEFAULT COLON statement  */
#line 716 "src/parser.y"
                              {
        (yyval.node) = create_node("DefaultStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2866 "build/parser.tab.cpp"
    break;

  case 113: /* expression_statement: expression SEMI  */
#line 723 "src/parser.y"
                    {
        (yyval.node) = create_node("ExpressionStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2875 "build/parser.tab.cpp"
    break;

  case 114: /* expression_statement: SEMI  */
#line 727 "src/parser.y"
           {
        (yyval.node) = create_node("EmptyStatement");
    }
#line 2883 "build/parser.tab.cpp"
    break;

  case 115: /* selection_statement: IF LPAREN expression RPAREN statement  */
#line 733 "src/parser.y"
                                                                {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2893 "build/parser.tab.cpp"
    break;

  case 116: /* selection_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 738 "src/parser.y"
                                                           {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2904 "build/parser.tab.cpp"
    break;

  case 117: /* selection_statement: SWITCH LPAREN expression RPAREN statement  */
#line 744 "src/parser.y"
                                                {
        (yyval.node) = create_node("SwitchStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2914 "build/parser.tab.cpp"
    break;

  case 118: /* iteration_statement: WHILE LPAREN expression RPAREN statement  */
#line 752 "src/parser.y"
                                             {
        (yyval.node) = create_node("WhileStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2924 "build/parser.tab.cpp"
    break;

  case 119: /* iteration_statement: DO statement WHILE LPAREN expression RPAREN SEMI  */
#line 757 "src/parser.y"
                                                       {
        (yyval.node) = create_node("DoWhileStatement");
        (yyval.node)->addChild((yyvsp[-5].node));
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2934 "build/parser.tab.cpp"
    break;

  case 120: /* iteration_statement: FOR LPAREN for_init_statement expression_statement RPAREN statement  */
#line 762 "src/parser.y"
                                                                          {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2945 "build/parser.tab.cpp"
    break;

  case 121: /* iteration_statement: FOR LPAREN for_init_statement expression_statement expression RPAREN statement  */
#line 768 "src/parser.y"
                                                                                     {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2957 "build/parser.tab.cpp"
    break;

  case 122: /* iteration_statement: FOR LPAREN range_based_for RPAREN statement  */
#line 775 "src/parser.y"
                                                  {
        (yyval.node) = create_node("RangeBasedForStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2967 "build/parser.tab.cpp"
    break;

  case 123: /* for_init_statement: expression_statement  */
#line 783 "src/parser.y"
                         {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2976 "build/parser.tab.cpp"
    break;

  case 124: /* for_init_statement: declaration  */
#line 787 "src/parser.y"
                  {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2985 "build/parser.tab.cpp"
    break;

  case 125: /* range_based_for: declaration_specifiers ID COLON expression  */
#line 794 "src/parser.y"
                                               {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2996 "build/parser.tab.cpp"
    break;

  case 126: /* range_based_for: declaration_specifiers BIT_AND ID COLON expression  */
#line 800 "src/parser.y"
                                                         {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild(create_node("Reference"));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3008 "build/parser.tab.cpp"
    break;

  case 127: /* jump_statement: GOTO ID SEMI  */
#line 810 "src/parser.y"
                 {
        (yyval.node) = create_node("GotoStatement", (yyvsp[-1].str));
    }
#line 3016 "build/parser.tab.cpp"
    break;

  case 128: /* jump_statement: CONTINUE SEMI  */
#line 813 "src/parser.y"
                    {
        (yyval.node) = create_node("ContinueStatement");
    }
#line 3024 "build/parser.tab.cpp"
    break;

  case 129: /* jump_statement: BREAK SEMI  */
#line 816 "src/parser.y"
                 {
        (yyval.node) = create_node("BreakStatement");
    }
#line 3032 "build/parser.tab.cpp"
    break;

  case 130: /* jump_statement: RETURN expression SEMI  */
#line 819 "src/parser.y"
                             {
        (yyval.node) = create_node("ReturnStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3041 "build/parser.tab.cpp"
    break;

  case 131: /* jump_statement: RETURN SEMI  */
#line 823 "src/parser.y"
                  {
        (yyval.node) = create_node("ReturnStatement");
    }
#line 3049 "build/parser.tab.cpp"
    break;

  case 132: /* expression: assignment_expression  */
#line 829 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3057 "build/parser.tab.cpp"
    break;

  case 133: /* expression: expression COMMA assignment_expression  */
#line 832 "src/parser.y"
                                             {
        (yyval.node) = create_node("CommaExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3067 "build/parser.tab.cpp"
    break;

  case 134: /* assignment_expression: conditional_expression  */
#line 840 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3075 "build/parser.tab.cpp"
    break;

  case 135: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 843 "src/parser.y"
                                                                 {
        (yyval.node) = create_node("AssignmentExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3085 "build/parser.tab.cpp"
    break;

  case 136: /* assignment_operator: ASSIGN  */
#line 851 "src/parser.y"
           { (yyval.str) = strdup("="); }
#line 3091 "build/parser.tab.cpp"
    break;

  case 137: /* assignment_operator: PLUS_EQ  */
#line 852 "src/parser.y"
              { (yyval.str) = strdup("+="); }
#line 3097 "build/parser.tab.cpp"
    break;

  case 138: /* assignment_operator: MINUS_EQ  */
#line 853 "src/parser.y"
               { (yyval.str) = strdup("-="); }
#line 3103 "build/parser.tab.cpp"
    break;

  case 139: /* assignment_operator: MUL_EQ  */
#line 854 "src/parser.y"
             { (yyval.str) = strdup("*="); }
#line 3109 "build/parser.tab.cpp"
    break;

  case 140: /* assignment_operator: DIV_EQ  */
#line 855 "src/parser.y"
             { (yyval.str) = strdup("/="); }
#line 3115 "build/parser.tab.cpp"
    break;

  case 141: /* assignment_operator: MOD_EQ  */
#line 856 "src/parser.y"
             { (yyval.str) = strdup("%="); }
#line 3121 "build/parser.tab.cpp"
    break;

  case 142: /* assignment_operator: AND_EQ  */
#line 857 "src/parser.y"
             { (yyval.str) = strdup("&="); }
#line 3127 "build/parser.tab.cpp"
    break;

  case 143: /* assignment_operator: OR_EQ  */
#line 858 "src/parser.y"
            { (yyval.str) = strdup("|="); }
#line 3133 "build/parser.tab.cpp"
    break;

  case 144: /* assignment_operator: XOR_EQ  */
#line 859 "src/parser.y"
             { (yyval.str) = strdup("^="); }
#line 3139 "build/parser.tab.cpp"
    break;

  case 145: /* assignment_operator: LSHIFT_EQ  */
#line 860 "src/parser.y"
                { (yyval.str) = strdup("<<="); }
#line 3145 "build/parser.tab.cpp"
    break;

  case 146: /* assignment_operator: RSHIFT_EQ  */
#line 861 "src/parser.y"
                { (yyval.str) = strdup(">>="); }
#line 3151 "build/parser.tab.cpp"
    break;

  case 147: /* conditional_expression: logical_or_expression  */
#line 865 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3159 "build/parser.tab.cpp"
    break;

  case 148: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 868 "src/parser.y"
                                                                             {
        (yyval.node) = create_node("ConditionalExpression");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3170 "build/parser.tab.cpp"
    break;

  case 149: /* logical_or_expression: logical_and_expression  */
#line 877 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3178 "build/parser.tab.cpp"
    break;

  case 150: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 880 "src/parser.y"
                                                      {
        (yyval.node) = create_node("LogicalOrExpression", "||");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3188 "build/parser.tab.cpp"
    break;

  case 151: /* logical_and_expression: inclusive_or_expression  */
#line 888 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3196 "build/parser.tab.cpp"
    break;

  case 152: /* logical_and_expression: logical_and_expression AND inclusive_or_expression  */
#line 891 "src/parser.y"
                                                         {
        (yyval.node) = create_node("LogicalAndExpression","&&");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3206 "build/parser.tab.cpp"
    break;

  case 153: /* inclusive_or_expression: exclusive_or_expression  */
#line 899 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3214 "build/parser.tab.cpp"
    break;

  case 154: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 902 "src/parser.y"
                                                             {
        (yyval.node) = create_node("InclusiveOrExpression","|");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3224 "build/parser.tab.cpp"
    break;

  case 155: /* exclusive_or_expression: and_expression  */
#line 910 "src/parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3232 "build/parser.tab.cpp"
    break;

  case 156: /* exclusive_or_expression: exclusive_or_expression BIT_XOR and_expression  */
#line 913 "src/parser.y"
                                                     {
        (yyval.node) = create_node("ExclusiveOrExpression","^");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3242 "build/parser.tab.cpp"
    break;

  case 157: /* and_expression: equality_expression  */
#line 921 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3250 "build/parser.tab.cpp"
    break;

  case 158: /* and_expression: and_expression BIT_AND equality_expression  */
#line 924 "src/parser.y"
                                                 {
        (yyval.node) = create_node("AndExpression","&");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3260 "build/parser.tab.cpp"
    break;

  case 159: /* equality_expression: relational_expression  */
#line 932 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3268 "build/parser.tab.cpp"
    break;

  case 160: /* equality_expression: equality_expression EQ relational_expression  */
#line 935 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "==");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3278 "build/parser.tab.cpp"
    break;

  case 161: /* equality_expression: equality_expression NE relational_expression  */
#line 940 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "!=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3288 "build/parser.tab.cpp"
    break;

  case 162: /* relational_expression: shift_expression  */
#line 948 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3296 "build/parser.tab.cpp"
    break;

  case 163: /* relational_expression: relational_expression LT shift_expression  */
#line 951 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3306 "build/parser.tab.cpp"
    break;

  case 164: /* relational_expression: relational_expression GT shift_expression  */
#line 956 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3316 "build/parser.tab.cpp"
    break;

  case 165: /* relational_expression: relational_expression LE shift_expression  */
#line 961 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3326 "build/parser.tab.cpp"
    break;

  case 166: /* relational_expression: relational_expression GE shift_expression  */
#line 966 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3336 "build/parser.tab.cpp"
    break;

  case 167: /* shift_expression: additive_expression  */
#line 974 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3344 "build/parser.tab.cpp"
    break;

  case 168: /* shift_expression: shift_expression LSHIFT additive_expression  */
#line 977 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", "<<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3354 "build/parser.tab.cpp"
    break;

  case 169: /* shift_expression: shift_expression RSHIFT additive_expression  */
#line 982 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", ">>");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3364 "build/parser.tab.cpp"
    break;

  case 170: /* additive_expression: multiplicative_expression  */
#line 990 "src/parser.y"
                              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3372 "build/parser.tab.cpp"
    break;

  case 171: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 993 "src/parser.y"
                                                         {
        (yyval.node) = create_node("AdditiveExpression", "+");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3382 "build/parser.tab.cpp"
    break;

  case 172: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 998 "src/parser.y"
                                                          {
        (yyval.node) = create_node("AdditiveExpression", "-");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3392 "build/parser.tab.cpp"
    break;

  case 173: /* multiplicative_expression: cast_expression  */
#line 1006 "src/parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3400 "build/parser.tab.cpp"
    break;

  case 174: /* multiplicative_expression: multiplicative_expression MUL cast_expression  */
#line 1009 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "*");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3410 "build/parser.tab.cpp"
    break;

  case 175: /* multiplicative_expression: multiplicative_expression DIV cast_expression  */
#line 1014 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "/");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3420 "build/parser.tab.cpp"
    break;

  case 176: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 1019 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "%");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3430 "build/parser.tab.cpp"
    break;

  case 177: /* cast_expression: unary_expression  */
#line 1027 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3438 "build/parser.tab.cpp"
    break;

  case 178: /* cast_expression: LPAREN type_name RPAREN cast_expression  */
#line 1030 "src/parser.y"
                                              {
        (yyval.node) = create_node("CastExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3448 "build/parser.tab.cpp"
    break;

  case 179: /* unary_expression: postfix_expression  */
#line 1038 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3456 "build/parser.tab.cpp"
    break;

  case 180: /* unary_expression: INC unary_expression  */
#line 1041 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "++");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3465 "build/parser.tab.cpp"
    break;

  case 181: /* unary_expression: DEC unary_expression  */
#line 1045 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "--");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3474 "build/parser.tab.cpp"
    break;

  case 182: /* unary_expression: unary_operator cast_expression  */
#line 1049 "src/parser.y"
                                     {
        (yyval.node) = create_node("UnaryExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3483 "build/parser.tab.cpp"
    break;

  case 183: /* unary_expression: SIZEOF unary_expression  */
#line 1053 "src/parser.y"
                              {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3492 "build/parser.tab.cpp"
    break;

  case 184: /* unary_expression: SIZEOF LPAREN type_name RPAREN  */
#line 1057 "src/parser.y"
                                     {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3501 "build/parser.tab.cpp"
    break;

  case 185: /* unary_operator: BIT_AND  */
#line 1064 "src/parser.y"
            { (yyval.str) = strdup("&"); }
#line 3507 "build/parser.tab.cpp"
    break;

  case 186: /* unary_operator: MUL  */
#line 1065 "src/parser.y"
          { (yyval.str) = strdup("*"); }
#line 3513 "build/parser.tab.cpp"
    break;

  case 187: /* unary_operator: PLUS  */
#line 1066 "src/parser.y"
           { (yyval.str) = strdup("+"); }
#line 3519 "build/parser.tab.cpp"
    break;

  case 188: /* unary_operator: MINUS  */
#line 1067 "src/parser.y"
            { (yyval.str) = strdup("-"); }
#line 3525 "build/parser.tab.cpp"
    break;

  case 189: /* unary_operator: BIT_NOT  */
#line 1068 "src/parser.y"
              { (yyval.str) = strdup("~"); }
#line 3531 "build/parser.tab.cpp"
    break;

  case 190: /* unary_operator: NOT  */
#line 1069 "src/parser.y"
          { (yyval.str) = strdup("!"); }
#line 3537 "build/parser.tab.cpp"
    break;

  case 191: /* postfix_expression: primary_expression  */
#line 1073 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3545 "build/parser.tab.cpp"
    break;

  case 192: /* postfix_expression: postfix_expression LBRACKET expression RBRACKET  */
#line 1076 "src/parser.y"
                                                      {
        (yyval.node) = create_node("ArraySubscript");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3555 "build/parser.tab.cpp"
    break;

  case 193: /* postfix_expression: postfix_expression LPAREN argument_expression_list RPAREN  */
#line 1081 "src/parser.y"
                                                                {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3565 "build/parser.tab.cpp"
    break;

  case 194: /* postfix_expression: postfix_expression LPAREN RPAREN  */
#line 1086 "src/parser.y"
                                       {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 3574 "build/parser.tab.cpp"
    break;

  case 195: /* postfix_expression: postfix_expression DOT ID  */
#line 1090 "src/parser.y"
                                {
        (yyval.node) = create_node("MemberAccess", ".");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3584 "build/parser.tab.cpp"
    break;

  case 196: /* postfix_expression: postfix_expression ARROW ID  */
#line 1095 "src/parser.y"
                                  {
        (yyval.node) = create_node("MemberAccess", "->");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3594 "build/parser.tab.cpp"
    break;

  case 197: /* postfix_expression: postfix_expression INC  */
#line 1100 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "++");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3603 "build/parser.tab.cpp"
    break;

  case 198: /* postfix_expression: postfix_expression DEC  */
#line 1104 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "--");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3612 "build/parser.tab.cpp"
    break;

  case 199: /* primary_expression: ID  */
#line 1111 "src/parser.y"
       {
        (yyval.node) = create_node("Identifier", (yyvsp[0].str));
    }
#line 3620 "build/parser.tab.cpp"
    break;

  case 200: /* primary_expression: constant  */
#line 1114 "src/parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3628 "build/parser.tab.cpp"
    break;

  case 201: /* primary_expression: string_literal  */
#line 1117 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3636 "build/parser.tab.cpp"
    break;

  case 202: /* primary_expression: LPAREN expression RPAREN  */
#line 1120 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3644 "build/parser.tab.cpp"
    break;

  case 203: /* string_literal: STRING_LIT  */
#line 1126 "src/parser.y"
               {
        (yyval.node) = create_node("StringLiteral", (yyvsp[0].str));
    }
#line 3652 "build/parser.tab.cpp"
    break;

  case 204: /* string_literal: string_literal STRING_LIT  */
#line 1129 "src/parser.y"
                                {
        (yyval.node) = create_node("StringLiteral");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild(create_node("StringLiteral", (yyvsp[0].str)));
    }
#line 3662 "build/parser.tab.cpp"
    break;

  case 205: /* argument_expression_list: assignment_expression  */
#line 1137 "src/parser.y"
                          {
        (yyval.node) = create_node("ArgumentList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3671 "build/parser.tab.cpp"
    break;

  case 206: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 1141 "src/parser.y"
                                                           {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3680 "build/parser.tab.cpp"
    break;

  case 207: /* constant: NUM  */
#line 1148 "src/parser.y"
        { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3686 "build/parser.tab.cpp"
    break;

  case 208: /* constant: FLOAT_LIT  */
#line 1149 "src/parser.y"
                { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3692 "build/parser.tab.cpp"
    break;

  case 209: /* constant: CHAR_LIT  */
#line 1150 "src/parser.y"
               { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3698 "build/parser.tab.cpp"
    break;

  case 210: /* constant: TRUE  */
#line 1151 "src/parser.y"
           { (yyval.node) = create_node("Constant", "true"); }
#line 3704 "build/parser.tab.cpp"
    break;

  case 211: /* constant: FALSE  */
#line 1152 "src/parser.y"
            { (yyval.node) = create_node("Constant", "false"); }
#line 3710 "build/parser.tab.cpp"
    break;

  case 212: /* constant: NULL_TOKEN  */
#line 1153 "src/parser.y"
                 { (yyval.node) = create_node("Constant", "NULL"); }
#line 3716 "build/parser.tab.cpp"
    break;

  case 213: /* constant: NULLPTR  */
#line 1154 "src/parser.y"
              { (yyval.node) = create_node("Constant", "nullptr"); }
#line 3722 "build/parser.tab.cpp"
    break;


#line 3726 "build/parser.tab.cpp"

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

#line 1157 "src/parser.y"


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
        has_semantic_errors = false;  // ✅ Reset flag
        
        SemanticAnalyzer analyzer(symbol_table);
        analyzer.analyze(root);
        
        // Print symbol table
        symbol_table->print_table();
        
        // ✅ CHECK THE FLAG
        if (has_semantic_errors) {
            printf("\n");
            printf("==================================================\n");
            printf("❌ COMPILATION FAILED\n");
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
        
        printf("\n✅ Semantic analysis passed with no errors.\n");
        
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
            printf("✅ COMPILATION SUCCESSFUL\n");
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
