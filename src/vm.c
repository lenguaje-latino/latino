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

lat_vm* lat_make_vm()
{
  lat_vm* ret = (lat_vm*)lmalloc(sizeof(lat_vm));
  ret->stack = make_list();
  ret->all_objects = make_list();
  ret->gc_objects = make_list();
  ret->memory_usage = 0;
  ret->true_object = lat_bool(ret, true);
  ret->false_object = lat_bool(ret, false);
  //memset(ret->regs, 0, 256);
  memset(ret->regs, 0, 1024);
  memset(ret->ctx_stack, 0, 256);
  ret->ctx_stack[0] = lat_instance(ret);
  ret->ctx_stack_pointer = 0;
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "imprimir"), definir_funcion_c(ret, lat_print));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "+"), definir_funcion_c(ret, lat_add));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "-"), definir_funcion_c(ret, lat_sub));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "*"), definir_funcion_c(ret, lat_mul));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "/"), definir_funcion_c(ret, lat_div));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "%"), definir_funcion_c(ret, lat_mod));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "!="), definir_funcion_c(ret, lat_neq));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "=="), definir_funcion_c(ret, lat_eq));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "<"), definir_funcion_c(ret, lat_lt));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "<="), definir_funcion_c(ret, lat_lte));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, ">"), definir_funcion_c(ret, lat_gt));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, ">="), definir_funcion_c(ret, lat_gte));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "gc"), definir_funcion_c(ret, lat_gc));

  /* funciones matematicas */
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "arco_coseno"), definir_funcion_c(ret, lat_acos));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "arco_seno"), definir_funcion_c(ret, lat_asin));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "arco_tangente"), definir_funcion_c(ret, lat_atan));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "arco_tangente_radianes"), definir_funcion_c(ret, lat_atan2));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "coseno"), definir_funcion_c(ret, lat_cos));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "coseno_hiperbolico"), definir_funcion_c(ret, lat_cosh));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "seno"), definir_funcion_c(ret, lat_sin));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "seno_hiperbolico"), definir_funcion_c(ret, lat_sinh));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "tangente"), definir_funcion_c(ret, lat_tan));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "tangente_hiperbolica"), definir_funcion_c(ret, lat_tanh));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "exponente"), definir_funcion_c(ret, lat_exp));
  //asignar_contexto(obtener_contexto(ret), lat_str(ret, "frexp"), definir_funcion_c(ret, lat_frexp));
  //asignar_contexto(obtener_contexto(ret), lat_str(ret, "ldexp"), definir_funcion_c(ret, lat_ldexp));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "logaritmo_natural"), definir_funcion_c(ret, lat_log));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "logaritmo_base10"), definir_funcion_c(ret, lat_log10));
  //asignar_contexto(obtener_contexto(ret), lat_str(ret, "modf"), definir_funcion_c(ret, lat_modf));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "potencia"), definir_funcion_c(ret, lat_pow));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "raiz_cuadrada"), definir_funcion_c(ret, lat_sqrt));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "redondear_arriba"), definir_funcion_c(ret, lat_ceil));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "valor_absoluto"), definir_funcion_c(ret, lat_fabs));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "redondear_abajo"), definir_funcion_c(ret, lat_floor));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "modulo"), definir_funcion_c(ret, lat_fmod));

  /*funciones para cadenas (string)*/
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "comparar"), definir_funcion_c(ret, lat_compare));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "concatenar"), definir_funcion_c(ret, lat_concat));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "contiene"), definir_funcion_c(ret, lat_contains));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "copiar"), definir_funcion_c(ret, lat_copy));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "termina_con"), definir_funcion_c(ret, lat_endsWith));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "es_igual"), definir_funcion_c(ret, lat_equals));
  //TODO: Pendiente
  //asignar_contexto(obtener_contexto(ret), lat_str(ret, "formato"), definir_funcion_c(ret, lat_format));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "indice"), definir_funcion_c(ret, lat_indexOf));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "insertar"), definir_funcion_c(ret, lat_insert));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "ultimo_indice"), definir_funcion_c(ret, lat_lastIndexOf));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "rellenar_izquierda"), definir_funcion_c(ret, lat_padLeft));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "rellenar_derecha"), definir_funcion_c(ret, lat_padRight));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "eliminar"), definir_funcion_c(ret, lat_remove));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "es_vacia"), definir_funcion_c(ret, lat_isEmpty));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "longitud"), definir_funcion_c(ret, lat_length));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "reemplazar"), definir_funcion_c(ret, lat_replace));
  //TODO: Pendiente, se implementara cuando se implementen Listas
  //asignar_contexto(obtener_contexto(ret), lat_str(ret, "partir"), definir_funcion_c(ret, lat_split));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "empieza_con"), definir_funcion_c(ret, lat_startsWith));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "subcadena"), definir_funcion_c(ret, lat_substring));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "minusculas"), definir_funcion_c(ret, lat_toLower));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "mayusculas"), definir_funcion_c(ret, lat_toUpper));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "quitar_espacios"), definir_funcion_c(ret, lat_trim));

  //entrada / salida
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "leer"), definir_funcion_c(ret, lat_read));
  asignar_contexto(obtener_contexto(ret), lat_str(ret, "escribir"), definir_funcion_c(ret, lat_print));
  return ret;
}

void lat_push_stack(lat_vm* vm, lat_object* o)
{
  insert_list(vm->stack, (void*)o);
}

lat_object* lat_pop_stack(lat_vm* vm)
{
  list_node* n = vm->stack->next;
  if (n->data == NULL) {
    log_err("Pila vacia");
  }
  else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    lat_object* ret = (lat_object*)n->data;
    lfree(n);
    return ret;
  }
}

void lat_push_list(lat_object* list, lat_object* o)
{
  insert_list(list->data.list, (void*)o);
}

lat_object* lat_pop_list(lat_object* list)
{
  list_node* n = ((list_node*)list)->next;
  if (n->data == NULL) {
    log_err("Lista vacia");
  }
  else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    lat_object* ret = (lat_object*)n->data;
    return ret;
  }
}

void lat_push_ctx(lat_vm* vm)
{
  if (vm->ctx_stack_pointer >= 255) {
    log_err("Namespace desborde de la pila");
  }
  vm->ctx_stack[vm->ctx_stack_pointer + 1] = lat_clone_object(vm, vm->ctx_stack[vm->ctx_stack_pointer]);
  vm->ctx_stack_pointer++;
}

void lat_pop_ctx(lat_vm* vm)
{
  if (vm->ctx_stack_pointer == 0) {
    log_err("Namespace pila vacia");
  }
  lat_delete_object(vm, vm->ctx_stack[vm->ctx_stack_pointer--]);
}

void lat_push_predefined_ctx(lat_vm* vm, lat_object* ctx)
{
  if (vm->ctx_stack_pointer >= 255) {
    log_err("Namespace desborde de la pila");
  }
  vm->ctx_stack[++vm->ctx_stack_pointer] = ctx;
}

lat_object* lat_pop_predefined_ctx(lat_vm* vm)
{
  if (vm->ctx_stack_pointer == 0) {
    log_err("Namespace pila vacia");
  }
  return vm->ctx_stack[vm->ctx_stack_pointer--];
}

lat_object* obtener_contexto(lat_vm* vm)
{
  return vm->ctx_stack[vm->ctx_stack_pointer];
}

void lat_gc_add_object(lat_vm* vm, lat_object* o)
{
  insert_list(vm->gc_objects, (void*)o);
}

void lat_gc(lat_vm* vm)
{
  for (size_t i = 0; i < 256; i++) {
    if (((lat_object*)vm->regs[i]) != 0x0) {
      if (((lat_object*)vm->regs[i])->marked != 3) {
        ((lat_object*)vm->regs[i])->marked = 2;
      }
    }
  }
  list_node* c;
  lat_object* cur;
  for (c = vm->gc_objects->next; c != NULL; c = c->next) {
    if (c->data != NULL) {
      cur = (lat_object*)c->data;
      if (cur->marked == 0) {
        lat_delete_object(vm, cur);
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

lat_object* definir_funcion(lat_vm* vm, lat_bytecode* inslist)
{
  lat_object* ret = lat_func(vm);
  lat_function* fval = (lat_function*)lmalloc(sizeof(lat_function));
  fval->bcode = inslist;
  ret->data.func = fval;
  //vm->memory_usage += sizeof(sizeof(lat_function));
  return ret;
}

lat_object* definir_funcion_c(lat_vm* vm, void (*function)(lat_vm* vm))
{
  lat_object* ret = lat_cfunc(vm);
  ret->data.cfunc = function;
  return ret;
}

void lat_nth_list(lat_vm* vm)
{
  lat_object* index = lat_pop_stack(vm);
  long i = lat_get_int_value(index);
  lat_object* list = lat_pop_stack(vm);
  list_node* l = list->data.list;
  int counter = 0;
  list_node* c;
  for (c = l->next; c->next != NULL; c = c->next) {
    if (c->data != NULL) {
      if (counter == i) {
        vm->regs[255] = (lat_object*)c->data;
        return;
      }
      counter++;
    }
  }
  log_err("Lista: indice fuera de rango");
}

static void lat_print_elem(lat_vm* vm)
{
  lat_object* in = lat_pop_stack(vm);
  if (in->type == T_NULL) {
    fprintf(stdout, "%s", "nulo");
  }
  else if (in->type == T_INSTANCE) {
    fprintf(stdout, "%s", "Objeto");
  }
  else if (in->type == T_CHAR) {
    fprintf(stdout, "%c", lat_get_char_value(in));
  }
  else if (in->type == T_INT) {
    fprintf(stdout, "%ld", lat_get_int_value(in));
  }
  else if (in->type == T_DOUBLE) {
    fprintf(stdout, "%.14g\n", lat_get_double_value(in));
  }
  else if (in->type == T_STR) {
    fprintf(stdout, "%s", lat_get_str_value(in));
  }
  else if (in->type == T_BOOL) {
    fprintf(stdout, "%i", lat_get_bool_value(in));
  }
  else if (in->type == T_LIST) {
    lat_print_list(vm, in->data.list);
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

void lat_print(lat_vm* vm)
{
  lat_object* in = lat_pop_stack(vm);
  if (in->type == T_NULL) {
    fprintf(stdout, "%s\n", "nulo");
  }
  else if (in->type == T_INSTANCE) {
    fprintf(stdout, "%s\n", "Objeto");
  }
  else if (in->type == T_CHAR) {
    fprintf(stdout, "%c\n", lat_get_char_value(in));
  }
  else if (in->type == T_INT) {
    fprintf(stdout, "%ld\n", lat_get_int_value(in));
  }
  else if (in->type == T_DOUBLE) {
    //fprintf(stdout, "%lf\n", lat_get_double_value(in));
    fprintf(stdout, "%.14g\n", lat_get_double_value(in));
  }
  else if (in->type == T_STR) {
    //fprintf(stdout, "%s\n", lat_get_str_value(in));
    fprintf(stdout, "%s\n", lat_get_str_value(in));
  }
  else if (in->type == T_BOOL) {
    if (lat_get_bool_value(in)) {
      fprintf(stdout, "%s\n", "verdadero");
    }
    else {
      fprintf(stdout, "%s\n", "falso");
    }
  }
  else if (in->type == T_LIST) {
    lat_print_list(vm, in->data.list);
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

void lat_print_list(lat_vm* vm, list_node* l)
{
  fprintf(stdout, "%s", "[ ");
  if (l != NULL && length_list(l) > 0) {
    list_node* c;
    for (c = l->next; c != NULL; c = c->next) {
      if (c->data != NULL) {
        lat_object* o = ((lat_object*)c->data);
        //printf("\ntype %i, obj_ref: %p\t, marked: %i", o->type, o, o->marked);
        if (o->type == T_LIST) {
          lat_print_list(vm, o->data.list);
          if (c->next->data) {
            fprintf(stdout, "%s", ", ");
          }
        }
        else {
          if (o->type) {
            lat_push_stack(vm, o);
            lat_print_elem(vm);
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

void lat_clone(lat_vm* vm)
{
  lat_object* ns = lat_pop_stack(vm);
  vm->regs[255] = lat_clone_object(vm, ns);
}

void lat_cons(lat_vm* vm)
{
  lat_object* list = lat_pop_stack(vm);
  lat_object* elem = lat_pop_stack(vm);
  list_node* ret = make_list();
  insert_list(ret, (void*)elem);
  ret->next->next = list->data.list;
  list->data.list->prev = ret->next;
  vm->regs[255] = lat_list(vm, ret);
}

void lat_add(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  switch (a->type) {
  case T_BOOL: {
    if (b->type == T_STR) {
      vm->regs[255] = lat_str(vm, concat(bool2str(a->data.b), b->data.str));
      return;
    }
  } break;
  case T_INT: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_int(vm, lat_get_int_value(a) + lat_get_int_value(b));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_double(vm, lat_get_int_value(a) + lat_get_double_value(b));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_int(vm, lat_get_int_value(a) + lat_get_char_value(b));
      return;
    }
    if (b->type == T_STR) {
      vm->regs[255] = lat_str(vm, concat(int2str(lat_get_int_value(a)), lat_get_str_value(b)));
      return;
    }
  } break;
  case T_CHAR: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_char(vm, (lat_get_char_value(a)) + lat_get_int_value(b));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_char(vm, lat_get_char_value(a) + lat_get_char_value(b));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_double(vm, ((int)lat_get_char_value(a)) + lat_get_double_value(b));
      return;
    }
    if (b->type == T_STR) {
      vm->regs[255] = lat_str(vm, concat(char2str(lat_get_char_value(a)), lat_get_str_value(b)));
      return;
    }
  } break;
  case T_DOUBLE: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_double(vm, lat_get_double_value(a) + lat_get_int_value(b));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_double(vm, lat_get_double_value(a) + ((int)lat_get_char_value(b)));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_double(vm, lat_get_double_value(a) + lat_get_double_value(b));
      return;
    }
    if (b->type == T_STR) {
      vm->regs[255] = lat_str(vm, concat(double2str(lat_get_double_value(a)), lat_get_str_value(b)));
      return;
    }
  } break;
  case T_STR: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_str(vm, concat(lat_get_str_value(a), int2str(lat_get_int_value(b))));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_str(vm, concat(lat_get_str_value(a), double2str(lat_get_double_value(b))));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_str(vm, concat(lat_get_str_value(a), char2str(lat_get_char_value(b))));
      return;
    }
    if (b->type == T_STR) {
      vm->regs[255] = lat_str(vm, concat(lat_get_str_value(a), lat_get_str_value(b)));
      return;
    }
  } break;
  default:
  break;
  }
  log_err("Intento de aplicar operador \"+\" en tipos invalidos");
}

void lat_sub(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  switch (a->type) {
  case T_INT: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_int(vm, lat_get_int_value(a) - lat_get_int_value(b));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_double(vm, lat_get_int_value(a) - lat_get_double_value(b));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_int(vm, lat_get_int_value(a) - lat_get_char_value(b));
      return;
    }
  } break;
  case T_CHAR: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_char(vm, (lat_get_char_value(a)) - lat_get_int_value(b));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_char(vm, lat_get_char_value(a) - lat_get_char_value(b));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_double(vm, ((int)lat_get_char_value(a)) - lat_get_double_value(b));
      return;
    }
  } break;
  case T_DOUBLE: {
    if (b->type == T_INT) {
      vm->regs[255] = lat_double(vm, lat_get_double_value(a) - lat_get_int_value(b));
      return;
    }
    if (b->type == T_CHAR) {
      vm->regs[255] = lat_double(vm, lat_get_double_value(a) - ((int)lat_get_char_value(b)));
      return;
    }
    if (b->type == T_DOUBLE) {
      vm->regs[255] = lat_double(vm, lat_get_double_value(a) - lat_get_double_value(b));
      return;
    }
  } break;
  default:
  break;
  }
  log_err("Intento de aplicar operador \"-\" en tipos invalidos");
}

void lat_mul(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \"*\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = lat_double(vm, lat_get_double_value(a) * lat_get_double_value(b));
  }
  else {
    vm->regs[255] = lat_int(vm, lat_get_int_value(a) * lat_get_int_value(b));
  }
}

void lat_div(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \"/\" en tipos invalidos");
  }
  if ((a->type == T_DOUBLE && b->type == T_DOUBLE) || (a->type == T_INT && b->type == T_DOUBLE)) {
    double tmp = lat_get_double_value(b);
    if (tmp == 0) {
      log_err("Division por cero");
    }
    else {
      vm->regs[255] = lat_double(vm, (lat_get_double_value(a) / tmp));
    }
  }
  else {
    int tmp = lat_get_int_value(b);
    if (tmp == 0) {
      log_err("Division por cero");
    }
    else {
      if (a->type == T_DOUBLE) {
        vm->regs[255] = lat_int(vm, ((int)(lat_get_double_value(a) / tmp)));
      }
      else {
        vm->regs[255] = lat_int(vm, ((int)(lat_get_int_value(a) / tmp)));
      }
    }
  }
}

void lat_mod(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if (a->type != T_INT || b->type != T_INT) {
    log_err("Intento de aplicar operador \"%%\" en tipos invalidos");
  }
  int tmp = lat_get_int_value(b);
  if (tmp == 0) {
    log_err("Modulo por cero");
  }
  else {
    vm->regs[255] = lat_int(vm, (lat_get_int_value(a) % tmp));
  }
}

void lat_neq(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \"!=\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = (lat_get_double_value(a) != lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (lat_get_int_value(a) != lat_get_int_value(b)) ? vm->true_object : vm->false_object;
  }
}

void lat_eq(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \"==\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = (lat_get_double_value(a) == lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (lat_get_int_value(a) == lat_get_int_value(b)) ? vm->true_object : vm->false_object;
  }
}

void lat_lt(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \"<\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = (lat_get_double_value(a) < lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (lat_get_int_value(a) < lat_get_int_value(b)) ? vm->true_object : vm->false_object;
  }
}

void lat_lte(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \"<=\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = (lat_get_double_value(a) <= lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (lat_get_int_value(a) <= lat_get_int_value(b)) ? vm->true_object : vm->false_object;
  }
}

void lat_gt(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \">\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = (lat_get_double_value(a) > lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (lat_get_int_value(a) > lat_get_int_value(b)) ? vm->true_object : vm->false_object;
  }
}

void lat_gte(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if ((a->type != T_INT && a->type != T_DOUBLE) || (b->type != T_INT && b->type != T_DOUBLE)) {
    log_err("Intento de aplicar operador \">=\" en tipos invalidos");
  }
  if (a->type == T_DOUBLE || b->type == T_DOUBLE) {
    vm->regs[255] = (lat_get_double_value(a) >= lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (lat_get_int_value(a) >= lat_get_int_value(b)) ? vm->true_object : vm->false_object;
  }
}

lat_object* lat_not(lat_vm* vm, lat_object* o)
{
  if (o->type != T_BOOL && o->type != T_INT) {
    log_err("Intento de negar tipo invalido");
  }
  return lat_get_bool_value(o) ? vm->false_object : vm->true_object;
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

void lat_call_func(lat_vm* vm, lat_object* func)
{
  if (func->type == T_FUNC) {
    lat_push_ctx(vm);
    asignar_contexto(obtener_contexto(vm), lat_str(vm, "$"), func);
    lat_bytecode* inslist = ((lat_function*)func->data.func)->bcode;
    lat_bytecode cur;
    int pos;
    for (pos = 0, cur = inslist[pos]; cur.ins != OP_END; cur = inslist[++pos]) {
#if DEBUG_VM
      printf("%6i\t", pos);
#endif
      switch (cur.ins) {
      case OP_END:
#if DEBUG_VM
        printf("END");
#endif
        return;
        break;
      case OP_NOP:
#if DEBUG_VM
        printf("NOP");
#endif
        break;
      case OP_PUSH:
        lat_push_stack(vm, vm->regs[cur.a]);
#if DEBUG_VM
        printf("PUSH r%i", cur.a);
#endif
        break;
      case OP_POP:
        vm->regs[cur.a] = lat_pop_stack(vm);
#if DEBUG_VM
        printf("POP r%i", cur.a);
#endif
        break;
      case OP_GET:
        vm->regs[cur.a] = lat_get_ctx(vm->regs[cur.b], vm->regs[cur.a]);
#if DEBUG_VM
        printf("GET r%i r%i", cur.a, cur.b);
#endif
        break;
      case OP_SET:
        asignar_contexto(vm->regs[cur.b], lat_clone_object(vm, ((lat_object*)cur.meta)), vm->regs[cur.a]);
#if DEBUG_VM
        printf("SET r%i r%i", cur.b, cur.a);
#endif
        break;
      case OP_STORECHAR:
        vm->regs[cur.a] = ((lat_object*)cur.meta);
#if DEBUG_VM
        printf("STORECHAR r%i, %c", cur.a, ((lat_object*)cur.meta)->data.c);
#endif
        break;
      case OP_STOREINT: {
        vm->regs[cur.a] = ((lat_object*)cur.meta);
#if DEBUG_VM
        printf("STOREINT r%i, %i", cur.a, ((lat_object*)cur.meta)->data.i);
#endif
      } break;
      case OP_STOREDOUBLE:
        vm->regs[cur.a] = ((lat_object*)cur.meta);
#if DEBUG_VM
        printf("STOREDOUBLE r%i, %d", cur.a, ((lat_object*)cur.meta)->data.d);
#endif
        break;
      case OP_STORESTR: {
        vm->regs[cur.a] = ((lat_object*)cur.meta);
#if DEBUG_VM
        printf("STORESTR r%i, %s", cur.a, ((lat_object*)cur.meta)->data.str);
#endif
      } break;
      case OP_STOREBOOL:
        vm->regs[cur.a] = ((lat_object*)cur.meta);
#if DEBUG_VM
        printf("STOREBOOL r%i, %i", cur.a, (int*)cur.meta);
#endif
        break;
      case OP_STORELIST:
        vm->regs[cur.a] = lat_list(vm, make_list());
#if DEBUG_VM
        printf("STORELIST r%i, %s", cur.a, "make_list");
#endif
        break;
      case OP_PUSHLIST:
        lat_push_list(vm->regs[cur.a], vm->regs[cur.b]);
#if DEBUG_VM
        printf("PUSHLIST r%i, r%i", cur.a, cur.b);
#endif
        break;
      case OP_POPLIST:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_pop_list(vm->regs[cur.b]);
#if DEBUG_VM
        printf("POPLIST r%i, r%i", cur.a, cur.b);
#endif
        break;
      case OP_LISTGETITEM:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_pop_list(vm->regs[cur.b]);
#if DEBUG_VM
        printf("LISTGETITEM r%i, r%i", cur.a, cur.b);
#endif
        break;
      case OP_STOREDICT:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_list(vm, make_dict());
#if DEBUG_VM
        printf("STOREDICT r%i, %s", cur.a, "make_dict");
#endif
        break;
      case OP_PUSHDICT:
        //TODO: Pendiente
        //lat_push_dict(vm->regs[cur.a], vm->regs[cur.b]);
#if DEBUG_VM
        printf("PUSHDICT r%i, r%i", cur.a, cur.b);
#endif
        break;
      case OP_POPDICT:
        //TODO: Pendiente
        //vm->regs[cur.a] = lat_pop_dict(vm->regs[cur.b]);
#if DEBUG_VM
        printf("POPDICT r%i, r%i", cur.a, cur.b);
#endif
        break;
      case OP_MOV:
        vm->regs[cur.a] = vm->regs[cur.b];
#if DEBUG_VM
        printf("MOV r%i, r%i", cur.a, cur.b);
#endif
        break;
      case OP_GLOBALNS:
        vm->regs[cur.a] = vm->ctx_stack[0];
        break;
      case OP_LOCALNS:
        vm->regs[cur.a] = obtener_contexto(vm);
#if DEBUG_VM
        printf("LOCALNS r%i", cur.a);
#endif
        break;
      case OP_FN:
        vm->regs[cur.a] = definir_funcion(vm, (lat_bytecode*)cur.meta);
#if DEBUG_VM
        printf("FN %i", (char*)cur.meta);
#endif
        break;
      case OP_NS:
#if DEBUG_VM
        printf("NS r%i", cur.a);
#endif
        vm->regs[cur.a] = lat_clone_object(vm, obtener_contexto(vm));
        lat_push_predefined_ctx(vm, vm->regs[cur.a]);
        break;
      case OP_ENDNS:
#if DEBUG_VM
        printf("ENDNS r%i", cur.a);
#endif
        vm->regs[cur.a] = lat_pop_predefined_ctx(vm);
        break;
      case OP_JMP:
        pos = cur.a - 1;
#if DEBUG_VM
        printf("JMP %i", pos);
#endif
        break;
      case OP_JMPIF:
#if DEBUG_VM
        printf("JMPIF r%i %i", cur.b, (cur.a - 1));
#endif
        if (lat_get_bool_value(vm->regs[cur.b])) {
          pos = cur.a - 1;
        }
        break;
      case OP_CALL:
#if DEBUG_VM
        printf("CALL r%i\n>> ", cur.a);
#endif
        lat_call_func(vm, vm->regs[cur.a]);
        break;
      case OP_NOT:
#if DEBUG_VM
        printf("NOT r%i", cur.a);
#endif
        vm->regs[cur.a] = lat_not(vm, vm->regs[cur.a]);
        break;
      case OP_INC:
#if DEBUG_VM
        printf("INC r%i", cur.a);
#endif
        ((lat_object*)vm->regs[cur.a])->data.i++;
        break;
      case OP_DEC:
#if DEBUG_VM
        printf("INC r%i", cur.a);
#endif
        ((lat_object*)vm->regs[cur.a])->data.i--;
        break;
      }
#if DEBUG_VM
      printf("\n");
#endif
    }
    lat_pop_ctx(vm);
  }
  else if (func->type == T_CFUNC) {
    ((void (*)(lat_vm*))(func->data.func))(vm);
  }
  else {
    debug("func->type: %d", func->type);
    log_err("Object not a function");
  }
}
