#ifndef _LIBSTRING_H_
#define _LIBSTRING_H_

#include "latino.h"

void lat_concat(lat_vm *vm);
lat_object * lat_str_new(const char* p, size_t len);

#endif // !_LIBSTRING_H_
