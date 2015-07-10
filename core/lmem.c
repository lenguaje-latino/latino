#include "lmem.h"
#include <stdio.h>

void *lmalloc(size_t size)
{
    void *value = malloc(size);
    if (value == 0)
        fprintf(stderr, "%s\n", "Memoria virtual agotada");
    return value;
}

void *lrealloc(void *ptr, size_t size)
{
    void *value = realloc(ptr, size);
    if (value == 0)
        fprintf(stderr, "%s\n", "Memoria virtual agotada");
    return value;
}

void lfree(void *ptr)
{
    if (ptr != NULL) {
        free(ptr);
    }
}

