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
#ifndef _LIB_DICT_H_
#define _LIB_DICT_H_

#include "latlist.h"

/**\brief Valor hash */
typedef struct hash_val {
  char llave[64]; /**< Llave */
  void *valor;    /**< Valor */
} hash_val;

/**\brief Mapa de valores hash */
typedef struct hash_map {
  lista *buckets[256]; //< Arreglo de listas
} hash_map;

/**
  *\brief Crea una tabla hash
  *
  *\return hash_map*: Apuntador a la tabla creada
  */
hash_map *__dic_crear();

/**
  *\brief Libera la informacion de una tabla hash
  *
  *\param dic*: Apuntador a la tabla creada
  */
void __dic_destruir(hash_map *dic);

/**\brief Crea un hash de una cadena
  *
  *\param key: Apuntador a cadena
  *\return int: Numero hash creado para la cadena
  */
int __dic_hash(const char *key);

/**\brief Obtiene un elemento de la tabla hash
  *
  *\param m: Apuntador a la tabla hash
  *\param key: Llave buscada
  *\return void*: Apuntador al objeto buscado
  */
void *__dic_obtener(hash_map *m, char *key);

/**\brief Guarda un elemento en la tabla buscada
  *
  *\param m: Apuntador a la tabla hash
  *\param key: Llave
  *\param val: Valor
  */
void __dic_asignar(hash_map *m, const char *key, void *val);

/**\brief Copia una tabla hash con todos sus elementos
  *\param m: Apuntador a tabla hash
  */
hash_map *__dic_clonar(hash_map *m);

/**\brief Genera la representacion en cadena del diccionario
 * \param m: Apuntador a tabla hash
 * \return char: La cadena del diccionario
 */
char *__dic_a_cadena(hash_map *m);

/**\brief Obtiene la longitud del diccionario
 * \param m: Apuntador a tabla hash
 * \return int: La longitud del diccionario
 */
int __dic_longitud(hash_map *m);

#endif /* !_LIB_DICT_H_ */
