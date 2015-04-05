#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "latino.h"
#include "structs.h"

/* symbol table */
/* hash symbol */
static unsigned
symhash(char *sym) {
    unsigned int hash = 0;
    unsigned c;
    while(c = *sym++) hash = hash*9 ^ c;
    return hash;
}

static char*
strdup0(const char *s)
{
    size_t len = strlen(s);
    char *p;
    p = (char*)malloc(len+1);
    if (p) {
        strcpy(p, s);
    }
    return p;
}

struct symbol *
lookup(char* sym, lat_value *v) {
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount        = NHASH; /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) {
            if (v != NULL)
            {
                /* set value to symbol if exists */
                sp->value = v;
            }
            return sp;
        }
        if (!sp->name) { /* new entry*/
            sp->name  = strdup0(sym);
            sp->value = NULL;
            sp->func  = NULL;
            sp->syms  = NULL;
            return sp;
        }
        if (++sp >= symtab + NHASH)
            sp = symtab; /* try the next entry */
    }
    yyerror("desbordamiento de la tabla de simbolos\n");
    abort();    /* tried them all, table is full */
}

struct ast *
newast(node_type nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *
newint(int i)
{
    node *a = malloc(sizeof(node));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_INT;
    lat_value *val = malloc(sizeof(lat_value));
    val->t = VALUE_INT;
    val->v.i = i;
    a->value = val;
    return (struct ast *)a;
}

struct ast *
newnum(double d)
{
    node *a = malloc(sizeof(node));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_DECIMAL;
    lat_value *val = malloc(sizeof(lat_value));
    val->t = VALUE_DOUBLE;
    val->v.d = d;
    a->value = val;
    return (struct ast *)a;
}

struct ast *
newbool(char *b)
{
    node *a = malloc(sizeof(node));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_BOOLEAN;
    lat_value *val = malloc(sizeof(lat_value));
    val->t = VALUE_BOOL;
    char *t = "verdadero";
    int ret = strncmp(t, b, 5);
    if (ret == 0) {
        val->v.b = 1;
    } else {
        val->v.b = 0;
    }
    a->value = val;
    return (struct ast *)a;
}

static char*
strndup0(const char *s, size_t n)
{
    size_t i;
    const char *p = s;
    char *new;
    for (i=0; i<n && *p; i++,p++)
        ;
    new = (char*)malloc(i+1);
    if (new) {
        memcpy(new, s, i);
        new[i] = '\0';
    }
    return new;
}

struct ast *
newchar(lat_string c, size_t l)
{

    node *a = malloc(sizeof(node));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_CHAR;
    lat_value *val = malloc(sizeof(lat_value));
    val->t = VALUE_CHAR;
    val->v.c = c[0];
    a->value = val;
    return (struct ast *)a;
}

struct ast *
newstr(lat_string s, size_t l)
{
    node *a = malloc(sizeof(node));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_STRING;
    lat_value *val = malloc(sizeof(lat_value));
    val->t = VALUE_STRING;
    val->v.s = strndup0(s, l);
    a->value = val;
    return (struct ast *)a;
}

struct ast *
newfunc(int functype, struct ast *l)
{
    /*printf("%s\n", "newfunc");*/
    struct fncall *a = malloc(sizeof(struct fncall));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_BUILTIN_FUNCTION;
    a->l = l;
    a->functype = functype;
    return (struct ast *)a;
}

struct ast *
newcall(struct symbol *s, struct ast *l)
{
    /*printf("%s\n", "newcall");*/
    struct ufncall *a = malloc(sizeof(struct ufncall));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_USER_FUNCTION;
    a->l = l;
    a->s = s;
    return (struct ast *)a;
}

struct ast *
newref(struct symbol *s)
{
    struct symref *a = malloc(sizeof(struct symref));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_SYMBOL;
    a->s = lookup(s->name, NULL);
    return (struct ast *)a;
}

struct ast *
newasgn(struct symbol *s, struct ast *v)
{
    /*printf("%s\n", "newasgn");*/
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_ASSIGMENT;
    a->s = s;
    a->v = v;
    switch (v->nodetype) {
    case NODE_BOOLEAN:
        a->s->value = malloc(sizeof(lat_value));
        a->s->value->t   = VALUE_BOOL;
        a->s->value->v.b = ((node *)v)->value->v.b;
        lookup(s->name, a->s->value);
        break;
    case NODE_INT:
        a->s->value = malloc(sizeof(lat_value));
        a->s->value->t   = VALUE_INT;
        a->s->value->v.i = ((node *)v)->value->v.i;
        lookup(s->name, a->s->value);
        break;
    case NODE_DECIMAL:
        a->s->value = malloc(sizeof(lat_value));
        a->s->value->t   = VALUE_DOUBLE;
        a->s->value->v.d = ((node *)v)->value->v.d;
        lookup(s->name, a->s->value);
        break;
    case NODE_CHAR:
        a->s->value = malloc(sizeof(lat_value));
        a->s->value->t   = VALUE_CHAR;
        a->s->value->v.c = ((node *)v)->value->v.c;
        lookup(s->name, a->s->value);
        break;
    case NODE_STRING:
        a->s->value = malloc(sizeof(lat_value));
        a->s->value->t   = VALUE_STRING;
        a->s->value->v.s = ((node *)v)->value->v.s;
        lookup(s->name, a->s->value);
        break;
    case NODE_ADD:
    case NODE_SUB:
    case NODE_DIV:
    case NODE_MOD:
    case NODE_MULT:
    case NODE_AND:
    case NODE_OR:
    case NODE_EQ:
    case NODE_NEQ:
    case NODE_GT:
    case NODE_LT:
    case NODE_GE:
    case NODE_LE:
        a->s->value = eval(a->v);
        lookup(s->name, a->s->value);
        break;    
    default:
        printf("newasgn=%i\n", v->nodetype);
        break;
    }
    return (struct ast *)a;
}

struct ast *
newflow(node_type nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
    struct flow *a = malloc(sizeof(struct flow));
    if(!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (struct ast *)a;
}

/* free a tree of ASTs */
void
treefree(struct ast *a)
{
    switch(a->nodetype) {
    /* two subtrees */
    case NODE_ADD:
    case NODE_SUB:
    case NODE_MULT:
    case NODE_DIV:
    case NODE_MOD:
    case NODE_AND:
    case NODE_OR:
    case NODE_EQ:
    case NODE_NEQ:
    case NODE_GT:
    case NODE_LT:
    case NODE_GE:
    case NODE_LE:
    case NODE_EXPRESION:
        treefree(a->r);
        break;
    /* one subtree */
    case NODE_UNARY_MINUS:
    case NODE_USER_FUNCTION_CALL:
    case NODE_BUILTIN_FUNCTION:
        treefree(a->l);
        break;
    /* no subtree */
    case NODE_INT:
    case NODE_CHAR:
    case NODE_DECIMAL:
    case NODE_SYMBOL:
    case NODE_BOOLEAN:
        break;
    case NODE_ASSIGMENT:
        free( ((struct symasgn *)a)->v);
        break;
    /* up to three subtrees */
    case NODE_IF:
    case NODE_WHILE:
        free( ((struct flow *)a)->cond);
        if( ((struct flow *)a)->tl) treefree( ((struct flow *)a)->tl);
        if( ((struct flow *)a)->el) treefree( ((struct flow *)a)->el);
        break;
    case NODE_STRING:
        //free( ((struct symasgn *)a)->v);
        free( ((node *)a)->value->v.s);
        break;
    default:
        printf("error interno: nodo mal liberado %i\n", a->nodetype);
        break;
    }
    free(a); /* always free the node itself */
}

struct symlist *
newsymlist(struct symbol *sym, struct symlist *next)
{
    struct symlist *sl = malloc(sizeof(struct symlist));
    if(!sl) {
        yyerror("sin espacio\n");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}

/* free a list of symbols */
void
symlistfree(struct symlist *sl)
{
    struct symlist *nsl;
    while(sl) {
        nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}

static double callbuiltin(struct fncall *);
static double calluser(struct ufncall *);

static lat_string * concat (lat_string s1, lat_string s2){
    lat_string *s3 = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

static lat_string * int2str(int i){
    char s[50];
    lat_string *r = malloc(strlen(s) + 1);
    snprintf(s, 50, "%i", i);
    strcpy(r, s);
    return r;
}

static lat_string * double2str(double d){
    char s[50];
    lat_string *r = malloc(strlen(s) + 1);
    snprintf(s, 50, "%g", (float)d);
    strcpy(r, s);
    return (lat_string)r;
}

lat_value* eval(struct ast *a)
{
    double v;
    if(!a) {
        yyerror("eval es nulo\n");
        return NULL;
    }
    lat_value *val = malloc(sizeof(lat_value));
    lat_value *arg1 = malloc(sizeof(lat_value));
    lat_value *arg2 = malloc(sizeof(lat_value));
    switch(a->nodetype) {
    /* constant */
    case NODE_BOOLEAN:
    case NODE_CHAR:
    case NODE_DECIMAL:
    case NODE_INT:
    case NODE_STRING:
        val = ((node *)a)->value;
        return val;
        break;
    /* name reference */
    case NODE_SYMBOL:        
	if(((struct symref *)a)->s->value == NULL){
	    yyerror("variable sin definir");	    
	}else{
	  val = ((struct symref *)a)->s->value;
	}	
        return val;
        break;
    /* assignment */
    case NODE_ASSIGMENT:
        val = ((struct symasgn *)a)->v;
        return val;
        break;
    /* expressions */
    case NODE_ADD:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->t = VALUE_INT;
            val->v.i = arg1->v.i + arg2->v.i;
            return val;
        }
        if ((arg1->t == VALUE_DOUBLE && arg2->t == VALUE_INT) || (arg1->t == VALUE_INT && arg2->t == VALUE_DOUBLE))
        {
            val->t = VALUE_DOUBLE;
            double d1 = arg1->t == VALUE_INT ? (double)arg1->v.i : arg1->v.d;
            double d2 = arg2->t == VALUE_INT ? (double)arg2->v.i : arg2->v.d;
            val->v.d  = d1 + d2;
            return val;
        }
        /* concat with + */
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->t = VALUE_STRING;
            val->v.s = concat(arg1->v.s, arg2->v.s);
            return val;
        }
        if (arg1->t == VALUE_STRING || arg2->t == VALUE_STRING)
        {
            lat_string *ls1 = malloc(256);
            lat_string *ls2 = malloc(256);
            val->t = VALUE_STRING;
            if(arg1->t != VALUE_STRING){
                ls1 = arg1->t == VALUE_INT ? int2str(arg1->v.i) : double2str(arg1->v.d);
                val->v.s = concat(ls1, arg2->v.s);
                return val;
            }
            if(arg2->t != VALUE_STRING){
                ls2 = arg2->t == VALUE_INT ? int2str(arg2->v.i) : double2str(arg2->v.d);
                val->v.s = concat(arg1->v.s, ls2);
                return val;
            }
        }
        /* TODO: pendiente concat con boolean y char*/
        break;
    case NODE_SUB:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->t = VALUE_INT;
            val->v.i = arg1->v.i - arg2->v.i;
            return val;
        }
        if ((arg1->t == VALUE_DOUBLE && arg2->t == VALUE_INT) || (arg1->t == VALUE_INT && arg2->t == VALUE_DOUBLE))
        {
            val->t = VALUE_DOUBLE;
            double d1 = arg1->t == VALUE_INT ? (double)arg1->v.i : arg1->v.d;
            double d2 = arg2->t == VALUE_INT ? (double)arg2->v.i : arg2->v.d;
            val->v.d  = d1 - d2;
            return val;
        }
        yyerror("- tipos incompatibles");
        break;
    case NODE_MULT:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->t = VALUE_INT;
            val->v.i = arg1->v.i * arg2->v.i;
            return val;
        }
        if ((arg1->t == VALUE_DOUBLE && arg2->t == VALUE_INT) || (arg1->t == VALUE_INT && arg2->t == VALUE_DOUBLE))
        {
            val->t = VALUE_DOUBLE;
            double d1 = arg1->t == VALUE_INT ? (double)arg1->v.i : arg1->v.d;
            double d2 = arg2->t == VALUE_INT ? (double)arg2->v.i : arg2->v.d;
            val->v.d  = d1 * d2;
            return val;
        }
        yyerror("* tipos incompatibles");
        break;
    case NODE_DIV:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->t = VALUE_INT;
            if (arg2->v.i != 0){
                val->v.i = arg1->v.i / arg2->v.i;
            }else{
                yyerror("division por cero");
            }
            return val;
        }
        if ((arg1->t == VALUE_DOUBLE && arg2->t == VALUE_INT) || (arg1->t == VALUE_INT && arg2->t == VALUE_DOUBLE))
        {
            val->t = VALUE_DOUBLE;
            double d1 = arg1->t == VALUE_INT ? (double)arg1->v.i : arg1->v.d;
            double d2 = arg2->t == VALUE_INT ? (double)arg2->v.i : arg2->v.d;
            if (d2 != 0){
                val->v.d  = d1 / d2;
            }else{
                yyerror("division por cero");
            }
            return val;
        }
        yyerror("/ tipos incompatibles");
        break;
    case NODE_MOD:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->t = VALUE_INT;
            if (arg2->v.i != 0){
                val->v.i = arg1->v.i % arg2->v.i;
            }else{
                yyerror("division por cero");
            }
            return val;
        }
        yyerror("\% tipos incompatibles");
        break;
    case NODE_AND:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if(arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL){
            val->t = VALUE_BOOL;
            val->v.b = arg1->v.b && arg2->v.b;
            return val;
        }
        yyerror("&& tipos incompatible"); 
        break;
    case NODE_OR:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        if(arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL){
            val->t = VALUE_BOOL;
            val->v.b = arg1->v.b || arg2->v.b;
            return val;
        }
        yyerror("|| tipos incompatible"); 
        break;
    case NODE_UNARY_MINUS:
        /*v = -eval(a->l);*/
        arg1 = eval(a->l);
        if (arg1->t == VALUE_INT)
        {
            val->t = VALUE_INT;
            val->v.i = - (arg1->v.i);
            return val;
        }
        if (arg1->t == VALUE_DOUBLE)
        {
            val->t = VALUE_DOUBLE;
            val->v.d  = - (arg1->v.d) ;
            return val;
        }
        yyerror("- tipos incompatible"); 
        break;
    /* comparisons */
    case NODE_GT:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        val->t = VALUE_BOOL;
	if (arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL)
        {
            val->v.b = arg1->v.b > arg2->v.b;
            return val;
        }
	if (arg1->t == VALUE_CHAR && arg2->t == VALUE_CHAR)
        {
            val->v.b = arg1->v.c > arg2->v.c;
            return val;
        }
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->v.b = arg1->v.i > arg2->v.i;
            return val;
        }
        if (arg1->t == VALUE_DOUBLE && arg2->t == VALUE_DOUBLE)
        {
            val->v.b = arg1->v.d > arg2->v.d;
            return val;
        }
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->v.b = arg1->v.s > arg2->v.s;
            return val;
        }
        yyerror("> tipos incompatibles");
        break;
    case NODE_LT:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        val->t = VALUE_BOOL;
	if (arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL)
        {
            val->v.b = arg1->v.b < arg2->v.b;
            return val;
        }
	if (arg1->t == VALUE_CHAR && arg2->t == VALUE_CHAR)
        {
            val->v.b = arg1->v.c < arg2->v.c;
            return val;
        }
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->v.b = arg1->v.i < arg2->v.i;
            return val;
        }
        if (arg1->t == VALUE_DOUBLE && arg2->t == VALUE_DOUBLE)
        {
            val->v.b = arg1->v.d < arg2->v.d;
            return val;
        }
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->v.b = arg1->v.s < arg2->v.s;
            return val;
        }
        yyerror("< tipos incompatibles");
        break;
    case NODE_NEQ:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        val->t = VALUE_BOOL;
	if (arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL)
        {
            val->v.b = arg1->v.b != arg2->v.b;
            return val;
        }
	if (arg1->t == VALUE_CHAR && arg2->t == VALUE_CHAR)
        {
            val->v.b = arg1->v.c != arg2->v.c;
            return val;
        }
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->v.b = arg1->v.i != arg2->v.i;
            return val;
        }
        if (arg1->t == VALUE_DOUBLE && arg2->t == VALUE_DOUBLE)
        {
            val->v.b = arg1->v.d != arg2->v.d;
            return val;
        }
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->v.b = arg1->v.s != arg2->v.s;
            return val;
        }
        yyerror("!= tipos incompatibles");
        break;
    case NODE_EQ:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        val->t = VALUE_BOOL;
	if (arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL)
        {
            val->v.b = arg1->v.b == arg2->v.b;
            return val;
        }
	if (arg1->t == VALUE_CHAR && arg2->t == VALUE_CHAR)
        {
            val->v.b = arg1->v.c == arg2->v.c;
            return val;
        }
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->v.b = arg1->v.i == arg2->v.i;
            return val;
        }
        if (arg1->t == VALUE_DOUBLE && arg2->t == VALUE_DOUBLE)
        {
            val->v.b = arg1->v.d == arg2->v.d;
            return val;
        }
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->v.b = arg1->v.s == arg2->v.s;
            return val;
        }
        yyerror("== tipos incompatibles");
        break;
    case NODE_GE:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        val->t = VALUE_BOOL;
	if (arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL)
        {
            val->v.b = arg1->v.b >= arg2->v.b;
            return val;
        }
	if (arg1->t == VALUE_CHAR && arg2->t == VALUE_CHAR)
        {
            val->v.b = arg1->v.c >= arg2->v.c;
            return val;
        }
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->v.b = arg1->v.i >= arg2->v.i;
            return val;
        }
        if (arg1->t == VALUE_DOUBLE && arg2->t == VALUE_DOUBLE)
        {
            val->v.b = arg1->v.d >= arg2->v.d;
            return val;
        }
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->v.b = arg1->v.s >= arg2->v.s;
            return val;
        }
        yyerror(">= tipos incompatibles");
        break;
    case NODE_LE:
        arg1 = eval(a->l);
        arg2 = eval(a->r);
        val->t = VALUE_BOOL;
	if (arg1->t == VALUE_BOOL && arg2->t == VALUE_BOOL)
        {
            val->v.b = arg1->v.b <= arg2->v.b;
            return val;
        }
	if (arg1->t == VALUE_CHAR && arg2->t == VALUE_CHAR)
        {
            val->v.b = arg1->v.c <= arg2->v.c;
            return val;
        }
        if (arg1->t == VALUE_INT && arg2->t == VALUE_INT)
        {
            val->v.b = arg1->v.i <= arg2->v.i;
            return val;
        }
        if (arg1->t == VALUE_DOUBLE && arg2->t == VALUE_DOUBLE)
        {
            val->v.b = arg1->v.d <= arg2->v.d;
            return val;
        }
        if (arg1->t == VALUE_STRING && arg2->t == VALUE_STRING)
        {
            val->v.b = arg1->v.s <= arg2->v.s;
            return val;
        }
        yyerror("<= tipos incompatibles");
        break;
    /* control flow */
    /* null expressions allowed in the grammar, so check for them */
    /* if/then/else */
    case NODE_IF:
        if((eval(((struct flow *)a)->cond))->v.b != 0) {
            /*check the condition*/
            if( ((struct flow *)a)->tl) {
                /*the true branch*/
                val = eval(((struct flow *)a)->tl);
            } 
        } else {
            if( ((struct flow *)a)->el) {
                /*the false branch*/
                val = eval(((struct flow *)a)->el);
	    }
        }
        break;
    /* while/do */
    case NODE_WHILE:
        v = 0.0; /* a default value */
        if( ((struct flow *)a)->tl) {
            while( eval(((struct flow *)a)->cond) != 0) {
                /*evaluate the condition*/
                /*v = eval(((struct flow *)a)->tl);*/
            }
            /*evaluate the target statements*/
        }
        break; /* value of last statement is value of while/do */
    /* list of statements */
    case NODE_DO:
        v = 0.0;    /*a default value */
        if(((struct flow *)a)->tl) {
            do {
                /*v = eval(((struct flow *)a)->tl);*/
            } while (eval(((struct flow *)a)->cond) != 0);
        }
        break;
    case NODE_EXPRESION:
        /*eval(a->l);*/
        /*v = eval(a->r);*/
        break;
    case NODE_BUILTIN_FUNCTION:
        /*printf("%s\n", "case NODE_BUILTIN_FUNCTION");*/
        v = callbuiltin((struct fncall *)a);
        break;
    case NODE_USER_FUNCTION_CALL:
        v = calluser((struct ufncall *)a);
        break;
    default:
        /*v = 0;*/
        printf("error interno: nodo incorrecto %i\n", a->nodetype );
        break;
    }
    return val;
}

void imprimir(lat_value *val)
{       
    if(val != NULL){        
	switch(val->t){
	  case VALUE_BOOL:
	    if(val->v.b)
		printf("verdadero\n");
	    else
		printf("falso\n");
	    break;
	  case VALUE_INT:
	    printf("%i\n", val->v.i);
	    break;
	  case VALUE_CHAR:
	    printf("%c\n", val->v.c);
	    break;
	  case VALUE_DOUBLE:
	    printf("%g\n", val->v.d);
	    break;
	  case VALUE_STRING:
	    printf("%s\n", val->v.s);
	    break;
	  default:
	    yyerror("variable no definida");
	    break;
	}  
    }
}

static double callbuiltin(struct fncall *f)
{
    /*printf("%s\n", "callbuiltin");*/
    enum bifs functype = f->functype;
    double v = 0;
    /*if(f->l->nodetype == NODE_DECIMAL)*/
        /*v = eval(f->l);*/
    switch(functype) {
    case B_sqrt:
        return sqrt(v);
    case B_exp:
        return exp(v);
    case B_log:
        return log(v);
    case B_print:
    {
	lat_value *val = malloc(sizeof(lat_value));
	val =  eval(f->l);
	imprimir(val);        
        return v;
    }
    break;
    default:
        yyerror("definicion de funcion desconocida\n");
        return 0.0;
    }
    return 0.0;
}

/* define a function */
void
dodef(struct symbol *name, struct symlist *syms, struct ast *func)
{
    if(name->syms) symlistfree(name->syms);
    if(name->func) treefree(name->func);
    name->syms = syms;
    name->func = func;
}

static double
calluser(struct ufncall *f)
{
    struct symbol *fn = f->s; /* function name */
    struct symlist *sl; /* dummy arguments */
    struct ast *args = f->l; /* actual arguments */
    double *oldval, *newval; /* saved arg values */
    double v;
    int nargs;
    int i;
    if(!fn->func) {
        yyerror("llamada a funcion indefinida\n");
        return 0.0;
    }
    /* count the arguments */
    sl = fn->syms;
    for(nargs = 0; sl; sl = sl->next)
        nargs++;
    /* prepare to save them */
    oldval = (double *)malloc(nargs * sizeof(double));
    newval = (double *)malloc(nargs * sizeof(double));
    if(!oldval || !newval) {
        yyerror("sin espacio en %s", fn->name);
        return 0.0;
    }
    /* evaluate the arguments */
    for(i = 0; i < nargs; i++) {
        if(!args) {
            yyerror("muy pocos argumentos en llamada a funcion %s", fn->name);
            free(oldval);
            free(newval);
            return 0.0;
        }
        if(args->nodetype == NODE_LIST_SYMBOLS) { /* if this is a list node */
            /*newval[i] = eval(args->l);*/
            args = args->r;
        } else { /* if it's the end of the list */
            /*newval[i] = eval(args);*/
            args = NULL;
        }
    }
    /* save old values of dummies, assign new ones */
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        //TODO: Pendiente
        /*oldval[i] = s->value.v.d;*/
        /*s->valuev.d = newval[i];*/
        sl = sl->next;
    }
    free(newval);
    /* evaluate the function */
    /*v = eval(fn->func);*/
    /* put the real values of the dummies back */
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        //TODO: Pendiente
        /*s->value = oldval[i];*/
        sl = sl->next;
    }
    free(oldval);
    return v;
}