/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
void lat_remove(lat_vm* vm);
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
