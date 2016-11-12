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

#ifndef _LIBLIST_H_
#define _LIBLIST_H_

/**\brief Almacena el valor del objeto */
typedef struct lista_nodo {
  struct lista_nodo *siguiente;
  struct lista_nodo *anterior;
  void *valor;
} lista_nodo;

/**\brief Lista de objetos */
typedef struct lista {
  int longitud;
  lista_nodo *primero;
  lista_nodo *ultimo;
} lista;

/**
  *\brief Crea una lista
  *
  *\return lista*: Apuntador a la lista nueva
  */
lista *__lista_crear();

/**
  *\brief Destruye una lista
  *
  *\param list: Apuntador a la lista
  */
void __lista_destruir(lista *list);

/**
  *\brief Limpia una lista, libera la memoria de los elementos
  *
  *\param list: Apuntador a la lista
  */
void __lista_limpiar(lista *list);

/**
  *\brief Limpia una lista, libera la memoria de los elementos y elimina la
  *lista de memoria
  *
  *\param list: Apuntador a la lista
  */
void __lista_limpiar_destruir(lista *list);

/**
  *\brief Devuelve el numero de elementos de la lista
  *
  *\param list: Apuntador a la lista
  */
#define __lista_longitud(A) ((A)->longitud)

/**
  *\brief Devuelve el primer elemento de la lista
  *
  *\param list: Apuntador a la lista
  */
#define __lista_primero(A) ((A)->primero != NULL ? (A)->primero->valor : NULL)

/**
  *\brief Devuelve el ultimo elemento de la lista
  *
  *\param list: Apuntador a la lista
  */
#define __lista_ultimo(A) ((A)->ultimo != NULL ? (A)->ultimo->valor : NULL)

/**
  *\brief Inserta un elemento al final de la lista
  *
  *\param list: Apuntador a la lista
  *\param value: Objeto a insertar
  */
void __lista_agregar(lista *list, void *value);

/**
  *\brief Extrae el ultimo elemento de la lista
  *
  *\param list: Apuntador a la lista
  *\return void*: Apuntador al Objeto eliminado
  */
void *__lista_desapilar(lista *list);

/**
  *\brief Inserta un elemento al inicio de la lista
  *
  *\param list: Apuntador a la lista
  *\param value: Objeto a insertar
  */
void __lista_insertar_inicio(lista *list, void *value);

/**
  *\brief Extrae el primer elemento de la lista
  *
  *\param list: Apuntador a la lista
  *\return void*: Apuntador al Objeto eliminado
  */
void *__lista_extraer_inicio(lista *list);

/**
  *\brief Elimina un nodo de la lista
  *
  *\param list: Apuntador a la lista
  *\param node: Apuntador al nodo de la lista
  *\return void*: Apuntador al Objeto eliminado
  */
void *__lista_eliminar_elemento(lista *list, lista_nodo *node);

/**
  *\brief Recorre la lista por cada elemento
  */
#define LIST_FOREACH(L, S, M, V)                                               \
  lista_nodo *_node = NULL;                                                    \
  lista_nodo *V = NULL;                                                        \
  for (V = _node = L->S; _node != NULL; V = _node = _node->M)

/**\brief Devuelve la representacion en cadena de la lista
  *
  *\param l: Apuntador a la lista
  *\return char*: La cadena que representa la lista
  */
// char* __lista_a_cadena(lista* list, char* dest);
char *__lista_a_cadena(lista *list);

/**\brief Modifica el valor de un elemento en la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto a modificar
  *\param pos: Posicion del elemento a modificar
  */
void __lista_modificar_elemento(lista *list, void *data, int pos);

/**\brief Compara los elementos de una lista
  *
  *\param lhs: Apuntador a la lista izquierda
  *\param rhs: Apuntador a la lista derecha
  *\return int: 0 si son iguales, -1 si la lista izquierda es menor y 1 si es
  *mayor
  */
int __lista_comparar(lista *lhs, lista *rhs);

/**\brief Agrega los elementos de la lista2 a la lista1
  *
  *\param lista1: Apuntador a la lista1
  *\param lista2: Apuntador a la lista2
  */
void __lista_extender(lista *list1, lista *list2);

/**\brief Inserta un elemento a la lista en la posicion indicada
  *
  *\param list: Apuntador a la lista
  *\param data: Objeto a insertar
  *\param pos: posicion en que se insertara el elemento
  */
void __lista_insertar_elemento(lista *list, void *data, int pos);

#endif /* !_LIBLIST_H_ */
