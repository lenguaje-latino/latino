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

#ifndef _LIBSTRING_H_
#define _LIBSTRING_H_

#include "latino.h"
#include "object.h"
#include "vm.h"

/** \file libstring.h
*
* Contiene las funciones para el manejo de cadenas
*
*/

/**\brief Duplica una cadena
  *
  * \param s: Apuntador a una cadena de caracteres
  * \return char*: Apuntador a una cadena de caracteres
  */
char* __str_duplicar(const char* s);

/**\brief Analiza una cadena de caracteres
  *
  * \param s: Apuntador a una cadena de caracteres
  * \param n: Longitud de la cadena
  * \return char*: Apuntador a una cadena de caracteres
  */
char* __str_analizar(const char* s, size_t n);

/**\brief concatena dos cadenas
  *
  *\param s1: Cadena 1 a concatena
  *\param s2: Cadena 2 a concatena
  *\return char*: Apuntador a cadena resultado de s1 + s2
  */
char* __str_concatenar(char* s1, char* s2);

/**\brief Convierte un decimal a cadena
  *
  *\param d: Valor decimal
  *\return char*: Apuntador a cadena
  */
char* __str_decimal_a_cadena(double d);

/**\brief Convierte un valor logico
  *
  *\param i: Valor logico 0, 1
  *\return char*: Apuntador a cadena
  */
char* __str_logico_a_cadena(int i);

char* __str_concatenar(char* s1, char* s2);

/** concatenar: Une dos cadenas
  *
  * \param vm: Maquina virtual de latino
  *
  */
void lat_concatenar(lat_mv* vm);

#endif // !_LIBSTRING_H_
