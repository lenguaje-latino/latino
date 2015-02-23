#include "latino.h"

#define true 1
#define false 0

int debug=0;

static FILE *file;
static int eof             = 0;
static int nRow            = 0;
static int nBuffer         = 0;
static int lBuffer         = 0;
static int nTokenStart     = 0;
static int nTokenLength    = 0;
static int nTokenNextStart = 0;
static int lMaxBuffer      = 1000;
static char *buffer;

/*--------------------------------------------------------------------
 * dump_char
 *
 * printable version of a char
 *------------------------------------------------------------------*/
static
char dump_char(char c) {
    if (  isprint(c)  )
        return c;
    return '@';
}
/*--------------------------------------------------------------------
 * dump_string
 *
 * printable version of a string upto 100 character
 *------------------------------------------------------------------*/
static
char *dump_string(char *s) {
    static char buf[101];
    int i;
    int n = strlen(s);

    if (  n > 100  )
        n = 100;

    for (i=0; i<n; i++)
        buf[i] = dump_char(s[i]);
    buf[i] = 0;
    return buf;
}
/*--------------------------------------------------------------------
 * dump_row
 *
 * dumps the contents of the current row
 *------------------------------------------------------------------*/
extern
void dump_row(void) {
    if (  nRow == 0  ) {
        int i;
        fprintf(stdout, "       |");
        for (i=1; i<71; i++)
            if (  i % 10 == 0  )
                fprintf(stdout, ":");
            else if (  i % 5 == 0  )
                fprintf(stdout, "+");
            else
                fprintf(stdout, ".");
        fprintf(stdout, "\n");
    }
    else
        fprintf(stdout, "%6d |%.*s", nRow, lBuffer, buffer);
}
/*--------------------------------------------------------------------
 * MarkToken
 *
 * marks the current read token
 *------------------------------------------------------------------*/
extern
void print_error(char *errorstring, ...) {
    static char errmsg[10000];
    va_list args;

    int start=nTokenStart;
    int end=start + nTokenLength - 1;
    int i;

    /*================================================================*/
    /* print it using variable arguments -----------------------------*/
    va_start(args, errorstring);
    vsprintf(errmsg, errorstring, args);
    va_end(args);

    fprintf(stdout, "Error: %s\n", errmsg);
}
/*--------------------------------------------------------------------
 * get_next_line
 *
 * reads a line into the buffer
 *------------------------------------------------------------------*/
static
int get_next_line(void) {
    int i;
    char *p;

    /*================================================================*/
    /*----------------------------------------------------------------*/
    nBuffer = 0;
    nTokenStart = -1;
    nTokenNextStart = 1;
    eof = false;

    /*================================================================*/
    /* read a line ---------------------------------------------------*/
    p = fgets(buffer, lMaxBuffer, file);
    if (  p == NULL  ) {
        if (  ferror(file)  )
            return -1;
        eof = true;
        return 1;
    }

    nRow += 1;
    lBuffer = strlen(buffer);
    dump_row();

    /*================================================================*/
    /* that's it -----------------------------------------------------*/
    return 0;
}
/*--------------------------------------------------------------------
 * get_next_char
 *
 * reads a character from input for flex
 *------------------------------------------------------------------*/
extern
int get_next_char(char *b, int maxBuffer) {
    int frc;

    /*================================================================*/
    /*----------------------------------------------------------------*/
    if (  eof  )
        return 0;

    /*================================================================*/
    /* read next line if at the end of the current -------------------*/
    while (  nBuffer >= lBuffer  ) {
        frc = get_next_line();
        if (  frc != 0  )
            return 0;
    }

    /*================================================================*/
    /* ok, return character ------------------------------------------*/
    b[0] = buffer[nBuffer];
    nBuffer += 1;

    if (  debug  )
        printf("get_next_char() => '%c'0x%02x at %d\n",
               dump_char(b[0]), b[0], nBuffer);
    return b[0]==0?0:1;
}
/*--------------------------------------------------------------------
 * begin_token
 *
 * marks the beginning of a new token
 *------------------------------------------------------------------*/
extern
void begin_token(char *t) {
    /*================================================================*/
    /* remember last read token --------------------------------------*/
    nTokenStart = nTokenNextStart;
    nTokenLength = strlen(t);
    nTokenNextStart = nBuffer; // + 1;

    /*================================================================*/
    /* location for bison --------------------------------------------*/
    yylloc.first_line = nRow;
    yylloc.first_column = nTokenStart;
    yylloc.last_line = nRow;
    yylloc.last_column = nTokenStart + nTokenLength - 1;

    if (  debug  ) {
        printf("Token '%s' a %d:%d siguiente a %d\n", dump_string(t),
               yylloc.first_column,
               yylloc.last_column, nTokenNextStart);
    }
}
/*--------------------------------------------------------------------
 * main
 *
 * the master
 *------------------------------------------------------------------*/
extern
int main(int argc, char *argv[]) {
    int i;
    char *infile=NULL;

    /*================================================================*/
    /*----------------------------------------------------------------*/
    debug = 0;
    /*printf("  ===  latino: Nuevo lenguaje de programacion     ===  \n");*/
    /*printf("  ***  author: primitivo.roman.montero@gmail.com  *** \n");*/
    /*printf("  \n");*/

    for (i=1; i<argc; i++) {
        if (  strcmp(argv[i], "-debug") == 0  ) {
            printf("Debugging activado\n");
            debug = 1;
        }
        else {
            infile = argv[i];
        }
    }

    if (  infile == NULL  )
        printf("Especifique un archivo\n");

    /*================================================================*/
    /* opening input -------------------------------------------------*/
    /*printf("reading file '%s'\n", infile);*/
    file = fopen(infile, "r");
    if (  file == NULL  ) {
        printf("No se pudo abrir el archivo\n");
        return 12;
    }

    /*================================================================*/
    /*----------------------------------------------------------------*/
    buffer = malloc(lMaxBuffer);
    if (  buffer == NULL  ) {
        printf("No se pudo asignar %d bytes de memoria\n", lMaxBuffer);
        fclose(file);
        return 12;
    }

    /*================================================================*/
    /* parse it ------------------------------------------------------*/
    dump_row();
    if (  get_next_line() == 0  )
        yyparse();

    /*================================================================*/
    /* ending... -----------------------------------------------------*/
    free(buffer);
    fclose(file);
    printf("Contenido final de las variables:\n");
    dump_variables("  ");
    return 0;
}
