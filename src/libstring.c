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

#include "khash.h"
#include "latino.h"
#include "object.h"
#include "libmem.h"
#include "utils.h"

KHASH_MAP_INIT_INT64(env, lat_object);
typedef khash_t(env) lat_env;
lat_env* globals;

struct sym_key {
  const char* ptr;
  size_t len;
};

static khint_t
sym_hash(struct sym_key key)
{
  const char* s = key.ptr;
  khint_t h;
  size_t len = key.len;
  h = *s++;
  while (len--) {
    h = (h << 5) - h + (khint_t)*s++;
  }
  return h;
}

static khint_t
sym_eq(struct sym_key a, struct sym_key b)
{
  if (a.len != b.len)
    return false;
  if (memcmp(a.ptr, b.ptr, a.len) == 0)
    return true;
  return false;
}

KHASH_INIT(sym, struct sym_key, lat_object*, 1, sym_hash, sym_eq);
static khash_t(sym) * sym_table;

static lat_object* str_new(const char* p, size_t len)
{
  lat_object* str = (lat_object*)lmalloc(sizeof(lat_object));
  str->type = T_STR;
  str->data_size = len;
  str->data.str = (char*)p;
  return str;
}

static lat_object* str_intern(const char* p, size_t len)
{
  khiter_t k;
  struct sym_key key;
  int ret;
  lat_object* str;
  if (!sym_table) {
    sym_table = kh_init(sym);
  }
  key.ptr = p;
  key.len = len;
  k = kh_put(sym, sym_table, key, &ret);
  if (ret == 0) {
    return kh_value(sym_table, k);
  }
  str = str_new(p, len);
  kh_key(sym_table, k).ptr = str->data.str;
  kh_value(sym_table, k) = str;
  return str;
}

lat_object* lat_str_new(const char* p, size_t len)
{
  if (p && (len < MAX_STR_INTERN)) {
    return str_intern(p, len);
  }
  return str_new(p, len);
}

void lat_compare(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_int(vm, strcmp(lat_get_str_value(a), lat_get_str_value(b)));
}

void lat_concat(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, concat(lat_get_str_value(a), lat_get_str_value(b)));
}

void lat_contains(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  char *result = strstr(lat_get_str_value(a), lat_get_str_value(b));
  if (result != NULL){
	  vm->regs[255] = vm->true_object;
  }
  else{
	  vm->regs[255] = vm->false_object;
  }
}

void lat_copy(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  vm->regs[255] = lat_clone_object(vm, b);
}

void lat_endsWith(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if (endsWith(lat_get_str_value(a), lat_get_str_value(b))){
    vm->regs[255] = vm->true_object;
  }
  else{
    vm->regs[255] = vm->false_object;
  }
}

void lat_equals(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if (strcmp(lat_get_str_value(a), lat_get_str_value(b)) == 0){
    vm->regs[255] = vm->true_object;
  }
  else{
    vm->regs[255] = vm->false_object;
  }
}

/*
void lat_format(lat_vm* vm){

}
*/

void lat_indexOf(lat_vm* vm){
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_int(vm, indexOf(lat_get_str_value(a), lat_get_str_value(b)));
}

void lat_insert(lat_vm* vm){
  lat_object* c = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, insert(lat_get_str_value(a), lat_get_str_value(b), lat_get_int_value(c)));
}

void lat_lastIndexOf(lat_vm* vm){
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_int(vm, lastIndexOf(lat_get_str_value(a), lat_get_str_value(b)));
}

void lat_padLeft(lat_vm* vm){
  lat_object* c = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, padLeft(lat_get_str_value(a), lat_get_int_value(b), lat_get_char_value(c)));
}

void lat_padRight(lat_vm* vm){
  lat_object* c = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, padRight(lat_get_str_value(a), lat_get_int_value(b), lat_get_char_value(c)));
}

void lat_remove(lat_vm* vm){
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, replace(lat_get_str_value(a), lat_get_str_value(b), ""));
}

void lat_isEmpty(lat_vm* vm){
  lat_object* a = lat_pop_stack(vm);
  if (strcmp(lat_get_str_value(a), "") == 0){
    vm->regs[255] = vm->true_object;
  }
  else{
    vm->regs[255] = vm->false_object;
  }
}

void lat_length(lat_vm* vm){
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_int(vm, strlen(lat_get_str_value(a)));
}

void lat_replace(lat_vm* vm){
  lat_object* c = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, replace(lat_get_str_value(a), lat_get_str_value(b), lat_get_str_value(c)));
}

void lat_startsWith(lat_vm* vm)
{
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  if (startsWith(lat_get_str_value(a), lat_get_str_value(b))){
    vm->regs[255] = vm->true_object;
  }
  else{
    vm->regs[255] = vm->false_object;
  }
}

void lat_substring(lat_vm* vm){
  lat_object* c = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, substring(lat_get_str_value(a), lat_get_int_value(b), lat_get_int_value(c)));
}

void lat_toLower(lat_vm* vm){
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, toLower(lat_get_str_value(a)));
}

void lat_toUpper(lat_vm* vm){
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, toUpper(lat_get_str_value(a)));
}

void lat_trim(lat_vm* vm){
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_str(vm, trim(lat_get_str_value(a)));
}
