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

#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = yylineno;

int f(int token, yyscan_t scanner);

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
":" |
";" |
"[" |
"]" |
"{" |
"}" |
"="     { return yytext[0]; }

 /* comparison operators */
">"     { return OP_GT; }
"<"     { return OP_LT; }
">="    { return OP_GE; }
"<="    { return OP_LE; }
"!="    { return OP_NEQ; }
"=="    { return OP_EQ; }
"&&"    { return OP_AND; }
"||"    { return OP_OR; }
"!"     { return OP_NEG; }

"++"	{ return OP_INCR; }
"--"	{ return OP_DECR; }

 /* keywords */
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
"verdadero" { return KTRUE; }
"falso"     { return KFALSE; }
"retorno"   { return KRETURN; }

 /*"elegir"    { return KSWITCH; }
 "caso"      { return KCASE; }
 "defecto"   { return KDEFAULT; }*/

 /* names */
[_a-zA-Z][_a-zA-Z0-9]* { yylval->node = newRef(yytext); return TIDENTIFIER; }
[0-9]+"."+[0-9]*{EXP}?|"."+[0-9]+{EXP}?       { yylval->node = newNum(strtod(yytext, NULL)); return TNUMBER; }
[0-9]+                 { yylval->node = newInt(strtol(yytext, NULL, 0)); return TINT; }
\"([^\\\"]|\\.)*\"     { yytext[strlen(yytext) - 1] = '\0'; yylval->node = newStr(yytext+1);return TSTRING; }
'([^'\\\n]|\\.)'       { yylval->node = newChar(yytext+1, strlen(yytext)-2); return TCHAR; }
"#".* /* ignore comments */
\n                     { ; } /*ignore end of line */
[ \t]+                 { ; } /* ignore whitespace tabs */
.                      { ; } /* ignore bad characters */

%%
