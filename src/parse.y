%{
/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define YYENABLE_NLS 1
#define YYLEX_PARAM &yylval, &yylloc

#include <stddef.h>

#include "latino.h"
#include "ast.h"
#include "lex.h"

#ifndef _WIN32
#include <libintl.h>
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root, const char *s);
int yylex (YYSTYPE * yylval_param,YYLTYPE * yylloc_param ,yyscan_t yyscanner);

%}

%output "parse.c"
%defines "parse.h"

%locations
%define api.pure
%lex-param {void *scanner}
%parse-param {ast **root}
%parse-param {void *scanner}

/* declare tokens */
%token <node> TTRUE
%token <node> TFALSE
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
    KINCLUDE
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
    OP_INCR
    OP_DECR
    OP_CONCAT
    OP_CONCAT_IGUAL

%type <node> include_declaration
%type <node> expression relational_expression
%type <node> logical_not_expression logical_and_expression logical_or_expression equality_expression
%type <node> multiplicative_expression additive_expression concat_expression
%type <node> statement statement_list unary_expression ternary_expression
%type <node> iteration_statement jump_statement function_definition
%type <node> argument_expression_list declaration primary_expression
%type <node> constant_expression function_call selection_statement identifier_list
%type <node> list_new list_items list_get_item
%type <node> dict_new dict_items dict_item key value

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
%left OP_AND OP_OR
%left OP_EQ OP_GE OP_GT OP_LE OP_LT OP_NEQ

%start program

%%

primary_expression:
      TIDENTIFIER { $$ = $1; }
    | TCONSTANT { $$ = $1; }
    | TTRUE { $$ = $1; }
    | TFALSE { $$ = $1; }
    | constant_expression  { $$ = $1; }
    ;

constant_expression:
      TINT { $$ = $1; }
    | TNUMBER { $$ = $1; }
    | TLIT { $$ = $1; }
    | TSTRING { $$ = $1; }
    ;

unary_expression:
	  TIDENTIFIER OP_INCR { $$ = nodo_nuevo(NODO_INCREMENTO, $1, NULL); }
	| TIDENTIFIER OP_DECR { $$ = nodo_nuevo(NODO_DECREMENTO, $1, NULL); }
    | '-' expression %prec '*' { $$ = nodo_nuevo_operador(NODO_MENOS_UNARIO, $2, NULL); }
    ;


multiplicative_expression
    : expression '*' expression { $$ = nodo_nuevo_operador(NODO_MULTIPLICACION, $1, $3); }
    | expression '/' expression { $$ = nodo_nuevo_operador(NODO_DIVISION, $1, $3); }
    | expression '%' expression { $$ = nodo_nuevo_operador(NODO_MODULO, $1, $3); }
    ;

additive_expression
    : expression '+' expression { $$ = nodo_nuevo_operador(NODO_SUMA, $1, $3); }
    | expression '-' expression { $$ = nodo_nuevo_operador(NODO_RESTA, $1, $3); }
    ;

relational_expression
    : expression OP_GT expression { $$ = nodo_nuevo_operador(NODO_MAYOR_QUE, $1, $3); }
    | expression OP_LT expression { $$ = nodo_nuevo_operador(NODO_MENOR_QUE, $1, $3); }
    | expression OP_GE expression { $$ = nodo_nuevo_operador(NODO_MAYOR_IGUAL, $1, $3); }
    | expression OP_LE expression { $$ = nodo_nuevo_operador(NODO_MENOR_IGUAL, $1, $3); }
    ;

equality_expression
    : expression OP_NEQ expression { $$ = nodo_nuevo_operador(NODO_DESIGUALDAD, $1, $3); }
    | expression OP_EQ expression { $$ = nodo_nuevo_operador(NODO_IGUALDAD, $1, $3); }
    ;

logical_not_expression
    : '!' expression %prec '*' { $$ = nodo_nuevo_operador(NODO_NEGACION, $2, NULL); }
    ;

logical_and_expression
    : expression OP_AND expression { $$ = nodo_nuevo_operador(NODO_Y, $1, $3); }
	;

logical_or_expression
    : logical_and_expression
	| expression OP_OR expression { $$ = nodo_nuevo_operador(NODO_O, $1, $3); }
	;

ternary_expression
    : logical_or_expression '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($1, $3, $5); }
    | '(' logical_or_expression ')' '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($2, $5, $7); }
    | relational_expression '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($1, $3, $5); }
    | '(' relational_expression ')' '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($2, $5, $7); }
    | equality_expression '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($1, $3, $5); }
    | '(' equality_expression ')' '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($2, $5, $7); }
    | logical_not_expression '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($1, $3, $5); }
    | '(' logical_not_expression ')' '\?' primary_expression ':' primary_expression  { $$ = nodo_nuevo_si($2, $5, $7); }
	;

concat_expression
    : expression OP_CONCAT expression { $$ = nodo_nuevo_operador(NODO_CONCATENAR, $1, $3); }
    ;

program
    : statement_list {
        *root = $1;
    }
    ;

statement_list
    : statement_list statement {
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
    | include_declaration { $$ = $1; }
    | declaration  { $$ = $1; }
    | selection_statement { $$ = $1; }
    | iteration_statement { $$ = $1; }
    | jump_statement { $$ = $1; }
    | function_definition { $$ = $1; }
    | function_call { $$ = $1; }
    ;

include_declaration:
    KINCLUDE TSTRING { $$ = nodo_nuevo_incluir($2); }
    ;

declaration:
      TIDENTIFIER '=' expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | TIDENTIFIER '=' ternary_expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | TIDENTIFIER '=' '[' list_items ']' { $$ = nodo_nuevo_asignacion(nodo_nuevo(NODO_LISTA, $4, NULL), $1); }
    | TIDENTIFIER '=' '{' dict_items '}' { $$ = nodo_nuevo_asignacion(nodo_nuevo(NODO_DICCIONARIO, $4, NULL), $1); }
    | TIDENTIFIER '[' TINT ']' '=' expression { $$ = nodo_nuevo_asignacion_lista_elem($6, $1, $3); }
    | TIDENTIFIER '[' TIDENTIFIER ']' '=' expression { $$ = nodo_nuevo_asignacion_lista_elem($6, $1, $3); }
    | TIDENTIFIER '[' TLIT ']' '=' expression { $$ = nodo_nuevo_asignacion_dicc_elem($6, $1, $3); }
    | TIDENTIFIER '[' TSTRING ']' '=' expression { $$ = nodo_nuevo_asignacion_dicc_elem($6, $1, $3); }
    | TIDENTIFIER OP_CONCAT_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo_operador(NODO_CONCATENAR, $1, $3)), $1); }
    | TCONSTANT '=' constant_expression { $$ = nodo_nuevo_asignacion($3, $1); }
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
    KIF expression statement_list KEND {
        $$ = nodo_nuevo_si($2, $3, NULL); }
    | KIF expression statement_list KELSE statement_list KEND {
        $$ = nodo_nuevo_si($2, $3, $5); }
    /*| KSWITCH '(' TIDENTIFIER ')' labeled_statement KEND {
        $$ = nodo_nuevo(NODO_SELECCION, $3, $5); }*/
    ;

iteration_statement
    : KWHILE '(' expression ')' statement_list KEND {
        $$ = nodo_nuevo_mientras($3, $5); }
    | KWHILE expression statement_list KEND {
        $$ = nodo_nuevo_mientras($2, $3); }
    | KDO statement_list KWHEN '(' expression ')' {
        $$ = nodo_nuevo_hacer($5, $2); }
    | KDO statement_list KWHEN expression {
        $$ = nodo_nuevo_hacer($4, $2); }
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

expression
    : '(' expression ')' { $$ = $2; }
    | logical_not_expression
    | logical_or_expression
    | primary_expression
    | relational_expression
    | multiplicative_expression
    | additive_expression
    | equality_expression
    | unary_expression
    | concat_expression
    | function_call
    | list_new
    | list_get_item
    | dict_new
    ;

function_call:
     TIDENTIFIER '(' argument_expression_list ')' { $$ = nodo_nuevo(NODO_FUNCION_LLAMADA, $1, $3); }
    ;

argument_expression_list: /* empty */ { $$ = NULL; }
    | expression { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, NULL); }
    | expression ',' argument_expression_list { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, $3); }
    ;

identifier_list: /* empty */ { $$ = NULL; }
    | TIDENTIFIER { $$ = nodo_nuevo(NODO_LISTA_PARAMETROS, $1, NULL); }
    | identifier_list ',' TIDENTIFIER { $$ = nodo_nuevo(NODO_LISTA_PARAMETROS, $3, $1); }
    ;

list_new:
    '[' list_items ']' { $$ = nodo_nuevo(NODO_LISTA, $2, NULL); }
    ;

dict_new:
    '{' dict_items '}' { $$ = nodo_nuevo(NODO_DICCIONARIO, $2, NULL); }
    ;

list_items: /* empty */ { $$ = NULL; }
    | list_items ',' expression { $$ = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, $3, $1); }
    | expression { $$ = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, $1, NULL); }
    ;

dict_items: /* empty */ { $$ = NULL; }
    | dict_item ',' dict_item { $$ = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, $3, $1); }
    | dict_item { $$ = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, $1, NULL); }
    ;

dict_item:
    key ':' value { $$ = nodo_nuevo(NODO_DICC_ELEMENTO, $3, $1); }
    ;

key:
    TLIT { $$ = $1; }
    | TSTRING { $$ = $1; }
    ;

value:
    primary_expression { $$ = $1; }
    ;

list_get_item:
      TIDENTIFIER '[' TSTRING ']' { $$ = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, $3, $1); }
    | TIDENTIFIER '[' TLIT ']' { $$ = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, $3, $1); }
    | TIDENTIFIER '[' TINT ']' { $$ = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, $3, $1); }
    | TIDENTIFIER '[' TIDENTIFIER ']' { $$ = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, $3, $1); }
    ;

%%

//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
  lat_registrar_error("Linea %d: %s", (yylloc_param->first_line + 1), s);
  return 0;
}
