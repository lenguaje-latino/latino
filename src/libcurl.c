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
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *tmp = NULL;
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
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
                      curl_easy_strerror(res));
    }
    tmp = lat_cadena_nueva(mv, strdup(s.ptr));
    curl_easy_cleanup(curl);
  }
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_curl_escape_url(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  CURL *curl = curl_easy_init();
  char *texto = __cadena(a);
  if (curl && strlen(texto) > 0) {
    char *output = curl_easy_escape(curl, texto, strlen(texto));
    if (output) {
      lat_objeto *tmp = lat_cadena_nueva(mv, output);
      lat_apilar(mv, tmp);
      curl_free(output);
      lat_gc_agregar(mv, tmp);
    }
  } else {
    lat_error("Linea %d, %d: %s", a->num_linea, a->num_columna,
                    "se esperaba una cadena mayor");
  }
}

static const lat_CReg lib_curl[] = {{"peticion", lat_curl_peticion, 1},
                                    {"url_escape", lat_curl_escape_url, 1},
                                    {NULL, NULL}};

void lat_importar_lib_curl(lat_mv *mv) {
  lat_importar_lib(mv, LIB_CURL_NAME, lib_curl);
}
