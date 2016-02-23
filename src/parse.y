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
%token <node> TLIT
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
    OP_CONCAT
    OP_CONCAT_IGUAL

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
%left '+' '-' OP_CONCAT OP_CONCAT_IGUAL
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
            $$ = nodo_nuevo(NODO_BLOQUE, $2, $1);
        }
    }
    | statement {
        $$ = nodo_nuevo(NODO_BLOQUE, $1, NULL);
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
      TIDENTIFIER '=' expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | TIDENTIFIER OP_CONCAT_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo_operador(NODO_CONCATENAR, $1, $3)), $1); }
    | TCONSTANT '=' constant_expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | get_list_item '=' expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | unary_expression { $$ = $1; }
    ;

/*labeled_statement:
    KCASE constant_expression ':' statement_list {
        $$ = nodo_nuevo(NODO_CASO, $2, $4);
    }
    | KDEFAULT ':' statement_list {
        $$ = nodo_nuevo(NODO_DEFECTO, NULL, $3);
    }
    ;
*/

selection_statement:
    KIF '(' expression ')' statement_list KEND {
        $$ = nodo_nuevo_si($3, $5, NULL); }
    | KIF '(' expression ')' statement_list KELSE statement_list KEND {
        $$ = nodo_nuevo_si($3, $5, $7); }
    /*| KSWITCH '(' TIDENTIFIER ')' labeled_statement KEND {
        $$ = nodo_nuevo(NODO_SELECCION, $3, $5); }*/
    ;


iteration_statement:
    KDO statement_list KWHEN '(' expression ')' {
        $$ = nodo_nuevo_hacer($5, $2); }
    | KWHILE '(' expression ')' statement_list KEND {
        $$ = nodo_nuevo_mientras($3, $5); }
    | KFROM '(' declaration ';' expression ';' declaration ')'
        statement_list  KEND {
        $$ = nodo_nuevo_desde($3, $5, $7, $9); }
    ;

jump_statement :
    KRETURN expression { $$ = nodo_nuevo(NODO_RETORNO, $2, NULL); }
    ;

function_definition:
    KFUNCTION TIDENTIFIER '(' identifier_list ')' statement_list KEND {
        $$ = nodo_nuevo_funcion($2, $4, $6);
    }
    ;

expression:
      expression OP_GT  expression { $$ = nodo_nuevo_operador(NODO_MAYOR_QUE, $1, $3); }
    | expression OP_LT expression { $$ = nodo_nuevo_operador(NODO_MENOR_QUE, $1, $3); }
    | expression OP_GE expression { $$ = nodo_nuevo_operador(NODO_MAYOR_IGUAL, $1, $3); }
    | expression OP_LE expression { $$ = nodo_nuevo_operador(NODO_MENOR_IGUAL, $1, $3); }
    | expression OP_NEQ expression { $$ = nodo_nuevo_operador(NODO_DESIGUALDAD, $1, $3); }
    | expression OP_EQ expression { $$ = nodo_nuevo_operador(NODO_IGUALDAD, $1, $3); }
    | expression OP_AND expression { $$ = nodo_nuevo_operador(NODO_Y, $1, $3); }
    | expression OP_OR expression { $$ = nodo_nuevo_operador(NODO_O, $1, $3); }
    | expression OP_CONCAT expression { $$ = nodo_nuevo_operador(NODO_CONCATENAR, $1, $3); }
    | OP_NEG expression %prec UNEG { $$ = nodo_nuevo_operador(NODO_NEGACION, $2, NULL); }
    | expression '+' expression { $$ = nodo_nuevo_operador(NODO_SUMA, $1, $3); }
    | expression '-' expression { $$ = nodo_nuevo_operador(NODO_RESTA, $1, $3); }
    | expression '*' expression { $$ = nodo_nuevo_operador(NODO_MULTIPLICACION, $1, $3); }
    | expression '/' expression { $$ = nodo_nuevo_operador(NODO_DIVISION, $1, $3); }
    | expression '%' expression { $$ = nodo_nuevo_operador(NODO_MODULO, $1, $3); }
    | '(' expression ')' { $$ = $2; }
    | '-' expression %prec UMINUS { $$ = nodo_nuevo_operador(NODO_MENOS_UNARIO, $2, NULL); }
    | primary_expression
    | function_call
    ;

function_call:
     TIDENTIFIER '(' argument_expression_list ')' { $$ = nodo_nuevo(NODO_FUNCION_LLAMADA, $1, $3); }
    ;

primary_expression:
      TIDENTIFIER { $$ = $1; }
    | TCONSTANT { $$ = $1; }
    | KTRUE { $$ = nodo_nuevo_logico(1); }
    | KFALSE { $$ = nodo_nuevo_logico(0); }
    | constant_expression  { $$ = $1; }
    ;

constant_expression:
      TINT { $$ = $1; }
    | TNUMBER { $$ = $1; }
    | TLIT { $$ = $1; }
    | TSTRING { $$ = $1; }
    | '[' list_items ']' { $$ = nodo_nuevo(NODO_LISTA, $2, NULL); }
    | '{' dict_items '}' { $$ = nodo_nuevo(NODO_DICCIONARIO, $2, NULL); }
    | get_list_item { $$ = $1; }
    | get_dict_item { $$ = $1; }
    ;

unary_expression:
	  TIDENTIFIER OP_INCR { $$ = nodo_nuevo(NODO_INCREMENTO, $1, NULL); }
	| TIDENTIFIER OP_DECR { $$ = nodo_nuevo(NODO_DECREMENTO, $1, NULL); }
    ;

argument_expression_list: /* empty */ { $$ = NULL; }
    | expression { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, NULL); }
    | expression ',' argument_expression_list { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, $3); }
    ;

identifier_list: /* empty */ { $$ = NULL; }
    | TIDENTIFIER { $$ = nodo_nuevo(NODO_LISTA_PARAMETROS, $1, NULL); }
    | identifier_list ',' TIDENTIFIER { $$ = nodo_nuevo(NODO_LISTA_PARAMETROS, $3, $1); }
    ;

list_items: /* empty */ { $$ = nodo_nuevo(NODO_LISTA_ASIGNAR_ELEMENTO, NULL, NULL); }
    | list_items ',' expression { $$ = nodo_nuevo(NODO_LISTA_ASIGNAR_ELEMENTO, $3, $1); }
    | expression { $$ = nodo_nuevo(NODO_LISTA_ASIGNAR_ELEMENTO, $1, NULL); }
    ;

get_list_item:
     TIDENTIFIER '[' TINT ']' { $$ = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, $1, $3); }
    ;

dict_items: /* empty */ { $$ = nodo_nuevo(NODO_DICCIONARIO_ELEMENTOS, NULL, NULL); }
    | dict_items ',' dict_item { $$ = nodo_nuevo(NODO_DICCIONARIO_ELEMENTOS, $3, $1); }
    | dict_item { $$ = nodo_nuevo(NODO_DICCIONARIO_ELEMENTOS, $1, NULL); }
    ;

dict_item: /* empty */ { $$ = NULL; }
    | dict_key ':' primary_expression { $$ = nodo_nuevo(NODO_DICCIONARIO_ELEMENTO, $1, $3); }
    ;

dict_key:
    TINT { $$ = $1; }
    | TSTRING { $$ = $1; }
    ;

get_dict_item:
     TIDENTIFIER '[' TSTRING ']' { $$ = nodo_nuevo(NODO_DICCIONARIO_OBTENER_ELEMENTO, $1, $3); }
    ;
%%
