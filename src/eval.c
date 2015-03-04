#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
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

struct symbol *
lookup(char* sym) {
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount        = NHASH; /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) {
            return sp;
        }
        if (!sp->name) { /* new entry*/
            sp->name  = strdup(sym);
            sp->value = 0;
            sp->func  = NULL;
            sp->syms  = NULL;
            return sp;
        }
        if (++sp >= symtab + NHASH) sp = symtab; /* try the next entry */
    }
    yyerror("desbordamiento de la tabla de simbolos\n");
    abort();    /* tried them all, table is full */
}

struct ast *
newast(node_type nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));
    if(!a) {
        yyerror("sin espacio");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *
newnum(double d)
{
    struct numval *a = malloc(sizeof(struct numval));
    if(!a) {
        yyerror("sin espacio");
        exit(0);
    }
    a->nodetype = NODE_DECIMAL;
    a->number = d;
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
newstr(lat_string s, size_t l)
{
    struct strval *a = malloc(sizeof(struct strval));
    if(!a){
        yyerror("sin espacio");
        exit(0);
    }
    a->nodetype = NODE_STRING;
    a->str      = strndup0(s, l);
    return (struct ast *)a;
}

struct ast *
newcmp(int cmptype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));
    if(!a) {
        yyerror("sin espacio");
        exit(0);
    }
    //a->nodetype = '0' + nodetype;
    a->nodetype = cmptype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *
newfunc(int functype, struct ast *l)
{
    struct fncall *a = malloc(sizeof(struct fncall));
    if(!a) {
        yyerror("sin espacio");
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
    struct ufncall *a = malloc(sizeof(struct ufncall));
    if(!a) {
        yyerror("sin espacio");
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
        yyerror("sin espacio");
        exit(0);
    }
    a->nodetype = NODE_SYMBOL;
    a->s = s;
    return (struct ast *)a;
}

struct ast *
newasgn(struct symbol *s, struct ast *v)
{
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("sin espacio");
        exit(0);
    }
    a->nodetype = NODE_ASSIGMENT;
    a->s = s;
    a->v = v;
    return (struct ast *)a;
}
struct ast *
newflow(node_type nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
    struct flow *a = malloc(sizeof(struct flow));
    if(!a) {
        yyerror("sin espacio");
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
    case NODE_EQUAL:
    case NODE_NOT_EQUAL:
    case NODE_GREATER_THAN:
    case NODE_LESS_THAN:
    case NODE_GREATER_THAN_EQUAL:
    case NODE_LESS_THAN_EQUAL:
    case NODE_EXPRESION:
        treefree(a->r);
    /* one subtree */
    case NODE_UNARY_MINUS:
    case NODE_USER_FUNCTION_CALL:
    case NODE_BUILTIN_FUNCTION:
        treefree(a->l);
    /* no subtree */
    case NODE_DECIMAL:
    case NODE_SYMBOL:
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
        free( ((struct strval *)a)->str);
        break;
    default:
        printf("error interno: nodo mal liberado %c\n", a->nodetype);
    }
    free(a); /* always free the node itself */
}
struct symlist *
newsymlist(struct symbol *sym, struct symlist *next)
{
    //printf("newsymlist: %s\n", sym->name);
    struct symlist *sl = malloc(sizeof(struct symlist));
    if(!sl) {
        yyerror("sin espacio");
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

double
eval(struct ast *a)
{
    double v;
    if(!a) {
        yyerror("error interno, eval es nulo");
        return 0.0;
    }
    switch(a->nodetype) {
    printf("%s", a->nodetype);
    /* constant */
    case NODE_DECIMAL:
        v = ((struct numval *)a)->number;
        break;
    /* name reference */
    case NODE_SYMBOL:
        v = ((struct symref *)a)->s->value;
        break;
    /* assignment */
    case NODE_ASSIGMENT:
        v = ((struct symasgn *)a)->s->value =
                eval(((struct symasgn *)a)->v);
        break;
    /* expressions */
    case NODE_ADD:
        v = eval(a->l) + eval(a->r);
        break;
    case NODE_SUB:
        v = eval(a->l) - eval(a->r);
        break;
    case NODE_MULT:
        v = eval(a->l) * eval(a->r);
        break;
    case NODE_DIV:
        if(eval(a->r) == 0)
            printf("error: division por 0 \"%c\"\n", a->nodetype);
        else
            v = eval(a->l) / eval(a->r);
        break;
    case NODE_UNARY_MINUS:
        v = -eval(a->l);
        break;
    /* comparisons */
    case NODE_GREATER_THAN:
        v = (eval(a->l) > eval(a->r))? 1 : 0;
        break;
    case NODE_LESS_THAN:
        v = (eval(a->l) < eval(a->r))? 1 : 0;
        break;
    case NODE_NOT_EQUAL:
        v = (eval(a->l) != eval(a->r))? 1 : 0;
        break;
    case NODE_EQUAL:
        v = (eval(a->l) == eval(a->r))? 1 : 0;
        break;
    case NODE_GREATER_THAN_EQUAL:
        v = (eval(a->l) >= eval(a->r))? 1 : 0;
        break;
    case NODE_LESS_THAN_EQUAL:
        v = (eval(a->l) <= eval(a->r))? 1 : 0;
        break;
    case '7':
        v = 1;
        break;
    case '8':
        v = 0;
        break;
    /* control flow */
    /* null expressions allowed in the grammar, so check for them */
    /* if/then/else */
    case NODE_IF:
        if( eval( ((struct flow *)a)->cond) != 0) {
            /*check the condition*/
            if( ((struct flow *)a)->tl) {
                /*the true branch*/
                v = eval( ((struct flow *)a)->tl);
            } else
                v = 0.0; /* a default value */
        } else {
            if( ((struct flow *)a)->el) {
                /*the false branch*/
                v = eval(((struct flow *)a)->el);
            } else
                v = 0.0; /* a default value */
        }
        break;
    /* while/do */
    case NODE_WHILE:
        v = 0.0; /* a default value */
        if( ((struct flow *)a)->tl) {
            while( eval(((struct flow *)a)->cond) != 0)
                /*evaluate the condition*/
                v = eval(((struct flow *)a)->tl);
            /*evaluate the target statements*/
        }
        break; /* value of last statement is value of while/do */
    /* list of statements */
    case NODE_DO:
        v = 0.0;    /*a default value */
        if(((struct flow *)a)->tl) {
            do{
                v = eval(((struct flow *)a)->tl);
            }while (eval(((struct flow *)a)->cond) != 0);
        }
        break;
    case NODE_EXPRESION:
        eval(a->l);
        v = eval(a->r);
        break;
    case NODE_BUILTIN_FUNCTION:
        v = callbuiltin((struct fncall *)a);
        break;
    case NODE_USER_FUNCTION_CALL:
        v = calluser((struct ufncall *)a);
        break;
    case NODE_STRING:
        //v = eval(a->str);
        //v = ((struct numval *)a)->number;
        printf("se encontro cadena: %s\n", ((struct strval *)a)->str);
        break;
    default:
        printf("error interno: nodo incorrecto %c\n", a->nodetype);
    }
    return v;
}

static double
callbuiltin(struct fncall *f)
{
    enum bifs functype = f->functype;
    double v = eval(f->l);
    //printf("=> %4.4g\n", v);
    switch(functype) {
    case B_sqrt:
        return sqrt(v);
    case B_exp:
        return exp(v);
    case B_log:
        return log(v);
    case B_print:
        printf("=> %4.4g\n", v);
        //printf("=> %s\n", f->l);
        return v;
    default:
        yyerror("error: definicion de funcion desconocida %d", functype);
        return 0.0;
    }
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
        yyerror("llamada a funcion indefinida", fn->name);
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
        if(args->nodetype == 'L') { /* if this is a list node */
            newval[i] = eval(args->l);
            args = args->r;
        } else { /* if it's the end of the list */
            newval[i] = eval(args);
            args = NULL;
        }
    }
    /* save old values of dummies, assign new ones */
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl->next;
    }
    free(newval);
    /* evaluate the function */
    v = eval(fn->func);
    /* put the real values of the dummies back */
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        s->value = oldval[i];
        sl = sl->next;
    }
    free(oldval);
    /*printf("%d", v);*/
    return v;
}
