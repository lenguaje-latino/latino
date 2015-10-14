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
"="     { return yytext[0]; }

 /* comparison ops, all are CMP token */
">"     { return OP_GT; }
"<"     { return OP_LT; }
">="    { return OP_GE; }
"<="    { return OP_LE; }
"!="    { return OP_NEQ; }
"=="    { return OP_EQ; }
"&&"    { return OP_AND; }
"||"    { return OP_OR; }
"!"     { return OP_NEG; }

 /* keywords */
"si"        { return KEYWORD_IF; }
"fin"       { return KEYWORD_END; }
"sino"      { return KEYWORD_ELSE; }
"romper"    { return KEYWORD_BREAK; }
"mientras"  { return KEYWORD_WHILE; }
"hacer"     { return KEYWORD_DO; }
"cuando"    { return KEYWORD_WHEN; }
"funcion"   {  return KEYWORD_FUNCTION; }
"elegir"    {  return KEYWORD_SWITCH; }
"caso"      {  return KEYWORD_CASE; }
"defecto"   {  return KEYWORD_DEFAULT; }
"desde"     {  return KEYWORD_FROM; }
"verdadero" { return KEYWORD_TRUE; }
"falso"     { return KEYWORD_FALSE; }
"retorno"   { return KEYWORD_RETURN; }

 /* names */
[_a-zA-Z][_a-zA-Z0-9]* { yylval->node = newRef(yytext); return TOKEN_IDENTIFIER; }
[0-9]+"."+[0-9]*{EXP}?|"."+[0-9]+{EXP}?       { yylval->node = newNum(strtod(yytext, NULL)); return TOKEN_NUMBER; }
[0-9]+                 { yylval->node = newInt(strtol(yytext, NULL, 0)); return TOKEN_INT; }
\"([^\\\"]|\\.)*\"     { yylval->node = newStr(yytext+1, strlen(yytext)-2);return TOKEN_STRING; }
'([^'\\\n]|\\.)'       { yylval->node = newChar(yytext+1, strlen(yytext)-2); return TOKEN_CHAR; }
"#".* /* ignore comments */
[ \t\v\n\f]                { ; } /* ignore whitespace tabs and eol */
.                      { ; } /* ignore bad characters */

%%
