#ifndef LATINO_H
#define LATINO_H 1

#define LATINO_HUGE 1

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include "parse.h"

/*
 * global variable
 */
extern int debug;

/*
 * lex & parse
 */
extern int yylex(void);

extern void dump_row(void);
extern int get_next_char(char *b, int maxBuffer);
extern void begin_token(char*);
extern void print_error(char *s, ...);

void yyerror(char *s, ...);
/* interface to the lexer */
extern int yylineno;    /* from lexer */


/* data types */
typedef enum {
    VALUE_NULL, /*0*/
    VALUE_BOOL,
    VALUE_INT,
    VALUE_CHAR,
    VALUE_DOUBLE,
    VALUE_STRING /*5*/
} lat_value_type;

/* string */
typedef char lat_string;

/* values for data */
typedef struct {
    lat_value_type t;
    union {
        int b;
        long i;
        double d;
        char c;
        lat_string *s;
    } v;
} lat_value;

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
typedef struct symbol{
    char *name; /* a variable name */
    lat_value *value; /* value's variable*/
    struct ast *func; /* stmt for the function */
    struct symlist *syms; /* list of dummy args */
} symbol;

/* simple symtab of fixed size */
#define NHASH 32767
struct symbol symtab[NHASH];

/* list of symbols, for an argument list */
typedef struct symlist {
    struct symbol *sym;
    struct symlist *next;
} symlist;

typedef struct {
    node_type nodetype;
    struct ast *l;
    struct symbol *s;
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
    struct symbol *s;
} symref ;

/* symbol assignment */
typedef struct {
    node_type nodetype;
    struct symbol *s;
    struct ast *v;
} symasgn;

/* build AST */
ast *newast(node_type nodetype, ast *l, ast *r);
ast *newfunc(int functype, ast *l);
ast *newcall(struct symbol *s, ast *l);
ast *newref(struct symbol *s);
ast *newasgn(struct symbol *s, ast *v);
ast *newnum(double d);
ast *newint(long i);
ast *newstr(lat_string *, size_t);
ast *newflow(node_type nodetype, ast *cond, ast *tl, ast *tr);
ast *newfor(node_type nodetype, ast *begin, ast *end, ast *stmts, ast *step);

double callbuiltin(fncall *);
lat_value *calluser(ufncall *);

symlist *newsymlist(struct symbol *sym, symlist *next);
void symlistfree(symlist *sl);
struct symbol *lookup(char *, lat_value *);

/* define a function */
void dodef(struct symbol *name, symlist *syms, ast *stmts);

/* delete and free an AST */
void treefree(ast *);

/* evaluate an AST */
lat_value *eval(ast *);
void print_ast(ast *);

#endif /* LATINO_H */
