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

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "latino.h"
#include "libmem.h"
#include "compat.h"

void* __memoria_asignar(size_t size)
{
    //printf("memoria asignada: %zu\n", size);
    void* value = calloc(1, size);
    if (value == 0)
        lat_fatal_error("Memoria virtual agotada\n");
    return value;
}

size_t __memoria_tamanio(void* ptr){
    return malloc_size(ptr);
}

void* __memoria_reasignar(void* ptr, size_t size)
{
    //size_t mem_ini = __memoria_tamanio(ptr);
    void* value = realloc(ptr, size);
    if (value == 0)
        lat_fatal_error("Memoria virtual agotada\n");
    //printf("memoria inicial: %zu memoria nueva: %zu\n", mem_ini, __memoria_tamanio(value));
    return value;
}

void __memoria_liberar(void* ptr)
{
    if (ptr != NULL)
    {
        //printf("memoria liberada: %zu\n", __memoria_tamanio(ptr));
        free(ptr);
    }
}
