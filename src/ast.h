#ifndef _AST_H_
#define _AST_H_

#include <stdbool.h>
#include "vm.h"

/* tipos de dato */
typedef enum {
  VALUE_NULL,
  VALUE_BOOL,
  VALUE_INT,
  VALUE_CHAR,
  VALUE_DOUBLE,
  VALUE_STRING
} ast_value_type;

/* valores de dato */
typedef struct {
  ast_value_type t;
  bool cst; // constant
  int line_num;
  int column_num;
  union val {
    int b;
    long i;
    double d;
    char c;
    char *s;
    void *f;
  } v;
} ast_value;

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
} ast_node_type;

/* nodos en arbol abstacto de sintaxis (abstract syntax tree) */
/* todos los nodos son inicializados con un tipo de nodo*/
typedef struct ast {
  ast_node_type node_type;
  ast_value *value;
  struct ast *l;
  struct ast *r;
} ast;

typedef struct lex_state { int insert; } lex_state;

typedef union YYSTYPE {
  int token;
  ast *node;
} YYSTYPE;

typedef struct {
  ast_node_type node_type;
  struct ast *cond; /* condition */
  struct ast *th;   /* instrucciones si la condicion es verdadera (then) */
  struct ast *el;   /* instrucciones si la condicion es falsa (else) */
} ast_node_if;

/* metodos para construir AST */
ast *ast_new_node(ast_node_type node_type, ast *l, ast *r);
ast *ast_new_identifier(char *s);
ast *ast_new_constant(char *s, int line_num, int column_num);
ast *ast_new_assignment(ast *s, ast *v);
ast *ast_new_integer(long i);
ast *ast_new_decimal(double d);
ast *ast_new_char(char *c, size_t l);
ast *ast_new_string(const char *);
ast *ast_new_node_if(ast *cond, ast *th, ast *el);
ast *ast_new_node_while(ast *cond, ast *stmts);
ast *ast_new_node_do(ast *cond, ast *stmts);
ast *ast_new_node_for(ast *dec, ast *cond, ast *inc, ast *stmts);

/* define una funcion */
ast *ast_new_node_function(ast *name, ast *syms, ast *stmts);
void ast_tree_free(ast *a);

/*VM*/
lat_object *ast_parse_tree(lat_vm *vm, ast *tree);
int ast_parse_node(lat_vm *vm, ast *node, lat_bytecode *bcode, int i);

#endif /*_AST_H_*/
