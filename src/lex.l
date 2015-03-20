%option yylineno
%option noyywrap
%option warn
%option nodefault

%{
#include <string.h>
#include <stdlib.h>
#include "latino.h"
#include "structs.h"

#define YY_INPUT(buf,result,max_size)  {\
    result = get_next_char(buf, max_size); \
    if (  result <= 0  ) \
      result = YY_NULL; \
    }
%}

 /* float exponent */
EXP ([Ee][-+]?[0-9]+)

%%

 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"%" |
"(" |
")" |
"," |
"|" |
";" |
"="     { return yytext[0]; }

 /* comparison ops, all are CMP token */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"!="    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }
"V"     { yylval.fn = 7; return CMP; }
"F"     { yylval.fn = 8; return CMP; }

 /* keywords */
"si"        { return KEYWORD_IF; }
"fin"       { return KEYWORD_END; }
"sino"      { return KEYWORD_ELSE; }
"mientras"  { return KEYWORD_WHILE; }
"hacer"     { return KEYWORD_DO; }
"cuando"    { return KEYWORD_WHEN; }
"funcion"   {  return KEYWORD_FUNCTION; }
"verdadero"   { yylval.b = yytext; return KEYWORD_TRUE; }
"falso"   { yylval.b = yytext; return KEYWORD_FALSE; }
"logico"   { return KEYWORD_BOOL; }
"entero"   { return KEYWORD_INT; }
"decimal"   { return KEYWORD_DECIMAL; }
"caracter"   { return KEYWORD_CHAR; }
"cadena"   { return KEYWORD_STRING; }

 /*built-in functions */
"raiz"          { yylval.fn = B_sqrt; return TOKEN_FUNC; }
"exponente"     { yylval.fn = B_exp; return TOKEN_FUNC; }
"logaritmo"     { yylval.fn = B_log; return TOKEN_FUNC; }
"imprimir"      { yylval.fn = B_print; return TOKEN_FUNC; }

 /* names */
[_a-zA-Z][_a-zA-Z0-9]* { yylval.s = lookup(yytext); return TOKEN_IDENTIFIER; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?       { yylval.d = strtod(yytext, NULL);
                         return TOKEN_NUMBER; }
\"([^\\\"]|\\.)*\"     { yylval.str = newstr(yytext+1, strlen(yytext)-2);return TOKEN_STRING; }
'([^'\\\n]|\\.)'       { yylval.c = newchar(yytext+1, strlen(yytext)-2); return TOKEN_CHAR; }
"#".* /* ignore comments */
\\\n                   { ; } /* ignore line continuation */
[ \t\n] /* ignore whitespace  tabs and eol */
 /*.                      { printf("error lexico %s ", yytext); }*/
.                      {;}

%%
