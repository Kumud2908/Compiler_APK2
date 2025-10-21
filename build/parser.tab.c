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


#line 148 "build/parser.tab.c"

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

#include "parser.tab.h"
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
  YYSYMBOL_UMINUS = 113,                   /* UMINUS  */
  YYSYMBOL_UPLUS = 114,                    /* UPLUS  */
  YYSYMBOL_IF_WITHOUT_ELSE = 115,          /* IF_WITHOUT_ELSE  */
  YYSYMBOL_YYACCEPT = 116,                 /* $accept  */
  YYSYMBOL_program = 117,                  /* program  */
  YYSYMBOL_translation_unit = 118,         /* translation_unit  */
  YYSYMBOL_external_declaration = 119,     /* external_declaration  */
  YYSYMBOL_preprocessor_directive = 120,   /* preprocessor_directive  */
  YYSYMBOL_function_definition = 121,      /* function_definition  */
  YYSYMBOL_declaration = 122,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 123,   /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 124,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 125,           /* type_specifier  */
  YYSYMBOL_type_keyword = 126,             /* type_keyword  */
  YYSYMBOL_struct_or_union_specifier = 127, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 128,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 129,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 130,       /* struct_declaration  */
  YYSYMBOL_struct_declarator_list = 131,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 132,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 133,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 134,          /* enumerator_list  */
  YYSYMBOL_enumerator = 135,               /* enumerator  */
  YYSYMBOL_init_declarator_list = 136,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 137,          /* init_declarator  */
  YYSYMBOL_declarator = 138,               /* declarator  */
  YYSYMBOL_pointer = 139,                  /* pointer  */
  YYSYMBOL_direct_declarator = 140,        /* direct_declarator  */
  YYSYMBOL_141_1 = 141,                    /* $@1  */
  YYSYMBOL_parameter_list = 142,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 143,    /* parameter_declaration  */
  YYSYMBOL_abstract_declarator = 144,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 145, /* direct_abstract_declarator  */
  YYSYMBOL_type_name = 146,                /* type_name  */
  YYSYMBOL_initializer = 147,              /* initializer  */
  YYSYMBOL_initializer_list = 148,         /* initializer_list  */
  YYSYMBOL_compound_statement = 149,       /* compound_statement  */
  YYSYMBOL_block_item_list = 150,          /* block_item_list  */
  YYSYMBOL_block_item = 151,               /* block_item  */
  YYSYMBOL_statement = 152,                /* statement  */
  YYSYMBOL_labeled_statement = 153,        /* labeled_statement  */
  YYSYMBOL_expression_statement = 154,     /* expression_statement  */
  YYSYMBOL_selection_statement = 155,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 156,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 157,       /* for_init_statement  */
  YYSYMBOL_range_based_for = 158,          /* range_based_for  */
  YYSYMBOL_jump_statement = 159,           /* jump_statement  */
  YYSYMBOL_expression = 160,               /* expression  */
  YYSYMBOL_assignment_expression = 161,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 162,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 163,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 164,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 165,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 166,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 167,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 168,           /* and_expression  */
  YYSYMBOL_equality_expression = 169,      /* equality_expression  */
  YYSYMBOL_relational_expression = 170,    /* relational_expression  */
  YYSYMBOL_shift_expression = 171,         /* shift_expression  */
  YYSYMBOL_additive_expression = 172,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 173, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 174,          /* cast_expression  */
  YYSYMBOL_unary_expression = 175,         /* unary_expression  */
  YYSYMBOL_unary_operator = 176,           /* unary_operator  */
  YYSYMBOL_postfix_expression = 177,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 178,       /* primary_expression  */
  YYSYMBOL_string_literal = 179,           /* string_literal  */
  YYSYMBOL_argument_expression_list = 180, /* argument_expression_list  */
  YYSYMBOL_constant = 181                  /* constant  */
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
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  116
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  206
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  344

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   370


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
     115
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   163,   163,   169,   174,   181,   184,   187,   193,   197,
     204,   213,   219,   227,   231,   236,   240,   248,   252,   253,
     254,   255,   259,   263,   264,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   281,   287,   292,   300,   301,
     305,   309,   316,   324,   328,   335,   339,   344,   348,   355,
     359,   366,   369,   376,   380,   387,   391,   399,   404,   410,
     413,   420,   423,   426,   431,   435,   435,   443,   451,   455,
     459,   466,   471,   476,   483,   487,   492,   499,   502,   505,
     509,   513,   518,   521,   525,   529,   537,   541,   549,   553,
     557,   564,   568,   575,   578,   585,   589,   596,   600,   607,
     608,   609,   610,   611,   612,   616,   620,   625,   632,   636,
     642,   647,   653,   661,   666,   671,   677,   684,   692,   696,
     703,   709,   719,   722,   725,   728,   732,   738,   741,   749,
     752,   760,   761,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   774,   777,   786,   789,   797,   800,   808,   811,
     819,   822,   830,   833,   841,   844,   849,   857,   860,   865,
     870,   875,   883,   886,   891,   899,   902,   907,   915,   918,
     923,   928,   936,   939,   947,   950,   954,   958,   962,   966,
     973,   974,   975,   976,   977,   978,   982,   985,   990,   995,
     999,  1004,  1009,  1013,  1020,  1023,  1026,  1029,  1035,  1038,
    1046,  1050,  1057,  1058,  1059,  1060,  1061
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
  "ELLIPSIS", "PREP", "NEWLINE", "END", "ERROR", "UMINUS", "UPLUS",
  "IF_WITHOUT_ELSE", "$accept", "program", "translation_unit",
  "external_declaration", "preprocessor_directive", "function_definition",
  "declaration", "declaration_specifiers", "storage_class_specifier",
  "type_specifier", "type_keyword", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
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

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     253,  -211,  -211,  -211,   -47,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
     -31,   -22,  -211,    40,   253,  -211,  -211,  -211,  -211,   -27,
    1490,  1490,  -211,  -211,   -43,  -211,   -39,    -5,     5,   -30,
     -14,  -211,   -21,  -211,  -211,  -211,     2,  -211,   -54,  -211,
    -211,    -6,   174,   449,  -211,     5,   -16,   906,   -14,    66,
     -60,  -211,  -211,  -211,   -22,  1111,  -211,   174,   -22,   821,
    -211,     8,  1324,    37,    13,   624,    43,    86,    49,  1243,
    1355,    79,    81,  -211,  -211,    55,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  1405,  1405,  -211,  -211,  -211,  -211,   875,
    -211,  -211,   -27,  -211,   552,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,    10,  -211,  -211,   -66,    67,   101,   114,   127,
      83,   130,   102,   133,   159,  -211,   447,  1324,    30,  -211,
     155,  -211,  -211,  1490,  -211,  -211,   113,   -58,  1324,   -14,
    -211,  -211,   170,  1111,  -211,  -211,   848,   104,  -211,  -211,
    -211,  -211,  -211,   137,  -211,   624,   208,   741,   148,  1324,
    -211,   115,   875,  -211,  1324,  1324,   624,  1324,  -211,  -211,
     -33,   144,    16,  -211,  -211,  -211,  1324,  1324,  1324,  1324,
    1324,  1324,  1324,  1324,  1324,  1324,  1324,  1324,  1324,  1324,
    1324,  1324,  1324,  1324,  1324,  1324,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  1324,  -211,  -211,
    -211,  -211,   192,   193,  1162,  1324,  -211,   -42,    17,  -211,
    -211,  -211,  -211,  -211,  -211,   -51,  -211,  -211,   -22,   624,
    -211,   150,  -211,    15,  -211,  1274,   152,  -211,    19,  -211,
     154,    28,    31,  -211,   392,   957,    22,  -211,    35,  1324,
    -211,  -211,    67,   -48,   101,   114,   127,    83,   130,   130,
     102,   102,   102,   102,   133,   133,   159,   159,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,    39,   -61,   337,  -211,
     -40,  -211,   301,  -211,  1059,  -211,  -211,  -211,  1324,   160,
     196,  1193,   624,   624,  -211,   624,   624,  -211,    41,   162,
    -211,   163,    35,   710,  1008,  -211,  1324,  1324,  -211,  -211,
    -211,  -211,  -211,  -211,    47,  1324,   168,   624,    54,  -211,
     259,  -211,  -211,  -211,  -211,  -211,  -211,    85,  -211,   179,
    -211,  -211,   177,   182,  1324,  -211,   624,   624,  -211,  -211,
    -211,   182,  -211,  -211
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    21,    26,    31,     0,    19,    30,    28,    29,    20,
      27,    32,    18,    38,    17,    39,    33,    25,    34,    61,
      59,     0,     8,     0,     2,     3,     7,     5,     6,     0,
      13,    15,    22,    23,     0,    24,     0,     0,    58,    48,
       0,    60,     0,     1,     4,    12,     0,    53,    55,    14,
      16,    37,     0,     0,    10,    57,    65,     0,     0,    51,
       0,    49,    62,    11,     0,     0,     9,     0,     0,     0,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,   206,   194,   202,   203,   204,   198,
     182,   183,   181,     0,     0,   185,   180,   184,   109,     0,
      93,    97,     0,   101,     0,    95,    98,    99,   100,   102,
     103,   104,     0,   127,   129,   142,   144,   146,   148,   150,
     152,   154,   157,   162,   165,   168,   172,     0,   174,   186,
     196,   195,    67,     0,   194,    64,     0,     0,     0,     0,
      47,    54,    55,     0,    56,    88,     0,     0,    43,    45,
      36,    41,   124,     0,   123,     0,     0,     0,     0,     0,
     126,     0,     0,   178,     0,     0,     0,     0,   175,   176,
      86,     0,     0,    94,    96,   108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,     0,   177,   172,
     192,   193,     0,     0,     0,     0,   199,    73,     0,    68,
      63,    46,    52,    50,    91,     0,    35,    42,     0,     0,
     107,     0,   119,     0,   118,     0,     0,   122,     0,   125,
       0,     0,     0,   105,     0,     0,    74,    87,    76,     0,
     197,   128,   145,     0,   147,   149,   151,   153,   155,   156,
     158,   159,   160,   161,   163,   164,   166,   167,   169,   170,
     171,   130,   191,   190,   189,   200,     0,     0,     0,    71,
      74,    72,     0,    66,     0,    89,    44,   106,     0,    61,
       0,     0,     0,     0,   179,     0,     0,    82,     0,     0,
      78,     0,    75,     0,     0,   173,     0,     0,   188,   187,
      70,    69,    90,    92,     0,     0,     0,     0,     0,   117,
     110,   112,   113,    83,    77,    79,    84,     0,    80,     0,
     143,   201,     0,   120,     0,   115,     0,     0,    85,    81,
     114,   121,   116,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,   263,  -211,  -211,   -45,    25,  -211,   -41,
    -211,  -211,  -211,   221,   -62,  -211,    62,  -211,   233,   153,
    -211,   229,     0,   -18,   -32,  -211,  -124,    12,  -150,  -210,
     134,  -137,  -211,    -4,  -211,   191,   -74,  -211,  -139,  -211,
    -211,  -211,  -211,  -211,   -76,   -53,  -211,    -9,  -211,   121,
     120,   122,   119,   123,    46,    48,    51,    53,  -100,   -17,
    -211,  -211,  -211,  -211,  -211,  -211
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    23,    24,    25,    26,    27,    28,   217,    30,    31,
      32,    33,    34,    69,    70,   147,   148,    35,    60,    61,
      46,    47,   142,    37,    38,   133,   298,   219,   299,   248,
     171,   144,   225,   103,   104,   105,   106,   107,   108,   109,
     110,   235,   236,   111,   112,   113,   207,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   276,   131
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,   156,    41,   161,   136,    55,   224,   151,   101,   218,
      39,    68,   145,    65,    51,    19,   177,    19,   234,   153,
     247,    42,    20,   172,    36,    29,    68,   208,    68,    48,
      19,    20,    54,    20,   178,    19,   302,    20,   176,   139,
      43,   139,    20,    59,    66,   140,   309,   221,   284,    29,
      53,   176,    19,   306,   285,    49,    50,    40,   170,   101,
     278,    52,   278,   163,   245,    53,   245,   281,   149,   244,
     302,    45,   289,   245,    58,    21,   168,   169,   102,    20,
      21,   230,    62,   238,   151,   222,   172,   132,   241,   242,
     145,   172,   243,   268,   269,   270,   291,    21,    67,   290,
      63,    64,   253,   210,   211,    68,   152,    56,   175,   176,
     209,    57,   232,    45,   155,   176,   282,    21,   176,   250,
     283,   170,   293,   251,   244,   212,   213,   176,   245,   102,
     176,   295,   214,   138,   296,   154,   215,   303,   307,   277,
     282,   304,   308,   158,   323,   157,   176,   313,   179,   305,
     332,   159,   246,   176,   271,   287,   166,   336,   183,   184,
     209,   275,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   327,
       2,   164,   233,   165,   282,     3,   180,     4,   338,     6,
     189,   190,   301,     7,     8,   191,   192,    10,    11,   280,
     181,    13,   227,   228,    15,    16,    17,   185,   186,   187,
     188,   182,   314,   239,   176,   318,   216,   279,   319,   320,
     220,   321,   322,   193,   194,   195,   246,    18,   149,   258,
     259,   145,   209,   260,   261,   262,   263,    65,   229,   333,
     264,   265,   231,   335,   266,   267,   237,   249,    55,   272,
     273,   329,   288,   316,   331,   292,     1,   294,   341,     2,
     280,   315,   342,   343,     3,   324,     4,     5,     6,   334,
     325,   337,     7,     8,     9,   340,    10,    11,    42,    12,
      13,   176,    14,    15,    16,    17,   339,    44,   146,   209,
     286,   137,   223,   141,   311,   174,   240,   330,   252,   254,
     256,     0,   255,     0,     1,   257,    18,     2,     0,     0,
      19,     0,     3,     0,     4,     5,     6,    20,     0,     0,
       7,     8,     9,     0,    10,    11,     0,    12,    13,     0,
      14,    15,    16,    17,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     2,     0,     0,     0,     0,     3,     0,
       4,     5,     6,     0,    18,    21,     7,     8,     9,     0,
      10,    11,    22,    12,    13,     0,    14,    15,    16,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,    19,     1,     0,     0,     2,     0,
       0,    20,     0,     3,     0,     4,     5,     6,     0,   310,
       0,     7,     8,     9,     0,    10,    11,     0,    12,    13,
       0,    14,    15,    16,    17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   278,
     297,     0,     0,   245,     0,    18,     0,     0,     0,     0,
       0,     0,     1,    71,    72,     2,    20,    73,    74,    75,
       3,     0,     4,     5,     6,    76,    77,    78,     7,     8,
       9,    79,    10,    11,    80,    12,    13,    81,    14,    15,
      16,    17,     0,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   244,   297,     0,     0,   245,     0,
       0,     0,    18,    83,    84,     0,    85,    86,    87,    88,
      89,    90,    91,    92,   196,   197,   198,   199,   200,   201,
       0,     0,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,    95,    96,     0,     0,    97,   202,   203,   204,
     205,   206,     0,     0,     0,     0,     0,    98,     0,     0,
       0,    99,     0,    53,   100,     1,    71,    72,     2,     0,
      73,    74,    75,     3,     0,     4,     5,     6,    76,    77,
      78,     7,     8,     9,    79,    10,    11,    80,    12,    13,
      81,    14,    15,    16,    17,     0,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    83,    84,     0,    85,
      86,    87,    88,    89,    90,    91,    92,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    94,     0,    71,    72,
       0,     0,    73,    74,    75,    95,    96,     0,     0,    97,
      76,    77,    78,     0,     0,     0,    79,     0,     0,    80,
      98,     0,    81,     0,    99,     0,    53,   173,    82,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,    84,
       0,    85,    86,    87,    88,    89,    90,    91,    92,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    96,     0,
       0,    97,     0,     1,     0,     0,     2,     0,     0,     0,
       0,     3,    98,     4,     5,     6,    99,     0,    53,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,    14,
      15,    16,    17,     0,     1,     0,     0,     2,     0,     0,
       0,     0,     3,     0,     4,     5,     6,     0,     0,     0,
       7,     8,     9,    18,    10,    11,    80,    12,    13,     0,
      14,    15,    16,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,    83,    84,     0,   134,    86,
      87,    88,    89,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,   326,    93,    94,     0,     0,     0,     0,
       0,     0,     0,     0,    95,    96,     0,     2,    97,     0,
       0,     0,     3,     0,     4,     0,     6,     0,     0,    98,
       7,     8,     0,    99,    10,    11,     0,     0,    13,     0,
       0,    15,    16,    17,     2,     0,     0,     0,     0,     3,
       0,     4,     0,     6,     0,     0,     0,     7,     8,     0,
       0,    10,    11,     0,    18,    13,     0,     0,    15,    16,
      17,     2,     0,     0,     0,     0,     3,     0,     4,     0,
       6,     0,     0,     0,     7,     8,     0,     0,    10,    11,
      80,    18,    13,     0,     0,    15,    16,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   150,     0,    18,    83,
      84,    80,   134,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    94,
       0,     0,     0,   226,     0,     0,     0,     0,    95,    96,
      83,    84,    97,   134,    86,    87,    88,    89,    90,    91,
      92,     0,     0,     0,     0,     0,     0,    99,     0,    93,
      94,     0,    80,     0,     0,     0,     0,     0,     0,    95,
      96,     0,     0,    97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,     0,
       0,    83,    84,   135,   134,    86,    87,    88,    89,    90,
      91,    92,     0,     0,     0,     0,     0,     0,     0,     0,
      93,    94,     0,    80,     0,     0,     0,     0,     0,     0,
      95,    96,     0,     0,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
       0,     0,    83,    84,   300,   134,    86,    87,    88,    89,
      90,    91,    92,     0,     0,     0,     0,     0,     0,     0,
       0,    93,    94,     0,    80,     0,     0,     0,     0,     0,
       0,    95,    96,     0,     0,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      99,     0,     0,    83,    84,   328,   134,    86,    87,    88,
      89,    90,    91,    92,     0,     0,     0,     0,     0,     0,
       0,     0,    93,    94,     0,     0,    80,     0,     0,     0,
       0,     0,    95,    96,     0,     0,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,     0,   143,   312,    83,    84,     0,   134,    86,
      87,    88,    89,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,    93,    94,     0,    80,     0,     0,
       0,     0,     0,     0,    95,    96,     0,     0,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,   143,    83,    84,    80,   134,
      86,    87,    88,    89,    90,    91,    92,     0,     0,     0,
       0,     0,     0,     0,     0,    93,    94,     0,     0,     0,
       0,     0,     0,     0,     0,    95,    96,    83,    84,    97,
     134,    86,    87,    88,    89,    90,    91,    92,     0,     0,
       0,     0,     0,     0,    99,   274,    93,    94,    80,     0,
       0,     0,     0,     0,     0,     0,    95,    96,     0,     0,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,   317,    83,    84,    80,
     134,    86,    87,    88,    89,    90,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,    93,    94,     0,     0,
       0,     0,     0,     0,     0,     0,    95,    96,    83,    84,
      97,   134,    86,    87,    88,    89,    90,    91,    92,     0,
       0,   160,     0,     0,     0,    99,     0,    93,    94,    80,
       0,     0,     0,     0,     0,     0,     0,    95,    96,     0,
       0,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,     0,     0,     0,    99,     0,    83,    84,
      80,   134,    86,    87,    88,    89,    90,    91,    92,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    96,    83,
      84,    97,   134,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,    99,     0,    93,    94,
      80,     0,     0,     0,     0,     0,     0,     0,    95,    96,
       0,     0,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   162,     0,    83,
      84,     0,   134,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,    95,    96,
       0,     0,    97,     1,     0,     0,     2,     0,     0,     0,
       0,     3,     0,     4,     5,     6,     0,   167,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,    14,
      15,    16,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       0,    75,    20,    79,    57,    37,   143,    69,    53,   133,
      57,    52,    65,    67,    57,    57,    82,    57,   157,    72,
     170,    21,    64,    99,    24,     0,    67,   127,    69,    29,
      57,    64,    36,    64,   100,    57,   246,    64,    99,    99,
       0,    99,    64,    57,    48,   105,   107,   105,    99,    24,
     104,    99,    57,   101,   105,    30,    31,   104,    99,   104,
     102,   104,   102,    80,   106,   104,   106,   217,    68,   102,
     280,    98,    57,   106,   104,   102,    93,    94,    53,    64,
     102,   155,   103,   159,   146,   138,   162,   103,   164,   165,
     143,   167,   166,   193,   194,   195,   235,   102,   104,    84,
      98,    99,   178,    73,    74,   146,    98,   102,    98,    99,
     127,   106,   157,    98,   101,    99,    99,   102,    99,   103,
     103,   162,   103,   176,   102,    95,    96,    99,   106,   104,
      99,   103,   102,    67,   103,    98,   106,   102,    99,   215,
      99,   106,   103,    57,   103,   102,    99,   284,    81,   249,
     103,   102,   170,    99,   207,   229,   101,   103,    75,    76,
     177,   214,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   303,
       6,   102,   157,   102,    99,    11,    85,    13,   103,    15,
      88,    89,   245,    19,    20,    62,    63,    23,    24,   217,
      86,    27,    98,    99,    30,    31,    32,    77,    78,    79,
      80,    84,   288,    98,    99,   291,    61,   217,   292,   293,
     107,   295,   296,    64,    65,    66,   244,    53,   228,   183,
     184,   284,   249,   185,   186,   187,   188,    67,   101,   315,
     189,   190,    34,   317,   191,   192,    98,   103,   280,    57,
      57,   304,   102,    57,   307,   103,     3,   103,   334,     6,
     278,   101,   336,   337,    11,   103,    13,    14,    15,   101,
     107,    12,    19,    20,    21,    98,    23,    24,   278,    26,
      27,    99,    29,    30,    31,    32,   107,    24,    67,   306,
     228,    58,   139,    64,   282,   104,   162,   306,   177,   179,
     181,    -1,   180,    -1,     3,   182,    53,     6,    -1,    -1,
      57,    -1,    11,    -1,    13,    14,    15,    64,    -1,    -1,
      19,    20,    21,    -1,    23,    24,    -1,    26,    27,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      13,    14,    15,    -1,    53,   102,    19,    20,    21,    -1,
      23,    24,   109,    26,    27,    -1,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    57,     3,    -1,    -1,     6,    -1,
      -1,    64,    -1,    11,    -1,    13,    14,    15,    -1,   108,
      -1,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,    -1,    -1,   106,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,    64,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,    -1,    -1,   106,    -1,
      -1,    -1,    53,    54,    55,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    67,    68,    69,    70,    71,    72,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    -1,    87,    90,    91,    92,
      93,    94,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,   102,    -1,   104,   105,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,     4,     5,
      -1,    -1,     8,     9,    10,    83,    84,    -1,    -1,    87,
      16,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      98,    -1,    28,    -1,   102,    -1,   104,   105,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,
      -1,    87,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    98,    13,    14,    15,   102,    -1,   104,    19,
      20,    21,    -1,    23,    24,    -1,    26,    27,    -1,    29,
      30,    31,    32,    -1,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    13,    14,    15,    -1,    -1,    -1,
      19,    20,    21,    53,    23,    24,    25,    26,    27,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    -1,     6,    87,    -1,
      -1,    -1,    11,    -1,    13,    -1,    15,    -1,    -1,    98,
      19,    20,    -1,   102,    23,    24,    -1,    -1,    27,    -1,
      -1,    30,    31,    32,     6,    -1,    -1,    -1,    -1,    11,
      -1,    13,    -1,    15,    -1,    -1,    -1,    19,    20,    -1,
      -1,    23,    24,    -1,    53,    27,    -1,    -1,    30,    31,
      32,     6,    -1,    -1,    -1,    -1,    11,    -1,    13,    -1,
      15,    -1,    -1,    -1,    19,    20,    -1,    -1,    23,    24,
      25,    53,    27,    -1,    -1,    30,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,    53,    54,
      55,    25,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,    83,    84,
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
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    11,    13,    14,    15,    19,    20,    21,
      23,    24,    26,    27,    29,    30,    31,    32,    53,    57,
      64,   102,   109,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   133,   138,   139,   140,    57,
     104,   139,   138,     0,   119,    98,   136,   137,   138,   123,
     123,    57,   104,   104,   149,   140,   102,   106,   104,    57,
     134,   135,   103,    98,    99,    67,   149,   104,   125,   129,
     130,     4,     5,     8,     9,    10,    16,    17,    18,    22,
      25,    28,    34,    54,    55,    57,    58,    59,    60,    61,
      62,    63,    64,    73,    74,    83,    84,    87,    98,   102,
     105,   122,   123,   149,   150,   151,   152,   153,   154,   155,
     156,   159,   160,   161,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   181,   103,   141,    57,   107,   161,   134,    67,    99,
     105,   137,   138,   104,   147,   161,   129,   131,   132,   138,
     105,   130,    98,   161,    98,   101,   152,   102,    57,   102,
      98,   160,   102,   175,   102,   102,   101,   102,   175,   175,
     125,   146,   160,   105,   151,    98,    99,    82,   100,    81,
      85,    86,    84,    75,    76,    77,    78,    79,    80,    88,
      89,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    90,    91,    92,    93,    94,   162,   174,   175,
      73,    74,    95,    96,   102,   106,    61,   123,   142,   143,
     107,   105,   161,   135,   147,   148,   105,    98,    99,   101,
     152,    34,   122,   123,   154,   157,   158,    98,   160,    98,
     146,   160,   160,   152,   102,   106,   139,   144,   145,   103,
     103,   161,   165,   160,   166,   167,   168,   169,   170,   170,
     171,   171,   171,   171,   172,   172,   173,   173,   174,   174,
     174,   161,    57,    57,   103,   161,   180,   160,   102,   138,
     139,   144,    99,   103,    99,   105,   132,   152,   102,    57,
      84,   154,   103,   103,   103,   103,   103,   103,   142,   144,
     107,   161,   145,   102,   106,   174,   101,    99,   103,   107,
     108,   143,   105,   147,   160,   101,    57,   103,   160,   152,
     152,   152,   152,   103,   103,   107,   103,   142,   107,   161,
     163,   161,   103,   160,   101,   152,   103,    12,   103,   107,
      98,   160,   152,   152
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   116,   117,   118,   118,   119,   119,   119,   120,   121,
     121,   122,   122,   123,   123,   123,   123,   124,   124,   124,
     124,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   127,   128,   128,
     129,   129,   130,   131,   131,   132,   133,   133,   133,   134,
     134,   135,   135,   136,   136,   137,   137,   138,   138,   139,
     139,   140,   140,   140,   140,   141,   140,   140,   142,   142,
     142,   143,   143,   143,   144,   144,   144,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   146,   146,   147,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   151,   152,
     152,   152,   152,   152,   152,   153,   153,   153,   154,   154,
     155,   155,   155,   156,   156,   156,   156,   156,   157,   157,
     158,   158,   159,   159,   159,   159,   159,   160,   160,   161,
     161,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   163,   163,   164,   164,   165,   165,   166,   166,
     167,   167,   168,   168,   169,   169,   169,   170,   170,   170,
     170,   170,   171,   171,   171,   172,   172,   172,   173,   173,
     173,   173,   174,   174,   175,   175,   175,   175,   175,   175,
     176,   176,   176,   176,   176,   176,   177,   177,   177,   177,
     177,   177,   177,   177,   178,   178,   178,   178,   179,   179,
     180,   180,   181,   181,   181,   181,   181
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       2,     3,     2,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     4,     2,     1,     1,
       1,     2,     3,     1,     3,     1,     5,     4,     2,     1,
       3,     1,     3,     1,     3,     1,     3,     2,     1,     1,
       2,     1,     3,     4,     3,     0,     5,     3,     1,     3,
       3,     2,     2,     1,     1,     2,     1,     3,     2,     3,
       3,     4,     2,     3,     3,     4,     1,     2,     1,     3,
       4,     1,     3,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     3,     2,     1,
       5,     7,     5,     5,     7,     6,     7,     5,     1,     1,
       4,     5,     3,     2,     2,     3,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     4,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     3,
       3,     3,     2,     2,     1,     1,     1,     3,     1,     2,
       1,     3,     1,     1,     1,     1,     1
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
#line 163 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1834 "build/parser.tab.c"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 169 "src/parser.y"
                         {
        (yyval.node) = create_node("TranslationUnit");
        (yyval.node)->addChild((yyvsp[0].node));
        root = (yyval.node);
    }
#line 1844 "build/parser.tab.c"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 174 "src/parser.y"
                                            {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1853 "build/parser.tab.c"
    break;

  case 5: /* external_declaration: function_definition  */
#line 181 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1861 "build/parser.tab.c"
    break;

  case 6: /* external_declaration: declaration  */
#line 184 "src/parser.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1869 "build/parser.tab.c"
    break;

  case 7: /* external_declaration: preprocessor_directive  */
#line 187 "src/parser.y"
                             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1877 "build/parser.tab.c"
    break;

  case 8: /* preprocessor_directive: PREP  */
#line 193 "src/parser.y"
         { (yyval.node) = create_node("Preprocessor", (yyvsp[0].str)); }
#line 1883 "build/parser.tab.c"
    break;

  case 9: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 197 "src/parser.y"
                                                         {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 1895 "build/parser.tab.c"
    break;

  case 10: /* function_definition: declarator compound_statement  */
#line 204 "src/parser.y"
                                    {
        (yyval.node) = create_node("FunctionDefinition");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
        in_typedef_declaration = 0;
    }
#line 1906 "build/parser.tab.c"
    break;

  case 11: /* declaration: declaration_specifiers init_declarator_list SEMI  */
#line 213 "src/parser.y"
                                                     {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        in_typedef_declaration = 0;
    }
#line 1917 "build/parser.tab.c"
    break;

  case 12: /* declaration: declaration_specifiers SEMI  */
#line 219 "src/parser.y"
                                  {
        (yyval.node) = create_node("Declaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        in_typedef_declaration = 0;
    }
#line 1927 "build/parser.tab.c"
    break;

  case 13: /* declaration_specifiers: storage_class_specifier  */
#line 227 "src/parser.y"
                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1936 "build/parser.tab.c"
    break;

  case 14: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 231 "src/parser.y"
                                                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1946 "build/parser.tab.c"
    break;

  case 15: /* declaration_specifiers: type_specifier  */
#line 236 "src/parser.y"
                     {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1955 "build/parser.tab.c"
    break;

  case 16: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 240 "src/parser.y"
                                            {
        (yyval.node) = create_node("DeclarationSpecifiers");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 1965 "build/parser.tab.c"
    break;

  case 17: /* storage_class_specifier: TYPEDEF  */
#line 248 "src/parser.y"
            {
        (yyval.node) = create_node("StorageClass", "typedef");
        in_typedef_declaration = 1;
    }
#line 1974 "build/parser.tab.c"
    break;

  case 18: /* storage_class_specifier: STATIC  */
#line 252 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "static"); }
#line 1980 "build/parser.tab.c"
    break;

  case 19: /* storage_class_specifier: EXTERN  */
#line 253 "src/parser.y"
             { (yyval.node) = create_node("StorageClass", "extern"); }
#line 1986 "build/parser.tab.c"
    break;

  case 20: /* storage_class_specifier: REGISTER  */
#line 254 "src/parser.y"
               { (yyval.node) = create_node("StorageClass", "register"); }
#line 1992 "build/parser.tab.c"
    break;

  case 21: /* storage_class_specifier: AUTO  */
#line 255 "src/parser.y"
           { (yyval.node) = create_node("StorageClass", "auto"); }
#line 1998 "build/parser.tab.c"
    break;

  case 22: /* type_specifier: type_keyword  */
#line 259 "src/parser.y"
                 {
        (yyval.node) = create_node("TypeSpecifier", (yyvsp[0].str));
        strcpy(current_type, (yyvsp[0].str));
    }
#line 2007 "build/parser.tab.c"
    break;

  case 23: /* type_specifier: struct_or_union_specifier  */
#line 263 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2013 "build/parser.tab.c"
    break;

  case 24: /* type_specifier: enum_specifier  */
#line 264 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2019 "build/parser.tab.c"
    break;

  case 25: /* type_keyword: VOID  */
#line 268 "src/parser.y"
         { (yyval.str) = strdup("void"); }
#line 2025 "build/parser.tab.c"
    break;

  case 26: /* type_keyword: CHAR  */
#line 269 "src/parser.y"
           { (yyval.str) = strdup("char"); }
#line 2031 "build/parser.tab.c"
    break;

  case 27: /* type_keyword: SHORT  */
#line 270 "src/parser.y"
            { (yyval.str) = strdup("short"); }
#line 2037 "build/parser.tab.c"
    break;

  case 28: /* type_keyword: INT  */
#line 271 "src/parser.y"
          { (yyval.str) = strdup("int"); }
#line 2043 "build/parser.tab.c"
    break;

  case 29: /* type_keyword: LONG  */
#line 272 "src/parser.y"
           { (yyval.str) = strdup("long"); }
#line 2049 "build/parser.tab.c"
    break;

  case 30: /* type_keyword: FLOAT  */
#line 273 "src/parser.y"
            { (yyval.str) = strdup("float"); }
#line 2055 "build/parser.tab.c"
    break;

  case 31: /* type_keyword: DOUBLE  */
#line 274 "src/parser.y"
             { (yyval.str) = strdup("double"); }
#line 2061 "build/parser.tab.c"
    break;

  case 32: /* type_keyword: SIGNED  */
#line 275 "src/parser.y"
             { (yyval.str) = strdup("signed"); }
#line 2067 "build/parser.tab.c"
    break;

  case 33: /* type_keyword: UNSIGNED  */
#line 276 "src/parser.y"
               { (yyval.str) = strdup("unsigned"); }
#line 2073 "build/parser.tab.c"
    break;

  case 34: /* type_keyword: BOOL  */
#line 277 "src/parser.y"
           { (yyval.str) = strdup("bool"); }
#line 2079 "build/parser.tab.c"
    break;

  case 35: /* struct_or_union_specifier: struct_or_union ID LBRACE struct_declaration_list RBRACE  */
#line 281 "src/parser.y"
                                                             {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-4].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2090 "build/parser.tab.c"
    break;

  case 36: /* struct_or_union_specifier: struct_or_union LBRACE struct_declaration_list RBRACE  */
#line 287 "src/parser.y"
                                                            {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2100 "build/parser.tab.c"
    break;

  case 37: /* struct_or_union_specifier: struct_or_union ID  */
#line 292 "src/parser.y"
                         {
        (yyval.node) = create_node("StructOrUnionSpecifier");
        (yyval.node)->addChild(create_node("StructOrUnion", (yyvsp[-1].str)));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 2110 "build/parser.tab.c"
    break;

  case 38: /* struct_or_union: STRUCT  */
#line 300 "src/parser.y"
           { (yyval.str) = strdup("struct"); }
#line 2116 "build/parser.tab.c"
    break;

  case 39: /* struct_or_union: UNION  */
#line 301 "src/parser.y"
            { (yyval.str) = strdup("union"); }
#line 2122 "build/parser.tab.c"
    break;

  case 40: /* struct_declaration_list: struct_declaration  */
#line 305 "src/parser.y"
                       {
        (yyval.node) = create_node("StructDeclarationList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2131 "build/parser.tab.c"
    break;

  case 41: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 309 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2140 "build/parser.tab.c"
    break;

  case 42: /* struct_declaration: type_specifier struct_declarator_list SEMI  */
#line 316 "src/parser.y"
                                               {
        (yyval.node) = create_node("StructDeclaration");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2150 "build/parser.tab.c"
    break;

  case 43: /* struct_declarator_list: struct_declarator  */
#line 324 "src/parser.y"
                      {
        (yyval.node) = create_node("StructDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2159 "build/parser.tab.c"
    break;

  case 44: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 328 "src/parser.y"
                                                     {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2168 "build/parser.tab.c"
    break;

  case 45: /* struct_declarator: declarator  */
#line 335 "src/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2174 "build/parser.tab.c"
    break;

  case 46: /* enum_specifier: ENUM ID LBRACE enumerator_list RBRACE  */
#line 339 "src/parser.y"
                                          {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-3].str)));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2184 "build/parser.tab.c"
    break;

  case 47: /* enum_specifier: ENUM LBRACE enumerator_list RBRACE  */
#line 344 "src/parser.y"
                                         {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2193 "build/parser.tab.c"
    break;

  case 48: /* enum_specifier: ENUM ID  */
#line 348 "src/parser.y"
              {
        (yyval.node) = create_node("EnumSpecifier");
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 2202 "build/parser.tab.c"
    break;

  case 49: /* enumerator_list: enumerator  */
#line 355 "src/parser.y"
               {
        (yyval.node) = create_node("EnumeratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2211 "build/parser.tab.c"
    break;

  case 50: /* enumerator_list: enumerator_list COMMA enumerator  */
#line 359 "src/parser.y"
                                       {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2220 "build/parser.tab.c"
    break;

  case 51: /* enumerator: ID  */
#line 366 "src/parser.y"
       {
        (yyval.node) = create_node("Enumerator", (yyvsp[0].str));
    }
#line 2228 "build/parser.tab.c"
    break;

  case 52: /* enumerator: ID ASSIGN assignment_expression  */
#line 369 "src/parser.y"
                                      {
        (yyval.node) = create_node("Enumerator", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2237 "build/parser.tab.c"
    break;

  case 53: /* init_declarator_list: init_declarator  */
#line 376 "src/parser.y"
                    {
        (yyval.node) = create_node("InitDeclaratorList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2246 "build/parser.tab.c"
    break;

  case 54: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 380 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2255 "build/parser.tab.c"
    break;

  case 55: /* init_declarator: declarator  */
#line 387 "src/parser.y"
               {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2264 "build/parser.tab.c"
    break;

  case 56: /* init_declarator: declarator ASSIGN initializer  */
#line 391 "src/parser.y"
                                    {
        (yyval.node) = create_node("InitDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2274 "build/parser.tab.c"
    break;

  case 57: /* declarator: pointer direct_declarator  */
#line 399 "src/parser.y"
                              {
        (yyval.node) = create_node("Declarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2284 "build/parser.tab.c"
    break;

  case 58: /* declarator: direct_declarator  */
#line 404 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2292 "build/parser.tab.c"
    break;

  case 59: /* pointer: MUL  */
#line 410 "src/parser.y"
        {
        (yyval.node) = create_node("Pointer");
    }
#line 2300 "build/parser.tab.c"
    break;

  case 60: /* pointer: MUL pointer  */
#line 413 "src/parser.y"
                  {
        (yyval.node) = create_node("Pointer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2309 "build/parser.tab.c"
    break;

  case 61: /* direct_declarator: ID  */
#line 420 "src/parser.y"
       {
        (yyval.node) = create_node("DirectDeclarator", (yyvsp[0].str));
    }
#line 2317 "build/parser.tab.c"
    break;

  case 62: /* direct_declarator: LPAREN declarator RPAREN  */
#line 423 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2325 "build/parser.tab.c"
    break;

  case 63: /* direct_declarator: direct_declarator LBRACKET assignment_expression RBRACKET  */
#line 426 "src/parser.y"
                                                                {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2335 "build/parser.tab.c"
    break;

  case 64: /* direct_declarator: direct_declarator LBRACKET RBRACKET  */
#line 431 "src/parser.y"
                                          {
        (yyval.node) = create_node("ArrayDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2344 "build/parser.tab.c"
    break;

  case 65: /* $@1: %empty  */
#line 435 "src/parser.y"
                               {
        in_function_params = 1;
    }
#line 2352 "build/parser.tab.c"
    break;

  case 66: /* direct_declarator: direct_declarator LPAREN $@1 parameter_list RPAREN  */
#line 437 "src/parser.y"
                            {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-1].node));
        in_function_params = 0;
    }
#line 2363 "build/parser.tab.c"
    break;

  case 67: /* direct_declarator: direct_declarator LPAREN RPAREN  */
#line 443 "src/parser.y"
                                      {
        (yyval.node) = create_node("FunctionDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
        in_function_params = 0;
    }
#line 2373 "build/parser.tab.c"
    break;

  case 68: /* parameter_list: parameter_declaration  */
#line 451 "src/parser.y"
                          {
        (yyval.node) = create_node("ParameterList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2382 "build/parser.tab.c"
    break;

  case 69: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 455 "src/parser.y"
                                                 {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2391 "build/parser.tab.c"
    break;

  case 70: /* parameter_list: parameter_list COMMA ELLIPSIS  */
#line 459 "src/parser.y"
                                    {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild(create_node("Ellipsis"));
    }
#line 2400 "build/parser.tab.c"
    break;

  case 71: /* parameter_declaration: declaration_specifiers declarator  */
#line 466 "src/parser.y"
                                      {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2410 "build/parser.tab.c"
    break;

  case 72: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 471 "src/parser.y"
                                                 {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2420 "build/parser.tab.c"
    break;

  case 73: /* parameter_declaration: declaration_specifiers  */
#line 476 "src/parser.y"
                             {
        (yyval.node) = create_node("ParameterDeclaration");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2429 "build/parser.tab.c"
    break;

  case 74: /* abstract_declarator: pointer  */
#line 483 "src/parser.y"
            {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2438 "build/parser.tab.c"
    break;

  case 75: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 487 "src/parser.y"
                                         {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2448 "build/parser.tab.c"
    break;

  case 76: /* abstract_declarator: direct_abstract_declarator  */
#line 492 "src/parser.y"
                                 {
        (yyval.node) = create_node("AbstractDeclarator");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2457 "build/parser.tab.c"
    break;

  case 77: /* direct_abstract_declarator: LPAREN abstract_declarator RPAREN  */
#line 499 "src/parser.y"
                                      {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2465 "build/parser.tab.c"
    break;

  case 78: /* direct_abstract_declarator: LBRACKET RBRACKET  */
#line 502 "src/parser.y"
                        {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
    }
#line 2473 "build/parser.tab.c"
    break;

  case 79: /* direct_abstract_declarator: LBRACKET assignment_expression RBRACKET  */
#line 505 "src/parser.y"
                                              {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2482 "build/parser.tab.c"
    break;

  case 80: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET RBRACKET  */
#line 509 "src/parser.y"
                                                   {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2491 "build/parser.tab.c"
    break;

  case 81: /* direct_abstract_declarator: direct_abstract_declarator LBRACKET assignment_expression RBRACKET  */
#line 513 "src/parser.y"
                                                                         {
        (yyval.node) = create_node("ArrayAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2501 "build/parser.tab.c"
    break;

  case 82: /* direct_abstract_declarator: LPAREN RPAREN  */
#line 518 "src/parser.y"
                    {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
    }
#line 2509 "build/parser.tab.c"
    break;

  case 83: /* direct_abstract_declarator: LPAREN parameter_list RPAREN  */
#line 521 "src/parser.y"
                                   {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2518 "build/parser.tab.c"
    break;

  case 84: /* direct_abstract_declarator: direct_abstract_declarator LPAREN RPAREN  */
#line 525 "src/parser.y"
                                               {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2527 "build/parser.tab.c"
    break;

  case 85: /* direct_abstract_declarator: direct_abstract_declarator LPAREN parameter_list RPAREN  */
#line 529 "src/parser.y"
                                                              {
        (yyval.node) = create_node("FunctionAbstractDeclarator");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2537 "build/parser.tab.c"
    break;

  case 86: /* type_name: type_specifier  */
#line 537 "src/parser.y"
                   {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2546 "build/parser.tab.c"
    break;

  case 87: /* type_name: type_specifier abstract_declarator  */
#line 541 "src/parser.y"
                                         {
        (yyval.node) = create_node("TypeName");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2556 "build/parser.tab.c"
    break;

  case 88: /* initializer: assignment_expression  */
#line 549 "src/parser.y"
                          {
        (yyval.node) = create_node("Initializer");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2565 "build/parser.tab.c"
    break;

  case 89: /* initializer: LBRACE initializer_list RBRACE  */
#line 553 "src/parser.y"
                                     {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2574 "build/parser.tab.c"
    break;

  case 90: /* initializer: LBRACE initializer_list COMMA RBRACE  */
#line 557 "src/parser.y"
                                           {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2583 "build/parser.tab.c"
    break;

  case 91: /* initializer_list: initializer  */
#line 564 "src/parser.y"
                {
        (yyval.node) = create_node("InitializerList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2592 "build/parser.tab.c"
    break;

  case 92: /* initializer_list: initializer_list COMMA initializer  */
#line 568 "src/parser.y"
                                         {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2601 "build/parser.tab.c"
    break;

  case 93: /* compound_statement: LBRACE RBRACE  */
#line 575 "src/parser.y"
                  {
        (yyval.node) = create_node("CompoundStatement");
    }
#line 2609 "build/parser.tab.c"
    break;

  case 94: /* compound_statement: LBRACE block_item_list RBRACE  */
#line 578 "src/parser.y"
                                    {
        (yyval.node) = create_node("CompoundStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2618 "build/parser.tab.c"
    break;

  case 95: /* block_item_list: block_item  */
#line 585 "src/parser.y"
               {
        (yyval.node) = create_node("BlockItemList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2627 "build/parser.tab.c"
    break;

  case 96: /* block_item_list: block_item_list block_item  */
#line 589 "src/parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2636 "build/parser.tab.c"
    break;

  case 97: /* block_item: declaration  */
#line 596 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2645 "build/parser.tab.c"
    break;

  case 98: /* block_item: statement  */
#line 600 "src/parser.y"
                {
        (yyval.node) = create_node("BlockItem");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2654 "build/parser.tab.c"
    break;

  case 99: /* statement: labeled_statement  */
#line 607 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2660 "build/parser.tab.c"
    break;

  case 100: /* statement: expression_statement  */
#line 608 "src/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2666 "build/parser.tab.c"
    break;

  case 101: /* statement: compound_statement  */
#line 609 "src/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2672 "build/parser.tab.c"
    break;

  case 102: /* statement: selection_statement  */
#line 610 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2678 "build/parser.tab.c"
    break;

  case 103: /* statement: iteration_statement  */
#line 611 "src/parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2684 "build/parser.tab.c"
    break;

  case 104: /* statement: jump_statement  */
#line 612 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2690 "build/parser.tab.c"
    break;

  case 105: /* labeled_statement: ID COLON statement  */
#line 616 "src/parser.y"
                       {
        (yyval.node) = create_node("LabeledStatement", (yyvsp[-2].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2699 "build/parser.tab.c"
    break;

  case 106: /* labeled_statement: CASE assignment_expression COLON statement  */
#line 620 "src/parser.y"
                                                 {
        (yyval.node) = create_node("CaseStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2709 "build/parser.tab.c"
    break;

  case 107: /* labeled_statement: DEFAULT COLON statement  */
#line 625 "src/parser.y"
                              {
        (yyval.node) = create_node("DefaultStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2718 "build/parser.tab.c"
    break;

  case 108: /* expression_statement: expression SEMI  */
#line 632 "src/parser.y"
                    {
        (yyval.node) = create_node("ExpressionStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2727 "build/parser.tab.c"
    break;

  case 109: /* expression_statement: SEMI  */
#line 636 "src/parser.y"
           {
        (yyval.node) = create_node("EmptyStatement");
    }
#line 2735 "build/parser.tab.c"
    break;

  case 110: /* selection_statement: IF LPAREN expression RPAREN statement  */
#line 642 "src/parser.y"
                                                                {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2745 "build/parser.tab.c"
    break;

  case 111: /* selection_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 647 "src/parser.y"
                                                           {
        (yyval.node) = create_node("IfStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2756 "build/parser.tab.c"
    break;

  case 112: /* selection_statement: SWITCH LPAREN expression RPAREN statement  */
#line 653 "src/parser.y"
                                                {
        (yyval.node) = create_node("SwitchStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2766 "build/parser.tab.c"
    break;

  case 113: /* iteration_statement: WHILE LPAREN expression RPAREN statement  */
#line 661 "src/parser.y"
                                             {
        (yyval.node) = create_node("WhileStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2776 "build/parser.tab.c"
    break;

  case 114: /* iteration_statement: DO statement WHILE LPAREN expression RPAREN SEMI  */
#line 666 "src/parser.y"
                                                       {
        (yyval.node) = create_node("DoWhileStatement");
        (yyval.node)->addChild((yyvsp[-5].node));
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 2786 "build/parser.tab.c"
    break;

  case 115: /* iteration_statement: FOR LPAREN for_init_statement expression_statement RPAREN statement  */
#line 671 "src/parser.y"
                                                                          {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2797 "build/parser.tab.c"
    break;

  case 116: /* iteration_statement: FOR LPAREN for_init_statement expression_statement expression RPAREN statement  */
#line 677 "src/parser.y"
                                                                                     {
        (yyval.node) = create_node("ForStatement");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2809 "build/parser.tab.c"
    break;

  case 117: /* iteration_statement: FOR LPAREN range_based_for RPAREN statement  */
#line 684 "src/parser.y"
                                                  {
        (yyval.node) = create_node("RangeBasedForStatement");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2819 "build/parser.tab.c"
    break;

  case 118: /* for_init_statement: expression_statement  */
#line 692 "src/parser.y"
                         {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2828 "build/parser.tab.c"
    break;

  case 119: /* for_init_statement: declaration  */
#line 696 "src/parser.y"
                  {
        (yyval.node) = create_node("ForInitStatement");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2837 "build/parser.tab.c"
    break;

  case 120: /* range_based_for: declaration_specifiers ID COLON expression  */
#line 703 "src/parser.y"
                                               {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2848 "build/parser.tab.c"
    break;

  case 121: /* range_based_for: declaration_specifiers BIT_AND ID COLON expression  */
#line 709 "src/parser.y"
                                                         {
        (yyval.node) = create_node("RangeBasedFor");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild(create_node("Reference"));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[-2].str)));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2860 "build/parser.tab.c"
    break;

  case 122: /* jump_statement: GOTO ID SEMI  */
#line 719 "src/parser.y"
                 {
        (yyval.node) = create_node("GotoStatement", (yyvsp[-1].str));
    }
#line 2868 "build/parser.tab.c"
    break;

  case 123: /* jump_statement: CONTINUE SEMI  */
#line 722 "src/parser.y"
                    {
        (yyval.node) = create_node("ContinueStatement");
    }
#line 2876 "build/parser.tab.c"
    break;

  case 124: /* jump_statement: BREAK SEMI  */
#line 725 "src/parser.y"
                 {
        (yyval.node) = create_node("BreakStatement");
    }
#line 2884 "build/parser.tab.c"
    break;

  case 125: /* jump_statement: RETURN expression SEMI  */
#line 728 "src/parser.y"
                             {
        (yyval.node) = create_node("ReturnStatement");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 2893 "build/parser.tab.c"
    break;

  case 126: /* jump_statement: RETURN SEMI  */
#line 732 "src/parser.y"
                  {
        (yyval.node) = create_node("ReturnStatement");
    }
#line 2901 "build/parser.tab.c"
    break;

  case 127: /* expression: assignment_expression  */
#line 738 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2909 "build/parser.tab.c"
    break;

  case 128: /* expression: expression COMMA assignment_expression  */
#line 741 "src/parser.y"
                                             {
        (yyval.node) = create_node("CommaExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2919 "build/parser.tab.c"
    break;

  case 129: /* assignment_expression: conditional_expression  */
#line 749 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 2927 "build/parser.tab.c"
    break;

  case 130: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 752 "src/parser.y"
                                                                 {
        (yyval.node) = create_node("AssignmentExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 2937 "build/parser.tab.c"
    break;

  case 131: /* assignment_operator: ASSIGN  */
#line 760 "src/parser.y"
           { (yyval.str) = strdup("="); }
#line 2943 "build/parser.tab.c"
    break;

  case 132: /* assignment_operator: PLUS_EQ  */
#line 761 "src/parser.y"
              { (yyval.str) = strdup("+="); }
#line 2949 "build/parser.tab.c"
    break;

  case 133: /* assignment_operator: MINUS_EQ  */
#line 762 "src/parser.y"
               { (yyval.str) = strdup("-="); }
#line 2955 "build/parser.tab.c"
    break;

  case 134: /* assignment_operator: MUL_EQ  */
#line 763 "src/parser.y"
             { (yyval.str) = strdup("*="); }
#line 2961 "build/parser.tab.c"
    break;

  case 135: /* assignment_operator: DIV_EQ  */
#line 764 "src/parser.y"
             { (yyval.str) = strdup("/="); }
#line 2967 "build/parser.tab.c"
    break;

  case 136: /* assignment_operator: MOD_EQ  */
#line 765 "src/parser.y"
             { (yyval.str) = strdup("%="); }
#line 2973 "build/parser.tab.c"
    break;

  case 137: /* assignment_operator: AND_EQ  */
#line 766 "src/parser.y"
             { (yyval.str) = strdup("&="); }
#line 2979 "build/parser.tab.c"
    break;

  case 138: /* assignment_operator: OR_EQ  */
#line 767 "src/parser.y"
            { (yyval.str) = strdup("|="); }
#line 2985 "build/parser.tab.c"
    break;

  case 139: /* assignment_operator: XOR_EQ  */
#line 768 "src/parser.y"
             { (yyval.str) = strdup("^="); }
#line 2991 "build/parser.tab.c"
    break;

  case 140: /* assignment_operator: LSHIFT_EQ  */
#line 769 "src/parser.y"
                { (yyval.str) = strdup("<<="); }
#line 2997 "build/parser.tab.c"
    break;

  case 141: /* assignment_operator: RSHIFT_EQ  */
#line 770 "src/parser.y"
                { (yyval.str) = strdup(">>="); }
#line 3003 "build/parser.tab.c"
    break;

  case 142: /* conditional_expression: logical_or_expression  */
#line 774 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3011 "build/parser.tab.c"
    break;

  case 143: /* conditional_expression: logical_or_expression QUESTION expression COLON conditional_expression  */
#line 777 "src/parser.y"
                                                                             {
        (yyval.node) = create_node("ConditionalExpression");
        (yyval.node)->addChild((yyvsp[-4].node));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3022 "build/parser.tab.c"
    break;

  case 144: /* logical_or_expression: logical_and_expression  */
#line 786 "src/parser.y"
                           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3030 "build/parser.tab.c"
    break;

  case 145: /* logical_or_expression: logical_or_expression OR logical_and_expression  */
#line 789 "src/parser.y"
                                                      {
        (yyval.node) = create_node("LogicalOrExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3040 "build/parser.tab.c"
    break;

  case 146: /* logical_and_expression: inclusive_or_expression  */
#line 797 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3048 "build/parser.tab.c"
    break;

  case 147: /* logical_and_expression: logical_and_expression AND inclusive_or_expression  */
#line 800 "src/parser.y"
                                                         {
        (yyval.node) = create_node("LogicalAndExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3058 "build/parser.tab.c"
    break;

  case 148: /* inclusive_or_expression: exclusive_or_expression  */
#line 808 "src/parser.y"
                            {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3066 "build/parser.tab.c"
    break;

  case 149: /* inclusive_or_expression: inclusive_or_expression BIT_OR exclusive_or_expression  */
#line 811 "src/parser.y"
                                                             {
        (yyval.node) = create_node("InclusiveOrExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3076 "build/parser.tab.c"
    break;

  case 150: /* exclusive_or_expression: and_expression  */
#line 819 "src/parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3084 "build/parser.tab.c"
    break;

  case 151: /* exclusive_or_expression: exclusive_or_expression BIT_XOR and_expression  */
#line 822 "src/parser.y"
                                                     {
        (yyval.node) = create_node("ExclusiveOrExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3094 "build/parser.tab.c"
    break;

  case 152: /* and_expression: equality_expression  */
#line 830 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3102 "build/parser.tab.c"
    break;

  case 153: /* and_expression: and_expression BIT_AND equality_expression  */
#line 833 "src/parser.y"
                                                 {
        (yyval.node) = create_node("AndExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3112 "build/parser.tab.c"
    break;

  case 154: /* equality_expression: relational_expression  */
#line 841 "src/parser.y"
                          {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3120 "build/parser.tab.c"
    break;

  case 155: /* equality_expression: equality_expression EQ relational_expression  */
#line 844 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "==");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3130 "build/parser.tab.c"
    break;

  case 156: /* equality_expression: equality_expression NE relational_expression  */
#line 849 "src/parser.y"
                                                   {
        (yyval.node) = create_node("EqualityExpression", "!=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3140 "build/parser.tab.c"
    break;

  case 157: /* relational_expression: shift_expression  */
#line 857 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3148 "build/parser.tab.c"
    break;

  case 158: /* relational_expression: relational_expression LT shift_expression  */
#line 860 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3158 "build/parser.tab.c"
    break;

  case 159: /* relational_expression: relational_expression GT shift_expression  */
#line 865 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3168 "build/parser.tab.c"
    break;

  case 160: /* relational_expression: relational_expression LE shift_expression  */
#line 870 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", "<=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3178 "build/parser.tab.c"
    break;

  case 161: /* relational_expression: relational_expression GE shift_expression  */
#line 875 "src/parser.y"
                                                {
        (yyval.node) = create_node("RelationalExpression", ">=");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3188 "build/parser.tab.c"
    break;

  case 162: /* shift_expression: additive_expression  */
#line 883 "src/parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3196 "build/parser.tab.c"
    break;

  case 163: /* shift_expression: shift_expression LSHIFT additive_expression  */
#line 886 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", "<<");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3206 "build/parser.tab.c"
    break;

  case 164: /* shift_expression: shift_expression RSHIFT additive_expression  */
#line 891 "src/parser.y"
                                                  {
        (yyval.node) = create_node("ShiftExpression", ">>");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3216 "build/parser.tab.c"
    break;

  case 165: /* additive_expression: multiplicative_expression  */
#line 899 "src/parser.y"
                              {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3224 "build/parser.tab.c"
    break;

  case 166: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 902 "src/parser.y"
                                                         {
        (yyval.node) = create_node("AdditiveExpression", "+");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3234 "build/parser.tab.c"
    break;

  case 167: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 907 "src/parser.y"
                                                          {
        (yyval.node) = create_node("AdditiveExpression", "-");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3244 "build/parser.tab.c"
    break;

  case 168: /* multiplicative_expression: cast_expression  */
#line 915 "src/parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3252 "build/parser.tab.c"
    break;

  case 169: /* multiplicative_expression: multiplicative_expression MUL cast_expression  */
#line 918 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "*");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3262 "build/parser.tab.c"
    break;

  case 170: /* multiplicative_expression: multiplicative_expression DIV cast_expression  */
#line 923 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "/");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3272 "build/parser.tab.c"
    break;

  case 171: /* multiplicative_expression: multiplicative_expression MOD cast_expression  */
#line 928 "src/parser.y"
                                                    {
        (yyval.node) = create_node("MultiplicativeExpression", "%");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3282 "build/parser.tab.c"
    break;

  case 172: /* cast_expression: unary_expression  */
#line 936 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3290 "build/parser.tab.c"
    break;

  case 173: /* cast_expression: LPAREN type_name RPAREN cast_expression  */
#line 939 "src/parser.y"
                                              {
        (yyval.node) = create_node("CastExpression");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3300 "build/parser.tab.c"
    break;

  case 174: /* unary_expression: postfix_expression  */
#line 947 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3308 "build/parser.tab.c"
    break;

  case 175: /* unary_expression: INC unary_expression  */
#line 950 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "++");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3317 "build/parser.tab.c"
    break;

  case 176: /* unary_expression: DEC unary_expression  */
#line 954 "src/parser.y"
                           {
        (yyval.node) = create_node("UnaryExpression", "--");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3326 "build/parser.tab.c"
    break;

  case 177: /* unary_expression: unary_operator cast_expression  */
#line 958 "src/parser.y"
                                     {
        (yyval.node) = create_node("UnaryExpression", (yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3335 "build/parser.tab.c"
    break;

  case 178: /* unary_expression: SIZEOF unary_expression  */
#line 962 "src/parser.y"
                              {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3344 "build/parser.tab.c"
    break;

  case 179: /* unary_expression: SIZEOF LPAREN type_name RPAREN  */
#line 966 "src/parser.y"
                                     {
        (yyval.node) = create_node("SizeOfExpression");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3353 "build/parser.tab.c"
    break;

  case 180: /* unary_operator: BIT_AND  */
#line 973 "src/parser.y"
            { (yyval.str) = strdup("&"); }
#line 3359 "build/parser.tab.c"
    break;

  case 181: /* unary_operator: MUL  */
#line 974 "src/parser.y"
          { (yyval.str) = strdup("*"); }
#line 3365 "build/parser.tab.c"
    break;

  case 182: /* unary_operator: PLUS  */
#line 975 "src/parser.y"
           { (yyval.str) = strdup("+"); }
#line 3371 "build/parser.tab.c"
    break;

  case 183: /* unary_operator: MINUS  */
#line 976 "src/parser.y"
            { (yyval.str) = strdup("-"); }
#line 3377 "build/parser.tab.c"
    break;

  case 184: /* unary_operator: BIT_NOT  */
#line 977 "src/parser.y"
              { (yyval.str) = strdup("~"); }
#line 3383 "build/parser.tab.c"
    break;

  case 185: /* unary_operator: NOT  */
#line 978 "src/parser.y"
          { (yyval.str) = strdup("!"); }
#line 3389 "build/parser.tab.c"
    break;

  case 186: /* postfix_expression: primary_expression  */
#line 982 "src/parser.y"
                       {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3397 "build/parser.tab.c"
    break;

  case 187: /* postfix_expression: postfix_expression LBRACKET expression RBRACKET  */
#line 985 "src/parser.y"
                                                      {
        (yyval.node) = create_node("ArraySubscript");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3407 "build/parser.tab.c"
    break;

  case 188: /* postfix_expression: postfix_expression LPAREN argument_expression_list RPAREN  */
#line 990 "src/parser.y"
                                                                {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-3].node));
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3417 "build/parser.tab.c"
    break;

  case 189: /* postfix_expression: postfix_expression LPAREN RPAREN  */
#line 995 "src/parser.y"
                                       {
        (yyval.node) = create_node("FunctionCall");
        (yyval.node)->addChild((yyvsp[-2].node));
    }
#line 3426 "build/parser.tab.c"
    break;

  case 190: /* postfix_expression: postfix_expression DOT ID  */
#line 999 "src/parser.y"
                                {
        (yyval.node) = create_node("MemberAccess", ".");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3436 "build/parser.tab.c"
    break;

  case 191: /* postfix_expression: postfix_expression ARROW ID  */
#line 1004 "src/parser.y"
                                  {
        (yyval.node) = create_node("MemberAccess", "->");
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild(create_node("Identifier", (yyvsp[0].str)));
    }
#line 3446 "build/parser.tab.c"
    break;

  case 192: /* postfix_expression: postfix_expression INC  */
#line 1009 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "++");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3455 "build/parser.tab.c"
    break;

  case 193: /* postfix_expression: postfix_expression DEC  */
#line 1013 "src/parser.y"
                             {
        (yyval.node) = create_node("PostfixExpression", "--");
        (yyval.node)->addChild((yyvsp[-1].node));
    }
#line 3464 "build/parser.tab.c"
    break;

  case 194: /* primary_expression: ID  */
#line 1020 "src/parser.y"
       {
        (yyval.node) = create_node("Identifier", (yyvsp[0].str));
    }
#line 3472 "build/parser.tab.c"
    break;

  case 195: /* primary_expression: constant  */
#line 1023 "src/parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3480 "build/parser.tab.c"
    break;

  case 196: /* primary_expression: string_literal  */
#line 1026 "src/parser.y"
                     {
        (yyval.node) = (yyvsp[0].node);
    }
#line 3488 "build/parser.tab.c"
    break;

  case 197: /* primary_expression: LPAREN expression RPAREN  */
#line 1029 "src/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3496 "build/parser.tab.c"
    break;

  case 198: /* string_literal: STRING_LIT  */
#line 1035 "src/parser.y"
               {
        (yyval.node) = create_node("StringLiteral", (yyvsp[0].str));
    }
#line 3504 "build/parser.tab.c"
    break;

  case 199: /* string_literal: string_literal STRING_LIT  */
#line 1038 "src/parser.y"
                                {
        (yyval.node) = create_node("StringLiteral");
        (yyval.node)->addChild((yyvsp[-1].node));
        (yyval.node)->addChild(create_node("StringLiteral", (yyvsp[0].str)));
    }
#line 3514 "build/parser.tab.c"
    break;

  case 200: /* argument_expression_list: assignment_expression  */
#line 1046 "src/parser.y"
                          {
        (yyval.node) = create_node("ArgumentList");
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3523 "build/parser.tab.c"
    break;

  case 201: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 1050 "src/parser.y"
                                                           {
        (yyval.node) = (yyvsp[-2].node);
        (yyval.node)->addChild((yyvsp[0].node));
    }
#line 3532 "build/parser.tab.c"
    break;

  case 202: /* constant: NUM  */
#line 1057 "src/parser.y"
        { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3538 "build/parser.tab.c"
    break;

  case 203: /* constant: FLOAT_LIT  */
#line 1058 "src/parser.y"
                { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3544 "build/parser.tab.c"
    break;

  case 204: /* constant: CHAR_LIT  */
#line 1059 "src/parser.y"
               { (yyval.node) = create_node("Constant", (yyvsp[0].str)); }
#line 3550 "build/parser.tab.c"
    break;

  case 205: /* constant: TRUE  */
#line 1060 "src/parser.y"
           { (yyval.node) = create_node("Constant", "true"); }
#line 3556 "build/parser.tab.c"
    break;

  case 206: /* constant: FALSE  */
#line 1061 "src/parser.y"
            { (yyval.node) = create_node("Constant", "false"); }
#line 3562 "build/parser.tab.c"
    break;


#line 3566 "build/parser.tab.c"

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

#line 1064 "src/parser.y"


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
