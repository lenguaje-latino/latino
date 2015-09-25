#include <stdio.h>
#include "latino.h"
#include "parse.h"
#include "ast.h"
#include "parse.h"
#include "lex.h"

/* parser debugging */
int yydebug = 0;

int debug = 0;

static FILE *file;
static char *buffer;
static int eof = 0;
static int nRow = 0;
static int nBuffer = 0;
static int lBuffer = 0;
static int nTokenStart = 0;
static int nTokenLength = 0;
static int nTokenNextStart = 0;

int yyparse(ast **expression, yyscan_t scanner);

/*typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
*/

ast *parse_expr(char *expr)
{
	ast *ret = NULL;
	yyscan_t scanner;
	YY_BUFFER_STATE state;

	lex_state scan_state = { .insert = 0 };
	yylex_init_extra(&scan_state, &scanner);
	state = yy_scan_string(expr, scanner);
	yyparse(&ret, scanner);
	yy_delete_buffer(state, scanner);
	yylex_destroy(scanner);

	/*printf("exp:\n%s\n", expr);*/
	return ret;
}

ast *parse_file(char *infile) {
	if (infile == NULL){
		printf("Especifique un archivo\n");
		return NULL;
	}
	file = fopen(infile, "r");
	if (file == NULL) {
		printf("No se pudo abrir el archivo\n");
		return NULL;
	}
	buffer = malloc(BUF_SIZE);
	size_t newSize = fread(buffer, sizeof(char), BUF_SIZE, file);
	if (buffer == NULL) {
		printf("No se pudo asignar %d bytes de memoria\n", BUF_SIZE);
		fclose(file);
		return NULL;
	}
	buffer[newSize] = '\0';
	fclose(file);
	return parse_expr(buffer);
}

int main(int argc, char *argv[])
{
	/*
	Para debuguear en visual studio:
	Menu propiedades del proyecto-> Debugging -> Command Arguments. Agregar $(SolutionDir)..\ejemplos\debug.lat
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
	ast *res = parse_file(infile);
	/*res = parse_expr(buffer);*/
	latValue *val = NULL;
	val = eval(res);
	/*imprimir(val);*/

	/*if (parseCadena){
		yy_delete_buffer(buffer);
	}
	else{
		free(buffer);
		fclose(file);
	}*/
    return EXIT_SUCCESS;
}

extern void printError(char *errorstring, ...)
{
    static char errmsg[1024];
    va_list args;
    va_start(args, errorstring);
    vsprintf(errmsg, errorstring, args);
    va_end(args);
    fprintf(stdout, "Error: %s\n", errmsg);
}
