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

#ifndef _LIBMATH_H_
#define _LIBMATH_H_

#include <math.h>
#include "vm.h"

/** \file libmath.h
*
* Contiene las funciones matematicas
*
*/

/** Arco coseno (acos) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_arco_coseno(lat_vm* vm);

/** Arco seno (asin) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_arco_seno(lat_vm* vm);

/** Arco tangente (atan) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_arco_tangente(lat_vm* vm);

/** Arco tangente (atan2) con dos parametros  (x, y) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_arco_tangente2(lat_vm* vm);

/** Coseno (cos) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_coseno(lat_vm* vm);

/** Coseno hiperbolico (cosh) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_coseno_hiperbolico(lat_vm* vm);

/** Seno (sin) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_seno(lat_vm* vm);

/** Seno hiperbolico (sinh) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_seno_hiperbolico(lat_vm* vm);

/** Tangente (tan) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_tangente(lat_vm* vm);

/** Tangente hiperbolica (tanh) expresado en radianes
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_tangente_hiperbolica(lat_vm* vm);

/** Exponente base (exp)
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_exponente(lat_vm* vm);

/** Logaritmo natural (log)
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_logaritmo_natural(lat_vm* vm);

/** Logaritmo base 10 (log10)
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_logaritmo_base10(lat_vm* vm);

/** Potencia de un numero (pow)
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_potencia(lat_vm* vm);

/** Raiz cuadrada (sqrt)
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_raiz_cuadrada(lat_vm* vm);

/** Redondeo hacia arriba (ceil) 2.3 es 3.0, -2.3 es -2.0
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_redondear_arriba(lat_vm* vm);

/** Valor absoluto (abs)
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_valor_absoluto(lat_vm* vm);

/** Redondeo hacia abajo (floor) 2.3 es 2.0, -2.3 es -3.0
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_redondeo_abajo(lat_vm* vm);

/** Modulo de un decimal (fmod) 5.3 / 2 es 1.300000
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_modulo_decimal(lat_vm* vm);

#endif /* ifndef _LIBMATH_H_ */
