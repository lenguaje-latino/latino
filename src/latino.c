#include "latino.h"
#include "parse.h"

#define true 1
#define false 0

int debug = 0;

static FILE *file;
static char *buffer;
static int eof             = 0;
static int nRow            = 0;
static int nBuffer         = 0;
static int lBuffer         = 0;
static int lMaxBuffer      = 1024*1024;
static int nTokenStart     = 0;
static int nTokenLength    = 0;
static int nTokenNextStart = 0;

int yyparse();

extern
int main(int argc, char *argv[])
{
    int i;
    char *infile = NULL;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            debug = 1;
        } else {
            infile = argv[i];
        }
    }
    if (infile == NULL)
        printf("Especifique un archivo\n");
    file = fopen(infile, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return EXIT_FAILURE;
    }
    buffer = malloc(lMaxBuffer);
    if (buffer == NULL) {
        printf("No se pudo asignar %d bytes de memoria\n", lMaxBuffer);
        fclose(file);
        return EXIT_FAILURE;
    }
    yyparse();
    free(buffer);
    fclose(file);
    return EXIT_SUCCESS;
}

extern
void print_error(char *errorstring, ...)
{
    static char errmsg[1024];
    va_list args;
    va_start(args, errorstring);
    vsprintf(errmsg, errorstring, args);
    va_end(args);
    fprintf(stdout, "Error: %s\n", errmsg);
}

extern
void dump_row(void)
{
    if (nRow == 0) {
        int i;
        fprintf(stdout, "       |");
        for (i = 1; i < 71; i++)
            if (i % 10 == 0)
                fprintf(stdout, ":");
            else if (i % 5 == 0)
                fprintf(stdout, "+");
            else
                fprintf(stdout, ".");
        fprintf(stdout, "\n");
    } else {
        fprintf(stdout, "%6d |%.*s", nRow, lBuffer, buffer);
    }
}

static
int get_next_line(void)
{
    char *p;
    nBuffer = 0;
    nTokenStart = -1;
    nTokenNextStart = 1;
    eof = false;
    p = fgets(buffer, lMaxBuffer, file);
    if (p == NULL) {
        if (ferror(file))
            return -1;
        eof = true;
        return 1;
    }
    nRow += 1;
    lBuffer = strlen(buffer);
    if(debug){
        dump_row();
    }
    return 0;
}

static
char dump_char(char c)
{
    if (isprint(c))
        return c;
    return '@';
}

extern
int get_next_char(char *b, int maxBuffer)
{
    int frc;
    if (eof)
        return 0;
    while (nBuffer >= lBuffer) {
        frc = get_next_line();
        if (frc != 0)
            return 0;
    }
    b[0] = buffer[nBuffer];
    nBuffer += 1;
    return b[0] == 0 ? 0 : 1;
}
