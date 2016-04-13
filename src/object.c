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

#include "object.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "latino.h"
#include "utils.h"
#include "libstring.h"
#include "libmem.h"

void lat_asignar_contexto_objeto(lat_objeto* ns, lat_objeto* name, lat_objeto* o)
{
  if (ns->type != T_INSTANCE) {
    debug("ns->type: %d", ns->type);
    lat_registrar_error("Namespace no es una instancia");
  }
  else {
    hash_map* h = ns->data.instance;
    set_hash(h, lat_obtener_cadena(name), (void*)o);
  }
}

lat_objeto* lat_lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name)
{
  if (ns->type != T_INSTANCE) {
    debug("ns->type: %d", ns->type);
    lat_registrar_error("Namespace is not an instance");
  }
  else {
    hash_map* h = ns->data.instance;
    lat_objeto* ret = (lat_objeto*)get_hash(h, lat_obtener_cadena(name));
    if (ret == NULL) {
      lat_registrar_error("Variable \"%s\" indefinida", lat_obtener_cadena(name));
    }
    return ret;
  }
}

int lat_contexto_contiene(lat_objeto* ns, lat_objeto* name)
{
  if (ns->type != T_INSTANCE) {
    debug("ns->type: %d", ns->type);
    lat_registrar_error("Namespace no es una instancia");
  }
  else {
    hash_map* h = ns->data.instance;
    lat_objeto* ret = (lat_objeto*)get_hash(h, lat_obtener_cadena(name));
    if (ret == NULL) {
      return 0;
    }
    return 1;
  }
}

lat_objeto* lat_crear_objeto(lat_vm* vm)
{
  lat_objeto* ret = (lat_objeto*)lat_asignar_memoria(sizeof(lat_objeto));
  ret->type = T_NULO;
  ret->data_size = 0;
  return ret;
}

lat_objeto* lat_instancia(lat_vm* vm)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_INSTANCE;
  ret->data_size = sizeof(hash_map*);
  ret->data.instance = make_hash_map();
  return ret;
}

lat_objeto* lat_literal_nuevo(lat_vm* vm, const char* p)
{
  lat_objeto* ret = lat_cadena_hash(p, strlen(p));
  return ret;
}

lat_objeto* lat_entero_nuevo(lat_vm* vm, long val)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_INT;
  ret->data_size = sizeof(long);
  ret->data.i = val;
  return ret;
}

lat_objeto* lat_decimal_nuevo(lat_vm* vm, double val)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_DOUBLE;
  ret->data_size = sizeof(double);
  ret->data.d = val;
  return ret;
}

lat_objeto* lat_logico_nuevo(lat_vm* vm, bool val)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_BOOL;
  ret->data_size = sizeof(bool);
  ret->data.b = val;
  return ret;
}

lat_objeto* lat_cadena_nueva(lat_vm* vm, const char* p)
{
  lat_objeto* ret = lat_cadena_hash(p, strlen(p));
  return ret;
}

lat_objeto* lat_lista_nueva(lat_vm* vm, list_node* l)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_LIST;
  ret->data_size = sizeof(list_node*);
  ret->data.list = l;
  return ret;
}

lat_objeto* lat_funcion_nueva(lat_vm* vm)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_FUNC;
  ret->data_size = 0;
  return ret; //We don't do anything here: all bytecode will be added later
}

lat_objeto* lat_cfuncion_nueva(lat_vm* vm)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_CFUNC;
  return ret;
}

lat_objeto* lat_estructura_nueva(lat_vm* vm, void* val)
{
  lat_objeto* ret = lat_crear_objeto(vm);
  ret->type = T_STRUCT;
  ret->data.cstruct = val;
  return ret;
}

void lat_marcar_objeto(lat_objeto* o, int m)
{
  if (o != NULL) {
    o->marked = m;
    switch (o->type) {
    case T_INSTANCE:
      lat_marcar_hash(o->data.instance, m);
      break;
    case T_LIST:
      lat_marcar_lista(o->data.list, m);
      break;
    default:
      break;
    }
  }
}

void lat_marcar_lista(list_node* l, unsigned char m)
{
  if (l != NULL) {
    list_node* c;
    for (c = l->next; c != NULL; c = c->next) {
      if (c->data != NULL) {
        lat_marcar_objeto((lat_objeto*)c->data, m);
      }
    }
  }
}

void lat_marcar_hash(hash_map* h, unsigned char m)
{
  int c = 0;
  list_node* l;
  list_node* cur;
  hash_val* hv;
  for (c = 0; c < 256; ++c) {
    l = h->buckets[c];
    if (l != NULL) {
      for (cur = l->next; cur != NULL; cur = cur->next) {
        if (cur->data != NULL) {
          hv = (hash_val*)cur->data;
          lat_marcar_objeto((lat_objeto*)hv->val, m);
        }
      }
    }
  }
}

void lat_eliminar_objeto(lat_vm* vm, lat_objeto* o)
{
  switch (o->type) {
  case T_NULO:
    return;
    break;
  case T_INSTANCE:
    return;
    break;
  case T_LIST:
    //lat_eliminar_lista(vm, o->data.list);
    break;
  case T_DICT:
    //lat_eliminar_lista(vm, o->data.list);
    break;
  case T_LIT:
  case T_INT:
  case T_DOUBLE:
  case T_BOOL:
    break;
  case T_STR:
    return;
    break;
  case T_FUNC:
  case T_CFUNC:
    return;
  case T_STRUCT:
    return;
    break;
  }
  lat_liberar_memoria(o);
}

void lat_eliminar_lista(lat_vm* vm, list_node* l)
{
  if (l != NULL) {
    list_node* c;
    for (c = l->next; c != NULL; c = c->next) {
      if (c->data != NULL) {
        lat_eliminar_objeto(vm, (lat_objeto*)c->data);
      }
      lat_liberar_memoria(c);
    }
  }
  lat_liberar_memoria(l);
}

void lat_eliminar_hash(lat_vm* vm, hash_map* h)
{
  int c = 0;
  list_node* l;
  list_node* cur;
  hash_val* hv;
  for (c = 0; c < 256; ++c) {
    l = h->buckets[c];
    if (l != NULL) {
      for (cur = l->next; cur != NULL; cur = cur->next) {
        if (cur != NULL) {
          if (cur->data != NULL) {
            hv = (hash_val*)cur->data;
            lat_eliminar_objeto(vm, (lat_objeto*)hv->val);
            lat_liberar_memoria(hv);
          }
          //lat_liberar_memoria(cur);
        }
      }
      lat_liberar_memoria(l);
    }
  }
}

lat_objeto* lat_clonar_objeto(lat_vm* vm, lat_objeto* obj)
{
  lat_objeto* ret;
  switch (obj->type) {
  case T_INSTANCE:
    ret = lat_crear_objeto(vm);
    ret->type = T_INSTANCE;
    ret->data_size = sizeof(hash_map*);
    ret->data.instance = lat_clonar_hash(vm, obj->data.instance);
    //ret->data.instance = obj->data.instance;
    break;
  case T_LIST:
    ret = lat_lista_nueva(vm, lat_clonar_lista(vm, obj->data.list));
    //ret = lat_lista_nueva(vm, obj->data.list);
    break;
  case T_FUNC:
  case T_CFUNC:
    ret = obj;
    break;
  default:
    ret = lat_crear_objeto(vm);
    ret->type = obj->type;
    ret->marked = obj->marked;
    ret->data_size = obj->data_size;
    ret->data = obj->data;
    break;
  }
  return ret;
}

list_node* lat_clonar_lista(lat_vm* vm, list_node* l)
{
  list_node* ret = lat_crear_lista();
  if (l != NULL) {
    list_node* c;
    for (c = l->next; c != NULL; c = c->next) {
      if (c->data != NULL) {
        insert_list(ret, lat_clonar_objeto(vm, (lat_objeto*)c->data));
      }
    }
  }
  return ret;
}

hash_map* lat_clonar_hash(lat_vm* vm, hash_map* h)
{
  int c = 0;
  hash_map* ret = make_hash_map();
  list_node* l;
  for (c = 0; c < 256; ++c) {
    l = h->buckets[c];
    if (l != NULL) {
      ret->buckets[c] = lat_crear_lista();
      if (l != NULL) {
        list_node* cur;
        for (cur = l->next; cur != NULL; cur = cur->next) {
          if (cur->data != NULL) {
            hash_val* hv = (hash_val*)lat_asignar_memoria(sizeof(hash_val));
            //vm->memory_usage += sizeof(hash_val);
            strncpy(hv->key, ((hash_val*)cur->data)->key, 256);
            hv->val = lat_clonar_objeto(vm, (lat_objeto*)((hash_val*)cur->data)->val);
            insert_list(ret->buckets[c], hv);
          }
        }
      }
    }
  }
  return ret;
}

char* lat_obtener_literal(lat_objeto* o)
{
  if (o->type == T_LIT || o->type == T_STR) {
    return o->data.c;
  }
  lat_registrar_error("Object no es un tipo caracter");
}

long lat_obtener_entero(lat_objeto* o)
{
  if (o->type == T_INT) {
    return o->data.i;
  }
  if (o->type == T_DOUBLE) {
    return (long)o->data.d;
  }
  lat_registrar_error("Object no es un tipo entero");
}

double lat_obtener_decimal(lat_objeto* o)
{
  if (o->type == T_DOUBLE) {
    return o->data.d;
  }
  else if (o->type == T_INT) {
    return (double)o->data.i;
  }
  lat_registrar_error("Object no es un tipo numerico");
}

char* lat_obtener_cadena(lat_objeto* o)
{
  if (o->type == T_STR) {
    return o->data.str;
  }
  lat_registrar_error("Object no es un tipo cadena");
}

bool lat_obtener_logico(lat_objeto* o)
{
  if (o->type == T_BOOL) {
    return o->data.b;
  }
  if (o->type == T_INT) {
    return o->data.i;
  }
  lat_registrar_error("Object no es un tipo logico");
}

list_node* lat_obtener_lista(lat_objeto* o)
{
  if (o->type == T_LIST) {
    return o->data.list;
  }
  lat_registrar_error("Object no es un tipo lista");
}

void* lat_obtener_estructura(lat_objeto* o)
{
  if (o->type == T_STRUCT) {
    return o->data.list;
  }
  lat_registrar_error("Object no es un tipo estructura");
}
