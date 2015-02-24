%option yylineno
%option noyywrap
%option warn
%option nodefault

%{
#include "latino.h"

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
"V"    { yylval.fn = 7; return CMP; }
"F"    { yylval.fn = 8; return CMP; }

 /* keywords */
"si"        { return IF; }
"fin"        { return END; }
"sino"      { return ELSE; }
"mientras"   { return WHILE; }
"hacer"     { return DO; }
"funcion"   { return FUNCTION; }
"let"   { return LET; }

 /*built-in functions */
"raiz"          { yylval.fn = B_sqrt; return FUNC; }
"exponente"           { yylval.fn = B_exp; return FUNC; }
"logaritmo"           { yylval.fn = B_log; return FUNC; }
"imprimir"      { yylval.fn = B_print; return FUNC; }

 /* names */
[_a-zA-Z][_a-zA-Z0-9]* { yylval.s = lookup(yytext); return NAME; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }
"#".* /* ignore comments */
\\\n { ; } /* ignore line continuation */
[ \t\n] /* ignore whitespace  tabs and eol */
.       { ; }

%%
