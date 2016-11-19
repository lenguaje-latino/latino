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

/*
 * File:   gc.h
 * Author: primi
 *
 * Created on 8 de septiembre de 2016, 09:03 AM
 */

#ifndef _GC_H_
#define _GC_H_

#include <time.h>

#include "latlist.h"
#include "latmv.h"
#include "latobj.h"

/**\brief Bandera habilitar o deshabilitar GC */
#define HABILITAR_GC 0

#define TIME_THIS(X)                                                           \
  {                                                                            \
    struct timespec ts1, ts2;                                                  \
    clock_gettime(CLOCK_REALTIME, &ts1);                                       \
    X;                                                                         \
    clock_gettime(CLOCK_REALTIME, &ts2);                                       \
    printf(#X " demora: %f\n",                                                 \
           (float)(1.0 * (1.0 * ts2.tv_nsec - ts1.tv_nsec * 1.0) * 1e-9 +      \
                   1.0 * ts2.tv_sec - 1.0 * ts1.tv_sec));                      \
  }

/** Agrega un objeto al colector de basura
  *
  * \param vm: Apuntador a Maquina Virtual
  * \param o: Objeto a agregar
  *
  */
void lat_gc_agregar(lat_mv *mv, lat_objeto *o);

/** Ejecuta la limpieza de objetos basura
  *
  * \param vm: Apuntador a Maquina Virtual
  *
  */
void lat_gc_limpiar(lat_mv *mv);

#endif /* _GC_H_ */
