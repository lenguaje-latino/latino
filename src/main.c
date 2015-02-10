#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "lex.yy.c"

yyerror(char *msg)
{
    printf("%s\n", msg);
}
int main(int argc, char* argv[]) {
    FILE* fh = fopen( argv[1], "r" );
    char* nombre_archivo=NULL;
    int p;
//you really should not examine argv[1] if there is no argument...
    if(argc<1) {
        printf("uso: sintaxis <nombre_archivo>\n");
        exit(EXIT_FAILURE);
    }
    nombre_archivo=argv[1];
//check that file opens successfully,
    if(!(fh=fopen(nombre_archivo,"r" ))) {
        printf("error: no se puede abrir el archivo%s\n",nombre_archivo);
        return 0;
    }
    yyin=fopen(nombre_archivo, "rt");
    if(yyin == NULL)
        printf("\nNo se puede leer el archivo");
    else
        p = yyparse();
    fclose(fh);
}

