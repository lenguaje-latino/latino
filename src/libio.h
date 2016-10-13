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

#ifndef _LIBIO_H_
#define _LIBIO_H_

#include <stdio.h>
#include "vm.h"

/** \file libio.h
*
* Contiene las funciones para el manejo de entradas y salidas
*
*/

/**\brief Valida si un archivo se puede leer
  *
  *\param archivo: Nombre completo del archivo
  *\return bool: true si se puede leer
  */
bool __io_es_legible(const char *archivo);

/** Lee de la entrada estandar (teclado)
  *
  * \param vm: Máquina virtual de latino
  *
  */
void lat_leer(lat_mv *vm);

/** Lee un archivo
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_leer_archivo(lat_mv *vm);

/** Escribir en un archivo
  *
  * \param vm: Máquina virtual de latino
  *
  */
void lat_escribir_archivo(lat_mv *vm);

/** Ejecuta un comando en el sistema actual ej. "cat file.lat"
  *
  * \param vm: Máquina virtual de latino
  *
  */
void lat_sistema(lat_mv *vm);

/** Ejecuta un comando en el sistema actual ej. "cat file.lat" regresando la cadena de salida
  *
  * \param vm: Máquina virtual de latino
  *
  */
void lat_ejecutar_pipe(lat_mv *vm);

/** Limpia pantalla. En windows es "cls" y linux "clear"
  * Uso: limpiar
  */
void lat_limpiar();

#endif /* !_LIBIO_H_ */
