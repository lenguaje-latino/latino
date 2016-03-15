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

#ifndef _LIBMEM_H_
#define _LIBMEM_H_

#include <stdlib.h>

/** \file libmem.h
*
* Contiene las funciones para el manejo de memoria dinamica
*
*/

/** Asigna memoria dinamicamente (malloc)
  *
  * \param size: Tamanio de memoria solicitado
  *
  */
void* lat_asignar_memoria(size_t size);

/** Reasigna memoria dinamicamente (realloc)
  *
  * \param ptr: Apuntador a la memoria actual
  * \param size: Tamanio nuevo de memoria solicitado
  *
  */
void* lat_reasignar_memoria(void* ptr, size_t size);

/** Libera la memoria (free)
  *
  * \param ptr: Apuntador a la memoria a liberar
  *
  */
void lat_liberar_memoria(void* ptr);

#endif /*_LIBMEM_H_*/
