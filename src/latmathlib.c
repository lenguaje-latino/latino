/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

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

#include "latino.h"

#undef PI
#define PI 3.141592653589793

#undef TAU
#define TAU 6.283185307179586

#undef Eu
#define Eu 2.718281828459045

#define INF_NEV -999999999999999
#define INF_POV 999999999999999

#define LIB_MATE_NAME "mate"

static void mate_abs(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, fabs(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_acos(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, acos(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_acosh(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, acosh(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_asin(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, asin(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_asinh(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, asinh(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_atan(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, atan(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_atanh(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, atanh(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_atan2(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(
        mv, atan2(latC_checar_numerico(mv, a), latC_checar_numerico(mv, b)));
    latC_apilar(mv, tmp);
}

static void mate_cos(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(mv, cos(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_cosh(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, cosh(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_cbrt(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, cbrt(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_sin(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(mv, sin(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_sinh(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, sinh(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_tan(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(mv, tan(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_tanh(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, tanh(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_exp(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(mv, exp(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_log(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(mv, log(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_log10(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, log10(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_sqrt(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, sqrt(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_ceil(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, ceil(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_floor(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, floor(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_pow(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(
        mv, pow(latC_checar_numerico(mv, a), latC_checar_numerico(mv, b)));
    latC_apilar(mv, tmp);
}

static void mate_frexp(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    int e = (int)latC_checar_numerico(mv, b);
    lat_objeto *tmp =
        latC_crear_numerico(mv, frexp(latC_checar_numerico(mv, a), &e));
    latC_apilar(mv, tmp);
}

static void mate_ldexp(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    int e = (int)latC_checar_numerico(mv, b);
    lat_objeto *tmp =
        latC_crear_numerico(mv, ldexp(latC_checar_numerico(mv, a), e));
    latC_apilar(mv, tmp);
}

// NOTA: Antigua funcion para numeros aleatorios (Obsoleta)
//
// static void mate_random(lat_mv *mv) {
//     lat_objeto *secundario = latC_desapilar(mv);
//     lat_objeto *primario = latC_desapilar(mv);
//     int resultado, min, max;
//     min = (int)latC_checar_numerico(mv, primario);
//     max = (int)latC_checar_numerico(mv, secundario);
//     if (min <= max) {
//         max = max + 1;
//     } else {
//         min = (int)latC_checar_numerico(mv, secundario);
//         max = (int)latC_checar_numerico(mv, primario) + 1;
//     }
//     srand(time(NULL));
//     resultado = (rand() % (max - min)) + min;
//     lat_objeto *tmp = latC_crear_numerico(mv, resultado);
//     latC_apilar(mv, tmp);
// }

static void mate_random(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    int res=0, vlmx=0, cant = (int)latC_checar_numerico(mv, o);
    if (cant <= 0) {
        res = (rand() % 2);
    } else if (cant == 1) {
        vlmx = (int)latC_checar_numerico(mv, latC_desapilar(mv));
        res = (rand() % (vlmx + 1));
    } else if (cant == 2) {
        int vlmn = (int)latC_checar_numerico(mv, latC_desapilar(mv));
        vlmx = (int)latC_checar_numerico(mv, latC_desapilar(mv));
        if (vlmn <= vlmx) {
            vlmx = vlmx + 1;
        } else {
            // Se intercambian los valores
            vlmn = vlmn - vlmx;
            vlmx = vlmn + vlmx;
            vlmn = vlmx - vlmn;
            vlmx = vlmx + 1;
        }
        res = (rand() % (vlmx - vlmn)) + vlmn;
    } else {
        latC_error(mv, "Numero invalido de argumentos");
    }
    lat_objeto *tmp = latC_crear_numerico(mv, res);
    latC_apilar(mv, tmp);
}

static void mate_pi(lat_mv *mv) {
    double pi = PI;
    lat_objeto *ret = latO_crear(mv);
    ret->tam += sizeof(double);
    setNumerico(ret, pi);
    latC_apilar(mv, ret);
}

static void mate_tau(lat_mv *mv) {
    double tau = TAU;
    lat_objeto *ret = latO_crear(mv);
    ret->tam += sizeof(double);
    setNumerico(ret, tau);
    latC_apilar(mv, ret);
}

static void mate_e(lat_mv *mv) {
    double eu = Eu;
    lat_objeto *ret = latO_crear(mv);
    ret->tam += sizeof(double);
    setNumerico(ret, eu);
    latC_apilar(mv, ret);
}

static void mate_base(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *bp =
        latC_crear_numerico(mv, (latC_checar_numerico(mv, b) / 100));
    lat_objeto *tmp = latC_crear_numerico(
        mv, (latC_checar_numerico(mv, a) / latC_checar_numerico(mv, bp)));
    latC_apilar(mv, tmp);
}

static void mate_parte(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *ap =
        latC_crear_numerico(mv, (latC_checar_numerico(mv, a) / 100));
    lat_objeto *tmp = latC_crear_numerico(
        mv, (latC_checar_numerico(mv, ap) * latC_checar_numerico(mv, b)));
    latC_apilar(mv, tmp);
}

static void mate_porc(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp = latC_crear_numerico(
        mv, (latC_checar_numerico(mv, a) / latC_checar_numerico(mv, b)));
    latC_apilar(mv, tmp);
}

static void mate_trunc(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, trunc(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_round(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, round(latC_checar_numerico(mv, a)));
    latC_apilar(mv, tmp);
}

static void mate_max(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    int i = 0, cant = (int)latC_checar_numerico(mv, o);
    if (cant <= 0) {
        latC_error(mv, "Numero invalido de argumentos");
    }
    double e = 0, vl = INF_NEV;
    lista *valores = latL_crear(mv);
    while (i < cant) {
        latL_insertar_inicio(mv, valores, latO_clonar(mv, latC_desapilar(mv)));
        i++;
    }
    for (i = 0; i < cant; i++) {
        e = latC_checar_numerico(mv, latL_extraer_inicio(mv, valores));
        if (e > vl) {
            vl = e;
        }
    }
    latL_destruir(mv, valores);
    lat_objeto *tmp = latO_crear(mv);
    setNumerico(tmp, vl);
    latC_apilar(mv, tmp);
}

static void mate_min(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    int i = 0, cant = (int)latC_checar_numerico(mv, o);
    if (cant <= 0) {
        latC_error(mv, "Numero invalido de argumentos");
    }
    double e = 0, vl = INF_POV;
    lista *valores = latL_crear(mv);
    while (i < cant) {
        latL_insertar_inicio(mv, valores, latO_clonar(mv, latC_desapilar(mv)));
        i++;
    }
    for (i = 0; i < cant; i++) {
        e = latC_checar_numerico(mv, latL_extraer_inicio(mv, valores));
        if (e < vl) {
            vl = e;
        }
    }
    latL_destruir(mv, valores);
    lat_objeto *tmp = latO_crear(mv);
    setNumerico(tmp, vl);
    latC_apilar(mv, tmp);
}

static const lat_CReg libmate_[] = {
    {"abs", mate_abs, 1},
    {"acos", mate_acos, 1},
    {"acosh", mate_acosh, 1},
    {"asen", mate_asin, 1},
    {"asenh", mate_asinh, 1},
    {"atan", mate_atan, 1},
    {"atanh", mate_atanh, 1},
    {"atan2", mate_atan2, 2},
    {"cos", mate_cos, 1},
    {"cosh", mate_cosh, 1},
    {"sen", mate_sin, 1},
    {"senh", mate_sinh, 1},
    {"tan", mate_tan, 1},
    {"tanh", mate_tanh, 1},
    {"exp", mate_exp, 1},
    {"log", mate_log, 1},
    {"log10", mate_log10, 1},
    {"max", mate_max, FUNCION_VAR_ARGS},
    {"min", mate_min, FUNCION_VAR_ARGS},
    {"raiz", mate_sqrt, 1},
    {"raizc", mate_cbrt, 1},
    {"techo", mate_ceil, 1},
    {"piso", mate_floor, 1},
    {"pot", mate_pow, 2},
    {"frexp", mate_frexp, 2},
    {"ldexp", mate_ldexp, 2},
    {"trunc", mate_trunc, 1},
    {"aleatorio", mate_random, FUNCION_VAR_ARGS},
    {"alt", mate_random, FUNCION_VAR_ARGS},
    {"pi", mate_pi, 0},
    {"tau", mate_tau, 0},
    {"e", mate_e, 0},
    {"redondear", mate_round, 1},
    {"rnd", mate_round, 1},
    {"base", mate_base, 2},
    {"parte", mate_parte, 2},
    {"porciento", mate_porc, 2},
    {"porcentaje", mate_porc, 2},
    {"porc", mate_porc, 2},
    {NULL, NULL}};

void latC_abrir_liblatino_mathlib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_MATE_NAME, libmate_);
}
