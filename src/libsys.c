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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "latcompat.h"
#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"

#define LIB_SISTEMA_NAME "sistema"

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}


void lat_sistema_ejecutar(lat_mv *mv) {
  lat_objeto *cmd = lat_desapilar(mv);
  system(__cadena(cmd));
}

void lat_sistema_dormir(lat_mv *mv) {
  lat_objeto *mili_segundos = lat_desapilar(mv);
  __lat_sleep(__numerico(mili_segundos));
}

void lat_sistema_pipe(lat_mv *mv) {
  lat_objeto *cmd = lat_desapilar(mv);
  FILE *fp = __lat_popen(mv, __cadena(cmd), "r");
  size_t rlen = MAX_BUFFERSIZE;
  char *p = __memoria_asignar(NULL, rlen);
  fread(p, sizeof(char), rlen, fp);
  rlen = strlen(p);
  p[rlen - 1] = '\0'; // elimina el ultimo '\n'
  lat_objeto *tmp = lat_cadena_nueva(mv, strdup(p));
  lat_apilar(mv, tmp);
  __lat_pclose(mv, fp);
  __memoria_liberar(mv, p);
  lat_gc_agregar(mv, tmp);
}

void lat_sistema_fecha(lat_mv *mv) {
  lat_objeto *tiempo = lat_desapilar(mv);
  char *num = __cadena(tiempo);
  time_t raw;
  struct tm *tipo;
  time(&raw);
  tipo = localtime(&raw);    
  lat_objeto *tmp = mv->objeto_nulo;
  if (!strcmp(num, "seg")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_sec); //segundos    
  } else if (!strcmp(num, "min")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_min);    
  } else if (!strcmp(num, "hora")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_hour);
  } else if (!strcmp(num, "d_mes")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_mday); // dia del mes    
  } else if (!strcmp(num, "mes")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_mon);    
  } else if (!strcmp(num, "año")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_year + 1900);    
  } else if (!strcmp(num, "d_sem")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_wday); // día de la sem.
  } else if (!strcmp(num, "d_año")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_yday); // día del año    
  } else if (!strcmp(num, "estacion")) {
    tmp = lat_numerico_nuevo(mv, tipo->tm_isdst); // verano/inv
  } else {
    lat_error("Linea %d, %d: %s", tiempo->num_linea, tiempo->num_columna,
                    "el formato de tiempo indicado no existe.");
  }
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_sistema_salir(lat_mv *mv) {
  exit(0);
}

static const lat_CReg libsistema[] = {
    {"dormir", lat_sistema_dormir, 1}, {"ejecutar", lat_sistema_ejecutar, 1},
    {"pipe", lat_sistema_pipe, 1},     {"fecha", lat_sistema_fecha, 1},
    {"salir", lat_sistema_salir, 0},   {NULL, NULL}};

void lat_importar_lib_sistema(lat_mv *mv) {
  lat_importar_lib(mv, LIB_SISTEMA_NAME, libsistema);
}
