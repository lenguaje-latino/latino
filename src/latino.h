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
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#include "compat.h"
#include "ast.h"
#include "vm.h"

/** \file latino.h
*
* Contiene los macros, definiciones y funciones generales para Latino
*
*/

/** Version mayor de Latino */
#define LAT_VERSION_MAYOR "0"
/** Version menor de Latino */
#define LAT_VERSION_MENOR "8"
/** Version de correcion de errores */
#define LAT_VERSION_PARCHE "2"
/** Version de Latino */
#define LAT_VERSION "Latino " LAT_VERSION_MAYOR "." LAT_VERSION_MENOR "." LAT_VERSION_PARCHE
/** Derechos de Latino */
#define LAT_DERECHOS LAT_VERSION "\nTodos los derechos reservados (C) 2015-2016. Latinoamerica"

/** Define el manejo de excepciones en Latino */
#define LAT_THROW(L,c)		longjmp((c)->b, 1)
#define LAT_TRY(L,c,a)		if (setjmp((c)->b) == 0) { a }
#define lat_jmpbuf		jmp_buf

// generado en
// http://www.patorjk.com/software/taag/#p=display&f=Graffiti&t=latino
/**
 Dibuja el logo
 */
#define LAT_LOGO "\n.__          __  .__               \n|  | _____ _/  |_|__| ____   ____  \n|  | \\__  \\\\   __\\  |/    \\ /  _ \\ \n|  |__/ __ \\|  | |  |   |  (  <_> )\n|____(____  /__| |__|___|  /\\____/ \n          \\/             \\/        \n"

/** Afirmar (asset), sirve para testear una condicion */
#define lat_afirmar(cond) ((void)(false && (cond)))

/* Envia un mensaje de error */
#define lat_error(M, ...)                               \
  {                                                   \
    fprintf(stderr, "Error: " M "\n", ##__VA_ARGS__); \
  }

/* Envia un mensaje de error */
#define lat_fatal_error(M, ...)                               \
  {                                                   \
    fprintf(stderr, "Error: " M "\n", ##__VA_ARGS__); \
    exit(1);  \
  }

/** Indica si se desea debuguear el parser de bison */
extern int debug;

/** Indica que el parser no debe de devolver errores, se usa para REPL */
extern int parse_silent;

/** Maximo numero de size_t */
#ifdef SIZE_MAX
#define LAT_SIZE_MAX SIZE_MAX
#else
#define LAT_SIZE_MAX ((size_t)-1)
#endif

/** Tamanio maximo de instrucciones bytecode de una funcion */
#define MAX_BYTECODE_FUNCTION (1024*10)
/** Tamanio maximo de memoria virtual permitida*/
#define MAX_VIRTUAL_MEMORY (1024*128)
/** Tamanio maximo de una cadena para ser almacenada en HASH TABLE */
#define MAX_STR_INTERN 64
/** Tamanio maximo de una cadena almacenada dinamicamente*/
//#define MAX_STR_LENGTH (1024*100)
#define MAX_STR_LENGTH (1024*1024)
/** Tamanio maximo de la pila de la maquina virtual */
#define MAX_STACK_SIZE 255
/** Tamanio maximo de una ruta de derectorio */
#define MAX_PATH_LENGTH 1024
/** Tamanio maximo de la entrada por teclado */
#define MAX_INPUT_SIZE 512
/** Maximo numero de llamadas recursivas a funcion */
#define MAX_CALL_FUNCTION 27
/** Maximo numero de caracteres para un identificador */
#define MAX_ID_LENGTH 32
/** Maximo numero de bits para un buffer */
#define MAX_BUFFERSIZE BUFSIZ

/** Interface con flex */
typedef struct YYLTYPE
{
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
ast* lat_analizar_expresion(char* expr, int* status);

/** Analiza un archivo
  *
  * \param ruta: Ruta del archivo a analizar
  * \return ast: Nodo AST
  *
  */
ast* lat_analizar_archivo(char* ruta, int* status);
#endif /* _LATINO_H_ */
