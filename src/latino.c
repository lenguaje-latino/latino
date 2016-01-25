#include <stdio.h>
#include <string.h>

#ifndef WIN32
#include <dlfcn.h>
#include <unistd.h>
#endif // WIN32

#include "latino.h"
#include "parse.h"
#include "lex.h"
#include "ast.h"

/* 1 para debuguear analizador */
int yydebug = 0;
int debug = 0;

static FILE *file;
static char *buffer;

int yyparse(ast **expression, yyscan_t scanner);

/*
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
*/

ast *lat_parse_expr(char *expr) {
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

ast *lat_parse_file(char *infile) {
  if (infile == NULL) {
    printf("Especifique un archivo\n");
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
    fclose(file);
    return NULL;
  }
  buffer[newSize] = '\0';
  fclose(file);
  return lat_parse_expr(buffer);
}

void lat_compile(lat_vm *vm) {
  vm->regs[255] =
      ast_parse_tree(vm, lat_parse_expr(lat_get_str_value(lat_pop_stack(vm))));
}

void lat_import(lat_vm *vm) {
  char *input = lat_get_str_value(lat_pop_stack(vm));
  char *dot = strrchr(input, '.');
  char *extension;
  if (!dot || dot == input) {
    extension = "";
  }
  extension = dot + 1;
  if (strcmp(extension, "lat") == 0) {
    lat_object *func = ast_parse_tree(vm, lat_parse_file(input));
    lat_call_func(vm, func);
  } else if (strcmp(extension, "so") == 0) {
#ifndef WIN32
    char buffer[256];
    getcwd(buffer, 256);
    strcat(buffer, "/");
    strcat(buffer, input);
    void *handle = dlopen(buffer, RTLD_LAZY);
    void (*init)(lat_vm *);
    if (handle == NULL) {
      log_err("Loading external library %s failed with error %s", input,
              dlerror());
      exit(1);
    }
    dlerror();
    *(void **)(&init) = dlsym(handle, "lat_init");
    init(vm);
    dlclose(handle);
#endif
  }
}

int main(int argc, char *argv[]) {
  /*
  Para debuguear en visual studio:
  Menu propiedades del proyecto-> Debugging -> Command Arguments. Agregar
  $(SolutionDir)..\ejemplos\debug.lat
  */
  /*int parseCadena = 0;*/
  int i;
  char *infile = NULL;
  /*char *cadena = NULL;*/
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      debug = 1;
    } else {
      /*printf(argv[i]);*/
      infile = argv[i];
    }
  }

  /*if (parseCadena){
    YY_BUFFER_STATE buffer = yy_scan_string(cadena);
    }*/

  /*printf("infile: %s\n", infile);*/
  /*error en chkstk.asm*/
  ast *tree = lat_parse_file(infile);
  // tree = lat_parse_expr(buffer);
  // ast_value *val = NULL;
  // val = eval(tree);

  if (!tree) {
    // log_err("Error: en el analizador sintactico");
    return EXIT_FAILURE;
  }

  lat_vm *vm = lat_make_vm();
  lat_set_ctx(lat_get_current_ctx(vm), lat_str(vm, "compile"),
              lat_define_c_function(vm, lat_compile));
  lat_set_ctx(lat_get_current_ctx(vm), lat_str(vm, "import"),
              lat_define_c_function(vm, lat_import));
  lat_object *mainFunc = ast_parse_tree(vm, tree);
  lat_call_func(vm, mainFunc);
  lat_push_stack(vm, vm->regs[255]);
  /*if (parseCadena){
    yy_delete_buffer(buffer);
  }
  else{
    free(buffer);
    fclose(file);
  }*/
  return EXIT_SUCCESS;
}
