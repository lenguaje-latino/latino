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
#include <string.h>

#include "latino.h"
#include "parse.h"
#include "lex.h"
#include "ast.h"

#ifndef WINDOWS
#include <locale.h>
#include "linenoise/linenoise.h"
#endif

/* 1 para debuguear analizador */
int yydebug = 0;
int debug = 1;

static FILE *file;
static char *buffer;

int yyparse(ast **expression, yyscan_t scanner);

ast *lat_analizar_expresion(char *expr) {
#ifndef WINDOWS
setlocale (LC_MESSAGES, "");
#endif // WINDOWS
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

ast *lat_analizar_archivo(char *infile) {
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
  return lat_analizar_expresion(buffer);
}

void lat_version(){
    printf("%s\n", LAT_DERECHOS);
}

#ifndef WINDOWS
void latino_repl(lat_vm *vm)
{
  linenoiseSetMultiLine(1);
	char *input;
	char *buffer;
	while ((input = linenoise("latino> ")) != NULL) {
		if (input[0] != '\0') {
			buffer = calloc(strlen(input) + 1, sizeof(char));
			strcpy(buffer, input);
			buffer[strlen(input)] = '\n';
			//linenoiseHistoryAdd(input);
			lat_objeto *curexpr = nodo_analizar_arbol(vm, lat_analizar_expresion(buffer));
			lat_llamar_funcion(vm, curexpr);
		}
	}
}
#endif

int main(int argc, char *argv[]) {
  /*
  Para debuguear en visual studio:
  Menu propiedades del proyecto-> Debugging -> Command Arguments. Agregar
  $(SolutionDir)..\ejemplos\debug.lat
  */

  int i;
  char *infile = NULL;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      debug = 1;
    } else if (strcmp(argv[i], "--version") == 0) {
      lat_version();
      return EXIT_SUCCESS;
    } else{
      infile = argv[i];
    }
  }

  if(argc > 1) {
    ast *tree = lat_analizar_archivo(infile);
    if (!tree) {
      return EXIT_FAILURE;
    }
    lat_vm *vm = lat_crear_maquina_virtual();
    lat_objeto *mainFunc = nodo_analizar_arbol(vm, tree);
    lat_llamar_funcion(vm, mainFunc);
    lat_apilar(vm, vm->regs[255]);
    if(file != NULL)
    {
      fclose(file);
    }
  }

#ifndef WINDOWS
  else{
  	lat_vm *vm = lat_crear_maquina_virtual();
    latino_repl(vm);
  }
#endif // WINDOWS
  return EXIT_SUCCESS;
}
