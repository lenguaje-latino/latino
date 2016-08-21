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

#include "compat.h"
#include "latino.h"
#include "vm.h"
#include "libmem.h"
#include "libmath.h"
#include "libstring.h"
#include "libio.h"
#include "liblist.h"
#include "libnet.h"
#include "parse.h"

static void registrar_cfuncion(lat_vm* vm, char *palabra_reservada, void (*function)(lat_vm* vm))
{
    lat_asignar_contexto_objeto(lat_obtener_contexto(vm),
                                lat_cadena_nueva(vm, palabra_reservada),
                                lat_definir_cfuncion(vm, function));
}

lat_vm* lat_crear_maquina_virtual()
{
    lat_vm* vm = (lat_vm*)__memoria_asignar(sizeof(lat_vm));
    vm->pila = __lista_nuevo();
    vm->todos_objetos = __lista_nuevo();
    vm->basurero_objetos = __lista_nuevo();
    vm->modulos = __lista_nuevo();
    vm->memoria_usada = 0;
    vm->objeto_verdadero = lat_logico_nuevo(vm, true);
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

    /*10 Operadores */
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

    /*20 funciones matematicas */
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

    /*30 funciones para cadenas (string)*/
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
    registrar_cfuncion(vm, "es_alfanumerico", lat_es_alfanumerico);

    registrar_cfuncion(vm, "ejecutar", lat_ejecutar);
    registrar_cfuncion(vm, "ejecutar_archivo", lat_ejecutar_archivo);

    /* 40 entrada / salida */
    registrar_cfuncion(vm, "leer", lat_leer);
    registrar_cfuncion(vm, "escribir", lat_imprimir);
    registrar_cfuncion(vm, "leer_archivo", lat_leer_archivo);
    registrar_cfuncion(vm, "escribir_archivo", lat_escribir_archivo);
    registrar_cfuncion(vm, "salir", lat_salir);

    /*50 conversion de tipos de dato*/
    registrar_cfuncion(vm, "tipo", lat_tipo);
    registrar_cfuncion(vm, "logico", lat_logico);
    registrar_cfuncion(vm, "entero", lat_entero);
    registrar_cfuncion(vm, "decimal", lat_decimal);
    registrar_cfuncion(vm, "cadena", lat_cadena);

    /*99 otras funciones */
    registrar_cfuncion(vm, "cadena", lat_cadena);
    registrar_cfuncion(vm, "maximo", lat_maximo);
    registrar_cfuncion(vm, "minimo", lat_minimo);
    registrar_cfuncion(vm, "sistema", lat_sistema);
#ifndef _WIN32
    registrar_cfuncion(vm, "peticion", lat_peticion);
#endif
    return vm;
}

void lat_apilar(lat_vm* vm, lat_objeto* o)
{
    __lista_agregar(vm->pila, (void*)o);
}

lat_objeto* lat_desapilar(lat_vm* vm)
{
    list_node* n = vm->pila;
    if (n->data == NULL)
    {
        lat_fatal_error("Pila vacia");
    }
    else
    {
        list_node *curr = n;
        lat_objeto *ret;
        if(curr->next->data == NULL)
        {
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
        return ret;
    }
    return NULL;
}

void lat_apilar_lista(lat_objeto* lista, lat_objeto* o)
{
    __lista_agregar(lista->data.lista, (void*)o);
}

lat_objeto* lat_desapilar_lista(lat_objeto* lista)
{
    list_node* n = ((list_node*)lista)->next;
    if (n->data == NULL)
    {
        lat_fatal_error("Lista vacia");
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
        lat_fatal_error("Namespace desborde de la pila");
    }
    vm->contexto_pila[vm->apuntador_pila + 1] = lat_clonar_objeto(vm, vm->contexto_pila[vm->apuntador_pila]);
    vm->apuntador_pila++;
}

void lat_desapilar_contexto(lat_vm* vm)
{
    if (vm->apuntador_pila == 0)
    {
        lat_fatal_error("Namespace pila vacia");
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
    lat_function* fval = (lat_function*)__memoria_asignar(sizeof(lat_function));
    fval->bcode = inslist;
    ret->data.func = fval;
    return ret;
}

lat_objeto* lat_definir_cfuncion(lat_vm* vm, void (*function)(lat_vm* vm))
{
    lat_objeto* ret = lat_cfuncion_nueva(vm);
    ret->data.cfunc = function;
    return ret;
}

static void __imprimir_objeto(lat_vm* vm, lat_objeto* in)
{
    fprintf(stdout, "%s", __objeto_a_cadena(in));
}

void lat_imprimir(lat_vm* vm)
{
    lat_objeto* in = lat_desapilar(vm);
    __imprimir_objeto(vm, in);
    printf("\n");
    vm->registros[255] = in;
}

void __imprimir_lista(lat_vm* vm, list_node* l)
{
    fprintf(stdout, "%s", __lista_a_cadena(l));
}

void __imprimir_diccionario(lat_vm* vm, hash_map* d)
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
                if (o->type == T_LIST)
                {
                    __imprimir_lista(vm, o->data.lista);
                    if (c->next->data)
                    {
                        fprintf(stdout, "%s", ", ");
                    }
                }
                if (o->type == T_DICT)
                {
                    __imprimir_diccionario(vm, o->data.dict);
                    if (c->next->data)
                    {
                        fprintf(stdout, "%s", ", ");
                    }
                }
                else
                {
                    if (o->type)
                    {
                        __imprimir_objeto(vm, o);
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
    lat_objeto *func = nodo_analizar_arbol(vm, lat_analizar_expresion(lat_obtener_cadena(lat_desapilar(vm)), &status));
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
        ast *tree = lat_analizar_archivo(input);
        if (!tree)
        {
            lat_fatal_error("Error al leer el archivo: %s", input);
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
    if ((a->type == T_DOUBLE && b->type == T_DOUBLE) || (a->type == T_INT && b->type == T_DOUBLE))
    {
        double tmp = lat_obtener_decimal(b);
        if (tmp == 0)
        {
            lat_fatal_error("Linea %d, %d: %s", b->num_linea, b->num_columna,  "Division entre cero");
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
            lat_fatal_error("Linea %d, %d: %s", b->num_linea, b->num_columna,  "Division entre cero");
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
        vm->registros[255] = lat_obtener_logico(a) != lat_obtener_logico(b) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) != lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) != 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) != 0 ? vm->objeto_verdadero : vm->objeto_falso;
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
        vm->registros[255] = lat_obtener_logico(a) == lat_obtener_logico(b) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) == lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) == 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) == 0 ? vm->objeto_verdadero : vm->objeto_falso;
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
        vm->registros[255] = (lat_obtener_decimal(a) < lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) < 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) < 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \"<\" en tipos invalidos");
}

void lat_menor_igual(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) <= lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) <= 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) <= 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \"<=\" en tipos invalidos");
}

void lat_mayor_que(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) > lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) > 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) > 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \">\" en tipos invalidos");
}

void lat_mayor_igual(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE))
    {
        vm->registros[255] = (lat_obtener_decimal(a) >= lat_obtener_decimal(b)) ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_STR && b->type == T_STR)
    {
        vm->registros[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) >= 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    if (a->type == T_LIT && b->type == T_LIT)
    {
        vm->registros[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) >= 0 ? vm->objeto_verdadero : vm->objeto_falso;
        return;
    }
    lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Intento de aplicar operador \">=\" en tipos invalidos");
}

void lat_y(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] =  (lat_obtener_logico(a) && lat_obtener_logico(b)) == true ? vm->objeto_verdadero : vm->objeto_falso;
}

void lat_o(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] =  (lat_obtener_logico(a) || lat_obtener_logico(b)) == true ? vm->objeto_verdadero : vm->objeto_falso;
}

void lat_negacion(lat_vm* vm)
{
    lat_objeto* o = lat_desapilar(vm);
    vm->registros[255] =  (lat_obtener_logico(o) == false) ? vm->objeto_verdadero : vm->objeto_falso;
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
    if (pos < 0 || pos >= __lista_longitud(l))
    {
        lat_fatal_error("Indice fuera de rango");
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
    if (pos < 0 || pos >= __lista_longitud(l))
    {
        lat_fatal_error("Indice fuera de rango");
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
#if DEPURAR_MV
        printf("Ejecutando...\n");
#endif
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
#if DEPURAR_MV
            printf("%i\t", pos);
#endif
            switch (cur.ins)
            {
            case OP_END:
#if DEPURAR_MV
                printf("END\n");
#endif
                return;
                break;
            case OP_NOP:
#if DEPURAR_MV
                printf("NOP\n");
#endif
                break;
            case OP_INC:
                vm->registros[cur.a]->data.i = vm->registros[cur.a]->data.i + 1;
#if DEPURAR_MV
                printf("INC %ld\n", vm->registros[cur.a]->data.i);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_PUSH:
                lat_apilar(vm, vm->registros[cur.a]);
#if DEPURAR_MV
                printf("PUSH ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_POP:
                vm->registros[cur.a] = lat_desapilar(vm);
#if DEPURAR_MV
                printf("POP ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_GET:
            {
                lat_objeto* contexto = vm->registros[cur.a];
                lat_objeto* nombre = vm->registros[cur.b];
                vm->registros[cur.b] = lat_obtener_contexto_objeto(contexto, nombre);
                if(vm->registros[cur.b]->type == T_FUNC)
                {
                    if(__lista_longitud(vm->pila) < nombre->num_param)
                    {
                        //TODO: Agregar manejo de excepciones
                        lat_fatal_error("Linea %d, %d: %s '%s'", nombre->num_linea, nombre->num_columna,  "Numero incorrecto de parametros en funcion\n", nombre->data.str);
                    }
                }
#if DEPURAR_MV
                printf("GET ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_objeto(vm, vm->registros[cur.b]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
            }
            break;
            case OP_SET:
                lat_asignar_contexto_objeto(vm->registros[cur.a], lat_clonar_objeto(vm, ((lat_objeto*)cur.meta)), vm->registros[cur.b]);
#if DEPURAR_MV
                printf("SET ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_objeto(vm, vm->registros[cur.b]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_STORELIT:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
#if DEPURAR_MV
                printf("STORELIT ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_STOREINT:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
#if DEPURAR_MV
                printf("STOREINT ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_STOREDOUBLE:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
#if DEPURAR_MV
                printf("STOREDOUBLE ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_STORESTR:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
#if DEPURAR_MV
                printf("STORESTR ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_STOREBOOL:
                vm->registros[cur.a] = ((lat_objeto*)cur.meta);
#if DEPURAR_MV
                printf("STOREBOOL ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_STORELIST:
            {
                lat_objeto* lst = lat_lista_nueva(vm, __lista_nuevo());
                long num_elementos = vm->registros[0]->data.i;
                lat_objeto* tmp = NULL;
                int i=0;
                for(i; i < num_elementos;i++){
                    tmp = lat_desapilar(vm);
                    __lista_agregar(lst->data.lista, tmp);
                }
                vm->registros[cur.a] = lst;
#if DEPURAR_MV
                printf("STORELIST ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
            }
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
                    lat_fatal_error("%s", "la posicion de la lista no es un entero");
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
#if DEPURAR_MV
                printf("MOV ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_objeto(vm, vm->registros[cur.b]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_GLOBALNS:
                vm->registros[cur.a] = vm->contexto_pila[0];
#if DEPURAR_MV
                printf("GLOBALNS ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_LOCALNS:
                vm->registros[cur.a] = lat_obtener_contexto(vm);
#if DEPURAR_MV
                printf("LOCALNS ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_FN:
                vm->registros[cur.a] = lat_definir_funcion(vm, (lat_bytecode*)cur.meta);
#if DEPURAR_MV
                printf("FN ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
                break;
            case OP_JMP:
                pos = cur.a - 1;
#if DEPURAR_MV
                printf("JMP %i", pos);
                printf("\n");
                printf("\t");
                __imprimir_lista(vm, vm->pila);
#endif
                break;
            case OP_JMPIF:
                if (lat_obtener_logico(vm->registros[cur.b]))
                {
                    pos = cur.a - 1;
#if DEPURAR_MV
                    printf("JMPIF %i", pos);
                    printf("\n");
                    printf("\t");
                    __imprimir_lista(vm, vm->pila);
#endif
                }
                break;
            case OP_CALL:
                if (vm->registros[cur.a] != NULL)
                {
#if DEPURAR_MV
                    printf("CALL ");
                    __imprimir_objeto(vm, vm->registros[cur.a]);
                    printf("\t");
                    __imprimir_lista(vm, vm->pila);
                    printf("\n");
#endif
                    lat_objeto* fun = (lat_objeto*) vm->registros[cur.a];
                    lat_llamar_funcion(vm, fun);
                }
                break;
            case OP_NOT:
                vm->registros[cur.a] = lat_obtener_logico(vm->registros[cur.a]) == true ? vm->objeto_falso : vm->objeto_verdadero;
#if DEPURAR_MV
                printf("NOT ");
                __imprimir_objeto(vm, vm->registros[cur.a]);
                printf("\t");
                __imprimir_lista(vm, vm->pila);
                printf("\n");
#endif
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
        lat_fatal_error("Linea %d, %d: %s", func->num_linea, func->num_columna,  "El objeto no es una funcion");
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
            vm->registros[255] = vm->objeto_verdadero;
        }
        break;
    case T_LIT:
        if (strcmp(a->data.c, "") == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_verdadero;
        }
        break;
    case T_DOUBLE:
        if ((int)a->data.d == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_verdadero;
        }
        break;
    case T_STR:
        if (strcmp(a->data.str, "") == 0)
        {
            vm->registros[255] = vm->objeto_falso;
        }
        else
        {
            vm->registros[255] = vm->objeto_verdadero;
        }
        break;
    default:
        lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Conversion de tipo de dato incompatible");
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
            lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Conversion de tipo de dato incompatible");
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
            lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Conversion de tipo de dato incompatible");
        }
    }
    break;
    default:
        lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Conversion de tipo de dato incompatible");
        break;
    }
}
void lat_literal(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        vm->registros[255] = lat_cadena_nueva(vm, __str_logico_a_cadena(a->data.b));
        break;
    case T_INT:
        vm->registros[255] = lat_cadena_nueva(vm, __str_entero_a_cadena(a->data.i));
        break;
    case T_DOUBLE:
        vm->registros[255] = lat_cadena_nueva(vm, __str_decimal_a_cadena(a->data.d));
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
            lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Conversion de tipo de dato incompatible");
        }
    }
    break;
    default:
       lat_fatal_error("Linea %d, %d: %s", a->num_linea, a->num_columna,  "Conversion de tipo de dato incompatible");
        break;
    }
}

void lat_cadena(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    switch (a->type)
    {
    case T_BOOL:
        vm->registros[255] = lat_cadena_nueva(vm, __str_logico_a_cadena(a->data.b));
        break;
    case T_INT:
        vm->registros[255] = lat_cadena_nueva(vm, __str_entero_a_cadena(a->data.i));
        break;
    case T_DOUBLE:
        vm->registros[255] = lat_cadena_nueva(vm, __str_decimal_a_cadena(a->data.d));
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
