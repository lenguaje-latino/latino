#include "latino.h"
#include "ast.h"
#include "utils.h"
#include "vm.h"
#include "node.h"

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
struct symbol *lookup(char *sym, latValue *v)
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
			/*printf("lookup(%s)\n", sym);*/
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

ast *newOp(nodeType nodetype, ast *l, ast *r)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
	switch (nodetype)
	{
	case NODE_ADD:{
		a->l = newRef("+");
	}break;
	case NODE_SUB:{
		a->l = newRef("-");
	}break;
	case NODE_MULT:{
		a->l = newRef("*");
	}break;
	case NODE_DIV:{
		a->l = newRef("/");
	}break;
	default:
		break;
	}
	a->nodetype = NODE_CALL_FUNCTION;
	a->r = newAst(NODE_LIST_SYMBOLS, l, r);
    return a;
}

ast *newAst(nodeType nodetype, ast *l, ast *r)
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

ast *newInt(long i)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_INT;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_INT;
    val->v.i = i;
    a->value = val;
    return a;
}

ast *newNum(double d)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_DECIMAL;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_DOUBLE;
    val->v.d = d;
    a->value = val;
    return a;
}

ast *newBool(int b)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_BOOLEAN;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_BOOL;
    val->v.b = b;
    a->value = val;
    return a;
}

/*FIXME*/
ast *newChar(char *c, size_t l)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_CHAR;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_CHAR;
    val->v.c = c[0];
    a->value = val;
    return a;
}

ast *newStr(const char *s, size_t l)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_STRING;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_STRING;
    val->v.s = strndup0(s, l);
    a->value = val;
    return a;
}

ast *newFunc(ast *functype, ast *l)
{
    fnCall *a = malloc(sizeof(fnCall));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_CALL_FUNCTION;
    a->l = l;
    a->functype = 0; /*imprimir*/
    return (ast *)a;
}

ast *newCall(ast *s, ast *l)
{
    ufnCall *a = malloc(sizeof(ufnCall));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_USER_FUNCTION;
    a->l = l;
    a->s = ((symRef *)s)->s;
    return (ast *)a;
}

ast *newRef(char *s)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_SYMBOL;
	latValue *val = malloc(sizeof(latValue));
	val->t = VALUE_STRING;
	val->v.s = strdup0(s);
	a->value = val;
    return a;
}

ast *newAsgn(ast *v, ast *s)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_ASSIGMENT;
    a->l = v;
    a->r = s;
    return a;
}

ast *newIf(nodeType nodetype, ast *cond, ast *tl, ast *el)
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

ast *newSwitch(nodeType nodetype, ast *cond, ast *tl, ast *el)
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

ast *newCase(nodeType nodetype, ast *cond, ast *tl, ast *el)
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

ast *newWhile(nodeType nodetype, ast *cond, ast *tl, ast *el)
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

ast *newDo(nodeType nodetype, ast *cond, ast *tl, ast *el)
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

ast *newFor(nodeType nodetype, ast *begin, ast *end, ast *stmts, ast *step)
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

ast *newSymList(ast *sym, ast *next)
{
    ast *sl = malloc(sizeof(ast));
    if (!sl) {
        yyerror("sin espacio\n");
        exit(0);
    }
	sl->nodetype = NODE_LIST_SYMBOLS;
    sl->l = sym;
    sl->r = next;
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
ast *doDef(ast *s, ast *syms, ast *func)
{
	ast *a = malloc(sizeof(ast));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
	a->nodetype = NODE_ASSIGMENT;
	a->l = newAst(NODE_USER_FUNCTION, syms, func);
	a->r = s;
	return a;
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
    case NODE_CALL_FUNCTION:
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
void symListFree(ast *sl)
{
    ast *nsl;
    while (sl) {
        nsl = sl->r;
        free(sl);
        sl = nsl;
    }
}

int tabstop = 2;
int indent = 0;

void printIndent()
{
    for (int i = 0; i < (indent * tabstop); i++) {
        printf(" ");
    }
}

void printAst(ast *a)
{
    if (!a) {
        yyerror("eval es nulo\n");
        return;
    }
    /*print indent*/
    switch (a->nodetype) {
    case NODE_BOOLEAN:
    case NODE_CHAR:
    case NODE_DECIMAL:
    case NODE_STRING:
    case NODE_INT:
        imprimir(a->value);
        break;
    case NODE_SYMBOL: {
        symRef *r = ((symRef *)a);
		if (r->s){
			printf("%s", r->s->name);
		}
    }
    break;
    /* assignment */
    case NODE_ASSIGMENT: {
        symAsgn *sa = ((symAsgn *)a);
        /*sa->s->value = eval(sa->v);*/
        //printIndent();
        printf("%s = ", sa->s->name);
        printAst(sa->v);
        printf("%s\n", ";");
    }
    break;
    case NODE_UNARY_MINUS:
        printf("%s", " - ");
        printAst(a->l);
        break;
    /* expressions */
    case NODE_ADD:
        printAst(a->l);
        printf("%s", " + ");
        printAst(a->r);
        break;
    case NODE_SUB:
        printAst(a->l);
        printf("%s", " - ");
        printAst(a->r);
        break;
    case NODE_MULT:
        printAst(a->l);
        printf("%s", " * ");
        printAst(a->r);
        break;
    case NODE_DIV:
        printAst(a->l);
        printf("%s", " / ");
        printAst(a->r);
        break;
    case NODE_MOD:
        printAst(a->l);
        printf("%s", " % ");
        printAst(a->r);
        break;
    case NODE_AND:
        printAst(a->l);
        printf("%s", " && ");
        printAst(a->r);
        break;
    case NODE_OR:
        printAst(a->l);
        printf("%s", " || ");
        printAst(a->r);
        break;
    case NODE_NEG:
        printAst(a->l);
        printf("%s", " !");
        break;
    /* comparisons */
    case NODE_GT:
        printAst(a->l);
        printf("%s", " > ");
        printAst(a->r);
        break;
    case NODE_LT:
        printAst(a->l);
        printf("%s", " < ");
        printAst(a->r);
        break;
    case NODE_NEQ:
        printAst(a->l);
        printf("%s", " != ");
        printAst(a->r);
        break;
    case NODE_EQ:
        printAst(a->l);
        printf("%s", " == ");
        printAst(a->r);
        break;
    case NODE_GE:
        printAst(a->l);
        printf("%s", " >= ");
        printAst(a->r);
        break;
    case NODE_LE:
        printAst(a->l);
        printf("%s", " <= ");
        printAst(a->r);
        break;
    case NODE_IF: {
        //printIndent();
        printf("%s", "if (");
        flow *ni = ((flow *)a);
        printAst(ni->cond);
        printf("%s", ")");
        if (ni->tl) {
            printf("%s\n", "{");
            indent++;
            //printIndent();
            printAst(ni->tl);
            indent--;
            printIndent();
            printf("%s\n", "}");
        }
        if (ni->el) {
            printIndent();
            printf("%s\n", "else {");
            indent++;
            //printIndent();
            printAst(ni->el);
            indent--;
            printIndent();
            printf("%s\n", "}");
        }
    }
    break;
    case NODE_WHILE: {
        //printIndent();
        printf("%s", "while (");
        flow *nw = ((flow *)a);
        printAst(nw->cond);
        printf("%s\n", ") {");
        if (nw->tl) {
            indent++;
            //printIndent();
            printAst(nw->tl);
            indent--;
        }
        printIndent();
        printf("%s\n", "}");
    }
    break;
    case NODE_DO: {
        //printIndent();
        flow *nd = ((flow *)a);
        printf("%s\n", "do {");
        if (nd->tl) {
            indent++;
            //printIndent();
            printAst(nd->tl);
            indent--;
        }
        printIndent();
        printf("%s", "} while (");
        printAst(nd->cond);
        printf("%s\n", ");");
    }
    break;
	case NODE_FROM:
	{
		//printIndent();
		nodeFor *nf = ((nodeFor *)a);
		latValue *begin = eval(nf->begin);
		latValue *end = eval(nf->end);
		if (begin->t == VALUE_INT && end->t == VALUE_INT){
			printf("for(int i = ");
			printf("%i; ", begin->v.i);
			if (begin->v.i < end->v.i){
				printf("i < ");
			}else{
				printf("i > ");
			}
			printAst(nf->end);
			printf("; ");
			if (begin->v.i < end->v.i){
				printf("%s\n", "i++) {");
			}else{
				printf("%s\n", "i--) {");
			}
			if (nf->stmts){
				indent++;
				//printIndent();
				printAst(nf->stmts);
				indent--;
			}
			printIndent();
			printf("%s\n", "}");
		}
	}break;
    case NODE_BLOCK: {
		printIndent();
		if (a->l){
			printAst(a->l);
		}
        if (a->r) {
            printAst(a->r);
        }
    }
    break;
    case NODE_RETURN: {
        if (a->l) {
            printf("%s", "return ");
            printAst(a->l);
        }
    }
    break;
	case NODE_CALL_FUNCTION:{
        //printIndent();
        fnCall *uf = ((fnCall *)a);
        if (uf->l) {
            indent++;
            //printIndent();
            printAst(uf->l);
            indent--;
        }
	}break;
    case NODE_USER_FUNCTION: {
        //printIndent();
        ufnCall *uf = ((ufnCall *)a);
        if (uf->s) {
			printf("%s", uf->s->name);
			printf("%s", "(");
            if (uf->l) {
                printAst(uf->l);
            }
			printf("%s", ")");
        }
    }
    break;
    case NODE_LIST_SYMBOLS: {
        if (a->l) {
            printAst(a->l);
        }
		if (a->r){
			printAst(a->l);
		}
    }
    break;
    default: {
        printf("default: %i\n", a->nodetype);
    }
    break;
    }
}

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(N) i = lat_parse_node(N, bcode, i)
#define fdbc(I, A, B, M) function_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(N) fi = lat_parse_node(N, function_bcode, fi)

lat_object *lat_parse_tree(lat_vm *vm, ast *tree)
{
    lat_bytecode *bcode = (lat_bytecode *)malloc(
                              sizeof(lat_bytecode) * 1024);
    int i = lat_parse_node(tree, bcode, 0);
    dbc(OP_END, 0, 0, NULL);
    return lat_define_function(vm, bcode);
}

int lat_parse_node(ast *node, lat_bytecode *bcode, int i)
{
	int temp[8] = { 0 };
	lat_bytecode *function_bcode = NULL;
	int fi = 0;
	switch (node->nodetype) {
	case NODE_BLOCK:
	{
		pn(node->l);
		if (node->r){
			pn(node->r);
		}
	}
	break;
	case NODE_SYMBOL: /*GET*/
	{
		/*if (node->l->r){
			pn(node->l->r);
			dbc(OP_MOV, 1, 255, NULL);
		}
		else{
			dbc(OP_LOCALNS, 1, 0, NULL);
		}*/
		dbc(OP_LOCALNS, 1, 0, NULL);
		dbc(OP_STORESTR, 2, 0, node->value->v.s);
		dbc(OP_GET, 2, 1, NULL);
		dbc(OP_MOV, 255, 2, NULL);
	}
	break;
	case NODE_ASSIGMENT: /*SET*/
	{
		pn(node->l);
		dbc(OP_PUSH, 255, 0, NULL);
		/*if (node->r) {
			pn(node->r);
			dbc(OP_MOV, 1, 255, NULL);
		}
		else {
			dbc(OP_LOCALNS, 1, 0, NULL);
		}*/
		dbc(OP_LOCALNS, 1, 0, NULL);
		dbc(OP_POP, 255, 0, NULL);
		dbc(OP_SET, 255, 1, node->r->value->v.s);
	}
	break;
	case NODE_INT:
	{
		dbc(OP_STOREINT, 255, node->value->v.i, NULL);
	}
	break;
	case NODE_DECIMAL:
	{
		dbc(OP_STOREDOUBLE, 255, 0, &(node->value->v.d));
	}
	break;
	case NODE_STRING:
	{
		dbc(OP_STORESTR, 255, 0, node->value->v.s);
	}
	break;
	case NODE_BOOLEAN:
	{
		dbc(OP_STOREBOOL, 255, node->value->v.b, NULL);
	}
	break;
	case NODE_CALL_FUNCTION:
	{
		pn(node->r);
		pn(node->l);
		dbc(OP_CALL, 255, 0, NULL);
	}
	break;
	case NODE_RETURN:
	{
		pn(node->l);
		dbc(OP_END, 0, 0, NULL);
	}
	break;
	case NODE_LIST_SYMBOLS: {
		if (node->r != NULL) {
			pn(node->r);
			dbc(OP_PUSH, 255, 0, NULL);
		}
		if (node->l != NULL) {
			pn(node->l);
			dbc(OP_PUSH, 255, 0, NULL);
		}
	}break;
	case NODE_USER_FUNCTION:
	{
		function_bcode = (lat_bytecode *)malloc(
			sizeof(lat_bytecode) * 1024);
		fi = 0;
		if (node->l != NULL) {
			fpn(node->l);
		}
		fpn(node->r);
		dbc(OP_FN, 255, 0, function_bcode);
		function_bcode = NULL;
		fi = 0;
	}break;
	/*case NS:
	{
		dbc(OP_NS, 255, 0, NULL);
		pn(node->l);
		dbc(OP_ENDNS, 255, 0, NULL);
	}
	break;*/
	default:
		printf("nodetype:%i\n", node->nodetype);
		return;
	}
	return i;
}
