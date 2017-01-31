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

#include "latgc.h"
#include "latino.h"
#include "latmem.h"
#include "latmv.h"

#define LIB_ARCHIVO_NAME "archivo"

static size_t __file_leer_linea(char **lineptr, size_t *n, FILE *stream) {
  static char line[256];
  char *ptr;
  size_t len;
  if (lineptr == NULL || n == NULL) {
    errno = EINVAL;
    return -1;
  }
  if (ferror(stream)) {
    return -1;
  }
  if (feof(stream)) {
    return -1;
  }
  fgets(line, 256, stream);
  ptr = strchr(line, '\n');
  if (ptr) {
    *ptr = '\0';
  } else {
    return -1;
  }
  len = strlen(line);
  if ((len + 1) < 256) {
    ptr = __memoria_reasignar(*lineptr, 256);
    *lineptr = ptr;
    *n = 256;
  }
  strcpy(*lineptr, line);
  return (len);
}

void lat_archivo_lineas(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  FILE *fp;
  char *buf = NULL;
  size_t len = 0;
  char *path = __cadena(o);
  fp = fopen(path, "r");
  if (fp == NULL) {
    filename = o->nombre_archivo;
    lat_error("Linea %d, %d: %s", o->num_linea, o->num_columna,
                    "No se pudo abrir el archivo\n");
  }
  lat_objeto *lineas = lat_lista_nueva(mv, __lista_crear());
  while ((len = __file_leer_linea(&buf, &len, fp)) != -1) {
    __lista_agregar(__lista(lineas), lat_cadena_nueva(mv, strdup(buf)));
  }
  fclose(fp);
  lat_apilar(mv, lineas);
  lat_gc_agregar(mv, lineas);
}

void lat_archivo_leer(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  FILE *archivo = fopen(__cadena(o), "r");
  if (archivo == NULL) {
      lat_apilar(mv, mv->objeto_falso);
      return;
  }
  char * final;
  size_t n = 0;
  int c;
  fseek(archivo, 0, SEEK_END);
  long f_size = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);
  final = malloc(f_size + 1);
  while ((c = fgetc(archivo)) != EOF) {
    final[n++] = (char)c;
  }
  final[n] = '\0';
  fclose(archivo);
  char *archivo_leido = strdup(final);
  lat_apilar(mv, lat_cadena_nueva(mv, archivo_leido));
  lat_gc_agregar(mv, lat_cadena_nueva(mv, archivo_leido));
  //free(archivo_leido);
}

void lat_archivo_escribir(lat_mv *mv) {
  lat_objeto *s = lat_desapilar(mv);
  lat_objeto *o = lat_desapilar(mv);
  if (o->tipo == T_STR) {
    FILE *fp;
    fp = fopen(__cadena(o), "w");
    const char *cad = __cadena(s);
    size_t lon = strlen(cad);
    fwrite(cad, 1, lon, fp);
    fclose(fp);
  } else {
    filename = o->nombre_archivo;
    lat_error("Linea %d, %d: %s %s\n", o->num_linea, o->num_columna,
                    "No se pudo escribir en el archivo", __cadena(o));
  }
}

void lat_archivo_ejecutar(lat_mv *mv) {
  lat_objeto *o = lat_desapilar(mv);
  char *input = __cadena(o);
  char *dot = strrchr(input, '.');
  char *extension;
  if (!dot || dot == input) {
    extension = "";
  } else {
    extension = dot + 1;
  }
  if (strcmp(extension, "lat") == 0) {
    int status;
    ast *tree = lat_analizar_archivo(input, &status);
    if (!tree) {
      filename = o->nombre_archivo;
      lat_error("Al leer el archivo: %s", input);
    }
    mv->REPL = false;
    mv->nombre_archivo = input;
    lat_objeto *func = ast_analizar_arbol(mv, tree);
    if (status == 0) {
      lat_llamar_funcion(mv, func);
      //__obj_eliminar(mv, func);
    } else {
      filename = o->nombre_archivo;
      lat_error("Error al ejeuctar archivo: %s\n", input);
    }
  }
}

void lat_archivo_copiar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  FILE *archivo = fopen(__cadena(a), "a");
  fprintf(archivo, "%s", __cadena(b));
  fclose(archivo);
}

void lat_archivo_eliminar(lat_mv *mv) {
   int status;
   lat_objeto *a = lat_desapilar(mv);

   status = remove(__cadena(a));
   if( status == 0 ) {
      lat_apilar(mv, mv->objeto_verdadero);
   } else {
      lat_apilar(mv, mv->objeto_falso);
   }
}

void lat_archivo_crear(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  FILE *archivo;
  archivo = fopen(__cadena(a), "r");
  if(archivo == NULL) {
     archivo = fopen(__cadena(a), "wb");
     lat_apilar(mv, mv->objeto_verdadero);
  } else {
     lat_apilar(mv, mv->objeto_falso);
  }
}

void lat_archivo_renombrar(lat_mv *mv) {
   lat_objeto *b = lat_desapilar(mv);
   lat_objeto *a = lat_desapilar(mv);
   char *nuevo = __cadena(b);
   bool ret = rename(__cadena(a), nuevo);
   if(!ret) {
      lat_apilar(mv, lat_cadena_nueva(mv, nuevo));
   } else {
      lat_apilar(mv, mv->objeto_falso);
   }
}

static const lat_CReg lib_archivo[] = {{"leer", lat_archivo_leer, 1},
                                       {"lineas", lat_archivo_lineas, 1},
                                       {"ejecutar", lat_archivo_ejecutar, 1},
                                       {"escribir", lat_archivo_escribir, 2},
                                       {"copiar", lat_archivo_copiar, 2},
                                       {"eliminar", lat_archivo_eliminar, 1},
                                       {"crear", lat_archivo_crear, 1},
                                       {"renombrar", lat_archivo_renombrar, 2},
                                       {NULL, NULL}};

void lat_importar_lib_archivo(lat_mv *mv) {
  lat_importar_lib(mv, LIB_ARCHIVO_NAME, lib_archivo);
}
