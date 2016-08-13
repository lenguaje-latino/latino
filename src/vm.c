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

#include "latino.h"
#include "vm.h"
#include "libmem.h"
#include "libmath.h"
#include "libstring.h"
#include "libio.h"
#include "liblist.h"
#include "libnet.h"

static void registrar_cfuncion(lat_vm* vm, char *palabra_reservada, void (*function)(lat_vm* vm))
{
    lat_asignar_contexto_objeto(lat_obtener_contexto(vm),
                                lat_cadena_nueva(vm, palabra_reservada),
                                lat_definir_cfuncion(vm, function));
}

lat_vm* lat_crear_maquina_virtual()
{
    lat_vm* vm = (lat_vm*)lat_asignar_memoria(sizeof(lat_vm));
    vm->pila = lat_crear_lista();
    vm->todos_objetos = lat_crear_lista();
    vm->basurero_objetos = lat_crear_lista();
    vm->modulos = lat_crear_lista();
    vm->memoria_usada = 0;
    vm->objeto_cierto = lat_logico_nuevo(vm, true);
    vm->objeto_falso = lat_logico_nuevo(vm, false);
    memset(vm->registros, 0, 256);
    memset(vm->contexto_pila, 0, 256);
    vm->contexto_pila[0] = lat_instancia(vm);
    vm->apuntador_pila = 0;
    
    /**
     * 10 Operadores
     * 20 funciones matematicas
     * 30 funciones para cadenas (string)
     * 40 entrada y salida
     * 50 conversion de tipos de dato
     * 60
     * 70
     * 9999 otras funciones // a crear una categoria para ellas
     *  
     */
    
    
    /*lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "+"), lat_definir_cfuncion(ret, lat_sumar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "-"), lat_definir_cfuncion(ret, lat_restar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "*"), lat_definir_cfuncion(ret, lat_multiplicar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "/"), lat_definir_cfuncion(ret, lat_dividir));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "%"), lat_definir_cfuncion(ret, lat_modulo_decimal));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "!="), lat_definir_cfuncion(ret, lat_diferente));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "=="), lat_definir_cfuncion(ret, lat_igualdad));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "<"), lat_definir_cfuncion(ret, lat_menor_que));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "<="), lat_definir_cfuncion(ret, lat_menor_igual));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, ">"), lat_definir_cfuncion(ret, lat_mayor_que));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, ">="), lat_definir_cfuncion(ret, lat_mayor_igual));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "&&"), lat_definir_cfuncion(ret, lat_y));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "y"), lat_definir_cfuncion(ret, lat_y));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "||"), lat_definir_cfuncion(ret, lat_o));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "o"), lat_definir_cfuncion(ret, lat_o));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "!"), lat_definir_cfuncion(ret, lat_negacion));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "no"), lat_definir_cfuncion(ret, lat_negacion));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "gc"), lat_definir_cfuncion(ret, lat_basurero));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "imprimir"), lat_definir_cfuncion(ret, lat_imprimir));
    */

    /**
     * 10 Operadores
     */
    registrar_cfuncion(vm, "+", lat_sumar);
    registrar_cfuncion(vm, "-", lat_restar);
    registrar_cfuncion(vm, "*", lat_multiplicar);
    registrar_cfuncion(vm, "/", lat_dividir);
    registrar_cfuncion(vm, "%", lat_modulo_decimal);
    registrar_cfuncion(vm, "!=", lat_diferente);
    registrar_cfuncion(vm, "==", lat_igualdad);
    registrar_cfuncion(vm, "<", lat_menor_que);
    registrar_cfuncion(vm, "<=", lat_menor_igual);
    registrar_cfuncion(vm, ">", lat_mayor_que);
    registrar_cfuncion(vm, ">=", lat_mayor_igual);
    registrar_cfuncion(vm, "&&", lat_y);
    registrar_cfuncion(vm, "||", lat_o);
    registrar_cfuncion(vm, "!", lat_negacion);
    registrar_cfuncion(vm, "imprimir", lat_imprimir);

    /*
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "ejecutar"), lat_definir_cfuncion(ret, lat_ejecutar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "ejecutar_archivo"), lat_definir_cfuncion(ret, lat_ejecutar_archivo));
    */

    registrar_cfuncion(vm, "ejecutar", lat_ejecutar);
    registrar_cfuncion(vm, "ejecutar_archivo", lat_ejecutar_archivo);


    /*
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "arco_coseno"), lat_definir_cfuncion(ret, lat_arco_coseno));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "arco_seno"), lat_definir_cfuncion(ret, lat_arco_seno));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "arco_tangente"), lat_definir_cfuncion(ret, lat_arco_tangente));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "arco_tangente2"), lat_definir_cfuncion(ret, lat_arco_tangente2));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "coseno"), lat_definir_cfuncion(ret, lat_coseno));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "coseno_hiperbolico"), lat_definir_cfuncion(ret, lat_coseno_hiperbolico));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "seno"), lat_definir_cfuncion(ret, lat_seno));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "seno_hiperbolico"), lat_definir_cfuncion(ret, lat_seno_hiperbolico));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "tangente"), lat_definir_cfuncion(ret, lat_tangente));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "tangente_hiperbolica"), lat_definir_cfuncion(ret, lat_tangente_hiperbolica));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "exponente"), lat_definir_cfuncion(ret, lat_exponente));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "frexp"), lat_definir_cfuncion(ret, lat_frexp));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "ldexp"), lat_definir_cfuncion(ret, lat_ldexp));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "logaritmo_natural"), lat_definir_cfuncion(ret, lat_logaritmo_natural));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "logaritmo_base10"), lat_definir_cfuncion(ret, lat_logaritmo_base10));
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "modf"), lat_definir_cfuncion(ret, lat_modf));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "potencia"), lat_definir_cfuncion(ret, lat_potencia));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "raiz_cuadrada"), lat_definir_cfuncion(ret, lat_raiz_cuadrada));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "redondear_arriba"), lat_definir_cfuncion(ret, lat_redondear_arriba));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "valor_absoluto"), lat_definir_cfuncion(ret, lat_valor_absoluto));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "redondear_abajo"), lat_definir_cfuncion(ret, lat_redondeo_abajo));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "modulo"), lat_definir_cfuncion(ret, lat_modulo_decimal));
    */

    /* 20 funciones matematicas */
    registrar_cfuncion(vm, "arco_coseno", lat_arco_coseno);
    registrar_cfuncion(vm, "arco_seno", lat_arco_seno);
    registrar_cfuncion(vm, "arco_tangente", lat_arco_tangente);
    registrar_cfuncion(vm, "arco_tangente2", lat_arco_tangente2);
    registrar_cfuncion(vm, "coseno", lat_coseno);
    registrar_cfuncion(vm, "coseno_hiperbolico", lat_coseno_hiperbolico);
    registrar_cfuncion(vm, "seno", lat_seno);
    registrar_cfuncion(vm, "seno_hiperbolico", lat_seno_hiperbolico);
    registrar_cfuncion(vm, "tangente", lat_tangente);
    registrar_cfuncion(vm, "tangente_hiperbolica", lat_tangente_hiperbolica);
    registrar_cfuncion(vm, "exponente", lat_exponente);
    registrar_cfuncion(vm, "logaritmo_natural", lat_logaritmo_natural);
    registrar_cfuncion(vm, "logaritmo_base10", lat_logaritmo_base10);
    registrar_cfuncion(vm, "potencia", lat_potencia);
    registrar_cfuncion(vm, "raiz_cuadrada", lat_raiz_cuadrada);
    registrar_cfuncion(vm, "redondear_arriba", lat_redondear_arriba);
    registrar_cfuncion(vm, "valor_absoluto", lat_valor_absoluto);
    registrar_cfuncion(vm, "redondear_abajo", lat_redondear_abajo);
    registrar_cfuncion(vm, "ejecutar_archivo", lat_ejecutar_archivo);
    registrar_cfuncion(vm, "modulo", lat_modulo_decimal);

    /*
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "comparar"), lat_definir_cfuncion(ret, lat_comparar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "concatenar"), lat_definir_cfuncion(ret, lat_concatenar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "."), lat_definir_cfuncion(ret, lat_concatenar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "contiene"), lat_definir_cfuncion(ret, lat_contiene));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "copiar"), lat_definir_cfuncion(ret, lat_copiar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "termina_con"), lat_definir_cfuncion(ret, lat_termina_con));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "es_igual"), lat_definir_cfuncion(ret, lat_es_igual));
    //TODO: Pendiente
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "formato"), lat_definir_cfuncion(ret, lat_format));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "indice"), lat_definir_cfuncion(ret, lat_indice));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "insertar"), lat_definir_cfuncion(ret, lat_insertar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "ultimo_indice"), lat_definir_cfuncion(ret, lat_ultimo_indice));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "rellenar_izquierda"), lat_definir_cfuncion(ret, lat_rellenar_izquierda));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "rellenar_derecha"), lat_definir_cfuncion(ret, lat_rellenar_derecha));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "eliminar"), lat_definir_cfuncion(ret, lat_eliminar));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "esta_vacia"), lat_definir_cfuncion(ret, lat_esta_vacia));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "longitud"), lat_definir_cfuncion(ret, lat_longitud));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "reemplazar"), lat_definir_cfuncion(ret, lat_reemplazar));
    //TODO: Pendiente, se implementara cuando se implementen Listas
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "partir"), lat_definir_cfuncion(ret, lat_split));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "empieza_con"), lat_definir_cfuncion(ret, lat_empieza_con));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "subcadena"), lat_definir_cfuncion(ret, lat_subcadena));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "minusculas"), lat_definir_cfuncion(ret, lat_minusculas));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "mayusculas"), lat_definir_cfuncion(ret, lat_mayusculas));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "quitar_espacios"), lat_definir_cfuncion(ret, lat_quitar_espacios));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "es_numero"), lat_definir_cfuncion(ret, lat_es_numero));
    */

    /* 30 funciones para cadenas (string)*/
    registrar_cfuncion(vm, "comparar", lat_comparar);
    registrar_cfuncion(vm, "concatenar", lat_concatenar);
    registrar_cfuncion(vm, ".", lat_concatenar);
    registrar_cfuncion(vm, "contiene", lat_contiene);
    registrar_cfuncion(vm, "copiar", lat_copiar);
    registrar_cfuncion(vm, "termina_con", lat_termina_con);
    registrar_cfuncion(vm, "es_igual", lat_es_igual);
    registrar_cfuncion(vm, "indice", lat_indice);
    registrar_cfuncion(vm, "insertar", lat_insertar);
    registrar_cfuncion(vm, "ultimo_indice", lat_ultimo_indice);
    registrar_cfuncion(vm, "rellenar_izquierda", lat_rellenar_izquierda);
    registrar_cfuncion(vm, "rellenar_derecha", lat_rellenar_derecha);
    registrar_cfuncion(vm, "eliminar", lat_eliminar);
    registrar_cfuncion(vm, "esta_vacia", lat_esta_vacia);
    registrar_cfuncion(vm, "longitud", lat_longitud);
    registrar_cfuncion(vm, "reemplazar", lat_reemplazar);
    registrar_cfuncion(vm, "empieza_con", lat_empieza_con);
    registrar_cfuncion(vm, "subcadena", lat_subcadena);
    registrar_cfuncion(vm, "minusculas", lat_minusculas);
    registrar_cfuncion(vm, "mayusculas", lat_mayusculas);
    registrar_cfuncion(vm, "quitar_espacios", lat_quitar_espacios);
    registrar_cfuncion(vm, "es_numero", lat_es_numero);

    /*
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "leer"), lat_definir_cfuncion(ret, lat_leer));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "escribir"), lat_definir_cfuncion(ret, lat_imprimir));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "leer_archivo"), lat_definir_cfuncion(ret, lat_leer_archivo));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "escribir_archivo"), lat_definir_cfuncion(ret, lat_escribir_archivo));
    */

    // 40 entrada / salida
    registrar_cfuncion(vm, "leer", lat_leer);
    registrar_cfuncion(vm, "escribir", lat_imprimir);
    registrar_cfuncion(vm, "leer_archivo", lat_leer_archivo);
    registrar_cfuncion(vm, "escribir_archivo", lat_escribir_archivo);
    registrar_cfuncion(vm, "salir", lat_salir);

    /*
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "tipo"), lat_definir_cfuncion(ret, lat_tipo));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "logico"), lat_definir_cfuncion(ret, lat_logico));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "entero"), lat_definir_cfuncion(ret, lat_entero));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "decimal"), lat_definir_cfuncion(ret, lat_decimal));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "cadena"), lat_definir_cfuncion(ret, lat_cadena));
    lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "salir"), lat_definir_cfuncion(ret, lat_salir));
    */

    /* 50 conversion de tipos de dato*/
    registrar_cfuncion(vm, "tipo", lat_tipo);
    registrar_cfuncion(vm, "logico", lat_logico);
    registrar_cfuncion(vm, "entero", lat_entero);
    registrar_cfuncion(vm, "decimal", lat_decimal);
    registrar_cfuncion(vm, "cadena", lat_cadena);

    /*ejemplo de implementacion de una funcion en C */
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "maximo"), lat_definir_cfuncion(ret, lat_maximo));
    /*Creacion dela funcion minimo*/
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "minimo"), lat_definir_cfuncion(ret, lat_minimo));

    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "sistema"), lat_definir_cfuncion(ret, lat_sistema));

    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "agregar"), lat_definir_cfuncion(ret, lat_agregar));

    /* operaciones con sockets */
    //lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "peticion"), lat_definir_cfuncion(ret, lat_peticion));

    /*operaciones con listas*/
    //registrar_cfuncion(vm, "cadena", lat_cadena);

    /* 9999 otras funciones */
    registrar_cfuncion(vm, "cadena", lat_cadena);
    registrar_cfuncion(vm, "maximo", lat_maximo);
    registrar_cfuncion(vm, "minimo", lat_minimo);
    registrar_cfuncion(vm, "sistema", lat_sistema);
    registrar_cfuncion(vm, "peticion", lat_peticion);
    return vm;
}

void lat_apilar(lat_vm* vm, lat_objeto* o)
{
    //printf("\n%s\n", "lat_apilar");
    insert_list(vm->pila, (void*)o);
    //lat_imprimir_lista(vm, vm->pila);
}

lat_objeto* lat_desapilar(lat_vm* vm)
{
    //FIXME: No desapila los objetos
    //printf("\n%s\n", "lat_desapilar");
    //lat_imprimir_lista(vm, vm->pila);
    list_node* n = vm->pila;
    if (n->data == NULL)
    {
        lat_error("Pila vacia");
    }
    else
    {
        list_node *curr = n;
        lat_objeto *ret;
        if(curr->next->data == NULL){
            //primer nodo
            ret = (lat_objeto*)curr->data;
            curr = curr->next;
            vm->pila = curr;
            return ret;
        }
        while (curr->next != NULL && curr->next->data != NULL)
        {
            curr = curr->next;
        }
        ret = (lat_objeto*)curr->data;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        //lat_imprimir_lista(vm, vm->pila);
        return ret;
    }
    return NULL;
}

void lat_apilar_lista(lat_objeto* lista, lat_objeto* o)
{
    //printf("\n%s\n", "lat_apilar_lista");
    insert_list(lista->data.lista, (void*)o);
}

lat_objeto* lat_desapilar_lista(lat_objeto* lista)
{
    //printf("\n%s\n", "lat_desapilar_lista");
    list_node* n = ((list_node*)lista)->next;
    if (n->data == NULL)
    {
        lat_error("Lista vacia");
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        lat_objeto* ret = (lat_objeto*)n->data;
        return ret;
    }
    return NULL;
}

void lat_apilar_contexto(lat_vm* vm)
{
    if (vm->apuntador_pila >= MAX_STACK_SIZE)
    {
        lat_error("Namespace desborde de la pila");
    }
    vm->contexto_pila[vm->apuntador_pila + 1] = lat_clonar_objeto(vm, vm->contexto_pila[vm->apuntador_pila]);
    vm->apuntador_pila++;
}

void lat_desapilar_contexto(lat_vm* vm)
{
    if (vm->apuntador_pila == 0)
    {
        lat_error("Namespace pila vacia");
    }
    lat_eliminar_objeto(vm, vm->contexto_pila[vm->apuntador_pila--]);
}

lat_objeto* lat_obtener_contexto(lat_vm* vm)
{
    return vm->contexto_pila[vm->apuntador_pila];
}

lat_objeto* lat_definir_funcion(lat_vm* vm, lat_bytecode* inslist)
{
    lat_objeto* ret = lat_funcion_nueva(vm);
    lat_function* fval = (lat_function*)lat_asignar_memoria(sizeof(lat_function));
    fval->bcode = inslist;
    ret->data.func = fval;
    //vm->memoria_usada += sizeof(sizeof(lat_function));
    return ret;
}

lat_objeto* lat_definir_cfuncion(lat_vm* vm, void (*function)(lat_vm* vm))
{
    lat_objeto* ret = lat_cfuncion_nueva(vm);
    ret->data.cfunc = function;
    return ret;
}

static void imprimir_objeto(lat_objeto* in)
{
    if (in == NULL || in->type == T_NULO)
    {
        fprintf(stdout, "%s", "nulo");
    }
    else if (in->type == T_BOOL)
    {
        fprintf(stdout, "%s", bool2str(lat_obtener_logico(in)));
    }
    else if (in->type == T_INSTANCE)
    {
        fprintf(stdout, "%s", "objeto");
    }
    else if (in->type == T_LIT)
    {
        fprintf(stdout, "%s", lat_obtener_literal(in));
    }
    else if (in->type == T_INT)
    {
        fprintf(stdout, "%ld", lat_obtener_entero(in));
    }
    else if (in->type == T_DOUBLE)
    {
        fprintf(stdout, "%.14g", lat_obtener_decimal(in));
    }
    else if (in->type == T_STR)
    {
        fprintf(stdout, "%s", lat_obtener_cadena(in));
    }
    else if (in->type == T_FUNC)
    {
        fprintf(stdout, "%s", "funcion");
    }
    else if (in->type == T_CFUNC)
    {
        fprintf(stdout, "%s", "c_funcion");
    }
    else if (in->type == T_CLASS)
    {
        fprintf(stdout, "%s", "clase");
    }
    else
    {
        fprintf(stdout, "Tipo desconocido %d", in->type);
    }
}

void lat_imprimir(lat_vm* vm)
{
    lat_objeto* in = lat_desapilar(vm);
    if (in->type == T_LIST)
    {
        lat_imprimir_lista(vm, in->data.lista);
    }
    else if (in->type == T_DICT)
    {
        lat_imprimir_diccionario(vm, in->data.dict);
    }
    else
    {
        imprimir_objeto(in);
    }
    printf("\n");
    vm->registros[255] = in;
}

void lat_imprimir_lista(lat_vm* vm, list_node* l)
{
    fprintf(stdout, "%s", "[ ");
    if (l != NULL && length_list(l) > 0)
    {
        list_node* c;
        for (c = l; c != NULL; c = c->next)
        {
            if (c->data != NULL)
            {
                lat_objeto* o = ((lat_objeto*)c->data);
                //printf("\ntype %i, obj_ref: %p\n", o->type, o);
                if (o->type == T_LIST)
                {
                    lat_imprimir_lista(vm, o->data.lista);
                    if (c->next)
                    {
                        fprintf(stdout, "%s", ", ");
                    }
                }
                else
                {
                    if (o->type)
                    {
                        imprimir_objeto(o);
                        if (c->next)
                        {
                            fprintf(stdout, "%s", ", ");
                        }
                    }
                }
            }
        }
    }
    fprintf(stdout, "%s", " ]");
}

void lat_imprimir_diccionario(lat_vm* vm, hash_map* d)
{
    fprintf(stdout, "%s", "{ ");
    if (d != NULL)
    {
        list_node* c;
        for (c = (list_node*) d->buckets; c != NULL; c = c->next)
        {
            if (c->data != NULL)
            {
                lat_objeto* o = ((lat_objeto*)c->data);
                //printf("\ntype %i, obj_ref: %p\t, marked: %i", o->type, o, o->marked);
                if (o->type == T_LIST)
                {
                    lat_imprimir_lista(vm, o->data.lista);
                    if (c->next->data)
                    {
                        fprintf(stdout, "%s", ", ");
                    }
                }
                if (o->type == T_DICT)
                {
                    lat_imprimir_diccionario(vm, o->data.dict);
                    if (c->next->data)
                    {
                        fprintf(stdout, "%s", ", ");
                    }
                }
                else
                {
                    if (o->type)
                    {
                        imprimir_objeto(o);
                        if (c->next->data)
                        {
                            fprintf(stdout, "%s", ", ");
                        }
                    }
                }
            }
        }
    }
    fprintf(stdout, "%s", " }");
}

void lat_ejecutar(lat_vm *vm)
{
    int status;
    lat_objeto *func = nodo_analizar_arbol(vm, lat_analizar_expresion(vm, lat_obtener_cadena(lat_desapilar(vm)), &status));
    lat_llamar_funcion(vm, func);
    lat_apilar(vm, vm->registros[255]);
}

void lat_ejecutar_archivo(lat_vm *vm)
{
    char *input = lat_obtener_cadena(lat_desapilar(vm));
    char *dot = strrchr(input, '.');
    char *extension;
    if (!dot || dot == input)
    {
        extension = "";
    }
    else
    {
        extension = dot + 1;
    }
    if (strcmp(extension, "lat") == 0)
    {
        ast *tree = lat_analizar_archivo(vm, input);
        if (!tree)
        {
            lat_error("error al leer el archivo: %s", input);
        }
        lat_objeto *func = nodo_analizar_arbol(vm, tree);
        lat_llamar_funcion(vm, func);
        lat_apilar(vm, vm->registros[255]);
    }
}

void lat_clonar(lat_vm* vm)
{
    lat_objeto* ns = lat_desapilar(vm);
    vm->registros[255] = lat_clonar_objeto(vm, ns);
}

void lat_sumar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE))
    {
        lat_error("Intento de aplicar operador \"+\" en tipos invalidos");
    }
    if (a->type == T_DOUBLE || b->type == T_DOUBLE)
    {
        vm->registros[255] = lat_decimal_nuevo(vm, lat_obtener_decimal(a) + lat_obtener_decimal(b));
    }
    else
    {
        vm->registros[255] = lat_entero_nuevo(vm, lat_obtener_entero(a) + lat_obtener_entero(b));
    }
}

void lat_restar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE))
    {
        lat_error("Intento de aplicar operador \"-\" en tipos invalidos");
    }
    if (a->type == T_DOUBLE || b->type == T_DOUBLE)
    {
        vm->registros[255] = lat_decimal_nuevo(vm, lat_obtener_decimal(a) - lat_obtener_decimal(b));
    }
    else
    {
        vm->registros[255] = lat_entero_nuevo(vm, lat_obtener_entero(a) - lat_obtener_entero(b));
    }
}

void lat_multiplicar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE))
    {
        lat_error("Intento de aplicar operador \"*\" en tipos invalidos");
    }
    if (a->type == T_DOUBLE || b->type == T_DOUBLE)
    {
        vm->registros[255] = lat_decimal_nuevo(vm, lat_obtener_decimal(a) * lat_obtener_decimal(b));
    }
    else
    {
        vm->registros[255] = lat_entero_nuevo(vm, lat_obtener_entero(a) * lat_obtener_entero(b));
    }
}

void lat_dividir(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE))
    {
        lat_error("Intento de aplicar operador \"/\" en tipos invalidos");
    }
    if ((a->type == T_DOUBLE && b->type == T_DOUBLE) || (a->type == T_INT && b->type == T_DOUBLE))
    {
        double tmp = lat_obtener_decimal(b);
        if (tmp == 0)
        {
            lat_error("Division por cero");
        }
        else
        {
            vm->registros[255] = lat_decimal_nuevo(vm, (lat_obtener_decimal(a) / tmp));
        }
    }
    else
    {
        int tmp = lat_obtener_entero(b);
        if (tmp == 0)
        {
            lat_error("Division por cero");
        }
        else
        {
            if (a->type == T_DOUBLE)
            {
                vm->registros[255] = lat_decimal_nuevo(vm, (lat_obtener_decimal(a) / tmp));
            }
            else
            {
                vm->registros[255] = lat_decimal_nuevo(vm, (lat_obtener_entero(a) / tmp));
            }
        }
    }
}

void lat_diferente(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (a->type == T_BOOL && b->type == T_BOOL)
    {
        vm->registros[255] = lat_obtener_logico(a) != lat_obtener_logico(b) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) != lat_obtener_decimal(b)) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) != 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) != 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    vm->registros[255] = vm->objeto_falso;
}

void lat_igualdad(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (a->type == T_BOOL && b->type == T_BOOL)
    {
        vm->registros[255] = lat_obtener_logico(a) == lat_obtener_logico(b) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) == lat_obtener_decimal(b)) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) == 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) == 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    vm->registros[255] = vm->objeto_falso;
}

void lat_menor_que(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) < lat_obtener_decimal(b)) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) < 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) < 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    lat_error("Intento de aplicar operador \"<\" en tipos invalidos");
}

void lat_menor_igual(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) <= lat_obtener_decimal(b)) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) <= 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) <= 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    lat_error("Intento de aplicar operador \"<=\" en tipos invalidos");
}

void lat_mayor_que(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) > lat_obtener_decimal(b)) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) > 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) > 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    lat_error("Intento de aplicar operador \">\" en tipos invalidos");
}

void lat_mayor_igual(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) >= lat_obtener_decimal(b)) ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) >= 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) >= 0 ? vm->objeto_cierto : vm->objeto_falso;
        return;
    }
    lat_error("Intento de aplicar operador \">=\" en tipos invalidos");
}

void lat_y(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((b->type != T_BOOL && b->type != T_INT) || (a->type != T_BOOL && a->type != T_INT))
    {
        lat_error("Intento de aplicar operador \"y\" en tipos invalidos");
    }
    vm->registros[255] =  (lat_obtener_logico(a) && lat_obtener_logico(b)) == true ? vm->objeto_cierto : vm->objeto_falso;
}

void lat_o(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((b->type != T_BOOL && b->type != T_INT) || (a->type != T_BOOL && a->type != T_INT))
    {
        lat_error("Intento de aplicar operador \"y\" en tipos invalidos");
    }
    vm->registros[255] =  (lat_obtener_logico(a) || lat_obtener_logico(b)) == true ? vm->objeto_cierto : vm->objeto_falso;
}

void lat_negacion(lat_vm* vm)
{
    //printf("%s\n", "dentro de lat_negacion");
    lat_objeto* o = lat_desapilar(vm);
    if (o->type != T_BOOL)
    {
        lat_error("Intento de negar tipo invalido");
    }
    vm->registros[255] =  (lat_obtener_logico(o) == false) ? vm->objeto_cierto : vm->objeto_falso;
}

lat_bytecode lat_bc(lat_ins i, int a, int b, void* meta)
{
    lat_bytecode ret;
    ret.ins = i;
    ret.a = a;
    ret.b = b;
    ret.meta = meta;
    return ret;
}

void lista_modificar_elemento(list_node* l, void* data, int pos)
{
    list_node* c;
    int i = -1;
    if (pos < 0 || pos >= length_list(l))
    {
        lat_error("Indice fuera de rango");
    }
    for (c = l; c->next != NULL; c = c->next)
    {
        if (i == pos)
        {
            c->data = data;
            return;
        }
        i++;
    }
}

lat_objeto* lista_obtener_elemento(list_node* l, int pos)
{
    list_node* c;
    int i = -1;
    if (pos < 0 || pos >= length_list(l))
    {
        lat_error("Indice fuera de rango");
    }
    for (c = l; c->next != NULL; c = c->next)
    {
        if (i == pos)
        {
            return (lat_objeto *)c->data;
        }
        i++;
    }
    return NULL;
}

void lat_llamar_funcion(lat_vm* vm, lat_objeto* func)
{
    if (func->type == T_FUNC)
    {
        if (!vm->REPL)
        {
            lat_apilar_contexto(vm);
        }
        lat_asignar_contexto_objeto(lat_obtener_contexto(vm), lat_cadena_nueva(vm, "$"), func);
        lat_bytecode* inslist = ((lat_function*)func->data.func)->bcode;
        lat_bytecode cur;
        int pos;
        for (pos = 0, cur = inslist[pos]; cur.ins != OP_END; cur = inslist[++pos])
        {
            switch (cur.ins)
            {
            case OP_END:
                return;
                break;
            case OP_NOP:
                break;
            case OP_PUSH:
                lat_apilar(vm, vm->registros[cur.a]);
                //lat_imprimir_lista(vm, vm->pila);
                //printf("\n");
                break;
            case OP_POP:
                vm->registros[cur.a] = lat_desapilar(vm);
                //lat_imprimir_lista(vm, vm->pila);
                //printf("\n");
                break;
            case OP_GET:
                vm->registros[cur.a] = lat_obtener_contexto_objeto(vm->registros[cur.b], vm->registros[cur.a]);
                break;
            case OP_SET:
                lat_asignar_contexto_objeto(vm->registros[cur.b], lat_clonar_objeto(vm, ((lat_objeto*)cur.meta)), vm->registros[cur.a]);
                break;
            case OP_STORELIT:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
                break;
            case OP_STOREINT:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
                break;
            case OP_STOREDOUBLE:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
                break;
            case OP_STORESTR:
            {
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
            }
            break;
            case OP_STOREBOOL:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
                break;
            case OP_STORELIST:
                vm->registros[cur.a] = lat_lista_nueva(vm, lat_crear_lista());
                break;
            case OP_PUSHLIST:
                lat_apilar_lista(vm->registros[cur.a], vm->registros[cur.b]);
                break;
            case OP_POPLIST:
                //TODO: Pendiente
                //vm->registros[cur.a] = lat_desapilar_lista(vm->registros[cur.b]);
                break;
            case OP_LISTGETITEM:
            {
                lat_objeto *l = vm->registros[cur.a];
                lat_objeto *pos = vm->registros[cur.b];
                vm->registros[cur.a] = lista_obtener_elemento(l->data.lista, pos->data.i);
            }
            break;
            case OP_LISTSETITEM:
            {
                lat_objeto *l = vm->registros[cur.a];
                lat_objeto *pos = vm->registros[(long) cur.meta];
                if (pos->type != T_INT)
                {
                    lat_error("%s", "la posicion de la lista no es un entero");
                }
                lista_modificar_elemento(l->data.lista, (lat_objeto*)vm->registros[cur.b], pos->data.i);
            }
            break;
            case OP_STOREDICT:
                //TODO: Pendiente
                //vm->registros[cur.a] = lat_lista_nueva(vm, make_dict());
                break;
            case OP_PUSHDICT:
                //TODO: Pendiente
                //lat_push_dict(vm->registros[cur.a], vm->registros[cur.b]);
                break;
            case OP_POPDICT:
                //TODO: Pendiente
                //vm->registros[cur.a] = lat_pop_dict(vm->registros[cur.b]);
                break;
            case OP_MOV:
                vm->registros[cur.a] = vm->registros[cur.b];
                break;
            case OP_GLOBALNS:
                vm->registros[cur.a] = vm->contexto_pila[0];
                break;
            case OP_LOCALNS:
                vm->registros[cur.a] = lat_obtener_contexto(vm);
                break;
            case OP_FN:
                vm->registros[cur.a] = lat_definir_funcion(vm, (lat_bytecode*)cur.meta);
                break;
            /*case OP_NS:
                vm->registros[cur.a] = lat_clonar_objeto(vm, lat_obtener_contexto(vm));
                lat_apilar_contexto_predefinido(vm, vm->registros[cur.a]);
                break;
            case OP_ENDNS:
                vm->registros[cur.a] = lat_desapilar_contexto_predefinido(vm);
                break;*/
            case OP_JMP:
                pos = cur.a - 1;
                break;
            case OP_JMPIF:
                if (lat_obtener_logico(vm->registros[cur.b]))
                {
                    pos = cur.a - 1;
                }
                break;
            case OP_CALL:
                if (vm->registros[cur.a] != NULL)
                {
                    lat_llamar_funcion(vm, vm->registros[cur.a]);
                }
                break;
            case OP_NOT:
                vm->registros[cur.a] = lat_obtener_logico(vm->registros[cur.a]) == true ? vm->objeto_falso : vm->objeto_cierto;
                break;
            case OP_PUSHDICTELEM:
                break;
            case OP_DICTGETITEM:
                break;
            case OP_DICTSETITEM:
                break;
            }
        }
        if (!vm->REPL)
        {
            lat_desapilar_contexto(vm);
        }
    }
    else if (func->type == T_CFUNC)
    {
        ((void (*)(lat_vm*))(func->data.func))(vm);
    }
    else
    {
        //debug("func->type: %d", func->type);
        lat_error("El objeto no es una funcion");
    }
}

void lat_logico(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_INT:
        if (a->data.i == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_cierto;
        }
        break;
    case T_LIT:
        if (strcmp(a->data.c, "") == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_cierto;
        }
        break;
    case T_DOUBLE:
        if ((int)a->data.d == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_cierto;
        }
        break;
    case T_STR:
        if (strcmp(a->data.str, "") == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_cierto;
        }
        break;
    default:
        lat_error("conversion incompatible");
        break;
    }
}
void lat_entero(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        if (a->data.b == false)
        {
            vm->registros[255] = lat_entero_nuevo(vm, 0);
        }
        else
        {
            vm->registros[255] = lat_entero_nuevo(vm, 1);
        }
        break;
    case T_LIT:
    {
        char *ptr;
        long ret;
        ret = strtol(a->data.c, &ptr, 10);
        if (strcmp(ptr, "") == 0)
        {
            vm->registros[255] = lat_entero_nuevo(vm, ret);
        }
        else
        {
            lat_error("conversion incompatible");
        }
    }
    break;
    case T_DOUBLE:
        vm->registros[255] = lat_entero_nuevo(vm, (int)a->data.d);
        break;
    case T_STR:
    {
        char *ptr;
        long ret;
        ret = strtol(a->data.str, &ptr, 10);
        if (strcmp(ptr, "") == 0)
        {
            vm->registros[255] = lat_entero_nuevo(vm, ret);
        }
        else
        {
            lat_error("conversion incompatible");
        }
    }
    break;
    default:
        lat_error("conversion incompatible");
        break;
    }
}
void lat_literal(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        vm->registros[255] = lat_cadena_nueva(vm, bool2str(a->data.b));
        break;
    case T_INT:
        vm->registros[255] = lat_cadena_nueva(vm, int2str(a->data.i));
        break;
    case T_DOUBLE:
        vm->registros[255] = lat_cadena_nueva(vm, double2str(a->data.d));
        break;
    default:
        vm->registros[255] = a;
        break;
    }
}

void lat_decimal(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        if (a->data.b == false)
        {
            vm->registros[255] = lat_decimal_nuevo(vm, 0);
        }
        else
        {
            vm->registros[255] = lat_decimal_nuevo(vm, 1);
        }
        break;
    case T_INT:
        vm->registros[255] = lat_decimal_nuevo(vm, (double)a->data.i);
        break;
    case T_DOUBLE:
        vm->registros[255] = lat_decimal_nuevo(vm, (double)a->data.i);
        break;
    case T_STR:
    {
        char *ptr;
        double ret;
        ret = strtod(a->data.str, &ptr);
        if (strcmp(ptr, "") == 0)
        {
            vm->registros[255] = lat_decimal_nuevo(vm, ret);
        }
        else
        {
            lat_error("conversion incompatible");
        }
    }
    break;
    default:
        lat_error("conversion incompatible");
        break;
    }
}

void lat_cadena(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        vm->registros[255] = lat_cadena_nueva(vm, bool2str(a->data.b));
        break;
    case T_INT:
        vm->registros[255] = lat_cadena_nueva(vm, int2str(a->data.i));
        break;
    case T_DOUBLE:
        vm->registros[255] = lat_cadena_nueva(vm, double2str(a->data.d));
        break;
    default:
        vm->registros[255] = a;
        break;
    }
}

void lat_maximo(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (lat_obtener_entero(b) > lat_obtener_entero(a))
    {
        vm->registros[255] = b;
    }
    else
    {
        vm->registros[255] = a;
    }
}

void lat_minimo(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (lat_obtener_entero(b) < lat_obtener_entero(a))
    {
        vm->registros[255] = b;
    }
    else
    {
        vm->registros[255] = a;
    }
}

void lat_tipo(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        vm->registros[255] = lat_cadena_nueva(vm, "logico");
        break;
    case T_INT:
        vm->registros[255] = lat_cadena_nueva(vm, "entero");
        break;
    case T_DOUBLE:
        vm->registros[255] = lat_cadena_nueva(vm, "decimal");
        break;
    case T_STR:
        vm->registros[255] = lat_cadena_nueva(vm, "cadena");
        break;
    case T_LIT:
        vm->registros[255] = lat_cadena_nueva(vm, "cadena");
        break;
    case T_LIST:
        vm->registros[255] = lat_cadena_nueva(vm, "lista");
        break;
    case T_DICT:
        vm->registros[255] = lat_cadena_nueva(vm, "diccionario");
        break;
    default:
        vm->registros[255] = lat_cadena_nueva(vm, "nulo");
        break;
    }
}

void lat_salir(lat_vm* vm)
{
    vm->registros[255] = lat_entero_nuevo(vm, 0L);
    exit(0);
}
