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

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "latcompat.h"
#include "latino.h"
#include "latmem.h"
#include "latmv.h"

void *__memoria_asignar(lat_mv * mv, size_t size) {
	// void* ptr = calloc(1, size);
	void *ptr = calloc(size + 1, sizeof(char));
	if (ptr == NULL)
		lat_error("Memoria virtual agotada\n");
	// printf("+++ memoria asignada: %zu, %p\n", size, &value);
	if (mv)
		mv->memoria_usada += __memoria_tamanio(ptr);
	return ptr;
}

size_t __memoria_tamanio(void *ptr) {
	return malloc_size(ptr);
}

void *__memoria_reasignar(void *ptr, size_t size) {
	// size_t mem_ini = __memoria_tamanio(ptr);
	void *value = realloc(ptr, size);
	if (value == NULL)
		lat_error("Memoria virtual agotada\n");
	// printf("memoria inicial: %zu memoria nueva: %zu, %p\n", mem_ini,
	// __memoria_tamanio(value), &value);
	return value;
}

void __memoria_liberar(lat_mv * mv, void *ptr) {
	if (ptr != NULL)			//&& __memoria_tamanio(ptr) > 0
	{
		// printf("--- memoria liberada: %zu, %p\n", __memoria_tamanio(ptr), ptr);
		if (mv != NULL) {
			mv->memoria_usada -= __memoria_tamanio(ptr);
		}
		free(ptr);
	}
}
