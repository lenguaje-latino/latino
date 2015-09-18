#ifndef _AST_H_
#define _AST_H_

#include "latino.h"

/* data types */
typedef enum {
    VALUE_NULL, /*0*/
    VALUE_BOOL,
    VALUE_INT,
    VALUE_CHAR,
    VALUE_DOUBLE,
    VALUE_STRING, /*5*/
	VALUE_FUN
} latValueType;

/* string */
typedef struct latString{
	const char *ptr;
	size_t len;
}latString;


/* values for data */
typedef struct {
    latValueType t;
    union {
        int b;
        long i;
        double d;
        char c;
        const char *s;
		void *f;
    } v;
} latValue;

typedef enum {
    B_print,
    B_exp,
    B_log,
    B_sqrt
} bifs;

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
    NODE_LIST_SYMBOLS,
    NODE_BUILTIN_FUNCTION,
    NODE_USER_FUNCTION, /*20*/
    NODE_RETURN,
    NODE_INT,
    NODE_DECIMAL,
    NODE_STRING,
    NODE_CHAR, /*25*/
    NODE_BOOLEAN,
    NODE_AND,
    NODE_OR,
    NODE_NEG,
    NODE_SWITCH, /*30*/
    NODE_CASE,
    NODE_DEFAULT,
    NODE_CASES,
    NODE_FROM
} nodeType;

/* nodes in the abstract syntax tree */
/* all have common initial nodetype */
typedef struct ast {
    nodeType nodetype;
    struct ast *l;
    struct ast *r;
} ast;

/* built-in function */
typedef struct {
    nodeType nodetype;
    struct ast *l;
    bifs functype;
} fnCall ;

/* symbol table */
typedef struct symbol{
    char *name; /* a variable name */
    latValue *value; /* value's variable*/
    struct ast *func; /* stmt for the function */
    struct symList *syms; /* list of dummy args */
} symbol;

/* simple symTab of fixed size */
#define NHASH 32767
struct symbol symTab[NHASH];

/* list of symbols, for an argument list */
typedef struct symList {
    struct symbol *sym;
    struct symList *next;
} symList;

typedef struct {
    nodeType nodetype;
    struct ast *l;
    struct symbol *s;
} ufnCall ;

typedef struct {
    nodeType nodetype;
    struct ast *cond;   /* condition */
    struct ast *tl; /* then branch or do list */
    struct ast *el; /* else branch */
} flow ;

typedef struct {
    nodeType nodetype;
    struct ast *begin;
    struct ast *end;
    struct ast *stmts;
    struct ast *step;
} nodeFor ;

/* node values */
typedef struct {
    nodeType nodetype;
    latValue *value;
} node;

/* symbol reference */
typedef struct {
    nodeType nodetype;
    struct symbol *s;
} symref ;

/* symbol assignment */
typedef struct {
    nodeType nodetype;
    struct symbol *s;
    struct ast *v;
} symAsgn;

/* build AST */
ast *newAst(nodeType nodetype, ast *l, ast *r);
ast *newFunc(int functype, ast *l);
ast *newCall(struct symbol *s, ast *l);
ast *newRef(struct symbol *s);
ast *newAsgn(struct symbol *s, ast *v);
ast *newNum(double d);
ast *newInt(long i);
ast *newStr(const char *, size_t);
ast *newIf(nodeType nodetype, ast *cond, ast *tl, ast *tr);
ast *newWhile(nodeType nodetype, ast *cond, ast *tl, ast *tr);
ast *newDo(nodeType nodetype, ast *cond, ast *tl, ast *tr);
ast *newFor(nodeType nodetype, ast *begin, ast *end, ast *stmts, ast *step);

double callBuiltin(fnCall *);
latValue *callUser(ufnCall *);

symList *newSymList(struct symbol *sym, symList *next);
void symListFree(symList *sl);
struct symbol *lookup(char *, latValue *);

/* define a function */
void doDef(struct symbol *name, symList *syms, ast *stmts);

/* delete and free an AST */
void treeFree(ast *);

/* evaluate an AST */
latValue *eval(ast *);

#endif /*_AST_H_*/