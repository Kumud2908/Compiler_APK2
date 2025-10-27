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
    NULL_TOKEN = 290,              /* NULL_TOKEN  */
    NULLPTR = 291,                 /* NULLPTR  */
    CLASS = 292,                   /* CLASS  */
    PRIVATE = 293,                 /* PRIVATE  */
    PROTECTED = 294,               /* PROTECTED  */
    PUBLIC = 295,                  /* PUBLIC  */
    VIRTUAL = 296,                 /* VIRTUAL  */
    FRIEND = 297,                  /* FRIEND  */
    INLINE = 298,                  /* INLINE  */
    OPERATOR = 299,                /* OPERATOR  */
    OVERLOAD = 300,                /* OVERLOAD  */
    TEMPLATE = 301,                /* TEMPLATE  */
    THIS = 302,                    /* THIS  */
    NEW = 303,                     /* NEW  */
    DELETE = 304,                  /* DELETE  */
    NAMESPACE = 305,               /* NAMESPACE  */
    USING = 306,                   /* USING  */
    TRY = 307,                     /* TRY  */
    CATCH = 308,                   /* CATCH  */
    THROW = 309,                   /* THROW  */
    BOOL = 310,                    /* BOOL  */
    TRUE = 311,                    /* TRUE  */
    FALSE = 312,                   /* FALSE  */
    TYPEDEF_NAME = 313,            /* TYPEDEF_NAME  */
    ID = 314,                      /* ID  */
    NUM = 315,                     /* NUM  */
    FLOAT_LIT = 316,               /* FLOAT_LIT  */
    CHAR_LIT = 317,                /* CHAR_LIT  */
    STRING_LIT = 318,              /* STRING_LIT  */
    PLUS = 319,                    /* PLUS  */
    MINUS = 320,                   /* MINUS  */
    MUL = 321,                     /* MUL  */
    DIV = 322,                     /* DIV  */
    MOD = 323,                     /* MOD  */
    ASSIGN = 324,                  /* ASSIGN  */
    PLUS_EQ = 325,                 /* PLUS_EQ  */
    MINUS_EQ = 326,                /* MINUS_EQ  */
    MUL_EQ = 327,                  /* MUL_EQ  */
    DIV_EQ = 328,                  /* DIV_EQ  */
    MOD_EQ = 329,                  /* MOD_EQ  */
    INC = 330,                     /* INC  */
    DEC = 331,                     /* DEC  */
    EQ = 332,                      /* EQ  */
    NE = 333,                      /* NE  */
    LT = 334,                      /* LT  */
    GT = 335,                      /* GT  */
    LE = 336,                      /* LE  */
    GE = 337,                      /* GE  */
    AND = 338,                     /* AND  */
    OR = 339,                      /* OR  */
    NOT = 340,                     /* NOT  */
    BIT_AND = 341,                 /* BIT_AND  */
    BIT_OR = 342,                  /* BIT_OR  */
    BIT_XOR = 343,                 /* BIT_XOR  */
    BIT_NOT = 344,                 /* BIT_NOT  */
    LSHIFT = 345,                  /* LSHIFT  */
    RSHIFT = 346,                  /* RSHIFT  */
    AND_EQ = 347,                  /* AND_EQ  */
    OR_EQ = 348,                   /* OR_EQ  */
    XOR_EQ = 349,                  /* XOR_EQ  */
    LSHIFT_EQ = 350,               /* LSHIFT_EQ  */
    RSHIFT_EQ = 351,               /* RSHIFT_EQ  */
    ARROW = 352,                   /* ARROW  */
    DOT = 353,                     /* DOT  */
    SCOPE = 354,                   /* SCOPE  */
    UNTIL = 355,                   /* UNTIL  */
    SEMI = 356,                    /* SEMI  */
    COMMA = 357,                   /* COMMA  */
    QUESTION = 358,                /* QUESTION  */
    COLON = 359,                   /* COLON  */
    LPAREN = 360,                  /* LPAREN  */
    RPAREN = 361,                  /* RPAREN  */
    LBRACE = 362,                  /* LBRACE  */
    RBRACE = 363,                  /* RBRACE  */
    LBRACKET = 364,                /* LBRACKET  */
    RBRACKET = 365,                /* RBRACKET  */
    ELLIPSIS = 366,                /* ELLIPSIS  */
    PREP = 367,                    /* PREP  */
    NEWLINE = 368,                 /* NEWLINE  */
    END = 369,                     /* END  */
    ERROR = 370,                   /* ERROR  */
    DESTRUCTOR = 371,              /* DESTRUCTOR  */
    UMINUS = 372,                  /* UMINUS  */
    UPLUS = 373,                   /* UPLUS  */
    IF_WITHOUT_ELSE = 374          /* IF_WITHOUT_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 129 "src/parser.y"

    char* str;
    int num;
    ASTNode* node;

#line 189 "build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_HPP_INCLUDED  */
