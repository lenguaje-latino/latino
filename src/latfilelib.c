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

#include "latino.h"

// Define en donde el comando Escribir escribira
#define _inicio 0
#define _final -1

#define LIB_ARCHIVO_NAME "archivo"

static size_t file_leerlinea(char **lineptr, size_t *n, FILE *stream) {
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
        ptr = realloc(*lineptr, 256);
        *lineptr = ptr;
        *n = 256;
    }
    strcpy(*lineptr, line);
    return (len);
}

static void file_lineas(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    FILE *fp;
    char *buf = NULL;
    size_t len = 0;
    char *path = latC_checar_cadena(mv, o);
    fp = fopen(path, "r");
    if (fp == NULL) {
        latC_error(mv, "No se pudo abrir el archivo '%s'", path);
    }
    lat_objeto *lineas = latC_crear_lista(mv, latL_crear(mv));
    while ((len = file_leerlinea(&buf, &len, fp)) != -1) {
        latL_agregar(mv, latC_checar_lista(mv, lineas),
                     latC_crear_cadena(mv, buf));
    }
    fclose(fp);
    latC_apilar(mv, lineas);
}

static void file_leer(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    FILE *archivo = fopen(latC_checar_cadena(mv, o), "r");
    if (archivo == NULL) {
        latC_apilar(mv, latO_falso);
        return;
    }
    char *final;
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
    latC_apilar(mv, latC_crear_cadena(mv, final));
    free(final);
}

static void file_escribir(lat_mv *mv) {
    lat_objeto *s = latC_desapilar(mv);
    lat_objeto *o = latC_desapilar(mv);
    if (o->tipo == T_STR) {
        FILE *fp;
        fp = fopen(latC_checar_cadena(mv, o), "w");
        const char *cad = latC_checar_cadena(mv, s);
        size_t lon = strlen(cad);
        fwrite(cad, 1, lon, fp);
        fclose(fp);
    } else {
        latC_error(mv, "No se pudo poner en el archivo '%s'",
                   latC_checar_cadena(mv, o));
    }
}

static void file_ejecutar(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    char *input = latC_checar_cadena(mv, o);
    char *dot = strrchr(input, '.');
    char *extension;
    if (!dot || dot == input) {
        extension = "";
    } else {
        extension = dot + 1;
    }
    if (!strcmp(extension, "lat")) {
        int status;
        ast *nodo = latA_analizar_arch(input, &status);
        if (!nodo) {
            latC_error(mv, "Error al leer el archivo: '%s'", input);
        }
        mv->global->REPL = false;
        mv->nombre_archivo = input;
        lat_objeto *func = latC_analizar(mv, nodo);
        if (status == 0) {
            status = latC_llamar_funcion(mv, func);
            latO_destruir(mv, func);
            latA_destruir(nodo);
        } else {
            latC_error(mv, "Error al ejecutar archivo '%s'", input);
        }
    }
}

static void file_duplicar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    char *aa = latC_checar_cadena(mv, a);
    char *bb = latC_checar_cadena(mv, b);
    if (strcmp(aa, bb) == 0) {
        latC_error(
            mv,
            "Error al duplicar archivo '%s', nombre o ruta deven ser distintos",
            latC_checar_cadena(mv, b));
    } else {
        FILE *archivo, *copiar;
        int txt;
        archivo = fopen(latC_checar_cadena(mv, a), "r");
        copiar = fopen(latC_checar_cadena(mv, b), "wb");
        if (!archivo) {
            latC_error(mv, "Error: No se pudo abrir el archivo '%s'",
                       latC_checar_cadena(mv, a));
        } else if (!copiar) {
            latC_error(mv, "Error: No se pudo abrir el archivo '%s'",
                       latC_checar_cadena(mv, b));
        }
        while ((txt = fgetc(archivo)) != EOF)
            fputc(txt, copiar);
        fclose(archivo);
        fclose(copiar);
    }
}

static void file_eliminar(lat_mv *mv) {
    int status;
    lat_objeto *a = latC_desapilar(mv);
    status = remove(latC_checar_cadena(mv, a));
    if (status == 0) {
        latC_apilar(mv, latO_verdadero);
    } else {
        latC_apilar(mv, latO_falso);
    }
}

static void file_crear(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    FILE *archivo;
    archivo = fopen(latC_checar_cadena(mv, a), "r");
    if (archivo == NULL) {
        archivo = fopen(latC_checar_cadena(mv, a), "wb");
        latC_apilar(mv, latO_verdadero);
    } else {
        latC_apilar(mv, latO_falso);
    }
    fclose(archivo);
}

static void file_renombrar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    char *nuevo = (char *)malloc(MAX_ID_LENGTH);
    strcpy(nuevo, "");
    strcpy(nuevo, latC_checar_cadena(mv, b));
    bool ret = rename(latC_checar_cadena(mv, a), nuevo);
    if (!ret) {
        latC_apilar(mv, latC_crear_cadena(mv, nuevo));
    } else {
        latC_apilar(mv, latO_falso);
    }
    free(nuevo);
}

static void file_anexar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    FILE *archivo = fopen(latC_checar_cadena(mv, a), "a");
    fprintf(archivo, "%s", latC_checar_cadena(mv, b));
    fclose(archivo);
}

static const lat_CReg libfile[] = {{"leer", file_leer, 1},
                                   {"lineas", file_lineas, 1},
                                   {"ejecutar", file_ejecutar, 1},
                                   {"escribir", file_escribir, 2},
                                   {"duplicar", file_duplicar, 2},
                                   {"anexar", file_anexar, 2},
                                   {"eliminar", file_eliminar, 1},
                                   {"borrar", file_eliminar, 1},
                                   {"crear", file_crear, 1},
                                   {"renombrar", file_renombrar, 2},
                                   {NULL, NULL}};

void latC_abrir_liblatino_filelib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_ARCHIVO_NAME, libfile);
}
//agregar funcion de elegiar donde escribir
// {"escribir", file_escribir, 3},
// archivo.escribir("archivo1.lat", "a�adir", 10)
//https://medium.com/10-goto-10/manejo-de-archivos-en-c-19f85b31ddd