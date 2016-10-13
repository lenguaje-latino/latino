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
%token <node> VERDADERO
%token <node> FALSO
%token <node> NULO
%token <node> NUMERICO
%token <node> CADENA
%token <node> IDENTIFICADOR

%token
    SI
    FIN
    SINO
    MIENTRAS
    HACER
    ROMPER
    CONTINUAR
    CUANDO
    FUNCION
    DESDE
    KBOOL
    RETORNO
    INCLUIR
    ELEGIR
    CASO
    DEFECTO
    ATRIBUTO

%token
    MAYOR_QUE
    MENOR_QUE
    MAYOR_IGUAL
    MENOR_IGUAL
    IGUAL_LOGICO
    DIFERENTE
    Y_LOGICO
    O_LOGICO
    INCREMENTO
    DECREMENTO
    CONCATENAR
    CONCATENAR_IGUAL
    MAS_IGUAL
    MENOS_IGUAL
    POR_IGUAL
    ENTRE_IGUAL
    MODULO_IGUAL

%type <node> include_declaration
%type <node> expression relational_expression
%type <node> logical_not_expression logical_and_expression logical_or_expression equality_expression
%type <node> multiplicative_expression additive_expression concat_expression
%type <node> statement statement_list unary_expression ternary_expression incdec_statement
%type <node> iteration_statement jump_statement function_definition
%type <node> argument_expression_list declaration primary_expression
%type <node> constant_expression function_call selection_statement parameter_list
%type <node> list_new list_items
%type <node> dict_new dict_items dict_item
%type <node> labeled_statements labeled_statement_case labeled_statement_default
%type <node> variable_access field_designator

/*
 * precedencia de operadores
 * 0: -
 * 1: * /
 * 2: + -
 *
 */
%right '='
%left CONCATENAR CONCATENAR_IGUAL
%left '+' '-'
%left '*' '/' '%' '!'
%left Y_LOGICO O_LOGICO
%left IGUAL_LOGICO MAYOR_IGUAL MAYOR_QUE MENOR_IGUAL MENOR_QUE DIFERENTE

%start program

%%

constant_expression
    : NUMERICO
    | CADENA
    ;

primary_expression
    : IDENTIFICADOR
    | VERDADERO
    | FALSO
    | NULO
    ;

unary_expression
    : '-' expression %prec '*' {
        $$ = nodo_reducir_constantes(NODO_MENOS_UNARIO, $2, NULL);
        if($$ == NULL) YYABORT;
    }
    | '+' expression %prec '*' {
        $$ = nodo_reducir_constantes(NODO_MAS_UNARIO, $2, NULL);
        if($$ == NULL) YYABORT;
    }
    ;

multiplicative_expression
    : expression '*' expression {
        $$ = nodo_reducir_constantes(NODO_MULTIPLICACION, $1, $3);
        if($$ == NULL) YYABORT;
    }
    | expression '/' expression {
        $$ = nodo_reducir_constantes(NODO_DIVISION, $1, $3);
        if($$ == NULL) YYABORT;
    }
    | expression '%' expression {
        $$ = nodo_reducir_constantes(NODO_MODULO, $1, $3);
        if($$ == NULL) YYABORT;
    }
    ;

additive_expression
    : expression '-' expression {
        $$ = nodo_reducir_constantes(NODO_RESTA, $1, $3);
        if($$ == NULL) YYABORT;
    }
    | expression '+' expression {
        $$ = nodo_reducir_constantes(NODO_SUMA, $1, $3);
        if($$ == NULL) YYABORT;
    }
    ;

relational_expression
    : expression MAYOR_QUE expression { $$ = nodo_nuevo(NODO_MAYOR_QUE, $1, $3); }
    | expression MENOR_QUE expression { $$ = nodo_nuevo(NODO_MENOR_QUE, $1, $3); }
    | expression MAYOR_IGUAL expression { $$ = nodo_nuevo(NODO_MAYOR_IGUAL, $1, $3); }
    | expression MENOR_IGUAL expression { $$ = nodo_nuevo(NODO_MENOR_IGUAL, $1, $3); }
    ;

equality_expression
    : expression DIFERENTE expression { $$ = nodo_nuevo(NODO_DESIGUALDAD, $1, $3); }
    | expression IGUAL_LOGICO expression { $$ = nodo_nuevo(NODO_IGUALDAD, $1, $3); }
    ;

logical_not_expression
    : '!' expression %prec '*' { $$ = nodo_nuevo(NODO_NO, $2, NULL); }
    ;

logical_and_expression
    : expression Y_LOGICO expression { $$ = nodo_nuevo(NODO_Y, $1, $3); }
	  ;

logical_or_expression
	  : expression O_LOGICO expression { $$ = nodo_nuevo(NODO_O, $1, $3); }
	  ;

ternary_expression
    : expression '\?' expression ':' expression  { $$ = nodo_nuevo_si($1, $3, $5); }
    ;

concat_expression
    : expression CONCATENAR expression { $$ = nodo_nuevo(NODO_CONCATENAR, $1, $3); }
    ;

expression
        : '(' expression ')' { $$ = $2; }
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
        | concat_expression
        | function_call
        | list_new
        | dict_new
        | variable_access
        ;

program
    : { /* empty */
        *root = NULL;
    }
    | statement_list { *root = $1; }
    ;

statement_list
    : statement statement_list {
        if($2){
            $$ = nodo_nuevo(NODO_BLOQUE, $1, $2);
        }
    }
    | statement {
        if($1){
          $$ = nodo_nuevo(NODO_BLOQUE, $1, NULL);
        }
    }
    | error statement_list { yyerrok; yyclearin;}
    ;

statement
    : include_declaration
    | declaration
    | selection_statement
    | iteration_statement
    | jump_statement
    | function_definition
    | function_call
    ;

incdec_statement
    : variable_access INCREMENTO { $$ = nodo_nuevo(NODO_INC, $1, NULL); }
    | variable_access DECREMENTO { $$ = nodo_nuevo(NODO_DEC, $1, NULL); }
    ;

include_declaration
    : INCLUIR '(' CADENA ')' { $$ = nodo_nuevo_incluir($3); }
    ;

variable_access
    : IDENTIFICADOR
    | field_designator
    ;

field_designator
    : variable_access ATRIBUTO IDENTIFICADOR { $$ = nodo_nuevo(NODO_ATRIBUTO, $1, $3); }
    | variable_access '[' expression ']' { $$ = nodo_nuevo(NODO_LISTA_OBTENER_ELEMENTO, $3, $1); }
    ;

declaration
    : variable_access '=' expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | variable_access '=' ternary_expression { $$ = nodo_nuevo_asignacion($3, $1); }
    | variable_access '[' expression ']' '=' expression { $$ = nodo_nuevo_asignacion_lista_elem($6, $1, $3); }
    | variable_access CONCATENAR_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo(NODO_CONCATENAR, $1, $3)), $1); }
    | variable_access MAS_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo(NODO_SUMA, $1, $3)), $1); }
    | variable_access MENOS_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo(NODO_RESTA, $1, $3)), $1); }
    | variable_access POR_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo(NODO_MULTIPLICACION, $1, $3)), $1); }
    | variable_access ENTRE_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo(NODO_DIVISION, $1, $3)), $1); }
    | variable_access MODULO_IGUAL expression { $$ = nodo_nuevo_asignacion((nodo_nuevo(NODO_MODULO, $1, $3)), $1); }
    | incdec_statement
;

labeled_statements
    : labeled_statement_case labeled_statements {
        $$ = nodo_nuevo(NODO_CASOS, $1, $2);
    }
    | labeled_statement_case {
        $$ = nodo_nuevo(NODO_CASOS, $1, NULL);
    }
    | labeled_statement_default {
        $$ = nodo_nuevo(NODO_CASOS, $1, NULL);
    }
    ;

labeled_statement_case
    :
    CASO constant_expression ':' statement_list {
        $$ = nodo_nuevo(NODO_CASO, $2, $4);
    }
    ;

labeled_statement_default
    :
    DEFECTO ':' statement_list {
        $$ = nodo_nuevo(NODO_DEFECTO, NULL, $3);
    }
    ;

selection_statement:
    SI expression statement_list FIN {
        $$ = nodo_nuevo_si($2, $3, NULL); }
    | SI expression statement_list SINO statement_list FIN {
        $$ = nodo_nuevo_si($2, $3, $5); }
    | ELEGIR expression labeled_statements FIN {
        $$ = nodo_nuevo(NODO_ELEGIR, $2, $3);
    }
    ;

iteration_statement
    : MIENTRAS expression statement_list FIN {
        $$ = nodo_nuevo_mientras($2, $3); }
    | HACER statement_list CUANDO expression {
        $$ = nodo_nuevo_hacer($4, $2); }
    | DESDE '(' declaration ';' expression ';' declaration ')'
        statement_list  FIN {
        $$ = nodo_nuevo_desde($3, $5, $7, $9); }
    ;

jump_statement
    : RETORNO expression { $$ = nodo_nuevo(NODO_RETORNO, $2, NULL); }
    ;

function_definition
    : FUNCION IDENTIFICADOR '(' parameter_list ')' statement_list FIN {
        $$ = nodo_nuevo_funcion($2, $4, $6);
    }
    ;

function_call
    : variable_access '(' argument_expression_list ')' { $$ = nodo_nuevo(NODO_FUNCION_LLAMADA, $1, $3); }
    ;

argument_expression_list
    : /* empty */ { $$ = NULL; }
    | expression { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, NULL); }
    | expression ',' argument_expression_list { $$ = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, $1, $3); }
    ;

parameter_list
    : /* empty */ { $$ = NULL; }
    | IDENTIFICADOR { $$ = nodo_nuevo(NODO_FUNCION_PARAMETROS, $1, NULL); }
    | parameter_list ',' IDENTIFICADOR { $$ = nodo_nuevo(NODO_FUNCION_PARAMETROS, $3, $1); }
    ;

list_new
    : '[' list_items ']' { $$ = nodo_nuevo(NODO_LISTA, $2, NULL); }
    ;

list_items
    : /* empty */ { $$ = NULL; }
    | expression { $$ = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, $1, NULL); }
    | list_items ',' expression { $$ = nodo_nuevo(NODO_LISTA_AGREGAR_ELEMENTO, $3, $1); }
    ;

dict_new
    : '{' dict_items '}' { $$ = nodo_nuevo(NODO_DICCIONARIO, $2, NULL); }
    ;

dict_items
    : /* empty */ { $$ = NULL; }
    | dict_item { $$ = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, $1, NULL); }
    | dict_items ',' dict_item { $$ = nodo_nuevo(NODO_DICC_AGREGAR_ELEMENTO, $3, $1); }
    ;

dict_item
    : { /* empty */ $$ = NULL; }
    | CADENA ':' expression { $$ = nodo_nuevo(NODO_DICC_ELEMENTO, $1, $3); }
    ;

%%

//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
  if(!parse_silent){
      lat_fatal_error("Linea %d, %d: %s", yylloc_param->first_line, yylloc_param->first_column,  s);
  }
  return 0;
}
