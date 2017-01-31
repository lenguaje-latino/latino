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

#include <stdio.h>
#include <string.h>

#include "latdic.h"
#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"

#define LIB_DIC_NAME "dic"

char * __str_reemplazar(char *str, const char *orig, const char *rep);

hash_map *__dic_crear() {
  // printf("__dic_crear\n");
  hash_map *ret = (hash_map *)__memoria_asignar(NULL, sizeof(hash_map));
  int c;
  for (c = 0; c < 256; c++) {
    ret->buckets[c] = NULL;
  }
  return ret;
}

void __dic_destruir(hash_map *dic) {
  int i;
  for (i = 0; i < 256; i++) {
    lista *list = dic->buckets[i];
    if (list != NULL) {
      __lista_limpiar_destruir(list);
      //__lista_destruir(list);
    }
  }
  __memoria_liberar(NULL, dic);
}

int __dic_hash(const char *key) {
  int h = 5381;
  unsigned char c;
  for (c = *key; c != '\0'; c = *++key)
    h = h * 33 + c;
  return abs(h % 256);
}

void *__dic_obtener(hash_map *m, char *key) {
  lista *list = m->buckets[__dic_hash(key)];
  if (list == NULL)
    return NULL;
  LIST_FOREACH(list, primero, siguiente, cur) {
    if (strcmp(key, ((hash_val *)cur->valor)->llave) == 0) {
      return ((hash_val *)cur->valor)->valor;
    }
  }
  return NULL;
}

void __dic_asignar(hash_map *m, const char *key, void *val) {
  // printf("__dic_asignar\n");
  hash_val *hv = (hash_val *)__memoria_asignar(NULL, sizeof(hash_val));
  strncpy(hv->llave, key, (strlen(key) + 1));
  hv->valor = val;
  int hk = __dic_hash(key);
  if (m->buckets[hk] == NULL) {
    m->buckets[hk] = __lista_crear();
  } else {
    lista *list = m->buckets[hk];
    LIST_FOREACH(list, primero, siguiente, cur) {
      if (strcmp(((hash_val *)cur->valor)->llave, key) == 0) {
        __memoria_liberar(NULL, cur->valor);
        cur->valor = hv;
        return;
      }
    }
  }
  __lista_agregar(m->buckets[hk], (void *)hv);
}

hash_map *__dic_clonar(hash_map *m) {
  hash_map *ret = __dic_crear();
  int i;
  for (i = 0; i < 256; i++) {
    lista *list = m->buckets[i];
    if (list != NULL) {
      LIST_FOREACH(list, primero, siguiente, cur) {
        if (cur->valor != NULL) {
          char *str_key = ((hash_val *)cur->valor)->llave;
          __dic_asignar(ret, str_key, ((hash_val *)cur->valor)->valor);
        }
      }
    }
  }
  return ret;
}

char *__dic_a_cadena(hash_map *m) {
  char *valor = __memoria_asignar(NULL, MAX_STR_LENGTH);
  strcat(valor, "{");
  int i;
  for (i = 0; i < 256; i++) {
    lista *list = m->buckets[i];
    if (list != NULL) {
      LIST_FOREACH(list, primero, siguiente, cur) {
        if (cur->valor != NULL) {
          strcat(valor, "\"");
          strcat(valor, ((hash_val *)cur->valor)->llave);
          strcat(valor, "\"");
          lat_objeto *val = (lat_objeto *)((hash_val *)cur->valor)->valor;
          strcat(valor, ": ");
          if (val == NULL) {
            strcat(valor, "\"nulo\"");
          } else {
            if (val->tipo == T_STR) {
              if (strstr(__cadena(val), "\"") != NULL) {
                strcat(valor, "'");
              } else {
                strcat(valor, "\"");
              }
            }
            char *tmp = lat_obj2cstring(val);
            strcat(valor, tmp);
            __memoria_liberar(NULL, tmp);
            if (val->tipo == T_STR) {
              if (strstr(__cadena(val), "\"") != NULL) {
                strcat(valor, "'");
              } else {
                strcat(valor, "\"");
              }
            }
          }
          strcat(valor, ", ");
        }
      }
    }
  }
  strcat(valor, "}");
  char *tmp = __str_reemplazar(valor, ", }", "}"); // elimina la ultima coma
  tmp[strlen(tmp)] = '\0';
  __memoria_liberar(NULL, valor);
  return tmp;
}

int __dic_longitud(hash_map *m) {
  int cant = 0;
  int i;
  for (i = 0; i < 256; i++) {
    lista *list = m->buckets[i];
    if (list != NULL) {
      LIST_FOREACH(list, primero, siguiente, cur) {
        if (cur->valor != NULL) {
          cant++;
        }
      }
    }
  }
  return cant;
}

void lat_dic_longitud(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *tmp = NULL;
  tmp = lat_numerico_nuevo(mv, (double)__dic_longitud(__dic(o)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_dic_llaves(lat_mv *mv){
  lat_objeto *o = lat_desapilar(mv);
  hash_map *m = __dic(o);
  lista *lst = __lista_crear();
  int i;
  for (i = 0; i < 256; i++) {
    lista *list = m->buckets[i];
    if (list != NULL) {
      LIST_FOREACH(list, primero, siguiente, cur) {
        if (cur->valor != NULL) {
          char *str_key = ((hash_val *)cur->valor)->llave;
          __lista_agregar(lst, lat_cadena_nueva(mv, strdup(str_key)));
        }
      }
    }
  }
  lat_objeto *tmp = lat_lista_nueva(mv, lst);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_dic_valores(lat_mv *mv){
  lat_objeto *o = lat_desapilar(mv);
  hash_map *m = __dic(o);
  lista *lst = __lista_crear();
  int i;
  for (i = 0; i < 256; i++) {
    lista *list = m->buckets[i];
    if (list != NULL) {
      LIST_FOREACH(list, primero, siguiente, cur) {
        if (cur->valor != NULL) {
          lat_objeto *val = (lat_objeto *)((hash_val *)cur->valor)->valor;
          __lista_agregar(lst, __obj_clonar(mv, val));
        }
      }
    }
  }
  lat_objeto *tmp = lat_lista_nueva(mv, lst);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

static const lat_CReg lib_dic[] = {{"longitud", lat_dic_longitud, 1},
                                   {"llaves", lat_dic_llaves, 1},
                                   {"valores", lat_dic_valores, 1},
                                   {"vals", lat_dic_valores, 1},
                                   {NULL, NULL}};

void lat_importar_lib_dic(lat_mv *mv) {
  lat_importar_lib(mv, LIB_DIC_NAME, lib_dic);
}
