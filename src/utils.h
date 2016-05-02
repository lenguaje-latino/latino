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
#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/** \file utils.h
  *
  * Contiene funciones auxiliares para el manejo de objetos (cadenas, listas, tablas hash, errores, etc)
  *
  */

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stdout, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#ifndef REGISTER_DEBUG
#define regdebug(M, ...)
#else
#define regdebug(M, ...) fprintf(stdout, "REGDEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define lat_registrar_error(M, ...)                               \
  {                                                   \
    fprintf(stderr, "Error: " M "\n", ##__VA_ARGS__); \
    exit(1);                                          \
  }
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define check(A, M, ...)       \
  if (!(A)) {                  \
    lat_registrar_error(M, ##__VA_ARGS__); \
    errno = 0;                 \
    goto error;                \
  }
#define sentinel(M, ...)       \
  {                            \
    lat_registrar_error(M, ##__VA_ARGS__); \
    errno = 0;                 \
    goto error;                \
  }
#define check_mem(A) check((A), "Out of memory.")
#define check_debug(A, M, ...) \
  if (!(A)) {                  \
    debug(M, ##__VA_ARGS__);   \
    errno = 0;                 \
    goto error;                \
  }

/** \brief Nodo de una lista */
typedef struct list_node {
  struct list_node* prev;   /**< Nodo previo*/
  struct list_node* next;   /**< Nodo siguiente*/
  void* data;   /**< Informacion del nodo*/
} list_node;

/**\brief Valor hash */
typedef struct hash_val {
  char key[256];    /**< Llave */
  void* val;    /**< Valor */
} hash_val;

/**\brief Tabla hash */
typedef struct hash_map {
  list_node* buckets[256];  /**< Arreglo de valores hash */
} hash_map;

/**\brief Conjunto hash */
typedef struct hash_set {
  list_node* buckets;   /**< Nodo */
} hash_set;

/**\brief Crea un nodo para la lista
  *
  *\param d: Apuntador a objeto
  *\return list_node: Apuntador al nodo de la lista
  */
list_node* lat_crear_lista_node(void* d);

/**\brief Crear una lista vacia
  *
  *\return list_node: Apuntador al primer nodo de la lista
  */
list_node* lat_crear_lista();

/**\brief Busca un elemento en la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto buscado
  *\return int: Retorna 1 si se encontro el objeto 0 en caso contrario
  */
int find_list(list_node* l, void* data);

/**\brief Inserta un elemento en la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto
  */
void insert_list(list_node* l, void* data);

/**\brief Elimina un elemento de la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto
  */
void remove_list(list_node* l, void* data);

/**\brief Devuelve la longitud de la lista
  *
  *\param l: Apuntador a la lista
  *\return int: La longitud de la lista
  */
int length_list(list_node* l);

/**
  *\brief Crea una tabla hash
  *
  *\return hash_map*: Apuntador a la tabla creada
  */
hash_map* make_hash_map();

/**\brief Crea un hash de una cadena
  *
  *\param key: Apuntador a cadena
  *\return int: Numero hash creado para la cadena
  */
int hash(char* key);

/**\brief Obtiene un elemento de la tabla hash
  *
  *\param m: Apuntador a la tabla hash
  *\param key: Llave buscada
  *\return void*: Apuntador al objeto buscado
  */
void* get_hash(hash_map* m, char* key);

/**\brief Guarda un elemento en la tabla buscada
  *
  *\param m: Apuntador a la tabla hash
  *\param key: Llave
  *\param val: Valor
  */
void set_hash(hash_map* m, char* key, void* val);

/**\brief Copia una tabla hash con todos sus elementos
  *\param m: Apuntador a tabla hash
  */
hash_map* copy_hash(hash_map* m);

/**\brief Duplica una cadena
  *
  * \param s: Apuntador a una cadena de caracteres
  * \return char*: Apuntador a una cadena de caracteres
  */
char* strdup0(const char* s);

/**\brief Analiza una cadena de caracteres
  *
  * \param s: Apuntador a una cadena de caracteres
  * \param n: Longitud de la cadena
  * \return char*: Apuntador a una cadena de caracteres
  */
char* parse_string(const char* s, size_t n);

/**\brief Concatena dos cadenas
  *
  *\param s1: Cadena 1 a concatenar
  *\param s2: Cadena 2 a concatenar
  *\return char*: Apuntador a cadena resultado de s1 + s2
  */
char* concat(char* s1, char* s2);

/**\brief Convierte un entero a cadena
  *
  *\param i: Valor entero largo
  *\return char*: Apuntador a cadena
  */
char* int2str(long i);

/**\brief Convierte un decimal a cadena
  *
  *\param d: Valor decimal
  *\return char*: Apuntador a cadena
  */
char* double2str(double d);

/**\brief Convierte un caracter a cadena
  *
  *\param c: Valor del caracter
  *\return char*: Apuntador a cadena
  */
char* char2str(char c);

/**\brief Convierte un valor logico
  *
  *\param i: Valor logico 0, 1
  *\return char*: Apuntador a cadena
  */
char* bool2str(int i);

/**\brief Valida si una cadena inicia con
  *
  *\param base: Cadena original
  *\param str: Cadena a buscar
  *\return bool: true si la cadena base inicia con el valor de str
  */
bool startsWith(char* base, char* str);

/**\brief Valida si una cadena termina con
  *
  *\param base: Cadena original
  *\param str: Cadena a buscar
  *\return bool: true si la cadena base termina con el valor de str
  */
bool endsWith(char* base, char* str);

/**\brief Regresa el indice en donde se encontro la cadena str
  *
  *\param base: Cadena original
  *\param str: Cadena a buscar
  *\return int: Indice dentro de cadena original
  */
int indexOf(char* base, char* str);

/**\brief Regresa el indice en donde se encontro la cadena str a partir de una posicion
  *
  *\param base: Cadena original
  *\param str: Cadena a buscar
  *\param startIndex: Indice inicial
  *\return int: Indice dentro de cadena original
  */
int indexOf_shift(char* base, char* str, int startIndex);

/**\brief Regresa el ultimo indice en donde se encontro la cadena str
  *
  *\param base: Cadena original
  *\param str: Cadena a buscar
  *\return int: Indice dentro de cadena original
  */
int lastIndexOf(char* base, char* str);

/**\brief Inserta una subcadena dentro de una cadena a partir de una posicion
  *
  *\param dest: Cadena destino
  *\param src: Cadena a insertar
  *\param pos: Posicion en la que se insertara la cadena
  *\return char*: Apuntador a la cadena resultante
  */
char* insert(char *dest, char* src, int pos);

/**\brief Rellena el espacio izquierdo de una cadena con un caracter especificado
  *
  *\param base: Cadena original
  *\param n: Longitud de la cadena resultante
  *\param c: Caracter con el que se rellenara
  *\return char*: Apuntador a la cadena resultante
  */
char* padLeft(char* base, int n, char* c);

/**\brief Rellena el espacio derecho de una cadena con un caracter especificado
  *
  *\param base: Cadena original
  *\param n: Longitud de la cadena resultante
  *\param c: Caracter con el que se rellenara
  *\return char*: Apuntador a la cadena resultante
  */
char* padRight(char *base, int n, char* c);

/**\brief Reemplaza una subcadena con otra subcadena
  *
  *\param str: Cadena original
  *\param orig: Cadena a reemplazar
  *\param rep: Cadena reemplazo
  *\return char*: Apuntador a la cadena resultante
  */
char *replace(char *str, char *orig, char *rep);

/**\brief Crea una subcadena especificando posicion inicial y longitud
  *
  *\param str: Cadena original
  *\param beg: Posicion de inicio
  *\param n: Longitud de la cadena resultante
  *\return char*: Apuntador a la cadena resultante
  */
char *substring(const char* str, int beg, int n);

/**\brief Convierte a minusculas la cadena
  *
  *\param str: Cadena original
  *\return char*: Apuntador a la cadena resultante
  */
char *toLower(const char* str);

/**\brief Convierte a mayusculas la cadena
  *
  *\param str: Cadena original
  *\return char*: Apuntador a la cadena resultante
  */
char *toUpper(const char* str);

/**\brief Elimina espacios vacios al inicio y fin de la cadena
  *
  *\param str: Cadena original
  *\return char*: Apuntador a la cadena resultante
  */
char *trim(const char* str);


/**\brief Valida si un archivo se puede leer
  *
  *\param archivo: Nombre completo del archivo
  *\return bool: true si se puede leer
  */
bool legible(const char *archivo);
#endif /*_UTILS_H_*/
