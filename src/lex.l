%option warn

%{
#include "latino.h"

#define YY_INPUT(buf,result,max_size)  {\
    result = get_next_char(buf, max_size); \
    if (  result <= 0  ) \
      result = YY_NULL; \
    }
%}

/*--------------------------------------------------------------------
 *
 * flex definitions
 *
 *------------------------------------------------------------------*/
DIGIT    [0-9]
ID       [_a-zA-Z][_a-zA-Z0-9]*
IGNORE   [ \t\r\n]+
COMMENT  "#".*

%%

{IGNORE} {
    /* eat up whitespace */
    begin_token(yytext);
    }
{COMMENT} {
    /* ignore comments */
    begin_token(yytext);
    return VALUE;
    }
{DIGIT}+  {
    begin_token(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{DIGIT}+"."{DIGIT}*        {
    begin_token(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{DIGIT}+[eE]["+""-"]?{DIGIT}*        {
    begin_token(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{DIGIT}+"."{DIGIT}*[eE]["+""-"]?{DIGIT}*        {
    begin_token(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{ID}        {
    begin_token(yytext);
    yylval.string = malloc(strlen(yytext)+1);
    strcpy(yylval.string, yytext);
    return IDENTIFIER;
    }

 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"%" |
"(" |
")" |
";" |
"="     { return yytext[0];}

 /* comparison ops, all are CMP token */
">"     { yylval.fn = 1; return CMP; } 
"<"     { yylval.fn = 2; return CMP; } 
"!="    { yylval.fn = 3; return CMP; } 
"=="    { yylval.fn = 4; return CMP; } 
">="    { yylval.fn = 5; return CMP; } 
"<="    { yylval.fn = 6; return CMP; } 

 /* keywords */

"si"        { return IF; }
"sino"      { return ELSE; }
"mietras"   { return WHILE; }
"hacer"     { return DO; }
"decimal"   { return LET; }

 /* built-in functions */
"raiz"          { yylval.fn = B_sqrt; return FUNC; }
"exp"           { yylval.fn = B_exp; return FUNC; }
"log"           { yylval.fn = B_log; return FUNC; }
"imprimir"      { yylval.fn = B_print; return FUNC; }

.       { begin_token(yytext); return yytext[0]; }

%%
