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
    TOKEN_INT = 258,
    TOKEN_CHAR = 259,
    TOKEN_NUMBER = 260,
    TOKEN_STRING = 261,
    TOKEN_IDENTIFIER = 262,
    TOKEN_FUNC = 263,
    KEYWORD_IF = 264,
    KEYWORD_END = 265,
    KEYWORD_ELSE = 266,
    KEYWORD_WHILE = 267,
    KEYWORD_DO = 268,
    KEYWORD_SWITCH = 269,
    KEYWORD_CASE = 270,
    KEYWORD_BREAK = 271,
    KEYWORD_DEFAULT = 272,
    KEYWORD_WHEN = 273,
    KEYWORD_FUNCTION = 274,
    KEYWORD_FROM = 275,
    KEYWORD_TO = 276,
    KEYWORD_STEP = 277,
    KEYWORD_BOOL = 278,
    KEYWORD_RETURN = 279,
    KEYWORD_TRUE = 280,
    KEYWORD_FALSE = 281,
    OP_GT = 282,
    OP_LT = 283,
    OP_GE = 284,
    OP_LE = 285,
    OP_EQ = 286,
    OP_NEQ = 287,
    OP_AND = 288,
    OP_OR = 289,
    OP_NEG = 290,
    UMINUS = 291,
    UNEG = 292
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
