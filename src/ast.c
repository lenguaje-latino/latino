#include "latino.h"
#include "ast.h"
#include "utils.h"
#include "vm.h"

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

ast * newNum(double d)
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

ast * newBool(int b)
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
ast * newChar(char *c, size_t l)
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

ast * newStr(const char *s, size_t l)
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

ast * newFunc(ast *functype, ast *l)
{
    fnCall *a = malloc(sizeof(fnCall));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_BUILTIN_FUNCTION;
    a->l = l;
    a->functype = 0; /*imprimir*/
    return (ast *)a;
}

ast * newCall(ast *s, ast *l)
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

ast * newRef(struct symbol *s)
{
    symRef *a = malloc(sizeof(symRef));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_SYMBOL;
    /*a->s = lookup(s->name, NULL);*/
    a->s = s; //lookup(s->name, NULL);
    return (ast *)a;
}

ast * newAsgn(ast *s, ast *v)
{
    symAsgn *a = malloc(sizeof(symAsgn));
    if (!a) {
        yyerror("sin espacio\n");
        exit(0);
    }
    a->nodetype = NODE_ASSIGMENT;
    a->s = ((symRef *)s)->s;
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
void doDef(ast *s, symList *syms, ast *func)
{
    ((symbol *)s)->syms = syms;
    ((symbol *)s)->func = func;
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

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(N) i = lat_parse_node(N, bcode, i)
#define fdbc(I, A, B, M) function_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(N) fi = lat_parse_node(N, function_bcode, fi)

lat_object *lat_parse_tree(lat_vm *vm, ast *tree)
{
	lat_bytecode *bcode = (lat_bytecode *)malloc(
		sizeof(lat_bytecode) * 1024);
	/*int i = lat_parse_node(tree, bcode, 0);*/
	int i = 0;
	dbc(OP_END, 0, 0, NULL);
	return lat_define_function(vm, bcode);
}

/*
int lat_parse_node(ast *node, lat_bytecode *bcode, int i)
{
	int temp[8] = { 0 };
	lat_bytecode *function_bcode = NULL;
	int fi = 0;
	//debug("parsing node with ins %d", node->ins);
	switch (node->nodetype) {
	case NODE_BLOCK:
		pn(node->l);
		if (node->r != NULL) {
			pn(node->r);
		}
		break;
	case BLOCK:
		pn(node->arg1);
		break;	
	case NODE_IDENTIFIER:
		log_err("IDENTIFIER node shouldn't be parsed.");
		exit(1);
		break;
	case NS_VAR:
		log_err("NS_VAR node shouldn't be parsed.");
		exit(1);
		break;
	case GET:
		if (node->arg1->arg2 != NULL) {
			pn(node->arg1->arg2);
			dbc(OP_MOV, 1, 255, NULL);
		}
		else {
			dbc(OP_LOCALNS, 1, 0, NULL);
		}
		dbc(OP_STORESTR, 2, 0, node->arg1->arg1->val.strval);
		dbc(OP_GET, 2, 1, NULL);
		dbc(OP_MOV, 255, 2, NULL);
		break;
	case GGET:
		dbc(OP_GLOBALNS, 1, 0, NULL);
		dbc(OP_STORESTR, 2, 0, node->arg1->val.strval);
		dbc(OP_GET, 2, 1, NULL);
		dbc(OP_MOV, 255, 2, NULL);
		break;
	case SET:
		pn(node->arg1);
		dbc(OP_PUSH, 255, 0, NULL);
		if (node->arg2->arg2 != NULL) {
			pn(node->arg2->arg2);
			dbc(OP_MOV, 1, 255, NULL);
		}
		else {
			dbc(OP_LOCALNS, 1, 0, NULL);
		}
		dbc(OP_POP, 255, 0, NULL);
		dbc(OP_SET, 255, 1, node->arg2->arg1->val.strval);
		break;
	case GSET:
		pn(node->arg1);
		dbc(OP_GLOBALNS, 1, 0, NULL);
		dbc(OP_SET, 255, 1, node->arg2->val.strval);
		break;
	case CALL:
		pn(node->arg2);
		pn(node->arg1);
		dbc(OP_CALL, 255, 0, NULL);
		break;
	case FUNC_ARGS:
		if (node->arg2 != NULL) {
			pn(node->arg2);
		}
		if (node->arg1 != NULL) {
			pn(node->arg1);
			dbc(OP_PUSH, 255, 0, NULL);
		}
		break;
	case CONST_INT:
		dbc(OP_STOREINT, 255, node->val.ival, NULL);
		break;
	case CONST_DOUBLE:
		dbc(OP_STOREDOUBLE, 255, 0, &(node->val.dval));
		break;
	case CONST_STR:
		dbc(OP_STORESTR, 255, 0, node->val.strval);
		break;
	case CONST_BOOL:
		dbc(OP_STOREBOOL, 255, node->val.ival, NULL);
		break;
	case CONST_LIST:
		dbc(OP_STORELIST, 0, 0, NULL);
		pn(node->arg1);
		break;
	case LIST_BODY:
		if (node->arg1 != NULL) {
			pn(node->arg1);
			dbc(OP_PUSHLIST, 0, 255, NULL);
		}
		if (node->arg2 != NULL) {
			pn(node->arg2);
		}
		dbc(OP_MOV, 255, 0, NULL);
		break;
	case IF:
		pn(node->arg1);
		dbc(OP_MOV, 2, 255, NULL);
		dbc(OP_NOT, 2, 0, NULL);
		temp[0] = i;
		dbc(OP_NOP, 0, 0, NULL);
		pn(node->arg2);
		bcode[temp[0]] = lat_bc(OP_JMPIF, i, 2, NULL);
		break;
	case WHILE:
		temp[0] = i;
		pn(node->arg1);
		dbc(OP_MOV, 2, 255, NULL);
		dbc(OP_NOT, 2, 0, NULL);
		temp[1] = i;
		dbc(OP_NOP, 0, 0, NULL);
		pn(node->arg2);
		dbc(OP_JMP, temp[0], 0, NULL);
		bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
		break;
	case FN:
		function_bcode = (lat_bytecode *)malloc(
			sizeof(lat_bytecode) * 1024);
		fi = 0;
		if (node->arg1 != NULL) {
			fpn(node->arg1);
		}
		fpn(node->arg2);
		dbc(OP_FN, 255, 0, function_bcode);
		function_bcode = NULL;
		fi = 0;
		break;
	case PARAM_LIST:
		if (node->arg1 != NULL) {
			dbc(OP_LOCALNS, 1, 0, NULL);
			dbc(OP_POP, 2, 0, NULL);
			dbc(OP_SET, 2, 1, node->arg1->val.strval);
		}
		if (node->arg2 != NULL) {
			pn(node->arg2);
		}
		break;
	case RET:
		pn(node->arg1);
		dbc(OP_END, 0, 0, NULL);
		break;
	case NS:
		dbc(OP_NS, 255, 0, NULL);
		pn(node->arg1);
		dbc(OP_ENDNS, 255, 0, NULL);
	}
	return i;
}*/