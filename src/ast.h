#ifndef _AST_H_
#define _AST_H_

#include <stdbool.h>
#include "vm.h"

/* tipos de dato */
typedef enum {
  VALOR_NULO,
  VALOR_LOGICO,
  VALOR_ENTERO,
  VALOR_CARACTER,
  VALOR_DECIMAL,
  VALOR_CADENA
} nodo_tipo_valor;

/* valores de dato */
typedef struct {
  nodo_tipo_valor t;
  bool es_constante; // constante
  int num_linea;
  int num_columna;
  union val {
    int b;
    long i;
    double d;
    char c;
    char *s;
    void *f;
  } v;
} nodo_valor;

/* tipos de nodos en arbol abstracto de sintaxis (abstract syntax tree) */
typedef enum {
  NODE_ADD,
  NODE_SUB,
  NODE_MULT,
  NODE_DIV,
  NODE_MOD,
  NODE_ASSIGMENT,
  NODE_UNARY_MINUS,
  NODE_EQ,
  NODE_NEQ,
  NODE_GT,
  NODE_LT,
  NODE_GE,
  NODE_LE,
  NODE_BLOCK,
  NODE_IF,
  NODE_WHILE,
  NODE_DO,
  NODE_SYMBOL,
  NODE_PARAM_LIST,
  NODE_FUNC_ARGS,
  NODE_CALL_FUNCTION,
  NODE_USER_FUNCTION,
  NODE_RETURN,
  NODE_INT,
  NODE_DECIMAL,
  NODE_STRING,
  NODE_CHAR,
  NODE_BOOLEAN,
  NODE_AND,
  NODE_OR,
  NODE_NEG,
  NODE_SWITCH,
  NODE_CASE,
  NODE_DEFAULT,
  NODE_CASES,
  NODE_FROM,
  NODE_LIST,
  NODE_LIST_SET_ITEM,
  NODE_LIST_GET_ITEM,
  NODE_INC,
  NODE_DEC,
  NODE_DICT,
  NODE_DICT_ITEMS,
  NODE_DICT_ITEM,
  NODE_GET_DICT_ITEM
} nodo_tipo;

/* nodos en arbol abstacto de sintaxis (abstract syntax tree) */
/* todos los nodos son inicializados con un tipo de nodo*/
typedef struct ast {
  nodo_tipo node_type;
  nodo_valor *value;
  struct ast *l;
  struct ast *r;
} ast;

typedef struct lex_state { int insert; } lex_state;

typedef union YYSTYPE {
  int token;
  ast *node;
} YYSTYPE;

typedef struct {
  nodo_tipo node_type;
  struct ast *cond; /* condicion */
  struct ast *th;   /* instrucciones si la condicion es verdadera (then) */
  struct ast *el;   /* instrucciones si la condicion es falsa (else) */
} nodo_si;

/* metodos para construir AST */
ast *nodo_nuevo(nodo_tipo node_type, ast *l, ast *r);
ast *nodo_nuevo_identificador(char *s);
ast *nodo_nuevo_constante(char *s, int num_linea, int num_columna);
ast *nodo_nuevo_asignacion(ast *s, ast *v);
ast *nodo_nuevo_entero(long i);
ast *nodo_nuevo_decimal(double d);
ast *nodo_nuevo_caracter(char *c, size_t l);
ast *nodo_nuevo_cadena(const char *);
ast *nodo_nuevo_si(ast *cond, ast *th, ast *el);
ast *nodo_nuevo_mientras(ast *cond, ast *stmts);
ast *nodo_nuevo_hacer(ast *cond, ast *stmts);
ast *nodo_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts);

/* define una funcion */
ast *nodo_nuevo_function(ast *name, ast *syms, ast *stmts);
void nodo_liberar(ast *a);

/*VM*/
lat_object *nodo_analizar_arbol(lat_vm *vm, ast *tree);
int nodo_analizar(lat_vm *vm, ast *node, lat_bytecode *bcode, int i);

#endif /*_AST_H_*/
