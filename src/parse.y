%{
/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1

#include <stddef.h>

#include "latino.h"
#include "ast.h"

%}

%output "parse.c"
%defines "parse.h"

%locations
%define api.pure
%lex-param {void *scanner}
%parse-param {ast **root}
%parse-param {void *scanner}

/* declare tokens */
%token <node> TINT
%token <node> TCHAR
%token <node> TNUMBER
%token <node> TSTRING
%token <node> TIDENTIFIER
%token <token> TFUNC
%token
    KIF
    KEND
    KELSE
    KWHILE
    KDO
    KSWITCH
    KCASE
    KBREAK
    KDEFAULT
    KWHEN
    KFUNCTION
    KFROM
    KBOOL
    KRETURN
    KTRUE
    KFALSE

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
%type <node> expression statement statement_list labeled_statement
%type <node> iteration_statement jump_statement function_definition
%type <node> argument_expression_list declaration primary_expression
%type <node> constant_expression function_call selection_statement
%type <node> list_expression_items identifier_list

/*
 * precedencia de operadores
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

program: statement_list {
        if($1){
            *root = $1;
        }
    }
    ;

statement_list:
    statement statement_list {
        if($2){
            $$ = newAst(NODE_BLOCK, $1, $2);
        }
    }
    | statement {
        $$ = newAst(NODE_BLOCK, $1, NULL);
    }
    ;

statement:
      declaration  { $$ = $1; }
    | labeled_statement { $$ = $1; }
    | selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; }
    | jump_statement { $$ = $1; }
    | function_definition { $$ = $1; }
    | function_call { $$ = $1; }
    ;

declaration:
      TIDENTIFIER '=' expression { $$ = newAsgn($3, $1); }
    ;

labeled_statement:
    KCASE constant_expression ':' statement_list {
        $$ = newAst(NODE_CASE, $2, $4);
    }
    | KDEFAULT ':' statement_list {
        $$ = newAst(NODE_DEFAULT, NULL, $3);
    }
    ;

selection_statement:
    KIF '(' expression ')' statement_list KEND {
        $$ = newIf($3, $5, NULL); }
    | KIF '(' expression ')' statement_list KELSE statement_list KEND {
        $$ = newIf($3, $5, $7); }
    | KSWITCH '(' TIDENTIFIER ')' labeled_statement KEND {
        $$ = newAst(NODE_SWITCH, $3, $5); }
    ;

iteration_statement:
    KDO statement_list KWHEN '(' expression ')' {
        $$ = newDo($5, $2); }
    | KWHILE '(' expression ')' statement_list KEND {
        $$ = newWhile($3, $5); }
    | KFROM '(' declaration ';' expression ';' declaration ')' statement_list  KEND {
        $$ = newFor($3, $5, $7, $9); }
    ;

jump_statement :
    KRETURN expression { $$ = newAst(NODE_RETURN, $2, NULL); }
    ;

function_definition:
    KFUNCTION TIDENTIFIER '(' identifier_list ')' statement_list KEND {
        $$ = doDef($2, $4, $6);
    }
    ;

expression:
      expression OP_GT  expression { $$ = newOp(NODE_GT, $1, $3); }
    | expression OP_LT expression { $$ = newOp(NODE_LT, $1, $3); }
    | expression OP_GE expression { $$ = newOp(NODE_GE, $1, $3); }
    | expression OP_LE expression { $$ = newOp(NODE_LE, $1, $3); }
    | expression OP_NEQ expression { $$ = newOp(NODE_NEQ, $1, $3); }
    | expression OP_EQ expression { $$ = newOp(NODE_EQ, $1, $3); }
    | expression OP_AND expression { $$ = newOp(NODE_AND, $1, $3); }
    | expression OP_OR expression { $$ = newOp(NODE_OR, $1, $3); }
    | OP_NEG expression %prec UNEG { $$ = newOp(NODE_NEG, $2, NULL); }
    | expression '+' expression { $$ = newOp(NODE_ADD, $1, $3); }
    | expression '-' expression { $$ = newOp(NODE_SUB, $1, $3); }
    | expression '*' expression { $$ = newOp(NODE_MULT, $1, $3); }
    | expression '/' expression { $$ = newOp(NODE_DIV, $1, $3); }
    | expression '%' expression { $$ = newOp(NODE_MOD, $1, $3); }
    | '(' expression ')' { $$ = $2; }
    | '-' expression %prec UMINUS { $$ = newOp(NODE_UNARY_MINUS, $2, NULL); }
    | primary_expression { $$ = $1; }
    | function_call { $$ = $1; }
    ;

function_call:
     TIDENTIFIER '(' argument_expression_list ')' { $$ = newAst(NODE_CALL_FUNCTION, $1, $3); }
    ;

primary_expression:
      TIDENTIFIER { $$ = $1; }
    | KTRUE { $$ = newBool(1); }
    | KFALSE { $$ = newBool(0); }
    | constant_expression  { $$ = $1; }
    ;

constant_expression:
      TINT { $$ = $1; }
    | TNUMBER { $$ = $1; }
    | TCHAR { $$ = $1; }
    | TSTRING { $$ = $1; }
    | '[' list_expression_items ']' { $$ = newAst(NODE_LIST, $2, NULL); }
    ;

argument_expression_list: /* empty */ { $$ = NULL; }
    | expression { $$ = newAst(NODE_FUNC_ARGS, $1, NULL); }
    | argument_expression_list ',' expression { $$ = newAst(NODE_FUNC_ARGS, $3, $1); }
    ;

identifier_list: /* empty */ { $$ = NULL; }
    | TIDENTIFIER { $$ = newAst(NODE_PARAM_LIST, $1, NULL); }
    | identifier_list ',' TIDENTIFIER { $$ = newAst(NODE_PARAM_LIST, $3, $1); }
    ;

list_expression_items: /* empty */ { $$ = newAst(NODE_LIST_BODY, NULL, NULL); }
    | list_expression_items ',' expression { $$ = newAst(NODE_LIST_BODY, $3, $1); }
    | expression { $$ = newAst(NODE_LIST_BODY, $1, NULL); }
    ;

%%
