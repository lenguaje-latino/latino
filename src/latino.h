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

#ifndef _LATINO_H_
#define _LATINO_H_

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>

#include "ast.h"
#include "vm.h"

#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 302) && \
defined(__ELF__)
#define LAT_FUNC __attribute__((visibility("hidden"))) extern
#define lnsprintf(s, l, f, i) snprintf(s, l, f, i)
#include <dlfcn.h>
#include <unistd.h>
#else
/* Visual Leak Detector for Visual C++ */
//#include <vld.h>
#define LAT_FUNC extern
#define lnsprintf(s, l, f, i) _snprintf(s, l, f, i)
#endif

#define lassert(cond) ((void)(false && (cond)))

extern int debug;
#define MAX_ERROR_LENGTH 1024
#define MAX_BYTECODE_FUNCTION (1024 * 10)
#define MAX_VIRTUAL_MEMORY (1024 * 10)
#define MAX_STR_INTERN 64
#define MAX_STACK_SIZE 255

/* interface con flex */
typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;

#define YYLTYPE_IS_DECLARED 1

#define YY_NO_UNISTD_H 1

ast* lat_parse_expr(char* expr);
ast* lat_parse_file(char* path);

#endif /* _LATINO_H_ */
