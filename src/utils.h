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
#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char* strdup0(const char* s);
char* parse_string(const char* s, size_t n);

#ifdef NDEBUG

#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stdout, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#ifndef REGISTER_DEBUG
#define regdebug(M, ...)
#else
#define regdebug(M, ...) fprintf(stdout, "REGDEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define lat_registrar_error(M, ...)                               \
  {                                                   \
    fprintf(stderr, "Error: " M "\n", ##__VA_ARGS__); \
    exit(1);                                          \
  }
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define check(A, M, ...)       \
  if (!(A)) {                  \
    lat_registrar_error(M, ##__VA_ARGS__); \
    errno = 0;                 \
    goto error;                \
  }
#define sentinel(M, ...)       \
  {                            \
    lat_registrar_error(M, ##__VA_ARGS__); \
    errno = 0;                 \
    goto error;                \
  }
#define check_mem(A) check((A), "Out of memory.")
#define check_debug(A, M, ...) \
  if (!(A)) {                  \
    debug(M, ##__VA_ARGS__);   \
    errno = 0;                 \
    goto error;                \
  }

typedef struct list_node {
  struct list_node* prev;
  struct list_node* next;
  void* data;
} list_node;

list_node* lat_crear_lista_node(void* d);
list_node* lat_crear_lista();
int find_list(list_node* l, void* data);
void insert_list(list_node* l, void* data);
void remove_list(list_node* l, void* data);
int length_list(list_node* l);

typedef struct hash_val {
  char key[256];
  void* val;
} hash_val;

typedef struct hash_map {
  list_node* buckets[256];
} hash_map;

hash_map* make_hash_map();
int hash(char* key);
void* get_hash(hash_map* m, char* key);
void set_hash(hash_map* m, char* key, void* val);
hash_map* copy_hash(hash_map* m);

typedef struct hash_set {
  list_node* buckets;
} hash_set;

/*funciones auxiliares para manejo de cadenas*/
char* concat(char* s1, char* s2);
char* int2str(long i);
char* double2str(double d);
char* char2str(char c);
char* bool2str(int i);
bool startsWith(char* base, char* str);
bool endsWith(char* base, char* str);
int indexOf(char* base, char* str);
int indexOf_shift(char* base, char* str, int startIndex);
int lastIndexOf(char* base, char* str);
char* insert(char *dest, char* src, int pos);
char* padLeft(char* base, int n, char* c);
char* padRight(char *base, int n, char* c);
char *replace(char *str, char *orig, char *rep);
char *substring(const char* str, int beg, int n);
char *toLower(const char* str);
char *toUpper(const char* str);
char *trim(const char* str);
#endif /*_UTILS_H_*/
