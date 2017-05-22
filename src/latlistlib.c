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

#define LIB_LISTA_NAME "lista"

static void lista_agregar(lat_mv *mv) {
    lat_objeto *elem = latC_desapilar(mv);
    lat_objeto *lst = latC_desapilar(mv);
    if (!latO_comparar(mv, lst, elem)) {
        latC_error(mv, "Referencia circular detectada");
    }
    latL_agregar(mv, latC_checar_lista(mv, lst), latO_clonar(mv, elem));
}

static void lista_extender(lat_mv *mv) {
    lat_objeto *l2 = latC_desapilar(mv);
    lat_objeto *lst = latC_desapilar(mv);
    if (lst->tipo != T_LIST) {
        latC_error(mv, "El objeto no es una lista");
    }
    if (l2->tipo != T_LIST) {
        latC_error(mv, "El objeto no es una lista");
    }
    lista *_lst2 = latC_checar_lista(mv, l2);
    lista *_lst = latC_checar_lista(mv, lst);
    latL_extender(mv, _lst, _lst2);
}

static void lista_eliminar_indice(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    int pos = latC_checar_numerico(mv, b);
    if (pos < 0 || pos >= latL_longitud(lst)) {
        latC_error(mv, "Indice fuera de rango");
    }
    if (pos >= 0) {
        nodo_lista *nt = latL_obtener_nodo(mv, lst, pos);
        latL_eliminar_nodo(mv, lst, nt);
    }
}

static void lista_invertir(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    lista *nl = latL_crear(mv);
    // FIXME: For performance
    int i;
    int len = latL_longitud(lst) - 1;
    for (i = len; i >= 0; i--) {
        latL_agregar(mv, nl, latL_obtener_elemento(mv, lst, i));
    }
    lat_objeto *tmp = latC_crear_lista(mv, nl);
    latC_apilar(mv, tmp);
}

static void lista_longitud(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, latL_longitud(latC_checar_lista(mv, o)));
    latC_apilar(mv, tmp);
}

static void lista_comparar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, latL_comparar(mv, latC_checar_lista(mv, a),
                                              latC_checar_lista(mv, b)));
    latC_apilar(mv, tmp);
}

static void lista_insertar(lat_mv *mv) {
    lat_objeto *c = latC_desapilar(mv);
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    latL_insertar_elemento(mv, latC_checar_lista(mv, a), b,
                           latC_checar_numerico(mv, c));
}

static void lista_eliminar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    int i = latL_obtener_indice(mv, lst, b);
    if (i >= 0) {
        nodo_lista *nt = latL_obtener_nodo(mv, lst, i);
        latL_eliminar_nodo(mv, lst, nt);
    }
}

static void lista_indice(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    int i = latL_obtener_indice(mv, lst, b);
    lat_objeto *tmp = latC_crear_numerico(mv, (double)i);
    latC_apilar(mv, tmp);
}

static void lista_contiene(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    bool contiene = latL_contiene_valor(mv, lst, b);
    if (contiene) {
        latC_apilar(mv, latO_verdadero);
    } else {
        latC_apilar(mv, latO_falso);
    }
}

static void lista_crear(lat_mv *mv) {
    lat_objeto *num = latC_desapilar(mv);
    int i = 0;
    int cant = latC_checar_numerico(mv, num);
    lista *lst = latL_crear(mv);
    if (cant > 0) {
        while (i < cant) {
            latL_agregar(mv, lst, latO_nulo);
            i++;
        }
    }
    latC_apilar(mv, latC_crear_lista(mv, lst));
}

static const lat_CReg liblist[] = {
    {"invertir", lista_invertir, 1},
    {"agregar", lista_agregar, 2},
    {"extender", lista_extender, 2},
    {"eliminar_indice", lista_eliminar_indice, 2},
    {"longitud", lista_longitud, 1},
    {"indice", lista_indice, 2},
    {"encontrar", lista_indice, 2},
    {"comparar", lista_comparar, 2},
    {"insertar", lista_insertar, 3},
    {"eliminar", lista_eliminar, 2},
    {"contiene", lista_contiene, 2},
    {"crear", lista_crear, 1},
    {NULL, NULL}};

void latC_abrir_liblatino_listlib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_LISTA_NAME, liblist);
}
