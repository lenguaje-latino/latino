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
  * Contiene funciones para el manejo de la máquina virtual
  *
  */

/**\brief Objeto tipo maquina virtual */
typedef struct lat_vm lat_vm;

#include "utils.h"
#include "object.h"

/**\brief Bandera para debuguear las instrucciones de la máquina virtual */
#define DEBUG_VM 0

/**\brief Instrucciones de la máquina virtual */
typedef enum lat_ins {
  OP_END,    /**< Fin de la máquina virtual */
  OP_NOP,    /**< Indica No operación */
  OP_PUSH,    /**< Inserta en la pila */
  OP_POP,    /**< Extrae de la pila */
  OP_GET,    /**< Obtiene un valor */
  OP_SET,    /**< Establece un valor */
  OP_STORELIT,    /**< Almacena un cadena tipo literal */
  OP_STOREINT,    /**< Almacena un entero */
  OP_STOREDOUBLE,    /**< Almacena un decimal */
  OP_STORESTR,    /**< Almacena una cadena */
  OP_STOREBOOL,    /**< Almacena un valor logico */
  OP_STORELIST,    /**< Almacena una lista */
  OP_PUSHLIST,    /**< Inserta la lista en la pila */
  OP_POPLIST,    /**< Extrae la lista de la pila */
  OP_LISTGETITEM,    /**< Obtiene un valor de la lista */
  OP_LISTSETITEM,    /**< Asigna un valor de la lista */
  OP_MOV,    /**< Mueve valores a los registros de la MV */
  OP_GLOBALNS,    /**< Almacena variables globales */
  OP_LOCALNS,    /**< Almacena variables locales */
  OP_FN,    /**< Define una funcion */
  OP_NS,    /**< Define un contexto */
  OP_ENDNS,    /**< Define el fin de un contexto */
  OP_JMP,    /**< Saltar a otra instruccion */
  OP_JMPIF,    /**< Saltar a otra instrucción SI la condición se cumple */
  OP_CALL,    /**< Llamada a una funcion */
  OP_NOT,    /**< Negacion de un valor logico */
  OP_INC,    /**< Incrementa un valor entero en 1 */
  OP_DEC,    /**< Disminuye un valor entero en 1 */
  OP_STOREDICT,    /**< Almacena un objeto diccionario */
  OP_PUSHDICT,    /**< Inserta un objeto diccionario en la pila */
  OP_POPDICT,    /**< Extrae un objeto diccionario de la pila */
  OP_PUSHDICTELEM, /**< Crea un objeto par (llave-valor) y lo agrega al diccionario de la pila */
  OP_DICTGETITEM,    /**< Obtiene un valor del diccionario */
  OP_DICTSETITEM    /**< Asigna un valor del diccionario */
} lat_ins;


/**\brief Estructura que almacena las instrucciones bytecode de la MV */
typedef struct lat_bytecode {
  lat_ins ins;    /**< Instruccion */
  int a;    /**< registro a */
  int b;    /**< registro b */
  void* meta;    /**< datos */
} lat_bytecode;

/**\brief Define una funcion de usuario */
typedef struct lat_function {
  lat_bytecode* bcode;    /**< Instrucciones de la funcion */
  //lat_objeto *closure;
} lat_function;

/**\brief Define la maquina virtual (MV) */
struct lat_vm {
  list_node* pila;     /**< pila de la maquina virtual */
  list_node* modulos;     /**< modulos importados en la MV */
  list_node* all_objects;     /**< objetos creados dinamicamente en la MV */
  list_node* gc_objects;     /**< objetos listos para liberar por el colector de basura */
  lat_objeto* regs[256];    /**< Registros de la MV */
  lat_objeto* ctx_stack[256];   /**< Tabla hash para el contexto actual */
  lat_objeto* true_object;   /**< Valor logico verdadero */
  lat_objeto* false_object;   /**< Valor logico falso */
  size_t memory_usage;      /**< Tamanio de memoria creado dinamicamente */
  int ctx_stack_pointer;      /**< Apuntador de la pila */
};

/**\brief Crea la maquina virtual (MV)
  *
  *\return lat_vm: Apuntador a la MV
  */
lat_vm* lat_crear_maquina_virtual();

/**\brief Ejecuta una cadena de instrucciones en la MV
  *
  *\param vm: Apuntador a la MV
  */
void lat_ejecutar(lat_vm* vm);

/**\brief Ejecuta un archivo en la MV
  *
  *\param vm: Apuntador a la MV
  */
void lat_ejecutar_archivo(lat_vm* vm);

/**\brief Inserta un objeto en la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\param o: Apuntador a objeto
  */
void lat_apilar(lat_vm* vm, lat_objeto* o);

/**\brief Extrae un objeto de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\return lat_objeto: Apuntador a objeto
  */
lat_objeto* lat_desapilar(lat_vm* vm);

/**\brief Inserta un objeto al final de la lista
  *
  *\param list: Apuntador a la lista
  *\param o: Apuntador a objeto
  */
void lat_apilar_lista(lat_objeto* list, lat_objeto* o);

/**\brief Extrae el ultimo elemento de la lista
  *
  *\param list: Apuntador a la lista
  *\return lat_objeto: Apuntador a objeto
  */
lat_objeto* lat_desapilar_lista(lat_objeto* list);

/**\brief Inserta un contexto en la pila de la MV
  *
  *\param vm: Apuntador a la MV
  */
void lat_apilar_contexto(lat_vm* vm);

/**\brief Extrae un contexto de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  */
void lat_desapilar_contexto(lat_vm* vm);

/**\brief Inserta el contexto principal en la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\param ctx: Apuntador al contexto
  */
void lat_apilar_contexto_predefinido(lat_vm* vm, lat_objeto* ctx);

/**\brief Extrae el contexto principal de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\return lat_objeto: Apuntador al contexto
  */
lat_objeto* lat_desapilar_contexto_predefinido(lat_vm* vm);

/**\brief Extrae el contexto de la pila de la MV
  *
  *\param vm: Apuntador a la MV
  *\return lat_objeto: Apuntador al contexto
  */
lat_objeto* lat_obtener_contexto(lat_vm* vm);

/**\brief Agrega un objeto al basurero para ser destruido
  *
  *\param vm: Apuntador a la MV
  *\param o: Apuntador a objeto
  */
void lat_basurero_agregar(lat_vm* vm, lat_objeto* o);

/**\brief Crea un objeto basurero
  *
  *\param vm: Apuntador a la MV
  */
void lat_basurero(lat_vm* vm);

/**\brief Define una funcion creada por el usuario
  *
  *\param vm: Apuntador a la MV
  *\param inslist: Lista de instrucciones de la funcion
  *\return lat_objeto: Apuntador a un objeto tipo funcion
  */
lat_objeto* lat_definir_funcion(lat_vm* vm, lat_bytecode* inslist);

/**\brief Define una funcion creada en C
  *
  *\param vm: Apuntador a la MV
  *\param *function: Apuntador a la funcion definida en C
  *\return lat_objeto: Apuntador a un objeto tipo cfuncion
  */
lat_objeto* lat_definir_cfuncion(lat_vm* vm, void (*function)(lat_vm* vm));

/**\brief Regresa el numero en que se encuentra un elemento
  *
  *\param vm: Apuntador a la MV
  */
void lat_numero_lista(lat_vm* vm);

/**\brief Envia a consola el contenido de la lista
  *
  *\param vm: Apuntador a la MV
  *\param l: Apuntador a la lista
  */
void lat_imprimir_lista(lat_vm* vm, list_node* l);

/**\brief Envia a consola el contenido del diccionario
  *
  *\param vm: Apuntador a la MV
  *\param d: Apuntador al diccionario
  */
void lat_imprimir_diccionario(lat_vm* vm, hash_map* d);

/**\brief Envia a consola el valor del objeto
  *
  *\param vm: Apuntador a la MV
  */
void lat_imprimir(lat_vm* vm);

/**\brief Clona un objeto
  *
  *\param vm: Apuntador a la MV
  */
void lat_clonar(lat_vm* vm);

/**\brief Agrega un elemento a la lista
  *
  *\param vm: Apuntador a la MV
  */
void lat_cons(lat_vm* vm);

/**\brief Operador +
  *
  *\param vm: Apuntador a la MV
  */
void lat_sumar(lat_vm* vm);

/**\brief Operador -
  *
  *\param vm: Apuntador a la MV
  */
void lat_restar(lat_vm* vm);

/**\brief Operador *
  *
  *\param vm: Apuntador a la MV
  */
void lat_multiplicar(lat_vm* vm);

/**\brief Operador /
  *
  *\param vm: Apuntador a la MV
  */
void lat_dividir(lat_vm* vm);

/**\brief Operador %
  *
  *\param vm: Apuntador a la MV
  */
void lat_modulo(lat_vm* vm);

/**\brief Operador !=
  *
  *\param vm: Apuntador a la MV
  */
void lat_diferente(lat_vm* vm);

/**\brief Operador ==
  *
  *\param vm: Apuntador a la MV
  */
void lat_igualdad(lat_vm* vm);

/**\brief Operador <
  *
  *\param vm: Apuntador a la MV
  */
void lat_menor_que(lat_vm* vm);

/**\brief Operador <=
  *
  *\param vm: Apuntador a la MV
  */
void lat_menor_igual(lat_vm* vm);

/**\brief Operador <
  *
  *\param vm: Apuntador a la MV
  */
void lat_mayor_que(lat_vm* vm);

/**\brief Operador >=
  *
  *\param vm: Apuntador a la MV
  */
void lat_mayor_igual(lat_vm* vm);

/**\brief Operador &&
  *
  *\param vm: Apuntador a la MV
  */
void lat_y(lat_vm* vm);

/**\brief Operador ||
  *
  *\param vm: Apuntador a la MV
  */
void lat_o(lat_vm* vm);

/**\brief Operador !
  *
  *\param vm: Apuntador a la MV
  */
void lat_negacion(lat_vm* vm);

/**\brief Obtiene el tipo de dato en cadena
  *
  *\param vm: Apuntador a la MV
  */
void lat_tipo(lat_vm* vm);

/**\brief Convierte un valor a logico
  *
  *\param vm: Apuntador a la MV
  */
void lat_logico(lat_vm* vm);

/**\brief Convierte un valor a entero
  *
  *\param vm: Apuntador a la MV
  */
void lat_entero(lat_vm* vm);

/**\brief Convierte un valor a literal
  *
  *\param vm: Apuntador a la MV
  */
void lat_literal(lat_vm* vm);

/**\brief Convierte un valor a decimal
  *
  *\param vm: Apuntador a la MV
  */
void lat_decimal(lat_vm* vm);

/**\brief Convierte un valor a cadena
  *
  *\param vm: Apuntador a la MV
  */
void lat_cadena(lat_vm* vm);

/**\brief Obtiene el maximo de dos numeros
  *
  *\param vm: Apuntador a la MV
  */
void lat_maximo(lat_vm* vm);

/**\brief Obtiene el minimo de dos numeros
  *
  *\param vm: Apuntador a la MV
  */
void lat_minimo(lat_vm* vm);

/**\brief Determina si una cadena es entero
  *
  *\param vm: Apuntador a la MV
  */
void lat_es_entero(lat_vm* vm);

/**\brief Determina si una cadena es decimal
  *
  *\param vm: Apuntador a la MV
  */
void lat_es_decimal(lat_vm* vm);

/**\brief Formatea un decimal con el numero de caracteres decimales que se especifique
  *
  *\param vm: Apuntador a la MV
  */
void lat_formato_numero(lat_vm* vm);

/**\brief Sale del sistema de Latino REPL
  *
  *\param vm: Apuntador a la MV
  */
void lat_salir(lat_vm* vm);

/**\brief Crea un objeto bytecode
  *
  *\param i: Tipo de instruccion
  *\param a: Registro a
  *\param b: Registro b
  *\param meta: Datos
  *\return lat_bytecode: Objeto bytecode
  */
lat_bytecode lat_bc(lat_ins i, int a, int b, void* meta);

/**\brief Ejecuta una funcion
  *
  *\param vm: Apuntador a la MV
  *\param func: Apuntador a funcion a ejecutar
  */
void lat_llamar_funcion(lat_vm* vm, lat_objeto* func);

#endif //_VM_H_
