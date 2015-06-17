/*
 * This file contains various definitions of structures that are used by Latino
 */

#include "latino.h"

/* data types */
typedef enum {
    VALUE_NULL = 0,
    VALUE_BOOL = 1,
    VALUE_INT = 2,
    VALUE_CHAR = 3,
    VALUE_DOUBLE = 4,
    VALUE_STRING = 5
} lat_value_type;

/* string */
typedef unsigned char lat_string;

/* values for data */
typedef struct {
    lat_value_type t;
    union {
        int b;
        int i;
        double d;
        char c;
        lat_string *s;
    } v;
} lat_value;

typedef enum {
    B_sqrt = 0,
    B_exp   = 1,
    B_log   = 2 ,
    B_print = 3
} bifs;

/* node types in the abstract syntax tree */
typedef enum {
    NODE_ADD = 0,
    NODE_SUB = 1,
    NODE_MULT = 2,
    NODE_DIV = 3,
    NODE_MOD = 4,
    NODE_ASSIGMENT = 5,
    NODE_UNARY_MINUS = 6,
    NODE_EQ = 7,
    NODE_NEQ = 8,
    NODE_GT = 9,
    NODE_LT = 10,
    NODE_GE = 11,
    NODE_LE = 12,
    NODE_BLOCK = 13,
    NODE_IF = 14,
    NODE_WHILE = 15,
    NODE_DO = 16,
    NODE_SYMBOL = 17,
    NODE_LIST_SYMBOLS = 18,
    NODE_BUILTIN_FUNCTION = 19,
    NODE_USER_FUNCTION = 20,
    NODE_RETURN = 21,
    NODE_INT = 22,
    NODE_DECIMAL = 23,
    NODE_STRING = 24,
    NODE_CHAR = 25,
    NODE_BOOLEAN = 26,
    NODE_AND = 27,
    NODE_OR = 28,
    NODE_NEG = 29,
    NODE_SWITCH  = 30,
    NODE_CASE = 31,
    NODE_DEFAULT = 32,
    NODE_CASES = 33,
    NODE_FROM = 34
} node_type;


/* nodes in the abstract syntax tree */
/* all have common initial nodetype */
typedef struct ast {
    node_type nodetype;
    struct ast *l;
    struct ast *r;
} ast;

/* built-in function */
typedef struct {
    node_type nodetype;
    struct ast *l;
    bifs functype;
} fncall ;

/* symbol table */
typedef struct {
    char *name; /* a variable name */
    lat_value *value; /* value's variable*/
    struct ast *func; /* stmt for the function */
    struct symlist *syms; /* list of dummy args */
} symbol;

/* simple symtab of fixed size */
#define NHASH 9997
symbol symtab[NHASH];

/* list of symbols, for an argument list */
typedef struct symlist {
    symbol *sym;
    struct symlist *next;
} symlist;

typedef struct {
    node_type nodetype;
    struct ast *l;
    symbol *s;
} ufncall ;

typedef struct {
    node_type nodetype;
    struct ast *cond;   /* condition */
    struct ast *tl; /* then branch or do list */
    struct ast *el; /* else branch */
} flow ;

typedef struct {
    node_type nodetype;
    struct ast *begin;
    struct ast *end;
    struct ast *stmts;
    struct ast *step;
} node_for ;

/* node values */
typedef struct {
    node_type nodetype;
    lat_value *value;
} node;

/* symbol reference */
typedef struct {
    node_type nodetype;
    symbol *s;
} symref ;

/* symbol assignment */
typedef struct {
    node_type nodetype;
    symbol *s;
    struct ast *v;
} symasgn;

/* build AST */
ast *newast(node_type nodetype, ast *l, ast *r);
ast *newfunc(int functype, ast *l);
ast *newcall(symbol *s, ast *l);
ast *newref(symbol *s);
ast *newasgn(symbol *s, ast *v);
ast *newnum(double d);
ast *newint(int i);
ast *newstr(lat_string *, size_t);
ast *newflow(node_type nodetype, ast *cond, ast *tl, ast *tr);
ast *newfor(node_type nodetype, ast *begin, ast *end, ast *stmts, ast *step);

static double callbuiltin(fncall *);
static lat_value *calluser(ufncall *);

symlist *newsymlist(symbol *sym, symlist *next);
void symlistfree(symlist *sl);
symbol *lookup(char *, lat_value *);

/* define a function */
void dodef(symbol *name, symlist *syms, ast *stmts);

/* delete and free an AST */
void treefree(ast *);

/* evaluate an AST */
lat_value *eval(ast *);
