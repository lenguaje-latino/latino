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

#ifndef _LATINO_AST_H_
#define _LATINO_AST_H_

#include <stdbool.h>

/**\brief Muestra las instrucciones que se generan con el AST */
#define DEPURAR_AST 0

extern char *filename;

/** Interface con flex */
typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    char *file_name;
} YYLTYPE;

/** Establece que se definio una interface con Flex */
#define YYLTYPE_IS_DECLARED 1

/** No se requiere cabecera unistd.h */
#define YY_NO_UNISTD_H 1

/** \brief Tipos de nodos en arbol abstracto de sintaxis (Abstract Syntax Tree)
 */
typedef enum {
    NODO_NULO, /* 0 */
    NODO_VALOR,
    NODO_MAS_UNARIO,
    NODO_MENOS_UNARIO,
    NODO_INC,
    NODO_DEC, /* 5 */
    NODO_SUMA,
    NODO_RESTA,
    NODO_POTENCIA,
    NODO_MULTIPLICACION,
    NODO_DIVISION, /* 10 */
    NODO_MODULO,
    NODO_MAYOR_QUE,
    NODO_MAYOR_IGUAL,
    NODO_MENOR_QUE,
    NODO_MENOR_IGUAL, /* 15 */
    NODO_IGUALDAD,
    NODO_DESIGUALDAD,
    NODO_Y,
    NODO_O,
    NODO_NO, /* 20 */
    NODO_IDENTIFICADOR,
    NODO_BLOQUE,
    NODO_ASIGNACION,
    NODO_SI,
    NODO_ELEGIR, /* 25 */
    NODO_CASO,
    NODO_DEFECTO,
    NODO_CASOS,
    NODO_MIENTRAS,
    NODO_REPETIR, /* 30 */
    NODO_DESDE,
    NODO_FUNCION_PARAMETROS,
    NODO_FUNCION_ARGUMENTOS,
    NODO_FUNCION_LLAMADA,
    NODO_FUNCION_USUARIO, /* 35 */
    NODO_RETORNO,
    NODO_CONCATENAR,
    NODO_LISTA,
    NODO_LISTA_ASIGNAR_ELEMENTO,
    NODO_LISTA_AGREGAR_ELEMENTO, /* 40 */
    NODO_LISTA_OBTENER_ELEMENTO,
    NODO_DICCIONARIO,
    NODO_DICC_AGREGAR_ELEMENTO,
    NODO_DICC_ELEMENTO,
    NODO_ATRIBUTO, /* 45 */
    NODO_GLOBAL,
    NODO_REGEX,
    NODO_VAR_ARGS,
    NODO_LOAD_VAR_ARGS,
    NODO_RANGO, /* 50 */
    NODO_ROMPER,
    NODO_CONTINUAR,
    NODO_IR,
    NODO_ETIQUETA,
} nodo_tipo;

/** \brief Tipos de dato */
typedef enum {
    VALOR_NULO,
    VALOR_LOGICO,
    VALOR_NUMERICO,
    VALOR_CADENA
} nodo_tipo_valor;

#define AST_COMUN                                                              \
    nodo_tipo tipo;                                                            \
    int nlin;                                                                  \
    int ncol;

/** \brief Valores del dato */
typedef struct {
    nodo_tipo_valor tipo;
    bool esconst;
    union val {
        bool logico;
        double numerico;
        char *cadena;
    } val;
} nodo_valor;

/** \brief Nodos en arbol abstacto de sintaxis (Abstract Syntax Tree).
 *
 * Todos los nodos son inicializados con un tipo de nodo */
typedef struct ast {
    AST_COMUN
    nodo_valor *valor;
    struct ast *izq;
    struct ast *der;
} ast;

/** \brief Estado del analizador lexico */
typedef struct lex_state {
    int insert;
} lex_state;

/** \brief Tipo de dato que se envia al analizador lexico */
typedef union YYSTYPE {
    int token;
    ast *node;
} YYSTYPE;

/** \brief Nodo para representar un ast SI (if).
 *
 * si (cond) [stmts] sino [stmts] fin */
typedef struct {
    AST_COMUN
    struct ast *cond;
    struct ast *entonces;
    struct ast *_sino;
} nodo_si;

/** \brief Nodo para representar un ast RANGO (range).
 *
 * para id en (ini, fin, inc) [stmts] fin */
typedef struct {
    AST_COMUN
    struct ast *id;
    struct ast *ini;
    struct ast *fin;
    struct ast *inc;
    struct ast *stmts;
} nodo_rango;

/** \brief Nodo para representar una fun.
 *
 * fun [nombre] (params) stmts fin */
typedef struct {
    AST_COMUN
    struct ast *nombre;
    struct ast *params;
    struct ast *stmts;
} nodo_funcion;

/** \brief Nodo para el elemento de una lista */
typedef struct {
    AST_COMUN
    struct ast *exp;
    struct ast *id;
    struct ast *pos;
} nodo_lista_elem;

/** \brief Nodo para el elemento de un diccionario */
typedef struct {
    AST_COMUN
    struct ast *exp;
    struct ast *id;
    struct ast *llave;
} nodo_dicc_elem;

ast *latA_nodo(nodo_tipo tipo, ast *l, ast *r, int nlin, int ncol);
ast *latA_var(const char *s, int nlin, int ncol, bool esconst);
ast *latA_logico(int b, int nlin, int ncol);
ast *latA_nulo(void *nulo, int nlin, int ncol);
ast *latA_numerico(double d, int nlin, int ncol);
ast *latA_cadena(const char *s, int nlin, int ncol);
ast *latA_literal(const char *s, int nlin, int ncol);
ast *latA_operador(nodo_tipo nt, ast *l, ast *r, int nlin, int ncol);
ast *latA_asign(ast *val, ast *sim);
ast *latA_asign_le(ast *s, ast *v, ast *pos);
ast *latA_si(ast *cond, ast *th, ast *el);
ast *latA_mientras(ast *cond, ast *stmts);
ast *latA_hacer(ast *cond, ast *stmts);
ast *latA_desde(ast *dec, ast *cond, ast *inc, ast *stmts);
ast *latA_para(ast *identificador, ast *inicio, ast *fin, ast *incremento, ast *sentencias);
ast *latA_funcion(ast *nombre, ast *params, ast *stmts, int nlin, int ncol);
ast *latA_analizar_exp(char *expr, int *status);
ast *latA_analizar_arch(char *ruta, int *status);

void latA_destruir(ast *a);
#endif /*_LATINO_AST_H_*/
