/*
The MIT License (MIT)

Copyright (c) 2015 - 2016. Latino

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

#include <math.h>
#include <stdbool.h>

#include "latast.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"
#include "latobj.h"

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(vm, N) i = nodo_analizar(vm, N, bcode, i)
#define fdbc(I, A, B, M) funcion_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(vm, N) fi = nodo_analizar(vm, N, funcion_bcode, fi)

ast *ast_nuevo(nodo_tipo nt, ast *l, ast *r) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = nt;
  a->izq = l;
  a->der = r;
  a->valor = NULL;
  return a;
}

ast *ast_nuevo_logico(int b, int num_linea, int num_columna) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_VALOR;
  nodo_valor *val = (nodo_valor *)__memoria_asignar(NULL, sizeof(nodo_valor));
  val->tipo = VALOR_LOGICO;
  val->val.logico = b;
  a->valor = val;
  a->num_linea = num_linea;
  a->num_columna = num_columna;
  return a;
}

ast *ast_nuevo_nulo(void *nulo, int num_linea, int num_columna) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_VALOR;
  nodo_valor *val = (nodo_valor *)__memoria_asignar(NULL, sizeof(nodo_valor));
  val->tipo = VALOR_NULO;
  val->val.cadena = nulo;
  a->valor = val;
  a->num_linea = num_linea;
  a->num_columna = num_columna;
  return a;
}

ast *ast_nuevo_numerico(double d, int num_linea, int num_columna) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_VALOR;
  nodo_valor *val = (nodo_valor *)__memoria_asignar(NULL, sizeof(nodo_valor));
  val->tipo = VALOR_NUMERICO;
  val->val.numerico = d;
  a->valor = val;
  a->num_linea = num_linea;
  a->num_columna = num_columna;
  return a;
}

ast *ast_nuevo_cadena(const char *s, int num_linea, int num_columna) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_VALOR;
  nodo_valor *val = (nodo_valor *)__memoria_asignar(NULL, sizeof(nodo_valor));
  val->tipo = VALOR_CADENA;
  val->val.cadena = strdup(s);
  a->valor = val;
  a->num_linea = num_linea;
  a->num_columna = num_columna;
  return a;
}

ast *ast_nuevo_identificador(const char *s, int num_linea, int num_columna,
                             bool es_constante) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_IDENTIFICADOR;
  nodo_valor *val = (nodo_valor *)__memoria_asignar(NULL, sizeof(nodo_valor));
  val->tipo = VALOR_CADENA;
  val->val.cadena = strdup(s);
  val->es_constante = es_constante;
  a->valor = val;
  a->num_linea = num_linea;
  a->num_columna = num_columna;
  return a;
}

ast *ast_nuevo_asignacion(ast *val, ast *sim) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_ASIGNACION;
  a->izq = val;
  a->der = sim;
  a->valor = NULL;
  return a;
}

ast *ast_nuevo_asignacion_lista_elem(ast *exp, ast *id, ast *pos) {
  nodo_lista_elem *a =
      (nodo_lista_elem *)__memoria_asignar(NULL, sizeof(nodo_lista_elem));
  a->tipo = NODO_LISTA_ASIGNAR_ELEMENTO;
  a->expresion = exp;
  a->identificador = id;
  a->posicion = pos;
  return (ast *)a;
}

ast *ast_nuevo_si(ast *cond, ast *th, ast *el) {
  nodo_si *a = (nodo_si *)__memoria_asignar(NULL, sizeof(nodo_si));
  a->tipo = NODO_SI;
  a->condicion = cond;
  a->entonces = th;
  a->_sino = el;
  return (ast *)a;
}

ast *ast_nuevo_mientras(ast *cond, ast *stmts) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_MIENTRAS;
  a->izq = cond;
  a->der = stmts;
  a->valor = NULL;
  return a;
}

ast *ast_nuevo_hacer(ast *cond, ast *stmts) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_REPETIR;
  a->izq = cond;
  a->der = stmts;
  a->valor = NULL;
  return a;
}

ast *ast_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts) {
  ast *a = (ast *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_BLOQUE;
  a->izq = dec;
  a->der = ast_nuevo_mientras(cond, ast_nuevo(NODO_BLOQUE, stmts, inc));
  a->valor = NULL;
  return a;
}

ast *ast_nuevo_funcion(ast *nombre, ast *parametros, ast *sentencias) {
  nodo_funcion *a = (nodo_funcion *)__memoria_asignar(NULL, sizeof(ast));
  a->tipo = NODO_FUNCION_USUARIO;
  a->nombre = nombre;
  a->parametros = parametros;
  a->sentencias = sentencias;
  return (ast *)a;
}

ast *ast_reducir_constantes(nodo_tipo nt, ast *lhs, ast *rhs) {
  return ast_nuevo(nt, lhs, rhs);
}

void ast_liberar(ast *a) {
  if (a) {
    switch (a->tipo) {
    case NODO_SI: {
      nodo_si *nsi = (nodo_si *)a;
      ast_liberar(nsi->condicion);
      ast_liberar(nsi->entonces);
      if (nsi->_sino)
        ast_liberar(nsi->_sino);
      break;
    }
    case NODO_FUNCION_USUARIO: {
      nodo_funcion *fun = (nodo_funcion *)a;
      if (fun->parametros)
        ast_liberar(fun->parametros);
      if (fun->sentencias)
        ast_liberar(fun->sentencias);
      ast_liberar(fun->nombre);
      break;
    }
    case NODO_LISTA_ASIGNAR_ELEMENTO: {
      nodo_lista_elem *nelem = (nodo_lista_elem *)a;
      ast_liberar(nelem->expresion);
      ast_liberar(nelem->identificador);
      ast_liberar(nelem->posicion);
      break;
    }
    case NODO_IDENTIFICADOR:
    case NODO_VALOR:
      if (a->valor->tipo == VALOR_CADENA) {
        __memoria_liberar(NULL, a->valor->val.cadena);
      }
      __memoria_liberar(NULL, a->valor);
      break;
    default:
      ast_liberar(a->izq);
      ast_liberar(a->der);
    }
    __memoria_liberar(NULL, a);
  }
}

ast *__transformar_casos(ast *casos, ast *cond_izq) {
  if (casos == NULL) {
    return NULL;
  }
  ast *caso = casos->izq;
  ast *cond = NULL;
  if (caso->tipo == NODO_CASO) {
    cond = ast_nuevo(NODO_IGUALDAD, cond_izq, caso->izq);
  }
  if (caso->tipo == NODO_DEFECTO) {
    cond = ast_nuevo(NODO_IGUALDAD, cond_izq, cond_izq);
  }
  ast *nSi = ast_nuevo_si(cond, caso->der,
                          ((ast *)__transformar_casos(casos->der, cond_izq)));
  return nSi;
}

static ast *__transformar_elegir(ast *nodo_elegir) {
  ast *cond_izq = nodo_elegir->izq;
  ast *casos = nodo_elegir->der;
  ast *nSi = NULL;
  nSi = __transformar_casos(casos, cond_izq);
  return nSi;
}

static int __contar_num_parargs(ast *node, nodo_tipo nt) {
  ast *tmp;
  int num_params = 0;
  if (node) {
    if (node->tipo == nt) {
      tmp = node;
      while (tmp->der != NULL && tmp->der->tipo == nt) {
        tmp = tmp->der;
        num_params++;
      }
      if (tmp->izq->tipo) {
        num_params++;
      }
    }
  }
  return num_params;
}

static int nodo_analizar(lat_mv *mv, ast *node, lat_bytecode *bcode, int i) {
  int temp[4] = {0};
  lat_bytecode *funcion_bcode = NULL;
  int fi = 0;
  switch (node->tipo) {
  case NODO_BLOQUE: {
    if (node->izq) {
      pn(mv, node->izq);
    }
    if (node->der) {
      pn(mv, node->der);
    }
  } break;
  case NODO_IDENTIFICADOR: {
    /*GET: Obtiene el valor de la variable en la tabla de simbolos*/
    lat_objeto *o = lat_cadena_nueva(mv, strdup(node->valor->val.cadena));
    o->num_linea = node->num_linea;
    o->num_columna = node->num_columna;
    o->es_constante = node->valor->es_constante;
    dbc(LOAD_NAME, 0, 0, o);
  } break;
  case NODO_ASIGNACION: {
    /*SET: Asigna el valor de la variable en la tabla de simbolos*/
    pn(mv, node->izq);
    if (node->der->tipo == NODO_ATRIBUTO) {
      // pn(mv, node->der);
      pn(mv, node->der->izq);
      lat_objeto *o =
          lat_cadena_nueva(mv, strdup(node->der->der->valor->val.cadena));
      o->num_linea = node->der->der->num_linea;
      o->num_columna = node->der->der->num_columna;
      o->es_constante = node->der->der->valor->es_constante;
      dbc(STORE_ATTR, 0, 0, o);
    } else {
      lat_objeto *o =
          lat_cadena_nueva(mv, strdup(node->der->valor->val.cadena));
      o->num_linea = node->der->num_linea;
      o->num_columna = node->der->num_columna;
      o->es_constante = node->der->valor->es_constante;
      dbc(STORE_NAME, 0, 0, o);
    }
  } break;
  case NODO_VALOR: {
    lat_objeto *o = NULL;
    if (node->valor->tipo == VALOR_LOGICO)
      o = (node->valor->val.logico == true) ? mv->objeto_verdadero
                                            : mv->objeto_falso;
    if (node->valor->tipo == VALOR_NUMERICO) {
      o = lat_numerico_nuevo(mv, node->valor->val.numerico);
    }
    if (node->valor->tipo == VALOR_CADENA) {
      o = lat_cadena_nueva(mv, strdup(node->valor->val.cadena));
    }
    if (node->valor->tipo == VALOR_NULO)
      o = mv->objeto_nulo;
    o->num_linea = node->num_linea;
    o->num_columna = node->num_columna;
    dbc(LOAD_CONST, 0, 0, o);
  } break;
  case NODO_MAS_UNARIO: {
    pn(mv, node->izq);
  } break;
  case NODO_MENOS_UNARIO: {
    pn(mv, node->izq);
    dbc(UNARY_MINUS, 0, 0, NULL);
  } break;
  case NODO_INC: {
    lat_objeto *o = lat_cadena_nueva(mv, strdup(node->izq->valor->val.cadena));
    o->num_linea = node->num_linea;
    o->num_columna = node->num_columna;
    o->es_constante = node->izq->valor->es_constante;
    dbc(INC, 0, 0, o);
  } break;
  case NODO_DEC: {
    lat_objeto *o = lat_cadena_nueva(mv, strdup(node->izq->valor->val.cadena));
    o->num_linea = node->num_linea;
    o->num_columna = node->num_columna;
    o->es_constante = node->izq->valor->es_constante;
    dbc(DEC, 0, 0, o);
  } break;
  case NODO_SUMA: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(BINARY_ADD, 0, 0, NULL);
  } break;
  case NODO_RESTA: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(BINARY_SUB, 0, 0, NULL);
  } break;
  case NODO_MULTIPLICACION: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(BINARY_MUL, 0, 0, NULL);
  } break;
  case NODO_DIVISION: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(BINARY_DIV, 0, 0, NULL);
  } break;
  case NODO_MODULO: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(BINARY_MOD, 0, 0, NULL);
  } break;
  case NODO_MAYOR_QUE: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_GT, 0, 0, NULL);
  } break;
  case NODO_MAYOR_IGUAL: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_GE, 0, 0, NULL);
  } break;
  case NODO_MENOR_QUE: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_LT, 0, 0, NULL);
  } break;
  case NODO_MENOR_IGUAL: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_LE, 0, 0, NULL);
  } break;
  case NODO_IGUALDAD: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_EQ, 0, 0, NULL);
  } break;
  case NODO_DESIGUALDAD: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_NEQ, 0, 0, NULL);
  } break;
  case NODO_Y: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_AND, 0, 0, NULL);
  } break;
  case NODO_O: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(OP_OR, 0, 0, NULL);
  } break;
  case NODO_NO: {
    pn(mv, node->izq);
    dbc(OP_NOT, 0, 0, NULL);
  } break;
  case NODO_CONCATENAR: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(CONCAT, 0, 0, NULL);
  } break;
  case NODO_SI: {
    nodo_si *nIf = ((nodo_si *)node);
    pn(mv, nIf->condicion);
    temp[0] = i;
    dbc(NOP, 0, 0, NULL);
    pn(mv, nIf->entonces);
    temp[1] = i;
    dbc(NOP, 0, 0, NULL);
    temp[2] = i;
    if (nIf->_sino) {
      pn(mv, nIf->_sino);
    }
    temp[3] = i;
    bcode[temp[0]] = lat_bc(POP_JUMP_IF_FALSE, (temp[2] - 1), 0, NULL);
    bcode[temp[1]] = lat_bc(JUMP_ABSOLUTE, (temp[3] - 1), 0, NULL);
  } break;
  case NODO_ELEGIR: {
    // FIXME: Memory leak
    // transformar nodo elegir en nodos si
    ast *nSi = __transformar_elegir(node);
    pn(mv, nSi);
  } break;
  case NODO_MIENTRAS: {
    dbc(SETUP_LOOP, 0, 0, NULL);
    temp[0] = i;
    pn(mv, node->izq);
    temp[1] = i;
    dbc(NOP, 0, 0, NULL);
    pn(mv, node->der);
    dbc(JUMP_ABSOLUTE, (temp[0] - 1), 0, NULL);
    dbc(POP_BLOCK, 0, 0, NULL);
    bcode[temp[1]] = lat_bc(POP_JUMP_IF_FALSE, (i - 1), 0, NULL);
  } break;
  case NODO_REPETIR: {
    dbc(SETUP_LOOP, 0, 0, NULL);
    temp[0] = i;
    pn(mv, node->der);
    pn(mv, node->izq);
    temp[1] = i;
    dbc(NOP, 0, 0, NULL);
    dbc(POP_BLOCK, 0, 0, NULL);
    bcode[temp[1]] = lat_bc(POP_JUMP_IF_FALSE, (temp[0] - 1), 0, NULL);
  } break;
  case NODO_FUNCION_LLAMADA: {
    // argumentos
    if (node->der) {
      pn(mv, node->der);
    }
    // nombre funcion
    pn(mv, node->izq);
    int num_args = __contar_num_parargs(node->der, NODO_FUNCION_ARGUMENTOS);
    dbc(CALL_FUNCTION, num_args, 0, NULL);
  } break;
  case NODO_RETORNO: {
    pn(mv, node->izq);
    dbc(RETURN_VALUE, 0, 0, NULL);
  } break;
  case NODO_FUNCION_ARGUMENTOS: {
    if (node->izq) {
      pn(mv, node->izq);
    }
    if (node->der) {
      pn(mv, node->der);
    }
  } break;
  case NODO_ATRIBUTO: {
    pn(mv, node->izq);
    lat_objeto *o = lat_cadena_nueva(mv, strdup(node->der->valor->val.cadena));
    o->num_linea = node->der->num_linea;
    o->num_columna = node->der->num_columna;
    o->es_constante = node->der->valor->es_constante;
    dbc(LOAD_ATTR, 0, 0, o);
  } break;
  case NODO_FUNCION_PARAMETROS: {
    if (node->izq) {
      lat_objeto *o =
          lat_cadena_nueva(mv, strdup(node->izq->valor->val.cadena));
      dbc(STORE_NAME, 0, 0, o);
    }
    if (node->der) {
      pn(mv, node->der);
    }
  } break;
  case NODO_FUNCION_USUARIO: {
    nodo_funcion *fun = (nodo_funcion *)node;
    funcion_bcode = (lat_bytecode *)__memoria_asignar(
        mv, sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    fi = 0;
    // procesar lista de parametros
    if (fun->parametros) {
      fpn(mv, fun->parametros);
    }
    // procesar instrucciones
    fpn(mv, fun->sentencias);
    fdbc(RETURN_VALUE, 0, 0, NULL);
    lat_objeto *f = lat_definir_funcion(mv, funcion_bcode, fi + 1);
    dbc(MAKE_FUNCTION, fi + 1, 0, f);
    funcion_bcode = NULL;
    fi = 0;
    lat_objeto *o =
        lat_cadena_nueva(mv, strdup(fun->nombre->valor->val.cadena));
    o->num_linea = fun->nombre->num_linea;
    o->num_columna = fun->nombre->num_columna;
    o->num_params =
        __contar_num_parargs(fun->parametros, NODO_FUNCION_PARAMETROS);
    o->nombre_cfun = fun->nombre->valor->val.cadena;
    dbc(STORE_NAME, 0, 0, o);
    if (0 == strcmp(o->datos.cadena, "menu")) {
      mv->menu = true;
    }
  } break;
  case NODO_LISTA: {
    int num_params = 0;
    if (node->izq) {
      pn(mv, node->izq);
      num_params = __contar_num_parargs(node->izq, NODO_LISTA_AGREGAR_ELEMENTO);
    }
    // FIX: Memory leak
    //lat_objeto *o = lat_lista_nueva(mv, __lista_crear());
    dbc(BUILD_LIST, num_params, 0, NULL);
  } break;
  case NODO_LISTA_AGREGAR_ELEMENTO: {
    if (node->izq) {
      pn(mv, node->izq);
    }
    if (node->der) {
      pn(mv, node->der);
    }
  } break;
  case NODO_LISTA_ASIGNAR_ELEMENTO: {
    nodo_lista_elem *nl = (nodo_lista_elem *)node;
    pn(mv, nl->expresion);
    pn(mv, nl->identificador);
    pn(mv, nl->posicion);
    dbc(STORE_SUBSCR, 0, 0, NULL);
  } break;
  case NODO_LISTA_OBTENER_ELEMENTO: {
    pn(mv, node->izq);
    pn(mv, node->der);
    dbc(BINARY_SUBSCR, 0, 0, NULL);
  } break;
  case NODO_DICCIONARIO: {
    int num_params = 0;
    if (node->izq) {
      num_params = __contar_num_parargs(node->izq, NODO_DICC_AGREGAR_ELEMENTO);
    }
    lat_objeto *o = lat_dic_nuevo(mv, __dic_crear());
    dbc(BUILD_MAP, num_params, 0, o);
    if (node->izq) {
      pn(mv, node->izq);
    }
  } break;
  case NODO_DICC_AGREGAR_ELEMENTO: {
    if (node->der) {
      pn(mv, node->der);
    }
    if (node->izq) {
      pn(mv, node->izq);
    }
    dbc(STORE_MAP, 0, 0, NULL);
  } break;
  case NODO_DICC_ELEMENTO: {
    if (node->der) {
      pn(mv, node->der);
    }
    if (node->izq) {
      pn(mv, node->izq);
    }
  } break;
  default:
    printf("ERROR node->tipo:%i\n", node->tipo);
    return 0;
  }
  return i;
}

void __mostrar_bytecode(lat_bytecode *bcode) {
#if DEPURAR_AST
  lat_bytecode *inslist = bcode;
  lat_bytecode cur;
  lat_objeto *o = NULL;
  int pos;
  for (pos = 0, cur = inslist[pos]; cur.ins && cur.ins != HALT;
       cur = inslist[++pos]) {
    char *buffer = __memoria_asignar(NULL, MAX_STR_LENGTH);
    printf("%i\t", pos);
    switch (cur.ins) {
    case HALT:
      return;
      break;
    case NOP:
    case UNARY_MINUS:
    case BINARY_ADD:
    case BINARY_SUB:
    case BINARY_MUL:
    case BINARY_DIV:
    case BINARY_MOD:
    case OP_GT:
    case OP_GE:
    case OP_LT:
    case OP_LE:
    case OP_EQ:
    case OP_NEQ:
    case OP_AND:
    case OP_OR:
    case OP_NOT:
    case OP_INC:
    case OP_DEC:
    case CONCAT:
    case SETUP_LOOP:
    case POP_BLOCK:
    case RETURN_VALUE:
    case STORE_SUBSCR:
    case BINARY_SUBSCR:
    case STORE_MAP:
    case STORE_ATTR:
      printf("%s\n", __obtener_bytecode_nombre(cur.ins));
      break;
    case CALL_FUNCTION: {
      printf("CALL_FUNCTION\t%i\n", cur.a);
    } break;
    case LOAD_ATTR: {
      o = (lat_objeto *)cur.meta;
      buffer = lat_obj2cstring(o);
      printf("LOAD_ATTR\t(%s)\n", buffer);
      __memoria_liberar(NULL, buffer);
    } break;
    case LOAD_CONST: {
      o = (lat_objeto *)cur.meta;
      buffer = lat_obj2cstring(o);
      printf("LOAD_CONST\t(%s)\n", buffer);
      __memoria_liberar(NULL, buffer);
    } break;
    case LOAD_NAME: {
      o = (lat_objeto *)cur.meta;
      buffer = lat_obj2cstring(o);
      printf("LOAD_NAME \t(%s)\n", buffer);
      __memoria_liberar(NULL, buffer);
    } break;
    case STORE_NAME: {
      o = (lat_objeto *)cur.meta;
      buffer = lat_obj2cstring(o);
      printf("STORE_NAME\t(%s)\n", buffer);
      __memoria_liberar(NULL, buffer);
    } break;
    case JUMP_ABSOLUTE: {
      printf("JUMP_ABSOLUTE\t(%i)\n", (cur.a + 1));
    } break;
    case POP_JUMP_IF_FALSE: {
      printf("POP_JUMP_IF_FALSE\t(%i)\n", (cur.a + 1));
    } break;
    case POP_JUMP_IF_TRUE: {
      printf("POP_JUMP_IF_TRUE\t(%i)\n", (cur.a + 1));
    } break;
    case INC: {
      o = (lat_objeto *)cur.meta;
      buffer = lat_obj2cstring(o);
      printf("INC\t(%s)\n", buffer);
      __memoria_liberar(NULL, buffer);
    } break;
    case DEC: {
      o = (lat_objeto *)cur.meta;
      buffer = lat_obj2cstring(o);
      printf("DEC\t(%s)\n", buffer);
      __memoria_liberar(NULL, buffer);
    } break;
    case MAKE_FUNCTION: {
      printf("MAKE_FUNCTION\n");
      printf("-------------------------------\n");
      __mostrar_bytecode(cur.meta);
      printf("-------------------------------\n");
    } break;
    case BUILD_LIST: {
      printf("BUILD_LIST\t%i\n", cur.a);
    } break;
    case BUILD_MAP: {
      printf("BUILD_MAP\t%i\n", cur.a);
    } break;
    }
  }
#endif
}

lat_objeto *ast_analizar_arbol(lat_mv *mv, ast *nodo) {
  lat_bytecode *bcode =
      __memoria_asignar(mv, sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
  int i = nodo_analizar(mv, nodo, bcode, 0);
  dbc(HALT, 0, 0, NULL);
  __mostrar_bytecode(bcode);
  return lat_definir_funcion(mv, bcode, i);
}
