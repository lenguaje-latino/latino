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
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "compat.h"
//#include "latino.h"
#include "vm.h"
#include "libmem.h"
#include "libmath.h"
#include "libstring.h"
#include "libio.h"
#include "liblist.h"
#include "libnet.h"
#include "parse.h"
#include "gc.h"

static const char *const bycode_nombre[] = {
    "NOP",
    "HALT",
    "UNARY_MINUS",
    "BINARY_ADD",
    "BINARY_SUB",
    "BINARY_MUL",
    "BINARY_DIV",
    "BINARY_MOD",
    "OP_GT",
    "OP_GE",
    "OP_LT",
    "OP_LE",
    "OP_EQ",
    "OP_NEQ",
    "OP_AND",
    "OP_OR",
    "OP_NOT",
    "OP_INC",
    "OP_DEC",
    "CONCAT",
    "LOAD_CONST",
    "LOAD_NAME",
    "STORE_NAME",
    "JUMP_ABSOLUTE",
    "POP_JUMP_IF_FALSE",
    "POP_JUMP_IF_TRUE",
    "SETUP_LOOP",
    "POP_BLOCK",
    "CALL_FUNCTION",
    "RETURN_VALUE",
    "MAKE_FUNCTION",    
    "INC",    
    "DEC", 
    "LOAD_ATTR",
};


static void __registrar_cfuncion(lat_mv* vm, char *palabra_reservada, void (*function)(lat_mv* vm), int num_params)
{
    lat_objeto *ctx = lat_obtener_contexto(vm);
    lat_objeto *nombre = lat_cadena_nueva(vm, palabra_reservada);
    lat_objeto *cfun = lat_definir_cfuncion(vm, function);
    cfun->nombre_cfun = palabra_reservada;
    cfun->num_params = num_params;
    lat_asignar_contexto_objeto(ctx, nombre, cfun);    
    //se agregan funciones para que se eliminen con el Colector de basura
    //__colector_agregar(vm, nombre);
    //__colector_agregar(vm, cfun);    
}

const char* __obtener_bytecode_nombre(int inst){
    return bycode_nombre[inst];
}

lat_objeto* __lista_obtener_elemento(lista* list, int pos)
{
    if (pos < 0 || pos >= __lista_longitud(list))
    {
        lat_fatal_error("Indice fuera de rango");
    }
    int i = 0;
    LIST_FOREACH(list, primero, siguiente, cur) {
        if (i == pos)
        {
            return (lat_objeto *)cur->valor;
        }
        i++;
    }
    return NULL;
}

lista_nodo* __lista_obtener_nodo(lista* list, int pos)
{
    if (pos < 0 || pos >= __lista_longitud(list))
    {
        lat_fatal_error("Indice fuera de rango");
    }
    int i = 0;
    LIST_FOREACH(list, primero, siguiente, cur) {
        if (i == pos)
        {
            return cur;
        }
        i++;
    }
    return NULL;
}

lat_mv* lat_mv_crear()
{
    //printf("creando mv\n");
    lat_mv* mv = (lat_mv*)__memoria_asignar(sizeof(lat_mv));
    mv->memoria_usada = sizeof(lat_mv);
    mv->gc_objetos = lat_lista_nueva(mv, __lista_crear());    
    mv->pila = lat_lista_nueva(mv, __lista_crear());
    mv->objeto_verdadero = lat_logico_nuevo(mv, true);
    mv->objeto_falso = lat_logico_nuevo(mv, false);
    memset(mv->contexto_pila, 0, 256);
    mv->contexto_pila[0] = lat_contexto_nuevo(mv);
    mv->apuntador_ctx = 0;    

    /**
     * 10 Operadores
     * 20 funciones matematicas
     * 30 funciones para cadenas (string)
     * 40 entrada y salida
     * 50 conversion de tipos de dato
     * 60
     * 70
     * 99 otras funciones // a crear una categoria para ellas
     *
     */

    /*10 Operadores */

    /*20 funciones matematicas */
    /*__registrar_cfuncion(vm, "arco_coseno", lat_arco_coseno);
    __registrar_cfuncion(vm, "arco_seno", lat_arco_seno);
    __registrar_cfuncion(vm, "arco_tangente", lat_arco_tangente);
    __registrar_cfuncion(vm, "arco_tangente2", lat_arco_tangente2);
    __registrar_cfuncion(vm, "coseno", lat_coseno);
    __registrar_cfuncion(vm, "coseno_hiperbolico", lat_coseno_hiperbolico);
    __registrar_cfuncion(vm, "seno", lat_seno);
    __registrar_cfuncion(vm, "seno_hiperbolico", lat_seno_hiperbolico);
    __registrar_cfuncion(vm, "tangente", lat_tangente);
    __registrar_cfuncion(vm, "tangente_hiperbolica", lat_tangente_hiperbolica);
    __registrar_cfuncion(vm, "exponente", lat_exponente);
    __registrar_cfuncion(vm, "logaritmo_natural", lat_logaritmo_natural);
    __registrar_cfuncion(vm, "logaritmo_base10", lat_logaritmo_base10);
    __registrar_cfuncion(vm, "potencia", lat_potencia);
    __registrar_cfuncion(vm, "raiz_cuadrada", lat_raiz_cuadrada);
    __registrar_cfuncion(vm, "redondear_arriba", lat_redondear_arriba);
    __registrar_cfuncion(vm, "valor_absoluto", lat_valor_absoluto);
    __registrar_cfuncion(vm, "redondear_abajo", lat_redondear_abajo);
    __registrar_cfuncion(vm, "ejecutar_archivo", lat_ejecutar_archivo);
    __registrar_cfuncion(vm, "modulo", lat_modulo_decimal);*/

    /*30 funciones para cadenas (string)*/
    /*__registrar_cfuncion(vm, "comparar", lat_comparar);
    __registrar_cfuncion(vm, "concatenar", lat_concatenar);
    __registrar_cfuncion(vm, ".", lat_concatenar);
    __registrar_cfuncion(vm, "contiene", lat_contiene);
    __registrar_cfuncion(vm, "termina_con", lat_termina_con);
    __registrar_cfuncion(vm, "es_igual", lat_es_igual);
    __registrar_cfuncion(vm, "indice", lat_indice);
    __registrar_cfuncion(vm, "insertar", lat_insertar);
    __registrar_cfuncion(vm, "ultimo_indice", lat_ultimo_indice);
    __registrar_cfuncion(vm, "rellenar_izquierda", lat_rellenar_izquierda);
    __registrar_cfuncion(vm, "rellenar_derecha", lat_rellenar_derecha);
    __registrar_cfuncion(vm, "eliminar", lat_eliminar);
    __registrar_cfuncion(vm, "esta_vacia", lat_esta_vacia);
    __registrar_cfuncion(vm, "longitud", lat_longitud);
    __registrar_cfuncion(vm, "reemplazar", lat_reemplazar);
    __registrar_cfuncion(vm, "empieza_con", lat_empieza_con);
    __registrar_cfuncion(vm, "subcadena", lat_subcadena);
    __registrar_cfuncion(vm, "minusculas", lat_minusculas);
    __registrar_cfuncion(vm, "mayusculas", lat_mayusculas);
    __registrar_cfuncion(vm, "quitar_espacios", lat_quitar_espacios);
    __registrar_cfuncion(vm, "es_numero", lat_es_numero);
    __registrar_cfuncion(vm, "es_alfanumerico", lat_es_alfanumerico);
    __registrar_cfuncion(vm, "ejecutar", lat_ejecutar);
    __registrar_cfuncion(vm, "ejecutar_archivo", lat_ejecutar_archivo);*/

    /*40 entrada / salida */   
    
    __registrar_cfuncion(mv, "imprimir", lat_imprimir, 1);
    __registrar_cfuncion(mv, "escribir", lat_imprimir, 1);
        
    /*__registrar_cfuncion(vm, "leer", lat_leer);
    __registrar_cfuncion(vm, "leer_archivo", lat_leer_archivo);
    __registrar_cfuncion(vm, "salir", lat_salir);*/

    /*50 conversion de tipos de dato*/
    /*__registrar_cfuncion(vm, "tipo", lat_tipo);
    __registrar_cfuncion(vm, "logico", lat_logico);
    __registrar_cfuncion(vm, "decimal", lat_decimal);
    __registrar_cfuncion(vm, "cadena", lat_cadena);*/

    /*60 funciones para listas*/
    //__registrar_cfuncion(vm, "agregar", lat_agregar);

    /*99 otras funciones */
    /*__registrar_cfuncion(vm, "cadena", lat_cadena);
    __registrar_cfuncion(vm, "maximo", lat_maximo);
    __registrar_cfuncion(vm, "minimo", lat_minimo);
    __registrar_cfuncion(vm, "sistema", lat_sistema);*/
#ifdef __linux__
    //__registrar_cfuncion(vm, "peticion", lat_peticion);
#endif
    return mv;
}

void lat_destruir_mv(lat_mv* mv){
    lat_eliminar_objeto(mv, mv->gc_objetos);
    lat_eliminar_objeto(mv, mv->pila);
    lat_eliminar_objeto(mv, mv->objeto_verdadero);
    lat_eliminar_objeto(mv, mv->objeto_falso); 
    /*lat_objeto* ctx = lat_obtener_contexto(mv);
    lat_eliminar_objeto(mv, ctx);
     mv->contexto_pila[0]
     */
    if(mv->contexto_pila[0] != NULL){
        lat_eliminar_objeto(mv, mv->contexto_pila[0]);        
    }
    __memoria_liberar(mv);
}

void lat_apilar(lat_mv* vm, lat_objeto* o)
{
    __lista_apilar(lat_obtener_lista(vm->pila), (void*)o);
}

lat_objeto* lat_desapilar(lat_mv* vm)
{
    return (lat_objeto*)__lista_desapilar(lat_obtener_lista(vm->pila));
}

lat_objeto* lat_tope(lat_mv* vm)
{
    return (lat_objeto*)vm->pila->datos.lista->ultimo->valor;
}

void lat_apilar_contexto(lat_mv* vm)
{
    //printf("apilando contexto...\n");
    if (vm->apuntador_ctx >= MAX_STACK_SIZE)
    {
        lat_fatal_error("Namespace desborde de la pila");
    }
    vm->contexto_pila[vm->apuntador_ctx + 1] = lat_clonar_objeto(vm, vm->contexto_pila[vm->apuntador_ctx]);
    vm->apuntador_ctx++;
}

void lat_desapilar_contexto(lat_mv* vm)
{
    //printf("...desapilando contexto\n");
    if (vm->apuntador_ctx == 0)
    {
        lat_fatal_error("Namespace pila vacia");
    }
    lat_eliminar_objeto(vm, vm->contexto_pila[vm->apuntador_ctx--]);
}

lat_objeto* lat_obtener_contexto(lat_mv* vm)
{
    return vm->contexto_pila[vm->apuntador_ctx];
}

lat_objeto* lat_definir_funcion(lat_mv* vm, lat_bytecode* inslist)
{
    lat_objeto* ret = lat_funcion_nueva(vm);
    lat_function* fval = (lat_function*)__memoria_asignar(sizeof(lat_function));
    fval->bcode = inslist;
    ret->datos.fun_usuario = fval;
    return ret;
}

lat_objeto* lat_definir_cfuncion(lat_mv* vm, void (*function)(lat_mv* vm))
{
    lat_objeto* ret = lat_cfuncion_nueva(vm);
    ret->datos.c_funcion = function;
    return ret;
}

void __imprimir_objeto(lat_mv* vm, lat_objeto* in)
{    
    char *tmp1 = NULL;
    if(in->tipo != T_STR){
        tmp1 = __objeto_a_cadena(in);
        fprintf(stdout, "%s", tmp1);
    }else{
        fprintf(stdout, "%s", lat_obtener_cadena(in));
    }    
    __memoria_liberar(tmp1);
}

void lat_imprimir(lat_mv* vm)
{
    lat_objeto* in = lat_desapilar(vm);
    __imprimir_objeto(vm, in);
    printf("\n");    
}

void __imprimir_lista(lat_mv* vm, lista* l)
{
    fprintf(stdout, "%s", __lista_a_cadena(l));
}

void lat_menos_unario(lat_mv* vm)
{
    lat_objeto* o = lat_tope(vm);
    o->datos.numerico = (-1) * lat_obtener_decimal(o);
}

void lat_sumar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = lat_decimal_nuevo(vm, lat_obtener_decimal(a) + lat_obtener_decimal(b));
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_restar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = lat_decimal_nuevo(vm, lat_obtener_decimal(a) - lat_obtener_decimal(b));
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_multiplicar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = lat_decimal_nuevo(vm, lat_obtener_decimal(a) * lat_obtener_decimal(b));
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_dividir(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(lat_obtener_decimal(b) == 0){
        lat_fatal_error("Linea %d, %d: %s", b->num_linea, b->num_columna,  "Division entre cero");
    }
    lat_objeto* r = lat_decimal_nuevo(vm, (lat_obtener_decimal(a) / lat_obtener_decimal(b)));
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_modulo_decimal(lat_mv *vm)
{
    lat_objeto *b = lat_desapilar(vm);
    lat_objeto *a = lat_desapilar(vm);
    lat_objeto* r = lat_decimal_nuevo(vm, fmod(lat_obtener_decimal(a), lat_obtener_decimal(b)));
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_diferente(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = NULL;
    if (a->tipo == T_BOOL && b->tipo == T_BOOL)
    {
        r = lat_obtener_logico(a) != lat_obtener_logico(b) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (b->tipo == T_NUMERIC && b->tipo == T_NUMERIC)
    {
        r = (lat_obtener_decimal(a) != lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_STR && b->tipo == T_STR)
    {
        r = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) != 0 ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    lat_apilar(vm, vm->objeto_falso);
}

void lat_igualdad(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = NULL;
    if (a->tipo == T_BOOL && b->tipo == T_BOOL)
    {
        r = lat_obtener_logico(a) == lat_obtener_logico(b) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_NUMERIC && b->tipo == T_NUMERIC)
    {
        r = (lat_obtener_decimal(a) == lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_STR && b->tipo == T_STR)
    {
        r = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) == 0 ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    r= vm->objeto_falso;
    lat_apilar(vm, r);
}

void lat_menor_que(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = NULL;
    if (b->tipo == T_NUMERIC && b->tipo == T_NUMERIC)
    {
        r = (lat_obtener_decimal(a) < lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_STR && b->tipo == T_STR)
    {
        r = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) < 0 ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \"<\" en tipos invalidos");
}

void lat_menor_igual(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = NULL;
    if (b->tipo == T_NUMERIC && b->tipo == T_NUMERIC)
    {
        r = (lat_obtener_decimal(a) <= lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_STR && b->tipo == T_STR)
    {
        r = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) <= 0 ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \"<=\" en tipos invalidos");
}

void lat_mayor_que(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = NULL;
    if (b->tipo == T_NUMERIC && b->tipo == T_NUMERIC)
    {
        r = (lat_obtener_decimal(a) > lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_STR && b->tipo == T_STR)
    {
        r = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) > 0 ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \">\" en tipos invalidos");
}

void lat_mayor_igual(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = NULL;
    if (b->tipo == T_NUMERIC && b->tipo == T_NUMERIC)
    {
        r = (lat_obtener_decimal(a) >= lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    if (a->tipo == T_STR && b->tipo == T_STR)
    {
        r = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) >= 0 ? vm->objeto_verdadero : vm->objeto_falso;
        lat_apilar(vm, r);
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \">=\" en tipos invalidos");
}

void lat_y(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r =  (lat_obtener_logico(a) && lat_obtener_logico(b)) == true ? vm->objeto_verdadero : vm->objeto_falso;
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_o(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* r = (lat_obtener_logico(a) || lat_obtener_logico(b)) == true ? vm->objeto_verdadero : vm->objeto_falso;
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_no(lat_mv* vm)
{
    lat_objeto* o = lat_desapilar(vm);
    lat_objeto* r = (lat_obtener_logico(o) == false) ? vm->objeto_verdadero : vm->objeto_falso;
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

lat_bytecode lat_bc(int i, int a, int b, void* meta)
{
    lat_bytecode ret;
    ret.ins = i;
    ret.a = a;
    ret.b = b;
    ret.meta = meta;
    return ret;
}

void lat_llamar_funcion(lat_mv* vm, lat_objeto* func)
{
    if (func->tipo == T_FUNC)
    {
#if DEPURAR_MV
        printf("\n.::Ejecutando funcion::.\n");
#endif
        lat_asignar_contexto_objeto(lat_obtener_contexto(vm), lat_cadena_nueva(vm, "lat_main"), func);
        lat_bytecode* inslist = ((lat_function*)func->datos.fun_usuario)->bcode;
        lat_bytecode cur;
        int pos;
        for (pos = 0, cur = inslist[pos]; cur.ins != HALT; cur = inslist[++pos])
        {
#if DEPURAR_MV
            printf("%i\t", pos);
            printf("%s\t", __obtener_bytecode_nombre(cur.ins));            
#endif
            switch (cur.ins)
            {
            case HALT:
                return;
                break;
            case NOP:
                break;
            case UNARY_MINUS:{
                lat_menos_unario(vm);
            }
            break;
            case INC:{
                lat_objeto *name =  (lat_objeto*)cur.meta;
                lat_objeto *ctx =  lat_obtener_contexto(vm);
                lat_objeto *val = lat_obtener_contexto_objeto(ctx, name);
                lat_objeto *tmp = lat_clonar_objeto(vm, val);
                tmp->datos.numerico++;
                lat_asignar_contexto_objeto(ctx, name, tmp);
                __colector_agregar(vm, tmp);
            }
            break;
            case DEC:{
                lat_objeto *name =  (lat_objeto*)cur.meta;
                lat_objeto *ctx =  lat_obtener_contexto(vm);
                lat_objeto *val = lat_obtener_contexto_objeto(ctx, name);
                lat_objeto *tmp = lat_clonar_objeto(vm, val);
                tmp->datos.numerico--;
                lat_asignar_contexto_objeto(ctx, name, tmp);
                __colector_agregar(vm, tmp);
            }
            break;
            case BINARY_ADD:{
                lat_sumar(vm);
            }
            break;
            case BINARY_SUB:{
                lat_restar(vm);
            }
            break;
            case BINARY_MUL:{
                lat_multiplicar(vm);
            }
            break;
            case BINARY_DIV:{
                lat_multiplicar(vm);
            }
            break;
            case BINARY_MOD:{
                lat_modulo_decimal(vm);
            }
            break;
            case OP_GT:{
                lat_mayor_que(vm);
            }
            break;
            case OP_GE:{
                lat_mayor_igual(vm);
            }
            break;
            case OP_LT:{
                lat_menor_que(vm);
            }
            break;
            case OP_LE:{
                lat_menor_igual(vm);
            }
            break;
            case OP_EQ:{
                lat_igualdad(vm);
            }
            break;
            case OP_NEQ:{
                lat_diferente(vm);
            }
            break;
            case OP_AND:{
                lat_y(vm);
            }
            break;
            case OP_OR:{
                lat_o(vm);
            }
            break;
            case OP_NOT:{
                lat_no(vm);
            }
            break;
            case CONCAT:{
                lat_concatenar(vm);
            }
            break;
            case LOAD_CONST:
            {                
                lat_objeto *o = (lat_objeto*)cur.meta;
#if DEPURAR_MV
                __imprimir_objeto(vm, o);
                printf("\t");
#endif
                lat_apilar(vm, o);
            }
                break;
            case STORE_NAME:{
                lat_objeto *val = lat_desapilar(vm);
                lat_objeto *name =  (lat_objeto*)cur.meta;
                lat_objeto *ctx =  lat_obtener_contexto(vm);
#if DEPURAR_MV
                __imprimir_objeto(vm, name);
                printf("\t");
#endif
                if(name->es_constante){
                    lat_objeto *tmp = lat_obtener_contexto_objeto(ctx, name);
                    if(tmp != NULL){
                        lat_fatal_error("Linea %d, %d: Intento de reasignar valor a constante '%s'", name->num_linea, name->num_columna, lat_obtener_cadena(name));
                    }
                }
                //asigna el numero de parametros
                if(name->nombre_cfun){
                    val->num_params = name->num_params;
                    val->nombre_cfun = name->nombre_cfun;                    
                }
                lat_asignar_contexto_objeto(ctx, name, val);
            }
                break;
            case LOAD_NAME:{
                lat_objeto *name =  (lat_objeto*)cur.meta;
                lat_objeto *ctx =  lat_obtener_contexto(vm);
#if DEPURAR_MV
                __imprimir_objeto(vm, name);
                printf("\t");
#endif
                lat_objeto *val = lat_obtener_contexto_objeto(ctx, name);
                if(val == NULL){
                    lat_fatal_error("Linea %d, %d: Variable \"%s\" indefinida", name->num_linea, name->num_columna, lat_obtener_cadena(name));                        
                }
                val->num_linea = name->num_linea;
                val->num_columna = name->num_columna;
                lat_apilar(vm, val);
            }
                break;
            case POP_JUMP_IF_FALSE:{
                lat_objeto *o = lat_desapilar(vm);
                if(lat_obtener_logico(o) == false){
                    pos = cur.a;
                }
            }
                break;
                case POP_JUMP_IF_TRUE:{
                lat_objeto *o = lat_desapilar(vm);
                if(lat_obtener_logico(o) == true){
                    pos = cur.a;
                }
            }
                break;
            case JUMP_ABSOLUTE:
                pos = cur.a;
                break;
            case CALL_FUNCTION: {          
#if DEPURAR_MV
                printf("\n=> ");
#endif
                int num_args = cur.a;
                lat_objeto *fun = lat_desapilar(vm);                
                if(num_args != fun->num_params ){
                    lat_fatal_error("Linea %d, %d: Numero invalido de argumentos en funcion '%s'. se esperaban %i valores.\n", fun->num_linea, fun->num_columna, fun->nombre_cfun, fun->num_params);
                }                
                lat_apilar_contexto(vm);
                vm->num_callf++;                
                if(vm->num_callf >= MAX_CALL_FUNCTION){
                    lat_fatal_error("Linea %d, %d: Numero maximo de llamadas a funciones recursivas excedido en '%s'\n", fun->num_linea, fun->num_columna, fun->nombre_cfun);
                }
                lat_llamar_funcion(vm, fun);
                vm->num_callf--;
                lat_desapilar_contexto(vm);
            }
            break;
            case RETURN_VALUE: {
                return;                
            }
            break;
            case MAKE_FUNCTION: {
                lat_objeto *fun = lat_definir_funcion(vm, (lat_bytecode*)cur.meta);
                lat_apilar(vm, fun);
            }
            break; 
            case SETUP_LOOP: lat_apilar_contexto(vm); break; 
            case POP_BLOCK: lat_desapilar_contexto(vm); break; 
            

            }   //fin de switch
            
#if DEPURAR_MV            
            __imprimir_lista(vm, vm->pila);
            printf("\n");
#endif            
        }   //fin for
    }   //fin if (T_FUNC)
    else if (func->tipo == T_CFUNC)
    {
        ((void (*)(lat_mv*))(func->datos.fun_usuario))(vm);
    }
    else
    {
        lat_fatal_error("Linea %d, %d: %s", func->num_linea, func->num_columna,  "El objeto no es una funcion");
    }
}
