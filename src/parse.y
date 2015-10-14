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
%type <node> expression statement statement_list labeled_statement selection_statement
%type <node> iteration_statement jump_statement function_definition
%type <node> argument_expression_list declaration primary_expression
%type <node> constant_expression direct_declarator identifier_list

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

program: statement_list {
        *root = $1;
    }
    ;

statement_list: statement statement_list {
        $$ = newAst(NODE_BLOCK, $1, $2);
    }
    | statement {
        $$ = newAst(NODE_BLOCK, $1, NULL);
    }
    ;

statement:
    labeled_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | function_definition
    | declaration
    | direct_declarator
    ;

labeled_statement:
    KEYWORD_CASE constant_expression ':' statement_list {
        $$ = newAst(NODE_CASE, $2, $4);
    }
    | KEYWORD_DEFAULT ':' statement_list {
        $$ = newAst(NODE_DEFAULT, NULL, $3);
    }
    ;

selection_statement:
    KEYWORD_IF '(' expression ')' statement_list KEYWORD_END {
        $$ = newIf($3, $5, NULL); }
    | KEYWORD_IF '(' expression ')' statement_list KEYWORD_ELSE statement_list KEYWORD_END {
        $$ = newIf($3, $5, $7); }
    | KEYWORD_SWITCH '(' TOKEN_IDENTIFIER ')' labeled_statement KEYWORD_END {
        $$ = newAst(NODE_SWITCH, $3, $5); }
    ;

iteration_statement:
    KEYWORD_DO statement_list KEYWORD_WHEN '(' expression ')' {
        $$ = newDo($5, $2); }
    | KEYWORD_WHILE '(' expression ')' statement_list KEYWORD_END {
        $$ = newWhile($3, $5); }
    | KEYWORD_FROM '(' declaration ';' expression ';' declaration ')' statement_list  KEYWORD_END {
        $$ = newFor($3, $5, $7, $9); }
    ;

jump_statement :
    KEYWORD_RETURN expression { $$ = newAst(NODE_RETURN, $2, NULL); }
    ;

function_definition:
    KEYWORD_FUNCTION TOKEN_IDENTIFIER '(' identifier_list ')' statement_list KEYWORD_END {
        $$ = doDef($2, $4, $6);
    }
    ;

expression: expression OP_GT  expression { $$ = newOp(NODE_GT, $1, $3); }
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
    | direct_declarator { $$ = $1; }
    ;

declaration: TOKEN_IDENTIFIER '=' expression { $$ = newAsgn($3, $1); }
    ;

direct_declarator:
     TOKEN_IDENTIFIER '(' argument_expression_list ')' { $$ = newAst(NODE_CALL_FUNCTION, $1, $3); }
    ;

primary_expression:
      TOKEN_IDENTIFIER { $$ = $1; }
    | KEYWORD_TRUE { $$ = newBool(1); }
    | KEYWORD_FALSE { $$ = newBool(0); }
    | constant_expression { $$ = $1; }
    ;

constant_expression:
    TOKEN_INT { $$ = $1; }
    | TOKEN_NUMBER { $$ = $1; }
    | TOKEN_CHAR { $$ = $1; }
    | TOKEN_STRING { $$ = $1; }
    ;

argument_expression_list: /* empty */ { $$ = NULL; }
    | expression { $$ = newAst(NODE_FUNC_ARGS, $1, NULL); }
    | argument_expression_list ',' expression { $$ = newAst(NODE_FUNC_ARGS, $3, $1); }
    ;

identifier_list: /* empty */ { $$ = NULL; }
    | TOKEN_IDENTIFIER { $$ = newAst(NODE_PARAM_LIST, $1, NULL); }
    | identifier_list ',' TOKEN_IDENTIFIER { $$ = newAst(NODE_PARAM_LIST, $3, $1); }
    ;

%%
/*
extern
void yyerror(char *s, ...)
{
    fflush(stdout);
    printError(s);
}
*/
