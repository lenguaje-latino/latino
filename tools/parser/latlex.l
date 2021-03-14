%option nounistd
%option outfile="latlex.c" header-file="latlex.h"
%option warn nodefault
%option reentrant noyywrap never-interactive
%option bison-bridge bison-locations
%option yylineno
%option extra-type="struct lex_state *"
%option nounput

%{

  /*
 The MIT License (MIT)

 Copyright (c) Latino - Lenguaje de Programacion

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
  */

/* flex -olex.c -i lex.l */
#include <string.h>
#include <stdlib.h>

#include "latast.h"
#include "latparse.h"

#define YY_NO_INPUT
#define YYBISON 1

#define YY_USER_ACTION \
    yylloc->file_name = filename;\
    yylloc->first_line = yylloc->last_line+1; \
    yylloc->first_column = yylloc->last_column+1; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#if YYBISON
union YYSTYPE;
extern int yylex (YYSTYPE * yylval_param,YYLTYPE * yylloc_param ,yyscan_t yyscanner);
#endif

%}

 /* exponente de punto flotante */
EXP ([Ee][-+]?[0-9]+)

%%

 /* operadores de un solo caracter */
"+" |
"-" |
"*" |
"/" |
"%" |
"(" |
")" |
"," |
";" |
"[" |
"]" |
"{" |
"}" |
"?" |
":" |
"!" |
"^" |
"="                                             { return yytext[0]; }

 /* operadores de comparacion y demas*/
"..."                                           { yylval->node = latA_nodo(NODO_VAR_ARGS, NULL, NULL, yylloc->first_line, yylloc->first_column); return VAR_ARGS; }
">="                                            { return MAYOR_IGUAL; }
"<="                                            { return MENOR_IGUAL; }
"!="                                            { return DIFERENTE; }
"=="                                            { return IGUAL_LOGICO; }
"&&"                                            { return Y_LOGICO; }
"||"                                            { return O_LOGICO; }
".."                                            { return CONCATENAR; }
"..="                                           { return CONCATENAR_IGUAL; }
"+="                                            { return MAS_IGUAL; }
"-="                                            { return MENOS_IGUAL; }
"*="                                            { return POR_IGUAL; }
"/="                                            { return ENTRE_IGUAL; }
"%="                                            { return MODULO_IGUAL; }
"~="                                            { return REGEX; }
">"                                             { return MAYOR_QUE; }
"<"                                             { return MENOR_QUE; }
"++"                                            { return INCREMENTO; }
"--"                                            { return DECREMENTO; }
"."                                             { return ATRIBUTO; }
"**"                                            { return EXPONENTE; }
 /* palabras reservadas */
"si"                                            { return SI; }
"osi"                                           { return O_SI; }
"fin"                                           { return FIN; }
"sino"                                          { return SINO; }
"romper"                                        { return ROMPER; }
"continuar"                                     { return CONTINUAR; }
"mientras"                                      { return MIENTRAS; }
"repetir"                                       { return REPETIR; }
"hasta"                                         { return HASTA; }
"funcion"|"fun"                                 { return FUNCION; }
"desde"                                         { return DESDE; }
"cierto"|"verdadero"                            { return VERDADERO; }
"falso"                                         { return FALSO; }
"nulo"                                          { return NULO; }
"retorno"|"retornar"|"ret"                      { return RETORNO; }
"elegir"                                        { return ELEGIR; }
"caso"                                          { return CASO; }
"otro"|"defecto"                                { return DEFECTO; }
"global"                                        { return GLOBAL; }
"para"                                          { return PARA; }
"en"                                            { return EN; }
"rango"                                         { return RANGO; }
"ir"                                            { return IR; }

 /* names */
[_A-Z]*                                         { yylval->node = latA_var(yytext, yylloc->first_line, yylloc->first_column, 1); return IDENTIFICADOR; }
[_a-zA-Z][_a-zA-Z0-9]*                          { yylval->node = latA_var(yytext, yylloc->first_line, yylloc->first_column, 0); return IDENTIFICADOR; }
[0-9]+|[0-9]+"."[0-9]*{EXP}?|"."[0-9]+{EXP}?    { yylval->node = latA_numerico(strtod(yytext, NULL), yylloc->first_line, yylloc->first_column); return NUMERICO; }
\"([^\\\"]|\\.)*\"                              { yytext[strlen(yytext) - 1] = '\0'; yylval->node = latA_cadena(yytext+1, yylloc->first_line, yylloc->first_column); return CADENA; }
'([^\\\']|\\.)*'                                { yytext[strlen(yytext) - 1] = '\0'; yylval->node = latA_literal(yytext+1, yylloc->first_line, yylloc->first_column); return CADENA; }
"#".*                                           { ; }  /* comentario de una linea estilo python */
"//".*                                          { ; }  /* comentario de una linea estilo c/c++ */
"/*"([^*]|(\*+[^*/]))*\*+\/                     { ; }  /* comentarios multilinea estilo c/c++ */
[\n\r]                                          { ; }  /* ignora saltos de linea */
[\t]+                                           { ; }  /* ignora espacios en blanco y tabuladores */
.                                               { ; }  /* ignora caracteres incorrectos */

%%
/*"clase"                                         { return CLASS; }*/