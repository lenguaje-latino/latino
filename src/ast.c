#include "latino.h"
#include "ast.h"
#include "utils.h"
#include "vm.h"

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(vm, N) i = lat_parse_node(vm, N, bcode, i)
#define fdbc(I, A, B, M) function_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(vm, N) fi = lat_parse_node(vm, N, function_bcode, fi)

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root, const char *s)
{
	log_err("%s at line %d", s, yylloc_param->first_line);
	exit(1);
	return 0;
}

ast *newOp(nodeType nodetype, ast *l, ast *r)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
	switch (nodetype)
	{
	case NODE_ADD:{
		a->l = newRef("+");
	}break;
	case NODE_UNARY_MINUS:
	case NODE_SUB:{
		a->l = newRef("-");
	}break;
	case NODE_MULT:{
		a->l = newRef("*");
	}break;
	case NODE_DIV:{
		a->l = newRef("/");
	}break;
	case NODE_MOD:{
		a->l = newRef("%");
	}break;
	case NODE_GE:{
		a->l = newRef(">=");
	}break;
	case NODE_GT:{
		a->l = newRef(">");
	}break;
	case NODE_LE:{
		a->l = newRef("<=");
	}break;
	case NODE_LT:{
		a->l = newRef("<");
	}break;
	case NODE_NEQ:{
		a->l = newRef("!=");
	}break;
	case NODE_EQ:{
		a->l = newRef("==");
	}break;
	default:
		break;
	}
	if (nodetype == NODE_UNARY_MINUS)
	{
		a->r = newAst(NODE_FUNC_ARGS, newInt(0), l);
	}
	else{
		a->r = newAst(NODE_FUNC_ARGS, l, r);
	}
	a->nodetype = NODE_CALL_FUNCTION;
	a->value = NULL;
    return a;
}

ast *newAst(nodeType nodetype, ast *l, ast *r)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
	a->value = NULL;
    return a;
}

ast *newInt(long i)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
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
        log_err("Memoria agotada\n");
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
        log_err("Memoria agotada\n");
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
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = NODE_CHAR;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_CHAR;
	char tmp = ' ';
	switch (c[0])
	{
	case '\\':{
		switch (c[1])
		{
		case 'a':{ tmp = '\a'; } break;
		case 'b':{ tmp = '\b'; } break;
		case 'f':{ tmp = '\f'; } break;
		case 'n':{ tmp = '\n'; } break;
		case 'r':{ tmp = '\r'; } break;
		case 't':{ tmp = '\t'; } break;
		case 'v':{ tmp = '\v'; } break;
		default: tmp = c[0]; break;
		}
	}
	break;
	default:
		tmp = c[0];
		break;
	}
	val->v.c = tmp;
    a->value = val;
    return a;
}

ast *newStr(const char *s, size_t l)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = NODE_STRING;
    latValue *val = malloc(sizeof(latValue));
    val->t = VALUE_STRING;
    val->v.s = parse_string(s, l);
    a->value = val;
    return a;
}

ast *newRef(char *s)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
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
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = NODE_ASSIGMENT;
    a->l = v;
    a->r = s;
	a->value = NULL;
    return a;
}

ast *newIf(ast *cond, ast *entonces, ast *sino)
{
    nodeIf *a = malloc(sizeof(nodeIf));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = NODE_IF;
    a->cond = cond;
    a->entonces = entonces;
    a->sino = sino;
    return (ast *)a;
}

ast *newSwitch(nodeType nodetype, ast *cond, ast *entonces, ast *sino)
{
    nodeIf *a = malloc(sizeof(nodeIf));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->entonces = entonces;
    a->sino = sino;
    return (ast *)a;
}

ast *newCase(nodeType nodetype, ast *cond, ast *entonces, ast *sino)
{
    nodeIf *a = malloc(sizeof(nodeIf));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->entonces = entonces;
    a->sino = sino;
    return (ast *)a;
}

ast *newWhile(ast *cond, ast *stmts)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = NODE_WHILE;
    a->l = cond;
    a->r = stmts;
	a->value = NULL;
    return a;
}

ast *newDo(ast *cond, ast *stmts)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->nodetype = NODE_DO;
    a->l = cond;
    a->r = stmts;
	a->value = NULL;
    return a;
}

ast *newFor(ast *dec, ast *cond, ast *inc, ast *stmts)
{
    ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
	a->nodetype = NODE_BLOCK;
	a->l = newWhile(cond, newAst(NODE_BLOCK, stmts, inc));
	a->r = dec;
	a->value = NULL;
	return a;
}

/* define una funcion */
ast *doDef(ast *s, ast *syms, ast *func)
{
	ast *a = malloc(sizeof(ast));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
	a->nodetype = NODE_ASSIGMENT;
	a->l = newAst(NODE_USER_FUNCTION, syms, func);
	a->r = s;
	a->value = NULL;
	return a;
}

void treeFree(ast *a){
	if (a){
		switch (a->nodetype)
		{
		case NODE_BLOCK:
		case NODE_LIST_BODY:
			if (a->r)
				treeFree(a->r);
			if (a->l)
				treeFree(a->l);
			break;
		default:
			if (a->value)
				free(a->value);
			free(a);
			break;
		}
	}
}

lat_object *lat_parse_tree(lat_vm *vm, ast *tree)
{
    lat_bytecode *bcode = (lat_bytecode *)malloc(sizeof(lat_bytecode) * 1024);
    int i = lat_parse_node(vm, tree, bcode, 0);
    dbc(OP_END, 0, 0, NULL);
	treeFree(tree);
    return lat_define_function(vm, bcode);
}

int nested = -1;

int lat_parse_node(lat_vm *vm, ast *node, lat_bytecode *bcode, int i)
{
	int temp[8] = { 0 };
	lat_bytecode *function_bcode = NULL;
	int fi = 0;
	switch (node->nodetype) {
	case NODE_BLOCK:
	{
		if (node->r){
			pn(vm, node->r);
		}
		if (node->l){
			pn(vm, node->l);
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
		lat_object *ret = lat_str(vm, node->value->v.s);
		dbc(OP_STORESTR, 2, 0, ret);
		dbc(OP_GET, 2, 1, NULL);
		dbc(OP_MOV, 255, 2, NULL);
	}
	break;
	case NODE_ASSIGMENT: /*SET*/
	{
		pn(vm, node->l);
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

		lat_object *ret = lat_str(vm, node->r->value->v.s);
		dbc(OP_SET, 255, 1, ret);
	}
	break;
	case NODE_CHAR:
	{
		dbc(OP_STORECHAR, 255, node->value->v.c, NULL);
	}
	break;
	case NODE_INT:
	{
		lat_object *ret = lat_int(vm, node->value->v.i);
		dbc(OP_STOREINT, 255, 0, ret);
	}
	break;
	case NODE_DECIMAL:
	{
		dbc(OP_STOREDOUBLE, 255, 0, &(node->value->v.d));
	}
	break;
	case NODE_STRING:
	{
		lat_object *ret = lat_str(vm, node->value->v.s);
		dbc(OP_STORESTR, 255, 0, ret);
	}
	break;
	case NODE_BOOLEAN:
	{
		lat_object *ret = node->value->v.b ? vm->true_object : vm->false_object;
		dbc(OP_STOREBOOL, 255, 0, ret);
	}
	break;
	case NODE_IF:
	{
		nodeIf *nIf = ((nodeIf *)node);
		pn(vm, nIf->cond);
		dbc(OP_MOV, 2, 255, NULL);
		dbc(OP_MOV, 3, 255, NULL);
		dbc(OP_NOT, 2, 0, NULL);
		temp[0] = i;
		dbc(OP_NOP, 0, 0, NULL);
		pn(vm, nIf->entonces);
		bcode[temp[0]] = lat_bc(OP_JMPIF, i, 2, NULL);
		if (nIf->sino){
			temp[1] = i;
			dbc(OP_NOP, 0, 0, NULL);
			pn(vm, nIf->sino);
			bcode[temp[1]] = lat_bc(OP_JMPIF, i, 3, NULL);
		}
	}
	break;
	case NODE_WHILE:
	{
		temp[0] = i;
		pn(vm, node->l);
		dbc(OP_MOV, 2, 255, NULL);
		dbc(OP_NOT, 2, 0, NULL);
		temp[1] = i;
		dbc(OP_NOP, 0, 0, NULL);
		pn(vm, node->r);
		dbc(OP_JMP, temp[0], 0, NULL);
		bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
	}
	break;
	case NODE_DO:
	{
		pn(vm, node->r);
		temp[0] = i;
		pn(vm, node->l);
		dbc(OP_MOV, 2, 255, NULL);
		dbc(OP_NOT, 2, 0, NULL);
		temp[1] = i;
		dbc(OP_NOP, 0, 0, NULL);
		pn(vm, node->r);
		dbc(OP_JMP, temp[0], 0, NULL);
		bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
	}
	break;
	case NODE_CALL_FUNCTION:
	{
		if (node->r){
			pn(vm, node->r);
		}
		pn(vm, node->l);
		dbc(OP_CALL, 255, 0, NULL);
	}
	break;
	case NODE_RETURN:
	{
		pn(vm, node->l);
		dbc(OP_END, 0, 0, NULL);
	}
	break;
	case NODE_FUNC_ARGS: {
		if (node->r) {
			pn(vm, node->r);
			dbc(OP_PUSH, 255, 0, NULL);
		}
		if (node->l) {
			pn(vm, node->l);
			dbc(OP_PUSH, 255, 0, NULL);
		}
	}break;
	case NODE_PARAM_LIST:
	{
		if (node->l) {
			dbc(OP_LOCALNS, 1, 0, NULL);
			dbc(OP_POP, 2, 0, NULL);
			lat_object *ret = lat_str(vm, node->l->value->v.s);
			dbc(OP_SET, 2, 1, ret);
		}
		if (node->r) {
			pn(vm, node->r);
		}
	}
	break;
	case NODE_USER_FUNCTION:
	{
		function_bcode = (lat_bytecode *)malloc(sizeof(lat_bytecode) * 1024);
		fi = 0;
		if (node->l) {
			fpn(vm, node->l);
		}
		fpn(vm, node->r);
		dbc(OP_FN, 255, 0, function_bcode);
		function_bcode = NULL;
		fi = 0;
	}
	break;
	case NODE_LIST:
	{
		nested++;
		dbc(OP_STORELIST, nested, 0, NULL);
		if (node->l){
			pn(vm, node->l);
		}
		dbc(OP_MOV, 255, nested, NULL);
		nested--;
	}
	break;
	case NODE_LIST_BODY:
	{
		if (node->l) {
			pn(vm, node->l);
			dbc(OP_PUSHLIST, nested, 255, NULL);
		}
		if (node->r) {
			pn(vm, node->r);
		}
	}
	break;
	/*case NS:
	{
		dbc(OP_NS, 255, 0, NULL);
		pn(node->l);
		dbc(OP_ENDNS, 255, 0, NULL);
	}
	break;*/
	default:
		printf("nodetype:%i\n", node->nodetype);
		return 0;
	}
	//printf("i = %i\n", i);
	return i;
}
