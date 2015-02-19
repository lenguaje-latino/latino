%{
#include "latino.h"

#define YYERROR_VERBOSE 1

static variable *var;
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
        var = var_get($1, &@1);
      }
      ASSIGN expression
      {
        var_set_value(var, $4);
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
        $$ = reduce_add($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf + %lf => %lf\n", $1, $3, $$);
      }
    | expression SUB expression
      {
        $$ = reduce_sub($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf - %lf => %lf\n", $1, $3, $$);
      }
    | expression MULT expression
      {
        $$ = reduce_mult($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf * %lf => %lf\n", $1, $3, $$);
      }
    | expression DIV expression
      {
        $$ = reduce_div($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf / %lf => %lf\n", $1, $3, $$);
      }
    | expression MOD expression
      {
        $$ = reduce_mod($1, $3, &@3);
        if (  debug  )
          printf("reduce %lf % %lf => %lf\n", $1, $3, $$);
      }
    | VALUE
      {
        $$ = $1;
      }
    | IDENTIFIER
      {
        $$ = var_get_value($1, &@1);
        if (  debug  )
          printf("identifier %s => %lf\n", $1, $$);
      }
    ;

%%

extern
void yyerror(char *s)
{
    print_error(s);
}
