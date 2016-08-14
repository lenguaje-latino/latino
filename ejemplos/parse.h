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
    VERDADERO = 258,
    FALSO = 259,
    ENTERO = 260,
    LITERAL = 261,
    NUMERO = 262,
    CADENA = 263,
    IDENTIFICADOR = 264,
    CONSTANTE = 265,
    FUNCION = 266,
    SI = 267,
    FIN = 268,
    SINO = 269,
    MIENTRAS = 270,
    HACER = 271,
    ROMPER = 272,
    CONTINUAR = 273,
    CUANDO = 274,
    FUNCION = 275,
    DESDE = 276,
    LOGICO = 277,
    RETORNO = 278,
    INCLUIR = 279,
    MAYOR_QUE = 280,
    MENOR_QUE = 281,
    MAYOR_IGUAL = 282,
    MENOR_IGUAL = 283,
    IGUAL_LOGICO = 284,
    DIFERENTE = 285,
    Y_LOGICO = 286,
    O_LOGICO = 287,
    INCREMENTO = 288,
    DECREMENTO = 289,
    CONCATENAR = 290,
    CONCATENAR_IGUAL = 291,
    OP_NEG = 292
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



int yyparse (ast **nodo, void *scanner);

#endif /* !YY_YY_PARSE_H_INCLUDED  */
