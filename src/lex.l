%option noyywrap
%option warn

%{
#include "latino.h"

#define YY_INPUT(buf,result,max_size)  {\
    result = GetNextChar(buf, max_size); \
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
    BeginToken(yytext);
    }
{COMMENT} {
    /* ignore comments */
    BeginToken(yytext);
    return VALUE;
    }
{DIGIT}+  {
    BeginToken(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{DIGIT}+"."{DIGIT}*        {
    BeginToken(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{DIGIT}+[eE]["+""-"]?{DIGIT}*        {
    BeginToken(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{DIGIT}+"."{DIGIT}*[eE]["+""-"]?{DIGIT}*        {
    BeginToken(yytext);
    yylval.value = atof(yytext);
    return VALUE;
    }
{ID}        {
    BeginToken(yytext);
    yylval.string = malloc(strlen(yytext)+1);
    strcpy(yylval.string, yytext);
    return IDENTIFIER;
    }
"+"       { BeginToken(yytext); return ADD; }
"-"       { BeginToken(yytext); return SUB; }
"*"       { BeginToken(yytext); return MULT; }
"/"       { BeginToken(yytext); return DIV; }
"%"       { BeginToken(yytext); return MOD; }
"("       { BeginToken(yytext); return LBRACE; }
")"       { BeginToken(yytext); return RBRACE; }
";"       { BeginToken(yytext); return SEMICOLON; }
"="       { BeginToken(yytext); return ASSIGN; }
.         { BeginToken(yytext); return yytext[0]; }

%%
