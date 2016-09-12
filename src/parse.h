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
    NUMERICO = 261,
    CADENA = 262,
    IDENTIFICADOR = 263,
    SI = 264,
    FIN = 265,
    SINO = 266,
    MIENTRAS = 267,
    HACER = 268,
    ROMPER = 269,
    CONTINUAR = 270,
    CUANDO = 271,
    FUNCION = 272,
    DESDE = 273,
    KBOOL = 274,
    RETORNO = 275,
    INCLUIR = 276,
    ELEGIR = 277,
    CASO = 278,
    DEFECTO = 279,
    ATRIBUTO = 280,
    MAYOR_QUE = 281,
    MENOR_QUE = 282,
    MAYOR_IGUAL = 283,
    MENOR_IGUAL = 284,
    IGUAL_LOGICO = 285,
    DIFERENTE = 286,
    Y_LOGICO = 287,
    O_LOGICO = 288,
    INCREMENTO = 289,
    DECREMENTO = 290,
    CONCATENAR = 291,
    CONCATENAR_IGUAL = 292
  };
#endif
/* Tokens.  */
#define VERDADERO 258
#define FALSO 259
#define ENTERO 260
#define NUMERICO 261
#define CADENA 262
#define IDENTIFICADOR 263
#define SI 264
#define FIN 265
#define SINO 266
#define MIENTRAS 267
#define HACER 268
#define ROMPER 269
#define CONTINUAR 270
#define CUANDO 271
#define FUNCION 272
#define DESDE 273
#define KBOOL 274
#define RETORNO 275
#define INCLUIR 276
#define ELEGIR 277
#define CASO 278
#define DEFECTO 279
#define ATRIBUTO 280
#define MAYOR_QUE 281
#define MENOR_QUE 282
#define MAYOR_IGUAL 283
#define MENOR_IGUAL 284
#define IGUAL_LOGICO 285
#define DIFERENTE 286
#define Y_LOGICO 287
#define O_LOGICO 288
#define INCREMENTO 289
#define DECREMENTO 290
#define CONCATENAR 291
#define CONCATENAR_IGUAL 292

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
