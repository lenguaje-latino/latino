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

#include <math.h>
#include "libmath.h"
#include "vm.h"

void lat_arco_coseno(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, acos(lat_obtener_decimal(a)));
}

void lat_arco_seno(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, asin(lat_obtener_decimal(a)));
}

void lat_arco_tangente(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, atan(lat_obtener_decimal(a)));
}

void lat_arco_tangente2(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  lat_objeto *b = lat_desapilar(vm);
  vm->regs[255] =
      lat_decimal_nuevo(vm, atan2(lat_obtener_decimal(a), lat_obtener_decimal(b)));
}

void lat_coseno(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, cos(lat_obtener_decimal(a)));
}

void lat_coseno_hiperbolico(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, cosh(lat_obtener_decimal(a)));
}

void lat_seno(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, sin(lat_obtener_decimal(a)));
}

void lat_seno_hiperbolico(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, sinh(lat_obtener_decimal(a)));
}

void lat_tangente(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, tan(lat_obtener_decimal(a)));
}

void lat_tangente_hiperbolica(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, tanh(lat_obtener_decimal(a)));
}

void lat_exponente(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, exp(lat_obtener_decimal(a)));
}

/*
void lat_frexp(lat_vm *vm){
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, frexp(lat_obtener_decimal(a)));
}
*/

/*
void lat_ldexp(lat_vm* vm)
{
  lat_objeto* a = lat_desapilar(vm);
  lat_objeto* b = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, ldexp(lat_obtener_decimal(a),
lat_obtener_entero(b)));
}
*/

void lat_logaritmo_natural(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, log(lat_obtener_decimal(a)));
}

void lat_logaritmo_base10(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, log10(lat_obtener_decimal(a)));
}

/*
void lat_modf(lat_vm *vm){
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, modf(lat_obtener_decimal(a)));
}
*/

void lat_potencia(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  lat_objeto *b = lat_desapilar(vm);
  vm->regs[255] =
      lat_decimal_nuevo(vm, pow(lat_obtener_decimal(a), lat_obtener_decimal(b)));
}

void lat_raiz_cuadrada(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, sqrt(lat_obtener_decimal(a)));
}

void lat_redondear_arriba(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, ceil(lat_obtener_decimal(a)));
}

void lat_valor_absoluto(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, fabs(lat_obtener_decimal(a)));
}

void lat_redondeo_abajo(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  vm->regs[255] = lat_decimal_nuevo(vm, floor(lat_obtener_decimal(a)));
}

void lat_modulo_decimal(lat_vm *vm) {
  lat_objeto *a = lat_desapilar(vm);
  lat_objeto *b = lat_desapilar(vm);
  vm->regs[255] =
      lat_decimal_nuevo(vm, fmod(lat_obtener_decimal(a), lat_obtener_decimal(b)));
}
