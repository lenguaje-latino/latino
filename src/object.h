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

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct lat_objeto lat_objeto;

#include "utils.h"
#include "vm.h"

/** \file object.h
*
* Contiene las funciones para el manejo de objetos
*
*/

/** \brief Tipo de dato
*
* Tipo de dato que maneja la maquina virtual
*/
typedef enum lat_type {
  T_NULO,    /**< nulo */
  T_INSTANCE,    /**< instancia */
  T_LIT,    /**< literal */
  T_INT,    /**< entero */
  T_DOUBLE,    /**< decimal */
  T_STR,    /**< cadena */
  T_BOOL,    /**< logico */
  T_LIST,    /**< lista */
  T_DICT,    /**< diccionario */
  T_FUNC,    /**< funcion */
  T_CFUNC,    /**< funcion C */
  T_STRUCT,    /**< estructura */
} lat_type;

/** \brief Datos del objeto
*
* Almacena la informacion del objeto
*/
typedef union lat_objeto_data {
  hash_map* instance;   /**< nombre del objeto */
  char* c;  /**< valor literal */
  long i;  /**< valor entero */
  double d;  /**< valor decimal */
  char* str;  /**< valor cadena */
  bool b;  /**< valor logico */
  list_node* list;  /**< valor de la lista */
  hash_map* dict;  /**< valor del diccionario */
  void* func;  /**< valor funcion */
  void (*cfunc)(lat_vm*);  /**< valor funcion C */
  void* cstruct;  /**< valor estructura */
} lat_objeto_data;

/** \brief Objeto
*
* Almacena toda la informacion del objeto
*/
struct lat_objeto {
  lat_type type;    /**< Tipo de objeto */
  int marked;    /**< para marcar el objeto Colector de basura */
  size_t data_size;   /**< Tamanio de la informacion */
  bool es_constante;   /**< Valida si es una constante */
  int num_declared;   /**< Numero de veces declarado */
  lat_objeto_data data;   /**< Informacion del objeto */
};

/** \brief Asigna el objeto a un contexto (local / publico)
  *
  * \param ns: Contexto en el que se encuentra el objeto
  * \param name: Nombre del objeto
  * \param o: objeto a asignado
  */
void lat_asignar_contexto_objeto(lat_objeto* ns, lat_objeto* name, lat_objeto* o);

/** \brief Obtiene un objeto de un contexto  (local / publico)
  *
  * \param ns: Contexto en el que se encuentra el objeto
  * \param name: Nombre del objeto
  */
lat_objeto* lat_lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name);

/** \brief Valida si el contexto enviado contiene al objeto
  *
  * \param ns: Contexto en el que se encuentra el objeto
  * \param name: Nombre del objeto
  */
int lat_contexto_contiene(lat_objeto* ns, lat_objeto* name);

/** \brief Crea un objeto determinado
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_crear_objeto(lat_vm* vm);

/** \brief Crea un contexto determinado
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al contexto creado
  */
lat_objeto* lat_instancia(lat_vm* vm);

/** \brief Crea un objeto literal
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: Apuntador a la cadena de caracteres
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_literal_nuevo(lat_vm* vm, const char* val);

/** \brief Crea un objeto entero
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor entero
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_entero_nuevo(lat_vm* vm, long val);

/** \brief Crea un objeto decimal
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor decimal
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_decimal_nuevo(lat_vm* vm, double val);

/** \brief Crea un objeto cadena
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor cadena
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_cadena_nueva(lat_vm* vm, const char* val);

/** \brief Crea un objeto logico
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor logico
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_logico_nuevo(lat_vm* vm, bool val);

/** \brief Crea un objeto lista
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador a un nodo de la lista
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_lista_nueva(lat_vm* vm, list_node* l);

/** \brief Crea un objeto funcion
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_funcion_nueva(lat_vm* vm);

/** \brief Crea un objeto funcion C
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_cfuncion_nueva(lat_vm* vm);

/** \brief Marca un objeto para el colector de basura
  *
  * \param o: Apuntador al objeto
  * \param m: valor de la marca
  */
void lat_marcar_objeto(lat_objeto* o, int m);

/** \brief Marca una lista de objetos para el colector de basura
  *
  * \param l: Apuntador al nodo de la lista
  * \param m: valor de la marca
  */
void lat_marcar_lista(list_node* l, unsigned char m);

/** \brief Marca una tabla hash de objetos para el colector de basura
  *
  * \param l: Apuntador al nodo de la tabla hash
  * \param m: valor de la marca
  */
void lat_marcar_hash(hash_map* l, unsigned char m);

/** \brief Elimina un objeto de la lista de objetos creados dinamicamente
  *
  * \param vm: Intancia de la maquina virtual
  * \param o: Apuntador al objeto
  */
void lat_eliminar_objeto(lat_vm* vm, lat_objeto* o);

/** \brief Elimina un objeto lista de la lista de objetos creados dinamicamente
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador al nodo de la lista
  */
void lat_eliminar_lista(lat_vm* vm, list_node* l);

/** \brief Elimina una tabla hash de la lista de objetos creados dinamicamente
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador al nodo de la tabla hash
  */
void lat_eliminar_hash(lat_vm* vm, hash_map* l);

/** \brief Clona (copia) un objeto
  *
  * \param vm: Intancia de la maquina virtual
  * \param o: Apuntador al objeto
  */
lat_objeto* lat_clonar_objeto(lat_vm* vm, lat_objeto* o);

/** \brief Clona (copia) una lista
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador al nodo de la lista
  */
list_node* lat_clonar_lista(lat_vm* vm, list_node* l);

/** \brief Clona (copia) una tabla hash
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador al nodo de la tabla hash
  */
hash_map* lat_clonar_hash(lat_vm* vm, hash_map* l);

/** \brief Obtiene el valor de la literal de un objeto
  *
  * \param o: Apuntador al objeto
  * \return char*: Apuntador a una cadena de caracteres
  */
char* lat_obtener_literal(lat_objeto* o);

/** \brief Obtiene el valor entero de un objeto
  *
  * \param o: Apuntador al objeto
  * \return long: Valor entero
  */
long lat_obtener_entero(lat_objeto* o);

/** \brief Obtiene el valor decimal de un objeto
  *
  * \param o: Apuntador al objeto
  * \return double: Valor decimal
  */
double lat_obtener_decimal(lat_objeto* o);

/** \brief Obtiene el valor de la cadena de un objeto
  *
  * \param o: Apuntador al objeto
  * \return char*: Apuntador a una cadena de caracteres
  */
char* lat_obtener_cadena(lat_objeto* o);

/** \brief Obtiene el valor logico de un objeto
  *
  * \param o: Apuntador al objeto
  * \return bool: Valor logico
  */
bool lat_obtener_logico(lat_objeto* o);

/** \brief Obtiene el valor de la lista de un objeto
  *
  * \param o: Apuntador al objeto
  * \return list_node: Apuntador al nodo de la lista
  */
list_node* lat_obtener_lista(lat_objeto* o);

/** \brief Obtiene el valor de la estructura de un objeto
  *
  * \param o: Apuntador al objeto
  */
void* lat_obtener_estructura(lat_objeto* o);

#endif // !_OBJECT_H_
