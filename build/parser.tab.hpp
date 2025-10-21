/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    AUTO = 258,                    /* AUTO  */
    BREAK = 259,                   /* BREAK  */
    CASE = 260,                    /* CASE  */
    CHAR = 261,                    /* CHAR  */
    CONST = 262,                   /* CONST  */
    CONTINUE = 263,                /* CONTINUE  */
    DEFAULT = 264,                 /* DEFAULT  */
    DO = 265,                      /* DO  */
    DOUBLE = 266,                  /* DOUBLE  */
    ELSE = 267,                    /* ELSE  */
    ENUM = 268,                    /* ENUM  */
    EXTERN = 269,                  /* EXTERN  */
    FLOAT = 270,                   /* FLOAT  */
    FOR = 271,                     /* FOR  */
    GOTO = 272,                    /* GOTO  */
    IF = 273,                      /* IF  */
    INT = 274,                     /* INT  */
    LONG = 275,                    /* LONG  */
    REGISTER = 276,                /* REGISTER  */
    RETURN = 277,                  /* RETURN  */
    SHORT = 278,                   /* SHORT  */
    SIGNED = 279,                  /* SIGNED  */
    SIZEOF = 280,                  /* SIZEOF  */
    STATIC = 281,                  /* STATIC  */
    STRUCT = 282,                  /* STRUCT  */
    SWITCH = 283,                  /* SWITCH  */
    TYPEDEF = 284,                 /* TYPEDEF  */
    UNION = 285,                   /* UNION  */
    UNSIGNED = 286,                /* UNSIGNED  */
    VOID = 287,                    /* VOID  */
    VOLATILE = 288,                /* VOLATILE  */
    WHILE = 289,                   /* WHILE  */
    CLASS = 290,                   /* CLASS  */
    PRIVATE = 291,                 /* PRIVATE  */
    PROTECTED = 292,               /* PROTECTED  */
    PUBLIC = 293,                  /* PUBLIC  */
    VIRTUAL = 294,                 /* VIRTUAL  */
    FRIEND = 295,                  /* FRIEND  */
    INLINE = 296,                  /* INLINE  */
    OPERATOR = 297,                /* OPERATOR  */
    OVERLOAD = 298,                /* OVERLOAD  */
    TEMPLATE = 299,                /* TEMPLATE  */
    THIS = 300,                    /* THIS  */
    NEW = 301,                     /* NEW  */
    DELETE = 302,                  /* DELETE  */
    NAMESPACE = 303,               /* NAMESPACE  */
    USING = 304,                   /* USING  */
    TRY = 305,                     /* TRY  */
    CATCH = 306,                   /* CATCH  */
    THROW = 307,                   /* THROW  */
    BOOL = 308,                    /* BOOL  */
    TRUE = 309,                    /* TRUE  */
    FALSE = 310,                   /* FALSE  */
    TYPEDEF_NAME = 311,            /* TYPEDEF_NAME  */
    ID = 312,                      /* ID  */
    NUM = 313,                     /* NUM  */
    FLOAT_LIT = 314,               /* FLOAT_LIT  */
    CHAR_LIT = 315,                /* CHAR_LIT  */
    STRING_LIT = 316,              /* STRING_LIT  */
    PLUS = 317,                    /* PLUS  */
    MINUS = 318,                   /* MINUS  */
    MUL = 319,                     /* MUL  */
    DIV = 320,                     /* DIV  */
    MOD = 321,                     /* MOD  */
    ASSIGN = 322,                  /* ASSIGN  */
    PLUS_EQ = 323,                 /* PLUS_EQ  */
    MINUS_EQ = 324,                /* MINUS_EQ  */
    MUL_EQ = 325,                  /* MUL_EQ  */
    DIV_EQ = 326,                  /* DIV_EQ  */
    MOD_EQ = 327,                  /* MOD_EQ  */
    INC = 328,                     /* INC  */
    DEC = 329,                     /* DEC  */
    EQ = 330,                      /* EQ  */
    NE = 331,                      /* NE  */
    LT = 332,                      /* LT  */
    GT = 333,                      /* GT  */
    LE = 334,                      /* LE  */
    GE = 335,                      /* GE  */
    AND = 336,                     /* AND  */
    OR = 337,                      /* OR  */
    NOT = 338,                     /* NOT  */
    BIT_AND = 339,                 /* BIT_AND  */
    BIT_OR = 340,                  /* BIT_OR  */
    BIT_XOR = 341,                 /* BIT_XOR  */
    BIT_NOT = 342,                 /* BIT_NOT  */
    LSHIFT = 343,                  /* LSHIFT  */
    RSHIFT = 344,                  /* RSHIFT  */
    AND_EQ = 345,                  /* AND_EQ  */
    OR_EQ = 346,                   /* OR_EQ  */
    XOR_EQ = 347,                  /* XOR_EQ  */
    LSHIFT_EQ = 348,               /* LSHIFT_EQ  */
    RSHIFT_EQ = 349,               /* RSHIFT_EQ  */
    ARROW = 350,                   /* ARROW  */
    DOT = 351,                     /* DOT  */
    SCOPE = 352,                   /* SCOPE  */
    SEMI = 353,                    /* SEMI  */
    COMMA = 354,                   /* COMMA  */
    QUESTION = 355,                /* QUESTION  */
    COLON = 356,                   /* COLON  */
    LPAREN = 357,                  /* LPAREN  */
    RPAREN = 358,                  /* RPAREN  */
    LBRACE = 359,                  /* LBRACE  */
    RBRACE = 360,                  /* RBRACE  */
    LBRACKET = 361,                /* LBRACKET  */
    RBRACKET = 362,                /* RBRACKET  */
    ELLIPSIS = 363,                /* ELLIPSIS  */
    PREP = 364,                    /* PREP  */
    NEWLINE = 365,                 /* NEWLINE  */
    END = 366,                     /* END  */
    ERROR = 367,                   /* ERROR  */
    UMINUS = 368,                  /* UMINUS  */
    UPLUS = 369,                   /* UPLUS  */
    IF_WITHOUT_ELSE = 370          /* IF_WITHOUT_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 78 "src/parser.y"

    char* str;
    int num;
    ASTNode* node;

#line 185 "build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED  */
