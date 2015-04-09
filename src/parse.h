
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     KEYWORD_SWITCH = 271,
     KEYWORD_CASE = 272,
     KEYWORD_BREAK = 273,
     KEYWORD_DEFAULT = 274,
     KEYWORD_WHEN = 275,
     KEYWORD_FUNCTION = 276,
     KEYWORD_FROM = 277,
     KEYWORD_TO = 278,
     KEYWORD_STEP = 279,
     KEYWORD_BOOL = 280,
     OP_GT = 281,
     OP_LT = 282,
     OP_GE = 283,
     OP_LE = 284,
     OP_EQ = 285,
     OP_NEQ = 286,
     OP_AND = 287,
     OP_OR = 288,
     OP_NEG = 289,
     UNEG = 290,
     UMINUS = 291
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
#define KEYWORD_SWITCH 271
#define KEYWORD_CASE 272
#define KEYWORD_BREAK 273
#define KEYWORD_DEFAULT 274
#define KEYWORD_WHEN 275
#define KEYWORD_FUNCTION 276
#define KEYWORD_FROM 277
#define KEYWORD_TO 278
#define KEYWORD_STEP 279
#define KEYWORD_BOOL 280
#define OP_GT 281
#define OP_LT 282
#define OP_GE 283
#define OP_LE 284
#define OP_EQ 285
#define OP_NEQ 286
#define OP_AND 287
#define OP_OR 288
#define OP_NEG 289
#define UNEG 290
#define UMINUS 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 8 "src/parse.y"

    int fn; /* which function */
    char *b; /* boolean type*/
    char *c; /* char type */
    int i;  /* int type */
    double d; /* double type */
    struct lat_string *str; /* string type */
    struct ast *a; /* astract syntax tree */
    struct symbol *s;   /* which symbol */
    struct symlist *sl; /* symbol list */



/* Line 1676 of yacc.c  */
#line 138 "src/parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


