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
    NUMERICO = 262,
    CADENA = 263,
    IDENTIFICADOR = 264,
    CONSTANTE = 265,
    SI = 266,
    FIN = 267,
    SINO = 268,
    MIENTRAS = 269,
    ROMPER = 270,
    CONTINUAR = 271,
    DESDE = 272,
    REPETIR = 273,
    HASTA = 274,
    POR = 275,
    EN = 276,
    FUNCION = 277,
    RETORNO = 278,
    INCLUIR = 279,
    ELEGIR = 280,
    CASO = 281,
    DEFECTO = 282,
    CLASE = 283,
    MAYOR_QUE = 284,
    MENOR_QUE = 285,
    MAYOR_IGUAL = 286,
    MENOR_IGUAL = 287,
    IGUAL_LOGICO = 288,
    DIFERENTE = 289,
    Y_LOGICO = 290,
    O_LOGICO = 291
  };
#endif
/* Tokens.  */
#define VERDADERO 258
#define FALSO 259
#define ENTERO 260
#define LITERAL 261
#define NUMERICO 262
#define CADENA 263
#define IDENTIFICADOR 264
#define CONSTANTE 265
#define SI 266
#define FIN 267
#define SINO 268
#define MIENTRAS 269
#define ROMPER 270
#define CONTINUAR 271
#define DESDE 272
#define REPETIR 273
#define HASTA 274
#define POR 275
#define EN 276
#define FUNCION 277
#define RETORNO 278
#define INCLUIR 279
#define ELEGIR 280
#define CASO 281
#define DEFECTO 282
#define CLASE 283
#define MAYOR_QUE 284
#define MENOR_QUE 285
#define MAYOR_IGUAL 286
#define MENOR_IGUAL 287
#define IGUAL_LOGICO 288
#define DIFERENTE 289
#define Y_LOGICO 290
#define O_LOGICO 291

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
