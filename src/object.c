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
#include "gc.h"

bool __objeto_a_logico(lat_objeto* o){
    switch (o->tipo)
    {
    case T_NULL:
        return false;
        break;
    case T_BOOL:
        return __logico(o);
        break;
    case T_NUMERIC:
        return __numerico(o) == 0 ? false : true;        
        break;
    case T_STR:
        return strcmp(__cadena(o), "") == 0 
                || strcmp(__cadena(o), "0") == 0 
                || strcmp(__str_minusculas(__cadena(o)), "falso") == 0
                || strcmp(__str_minusculas(__cadena(o)), "false") == 0 ? false : true;        
        break;
    case T_LIST:
        return __lista_longitud(__lista(o)) == 0 ? false : true;
    case T_DICT:
        return __dic_longitud(__dic(o)) == 0 ? false : true;
    default:
        lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  
                "Conversion de tipo de dato incompatible");
        break;
    }
    return false;
}

double __objeto_a_numerico(lat_objeto* o){
    switch (o->tipo)
    {
    case T_NULL:
        return 0;
        break;
    case T_BOOL:
        return __logico(o) == false ? 0 : 1;
        break;
    case T_NUMERIC:
        return __numerico(o);
        break;
    case T_STR:{
            char *ptr;
            double ret;
            ret = strtod(__cadena(o), &ptr);
            if (strcmp(ptr, "") == 0){
                return ret;
            }
        }
        break;
    case T_LIST:
        return __lista_longitud(__lista(o));
        break;
    case T_DICT:
        return __dic_longitud(__dic(o));
        break;
    default:
        lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  
                "Conversion de tipo de dato incompatible");
        break;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  
                "Conversion de tipo de dato incompatible");
    return 0;
}

char* __objeto_a_cadena(lat_objeto* o)
{ 
    if(o->tipo == T_NULL){
        return "nulo";
    }
    if (o->tipo == T_BOOL)
    {
        return __str_logico_a_cadena(__logico(o));
    }
    else if (o->tipo == T_CONTEXT)
    {
        return "contexto";
    }
    else if (o->tipo == T_NUMERIC)
    {        
        return __str_decimal_a_cadena(__numerico(o));
    }
    else if (o->tipo == T_STR)
    {
        return __cadena(o);
    }
    else if (o->tipo == T_FUNC)
    {
        return "funcion";
    }
    else if (o->tipo == T_CFUNC)
    {
        return "cfuncion";
    }
    else if (o->tipo == T_CLASS)
    {
        return "clase";
    }
    if (o->tipo == T_LIST)
    {
        return __lista_a_cadena(o->datos.lista);
    }
    else if (o->tipo == T_DICT)
    {
        return __dic_a_cadena(o->datos.dic);
    }    
    return "";
}

void lat_asignar_contexto_objeto(lat_objeto* ns, lat_objeto* name, lat_objeto* o)
{
    //printf("lat_asignar_contexto_objeto: %s\n", lat_obtener_cadena(name));
    if (ns->tipo != T_CONTEXT)
    {
        lat_fatal_error("Objeto no es un contexto");
    }
    else
    {
        hash_map* h = ns->datos.contexto;        
        if(strlen(__cadena(name)) > MAX_ID_LENGTH){
            lat_fatal_error("Linea %d, %d: Longitud maxima de (%i) excedida para un identificador", name->num_linea, name->num_columna, MAX_ID_LENGTH);
        }
        __dic_asignar(h, __cadena(name), (void*)o);
    }
}

lat_objeto* lat_obtener_contexto_objeto(lat_objeto* ns, lat_objeto* name)
{
    if (ns->tipo != T_CONTEXT)
    {
        lat_fatal_error("Objeto no es un contexto");
    }
    else
    {
        hash_map* h = ns->datos.contexto;
        lat_objeto* ret = (lat_objeto*) __dic_obtener(h, __cadena(name));        
        return ret;
    }
    return NULL;
}

lat_objeto* lat_crear_objeto(lat_mv* vm)
{    
    //printf("lat_crear_objeto\n");
    lat_objeto* ret = (lat_objeto*)__memoria_asignar(sizeof(lat_objeto));
    ret->tipo = T_NULL;
    ret->tamanio = sizeof(lat_objeto);        
    ret->num_ref = 0;
    return ret;
}

lat_objeto* lat_contexto_nuevo(lat_mv* vm)
{
    //printf("lat_contexto_nuevo\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_CONTEXT;
    ret->tamanio += sizeof(hash_map);
    ret->datos.contexto = __dic_crear();    
    vm->memoria_usada += ret->tamanio;
    return ret;
}

lat_objeto* lat_numerico_nuevo(lat_mv* vm, double val)
{
    //printf("lat_decimal_nuevo: %.14g\n", val);
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_NUMERIC;
    ret->tamanio += sizeof(double);
    ret->datos.numerico = val;
    vm->memoria_usada += ret->tamanio;
    return ret;
}

lat_objeto* lat_logico_nuevo(lat_mv* vm, bool val)
{
    //printf("lat_logico_nuevo: %i\n", val);
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_BOOL;
    ret->tamanio += sizeof(bool);
    ret->datos.logico = val;
    vm->memoria_usada += ret->tamanio;
    return ret;
}

lat_objeto* lat_cadena_nueva(lat_mv* vm, const char* p)
{
    //printf("lat_cadena_nueva: %s\n", p);
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_STR;
    ret->tamanio += strlen(p);
    ret->datos.cadena = (char *)p;  
    vm->memoria_usada += ret->tamanio;
    return ret;
}

lat_objeto* lat_lista_nueva(lat_mv* vm, lista* l)
{
    //printf("lat_lista_nueva\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_LIST;
    ret->tamanio += sizeof(lista);
    ret->datos.lista = l;
    vm->memoria_usada += ret->tamanio;
    return ret;
}

lat_objeto* lat_dic_nuevo(lat_mv* vm, hash_map* dic)
{
    //printf("lat_dic_nuevo\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_DICT;
    ret->tamanio += sizeof(hash_map);
    ret->datos.dic = dic;
    vm->memoria_usada += ret->tamanio;
    return ret;
}

lat_objeto* lat_funcion_nueva(lat_mv* vm)
{
    //printf("lat_funcion_nueva\n");
    lat_objeto* ret = lat_crear_objeto(vm);
    ret->tipo = T_FUNC;
    //ret->tamanio = ret->tamanio;
    vm->memoria_usada += ret->tamanio;
    return ret; //We don't do anything here: all bytecode will be added later
}

lat_objeto* lat_cfuncion_nueva(lat_mv* mv)
{
    //printf("lat_cfuncion_nueva\n");
    lat_objeto* ret = lat_crear_objeto(mv);
    ret->tipo = T_CFUNC;
    //ret->tamanio = ret->tamanio;
    mv->memoria_usada += ret->tamanio;
    return ret;
}

void lat_eliminar_objeto(lat_mv* vm, lat_objeto* o)
{
    //printf("eliminando objeto %p\n", &o);
    switch (o->tipo)
    {
    case T_CONTEXT:
        __dic_destruir(o->datos.contexto);
        break;
    case T_LIST:                
        __lista_limpiar_destruir(o->datos.lista);
        break;
    case T_DICT:
        __dic_destruir(o->datos.dic);
        break;
    case T_STR:
        __memoria_liberar(o->datos.cadena);        
        break;
    case T_FUNC: {
        lat_function* fun = (lat_function*)o->datos.fun_usuario;
        __memoria_liberar(fun->bcode); 
        __memoria_liberar(fun);
    }
    break;    
    case T_CFUNC: {
        __memoria_liberar(o->datos.c_funcion);
        __memoria_liberar(o->nombre_cfun);
    }
    break;
    default:
        break;
    }
    __memoria_liberar(o);
}

lat_objeto* lat_clonar_objeto(lat_mv* vm, lat_objeto* obj)
{    
    //printf("lat_clonar_objeto\n");
    lat_objeto* ret = NULL;
    switch (obj->tipo)
    {
    case T_CONTEXT:
        ret = lat_crear_objeto(vm);
        ret->tipo = T_CONTEXT;
        ret->tamanio = sizeof(hash_map*);
        ret->datos.contexto = __dic_clonar(obj->datos.contexto);
        break;
    case T_LIST:
        ret = lat_lista_nueva(vm, lat_clonar_lista(vm, obj->datos.lista));        
        break;    
    case T_FUNC:
        ret = lat_crear_objeto(vm);
        ret->tipo = obj->tipo;
        ret->datos.fun_usuario = obj->datos.fun_usuario;
        ret->num_params = obj->num_params;
        break;
    case T_CFUNC:
        ret = lat_crear_objeto(vm);
        ret->tipo = obj->tipo;
        ret->datos.c_funcion = obj->datos.c_funcion;
        ret->num_params = obj->num_params;
        break;
    case T_NUMERIC:        
        ret = lat_crear_objeto(vm);
        ret->tipo = obj->tipo;
        ret->datos.numerico = obj->datos.numerico;        
        ret->tamanio = obj->tamanio;
        ret->num_linea = obj->num_linea;
        ret->num_columna = obj->num_columna;
        vm->memoria_usada += obj->tamanio;
    break;
    default:        
        ret = lat_crear_objeto(vm);
        ret->tipo = obj->tipo;
        ret->marca = obj->marca;
        ret->tamanio = obj->tamanio;
        ret->datos = obj->datos;
        ret->num_params = obj->num_params;
        ret->num_linea = obj->num_linea;
        ret->num_columna = obj->num_columna;
        break;
    }
    return ret;
}

lista* lat_clonar_lista(lat_mv* vm, lista* list)
{
    lista* ret = __lista_crear();
    LIST_FOREACH(list, primero, siguiente, cur) {
        __lista_apilar(ret, cur->valor);
    }    
    return ret;
}

bool __logico(lat_objeto* o)
{
    if (o->tipo == T_BOOL)
    {
        return o->datos.logico;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser un valor logico (verdadero o falso)");
    return false;
}

double __numerico(lat_objeto* o)
{
    if (o->tipo == T_NUMERIC)
    {
        return o->datos.numerico;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser un decimal");
    return 0;
}

char* __cadena(lat_objeto* o)
{
    if (o->tipo == T_STR)
    {
        return o->datos.cadena;
    }
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser una cadena");
    return 0;
}

lista* __lista(lat_objeto* o)
{
    if (o->tipo == T_LIST)
    {
        return o->datos.lista;
    }
    /*else{
        o->tipo = T_LIST;
        o->datos.lista = __lista_crear();
        return o->datos.lista;
    }*/
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser una lista");
    return NULL;
}

hash_map* __dic(lat_objeto* o)
{
    if (o->tipo == T_DICT)
    {
        return o->datos.dic;
    }/*
    else{
        o->tipo = T_DICT;
        o->datos.dic = __dic_crear();
        return o->datos.dic;
    }*/
    lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "El parametro debe de ser un diccionario");
    return NULL;
}

bool __es_igual(lat_objeto* lhs, lat_objeto* rhs){
    if(lhs->tipo != rhs->tipo){
        return false;
    }    
    if(lhs->tipo == T_NUMERIC){
        return __numerico(lhs) == __numerico(rhs);
    }    
    if(lhs->tipo == T_STR){
        return strcmp(__cadena(lhs), __cadena(rhs)) == 0 ? true : false;
    }
    if(lhs->tipo == T_LIST){
        return __lista_comparar(__lista(lhs), __lista(rhs)) == 0 ? true : false;
    }
    return false;
}


int __objeto_comparar(lat_objeto* lhs, lat_objeto* rhs){
    int res = 1;
    if(lhs->tipo != rhs->tipo){
        res = strcmp(__objeto_a_cadena(lhs), __objeto_a_cadena(rhs));
        goto RESPUESTA;
    }
    if(lhs->tipo == T_BOOL){
        res = __logico(lhs) - __logico(rhs);
        goto RESPUESTA;
    }
    if(lhs->tipo == T_NUMERIC){
        res = __numerico(lhs) - __numerico(rhs);
        goto RESPUESTA;
    }
    if(lhs->tipo == T_STR){
        res = strcmp(__cadena(lhs), __cadena(rhs));
        goto RESPUESTA;
    }
    if(lhs->tipo == T_LIST){
        res = __lista_comparar(__lista(lhs), __lista(rhs));
        goto RESPUESTA;
    }   
RESPUESTA:    
    if(res < 0){
        return -1;
    }
    if(res > 0){
        return 1;
    }
    return res;
}