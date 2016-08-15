/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

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

#include "latino.h"
#include "vm.h"

/** \brief Nodo de una lista */
typedef struct list_node
{
    struct list_node* prev;   /**< Nodo previo*/
    struct list_node* next;   /**< Nodo siguiente*/
    void* data;   /**< Informacion del nodo*/
} list_node;

/**\brief Crear una lista vacia
  *
  *\return list_node: Apuntador al primer nodo de la lista
  */
list_node* __lista_nuevo();

/**\brief Busca un elemento en la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto buscado
  *\return int: Retorna 1 si se encontro el objeto 0 en caso contrario
  */
int __lista_existe_dato(list_node* l, void* data);

/**\brief __str_insertara un elemento en la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto
  */
void __lista_agregar(list_node* l, void* data);

/**\brief Devuelve la longitud de la lista
  *
  *\param l: Apuntador a la lista
  *\return int: La longitud de la lista
  */
int __lista_longitud(list_node* l);

/** Agrega un elemento al final de la lista
  * \param vm: Maquina virtual de latino
 * */
void lat_agregar(lat_vm *vm);

#endif /* !_LIBLIST_H_ */
