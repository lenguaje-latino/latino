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
#include <string.h>

#include "latino.h"
#include "libstring.h"
#include "liblist.h"
#include "libmem.h"
#include "libdict.h"


char* __objeto_a_cadena(lat_objeto* in)
{    
    if (in->type == T_BOOL)
    {
        return __str_logico_a_cadena(lat_obtener_logico(in));
    }
    else if (in->type == T_INSTANCE)
    {
        return "objeto";
    }
    else if (in->type == T_DOUBLE)
    {
        return __str_decimal_a_cadena(lat_obtener_decimal(in));
    }
    else if (in->type == T_STR)
    {
        return lat_obtener_cadena(in);
    }
    else if (in->type == T_FUNC)
    {
        return "funcion";
    }
    else if (in->type == T_CFUNC)
    {
        return "cfuncion";
    }
    else if (in->type == T_CLASS)
    {
        return "clase";
    }
    if (in->type == T_LIST)
    {
        return __lista_a_cadena(in->data.lista);
    }
    else if (in->type == T_DICT)
    {
        //__imprimir_diccionario(vm, in->data.dict);
    }    
    return "";
}

void lat_asignar_contexto_objeto(lat_objeto* ns, lat_objeto* name, lat_objeto* o)
{
    //printf("lat_asignar_contexto_objeto\n");
    if (ns->type != T_INSTANCE)
    {
        lat_fatal_error("Objeto no es una instancia");
    }
    else
    {
        hash_map* h = ns->data.nombre;
        __dic_asignar(h, lat_obtener_cadena(name), (void*)o);
    }
}

lat_objeto* lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name)
{
    if (ns->type != T_INSTANCE)
    {
        lat_fatal_error("Objeto no es un nombre");
    }
    else
    {
        hash_map* h = ns->data.nombre;
        lat_objeto* ret = (lat_objeto*) __dic_obtener(h, lat_obtener_cadena(name));
        if (ret == NULL)
        {
            lat_fatal_error("Linea %d, %d: Variable \"%s\" indefinida", name->num_linea, name->num_columna, lat_obtener_cadena(name));
        }
        return ret;
    }
    return NULL;
}

lat_objeto* lat_crear_objeto(lat_vm* vm)
{
    lat_objeto* ret = (lat_objeto*)__memoria_asignar(sizeof(lat_objeto));
    ret->type = T_INSTANCE;
    ret->data_size = 0;
    return ret;
}

lat_objeto* lat_instancia(lat_vm* vm)
{
    //printf("instancia nueva\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->type = T_INSTANCE;
    ret->data_size = sizeof(hash_map*);
    ret->data.nombre = __dic_crear();
    return ret;
}

lat_objeto* lat_decimal_nuevo(lat_vm* vm, double val)
{
    //printf("decimal nuevo: %.14g\n", val);
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->type = T_DOUBLE;
    ret->data_size = sizeof(double);
    ret->data.d = val;
    return ret;
}

lat_objeto* lat_logico_nuevo(lat_vm* vm, bool val)
{
    //printf("logico nuevo: %i\n", val);
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->type = T_BOOL;
    ret->data_size = sizeof(bool);
    ret->data.b = val;
    return ret;
}

lat_objeto* lat_cadena_nueva(lat_vm* vm, const char* p)
{
    //printf("cadena nueva: %s\n", p);
    lat_objeto* str = (lat_objeto*)__memoria_asignar(sizeof(lat_objeto));
    str->type = T_STR;
    str->data_size = strlen(p);
    str->data.str = (char *)p;    
    return str;
}

lat_objeto* lat_lista_nueva(lat_vm* vm, lista* l)
{
    //printf("lista nueva\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->type = T_LIST;
    ret->data_size = sizeof(lista);
    ret->data.lista = l;
    return ret;
}

lat_objeto* lat_funcion_nueva(lat_vm* vm)
{
    //printf("funcion nueva\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->type = T_FUNC;
    ret->data_size = 0;
    return ret; //We don't do anything here: all bytecode will be added later
}

lat_objeto* lat_cfuncion_nueva(lat_vm* vm)
{
    //printf("cfuncion nueva\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->type = T_CFUNC;
    return ret;
}

void lat_eliminar_objeto(lat_vm* vm, lat_objeto* o)
{
    switch (o->type)
    {
    case T_INSTANCE:        
        //TODO:Eliminar objeto
        break;
    case T_LIST:        
        //TODO:Eliminar objeto lista
        break;
    case T_DICT:        
        //TODO:Eliminar objeto dic
        break;
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
    __memoria_liberar(o);
}

lat_objeto* lat_clonar_objeto(lat_vm* vm, lat_objeto* obj)
{
    //printf("lat_clonar_objeto\n");
    lat_objeto* ret;
    switch (obj->type)
    {
    case T_INSTANCE:
        ret = lat_crear_objeto(vm);
        ret->type = T_INSTANCE;
        ret->data_size = sizeof(hash_map*);
        ret->data.nombre = __dic_clonar(obj->data.nombre);
        break;
    case T_LIST:
        ret = lat_lista_nueva(vm, lat_clonar_lista(vm, obj->data.lista));        
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
        ret->num_param = obj->num_param;
        ret->num_linea = obj->num_linea;
        ret->num_columna = obj->num_columna;
        break;
    }
    return ret;
}

lista* lat_clonar_lista(lat_vm* vm, lista* list)
{
    lista* ret = __lista_crear();
    LIST_FOREACH(list, primero, siguiente, cur) {
        __lista_apilar(ret, cur->valor);
    }    
    return ret;
}

double lat_obtener_decimal(lat_objeto* o)
{
    if (o->type == T_DOUBLE)
    {
        return o->data.d;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser un decimal");
    return 0;
}

char* lat_obtener_cadena(lat_objeto* o)
{
    if (o->type == T_STR)
    {
        return o->data.str;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser una cadena");
    return 0;
}

bool lat_obtener_logico(lat_objeto* o)
{
    if (o->type == T_BOOL)
    {
        return o->data.b;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser un valor logico (verdadero o falso)");
    return false;
}

lista* lat_obtener_lista(lat_objeto* o)
{
    if (o->type == T_LIST)
    {
        return o->data.lista;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser una lista");
    return NULL;
}
