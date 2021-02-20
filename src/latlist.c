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

#include "latlist.h"
#include "latdo.h"
#include "latgc.h"
#include "latino.h"
#include "latmem.h"

LATINO_API lista *latL_crear(lat_mv *mv) {
    lista *l = latM_asignar(mv, sizeof(lista));
#if DEPURAR_MEM
    printf("latL_crear.l: %p\n", l);
#endif
    l->longitud = 0;
    l->primero = NULL;
    l->ultimo = NULL;
    return l;
}

LATINO_API void latL_destruir(lat_mv *mv, lista *list) {

    LIST_FOREACH(list, primero, siguiente, cur) {
        if (cur->anterior) {
            latM_liberar(mv, cur->anterior);
        }
    }
    latM_liberar(mv, list->ultimo);
    latM_liberar(mv, list);
}

LATINO_API void latL_limpiar(lat_mv *mv, lista *list) {

    LIST_FOREACH(list, primero, siguiente, cur) {
        latM_liberar(mv, cur->valor);
    }
}

LATINO_API void latL_limpiar_destruir(lat_mv *mv, lista *list) {
    latL_limpiar(mv, list);
    latL_destruir(mv, list);
}

LATINO_API void latL_agregar(lat_mv *mv, lista *list, void *value) {
    nodo_lista *node = latM_asignar(mv, sizeof(nodo_lista));
#if DEPURAR_MEM
    printf("latL_agregar.node: %p\n", node);
#endif
    node->valor = value;
    node->siguiente = NULL;
    node->anterior = NULL;
    if (list->ultimo == NULL) {
        list->primero = node;
        list->ultimo = node;
    } else {
        list->ultimo->siguiente = node;
        node->anterior = list->ultimo;
        list->ultimo = node;
    }
    list->longitud++;
}

LATINO_API void *latL_desapilar(lat_mv *mv, lista *list) {
    nodo_lista *node = list->ultimo;
    return node != NULL ? latL_eliminar_nodo(mv, list, node) : NULL;
}

LATINO_API void latL_insertar_inicio(lat_mv *mv, lista *list, void *value) {
    nodo_lista *node = latM_asignar(mv, sizeof(nodo_lista));
#if DEPURAR_MEM
    printf("latL_insertar_inicio.node: %p\n", node);
#endif
    node->valor = value;
    if (list->primero == NULL) {
        list->primero = node;
        list->ultimo = node;
    } else {
        node->siguiente = list->primero;
        list->primero->anterior = node;
        list->primero = node;
    }
    list->longitud++;
}

LATINO_API void *latL_extraer_inicio(lat_mv *mv, lista *list) {
    nodo_lista *node = list->primero;
    return node != NULL ? latL_eliminar_nodo(mv, list, node) : NULL;
}

LATINO_API void *latL_eliminar_nodo(lat_mv *mv, lista *list, nodo_lista *node) {
    void *result = NULL;
    if (node == list->primero && node == list->ultimo) {
        list->primero = NULL;
        list->ultimo = NULL;
    } else if (node == list->primero) {
        list->primero = node->siguiente;
        list->primero->anterior = NULL;
    } else if (node == list->ultimo) {
        list->ultimo = node->anterior;
        list->ultimo->siguiente = NULL;
    } else {
        nodo_lista *after = node->siguiente;
        nodo_lista *before = node->anterior;
        after->anterior = before;
        before->siguiente = after;
    }
    list->longitud--;
    result = node->valor;
    latM_liberar(mv, node);
    return result;
}

LATINO_API void latL_extender(lat_mv *mv, lista *list1, lista *list2) {

    LIST_FOREACH(list2, primero, siguiente, cur) {
        latL_agregar(mv, list1, cur->valor);
    }
}

LATINO_API bool latL_contiene_valor(lat_mv *mv, lista *list, void *data) {
    lat_objeto *bus = (lat_objeto *)data;

    LIST_FOREACH(list, primero, siguiente, cur) {
        lat_objeto *tmp = (lat_objeto *)cur->valor;
        if (latO_comparar(mv, tmp, bus) == 0) {
            return true;
        }
    }
    return false;
}

LATINO_API lat_objeto *latL_obtener_elemento(lat_mv *mv, lista *list, int pos) {
    if (pos < 0 || pos >= latL_longitud(list)) {
        latC_error(mv, "Indice fuera de rango");
    }
    int i = 0;

    LIST_FOREACH(list, primero, siguiente, cur) {
        if (i == pos) {
            return (lat_objeto *)cur->valor;
        }
        i++;
    }
    return latO_nulo;
}

LATINO_API nodo_lista *latL_obtener_nodo(lat_mv *mv, lista *list, int pos) {
    if (pos < 0 || pos >= latL_longitud(list)) {
        latC_error(mv, "Indice fuera de rango");
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

LATINO_API void latL_insertar_elemento(lat_mv *mv, lista *list, void *data,
                                       int pos) {
    // FIXME: Memory leak and for performance
    int len = latL_longitud(list);
    if (pos < 0 || pos > len) {
        latC_error(mv, "Indice fuera de rango");
    }
    if (pos == 0) {
        latL_insertar_inicio(mv, list, data);
        return;
    }
    if (pos == len) {
        latL_agregar(mv, list, data);
        return;
    }
    lista *tmp1 = latL_crear(mv);
    lista *tmp2 = latL_crear(mv);
    int i = 0;

    LIST_FOREACH(list, primero, siguiente, cur) {
        if (i < pos) {
            latL_agregar(mv, tmp1, cur->valor);
        } else {
            latL_agregar(mv, tmp2, cur->valor);
        }
        i++;
    }
    lista *nl = latL_crear(mv);
    latL_extender(mv, nl, tmp1);
    latL_agregar(mv, nl, data);
    latL_extender(mv, nl, tmp2);
    *list = *nl;
    latM_liberar(mv, tmp1);
    latM_liberar(mv, tmp2);
}
