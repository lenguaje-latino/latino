/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <stdbool.h>
#include "latino.h"
#include "ast.h"
#include "utils.h"
#include "vm.h"
#include "libmem.h"

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(vm, N) i = nodo_analizar(vm, N, bcode, i)
#define fdbc(I, A, B, M) funcion_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(vm, N) fi = nodo_analizar(vm, N, funcion_bcode, fi)

//se define para analizador sintactico (bison)
int yyerror(struct YYLTYPE *yylloc_param, void *scanner, struct ast **root,
            const char *s) {
  log_err("Linea %d: %s", (yylloc_param->first_line + 1), s);
  return 0;
}

ast *nodo_nuevo_operador(nodo_tipo nt, ast *l, ast *r) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  switch (nt) {
  case NODO_SUMA: {
    a->l = nodo_nuevo_identificador("+");
  } break;
  case NODO_MENOS_UNARIO:
  case NODO_RESTA: {
    a->l = nodo_nuevo_identificador("-");
  } break;
  case NODO_MULTIPLICACION: {
    a->l = nodo_nuevo_identificador("*");
  } break;
  case NODO_DIVISION: {
    a->l = nodo_nuevo_identificador("/");
  } break;
  case NODO_MODULO: {
    a->l = nodo_nuevo_identificador("%");
  } break;
  case NODO_MAYOR_IGUAL: {
    a->l = nodo_nuevo_identificador(">=");
  } break;
  case NODO_MAYOR_QUE: {
    a->l = nodo_nuevo_identificador(">");
  } break;
  case NODO_MENOR_IGUAL: {
    a->l = nodo_nuevo_identificador("<=");
  } break;
  case NODO_MENOR_QUE: {
    a->l = nodo_nuevo_identificador("<");
  } break;
  case NODO_DESIGUALDAD: {
    a->l = nodo_nuevo_identificador("!=");
  } break;
  case NODO_IGUALDAD: {
    a->l = nodo_nuevo_identificador("==");
  } break;
  default:
    break;
  }
  if (nt == NODO_MENOS_UNARIO) {
    a->r = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, nodo_nuevo_entero(0), l);
  } else {
    a->r = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, l, r);
  }
  a->tipo = NODO_FUNCION_LLAMADA;
  a->valor = NULL;
  return a;
}

ast *nodo_nuevo(nodo_tipo nt, ast *l, ast *r) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = nt;
  a->l = l;
  a->r = r;
  a->valor = NULL;
  return a;
}

ast *nodo_nuevo_entero(long i) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_ENTERO;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_ENTERO;
  val->v.i = i;
  a->valor = val;
  return a;
}

ast *nodo_nuevo_decimal(double d) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_DECIMAL;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_DECIMAL;
  val->v.d = d;
  a->valor = val;
  return a;
}

ast *nodo_nuevo_logico(int b) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_LOGICO;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_LOGICO;
  val->v.b = b;
  a->valor = val;
  return a;
}

ast *nodo_nuevo_caracter(char *c, size_t l) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_CARACTER;
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
  a->valor = val;
  return a;
}

ast *nodo_nuevo_cadena(const char *s) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_CADENA;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CADENA;
  val->v.s = parse_string(s, strlen(s));
  a->valor = val;
  return a;
}

ast *nodo_nuevo_constante(char *s, int num_linea, int num_columna) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_IDENTIFICADOR;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CADENA;
  val->v.s = strdup0(s);
  a->valor = val;
  a->valor->es_constante = true;
  a->valor->num_linea = num_linea;
  a->valor->num_columna = num_columna;
  return a;
}

ast *nodo_nuevo_identificador(const char *s) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_IDENTIFICADOR;
  nodo_valor *val = (nodo_valor*)lmalloc(sizeof(nodo_valor));
  val->t = VALOR_CADENA;
  val->v.s = strdup0(s);
  a->valor = val;
  a->valor->es_constante = false;
  return a;
}

ast *nodo_nuevo_asignacion(ast *v, ast *s) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_ASIGNACION;
  a->l = v;
  a->r = s;
  a->valor = NULL;
  return a;
}

ast *nodo_nuevo_si(ast *cond, ast *th, ast *el) {
  nodo_si *a = (nodo_si*)lmalloc(sizeof(nodo_si));
  a->tipo = NODO_SI;
  a->cond = cond;
  a->th = th;
  a->el = el;
  return (ast *)a;
}

ast *nodo_nuevo_mientras(ast *cond, ast *stmts) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_MIENTRAS;
  a->l = cond;
  a->r = stmts;
  a->valor = NULL;
  return a;
}

ast *nodo_nuevo_hacer(ast *cond, ast *stmts) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_HACER;
  a->l = cond;
  a->r = stmts;
  a->valor = NULL;
  return a;
}

ast *nodo_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_BLOQUE;
  a->l = nodo_nuevo_mientras(cond, nodo_nuevo(NODO_BLOQUE, inc, stmts));
  a->r = dec;
  a->valor = NULL;
  return a;
}

ast *nodo_nuevo_funcion(ast *s, ast *syms, ast *func) {
  ast *a = (ast*)lmalloc(sizeof(ast));
  a->tipo = NODO_ASIGNACION;
  a->l = nodo_nuevo(NODO_FUNCION_USUARIO, syms, func);
  a->r = s;
  a->valor = NULL;
  return a;
}

void nodo_liberar(ast *a) {
  if (a) {
    switch (a->tipo) {
    case NODO_BLOQUE:
    case NODO_LISTA_ASIGNAR_ELEMENTO:
      if (a->r)
        nodo_liberar(a->r);
      if (a->l)
        nodo_liberar(a->l);
      break;
    default:
      if (a->tipo)
        lfree(a->valor);
      lfree(a);
      break;
    }
  }
}

lat_object *nodo_analizar_arbol(lat_vm *vm, ast *tree) {
  lat_bytecode *bcode = (lat_bytecode *)lmalloc(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
  int i = nodo_analizar(vm, tree, bcode, 0);
  dbc(OP_END, 0, 0, NULL);
  nodo_liberar(tree);
  return definir_funcion(vm, bcode);
}

int nested = -1;

int nodo_analizar(lat_vm *vm, ast *node, lat_bytecode *bcode, int i) {
  int temp[8] = {0};
  lat_bytecode *funcion_bcode = NULL;
  int fi = 0;
  switch (node->tipo) {
  case NODO_BLOQUE: {
    if (node->r) {
      pn(vm, node->r);
    }
    if (node->l) {
      pn(vm, node->l);
    }
  } break;
  case NODO_IDENTIFICADOR: /*GET*/
  {
    /*if (node->l->r){
            pn(node->l->r);
            dbc(OP_MOV, 1, 255, NULL);
            }
            else{
            dbc(OP_LOCALNS, 1, 0, NULL);
            }*/
    dbc(OP_LOCALNS, 1, 0, NULL);
    lat_object *ret = lat_str(vm, node->valor->v.s);
    dbc(OP_STORESTR, 2, 0, ret);
    dbc(OP_GET, 2, 1, NULL);
    dbc(OP_MOV, 255, 2, NULL);
  } break;
  case NODO_ASIGNACION: /*SET*/
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
    // lat_object *ret = lat_clone_object(vm, lat_str(vm, node->r->tipo->v.s));
    lat_object *ret = lat_str(vm, node->r->valor->v.s);
    if (ret->num_declared < 0) {
      ret->num_declared = 0;
    }
    ret->es_constante = node->r->valor->es_constante;
    ret->num_declared++;
    if (ret->es_constante && ret->num_declared > 1) {
      log_err("Linea %d: %s", (node->r->valor->num_linea + 1),  "Intento de asignar un nuevo valor a una constante ");
    }
    dbc(OP_LOCALNS, 1, 0, NULL);
    dbc(OP_POP, 255, 0, NULL);
    dbc(OP_SET, 255, 1, ret);
  } break;
  case NODO_INCREMENTO: {
    pn(vm, node->l);
    dbc(OP_INC, 255, 0, NULL);
  } break;
  case NODO_DECREMENTO: {
    pn(vm, node->l);
    dbc(OP_DEC, 255, 0, NULL);
  } break;
  case NODO_CARACTER: {
    lat_object *ret = lat_char(vm, node->valor->v.c);
    // lat_mark_object(ret, 3);
    dbc(OP_STORECHAR, 255, 0, ret);
  } break;
  case NODO_ENTERO: {
    lat_object *ret = lat_int(vm, node->valor->v.i);
    // lat_mark_object(ret, 3);
    dbc(OP_STOREINT, 255, 0, ret);
  } break;
  case NODO_DECIMAL: {
    lat_object *ret = lat_double(vm, node->valor->v.d);
    // lat_mark_object(ret, 3);
    dbc(OP_STOREDOUBLE, 255, 0, ret);
  } break;
  case NODO_CADENA: {
    lat_object *ret = lat_str(vm, node->valor->v.s);
    dbc(OP_STORESTR, 255, 0, ret);
  } break;
  case NODO_LOGICO: {
    lat_object *ret = node->valor->v.b ? vm->true_object : vm->false_object;
    dbc(OP_STOREBOOL, 255, 0, ret);
  } break;
  case NODO_SI: {
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
  case NODO_MIENTRAS: {
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
  case NODO_HACER: {
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
  case NODO_FUNCION_LLAMADA: {
    if (node->r) {
      pn(vm, node->r);
    }
    pn(vm, node->l);
    dbc(OP_CALL, 255, 0, NULL);
  } break;
  case NODO_RETORNO: {
    pn(vm, node->l);
    dbc(OP_END, 0, 0, NULL);
  } break;
  case NODO_FUNCION_ARGUMENTOS: {
    if (node->l) {
      pn(vm, node->l);
      dbc(OP_PUSH, 255, 0, NULL);
    }
    if (node->r) {
      pn(vm, node->r);
      //Soporte para recursion NODO_FUNCION_LLAMADA
      if (node->r->valor || node->r->tipo == NODO_FUNCION_LLAMADA) {
        dbc(OP_PUSH, 255, 0, NULL);
      }
    }
  } break;
  case NODO_LISTA_PARAMETROS: {
    if (node->l) {
      dbc(OP_LOCALNS, 1, 0, NULL);
      dbc(OP_POP, 2, 0, NULL);
      lat_object *ret = lat_clone_object(vm, lat_str(vm, node->l->valor->v.s));
      dbc(OP_SET, 2, 1, ret);
    }
    if (node->r) {
      pn(vm, node->r);
    }
  } break;
  case NODO_FUNCION_USUARIO: {
    funcion_bcode =
        (lat_bytecode *)lmalloc(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    fi = 0;
    if (node->l) {
      fpn(vm, node->l);
    }
    fpn(vm, node->r);
    dbc(OP_FN, 255, 0, funcion_bcode);
    funcion_bcode = NULL;
    fi = 0;
  } break;
  case NODO_LISTA: {
    nested++;
    dbc(OP_STORELIST, nested, 0, NULL);
    if (node->l) {
      pn(vm, node->l);
    }
    dbc(OP_MOV, 255, nested, NULL);
    nested--;
  } break;
  case NODO_LISTA_ASIGNAR_ELEMENTO: {
    if (node->l) {
      pn(vm, node->l);
      dbc(OP_PUSHLIST, nested, 255, NULL);
    }
    if (node->r) {
      pn(vm, node->r);
    }
  } break;
  case NODO_LISTA_OBTENER_ELEMENTO:{
    if (node->l){
      pn(vm, node->l);
      dbc(OP_POPLIST, nested, 255, NULL);
    }
    if (node->r){
      pn(vm, node->r);
      dbc(OP_LISTGETITEM, nested, 255, NULL);
    }
  } break;
  case NODO_DICCIONARIO: {
    nested++;
    dbc(OP_STOREDICT, nested, 0, NULL);
    if (node->l) {
      pn(vm, node->l);
    }
    dbc(OP_MOV, 255, nested, NULL);
    nested--;
  } break;
  case NODO_DICCIONARIO_ELEMENTOS: {
    if (node->l) {
      pn(vm, node->l);
      dbc(OP_PUSHDICT, nested, 255, NULL);
    }
    if (node->r) {
      pn(vm, node->r);
    }
  } break;
  case NODO_DICCIONARIO_ELEMENTO:{
    pn(vm, node->l);
    dbc(OP_PUSH, 255, 0, NULL);
    lat_object *ret = lat_str(vm, node->r->valor->v.s);
    if (ret->num_declared < 0) {
      ret->num_declared = 0;
    }
    ret->es_constante = node->r->valor->es_constante;
    ret->num_declared++;
    if (ret->es_constante && ret->num_declared > 1) {
      log_err("Linea %d: %s", (node->r->valor->num_linea + 1),  "Intento de asignar un nuevo valor a una constante ");
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
    printf("nodo_tipo:%i\n", node->tipo);
    return 0;
  }
  // printf("i = %i\n", i);
  return i;
}
