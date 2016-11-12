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

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latast.h"
#include "latgc.h"
#include "latino.h"
#include "latlex.h"
#include "latmem.h"
#include "latmv.h"
#include "latobj.h"
#include "latparse.h"
#include "linenoise/linenoise.h"

/*
Para depurar en visual studio:
Menu propiedades del proyecto-> Debugging -> Command Arguments. Agregar
$(SolutionDir)..\ejemplos\debug.lat
----------------------------------
Para depurar en Netbeans ir a propiedades del proyecto -> Run command y Agregar
"${OUTPUT_PATH}" ejemplos/debug.lat
*/

int yydebug = 0; /* 1 para debuguear analizador lexico/sintactico */
int parse_silent;
char *filename = NULL;
int yyparse(ast **root, yyscan_t scanner);

bool __str_inicia_con(const char *base, const char *str);
char *__str_reemplazar(char *str, const char *orig, const char *rep);

ast *lat_analizar_expresion(char *expr, int *status) {
  ast *ret = NULL;
  yyscan_t scanner;
  YY_BUFFER_STATE state;
  lex_state scan_state = {.insert = 0};
  yylex_init_extra(&scan_state, &scanner);
  state = yy_scan_string(expr, scanner);
  *status = yyparse(&ret, scanner);
  yy_delete_buffer(state, scanner);
  yylex_destroy(scanner);
  if (parse_silent == 0) {
    __memoria_liberar(NULL, expr);
  }
  return ret;
}

ast *lat_analizar_archivo(char *infile, int *status) {
  if (infile == NULL) {
    printf("Especifique un archivo\n");
    return NULL;
  }
  char *dot = strrchr(infile, '.');
  char *extension;
  if (!dot || dot == infile) {
    extension = "";
  } else {
    extension = dot + 1;
    if (strcmp(extension, "lat") != 0) {
      printf("El archivo '%s' no contiene la extension .lat\n", infile);
      return NULL;
    }
  }
  FILE *file = fopen(infile, "r");
  if (file == NULL) {
    printf("No se pudo abrir el archivo: %s\n", infile);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  int fsize = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buffer = __memoria_asignar(NULL, fsize + 1);
  size_t newSize = fread(buffer, sizeof(char), fsize, file);
  if (buffer == NULL) {
    printf("No se pudo asignar %d bytes de memoria\n", fsize);
    return NULL;
  }
  if (file != NULL) {
    fclose(file);
  }
  buffer[newSize] = '\0';
  filename = infile;
  return lat_analizar_expresion(buffer, status);
}

/**
 * Muestra la version de latino en la consola
 */
void lat_version() { printf("%s\n", LAT_DERECHOS); }

/**
 * Para crear el logo en ascii
 */
void lat_logo() { printf("%s\n", LAT_LOGO); }

/**
 * Muestra la ayuda en la consola
 */
void lat_ayuda() {
  lat_logo();
  lat_version();
  printf("%s\n", "Uso de latino: latino [opcion] [archivo]");
  printf("\n");
  printf("%s\n", "Opciones:");
  printf("%s\n", "-a           : Muestra la ayuda de Latino");
  printf("%s\n", "-e           : Ejecuta una cadena de codigo");
  printf("%s\n", "-v           : Muestra la version de Latino");
  printf("%s\n", "archivo      : Nombre del archivo con extension .lat");
  printf("%s\n", "Ctrl-C       : Para cerrar");
  printf("\n");
  printf("%s\n", "Variables de entorno:");
  printf("%s\n", "_____________________");
  printf("%s%s\n", "LATINO_PATH  : ", getenv("LATINO_PATH"));
  printf("%s%s\n", "LATINO_LIB   : ", getenv("LATINO_LIB"));
  printf("%s%s\n", "HOME         : ", getenv("HOME"));
}

static void completion(const char *buf, linenoiseCompletions *lc) {
  if (__str_inicia_con(buf, "esc")) {
    linenoiseAddCompletion(lc, "escribir");
  }
  if (__str_inicia_con(buf, "imp")) {
    linenoiseAddCompletion(lc, "imprimir");
  }
  if (__str_inicia_con(buf, "eje")) {
    linenoiseAddCompletion(lc, "ejecutar");
  }
  if (__str_inicia_con(buf, "fun")) {
    linenoiseAddCompletion(lc, "funcion");
  }
  if (__str_inicia_con(buf, "com")) {
    linenoiseAddCompletion(lc, "comparar");
  }
  if (__str_inicia_con(buf, "con")) {
    linenoiseAddCompletion(lc, "concatenar");
  }
  if (__str_inicia_con(buf, "cont")) {
    linenoiseAddCompletion(lc, "contiene");
  }
  if (__str_inicia_con(buf, "cop")) {
    linenoiseAddCompletion(lc, "copiar");
  }
  if (__str_inicia_con(buf, "ter")) {
    linenoiseAddCompletion(lc, "termina_con");
  }
  if (__str_inicia_con(buf, "es_")) {
    linenoiseAddCompletion(lc, "es_igual");
  }
  if (__str_inicia_con(buf, "ind")) {
    linenoiseAddCompletion(lc, "indice");
  }
  if (__str_inicia_con(buf, "ins")) {
    linenoiseAddCompletion(lc, "insertar");
  }
  if (__str_inicia_con(buf, "ult")) {
    linenoiseAddCompletion(lc, "ultimo_indice");
  }
  if (__str_inicia_con(buf, "reli")) {
    linenoiseAddCompletion(lc, "rellenar_izquierda");
  }
  if (__str_inicia_con(buf, "reld")) {
    linenoiseAddCompletion(lc, "rellenar_derecha");
  }
  if (__str_inicia_con(buf, "eli")) {
    linenoiseAddCompletion(lc, "eliminar");
  }
  if (__str_inicia_con(buf, "est")) {
    linenoiseAddCompletion(lc, "esta_vacia");
  }
  if (__str_inicia_con(buf, "lon")) {
    linenoiseAddCompletion(lc, "longitud");
  }
  if (__str_inicia_con(buf, "ree")) {
    linenoiseAddCompletion(lc, "reemplazar");
  }
  if (__str_inicia_con(buf, "emp")) {
    linenoiseAddCompletion(lc, "inicia_con");
  }
  if (__str_inicia_con(buf, "sub")) {
    linenoiseAddCompletion(lc, "subcadena");
  }
  if (__str_inicia_con(buf, "min")) {
    linenoiseAddCompletion(lc, "minusculas");
  }
  if (__str_inicia_con(buf, "may")) {
    linenoiseAddCompletion(lc, "mayusculas");
  }
  if (__str_inicia_con(buf, "qui")) {
    linenoiseAddCompletion(lc, "quitar_espacios");
  }
  if (__str_inicia_con(buf, "lee")) {
    linenoiseAddCompletion(lc, "leer");
  }
  if (__str_inicia_con(buf, "tip")) {
    linenoiseAddCompletion(lc, "tipo");
  }
  if (__str_inicia_con(buf, "log")) {
    linenoiseAddCompletion(lc, "logico");
  }
  if (__str_inicia_con(buf, "num")) {
    linenoiseAddCompletion(lc, "numerico");
  }
  if (__str_inicia_con(buf, "cad")) {
    linenoiseAddCompletion(lc, "cadena");
  }
  if (__str_inicia_con(buf, "sal")) {
    linenoiseAddCompletion(lc, "salir");
  }
}

static int leer_linea(char *buffer) {
  char *prompt = "latino> ";
  parse_silent = 1;
  char *input;
  // char *tmp = "";
  char *tmp = __memoria_asignar(NULL, MAX_STR_LENGTH);
REP:
  input = linenoise(prompt);
  if (input == NULL) {
    return -1;
  }
  for (;;) {
    // tmp = __str_concatenar(tmp, "\n");
    // tmp = __str_concatenar(tmp, input);
    tmp = strcat(tmp, "\n");
    tmp = strcat(tmp, input);
    int estatus;
    lat_analizar_expresion(tmp, &estatus);
    if (estatus == 1) {
      prompt = "    >>> ";
      goto REP;
    } else {
      prompt = "latino> ";
      strcpy(buffer, tmp);
      __memoria_liberar(NULL, tmp);
      return 0;
    }
  }
}

static void lat_repl(lat_mv *mv) {
  char *buf = __memoria_asignar(mv, MAX_STR_LENGTH);
  ast *tmp = NULL;
  int status;
  mv->REPL = true;
  linenoiseHistoryLoad(".history");
  linenoiseSetCompletionCallback(completion);
  while (leer_linea(buf) != -1) {
    tmp = lat_analizar_expresion(buf, &status);
    if (tmp != NULL) {
      lat_objeto *curexpr = ast_analizar_arbol(mv, tmp);
      lat_llamar_funcion(mv, curexpr);
      lat_objeto *o = lat_desapilar(mv);
      if (o != NULL && (strstr(buf, "escribir") == NULL &&
                        strstr(buf, "imprimir") == NULL)) {
        lat_apilar(mv, o);
        lat_apilar(mv, mv->objeto_nulo);
        lat_imprimir(mv);
      }
    }
    // se guarda el comando al historial aunque haya error
    linenoiseHistoryAdd(__str_reemplazar(buf, "\n", ""));
    linenoiseHistorySave(".history");
  }
  __memoria_liberar(mv, buf);
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  setlocale(LC_CTYPE, "");
  /*para numeros decimales*/
  setlocale(LC_NUMERIC, "es_MX");
  setlocale(LC_MONETARY, "es_MX");
  int i;
  char *infile = NULL;
  int pe = false;
  int pf = false;
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0) {
      lat_version();
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--help") == 0) {
      lat_ayuda();
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-e") == 0) {
      pe = true;
    } else {
      pf = true;
    }
  }
  lat_mv *mv = lat_mv_crear();
  if (pe) {
    if (argc != 3) {
      printf("Error: Se requiere una cadena para ejecución.\n");
      return EXIT_FAILURE;
    }
    mv->nombre_archivo = NULL;
    mv->REPL = false;
    int status;
    char *cmd = __memoria_asignar(NULL, MAX_STR_LENGTH);
    strcpy(cmd, argv[2]);
    ast *nodo = lat_analizar_expresion(cmd, &status);
    if (status == 0 && nodo != NULL) {
      lat_objeto *mainFunc = ast_analizar_arbol(mv, nodo);
      lat_llamar_funcion(mv, mainFunc);
    }
    ast_liberar(nodo);
  } else if (argc > 1 && pf) {
    infile = argv[1]; // nombre del archivo
    mv->nombre_archivo = infile;
    mv->REPL = false;
    mv->argc = argc - 2;
    int i;
    for (i = 2; i < argc; i++) {
      __lista_agregar(__lista(mv->argv),
                      lat_cadena_nueva(mv, strdup(argv[i])));
    }
    int status;
    ast *nodo = lat_analizar_archivo(infile, &status);
    if (status == 0 && nodo != NULL) {
      lat_objeto *mainFunc = ast_analizar_arbol(mv, nodo);
      if (mv->menu) {
        // agrego instrucciones para llamar a menu
        lat_function *fval = (lat_function *)mainFunc->datos.fun_usuario;
        lat_bytecode *bcode = (lat_bytecode *)fval->bcode;
        int num_inst = mainFunc->num_inst;
        lat_bytecode *new_bcode =
            __memoria_asignar(NULL, sizeof(lat_bytecode) * (num_inst + 2));
        memcpy(new_bcode, bcode, __memoria_tamanio(new_bcode));
        new_bcode[num_inst - 1] =
            lat_bc(LOAD_NAME, 0, 0, lat_cadena_nueva(mv, strdup("menu")));
        new_bcode[num_inst] = lat_bc(CALL_FUNCTION, 2, 0, NULL);
        new_bcode[num_inst + 1] = lat_bc(HALT, 0, 0, NULL);
        lat_objeto *num = lat_numerico_nuevo(mv, mv->argc);
        lat_apilar(mv, num);
        lat_apilar(mv, mv->argv);
        lat_gc_agregar(mv, num);
        lat_objeto *newMain = lat_definir_funcion(mv, new_bcode, num_inst + 2);
        lat_llamar_funcion(mv, newMain);
        __obj_eliminar(mv, newMain);
      } else {
        lat_llamar_funcion(mv, mainFunc);
        __obj_eliminar(mv, mainFunc);
      }
    }
    ast_liberar(nodo);
  } else {
    lat_version();
    lat_repl(mv);
  }
  lat_destruir_mv(mv);
  return EXIT_SUCCESS;
}
