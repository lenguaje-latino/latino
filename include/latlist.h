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

#ifndef _LATINO_LIST_H_
#define _LATINO_LIST_H_

typedef struct lat_mv lat_mv;

#define latL_longitud(A) ((A)->longitud)
#define latL_primero(A) ((A)->primero != NULL ? (A)->primero->valor : NULL)
#define latL_ultimo(A) ((A)->ultimo != NULL ? (A)->ultimo->valor : NULL)

/**\brief Almacena el valor del objeto */
typedef struct nodo_lista {
    struct nodo_lista *siguiente;
    struct nodo_lista *anterior;
    void *valor;
} nodo_lista;

/**\brief Lista de objetos */
typedef struct lista {
    int longitud;
    nodo_lista *primero;
    nodo_lista *ultimo;
} lista;

/**
 *\brief Recorre la lista por cada elemento
 */
#define LIST_FOREACH(L, S, M, V)                                               \
    nodo_lista *_node = NULL;                                                  \
    nodo_lista *V = NULL;                                                      \
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif /* !_LATINO_LIST_H_ */
