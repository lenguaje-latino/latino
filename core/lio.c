#include <stdlib.h>
#include "lio.h"
#include "lmem.h"

lstring read_file(lstring path)
{
    FILE *fp = fopen(path, "r");
    lstring source = NULL;
    if (fp != NULL) {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            if (bufsize == -1) {
                /* Error */
                fputs("Error al leer el archivo\n", stderr);
                return source;
            }
            /* Allocate our buffer to that size. */
            source = (lstring) lmalloc(sizeof(char) * (bufsize + 1));
            /* Go back to the start of the file. */
            rewind(fp);
            /* Read the entire file into memory. */
            size_t new_len = fread(source, sizeof(char), bufsize, fp);
            if (new_len == 0) {
                fputs("Archivo vacio\n", stderr);
                return NULL;
            } else {
                source[++new_len] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }
    return source;
}
