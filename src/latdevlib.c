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

#define LIB_LAT_NAME "lat"

char *tipo(int tipo);

static void dev_mostrar(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    char *tmp = latC_astring(mv, o);
    printf("Tipo : %s\n", tipo(o->tipo));
    printf("Marca : %i\n", o->marca);
    printf("Num. Referencias : %i\n", o->nref);
    printf("Tamanio : %zu\n", o->tam);
    printf("Direccion : %p\n", o);
    printf("Contenido : %s\n", tmp);
    printf("------------------------------------\n");
    free(tmp);
}

void imprimir_pila(lat_mv *mv);
static void dev_imprimir_pila(lat_mv *mv) { imprimir_pila(mv); }

static const lat_CReg liblat[] = {{"mostrar", dev_mostrar, 1},
                                  {"imprimir_pila", dev_imprimir_pila, 0},
                                  {NULL, NULL, 0}};

void latC_abrir_liblatino_devlib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_LAT_NAME, liblat);
}
// Mirar Python Debbuger
//https://docs.python.org/3/library/pdb.html