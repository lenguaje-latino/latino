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

 /* keywords */
"si"        { return IF; }
"entonces"        { return IF; }
"sino"      { return ELSE; }
"mientras"   { return WHILE; }
"hacer"     { return DO; }
"funcion"   { return FUNCTION; }
"let"   { return LET; }

 /*built-in functions */
"sqrt"          { yylval.fn = B_sqrt; return FUNC; }
"exp"           { yylval.fn = B_exp; return FUNC; }
"log"           { yylval.fn = B_log; return FUNC; }
"print"      { yylval.fn = B_print; return FUNC; }

 /* names */
[_a-zA-Z][_a-zA-Z0-9]* { yylval.s = lookup(yytext); return NAME; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }
"#".* /* ignore comments */
\\\n { printf("c> "); } /* ignore line continuation */
[ \t] /* ignore whitespace */
\n { return EOL; }
.       { yyerror("Mystery character %c\n", *yytext); }

%%
