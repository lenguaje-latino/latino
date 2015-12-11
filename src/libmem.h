#ifndef _LIBMEM_H_
#define _LIBMEM_H_

#include <stdlib.h>

void* lmalloc(size_t size);
void* lrealloc(void* ptr, size_t size);
void lfree(void* ptr);

#endif /*_LIBMEM_H_*/
