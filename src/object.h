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

#include "vm.h"
#include "liblist.h"
#include "libdict.h"


/** \file object.h
*
* Contiene las funciones para el manejo de objetos
*
*/

/**< Incrementa y decrementa las referencias de un objeto */
#define Lat_INCREF(o)   o->num_ref++
#define Lat_DECREF(o)   o->num_ref--

/** \brief Tipo de dato
*
* Tipo de dato que maneja la maquina virtual
*/
typedef enum lat_type
{  
    T_NULO,     /**< Nulo, valor inicial */
    T_CONTEXT,    /**< Contexto o contexto de variables */    
    T_NUMERIC,    /**< decimal */
    T_STR,    /**< cadena */
    T_BOOL,    /**< logico */
    T_LIST,    /**< lista */
    T_DICT,    /**< diccionario */
    T_FUNC,    /**< funcion */
    T_CFUNC,    /**< funcion C */
    T_CLASS,    /**< estructura */
} lat_type;

/** \brief Datos del objeto
*
* Almacena la informacion del objeto
*/
typedef union lat_datos_objeto
{
    hash_map* contexto;   //< nombre del objeto    
    double numerico;           //< valor decimal
    char* cadena;          //< valor cadena
    bool logico;             //< valor logico
    lista* lista;        //< valor de la lista
    hash_map* dic;     //< valor del diccionario
    void* fun_usuario;         //< valor funcion
    void (*c_funcion)(lat_mv*);  //< valor funcion C
} lat_datos_objeto;

/** \brief Objeto
*
* Almacena toda la informacion del objeto
*/
typedef struct lat_objeto
{
    lat_type tipo;    /**< Tipo de objeto */
    int marca;    /**< para marcar el objeto Colector de basura */
    int num_ref;    /**< numero de referencias a este objeto */
    size_t tamanio;   /**< Tamanio de la informacion */
    bool es_constante;   /**< Valida si es una constante */
    int num_declared;   /**< Numero de veces declarado - auxiliar para validar CONSTANTES*/    
    int num_linea;
    int num_columna;
    int num_params;	/**<Numero de parametros de una funcion definida por el usuario */
    char* nombre_cfun;
    lat_datos_objeto datos;   /**< Informacion del objeto */
} lat_objeto;

struct lat_llave_valor
{
    lat_type type;
};

/** \brief Convierte un objeto a su representacion logica (verdadero o falso)
  *
  * \param o: objeto a convertir
  */
bool __objeto_a_logico(lat_objeto* o);

/** \brief Convierte un objeto a su representacion numerica
  *
  * \param o: objeto a convertir
  */
double __objeto_a_numerico(lat_objeto* o);

/** \brief Convierte un objeto a su representacion en cadena
  *
  * \param o: objeto a convertir
  */
char* __objeto_a_cadena(lat_objeto* o);

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
lat_objeto* lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name);

/** \brief Crea un objeto determinado
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_crear_objeto(lat_mv* vm);

/** \brief Crea un contexto determinado
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al contexto creado
  */
lat_objeto* lat_contexto_nuevo(lat_mv* vm);

/** \brief Crea un objeto decimal
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor decimal
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_numerico_nuevo(lat_mv* vm, double val);

/** \brief Crea un objeto cadena
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor cadena
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_cadena_nueva(lat_mv* vm, const char* val);

/** \brief Crea un objeto logico
  *
  * \param vm: Intancia de la maquina virtual
  * \param val: valor logico
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_logico_nuevo(lat_mv* vm, bool val);

/** \brief Crea un objeto lista
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador a un nodo de la lista
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_lista_nueva(lat_mv* vm, lista* l);

/** \brief Crea un objeto funcion
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_funcion_nueva(lat_mv* vm);

/** \brief Crea un objeto funcion C
  *
  * \param vm: Intancia de la maquina virtual
  * \return lat_objeto: Apuntador al objeto creado
  */
lat_objeto* lat_cfuncion_nueva(lat_mv* vm);

/** \brief Elimina un objeto de la lista de objetos creados dinamicamente
  *
  * \param vm: Intancia de la maquina virtual
  * \param o: Apuntador al objeto
  */
void lat_eliminar_objeto(lat_mv* vm, lat_objeto* o);

/** \brief Clona (copia) un objeto
  *
  * \param vm: Intancia de la maquina virtual
  * \param o: Apuntador al objeto
  */
lat_objeto* lat_clonar_objeto(lat_mv* vm, lat_objeto* o);

/** \brief Clona (copia) una lista
  *
  * \param vm: Intancia de la maquina virtual
  * \param l: Apuntador al nodo de la lista
  */
lista* lat_clonar_lista(lat_mv* vm, lista* l);

/** \brief Obtiene el valor decimal de un objeto
  *
  * \param o: Apuntador al objeto
  * \return double: Valor decimal
  */
double __numerico(lat_objeto* o);

/** \brief Obtiene el valor de la cadena de un objeto
  *
  * \param o: Apuntador al objeto
  * \return char*: Apuntador a una cadena de caracteres
  */
char* __cadena(lat_objeto* o);

/** \brief Obtiene el valor logico de un objeto
  *
  * \param o: Apuntador al objeto
  * \return bool: Valor logico
  */
bool __logico(lat_objeto* o);

/** \brief Obtiene el valor de la lista de un objeto
  *
  * \param o: Apuntador al objeto
  * \return list_node: Apuntador al nodo de la lista
  */
lista* __lista(lat_objeto* o);

/** \brief Valida si dos objetos son iguales
  *
  * \param lhs: Apuntador al objeto izquierdo
  * \param rhs: Apuntador al objeto derecho
  * \return bool: true si son iguales
  */
bool __es_igual(lat_objeto* lhs, lat_objeto* rhs);

/** \brief Compara dos objetos
  *
  * \param lhs: Apuntador al objeto izquierdo
  * \param rhs: Apuntador al objeto derecho
  * \return int: 0 si son iguales, -1 si el objeto izquierdo es menos y 1 si es mayor
  */
int __objeto_comparar(lat_objeto* lhs, lat_objeto* rhs);
#endif // !_OBJECT_H_
