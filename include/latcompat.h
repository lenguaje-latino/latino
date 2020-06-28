/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

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

#ifndef _LATINO_COMPAT_H_
#define _LATINO_COMPAT_H_

/** Determina el sistema operativo*/
#if (defined __WIN32__) || (defined _WIN32)
#define SISTEMAOPERATIVO "WIN32"
#define LATINO_BUILD_AS_DLL
#define PATH_SEP "\\"
#define LAT_FUNC extern
#include <limits.h>
#include <windows.h>

#include "regex.h"
#define snprintf(s, l, f, i) _snprintf(s, l, f, i)
#define getcwd(ruta, tam) GetCurrentDirectory(MAX_PATH, ruta);
#define malloc_size(ptr) _msize(ptr)
#define latC_popen(L, c, m) ((void)L, _popen(c, m))
#define latC_pclose(L, file) ((void)L, _pclose(file))
#define strdup _strdup
#define latC_clear "@cls"
#define latC_sleep(mili) Sleep(mili * 1000)
#define latC_leer_linea(x) fgets(x, MAX_INPUT_SIZE, stdin)
#define LAT_ERROR_FMT "%s:%d:%d: %s\n"
/* Visual Leak Detector for Visual C++ */
//#include <vld.h>
#endif /* _WIN32 */

/* __MacOS__ */
#ifdef __APPLE__
//#include "TargetConditionals.h"
//#include <GLUT/glut.h>
//#include <OpenGL/OpenGL.h>
#define SISTEMAOPERATIVO "APPLE"
#include <dlfcn.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#define PATH_SET "~/"
#define LAT_FUNC extern
#define malloc_size(ptr)
#define latC_popen(L, c, m) ((void)L, fflush(NULL), popen(c, m))
#define latC_pclose(L, file) ((void)L, pclose(file))
#define latC_clear "clear"
#define latC_sleep(seg) sleep_ms(seg * 1000)
#define latC_leer_linea(x) readline(NULL)
#define LAT_ERROR_FMT "%s:%d:%d: %s\n"
#endif
/* --EndsMacOS-- */

#ifdef __linux__
#define SISTEMAOPERATIVO "LINUX"
#include <dlfcn.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#define PATH_SEP "/"
#define LAT_FUNC __attribute__((visibility("hidden"))) extern
#define malloc_size(ptr) malloc_usable_size(ptr)
#define latC_popen(L, c, m) ((void)L, fflush(NULL), popen(c, m))
#define latC_pclose(L, file) ((void)L, pclose(file))
#define latC_clear "clear"
#define latC_sleep(seg) sleep_ms(seg * 1000)
#define latC_leer_linea(x) readline(NULL)
#define LAT_ERROR_FMT "\033[1;31m%s:%d:%d:\033[0m %s\n"
#endif /* __linux__ */

#ifdef __CYGWIN__
#include <dlfcn.h>
#include <regex.h>
#include <time.h>
#include <unistd.h>
#define PATH_SEP "/"
#define LAT_FUNC __attribute__((visibility("hidden"))) extern
#define malloc_size(ptr) malloc_usable_size(ptr)
#define latC_popen(L, c, m) ((void)L, fflush(NULL), popen(c, m))
#define latC_pclose(L, file) ((void)L, pclose(file))
#define latC_clear "clear"
#define latC_sleep(seg) sleep_ms(seg * 1000)
#define latC_leer_linea(x) fgets(x, MAX_INPUT_SIZE, stdin)
#define LAT_ERROR_FMT "\033[1;31m%s:%d:%d:\033[0m %s\n"
#endif

/** Determina el compilador*/
#if defined(__GNUC__)
#define latC_noret void __attribute__((noreturn))
#elif defined(_MSC_VER)
#define latC_noret void __declspec(noreturn)
#else
#define latC_noret void
#endif

#include <time.h>
#define TIME_THIS(X)                                                           \
    {                                                                          \
        struct timespec ts1, ts2;                                              \
        clock_gettime(CLOCK_REALTIME, &ts1);                                   \
        X;                                                                     \
        clock_gettime(CLOCK_REALTIME, &ts2);                                   \
        printf(#X " demora: %f\n",                                             \
               (float)(1.0 * (1.0 * ts2.tv_nsec - ts1.tv_nsec * 1.0) * 1e-9 +  \
                       1.0 * ts2.tv_sec - 1.0 * ts1.tv_sec));                  \
    }

#endif /*_LATINO_COMPAT_H_*/
