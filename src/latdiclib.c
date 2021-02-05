/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

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

#include "latino.h"

#define LIB_DIC_NAME "dic"

static void dic_longitud(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    lat_objeto *tmp = NULL;
    tmp =
        latC_crear_numerico(mv, (double)latH_longitud(latC_checar_dic(mv, o)));
    latC_apilar(mv, tmp);
}

static void dic_llaves(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    hash_map *m = latC_checar_dic(mv, o);
    lista *lst = latL_crear(mv);
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = m->buckets[i];
        if (list != NULL) {
            if (list->longitud > 0) {
                LIST_FOREACH(list, primero, siguiente, cur) {
                    if (cur->valor != NULL) {
                        char *str_key = ((hash_val *)cur->valor)->llave;
                        latL_agregar(mv, lst, latC_crear_cadena(mv, str_key));
                    }
                }
            }
        }
    }
    lat_objeto *tmp = latC_crear_lista(mv, lst);
    latC_apilar(mv, tmp);
}

static void dic_valores(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    hash_map *m = latC_checar_dic(mv, o);
    lista *lst = latL_crear(mv);
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = m->buckets[i];
        if (list != NULL) {
            if (list->longitud > 0) {
                LIST_FOREACH(list, primero, siguiente, cur) {
                    if (cur->valor != NULL) {
                        lat_objeto *val =
                            (lat_objeto *)((hash_val *)cur->valor)->valor;
                        latL_agregar(mv, lst, val);
                    }
                }
            }
        }
    }
    lat_objeto *tmp = latC_crear_lista(mv, lst);
    latC_apilar(mv, tmp);
}

static void dic_contiene(lat_mv *mv) {
    lat_objeto *ll = latC_desapilar(mv);
    lat_objeto *o = latC_desapilar(mv);
    hash_map *m = latC_checar_dic(mv, o);
    const char *llave = latC_checar_cadena(mv, ll);
    lat_objeto *tmp = latO_falso;
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = m->buckets[i];
        if (list != NULL) {
            if (list->longitud > 0) {
                LIST_FOREACH(list, primero, siguiente, cur) {
                    if (cur->valor != NULL) {
                        char *str_key = ((hash_val *)cur->valor)->llave;
                        if (strcmp(str_key, latC_checar_cadena(mv, ll)) == 0) {
                            tmp = latO_verdadero;
                            break;
                        }
                    }
                }
            }
        }
    }
    latC_apilar(mv, tmp);
}

static void dic_eliminar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    hash_map *m = latC_checar_dic(mv, a);
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = m->buckets[i];
        if (list != NULL) {
            if (list->longitud > 0) {
                LIST_FOREACH(list, primero, siguiente, cur) {
                    if (cur->valor != NULL) {
                        char *str_key = ((hash_val *)cur->valor)->llave;
                        if (strcmp(str_key, latC_checar_cadena(mv, b)) == 0) {
                            m->buckets[i] = NULL;
                        }
                    }
                }
            }
        }
    }
}

static const lat_CReg libdic[] = {{"longitud", dic_longitud, 1},
                                  {"llaves", dic_llaves, 1},
                                  {"valores", dic_valores, 1},
                                  {"vals", dic_valores, 1},
                                  {"contiene", dic_contiene, 2},
                                  {"eliminar", dic_eliminar, 2},
                                  {NULL, NULL}};

void latC_abrir_liblatino_diclib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_DIC_NAME, libdic);
}
