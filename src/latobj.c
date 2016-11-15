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

#include "latobj.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latdic.h"
#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"

char *__str_minusculas(const char *str);
char *__dic_a_cadena(hash_map *m);
char *__str_logico_a_cadena(int i);
char *__str_decimal_a_cadena(double d);

void __obj_asignar_contexto(lat_objeto *ns, lat_objeto *name, lat_objeto *o) {
  // printf("lat_asignar_contexto_objeto: %s\n", lat_obtener_cadena(name));
  if (ns->tipo != T_CONTEXT) {
    lat_error("Objeto no es un contexto");
  } else {
    hash_map *h = ns->datos.contexto;
    if (strlen(__cadena(name)) > MAX_ID_LENGTH) {
      lat_error("Linea %d, %d: Longitud maxima de (%i) excedida para un "
                "identificador",
                name->num_linea, name->num_columna, MAX_ID_LENGTH);
    }
    __dic_asignar(h, __cadena(name), o);
  }
}

lat_objeto *__obj_obtener_contexto(lat_objeto *ns, lat_objeto *name) {
  if (ns->tipo != T_CONTEXT) {
    lat_error("Objeto no es un contexto");
  } else {
    hash_map *h = ns->datos.contexto;
    lat_objeto *ret = (lat_objeto *)__dic_obtener(h, __cadena(name));
    return ret;
  }
  return NULL;
}

lat_objeto *__obj_crear(lat_mv *mv) {
  // printf("lat_crear_objeto\n");
  lat_objeto *ret = (lat_objeto *)__memoria_asignar(mv, sizeof(lat_objeto));
  ret->tipo = T_NULL;
  ret->tamanio = sizeof(lat_objeto);
  ret->num_ref = 0;
  return ret;
}

lat_objeto *__obj_contexto_nuevo(lat_mv *mv) {
  // printf("lat_contexto_nuevo\n");
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_CONTEXT;
  ret->tamanio += sizeof(hash_map);
  ret->datos.contexto = __dic_crear();
  return ret;
}

lat_objeto *__obj_logico_nuevo(lat_mv *mv, bool val) {
  // printf("lat_logico_nuevo: %i\n", val);
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_BOOL;
  ret->tamanio += sizeof(bool);
  ret->datos.logico = val;
  return ret;
}

lat_objeto *lat_numerico_nuevo(lat_mv *mv, double val) {
  // printf("lat_decimal_nuevo: %.14g\n", val);
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_NUMERIC;
  ret->tamanio += sizeof(double);
  ret->datos.numerico = val;
  return ret;
}

lat_objeto *lat_cadena_nueva(lat_mv *mv, char *p) {
  // printf("lat_cadena_nueva: %s\n", p);
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_STR;
  ret->tamanio += strlen(p);
  ret->datos.cadena = p;
  return ret;
}

lat_objeto *lat_lista_nueva(lat_mv *mv, lista *l) {
  // printf("lat_lista_nueva\n");
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_LIST;
  ret->tamanio += sizeof(lista);
  ret->datos.lista = l;
  return ret;
}

lat_objeto *lat_dic_nuevo(lat_mv *mv, hash_map *dic) {
  // printf("lat_dic_nuevo\n");
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_DICT;
  ret->tamanio += sizeof(hash_map);
  ret->datos.dic = dic;
  return ret;
}

lat_objeto *lat_cdato_nuevo(lat_mv *mv, void *ptr) {
  // printf("lat_cadena_nueva: %s\n", p);
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_CDATA;
  ret->datos.fun_usuario = ptr;
  return ret;
}

lat_objeto *__obj_funcion_nueva(lat_mv *mv) {
  // printf("lat_funcion_nueva\n");
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_FUNC;
  return ret; // We don't do anything here: all bytecode will be added later
}

lat_objeto *__obj_cfuncion_nueva(lat_mv *mv) {
  // printf("lat_cfuncion_nueva\n");
  lat_objeto *ret = __obj_crear(mv);
  ret->tipo = T_CFUNC;
  return ret;
}

void __obj_eliminar(lat_mv *mv, lat_objeto *o) {
  // printf("eliminando objeto %p\n", o);
  switch (o->tipo) {
  case T_CONTEXT:
    // printf("eliminando contexto...\n");
    __dic_destruir(o->datos.contexto);
    break;
  case T_LIST: {
    lista *list = __lista(o);
    /*printf("eliminando lista... %i\n", __lista_longitud(list));
    __imprimir_objeto(mv, o, false);
    printf("%s\n", "");*/
    LIST_FOREACH(list, primero, siguiente, cur) {
      lat_objeto *tmp = (lat_objeto *)cur->valor;
      if (tmp != NULL && tmp->tipo != T_LIST) {
        __obj_eliminar(mv, tmp);
      }
    }
    __lista_destruir(list);
  } break;
  case T_DICT:
    __dic_destruir(__dic(o));
    break;
  case T_STR: {
    char *s = __cadena(o);
    // printf("eliminando cadena... (%p): %s\n", s, s);
    __memoria_liberar(mv, s);
  } break;
  case T_FUNC: {
    // printf("eliminando funcion de usuario...\n");
    lat_function *fun = (lat_function *)o->datos.fun_usuario;
    lat_bytecode *inslist = fun->bcode;
    lat_bytecode cur;
    int pos;
    for (pos = 0, cur = inslist[pos]; pos < o->num_inst; cur = inslist[++pos]) {
      if (cur.meta != NULL) {
        lat_objeto *tmp = (lat_objeto *)cur.meta;
        if (tmp != NULL && cur.ins != BUILD_LIST) {
          __obj_eliminar(mv, tmp);
        }
        if (tmp != NULL && cur.ins == BUILD_LIST) {
          lista *list = __lista(tmp);
          __memoria_liberar(mv, list);
          __memoria_liberar(mv, tmp);
        }
      }
    }
    __memoria_liberar(mv, fun->bcode);
    __memoria_liberar(mv, fun);
  } break;
  case T_CFUNC: {
    // printf("eliminando cfuncion...\n");
    __memoria_liberar(mv, o->nombre_cfun);
  } break;
  /*case T_NUMERIC:{
      //printf("eliminando numerico: %.14g\n", __numerico(o));
  }
  break;*/
  case T_NULL:
  case T_BOOL:
    /* nunca colectar nulo y booleano */
    return;
  default:
    break;
  }
  __memoria_liberar(mv, o);
}

lat_objeto *__obj_clonar(lat_mv *mv, lat_objeto *obj) {
  // printf("lat_clonar_objeto\n");
  lat_objeto *ret = NULL;
  switch (obj->tipo) {
  case T_CONTEXT:
    ret = __obj_crear(mv);
    ret->tipo = T_CONTEXT;
    ret->tamanio = sizeof(hash_map *);
    ret->datos.contexto = __dic_clonar(obj->datos.contexto);
    break;
  case T_LIST:
    ret = lat_lista_nueva(mv, __lista_clonar(mv, __lista(obj)));
    break;
  case T_DICT:
    ret = lat_dic_nuevo(mv, __dic_clonar(__dic(obj)));
    break;
  case T_FUNC:
    ret = __obj_crear(mv);
    ret->tipo = obj->tipo;
    ret->datos.fun_usuario = obj->datos.fun_usuario;
    ret->num_params = obj->num_params;
    break;
  case T_CFUNC:
    ret = __obj_crear(mv);
    ret->tipo = obj->tipo;
    ret->datos.c_funcion = obj->datos.c_funcion;
    ret->num_params = obj->num_params;
    break;
  case T_STR: {
    ret = lat_cadena_nueva(mv, strdup(__cadena(obj)));
  } break;
  case T_NUMERIC:
    ret = lat_numerico_nuevo(mv, __numerico(obj));
    break;
  default:
    ret = __obj_crear(mv);
    ret->tipo = obj->tipo;
    ret->datos = obj->datos;
    break;
  }
  ret->num_ref = obj->num_ref;
  ret->marca = obj->marca;
  ret->tamanio = obj->tamanio;
  ret->num_params = obj->num_params;
  ret->num_linea = obj->num_linea;
  ret->num_columna = obj->num_columna;
  return ret;
}

lista *__lista_clonar(lat_mv *mv, lista *list) {
  lista *ret = __lista_crear();
  LIST_FOREACH(list, primero, siguiente, cur) {
    lat_objeto *tmp = (lat_objeto *)cur->valor;
    // lat_objeto* nuevo = lat_clonar_objeto(mv, tmp);
    __lista_agregar(ret, tmp);
  }
  return ret;
}

bool __logico(lat_objeto *o) {
  if (o->tipo == T_BOOL) {
    return o->datos.logico;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "El parametro debe de ser un valor logico (verdadero o falso)");
  return false;
}

double __numerico(lat_objeto *o) {
  if (o->tipo == T_NUMERIC) {
    return o->datos.numerico;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "El parametro debe de ser un decimal");
  return 0;
}

char *__cadena(lat_objeto *o) {
  if (o->tipo == T_STR) {
    return o->datos.cadena;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "El parametro debe de ser una cadena");
  return 0;
}

lista *__lista(lat_objeto *o) {
  if (o->tipo == T_LIST) {
    return o->datos.lista;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "El parametro debe de ser una lista");
  return NULL;
}

hash_map *__dic(lat_objeto *o) {
  if (o->tipo == T_DICT) {
    return o->datos.dic;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "El parametro debe de ser un diccionario");
  return NULL;
}

void *__cdato(lat_objeto *o) {
  if (o->tipo == T_CDATA) {
    return o->datos.fun_usuario;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "El parametro debe de ser un dato de c (void *)");
  return NULL;
}

bool __obj_es_igual(lat_objeto *lhs, lat_objeto *rhs) {
  if (lhs->tipo != rhs->tipo) {
    return false;
  }
  if (lhs->tipo == T_NUMERIC) {
    return __numerico(lhs) == __numerico(rhs);
  }
  if (lhs->tipo == T_STR) {
    return strcmp(__cadena(lhs), __cadena(rhs)) == 0 ? true : false;
  }
  if (lhs->tipo == T_LIST) {
    return __lista_comparar(__lista(lhs), __lista(rhs)) == 0 ? true : false;
  }
  return false;
}

int __obj_comparar(lat_objeto *lhs, lat_objeto *rhs) {
  int res = 1;
  if (lhs->tipo != rhs->tipo) {
    char *buffer = lat_obj2cstring(lhs);
    char *buffer2 = lat_obj2cstring(rhs);
    res = strcmp(buffer, buffer2);
    __memoria_liberar(NULL, buffer);
    __memoria_liberar(NULL, buffer2);
    goto RESPUESTA;
  }
  if (lhs->tipo == T_BOOL) {
    res = __logico(lhs) - __logico(rhs);
    goto RESPUESTA;
  }
  if (lhs->tipo == T_NUMERIC) {
    res = __numerico(lhs) - __numerico(rhs);
    goto RESPUESTA;
  }
  if (lhs->tipo == T_STR) {
    res = strcmp(__cadena(lhs), __cadena(rhs));
    goto RESPUESTA;
  }
  if (lhs->tipo == T_LIST) {
    res = __lista_comparar(__lista(lhs), __lista(rhs));
    goto RESPUESTA;
  }
RESPUESTA:
  if (res < 0) {
    return -1;
  }
  if (res > 0) {
    return 1;
  }
  return res;
}

bool lat_obj2bool(lat_objeto *o) {
  switch (o->tipo) {
  case T_NULL:
    return false;
    break;
  case T_BOOL:
    return __logico(o);
    break;
  case T_NUMERIC:
    return __numerico(o) == 0 ? false : true;
    break;
  case T_STR:
    return strcmp(__cadena(o), "") == 0 || strcmp(__cadena(o), "0") == 0 ||
                   strcmp(__str_minusculas(__cadena(o)), "falso") == 0 ||
                   strcmp(__str_minusculas(__cadena(o)), "false") == 0
               ? false
               : true;
    break;
  case T_LIST:
    return __lista_longitud(__lista(o)) == 0 ? false : true;
  case T_DICT:
    return __dic_longitud(__dic(o)) == 0 ? false : true;
  default:
    lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
              "Conversion de tipo de dato incompatible");
    break;
  }
  return false;
}

double lat_obj2double(lat_objeto *o) {
  switch (o->tipo) {
  case T_NULL:
    return 0;
    break;
  case T_BOOL:
    return __logico(o) == false ? 0 : 1;
    break;
  case T_NUMERIC:
    return __numerico(o);
    break;
  case T_STR: {
    char *ptr;
    double ret;
    ret = strtod(__cadena(o), &ptr);
    if (strcmp(ptr, "") == 0) {
      return ret;
    }
  } break;
  case T_LIST:
    return __lista_longitud(__lista(o));
    break;
  case T_DICT:
    return __dic_longitud(__dic(o));
    break;
  default:
    lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
              "Conversion de tipo de dato incompatible");
    break;
  }
  lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
            "Conversion de tipo de dato incompatible");
  return 0;
}

char *lat_obj2cstring(lat_objeto *o) {
  if (o->tipo == T_NULL) {
    return strdup("nulo");
  }
  if (o->tipo == T_BOOL) {
    return __str_logico_a_cadena(__logico(o));
  } else if (o->tipo == T_CONTEXT) {
    return strdup("contexto");
  } else if (o->tipo == T_NUMERIC) {
    return __str_decimal_a_cadena(__numerico(o));
  } else if (o->tipo == T_STR) {
    return strdup(__cadena(o));
  } else if (o->tipo == T_FUNC) {
    return strdup("funcion");
  } else if (o->tipo == T_CFUNC) {
    return strdup("cfuncion");
  } else if (o->tipo == T_CLASS) {
    return strdup("clase");
  }
  if (o->tipo == T_LIST) {
    return __lista_a_cadena(__lista(o));
  } else if (o->tipo == T_DICT) {
    return __dic_a_cadena(__dic(o));
  }
  return strdup("");
}
