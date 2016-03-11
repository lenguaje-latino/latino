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

/// tipos de dato
typedef enum {
  VALOR_NULO, /** < valor nulo */
  VALOR_LOGICO,
  VALOR_ENTERO,
  VALOR_LITERAL,
  VALOR_DECIMAL,
  VALOR_CADENA
} nodo_tipo_valor;

/** valores de dato */
typedef struct {
  nodo_tipo_valor t;
  bool es_constante; //para validar si es constante
  int num_linea;
  int num_columna;
  union val {
    int b;
    long i;
    double d;
    char *c;
    char *s;
    void *f;
  } v;
} nodo_valor;

/** tipos de nodos en arbol abstracto de sintaxis (abstract syntax tree) */
typedef enum {
  NODO_SUMA,
  NODO_RESTA,
  NODO_MULTIPLICACION,
  NODO_DIVISION,
  NODO_MODULO,
  NODO_ASIGNACION,
  NODO_MENOS_UNARIO,
  NODO_IGUALDAD,
  NODO_DESIGUALDAD,
  NODO_MAYOR_QUE,
  NODO_MENOR_QUE,
  NODO_MAYOR_IGUAL,
  NODO_MENOR_IGUAL,
  NODO_BLOQUE,
  NODO_SI,
  NODO_MIENTRAS,
  NODO_HACER,
  NODO_IDENTIFICADOR,
  NODO_LISTA_PARAMETROS,
  NODO_FUNCION_ARGUMENTOS,
  NODO_FUNCION_LLAMADA,
  NODO_FUNCION_USUARIO,
  NODO_RETORNO,
  NODO_ENTERO,
  NODO_DECIMAL,
  NODO_CADENA,
  NODO_LITERAL,
  NODO_LOGICO,
  NODO_Y,
  NODO_O,
  NODO_NEGACION,
  NODO_SELECCION,
  NODO_CASO,
  NODO_DEFECTO,
  NODO_CASOS,
  NODO_DESDE,
  NODO_INCREMENTO,
  NODO_DECREMENTO,
  NODO_CONCATENAR,
  NODO_LISTA,
  NODO_LISTA_ASIGNAR_ELEMENTO,
  NODO_LISTA_OBTENER_ELEMENTO,
  NODO_DICCIONARIO,
  NODO_DICCIONARIO_ELEMENTOS,
  NODO_DICCIONARIO_ELEMENTO,
  NODO_DICCIONARIO_OBTENER_ELEMENTO
} nodo_tipo;

/// nodos en arbol abstacto de sintaxis (abstract syntax tree)
/** todos los nodos son inicializados con un tipo de nodo */
typedef struct ast {
  nodo_tipo tipo;
  nodo_valor *valor;
  struct ast *l;
  struct ast *r;
} ast;

typedef struct lex_state { int insert; } lex_state;

typedef union YYSTYPE {
  int token;
  ast *node;
} YYSTYPE;

/// nodo para representar un ast si (if)
/** */
typedef struct {
  nodo_tipo tipo;
  struct ast *cond; /** < condicion */
  struct ast *th;   /** < instrucciones si la condicion es verdadera (then) */
  struct ast *el;   /** < instrucciones si la condicion es falsa (else) */
} nodo_si;

typedef struct {
  nodo_tipo tipo;
  struct ast *exp;  /* expresion */
  struct ast *id;   /* identificador */
  struct ast *pos;  /* posicion de la lista */
} nodo_lista_elem;

/* metodos para construir arbolo AST */
ast *nodo_nuevo(nodo_tipo tipo, ast *l, ast *r);
ast *nodo_nuevo_identificador(const char *s);
ast *nodo_nuevo_constante(char *s, int num_linea, int num_columna);
ast *nodo_nuevo_operador(nodo_tipo nt, ast *l, ast *r);
ast *nodo_nuevo_asignacion(ast *s, ast *v);
ast *nodo_nuevo_asignacion_lista(ast *s, ast *v, ast *pos);
ast *nodo_nuevo_logico(int b);
ast *nodo_nuevo_entero(long i);
ast *nodo_nuevo_decimal(double d);
ast *nodo_nuevo_literal(char *c);
ast *nodo_nuevo_cadena(const char *);
ast *nodo_nuevo_si(ast *cond, ast *th, ast *el);
ast *nodo_nuevo_mientras(ast *cond, ast *stmts);
ast *nodo_nuevo_hacer(ast *cond, ast *stmts);
ast *nodo_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts);

/* define una funcion */
ast *nodo_nuevo_funcion(ast *name, ast *syms, ast *stmts);
void nodo_liberar(ast *a);

/*VM*/
lat_objeto *nodo_analizar_arbol(lat_vm *vm, ast *tree);
int nodo_analizar(lat_vm *vm, ast *node, lat_bytecode *bcode, int i);

#endif /*_AST_H_*/
