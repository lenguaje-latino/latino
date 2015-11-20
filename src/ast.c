#include "latino.h"
#include "ast.h"
#include "utils.h"
#include "vm.h"
#include "libmem.h"

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(vm, N) i = ast_parse_node(vm, N, bcode, i)
#define fdbc(I, A, B, M) function_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(vm, N) fi = ast_parse_node(vm, N, function_bcode, fi)

int yyerror(struct YYLTYPE* yylloc_param, void* scanner, struct ast** root, const char* s)
{
    log_err("%s at line %d", s, (yylloc_param->first_line + 1));
    return 0;
}

ast* ast_new_op(ast_node_type node_type, ast* l, ast* r)
{
    ast* a = lmalloc(sizeof(ast));
    switch (node_type) {
    case NODE_ADD: {
        a->l = ast_new_identifier("+");
    } break;
    case NODE_UNARY_MINUS:
    case NODE_SUB: {
        a->l = ast_new_identifier("-");
    } break;
    case NODE_MULT: {
        a->l = ast_new_identifier("*");
    } break;
    case NODE_DIV: {
        a->l = ast_new_identifier("/");
    } break;
    case NODE_MOD: {
        a->l = ast_new_identifier("%");
    } break;
    case NODE_GE: {
        a->l = ast_new_identifier(">=");
    } break;
    case NODE_GT: {
        a->l = ast_new_identifier(">");
    } break;
    case NODE_LE: {
        a->l = ast_new_identifier("<=");
    } break;
    case NODE_LT: {
        a->l = ast_new_identifier("<");
    } break;
    case NODE_NEQ: {
        a->l = ast_new_identifier("!=");
    } break;
    case NODE_EQ: {
        a->l = ast_new_identifier("==");
    } break;
    default:
        break;
    }
    if (node_type == NODE_UNARY_MINUS) {
        a->r = ast_new_node(NODE_FUNC_ARGS, ast_new_integer(0), l);
    } else {
        a->r = ast_new_node(NODE_FUNC_ARGS, l, r);
    }
    a->node_type = NODE_CALL_FUNCTION;
    a->value = NULL;
    return a;
}

ast* ast_new_node(ast_node_type node_type, ast* l, ast* r)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = node_type;
    a->l = l;
    a->r = r;
    a->value = NULL;
    return a;
}

ast* ast_new_integer(long i)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_INT;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_INT;
    val->v.i = i;
    a->value = val;
    return a;
}

ast* ast_new_decimal(double d)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_DECIMAL;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_DOUBLE;
    val->v.d = d;
    a->value = val;
    return a;
}

ast* ast_new_bool(int b)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_BOOLEAN;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_BOOL;
    val->v.b = b;
    a->value = val;
    return a;
}

ast* ast_new_char(char* c, size_t l)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_CHAR;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_CHAR;
    char tmp = ' ';
    switch (c[0]) {
    case '\\': {
        switch (c[1]) {
        case 'a': {
            tmp = '\a';
        } break;
        case 'b': {
            tmp = '\b';
        } break;
        case 'f': {
            tmp = '\f';
        } break;
        case 'n': {
            tmp = '\n';
        } break;
        case 'r': {
            tmp = '\r';
        } break;
        case 't': {
            tmp = '\t';
        } break;
        case 'v': {
            tmp = '\v';
        } break;
        default:
            tmp = c[0];
            break;
        }
    } break;
    default:
        tmp = c[0];
        break;
    }
    val->v.c = tmp;
    a->value = val;
    return a;
}

ast* ast_new_string(const char* s)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_STRING;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_STRING;
    val->v.s = parse_string(s, strlen(s));
    a->value = val;
    return a;
}

ast* ast_new_constant(char* s)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_SYMBOL;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_STRING;
    val->v.s = strdup0(s);
    a->value = val;
    a->value->cst = true;
    return a;
}

ast* ast_new_identifier(char* s)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_SYMBOL;
    ast_value* val = lmalloc(sizeof(ast_value));
    val->t = VALUE_STRING;
    val->v.s = strdup0(s);
    a->value = val;
    return a;
}

ast* ast_new_assignment(ast* v, ast* s)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_ASSIGMENT;
    a->l = v;
    a->r = s;
    a->value = NULL;
    return a;
}

ast* ast_new_node_if(ast* cond, ast* th, ast* el)
{
    ast_node_if* a = lmalloc(sizeof(ast_node_if));
    a->node_type = NODE_IF;
    a->cond = cond;
    a->th = th;
    a->el = el;
    return (ast*)a;
}

/*
ast *newSwitch(ast_node_type node_type, ast *cond, ast *th, ast *el)
{
    ast_node_if *a = malloc(sizeof(ast_node_if));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->node_type = node_type;
    a->cond = cond;
    a->th = th;
    a->el = el;
    return (ast *)a;
}

ast *newCase(ast_node_type node_type, ast *cond, ast *th, ast *el)
{
    ast_node_if *a = malloc(sizeof(ast_node_if));
    if (!a) {
        log_err("Memoria agotada\n");
        exit(0);
    }
    a->node_type = node_type;
    a->cond = cond;
    a->th = th;
    a->el = el;
    return (ast *)a;
}
*/

ast* ast_new_node_while(ast* cond, ast* stmts)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_WHILE;
    a->l = cond;
    a->r = stmts;
    a->value = NULL;
    return a;
}

ast* ast_new_node_do(ast* cond, ast* stmts)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_DO;
    a->l = cond;
    a->r = stmts;
    a->value = NULL;
    return a;
}

ast* ast_new_node_for(ast* dec, ast* cond, ast* inc, ast* stmts)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_BLOCK;
    a->l = ast_new_node_while(cond, ast_new_node(NODE_BLOCK, inc, stmts));
    a->r = dec;
    a->value = NULL;
    return a;
}

ast* ast_new_node_function(ast* s, ast* syms, ast* func)
{
    ast* a = lmalloc(sizeof(ast));
    a->node_type = NODE_ASSIGMENT;
    a->l = ast_new_node(NODE_USER_FUNCTION, syms, func);
    a->r = s;
    a->value = NULL;
    return a;
}

void ast_tree_free(ast* a)
{
    if (a) {
        switch (a->node_type) {
        case NODE_BLOCK:
        case NODE_LIST_BODY:
            if (a->r)
                ast_tree_free(a->r);
            if (a->l)
                ast_tree_free(a->l);
            break;
        default:
            if (a->value)
                lfree(a->value);
            lfree(a);
            break;
        }
    }
}

lat_object* ast_parse_tree(lat_vm* vm, ast* tree)
{
    lat_bytecode* bcode = (lat_bytecode*)lmalloc(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    int i = ast_parse_node(vm, tree, bcode, 0);
    dbc(OP_END, 0, 0, NULL);
    ast_tree_free(tree);
    return lat_define_function(vm, bcode);
}

int nested = -1;

int ast_parse_node(lat_vm* vm, ast* node, lat_bytecode* bcode, int i)
{
    int temp[8] = { 0 };
    lat_bytecode* function_bcode = NULL;
    int fi = 0;
    switch (node->node_type) {
    case NODE_BLOCK: {
        if (node->r) {
            pn(vm, node->r);
        }
        if (node->l) {
            pn(vm, node->l);
        }
    } break;
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
        lat_object* ret = lat_str(vm, node->value->v.s);
        dbc(OP_STORESTR, 2, 0, ret);
        dbc(OP_GET, 2, 1, NULL);
        dbc(OP_MOV, 255, 2, NULL);
    } break;
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
        //lat_object *ret = lat_clone_object(vm, lat_str(vm, node->r->value->v.s));
        lat_object* ret = lat_str(vm, node->r->value->v.s);
        if (ret->num_declared < 0) {
            ret->num_declared = 0;
        }
        ret->is_constant = node->r->value->cst;
        ret->num_declared++;
        if (ret->is_constant && ret->num_declared > 1) {
            log_err("Intento de asignar un nuevo valor a una constante");
        }
        dbc(OP_LOCALNS, 1, 0, NULL);
        dbc(OP_POP, 255, 0, NULL);
        dbc(OP_SET, 255, 1, ret);
    } break;
    case NODE_INC: {
        pn(vm, node->l);
        dbc(OP_INC, 255, 0, NULL);
    } break;
    case NODE_DEC: {
        pn(vm, node->l);
        dbc(OP_DEC, 255, 0, NULL);
    } break;
    case NODE_CHAR: {
        lat_object* ret = lat_char(vm, node->value->v.c);
        //lat_mark_object(ret, 3);
        dbc(OP_STORECHAR, 255, 0, ret);
    } break;
    case NODE_INT: {
        lat_object* ret = lat_int(vm, node->value->v.i);
        //lat_mark_object(ret, 3);
        dbc(OP_STOREINT, 255, 0, ret);
    } break;
    case NODE_DECIMAL: {
        lat_object* ret = lat_double(vm, node->value->v.d);
        //lat_mark_object(ret, 3);
        dbc(OP_STOREDOUBLE, 255, 0, ret);
    } break;
    case NODE_STRING: {
        lat_object* ret = lat_str(vm, node->value->v.s);
        dbc(OP_STORESTR, 255, 0, ret);
    } break;
    case NODE_BOOLEAN: {
        lat_object* ret = node->value->v.b ? vm->true_object : vm->false_object;
        dbc(OP_STOREBOOL, 255, 0, ret);
    } break;
    case NODE_IF: {
        ast_node_if* nIf = ((ast_node_if*)node);
        pn(vm, nIf->cond);
        dbc(OP_MOV, 2, 255, NULL);
        dbc(OP_MOV, 3, 255, NULL);
        dbc(OP_NOT, 2, 0, NULL);
        temp[0] = i;
        dbc(OP_NOP, 0, 0, NULL);
        pn(vm, nIf->th);
        bcode[temp[0]] = lat_bc(OP_JMPIF, i, 2, NULL);
        if (nIf->el) {
            temp[1] = i;
            dbc(OP_NOP, 0, 0, NULL);
            pn(vm, nIf->el);
            bcode[temp[1]] = lat_bc(OP_JMPIF, i, 3, NULL);
        }
    } break;
    case NODE_WHILE: {
        temp[0] = i;
        pn(vm, node->l);
        dbc(OP_MOV, 2, 255, NULL);
        dbc(OP_NOT, 2, 0, NULL);
        temp[1] = i;
        dbc(OP_NOP, 0, 0, NULL);
        pn(vm, node->r);
        dbc(OP_JMP, temp[0], 0, NULL);
        bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
    } break;
    case NODE_DO: {
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
    } break;
    case NODE_CALL_FUNCTION: {
        if (node->r) {
            pn(vm, node->r);
        }
        pn(vm, node->l);
        dbc(OP_CALL, 255, 0, NULL);
    } break;
    case NODE_RETURN: {
        pn(vm, node->l);
        dbc(OP_END, 0, 0, NULL);
    } break;
    case NODE_FUNC_ARGS: {
        if (node->r) {
            pn(vm, node->r);
            dbc(OP_PUSH, 255, 0, NULL);
        }
        if (node->l) {
            pn(vm, node->l);
            dbc(OP_PUSH, 255, 0, NULL);
        }
    } break;
    case NODE_PARAM_LIST: {
        if (node->l) {
            dbc(OP_LOCALNS, 1, 0, NULL);
            dbc(OP_POP, 2, 0, NULL);
            lat_object* ret = lat_clone_object(vm, lat_str(vm, node->l->value->v.s));
            dbc(OP_SET, 2, 1, ret);
        }
        if (node->r) {
            pn(vm, node->r);
        }
    } break;
    case NODE_USER_FUNCTION: {
        function_bcode = (lat_bytecode*)lmalloc(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
        fi = 0;
        if (node->l) {
            fpn(vm, node->l);
        }
        fpn(vm, node->r);
        dbc(OP_FN, 255, 0, function_bcode);
        function_bcode = NULL;
        fi = 0;
    } break;
    case NODE_LIST: {
        nested++;
        dbc(OP_STORELIST, nested, 0, NULL);
        if (node->l) {
            pn(vm, node->l);
        }
        dbc(OP_MOV, 255, nested, NULL);
        nested--;
    } break;
    case NODE_LIST_BODY: {
        if (node->l) {
            pn(vm, node->l);
            dbc(OP_PUSHLIST, nested, 255, NULL);
        }
        if (node->r) {
            pn(vm, node->r);
        }
    } break;
    /*case NS:
    {
        dbc(OP_NS, 255, 0, NULL);
        pn(node->l);
        dbc(OP_ENDNS, 255, 0, NULL);
    }
    break;*/
    default:
        printf("ast_node_type:%i\n", node->node_type);
        return 0;
    }
    //printf("i = %i\n", i);
    return i;
}
