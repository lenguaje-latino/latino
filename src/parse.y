%{
#include "latino.h"

#define YYERROR_VERBOSE 1

static Variable *var;
%}

%defines
%union {
    double value;
    char *string;
}

%token COMMENT
%token <string> T_DECIMAL
%token <string>   IDENTIFIER
%token <value>    VALUE
%type <value> expression

%token LBRACE
%token RBRACE
%token ASSIGN
%token SEMICOLON

/*
 * presedencia de operadores
 * 0: -
 * 1: * /
 * 2: + -
 *
 */

%left ADD SUB
%left MULT DIV MOD
%left NEG


%start program

%%


program
    : statement
    | COMMENT
    | statement program
    | statement error program
      {
      yyerrok;
      }
    ;

statement
    : IDENTIFIER
      {
        var = VarGet($1, &@1);
      }
      ASSIGN expression
      {
        VarSetValue(var, $4);
      }
    | expression
    ;

expression
    : LBRACE expression RBRACE
      {
        $$ = $2;
      }
    | SUB expression %prec NEG
      {
        $$ = - $2;
      }
    | expression ADD expression
      {
        $$ = ReduceAdd($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf + %lf => %lf\n", $1, $3, $$);
      }
    | expression SUB expression
      {
        $$ = ReduceSub($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf - %lf => %lf\n", $1, $3, $$);
      }
    | expression MULT expression
      {
        $$ = ReduceMult($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf * %lf => %lf\n", $1, $3, $$);
      }
    | expression DIV expression
      {
        $$ = ReduceDiv($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf / %lf => %lf\n", $1, $3, $$);
      }
    | expression MOD expression
      {
        $$ = ReduceMod($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf % %lf => %lf\n", $1, $3, $$);
      }
    | VALUE
      {
        $$ = $1;
      }
    | IDENTIFIER
      {
        $$ = VarGetValue($1, &@1);
        if (  debug  )
          printf("identifier %s => %lf\n", $1, $$);
      }
    ;

%%

extern
void yyerror(char *s)
{
    PrintError(s);
}

