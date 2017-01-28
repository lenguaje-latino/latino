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

#include <curl/curl.h>
#include <stdio.h>

#include "latino.h"
#include "latmem.h"
#include "latmv.h"
#include "latgc.h"

#define LIB_CURL_NAME "curl"

struct string {
  char *ptr;
  size_t len;
};

void __curl_init_string(struct string *s) {
  s->len = 0;
  s->ptr = __memoria_asignar(NULL, s->len + 1);
  s->ptr[0] = '\0';
}

size_t __curl_writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = __memoria_reasignar(s->ptr, new_len +1);
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  return size * nmemb;
}

void lat_curl_peticion(lat_mv *mv) {
  lat_objeto *tiempo = lat_desapilar(mv);
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *tmp = NULL;
  int espera;
  if (tiempo->tipo != T_NULL) {
     espera = __numerico(tiempo);
  }
  char *url = __cadena(o);
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    struct string s;
    __curl_init_string(&s);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __curl_writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    if(espera) { curl_easy_setopt(curl, CURLOPT_TIMEOUT, espera); };
    res = curl_easy_perform(curl);
    if (res == CURLE_OPERATION_TIMEDOUT){
      lat_apilar(mv, mv->objeto_falso);
      return;
   } else if (res != CURLE_OK) {
      curl_easy_cleanup(curl);
      lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
                      curl_easy_strerror(res));
    }
    tmp = lat_cadena_nueva(mv, strdup(s.ptr));
    curl_easy_cleanup(curl);
  }
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_curl_escape(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  CURL *curl = curl_easy_init();
  char *texto = __cadena(a);
  if (curl && strlen(texto) > 0) {
    char *output = curl_easy_escape(curl, texto, strlen(texto));
    if (output) {
      lat_objeto *tmp = lat_cadena_nueva(mv, strdup(output));
      lat_apilar(mv, tmp);
      curl_free(output);
      lat_gc_agregar(mv, tmp);
    }
  } else {
    lat_error("Linea %d, %d: %s", a->num_linea, a->num_columna,
                    "se esperaba una cadena mayor");
  }
}

size_t __escribir_datos(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t cdato = fwrite(ptr, size, nmemb, stream);
    return cdato;
}

void lat_curl_descargar(lat_mv *mv) {
   lat_objeto *nombre_archivo = lat_desapilar(mv);
   lat_objeto *url = lat_desapilar(mv);
   CURL *curl;
   FILE *fp;
   CURLcode res;
   curl = curl_easy_init();
   if (curl) {
      fp = fopen(__cadena(nombre_archivo),"wb");
      curl_easy_setopt(curl, CURLOPT_URL, __cadena(url));
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __escribir_datos);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
      res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
         lat_apilar(mv, mv->objeto_falso);
         curl_easy_cleanup(curl);
         return;
      }
      lat_apilar(mv, mv->objeto_verdadero);
      curl_easy_cleanup(curl);
      fclose(fp);
   }
}
static const lat_CReg lib_curl[] = {{"peticion", lat_curl_peticion, 2},
                                    {"escape", lat_curl_escape, 1},
                                    {"descargar", lat_curl_descargar, 2},
                                    {NULL, NULL}};

void lat_importar_lib_curl(lat_mv *mv) {
  lat_importar_lib(mv, LIB_CURL_NAME, lib_curl);
}
