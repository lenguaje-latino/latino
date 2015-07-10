#ifndef _LMEM_H_
#define _LMEM_H_

#include <stdlib.h>

void *lmalloc(size_t size);
void *lrealloc(void *ptr, size_t size);
void lfree(void *ptr);

#endif /*_LMEM_H_*/
