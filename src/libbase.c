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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latgc.h"
#include "latino.h"
#include "latmem.h"
#include "latmv.h"

#define LIB_BASE_NAME ""

char *__str_analizar_fmt(const char *s, size_t len);
char *__str_analizar(const char *s, size_t len);

bool __es_legible(const char *archivo) {
  FILE *f = fopen(archivo, "r");
  if (f == NULL) {
    return false;
  }
  fclose(f);
  return true;
}

void __imprimir_objeto(lat_mv *mv, lat_objeto *o, bool fmt) {
  char *tmp = lat_obj2cstring(o);
  char *tmp2 = NULL;
  if (fmt) {
    tmp2 = __str_analizar_fmt(tmp, strlen(tmp));
    fprintf(stdout, "%s", tmp2);
  } else {
    tmp2 = __str_analizar(tmp, strlen(tmp));
    fprintf(stdout, "%s", tmp2);
  }
  __memoria_liberar(mv, tmp);
  __memoria_liberar(mv, tmp2);
}

char *__tipo(int tipo) {
  switch (tipo) {
  case T_NULL:
    return "nulo";
    break;
  case T_BOOL:
    return "logico";
    break;
  case T_NUMERIC:
    return "decimal";
    break;
  case T_STR:
    return "cadena";
    break;
  case T_LIST:
    return "lista";
    break;
  case T_DICT:
    return "diccionario";
    break;
  case T_FUNC:
    return "funcion";
    break;
  case T_CFUNC:
    return "cfuncion";
    break;
  default:
    return "indefinido";
    break;
  }
}

void lat_imprimir(lat_mv *mv) {
  lat_objeto *f = lat_desapilar(mv);
  bool fmt = false;
  if (f == NULL) {
    printf("nulo");
  } else {
    lat_objeto *o = lat_desapilar(mv);
    if (f->tipo != T_NULL) {
      fmt = lat_obj2bool(f);
    }
    __imprimir_objeto(mv, o, fmt);
  }
  printf("\n");
}

void lat_incluir(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  int status;
  lista *modulos = __lista(mv->modulos);
  char dir_actual[MAX_PATH_LENGTH];
  getcwd(dir_actual, sizeof(dir_actual));
  strcat(dir_actual, PATH_SEP);
  char archivo_ext[MAX_STR_INTERN] = {0};
  strcat(archivo_ext, __cadena(o));
  strcat(archivo_ext, ".lat");
  archivo_ext[strlen(archivo_ext)] = '\0';
  // buscar en ruta actual
  lat_objeto *mod =
      lat_cadena_nueva(mv, strdup(strcat(dir_actual, archivo_ext)));
  if (__es_legible(__cadena(mod))) {
    if (!__lista_contiene_valor(modulos, mod)) {
      // printf("buscar con terminacion .lat, buscar en ruta actual: %s\n",
      // __cadena(mod));
      __lista_agregar(modulos, mod);
      ast *nodo = lat_analizar_archivo(__cadena(mod), &status);
      if (status == 0 && nodo != NULL) {
        lat_objeto *funmod = ast_analizar_arbol(mv, nodo);        
        lat_llamar_funcion(mv, funmod);
        ast_liberar(nodo);
        lat_gc_agregar(mv, funmod);        
        return;
      }
    }else{
      return;
    }
  }
  lat_gc_agregar(mv, mod);
  // buscar en $LATINO_LIB  
  char *latino_lib = getenv("LATINO_LIB");
  if (latino_lib != NULL) {
    strcat(latino_lib, PATH_SEP);
    strcat(latino_lib, archivo_ext);
    lat_objeto *mod_lib = lat_cadena_nueva(mv, strdup(latino_lib));
    // printf("buscar con terminacion .lat, buscar en $LATINO_LIB: %s\n",
    // __cadena(mod));
    if (__es_legible(__cadena(mod_lib))) {
      if (!__lista_contiene_valor(modulos, mod_lib)) {
        __lista_agregar(modulos, mod_lib);
        ast *nodo = lat_analizar_archivo(__cadena(mod_lib), &status);
        if (status == 0 && nodo != NULL) {
          lat_objeto *funmod_lib = ast_analizar_arbol(mv, nodo);          
          lat_llamar_funcion(mv, funmod_lib);
          ast_liberar(nodo);
          lat_gc_agregar(mv, funmod_lib);
          return;
        }
      }else{
        return;
      }
    }
    lat_gc_agregar(mv, mod_lib);
  }
  lat_error("Linea %d, %d: %s '%s'", o->num_linea, o->num_columna,
            "No se pudo incluir el modulo", __cadena(o));
}

void lat_leer(lat_mv *mv) {
  char str[MAX_INPUT_SIZE];
  fgets(str, MAX_INPUT_SIZE, stdin);
  int i = strlen(str) - 1;
  if (str[i] == '\n')
    str[i] = '\0';
  // obtiene decimal
  char *ptr;
  double ret;
  ret = strtod(str, &ptr);
  lat_objeto *tmp = NULL;
  if (strcmp(ptr, "") == 0) {
    tmp = lat_numerico_nuevo(mv, ret);
    lat_apilar(mv, tmp);
  } else {
    tmp = lat_cadena_nueva(mv, strdup(str));
    lat_apilar(mv, tmp);
  }
}

void lat_limpiar(lat_mv *mv) { system(__lat_clear); }

void lat_tipo(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = lat_cadena_nueva(mv, strdup(__tipo(a->tipo)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_imprimirf(lat_mv *mv) {
  // TODO: Pendiente implementacion
  /*
  lat_objeto *args = lat_desapilar(mv);
  lat_objeto *fmt = lat_desapilar(mv);
  char *cfmt = __cadena(fmt);*/
}

/*
void imprimirf(const char *formato, ...)
{
va_list ap;
va_start(ap, formato);
vfprintf(stderr, formato, ap);
va_end(ap);
}

imprimirf("hola latino, %s", sksk)
*/

static const lat_CReg lib_base[] = {{"escribir", lat_imprimir, 2},
                                    {"imprimir", lat_imprimir, 2},
                                    {"incluir", lat_incluir, 1},
                                    {"leer", lat_leer, 0},
                                    {"limpiar", lat_limpiar, 0},
                                    {"tipo", lat_tipo, 1},
                                    {NULL, NULL}};

void lat_importar_lib_base(lat_mv *mv) {
  lat_importar_lib(mv, LIB_BASE_NAME, lib_base);
}
