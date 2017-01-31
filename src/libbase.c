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

#include <readline/readline.h>
#include <readline/history.h>

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
    printf("%s", tmp2);
  } else {
    tmp2 = __str_analizar(tmp, strlen(tmp));
    printf("%s", tmp2);
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

void lat_imprimirf(lat_mv *mv) {
  // para funciones var_arg se obtiene el numero de parametros enviados
  lat_objeto *num_params = lat_desapilar(mv);
  int top = __numerico(num_params);
  int arg = 1;
  int i = 0;
  lista *params = __lista_crear();
  while (i < top) {
    __lista_insertar_inicio(params, lat_desapilar(mv));
    i++;
  }
  lat_objeto *ofmt = __lista_extraer_inicio(params);
  if (ofmt == NULL) {
    printf("nulo\n");
    return;
  }
  char *strfrmt = __cadena(ofmt);
  char *strfrmt_end = strfrmt + strlen(strfrmt);
  char *b = __memoria_asignar(mv, MAX_STR_LENGTH);
  while (strfrmt < strfrmt_end) {
    if (*strfrmt != '%') {
      sprintf(b, "%s%c", b, *strfrmt++);
    } else if (*++strfrmt == '%') {
      sprintf(b, "%s%c", b, *strfrmt++);
    } else {
      char buff[1024];
      if (++arg > top) {
        filename = ofmt->nombre_archivo;
        lat_error("Linea %d, %d: %s", ofmt->num_linea, ofmt->num_columna,
                  "Numero de argumentos invalido para el formato.");
      }
      switch (*strfrmt++) {
      case 'c': {
        lat_objeto *cr = __lista_extraer_inicio(params);
        sprintf(buff, "%c", (int)lat_obj2double(cr));
      } break;
      case 'i': {
        lat_objeto *ent = __lista_extraer_inicio(params);
        sprintf(buff, "%i", (int)lat_obj2double(ent));
      } break;
      case 'f': {
        lat_objeto *dec = __lista_extraer_inicio(params);
        sprintf(buff, "%f", (float)lat_obj2double(dec));
      } break;
      case 'd': {
        lat_objeto *dec = __lista_extraer_inicio(params);
        sprintf(buff, LAT_NUMERIC_FMT, lat_obj2double(dec));
      } break;
      case 's': {
        lat_objeto *str = __lista_extraer_inicio(params);
        sprintf(buff, "%s", lat_obj2cstring(str));
      } break;
      default: {
        filename = ofmt->nombre_archivo;
        lat_error("Linea %d, %d: %s", ofmt->num_linea, ofmt->num_columna,
                  "Opcion de formato invalida.");
      }
      }
      strcat(b, buff);
    }
  }
  lat_objeto *f = lat_cadena_nueva(mv, b);
  __imprimir_objeto(mv, f, true);
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
  char *tmp_name = mv->nombre_archivo;
  if (__es_legible(__cadena(mod))) {
    // if (!__lista_contiene_valor(modulos, mod)) {
    // printf("buscar con terminacion .lat, buscar en ruta actual: %s\n",
    // __cadena(mod));
    //__lista_agregar(modulos, mod);
      mv->nombre_archivo = __cadena(mod);
    ast *nodo = lat_analizar_archivo(__cadena(mod), &status);    
    if (status == 0 && nodo != NULL) {      
      lat_objeto *funmod = ast_analizar_arbol(mv, nodo);
      lat_llamar_funcion(mv, funmod);
      //FIX: Memory leak
      //ast_liberar(nodo);
      lat_gc_agregar(mv, funmod);
      mv->nombre_archivo = tmp_name;
      return;
    }
    /*}else{
      return;
    }*/
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
    // if (__es_legible(__cadena(mod_lib))) {
    if (!__lista_contiene_valor(modulos, mod_lib)) {
      __lista_agregar(modulos, mod_lib);
      mv->nombre_archivo = __cadena(mod_lib);
      ast *nodo = lat_analizar_archivo(__cadena(mod_lib), &status);      
      if (status == 0 && nodo != NULL) {
        lat_objeto *funmod_lib = ast_analizar_arbol(mv, nodo);
        lat_llamar_funcion(mv, funmod_lib);
        //FIX: Memory leak
        //ast_liberar(nodo);
        lat_gc_agregar(mv, funmod_lib);
        mv->nombre_archivo = tmp_name;
        return;
      }
      /*}else{
        return;
      }*/
    }
    lat_gc_agregar(mv, mod_lib);
  }
  filename = o->nombre_archivo;
  lat_error("Linea %d, %d: %s '%s'", o->num_linea, o->num_columna,
            "No se pudo incluir el modulo", __cadena(o));
}

void lat_leer(lat_mv *mv) {  
  char *str = __memoria_asignar(NULL, MAX_INPUT_SIZE);
  str = readline(NULL);
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

// convertir

double lat_tonumber(lat_objeto *o) {
  switch (o->tipo) {
  case T_NULL:
    return 0;
    break;
  case T_BOOL:
    return __logico(o) == false ? 0 : 1;
    break;
  case T_NUMERIC:
    return __numerico(o);
    break;
  case T_STR: {
    char *ptr;
    double ret;
    ret = strtod(__cadena(o), &ptr);
    if (strcmp(ptr, "") == 0) {
      return ret;
    }
  } break;
  case T_LIST:
    return __lista_longitud(__lista(o));
    break;
  case T_DICT:
    return __dic_longitud(__dic(o));
    break;
  default:
    break;
  }
  return 0;
}

void lat_alogico(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  lat_objeto *tmp =
      lat_obj2bool(o) == true ? mv->objeto_verdadero : mv->objeto_falso;
  lat_apilar(mv, tmp);
}

void lat_anumero(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  double var = lat_tonumber(o);
  if (!var) {
    lat_apilar(mv, mv->objeto_nulo);
    return;
  }
  lat_objeto *tmp = lat_numerico_nuevo(mv, var);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_acadena(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  char *buf = lat_obj2cstring(o);
  lat_objeto *tmp = lat_cadena_nueva(mv, buf);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

static const lat_CReg lib_base[] = {
    {"escribir", lat_imprimir, 2}, {"escribirf", lat_imprimirf, -1},
    {"imprimir", lat_imprimir, 2}, {"imprimirf", lat_imprimirf, -1},
    {"acadena", lat_acadena, 1},   {"anumero", lat_anumero, 1},
    {"alogico", lat_alogico, 1},   {"incluir", lat_incluir, 1},
    {"leer", lat_leer, 0},         {"limpiar", lat_limpiar, 0},
    {"tipo", lat_tipo, 1},         {NULL, NULL}};

void lat_importar_lib_base(lat_mv *mv) {
  lat_importar_lib(mv, LIB_BASE_NAME, lib_base);
}
