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
    return new ASTNode(name, lexeme);
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

/* Symbol table declarations (for future use) */
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER,
    SYMBOL_STRUCT,
    SYMBOL_ENUM,
    SYMBOL_TYPEDEF
} SymbolType;

char current_type[64] = "int";
int in_function_params = 0;
int in_typedef_declaration = 0;


#line 150 "build/parser.tab.cpp"

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
  YYSYMBOL_CLASS = 35,                     /* CLASS  */
  YYSYMBOL_PRIVATE = 36,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 37,                 /* PROTECTED  */
  YYSYMBOL_PUBLIC = 38,                    /* PUBLIC  */
  YYSYMBOL_VIRTUAL = 39,                   /* VIRTUAL  */
  YYSYMBOL_FRIEND = 40,                    /* FRIEND  */
  YYSYMBOL_INLINE = 41,                    /* INLINE  */
  YYSYMBOL_OPERATOR = 42,                  /* OPERATOR  */
  YYSYMBOL_OVERLOAD = 43,                  /* OVERLOAD  */
  YYSYMBOL_TEMPLATE = 44,                  /* TEMPLATE  */
  YYSYMBOL_THIS = 45,                      /* THIS  */
  YYSYMBOL_NEW = 46,                       /* NEW  */
  YYSYMBOL_DELETE = 47,                    /* DELETE  */
  YYSYMBOL_NAMESPACE = 48,                 /* NAMESPACE  */
  YYSYMBOL_USING = 49,                     /* USING  */
  YYSYMBOL_TRY = 50,                       /* TRY  */
  YYSYMBOL_CATCH = 51,                     /* CATCH  */
  YYSYMBOL_THROW = 52,                     /* THROW  */
  YYSYMBOL_BOOL = 53,                      /* BOOL  */
  YYSYMBOL_TRUE = 54,                      /* TRUE  */
  YYSYMBOL_FALSE = 55,                     /* FALSE  */
  YYSYMBOL_TYPEDEF_NAME = 56,              /* TYPEDEF_NAME  */
  YYSYMBOL_ID = 57,                        /* ID  */
  YYSYMBOL_NUM = 58,                       /* NUM  */
  YYSYMBOL_FLOAT_LIT = 59,                 /* FLOAT_LIT  */
  YYSYMBOL_CHAR_LIT = 60,                  /* CHAR_LIT  */
  YYSYMBOL_STRING_LIT = 61,                /* STRING_LIT  */
  YYSYMBOL_PLUS = 62,                      /* PLUS  */
  YYSYMBOL_MINUS = 63,                     /* MINUS  */
  YYSYMBOL_MUL = 64,                       /* MUL  */
  YYSYMBOL_DIV = 65,                       /* DIV  */
  YYSYMBOL_MOD = 66,                       /* MOD  */
  YYSYMBOL_ASSIGN = 67,                    /* ASSIGN  */
  YYSYMBOL_PLUS_EQ = 68,                   /* PLUS_EQ  */
  YYSYMBOL_MINUS_EQ = 69,                  /* MINUS_EQ  */
  YYSYMBOL_MUL_EQ = 70,                    /* MUL_EQ  */
  YYSYMBOL_DIV_EQ = 71,                    /* DIV_EQ  */
  YYSYMBOL_MOD_EQ = 72,                    /* MOD_EQ  */
  YYSYMBOL_INC = 73,                       /* INC  */
  YYSYMBOL_DEC = 74,                       /* DEC  */
  YYSYMBOL_EQ = 75,                        /* EQ  */
  YYSYMBOL_NE = 76,                        /* NE  */
  YYSYMBOL_LT = 77,                        /* LT  */
  YYSYMBOL_GT = 78,                        /* GT  */
  YYSYMBOL_LE = 79,                        /* LE  */
  YYSYMBOL_GE = 80,                        /* GE  */
  YYSYMBOL_AND = 81,                       /* AND  */
  YYSYMBOL_OR = 82,                        /* OR  */
  YYSYMBOL_NOT = 83,                       /* NOT  */
  YYSYMBOL_BIT_AND = 84,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 85,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 86,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 87,                   /* BIT_NOT  */
  YYSYMBOL_LSHIFT = 88,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 89,                    /* RSHIFT  */
  YYSYMBOL_AND_EQ = 90,                    /* AND_EQ  */
  YYSYMBOL_OR_EQ = 91,                     /* OR_EQ  */
  YYSYMBOL_XOR_EQ = 92,                    /* XOR_EQ  */
  YYSYMBOL_LSHIFT_EQ = 93,                 /* LSHIFT_EQ  */
  YYSYMBOL_RSHIFT_EQ = 94,                 /* RSHIFT_EQ  */
  YYSYMBOL_ARROW = 95,                     /* ARROW  */
  YYSYMBOL_DOT = 96,                       /* DOT  */
  YYSYMBOL_SCOPE = 97,                     /* SCOPE  */
  YYSYMBOL_SEMI = 98,                      /* SEMI  */
  YYSYMBOL_COMMA = 99,                     /* COMMA  */
  YYSYMBOL_QUESTION = 100,                 /* QUESTION  */
  YYSYMBOL_COLON = 101,                    /* COLON  */
  YYSYMBOL_LPAREN = 102,                   /* LPAREN  */
  YYSYMBOL_RPAREN = 103,                   /* RPAREN  */
  YYSYMBOL_LBRACE = 104,                   /* LBRACE  */
  YYSYMBOL_RBRACE = 105,                   /* RBRACE  */
  YYSYMBOL_LBRACKET = 106,                 /* LBRACKET  */
  YYSYMBOL_RBRACKET = 107,                 /* RBRACKET  */
  YYSYMBOL_ELLIPSIS = 108,                 /* ELLIPSIS  */
  YYSYMBOL_PREP = 109,                     /* PREP  */
  YYSYMBOL_NEWLINE = 110,                  /* NEWLINE  */
  YYSYMBOL_END = 111,                      /* END  */
  YYSYMBOL_ERROR = 112,                    /* ERROR  */
  YYSYMBOL_DESTRUCTOR = 113,               /* DESTRUCTOR  */
  YYSYMBOL_UMINUS = 114,                   /* UMINUS  */
  YYSYMBOL_UPLUS = 115,                    /* UPLUS  */
  YYSYMBOL_IF_WITHOUT_ELSE = 116,          /* IF_WITHOUT_ELSE  */
  YYSYMBOL_YYACCEPT = 117,                 /* $accept  */
  YYSYMBOL_program = 118,                  /* program  */
  YYSYMBOL_translation_unit = 119,         /* translation_unit  */
  YYSYMBOL_external_declaration = 120,     /* external_declaration  */
  YYSYMBOL_preprocessor_directive = 121,   /* preprocessor_directive  */
  YYSYMBOL_function_definition = 122,      /* function_definition  */
  YYSYMBOL_declaration = 123,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 124,   /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 125,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 126,           /* type_specifier  */
  YYSYMBOL_type_keyword = 127,             /* type_keyword  */
  YYSYMBOL_struct_or_union_specifier = 128, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 129,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 130,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 131,       /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 132,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 133,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 134,           /* enum_specifier  */
  YYSYMBOL_class_specifier = 135,          /* class_specifier  */
  YYSYMBOL_class_declaration_list = 136,   /* class_declaration_list  */
  YYSYMBOL_class_declaration = 137,        /* class_declaration  */
  YYSYMBOL_access_specifier = 138,         /* access_specifier  */
  YYSYMBOL_member_declaration = 139,       /* member_declaration  */
  YYSYMBOL_member_declarator_list = 140,   /* member_declarator_list  */
  YYSYMBOL_member_declarator = 141,        /* member_declarator  */
  YYSYMBOL_enumerator_list = 142,          /* enumerator_list  */
  YYSYMBOL_enumerator = 143,               /* enumerator  */
  YYSYMBOL_init_declarator_list = 144,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 145,          /* init_declarator  */
  YYSYMBOL_declarator = 146,               /* declarator  */
  YYSYMBOL_pointer = 147,                  /* pointer  */
  YYSYMBOL_direct_declarator = 148,        /* direct_declarator  */
  YYSYMBOL_parameter_list = 149,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 150,    /* parameter_declaration  */
  YYSYMBOL_abstract_declarator = 151,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 152, /* direct_abstract_declarator  */
  YYSYMBOL_type_name = 153,                /* type_name  */
  YYSYMBOL_initializer = 154,              /* initializer  */
  YYSYMBOL_initializer_list = 155,         /* initializer_list  */
  YYSYMBOL_compound_statement = 156,       /* compound_statement  */
  YYSYMBOL_block_item_list = 157,          /* block_item_list  */
  YYSYMBOL_block_item = 158,               /* block_item  */
  YYSYMBOL_statement = 159,                /* statement  */
  YYSYMBOL_labeled_statement = 160,        /* labeled_statement  */
  YYSYMBOL_expression_statement = 161,     /* expression_statement  */
  YYSYMBOL_selection_statement = 162,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 163,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 164,       /* for_init_statement  */
  YYSYMBOL_range_based_for = 165,          /* range_based_for  */
  YYSYMBOL_jump_statement = 166,           /* jump_statement  */
  YYSYMBOL_expression = 167,               /* expression  */
  YYSYMBOL_assignment_expression = 168,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 169,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 170,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 171,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 172,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 173,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 174,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 175,           /* and_expression  */
  YYSYMBOL_equality_expression = 176,      /* equality_expression  */
  YYSYMBOL_relational_expression = 177,    /* relational_expression  */
  YYSYMBOL_shift_expression = 178,         /* shift_expression  */
  YYSYMBOL_additive_expression = 179,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 180, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 181,          /* cast_expression  */
  YYSYMBOL_unary_expression = 182,         /* unary_expression  */
  YYSYMBOL_unary_operator = 183,           /* unary_operator  */
  YYSYMBOL_postfix_expression = 184,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 185,       /* primary_expression  */
  YYSYMBOL_string_literal = 186,           /* string_literal  */
  YYSYMBOL_argument_expression_list = 187, /* argument_expression_list  */
  YYSYMBOL_constant = 188                  /* constant  */
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
#define YYLAST   1813

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  223
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  372

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   371


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
     115,   116
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   175,   180,   187,   190,   193,   199,   203,
     210,   219,   225,   233,   237,   242,   246,   254,   258,   259,
     260,   261,   265,   269,   270,   271,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   288,   294,   299,   307,
     308,   312,   316,   323,   331,   335,   342,   346,   351,   355,
     363,   368,   372,   379,   383,   390,   393,   399,   402,   405,
     411,   416,   420,   427,   431,   438,   441,   449,   453,   460,
     463,   470,   474,   481,   485,   493,   498,   504,   507,   514,
     517,   520,   524,   529,   533,   541,   545,   549,   556,   561,
     566,   573,   577,   582,   589,   592,   595,   599,   603,   608,
     611,   615,   619,   627,   631,   639,   643,   647,   654,   658,
     665,   668,   675,   679,   686,   690,   697,   698,   699,   700,
     701,   702,   706,   710,   715,   722,   726,   732,   737,   743,
     751,   756,   761,   767,   774,   782,   786,   793,   799,   809,
     812,   815,   818,   822,   828,   831,   839,   842,   850,   851,
     852,   853,   854,   855,   856,   857,   858,   859,   860,   864,
     867,   876,   879,   887,   890,   898,   901,   909,   912,   920,
     923,   931,   934,   939,   947,   950,   955,   960,   965,   973,
     976,   981,   989,   992,   997,  1005,  1008,  1013,  1018,  1026,
    1029,  1037,  1040,  1044,  1048,  1052,  1056,  1063,  1064,  1065,
    1066,  1067,  1068,  1072,  1075,  1080,  1085,  1089,  1094,  1099,
    1103,  1110,  1113,  1116,  1119,  1125,  1128,  1136,  1140,  1147,
    1148,  1149,  1150,  1151
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
  "CLASS", "PRIVATE", "PROTECTED", "PUBLIC", "VIRTUAL", "FRIEND", "INLINE",
  "OPERATOR", "OVERLOAD", "TEMPLATE", "THIS", "NEW", "DELETE", "NAMESPACE",
  "USING", "TRY", "CATCH", "THROW", "BOOL", "TRUE", "FALSE",
  "TYPEDEF_NAME", "ID", "NUM", "FLOAT_LIT", "CHAR_LIT", "STRING_LIT",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "ASSIGN", "PLUS_EQ", "MINUS_EQ",
  "MUL_EQ", "DIV_EQ", "MOD_EQ", "INC", "DEC", "EQ", "NE", "LT", "GT", "LE",
  "GE", "AND", "OR", "NOT", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT",
  "LSHIFT", "RSHIFT", "AND_EQ", "OR_EQ", "XOR_EQ", "LSHIFT_EQ",
  "RSHIFT_EQ", "ARROW", "DOT", "SCOPE", "SEMI", "COMMA", "QUESTION",
  "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "ELLIPSIS", "PREP", "NEWLINE", "END", "ERROR", "DESTRUCTOR", "UMINUS",
  "UPLUS", "IF_WITHOUT_ELSE", "$accept", "program", "translation_unit",
  "external_declaration", "preprocessor_directive", "function_definition",
  "declaration", "declaration_specifiers", "storage_class_specifier",
  "type_specifier", "type_keyword", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "enum_specifier",
  "class_specifier", "class_declaration_list", "class_declaration",
  "access_specifier", "member_declaration", "member_declarator_list",
  "member_declarator", "enumerator_list", "enumerator",
  "init_declarator_list", "init_declarator", "declarator", "pointer",
  "direct_declarator", "parameter_list", "parameter_declaration",
  "abstract_declarator", "direct_abstract_declarator", "type_name",
  "initializer", "initializer_list", "compound_statement",
  "block_item_list", "block_item", "statement", "labeled_statement",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_init_statement", "range_based_for", "jump_statement", "expression",
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

#define YYPACT_NINF (-219)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     299,  -219,  -219,  -219,   -40,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,   -34,  -219,
    -219,   -46,   -16,  -219,    33,   299,  -219,  -219,  -219,  -219,
     -13,  1760,  1760,  -219,  -219,   -33,  -219,  -219,   -64,   -15,
     -26,   -58,    -8,   -37,  1055,  -219,   -48,  -219,  -219,  -219,
      68,  -219,     7,  -219,  -219,     3,   182,   509,  -219,   -26,
     907,  1176,    -8,    12,    15,  -219,  1055,  -219,  -219,  -219,
    -219,   -10,   709,  -219,    17,  -219,  -219,  -219,   -16,  1381,
    -219,   182,   -16,  1083,  -219,    32,  1594,    43,    51,   821,
     -45,    56,    57,  1513,  1625,    62,    75,  -219,  -219,    85,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  1675,  1675,  -219,
    -219,  -219,  -219,  1145,  -219,  -219,   -13,  -219,   612,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,   105,  -219,  -219,   -55,
     110,    50,   114,   123,   135,   141,   127,   170,   165,  -219,
      78,  1594,    20,  -219,   163,  -219,  -219,   -44,    34,  -219,
    -219,  -219,   133,    22,  1594,    -8,  -219,   764,  -219,   138,
    -219,     8,  -219,  -219,  -219,  -219,   167,  1381,  -219,  -219,
    1110,   140,  -219,  -219,  -219,  -219,  -219,   152,  -219,   821,
     221,   969,   159,  1594,  -219,   149,  1145,  -219,  1594,  1594,
     821,  1594,  -219,  -219,   -50,   161,    37,  -219,  -219,  -219,
    1594,  1594,  1594,  1594,  1594,  1594,  1594,  1594,  1594,  1594,
    1594,  1594,  1594,  1594,  1594,  1594,  1594,  1594,  1594,  1594,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  1594,  -219,  -219,  -219,  -219,   205,   209,  1432,  1594,
    -219,   400,  1227,  -219,   -41,  -219,    36,   354,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,   -16,  1594,  -219,    26,  -219,
    -219,   -16,   821,  -219,   168,  -219,   -25,  -219,  1544,   166,
    -219,    52,  -219,   169,    54,    55,  -219,   452,    59,  -219,
    1594,  -219,  -219,   110,    -3,    50,   114,   123,   135,   141,
     141,   127,   127,   127,   127,   170,   170,   165,   165,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,    79,    10,  -219,
      80,   172,  -219,   164,    36,   938,  1278,  -219,  -219,  -219,
     206,  -219,  1329,  -219,  -219,  -219,  1594,   175,   225,  1463,
     821,   821,  -219,   821,   821,  -219,  1594,  1594,  -219,  -219,
    -219,  -219,  -219,  -219,    81,  -219,   177,  -219,  -219,    93,
    1594,   202,   821,    95,  -219,   292,  -219,  -219,  -219,  -219,
    -219,  -219,   208,   210,  1594,  -219,   821,   821,  -219,   210,
    -219,  -219
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    21,    27,    32,     0,    19,    31,    29,    30,    20,
      28,    33,    18,    39,    17,    40,    34,    26,     0,    35,
      79,    77,     0,     8,     0,     2,     3,     7,     5,     6,
       0,    13,    15,    22,    23,     0,    24,    25,     0,     0,
      76,    49,     0,    52,     0,    78,     0,     1,     4,    12,
       0,    71,    73,    14,    16,    38,     0,     0,    10,    75,
       0,     0,     0,    69,     0,    67,     0,    58,    59,    57,
      62,     0,     0,    53,     0,    56,    80,    11,     0,     0,
       9,     0,     0,     0,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   222,   223,   211,
     219,   220,   221,   215,   199,   200,   198,     0,     0,   202,
     197,   201,   126,     0,   110,   114,     0,   118,     0,   112,
     115,   116,   117,   119,   120,   121,     0,   144,   146,   159,
     161,   163,   165,   167,   169,   171,   174,   179,   182,   185,
     189,     0,   191,   203,   213,   212,    83,    90,     0,    85,
     211,    81,     0,     0,     0,     0,    48,     0,    61,     0,
      63,    65,    51,    54,    55,    72,    73,     0,    74,   105,
       0,     0,    44,    46,    37,    42,   141,     0,   140,     0,
       0,     0,     0,     0,   143,     0,     0,   195,     0,     0,
       0,     0,   192,   193,   103,     0,     0,   111,   113,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,     0,   194,   189,   209,   210,     0,     0,     0,     0,
     216,     0,     0,    88,    91,    89,    93,     0,    84,    82,
      47,    70,    68,    50,    60,     0,     0,   108,     0,    36,
      43,     0,     0,   124,     0,   136,     0,   135,     0,     0,
     139,     0,   142,     0,     0,     0,   122,     0,    91,   104,
       0,   214,   145,   162,     0,   164,   166,   168,   170,   172,
     173,   175,   176,   177,   178,   180,   181,   183,   184,   186,
     187,   188,   147,   208,   207,   206,   217,     0,     0,    99,
       0,     0,    95,     0,    92,     0,     0,    87,    86,    64,
      65,    66,     0,   106,    45,   123,     0,    79,     0,     0,
       0,     0,   196,     0,     0,   190,     0,     0,   205,   204,
     100,    94,    96,   101,     0,    97,     0,   107,   109,     0,
       0,     0,     0,     0,   134,   127,   129,   130,   160,   218,
     102,    98,     0,   137,     0,   132,     0,     0,   131,   138,
     133,   128
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -219,  -219,  -219,   282,  -219,    28,   -49,     6,  -219,   -47,
    -219,  -219,  -219,   227,   -71,  -219,    60,  -219,  -219,   245,
     -53,  -219,  -219,  -219,    61,   253,   162,  -219,   246,    13,
     -19,   -36,   -59,    86,  -126,  -218,   146,  -160,  -219,   -27,
    -219,   217,   -89,  -219,  -166,  -219,  -219,  -219,  -219,  -219,
     -83,   -57,  -219,    -9,  -219,   136,   137,   132,   134,   139,
      42,    16,    38,    45,  -136,    82,  -219,  -219,  -219,  -219,
    -219,  -219
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    24,    25,    26,    27,    70,    29,   147,    31,    32,
      33,    34,    35,    83,    84,   171,   172,    36,    37,    72,
      73,    74,    75,   159,   160,    64,    65,    50,    51,    38,
      39,    40,   310,   149,   311,   246,   195,   168,   258,   117,
     118,   119,   120,   121,   122,   123,   124,   268,   269,   125,
     126,   127,   231,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     307,   145
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     180,   148,    45,    59,   152,   232,    30,   257,   115,    82,
     185,    58,   175,    20,    21,   267,    20,    41,    21,   163,
      21,   245,   169,    43,    55,    80,   314,   201,    28,   177,
     196,    30,   327,    47,    82,    46,    82,    53,    54,    21,
      57,    20,    20,    52,    20,   202,    62,    20,    21,    63,
      71,    21,   277,    28,    21,    76,   242,   181,   241,   328,
     314,   241,   242,   116,    42,   242,   194,    66,   279,   115,
      44,    56,    71,    49,    79,   256,    60,    22,    71,   154,
      61,   299,   300,   301,   161,    49,    22,    22,   158,    22,
     263,   166,    22,   234,   235,   173,   200,   251,   336,   175,
     271,   276,   329,   196,   163,   274,   275,    81,   196,   200,
     169,    57,    57,   182,   155,   236,   237,   339,   164,   284,
     156,   155,   238,    82,   116,   322,   239,   250,   244,   166,
     176,   323,   265,   247,    80,   204,   200,   248,   315,   194,
     281,   178,   316,   282,   335,   220,   221,   222,   223,   224,
     225,   200,   179,   200,   200,   331,   308,   333,   334,   183,
     243,   277,   348,    71,   188,   242,    77,    78,   226,   227,
     228,   229,   230,   325,   302,   278,   187,   189,   337,   247,
     247,   306,   338,   340,   360,   313,   190,   266,     2,   192,
     193,   203,   200,     3,   200,     4,   362,     6,   366,   321,
     205,     7,     8,   199,   200,    10,    11,   206,    59,    13,
     207,   208,    15,    16,    17,   213,   214,    18,   209,   210,
     211,   212,   244,   233,   240,   291,   292,   293,   294,   217,
     218,   219,   215,   216,    79,    19,   254,   255,   260,   261,
     249,   354,   355,   349,   356,   357,   353,   272,   200,   289,
     290,   295,   296,   262,    46,   264,   344,   270,   278,   346,
     297,   298,   303,   365,   280,   169,   304,   363,   320,   330,
     326,   342,   332,   256,   173,   341,   350,   370,   371,   166,
     359,   369,   351,   233,   361,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,     1,   364,   367,     2,   368,    48,   170,   200,
       3,   157,     4,     5,     6,   153,   319,   252,     7,     8,
       9,   324,    10,    11,   165,    12,    13,   358,    14,    15,
      16,    17,   273,   318,    18,   198,   286,   283,     0,   287,
     285,     0,     0,     0,     0,   288,     0,     0,     0,     0,
       0,     0,    19,     0,     0,     0,    20,     1,     0,     0,
       2,     0,   233,    21,     0,     3,     0,     4,     5,     6,
       0,     0,     0,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,    14,    15,    16,    17,     0,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     1,     0,     0,     2,    19,    23,     0,
       0,     3,     0,     4,     5,     6,     0,     0,   233,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,    14,
      15,    16,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     1,     0,    20,     2,     0,
       0,     0,   317,     3,    21,     4,     5,     6,     0,     0,
       0,     7,     8,     9,     0,    10,    11,     0,    12,    13,
       0,    14,    15,    16,    17,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   241,   309,     0,    19,   242,     0,     0,     0,
       0,     0,     1,    85,    86,     2,    21,    87,    88,    89,
       3,     0,     4,     5,     6,    90,    91,    92,     7,     8,
       9,    93,    10,    11,    94,    12,    13,    95,    14,    15,
      16,    17,     0,    96,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,   309,     0,     0,   242,     0,
       0,     0,    19,    97,    98,     0,    99,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,     0,
       0,     0,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
       0,   113,     0,    57,   114,     1,    85,    86,     2,     0,
      87,    88,    89,     3,     0,     4,     5,     6,    90,    91,
      92,     7,     8,     9,    93,    10,    11,    94,    12,    13,
      95,    14,    15,    16,    17,     0,    96,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,    97,    98,     0,    99,
     100,   101,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,   109,   110,     0,     0,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,     0,     1,     0,   113,     2,    57,   197,     0,     0,
       3,     0,     4,     5,     6,     0,     0,     0,     7,     8,
       9,     0,    10,    11,     0,    12,    13,     0,    14,    15,
      16,    17,     0,     0,    18,    67,    68,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,     0,     0,     0,    20,     1,     0,     0,
       2,     0,     0,    21,     0,     3,     0,     4,     5,     6,
       0,     0,     0,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,    14,    15,    16,    17,     0,     0,    18,
      67,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,   162,     0,     0,    19,     0,     0,
       0,    20,     0,     0,     0,    85,    86,     0,    21,    87,
      88,    89,     0,     0,     0,     0,     0,    90,    91,    92,
       0,     0,     0,    93,     0,     0,    94,     0,     0,    95,
       0,     0,     0,     0,     0,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,     0,   253,
       0,     0,     0,     0,     0,    97,    98,     0,    99,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,   107,   108,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   110,     0,     0,   111,     0,
       1,     0,     0,     2,     0,     0,     0,     0,     3,   112,
       4,     5,     6,   113,     0,    57,     7,     8,     9,     0,
      10,    11,     0,    12,    13,     0,    14,    15,    16,    17,
       0,     1,    18,     0,     2,     0,     0,     0,     0,     3,
       0,     4,     5,     6,     0,     0,     0,     7,     8,     9,
      19,    10,    11,     0,    12,    13,     0,    14,    15,    16,
      17,     0,     1,    18,     0,     2,     0,     0,     0,     0,
       3,     0,     4,     5,     6,     0,     0,     0,     7,     8,
       9,    19,    10,    11,    94,    12,    13,     0,    14,    15,
      16,    17,     0,     0,    18,     0,     0,     0,     0,     0,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,    97,    98,     0,   150,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,     0,
       0,   343,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   110,     0,     0,   111,     0,     1,     0,
       0,     2,     0,     0,     0,     0,     3,   112,     4,     5,
       6,   113,     0,     0,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,    14,    15,    16,    17,     0,     2,
      18,    67,    68,    69,     3,     0,     4,     0,     6,     0,
       0,     0,     7,     8,     0,     0,    10,    11,    19,     0,
      13,     0,    20,    15,    16,    17,     2,     0,    18,    21,
       0,     3,     0,     4,     0,     6,     0,     0,     0,     7,
       8,     0,     0,    10,    11,     0,    19,    13,     0,     0,
      15,    16,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     2,     0,     0,     0,     0,     3,    22,     4,     0,
       6,     0,     0,    19,     7,     8,     0,     0,    10,    11,
      94,     0,    13,     0,     0,    15,    16,    17,     0,     0,
      18,     0,     0,     0,     0,     0,     0,     0,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,    97,
      98,    94,   150,   100,   101,   102,   103,   104,   105,   106,
       0,     0,     0,     0,     0,   259,     0,     0,   107,   108,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   110,
      97,    98,   111,   150,   100,   101,   102,   103,   104,   105,
     106,     0,     0,     0,     0,     0,     0,   113,     0,   107,
     108,     0,    94,     0,     0,     0,     0,     0,     0,   109,
     110,     0,     0,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,     0,
       0,    97,    98,   151,   150,   100,   101,   102,   103,   104,
     105,   106,     0,     0,     0,     0,     0,     0,     0,     0,
     107,   108,     0,    94,     0,     0,     0,     0,     0,     0,
     109,   110,     0,     0,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
       0,     0,    97,    98,   312,   150,   100,   101,   102,   103,
     104,   105,   106,     0,     0,     0,     0,     0,     0,     0,
       0,   107,   108,     0,    94,     0,     0,     0,     0,     0,
       0,   109,   110,     0,     0,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,     0,     0,    97,    98,   345,   150,   100,   101,   102,
     103,   104,   105,   106,     0,     0,     0,     0,     0,     0,
       0,     0,   107,   108,     0,     0,    94,     0,     0,     0,
       0,     0,   109,   110,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,     0,   167,   347,    97,    98,     0,   150,   100,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,   107,   108,     0,    94,     0,     0,
       0,     0,     0,     0,   109,   110,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,     0,   167,    97,    98,    94,   150,
     100,   101,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,   109,   110,    97,    98,   111,
     150,   100,   101,   102,   103,   104,   105,   106,     0,     0,
       0,     0,     0,     0,   113,   305,   107,   108,    94,     0,
       0,     0,     0,     0,     0,     0,   109,   110,     0,     0,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,   352,    97,    98,    94,
     150,   100,   101,   102,   103,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,   107,   108,     0,     0,
       0,     0,     0,     0,     0,     0,   109,   110,    97,    98,
     111,   150,   100,   101,   102,   103,   104,   105,   106,     0,
       0,   184,     0,     0,     0,   113,     0,   107,   108,    94,
       0,     0,     0,     0,     0,     0,     0,   109,   110,     0,
       0,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,     0,     0,     0,   113,     0,    97,    98,
      94,   150,   100,   101,   102,   103,   104,   105,   106,     0,
       0,     0,     0,     0,     0,     0,     0,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   110,    97,
      98,   111,   150,   100,   101,   102,   103,   104,   105,   106,
       0,     0,     0,     0,     0,     0,   113,     0,   107,   108,
      94,     0,     0,     0,     0,     0,     0,     0,   109,   110,
       0,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   186,     0,    97,
      98,     0,   150,   100,   101,   102,   103,   104,   105,   106,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   110,
       0,     0,   111,     1,     0,     0,     2,     0,     0,     0,
       0,     3,     0,     4,     5,     6,     0,   191,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,    14,
      15,    16,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19
};

static const yytype_int16 yycheck[] =
{
      89,    60,    21,    39,    61,   141,     0,   167,    57,    56,
      93,    38,    83,    57,    64,   181,    57,    57,    64,    72,
      64,   147,    79,    57,    57,    52,   244,    82,     0,    86,
     113,    25,    57,     0,    81,    22,    83,    31,    32,    64,
     104,    57,    57,    30,    57,   100,   104,    57,    64,    57,
      44,    64,   102,    25,    64,   103,   106,   102,   102,    84,
     278,   102,   106,    57,   104,   106,   113,   104,   194,   118,
     104,   104,    66,    98,    67,    67,   102,   102,    72,    67,
     106,   217,   218,   219,    71,    98,   102,   102,    98,   102,
     179,    78,   102,    73,    74,    82,    99,   154,   101,   170,
     183,   190,   268,   186,   157,   188,   189,   104,   191,    99,
     167,   104,   104,    57,    99,    95,    96,   107,   101,   202,
     105,    99,   102,   170,   118,    99,   106,   105,   147,   116,
      98,   105,   181,    99,   161,    85,    99,   103,   102,   186,
     103,    98,   106,   200,   280,    67,    68,    69,    70,    71,
      72,    99,   101,    99,    99,   103,   239,   103,   103,   102,
     147,   102,   322,   157,   102,   106,    98,    99,    90,    91,
      92,    93,    94,   262,   231,   194,    94,   102,    99,    99,
      99,   238,   103,   103,   103,   242,   101,   181,     6,   107,
     108,    81,    99,    11,    99,    13,   103,    15,   103,   256,
      86,    19,    20,    98,    99,    23,    24,    84,   244,    27,
      75,    76,    30,    31,    32,    88,    89,    35,    77,    78,
      79,    80,   241,   141,    61,   209,   210,   211,   212,    64,
      65,    66,    62,    63,    67,    53,    98,    99,    98,    99,
     107,   330,   331,   326,   333,   334,   329,    98,    99,   207,
     208,   213,   214,   101,   241,    34,   315,    98,   277,   316,
     215,   216,    57,   352,   103,   322,    57,   350,   255,   103,
     102,   107,   103,    67,   261,   103,   101,   366,   367,   266,
     337,   364,    57,   201,   107,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,     3,   101,    12,     6,    98,    25,    81,    99,
      11,    66,    13,    14,    15,    62,   255,   155,    19,    20,
      21,   261,    23,    24,    78,    26,    27,   336,    29,    30,
      31,    32,   186,   247,    35,   118,   204,   201,    -1,   205,
     203,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,     3,    -1,    -1,
       6,    -1,   280,    64,    -1,    11,    -1,    13,    14,    15,
      -1,    -1,    -1,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    -1,    29,    30,    31,    32,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,     3,    -1,    -1,     6,    53,   109,    -1,
      -1,    11,    -1,    13,    14,    15,    -1,    -1,   336,    19,
      20,    21,    -1,    23,    24,    -1,    26,    27,    -1,    29,
      30,    31,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,     3,    -1,    57,     6,    -1,
      -1,    -1,   108,    11,    64,    13,    14,    15,    -1,    -1,
      -1,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    29,    30,    31,    32,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,    -1,    53,   106,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    64,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,    -1,    -1,   106,    -1,
      -1,    -1,    53,    54,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,   102,    -1,   104,   105,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    -1,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,     3,    -1,   102,     6,   104,   105,    -1,    -1,
      11,    -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,
      21,    -1,    23,    24,    -1,    26,    27,    -1,    29,    30,
      31,    32,    -1,    -1,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,     3,    -1,    -1,
       6,    -1,    -1,    64,    -1,    11,    -1,    13,    14,    15,
      -1,    -1,    -1,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    -1,    29,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,   105,    -1,    -1,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,     4,     5,    -1,    64,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    54,    55,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    -1,    -1,    87,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    98,
      13,    14,    15,   102,    -1,   104,    19,    20,    21,    -1,
      23,    24,    -1,    26,    27,    -1,    29,    30,    31,    32,
      -1,     3,    35,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,    21,
      53,    23,    24,    -1,    26,    27,    -1,    29,    30,    31,
      32,    -1,     3,    35,    -1,     6,    -1,    -1,    -1,    -1,
      11,    -1,    13,    14,    15,    -1,    -1,    -1,    19,    20,
      21,    53,    23,    24,    25,    26,    27,    -1,    29,    30,
      31,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    87,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    98,    13,    14,
      15,   102,    -1,    -1,    19,    20,    21,    -1,    23,    24,
      -1,    26,    27,    -1,    29,    30,    31,    32,    -1,     6,
      35,    36,    37,    38,    11,    -1,    13,    -1,    15,    -1,
      -1,    -1,    19,    20,    -1,    -1,    23,    24,    53,    -1,
      27,    -1,    57,    30,    31,    32,     6,    -1,    35,    64,
      -1,    11,    -1,    13,    -1,    15,    -1,    -1,    -1,    19,
      20,    -1,    -1,    23,    24,    -1,    53,    27,    -1,    -1,
      30,    31,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,   102,    13,    -1,
      15,    -1,    -1,    53,    19,    20,    -1,    -1,    23,    24,
      25,    -1,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    25,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,   105,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      54,    55,    87,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    73,
      74,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      84,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    54,    55,   107,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,    -1,    54,    55,   107,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    84,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    54,    55,   107,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,   104,   105,    54,    55,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    -1,    -1,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,   104,    54,    55,    25,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    83,    84,    54,    55,    87,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,    73,    74,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,    54,    55,    25,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    54,    55,
      87,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    98,    -1,    -1,    -1,   102,    -1,    73,    74,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,
      -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,   102,    -1,    54,    55,
      25,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    54,
      55,    87,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    73,    74,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    54,
      55,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      -1,    -1,    87,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    13,    14,    15,    -1,   102,    -1,    19,
      20,    21,    -1,    23,    24,    -1,    26,    27,    -1,    29,
      30,    31,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    11,    13,    14,    15,    19,    20,    21,
      23,    24,    26,    27,    29,    30,    31,    32,    35,    53,
      57,    64,   102,   109,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   134,   135,   146,   147,
     148,    57,   104,    57,   104,   147,   146,     0,   120,    98,
     144,   145,   146,   124,   124,    57,   104,   104,   156,   148,
     102,   106,   104,    57,   142,   143,   104,    36,    37,    38,
     122,   124,   136,   137,   138,   139,   103,    98,    99,    67,
     156,   104,   126,   130,   131,     4,     5,     8,     9,    10,
      16,    17,    18,    22,    25,    28,    34,    54,    55,    57,
      58,    59,    60,    61,    62,    63,    64,    73,    74,    83,
      84,    87,    98,   102,   105,   123,   124,   156,   157,   158,
     159,   160,   161,   162,   163,   166,   167,   168,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   188,   103,   124,   149,   150,
      57,   107,   168,   142,    67,    99,   105,   136,    98,   140,
     141,   146,   105,   137,   101,   145,   146,   104,   154,   168,
     130,   132,   133,   146,   105,   131,    98,   168,    98,   101,
     159,   102,    57,   102,    98,   167,   102,   182,   102,   102,
     101,   102,   182,   182,   126,   153,   167,   105,   158,    98,
      99,    82,   100,    81,    85,    86,    84,    75,    76,    77,
      78,    79,    80,    88,    89,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    90,    91,    92,    93,
      94,   169,   181,   182,    73,    74,    95,    96,   102,   106,
      61,   102,   106,   146,   147,   151,   152,    99,   103,   107,
     105,   168,   143,   105,    98,    99,    67,   154,   155,   105,
      98,    99,   101,   159,    34,   123,   124,   161,   164,   165,
      98,   167,    98,   153,   167,   167,   159,   102,   147,   151,
     103,   103,   168,   172,   167,   173,   174,   175,   176,   177,
     177,   178,   178,   178,   178,   179,   179,   180,   180,   181,
     181,   181,   168,    57,    57,   103,   168,   187,   167,   103,
     149,   151,   107,   168,   152,   102,   106,   108,   150,   141,
     146,   168,    99,   105,   133,   159,   102,    57,    84,   161,
     103,   103,   103,   103,   103,   181,   101,    99,   103,   107,
     103,   103,   107,   103,   149,   107,   168,   105,   154,   167,
     101,    57,   103,   167,   159,   159,   159,   159,   170,   168,
     103,   107,   103,   167,   101,   159,   103,    12,    98,   167,
     159,   159
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   117,   118,   119,   119,   120,   120,   120,   121,   122,
     122,   123,   123,   124,   124,   124,   124,   125,   125,   125,
     125,   125,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   128,   128,   128,   129,
     129,   130,   130,   131,   132,   132,   133,   134,   134,   134,
     135,   135,   135,   136,   136,   137,   137,   138,   138,   138,
     139,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   148,
     148,   148,   148,   148,   148,   149,   149,   149,   150,   150,
     150,   151,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   153,   153,   154,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   159,   159,
     159,   159,   160,   160,   160,   161,   161,   162,   162,   162,
     163,   163,   163,   163,   163,   164,   164,   165,   165,   166,
     166,   166,   166,   166,   167,   167,   168,   168,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   170,
     170,   171,   171,   172,   172,   173,   173,   174,   174,   175,
     175,   176,   176,   176,   177,   177,   177,   177,   177,   178,
     178,   178,   179,   179,   179,   180,   180,   180,   180,   181,
     181,   182,   182,   182,   182,   182,   182,   183,   183,   183,
     183,   183,   183,   184,   184,   184,   184,   184,   184,   184,
     184,   185,   185,   185,   185,   186,   186,   187,   187,   188,
     188,   188,   188,   188
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       2,     3,     2,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     4,     2,     1,
       1,     1,     2,     3,     1,     3,     1,     5,     4,     2,
       5,     4,     2,     1,     2,     2,     1,     1,     1,     1,
       3,     2,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     1,     1,     2,     1,
       3,     3,     4,     3,     4,     1,     3,     3,     2,     2,
       1,     1,     2,     1,     3,     2,     3,     3,     4,     2,
       3,     3,     4,     1,     2,     1,     3,     4,     1,     3,
       2,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     4,     3,     2,     1,     5,     7,     5,
       5,     7,     6,     7,     5,     1,     1,     4,     5,     3,
       2,     2,     3,     2,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       4,     1,     2,     2,     2,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     3,     3,     3,     2,
       2,     1,     1,     1,     3,     1,     2,     1,     3,     1,
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
#line 169 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1916 "build/parser.tab.cpp"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 175 "src/parser.y"
                         {
        (yyval.node) = create_node("TranslationUnit");
        (yyval.node)->addChild((yyvsp[0].node));
        root = (yyval.node);
    }
#line 1926 "build/parser.tab.cpp"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 180 "src/parser.y"
                                            {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1935 "build/parser.tab.cpp"
    break;

  case 5: /* external_declaration: function_definition  */
#line 187 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1943 "build/parser.tab.cpp"
    break;

  case 6: /* external_declaration: declaration  */
#line 190 "src/parser.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1951 "build/parser.tab.cpp"
    break;

  case 7: /* external_declaration: preprocessor_directive  */
#line 193 "src/parser.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1959 "build/parser.tab.cpp"
    break;

  case 8: /* preprocessor_directive: PREP  */
#line 199 "src/parser.y"
         { (yyval.node) = create_node("Preprocessor", (yyvsp[0].str)); }
#line 1965 "build/parser.tab.cpp"
    break;

  case 9: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 203 "src/parser.y"
                                                         {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 1977 "build/parser.tab.cpp"
    break;

  case 10: /* function_definition: declarator compound_statement  */
#line 210 "src/parser.y"
                                    {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 1988 "build/parser.tab.cpp"
    break;

  case 11: /* declaration: declaration_specifiers init_declarator_list SEMI  */
#line 219 "src/parser.y"
                                                     {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        in_typedef_declaration = 0;
    }
#line 1999 "build/parser.tab.cpp"
    break;

  case 12: /* declaration: declaration_specifiers SEMI  */
#line 225 "src/parser.y"
                                  {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        in_typedef_declaration = 0;
    }
#line 2009 "build/parser.tab.cpp"
    break;

  case 13: /* declaration_specifiers: storage_class_specifier  */
#line 233 "src/parser.y"
                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2018 "build/parser.tab.cpp"
    break;

  case 14: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 237 "src/parser.y"
                                                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2028 "build/parser.tab.cpp"
    break;

  case 15: /* declaration_specifiers: type_specifier  */
#line 242 "src/parser.y"
                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2037 "build/parser.tab.cpp"
    break;

  case 16: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 246 "src/parser.y"
                                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2047 "build/parser.tab.cpp"
    break;

  case 17: /* storage_class_specifier: TYPEDEF  */
#line 254 "src/parser.y"
            {
        (yyval.node) = create_node("StorageClass", "typedef");
        in_typedef_declaration = 1;
    }
#line 2056 "build/parser.tab.cpp"
    break;

  case 18: /* storage_class_specifier: STATIC  */
#line 258 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "static"); }
#line 2062 "build/parser.tab.cpp"
    break;

  case 19: /* storage_class_specifier: EXTERN  */
#line 259 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "extern"); }
#line 2068 "build/parser.tab.cpp"
    break;

  case 20: /* storage_class_specifier: REGISTER  */
#line 260 "src/parser.y"
               { (yyval.node) = create_node("StorageClass", "register"); }
#line 2074 "build/parser.tab.cpp"
    break;

  case 21: /* storage_class_specifier: AUTO  */
#line 261 "src/parser.y"
           { (yyval.node) = create_node("StorageClass", "auto"); }
#line 2080 "build/parser.tab.cpp"
    break;

  case 22: /* type_specifier: type_keyword  */
#line 265 "src/parser.y"
                 {
        (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str));
        strcpy(current_type, (yyvsp[0].str));
    }
#line 2089 "build/parser.tab.cpp"
    break;

  case 23: /* type_specifier: struct_or_union_specifier  */
#line 269 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2095 "build/parser.tab.cpp"
    break;

  case 24: /* type_specifier: enum_specifier  */
#line 270 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2101 "build/parser.tab.cpp"
    break;

  case 25: /* type_specifier: class_specifier  */
#line 271 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2107 "build/parser.tab.cpp"
    break;

  case 26: /* type_keyword: VOID  */
#line 275 "src/parser.y"
         { (yyval.str) = strdup("void"); }
#line 2113 "build/parser.tab.cpp"
    break;

  case 27: /* type_keyword: CHAR  */
#line 276 "src/parser.y"
           { (yyval.str) = strdup("char"); }
#line 2119 "build/parser.tab.cpp"
    break;

  case 28: /* type_keyword: SHORT  */
#line 277 "src/parser.y"
            { (yyval.str) = strdup("short"); }
#line 2125 "build/parser.tab.cpp"
    break;

  case 29: /* type_keyword: INT  */
#line 278 "src/parser.y"
          { (yyval.str) = strdup("int"); }
#line 2131 "build/parser.tab.cpp"
    break;

  case 30: /* type_keyword: LONG  */
#line 279 "src/parser.y"
           { (yyval.str) = strdup("long"); }
#line 2137 "build/parser.tab.cpp"
    break;

  case 31: /* type_keyword: FLOAT  */
#line 280 "src/parser.y"
            { (yyval.str) = strdup("float"); }
#line 2143 "build/parser.tab.cpp"
    break;

  case 32: /* type_keyword: DOUBLE  */
#line 281 "src/parser.y"
             { (yyval.str) = strdup("double"); }
#line 2149 "build/parser.tab.cpp"
    break;

  case 33: /* type_keyword: SIGNED  */
#line 282 "src/parser.y"
             { (yyval.str) = strdup("signed"); }
#line 2155 "build/parser.tab.cpp"
    break;

  case 34: /* type_keyword: UNSIGNED  */
#line 283 "src/parser.y"
               { (yyval.str) = strdup("unsigned"); }
#line 2161 "build/parser.tab.cpp"
    break;

  case 35: /* type_keyword: BOOL  */
#line 284 "src/parser.y"
           { (yyval.str) = strdup("bool"); }
#line 2167 "build/parser.tab.cpp"
    break;

  case 36: /* struct_or_union_specifier: struct_or_union ID LBRACE struct_declaration_list RBRACE  */
#line 288 "src/parser.y"
                                                             {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-4].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2178 "build/parser.tab.cpp"
    break;

  case 37: /* struct_or_union_specifier: struct_or_union LBRACE struct_declaration_list RBRACE  */
#line 294 "src/parser.y"
                                                            {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2188 "build/parser.tab.cpp"
    break;

  case 38: /* struct_or_union_specifier: struct_or_union ID  */
#line 299 "src/parser.y"
                         {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-1].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 2198 "build/parser.tab.cpp"
    break;

  case 39: /* struct_or_union: STRUCT  */
#line 307 "src/parser.y"
           { (yyval.str) = strdup("struct"); }
#line 2204 "build/parser.tab.cpp"
    break;

  case 40: /* struct_or_union: UNION  */
#line 308 "src/parser.y"
            { (yyval.str) = strdup("union"); }
#line 2210 "build/parser.tab.cpp"
    break;

  case 41: /* struct_declaration_list: struct_declaration  */
#line 312 "src/parser.y"
                       {
        (yyval.node) = create_node("StructDeclarationList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2219 "build/parser.tab.cpp"
    break;

  case 42: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 316 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2228 "build/parser.tab.cpp"
    break;

  case 43: /* struct_declaration: type_specifier struct_declarator_list SEMI  */
#line 323 "src/parser.y"
                                               {
        (yyval.node) = create_node("StructDeclaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2238 "build/parser.tab.cpp"
    break;

  case 44: /* struct_declarator_list: struct_declarator  */
#line 331 "src/parser.y"
                      {
        (yyval.node) = create_node("StructDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2247 "build/parser.tab.cpp"
    break;

  case 45: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 335 "src/parser.y"
                                                     {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2256 "build/parser.tab.cpp"
    break;

  case 46: /* struct_declarator: declarator  */
#line 342 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2262 "build/parser.tab.cpp"
    break;

  case 47: /* enum_specifier: ENUM ID LBRACE enumerator_list RBRACE  */
#line 346 "src/parser.y"
                                          {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2272 "build/parser.tab.cpp"
    break;

  case 48: /* enum_specifier: ENUM LBRACE enumerator_list RBRACE  */
#line 351 "src/parser.y"
                                         {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2281 "build/parser.tab.cpp"
    break;

  case 49: /* enum_specifier: ENUM ID  */
#line 355 "src/parser.y"
              {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 2290 "build/parser.tab.cpp"
    break;

  case 50: /* class_specifier: CLASS ID LBRACE class_declaration_list RBRACE  */
#line 363 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ClassSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2300 "build/parser.tab.cpp"
    break;

  case 51: /* class_specifier: CLASS LBRACE class_declaration_list RBRACE  */
#line 368 "src/parser.y"
                                                 {
        (yyval.node) = create_node("ClassSpecifier");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2309 "build/parser.tab.cpp"
    break;

  case 52: /* class_specifier: CLASS ID  */
#line 372 "src/parser.y"
               {
        (yyval.node) = create_node("ClassSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 2318 "build/parser.tab.cpp"
    break;

  case 53: /* class_declaration_list: class_declaration  */
#line 379 "src/parser.y"
                      {
        (yyval.node) = create_node("ClassDeclarationList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2327 "build/parser.tab.cpp"
    break;

  case 54: /* class_declaration_list: class_declaration_list class_declaration  */
#line 383 "src/parser.y"
                                               {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2336 "build/parser.tab.cpp"
    break;

  case 55: /* class_declaration: access_specifier COLON  */
#line 390 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2344 "build/parser.tab.cpp"
    break;

  case 56: /* class_declaration: member_declaration  */
#line 393 "src/parser.y"
                         {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2352 "build/parser.tab.cpp"
    break;

  case 57: /* access_specifier: PUBLIC  */
#line 399 "src/parser.y"
           { 
        (yyval.node) = create_node("AccessSpecifier", "public"); 
    }
#line 2360 "build/parser.tab.cpp"
    break;

  case 58: /* access_specifier: PRIVATE  */
#line 402 "src/parser.y"
              { 
        (yyval.node) = create_node("AccessSpecifier", "private"); 
    }
#line 2368 "build/parser.tab.cpp"
    break;

  case 59: /* access_specifier: PROTECTED  */
#line 405 "src/parser.y"
                { 
        (yyval.node) = create_node("AccessSpecifier", "protected"); 
    }
#line 2376 "build/parser.tab.cpp"
    break;

  case 60: /* member_declaration: declaration_specifiers member_declarator_list SEMI  */
#line 411 "src/parser.y"
                                                       {
        (yyval.node) = create_node("MemberDeclaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2386 "build/parser.tab.cpp"
    break;

  case 61: /* member_declaration: declaration_specifiers SEMI  */
#line 416 "src/parser.y"
                                  {
        (yyval.node) = create_node("MemberDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2395 "build/parser.tab.cpp"
    break;

  case 62: /* member_declaration: function_definition  */
#line 420 "src/parser.y"
                          {
        (yyval.node) = create_node("MemberFunction");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2404 "build/parser.tab.cpp"
    break;

  case 63: /* member_declarator_list: member_declarator  */
#line 427 "src/parser.y"
                      {
        (yyval.node) = create_node("MemberDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2413 "build/parser.tab.cpp"
    break;

  case 64: /* member_declarator_list: member_declarator_list COMMA member_declarator  */
#line 431 "src/parser.y"
                                                     {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2422 "build/parser.tab.cpp"
    break;

  case 65: /* member_declarator: declarator  */
#line 438 "src/parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2430 "build/parser.tab.cpp"
    break;

  case 66: /* member_declarator: declarator ASSIGN assignment_expression  */
#line 441 "src/parser.y"
                                              {
        (yyval.node) = create_node("MemberDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2440 "build/parser.tab.cpp"
    break;

  case 67: /* enumerator_list: enumerator  */
#line 449 "src/parser.y"
               {
        (yyval.node) = create_node("EnumeratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2449 "build/parser.tab.cpp"
    break;

  case 68: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 453 "src/parser.y"
                                       {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2458 "build/parser.tab.cpp"
    break;

  case 69: /* enumerator: ID  */
#line 460 "src/parser.y"
       {
        (yyval.node) = create_node("Enumerator", (yyvsp[0].str));
    }
#line 2466 "build/parser.tab.cpp"
    break;

  case 70: /* enumerator: ID ASSIGN assignment_expression  */
#line 463 "src/parser.y"
                                      {
        (yyval.node) = create_node("Enumerator", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2475 "build/parser.tab.cpp"
    break;

  case 71: /* init_declarator_list: init_declarator  */
#line 470 "src/parser.y"
                    {
        (yyval.node) = create_node("InitDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2484 "build/parser.tab.cpp"
    break;

  case 72: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 474 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2493 "build/parser.tab.cpp"
    break;

  case 73: /* init_declarator: declarator  */
#line 481 "src/parser.y"
               {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2502 "build/parser.tab.cpp"
    break;

  case 74: /* init_declarator: declarator ASSIGN initializer  */
#line 485 "src/parser.y"
                                    {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2512 "build/parser.tab.cpp"
    break;

  case 75: /* declarator: pointer direct_declarator  */
#line 493 "src/parser.y"
                              {
        (yyval.node) = create_node("Declarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2522 "build/parser.tab.cpp"
    break;

  case 76: /* declarator: direct_declarator  */
#line 498 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2530 "build/parser.tab.cpp"
    break;

  case 77: /* pointer: MUL  */
#line 504 "src/parser.y"
        {
        (yyval.node) = create_node("Pointer");
    }
#line 2538 "build/parser.tab.cpp"
    break;

  case 78: /* pointer: MUL pointer  */
#line 507 "src/parser.y"
                  {
        (yyval.node) = create_node("Pointer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2547 "build/parser.tab.cpp"
    break;

  case 79: /* direct_declarator: ID  */
#line 514 "src/parser.y"
       {
        (yyval.node) = create_node("DirectDeclarator", (yyvsp[0].str));
    }
#line 2555 "build/parser.tab.cpp"
    break;

  case 80: /* direct_declarator: LPAREN declarator RPAREN  */
#line 517 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2563 "build/parser.tab.cpp"
    break;

  case 81: /* direct_declarator: direct_declarator LBRACKET RBRACKET  */
#line 520 "src/parser.y"
                                          {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2572 "build/parser.tab.cpp"
    break;

  case 82: /* direct_declarator: direct_declarator LBRACKET assignment_expression RBRACKET  */
#line 524 "src/parser.y"
                                                                {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2582 "build/parser.tab.cpp"
    break;

  case 83: /* direct_declarator: direct_declarator LPAREN RPAREN  */
#line 529 "src/parser.y"
                                      {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2591 "build/parser.tab.cpp"
    break;

  case 84: /* direct_declarator: direct_declarator LPAREN parameter_list RPAREN  */
#line 533 "src/parser.y"
                                                     {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2601 "build/parser.tab.cpp"
    break;

  case 85: /* parameter_list: parameter_declaration  */
#line 541 "src/parser.y"
                          {
        (yyval.node) = create_node("ParameterList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2610 "build/parser.tab.cpp"
    break;

  case 86: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 545 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2619 "build/parser.tab.cpp"
    break;

  case 87: /* parameter_list: parameter_list COMMA ELLIPSIS  */
#line 549 "src/parser.y"
                                    {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild(create_node("Ellipsis"));
    }
#line 2628 "build/parser.tab.cpp"
    break;

  case 88: /* parameter_declaration: declaration_specifiers declarator  */
#line 556 "src/parser.y"
                                      {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2638 "build/parser.tab.cpp"
    break;

  case 89: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 561 "src/parser.y"
                                                 {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2648 "build/parser.tab.cpp"
    break;

  case 90: /* parameter_declaration: declaration_specifiers  */
#line 566 "src/parser.y"
                             {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2657 "build/parser.tab.cpp"
    break;

  case 91: /* abstract_declarator: pointer  */
#line 573 "src/parser.y"
            {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2666 "build/parser.tab.cpp"
    break;

  case 92: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 577 "src/parser.y"
                                         {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2676 "build/parser.tab.cpp"
    break;

  case 93: /* abstract_declarator: direct_abstract_declarator  */
#line 582 "src/parser.y"
                                 {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2685 "build/parser.tab.cpp"
    break;

  case 94: /* direct_abstract_declarator: LPAREN abstract_declarator RPAREN  */
#line 589 "src/parser.y"
                                      {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2693 "build/parser.tab.cpp"
    break;

  case 95: /* direct_abstract_declarator: LBRACKET RBRACKET  */
#line 592 "src/parser.y"
                        {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
    }
#line 2701 "build/parser.tab.cpp"
    break;

  case 96: /* direct_abstract_declarator: LBRACKET assignment_expression RBRACKET  */
#line 595 "src/parser.y"
                                              {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2710 "build/parser.tab.cpp"
    break;

  case 97: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET RBRACKET  */
#line 599 "src/parser.y"
                                                   {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2719 "build/parser.tab.cpp"
    break;

  case 98: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET assignment_expression RBRACKET  */
#line 603 "src/parser.y"
                                                                         {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2729 "build/parser.tab.cpp"
    break;

  case 99: /* direct_abstract_declarator: LPAREN RPAREN  */
#line 608 "src/parser.y"
                    {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
    }
#line 2737 "build/parser.tab.cpp"
    break;

  case 100: /* direct_abstract_declarator: LPAREN parameter_list RPAREN  */
#line 611 "src/parser.y"
                                   {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2746 "build/parser.tab.cpp"
    break;

  case 101: /* direct_abstract_declarator: direct_abstract_declarator LPAREN RPAREN  */
#line 615 "src/parser.y"
                                               {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2755 "build/parser.tab.cpp"
    break;

  case 102: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_list RPAREN  */
#line 619 "src/parser.y"
                                                              {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2765 "build/parser.tab.cpp"
    break;

  case 103: /* type_name: type_specifier  */
#line 627 "src/parser.y"
                   {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2774 "build/parser.tab.cpp"
    break;

  case 104: /* type_name: type_specifier abstract_declarator  */
#line 631 "src/parser.y"
                                         {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2784 "build/parser.tab.cpp"
    break;

  case 105: /* initializer: assignment_expression  */
#line 639 "src/parser.y"
                          {
        (yyval.node) = create_node("Initializer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2793 "build/parser.tab.cpp"
    break;

  case 106: /* initializer: LBRACE initializer_list RBRACE  */
#line 643 "src/parser.y"
                                     {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2802 "build/parser.tab.cpp"
    break;

  case 107: /* initializer: LBRACE initializer_list COMMA RBRACE  */
#line 647 "src/parser.y"
                                           {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2811 "build/parser.tab.cpp"
    break;

  case 108: /* initializer_list: initializer  */
#line 654 "src/parser.y"
                {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2820 "build/parser.tab.cpp"
    break;

  case 109: /* initializer_list: initializer_list COMMA initializer  */
#line 658 "src/parser.y"
                                         {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2829 "build/parser.tab.cpp"
    break;

  case 110: /* compound_statement: LBRACE RBRACE  */
#line 665 "src/parser.y"
                  {
        (yyval.node) = create_node("CompoundStatement");
    }
#line 2837 "build/parser.tab.cpp"
    break;

  case 111: /* compound_statement: LBRACE block_item_list RBRACE  */
#line 668 "src/parser.y"
                                    {
        (yyval.node) = create_node("CompoundStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2846 "build/parser.tab.cpp"
    break;

  case 112: /* block_item_list: block_item  */
#line 675 "src/parser.y"
               {
        (yyval.node) = create_node("BlockItemList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2855 "build/parser.tab.cpp"
    break;

  case 113: /* block_item_list: block_item_list block_item  */
#line 679 "src/parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2864 "build/parser.tab.cpp"
    break;

  case 114: /* block_item: declaration  */
#line 686 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2873 "build/parser.tab.cpp"
    break;

  case 115: /* block_item: statement  */
#line 690 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2882 "build/parser.tab.cpp"
    break;

  case 116: /* statement: labeled_statement  */
#line 697 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2888 "build/parser.tab.cpp"
    break;

  case 117: /* statement: expression_statement  */
#line 698 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2894 "build/parser.tab.cpp"
    break;

  case 118: /* statement: compound_statement  */
#line 699 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2900 "build/parser.tab.cpp"
    break;

  case 119: /* statement: selection_statement  */
#line 700 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2906 "build/parser.tab.cpp"
    break;

  case 120: /* statement: iteration_statement  */
#line 701 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2912 "build/parser.tab.cpp"
    break;

  case 121: /* statement: jump_statement  */
#line 702 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2918 "build/parser.tab.cpp"
    break;

  case 122: /* labeled_statement: ID COLON statement  */
#line 706 "src/parser.y"
                       {
        (yyval.node) = create_node("LabeledStatement", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2927 "build/parser.tab.cpp"
    break;

  case 123: /* labeled_statement: CASE assignment_expression COLON statement  */
#line 710 "src/parser.y"
                                                 {
        (yyval.node) = create_node("CaseStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2937 "build/parser.tab.cpp"
    break;

  case 124: /* labeled_statement: DEFAULT COLON statement  */
#line 715 "src/parser.y"
                              {
        (yyval.node) = create_node("DefaultStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2946 "build/parser.tab.cpp"
    break;

  case 125: /* expression_statement: expression SEMI  */
#line 722 "src/parser.y"
                    {
        (yyval.node) = create_node("ExpressionStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2955 "build/parser.tab.cpp"
    break;

  case 126: /* expression_statement: SEMI  */
#line 726 "src/parser.y"
           {
        (yyval.node) = create_node("EmptyStatement");
    }
#line 2963 "build/parser.tab.cpp"
    break;

  case 127: /* selection_statement: IF LPAREN expression RPAREN statement  */
#line 732 "src/parser.y"
                                                                {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2973 "build/parser.tab.cpp"
    break;

  case 128: /* selection_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 737 "src/parser.y"
                                                           {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2984 "build/parser.tab.cpp"
    break;

  case 129: /* selection_statement: SWITCH LPAREN expression RPAREN statement  */
#line 743 "src/parser.y"
                                                {
        (yyval.node) = create_node("SwitchStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2994 "build/parser.tab.cpp"
    break;

  case 130: /* iteration_statement: WHILE LPAREN expression RPAREN statement  */
#line 751 "src/parser.y"
                                             {
        (yyval.node) = create_node("WhileStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3004 "build/parser.tab.cpp"
    break;

  case 131: /* iteration_statement: DO statement WHILE LPAREN expression RPAREN SEMI  */
#line 756 "src/parser.y"
                                                       {
        (yyval.node) = create_node("DoWhileStatement");
        (yyval.node)->addChild((yyvsp[-5].node));
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 3014 "build/parser.tab.cpp"
    break;

  case 132: /* iteration_statement: FOR LPAREN for_init_statement expression_statement RPAREN statement  */
#line 761 "src/parser.y"
                                                                          {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3025 "build/parser.tab.cpp"
    break;

  case 133: /* iteration_statement: FOR LPAREN for_init_statement expression_statement expression RPAREN statement  */
#line 767 "src/parser.y"
                                                                                     {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3037 "build/parser.tab.cpp"
    break;

  case 134: /* iteration_statement: FOR LPAREN range_based_for RPAREN statement  */
#line 774 "src/parser.y"
                                                  {
        (yyval.node) = create_node("RangeBasedForStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3047 "build/parser.tab.cpp"
    break;

  case 135: /* for_init_statement: expression_statement  */
#line 782 "src/parser.y"
                         {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3056 "build/parser.tab.cpp"
    break;

  case 136: /* for_init_statement: declaration  */
#line 786 "src/parser.y"
                  {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3065 "build/parser.tab.cpp"
    break;

  case 137: /* range_based_for: declaration_specifiers ID COLON expression  */
#line 793 "src/parser.y"
                                               {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3076 "build/parser.tab.cpp"
    break;

  case 138: /* range_based_for: declaration_specifiers BIT_AND ID COLON expression  */
#line 799 "src/parser.y"
                                                         {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild(create_node("Reference"));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3088 "build/parser.tab.cpp"
    break;

  case 139: /* jump_statement: GOTO ID SEMI  */
#line 809 "src/parser.y"
                 {
        (yyval.node) = create_node("GotoStatement", (yyvsp[-1].str));
    }
#line 3096 "build/parser.tab.cpp"
    break;

  case 140: /* jump_statement: CONTINUE SEMI  */
#line 812 "src/parser.y"
                    {
        (yyval.node) = create_node("ContinueStatement");
    }
#line 3104 "build/parser.tab.cpp"
    break;

  case 141: /* jump_statement: BREAK SEMI  */
#line 815 "src/parser.y"
                 {
        (yyval.node) = create_node("BreakStatement");
    }
#line 3112 "build/parser.tab.cpp"
    break;

  case 142: /* jump_statement: RETURN expression SEMI  */
#line 818 "src/parser.y"
                             {
        (yyval.node) = create_node("ReturnStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3121 "build/parser.tab.cpp"
    break;

  case 143: /* jump_statement: RETURN SEMI  */
#line 822 "src/parser.y"
                  {
        (yyval.node) = create_node("ReturnStatement");
    }
#line 3129 "build/parser.tab.cpp"
    break;

  case 144: /* expression: assignment_expression  */
#line 828 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3137 "build/parser.tab.cpp"
    break;

  case 145: /* expression: expression COMMA assignment_expression  */
#line 831 "src/parser.y"
                                             {
        (yyval.node) = create_node("CommaExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3147 "build/parser.tab.cpp"
    break;

  case 146: /* assignment_expression: conditional_expression  */
#line 839 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3155 "build/parser.tab.cpp"
    break;

  case 147: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 842 "src/parser.y"
                                                                 {
        (yyval.node) = create_node("AssignmentExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3165 "build/parser.tab.cpp"
    break;

  case 148: /* assignment_operator: ASSIGN  */
#line 850 "src/parser.y"
           { (yyval.str) = strdup("="); }
#line 3171 "build/parser.tab.cpp"
    break;

  case 149: /* assignment_operator: PLUS_EQ  */
#line 851 "src/parser.y"
              { (yyval.str) = strdup("+="); }
#line 3177 "build/parser.tab.cpp"
    break;

  case 150: /* assignment_operator: MINUS_EQ  */
#line 852 "src/parser.y"
               { (yyval.str) = strdup("-="); }
#line 3183 "build/parser.tab.cpp"
    break;

  case 151: /* assignment_operator: MUL_EQ  */
#line 853 "src/parser.y"
             { (yyval.str) = strdup("*="); }
#line 3189 "build/parser.tab.cpp"
    break;

  case 152: /* assignment_operator: DIV_EQ  */
#line 854 "src/parser.y"
             { (yyval.str) = strdup("/="); }
#line 3195 "build/parser.tab.cpp"
    break;

  case 153: /* assignment_operator: MOD_EQ  */
#line 855 "src/parser.y"
             { (yyval.str) = strdup("%="); }
#line 3201 "build/parser.tab.cpp"
    break;

  case 154: /* assignment_operator: AND_EQ  */
#line 856 "src/parser.y"
             { (yyval.str) = strdup("&="); }
#line 3207 "build/parser.tab.cpp"
    break;

  case 155: /* assignment_operator: OR_EQ  */
#line 857 "src/parser.y"
            { (yyval.str) = strdup("|="); }
#line 3213 "build/parser.tab.cpp"
    break;

  case 156: /* assignment_operator: XOR_EQ  */
#line 858 "src/parser.y"
             { (yyval.str) = strdup("^="); }
#line 3219 "build/parser.tab.cpp"
    break;

  case 157: /* assignment_operator: LSHIFT_EQ  */
#line 859 "src/parser.y"
                { (yyval.str) = strdup("<<="); }
#line 3225 "build/parser.tab.cpp"
    break;

  case 158: /* assignment_operator: RSHIFT_EQ  */
#line 860 "src/parser.y"
                { (yyval.str) = strdup(">>="); }
#line 3231 "build/parser.tab.cpp"
    break;

  case 159: /* conditional_expression: logical_or_expression  */
#line 864 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3239 "build/parser.tab.cpp"
    break;

  case 160: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 867 "src/parser.y"
                                                                             {
        (yyval.node) = create_node("ConditionalExpression");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3250 "build/parser.tab.cpp"
    break;

  case 161: /* logical_or_expression: logical_and_expression  */
#line 876 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3258 "build/parser.tab.cpp"
    break;

  case 162: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 879 "src/parser.y"
                                                      {
        (yyval.node) = create_node("LogicalOrExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3268 "build/parser.tab.cpp"
    break;

  case 163: /* logical_and_expression: inclusive_or_expression  */
#line 887 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3276 "build/parser.tab.cpp"
    break;

  case 164: /* logical_and_expression: logical_and_expression AND inclusive_or_expression  */
#line 890 "src/parser.y"
                                                         {
        (yyval.node) = create_node("LogicalAndExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3286 "build/parser.tab.cpp"
    break;

  case 165: /* inclusive_or_expression: exclusive_or_expression  */
#line 898 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3294 "build/parser.tab.cpp"
    break;

  case 166: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 901 "src/parser.y"
                                                             {
        (yyval.node) = create_node("InclusiveOrExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3304 "build/parser.tab.cpp"
    break;

  case 167: /* exclusive_or_expression: and_expression  */
#line 909 "src/parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3312 "build/parser.tab.cpp"
    break;

  case 168: /* exclusive_or_expression: exclusive_or_expression BIT_XOR and_expression  */
#line 912 "src/parser.y"
                                                     {
        (yyval.node) = create_node("ExclusiveOrExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3322 "build/parser.tab.cpp"
    break;

  case 169: /* and_expression: equality_expression  */
#line 920 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3330 "build/parser.tab.cpp"
    break;

  case 170: /* and_expression: and_expression BIT_AND equality_expression  */
#line 923 "src/parser.y"
                                                 {
        (yyval.node) = create_node("AndExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3340 "build/parser.tab.cpp"
    break;

  case 171: /* equality_expression: relational_expression  */
#line 931 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3348 "build/parser.tab.cpp"
    break;

  case 172: /* equality_expression: equality_expression EQ relational_expression  */
#line 934 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "==");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3358 "build/parser.tab.cpp"
    break;

  case 173: /* equality_expression: equality_expression NE relational_expression  */
#line 939 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "!=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3368 "build/parser.tab.cpp"
    break;

  case 174: /* relational_expression: shift_expression  */
#line 947 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3376 "build/parser.tab.cpp"
    break;

  case 175: /* relational_expression: relational_expression LT shift_expression  */
#line 950 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3386 "build/parser.tab.cpp"
    break;

  case 176: /* relational_expression: relational_expression GT shift_expression  */
#line 955 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3396 "build/parser.tab.cpp"
    break;

  case 177: /* relational_expression: relational_expression LE shift_expression  */
#line 960 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3406 "build/parser.tab.cpp"
    break;

  case 178: /* relational_expression: relational_expression GE shift_expression  */
#line 965 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3416 "build/parser.tab.cpp"
    break;

  case 179: /* shift_expression: additive_expression  */
#line 973 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3424 "build/parser.tab.cpp"
    break;

  case 180: /* shift_expression: shift_expression LSHIFT additive_expression  */
#line 976 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", "<<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3434 "build/parser.tab.cpp"
    break;

  case 181: /* shift_expression: shift_expression RSHIFT additive_expression  */
#line 981 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", ">>");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3444 "build/parser.tab.cpp"
    break;

  case 182: /* additive_expression: multiplicative_expression  */
#line 989 "src/parser.y"
                              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3452 "build/parser.tab.cpp"
    break;

  case 183: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 992 "src/parser.y"
                                                         {
        (yyval.node) = create_node("AdditiveExpression", "+");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3462 "build/parser.tab.cpp"
    break;

  case 184: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 997 "src/parser.y"
                                                          {
        (yyval.node) = create_node("AdditiveExpression", "-");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3472 "build/parser.tab.cpp"
    break;

  case 185: /* multiplicative_expression: cast_expression  */
#line 1005 "src/parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3480 "build/parser.tab.cpp"
    break;

  case 186: /* multiplicative_expression: multiplicative_expression MUL cast_expression  */
#line 1008 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "*");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3490 "build/parser.tab.cpp"
    break;

  case 187: /* multiplicative_expression: multiplicative_expression DIV cast_expression  */
#line 1013 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "/");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3500 "build/parser.tab.cpp"
    break;

  case 188: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 1018 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "%");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3510 "build/parser.tab.cpp"
    break;

  case 189: /* cast_expression: unary_expression  */
#line 1026 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3518 "build/parser.tab.cpp"
    break;

  case 190: /* cast_expression: LPAREN type_name RPAREN cast_expression  */
#line 1029 "src/parser.y"
                                              {
        (yyval.node) = create_node("CastExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3528 "build/parser.tab.cpp"
    break;

  case 191: /* unary_expression: postfix_expression  */
#line 1037 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3536 "build/parser.tab.cpp"
    break;

  case 192: /* unary_expression: INC unary_expression  */
#line 1040 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "++");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3545 "build/parser.tab.cpp"
    break;

  case 193: /* unary_expression: DEC unary_expression  */
#line 1044 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "--");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3554 "build/parser.tab.cpp"
    break;

  case 194: /* unary_expression: unary_operator cast_expression  */
#line 1048 "src/parser.y"
                                     {
        (yyval.node) = create_node("UnaryExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3563 "build/parser.tab.cpp"
    break;

  case 195: /* unary_expression: SIZEOF unary_expression  */
#line 1052 "src/parser.y"
                              {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3572 "build/parser.tab.cpp"
    break;

  case 196: /* unary_expression: SIZEOF LPAREN type_name RPAREN  */
#line 1056 "src/parser.y"
                                     {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3581 "build/parser.tab.cpp"
    break;

  case 197: /* unary_operator: BIT_AND  */
#line 1063 "src/parser.y"
            { (yyval.str) = strdup("&"); }
#line 3587 "build/parser.tab.cpp"
    break;

  case 198: /* unary_operator: MUL  */
#line 1064 "src/parser.y"
          { (yyval.str) = strdup("*"); }
#line 3593 "build/parser.tab.cpp"
    break;

  case 199: /* unary_operator: PLUS  */
#line 1065 "src/parser.y"
           { (yyval.str) = strdup("+"); }
#line 3599 "build/parser.tab.cpp"
    break;

  case 200: /* unary_operator: MINUS  */
#line 1066 "src/parser.y"
            { (yyval.str) = strdup("-"); }
#line 3605 "build/parser.tab.cpp"
    break;

  case 201: /* unary_operator: BIT_NOT  */
#line 1067 "src/parser.y"
              { (yyval.str) = strdup("~"); }
#line 3611 "build/parser.tab.cpp"
    break;

  case 202: /* unary_operator: NOT  */
#line 1068 "src/parser.y"
          { (yyval.str) = strdup("!"); }
#line 3617 "build/parser.tab.cpp"
    break;

  case 203: /* postfix_expression: primary_expression  */
#line 1072 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3625 "build/parser.tab.cpp"
    break;

  case 204: /* postfix_expression: postfix_expression LBRACKET expression RBRACKET  */
#line 1075 "src/parser.y"
                                                      {
        (yyval.node) = create_node("ArraySubscript");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3635 "build/parser.tab.cpp"
    break;

  case 205: /* postfix_expression: postfix_expression LPAREN argument_expression_list RPAREN  */
#line 1080 "src/parser.y"
                                                                {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3645 "build/parser.tab.cpp"
    break;

  case 206: /* postfix_expression: postfix_expression LPAREN RPAREN  */
#line 1085 "src/parser.y"
                                       {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 3654 "build/parser.tab.cpp"
    break;

  case 207: /* postfix_expression: postfix_expression DOT ID  */
#line 1089 "src/parser.y"
                                {
        (yyval.node) = create_node("MemberAccess", ".");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3664 "build/parser.tab.cpp"
    break;

  case 208: /* postfix_expression: postfix_expression ARROW ID  */
#line 1094 "src/parser.y"
                                  {
        (yyval.node) = create_node("MemberAccess", "->");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3674 "build/parser.tab.cpp"
    break;

  case 209: /* postfix_expression: postfix_expression INC  */
#line 1099 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "++");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3683 "build/parser.tab.cpp"
    break;

  case 210: /* postfix_expression: postfix_expression DEC  */
#line 1103 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "--");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3692 "build/parser.tab.cpp"
    break;

  case 211: /* primary_expression: ID  */
#line 1110 "src/parser.y"
       {
        (yyval.node) = create_node("Identifier", (yyvsp[0].str));
    }
#line 3700 "build/parser.tab.cpp"
    break;

  case 212: /* primary_expression: constant  */
#line 1113 "src/parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3708 "build/parser.tab.cpp"
    break;

  case 213: /* primary_expression: string_literal  */
#line 1116 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3716 "build/parser.tab.cpp"
    break;

  case 214: /* primary_expression: LPAREN expression RPAREN  */
#line 1119 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3724 "build/parser.tab.cpp"
    break;

  case 215: /* string_literal: STRING_LIT  */
#line 1125 "src/parser.y"
               {
        (yyval.node) = create_node("StringLiteral", (yyvsp[0].str));
    }
#line 3732 "build/parser.tab.cpp"
    break;

  case 216: /* string_literal: string_literal STRING_LIT  */
#line 1128 "src/parser.y"
                                {
        (yyval.node) = create_node("StringLiteral");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild(create_node("StringLiteral", (yyvsp[0].str)));
    }
#line 3742 "build/parser.tab.cpp"
    break;

  case 217: /* argument_expression_list: assignment_expression  */
#line 1136 "src/parser.y"
                          {
        (yyval.node) = create_node("ArgumentList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3751 "build/parser.tab.cpp"
    break;

  case 218: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 1140 "src/parser.y"
                                                           {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3760 "build/parser.tab.cpp"
    break;

  case 219: /* constant: NUM  */
#line 1147 "src/parser.y"
        { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3766 "build/parser.tab.cpp"
    break;

  case 220: /* constant: FLOAT_LIT  */
#line 1148 "src/parser.y"
                { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3772 "build/parser.tab.cpp"
    break;

  case 221: /* constant: CHAR_LIT  */
#line 1149 "src/parser.y"
               { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3778 "build/parser.tab.cpp"
    break;

  case 222: /* constant: TRUE  */
#line 1150 "src/parser.y"
           { (yyval.node) = create_node("Constant", "true"); }
#line 3784 "build/parser.tab.cpp"
    break;

  case 223: /* constant: FALSE  */
#line 1151 "src/parser.y"
            { (yyval.node) = create_node("Constant", "false"); }
#line 3790 "build/parser.tab.cpp"
    break;


#line 3794 "build/parser.tab.cpp"

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

#line 1154 "src/parser.y"


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
        SemanticAnalyzer analyzer(symbol_table);
        analyzer.analyze(root);
        
        // Print symbol table
        symbol_table->print_table();
        
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
        }
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Total syntax errors: %d\n", syntax_errors);
        return 1;
    }
    
    return 0;
}
