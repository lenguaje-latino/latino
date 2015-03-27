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
"="     { return yytext[0]; }

 /* comparison ops, all are CMP token */
">"     { yylval.fn = NODE_GREATER_THAN; return CMP; }
"<"     { yylval.fn = NODE_LESS_THAN; return CMP; }
"!="    { yylval.fn = NODE_NOT_EQUAL; return CMP; }
"=="    { yylval.fn = NODE_EQUAL; return CMP; }
">="    { yylval.fn = NODE_GREATER_THAN_EQUAL; return CMP; }
"<="    { yylval.fn = NODE_LESS_THAN_EQUAL; return CMP; }

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
.                      { ; }

%%
