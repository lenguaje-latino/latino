%{
#include "latino.h"
#include "structs.h"
#define YYERROR_VERBOSE 1
%}

%defines
%union {
    char *b;
    struct ast *a;
    double d;
    char *c;
    struct symbol *s;   /* which symbol */
    struct symlist *sl;
    int fn; /* which function */
    struct lat_string *str;
}

/* declare tokens */
%token <b> KEYWORD_TRUE KEYWORD_FALSE
%token <c> TOKEN_CHAR
%token <d> TOKEN_NUMBER
%token <str> TOKEN_STRING
%token <s> TOKEN_IDENTIFIER
%token <fn> TOKEN_FUNC
%token
    KEYWORD_IF
    KEYWORD_END
    KEYWORD_ELSE
    KEYWORD_WHILE
    KEYWORD_DO
    KEYWORD_WHEN
    KEYWORD_FUNCTION
    KEYWORD_TRUE
    KEYWORD_FALSE
    KEYWORD_FROM
    KEYWORD_TO
    KEYWORD_STEP
    KEYWORD_BOOL
    KEYWORD_INT
    KEYWORD_DECIMAL
    KEYWORD_CHAR
    KEYWORD_STRING

%token
    LIT_STRING

%nonassoc <fn> CMP
%type <a> exp stmt list explist var
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

%start program

%%

program: /* empty */
    | program stmt {
        //printf("= %4.4g\n> ", eval($2));
        eval($2);
        treefree($2);
    }
    | program KEYWORD_FUNCTION TOKEN_IDENTIFIER '(' symlist ')' list KEYWORD_END {
        dodef($3, $5, $7);
        //printf("Define %s\n> ", $3->name);
    }
    | program error { yyerrok; printf("=> "); }
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
    | var
    ;

var: TOKEN_NUMBER { $$ = newnum($1); }
    | TOKEN_STRING { $$ = $<str>1; }
    | TOKEN_IDENTIFIER { $$ = newref($1); }
    | KEYWORD_BOOL TOKEN_IDENTIFIER { $$ = newref($2); }
    | KEYWORD_INT TOKEN_IDENTIFIER { $$ = newref($2); }
    | KEYWORD_DECIMAL TOKEN_IDENTIFIER { $$ = newref($2); }
    | KEYWORD_CHAR TOKEN_IDENTIFIER { $$ = newref($2); }
    | KEYWORD_STRING TOKEN_IDENTIFIER { $$ = newref($2); }
    | KEYWORD_BOOL TOKEN_IDENTIFIER '=' exp { $$ = newasgn($2, $4); }
    | KEYWORD_INT TOKEN_IDENTIFIER '=' exp { $$ = newasgn($2, $4); }
    | KEYWORD_DECIMAL TOKEN_IDENTIFIER '=' exp { $$ = newasgn($2, $4); }
    | KEYWORD_CHAR TOKEN_IDENTIFIER '=' exp { $$ = newasgn($2, $4); }
    | KEYWORD_STRING TOKEN_IDENTIFIER '=' exp { $$ = newasgn($2, $4); }
    | TOKEN_IDENTIFIER '=' exp { $$ = newasgn($1, $3); }
    | TOKEN_FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    | TOKEN_IDENTIFIER '(' explist ')' { $$ = newcall($1, $3); }
    | KEYWORD_TRUE { $$ = newbool($1); }
    | KEYWORD_FALSE { $$ = newbool($1); }
    | TOKEN_CHAR { $$ = $<c>1; }
    ;

explist: /* empty */ { $$ = NULL; }
    | exp
    | exp ',' explist { $$ = newast(NODE_EXPRESION, $1, $3); }
    ;

symlist: /* empty */ { $$ = NULL; }
    | TOKEN_IDENTIFIER { $$ = newsymlist($1, NULL); }
    | TOKEN_IDENTIFIER ',' symlist { $$ = newsymlist($1, $3); }
    ;

%%

extern
void yyerror(char *s, ...)
{
    print_error(s);
}
