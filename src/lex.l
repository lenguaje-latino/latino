%option nounistd
%option outfile="lex.c" header-file="lex.h"
%option warn nodefault
%option reentrant noyywrap never-interactive
%option bison-bridge bison-locations
%option yylineno
%option extra-type="struct lex_state *"
%option nounput

%{

/* flex -olex.c -i lex.l */
#include <string.h>
#include <stdlib.h>

#include "latino.h"
#include "ast.h"
#include "parse.h"

#define YY_NO_INPUT
#define YYBISON 1

#define YY_USER_ACTION \
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

int f(int token, yyscan_t scanner);

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
"="     { return yytext[0]; }

 /* operadores de comparacion y demas*/
">="    { return MAYOR_IGUAL; }
"<="    { return MENOR_IGUAL; }
"!="    { return DIFERENTE; }
"=="    { return IGUAL_LOGICO; }
"&&"    { return Y_LOGICO; }
"||"    { return O_LOGICO; }
"."     { return CONCATENAR; }
".="    { return CONCATENAR_IGUAL; }
"+="    { return MAS_IGUAL; }
"-="    { return MENOS_IGUAL; }
"*="    { return POR_IGUAL; }
"/="    { return ENTRE_IGUAL; }
"%="    { return MODULO_IGUAL; }
">"     { return MAYOR_QUE; }
"<"     { return MENOR_QUE; }
"++"	  { return INCREMENTO; }
"--"	  { return DECREMENTO; }
"->"	  { return ATRIBUTO; }

 /* palabras reservadas */
"si"        { return SI; }
"fin"       { return FIN; }
"sino"      { return SINO; }
"romper"    { return ROMPER; }
"continuar" { return CONTINUAR; }
"mientras"  { return MIENTRAS; }
"hacer"     { return HACER; }
"cuando"    { return CUANDO; }
"funcion"   { return FUNCION; }
"desde"     { return DESDE; }
"verdadero" { yylval->node = nodo_nuevo_logico(1, yylloc->first_line, yylloc->first_column); return VERDADERO; }
"cierto"    { yylval->node = nodo_nuevo_logico(1, yylloc->first_line, yylloc->first_column); return VERDADERO; }
"falso"     { yylval->node = nodo_nuevo_logico(0, yylloc->first_line, yylloc->first_column); return FALSO; }
"nulo"      { yylval->node = nodo_nuevo_nulo(NULL, yylloc->first_line, yylloc->first_column); return NULO; }
"retorno"   { return RETORNO; }
"incluir"   { return INCLUIR; }
"elegir"    { return ELEGIR; }
"caso"      { return CASO; }
"defecto"   { return DEFECTO; }

 /* names */
[_A-Z]*             { yylval->node = nodo_nuevo_identificador(yytext, yylloc->first_line, yylloc->first_column, 1); return IDENTIFICADOR; }
[_a-zA-Z][_a-zA-Z0-9]* { yylval->node = nodo_nuevo_identificador(yytext, yylloc->first_line, yylloc->first_column, 0); return IDENTIFICADOR; }
[0-9]+"."[0-9]*{EXP}?|"."[0-9]+{EXP}?       { yylval->node = nodo_nuevo_numerico(strtod(yytext, NULL), yylloc->first_line, yylloc->first_column); return NUMERICO; }
[0-9]+                 { yylval->node = nodo_nuevo_numerico(strtod(yytext, NULL), yylloc->first_line, yylloc->first_column); return ENTERO; }
\"([^\\\"]|\\.)*\"     { yytext[strlen(yytext) - 1] = '\0'; yylval->node = nodo_nuevo_cadena(yytext+1, yylloc->first_line, yylloc->first_column); return CADENA; }
'([^\\\']|\\.)*'       { yytext[strlen(yytext) - 1] = '\0'; yylval->node = nodo_nuevo_cadena(yytext+1, yylloc->first_line, yylloc->first_column); return CADENA; }
"#".*                  { ; }  /* comentario de una linea estilo python */
"//".*                 { ; }  /* comentario de una linea estilo c/c++ */
"/*"([^*]|(\*+[^*/]))*\*+\/ { ; } /* comentarios multilinea estilo c/c++ */
[\n\r]                 { ; }  /* ignora saltos de linea */
[ \t]+                 { ; } /* ignora espacios en blanco y tabuladores */
.                      { ; } /* ignora caracteres incorrectos */

%%
