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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latino.h"

#define LIB_BASE_NAME ""

char *analizar_fmt(const char *s, size_t len);
char *analizar(const char *s, size_t len);

static bool eslegible(const char *archivo) {
    FILE *f = fopen(archivo, "r");
    if (f == NULL) {
        return false;
    }
    fclose(f);
    return true;
}

char *tipo(int tipo) {
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
        case T_DIC:
            return "diccionario";
            break;
        case T_FUN:
            return "fun";
            break;
        case T_CFUN:
            return "cfun";
            break;
        default:
            return "indefinido";
            break;
    }
}

void base_poner(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    latO_imprimir(mv, o, false);
    printf("\n");
}

void str_formato(lat_mv *mv);

void base_imprimirf(lat_mv *mv) {
    // FIXME: Imprimir todos los formatos de C / C++
    str_formato(mv);
    lat_objeto *str = latC_desapilar(mv);
    latO_imprimir(mv, str, true);
}

int ultima_pos(char *base, char *str);
char *subcadena(const char *str, int beg, int n);

static void base_incluir(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    char *libname = latC_checar_cadena(mv, o);
    int status;
    char dir_actual[MAX_PATH_LENGTH];
    getcwd(dir_actual, sizeof(dir_actual));
    strcat(dir_actual, PATH_SEP);
    char archivo_ext[MAX_STR_INTERN] = {0};
    strcat(archivo_ext, libname);
    strcat(archivo_ext, ".lat");
    archivo_ext[strlen(archivo_ext)] = '\0';
    // buscar en ruta actual
    lat_objeto *mod = latC_crear_cadena(mv, strcat(dir_actual, archivo_ext));
    char *tmp_name = mv->nombre_archivo;
    if (eslegible(latC_checar_cadena(mv, mod))) {
        mv->nombre_archivo = latC_checar_cadena(mv, mod);
        ast *nodo = latA_analizar_arch(latC_checar_cadena(mv, mod), &status);
        if (status == 0 && nodo != NULL) {
            // FIXME: Liberar la memoria de fun_mod
            lat_objeto *fun_mod = latC_analizar(mv, nodo);
            status = latC_llamar_funcion(mv, fun_mod);
            mv->nombre_archivo = tmp_name;
            latA_destruir(nodo);
            return;
        }
    }
    // busca en ruta del archivo que incluye
    int pos = ultima_pos(mv->nombre_archivo, PATH_SEP);
    if (pos > -1) {
        char *prepath = calloc(1, MAX_PATH_LENGTH);
        strcat(prepath, subcadena(mv->nombre_archivo, 0, pos + 1));
        lat_objeto *modcurr =
            latC_crear_cadena(mv, strcat(prepath, archivo_ext));
        tmp_name = mv->nombre_archivo;
        if (eslegible(latC_checar_cadena(mv, modcurr))) {
            mv->nombre_archivo = latC_checar_cadena(mv, modcurr);
            ast *nodo =
                latA_analizar_arch(latC_checar_cadena(mv, modcurr), &status);
            if (status == 0 && nodo != NULL) {
                // FIXME: Liberar la memoria de fun_mod
                lat_objeto *fun_mod = latC_analizar(mv, nodo);
                status = latC_llamar_funcion(mv, fun_mod);
                mv->nombre_archivo = tmp_name;
                latA_destruir(nodo);
                return;
            }
        }
    }
    // buscar en $LATINO_LIB
    char *latino_lib = getenv("LATINO_LIB");
    if (latino_lib != NULL) {
        char lib_path[MAX_PATH_LENGTH] = {0};
        strcpy(lib_path, latino_lib);
        strcat(lib_path, PATH_SEP);
        strcat(lib_path, archivo_ext);
        lat_objeto *mod_lib = latC_crear_cadena(mv, lib_path);
        if (eslegible(latC_checar_cadena(mv, mod_lib))) {
            mv->nombre_archivo = latC_checar_cadena(mv, mod_lib);
            ast *nodo =
                latA_analizar_arch(latC_checar_cadena(mv, mod_lib), &status);
            if (status == 0 && nodo != NULL) {
                // FIXME: Liberar la memoria de fun_mod_lib
                lat_objeto *fun_mod_lib = latC_analizar(mv, nodo);
                status = latC_llamar_funcion(mv, fun_mod_lib);
                mv->nombre_archivo = tmp_name;
                latA_destruir(nodo);
                return;
            }
        }
    }
    // buscamos libreria dinamica
    char libpath[MAX_PATH_LENGTH] = {0};
    char funcname[MAX_ID_LENGTH] = {0};
#ifdef _WIN32
    strcat(libpath, "latino-");
#else
    strcat(libpath, "liblatino-");
#endif
    strcat(libpath, libname);
#ifdef _WIN32
    strcat(libpath, ".dll");
#elif __APPLE__
    strcat(libpath, ".dylib");
#else
    strcat(libpath, ".so");
#endif
    strcat(funcname, "latC_abrir_liblatino_");
    strcat(funcname, libname);
    int stat = latC_cargarlib(mv, libpath, funcname);
    if (stat != 0) {
        latC_error(mv, "Error al cargar libreria dinamica '%s'", libpath);
    }
}

static void base_leer(lat_mv *mv) {
    char *str = calloc(1, MAX_INPUT_SIZE);
#if (defined __WIN32__) || (defined _WIN32)
    str = latC_leer_linea(str);
#else
    str = latC_leer_linea(NULL);
#endif

    int i = strlen(str) - 1;
    if (str[i] == '\n') {
        str[i] = '\0';
    }
    char *ptr;
    double ret;
    ret = strtod(str, &ptr);
    lat_objeto *tmp = NULL;
    if (!strcmp(ptr, "")) {
        tmp = latC_crear_numerico(mv, ret);
        latC_apilar(mv, tmp);
    } else {
        tmp = latC_crear_cadena(mv, str);
        latC_apilar(mv, tmp);
    }
}

static void base_limpiar(lat_mv *mv) { system(latC_clear); }

static void base_tipo(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    latC_apilar_string(mv, tipo(a->tipo));
}

static void base_alogico(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    lat_objeto *tmp = latC_abool(mv, o) == true ? latO_verdadero : latO_falso;
    latC_apilar(mv, tmp);
}

static void base_anumero(lat_mv *mv) {
    // FIXME: Error cuando la cadena contiene separadores de miles (,)
    lat_objeto *o = latC_desapilar(mv);
    double var = latC_adouble(mv, o);
    if (!var) {
        latC_apilar(mv, latO_nulo);
        return;
    }
    lat_objeto *tmp = latC_crear_numerico(mv, var);
    latC_apilar(mv, tmp);
}

static void base_acadena(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    char *buf = latC_astring(mv, o);
    lat_objeto *tmp = latC_crear_cadena(mv, buf);
    latC_apilar(mv, tmp);
    free(buf);
}

static void base_error(lat_mv *mv) {
    str_formato(mv);
    lat_objeto *error = latC_desapilar(mv);
    latC_error(mv, "%s", latC_checar_cadena(mv, error));
}

static void base_beep(lat_mv *mv) {
    fprintf(stderr, "\x7");
    fflush(stderr);
}

static const lat_CReg libbase[] = {
    {"poner", base_poner, 1},
    {"escribir", base_poner, 1},
    {"imprimir", base_poner, 1},
    {"acadena", base_acadena, 1},
    {"anumero", base_anumero, 1},
    {"alogico", base_alogico, 1},
    {"incluir", base_incluir, 1},
    {"leer", base_leer, 0},
    {"limpiar", base_limpiar, 0},
    {"tipo", base_tipo, 1},
    {"imprimirf", base_imprimirf, FUNCION_VAR_ARGS},
    {"error", base_error, FUNCION_VAR_ARGS},
    {"beep", base_beep, 0},
    {NULL, NULL}};

void latC_abrir_liblatino_baselib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_BASE_NAME, libbase);
}
