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

#ifdef __linux
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
%token <nodo> VERDADERO
%token <nodo> FALSO
%token <nodo> ENTERO
%token <nodo> LITERAL
%token <nodo> NUMERICO
%token <nodo> CADENA
%token <nodo> IDENTIFICADOR
%token <nodo> CONSTANTE
%token
SI
FIN
SINO
MIENTRAS
ROMPER
CONTINUAR
DESDE
REPETIR
HASTA
POR
EN
FUNCION
RETORNO
INCLUIR
ELEGIR
CASO
DEFECTO
CLASE

%token
MAYOR_QUE
MENOR_QUE
MAYOR_IGUAL
MENOR_IGUAL
IGUAL_LOGICO
DIFERENTE
Y_LOGICO
O_LOGICO

%type <nodo> include_declaration
%type <nodo> expression relational_expression
%type <nodo> logical_not_expression logical_and_expression logical_or_expression equality_expression
%type <nodo> multiplicative_expression additive_expression
%type <nodo> statement statement_list unary_expression ternary_expression
%type <nodo> iteration_statement jump_statement function_definition
%type <nodo> argument_expression_list declaration primary_expression
%type <nodo> constant_expression function_call selection_statement identifier_list
%type <nodo> list_new list_items list_get_item
%type <nodo> dict_new dict_items dict_item key
%type <nodo> labeled_statements labeled_statement_case labeled_statement_default
%type <nodo> class_declaration variable_access field_designator


/*
 * precedencia de operadores
 * 0: -
 * 1: * /
 * 2: + -
 *
 */
%right '='
%left '+' '-' /*OP_CONCAT OP_CONCAT_IGUAL*/
%left '*' '/' '%'
%left Y_LOGICO O_LOGICO
%left MAYOR_QUE MENOR_QUE MAYOR_IGUAL MENOR_IGUAL IGUAL_LOGICO DIFERENTE

%start program

%%

constant_expression
:
ENTERO
| NUMERICO
| LITERAL
| CADENA
;

primary_expression
:
IDENTIFICADOR
| CONSTANTE
| VERDADERO
| FALSO
;

unary_expression
: '-'
expression %prec '*' { $$ = nodo_nuevo_op("-", $2, NULL, @1.first_line, @1.first_column); }
| '+' expression %prec '*' { $$ = nodo_nuevo_op("+", $2, NULL, @1.first_line, @1.first_column); }
;

multiplicative_expression
:
expression '*' expression { $$ = nodo_nuevo_op("*", $1, $3, @2.first_line, @2.first_column); }
| expression '/' expression { $$ = nodo_nuevo_op("/", $1, $3, @2.first_line, @2.first_column); }
| expression '%' expression { $$ = nodo_nuevo_op("%", $1, $3, @2.first_line, @2.first_column); }
;

additive_expression
:
expression '-' expression { $$ = nodo_nuevo_op("-", $1, $3, @2.first_line, @2.first_column); }
| expression '+' expression { $$ = nodo_nuevo_op("+", $1, $3, @2.first_line, @2.first_column); }
;

relational_expression
:
expression MAYOR_QUE expression { $$ = nodo_nuevo_op(">", $1, $3, @2.first_line, @2.first_column); }
| expression MENOR_QUE expression { $$ = nodo_nuevo_op("<", $1, $3, @2.first_line, @2.first_column); }
| expression MAYOR_IGUAL expression { $$ = nodo_nuevo_op(">=", $1, $3, @2.first_line, @2.first_column); }
| expression MENOR_IGUAL expression { $$ = nodo_nuevo_op("<=", $1, $3, @2.first_line, @2.first_column); }
;

equality_expression
:
expression DIFERENTE expression { $$ = nodo_nuevo_op("!=", $1, $3, @2.first_line, @2.first_column); }
| expression IGUAL_LOGICO expression { $$ = nodo_nuevo_op("==", $1, $3, @2.first_line, @2.first_column); }
;

logical_not_expression
: '!'
expression %prec '*' { $$ = nodo_nuevo_op("!", $2, NULL, @1.first_line, @1.first_column); }
;

logical_and_expression
:
expression Y_LOGICO expression { $$ = nodo_nuevo_op("&&", $1, $3, @2.first_line, @2.first_column); }
;

logical_or_expression
:
expression O_LOGICO expression { $$ = nodo_nuevo_op("||", $1, $3, @2.first_line, @2.first_column); }
;

ternary_expression
:
expression '\?' expression ':' expression {
    $$ = nodo_nuevo_si($1, $3, $5, @1.first_line, @1.first_column);
}

expression
: '('
expression ')' { $$ = $2; }
| constant_expression
| primary_expression
| unary_expression
| multiplicative_expression
| additive_expression
| relational_expression
| equality_expression
| logical_not_expression
| logical_and_expression
| logical_or_expression
| function_call
| list_new
| list_get_item
| dict_new
;

program
: { /* empty */
    *root = NULL;
}
| statement_list { *root = $1; }
;

statement_list
:
statement statement_list {
    if($2) {
        $$ = nodo_nuevo(NODO_BLOQUE, $1, $2, @1.first_line, @1.first_column);
    }
}
| statement {
    if($1) {
        $$ = nodo_nuevo(NODO_BLOQUE, $1, NULL, @1.first_line, @1.first_column);
    }
}
| error statement_list { yyerrok; yyclearin; }
;

statement
:
include_declaration
| declaration
| selection_statement
| iteration_statement
| jump_statement
| function_definition
| function_call
| class_declaration
;

class_statements
: class_statement class_statements
| class_statement
;

class_statement
: declaration
| function_definition
;

class_declaration
: CLASE IDENTIFICADOR class_statements FIN {
    $$ = NULL;
    printf("creando clase...\n");
}
| CLASE IDENTIFICADOR ':' IDENTIFICADOR class_statements FIN {
    $$ = NULL;
    printf("creando clase hija...\n");
}


include_declaration
:
INCLUIR '(' CADENA ')' { $$ = nodo_nuevo_incluir($3, @1.first_line, @1.first_column); }
;

variable_access
: IDENTIFICADOR
| field_designator
;

field_designator
: variable_access '.' IDENTIFICADOR { $$ = NULL; }
;

declaration
: variable_access '=' expression { $$ = nodo_nuevo_asignacion($1, $3, @1.first_line, @1.first_column); }
| variable_access '=' ternary_expression { $$ = nodo_nuevo_asignacion($1, $3, @1.first_line, @1.first_column); }
 /*| CONSTANTE '=' constant_expression { $$ = nodo_nuevo_asignacion($1, $3, @1.first_line, @1.first_column); }*/
| variable_access '[' ENTERO ']' '=' expression { $$ = nodo_nuevo_asignacion_lista_elem($1, $3, $6, @1.first_line, @1.first_column); }
| variable_access '[' IDENTIFICADOR ']' '=' expression { $$ = nodo_nuevo_asignacion_lista_elem($1, $3, $6, @1.first_line, @1.first_column); }
;

labeled_statements
:
labeled_statement_case {
    $$ = nodo_nuevo(NODO_CASOS, $1, NULL, @1.first_line, @1.first_column);
}
| labeled_statement_case labeled_statements {
    $$ = nodo_nuevo(NODO_CASOS, $1, $2, @1.first_line, @1.first_column);
}
| labeled_statement_default {
    $$ = nodo_nuevo(NODO_CASOS, $1, NULL, @1.first_line, @1.first_column);
}
;

labeled_statement_case
:
CASO constant_expression ':' statement_list {
    $$ = nodo_nuevo(NODO_CASO, $2, $4, @1.first_line, @1.first_column);
}
;

labeled_statement_default
:
DEFECTO ':' statement_list {
    $$ = nodo_nuevo(NODO_DEFECTO, NULL, $3, @1.first_line, @1.first_column);
}
;

selection_statement
:
SI expression statement_list FIN {
    $$ = nodo_nuevo_si($2, $3, NULL, @1.first_line, @1.first_column);
}
| SI expression statement_list SINO statement_list FIN {
    $$ = nodo_nuevo_si($2, $3, $5, @1.first_line, @1.first_column);
}
| ELEGIR expression labeled_statements FIN {
    $$ = nodo_nuevo(NODO_ELEGIR, $2, $3, @1.first_line, @1.first_column);
}
;

iteration_statement
:
MIENTRAS expression statement_list FIN {
    $$ = nodo_nuevo_mientras($2, $3, @1.first_line, @1.first_column);
}
| REPETIR statement_list HASTA expression {
    $$ = nodo_nuevo_repetir($2, $4, @1.first_line, @1.first_column);
}
| POR IDENTIFICADOR EN list_new statement_list FIN {
    $$ = nodo_nuevo_por($2, $4, $5, @1.first_line, @1.first_column);
}
| POR IDENTIFICADOR EN IDENTIFICADOR statement_list FIN {
    $$ = nodo_nuevo_por($2, $4, $5, @1.first_line, @1.first_column);
}
;

jump_statement
:
RETORNO expression { $$ = nodo_nuevo(NODO_RETORNO, $2, NULL, @1.first_line, @1.first_column); }
| ROMPER { $$ = nodo_nuevo(NODO_ROMPER, NULL, NULL, @1.first_line, @1.first_column); }
| CONTINUAR { $$ = nodo_nuevo(NODO_CONTINUAR, NULL, NULL, @1.first_line, @1.first_column); }
;

function_definition
:
FUNCION IDENTIFICADOR '(' identifier_list ')' statement_list FIN {
    $$ = nodo_nuevo_funcion($2, $4, $6, @1.first_line, @1.first_column);
}
;

function_call
:
variable_access '(' argument_expression_list ')' { $$ = nodo_nuevo(NODO_FUNCION_LLAMADA, $1, $3, @1.first_line, @1.first_column); }
;

argument_expression_list
: { /* empty */
    $$ = NULL;
}
| expression ',' argument_expression_list { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, $3, @1.first_line, @1.first_column); }
| expression { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, NULL, @1.first_line, @1.first_column); }
;

identifier_list
: { /* empty */
    $$ = NULL;
}
| IDENTIFICADOR ',' identifier_list { $$ = nodo_nuevo(NODO_FUNCION_PARAMETROS, $1, $3, @1.first_line, @1.first_column); }
| IDENTIFICADOR { $$ = nodo_nuevo(NODO_FUNCION_PARAMETROS, $1, NULL, @1.first_line, @1.first_column); }
;

list_new
: '['
list_items ']' { $$ = nodo_nuevo(NODO_LISTA, $2, NULL, @1.first_line, @1.first_column); }
;

dict_new
: '{'
dict_items '}' { $$ = nodo_nuevo(NODO_DICCIONARIO, $2, NULL, @1.first_line, @1.first_column); }
;

list_items
: { /* empty */
    $$ = NULL;
}
| expression ',' list_items { $$ = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
| expression { $$ = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, $1, NULL, @1.first_line, @1.first_column); }
;

dict_items
:
dict_item ',' dict_items { $$ = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
| dict_item { $$ = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, $1, NULL, @1.first_line, @1.first_column); }
;

dict_item
: { /* empty */
    $$ = NULL;
}
| key ':' expression { $$ = nodo_nuevo(NODO_DICC_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
;

key
:
LITERAL
| CADENA
;

list_get_item
:
IDENTIFICADOR '[' CADENA ']' { $$ = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
| IDENTIFICADOR '[' LITERAL ']' { $$ = nodo_nuevo(NODO_DICC_OBTENER_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
| IDENTIFICADOR '[' ENTERO ']' { $$ = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
| IDENTIFICADOR '[' IDENTIFICADOR ']' { $$ = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
;

%%

//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
    if(!analisis_silencioso) {
        error("linea %i, %i: %s", yylloc_param->first_line, yylloc_param->first_column, s);
    }
    return 0;
}
