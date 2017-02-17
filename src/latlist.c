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

#include "latlist.h"
#include "latgc.h"
#include "latino.h"
#include "latmem.h"

#define LIB_LISTA_NAME "lista"

lista *__lista_crear() {
        // printf("__lista_crear\n");
        return __memoria_asignar(NULL, sizeof(lista));
}

void __lista_destruir(lista *list) {
        LIST_FOREACH(list, primero, siguiente, cur) {
                if (cur->anterior) {
                        __memoria_liberar(NULL, cur->anterior);
                }
        }
        __memoria_liberar(NULL, list->ultimo);
        __memoria_liberar(NULL, list);
}

void __lista_limpiar(lista *list) {
        LIST_FOREACH(list, primero, siguiente, cur) {
                __memoria_liberar(NULL, cur->valor);
        }
}

void __lista_limpiar_destruir(lista *list) {
        __lista_limpiar(list);
        __lista_destruir(list);
}

void __lista_agregar(lista *list, void *value) {
        lista_nodo *node = __memoria_asignar(NULL, sizeof(lista_nodo));
        node->valor = value;
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

void *__lista_desapilar(lista *list) {
        lista_nodo *node = list->ultimo;
        return node != NULL ? __lista_eliminar_elemento(list, node) : NULL;
}

void __lista_insertar_inicio(lista *list, void *value) {
        lista_nodo *node = __memoria_asignar(NULL, sizeof(lista_nodo));
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

void *__lista_extraer_inicio(lista *list) {
        lista_nodo *node = list->primero;
        return node != NULL ? __lista_eliminar_elemento(list, node) : NULL;
}

void *__lista_eliminar_elemento(lista *list, lista_nodo *node) {
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
                lista_nodo *after = node->siguiente;
                lista_nodo *before = node->anterior;
                after->anterior = before;
                before->siguiente = after;
        }
        list->longitud--;
        result = node->valor;
        __memoria_liberar(NULL, node);
        return result;
}

char *__lista_a_cadena(lista *list) {
        char *valor = __memoria_asignar(NULL, MAX_STR_LENGTH);
        strcat(valor, "[");
        LIST_FOREACH(list, primero, siguiente, cur) {
                lat_objeto *o = ((lat_objeto *)cur->valor);
                char *tmp = lat_obj2cstring(o);
                if (o->tipo == T_STR) {
                        if (strstr(__cadena(o), "\"") != NULL) {
                                strcat(valor, "'");
                        } else {
                                strcat(valor, "\"");
                        }
                }
                strcat(valor, tmp);
                __memoria_liberar(NULL, tmp);
                if (o->tipo == T_STR) {
                        if (strstr(__cadena(o), "\"") != NULL) {
                                strcat(valor, "'");
                        } else {
                                strcat(valor, "\"");
                        }
                }
                if (cur != list->ultimo) {
                        strcat(valor, ", ");
                }
        }
        strcat(valor, "]");
        valor[strlen(valor)] = '\0';
        return valor;
}

void __lista_modificar_elemento(lista *list, void *data, int pos) {
        int i = 0;
        if (pos < 0 || pos >= __lista_longitud(list)) {
                lat_error("Indice fuera de rango");
        }
        LIST_FOREACH(list, primero, siguiente, cur) {
                if (i == pos) {
                        cur->valor = data;
                }
                i++;
        }
}

int __lista_comparar(lista *lhs, lista *rhs) {
        int res = 0;
        int len1 = __lista_longitud(lhs);
        int len2 = __lista_longitud(rhs);
        if (len1 < len2) {
                return -1;
        }
        if (len1 > len2) {
                return 1;
        }
        int i;
        for (i = 0; i < len1; i++) {
                lat_objeto *tmp1 = __lista_obtener_elemento(lhs, i);
                lat_objeto *tmp2 = __lista_obtener_elemento(rhs, i);
                res = __obj_comparar(tmp1, tmp2);
                if (res < 0) {
                        return -1;
                }
                if (res > 0) {
                        return 1;
                }
        }
        return res;
}

void __lista_extender(lista *list1, lista *list2) {
        LIST_FOREACH(list2, primero, siguiente, cur) {
                __lista_agregar(list1, cur->valor);
        }
}

bool __lista_contiene_valor(lista *list, void *data) {
        lat_objeto *bus = (lat_objeto *)data;
        LIST_FOREACH(list, primero, siguiente, cur) {
                lat_objeto *tmp = (lat_objeto *)cur->valor;
                if (__obj_comparar(tmp, bus) == 0) {
                        return true;
                }
        }
        return false;
}

lat_objeto *__lista_obtener_elemento(lista *list, int pos) {
        if (pos < 0 || pos >= __lista_longitud(list)) {
                lat_error("Indice fuera de rango");
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
                lat_error("Indice fuera de rango");
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

int __lista_obtener_indice(lista *list, void *data) {
        int i = 0;
        lat_objeto *find = (lat_objeto *)data;
        LIST_FOREACH(list, primero, siguiente, cur) {
                // if (memcmp(cur->valor, data, sizeof(cur->valor)) == 0)
                lat_objeto *tmp = (lat_objeto *)cur->valor;
                if (__obj_es_igual(find, tmp)) {
                        return i;
                }
                i++;
        }
        return -1;
}

void __lista_insertar_elemento(lista *list, void *data, int pos) {
        // FIXME: Memory leak and for performance
        int len = __lista_longitud(list);
        if (pos < 0 || pos > len) // permite insertar al ultimo
        {
                lat_error("Indice fuera de rango");
        }
        if (pos == 0) {
                __lista_insertar_inicio(list, data);
                return;
        }
        if (pos == len) {
                __lista_agregar(list, data);
                return;
        }
        lista *tmp1 = __lista_crear();
        lista *tmp2 = __lista_crear();
        int i = 0;
        LIST_FOREACH(list, primero, siguiente, cur) {
                if (i < pos) {
                        __lista_agregar(tmp1, cur->valor);
                } else {
                        __lista_agregar(tmp2, cur->valor);
                }
                i++;
        }
        lista *new = __lista_crear();
        __lista_extender(new, tmp1);
        __lista_agregar(new, data);
        __lista_extender(new, tmp2);
        *list = *new;
        __memoria_liberar(NULL, tmp1);
        __memoria_liberar(NULL, tmp2);
}

void lat_lista_agregar(lat_mv *mv) {
        lat_objeto *elem = lat_desapilar(mv);
        lat_objeto *lst = lat_desapilar(mv);
        if(!__obj_comparar(lst, elem)){
                filename = lst->nombre_archivo;
                lat_error("Linea %d, %d: Referencia circular detectada.", lst->num_linea,
                lst->num_columna);
        }
        __lista_agregar(__lista(lst), elem);
}

void lat_lista_extender(lat_mv *mv) {
        lat_objeto *l2 = lat_desapilar(mv);
        lat_objeto *lst = lat_desapilar(mv);
        if (lst->tipo != T_LIST) {
                filename = lst->nombre_archivo;
                lat_error("Linea %d, %d: %s", lst->num_linea, lst->num_columna,
                "El objeto no es una lista");
        }
        if (l2->tipo != T_LIST) {
                filename = lst->nombre_archivo;
                lat_error("Linea %d, %d: %s", l2->num_linea, l2->num_columna,
                "El objeto no es una lista");
        }
        lista *_lst2 = __lista(l2);
        lista *_lst = __lista(lst);
        __lista_extender(_lst, _lst2);
}

void lat_lista_eliminar_indice(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lista *lst = __lista(a);
        int pos = __numerico(b);
        if (pos < 0 || pos >= __lista_longitud(lst)) {
                filename = a->nombre_archivo;
                lat_error("Linea %d, %d: %s", a->num_linea, a->num_columna,
                "Indice fuera de rango");
        }
        if (pos >= 0) {
                lista_nodo *nt = __lista_obtener_nodo(lst, pos);
                __lista_eliminar_elemento(lst, nt);
        }
}

void lat_lista_invertir(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lista *lst = __lista(a);
        lista *new = __lista_crear();
        // FIXME: For performance
        int i;
        int len = __lista_longitud(lst) - 1;
        for (i = len; i >= 0; i--) {
                __lista_agregar(new, __lista_obtener_elemento(lst, i));
        }
        lat_objeto *tmp = lat_lista_nueva(mv, new);
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_lista_longitud(lat_mv *mv) {
        lat_objeto *o = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, __lista_longitud(__lista(o)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}
void lat_lista_comparar(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp =
        lat_numerico_nuevo(mv, __lista_comparar(__lista(a), __lista(b)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_lista_insertar(lat_mv *mv) {
        lat_objeto *c = lat_desapilar(mv);
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        __lista_insertar_elemento(__lista(a), b, __numerico(c));
}

void lat_lista_eliminar(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lista *lst = __lista(a);
        int i = __lista_obtener_indice(lst, b);
        if (i >= 0) {
                lista_nodo *nt = __lista_obtener_nodo(lst, i);
                __lista_eliminar_elemento(lst, nt);
        }
}

void lat_lista_indice(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lista *lst = __lista(a);
        int i = __lista_obtener_indice(lst, b);
        lat_objeto *tmp = lat_numerico_nuevo(mv, (double)i);
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_lista_contiene(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lista *lst = __lista(a);
        bool contiene = __lista_contiene_valor(lst, b);
        if (contiene) {
                lat_apilar(mv, mv->objeto_verdadero);
        } else {
                lat_apilar(mv, mv->objeto_falso);
        }
}

void lat_lista_crear(lat_mv *mv) {
        lat_objeto *num = lat_desapilar(mv);        
        int i = 0;
        int cant = __numerico(num);
        lista *lst = __lista_crear();
                if(cant > 0){
                        while(i<cant){
                                __lista_agregar(lst, mv->objeto_nulo);
                        i++;
                }
        }
        lat_apilar(mv, lat_lista_nueva(mv, lst));
}

static const lat_CReg lib_lista[] = {
        {"invertir", lat_lista_invertir, 1},
        {"agregar", lat_lista_agregar, 2},
        {"extender", lat_lista_extender, 2},
        {"eliminar_indice", lat_lista_eliminar_indice, 2},
        {"longitud", lat_lista_longitud, 1},
        {"indice", lat_lista_indice, 2},
        {"encontrar", lat_lista_indice, 2},
        {"comparar", lat_lista_comparar, 2},
        {"insertar", lat_lista_insertar, 3},
        {"eliminar", lat_lista_eliminar, 2},
        {"contiene", lat_lista_contiene, 2},
        {"crear", lat_lista_crear, 1},
        {NULL, NULL}
};

void lat_importar_lib_lista(lat_mv *mv) {
        lat_importar_lib(mv, LIB_LISTA_NAME, lib_lista);
}
