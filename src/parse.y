%{
#include "latino.h"
#define YYERROR_VERBOSE 1
%}

%defines
%union {
    struct ast *a;
    double d;
    struct symbol *s;   /* which symbol */
    struct symlist *sl;
    int fn; /* which function */
}

/* declare tokens */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token EOL
%token IF END ELSE WHILE DO LET FUNCTION

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
%right '='
%left '+' '-'
%left '*' '/' '%'

%start calclist

%%

calclist: /* nothing */
    | calclist stmt {
        //printf("= %4.4g\n> ", eval($2));
        eval($2);
        treefree($2);
    }
    | calclist FUNCTION NAME '(' symlist ')' list END {
        dodef($3, $5, $7);
        //printf("Define %s\n> ", $3->name);
    }
    | calclist error { yyerrok; printf("=> "); }
    ;

stmt:
    IF '(' exp ')' list END { $$ = newflow('I', $3, $5, NULL); }
    | IF '(' exp ')' list ELSE list END { $$ = newflow('I', $3, $5, $7); }
    | WHILE '(' exp ')' list END { $$ = newflow('W', $3, $5, NULL); }
    | exp
    ;

list:   /* nothing */ { $$ = NULL; }
    | stmt list {
        if ($2 == NULL)
            $$ = $1;
        else
            $$ = newast('L', $1, $2);
    }
    ;

exp: exp CMP exp { $$ = newcmp($2, $1, $3); }
    | exp '+' exp { $$ = newast('+', $1, $3); }
    | exp '-' exp { $$ = newast('-', $1, $3); }
    | exp '*' exp { $$ = newast('*', $1, $3); }
    | exp '/' exp { $$ = newast('/', $1, $3); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
    | NUMBER { $$ = newnum($1); }
    | NAME { $$ = newref($1); }
    | NAME '=' exp { $$ = newasgn($1, $3); }
    | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    | NAME '(' explist ')' { $$ = newcall($1, $3); }
    ;

explist: exp
    | exp ',' explist { $$ = newast('L', $1, $3); }
    ;

symlist: NAME { $$ = newsymlist($1, NULL); }
    | NAME ',' symlist { $$ = newsymlist($1, $3); }
    ;

%%

extern
void yyerror(char *s, ...)
{
    print_error(s);
}
