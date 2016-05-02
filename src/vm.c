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

#include "vm.h"
#include "utils.h"
#include "libmem.h"
#include "libmath.h"
#include "libstring.h"
#include "libio.h"

lat_vm* lat_crear_maquina_virtual()
{
  lat_vm* ret = (lat_vm*)lat_asignar_memoria(sizeof(lat_vm));
  ret->pila = lat_crear_lista();
  ret->all_objects = lat_crear_lista();
  ret->gc_objects = lat_crear_lista();
  ret->modulos = lat_crear_lista();
  ret->memory_usage = 0;
  ret->true_object = lat_logico_nuevo(ret, true);
  ret->false_object = lat_logico_nuevo(ret, false);
  //memset(ret->regs, 0, 256);
  memset(ret->regs, 0, 1024);
  memset(ret->ctx_stack, 0, 256);
  ret->ctx_stack[0] = lat_instancia(ret);
  ret->ctx_stack_pointer = 0;
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "imprimir"), lat_definir_cfuncion(ret, lat_imprimir));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "+"), lat_definir_cfuncion(ret, lat_sumar));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "-"), lat_definir_cfuncion(ret, lat_restar));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "*"), lat_definir_cfuncion(ret, lat_multiplicar));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "/"), lat_definir_cfuncion(ret, lat_dividir));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "%"), lat_definir_cfuncion(ret, lat_modulo));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "!="), lat_definir_cfuncion(ret, lat_diferente));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "=="), lat_definir_cfuncion(ret, lat_igualdad));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "<"), lat_definir_cfuncion(ret, lat_menor_que));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "<="), lat_definir_cfuncion(ret, lat_menor_igual));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, ">"), lat_definir_cfuncion(ret, lat_mayor_que));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, ">="), lat_definir_cfuncion(ret, lat_mayor_igual));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "&&"), lat_definir_cfuncion(ret, lat_y));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "y"), lat_definir_cfuncion(ret, lat_y));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "||"), lat_definir_cfuncion(ret, lat_o));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "o"), lat_definir_cfuncion(ret, lat_o));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "!"), lat_definir_cfuncion(ret, lat_negacion));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "no"), lat_definir_cfuncion(ret, lat_negacion));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "gc"), lat_definir_cfuncion(ret, lat_basurero));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "ejecutar"), lat_definir_cfuncion(ret, lat_ejecutar));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "ejecutar_archivo"), lat_definir_cfuncion(ret, lat_ejecutar_archivo));

  /* funciones matematicas */
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

  /*funciones para cadenas (string)*/
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

  //entrada / salida
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "leer"), lat_definir_cfuncion(ret, lat_leer));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "escribir"), lat_definir_cfuncion(ret, lat_imprimir));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "leer_archivo"), lat_definir_cfuncion(ret, lat_leer_archivo));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "escribir_archivo"), lat_definir_cfuncion(ret, lat_escribir_archivo));

  /*conversion de tipos de dato*/
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "tipo"), lat_definir_cfuncion(ret, lat_tipo));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "logico"), lat_definir_cfuncion(ret, lat_logico));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "entero"), lat_definir_cfuncion(ret, lat_entero));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "decimal"), lat_definir_cfuncion(ret, lat_decimal));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "cadena"), lat_definir_cfuncion(ret, lat_cadena));
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "salir"), lat_definir_cfuncion(ret, lat_salir));

  /*ejemplo de implementacion de una funcion en C */
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "maximo"), lat_definir_cfuncion(ret, lat_maximo));
  /*Creacion dela funcion minimo*/
  lat_asignar_contexto_objeto(lat_obtener_contexto(ret), lat_cadena_nueva(ret, "minimo"), lat_definir_cfuncion(ret, lat_minimo));

  return ret;
}

void lat_apilar(lat_vm* vm, lat_objeto* o)
{
  insert_list(vm->pila, (void*)o);
}

lat_objeto* lat_desapilar(lat_vm* vm)
{
  list_node* n = vm->pila->next;
  if (n->data == NULL) {
    lat_registrar_error("Pila vacia");
  }
  else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    lat_objeto* ret = (lat_objeto*)n->data;
    lat_liberar_memoria(n);
    return ret;
  }
}

void lat_apilar_lista(lat_objeto* list, lat_objeto* o)
{
  insert_list(list->data.list, (void*)o);
}

lat_objeto* lat_desapilar_lista(lat_objeto* list)
{
  list_node* n = ((list_node*)list)->next;
  if (n->data == NULL) {
    lat_registrar_error("Lista vacia");
  }
  else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    lat_objeto* ret = (lat_objeto*)n->data;
    return ret;
  }
}

void lat_apilar_contexto(lat_vm* vm)
{
  if (vm->ctx_stack_pointer >= MAX_STACK_SIZE) {
    lat_registrar_error("Namespace desborde de la pila");
  }
  vm->ctx_stack[vm->ctx_stack_pointer + 1] = lat_clonar_objeto(vm, vm->ctx_stack[vm->ctx_stack_pointer]);
  vm->ctx_stack_pointer++;
}

void lat_desapilar_contexto(lat_vm* vm)
{
  if (vm->ctx_stack_pointer == 0) {
    lat_registrar_error("Namespace pila vacia");
  }
  lat_eliminar_objeto(vm, vm->ctx_stack[vm->ctx_stack_pointer--]);
}

void lat_apilar_contexto_predefinido(lat_vm* vm, lat_objeto* ctx)
{
  if (vm->ctx_stack_pointer >= 255) {
    lat_registrar_error("Namespace desborde de la pila");
  }
  vm->ctx_stack[++vm->ctx_stack_pointer] = ctx;
}

lat_objeto* lat_desapilar_contexto_predefinido(lat_vm* vm)
{
  if (vm->ctx_stack_pointer == 0) {
    lat_registrar_error("Namespace pila vacia");
  }
  return vm->ctx_stack[vm->ctx_stack_pointer--];
}

lat_objeto* lat_obtener_contexto(lat_vm* vm)
{
  return vm->ctx_stack[vm->ctx_stack_pointer];
}

void lat_basurero_agregar(lat_vm* vm, lat_objeto* o)
{
  insert_list(vm->gc_objects, (void*)o);
}

void lat_basurero(lat_vm* vm)
{
  int i = 0;
  for (i = 0; i < 256; i++) {
    if (((lat_objeto*)vm->regs[i]) != 0x0) {
      if (((lat_objeto*)vm->regs[i])->marked != 3) {
        ((lat_objeto*)vm->regs[i])->marked = 2;
      }
    }
  }
  list_node* c;
  lat_objeto* cur;
  for (c = vm->gc_objects->next; c != NULL; c = c->next) {
    if (c->data != NULL) {
      cur = (lat_objeto*)c->data;
      if (cur->marked == 0) {
        lat_eliminar_objeto(vm, cur);
        list_node* prev = c->prev;
        c->prev->next = c->next;
        c->next->prev = c->prev;
        //free(c);
        c = prev;
      }
      else if (cur->marked == 2) {
        cur->marked = 1;
      }
      else if (cur->marked == 1) {
        cur->marked = 0;
      }
    }
    //free(c);
  }
}

lat_objeto* lat_definir_funcion(lat_vm* vm, lat_bytecode* inslist)
{
  lat_objeto* ret = lat_funcion_nueva(vm);
  lat_function* fval = (lat_function*)lat_asignar_memoria(sizeof(lat_function));
  fval->bcode = inslist;
  ret->data.func = fval;
  //vm->memory_usage += sizeof(sizeof(lat_function));
  return ret;
}

lat_objeto* lat_definir_cfuncion(lat_vm* vm, void (*function)(lat_vm* vm))
{
  lat_objeto* ret = lat_cfuncion_nueva(vm);
  ret->data.cfunc = function;
  return ret;
}

void lat_numero_lista(lat_vm* vm)
{
  lat_objeto* index = lat_desapilar(vm);
  long i = lat_obtener_entero(index);
  lat_objeto* list = lat_desapilar(vm);
  list_node* l = list->data.list;
  int counter = 0;
  list_node* c;
  for (c = l->next; c->next != NULL; c = c->next) {
    if (c->data != NULL) {
      if (counter == i) {
        vm->regs[255] = (lat_objeto*)c->data;
        return;
      }
      counter++;
    }
  }
  lat_registrar_error("Lista: indice fuera de rango");
}

static void lat_imprimir_elem(lat_vm* vm)
{
  lat_objeto* in = lat_desapilar(vm);
  if (in->type == T_NULO) {
    fprintf(stdout, "%s", "nulo");
  }
  else if (in->type == T_INSTANCE) {
    fprintf(stdout, "%s", "objeto");
  }
  else if (in->type == T_LIT) {
    fprintf(stdout, "%s", lat_obtener_literal(in));
  }
  else if (in->type == T_INT) {
    fprintf(stdout, "%ld", lat_obtener_entero(in));
  }
  else if (in->type == T_DOUBLE) {
    fprintf(stdout, "%.14g\n", lat_obtener_decimal(in));
  }
  else if (in->type == T_STR) {
    fprintf(stdout, "%s", lat_obtener_cadena(in));
  }
  else if (in->type == T_BOOL) {
    fprintf(stdout, "%i", lat_obtener_logico(in));
  }
  else if (in->type == T_LIST) {
    lat_imprimir_lista(vm, in->data.list);
  }
  else if (in->type == T_DICT) {
    lat_imprimir_diccionario(vm, in->data.dict);
  }
  else if (in->type == T_FUNC) {
    fprintf(stdout, "%s", "Funcion");
  }
  else if (in->type == T_CFUNC) {
    fprintf(stdout, "%s", "C_Funcion");
  }
  else if (in->type == T_STRUCT) {
    fprintf(stdout, "%s", "Struct");
  }
  else {
    fprintf(stdout, "Tipo desconocido %d\n", in->type);
  }
  vm->regs[255] = in;
}

void lat_imprimir(lat_vm* vm)
{
  lat_objeto* in = lat_desapilar(vm);
  if (in->type == T_NULO) {
    fprintf(stdout, "%s\n", "nulo");
  }
  else if (in->type == T_INSTANCE) {
    fprintf(stdout, "%s\n", "Objeto");
  }
  else if (in->type == T_LIT) {
    fprintf(stdout, "%s\n", lat_obtener_literal(in));
  }
  else if (in->type == T_INT) {
    fprintf(stdout, "%ld\n", lat_obtener_entero(in));
  }
  else if (in->type == T_DOUBLE) {
    fprintf(stdout, "%.14g\n", lat_obtener_decimal(in));
  }
  else if (in->type == T_STR) {
    fprintf(stdout, "%s\n", lat_obtener_cadena(in));
  }
  else if (in->type == T_BOOL) {
    if (lat_obtener_logico(in)) {
      fprintf(stdout, "%s\n", "verdadero");
    }
    else {
      fprintf(stdout, "%s\n", "falso");
    }
  }
  else if (in->type == T_LIST) {
    lat_imprimir_lista(vm, in->data.list);
    fprintf(stdout, "%s\n", "");
  }
  else if (in->type == T_FUNC) {
    fprintf(stdout, "%s\n", "Funcion");
  }
  else if (in->type == T_CFUNC) {
    fprintf(stdout, "%s\n", "C_Funcion");
  }
  else if (in->type == T_STRUCT) {
    fprintf(stdout, "%s\n", "Struct");
  }
  else {
    fprintf(stdout, "Tipo desconocido %d\n", in->type);
  }
  vm->regs[255] = in;
}

void lat_imprimir_lista(lat_vm* vm, list_node* l)
{
  fprintf(stdout, "%s", "[ ");
  if (l != NULL && length_list(l) > 0) {
    list_node* c;
    for (c = l->next; c != NULL; c = c->next) {
      if (c->data != NULL) {
        lat_objeto* o = ((lat_objeto*)c->data);
        //printf("\ntype %i, obj_ref: %p\t, marked: %i", o->type, o, o->marked);
        if (o->type == T_LIST) {
          lat_imprimir_lista(vm, o->data.list);
          if (c->next->data) {
            fprintf(stdout, "%s", ", ");
          }
        }
        else {
          if (o->type) {
            lat_apilar(vm, o);
            lat_imprimir_elem(vm);
            if (c->next->data) {
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
  if (d != NULL) {
    list_node* c;
    for (c = d->buckets; c != NULL; c = c->next) {
      if (c->data != NULL) {
        lat_objeto* o = ((lat_objeto*)c->data);
        //printf("\ntype %i, obj_ref: %p\t, marked: %i", o->type, o, o->marked);
        if (o->type == T_LIST) {
          lat_imprimir_lista(vm, o->data.list);
          if (c->next->data) {
            fprintf(stdout, "%s", ", ");
          }
        }
        if (o->type == T_LIST) {
          lat_imprimir_diccionario(vm, o->data.dict);
          if (c->next->data) {
            fprintf(stdout, "%s", ", ");
          }
        }
        else {
          if (o->type) {
            lat_apilar(vm, o);
            lat_imprimir_elem(vm);
            if (c->next->data) {
              fprintf(stdout, "%s", ", ");
            }
          }
        }
      }
    }
  }
  fprintf(stdout, "%s", " ]");
}

void lat_ejecutar(lat_vm *vm) {
  lat_objeto *func = nodo_analizar_arbol(vm, lat_analizar_expresion(vm, lat_obtener_cadena(lat_desapilar(vm))));
  lat_llamar_funcion(vm, func);
  lat_apilar(vm, vm->regs[255]);
}

void lat_ejecutar_archivo(lat_vm *vm) {
  char *input = lat_obtener_cadena(lat_desapilar(vm));
  char *dot = strrchr(input, '.');
  char *extension;
  if (!dot || dot == input) {
    extension = "";
  }else{
    extension = dot + 1;
  }
  if (strcmp(extension, "lat") == 0) {
    ast *tree = lat_analizar_archivo(vm, input);
    if (!tree) {
      lat_registrar_error("error al leer el archivo: %s", input);
    }
    lat_objeto *func = nodo_analizar_arbol(vm, tree);
    lat_llamar_funcion(vm, func);
    lat_apilar(vm, vm->regs[255]);
  }
}

void lat_clonar(lat_vm* vm)
{
  lat_objeto* ns = lat_desapilar(vm);
  vm->regs[255] = lat_clonar_objeto(vm, ns);
}

void lat_cons(lat_vm* vm)
{
  lat_objeto* list = lat_desapilar(vm);
  lat_objeto* elem = lat_desapilar(vm);
  list_node* ret = lat_crear_lista();
  insert_list(ret, (void*)elem);
  ret->next->next = list->data.list;
  list->data.list->prev = ret->next;
  vm->regs[255] = lat_lista_nueva(vm, ret);
}

void lat_sumar(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    lat_registrar_error("Intento de aplicar operador \"+\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = lat_decimal_nuevo(vm, lat_obtener_decimal(a) + lat_obtener_decimal(b));
  }
  else {
    vm->regs[255] = lat_entero_nuevo(vm, lat_obtener_entero(a) + lat_obtener_entero(b));
  }
}

void lat_restar(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    lat_registrar_error("Intento de aplicar operador \"-\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = lat_decimal_nuevo(vm, lat_obtener_decimal(a) - lat_obtener_decimal(b));
  }
  else {
    vm->regs[255] = lat_entero_nuevo(vm, lat_obtener_entero(a) - lat_obtener_entero(b));
  }
}

void lat_multiplicar(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    lat_registrar_error("Intento de aplicar operador \"*\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = lat_decimal_nuevo(vm, lat_obtener_decimal(a) * lat_obtener_decimal(b));
  }
  else {
    vm->regs[255] = lat_entero_nuevo(vm, lat_obtener_entero(a) * lat_obtener_entero(b));
  }
}

void lat_dividir(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    lat_registrar_error("Intento de aplicar operador \"/\" en tipos invalidos");
  }
  if ((a->type == T_DOUBLE && b->type == T_DOUBLE) || (a->type == T_INT && b->type == T_DOUBLE)) {
    double tmp = lat_obtener_decimal(b);
    if (tmp == 0) {
      lat_registrar_error("Division por cero");
    }
    else {
      vm->regs[255] = lat_decimal_nuevo(vm, (lat_obtener_decimal(a) / tmp));
    }
  }
  else {
    int tmp = lat_obtener_entero(b);
    if (tmp == 0) {
      lat_registrar_error("Division por cero");
    }
    else {
      if (a->type == T_DOUBLE) {
        vm->regs[255] = lat_decimal_nuevo(vm, (lat_obtener_decimal(a) / tmp));
      }
      else {
        vm->regs[255] = lat_decimal_nuevo(vm, (lat_obtener_entero(a) / tmp));
      }
    }
  }
}

void lat_modulo(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if (a->type != T_INT || b->type != T_INT) {
    lat_registrar_error("Intento de aplicar operador \"%%\" en tipos invalidos");
  }
  int tmp = lat_obtener_entero(b);
  if (tmp == 0) {
    lat_registrar_error("Modulo por cero");
  }
  else {
    vm->regs[255] = lat_entero_nuevo(vm, (lat_obtener_entero(a) % tmp));
  }
}

void lat_diferente(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if (a->type == T_BOOL && b->type == T_BOOL) {
    vm->regs[255] = lat_obtener_logico(a) != lat_obtener_logico(b) ? vm->true_object : vm->false_object;
    return;
  }
  if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE)) {
    vm->regs[255] = (lat_obtener_decimal(a) != lat_obtener_decimal(b)) ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_STR && b->type == T_STR) {
    vm->regs[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) != 0 ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_LIT && b->type == T_LIT) {
    vm->regs[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) != 0 ? vm->true_object : vm->false_object;
    return;
  }
  vm->regs[255] = vm->false_object;
}

void lat_igualdad(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if (a->type == T_BOOL && b->type == T_BOOL) {
    vm->regs[255] = lat_obtener_logico(a) == lat_obtener_logico(b) ? vm->true_object : vm->false_object;
    return;
  }
  if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE)) {
    vm->regs[255] = (lat_obtener_decimal(a) == lat_obtener_decimal(b)) ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_STR && b->type == T_STR) {
    vm->regs[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) == 0 ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_LIT && b->type == T_LIT) {
    vm->regs[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) == 0 ? vm->true_object : vm->false_object;
    return;
  }
  vm->regs[255] = vm->false_object;
}

void lat_menor_que(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE)) {
    vm->regs[255] = (lat_obtener_decimal(a) < lat_obtener_decimal(b)) ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_STR && b->type == T_STR) {
    vm->regs[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) < 0 ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_LIT && b->type == T_LIT) {
    vm->regs[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) < 0 ? vm->true_object : vm->false_object;
    return;
  }
  lat_registrar_error("Intento de aplicar operador \"<\" en tipos invalidos");
}

void lat_menor_igual(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE)) {
    vm->regs[255] = (lat_obtener_decimal(a) <= lat_obtener_decimal(b)) ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_STR && b->type == T_STR) {
    vm->regs[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) <= 0 ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_LIT && b->type == T_LIT) {
    vm->regs[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) <= 0 ? vm->true_object : vm->false_object;
    return;
  }
  lat_registrar_error("Intento de aplicar operador \"<=\" en tipos invalidos");
}

void lat_mayor_que(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE)) {
    vm->regs[255] = (lat_obtener_decimal(a) > lat_obtener_decimal(b)) ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_STR && b->type == T_STR) {
    vm->regs[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) > 0 ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_LIT && b->type == T_LIT) {
    vm->regs[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) > 0 ? vm->true_object : vm->false_object;
    return;
  }
  lat_registrar_error("Intento de aplicar operador \">\" en tipos invalidos");
}

void lat_mayor_igual(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((a->type == T_INT || a->type == T_DOUBLE) && (b->type == T_INT || b->type == T_DOUBLE)) {
    vm->regs[255] = (lat_obtener_decimal(a) >= lat_obtener_decimal(b)) ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_STR && b->type == T_STR) {
    vm->regs[255] = strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) >= 0 ? vm->true_object : vm->false_object;
    return;
  }
  if (a->type == T_LIT && b->type == T_LIT) {
    vm->regs[255] = strcmp(lat_obtener_literal(a), lat_obtener_literal(b)) >= 0 ? vm->true_object : vm->false_object;
    return;
  }
  lat_registrar_error("Intento de aplicar operador \">=\" en tipos invalidos");
}

void lat_y(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((b->type != T_BOOL && b->type != T_INT) || (a->type != T_BOOL && a->type != T_INT)) {
    lat_registrar_error("Intento de aplicar operador \"y\" en tipos invalidos");
  }
  vm->regs[255] =  (lat_obtener_logico(a) && lat_obtener_logico(b)) == true ? vm->true_object : vm->false_object;
}

void lat_o(lat_vm* vm)
{
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if ((b->type != T_BOOL && b->type != T_INT) || (a->type != T_BOOL && a->type != T_INT)) {
    lat_registrar_error("Intento de aplicar operador \"y\" en tipos invalidos");
  }
  vm->regs[255] =  (lat_obtener_logico(a) || lat_obtener_logico(b)) == true ? vm->true_object : vm->false_object;
}

void lat_negacion(lat_vm* vm)
{
  lat_objeto* o = lat_desapilar(vm);
  if (o->type != T_BOOL && o->type != T_INT) {
    lat_registrar_error("Intento de negar tipo invalido");
  }
  vm->regs[255] =  lat_obtener_logico(o) == true ? vm->false_object : vm->true_object;
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

void lista_modificar_elemento(list_node* l, void* data, int pos){
  list_node* c;
  int i = -1;
  if(pos < 0 || pos >= length_list(l)){
    lat_registrar_error("Indice fuera de rango");
  }
  for (c = l; c->next != NULL; c = c->next) {
    if(i == pos) {
        c->data = data;
        return;
    }
    i++;
  }
}

lat_objeto* lista_obtener_elemento(list_node* l, int pos){
  list_node* c;
  int i = -1;
  if(pos < 0 || pos >= length_list(l)){
    lat_registrar_error("Indice fuera de rango");
  }
  for (c = l; c->next != NULL; c = c->next) {
    if(i == pos) {
        return (lat_objeto *)c->data;
    }
    i++;
  }
}

void lat_llamar_funcion(lat_vm* vm, lat_objeto* func)
{
  if (func->type == T_FUNC) {
    lat_apilar_contexto(vm);
    lat_asignar_contexto_objeto(lat_obtener_contexto(vm), lat_cadena_nueva(vm, "$"), func);
    lat_bytecode* inslist = ((lat_function*)func->data.func)->bcode;
    lat_bytecode cur;
    int pos;
    for (pos = 0, cur = inslist[pos]; cur.ins != OP_END; cur = inslist[++pos]) {
      switch (cur.ins) {
      case OP_END:
        return;
        break;
      case OP_NOP:
        break;
      case OP_PUSH:
        lat_apilar(vm, vm->regs[cur.a]);
        break;
      case OP_POP:
        vm->regs[cur.a] = lat_desapilar(vm);
        break;
      case OP_GET:
        vm->regs[cur.a] = lat_lat_obtener_contexto_objeto(vm->regs[cur.b], vm->regs[cur.a]);
        break;
      case OP_SET:
        lat_asignar_contexto_objeto(vm->regs[cur.b], lat_clonar_objeto(vm, ((lat_objeto*)cur.meta)), vm->regs[cur.a]);
        break;
      case OP_STORELIT:
        vm->regs[cur.a] = ((lat_objeto*)cur.meta);
        break;
      case OP_STOREINT: {
        vm->regs[cur.a] = ((lat_objeto*)cur.meta);
      } break;
      case OP_STOREDOUBLE:
        vm->regs[cur.a] = ((lat_objeto*)cur.meta);
        break;
      case OP_STORESTR: {
        vm->regs[cur.a] = ((lat_objeto*)cur.meta);
      } break;
      case OP_STOREBOOL:
        vm->regs[cur.a] = ((lat_objeto*)cur.meta);
        break;
      case OP_STORELIST:
        vm->regs[cur.a] = lat_lista_nueva(vm, lat_crear_lista());
        break;
      case OP_PUSHLIST:
        lat_apilar_lista(vm->regs[cur.a], vm->regs[cur.b]);
        break;
      case OP_POPLIST:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_desapilar_lista(vm->regs[cur.b]);
        break;
      case OP_LISTGETITEM:{
        lat_objeto *l = vm->regs[cur.a];
        lat_objeto *pos = vm->regs[cur.b];
        vm->regs[cur.a] = lista_obtener_elemento(l->data.list, pos->data.i);
      }
      break;
      case OP_LISTSETITEM:{
        lat_objeto *l = vm->regs[cur.a];
        lat_objeto *pos = vm->regs[(int)cur.meta];
        if(pos->type != T_INT){
          lat_registrar_error("%s", "la posicion de la lista no es un entero");
        }
        lista_modificar_elemento(l->data.list, (lat_objeto*)vm->regs[cur.b], pos->data.i);
        }
        break;
      case OP_STOREDICT:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_lista_nueva(vm, make_dict());
        break;
      case OP_PUSHDICT:
        //TODO: Pendiente
        //lat_push_dict(vm->regs[cur.a], vm->regs[cur.b]);
        break;
      case OP_POPDICT:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_pop_dict(vm->regs[cur.b]);
        break;
      case OP_MOV:
        vm->regs[cur.a] = vm->regs[cur.b];
        break;
      case OP_GLOBALNS:
        vm->regs[cur.a] = vm->ctx_stack[0];
        break;
      case OP_LOCALNS:
        vm->regs[cur.a] = lat_obtener_contexto(vm);
        break;
      case OP_FN:
        vm->regs[cur.a] = lat_definir_funcion(vm, (lat_bytecode*)cur.meta);
        break;
      case OP_NS:
        vm->regs[cur.a] = lat_clonar_objeto(vm, lat_obtener_contexto(vm));
        lat_apilar_contexto_predefinido(vm, vm->regs[cur.a]);
        break;
      case OP_ENDNS:
        vm->regs[cur.a] = lat_desapilar_contexto_predefinido(vm);
        break;
      case OP_JMP:
        pos = cur.a - 1;
        break;
      case OP_JMPIF:
        if (lat_obtener_logico(vm->regs[cur.b])) {
          pos = cur.a - 1;
        }
        break;
      case OP_CALL:
        lat_llamar_funcion(vm, vm->regs[cur.a]);
        break;
      case OP_NOT:
        vm->regs[cur.a] = lat_obtener_logico(vm->regs[cur.a]) == true ? vm->false_object : vm->true_object;
        break;
      case OP_INC:
        ((lat_objeto*)vm->regs[cur.a])->data.i++;
        break;
      case OP_DEC:
        ((lat_objeto*)vm->regs[cur.a])->data.i--;
        break;
      }
    }
    lat_desapilar_contexto(vm);
  }
  else if (func->type == T_CFUNC) {
    ((void (*)(lat_vm*))(func->data.func))(vm);
  }
  else {
    debug("func->type: %d", func->type);
    lat_registrar_error("Object not a function");
  }
}


void lat_logico(lat_vm* vm){
  lat_objeto* a = lat_desapilar(vm);
  switch (a->type) {
    case T_INT:
    if(a->data.i == 0){
      vm->regs[255] = vm->false_object;
    }else{
      vm->regs[255] = vm->true_object;
    }
    break;
    case T_LIT:
    if(strcmp(a->data.c, "") == 0){
      vm->regs[255] = vm->false_object;
    }else{
      vm->regs[255] = vm->true_object;
    }
    break;
    case T_DOUBLE:
    if((int)a->data.d == 0){
      vm->regs[255] = vm->false_object;
    }else{
      vm->regs[255] = vm->true_object;
    }
    break;
    case T_STR:
    if(strcmp(a->data.str, "") == 0){
      vm->regs[255] = vm->false_object;
    }else{
      vm->regs[255] = vm->true_object;
    }
    break;
    default:
    lat_registrar_error("conversion incompatible");
    break;
  }
}
void lat_entero(lat_vm* vm){
  lat_objeto* a = lat_desapilar(vm);
  switch (a->type) {
    case T_BOOL:
    if(a->data.b == false){
      vm->regs[255] = lat_entero_nuevo(vm, 0);
    }else{
      vm->regs[255] = lat_entero_nuevo(vm, 1);
    }
    break;
    case T_LIT:{
        char *ptr;
        long ret;
        ret =strtol(a->data.c, &ptr, 10);
        if(strcmp(ptr, "") == 0){
          vm->regs[255] = lat_entero_nuevo(vm, ret);
        }else{
          lat_registrar_error("conversion incompatible");
        }
    }
    break;
    case T_DOUBLE:
      vm->regs[255] = lat_entero_nuevo(vm, (int)a->data.d);
    break;
    case T_STR:{
      char *ptr;
      long ret;
      ret =strtol(a->data.str, &ptr, 10);
      if(strcmp(ptr, "") == 0){
        vm->regs[255] = lat_entero_nuevo(vm, ret);
      }else{
        lat_registrar_error("conversion incompatible");
      }
    }
    break;
    default:
    lat_registrar_error("conversion incompatible");
    break;
  }
}
void lat_literal(lat_vm* vm){
  lat_objeto* a = lat_desapilar(vm);
  switch (a->type) {
    case T_BOOL:
    if(a->data.b == false){
      vm->regs[255] = lat_literal_nuevo(vm, "falso");
    }else{
      vm->regs[255] = lat_literal_nuevo(vm, "verdadero");
    }
    break;
   case T_STR:{
      vm->regs[255] = a;
    }
    break;
    default:
    lat_registrar_error("conversion incompatible");
    break;
  }
}
void lat_decimal(lat_vm* vm){
  lat_objeto* a = lat_desapilar(vm);
  switch (a->type) {
    case T_BOOL:
    if(a->data.b == false){
      vm->regs[255] = lat_decimal_nuevo(vm, 0);
    }else{
      vm->regs[255] = lat_decimal_nuevo(vm, 1);
    }
    break;
    case T_INT:
      vm->regs[255] = lat_decimal_nuevo(vm, (double)a->data.i);
    break;
    case T_DOUBLE:
      vm->regs[255] = lat_decimal_nuevo(vm, (double)a->data.i);
    break;
    case T_STR:{
      char *ptr;
      double ret;
      ret =strtod(a->data.str, &ptr);
      if(strcmp(ptr, "") == 0){
        vm->regs[255] = lat_decimal_nuevo(vm, ret);
      }else{
        lat_registrar_error("conversion incompatible");
      }
    }
    break;
    default:
    lat_registrar_error("conversion incompatible");
    break;
  }
}

void lat_cadena(lat_vm* vm){
  lat_objeto* a = lat_desapilar(vm);
  switch (a->type) {
    case T_BOOL:
      vm->regs[255] = lat_cadena_nueva(vm, bool2str(a->data.b));
    break;
    case T_INT:
      vm->regs[255] = lat_cadena_nueva(vm, int2str(a->data.i));
    break;
    case T_DOUBLE:
      vm->regs[255] = lat_cadena_nueva(vm, double2str(a->data.d));
    break;
    default:
    vm->regs[255] = a;
    break;
  }
}

void lat_maximo(lat_vm* vm){
  lat_objeto* b = lat_desapilar(vm);
  lat_objeto* a = lat_desapilar(vm);
  if(lat_obtener_entero(b) > lat_obtener_entero(a)){
    vm->regs[255] = b;
  }else{
    vm->regs[255] = a;
  }
}

void lat_minimo(lat_vm* vm){
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(lat_obtener_entero(b) < lat_obtener_entero(a)) {
        vm->regs[255] = b;
    }else{
        vm->regs[255] = a;
    }
}

void lat_tipo(lat_vm* vm){
  lat_objeto* a = lat_desapilar(vm);
  switch (a->type) {
    case T_BOOL:
      vm->regs[255] = lat_cadena_nueva(vm, "logico");
      break;
    case T_INT:
      vm->regs[255] = lat_cadena_nueva(vm, "entero");
      break;
    case T_DOUBLE:
      vm->regs[255] = lat_cadena_nueva(vm, "decimal");
      break;
    case T_STR:
      vm->regs[255] = lat_cadena_nueva(vm, "cadena");
      break;
    case T_LIT:
        vm->regs[255] = lat_cadena_nueva(vm, "cadena");
        break;
    case T_LIST:
      vm->regs[255] = lat_cadena_nueva(vm, "lista");
      break;
    case T_DICT:
      vm->regs[255] = lat_cadena_nueva(vm, "diccionario");
      break;
    default:
      vm->regs[255] = lat_cadena_nueva(vm, "nulo");
      break;
  }
}

void lat_salir(lat_vm* vm){
  vm->regs[255] = lat_entero_nuevo(vm, 0L);
  exit(0);
}
