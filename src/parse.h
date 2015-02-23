
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
     NUMBER = 258,
     NAME = 259,
     FUNC = 260,
     EOL = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     DO = 265,
     LET = 266,
     COMMENT = 267,
     LBRACE = 268,
     RBRACE = 269,
     ASSIGN = 270,
     SEMICOLON = 271,
     CMP = 272,
     UMINUS = 273,
     SUB = 274,
     ADD = 275,
     MOD = 276,
     DIV = 277,
     MULT = 278,
     NEG = 279
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define NAME 259
#define FUNC 260
#define EOL 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define DO 265
#define LET 266
#define COMMENT 267
#define LBRACE 268
#define RBRACE 269
#define ASSIGN 270
#define SEMICOLON 271
#define CMP 272
#define UMINUS 273
#define SUB 274
#define ADD 275
#define MOD 276
#define DIV 277
#define MULT 278
#define NEG 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 14 "src/parse.y"

    struct ast *a;
    double d;
    struct symbol *s;   /* which symbol */
    struct symbol *sl;
    int fn; /* which function */



/* Line 1676 of yacc.c  */
#line 110 "src/parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


