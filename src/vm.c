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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <wchar.h>
#include <math.h>

#include <jansson.h>

#include "compat.h"
#include "gc.h"
#include "libio.h"
#include "liblist.h"
#include "libmath.h"
#include "libmem.h"
#include "libnet.h"
#include "libstring.h"
#include "parse.h"
#include "vm.h"

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
};

bool __lista_contiene_valor(lista *list, void *data) {
  lat_objeto *bus = (lat_objeto *)data;
  LIST_FOREACH(list, primero, siguiente, cur) {
    lat_objeto *tmp = (lat_objeto *)cur->valor;
    if (__objeto_comparar(tmp, bus) == 0) {
      return true;
    }
  }
  return false;
}

static json_t *__cargar_json(const char *text) {
  json_t *root;
  json_error_t error;
  root = json_loads(text, 0, &error);
  if (root) {
    return root;
  } else {
    lat_fatal_error("Linea %d: %s", error.line, error.text);
    return (json_t *)0;
  }
}

static lat_objeto *__json_a_latino(lat_mv *mv, json_t *element) {
  size_t i;
  size_t size;
  json_t *value = NULL;
  const char *key;
  switch (json_typeof(element)) {
  case JSON_OBJECT: {
    size = json_object_size(element);
    lat_objeto *dic = lat_dic_nuevo(mv, __dic_crear());
    json_object_foreach(element, key, value) {
      // printf("key: %s\n", key);
      __dic_asignar(__dic(dic), key, (void *)__json_a_latino(mv, value));
    }
    return dic;
  } break;
  case JSON_ARRAY: {
    size = json_array_size(element);
    lat_objeto *lst = lat_lista_nueva(mv, __lista_crear());
    for (i = 0; i < size; i++) {
      value = json_array_get(element, i);
      __lista_apilar(__lista(lst), (void *)__json_a_latino(mv, value));
    }
    return lst;
  } break;
  case JSON_STRING: {
    lat_objeto *str = lat_cadena_nueva(mv, strdup(json_string_value(element)));
    return str;
  } break;
  case JSON_INTEGER: {
    lat_objeto *dec =
        lat_numerico_nuevo(mv, (double)json_integer_value(element));
    return dec;
  } break;
  case JSON_REAL: {
    lat_objeto *dec = lat_numerico_nuevo(mv, (double)json_real_value(element));
    return dec;
  } break;
  case JSON_TRUE:
    return mv->objeto_verdadero;
    break;
  case JSON_FALSE:
    return mv->objeto_falso;
    break;
  case JSON_NULL:
    return mv->objeto_nulo;
    break;
  default:
    fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
  }
  return NULL;
}

static json_t *__latino_a_json(lat_mv *mv, lat_objeto *element) {
  json_t *value = NULL;
  switch (element->tipo) {
  case T_DICT: {
    value = json_object();
    int i;
    for (i = 0; i < 256; i++) {
      lista *list = __dic(element)->buckets[i];
      if (list != NULL) {
        LIST_FOREACH(list, primero, siguiente, cur) {
          if (cur->valor != NULL) {
            json_object_set(
                value, ((hash_val *)cur->valor)->llave,
                __latino_a_json(mv,
                                (lat_objeto *)((hash_val *)cur->valor)->valor));
          }
        }
      }
    }
    return value;
  } break;
  case T_LIST: {
    value = json_array();
    lista *list = __lista(element);
    LIST_FOREACH(list, primero, siguiente, cur) {
      if (cur->valor != NULL) {
        json_array_append_new(value,
                              __latino_a_json(mv, (lat_objeto *)cur->valor));
      }
    }
    return value;
  } break;
  case T_STR: {
    value = json_string(strdup(__cadena(element)));
    return value;
  } break;
  case T_NUMERIC: {
    double d = __numerico(element);
    if (fmod(d, 1) == 0) {
      value = json_integer((int)__numerico(element));
    } else {
      value = json_real(__numerico(element));
    }
    return value;
  } break;
  case T_BOOL: {
    if (__logico(element)) {
      value = json_true();
    } else {
      value = json_false();
    }
    return value;
  } break;
  case T_NULL: {
    value = json_null();
    return value;
  } break;
  default: {
    value = json_null();
    return value;
  }
  }
}

static void __registrar_cfuncion(lat_mv *vm, char *palabra_reservada,
                                 void (*function)(lat_mv *vm), int num_params) {
  lat_objeto *ctx = lat_obtener_contexto(vm);
  lat_objeto *nombre = lat_cadena_nueva(vm, palabra_reservada);
  lat_objeto *cfun = lat_definir_cfuncion(vm, function);
  cfun->nombre_cfun = palabra_reservada;
  cfun->num_params = num_params;
  lat_asignar_contexto_objeto(ctx, nombre, cfun);
  lista *oo = __lista(vm->otros_objetos);
  __lista_apilar(oo, nombre);
  __lista_apilar(oo, cfun);
}

const char *__obtener_bytecode_nombre(int inst) { return bycode_nombre[inst]; }

lat_objeto *__lista_obtener_elemento(lista *list, int pos) {
  if (pos < 0 || pos >= __lista_longitud(list)) {
    lat_fatal_error("Indice fuera de rango");
  }
  int i = 0;
  LIST_FOREACH(list, primero, siguiente, cur) {
    if (i == pos) {
      return (lat_objeto *)cur->valor;
    }
    i++;
  }
  return NULL;
}

lista_nodo *__lista_obtener_nodo(lista *list, int pos) {
  if (pos < 0 || pos >= __lista_longitud(list)) {
    lat_fatal_error("Indice fuera de rango");
  }
  int i = 0;
  LIST_FOREACH(list, primero, siguiente, cur) {
    if (i == pos) {
      return cur;
    }
    i++;
  }
  return NULL;
}

lat_mv *lat_mv_crear() {
  // printf("creando mv\n");
  lat_mv *mv = (lat_mv *)__memoria_asignar(sizeof(lat_mv));
  mv->memoria_usada = sizeof(lat_mv);
  mv->modulos = lat_lista_nueva(mv, __lista_crear());
  mv->gc_objetos = lat_lista_nueva(mv, __lista_crear());
  mv->otros_objetos = lat_lista_nueva(mv, __lista_crear());
  mv->pila = lat_lista_nueva(mv, __lista_crear());
  mv->argv = lat_lista_nueva(mv, __lista_crear());
  mv->objeto_verdadero = lat_logico_nuevo(mv, true);
  mv->objeto_falso = lat_logico_nuevo(mv, false);
  mv->objeto_nulo = lat_crear_objeto(mv);
  memset(mv->contexto_pila, 0, 256);
  mv->contexto_pila[0] = lat_contexto_nuevo(mv);
  mv->apuntador_ctx = 0;

  /**
   * 10 Operadores
   * 20 funciones matematicas
   * 30 funciones para cadenas (string)
   * 40 entrada y salida
   * 50 conversion de tipos de dato
   * 60 funciones para listas
   * 70
   * 99 otras funciones // a crear una categoria para ellas
   *
   */

  /*10 Operadores */

  /*20 funciones matematicas */
  __registrar_cfuncion(mv, "arco_coseno", lat_arco_coseno, 1);
  __registrar_cfuncion(mv, "arco_seno", lat_arco_seno, 1);
  __registrar_cfuncion(mv, "arco_tangente", lat_arco_tangente, 1);
  __registrar_cfuncion(mv, "arco_tangente2", lat_arco_tangente2, 2);
  __registrar_cfuncion(mv, "coseno", lat_coseno, 1);
  __registrar_cfuncion(mv, "coseno_hiperbolico", lat_coseno_hiperbolico, 1);
  __registrar_cfuncion(mv, "seno", lat_seno, 1);
  __registrar_cfuncion(mv, "seno_hiperbolico", lat_seno_hiperbolico, 1);
  __registrar_cfuncion(mv, "tangente", lat_tangente, 1);
  __registrar_cfuncion(mv, "tangente_hiperbolica", lat_tangente_hiperbolica, 1);
  __registrar_cfuncion(mv, "exponente", lat_exponente, 1);
  __registrar_cfuncion(mv, "logaritmo_natural", lat_logaritmo_natural, 1);
  __registrar_cfuncion(mv, "logaritmo_base10", lat_logaritmo_base10, 1);
  __registrar_cfuncion(mv, "potencia", lat_potencia, 2);
  __registrar_cfuncion(mv, "raiz_cuadrada", lat_raiz_cuadrada, 1);
  __registrar_cfuncion(mv, "redondear_arriba", lat_redondear_arriba, 1);
  __registrar_cfuncion(mv, "valor_absoluto", lat_valor_absoluto, 1);
  __registrar_cfuncion(mv, "redondear_abajo", lat_redondear_abajo, 1);
  __registrar_cfuncion(mv, "modulo", __modulo, 1);
  __registrar_cfuncion(mv, "aleatorio", lat_aleatorio, 2);

  /*30 funciones para cadenas (string)*/
  __registrar_cfuncion(mv, "comparar", lat_comparar, 2);
  __registrar_cfuncion(mv, "concatenar", lat_concatenar, 2);
  __registrar_cfuncion(mv, ".", lat_concatenar, 2);
  __registrar_cfuncion(mv, "contiene", lat_contiene, 2);
  __registrar_cfuncion(mv, "termina_con", lat_termina_con, 2);
  __registrar_cfuncion(mv, "es_igual", lat_es_igual, 2);
  __registrar_cfuncion(mv, "indice", lat_indice, 2);
  __registrar_cfuncion(mv, "insertar", lat_insertar, 3);
  __registrar_cfuncion(mv, "ultimo_indice", lat_ultimo_indice, 2);
  __registrar_cfuncion(mv, "rellenar_izquierda", lat_rellenar_izquierda, 3);
  __registrar_cfuncion(mv, "rellenar_derecha", lat_rellenar_derecha, 3);
  __registrar_cfuncion(mv, "eliminar", lat_eliminar, 2);
  __registrar_cfuncion(mv, "esta_vacia", lat_esta_vacia, 1);
  __registrar_cfuncion(mv, "longitud", lat_longitud, 1);
  __registrar_cfuncion(mv, "reemplazar", lat_reemplazar, 3);
  __registrar_cfuncion(mv, "empieza_con", lat_empieza_con, 2);
  __registrar_cfuncion(mv, "subcadena", lat_subcadena, 3);
  __registrar_cfuncion(mv, "minusculas", lat_minusculas, 1);
  __registrar_cfuncion(mv, "mayusculas", lat_mayusculas, 1);
  __registrar_cfuncion(mv, "quitar_espacios", lat_quitar_espacios, 1);
  __registrar_cfuncion(mv, "es_numerico", lat_es_numerico, 1);
  __registrar_cfuncion(mv, "es_numero", lat_es_numerico, 1); // alias
  __registrar_cfuncion(mv, "es_alfanumerico", lat_es_alfanumerico, 1);
  __registrar_cfuncion(mv, "ejecutar", lat_ejecutar, 1);
  __registrar_cfuncion(mv, "ejecutar_archivo", lat_ejecutar_archivo, 1);
  __registrar_cfuncion(mv, "separar", lat_separar, 2);
  __registrar_cfuncion(mv, "separar_en_palabras", lat_separar, 2);

  /*40 entrada / salida */
  __registrar_cfuncion(mv, "imprimir", lat_imprimir, 2);
  __registrar_cfuncion(mv, "escribir", lat_imprimir, 2);
  __registrar_cfuncion(mv, "leer", lat_leer, 0);
  __registrar_cfuncion(mv, "leer_archivo", lat_leer_archivo, 1);
  __registrar_cfuncion(mv, "escribir_archivo", lat_escribir_archivo, 2);
  __registrar_cfuncion(mv, "salir", lat_salir, 0);
  __registrar_cfuncion(mv, "copiar_texto", lat_copiar_texto, 2);
  __registrar_cfuncion(mv, "leer_lineas", lat_leer_lineas, 1);
  __registrar_cfuncion(mv, "invertir", lat_invertir_cadena, 1);
  __registrar_cfuncion(mv, "fecha", lat_fecha, 1);

  /*50 conversion de tipos de dato*/
  __registrar_cfuncion(mv, "tipo", lat_tipo, 1);
  __registrar_cfuncion(mv, "logico", lat_logico, 1);
  __registrar_cfuncion(mv, "decimal", lat_numerico, 1);
  __registrar_cfuncion(mv, "cadena", lat_cadena, 1);

  /*60 funciones para listas*/
  __registrar_cfuncion(mv, "agregar", lat_agregar, 2);
  __registrar_cfuncion(mv, "extender", lat_extender, 2);
  __registrar_cfuncion(mv, "eliminar_indice", lat_eliminar_indice, 2);
  __registrar_cfuncion(mv, "invertir_lista", lat_invertir_lista, 1);

  /*99 otras funciones */
  __registrar_cfuncion(mv, "sistema", lat_sistema, 1);
  __registrar_cfuncion(mv, "ejecutar_pipe", lat_ejecutar_pipe, 1);
  __registrar_cfuncion(mv, "json_decodificar", lat_json_decodificar, 1);
  __registrar_cfuncion(mv, "json_codificar", lat_json_codificar, 1);
  __registrar_cfuncion(mv, "peticion", lat_peticion, 1);
  __registrar_cfuncion(mv, "limpiar", lat_limpiar, 0);
  __registrar_cfuncion(mv, "dormir", lat_dormir, 1);

  /* Redis funciones */
  __registrar_cfuncion(mv, "redis_asignar", lat_redis_asignar, 3);
  __registrar_cfuncion(mv, "redis_obtener", lat_redis_obtener, 2);
  __registrar_cfuncion(mv, "redis_conectar", lat_redis_conectar, 2);
  __registrar_cfuncion(mv, "redis_liberar", lat_redis_liberar, 1);

  return mv;
}

void lat_destruir_mv(lat_mv *mv) {
  lat_eliminar_objeto(mv, mv->argv);
  lat_eliminar_objeto(mv, mv->modulos);
  lat_eliminar_objeto(mv, mv->gc_objetos);
  lat_eliminar_objeto(mv, mv->otros_objetos);
  lat_eliminar_objeto(mv, mv->objeto_verdadero);
  lat_eliminar_objeto(mv, mv->objeto_falso);
  lat_eliminar_objeto(mv, mv->objeto_nulo);
  if (mv->contexto_pila[0] != NULL) {
    lat_eliminar_objeto(mv, mv->contexto_pila[0]);
  }
  // lat_eliminar_objeto(mv, mv->pila);
  __memoria_liberar(mv);
}

void lat_apilar(lat_mv *vm, lat_objeto *o) {
  __lista_apilar(__lista(vm->pila), (void *)o);
}

lat_objeto *lat_desapilar(lat_mv *vm) {
  return (lat_objeto *)__lista_desapilar(__lista(vm->pila));
}

lat_objeto *lat_tope(lat_mv *vm) {
  if ((lat_objeto *)vm->pila->datos.lista->ultimo)
    return (lat_objeto *)vm->pila->datos.lista->ultimo->valor;

  return NULL;
}

void lat_apilar_contexto(lat_mv *vm) {
  // printf("apilando contexto...\n");
  if (vm->apuntador_ctx >= MAX_STACK_SIZE) {
    lat_fatal_error("Namespace desborde de la pila");
  }
  vm->contexto_pila[vm->apuntador_ctx + 1] =
      lat_clonar_objeto(vm, vm->contexto_pila[vm->apuntador_ctx]);
  vm->apuntador_ctx++;
}

void lat_desapilar_contexto(lat_mv *vm) {
  // printf("...desapilando contexto\n");
  if (vm->apuntador_ctx == 0) {
    lat_fatal_error("Namespace pila vacia");
  }
  lat_eliminar_objeto(vm, vm->contexto_pila[vm->apuntador_ctx--]);
}

lat_objeto *lat_obtener_contexto(lat_mv *vm) {
  return vm->contexto_pila[vm->apuntador_ctx];
}

lat_objeto *lat_definir_funcion(lat_mv *vm, lat_bytecode *inslist,
                                int num_inst) {
  lat_objeto *ret = lat_funcion_nueva(vm);
  lat_function *fval = (lat_function *)__memoria_asignar(sizeof(lat_function));
  fval->bcode = inslist;
  ret->datos.fun_usuario = fval;
  ret->num_inst = num_inst;
  return ret;
}

lat_objeto *lat_definir_cfuncion(lat_mv *vm, void (*function)(lat_mv *vm)) {
  lat_objeto *ret = lat_cfuncion_nueva(vm);
  ret->datos.c_funcion = function;
  return ret;
}

void __imprimir_objeto(lat_mv *vm, lat_objeto *in, bool fmt) {
  char *tmp1 = NULL;
  if (in->tipo != T_STR) {
    tmp1 = __objeto_a_cadena(in);
    char *tmp2;
    if (fmt) {
      tmp2 = __str_analizar_fmt(tmp1, strlen(tmp1));
    } else {
      tmp2 = __str_analizar(tmp1, strlen(tmp1));
    }
    fprintf(stdout, "%s", tmp2);
    // wprintf(stdout, "%s", tmp2);
    __memoria_liberar(tmp2);
  } else {
    char *s = __cadena(in);
    if (fmt) {
      tmp1 = __str_analizar_fmt(s, strlen(s));
    } else {
      tmp1 = __str_analizar(s, strlen(s));
    }
    fprintf(stdout, "%s", tmp1);
    // fprintf(stdout, "%s", s);
    // return;
  }
  __memoria_liberar(tmp1);
}

void lat_imprimir(lat_mv *vm) {
  lat_objeto *f = lat_desapilar(vm);
  bool fmt = false;
  if (f == NULL) {
    printf("nulo");
  } else {
    // Lat_DECREF(o);
    lat_objeto *o = lat_desapilar(vm);
    if (f->tipo != T_NULL) {
      fmt = __objeto_a_logico(f);
    }
    __imprimir_objeto(vm, o, fmt);
  }
  printf("\n");
}

void __imprimir_lista(lat_mv *vm, lista *l, bool fmt) {
  char *tmp1 = __lista_a_cadena(l);
  // fprintf(stdout, "%s", tmp1);
  if (fmt) {
    fprintf(stdout, "%s", __str_analizar_fmt(tmp1, strlen(tmp1)));
  } else {
    fprintf(stdout, "%s", __str_analizar(tmp1, strlen(tmp1)));
  }
  __memoria_liberar(tmp1);
}

void lat_ejecutar(lat_mv *vm) {
  int status;
  lat_objeto *func = nodo_analizar_arbol(
      vm, lat_analizar_expresion(__cadena(lat_desapilar(vm)), &status));
  lat_llamar_funcion(vm, func);
}

void lat_ejecutar_archivo(lat_mv *vm) {
  char *input = __cadena(lat_desapilar(vm));
  char *dot = strrchr(input, '.');
  char *extension;
  if (!dot || dot == input) {
    extension = "";
  } else {
    extension = dot + 1;
  }
  if (strcmp(extension, "lat") == 0) {
    int status;
    ast *tree = lat_analizar_archivo(input, &status);
    if (!tree) {
      lat_fatal_error("Al leer el archivo: %s", input);
    }
    lat_objeto *func = nodo_analizar_arbol(vm, tree);
    lat_llamar_funcion(vm, func);
  }
}

void __menos_unario(lat_mv *vm) {
  lat_objeto *o = lat_desapilar(vm);
  lat_objeto *r = lat_numerico_nuevo(vm, (-1) * __objeto_a_numerico(o));
  Lat_DECREF(o);
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void __sumar(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  lat_objeto *r =
      lat_numerico_nuevo(vm, __objeto_a_numerico(a) + __objeto_a_numerico(b));
  lat_apilar(vm, r);
  Lat_DECREF(b);
  Lat_DECREF(a);
  __colector_agregar(vm, r);
}

void __restar(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r =
      lat_numerico_nuevo(vm, __objeto_a_numerico(a) - __objeto_a_numerico(b));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void __multiplicar(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r =
      lat_numerico_nuevo(vm, __objeto_a_numerico(a) * __objeto_a_numerico(b));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void __dividir(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  if (__objeto_a_numerico(b) == 0) {
    lat_fatal_error("Linea %d, %d: %s", b->num_linea, b->num_columna,
                    "Division entre cero");
  }
  lat_objeto *r =
      lat_numerico_nuevo(vm, (__objeto_a_numerico(a) / __objeto_a_numerico(b)));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void __modulo(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  if (__objeto_a_numerico(b) == 0) {
    lat_fatal_error("Linea %d, %d: %s", b->num_linea, b->num_columna,
                    "Modulo entre cero");
  }
  lat_objeto *r = lat_numerico_nuevo(
      vm, fmod(__objeto_a_numerico(a), __objeto_a_numerico(b)));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void __igualdad(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  switch (a->tipo) {
  case T_BOOL: {
    r = __logico(a) == __objeto_a_logico(b) ? vm->objeto_verdadero
                                            : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  } break;
  case T_NUMERIC: {
    r = (__numerico(a) == __objeto_a_numerico(b)) ? vm->objeto_verdadero
                                                  : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  } break;
  case T_STR: {
    r = strcmp(__cadena(a), __objeto_a_cadena(b)) == 0 ? vm->objeto_verdadero
                                                       : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  } break;
  default:
    r = strcmp(__objeto_a_cadena(a), __objeto_a_cadena(b)) == 0
            ? vm->objeto_verdadero
            : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  }
  r = vm->objeto_falso;
  lat_apilar(vm, r);
}

void __diferente(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  switch (a->tipo) {
  case T_BOOL: {
    r = __logico(a) != __objeto_a_logico(b) ? vm->objeto_verdadero
                                            : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  } break;
  case T_NUMERIC: {
    r = (__numerico(a) != __objeto_a_numerico(b)) ? vm->objeto_verdadero
                                                  : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  } break;
  case T_STR: {
    r = strcmp(__cadena(a), __objeto_a_cadena(b)) != 0 ? vm->objeto_verdadero
                                                       : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  } break;
  default:
    r = strcmp(__objeto_a_cadena(a), __objeto_a_cadena(b)) != 0
            ? vm->objeto_verdadero
            : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  }
  r = vm->objeto_falso;
  lat_apilar(vm, r);
}

void __menor_que(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (__objeto_a_numerico(a) < __objeto_a_numerico(b)) ? vm->objeto_verdadero
                                                          : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  }
  r = __objeto_comparar(a, b) < 0 ? vm->objeto_verdadero : vm->objeto_falso;
  lat_apilar(vm, r);
  return;
}

void __menor_igual(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (__objeto_a_numerico(a) <= __objeto_a_numerico(b))
            ? vm->objeto_verdadero
            : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  }
  r = __objeto_comparar(a, b) <= 0 ? vm->objeto_verdadero : vm->objeto_falso;
  lat_apilar(vm, r);
  return;
}

void __mayor_que(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (__objeto_a_numerico(a) > __objeto_a_numerico(b)) ? vm->objeto_verdadero
                                                          : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  }
  r = __objeto_comparar(a, b) > 0 ? vm->objeto_verdadero : vm->objeto_falso;
  lat_apilar(vm, r);
  return;
}

void __mayor_igual(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
    r = (__objeto_a_numerico(a) >= __objeto_a_numerico(b))
            ? vm->objeto_verdadero
            : vm->objeto_falso;
    lat_apilar(vm, r);
    return;
  }
  r = __objeto_comparar(a, b) >= 0 ? vm->objeto_verdadero : vm->objeto_falso;
  lat_apilar(vm, r);
  return;
}

void __y_logico(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  if (__objeto_a_logico(a)) {
    r = b;
  } else {
    r = a;
  }
  lat_apilar(vm, r);
}

void __o_logico(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  Lat_DECREF(b);
  Lat_DECREF(a);
  lat_objeto *r = NULL;
  if (__objeto_a_logico(a)) {
    r = a;
  } else {
    r = b;
  }
  lat_apilar(vm, r);
}

void __no_logico(lat_mv *vm) {
  lat_objeto *o = lat_desapilar(vm);
  Lat_DECREF(o);
  lat_objeto *r =
      (__objeto_a_logico(o) == false) ? vm->objeto_verdadero : vm->objeto_falso;
  lat_apilar(vm, r);
}

void lat_logico(lat_mv *vm) {
  lat_objeto *o = lat_desapilar(vm);
  lat_objeto *r =
      __objeto_a_logico(o) == true ? vm->objeto_verdadero : vm->objeto_falso;
  lat_apilar(vm, r);
}

void lat_numerico(lat_mv *vm) {
  lat_objeto *o = lat_desapilar(vm);
  Lat_DECREF(o);
  lat_objeto *r = lat_numerico_nuevo(vm, __objeto_a_numerico(o));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void lat_cadena(lat_mv *vm) {
  lat_objeto *o = lat_desapilar(vm);
  Lat_DECREF(o);
  lat_objeto *r = lat_cadena_nueva(vm, __objeto_a_cadena(o));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

char *__tipo(int tipo) {
  switch (tipo) {
  case T_NULL:
    return "nulo";
    break;
  case T_BOOL:
    return "logico";
    break;
  case T_NUMERIC:
    return "decimal";
    break;
  case T_STR:
    return "cadena";
    break;
  case T_LIST:
    return "lista";
    break;
  case T_DICT:
    return "diccionario";
    break;
  case T_FUNC:
    return "funcion";
    break;
  case T_CFUNC:
    return "cfuncion";
    break;
  default:
    return "indefinido";
    break;
  }
}

void lat_tipo(lat_mv *vm) {
  lat_objeto *a = lat_desapilar(vm);
  lat_objeto *r = lat_cadena_nueva(vm, __tipo(a->tipo));
  lat_apilar(vm, r);
  __colector_agregar(vm, r);
}

void lat_salir(lat_mv *vm) {
  // lat_apilar(vm, lat_entero_nuevo(vm, 0L));
  exit(0);
}

lat_bytecode lat_bc(int i, int a, int b, void *meta) {
  lat_bytecode ret;
  ret.ins = i;
  ret.a = a;
  ret.b = b;
  ret.meta = meta;
  return ret;
}

void lat_llamar_funcion(lat_mv *vm, lat_objeto *func) {
  if (func->tipo == T_FUNC) {
#if DEPURAR_MV
    printf("\n.::Ejecutando funcion::.\n");
#endif
    lat_asignar_contexto_objeto(lat_obtener_contexto(vm),
                                lat_cadena_nueva(vm, "lat_main"), func);
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
        __menos_unario(vm);
      } break;
      case INC: {
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(vm);
        lat_objeto *val = lat_obtener_contexto_objeto(ctx, name);
        Lat_DECREF(val);
        lat_objeto *tmp = lat_clonar_objeto(vm, val);
        tmp->datos.numerico++;
        lat_asignar_contexto_objeto(ctx, name, tmp);
        __colector_agregar(vm, tmp);
      } break;
      case DEC: {
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(vm);
        lat_objeto *val = lat_obtener_contexto_objeto(ctx, name);
        Lat_DECREF(val);
        lat_objeto *tmp = lat_clonar_objeto(vm, val);
        tmp->datos.numerico--;
        lat_asignar_contexto_objeto(ctx, name, tmp);
        __colector_agregar(vm, tmp);
      } break;
      case BINARY_ADD: {
        __sumar(vm);
      } break;
      case BINARY_SUB: {
        __restar(vm);
      } break;
      case BINARY_MUL: {
        __multiplicar(vm);
      } break;
      case BINARY_DIV: {
        __dividir(vm);
      } break;
      case BINARY_MOD: {
        __modulo(vm);
      } break;
      case OP_GT: {
        __mayor_que(vm);
      } break;
      case OP_GE: {
        __mayor_igual(vm);
      } break;
      case OP_LT: {
        __menor_que(vm);
      } break;
      case OP_LE: {
        __menor_igual(vm);
      } break;
      case OP_EQ: {
        __igualdad(vm);
      } break;
      case OP_NEQ: {
        __diferente(vm);
      } break;
      case OP_AND: {
        __y_logico(vm);
      } break;
      case OP_OR: {
        __o_logico(vm);
      } break;
      case OP_NOT: {
        __no_logico(vm);
      } break;
      case CONCAT: {
        lat_concatenar(vm);
      } break;
      case LOAD_CONST: {
        lat_objeto *o = (lat_objeto *)cur.meta;
#if DEPURAR_MV
        __imprimir_objeto(vm, o, false);
        printf("\t");
#endif
        lat_apilar(vm, o);
      } break;
      case STORE_NAME: {
        lat_objeto *val = lat_desapilar(vm);
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(vm);
        Lat_INCREF(val);
#if DEPURAR_MV
        __imprimir_objeto(vm, name, false);
        printf("\t");
#endif
        // objeto anterior
        lat_objeto *tmp = lat_obtener_contexto_objeto(ctx, name);
        if (tmp != NULL) {
          Lat_DECREF(tmp);
        }
        if (name->es_constante) {
          if (tmp != NULL) {
            lat_fatal_error(
                "Linea %d, %d: Intento de reasignar valor a constante '%s'",
                name->num_linea, name->num_columna, __cadena(name));
          }
        }
        // asigna el numero de parametros
        if (name->nombre_cfun) {
          val->num_params = name->num_params;
          val->nombre_cfun = name->nombre_cfun;
        }
        lat_asignar_contexto_objeto(ctx, name, val);
      } break;
      case LOAD_NAME: {
        lat_objeto *name = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(vm);
#if DEPURAR_MV
        __imprimir_objeto(vm, name, false);
        printf("\t");
#endif
        lat_objeto *val = lat_obtener_contexto_objeto(ctx, name);
        if (val == NULL) {
          lat_fatal_error("Linea %d, %d: Variable \"%s\" indefinida",
                          name->num_linea, name->num_columna, __cadena(name));
        }
        val->num_linea = name->num_linea;
        val->num_columna = name->num_columna;
        lat_apilar(vm, val);
      } break;
      case POP_JUMP_IF_FALSE: {
        lat_objeto *o = lat_desapilar(vm);
        if (__objeto_a_logico(o) == false) {
          pos = cur.a;
        }
      } break;
      case POP_JUMP_IF_TRUE: {
        lat_objeto *o = lat_desapilar(vm);
        if (__objeto_a_logico(o) == true) {
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
        lat_objeto *fun = lat_desapilar(vm);
        if (num_args != fun->num_params) {
          /*si se envian menos parametros se acompletan con nulos*/
          while (num_args < fun->num_params) {
            lat_apilar(vm, vm->objeto_nulo);
            num_args++;
          }
          if (num_args != fun->num_params) {
            lat_fatal_error("Linea %d, %d: Numero invalido de argumentos en "
                            "funcion '%s'. se esperaban %i valores.\n",
                            fun->num_linea, fun->num_columna, fun->nombre_cfun,
                            fun->num_params);
          }
        }
        lat_apilar_contexto(vm);
        vm->num_callf++;
        if (vm->num_callf >= MAX_CALL_FUNCTION) {
          lat_fatal_error("Linea %d, %d: Numero maximo de llamadas a funciones "
                          "recursivas excedido en '%s'\n",
                          fun->num_linea, fun->num_columna, fun->nombre_cfun);
        }
        lat_llamar_funcion(vm, fun);
        vm->num_callf--;
        lat_desapilar_contexto(vm);
      } break;
      case RETURN_VALUE: {
        return;
      } break;
      case MAKE_FUNCTION: {
        lat_objeto *fun =
            lat_definir_funcion(vm, (lat_bytecode *)cur.meta, cur.a);
        lat_apilar(vm, fun);
      } break;
      case SETUP_LOOP:
        // lat_apilar_contexto(vm);
        break;
      case POP_BLOCK:
        // lat_desapilar_contexto(vm);
        break;
      case BUILD_LIST: {
        int num_elem = cur.a;
        int i;
        lista *l = __lista_crear();
        for (i = 0; i < num_elem; i++) {
          lat_objeto *tmp = lat_desapilar(vm);
          __lista_apilar(l, tmp);
        }
        lat_objeto *obj = lat_lista_nueva(vm, l);
        lat_apilar(vm, obj);
      } break;
      case LOAD_ATTR: {
        lat_objeto *obj = lat_desapilar(vm);
        lat_objeto *attr = (lat_objeto *)cur.meta;
        lat_objeto *ctx = lat_obtener_contexto(vm);
        lat_objeto *val = NULL;
#if DEPURAR_MV
        __imprimir_objeto(vm, attr, false);
        printf("\t");
#endif
        val = lat_obtener_contexto_objeto(ctx, attr);
        if (val != NULL && val->tipo == T_CFUNC) {
          val->num_linea = attr->num_linea;
          val->num_columna = attr->num_columna;
          lista *list = __lista_crear();
          int i;
          for (i = 0; i < val->num_params - 1; i++) {
            __lista_insertar_inicio(list, (void *)lat_desapilar(vm));
          }
          lat_apilar(vm, obj);
          LIST_FOREACH(list, primero, siguiente, cur) {
            lat_apilar(vm, (lat_objeto *)cur->valor);
          }
          lat_apilar(vm, val);
          __memoria_liberar(list);
        } else {
          if (obj->tipo == T_DICT) {
            val = (lat_objeto *)__dic_obtener(__dic(obj), __cadena(attr));
            if (val != NULL) {
              lat_apilar(vm, val);
              break;
            } else {
              val = lat_cadena_nueva(vm, strdup(""));
              lat_apilar(vm, val);
            }
          }
          lat_objeto *top = lat_tope(vm);
          if (top && (next.ins == BINARY_SUBSCR)) {
            if (top->tipo == T_STR) {
              if (obj->tipo != T_DICT) {
                obj = lat_dic_nuevo(vm, __dic_crear());
                __dic_asignar(__dic(obj), strdup(__cadena(attr)), (void *)val);
                lat_apilar(vm, obj);
                break;
              }
            }
            if (top->tipo == T_NUMERIC) {
              if (obj->tipo != T_LIST) {
                obj = lat_lista_nueva(vm, __lista_crear());
                lat_apilar(vm, obj);
                break;
              }
            }
          }
          val = lat_cadena_nueva(vm, strdup(""));
          lat_apilar(vm, val);
        }
      } break;
      case STORE_SUBSCR: {
        lat_objeto *pos = lat_desapilar(vm);
        lat_objeto *lst = lat_desapilar(vm);
        lat_objeto *exp = lat_desapilar(vm);
        if (lst->tipo == T_DICT) {
          __dic_asignar(__dic(lst), __cadena(pos), (void *)exp);
          break;
        }
        int ipos = __numerico(pos);
        if (lst->tipo == T_STR) {
          char *slst = __cadena(lst);
          if (ipos < 0 || ipos >= strlen(slst)) {
            lat_fatal_error("Linea %d, %d: Indice fuera de rango.",
                            pos->num_linea, pos->num_columna);
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
            lat_fatal_error("Linea %d, %d: Indice fuera de rango.",
                            pos->num_linea, pos->num_columna);
          }
          __lista_modificar_elemento(__lista(lst), exp, ipos);
        }
      } break;
      case BINARY_SUBSCR: {
        lat_objeto *obj = lat_desapilar(vm);
        lat_objeto *pos = lat_desapilar(vm);
        lat_objeto *o = NULL;
        if (obj->tipo == T_DICT) {
          o = __dic_obtener(__dic(obj), __cadena(pos));
          if (o == NULL) {
            lat_fatal_error(
                "Linea %d, %d: No se encontro la llave '%s' en el diccionario.",
                pos->num_linea, pos->num_columna, __cadena(pos));
          }
          lat_apilar(vm, o);
          break;
        }
        int ipos = __numerico(pos);
        if (obj->tipo == T_STR) {
          char *slst = __cadena(obj);
          if (ipos < 0 || ipos >= strlen(slst)) {
            lat_fatal_error("Linea %d, %d: Indice fuera de rango.",
                            pos->num_linea, pos->num_columna);
          }
          char c[2] = {slst[ipos], '\0'};
          o = lat_cadena_nueva(vm, c);
        }
        if (obj->tipo == T_LIST) {
          if (ipos < 0 || ipos >= __lista_longitud(__lista(obj))) {
            o = lat_cadena_nueva(vm, "");
            lat_apilar(vm, o);
            break;
            /*lat_fatal_error("Linea %d, %d: Indice fuera de rango.",
                    pos->num_linea, pos->num_columna);*/
          }
          o = __lista_obtener_elemento(__lista(obj), __numerico(pos));
        }
        lat_apilar(vm, o);
      } break;
      case BUILD_MAP: {
        lat_objeto *o = lat_dic_nuevo(vm, __dic_crear());
        lat_apilar(vm, o);
      } break;
      case STORE_MAP: {
        lat_objeto *key = lat_desapilar(vm);
        lat_objeto *val = lat_desapilar(vm);
        lat_objeto *dic = lat_tope(vm);
        while (dic && dic->tipo != T_DICT) {
          lat_desapilar(vm);
          dic = lat_tope(vm);
        }
        __dic_asignar(__dic(dic), __cadena(key), (void *)val);
      } break;
      case STORE_ATTR: {
        lat_objeto *attr = lat_desapilar(vm);
        lat_objeto *obj = lat_desapilar(vm);
        lat_objeto *val = lat_desapilar(vm);
        if (obj->tipo == T_DICT) {
          __dic_asignar(__dic(obj), __cadena(attr), (void *)val);
        }
      } break;

      } // fin de switch

#if DEPURAR_MV
      __imprimir_lista(vm, __lista(vm->pila), false);
      printf("\n");
#endif
    } // fin for
  }   // fin if (T_FUNC)
  else if (func->tipo == T_CFUNC) {
    ((void (*)(lat_mv *))(func->datos.fun_usuario))(vm);
  } else {
    lat_fatal_error("Linea %d, %d: %s", func->num_linea, func->num_columna,
                    "El objeto no es una funcion");
  }
}

/* funciones para listas */
int __lista_obtener_indice(lista *list, void *data) {
  int i = 0;
  lat_objeto *find = (lat_objeto *)data;
  LIST_FOREACH(list, primero, siguiente, cur) {
    // if (memcmp(cur->valor, data, sizeof(cur->valor)) == 0)
    lat_objeto *tmp = (lat_objeto *)cur->valor;
    if (__es_igual(find, tmp)) {
      return i;
    }
    i++;
  }
  return -1;
}

void __lista_insertar_elemento(lista *list, void *data, int pos) {
  int len = __lista_longitud(list);
  if (pos < 0 || pos > len) // permite insertar al ultimo
  {
    lat_fatal_error("Indice fuera de rango");
  }
  if (pos == 0) {
    __lista_insertar_inicio(list, data);
    return;
  }
  if (pos == len) {
    __lista_apilar(list, data);
    return;
  }
  // FIX: For performance
  lista *tmp1 = __lista_crear();
  lista *tmp2 = __lista_crear();
  int i = 0;
  LIST_FOREACH(list, primero, siguiente, cur) {
    if (i < pos) {
      __lista_apilar(tmp1, cur->valor);
    } else {
      __lista_apilar(tmp2, cur->valor);
    }
    i++;
  }
  lista *new = __lista_crear();
  __lista_extender(new, tmp1);
  __lista_apilar(new, data);
  __lista_extender(new, tmp2);
  *list = *new;
  __memoria_liberar(tmp1);
  __memoria_liberar(tmp2);
}

void lat_agregar(lat_mv *vm) {
  lat_objeto *elem = lat_desapilar(vm);
  lat_objeto *lst = lat_desapilar(vm);
  __lista_apilar(__lista(lst), elem);
}

void lat_extender(lat_mv *vm) {
  lat_objeto *l2 = lat_desapilar(vm);
  lat_objeto *lst = lat_desapilar(vm);
  if (lst->tipo != T_LIST) {
    lat_fatal_error("Linea %d, %d: %s", lst->num_linea, lst->num_columna,
                    "El objeto no es una lista");
  }
  if (l2->tipo != T_LIST) {
    lat_fatal_error("Linea %d, %d: %s", l2->num_linea, l2->num_columna,
                    "El objeto no es una lista");
  }
  lista *_lst2 = __lista(l2);
  lista *_lst = __lista(lst);
  __lista_extender(_lst, _lst2);
}

void lat_eliminar_indice(lat_mv *vm) {
  lat_objeto *b = lat_desapilar(vm);
  lat_objeto *a = lat_desapilar(vm);
  lista *lst = __lista(a);
  int pos = __numerico(b);
  if (pos < 0 || pos >= __lista_longitud(lst)) {
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,
                    "Indice fuera de rango");
  }
  if (pos >= 0) {
    lista_nodo *nt = __lista_obtener_nodo(lst, pos);
    __lista_eliminar_elemento(lst, nt);
  }
}

void lat_invertir_lista(lat_mv *vm) {
  lat_objeto *a = lat_desapilar(vm);
  lista *lst = __lista(a);
  lista *new = __lista_crear();
  // FIX: For performance
  int i;
  int len = __lista_longitud(lst) - 1;
  for (i = len; i >= 0; i--) {
    __lista_apilar(new, __lista_obtener_elemento(lst, i));
  }
  lat_apilar(vm, lat_lista_nueva(vm, new));
}

void lat_json_decodificar(lat_mv *vm) {
  lat_objeto *a = lat_desapilar(vm);
  char *str = __cadena(a);
  json_t *root = __cargar_json(str);
  lat_objeto *o = NULL;

  if (root) {
    o = __json_a_latino(vm, root);
    json_decref(root);
  }
  lat_apilar(vm, o);
}

void lat_json_codificar(lat_mv *vm) {
  lat_objeto *a = lat_desapilar(vm);
  lat_objeto *r = NULL;
  json_t *j = __latino_a_json(vm, a);
  char *s = json_dumps(j, 0);
  r = lat_cadena_nueva(vm, strdup(s));
  lat_apilar(vm, r);
}
