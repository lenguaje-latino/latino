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

#define LATINO_CORE

#include "latdic.h"
#include "latgc.h"
#include "latino.h"
#include "latmem.h"

LATINO_API hash_map *latH_crear(lat_mv *mv) {
    hash_map *ret = (hash_map *)latM_asignar(mv, sizeof(hash_map));
#if DEPURAR_MEM
    printf("latH_crear.ret: %p\n", ret);
#endif
    int c;
    for (c = 0; c < 256; c++) {
        ret->buckets[c] = NULL;
    }
    ret->longitud = 0;
    return ret;
}

LATINO_API void latH_asignar(lat_mv *mv, hash_map *m, const char *key,
                             void *val) {
    int hk = latH_hash(key);
    if (m->buckets[hk] == NULL) {
        m->buckets[hk] = latL_crear(mv);
    } else {
        lista *list = m->buckets[hk];
        LIST_FOREACH(list, primero, siguiente, cur) {
            if (cur->valor) {
                if (!strcmp(((hash_val *)cur->valor)->llave, key)) {
                    lat_objeto *obj =
                        (lat_objeto *)((hash_val *)cur->valor)->valor;
                    setobj2obj(obj, val);
                    return;
                }
            }
        }
    }
    // crea una nueva llave
    hash_val *hv = (hash_val *)latM_asignar(mv, sizeof(hash_val));
#if DEPURAR_MEM
    printf("latH_asignar.hv: %p\n", hv);
#endif
    strncpy(hv->llave, key, (strlen(key) + 1));
    // FIXME: Memory leak
    lat_objeto *obj = latO_crear(mv);
    setobj2obj(obj, val);
    hv->valor = obj;
    latL_agregar(mv, m->buckets[hk], (void *)hv);
    m->longitud++;
}

LATINO_API void latH_limpiar(lat_mv *mv, hash_map *dic) {
    int i;
    for (i = 0; i < 256; i++) {
        dic->buckets[i] = NULL;
    }
    latM_liberar(mv, dic);
}

LATINO_API void latH_destruir(lat_mv *mv, hash_map *dic) {
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = dic->buckets[i];
        if (list != NULL) {
            LIST_FOREACH(list, primero, siguiente, cur) {
                hash_val *hv = (hash_val *)cur->valor;
                lat_objeto *val = hv->valor;
                latO_destruir(mv, val);
            }
            latL_limpiar_destruir(mv, list);
        }
    }
    latM_liberar(mv, dic);
}

int latH_hash(const char *key) {
    int h = 5381;
    unsigned char c;
    for (c = *key; c != '\0'; c = *++key)
        h = h * 33 + c;
    return abs(h % 256);
}

LATINO_API void *latH_obtener(hash_map *m, const char *key) {
    lista *list = m->buckets[latH_hash(key)];
    if (list == NULL)
        return NULL;
    if (list->longitud > 0) {
        LIST_FOREACH(list, primero, siguiente, cur) {
            if (!strcmp(key, ((hash_val *)cur->valor)->llave)) {
                return ((hash_val *)cur->valor)->valor;
            }
        }
    }
    return NULL;
}

LATINO_API hash_map *latH_clonar(lat_mv *mv, hash_map *m) {
    hash_map *ret = latH_crear(mv);
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = m->buckets[i];
        if (list != NULL) {
            if (list->longitud > 0) {
                LIST_FOREACH(list, primero, siguiente, cur) {
                    if (cur->valor) {
                        char *str_key = ((hash_val *)cur->valor)->llave;
                        latH_asignar(mv, ret, str_key,
                                     ((hash_val *)cur->valor)->valor);
                    }
                }
            }
        }
    }
    return ret;
}
