/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_SRC_PARSE_H_INCLUDED
# define YY_YY_SRC_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KEYWORD_TRUE = 258,
    KEYWORD_FALSE = 259,
    TOKEN_INT = 260,
    TOKEN_CHAR = 261,
    TOKEN_NUMBER = 262,
    TOKEN_STRING = 263,
    TOKEN_IDENTIFIER = 264,
    TOKEN_FUNC = 265,
    KEYWORD_IF = 266,
    KEYWORD_END = 267,
    KEYWORD_ELSE = 268,
    KEYWORD_WHILE = 269,
    KEYWORD_DO = 270,
    KEYWORD_WHEN = 271,
    KEYWORD_FUNCTION = 272,
    KEYWORD_FROM = 273,
    KEYWORD_TO = 274,
    KEYWORD_STEP = 275,
    KEYWORD_BOOL = 276,
    OP_GT = 277,
    OP_LT = 278,
    OP_GE = 279,
    OP_LE = 280,
    OP_EQ = 281,
    OP_NEQ = 282,
    OP_AND = 283,
    OP_OR = 284,
    UMINUS = 285
  };
#endif
/* Tokens.  */
#define KEYWORD_TRUE 258
#define KEYWORD_FALSE 259
#define TOKEN_INT 260
#define TOKEN_CHAR 261
#define TOKEN_NUMBER 262
#define TOKEN_STRING 263
#define TOKEN_IDENTIFIER 264
#define TOKEN_FUNC 265
#define KEYWORD_IF 266
#define KEYWORD_END 267
#define KEYWORD_ELSE 268
#define KEYWORD_WHILE 269
#define KEYWORD_DO 270
#define KEYWORD_WHEN 271
#define KEYWORD_FUNCTION 272
#define KEYWORD_FROM 273
#define KEYWORD_TO 274
#define KEYWORD_STEP 275
#define KEYWORD_BOOL 276
#define OP_GT 277
#define OP_LT 278
#define OP_GE 279
#define OP_LE 280
#define OP_EQ 281
#define OP_NEQ 282
#define OP_AND 283
#define OP_OR 284
#define UMINUS 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 8 "src/parse.y" /* yacc.c:1909  */

    int fn; /* which function */
    char *b; /* boolean type*/
    char *c; /* char type */
    int i;  /* int type */
    double d; /* double type */
    struct lat_string *str; /* string type */
    struct ast *a; /* astract syntax tree */
    struct symbol *s;   /* which symbol */
    struct symlist *sl;

#line 126 "src/parse.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSE_H_INCLUDED  */
