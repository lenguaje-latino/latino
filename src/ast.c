#include <stdbool.h>
#include "latino.h"
#include "ast.h"
#include "utils.h"
#include "vm.h"
#include "libmem.h"

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(vm, N) i = nodo_analizar(vm, N, bcode, i)
#define fdbc(I, A, B, M) function_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(vm, N) fi = nodo_analizar(vm, N, function_bcode, fi)

int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
  log_err("Linea %d: %s", (yylloc_param->first_line + 1), s);
  return 0;
}

ast *ast_new_op(nodo_tipo node_type, ast *l, ast *r) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  switch (node_type) {
  case NODE_ADD: {
    a->l = nodo_nuevo_identificador("+");
  } break;
  case NODE_UNARY_MINUS:
  case NODE_SUB: {
    a->l = nodo_nuevo_identificador("-");
  } break;
  case NODE_MULT: {
    a->l = nodo_nuevo_identificador("*");
  } break;
  case NODE_DIV: {
    a->l = nodo_nuevo_identificador("/");
  } break;
  case NODE_MOD: {
    a->l = nodo_nuevo_identificador("%");
  } break;
  case NODE_GE: {
    a->l = nodo_nuevo_identificador(">=");
  } break;
  case NODE_GT: {
    a->l = nodo_nuevo_identificador(">");
  } break;
  case NODE_LE: {
    a->l = nodo_nuevo_identificador("<=");
  } break;
  case NODE_LT: {
    a->l = nodo_nuevo_identificador("<");
  } break;
  case NODE_NEQ: {
    a->l = nodo_nuevo_identificador("!=");
  } break;
  case NODE_EQ: {
    a->l = nodo_nuevo_identificador("==");
  } break;
  default:
    break;
  }
  if (node_type == NODE_UNARY_MINUS) {
    a->r = nodo_nuevo(NODE_FUNC_ARGS, nodo_nuevo_entero(0), l);
  } else {
    a->r = nodo_nuevo(NODE_FUNC_ARGS, l, r);
  }
  a->node_type = NODE_CALL_FUNCTION;
  a->value = NULL;
  return a;
}

ast *nodo_nuevo(nodo_tipo node_type, ast *l, ast *r) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = node_type;
  a->l = l;
  a->r = r;
  a->value = NULL;
  return a;
}

ast *nodo_nuevo_entero(long i) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_INT;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_ENTERO;
  val->v.i = i;
  a->value = val;
  return a;
}

ast *nodo_nuevo_decimal(double d) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_DECIMAL;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_DECIMAL;
  val->v.d = d;
  a->value = val;
  return a;
}

ast *nodo_nuevo_logico(int b) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_BOOLEAN;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_LOGICO;
  val->v.b = b;
  a->value = val;
  return a;
}

ast *nodo_nuevo_caracter(char *c, size_t l) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_CHAR;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CARACTER;
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

ast *nodo_nuevo_cadena(const char *s) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_STRING;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CADENA;
  val->v.s = parse_string(s, strlen(s));
  a->value = val;
  return a;
}

ast *nodo_nuevo_constante(char *s, int num_linea, int num_columna) {
  // printf("new_constant in line %i, :%s\n", yylineno, s);
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_SYMBOL;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CADENA;
  val->v.s = strdup0(s);
  a->value = val;
  a->value->es_constante = true;
  a->value->num_linea = num_linea;
  a->value->num_columna = num_columna;
  return a;
}

ast *nodo_nuevo_identificador(char *s) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_SYMBOL;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CADENA;
  val->v.s = strdup0(s);
  a->value = val;
  a->value->es_constante = false;
  return a;
}

ast *nodo_nuevo_asignacion(ast *v, ast *s) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_ASSIGMENT;
  a->l = v;
  a->r = s;
  a->value = NULL;
  return a;
}

ast *nodo_nuevo_si(ast *cond, ast *th, ast *el) {
  nodo_si *a = (nodo_si*)lmalloc(sizeof(nodo_si));
  a->node_type = NODE_IF;
  a->cond = cond;
  a->th = th;
  a->el = el;
  return (ast *)a;
}

/*
ast *newSwitch(nodo_tipo node_type, ast *cond, ast *th, ast *el)
{
    nodo_si *a = malloc(sizeof(nodo_si));
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

ast *newCase(nodo_tipo node_type, ast *cond, ast *th, ast *el)
{
    nodo_si *a = malloc(sizeof(nodo_si));
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

ast *nodo_nuevo_mientras(ast *cond, ast *stmts) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_WHILE;
  a->l = cond;
  a->r = stmts;
  a->value = NULL;
  return a;
}

ast *nodo_nuevo_hacer(ast *cond, ast *stmts) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_DO;
  a->l = cond;
  a->r = stmts;
  a->value = NULL;
  return a;
}

ast *nodo_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_BLOCK;
  a->l = nodo_nuevo_mientras(cond, nodo_nuevo(NODE_BLOCK, inc, stmts));
  a->r = dec;
  a->value = NULL;
  return a;
}

ast *nodo_nuevo_function(ast *s, ast *syms, ast *func) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->node_type = NODE_ASSIGMENT;
  a->l = nodo_nuevo(NODE_USER_FUNCTION, syms, func);
  a->r = s;
  a->value = NULL;
  return a;
}

void nodo_liberar(ast *a) {
  if (a) {
    switch (a->node_type) {
    case NODE_BLOCK:
    case NODE_LIST_SET_ITEM:
      if (a->r)
        nodo_liberar(a->r);
      if (a->l)
        nodo_liberar(a->l);
      break;
    default:
      if (a->value)
        lfree(a->value);
      lfree(a);
      break;
    }
  }
}

lat_object *nodo_analizar_arbol(lat_vm *vm, ast *tree) {
  lat_bytecode *bcode =
      (lat_bytecode *)lmalloc(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
  int i = nodo_analizar(vm, tree, bcode, 0);
  dbc(OP_END, 0, 0, NULL);
  nodo_liberar(tree);
  return lat_define_function(vm, bcode);
}

int nested = -1;

int nodo_analizar(lat_vm *vm, ast *node, lat_bytecode *bcode, int i) {
  int temp[8] = {0};
  lat_bytecode *function_bcode = NULL;
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
    lat_object *ret = lat_str(vm, node->value->v.s);
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
    // lat_object *ret = lat_clone_object(vm, lat_str(vm, node->r->value->v.s));
    lat_object *ret = lat_str(vm, node->r->value->v.s);
    if (ret->num_declared < 0) {
      ret->num_declared = 0;
    }
    ret->es_constante = node->r->value->es_constante;
    ret->num_declared++;
    if (ret->es_constante && ret->num_declared > 1) {
      log_err("Linea %d: %s", (node->r->value->num_linea + 1),  "Intento de asignar un nuevo valor a una constante ");
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
    lat_object *ret = lat_char(vm, node->value->v.c);
    // lat_mark_object(ret, 3);
    dbc(OP_STORECHAR, 255, 0, ret);
  } break;
  case NODE_INT: {
    lat_object *ret = lat_int(vm, node->value->v.i);
    // lat_mark_object(ret, 3);
    dbc(OP_STOREINT, 255, 0, ret);
  } break;
  case NODE_DECIMAL: {
    lat_object *ret = lat_double(vm, node->value->v.d);
    // lat_mark_object(ret, 3);
    dbc(OP_STOREDOUBLE, 255, 0, ret);
  } break;
  case NODE_STRING: {
    lat_object *ret = lat_str(vm, node->value->v.s);
    dbc(OP_STORESTR, 255, 0, ret);
  } break;
  case NODE_BOOLEAN: {
    lat_object *ret = node->value->v.b ? vm->true_object : vm->false_object;
    dbc(OP_STOREBOOL, 255, 0, ret);
  } break;
  case NODE_IF: {
    nodo_si *nIf = ((nodo_si *)node);
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
    if (node->l) {
      pn(vm, node->l);
      dbc(OP_PUSH, 255, 0, NULL);
    }
    if (node->r) {
      pn(vm, node->r);
      //Soporte para recursion NODE_CALL_FUNCTION
      if (node->r->value || node->r->node_type == NODE_CALL_FUNCTION) {
        dbc(OP_PUSH, 255, 0, NULL);
      }
    }
  } break;
  case NODE_PARAM_LIST: {
    if (node->l) {
      dbc(OP_LOCALNS, 1, 0, NULL);
      dbc(OP_POP, 2, 0, NULL);
      lat_object *ret = lat_clone_object(vm, lat_str(vm, node->l->value->v.s));
      dbc(OP_SET, 2, 1, ret);
    }
    if (node->r) {
      pn(vm, node->r);
    }
  } break;
  case NODE_USER_FUNCTION: {
    function_bcode =
        (lat_bytecode *)lmalloc(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
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
  case NODE_LIST_SET_ITEM: {
    if (node->l) {
      pn(vm, node->l);
      dbc(OP_PUSHLIST, nested, 255, NULL);
    }
    if (node->r) {
      pn(vm, node->r);
    }
  } break;
  case NODE_LIST_GET_ITEM:{
    if (node->l){
      pn(vm, node->l);
      dbc(OP_POPLIST, nested, 255, NULL);
    }
    if (node->r){
      pn(vm, node->r);
      dbc(OP_LISTGETITEM, nested, 255, NULL);
    }
  } break;
  case NODE_DICT: {
    nested++;
    dbc(OP_STOREDICT, nested, 0, NULL);
    if (node->l) {
      pn(vm, node->l);
    }
    dbc(OP_MOV, 255, nested, NULL);
    nested--;
  } break;
  case NODE_DICT_ITEMS: {
    if (node->l) {
      pn(vm, node->l);
      dbc(OP_PUSHDICT, nested, 255, NULL);
    }
    if (node->r) {
      pn(vm, node->r);
    }
  } break;
  case NODE_DICT_ITEM:{
    pn(vm, node->l);
    dbc(OP_PUSH, 255, 0, NULL);
    /*if (node->r) {
            pn(node->r);
            dbc(OP_MOV, 1, 255, NULL);
            }
            else {
            dbc(OP_LOCALNS, 1, 0, NULL);
            }*/
    // lat_object *ret = lat_clone_object(vm, lat_str(vm, node->r->value->v.s));
    lat_object *ret = lat_str(vm, node->r->value->v.s);
    if (ret->num_declared < 0) {
      ret->num_declared = 0;
    }
    ret->es_constante = node->r->value->es_constante;
    ret->num_declared++;
    if (ret->es_constante && ret->num_declared > 1) {
      log_err("Linea %d: %s", (node->r->value->num_linea + 1),  "Intento de asignar un nuevo valor a una constante ");
    }
    dbc(OP_LOCALNS, 1, 0, NULL);
    dbc(OP_POP, 255, 0, NULL);
    dbc(OP_SET, 255, 1, ret);
  }break;
  /*case NS:
    {
        dbc(OP_NS, 255, 0, NULL);
        pn(node->l);
        dbc(OP_ENDNS, 255, 0, NULL);
    }
    break;*/
  default:
    printf("nodo_tipo:%i\n", node->node_type);
    return 0;
  }
  // printf("i = %i\n", i);
  return i;
}
