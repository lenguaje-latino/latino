%option noyywrap
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
"+"       { begin_token(yytext); return ADD; }
"-"       { begin_token(yytext); return SUB; }
"*"       { begin_token(yytext); return MULT; }
"/"       { begin_token(yytext); return DIV; }
"%"       { begin_token(yytext); return MOD; }
"("       { begin_token(yytext); return LBRACE; }
")"       { begin_token(yytext); return RBRACE; }
";"       { begin_token(yytext); return SEMICOLON; }
"="       { begin_token(yytext); return ASSIGN; }
.         { begin_token(yytext); return yytext[0]; }

%%
