%option nounistd
%option outfile="lex.c" header-file="lex.h"
%option warn nodefault
%option reentrant noyywrap never-interactive
%option bison-bridge bison-locations
%option yylineno
%option extra-type="struct lex_state *"

%{

/* flex -olex.c -i lex.l */
#include <string.h>
#include <stdlib.h>

#include "latino.h"
#include "ast.h"
#include "parse.h"

#define YYBISON 1

#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
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
":" |
";" |
"[" |
"]" |
"{" |
"}" |
"?" |
"="     { return yytext[0]; }

 /* operadores de comparacion */
">"     { return OP_GT; }
"<"     { return OP_LT; }
">="    { return OP_GE; }
"<="    { return OP_LE; }
"!="    { return OP_NEQ; }
"=="    { return OP_EQ; }
"&&"    { return OP_AND; }
"||"    { return OP_OR; }
".="    { return OP_CONCAT_IGUAL; }
"."     { return OP_CONCAT; }

"++"	{ return OP_INCR; }
"--"	{ return OP_DECR; }

 /* palabras reservadas */
"si"        { return KIF; }
"fin"       { return KEND; }
"sino"      { return KELSE; }
"romper"    { return KBREAK; }
"continuar" { return KCONTINUE; }
"mientras"  { return KWHILE; }
"hacer"     { return KDO; }
"cuando"    { return KWHEN; }
"funcion"   { return KFUNCTION; }
"desde"     { return KFROM; }
"verdadero" { yylval->node = nodo_nuevo_logico(1, yylloc->first_line, yylloc->first_column); return TTRUE; }
"cierto" { yylval->node = nodo_nuevo_logico(1, yylloc->first_line, yylloc->first_column); return TTRUE; }
"falso"     { yylval->node = nodo_nuevo_logico(0, yylloc->first_line, yylloc->first_column); return TFALSE; }
"retorno"   { return KRETURN; }
"incluir"   { return KINCLUDE; }

 /*"elegir"    { return KSWITCH; }
 "caso"      { return KCASE; }
 "defecto"   { return KDEFAULT; }*/

 /* names */
[_A-Z][_A-Z0-9]*       { yylval->node = nodo_nuevo_constante(yytext, yylloc->first_line, yylloc->first_column); return TCONSTANT; }
[_a-zA-Z][_a-zA-Z0-9]* { yylval->node = nodo_nuevo_identificador(yytext, yylloc->first_line, yylloc->first_column); return TIDENTIFIER; }
[0-9]+"."+[0-9]*{EXP}?|"."+[0-9]+{EXP}?       { yylval->node = nodo_nuevo_decimal(strtod(yytext, NULL), yylloc->first_line, yylloc->first_column); return TNUMBER; }
[0-9]+                 { yylval->node = nodo_nuevo_entero(strtol(yytext, NULL, 0), yylloc->first_line, yylloc->first_column); return TINT; }
\"([^\\\"]|\\.)*\"     { yytext[strlen(yytext) - 1] = '\0'; yylval->node = nodo_nuevo_cadena(yytext+1, yylloc->first_line, yylloc->first_column); return TSTRING; }
'([^\\\']|\\.)*'       { yytext[strlen(yytext) - 1] = '\0'; yylval->node = nodo_nuevo_literal(yytext+1, yylloc->first_line, yylloc->first_column); return TLIT; }
"#".* /* ignore comments */
[\n]                   { yycolumn = 1; }
[ \t]+                 { ; } /* ignora espacios en blanco y tabuladores */
.                      { ; } /* ignora caracteres incorrectos */

%%
