#include <stdlib.h>
#include "lio.h"
#include "mem.h"

lstring read_file(lstring path){
    FILE *fp = fopen(path,"r");
    lstring source = NULL;
    if (fp != NULL) {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            if (bufsize == -1) {
                /* Error */
                fputs("Error al leer el archivo: ", stderr);
            }
            /* Allocate our buffer to that size. */
            source = (lstring) lmalloc(sizeof(lchar) * (bufsize + 1));
            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) != 0) {
                /* Error */
                fputs("Error al leer el archivo: ", stderr);
            }
            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(lchar), bufsize, fp);
            if (newLen == 0) {
                fputs("Error al leer el archivo: ", stderr);
            } else {
                source[++newLen] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }
    return source;
}
