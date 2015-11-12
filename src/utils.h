#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char * strdup0(const char *s);
char * parse_string(const char *s, size_t n);

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
#define log_err(M, ...) { fprintf(stderr, "Error: " M "\n", ##__VA_ARGS__); exit(1); }
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_mem(A) check((A), "Out of memory.")
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

typedef struct list_node {
	struct list_node *prev;
	struct list_node *next;
	void *data;
} list_node;

list_node *make_list_node(void *d);
list_node *make_list();
int find_list(list_node *l, void *data);
void insert_list(list_node *l, void *data);
void remove_list(list_node *l, void *data);
int length_list(list_node *l);

typedef struct hash_val {
	char key[256];
	void *val;
} hash_val;

typedef struct hash_map {
	list_node *buckets[256];
} hash_map;

hash_map *make_hash_map();
int hash(char *key);
void *get_hash(hash_map *m, char *key);
void set_hash(hash_map *m, char *key, void *val);
hash_map *copy_hash(hash_map *m);

typedef struct hash_set {
	list_node *buckets;
} hash_set;

#endif /*_UTILS_H_*/
