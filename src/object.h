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

typedef enum lat_type {
  T_NULO,
  T_INSTANCE,
  T_LIT,
  T_INT,
  T_DOUBLE,
  T_STR,
  T_BOOL,
  T_LIST,
  T_FUNC,
  T_CFUNC,
  T_STRUCT,
} lat_type;

typedef union lat_objeto_data {
  hash_map* instance;
  char c;
  long i;
  double d;
  char* str;
  bool b;
  list_node* list;
  void* func;
  void (*cfunc)(lat_vm*);
  void* cstruct;
} lat_objeto_data;

struct lat_objeto {
  lat_type type;
  int marked;
  size_t data_size;
  bool es_constante;
  int num_declared;
  lat_objeto_data data;
};

void lat_asignar_contexto_objeto(lat_objeto* ns, lat_objeto* name, lat_objeto* o);
lat_objeto* lat_lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name);
int lat_contexto_contiene(lat_objeto* ns, lat_objeto* name);
lat_objeto* lat_crear_objeto(lat_vm* vm);
lat_objeto* lat_instancia(lat_vm* vm);
lat_objeto* lat_literal_nuevo(lat_vm* vm, const char* val);
lat_objeto* lat_entero_nuevo(lat_vm* vm, long val);
lat_objeto* lat_decimal_nuevo(lat_vm* vm, double val);
lat_objeto* lat_cadena_nueva(lat_vm* vm, const char* val);
lat_objeto* lat_logico_nuevo(lat_vm* vm, bool val);
lat_objeto* lat_lista_nueva(lat_vm* vm, list_node* l);
lat_objeto* lat_funcion_nueva(lat_vm* vm);
lat_objeto* lat_cfuncion_nueva(lat_vm* vm);

void lat_marcar_objeto(lat_objeto* o, int m);
void lat_marcar_lista(list_node* l, unsigned char m);
void lat_marcar_hash(hash_map* l, unsigned char m);

void lat_eliminar_objeto(lat_vm* vm, lat_objeto* o);
void lat_eliminar_lista(lat_vm* vm, list_node* l);
void lat_eliminar_hash(lat_vm* vm, hash_map* l);

lat_objeto* lat_clonar_objeto(lat_vm* vm, lat_objeto* obj);
list_node* lat_clonar_lista(lat_vm* vm, list_node* l);
hash_map* lat_clonar_hash(lat_vm* vm, hash_map* l);

char lat_obtener_literal(lat_objeto* o);
long lat_obtener_entero(lat_objeto* o);
double lat_obtener_decimal(lat_objeto* o);
char* lat_obtener_cadena(lat_objeto* o);
bool lat_obtener_logico(lat_objeto* o);
list_node* lat_obtener_lista(lat_objeto* o);
void* lat_obtener_estructura(lat_objeto* o);

#endif // !_OBJECT_H_
