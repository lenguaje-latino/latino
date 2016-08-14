/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

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
#ifndef _AST_H_
#define _AST_H_

#include <stdbool.h>
#include "vm.h"

/** \file ast.h
*
* Contiene las estructuras y metodos necesarios para el manejo del analizador lexico sintactico
*
*/

/** Indica que el analizador sintactico (bison) no debe emitir errores **/
extern int analisis_silencioso;

#define error(M, ...)                           \
  {                                             \
    fprintf(stderr, M "\n", ##__VA_ARGS__);     \
  }

/** Interface con flex */
typedef struct YYLTYPE
{
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;

/** Establece que se definio una interface con Flex */
#define YYLTYPE_IS_DECLARED 1

/** No se requiere cabecera unistd.h */
#define YY_NO_UNISTD_H 1

/** \brief Tipos de dato */
typedef enum
{
    VALOR_NULO,    /**< Valor nulo */
    VALOR_LOGICO,  /**< Valor logico */
    VALOR_ENTERO,  /**< Valor entero */
    VALOR_LITERAL, /**< Valor literal */
    VALOR_NUMERICO, /**< Valor NUMERICO */
    VALOR_CADENA   /**< Valor cadena */
} tipo_valor;

/** \brief Valores del dato */
typedef struct
{
    tipo_valor t; /**< Nodo tipo valor */
    bool es_constante; /**< Para validar si es constante */
    int logico;    /**< Logico */
    long entero;   /**< Entero */
    double numerico; /**< NUMERICO */
    char* cadena;  /**< Cadena o literal */
} nodo_valor;

/** \brief Tipos de nodos en arbol abstracto de sintaxis (abstract syntax tree) */

typedef enum
{
    NODO_NULO,                   /**< Nodo Nulo para indicar que no se creo un  nodo */
    NODO_ASIGNACION,             /**< Nodo asignacion (variable = valor) */
    NODO_OPERADOR,               /**< Nodo operador (+ - * / % < <= > >= == != && ||) */
    NODO_IDENTIFICADOR,          /**< Nodo identificador */
    NODO_VALOR,                  /**< Nodo valor (logico, entero, NUMERICO, cadena, literal) */
    NODO_BLOQUE,                 /**< Nodo bloque */
    NODO_SI,                     /**< Nodo si */
    NODO_ELEGIR,
    NODO_CASO,
    NODO_CASOS,
    NODO_DEFECTO,
    NODO_MIENTRAS,               /**< Nodo mientras */
    NODO_REPETIR,                /**< Nodo repetir */
    NODO_POR,                    /**< Nodo por cada */
    NODO_FUNCION_PARAMETROS,     /**< Nodo parametros (suma(a, b))*/
    NODO_FUNCION_ARGUMENTOS,     /**< Nodo argumentos de una funcion (funcion suma(1, b)) */
    NODO_FUNCION_LLAMADA,        /**< Nodo llamada a una funcion (suma(2,3)) */
    NODO_FUNCION_USUARIO,        /**< Nodo definicion de una funcion de usuario*/
    NODO_RETORNO,                /**< Nodo retorno */
    NODO_ROMPER,                 /**< Nodo romper */
    NODO_CONTINUAR,              /**< Nodo continuar */
    NODO_LISTA,                  /**< Nodo lista nueva */
    NODO_LISTA_ASIGNAR_ELEMENTO, /**< Nodo asignar un nuevo valor a un elemento de la lista (lista[0] = 10)*/
    NODO_LISTA_AGREGAR_ELEMENTO, /**< Nodo agregar elemento a una lista (1,2,3,X)*/
    NODO_LISTA_OBTENER_ELEMENTO, /**< Nodo obtener un elemento de una lista (num = lista[0])*/
    NODO_DICCIONARIO,            /**< Nodo diccionario nuevo */
    NODO_DICC_ASIGNAR_ELEMENTO,  /**< Nodo un nuevo valor a un elemento del diccionario (dic["uno"] = valor)*/
    NODO_DICC_AGREGAR_ELEMENTO,  /**< Nodo agregar un elemento al diccionario {"uno":1, "dos":2, "tres":3, "xxx": n} */
    NODO_DICC_OBTENER_ELEMENTO,  /**< Nodo obtener un elemento del diccionario (valor = dic["uno"]) */
    NODO_DICC_ELEMENTO,          /**< Nodo par de llave valor del diccionario (key : value) */
    NODO_INCLUIR                 /**< Nodo para incluir codigo de otro archivo */
} nodo_tipo;

/** \brief datos comunes para nodos ast*/
#define ast_comun int tipo; \
    int num_linea; \
    int num_columna; \

/** \brief Nodos en arbol abstacto de sintaxis (Abstract Syntax Tree).
  *
  * Todos los nodos son inicializados con un tipo de nodo */
typedef struct ast
{
    ast_comun
    struct ast* izquierdo;     /**< Nodo izquierdo */
    struct ast* derecho;     /**< Nodo derecho */
} ast;

/** \brief Estado del analizador lexico */
typedef struct lex_state
{
    int insert;
} lex_state;

/** \brief Tipo de dato que se envia al analizador lexico */
typedef union YYSTYPE
{
    int token;
    ast* nodo;
} YYSTYPE;

typedef struct
{
    ast_comun
    char* operador;         /**< operador (+ - * / %)  */
    struct ast* izquierdo;  /**< Nodo izquierdo */
    struct ast* derecho;    /**< Nodo derecho */
} ast_op;

typedef struct
{
    ast_comun
    nodo_valor* valor;  /** Valor del nodo (entero, NUMERICO, cadena, literal) */
} ast_valor;

/** \brief nodo para representar un ast SI (if).
  *
  * si (condicion)
  *     [sentencias]
  * sino
  *     [sentencias]
  * fin
  */
typedef struct
{
    ast_comun
    struct ast* condicion; /**< Condicion */
    struct ast* entonces;  /**< Instrucciones que se ejecutan si la condicion es verdadera */
    struct ast* sino;      /**< Instrucciones que se ejecutan si la condicion es falsa */
} ast_si;

typedef struct
{
    ast_comun
    struct ast* identificador;  /**< Nodo identificador */
    struct ast* iterable;       /**< Nodo iterable */
    struct ast* sentencias;     /**< Nodo lista de instrucciones */
} ast_por;

/** \brief nodo para representar una funcion.
  *
  * funcion nombre_fun ([param1, param2, ... ])
  *     [sentencias]
  * fin
  */
typedef struct
{
    ast_comun
    struct ast* nombre;
    struct ast* parametros;
    struct ast* sentencias;
} ast_funcion;

/** \brief Nodo para el elemento de una lista */
typedef struct
{
    ast_comun
    struct ast* expresion;      /**< Expresion */
    struct ast* identificador;  /**< Identificador */
    struct ast* posicion;       /**< Posicion de la lista */
} ast_lista_elem;

/** \brief Nodo para el elemento de un diccionario */
typedef struct
{
    ast_comun
    struct ast* expresion;      /**< Expresion */
    struct ast* identificador;  /**< Identificador */
    struct ast* llave;          /**< Llave del diccionario */
} ast_dicc_elem;

/** \brief Nuevo nodo generico para el AST
  *
  * \param tipo: Tipo de nodo
  * \param izquierdo: Nodo izquierdo
  * \param derecho: Nodo derecho
  * \num_linea: Numero de line
  * \num_columna: Numero de columna
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo(nodo_tipo tipoNodo, ast* izquierdo, ast* derecho, int num_linea, int num_columna);

/** \brief Nuevo nodo operador
  *
  * \param op: Operador (+ - * / %)
  * \param izquierdo: Nodo izquierdo
  * \param derecho: Nodo derecho
  * \num_linea: Numero de line
  * \num_columna: Numero de columna
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_op(char* operador, ast* izquierdo, ast* derecho, int num_linea, int num_columna);

/** Nuevo nodo tipo Identificador (var)
  *
  * \param identificador: nombre del identificador
  * \num_linea: Numero de line
  * \num_columna: Numero de columna
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_identificador(char* identificador, int num_linea, int num_columna);

/** Nuevo nodo tipo Constante (PI)
  *
  * \param identificador: nombre del identificador constante
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_constante(char* identificador, int num_linea, int num_columna);

/** Nuevo nodo tipo Logico (verdadero/falso)
  *
  * \param logico: Nodo valor (0 o 1)
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_logico(int logico, int num_linea, int num_columna);

/** Nuevo nodo tipo Entero (1234)
  *
  * \param logico: Nodo valor
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_entero(long entero, int num_linea, int num_columna);

/** Nuevo nodo tipo numerico (1.25)
  *
  * \param numerico: Nodo valor
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_numerico(double numerico, int num_linea, int num_columna);

/** Nuevo nodo tipo Literal ('Esto es una "literal"')
  *
  * \param literal: Nodo valor
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_literal(char* literal, int num_linea, int num_columna);

/** Nuevo nodo tipo Cadena ("Esto es una 'cadena'")
  *
  * \param cadena: Nodo valor
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_cadena(char* cadena, int num_linea, int num_columna);

/** Nuevo nodo tipo Asignacion (var = "hola latino")
  *
  * \param identificador: Nodo identificador
  * \param expresion: Nodo valor
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_asignacion(ast* identificador, ast* expresion, int num_linea, int num_columna);

/** Nuevo nodo tipo Asignacion Lista (lista[pos] = exp)
  *
  * \param identificador: Nodo identificador de la lista
  * \param expresion: Nodo valor o expresion
  * \param posicion: Nodo posicion en la lista
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_asignacion_lista_elem(ast* identificador, ast* expresion, ast* posicion, int num_linea, int num_columna);

/** Nuevo nodo tipo Asignacion Diccionario (dicc[llave] = exp)
  *
  * \param identificador: Nodo identificador del diccionario
  * \param expresion: Nodo valor o expresion
  * \param llave: Nodo llave del diccionario
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_asignacion_dicc_elem(ast* identificador, ast* expresion, ast* llave, int num_linea, int num_columna);

/** Nuevo nodo tipo si (if)
  *
  * \param condicion: Nodo condicion ( a > b && a > c )
  * \param entonces: Nodo lista de sentencias (en caso de ser verdadera la condicion)
  * \param sino: Nodo lista de sentencias (en caso de ser falsa la condicion)
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_si(ast* condicion, ast* entonces, ast* sino, int num_linea, int num_columna);

/** Nuevo nodo tipo mientras (while)
  *
  * \param condicion: Nodo condicion ( a > b && a > c )
  * \param sentencias: Nodo lista de sentencias (mientras sea verdadera la condicion)
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_mientras(ast* condicion, ast* sentencias, int num_linea, int num_columna);

/** Nuevo nodo tipo repetir (repit)
  *
  * \param condicion: Nodo condicion ( a > b && a > c )
  * \param sentencias: Nodo lista de sentencias (mientras sea verdadera la condicion)
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_repetir(ast* condicion, ast* sentencias, int num_linea, int num_columna);

/** Nuevo nodo tipo por cada (for each)
  *
  * \param identificador: Nodo identificador
  * \param iterable: Nodo lista u objeto iterable
  * \param sentencias: Nodo lista de instrucciones a ejecutar
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_por(ast* identificador, ast* iterable, ast* sentencias, int num_linea, int num_columna);

/** Nuevo nodo tipo funcion
  *
  * \param identificador: Nodo nombre de la funcion
  * \param parametros: Nodo parametros de la funcion
  * \param sentencias: Nodo lista de sentencias de la funcion
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_funcion(ast* nombre, ast* parametros, ast* sentencias, int num_linea, int num_columna);

/** Nuevo nodo que incluye un modulo
  *
  * \param ruta: Nodo nombre del modulo o ruta del modulo
  * \param num_linea: Numero de linea donde se declaro la constante
  * \param num_columna: Numero de columna donde se declaro la constante
  * \return ast: Un nodo AST
  *
  */
ast* nodo_nuevo_incluir(ast* ruta, int num_linea, int num_columna);

/** Libera la memoria creada dinamicamente
  *
  * \param nodo: Nodo AST
  *
  */
void nodo_liberar(ast* nodo);

/** Muestra el nodo en un formato amigable
  *
  * \param nodo: Nodo AST
  *
  */
void nodo_mostrar(ast* a, int ident, int nivel);

/** Analiza una cadena como expresion
  *
  * \param nodo: Nodo AST que se crea al analizar la expresion
  * \param expresion: Cadena a analizar
  * \return int: Codigo de error
  *
  */
int nodo_analizar_expresion(ast** nodo, char* expresion);

/** Analiza un archivo
  *
  * \param nodo: Nodo AST que se crea al analizar archivo
  * \param ruta: Ruta del archivo a analizar
  * \return int: Codigo de error
  *
  */
int nodo_analizar_archivo(ast** nodo, char* archivo);

lat_objeto *nodo_analizar_arbol(lat_vm *vm, ast *tree);
#endif /*_AST_H_*/
