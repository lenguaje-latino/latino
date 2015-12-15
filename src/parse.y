%{
/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define YYLEX_PARAM &yylval, &yylloc

#include <stddef.h>

#include "latino.h"
#include "ast.h"

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root, const char *s);

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
%token <node> TCONSTANT
%token <token> TFUNC
%token
    KIF
    KEND
    KELSE
    KWHILE
    KDO
    KBREAK
    KCONTINUE
    KWHEN
    KFUNCTION
    KFROM
    KBOOL
    KRETURN
    KTRUE
    KFALSE
    /*
    KSWITCH
    KCASE
    KDEFAULT
    */

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
    OP_INCR
    OP_DECR

%nonassoc <node> OP_EQ OP_GE OP_GT OP_LE OP_LT OP_NEQ OP_NEG
%type <node> expression statement statement_list unary_expression
%type <node> iteration_statement jump_statement function_definition
%type <node> argument_expression_list declaration primary_expression
%type <node> constant_expression function_call selection_statement identifier_list
%type <node> list_items get_list_item
%type <node> dict_items get_dict_item dict_item dict_key

 /*labeled_statement*/

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
        *root = $1;
    }
    ;

statement_list:
    statement_list statement {
        if($2){
            $$ = ast_new_node(NODE_BLOCK, $2, $1);
        }
    }
    | statement {
        $$ = ast_new_node(NODE_BLOCK, $1, NULL);
    }
    ;

    /*| labeled_statement { $$ = $1; }*/
statement: /* empty */ { $$ = NULL; }
    | declaration  { $$ = $1; }
    | selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; }
    | jump_statement { $$ = $1; }
    | function_definition { $$ = $1; }
    | function_call { $$ = $1; }
    ;

declaration:
      TIDENTIFIER '=' expression { $$ = ast_new_assignment($3, $1); }
    | TCONSTANT '=' constant_expression { $$ = ast_new_assignment($3, $1); }
    | unary_expression { $$ = $1; }
    ;

/*labeled_statement:
    KCASE constant_expression ':' statement_list {
        $$ = ast_new_node(NODE_CASE, $2, $4);
    }
    | KDEFAULT ':' statement_list {
        $$ = ast_new_node(NODE_DEFAULT, NULL, $3);
    }
    ;
*/

selection_statement:
    KIF '(' expression ')' statement_list KEND {
        $$ = ast_new_node_if($3, $5, NULL); }
    | KIF '(' expression ')' statement_list KELSE statement_list KEND {
        $$ = ast_new_node_if($3, $5, $7); }
    /*| KSWITCH '(' TIDENTIFIER ')' labeled_statement KEND {
        $$ = ast_new_node(NODE_SWITCH, $3, $5); }*/
    ;


iteration_statement:
    KDO statement_list KWHEN '(' expression ')' {
        $$ = ast_new_node_do($5, $2); }
    | KWHILE '(' expression ')' statement_list KEND {
        $$ = ast_new_node_while($3, $5); }
    | KFROM '(' declaration ';' expression ';' declaration ')'
        statement_list  KEND {
        $$ = ast_new_node_for($3, $5, $7, $9); }
    ;

jump_statement :
    KRETURN expression { $$ = ast_new_node(NODE_RETURN, $2, NULL); }
    ;

function_definition:
    KFUNCTION TIDENTIFIER '(' identifier_list ')' statement_list KEND {
        $$ = ast_new_node_function($2, $4, $6);
    }
    ;

expression:
      expression OP_GT  expression { $$ = ast_new_op(NODE_GT, $1, $3); }
    | expression OP_LT expression { $$ = ast_new_op(NODE_LT, $1, $3); }
    | expression OP_GE expression { $$ = ast_new_op(NODE_GE, $1, $3); }
    | expression OP_LE expression { $$ = ast_new_op(NODE_LE, $1, $3); }
    | expression OP_NEQ expression { $$ = ast_new_op(NODE_NEQ, $1, $3); }
    | expression OP_EQ expression { $$ = ast_new_op(NODE_EQ, $1, $3); }
    | expression OP_AND expression { $$ = ast_new_op(NODE_AND, $1, $3); }
    | expression OP_OR expression { $$ = ast_new_op(NODE_OR, $1, $3); }
    | OP_NEG expression %prec UNEG { $$ = ast_new_op(NODE_NEG, $2, NULL); }
    | expression '+' expression { $$ = ast_new_op(NODE_ADD, $1, $3); }
    | expression '-' expression { $$ = ast_new_op(NODE_SUB, $1, $3); }
    | expression '*' expression { $$ = ast_new_op(NODE_MULT, $1, $3); }
    | expression '/' expression { $$ = ast_new_op(NODE_DIV, $1, $3); }
    | expression '%' expression { $$ = ast_new_op(NODE_MOD, $1, $3); }
    | '(' expression ')' { $$ = $2; }
    | '-' expression %prec UMINUS { $$ = ast_new_op(NODE_UNARY_MINUS, $2, NULL); }
    | primary_expression
    | function_call
    ;

function_call:
     TIDENTIFIER '(' argument_expression_list ')' { $$ = ast_new_node(NODE_CALL_FUNCTION, $1, $3); }
    ;

primary_expression:
      TIDENTIFIER { $$ = $1; }
    | TCONSTANT { $$ = $1; }
    | KTRUE { $$ = ast_new_bool(1); }
    | KFALSE { $$ = ast_new_bool(0); }
    | constant_expression  { $$ = $1; }
    ;

constant_expression:
      TINT { $$ = $1; }
    | TNUMBER { $$ = $1; }
    | TCHAR { $$ = $1; }
    | TSTRING { $$ = $1; }
    | '[' list_items ']' { $$ = ast_new_node(NODE_LIST, $2, NULL); }
    | '{' dict_items '}' { $$ = ast_new_node(NODE_DICT, $2, NULL); }
    | get_list_item { $$ = $1; }
    | get_dict_item { $$ = $1; }
    ;

unary_expression:
	  TIDENTIFIER OP_INCR { $$ = ast_new_node(NODE_INC, $1, NULL); }
	| TIDENTIFIER OP_DECR { $$ = ast_new_node(NODE_DEC, $1, NULL); }
    ;

argument_expression_list: /* empty */ { $$ = NULL; }
    | expression { $$ = ast_new_node(NODE_FUNC_ARGS, $1, NULL); }
    | expression ',' argument_expression_list { $$ = ast_new_node(NODE_FUNC_ARGS, $1, $3); }
    ;

identifier_list: /* empty */ { $$ = NULL; }
    | TIDENTIFIER { $$ = ast_new_node(NODE_PARAM_LIST, $1, NULL); }
    | identifier_list ',' TIDENTIFIER { $$ = ast_new_node(NODE_PARAM_LIST, $3, $1); }
    ;

list_items: /* empty */ { $$ = ast_new_node(NODE_LIST_SET_ITEM, NULL, NULL); }
    | list_items ',' expression { $$ = ast_new_node(NODE_LIST_SET_ITEM, $3, $1); }
    | expression { $$ = ast_new_node(NODE_LIST_SET_ITEM, $1, NULL); }
    ;

get_list_item:
     TIDENTIFIER '[' TINT ']' { $$ = ast_new_node(NODE_LIST_GET_ITEM, $1, $3); }
    ;

dict_items: /* empty */ { $$ = ast_new_node(NODE_DICT_ITEMS, NULL, NULL); }
    | dict_items ',' dict_item { $$ = ast_new_node(NODE_DICT_ITEMS, $3, $1); }
    | dict_item { $$ = ast_new_node(NODE_DICT_ITEMS, $1, NULL); }
    ;

dict_item: /* empty */ { $$ = NULL; }
    | dict_key ':' primary_expression { $$ = ast_new_node(NODE_DICT_ITEM, $1, $3); }
    ;

dict_key:
    TINT { $$ = $1; }
    | TSTRING { $$ = $1; }
    ;

get_dict_item:
     TIDENTIFIER '[' TSTRING ']' { $$ = ast_new_node(NODE_GET_DICT_ITEM, $1, $3); }
    ;
%%
