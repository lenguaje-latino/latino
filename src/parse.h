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
    VERDADERO = 258,
    FALSO = 259,
    ENTERO = 260,
    LITERAL = 261,
    _DECIMAL = 262,
    CADENA = 263,
    IDENTIFICADOR = 264,
    CONSTANTE = 265,
    SI = 266,
    FIN = 267,
    SINO = 268,
    MIENTRAS = 269,
    HACER = 270,
    ROMPER = 271,
    CONTINUAR = 272,
    CUANDO = 273,
    FUNCION = 274,
    DESDE = 275,
    KBOOL = 276,
    RETORNO = 277,
    INCLUIR = 278,
    ELEGIR = 279,
    CASO = 280,
    DEFECTO = 281,
    MAYOR_QUE = 282,
    MENOR_QUE = 283,
    MAYOR_IGUAL = 284,
    MENOR_IGUAL = 285,
    IGUAL_LOGICO = 286,
    DIFERENTE = 287,
    Y_LOGICO = 288,
    O_LOGICO = 289,
    INCREMENTO = 290,
    DECREMENTO = 291,
    CONCATENAR = 292,
    CONCATENAR_IGUAL = 293
  };
#endif
/* Tokens.  */
#define VERDADERO 258
#define FALSO 259
#define ENTERO 260
#define LITERAL 261
#define _DECIMAL 262
#define CADENA 263
#define IDENTIFICADOR 264
#define CONSTANTE 265
#define SI 266
#define FIN 267
#define SINO 268
#define MIENTRAS 269
#define HACER 270
#define ROMPER 271
#define CONTINUAR 272
#define CUANDO 273
#define FUNCION 274
#define DESDE 275
#define KBOOL 276
#define RETORNO 277
#define INCLUIR 278
#define ELEGIR 279
#define CASO 280
#define DEFECTO 281
#define MAYOR_QUE 282
#define MENOR_QUE 283
#define MAYOR_IGUAL 284
#define MENOR_IGUAL 285
#define IGUAL_LOGICO 286
#define DIFERENTE 287
#define Y_LOGICO 288
#define O_LOGICO 289
#define INCREMENTO 290
#define DECREMENTO 291
#define CONCATENAR 292
#define CONCATENAR_IGUAL 293

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
