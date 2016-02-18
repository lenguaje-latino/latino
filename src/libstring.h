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

lat_objeto* lat_cadena_hash(const char* p, size_t len);

/*libreria cadena*/
void lat_comparar(lat_vm* vm);
void lat_concatenar(lat_vm* vm);
void lat_contiene(lat_vm* vm);
void lat_copiar(lat_vm* vm);
void lat_termina_con(lat_vm* vm);
void lat_es_igual(lat_vm* vm);
//void lat_format(lat_vm* vm);
void lat_indice(lat_vm* vm);
void lat_insertar(lat_vm* vm);
void lat_ultimo_indice(lat_vm* vm);
void lat_rellenar_izquierda(lat_vm* vm);
void lat_rellenar_derecha(lat_vm* vm);
void lat_eliminar(lat_vm* vm);
void lat_esta_vacia(lat_vm* vm);
void lat_longitud(lat_vm* vm);
void lat_reemplazar(lat_vm* vm);
//void lat_split(lat_vm* vm);
void lat_empieza_con(lat_vm* vm);
void lat_restarcadena(lat_vm* vm);
void lat_minusculas(lat_vm* vm);
void lat_mayusculas(lat_vm* vm);
void lat_quitar_espacios(lat_vm* vm);
//void lat_valueOf(lat_vm* vm);

#endif // !_LIBSTRING_H_
