#ifndef _AST_H_
#define _AST_H_

#include "latino.h"
#include "vm.h"

/* data types */
typedef enum {
    VALUE_NULL, /*0*/
    VALUE_BOOL,
    VALUE_INT,
    VALUE_CHAR,
    VALUE_DOUBLE,
    VALUE_STRING /*5*/
} latValueType;

/* values for data */
typedef struct {
    latValueType t;
    union val {
        int b;
        long i;
        double d;
        char c;
        char *s;
		void *f;
    } v;
} latValue;

/* node types in the abstract syntax tree */
typedef enum {
    NODE_ADD, /*0*/
    NODE_SUB,
    NODE_MULT,
    NODE_DIV,
    NODE_MOD,
    NODE_ASSIGMENT, /*5*/
    NODE_UNARY_MINUS,
    NODE_EQ,
    NODE_NEQ,
    NODE_GT,
    NODE_LT, /*10*/
    NODE_GE,
    NODE_LE,
    NODE_BLOCK,
    NODE_IF,
    NODE_WHILE, /*15*/
    NODE_DO,
    NODE_SYMBOL,
    NODE_PARAM_LIST,
	NODE_FUNC_ARGS,
    NODE_CALL_FUNCTION, /*20*/
    NODE_USER_FUNCTION,
    NODE_RETURN,
    NODE_INT,
    NODE_DECIMAL,
    NODE_STRING, /*25*/
    NODE_CHAR,
    NODE_BOOLEAN,
    NODE_AND,
    NODE_OR,
	NODE_NEG, /*30*/
    NODE_SWITCH,
    NODE_CASE,
    NODE_DEFAULT,
    NODE_CASES,
	NODE_FROM, /*35*/
	NODE_LIST,
	NODE_LIST_BODY
} nodeType;

/* nodes in the abstract syntax tree */
/* all have common initial nodetype */
typedef struct ast {
    nodeType nodetype;
    latValue *value;
    struct ast *l;
    struct ast *r;
} ast;

typedef struct lex_state{
	int insert;
}lex_state;

typedef union YYSTYPE {
	int token;
	ast *node;
} YYSTYPE;

typedef struct {
    nodeType nodetype;
    struct ast *cond;   /* condition */
    struct ast *entonces; /* then branch or do list */
    struct ast *sino; /* else branch */
} nodeIf ;

/* build AST */
ast *newAst(nodeType nodetype, ast *l, ast *r);
ast *newRef(char *s);
ast *newAsgn(ast *s, ast *v);
ast *newInt(long i);
ast *newNum(double d);
ast *newChar(char *c, size_t l);
ast *newStr(const char *, size_t);
ast *newIf(ast *cond, ast *entonces, ast *sino);
ast *newWhile(ast *cond, ast *stmts);
ast *newDo(ast *cond, ast *stmts);
ast *newFor(ast *dec, ast *cond, ast *inc, ast *stmts);

/* define a function */
ast *doDef(ast *name, ast *syms, ast *stmts);
void treeFree(ast *a);

/*VM*/
lat_object *lat_parse_tree(lat_vm *vm, ast *tree);
int lat_parse_node(lat_vm *vm, ast *node, lat_bytecode *bcode, int i);

#endif /*_AST_H_*/
