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
    TLIT = 259,
    TNUMBER = 260,
    TSTRING = 261,
    TIDENTIFIER = 262,
    TCONSTANT = 263,
    TFUNC = 264,
    KIF = 265,
    KEND = 266,
    KELSE = 267,
    KWHILE = 268,
    KDO = 269,
    KBREAK = 270,
    KCONTINUE = 271,
    KWHEN = 272,
    KFUNCTION = 273,
    KFROM = 274,
    KBOOL = 275,
    KRETURN = 276,
    KTRUE = 277,
    KFALSE = 278,
    OP_GT = 279,
    OP_LT = 280,
    OP_GE = 281,
    OP_LE = 282,
    OP_EQ = 283,
    OP_NEQ = 284,
    OP_AND = 285,
    OP_OR = 286,
    OP_NEG = 287,
    OP_INCR = 288,
    OP_DECR = 289,
    OP_CONCAT = 290,
    OP_CONCAT_IGUAL = 291,
    UMINUS = 292,
    UNEG = 293
  };
#endif

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
