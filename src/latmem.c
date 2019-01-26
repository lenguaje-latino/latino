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

#include <stdlib.h>

#include "latdo.h"
#include "latino.h"
#include "latmem.h"
#include "latmv.h"

void *latM_asignar(lat_mv *mv, size_t size) {
    void *ptr = calloc(1, size);
    // void *ptr = malloc(size);
    if (ptr == NULL) {
        latC_error(mv, "Memoria virtual agotada");
    }
    if (mv) {
        // size_t tam = latM_tamanio(ptr);
        // printf("+++ memoria asignada: %zu, %p\n", tam, ptr);
        mv->memoria_usada += latM_tamanio(ptr);
    }
    return ptr;
}

size_t latM_tamanio(void *ptr) {
#ifdef __APPLE__
    return 0;
#else
    return malloc_size(ptr);
#endif
}

void *latM_reasignar(lat_mv *mv, void *ptr, size_t size) {
    // size_t mem_ini = latM_tamanio(ptr);
    void *value = realloc(ptr, size);
    if (value == NULL)
        latC_error(mv, "Memoria virtual agotada");
    /*printf("memoria inicial: %zu memoria nueva: %zu, %p\n",
    mem_ini, latM_tamanio(value), &value);*/
    return value;
}

void latM_liberar(lat_mv *mv, void *ptr) {
    if (ptr != NULL) //&& latM_tamanio(ptr) > 0
    {
        // printf("--- memoria liberada: %zu, %p\n",
        // latM_tamanio(ptr), ptr);
        if (mv != NULL) {
            // size_t tam = latM_tamanio(ptr);
            // printf("--- memoria liberada: %zu, %p\n", tam, ptr);
            mv->memoria_usada -= latM_tamanio(ptr);
        }
        ptr = NULL;
        free(ptr);
    }
}
