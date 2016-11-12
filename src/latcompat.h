/*
The MIT License (MIT)

Copyright (c) 2015 - 2016. Latino

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

#ifndef _COMPAT_H_
#define _COMPAT_H_

/** Determina el sistema operativo*/
#ifdef _WIN32
#define PATH_SEP "\\"
/* Visual Leak Detector for Visual C++ */
//#include <vld.h>
#define LAT_FUNC extern
#include <limits.h>
#include <windows.h>
#define snprintf(s, l, f, i) _snprintf(s, l, f, i)
#define getcwd(ruta, tamanio) GetCurrentDirectory(MAX_PATH, ruta);
#include "stdbool.h"
#define malloc_size(ptr) _msize(ptr)
#define __lat_popen(L, c, m) ((void)L, _popen(c, m))
#define __lat_pclose(L, file) ((void)L, _pclose(file))
#define strdup _strdup
#define __lat_clear "@cls"
#define __lat_sleep(mili) Sleep(mili * 1000)
#endif
#ifdef __linux__
#include <dlfcn.h>
#include <stdbool.h>
#include <unistd.h>
#define PATH_SEP "/"
#define LAT_FUNC __attribute__((visibility("hidden"))) extern
#define malloc_size(ptr) malloc_usable_size(ptr)
#define __lat_popen(L, c, m) ((void)L, fflush(NULL), popen(c, m))
#define __lat_pclose(L, file) ((void)L, pclose(file))
#define __lat_clear "clear"
#define __lat_sleep(seg) sleep(seg)
#endif

/** Determina el compilador*/
#if defined(__GNUC__)
#define __lat_noret void __attribute__((noreturn))
#elif defined(_MSC_VER)
#define __lat_noret void __declspec(noreturn)
#else
#define __lat_noret void
#endif

#endif /*_COMPAT_H_*/
