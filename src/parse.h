/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
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
    TINT = 258,
    TCHAR = 259,
    TNUMBER = 260,
    TSTRING = 261,
    TIDENTIFIER = 262,
    TFUNC = 263,
    KIF = 264,
    KEND = 265,
    KELSE = 266,
    KWHILE = 267,
    KDO = 268,
    KBREAK = 269,
    KCONTINUE = 270,
    KWHEN = 271,
    KFUNCTION = 272,
    KFROM = 273,
    KBOOL = 274,
    KRETURN = 275,
    KTRUE = 276,
    KFALSE = 277,
    OP_GT = 278,
    OP_LT = 279,
    OP_GE = 280,
    OP_LE = 281,
    OP_EQ = 282,
    OP_NEQ = 283,
    OP_AND = 284,
    OP_OR = 285,
    OP_NEG = 286,
    OP_INCR = 287,
    OP_DECR = 288,
    UMINUS = 289,
    UNEG = 290
  };
#endif
/* Tokens.  */
#define TINT 258
#define TCHAR 259
#define TNUMBER 260
#define TSTRING 261
#define TIDENTIFIER 262
#define TFUNC 263
#define KIF 264
#define KEND 265
#define KELSE 266
#define KWHILE 267
#define KDO 268
#define KBREAK 269
#define KCONTINUE 270
#define KWHEN 271
#define KFUNCTION 272
#define KFROM 273
#define KBOOL 274
#define KRETURN 275
#define KTRUE 276
#define KFALSE 277
#define OP_GT 278
#define OP_LT 279
#define OP_GE 280
#define OP_LE 281
#define OP_EQ 282
#define OP_NEQ 283
#define OP_AND 284
#define OP_OR 285
#define OP_NEG 286
#define OP_INCR 287
#define OP_DECR 288
#define UMINUS 289
#define UNEG 290

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (ast **root, void *scanner);

#endif /* !YY_YY_PARSE_H_INCLUDED  */
