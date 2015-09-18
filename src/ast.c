#include "ast.h"
#include "utils.h"

/* tabla de simbolos */
static long symHash(char *sym)
{
    int hash = 0;
    int len = strlen(sym);
    while (len--) hash = (hash << 5) - hash + *sym++;
    return abs(hash);
}

/*
 * busca un valor en la tabla de simbolos
 * si no existe lo crea
 */
struct symbol * lookup(char *sym, latValue *v)
{
    symbol *sp = &symTab[symHash(sym) % NHASH];
    int scount = NHASH; /* how many have we looked at */
    while (--scount >= 0) {
        if (sp->name && !strcmp(sp->name, sym)) {
            if (v != NULL) {
                /* set value to symbol if exists */
                sp->value = v;
            }
            return sp;
        }
        if (!sp->name) { /* new entry*/
            sp->name = strdup0(sym);
            sp->value = NULL;
            sp->func = NULL;
            sp->syms = NULL;
            return sp;
        }
        if (++sp >= symTab + NHASH)
            sp = symTab; /* try the next entry */
    }
    yyerror("desbordamiento de la tabla de simbolos\n");
    abort();    /* tried them all, table is full */
}

ast * newAst(nodeType nodetype, ast *l, ast *r)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

ast * newInt(long i)
{
    node *a = malloc(sizeof(node));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_INT;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_INT;
    val->v.i = i;
    a->value = val;
    return (ast *)a;
}

ast * newNum(double d)
{
    node *a = malloc(sizeof(node));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_DECIMAL;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_DOUBLE;
    val->v.d = d;
    a->value = val;
    return (ast *)a;
}

ast * newBool(int b)
{
    node *a = malloc(sizeof(node));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_BOOLEAN;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_BOOL;
    val->v.b = b;
    a->value = val;
    return (ast *)a;
}

/*FIXME*/
ast * newChar(char *c, size_t l)
{
    node *a = malloc(sizeof(node));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_CHAR;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_CHAR;
    val->v.c = c[0];
    a->value = val;
    return (ast *)a;
}

ast * newStr(char *s, size_t l)
{
    node *a = malloc(sizeof(node));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_STRING;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_STRING;
    val->v.s = strndup0(s, l);
    a->value = val;
    return (ast *)a;
}

ast * newFunc(int functype, ast *l)
{
    fnCall *a = malloc(sizeof(fnCall));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_BUILTIN_FUNCTION;
    a->l = l;
    a->functype = functype;
    return (ast *)a;
}

ast * newCall(struct symbol *s, ast *l)
{
    ufnCall *a = malloc(sizeof(ufnCall));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_USER_FUNCTION;
    a->l = l;
    a->s = s;
    return (ast *)a;
}

ast * newRef(struct symbol *s)
{
    symref *a = malloc(sizeof(symref));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_SYMBOL;
    a->s = lookup(s->name, NULL);
    return (ast *)a;
}

ast * newAsgn(struct symbol *s, ast *v)
{
    symAsgn *a = malloc(sizeof(symAsgn));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_ASSIGMENT;
    a->s = s;
    a->v = v;
    return (ast *)a;
}

ast * newIf(nodeType nodetype, ast *cond, ast *tl, ast *el)
{
    flow *a = malloc(sizeof(flow));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (ast *)a;
}

ast * newSwitch(nodeType nodetype, ast *cond, ast *tl, ast *el)
{
    flow *a = malloc(sizeof(flow));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (ast *)a;
}

ast * newCase(nodeType nodetype, ast *cond, ast *tl, ast *el)
{
    flow *a = malloc(sizeof(flow));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (ast *)a;
}

ast * newWhile(nodeType nodetype, ast *cond, ast *tl, ast *el)
{
    flow *a = malloc(sizeof(flow));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (ast *)a;
}

ast * newDo(nodeType nodetype, ast *cond, ast *tl, ast *el)
{
    flow *a = malloc(sizeof(flow));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (ast *)a;
}

ast * newFor(nodeType nodetype, ast *begin, ast *end, ast *stmts, ast *step)
{
    nodeFor *a = malloc(sizeof(nodeFor));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->begin = begin;
    a->end = end;
    a->stmts = stmts;
    a->step = step;
    return (ast *)a;
}

symList * newSymList(struct symbol *sym, symList *next)
{
    symList *sl = malloc(sizeof(symList));
    if (!sl) {
        yyerror("sin espacio\n");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}

double callBuiltin(fnCall *f)
{
    double v = 0;
    switch (f->functype) {
    case B_sqrt:
        return sqrt(v);
    case B_exp:
        return exp(v);
    case B_log:
        return log(v);
    case B_print: {
        latValue *val;
        val = eval(f->l);
        imprimir(val);
    }
                  return v;
    default:
        yyerror("definicion de funcion desconocida\n");
    }
    return v;
}

/* define una funcion */
void doDef(struct symbol *s, symList *syms, ast *func)
{
    s->syms = syms;
    s->func = func;
}

/* free a tree of ASTs */
void treeFree(ast *a)
{
    switch (a->nodetype) {
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
    case NODE_BLOCK:
        if (a->r)
            treeFree(a->r);
        if (a->l)
            treeFree(a->l);
        break;
        /* one subtree */
    case NODE_NEG:
    case NODE_UNARY_MINUS:
    case NODE_USER_FUNCTION:
    case NODE_LIST_SYMBOLS:
    case NODE_RETURN:
    case NODE_BUILTIN_FUNCTION:
        if (a->l)
            treeFree(a->l);
        break;
        /* no subtree */
    case NODE_INT:
    case NODE_CHAR:
    case NODE_DECIMAL:
    case NODE_SYMBOL:
    case NODE_BOOLEAN:
    case NODE_STRING:
        break;
    case NODE_ASSIGMENT:
        if (((symAsgn *)a)->v)
            treeFree(((symAsgn *)a)->v);
        break;
        /* up to three subtrees */
    case NODE_IF:
    case NODE_DO:
    case NODE_WHILE:
    case NODE_SWITCH:
    case NODE_CASES:
    case NODE_CASE:
    case NODE_DEFAULT:
        if (((flow *)a)->el)
            treeFree(((flow *)a)->el);
        if (((flow *)a)->tl)
            treeFree(((flow *)a)->tl);
        if (((flow *)a)->cond)
            treeFree(((flow *)a)->cond);
        break;
    case NODE_FROM:
        if (((nodeFor *)a)->stmts)
            treeFree(((nodeFor *)a)->stmts);
        if (((nodeFor *)a)->step)
            treeFree(((nodeFor *)a)->step);
        break;
    default:
        printf("error interno: nodo mal liberado %i\n", a->nodetype);
        break;
    }
}

/* free a list of symbols */
void symListFree(symList *sl)
{
    symList *nsl;
    while (sl) {
        nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}
