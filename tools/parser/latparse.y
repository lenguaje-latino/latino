%{

/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* bison -y -oparse.c parse.y */
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define YYENABLE_NLS 1
#define YYLEX_PARAM &yylval, &yylloc

#include <stddef.h>

#include "latino.h"
#include "latast.h"
#include "latlex.h"

#ifndef LAT_ERROR_FMT
#define LAT_ERROR_FMT "%s:%d:%d: %s\n"
#endif

#ifdef __linux
#include <libintl.h>
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root, const char *s);
int yylex (YYSTYPE * yylval_param,YYLTYPE * yylloc_param ,yyscan_t yyscanner);

%}

%output "latparse.c"
%defines "latparse.h"

%locations
%define api.pure
%lex-param {void *scanner}
%parse-param {ast **root}
%parse-param {void *scanner}

/* declare tokens */
%token <node> NUMERICO
%token <node> CADENA
%token <node> IDENTIFICADOR
%token <node> VAR_ARGS

%token
    SI
    O_SI
    FIN
    SINO
    MIENTRAS
    REPETIR
    ROMPER
    CONTINUAR
    HASTA
    FUNCION
    DESDE
    RETORNO
    ELEGIR
    CASO
    DEFECTO
    ATRIBUTO
    VERDADERO
    FALSO
    NULO
    EXPONENTE
    PARA
    EN
    RANGO
    IR

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
    REGEX
    GLOBAL

%type <node> expression relational_expression
%type <node> logical_not_expression logical_and_expression logical_or_expression equality_expression
%type <node> multiplicative_expression additive_expression concat_expression
%type <node> statement statement_list unary_expression ternary_expression incdec_statement
%type <node> iteration_statement jump_statement function_definition function_anonymous jump_loop
%type <node> argument_expression_list declaration primary_expression
%type <node> constant_expression function_call selection_statement parameter_list
%type <node> list_new list_items
%type <node> dict_new dict_items dict_item
%type <node> labeled_statements labeled_statement_case labeled_statement_case_case labeled_statement_default
%type <node> variable_access field_designator
%type <node> osi_statements osi_statement global_declaration goto_etiqueta

/*
 * precedencia de operadores
 * 0: -
 * 1: * /
 * 2: + -
 *
 */
%right '='
%right CONCATENAR
%left CONCATENAR_IGUAL
%left Y_LOGICO O_LOGICO
%left IGUAL_LOGICO MAYOR_IGUAL MAYOR_QUE MENOR_IGUAL MENOR_QUE DIFERENTE REGEX
%left '+' '-'
%left '*' '/' '%' '!'
%left '^'
%left EXPONENTE

%start program

%%

constant_expression
    : NUMERICO
    | CADENA
    ;

primary_expression
    : IDENTIFICADOR
    | VERDADERO { $$ = latA_logico(1, @1.first_line, @1.first_column);}
    | FALSO { $$ = latA_logico(0, @1.first_line, @1.first_column);}
    | NULO { $$ = latA_nulo(NULL, @1.first_line, @1.first_column);}
    ;

unary_expression
    : '-' expression %prec '*' {
        $$ = latA_nodo(NODO_MENOS_UNARIO, $2, NULL, @1.first_line, @1.first_column);
        if($$ == NULL) YYABORT;
    }
    | '+' expression %prec '*' {
        $$ = latA_nodo(NODO_MAS_UNARIO, $2, NULL, @1.first_line, @1.first_column);
        if($$ == NULL) YYABORT;
    }
    ;

multiplicative_expression
    : expression '^' expression {
        $$ = latA_nodo(NODO_POTENCIA, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    | expression EXPONENTE expression {
        $$ = latA_nodo(NODO_POTENCIA, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    | expression '*' expression {
        $$ = latA_nodo(NODO_MULTIPLICACION, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    | expression '/' expression {
        $$ = latA_nodo(NODO_DIVISION, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    | expression '%' expression %prec '*' {
        $$ = latA_nodo(NODO_MODULO, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    ;

additive_expression
    : expression '-' expression {
        $$ = latA_nodo(NODO_RESTA, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    | expression '+' expression {
        $$ = latA_nodo(NODO_SUMA, $1, $3, @2.first_line, @2.first_column);
        if($$ == NULL) YYABORT;
    }
    ;

relational_expression
    : expression MAYOR_QUE expression { $$ = latA_nodo(NODO_MAYOR_QUE, $1, $3, @2.first_line, @2.first_column); }
    | expression MENOR_QUE expression { $$ = latA_nodo(NODO_MENOR_QUE, $1, $3, @2.first_line, @2.first_column); }
    | expression MAYOR_IGUAL expression { $$ = latA_nodo(NODO_MAYOR_IGUAL, $1, $3, @2.first_line, @2.first_column); }
    | expression MENOR_IGUAL expression { $$ = latA_nodo(NODO_MENOR_IGUAL, $1, $3, @2.first_line, @2.first_column); }
    ;

equality_expression
    : expression DIFERENTE expression { $$ = latA_nodo(NODO_DESIGUALDAD, $1, $3, @2.first_line, @2.first_column); }
    | expression IGUAL_LOGICO expression { $$ = latA_nodo(NODO_IGUALDAD, $1, $3, @2.first_line, @2.first_column); }
    | expression REGEX expression { $$ = latA_nodo(NODO_REGEX, $1, $3, @2.first_line, @2.first_column); }
    ;

logical_not_expression
    : '!' expression %prec '*' { $$ = latA_nodo(NODO_NO, $2, NULL, @2.first_line, @2.first_column); }
    ;

logical_and_expression
    : expression Y_LOGICO expression { $$ = latA_nodo(NODO_Y, $1, $3, @2.first_line, @2.first_column); }
    ;

logical_or_expression
    : expression O_LOGICO expression { $$ = latA_nodo(NODO_O, $1, $3, @2.first_line, @2.first_column); }
    ;

ternary_expression
    : expression '\?' expression ':' expression  { $$ = latA_si($1, $3, $5); }
    ;

concat_expression
    : expression CONCATENAR expression { $$ = latA_nodo(NODO_CONCATENAR, $1, $3, @2.first_line, @2.first_column); }
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
    | function_anonymous
    | ternary_expression
    | incdec_statement
    | VAR_ARGS { $$ = latA_nodo(NODO_LOAD_VAR_ARGS , NULL, NULL, 0, 0); }
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
            $$ = latA_nodo(NODO_BLOQUE, $1, $2, @1.first_line, @1.first_column);
        }
    }
    | statement {
        if($1){
          $$ = latA_nodo(NODO_BLOQUE, $1, NULL, @1.first_line, @1.first_column);
        }
    }
    | error statement_list { yyerrok; yyclearin;}
    ;

statement
    : declaration
    | global_declaration
    | selection_statement
    | iteration_statement
    | jump_statement
    | function_definition
    | function_call
    | incdec_statement
    | jump_loop
    | goto_etiqueta
    ;

incdec_statement
    : variable_access INCREMENTO { $$ = latA_nodo(NODO_INC, $1, NULL, @2.first_line, @2.first_column); }
    | variable_access DECREMENTO { $$ = latA_nodo(NODO_DEC, $1, NULL, @2.first_line, @2.first_column); }
    ;

variable_access
    : IDENTIFICADOR
    | field_designator
    | function_call
    ;

field_designator
    : variable_access ATRIBUTO IDENTIFICADOR { $$ = latA_nodo(NODO_ATRIBUTO, $1, $3, @3.first_line, @3.first_column); }
    | variable_access '[' expression ']' { $$ = latA_nodo(NODO_LISTA_OBTENER_ELEMENTO, $3, $1, @3.first_line, @3.first_column); }
    ;

global_declaration
    : GLOBAL declaration {
        $$ = latA_nodo(NODO_GLOBAL, $2, NULL, @1.first_line, @1.first_column);
    }
    | GLOBAL function_definition {
        $$ = latA_nodo(NODO_GLOBAL, $2, NULL, @1.first_line, @1.first_column);
    }
    ;

declaration
    : variable_access '=' expression { $$ = latA_asign($3, $1); }
    | variable_access CONCATENAR_IGUAL expression { $$ = latA_asign(
        (latA_nodo(NODO_CONCATENAR, $1, $3, @2.first_line, @2.first_column)), $1); }
    | variable_access MAS_IGUAL expression { $$ = latA_asign(
        (latA_nodo(NODO_SUMA, $1, $3, @2.first_line, @2.first_column)), $1); }
    | variable_access MENOS_IGUAL expression { $$ = latA_asign(
        (latA_nodo(NODO_RESTA, $1, $3, @2.first_line, @2.first_column)), $1); }
    | variable_access POR_IGUAL expression { $$ = latA_asign(
        (latA_nodo(NODO_MULTIPLICACION, $1, $3, @2.first_line, @2.first_column)), $1); }
    | variable_access ENTRE_IGUAL expression { $$ = latA_asign(
        (latA_nodo(NODO_DIVISION, $1, $3, @2.first_line, @2.first_column)), $1); }
    | variable_access MODULO_IGUAL expression { $$ = latA_asign(
        (latA_nodo(NODO_MODULO, $1, $3, @2.first_line, @2.first_column)), $1); }
    | parameter_list '=' argument_expression_list { $$ = latA_asign($3, $1); }
    | variable_access '[' expression ']' '=' expression { $$ = latA_asign_le($6, $1, $3); }
    ;

labeled_statements
    : labeled_statement_case labeled_statements {
        $$ = latA_nodo(NODO_CASOS, $1, $2, @1.first_line, @1.first_column);
    }
    | labeled_statement_case {
        $$ = latA_nodo(NODO_CASOS, $1, NULL, @1.first_line, @1.first_column);
    }
    | labeled_statement_default {
        $$ = latA_nodo(NODO_CASOS, $1, NULL, @1.first_line, @1.first_column);
    }
    ;

labeled_statement_case
    : CASO labeled_statement_case_case statement_list {
        $$ = latA_nodo(NODO_CASO, $2, $3, @1.first_line, @1.first_column);
    }
    ;

labeled_statement_case_case
    : constant_expression ':'
    | constant_expression ':' CASO labeled_statement_case_case {
        $$ = latA_nodo(NODO_CASOS, $1, $4, @1.first_line, @1.first_column);
    }
    ;

labeled_statement_default
    : DEFECTO ':' statement_list {
        $$ = latA_nodo(NODO_DEFECTO, NULL, $3, @1.first_line, @1.first_column);
    }
    ;

selection_statement
    : SI expression statement_list FIN {
        $$ = latA_si($2, $3, NULL); }
    | SI expression statement_list SINO statement_list FIN {
        $$ = latA_si($2, $3, $5); }
    | SI expression statement_list osi_statements FIN {
        $$ = latA_si($2, $3, $4); }
    | ELEGIR expression labeled_statements FIN {
        $$ = latA_nodo(NODO_ELEGIR, $2, $3, @1.first_line, @1.first_column);
    }
    ;

osi_statements
    : osi_statement
    | osi_statements osi_statement
    ;

osi_statement
    : O_SI expression statement_list {
          $$ = latA_si($2, $3, NULL);
    }
    | O_SI expression statement_list SINO statement_list {
          $$ = latA_si($2, $3, $5);
    }
    | O_SI expression statement_list osi_statements {
          $$ = latA_si($2, $3, $4);
    }
    ;

iteration_statement
    : MIENTRAS expression statement_list FIN {
        $$ = latA_mientras($2, $3); }
    | REPETIR statement_list HASTA expression {
        $$ = latA_hacer($4, $2); }
    | DESDE '(' declaration ';' expression ';' statement ')'
        statement_list  FIN {
        $$ = latA_desde($3, $5, $7, $9); }
    | PARA IDENTIFICADOR EN RANGO '(' expression ')'
        statement_list FIN {
        $$ = latA_para($2, NULL, $6, NULL, $8);
        }
    | PARA IDENTIFICADOR EN RANGO '(' expression ',' expression ')'
        statement_list FIN {
        $$ = latA_para($2, $6, $8, NULL, $10);
        }
    | PARA IDENTIFICADOR EN RANGO '(' expression ',' expression ',' expression ')'
        statement_list FIN {
        $$ = latA_para($2, $6, $8, $10, $12);
        }
    ;

goto_etiqueta
    : IDENTIFICADOR ':' { $$ = latA_nodo(NODO_ETIQUETA, $1, NULL, @1.first_line, @1.first_column); }
    ;

jump_statement
    : RETORNO expression { $$ = latA_nodo(NODO_RETORNO, $2, NULL, @1.first_line, @1.first_column); }
    | RETORNO argument_expression_list { $$ = latA_nodo(NODO_RETORNO, $2, NULL, @1.first_line, @1.first_column); }
    | IR IDENTIFICADOR { $$ =  latA_nodo(NODO_IR, $2, NULL, @1.first_line, @1.first_column); }
    ;

jump_loop
    : ROMPER    { $$ = latA_nodo(NODO_ROMPER, NULL, NULL, @1.first_line, @1.first_column); }
    | CONTINUAR { $$ = latA_nodo(NODO_CONTINUAR, NULL, NULL, @1.first_line, @1.first_column); }
    ;

function_definition
    : FUNCION IDENTIFICADOR '(' parameter_list ')' statement_list FIN {
        $$ = latA_funcion($2, $4, $6, @2.first_line, @2.first_column);
    }
    ;

function_anonymous
    : FUNCION '(' parameter_list ')' statement_list FIN {
        $$ = latA_funcion(latA_var("anonima", @1.first_line, @1.first_column, false), $3, $5, @1.first_line, @1.first_column);
    }
    ;

function_call
    : variable_access '(' argument_expression_list ')' { $$ = latA_nodo(NODO_FUNCION_LLAMADA, $1, $3, @1.first_line, @1.first_column); }
    ;

argument_expression_list
    : /* empty */ { $$ = NULL; }
    | expression { $$ = latA_nodo(NODO_FUNCION_ARGUMENTOS, $1, NULL, @1.first_line, @1.first_column); }
    | expression ',' argument_expression_list {
        if($1->tipo == NODO_VAR_ARGS){
            printf(LAT_ERROR_FMT, filename, @1.first_line, @1.first_column, "Parametro VAR_ARGS (...) debe de ser el ultimo parametro");
            YYABORT;
        }
        $$ = latA_nodo(NODO_FUNCION_ARGUMENTOS, $1, $3, @1.first_line, @1.first_column);
    }
    ;

parameter_list
    : /* empty */ { $$ = NULL; }
    | IDENTIFICADOR { $$ = latA_nodo(NODO_FUNCION_PARAMETROS, $1, NULL, @1.first_line, @1.first_column); }
    | VAR_ARGS { $$ = latA_nodo(NODO_FUNCION_PARAMETROS, $1, NULL, 0, 0); }
    | parameter_list ',' IDENTIFICADOR {
        if($1->izq->tipo == NODO_VAR_ARGS){
            printf(LAT_ERROR_FMT, @3.file_name, @3.first_line, @3.first_column, "Parametro VAR_ARGS (...) debe de ser el ultimo parametro");
            YYABORT;
        }
        $$ = latA_nodo(NODO_FUNCION_PARAMETROS, $3, $1, @3.first_line, @3.first_column); }
    | parameter_list ',' VAR_ARGS { $$ = latA_nodo(NODO_FUNCION_PARAMETROS, $3, $1, 0, 0); }
    ;

list_new
    : '[' list_items ']' { $$ = latA_nodo(NODO_LISTA, $2, NULL, @1.first_line, @1.first_column); }
    ;

list_items
    : /* empty */ { $$ = NULL; }
    | expression { $$ = latA_nodo(NODO_LISTA_AGREGAR_ELEMENTO, $1, NULL, @1.first_line, @1.first_column); }
    | expression ',' list_items {
        if($1->tipo == NODO_LOAD_VAR_ARGS){
            printf(LAT_ERROR_FMT, filename, @1.first_line, @1.first_column, "Parametro VAR_ARGS (...) debe de ser el ultimo parametro");
            YYABORT;
        }
        $$ = latA_nodo(NODO_LISTA_AGREGAR_ELEMENTO, $1, $3, @3.first_line, @3.first_column);
    }
    ;

dict_new
    : '{' dict_items '}' { $$ = latA_nodo(NODO_DICCIONARIO, $2, NULL, @2.first_line, @2.first_column); }
    ;

dict_items
    : /* empty */ { $$ = NULL; }
    | dict_item { $$ = latA_nodo(NODO_DICC_AGREGAR_ELEMENTO, $1, NULL, @1.first_line, @1.first_column); }
    | dict_items ',' dict_item { $$ = latA_nodo(NODO_DICC_AGREGAR_ELEMENTO, $3, $1, @3.first_line, @3.first_column); }
    ;

dict_item
    : { /* empty */ $$ = NULL; }
    | expression ':' expression { $$ = latA_nodo(NODO_DICC_ELEMENTO, $1, $3, @1.first_line, @1.first_column); }
    ;


%%

/*
class_statement
    : class_definition
    | class_definition class_statement
    ;

class_definition
    : CLASS IDENTIFICADOR valores FIN {
        $$ = latA_class(NODO_, $2, $3);
    }
    ;
*/
//se define para analisis sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
const char *s) {
  if(!parse_silent){
      fprintf(stderr, LAT_ERROR_FMT, yylloc_param->file_name,
        yylloc_param->first_line, yylloc_param->first_column,  s);
  }
  return 0;
}