%{
/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1

#include <stddef.h>

#include "latino.h"
#include "ast.h"
#include "node.h"
%}

%output "parse.c"
%defines "parse.h"

%locations
%define api.pure
%lex-param {void *scanner}
%parse-param {ast **root}
%parse-param {void *scanner}

/* declare tokens */
%token <node> TOKEN_INT
%token <node> TOKEN_CHAR
%token <node> TOKEN_NUMBER
%token <node> TOKEN_STRING
%token <node> TOKEN_IDENTIFIER
%token <token> TOKEN_FUNC
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
    KEYWORD_TRUE
    KEYWORD_FALSE

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

%nonassoc <node> OP_EQ OP_GE OP_GT OP_LE OP_LT OP_NEQ OP_NEG
%type <node> exp stmt list explist var value cases case default atom_value callfunc jump_stmt symList

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

program: list {
        *root = $1;
    }
    ;

list: stmt list {
        if ($2){
            $$ = newAst(NODE_BLOCK, $1, $2);
        }
    }
    | stmt {
        $$ = newAst(NODE_BLOCK, $1, NULL);
    }
    ;

stmt:
    KEYWORD_IF '(' exp ')' list KEYWORD_END {
        $$ = newIf(NODE_IF, $3, $5, NULL); }
    | KEYWORD_IF '(' exp ')' list KEYWORD_ELSE list KEYWORD_END {
        $$ = newIf(NODE_IF, $3, $5, $7); }
    | KEYWORD_DO list KEYWORD_WHEN '(' exp ')' {
        $$ = newDo(NODE_DO, $5, $2, NULL); }
    | KEYWORD_WHILE '(' exp ')' list KEYWORD_END {
        $$ = newWhile(NODE_WHILE, $3, $5, NULL); }
    | KEYWORD_SWITCH '(' value ')' cases KEYWORD_END {
        $$ = newSwitch(NODE_SWITCH, $3, $5, NULL); }
    | KEYWORD_SWITCH '(' value ')' cases default KEYWORD_END {
        $$ = newSwitch(NODE_SWITCH, $3, $5, $6); }
    | KEYWORD_FROM exp KEYWORD_TO exp list KEYWORD_END {
        $$ = newFor(NODE_FROM, $2, $4, $5, NULL); }
    | KEYWORD_FROM exp KEYWORD_TO exp KEYWORD_STEP '=' value list  KEYWORD_END {
        $$ = newFor(NODE_FROM, $2, $4, $8, $7); }
    | KEYWORD_FROM var KEYWORD_TO exp list KEYWORD_END {
        $$ = newFor(NODE_FROM, $2, $4, $5, NULL); }
    | KEYWORD_FROM var KEYWORD_TO exp KEYWORD_STEP '=' value list  KEYWORD_END {
        $$ = newFor(NODE_FROM, $2, $4, $8, $7); }
    | KEYWORD_FUNCTION TOKEN_IDENTIFIER '(' symList ')' list KEYWORD_END {
        $$ = doDef($2, $4, $6);
    }
    | var
    | callfunc
    | jump_stmt
    ;

jump_stmt : KEYWORD_RETURN exp { $$ = newAst(NODE_RETURN, $2, NULL);}
    ;

cases:
     cases case {
        $$ = newCase(NODE_CASES, NULL, $1, $2);
     }
     | case {
            $$ = $1;
        }
     ;

case:
    KEYWORD_CASE atom_value ':' list {
        $$ = newCase(NODE_CASE, NULL, $2, $4);
    }
    ;

default:
    KEYWORD_DEFAULT ':' list {
        $$ = newCase(NODE_DEFAULT, NULL, $3, NULL);
    }
    ;

exp: exp OP_GT  exp { $$ = newAst(NODE_GT, $1, $3); }
    | exp OP_LT exp { $$ = newAst(NODE_LT, $1, $3); }
    | exp OP_GE exp { $$ = newAst(NODE_GE, $1, $3); }
    | exp OP_LE exp { $$ = newAst(NODE_LE, $1, $3); }
    | exp OP_NEQ exp { $$ = newAst(NODE_NEQ, $1, $3); }
    | exp OP_EQ exp { $$ = newAst(NODE_EQ, $1, $3); }
    | exp OP_AND exp { $$ = newAst(NODE_AND, $1, $3); }
    | exp OP_OR exp { $$ = newAst(NODE_OR, $1, $3); }
    | OP_NEG exp %prec UNEG { $$ = newAst(NODE_NEG, $2, NULL); }
    | exp '+' exp { $$ = newOp(NODE_ADD, $1, $3); }
    | exp '-' exp { $$ = newOp(NODE_SUB, $1, $3); }
    | exp '*' exp { $$ = newOp(NODE_MULT, $1, $3); }
    | exp '/' exp { $$ = newOp(NODE_DIV, $1, $3); }
    | exp '%' exp { $$ = newAst(NODE_MOD, $1, $3); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newAst(NODE_UNARY_MINUS, $2, NULL); }
    | value
    | callfunc
    ;

var: TOKEN_IDENTIFIER '=' exp { $$ = newAsgn($3, $1); }
    ;

/*TOKEN_IDENTIFIER '(' explist ')' { $$ = newCall($1, $3); }*/

callfunc:
     TOKEN_IDENTIFIER '(' explist ')' { $$ = newAst(NODE_CALL_FUNCTION, $1, $3); }
    | TOKEN_FUNC '(' explist ')' { $$ = newFunc($1, $3); }
    ;

value:
      TOKEN_IDENTIFIER { $$ = $1; }
    | KEYWORD_TRUE { $$ = newBool(1); }
    | KEYWORD_FALSE { $$ = newBool(0); }
    | atom_value { $$ = $1; }
    ;

atom_value:
      TOKEN_INT { $$ = $1; }
    | TOKEN_NUMBER { $$ = $1; }
    | TOKEN_CHAR { $$ = $1; }
    | TOKEN_STRING { $$ = $1; }
    ;

explist: /* empty */ { $$ = NULL; }
    | exp { $$ = newAst(NODE_LIST_SYMBOLS, $1, NULL); }
    | exp ',' explist { $$ = newAst(NODE_LIST_SYMBOLS, $1, $3); }
    ;

symList: /* empty */ { $$ = NULL; }
    | TOKEN_IDENTIFIER { $$ = newSymList($1, NULL); }
    | TOKEN_IDENTIFIER ',' symList { $$ = newSymList($1, $3); }
    ;

%%

extern
void yyerror(char *s, ...)
{
    printError("%s", s);
}
