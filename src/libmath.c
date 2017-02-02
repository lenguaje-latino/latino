/*
The MIT License (MIT)

Copyright (c) 2015 - 2016. Latino

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

#include "latgc.h"
#include "latmv.h"
#include <math.h>

#define LIB_MATE_NAME "mate"

void lat_mate_acos(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, acos(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_asin(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, asin(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_atan(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, atan(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_cos(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, cos(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_cosh(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, cosh(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_sin(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, sin(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_sinh(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, sinh(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_tan(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, tan(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_tanh(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, tanh(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_exp(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, exp(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_log(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, log(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_log10(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, log10(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_sqrt(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, sqrt(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_ceil(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, ceil(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_floor(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, floor(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_abs(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, fabs(__numerico(a)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_atan2(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp =
        lat_numerico_nuevo(mv, atan2(__numerico(a), __numerico(b)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_pow(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        lat_objeto *tmp = lat_numerico_nuevo(mv, pow(__numerico(a), __numerico(b)));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_frexp(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        int e = (int)__numerico(b);
        lat_objeto *tmp = lat_numerico_nuevo(mv, frexp(__numerico(a), &e));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_ldexp(lat_mv *mv) {
        lat_objeto *b = lat_desapilar(mv);
        lat_objeto *a = lat_desapilar(mv);
        int e = (int)__numerico(b);
        lat_objeto *tmp = lat_numerico_nuevo(mv, ldexp(__numerico(a), e));
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

void lat_mate_random(lat_mv *mv) {
        lat_objeto *secundario = lat_desapilar(mv);
        lat_objeto *primario = lat_desapilar(mv);
        int resultado, min, max;
        min = __numerico(primario);
        max = __numerico(secundario);
        if (min <= max) {
                max = max + 1;
        } else {
                min = __numerico(secundario);
                max = __numerico(primario) + 1;
        }
        srand(time(NULL));
        resultado = (rand() % (max - min)) + min;
        lat_objeto *tmp = lat_numerico_nuevo(mv, resultado);
        lat_apilar(mv, tmp);
        lat_gc_agregar(mv, tmp);
}

static const lat_CReg libmate[] = {
        {"acos", lat_mate_acos, 1},        {"asen", lat_mate_asin, 1},
        {"atan", lat_mate_atan, 1},        {"cos", lat_mate_cos, 1},
        {"cosh", lat_mate_cosh, 1},        {"sen", lat_mate_sin, 1},
        {"senh", lat_mate_sinh, 1},        {"tan", lat_mate_tan, 1},
        {"tanh", lat_mate_tanh, 1},        {"exp", lat_mate_exp, 1},
        {"log", lat_mate_log, 1},          {"log10", lat_mate_log10, 1},
        {"raiz", lat_mate_sqrt, 1},        {"techo", lat_mate_ceil, 1},
        {"piso", lat_mate_floor, 1},       {"abs", lat_mate_abs, 1},
        {"atan2", lat_mate_atan2, 2},      {"pot", lat_mate_pow, 2},
        {"frexp", lat_mate_frexp, 2},      {"ldexp", lat_mate_ldexp, 2},
        {"aleatorio", lat_mate_random, 2}, {NULL, NULL}
};

void lat_importar_lib_mate(lat_mv *mv) {
        lat_importar_lib(mv, LIB_MATE_NAME, libmate);
}
