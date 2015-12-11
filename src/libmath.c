#include <math.h>
#include "libmath.h"
#include "vm.h"

void lat_acos(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, acos(lat_get_double_value(a)));
}

void lat_asin(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, asin(lat_get_double_value(a)));
}

void lat_atan(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, atan(lat_get_double_value(a)));
}

void lat_atan2(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, atan2(lat_get_double_value(a), lat_get_double_value(b)));
}

void lat_cos(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, cos(lat_get_double_value(a)));
}

void lat_cosh(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, cosh(lat_get_double_value(a)));
}

void lat_sin(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, sin(lat_get_double_value(a)));
}

void lat_sinh(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, sinh(lat_get_double_value(a)));
}

void lat_tan(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, tan(lat_get_double_value(a)));
}

void lat_tanh(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, tanh(lat_get_double_value(a)));
}

void lat_exp(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, exp(lat_get_double_value(a)));
}

/*
void lat_frexp(lat_vm *vm){
  lat_object *a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, frexp(lat_get_double_value(a)));
}
*/

/*
void lat_ldexp(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, ldexp(lat_get_double_value(a), lat_get_int_value(b)));
}
*/

void lat_log(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, log(lat_get_double_value(a)));
}

void lat_log10(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, log10(lat_get_double_value(a)));
}

/*
void lat_modf(lat_vm *vm){
  lat_object *a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, modf(lat_get_double_value(a)));
}
*/

void lat_pow(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, pow(lat_get_double_value(a), lat_get_double_value(b)));
}

void lat_sqrt(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, sqrt(lat_get_double_value(a)));
}

void lat_ceil(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, ceil(lat_get_double_value(a)));
}

void lat_fabs(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, fabs(lat_get_double_value(a)));
}

void lat_floor(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, floor(lat_get_double_value(a)));
}

void lat_fmod(lat_vm* vm)
{
  lat_object* a = lat_pop_stack(vm);
  lat_object* b = lat_pop_stack(vm);
  vm->regs[255] = lat_double(vm, fmod(lat_get_double_value(a), lat_get_double_value(b)));
}
