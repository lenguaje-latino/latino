%{
#include "latino.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
%}

%defines
%union {
    struct ast *a;
    double d;
    struct symbol *s;   /* which symbol */
    struct symlist *sl;
    int fn; /* which function */
    struct lat_string *str;
}

/* declare tokens */
%token <d> TOKEN_NUMBER
%token <s> TOKEN_STRING
%token <s> TOKEN_NAME
%token <fn> TOKEN_FUNC
%token
    KEYWORD_IF
    KEYWORD_END
    KEYWORD_ELSE
    KEYWORD_WHILE
    KEYWORD_DO
    KEYWORD_WHEN
    KEYWORD_FUNCTION
    KEYWORD_V
    KEYWORD_F
    KEYWORD_FROM
    KEYWORD_TO
    KEYWORD_STEP

%token
    LIT_STRING

%nonassoc <fn> CMP
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
%left UMINUS

%start calclist

%%

calclist: /* empty */
    | calclist stmt {
        //printf("= %4.4g\n> ", eval($2));
        eval($2);
        treefree($2);
    }
    | calclist KEYWORD_FUNCTION TOKEN_NAME '(' symlist ')' list KEYWORD_END {
        dodef($3, $5, $7);
        //printf("Define %s\n> ", $3->name);
    }
    | calclist error { yyerrok; printf("=> "); }
    ;

stmt:
    KEYWORD_IF '(' exp ')' list KEYWORD_END {
        $$ = newflow(NODE_IF, $3, $5, NULL); }
    | KEYWORD_IF '(' exp ')' list KEYWORD_ELSE list KEYWORD_END {
        $$ = newflow(NODE_IF, $3, $5, $7); }
    | KEYWORD_WHILE '(' exp ')' list KEYWORD_END {
        $$ = newflow(NODE_WHILE, $3, $5, NULL); }
    | KEYWORD_DO list KEYWORD_WHEN '(' exp ')' {
        $$ = newflow(NODE_DO, $5, $2, NULL); }
    | exp
    ;

list:   /* empty */ { $$ = NULL; }
    | stmt list {
        if ($2 == NULL)
            $$ = $1;
        else
            $$ = newast(NODE_EXPRESION, $1, $2);
    }
    ;

exp: exp CMP exp { $$ = newcmp($2, $1, $3); }
    | CMP        { $$ = newcmp($1, NULL, NULL); }
    | exp '+' exp { $$ = newast(NODE_ADD, $1, $3); }
    | exp '-' exp { $$ = newast(NODE_SUB, $1, $3); }
    | exp '*' exp { $$ = newast(NODE_MULT, $1, $3); }
    | exp '/' exp { $$ = newast(NODE_DIV, $1, $3); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast(NODE_UNARY_MINUS, $2, NULL); }
    | TOKEN_NUMBER { $$ = newnum($1); }
    | TOKEN_NAME { $$ = newref($1); }
    | TOKEN_NAME '=' exp { $$ = newasgn($1, $3); }
    | TOKEN_FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    | TOKEN_NAME '(' explist ')' { $$ = newcall($1, $3); }
    | TOKEN_STRING { $$ = $<str>1; }
    ;

explist: /* empty */ { $$ = NULL; }
    | exp
    | exp ',' explist { $$ = newast(NODE_EXPRESION, $1, $3); }
    ;

symlist: /* empty */ { $$ = NULL; }
    | TOKEN_NAME { $$ = newsymlist($1, NULL); }
    | TOKEN_NAME ',' symlist { $$ = newsymlist($1, $3); }
    ;

%%

extern
void yyerror(char *s, ...)
{
    print_error(s);
}
