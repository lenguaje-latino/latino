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

#ifndef _LATINO_DIC_H_
#define _LATINO_DIC_H_

#include <stdlib.h>

#include "latlist.h"

typedef struct _lat_objeto lat_objeto;
typedef struct lat_mv lat_mv;

/**\brief Valor hash */
typedef struct hash_val {
    char llave[64];
    lat_objeto *valor;
} hash_val;

/**\brief Mapa de valores hash */
typedef struct hash_map {
    lista *buckets[256];
    size_t longitud;
} hash_map;

#define latH_longitud(hm) (hm)->longitud

int latH_hash(const char *key);

#endif /* !_LATINO_DIC_H_ */
