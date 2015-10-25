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
    KSWITCH = 269,
    KCASE = 270,
    KBREAK = 271,
    KDEFAULT = 272,
    KWHEN = 273,
    KFUNCTION = 274,
    KFROM = 275,
    KBOOL = 276,
    KRETURN = 277,
    KTRUE = 278,
    KFALSE = 279,
    OP_GT = 280,
    OP_LT = 281,
    OP_GE = 282,
    OP_LE = 283,
    OP_EQ = 284,
    OP_NEQ = 285,
    OP_AND = 286,
    OP_OR = 287,
    OP_NEG = 288,
    UMINUS = 289,
    UNEG = 290
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
