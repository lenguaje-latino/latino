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
#ifndef _VM_H_
#define _VM_H_

/** \file mv.h
  *
  * Contiene funciones para el manejo de la maquina virtual
  *
  */

#include <math.h>

typedef struct lat_mv lat_mv;

#include "latdic.h"
#include "latlist.h"
#include "latobj.h"

/**\brief Bandera para debuguear las instrucciones que se generan con el AST */
#define DEPURAR_MV 0

/**\brief op_codes de la maquina virtual */
#define NOP 0
#define HALT 1
#define UNARY_MINUS 2
#define BINARY_ADD 3
#define BINARY_SUB 4
#define BINARY_MUL 5
#define BINARY_DIV 6
#define BINARY_MOD 7
#define OP_GT 8
#define OP_GE 9
#define OP_LT 10
#define OP_LE 11
#define OP_EQ 12
#define OP_NEQ 13
#define OP_AND 14
#define OP_OR 15
#define OP_NOT 16
#define OP_INC 17
#define OP_DEC 18
#define CONCAT 19
#define LOAD_CONST 20
#define LOAD_NAME 21
#define STORE_NAME 22
#define JUMP_ABSOLUTE 23
#define POP_JUMP_IF_FALSE 24
#define POP_JUMP_IF_TRUE 25
#define SETUP_LOOP 26
#define POP_BLOCK 27
#define CALL_FUNCTION 28
#define RETURN_VALUE 29
#define MAKE_FUNCTION 30
#define INC 31
#define DEC 32
#define LOAD_ATTR 33
#define BUILD_LIST 34
#define STORE_SUBSCR 35
#define BINARY_SUBSCR 36
#define BUILD_MAP 37
#define STORE_MAP 38
#define STORE_ATTR 39
#define STORE_GLOBAL 40
#define OP_REGEX 41

/**\brief Objeto tipo maquina virtual */

typedef void (*lat_CFuncion)(lat_mv *mv);

typedef struct lat_CReg {
  const char *nombre;
  lat_CFuncion func;
  int num_params;
} lat_CReg;

/**\brief Estructura que almacena las instrucciones bytecode de la MV */
typedef struct lat_bytecode {
  int ins;    /**< Instruccion */
  int a;      /**< registro a */
  int b;      /**< registro b */
  void *meta; /**< datos */
} lat_bytecode;

/**\brief Define una funcion de usuario */
typedef struct lat_function {
  lat_bytecode *bcode; /**< Instrucciones de la funcion */
} lat_function;

/**\brief Define la maquina virtual (MV) */
typedef struct lat_mv {
  lat_objeto *modulos;
  lat_objeto *gc_objetos;
  lat_objeto *otros_objetos;
  lat_objeto *pila;               //< pila de la maquina virtual
  lat_objeto *contexto_pila[256]; //< Arreglo para el contexto actual
  lat_objeto *objeto_verdadero;   //< Valor logico verdadero
  lat_objeto *objeto_falso;       //< Valor logico falso
  lat_objeto *objeto_nulo;
  lat_objeto *argv;
  int argc;
  int apuntador_ctx;    //< Apuntador para el contexto de la pila
  int num_callf;        //< Numero de llamadas a funcion recursivas
  size_t memoria_usada; //< Tamanio de memoria creado dinamicamente
  bool menu;
  bool REPL; //< Indica si esta corriendo REPL
  char *nombre_archivo;
} lat_mv;

/**\brief Busca un elemento en la lista
  *
  *\param l: Apuntador a la lista
  *\param data: Apuntador a objeto buscado
  *\return int: Retorna 1 si se encontro el objeto 0 en caso contrario
  */
bool __lista_contiene_valor(lista *l, void *data);

/**\brief Obtiene el nombre del bytecode
  *
  *\param inst: Instruccion bytecode
  */
const char *__obtener_bytecode_nombre(int inst);

/**\brief Envia a consola el valor del objeto
  *
  *\param mv: Apuntador a la MV
  */
void __imprimir_objeto(lat_mv *mv, lat_objeto *in, bool fmt);

/**\brief Obtiene un elemento de la lista en la posicion indicada
  *
  *\param mv: Apuntador a la MV
  *\param l: Apuntador a la lista
  */
lat_objeto *__lista_obtener_elemento(lista *list, int pos);

/**\brief Obtiene un nodo de la lista en la posicion indicada
  *
  *\param lista: Apuntador a la lista
  *\param pos: Posicion en la lista
  *\return lista_nodo: Apuntador al nodo de la lista
  */
lista_nodo *__lista_obtener_nodo(lista *list, int pos);

/**\brief Crea la maquina virtual (MV)
  *
  *\return lat_mv: Apuntador a la MV
  */
lat_mv *lat_mv_crear();

/**\brief Destruye la memoria asignada por la maquina virtual (MV)
  *
  *\param lat_mv: Apuntador a la MV
  */
void lat_destruir_mv(lat_mv *mv);

/**\brief inserta un objeto en la pila de la MV
  *
  *\param mv: Apuntador a la MV
  *\param o: Apuntador a objeto
  */
void lat_apilar(lat_mv *mv, lat_objeto *o);

/**\brief Extrae un objeto de la pila de la MV
  *
  *\param mv: Apuntador a la MV
  *\return lat_objeto: Apuntador a objeto
  */
lat_objeto *lat_desapilar(lat_mv *mv);

/**\brief Extrae el contexto de la pila de la MV
  *
  *\param mv: Apuntador a la MV
  *\return lat_objeto: Apuntador al contexto
  */
lat_objeto *lat_obtener_contexto(lat_mv *mv);

lat_objeto *lat_obtener_global_ctx(lat_mv *mv);

/**\brief Define una funcion creada por el usuario
  *
  *\param mv: Apuntador a la MV
  *\param inslist: Lista de instrucciones de la funcion
  *\return lat_objeto: Apuntador a un objeto tipo funcion
  */
lat_objeto *lat_definir_funcion(lat_mv *mv, lat_bytecode *inslist,
                                int num_inst);

/**\brief Define una funcion creada en C
  *
  *\param mv: Apuntador a la MV
  *\param *function: Apuntador a la funcion definida en C
  *\return lat_objeto: Apuntador a un objeto tipo cfuncion
  */
lat_objeto *lat_definir_cfuncion(lat_mv *mv, lat_CFuncion func);

/**\brief Envia a consola el valor del objeto
  *
  *\param mv: Apuntador a la MV
  */
void lat_imprimir(lat_mv *mv);

/**\brief Ejecuta una cadena de codigo Latino
  *
  *\param mv: Apuntador a la MV
  */
void lat_cadena_ejecutar(lat_mv *mv);

/**\brief Determina si una cadena es decimal
  *
  *\param mv: Apuntador a la MV
  */
void lat_es_decimal(lat_mv *mv);

/**\brief Formatea un decimal con el numero de caracteres decimales que se
  *especifique
  *
  *\param mv: Apuntador a la MV
  */
void lat_formato_numero(lat_mv *mv);

/**\brief Crea un objeto bytecode
  *
  *\param i: Tipo de instruccion
  *\param a: Registro a
  *\param b: Registro b
  *\param meta: Datos
  *\return lat_bytecode: Objeto bytecode
  */
lat_bytecode lat_bc(int i, int a, int b, void *meta);

/**\brief Ejecuta una funcion
  *
  *\param mv: Apuntador a la MV
  *\param func: Apuntador a funcion a ejecutar
  */
void lat_llamar_funcion(lat_mv *mv, lat_objeto *func);

// void lat_json_codificar(lat_mv* mv);

void lat_importar_lib(lat_mv *mv, const char *nombre_lib, const lat_CReg *funs);

#endif //_VM_H_
