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
#include "libstring.h"
#include "liblist.h"
#include "libmem.h"
#include "libdict.h"

void lat_asignar_contexto_objeto(lat_objeto* ns, lat_objeto* name, lat_objeto* o)
{
    if (ns->type != T_INSTANCE)
    {
        debug("ns->type: %d", ns->type);
        lat_error("Namespace no es una instancia");
    }
    else
    {
        hash_map* h = ns->data.nombre;
        set_hash(h, lat_obtener_cadena(name), (void*)o);
    }
}

lat_objeto* lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name)
{
    if (ns->type != T_INSTANCE)
    {
        debug("ns->type: %d", ns->type);
        lat_error("Namespace is not an nombre");
    }
    else
    {
        hash_map* h = ns->data.nombre;
        lat_objeto* ret = (lat_objeto*)get_hash(h, lat_obtener_cadena(name));
        if (ret == NULL)
        {
            lat_error("Variable \"%s\" indefinida", lat_obtener_cadena(name));
        }
        return ret;
    }
    return NULL;
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
    ret->data.nombre = make_hash_map();
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
    ret->data.lista = l;
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

void lat_eliminar_objeto(lat_vm* vm, lat_objeto* o)
{
    switch (o->type)
    {
    case T_NULO:
        return;
        break;
    case T_INSTANCE:
        return;
        break;
    case T_LIST:
        //lat_eliminar_lista(vm, o->data.lista);
        break;
    case T_DICT:
        //lat_eliminar_lista(vm, o->data.lista);
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
    case T_CLASS:
        return;
        break;
    }
    lat_liberar_memoria(o);
}

lat_objeto* lat_clonar_objeto(lat_vm* vm, lat_objeto* obj)
{
    lat_objeto* ret;
    switch (obj->type)
    {
    case T_INSTANCE:
        ret = lat_crear_objeto(vm);
        ret->type = T_INSTANCE;
        ret->data_size = sizeof(hash_map*);
        //ret->data.nombre = lat_clonar_hash(vm, obj->data.nombre);
        ret->data.nombre = copy_hash(obj->data.nombre);
        //ret->data.nombre = obj->data.nombre;
        break;
    case T_LIST:
        ret = lat_lista_nueva(vm, lat_clonar_lista(vm, obj->data.lista));
        //ret = lat_lista_nueva(vm, obj->data.lista);
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
    if (l != NULL)
    {
        list_node* c;
        for (c = l; c->next != NULL; c = c->next)
        {
            if (c->data != NULL)
            {
                insert_list(ret, lat_clonar_objeto(vm, (lat_objeto*)c->data));
            }
        }
    }
    return ret;
}

char* lat_obtener_literal(lat_objeto* o)
{
    if (o->type == T_LIT || o->type == T_STR)
    {
        return o->data.c;
    }
    lat_error("Objeto no es un tipo caracter");
    return 0;
}

long lat_obtener_entero(lat_objeto* o)
{
    if (o->type == T_INT)
    {
        return o->data.i;
    }
    if (o->type == T_DOUBLE)
    {
        return (long)o->data.d;
    }
    lat_error("Objeto no es un tipo entero");
    return 0;
}

double lat_obtener_decimal(lat_objeto* o)
{
    if (o->type == T_DOUBLE)
    {
        return o->data.d;
    }
    else if (o->type == T_INT)
    {
        return (double)o->data.i;
    }
    lat_error("Objeto no es un tipo numerico");
    return 0;
}

char* lat_obtener_cadena(lat_objeto* o)
{
    if (o->type == T_STR)
    {
        return o->data.str;
    }
    lat_error("Objeto no es un tipo cadena");
    return 0;
}

bool lat_obtener_logico(lat_objeto* o)
{
    if (o->type == T_BOOL)
    {
        return o->data.b;
    }
    lat_error("Objeto no es un tipo logico");
    return false;
}

list_node* lat_obtener_lista(lat_objeto* o)
{
    if (o->type == T_LIST)
    {
        return o->data.lista;
    }
    lat_error("Objeto no es un tipo lista");
    return NULL;
}
