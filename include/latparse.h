/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_LATPARSE_H_INCLUDED
#define YY_YY_LATPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype {
    NUMERICO = 258,
    CADENA = 259,
    IDENTIFICADOR = 260,
    VAR_ARGS = 261,
    SI = 262,
    O_SI = 263,
    FIN = 264,
    SINO = 265,
    MIENTRAS = 266,
    REPETIR = 267,
    ROMPER = 268,
    CONTINUAR = 269,
    HASTA = 270,
    FUNCION = 271,
    DESDE = 272,
    RETORNO = 273,
    ELEGIR = 274,
    CASO = 275,
    DEFECTO = 276,
    ATRIBUTO = 277,
    VERDADERO = 278,
    FALSO = 279,
    NULO = 280,
<<<<<<< HEAD
    EXPONENTE = 281,
    PARA = 282,
    EN = 283,
    RANGO = 284,
    MAYOR_QUE = 285,
    MENOR_QUE = 286,
    MAYOR_IGUAL = 287,
    MENOR_IGUAL = 288,
    IGUAL_LOGICO = 289,
    DIFERENTE = 290,
    Y_LOGICO = 291,
    O_LOGICO = 292,
    INCREMENTO = 293,
    DECREMENTO = 294,
    CONCATENAR = 295,
    CONCATENAR_IGUAL = 296,
    MAS_IGUAL = 297,
    MENOS_IGUAL = 298,
    POR_IGUAL = 299,
    ENTRE_IGUAL = 300,
    MODULO_IGUAL = 301,
    REGEX = 302,
    GLOBAL = 303
  };
=======
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
    CONCATENAR_IGUAL = 292,
    MAS_IGUAL = 293,
    MENOS_IGUAL = 294,
    POR_IGUAL = 295,
    ENTRE_IGUAL = 296,
    MODULO_IGUAL = 297,
    REGEX = 298,
    GLOBAL = 299
};
>>>>>>> 9e7c3d9aa5d238a80d09553b9ceabc7ba57941ca
#endif
/* Tokens.  */
#define NUMERICO 258
#define CADENA 259
#define IDENTIFICADOR 260
#define VAR_ARGS 261
#define SI 262
#define O_SI 263
#define FIN 264
#define SINO 265
#define MIENTRAS 266
#define REPETIR 267
#define ROMPER 268
#define CONTINUAR 269
#define HASTA 270
#define FUNCION 271
#define DESDE 272
#define RETORNO 273
#define ELEGIR 274
#define CASO 275
#define DEFECTO 276
#define ATRIBUTO 277
#define VERDADERO 278
#define FALSO 279
#define NULO 280
#define EXPONENTE 281
#define PARA 282
#define EN 283
#define RANGO 284
#define MAYOR_QUE 285
#define MENOR_QUE 286
#define MAYOR_IGUAL 287
#define MENOR_IGUAL 288
#define IGUAL_LOGICO 289
#define DIFERENTE 290
#define Y_LOGICO 291
#define O_LOGICO 292
#define INCREMENTO 293
#define DECREMENTO 294
#define CONCATENAR 295
#define CONCATENAR_IGUAL 296
#define MAS_IGUAL 297
#define MENOS_IGUAL 298
#define POR_IGUAL 299
#define ENTRE_IGUAL 300
#define MODULO_IGUAL 301
#define REGEX 302
#define GLOBAL 303

/* Value type.  */

/* Location type.  */
#if !defined YYLTYPE && !defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
#endif

int yyparse(ast **root, void *scanner);

#endif /* !YY_YY_LATPARSE_H_INCLUDED  */
