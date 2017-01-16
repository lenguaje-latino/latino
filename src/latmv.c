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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latcompat.h"
#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"
#include "latparse.h"

static const char *const bycode_nombre[] = {
    "NOP",
    "HALT",
    "UNARY_MINUS",
    "BINARY_ADD",
    "BINARY_SUB",
    "BINARY_MUL",
    "BINARY_DIV",
    "BINARY_MOD",
    "OP_GT",
    "OP_GE",
    "OP_LT",
    "OP_LE",
    "OP_EQ",
    "OP_NEQ",
    "OP_AND",
    "OP_OR",
    "OP_NOT",
    "OP_INC",
    "OP_DEC",
    "CONCAT",
    "LOAD_CONST",
    "LOAD_NAME",
    "STORE_NAME",
    "JUMP_ABSOLUTE",
    "POP_JUMP_IF_FALSE",
    "POP_JUMP_IF_TRUE",
    "SETUP_LOOP",
    "POP_BLOCK",
    "CALL_FUNCTION",
    "RETURN_VALUE",
    "MAKE_FUNCTION",
    "INC",
    "DEC",
    "LOAD_ATTR",
    "BUILD_LIST",
    "STORE_SUBSCR",
    "BINARY_SUBSCR",
    "BUILD_MAP",
    "STORE_MAP",
    "STORE_ATTR",
    "STORE_GLOBAL",
};

void lat_cadena_concatenar(lat_mv *mv);

void lat_importar_lib_base(lat_mv *mv);
void lat_importar_lib_cast(lat_mv *mv);
void lat_importar_lib_curl(lat_mv *mv);
void lat_importar_lib_archivo(lat_mv *mv);
void lat_importar_lib_json(lat_mv *mv);
void lat_importar_lib_lista(lat_mv *mv);
void lat_importar_lib_mate(lat_mv *mv);
void lat_importar_lib_cadena(lat_mv *mv);
void lat_importar_lib_redis(lat_mv *mv);
void lat_importar_lib_sistema(lat_mv *mv);
void lat_importar_lib_dic(lat_mv *mv);
void lat_importar_lib_gtk(lat_mv *mv);

const char *__obtener_bytecode_nombre(int inst) { return bycode_nombre[inst]; }

static void __menos_unario(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *r = lat_numerico_nuevo(mv, (-1) * lat_obj2double(o));
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
}

static void __sumar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = lat_numerico_nuevo(mv, lat_obj2double(a) + lat_obj2double(b));
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
}

static void __restar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = lat_numerico_nuevo(mv, lat_obj2double(a) - lat_obj2double(b));
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
}

static void __multiplicar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = lat_numerico_nuevo(mv, lat_obj2double(a) * lat_obj2double(b));
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
}

static void __dividir(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  if (lat_obj2double(b) == 0) {
    lat_error("Linea %d, %d: %s", b->num_linea, b->num_columna,
              "Division entre cero");
  }
  lat_objeto *r =
      lat_numerico_nuevo(mv, (lat_obj2double(a) / lat_obj2double(b)));
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
}

static void __modulo(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  if (lat_obj2double(b) == 0) {
    lat_error("Linea %d, %d: %s", b->num_linea, b->num_columna,
              "Modulo entre cero");
  }
  lat_objeto *r =
      lat_numerico_nuevo(mv, fmod(lat_obj2double(a), lat_obj2double(b)));
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
}

static void __igualdad(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  char *buffer = NULL;
  char *buffer2 = NULL;
  switch (a->tipo) {
  case T_BOOL: {
    r = __logico(a) == lat_obj2bool(b) ? mv->objeto_verdadero
                                       : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  } break;
  case T_NUMERIC: {
    r = (__numerico(a) == lat_obj2double(b)) ? mv->objeto_verdadero
                                             : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  } break;
  case T_STR: {
    buffer = lat_obj2cstring(b);
    r = strcmp(__cadena(a), buffer) == 0 ? mv->objeto_verdadero
                                         : mv->objeto_falso;
    lat_apilar(mv, r);
    __memoria_liberar(mv, buffer);
    return;
  } break;
  default: {
    buffer = lat_obj2cstring(a);
    buffer2 = lat_obj2cstring(b);
    r = strcmp(buffer, buffer2) == 0 ? mv->objeto_verdadero : mv->objeto_falso;
    lat_apilar(mv, r);
    __memoria_liberar(mv, buffer);
    __memoria_liberar(mv, buffer2);
  }
    return;
  }
  r = mv->objeto_falso;
  lat_apilar(mv, r);
}

static void __diferente(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  char *buffer = NULL;
  char *buffer2 = NULL;
  switch (a->tipo) {
  case T_BOOL: {
    r = __logico(a) != lat_obj2bool(b) ? mv->objeto_verdadero
                                       : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  } break;
  case T_NUMERIC: {
    r = (__numerico(a) != lat_obj2double(b)) ? mv->objeto_verdadero
                                             : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  } break;
  case T_STR: {
    buffer = lat_obj2cstring(b);
    r = strcmp(__cadena(a), buffer) != 0 ? mv->objeto_verdadero
                                         : mv->objeto_falso;
    lat_apilar(mv, r);
    __memoria_liberar(mv, buffer);
    return;
  } break;
  default: {
    buffer = lat_obj2cstring(a);
    buffer2 = lat_obj2cstring(b);
    r = strcmp(buffer, buffer2) != 0 ? mv->objeto_verdadero : mv->objeto_falso;
    lat_apilar(mv, r);
    __memoria_liberar(mv, buffer);
    __memoria_liberar(mv, buffer2);
    return;
  }
  }
  r = mv->objeto_falso;
  lat_apilar(mv, r);
}

static void __menor_que(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (lat_obj2double(a) < lat_obj2double(b)) ? mv->objeto_verdadero
                                                : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  }
  r = __obj_comparar(a, b) < 0 ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, r);
  return;
}

static void __menor_igual(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (lat_obj2double(a) <= lat_obj2double(b)) ? mv->objeto_verdadero
                                                 : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  }
  r = __obj_comparar(a, b) <= 0 ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, r);
  return;
}

static void __mayor_que(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (lat_obj2double(a) > lat_obj2double(b)) ? mv->objeto_verdadero
                                                : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  }
  r = __obj_comparar(a, b) > 0 ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, r);
  return;
}

static void __mayor_igual(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (lat_obj2double(a) >= lat_obj2double(b)) ? mv->objeto_verdadero
                                                 : mv->objeto_falso;
    lat_apilar(mv, r);
    return;
  }
  r = __obj_comparar(a, b) >= 0 ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, r);
  return;
}

static void __y_logico(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (lat_obj2bool(a)) {
    r = b;
  } else {
    r = a;
  }
  lat_apilar(mv, r);
}

static void __o_logico(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (lat_obj2bool(a)) {
    r = a;
  } else {
    r = b;
  }
  lat_apilar(mv, r);
}

static void __no_logico(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *r =
      (lat_obj2bool(o) == false) ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, r);
}

void lat_importar_lib(lat_mv *mv, const char *nombre_lib,
                      const lat_CReg *funs) {
  lat_objeto *ctx = lat_obtener_contexto(mv);
  if (strcmp(nombre_lib, "") == 0) {
    /*alcance global o libreria base*/
    for (; funs->nombre; funs++) {
      lat_objeto *cfun = lat_definir_cfuncion(mv, funs->func);
      cfun->nombre_cfun = strdup(funs->nombre);
      cfun->num_params = funs->num_params;
      lat_objeto *tmp = lat_cadena_nueva(mv, strdup(funs->nombre));
      __obj_asignar_contexto(ctx, tmp, cfun);
      __lista_agregar(__lista(mv->otros_objetos), tmp);
      __lista_agregar(__lista(mv->otros_objetos), cfun);
    }
  } else {
    lat_objeto *lib = lat_cadena_nueva(mv, strdup(nombre_lib));
    lat_objeto *mod = __obj_obtener_contexto(ctx, lib);
    if (mod == NULL) {
      mod = lat_dic_nuevo(mv, __dic_crear());
    }
    for (; funs->nombre; funs++) {
      lat_objeto *cfun = lat_definir_cfuncion(mv, funs->func);
      cfun->nombre_cfun = strdup(funs->nombre);
      cfun->num_params = funs->num_params;
      __dic_asignar(__dic(mod), funs->nombre, cfun);
      __lista_agregar(__lista(mv->otros_objetos), cfun);
    }
    __obj_asignar_contexto(ctx, lib, mod);
    __lista_agregar(__lista(mv->otros_objetos), lib);
    __lista_agregar(__lista(mv->otros_objetos), mod);
  }
}

lat_mv *lat_mv_crear() {
  // printf("creando mv\n");
  lat_mv *mv = (lat_mv *)__memoria_asignar(NULL, sizeof(lat_mv));
  mv->modulos = lat_lista_nueva(mv, __lista_crear());
  mv->gc_objetos = lat_lista_nueva(mv, __lista_crear());
  mv->otros_objetos = lat_lista_nueva(mv, __lista_crear());
  mv->pila = lat_lista_nueva(mv, __lista_crear());
  mv->argv = lat_lista_nueva(mv, __lista_crear());
  mv->objeto_verdadero = __obj_logico_nuevo(mv, true);
  mv->objeto_falso = __obj_logico_nuevo(mv, false);
  mv->objeto_nulo = __obj_crear(mv);
  memset(mv->contexto_pila, 0, 256);
  mv->contexto_pila[0] = __obj_contexto_nuevo(mv);
  mv->apuntador_ctx = 0;
  lat_importar_lib_base(mv);
  lat_importar_lib_cast(mv);
  lat_importar_lib_curl(mv);
  lat_importar_lib_archivo(mv);
  lat_importar_lib_json(mv);
  lat_importar_lib_lista(mv);
  lat_importar_lib_mate(mv);
  lat_importar_lib_cadena(mv);
  lat_importar_lib_redis(mv);
  lat_importar_lib_sistema(mv);
  lat_importar_lib_dic(mv);
  lat_importar_lib_gtk(mv);
  return mv;
}

void lat_destruir_mv(lat_mv *mv) {
  __obj_eliminar(mv, mv->argv);
  // printf("%s\n", ">>>liberando modulos:");
  //__obj_eliminar(mv, mv->modulos);
  // printf("%s\n", ">>>liberando otros_objetos:");
  __obj_eliminar(mv, mv->otros_objetos);
  // printf("%s\n", ">>>liberando gc:");
  //__obj_eliminar(mv, mv->gc_objetos);
  __obj_eliminar(mv, mv->pila);
  if (mv->contexto_pila[0] != NULL) {
    __obj_eliminar(mv, mv->contexto_pila[0]);
  }
  __memoria_liberar(mv, mv->objeto_verdadero);
  __memoria_liberar(mv, mv->objeto_falso);
  __memoria_liberar(mv, mv->objeto_nulo);
  __memoria_liberar(NULL, mv);
}

void lat_apilar(lat_mv *mv, lat_objeto *o) {
  __lista_agregar(__lista(mv->pila), (void *)o);
}

lat_objeto *lat_desapilar(lat_mv *mv) {
  return (lat_objeto *)__lista_desapilar(__lista(mv->pila));
}

lat_objeto *lat_tope(lat_mv *mv) {
  if ((lat_objeto *)mv->pila->datos.lista->ultimo)
    return (lat_objeto *)mv->pila->datos.lista->ultimo->valor;

  return NULL;
}

static void __mv_apilar_contexto(lat_mv *mv) {
  //printf("apilando contexto...\n");
  if (mv->apuntador_ctx >= MAX_STACK_SIZE) {
    lat_error("Namespace desborde de la pila");
  }
  mv->contexto_pila[mv->apuntador_ctx + 1] =
      __obj_clonar(mv, mv->contexto_pila[mv->apuntador_ctx]);
  mv->apuntador_ctx++;
}

static void __mv_desapilar_contexto(lat_mv *mv) {
  //printf("...desapilando contexto\n");
  if (mv->apuntador_ctx == 0) {
    lat_error("Namespace pila vacia");
  }
  __obj_eliminar(mv, mv->contexto_pila[mv->apuntador_ctx--]);
}

lat_objeto *lat_obtener_contexto(lat_mv *mv) {
  return mv->contexto_pila[mv->apuntador_ctx];
}

lat_objeto *lat_obtener_global_ctx(lat_mv *mv) {
  return mv->contexto_pila[0];
}

lat_objeto *lat_definir_funcion(lat_mv *mv, lat_bytecode *inslist,
                                int num_inst) {
  lat_objeto *ret = __obj_funcion_nueva(mv);
  lat_function *fval = __memoria_asignar(mv, sizeof(lat_function));
  fval->bcode = inslist;
  ret->datos.fun_usuario = fval;
  ret->num_inst = num_inst;
  return ret;
}

lat_objeto *lat_definir_cfuncion(lat_mv *mv, lat_CFuncion func) {
  lat_objeto *ret = __obj_cfuncion_nueva(mv);
  ret->datos.c_funcion = func;
  return ret;
}

lat_bytecode lat_bc(int i, int a, int b, void *meta) {
  lat_bytecode ret;
  ret.ins = i;
  ret.a = a;
  ret.b = b;
  ret.meta = meta;
  return ret;
}

void lat_llamar_funcion(lat_mv *mv, lat_objeto *func) {
  if (func->tipo == T_FUNC) {
#if DEPURAR_MV
    printf("\n.::Ejecutando funcion::.\n");
#endif
    lat_objeto *nom_fun = lat_cadena_nueva(mv, strdup("lat_main"));
    //__lista_agregar(__lista(mv->otros_objetos), nom_fun);
    lat_gc_agregar(mv, nom_fun);
    __obj_asignar_contexto(lat_obtener_contexto(mv), nom_fun, func);
    lat_bytecode *inslist = ((lat_function *)func->datos.fun_usuario)->bcode;
    lat_bytecode cur;
    int pos;
    for (pos = 0, cur = inslist[pos]; cur.ins != HALT; cur = inslist[++pos]) {
      lat_bytecode next = inslist[pos + 1];
#if DEPURAR_MV
      printf("%i\t", pos);
      printf("%s\t", __obtener_bytecode_nombre(cur.ins));
#endif
      switch (cur.ins) {
      case HALT:
        return;
        break;
      case NOP:
        break;
      case UNARY_MINUS: {
        __menos_unario(mv);
      } break;
      case INC: {
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(mv);
        lat_objeto *val = __obj_obtener_contexto(ctx, name);
        if(val == NULL){
          //si no existe se infiere que es entero y se inicializa en 0
          val = lat_numerico_nuevo(mv, 0);
        }
        lat_objeto *tmp = __obj_clonar(mv, val);
        tmp->datos.numerico++;
        __obj_asignar_contexto(ctx, name, tmp);
        lat_gc_agregar(mv, tmp);
        Lat_INCREF(val);
        Lat_INCREF(tmp);
      } break;
      case DEC: {
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(mv);
        lat_objeto *val = __obj_obtener_contexto(ctx, name);
        if(val == NULL){
          //si no existe se infiere que es entero y se inicializa en 0
          val = lat_numerico_nuevo(mv, 0);
        }
        lat_objeto *tmp = __obj_clonar(mv, val);
        tmp->datos.numerico--;
        __obj_asignar_contexto(ctx, name, tmp);
        lat_gc_agregar(mv, tmp);
        Lat_INCREF(val);
        Lat_INCREF(tmp);
      } break;
      case BINARY_ADD: {
        __sumar(mv);
      } break;
      case BINARY_SUB: {
        __restar(mv);
      } break;
      case BINARY_MUL: {
        __multiplicar(mv);
      } break;
      case BINARY_DIV: {
        __dividir(mv);
      } break;
      case BINARY_MOD: {
        __modulo(mv);
      } break;
      case OP_GT: {
        __mayor_que(mv);
      } break;
      case OP_GE: {
        __mayor_igual(mv);
      } break;
      case OP_LT: {
        __menor_que(mv);
      } break;
      case OP_LE: {
        __menor_igual(mv);
      } break;
      case OP_EQ: {
        __igualdad(mv);
      } break;
      case OP_NEQ: {
        __diferente(mv);
      } break;
      case OP_AND: {
        __y_logico(mv);
      } break;
      case OP_OR: {
        __o_logico(mv);
      } break;
      case OP_NOT: {
        __no_logico(mv);
      } break;
      case CONCAT: {
        lat_cadena_concatenar(mv);
      } break;
      case LOAD_CONST: {
        lat_objeto *o = (lat_objeto *)cur.meta;
#if DEPURAR_MV
        __imprimir_objeto(mv, o, false);
        printf("\t");
#endif
        lat_apilar(mv, o);
      } break;
      case STORE_NAME: {
        lat_objeto *val = NULL;
        if(next.ins == STORE_GLOBAL){
          val = lat_tope(mv);
        }else {
          val = lat_desapilar(mv);
        }
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(mv);
        Lat_INCREF(val);
#if DEPURAR_MV
        __imprimir_objeto(mv, name, false);
        printf("\t");
#endif
        // objeto anterior
        lat_objeto *tmp = __obj_obtener_contexto(ctx, name);
        Lat_DECREF(tmp);
        if (name->es_constante) {
          if (tmp != NULL) {
            lat_error(
                "Linea %d, %d: Intento de reasignar valor a constante '%s'",
                name->num_linea, name->num_columna, __cadena(name));
          }
        }
        // asigna el numero de parametros
        if (name->nombre_cfun) {
          val->num_params = name->num_params;
          // val->nombre_cfun = strdup(name->nombre_cfun);
          val->nombre_cfun = name->nombre_cfun;
        }
        __obj_asignar_contexto(ctx, name, val);
      } break;
      case STORE_GLOBAL: {
        lat_bytecode prev = inslist[pos - 1];
        lat_objeto *val = lat_desapilar(mv);
        lat_objeto *name = (lat_objeto *)prev.meta;
        lat_objeto *ctx = lat_obtener_global_ctx(mv);
        //Lat_INCREF(val);
#if DEPURAR_MV
        __imprimir_objeto(mv, name, false);
        printf("\t");
#endif
        // objeto anterior
        lat_objeto *tmp = __obj_obtener_contexto(ctx, name);
        Lat_DECREF(tmp);
        if (name->es_constante) {
          if (tmp != NULL) {
            lat_error(
                "Linea %d, %d: Intento de reasignar valor a constante '%s'",
                name->num_linea, name->num_columna, __cadena(name));
          }
        }
        // asigna el numero de parametros
        if (name->nombre_cfun) {
          val->num_params = name->num_params;
          // val->nombre_cfun = strdup(name->nombre_cfun);
          val->nombre_cfun = name->nombre_cfun;
        }
        __obj_asignar_contexto(ctx, name, val);
      } break;
      case LOAD_NAME: {
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(mv);
#if DEPURAR_MV
        __imprimir_objeto(mv, name, false);
        printf("\t");
#endif
        lat_objeto *val = __obj_obtener_contexto(ctx, name);
        if (val == NULL) {
          ctx = lat_obtener_global_ctx(mv);
          val = __obj_obtener_contexto(ctx, name);
          if (val == NULL) {
            lat_error("Linea %d, %d: Variable \"%s\" indefinida", name->num_linea,
                    name->num_columna, __cadena(name));
          }
        }
        val->num_linea = name->num_linea;
        val->num_columna = name->num_columna;
        lat_apilar(mv, val);
      } break;
      case POP_JUMP_IF_FALSE: {
        lat_objeto *o = lat_desapilar(mv);
        if (lat_obj2bool(o) == false) {
          pos = cur.a;
        }
      } break;
      case POP_JUMP_IF_TRUE: {
        // TODO: Unused bytecode
        lat_objeto *o = lat_desapilar(mv);
        if (lat_obj2bool(o) == true) {
          pos = cur.a;
        }
      } break;
      case JUMP_ABSOLUTE:
        pos = cur.a;
        break;
      case CALL_FUNCTION: {
#if DEPURAR_MV
        printf("\n=> ");
#endif
        int num_args = cur.a;
        lat_objeto *fun = lat_desapilar(mv);
        if (num_args != fun->num_params) {
          /*si se envian menos parametros se acompletan con nulos*/
          while (num_args < fun->num_params) {
            lat_apilar(mv, mv->objeto_nulo);
            num_args++;
          }
          if (num_args != fun->num_params) {
            lat_error("Linea %d, %d: Numero invalido de argumentos en "
                      "funcion '%s'. se esperaban %i valores.\n",
                      fun->num_linea, fun->num_columna, fun->nombre_cfun,
                      fun->num_params);
          }
        }
        mv->num_callf++;
        if (mv->num_callf >= MAX_CALL_FUNCTION) {
          lat_error("Linea %d, %d: Numero maximo de llamadas a funciones "
                    "recursivas excedido en '%s'\n",
                    fun->num_linea, fun->num_columna, fun->nombre_cfun);
        }
        bool apilar = next.ins == STORE_NAME ||
                      (func->nombre_cfun != NULL && fun->nombre_cfun != NULL &&
                       0 == strcmp(func->nombre_cfun, fun->nombre_cfun));
        if (apilar) {
          __mv_apilar_contexto(mv);
        }
        lat_llamar_funcion(mv, fun);
        mv->num_callf--;
        if (apilar) {
          __mv_desapilar_contexto(mv);
        }
      } break;
      case RETURN_VALUE: {
        return;
      } break;
      case MAKE_FUNCTION: {
        lat_objeto *fun = (lat_objeto *)cur.meta;
        lat_apilar(mv, fun);
      } break;
      case SETUP_LOOP:
        __mv_apilar_contexto(mv);
        break;
      case POP_BLOCK:
        __mv_desapilar_contexto(mv);
        break;
      case BUILD_LIST: {
        int num_elem = cur.a;
        int i;
        //lat_objeto *obj = (lat_objeto *)cur.meta;
        lat_objeto *obj = lat_lista_nueva(mv, __lista_crear());
        for (i = 0; i < num_elem; i++) {
          lat_objeto *tmp = lat_desapilar(mv);
          __lista_agregar(__lista(obj), tmp);
        }
        lat_apilar(mv, obj);
      } break;
      case LOAD_ATTR: {
        lat_objeto *obj = lat_desapilar(mv);
        lat_objeto *attr = (lat_objeto *)cur.meta;
        // lat_objeto *ctx = lat_obtener_contexto(mv);
        lat_objeto *val = NULL;
#if DEPURAR_MV
        __imprimir_objeto(mv, attr, false);
        printf("\t");
#endif
        if (obj->tipo == T_DICT) {
          val = (lat_objeto *)__dic_obtener(__dic(obj), __cadena(attr));
          if (val != NULL) {
            // printf("apilando objeto %s\n", __tipo(val->tipo));
            lat_apilar(mv, val);
            break;
          } else {
            if (next.ins == CALL_FUNCTION) {
              lat_error("Linea %d, %d: No se encontro la funcion %s.",
                        attr->num_linea, attr->num_columna, __cadena(attr));
            } else {
              val = lat_cadena_nueva(mv, strdup(""));
              lat_apilar(mv, val);
            }
          }
        }
        lat_objeto *top = lat_tope(mv);
        if (top && (next.ins == BINARY_SUBSCR)) {
          if (top->tipo == T_STR) {
            if (obj->tipo != T_DICT) {
              obj = lat_dic_nuevo(mv, __dic_crear());
              __dic_asignar(__dic(obj), __cadena(attr), val);
              lat_apilar(mv, obj);
              lat_gc_agregar(mv, obj);
              break;
            }
          }
          if (top->tipo == T_NUMERIC) {
            if (obj->tipo != T_LIST) {
              obj = lat_lista_nueva(mv, __lista_crear());
              lat_apilar(mv, obj);
              break;
            }
          }
        }
        val = lat_cadena_nueva(mv, strdup(""));
        lat_apilar(mv, val);
      } break;
      case STORE_SUBSCR: {
        lat_objeto *pos = lat_desapilar(mv);
        lat_objeto *lst = lat_desapilar(mv);
        lat_objeto *exp = lat_desapilar(mv);
        if (lst->tipo == T_DICT) {
          __dic_asignar(__dic(lst), __cadena(pos), exp);
          break;
        }
        int ipos = __numerico(pos);
        if (lst->tipo == T_STR) {
          char *slst = __cadena(lst);
          if (ipos < 0 || ipos >= strlen(slst)) {
            lat_error("Linea %d, %d: Indice fuera de rango.", pos->num_linea,
                      pos->num_columna);
          }
          char *sexp = strdup(__cadena(exp));
          if (strlen(sexp) == 0) {
            sexp = " ";
          }
          slst[ipos] = sexp[0];
          lst->datos.cadena = slst;
        }
        if (lst->tipo == T_LIST) {
          if (ipos < 0 || ipos >= __lista_longitud(__lista(lst))) {
            lat_error("Linea %d, %d: Indice fuera de rango.", pos->num_linea,
                      pos->num_columna);
          }
          __lista_modificar_elemento(__lista(lst), exp, ipos);
        }
      } break;
      case BINARY_SUBSCR: {
        lat_objeto *obj = lat_desapilar(mv);
        lat_objeto *pos = lat_desapilar(mv);
        lat_objeto *o = NULL;
        if (obj->tipo == T_DICT) {
          o = __dic_obtener(__dic(obj), __cadena(pos));
          if (o == NULL) {
            o = lat_cadena_nueva(mv, strdup(""));
            lat_gc_agregar(mv, o);
          }
          lat_apilar(mv, o);
          break;
        }
        int ipos = __numerico(pos);
        if (obj->tipo == T_STR) {
          char *slst = __cadena(obj);
          if (ipos < 0 || ipos >= strlen(slst)) {
            o = mv->objeto_nulo;
            lat_apilar(mv, o);
            break;
          }
          char c[2] = {slst[ipos], '\0'};
          o = lat_cadena_nueva(mv, strdup(c));
          lat_gc_agregar(mv, o);
        }
        if (obj->tipo == T_LIST) {
          if (ipos < 0 || ipos >= __lista_longitud(__lista(obj))) {
            o = lat_cadena_nueva(mv, strdup(""));
            lat_apilar(mv, o);
            break;
          }
          o = __lista_obtener_elemento(__lista(obj), __numerico(pos));
        }
        lat_apilar(mv, o);
      } break;
      case BUILD_MAP: {
        lat_objeto *o = (lat_objeto *)cur.meta;
        lat_apilar(mv, o);
      } break;
      case STORE_MAP: {
        lat_objeto *key = lat_desapilar(mv);
        lat_objeto *val = lat_desapilar(mv);
        lat_objeto *dic = lat_tope(mv);
        while (dic && dic->tipo != T_DICT) {
          lat_desapilar(mv);
          dic = lat_tope(mv);
        }
        // lat_objeto *tmp = __obj_clonar(mv, val);
        //__dic_asignar(__dic(dic), strdup(__cadena(key)), tmp);
        __dic_asignar(__dic(dic), __cadena(key), val);
      } break;
      case STORE_ATTR: {
        lat_objeto *attr = (lat_objeto *)cur.meta;
        lat_objeto *obj = lat_desapilar(mv);
        lat_objeto *val = lat_desapilar(mv);
        if (obj->tipo == T_DICT) {
          __dic_asignar(__dic(obj), __cadena(attr), val);
        }
      } break;

      } // fin de switch

#if DEPURAR_MV
      __imprimir_objeto(mv, mv->pila, false);
      printf("\n");
#endif
    } // fin for
  }   // fin if (T_FUNC)
  else if (func->tipo == T_CFUNC) {
    // printf("%s\n", "llamando c funcion");
    ((void (*)(lat_mv *))(func->datos.fun_usuario))(mv);
  } else {
    lat_error("Linea %d, %d: %s", func->num_linea, func->num_columna,
              "El objeto no es una funcion");
  }
}
