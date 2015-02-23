%{
#include <stdio.h>
#include <stdlib.h>
#include "latino.h"

#define YYERROR_VERBOSE 1

static variable *var;
%}

%defines
%union {
    struct ast *a;
    double d;
    struct symbol *s;   /* which symbol */
    struct symbol *sl;  
    int fn; /* which function */
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token EOL
%token IF ELSE WHILE DO LET
%token COMMENT
%token LBRACE
%token RBRACE
%token ASSIGN
%token SEMICOLON

%nonassoc <fn> CMP
%nonassoc '|' UMINUS
%type <a> exp stmt list explist
%type <sl> symlist

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

%start calclist

%%

calclist: /* nothing */ 
    | calclist stmt EOL {
        printf("= %4.4g\n> ", eval($2));
        treefree($2);
    }
    | calclist LET NAME '(' symlist ')' '=' list EOL {
        dodef($3, $5, $8);
        printf("Define %s\n> ", $3->name);
    }
    | COMMENT
    | calclist error EOL
      {
        yyerrok;
        printf("> ");
      }
    ;

stmt:
    IF exp list {
        $$ = newflow('I', $2, $3, NULL);
    }
    | IF exp list ELSE list {
        $$ = newflow('I', $2, $3, $5);
    }
    | WHILE exp DO list {
        $$ = newflow('W', $2, $4, NULL);
    }
    | exp
    ;

exp
    : LBRACE exp RBRACE
      {
        $$ = $2;
      }
    | '-' exp %prec UMINUS {
        $$ = newast('M', $2, NULL);
    }
    | exp ADD exp
      {
        $$ = newast('+', $1, $3);
        if (  debug  )
          printf("reduce %lf + %lf => %lf\n", $1, $3, $$);
      }
    | exp SUB exp
      {
        $$ = newast('-', $1, $3);
        if (  debug  )
          printf("reduce %lf - %lf => %lf\n", $1, $3, $$);
      }
    | exp MULT exp
      {
        $$ = newast('*', $1, $3);
        if (  debug  )
          printf("reduce %lf * %lf => %lf\n", $1, $3, $$);
      }
    | exp DIV exp
      {
        $$ = newast('/', $1, $3);
        if (  debug  )
          printf("reduce %lf / %lf => %lf\n", $1, $3, $$);
      }
    | exp MOD exp
      {
        $$ = newast('%', $1, $3);
        if (  debug  )
          printf("reduce %lf % %lf => %lf\n", $1, $3, $$);
      }
    | NUMBER
      {
        $$ = newnum($1);
      }
    | NAME {
        $$ = newref($1);
    }
    | NAME '=' exp {
        $$ = newasgn($1, $3);
    }
    | FUNC '(' explist ')' {
        $$ = newfunc($1, $3);
    }
    | NAME '(' explist ')' {
        $$ = newcall($1, $3);
    }
    ;

list:   /* nothing */ 
    { $$ = NULL; }
    | stmt list {
        if ($2 == NULL)
            $$ = $1;
        else
            $$ = newast('L', $1, $2);
    }
    ;

explist: 
    exp 
    | exp ',' explist {
        $$ = newast('L', $1, $3);
    }
    ;

symlist:
    NAME {
        $$ = newsymlist($1, NULL);
    }
    | NAME ',' symlist {
        $$ = newsymlist($1, $3);
    }
    ;

%%

extern
void yyerror(char *s)
{
    print_error(s);
}
