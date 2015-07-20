#include "lmemory.h"

void *lmalloc (size_t size)
{
	return (void *) malloc(size);
}
