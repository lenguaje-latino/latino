%{
#include "latino.h"
#define YYERROR_VERBOSE 1
%}

%defines
%union {
    int fn; /* which function */
    char *b; /* boolean type*/
    char *c; /* char type */
    long i;  /* int type */
    double d; /* double type */
    struct lat_string *str; /* string type */
    struct ast *a; /* astract syntax tree */
    struct symbol *s;   /* which symbol */
    struct symlist *sl; /* symbol list */
}

/* declare tokens */
%token <b> KEYWORD_TRUE KEYWORD_FALSE
%token <i> TOKEN_INT
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
    KEYWORD_SWITCH
    KEYWORD_CASE
    KEYWORD_BREAK
    KEYWORD_DEFAULT
    KEYWORD_WHEN
    KEYWORD_FUNCTION
    KEYWORD_FROM
    KEYWORD_TO
    KEYWORD_STEP
    KEYWORD_BOOL
    KEYWORD_RETURN

%token
    OP_GT
    OP_LT
    OP_GE
    OP_LE
    OP_EQ
    OP_NEQ
    OP_AND
    OP_OR
    OP_NEG


%nonassoc <fn> OP_EQ OP_GE OP_GT OP_LE OP_LT OP_NEQ OP_NEG
%type <a> exp stmt list explist var value cases case default atom_value callfunc jump_stmt
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
%left UMINUS UNEG

%start program

%%

program: /* empty */
    | program list {
        if($2) {
            eval($2);
            treefree($2);
        }
    }
    ;

list:   /* empty */ { $$ = NULL; }
    | stmt list {
        if ($2){
            $$ = newast(NODE_BLOCK, $1, $2);
        } else {
            $$ = newast(NODE_BLOCK, $1, NULL);
        }
    }
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
    | KEYWORD_SWITCH '(' value ')' cases KEYWORD_END {
        $$ = newflow(NODE_SWITCH, $3, $5, NULL); }
    | KEYWORD_SWITCH '(' value ')' cases default KEYWORD_END {
        $$ = newflow(NODE_SWITCH, $3, $5, $6); }
    | KEYWORD_FROM exp KEYWORD_TO exp list KEYWORD_END {
        $$ = newfor(NODE_FROM, $2, $4, $5, NULL); }
    | KEYWORD_FROM exp KEYWORD_TO exp KEYWORD_STEP '=' value list  KEYWORD_END {
        $$ = newfor(NODE_FROM, $2, $4, $8, $7); }
    | KEYWORD_FROM var KEYWORD_TO exp list KEYWORD_END {
        $$ = newfor(NODE_FROM, $2, $4, $5, NULL); }
    | KEYWORD_FROM var KEYWORD_TO exp KEYWORD_STEP '=' value list  KEYWORD_END {
        $$ = newfor(NODE_FROM, $2, $4, $8, $7); }
    | KEYWORD_FUNCTION TOKEN_IDENTIFIER '(' symlist ')' list KEYWORD_END {
        dodef($2, $4, $6);
        $$ = NULL;
    }
    | var
    | callfunc
    | jump_stmt
    ;

jump_stmt : KEYWORD_RETURN exp { $$ = newast(NODE_RETURN, $2, NULL);}
    ;

cases:
     cases case {
        $$ = newflow(NODE_CASES, NULL, $1, $2);
     }
     | case {
            $$ = $1;
        }
     ;

case:
    KEYWORD_CASE atom_value ':' list {
        $$ = newflow(NODE_CASE, NULL, $2, $4);
    }
    ;

default:
    KEYWORD_DEFAULT ':' list {
        $$ = newflow(NODE_DEFAULT, NULL, $3, NULL);
    }
    ;

exp: exp OP_GT  exp { $$ = newast(NODE_GT, $1, $3); }
    | exp OP_LT exp { $$ = newast(NODE_LT, $1, $3); }
    | exp OP_GE exp { $$ = newast(NODE_GE, $1, $3); }
    | exp OP_LE exp { $$ = newast(NODE_LE, $1, $3); }
    | exp OP_NEQ exp { $$ = newast(NODE_NEQ, $1, $3); }
    | exp OP_EQ exp { $$ = newast(NODE_EQ, $1, $3); }
    | exp OP_AND exp { $$ = newast(NODE_AND, $1, $3); }
    | exp OP_OR exp { $$ = newast(NODE_OR, $1, $3); }
    | OP_NEG exp %prec UNEG { $$ = newast(NODE_NEG, $2, NULL); }
    | exp '+' exp { $$ = newast(NODE_ADD, $1, $3); }
    | exp '-' exp { $$ = newast(NODE_SUB, $1, $3); }
    | exp '*' exp { $$ = newast(NODE_MULT, $1, $3); }
    | exp '/' exp { $$ = newast(NODE_DIV, $1, $3); }
    | exp '%' exp { $$ = newast(NODE_MOD, $1, $3); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast(NODE_UNARY_MINUS, $2, NULL); }
    | value
    | callfunc
    ;

var: TOKEN_IDENTIFIER '=' exp { $$ = newasgn($1, $3); }
    ;

callfunc:
     TOKEN_IDENTIFIER '(' explist ')' { $$ = newcall($1, $3); }
    | TOKEN_FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    ;

value:
      TOKEN_IDENTIFIER { $$ = newref($<s>1); }
    | KEYWORD_TRUE { $$ = newbool($1); }
    | KEYWORD_FALSE { $$ = newbool($1); }
    | atom_value { $$ = $1; }
    ;

atom_value:
      TOKEN_INT { $$ = newint($1); }
    | TOKEN_NUMBER { $$ = newnum($1); }
    | TOKEN_CHAR { $$ = $<c>1; }
    | TOKEN_STRING { $$ = $<str>1; }
    ;

explist: /* empty */ { $$ = NULL; }
    | exp { $$ = newast(NODE_LIST_SYMBOLS, $1, NULL); }
    | exp ',' explist { $$ = newast(NODE_LIST_SYMBOLS, $1, $3); }
    ;

symlist: /* empty */ { $$ = NULL; }
    | TOKEN_IDENTIFIER { $$ = newsymlist($1, NULL); }
    | TOKEN_IDENTIFIER ',' symlist { $$ = newsymlist($1, $3); }
    ;

%%

extern
void yyerror(char *s, ...)
{
    print_error("linea %i, %s", yylineno, s);
}
