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

#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"
#include "latobj.h"

#define LIB_GC_NAME "gc"

void gc_agregar(lat_mv *mv, lat_objeto *o) {
#if HABILITAR_GC
    if (mv->global->gc_objetos == NULL) {
        return;
    }
    o->marca = 1;
    latL_agregar(mv, latC_checar_lista(mv, mv->global->gc_objetos), o);
    gc_checar(mv);
#endif
}

void gc_paso(lat_mv *mv) {
    if (!mv->global->gc_objetos) {
        return;
    }
    lista *list = latC_checar_lista(mv, mv->global->gc_objetos);
    if (list->longitud > 0) {
        LIST_FOREACH(list, primero, siguiente, cur) {
            lat_objeto *tmp = (lat_objeto *)cur->valor;
            if (tmp != NULL) {
                if (tmp->marca && tmp->nref <= 0) {
                    if (mv->memoria_usada > (MAX_VIRTUAL_MEMORY * 0.0001)) {
                        latO_destruir(mv, tmp);
                    }
                }
            }
        }
    }
}

void gc_recolectar(lat_mv *mv) {
    printf("gc_recolectar inici: %zu\n", mv->memoria_usada);
    if (!mv->global->gc_objetos) {
        return;
    }
    lista *list = latC_checar_lista(mv, mv->global->gc_objetos);
    if (list->longitud > 0) {
        LIST_FOREACH(list, primero, siguiente, cur) {
            lat_objeto *tmp = (lat_objeto *)cur->valor;
            if (tmp != NULL && tmp->tipo != T_LIST && tmp->tipo != T_DIC &&
                tmp->tipo != T_CONTEXT) {
                latO_destruir(mv, tmp);
            }
        }
    }
    latL_limpiar_destruir(mv, list);
    printf("gc_recolectar final: %zu\n", mv->memoria_usada);
}

void gc_checar(lat_mv *mv) {
    if (!mv->global->gc_objetos) {
        return;
    }
    if (mv->memoria_usada > mv->gc_limite) {
        gc_paso(mv);
    } /*fin cond memoria_usada*/
}

static void gc_mostrar(lat_mv *mv) { ; }

static const lat_CReg libgc[] = {
    {"mostrar", gc_mostrar, 0}, {"limpiar", gc_checar, 0}, {NULL, NULL}};

void latC_abrir_liblatino_gc(lat_mv *mv) { latC_abrir_liblatino(mv, LIB_GC_NAME, libgc); }

//Lua GC
//https://www.tutorialspoint.com/lua/lua_garbage_collection.htm
//https://poga.github.io/lua53-notes/gc.html
//Algoritmo Mark-and-sweep
