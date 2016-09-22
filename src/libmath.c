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

void lat_arco_coseno(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, acos(__numerico(a))));
}

void lat_arco_seno(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, asin(__numerico(a))));
}

void lat_arco_tangente(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, atan(__numerico(a))));
}

void lat_arco_tangente2(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_objeto *b = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, atan2(__numerico(a), __numerico(b))));
}

void lat_coseno(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, cos(__numerico(a))));
}

void lat_coseno_hiperbolico(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, cosh(__numerico(a))));
}

void lat_seno(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, sin(__numerico(a))));
}

void lat_seno_hiperbolico(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, sinh(__numerico(a))));
}

void lat_tangente(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, tan(__numerico(a))));
}

void lat_tangente_hiperbolica(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, tanh(__numerico(a))));
}

void lat_exponente(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, exp(__numerico(a))));
}

/*
void lat_frexp(lat_mv *vm){
  lat_objeto *a = lat_desapilar(vm);
  lat_apilar(vm, lat_decimal_nuevo(vm, frexp(lat_obtener_decimal(a)));
}
*/

/*
void lat_ldexp(lat_mv* vm)
{
  lat_objeto* a = lat_desapilar(vm);
  lat_objeto* b = lat_desapilar(vm);
  lat_apilar(vm, lat_decimal_nuevo(vm, ldexp(lat_obtener_decimal(a),
lat_obtener_entero(b)));
}
*/

void lat_logaritmo_natural(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, log(__numerico(a))));
}

void lat_logaritmo_base10(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, log10(__numerico(a))));
}

/*
void lat_modf(lat_mv *vm){
  lat_objeto *a = lat_desapilar(vm);
  lat_apilar(vm, lat_decimal_nuevo(vm, modf(lat_obtener_decimal(a)));
}
*/

void lat_potencia(lat_mv *vm)
{
    lat_objeto *b = lat_desapilar(vm);
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, pow(__numerico(a), __numerico(b))));
}

void lat_raiz_cuadrada(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, sqrt(__numerico(a))));
}

void lat_redondear_arriba(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, ceil(__numerico(a))));
}

void lat_valor_absoluto(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, fabs(__numerico(a))));
}

void lat_redondear_abajo(lat_mv *vm)
{
    lat_objeto *a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, floor(__numerico(a))));
}