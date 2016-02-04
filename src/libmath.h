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

#ifndef _LIBMATH_H_
#define _LIBMATH_H_

#include <math.h>
#include "vm.h"

void lat_arco_coseno(lat_vm* vm);
void lat_arco_seno(lat_vm* vm);
void lat_arco_tangente(lat_vm* vm);
void lat_arco_tangente_radianes(lat_vm* vm);
void lat_coseno(lat_vm* vm);
void lat_cosenoh(lat_vm* vm);
void lat_seno(lat_vm* vm);
void lat_seno_hiperbolico(lat_vm* vm);
void lat_tangente(lat_vm* vm);
void lat_tangente_hiperbolica(lat_vm* vm);
void lat_exponente(lat_vm* vm);
void lat_logaritmo_natural(lat_vm* vm);
void lat_logaritmo_base10(lat_vm* vm);
void lat_potencia(lat_vm* vm);
void lat_raiz_cuadrada(lat_vm* vm);
void lat_redondear_arriba(lat_vm* vm);
void lat_valor_absoluto(lat_vm* vm);
void lat_redondeo_abajo(lat_vm* vm);
void lat_modulo_decimal(lat_vm* vm);

#endif /* ifndef _LIBMATH_H_ */
