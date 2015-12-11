#include <stdio.h>

#include "libmem.h"
#include "utils.h"

void* lmalloc(size_t size)
{
  void* value = malloc(size);
  if (value == 0)
    log_err("Memoria virtual agotada\n");
  return value;
}

void* lrealloc(void* ptr, size_t size)
{
  void* value = realloc(ptr, size);
  if (value == 0)
    log_err("Memoria virtual agotada\n");
  return value;
}

void lfree(void* ptr)
{
  if (ptr != NULL) {
    free(ptr);
  }
}
