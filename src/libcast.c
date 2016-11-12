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

#define LIB_CAST_NAME "convertir"

#include "latgc.h"
#include "latino.h"
#include "latmv.h"
#include "latobj.h"

void lat_logico(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *tmp =
      lat_obj2bool(o) == true ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, tmp);
}

void lat_numerico(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *tmp = lat_numerico_nuevo(mv, lat_obj2double(o));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  char *buf = lat_obj2cstring(o);
  lat_objeto *tmp = lat_cadena_nueva(mv, buf);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

static const lat_CReg lib_cast[] = {{"logico", lat_logico, 1},
                                    {"numerico", lat_numerico, 1},
                                    {"cadena", lat_cadena, 1},
                                    {NULL, NULL}};

void lat_importar_lib_cast(lat_mv *mv) {
  lat_importar_lib(mv, LIB_CAST_NAME, lib_cast);
}
