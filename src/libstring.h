#ifndef _LIBSTRING_H_
#define _LIBSTRING_H_

#include "latino.h"

lat_object* lat_str_new(const char* p, size_t len);

/*libreria cadena*/
void lat_compare(lat_vm* vm);
void lat_concat(lat_vm* vm);
void lat_contains(lat_vm* vm);
void lat_copy(lat_vm* vm);
void lat_endsWith(lat_vm* vm);
void lat_equals(lat_vm* vm);
//void lat_format(lat_vm* vm);
void lat_indexOf(lat_vm* vm);
void lat_insert(lat_vm* vm);
void lat_lastIndexOf(lat_vm* vm);
void lat_padLeft(lat_vm* vm);
void lat_padRight(lat_vm* vm);
//void lat_remove(lat_vm* vm);
void lat_isEmpty(lat_vm* vm);
void lat_length(lat_vm* vm);
void lat_replace(lat_vm* vm);
//void lat_split(lat_vm* vm);
void lat_startsWith(lat_vm* vm);
void lat_substring(lat_vm* vm);
void lat_toLower(lat_vm* vm);
void lat_toUpper(lat_vm* vm);
void lat_trim(lat_vm* vm);
//void lat_valueOf(lat_vm* vm);

#endif // !_LIBSTRING_H_
