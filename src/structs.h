/*
 * This file contains various definitions of structures that are used by Latino
 */

#include "latino.h"

#ifdef LATINO_HUGE
typedef long int varinteger_T;
typedef long double vardecimal_T;
#else
typedef int varinteger_T;
typedef double vardecimal_T;
#endif

/* symbol table */
struct symbol{  /* a variable name */
    char *name;
    double value;
    struct ast *func;   /* stmt for the function */
    struct symlist *syms;   /* list of dummy args */
};

/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char*);

/* list of symbols, for an argument list */
struct symlist {
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);

enum bifs {
    B_sqrt = 1,
    B_exp,
    B_log,
    B_print
};

/* node types
 * + - * /
 * 0-7 comparison ops, bit coded 04 equal, 02 less, 01 grieta
 * M unary minus
 * L expression or statement list
 * I IF statement
 * W WHILE statement
 * N symbol ref
 * = assigment
 * S list of symbols
 * F built in function call
 * C user function call
 */

typedef enum {
    NODE_ADD,
    NODE_SUB,
    NODE_MULT,
    NODE_DIV,
    NODE_MOD,
    NODE_ASSIGMENT,
    NODE_UNARY_MINUS,
    NODE_EQUAL,
    NODE_NOT_EQUAL,
    NODE_GREATER_THAN,
    NODE_LESS_THAN,
    NODE_GREATER_THAN_EQUAL,
    NODE_LESS_THAN_EQUAL,
    NODE_EXPRESION,
    NODE_IF,
    NODE_WHILE,
    NODE_DO,
    NODE_SYMBOL,
    NODE_LIST_SYMBOLS,
    NODE_BUILTIN_FUNCTION,
    NODE_USER_FUNCTION,
    NODE_USER_FUNCTION_CALL,
    NODE_INT,
    NODE_DECIMAL,
    NODE_STRING,
    NODE_CHAR,
    NODE_BOOLEAN
} node_type;

typedef unsigned char	char_u;

typedef struct
{
    char         v_type;
    varinteger_T v_integer;
    vardecimal_T v_decimal;
    char_u       *v_string;
} node_value;

/* Values for "v_type". */
#define VAR_UNKNOWN 0
#define VAR_INTEGER 1	/* "v_integer" is used */
#define VAR_STRING  2	/* "v_string" is used */
#define VAR_FUNC    3	/* "v_string" is function name */
#define VAR_LIST    4	/* "v_list" is used */
#define VAR_DICT    5	/* "v_dict" is used */
#define VAR_DECIMAL 6	/* "v_decimal" is used */

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

struct numval {
    node_type nodetype;   /* type K */
    double number;
};

struct boolval {
    node_type nodetype;   /* type K */
    int value;
};

typedef char* lat_string;

struct strval {
    node_type nodetype;  /* type ? */
    lat_string str;
};


struct charval {
    node_type nodetype;  /* type ? */
    char c;
};

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
struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(int functype, struct ast *l);
struct ast *newcall(struct symbol *s, struct ast *l);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);
struct ast *newnum(double d);
struct ast *newstr(lat_string, size_t);
struct ast *newflow(node_type nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* define a function */
void
dodef(struct symbol *name, struct symlist *syms, struct ast *stmts);

/* evaluate an AST */
double eval(struct ast *);

