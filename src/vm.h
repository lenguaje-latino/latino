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

typedef struct lat_vm lat_vm;

#include "utils.h"
#include "object.h"

#define DEBUG_VM 0

typedef enum lat_ins {
  OP_END,
  OP_NOP,
  OP_PUSH,
  OP_POP,
  OP_GET,
  OP_SET,
  OP_STORECHAR,
  OP_STOREINT,
  OP_STOREDOUBLE,
  OP_STORESTR,
  OP_STOREBOOL,
  OP_STORELIST,
  OP_PUSHLIST,
  OP_POPLIST,
  OP_LISTGETITEM,
  OP_MOV,
  OP_GLOBALNS,
  OP_LOCALNS,
  OP_FN,
  OP_NS,
  OP_ENDNS,
  OP_JMP,
  OP_JMPIF,
  OP_CALL,
  OP_NOT,
  OP_INC,
  OP_DEC,
  OP_STOREDICT,
  OP_PUSHDICT,
  OP_POPDICT
} lat_ins;

typedef struct lat_bytecode {
  lat_ins ins;
  int a;
  int b;
  void* meta;
} lat_bytecode;

typedef struct lat_function {
  lat_bytecode* bcode;
  //lat_objeto *closure;
} lat_function;

struct lat_vm {
  list_node* stack;
  list_node* all_objects;
  list_node* gc_objects;
  lat_objeto* regs[256];
  lat_objeto* ctx_stack[256];
  lat_objeto* true_object;
  lat_objeto* false_object;
  size_t memory_usage;
  int ctx_stack_pointer;
};

lat_vm* lat_crear_maquina_virtual();
void lat_ejecutar(lat_vm* vm);
void lat_ejecutar_archivo(lat_vm* vm);
void lat_apilar(lat_vm* vm, lat_objeto* o);
lat_objeto* lat_desapilar(lat_vm* vm);
void lat_apilar_lista(lat_objeto* list, lat_objeto* o);
lat_objeto* lat_desapilar_lista(lat_objeto* list);
void lat_apilar_contexto(lat_vm* vm);
void lat_desapilar_contexto(lat_vm* vm);
void lat_apilar_contexto_predefinido(lat_vm* vm, lat_objeto* ctx);
lat_objeto* lat_desapilar_contexto_predefinido(lat_vm* vm);
lat_objeto* lat_obtener_contexto(lat_vm* vm);
void lat_basurero_agregar(lat_vm* vm, lat_objeto* o);
void lat_basurero(lat_vm* vm);
lat_objeto* lat_definir_funcion(lat_vm* vm, lat_bytecode* inslist);
lat_objeto* lat_definir_cfuncion(lat_vm* vm, void (*function)(lat_vm* vm));

void lat_numero_lista(lat_vm* vm);
void lat_imprimir_lista(lat_vm* vm, list_node* l);
void lat_imprimir(lat_vm* vm);
void lat_clonar(lat_vm* vm);
void lat_cons(lat_vm* vm);
void lat_sumar(lat_vm* vm);
void lat_restar(lat_vm* vm);
void lat_multiplicar(lat_vm* vm);
void lat_dividir(lat_vm* vm);
void lat_modulo(lat_vm* vm);
void lat_diferente(lat_vm* vm);
void lat_igualdad(lat_vm* vm);
void lat_menor_que(lat_vm* vm);
void lat_menor_igual(lat_vm* vm);
void lat_mayor_que(lat_vm* vm);
void lat_mayor_igual(lat_vm* vm);
void lat_negacion(lat_vm* vm);

/*conversion de tipos de dato*/
void lat_logico(lat_vm* vm);
void lat_entero(lat_vm* vm);
void lat_caracter(lat_vm* vm);
void lat_decimal(lat_vm* vm);
void lat_cadena(lat_vm* vm);

void lat_maximo(lat_vm* vm);
void lat_minimo(lat_vm* vm);


lat_bytecode lat_bc(lat_ins i, int a, int b, void* meta);
void lat_llamar_funcion(lat_vm* vm, lat_objeto* func);

#endif //_VM_H_
