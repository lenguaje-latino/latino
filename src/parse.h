
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
     TOKEN_NUMBER = 258,
     TOKEN_STRING = 259,
     TOKEN_IDENTIFIER = 260,
     TOKEN_FUNC = 261,
     KEYWORD_IF = 262,
     KEYWORD_END = 263,
     KEYWORD_ELSE = 264,
     KEYWORD_WHILE = 265,
     KEYWORD_DO = 266,
     KEYWORD_WHEN = 267,
     KEYWORD_FUNCTION = 268,
     KEYWORD_TRUE = 269,
     KEYWORD_FALSE = 270,
     KEYWORD_FROM = 271,
     KEYWORD_TO = 272,
     KEYWORD_STEP = 273,
     KEYWORD_BOOL = 274,
     KEYWORD_INT = 275,
     KEYWORD_DECIMAL = 276,
     KEYWORD_CHAR = 277,
     KEYWORD_STRING = 278,
     LIT_STRING = 279,
     CMP = 280,
     UMINUS = 281
   };
#endif
/* Tokens.  */
#define TOKEN_NUMBER 258
#define TOKEN_STRING 259
#define TOKEN_IDENTIFIER 260
#define TOKEN_FUNC 261
#define KEYWORD_IF 262
#define KEYWORD_END 263
#define KEYWORD_ELSE 264
#define KEYWORD_WHILE 265
#define KEYWORD_DO 266
#define KEYWORD_WHEN 267
#define KEYWORD_FUNCTION 268
#define KEYWORD_TRUE 269
#define KEYWORD_FALSE 270
#define KEYWORD_FROM 271
#define KEYWORD_TO 272
#define KEYWORD_STEP 273
#define KEYWORD_BOOL 274
#define KEYWORD_INT 275
#define KEYWORD_DECIMAL 276
#define KEYWORD_CHAR 277
#define KEYWORD_STRING 278
#define LIT_STRING 279
#define CMP 280
#define UMINUS 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 8 "src/parse.y"

    struct ast *a;
    double d;
    struct symbol *s;   /* which symbol */
    struct symlist *sl;
    int fn; /* which function */
    struct lat_string *str;



/* Line 1676 of yacc.c  */
#line 115 "src/parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


