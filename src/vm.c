#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "vm.h"
#include "utils.h"
#include "libmem.h"
#include "libmath.h"
#include "libstring.h"

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
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "imprimir"), lat_define_c_function(ret, lat_print));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "+"), lat_define_c_function(ret, lat_add));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "-"), lat_define_c_function(ret, lat_sub));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "*"), lat_define_c_function(ret, lat_mul));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "/"), lat_define_c_function(ret, lat_div));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "%"), lat_define_c_function(ret, lat_mod));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "!="), lat_define_c_function(ret, lat_neq));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "=="), lat_define_c_function(ret, lat_eq));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "<"), lat_define_c_function(ret, lat_lt));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "<="), lat_define_c_function(ret, lat_lte));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, ">"), lat_define_c_function(ret, lat_gt));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, ">="), lat_define_c_function(ret, lat_gte));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "gc"), lat_define_c_function(ret, lat_gc));

  /* funciones matematicas */
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "arco_coseno"), lat_define_c_function(ret, lat_acos));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "arco_seno"), lat_define_c_function(ret, lat_asin));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "arco_tangente"), lat_define_c_function(ret, lat_atan));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "arco_tangente_radianes"), lat_define_c_function(ret, lat_atan2));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "coseno"), lat_define_c_function(ret, lat_cos));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "coseno_hiperbolico"), lat_define_c_function(ret, lat_cosh));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "seno"), lat_define_c_function(ret, lat_sin));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "seno_hiperbolico"), lat_define_c_function(ret, lat_sinh));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "tangente"), lat_define_c_function(ret, lat_tan));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "tangente_hiperbolica"), lat_define_c_function(ret, lat_tanh));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "exponente"), lat_define_c_function(ret, lat_exp));
  //lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "frexp"), lat_define_c_function(ret, lat_frexp));
  //lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "ldexp"), lat_define_c_function(ret, lat_ldexp));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "logaritmo_natural"), lat_define_c_function(ret, lat_log));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "logaritmo_base10"), lat_define_c_function(ret, lat_log10));
  //lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "modf"), lat_define_c_function(ret, lat_modf));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "potencia"), lat_define_c_function(ret, lat_pow));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "raiz_cuadrada"), lat_define_c_function(ret, lat_sqrt));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "redondear_arriba"), lat_define_c_function(ret, lat_ceil));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "valor_absoluto"), lat_define_c_function(ret, lat_fabs));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "redondear_abajo"), lat_define_c_function(ret, lat_floor));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "modulo"), lat_define_c_function(ret, lat_fmod));

  /*funciones para cadenas (string)*/
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "comparar"), lat_define_c_function(ret, lat_compare));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "concatenar"), lat_define_c_function(ret, lat_concat));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "contiene"), lat_define_c_function(ret, lat_contains));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "copiar"), lat_define_c_function(ret, lat_copy));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "termina_con"), lat_define_c_function(ret, lat_endsWith));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "es_igual"), lat_define_c_function(ret, lat_equals));
  //TODO: Pendiente
  //lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "formato"), lat_define_c_function(ret, lat_format));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "indice"), lat_define_c_function(ret, lat_indexOf));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "insertar"), lat_define_c_function(ret, lat_insert));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "ultimo_indice"), lat_define_c_function(ret, lat_lastIndexOf));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "rellenar_izquierda"), lat_define_c_function(ret, lat_padLeft));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "rellenar_derecha"), lat_define_c_function(ret, lat_padRight));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "eliminar"), lat_define_c_function(ret, lat_remove));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "es_vacia"), lat_define_c_function(ret, lat_isEmpty));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "longitud"), lat_define_c_function(ret, lat_length));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "reemplazar"), lat_define_c_function(ret, lat_replace));
  //TODO: Pendiente, se implementara cuando se implementen Listas
  //lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "partir"), lat_define_c_function(ret, lat_split));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "empieza_con"), lat_define_c_function(ret, lat_startsWith));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "subcadena"), lat_define_c_function(ret, lat_substring));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "minusculas"), lat_define_c_function(ret, lat_toLower));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "mayusculas"), lat_define_c_function(ret, lat_toUpper));
  lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "quitar_espacios"), lat_define_c_function(ret, lat_trim));
  //lat_set_ctx(lat_get_current_ctx(ret), lat_str(ret, "cadena"), lat_define_c_function(ret, lat_valueOf));
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

lat_object* lat_get_current_ctx(lat_vm* vm)
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

lat_object* lat_define_function(lat_vm* vm, lat_bytecode* inslist)
{
  lat_object* ret = lat_func(vm);
  lat_function* fval = (lat_function*)lmalloc(sizeof(lat_function));
  fval->bcode = inslist;
  ret->data.func = fval;
  //vm->memory_usage += sizeof(sizeof(lat_function));
  return ret;
}

lat_object* lat_define_c_function(lat_vm* vm, void (*function)(lat_vm* vm))
{
  lat_object* ret = lat_cfunc(vm);
  ret->data.cfunc = function;
  return ret;
}

void lat_nth_list(lat_vm* vm)
{
  lat_object* index = lat_pop_stack(vm);
  int i = lat_get_int_value(index);
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
    fprintf(stdout, "%s", "NULO");
  }
  else if (in->type == T_INSTANCE) {
    fprintf(stdout, "%s", "Objeto");
  }
  else if (in->type == T_CHAR) {
    fprintf(stdout, "%c", lat_get_char_value(in));
  }
  else if (in->type == T_INT) {
    fprintf(stdout, "%d", lat_get_int_value(in));
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
    fprintf(stdout, "%s\n", "NULO");
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
    vm->regs[255] = (vm, lat_get_double_value(a) != lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (vm, lat_get_int_value(a) != lat_get_int_value(b)) ? vm->true_object : vm->false_object;
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
    vm->regs[255] = (vm, lat_get_double_value(a) == lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (vm, lat_get_int_value(a) == lat_get_int_value(b)) ? vm->true_object : vm->false_object;
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
    vm->regs[255] = (vm, lat_get_double_value(a) < lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (vm, lat_get_int_value(a) < lat_get_int_value(b)) ? vm->true_object : vm->false_object;
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
    vm->regs[255] = (vm, lat_get_double_value(a) <= lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (vm, lat_get_int_value(a) <= lat_get_int_value(b)) ? vm->true_object : vm->false_object;
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
    vm->regs[255] = (vm, lat_get_double_value(a) > lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (vm, lat_get_int_value(a) > lat_get_int_value(b)) ? vm->true_object : vm->false_object;
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
    vm->regs[255] = (vm, lat_get_double_value(a) >= lat_get_double_value(b)) ? vm->true_object : vm->false_object;
  }
  else {
    vm->regs[255] = (vm, lat_get_int_value(a) >= lat_get_int_value(b)) ? vm->true_object : vm->false_object;
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
    lat_set_ctx(lat_get_current_ctx(vm), lat_str(vm, "$"), func);
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
        lat_set_ctx(vm->regs[cur.b], lat_clone_object(vm, ((lat_object*)cur.meta)), vm->regs[cur.a]);
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
        vm->regs[cur.a] = lat_get_current_ctx(vm);
#if DEBUG_VM
        printf("LOCALNS r%i", cur.a);
#endif
        break;
      case OP_FN:
        vm->regs[cur.a] = lat_define_function(vm, (lat_bytecode*)cur.meta);
#if DEBUG_VM
        printf("FN %i", (char*)cur.meta);
#endif
        break;
      case OP_NS:
#if DEBUG_VM
        printf("NS r%i", cur.a);
#endif
        vm->regs[cur.a] = lat_clone_object(vm, lat_get_current_ctx(vm));
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
