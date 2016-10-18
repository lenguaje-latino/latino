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
#ifndef _VM_H_
#define _VM_H_

/** \file vm.h
  *
  * Contiene funciones para el manejo de la maquina virtual
  *
  */

#include <math.h>

/**\brief Objeto tipo maquina virtual */
typedef struct lat_mv lat_mv;

#include "object.h"
#include "libdict.h"
#include "liblist.h"
#include "libstring.h"

/**\brief Bandera para debuguear las instrucciones que se generan con el AST */
#define DEPURAR_MV 0

/**\brief op_codes de la maquina virtual */
#define NOP                 0
#define HALT                1
#define UNARY_MINUS         2
#define BINARY_ADD          3
#define BINARY_SUB          4
#define BINARY_MUL          5
#define BINARY_DIV          6
#define BINARY_MOD          7
#define OP_GT               8
#define OP_GE               9
#define OP_LT              10
#define OP_LE              11
#define OP_EQ              12
#define OP_NEQ             13
#define OP_AND             14
#define OP_OR              15 
#define OP_NOT             16 
#define OP_INC             17
#define OP_DEC             18
#define CONCAT             19
#define LOAD_CONST         20
#define LOAD_NAME          21
#define STORE_NAME         22
#define JUMP_ABSOLUTE      23
#define POP_JUMP_IF_FALSE  24
#define POP_JUMP_IF_TRUE   25
#define SETUP_LOOP         26
#define POP_BLOCK          27
#define CALL_FUNCTION      28
#define RETURN_VALUE       29
#define MAKE_FUNCTION      30
#define INC                31
#define DEC                32
#define LOAD_ATTR          33
#define BUILD_LIST         34
#define STORE_SUBSCR       35
#define BINARY_SUBSCR      36
#define BUILD_MAP          37
#define STORE_MAP          38
#define STORE_ATTR         39

/**\brief Estructura que almacena las instrucciones bytecode de la MV */
typedef struct lat_bytecode
{
    int ins;    /**< Instruccion */
    int a;    /**< registro a */
    int b;    /**< registro b */
    void* meta;    /**< datos */
} lat_bytecode;

/**\brief Define una funcion de usuario */
typedef struct lat_function
{
    lat_bytecode* bcode;    /**< Instrucciones de la funcion */
    //lat_objeto *closure;
} lat_function;

/**\brief Define la maquina virtual (MV) */
typedef struct lat_mv
{
    lat_objeto* modulos;
    lat_objeto* gc_objetos;    
    lat_objeto* otros_objetos;    
    lat_objeto* pila;     //< pila de la maquina virtual
    lat_objeto* contexto_pila[256];   //< Arreglo para el contexto actual
    lat_objeto* objeto_verdadero;   //< Valor logico verdadero
    lat_objeto* objeto_falso;   //< Valor logico falso 
    lat_objeto* objeto_nulo;
    int apuntador_ctx;      //< Apuntador para el contexto de la pila        
    bool REPL;  //< Indica si esta corriendo REPL
    int num_callf;  //< Numero de llamadas a funcion recursivas
    size_t memoria_usada;   //< Tamanio de memoria creado dinamicamente
    char *nombre_archivo;
} lat_mv;

/**\brief Busca un elemento en la lista
  * 
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto buscado
  *\return int: Retorna 1 si se encontro el objeto 0 en caso contrario
  */
bool __lista_contiene_valor(lista* l, void* data);

/**\brief Obtiene el nombre del bytecode
  *
  *\param vm: Apuntador a la MV
  */
const char* __obtener_bytecode_nombre(int inst);

/**\brief Envia a consola el valor del objeto
  *
  *\param vm: Apuntador a la MV
  */
void __imprimir_objeto(lat_mv* vm, lat_objeto* in, bool fmt);

/**\brief Envia a consola el contenido de la lista
  *
  *\param vm: Apuntador a la MV
  *\param l: Apuntador a la lista
  */
void __imprimir_lista(lat_mv* vm, lista* l, bool fmt);

/**\brief Obtiene un elemento de la lista en la posicion indicada
  *
  *\param vm: Apuntador a la MV
  *\param l: Apuntador a la lista
  */
lat_objeto* __lista_obtener_elemento(lista* list, int pos);

/**\brief Obtiene un nodo de la lista en la posicion indicada
  *
  *\param lista: Apuntador a la lista
  *\param pos: Posicion en la lista
  *\return lista_nodo: Apuntador al nodo de la lista
  */
lista_nodo* __lista_obtener_nodo(lista* list, int pos);

/**\brief Envia a consola el contenido del diccionario
  *
  *\param vm: Apuntador a la MV
  *\param d: Apuntador al diccionario
  */
void __imprimir_diccionario(lat_mv* vm, hash_map* d);

/**\brief Regresa el nombre del tipo de dato
  *
  *\param tipo: Tipo de dato Latino
  *\return char: Apuntador al nombre del tipo
  */
char* __tipo(int tipo);

/**\brief Crea la maquina virtual (MV)
  *
  *\return lat_vm: Apuntador a la MV
  */
lat_mv* lat_mv_crear();

/**\brief Destruye la memoria asignada por la maquina virtual (MV)
  *
  *\param lat_vm: Apuntador a la MV
  */
void lat_destruir_mv(lat_mv* mv);

/**\brief inserta un objeto en la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\param o: Apuntador a objeto
  */
void lat_apilar(lat_mv* vm, lat_objeto* o);

/**\brief Extrae un objeto de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\return lat_objeto: Apuntador a objeto
  */
lat_objeto* lat_desapilar(lat_mv* vm);

/**\brief inserta un contexto en la pila de la MV
  *
  *\param vm: Apuntador a la MV
  */
void lat_apilar_contexto(lat_mv* vm);

/**\brief Extrae un contexto de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  */
void lat_desapilar_contexto(lat_mv* vm);

/**\brief Extrae el contexto de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\return lat_objeto: Apuntador al contexto
  */
lat_objeto* lat_obtener_contexto(lat_mv* vm);

/**\brief Define una funcion creada por el usuario
  *
  *\param vm: Apuntador a la MV
  *\param inslist: Lista de instrucciones de la funcion
  *\return lat_objeto: Apuntador a un objeto tipo funcion
  */
lat_objeto* lat_definir_funcion(lat_mv* vm, lat_bytecode* inslist);

/**\brief Define una funcion creada en C
  *
  *\param vm: Apuntador a la MV
  *\param *function: Apuntador a la funcion definida en C
  *\return lat_objeto: Apuntador a un objeto tipo cfuncion
  */
lat_objeto* lat_definir_cfuncion(lat_mv* vm, void (*function)(lat_mv* vm));

/**\brief Envia a consola el valor del objeto
  *
  *\param vm: Apuntador a la MV
  */
void lat_imprimir(lat_mv* vm);

/**\brief Ejecuta una cadena de codigo Latino
  *
  *\param vm: Apuntador a la MV
  */
void lat_ejecutar(lat_mv *vm);

/**\brief Ejecuta un archivo con codigo Latino
  *
  *\param vm: Apuntador a la MV
  */
void lat_ejecutar_archivo(lat_mv *vm);

/**\brief Operador - unario
  *
  *\param vm: Apuntador a la MV
  */
void __menos_unario(lat_mv* vm);

/**\brief Operador +
  *
  *\param vm: Apuntador a la MV
  */
void __sumar(lat_mv* vm);

/**\brief Operador -
  *
  *\param vm: Apuntador a la MV
  */
void __restar(lat_mv* vm);

/**\brief Operador *
  *
  *\param vm: Apuntador a la MV
  */
void __multiplicar(lat_mv* vm);

/**\brief Operador /
  *
  *\param vm: Apuntador a la MV
  */
void __dividir(lat_mv* vm);

/** Modulo de un decimal (fmod) 5.3 / 2 es 1.300000
  *
  * \param vm: Maquina virtual de latino
  *
  */
void __modulo(lat_mv* vm);

/**\brief Operador !=
  *
  *\param vm: Apuntador a la MV
  */
void __diferente(lat_mv* vm);

/**\brief Operador ==
  *
  *\param vm: Apuntador a la MV
  */
void __igualdad(lat_mv* vm);

/**\brief Operador <
  *
  *\param vm: Apuntador a la MV
  */
void __menor_que(lat_mv* vm);

/**\brief Operador <=
  *
  *\param vm: Apuntador a la MV
  */
void __menor_igual(lat_mv* vm);

/**\brief Operador <
  *
  *\param vm: Apuntador a la MV
  */
void __mayor_que(lat_mv* vm);

/**\brief Operador >=
  *
  *\param vm: Apuntador a la MV
  */
void __mayor_igual(lat_mv* vm);

/**\brief Operador &&
  *
  *\param vm: Apuntador a la MV
  */
void __y_logico(lat_mv* vm);

/**\brief Operador ||
  *
  *\param vm: Apuntador a la MV
  */
void __o_logico(lat_mv* vm);

/**\brief Operador !
  *
  *\param vm: Apuntador a la MV
  */
void __no_logico(lat_mv* vm);

/**\brief Obtiene el tipo de dato en cadena
  *
  *\param vm: Apuntador a la MV
  */
void lat_tipo(lat_mv* vm);

/**\brief Convierte un valor a logico
  *
  *\param vm: Apuntador a la MV
  */
void lat_logico(lat_mv* vm);

/**\brief Convierte un valor a decimal
  *
  *\param vm: Apuntador a la MV
  */
void lat_numerico(lat_mv* vm);

/**\brief Convierte un valor a cadena
  *
  *\param vm: Apuntador a la MV
  */
void lat_cadena(lat_mv* vm);

/**\brief Determina si una cadena es decimal
  *
  *\param vm: Apuntador a la MV
  */
void lat_es_decimal(lat_mv* vm);

/**\brief Formatea un decimal con el numero de caracteres decimales que se especifique
  *
  *\param vm: Apuntador a la MV
  */
void lat_formato_numero(lat_mv* vm);

/**\brief Sale del sistema de Latino REPL
  *
  *\param vm: Apuntador a la MV
  */
void lat_salir(lat_mv* vm);

/**\brief Crea un objeto bytecode
  *
  *\param i: Tipo de instruccion
  *\param a: Registro a
  *\param b: Registro b
  *\param meta: Datos
  *\return lat_bytecode: Objeto bytecode
  */
lat_bytecode lat_bc(int i, int a, int b, void* meta);

/**\brief Ejecuta una funcion
  *
  *\param vm: Apuntador a la MV
  *\param func: Apuntador a funcion a ejecutar
  */
void lat_llamar_funcion(lat_mv* vm, lat_objeto* func);

/**\brief Agrega un elemento a la lista
  *
  *\param vm: Apuntador a la MV
  */
void lat_agregar(lat_mv *vm);

/**\brief Agrega los elementos de una lista al final de la lista
  *
  *\param vm: Apuntador a la MV
  */
void lat_extender(lat_mv *vm);

/**\brief Regresa el indice en que se encuentra el objeto enviado
  *
  *\param lista: Apuntador a la lista
  *\param lista: Apuntador al objeto buscado
  */
int __lista_obtener_indice(lista* list, void* data);

/**\brief Elimina un elemento en el indice indicado
  *
  *\param vm: Apuntador a la MV
  */
void lat_eliminar_indice(lat_mv* vm);

/**\brief Invierte los elementos de una lista
  *
  *\param vm: Apuntador a la MV
  */
void lat_invertir_lista(lat_mv* vm);

void lat_json_decodificar(lat_mv* vm);

void lat_json_codificar(lat_mv* vm);

#endif //_VM_H_
