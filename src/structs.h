/*
 * This file contains various definitions of structures that are used by Latino
 */

#include "latino.h"

typedef enum{
    VALUE_NULL = 0,
    VALUE_BOOL = 1,
    VALUE_INT = 2,
    VALUE_CHAR = 3,
    VALUE_DOUBLE = 4,
    VALUE_STRING = 5
} lat_value_type;

typedef char* lat_string;

typedef struct{
    lat_value_type t;
    union{
        int b;
        int i;
        double d;
        char c;
        lat_string s;
    }v;
} lat_value;

/* symbol table */
struct symbol{  /* a variable name */
    char *name;
    lat_value *value;
    struct ast *func;   /* stmt for the function */
    struct symlist *syms;   /* list of dummy args */
};

/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char*, lat_value*);

/* list of symbols, for an argument list */
struct symlist {
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

enum bifs {
    B_sqrt = 0,
    B_exp   = 1,
    B_log   = 2 ,
    B_print = 3
};

typedef enum {
    NODE_ADD=0,
    NODE_SUB=1,
    NODE_MULT=2,
    NODE_DIV=3,
    NODE_MOD=4,
    NODE_ASSIGMENT=5,
    NODE_UNARY_MINUS=6,
    NODE_EQ=7,
    NODE_NEQ=8,
    NODE_GT=9,
    NODE_LT=10,
    NODE_GE=11,
    NODE_LE=12,
    NODE_EXPRESSION=13,
    NODE_IF=14,
    NODE_WHILE=15,
    NODE_DO=16,
    NODE_SYMBOL=17,
    NODE_LIST_SYMBOLS=18,
    NODE_BUILTIN_FUNCTION=19,
    NODE_USER_FUNCTION=20,
    NODE_USER_FUNCTION_CALL=21,
    NODE_INT=22,
    NODE_DECIMAL=23,
    NODE_STRING=24,
    NODE_CHAR=25,
    NODE_BOOLEAN=26,
    NODE_AND =27,
    NODE_OR = 28
} node_type;

/* nodes in the abstract syntax tree */
/* all have common initial nodetype */
struct ast {
    node_type nodetype;
    struct ast *l;
    struct ast *r;
};

struct fncall {     /* built-in function */
    node_type nodetype;   /* type C */
    struct ast *l;
    enum bifs functype;
};

struct ufncall {
    node_type nodetype;
    struct ast *l;
    struct symbol *s;
};

struct flow {
    node_type nodetype;   /* type I or W */
    struct ast *cond;   /* condition */
    struct ast *tl; /* then branch or do list */
    struct ast *el;
};

typedef struct{
    node_type nodetype;   /* type K */
    lat_value *value;
}node;

struct symref {
    node_type nodetype;   /* type N */
    struct symbol *s;
};

struct symasgn {
    node_type nodetype;   /* type = */
    struct symbol *s;
    struct ast *v;
};

/* build AST */
struct ast *newast(node_type nodetype, struct ast *l, struct ast *r);
/*struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);*/
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newint(int i);
struct ast *newstr(lat_string, size_t);
struct ast *newflow(node_type nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* define a function */
void
dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate an AST */
lat_value* eval(struct ast *);

