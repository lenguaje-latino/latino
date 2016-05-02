/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

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

#ifndef _LATINO_H_
#define _LATINO_H_

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include <setjmp.h>

#include "ast.h"
#include "vm.h"

/** \file latino.h
*
* Contiene los macros, definiciones y funciones generales para Latino
*
*/

/** Determina si el sistema es GNU */
#ifdef _WIN32
#define PATH_SEP "\\"
/* Visual Leak Detector for Visual C++ */
//#include <vld.h>
#define LAT_FUNC extern
#define lnsprintf(s, l, f, i) _snprintf(s, l, f, i)
#include <windows.h>
#include <limits.h>
#define ldirectorio_actual(ruta, tamanio) GetCurrentDirectory (MAX_PATH, ruta);
#else
#define PATH_SEP "/"
#define LAT_FUNC __attribute__((visibility("hidden"))) extern
#define lnsprintf(s, l, f, i) snprintf(s, l, f, i)
#include <dlfcn.h>
#include <unistd.h>
#define ldirectorio_actual(ruta, tamanio) getcwd (ruta, tamanio)
#endif

/** Define el manejo de excepciones en Latino */
#define LAT_THROW(L,c)		longjmp((c)->b, 1)
#define LAT_TRY(L,c,a)		if (setjmp((c)->b) == 0) { a }
#define lat_jmpbuf		jmp_buf

/** Version mayor de Latino */
#define LAT_VERSION_MAYOR "0"
/** Version menor de Latino */
#define LAT_VERSION_MENOR "5"
/** Version de correcion de errores */
#define LAT_VERSION_PARCHE "0"
/** Version de Latino */
#define LAT_VERSION "Latino " LAT_VERSION_MAYOR "." LAT_VERSION_MENOR "." LAT_VERSION_PARCHE
/** Derechos de Latino */
#define LAT_DERECHOS LAT_VERSION "\nTodos los derechos reservados (C) 2015-2016. Latinoamerica"

// generado en
// http://www.patorjk.com/software/taag/#p=display&f=Graffiti&t=latino
/**
 Dibuja el logo
 */
#define LAT_LOGO "\n.__          __  .__               \n|  | _____ _/  |_|__| ____   ____  \n|  | \\__  \\\\   __\\  |/    \\ /  _ \\ \n|  |__/ __ \\|  | |  |   |  (  <_> )\n|____(____  /__| |__|___|  /\\____/ \n          \\/             \\/        \n"

/** Afirmar (asset), sirve para testear una condicion */
#define lat_afirmar(cond) ((void)(false && (cond)))

/** Indica si se desea debuguear el parser de bison */
extern int debug;

/** Tamanio maximo de instrucciones bytecode de una funcion */
#define MAX_BYTECODE_FUNCTION (1024 * 10)
/** Tamanio maximo de memoria virtual permitida */
#define MAX_VIRTUAL_MEMORY (1024 * 10)
/** Tamanio maximo de una cadena para ser almacenada en HASH TABLE */
#define MAX_STR_INTERN 64
/** Tamanio maximo de una cadena almacenada dinamicamente */
#define MAX_STR_LENGTH (1024*2)
/** Tamanio maximo de la pila de la maquina virtual */
#define MAX_STACK_SIZE 255

/** Tamanio maximo de una ruta de derectorio */
#define MAX_PATH_LENGTH 1024

/** Tamanio maximo de la entrada por teclado */
#define MAX_INPUT_SIZE 512

/** Interface con flex */
typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;

/** Establece que se definio una interface con Flex */
#define YYLTYPE_IS_DECLARED 1

/** No se requiere cabecera unistd.h */
#define YY_NO_UNISTD_H 1

/** Analiza una cadena como expresion
  *
  * \param expr: cadena a analizar
  * \return ast: Nodo AST
  *
  */
ast* lat_analizar_expresion(lat_vm* vm, char* expr);

/** Analiza un archivo
  *
  * \param ruta: Ruta del archivo a analizar
  * \return ast: Nodo AST
  *
  */
ast* lat_analizar_archivo(lat_vm* vm, char* ruta);

#endif /* _LATINO_H_ */
