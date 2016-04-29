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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "linenoise/linenoise.h"
#include "latino.h"
#include "parse.h"
#include "lex.h"
#include "ast.h"

/* 1 para debuguear analizador */
int yydebug = 0;

static FILE *file;
static char *buffer;

int yyparse(ast **root, yyscan_t scanner);

ast *lat_analizar_expresion(lat_vm* vm, char *expr) {
  setlocale (LC_ALL, "");
  ast *ret = NULL;
  yyscan_t scanner;
  YY_BUFFER_STATE state;
  lex_state scan_state = {.insert = 0};
  yylex_init_extra(&scan_state, &scanner);
  state = yy_scan_string(expr, scanner);
  yyparse(&ret, scanner);
  yy_delete_buffer(state, scanner);
  yylex_destroy(scanner);
  return ret;
}

ast *lat_analizar_archivo(lat_vm* vm, char *infile) {
  if (infile == NULL) {
    printf("Especifique un archivo\n");
    return NULL;
  }
  char *dot = strrchr(infile, '.');
  char *extension;
  if (!dot || dot == infile) {
    extension = "";
  }else{
    extension = dot + 1;
  }
  if (strcmp(extension, "lat") != 0) {
    printf("El archivo no contiene la extension .lat\n");
    return NULL;
  }
  file = fopen(infile, "r");
  if (file == NULL) {
    printf("No se pudo abrir el archivo\n");
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  int fsize = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer = calloc(fsize, 1);
  size_t newSize = fread(buffer, sizeof(char), fsize, file);
  if (buffer == NULL) {
    printf("No se pudo asignar %d bytes de memoria\n", fsize);
    return NULL;
  }
  buffer[newSize] = '\0';
  return lat_analizar_expresion(vm, buffer);
}
/**
 * Muestra la version de latino en la consola
 */
void lat_version(){
    printf("%s\n", LAT_DERECHOS);
}
/**
 * Para crear el logo en ascii
 */
void lat_logo(){
    printf("%s\n", LAT_LOGO);
}

/**
 * Muestra la ayuda en la consola
 */
void lat_ayuda(){
    lat_logo();
    lat_version();
    printf("%s\n", "Uso de latino: latino [opcion] [archivo]");
    printf("\n");
    printf("%s\n", "Opciones:");
    printf("%s\n", "-a           : Muestra la ayuda de Latino");
    printf("%s\n", "-i           : Inicia el interprete de Latino (Modo interactivo)");
    printf("%s\n", "-v           : Muestra la version de Latino");
    printf("%s\n", "archivo      : Nombre del archivo con extension .lat");
    printf("%s\n", "Ctrl-C       : Para cerrar");
    printf("\n");
    printf("%s\n", "Variables de entorno:");
    printf("%s\n", "_____________________");
    printf("%s%s\n", "LATINO_PATH  : ", getenv("LATINO_PATH"));
    printf("%s%s\n", "LATINO_LIB  : ", getenv("LATINO_LIB"));
    printf("%s%s\n", "LC_LANG      : ", getenv("LC_LANG"));
    printf("%s%s\n", "HOME         : ", getenv("HOME"));
}

static void lat_repl(lat_vm *vm)
{
	char *input;
	char *buffer;
	while ((input = linenoise("latino> ")) != NULL) {
		if (input[0] != '\0') {
			buffer = calloc(strlen(input) + 1, sizeof(char));
			strcpy(buffer, input);
			buffer[strlen(input)] = '\n';
			lat_objeto *curexpr = nodo_analizar_arbol(vm, lat_analizar_expresion(vm, buffer));
			lat_llamar_funcion(vm, curexpr);
		}
	}
}

int main(int argc, char *argv[]) {
  /*
  Para debuguear en visual studio:
  Menu propiedades del proyecto-> Debugging -> Command Arguments. Agregar
  $(SolutionDir)..\ejemplos\debug.lat
  */

  int i;
  char *infile = NULL;
  lat_vm *vm = lat_crear_maquina_virtual();
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) {
      lat_version();
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-a") == 0) {
      lat_ayuda();
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-i") == 0) {
      lat_version();
      lat_repl(vm);
      return EXIT_SUCCESS;
    } else{
      infile = argv[i];
    }
  }
  if(argc > 1 && infile != NULL) {
    ast *tree = lat_analizar_archivo(vm, infile);
    if (!tree) {
      return EXIT_FAILURE;
    }
    lat_objeto *mainFunc = nodo_analizar_arbol(vm, tree);
    lat_llamar_funcion(vm, mainFunc);
    lat_apilar(vm, vm->regs[255]);
    if(file != NULL)
    {
      fclose(file);
    }
  }
  else{
#ifdef _WIN32
    system("cmd");
#else
    lat_version();
    lat_repl(vm);
#endif
  }

  return EXIT_SUCCESS;
}
