#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct lat_object lat_object;

#include "utils.h"
#include "vm.h"

typedef	struct lat_vm lat_vm;
typedef enum lat_type {
	T_NULL, //Throw an error when detected.
	T_INSTANCE,
	T_CHAR,
	T_INT,
	T_DOUBLE,
	T_STR,
	T_BOOL,
	T_LIST,
	T_FUNC,
	T_CFUNC,
	T_STRUCT, //Arbitrary C struct.
} lat_type;

typedef union lat_object_data {
	hash_map *instance;
	char c;
	long i;
	double d;
	char *str;
	bool b;
	list_node *list;
	void *func;
	void(*cfunc)(lat_vm *);
	void *cstruct;
} lat_object_data;

struct lat_object {
	lat_type type;
	char marked;
	size_t data_size;
	lat_object_data data;
};

void lat_set_ctx(lat_object *ns, lat_object *name, lat_object *o);
lat_object *lat_get_ctx(lat_object *ns, lat_object *name);
int lat_ctx_has(lat_object *ns, lat_object *name);
lat_object *lat_make_object(lat_vm *vm);
lat_object *lat_instance(lat_vm *vm);
lat_object *lat_char(lat_vm *vm, char val);
lat_object *lat_int(lat_vm *vm, long val);
lat_object *lat_double(lat_vm *vm, double val);
lat_object *lat_str(lat_vm *vm, char *val);
lat_object *lat_bool(lat_vm *vm, bool val);
lat_object *lat_list(lat_vm *vm, list_node *l);
lat_object *lat_func(lat_vm *vm);
lat_object *lat_cfunc(lat_vm *vm);
lat_object *lat_struct(lat_vm *vm, void *val);

void lat_mark_object(lat_object *o, unsigned char m);
void lat_mark_list(list_node *l, unsigned char m);
void lat_mark_hash(hash_map *l, unsigned char m);

void lat_delete_object(lat_vm *vm, lat_object *o);
void lat_delete_list(lat_vm *vm, list_node *l);
//void lat_delete_hash(lat_vm *vm, hash_map *l);

lat_object *lat_clone_object(lat_vm *vm, lat_object *obj);
list_node *lat_clone_list(lat_vm *vm, list_node *l);
hash_map *lat_clone_hash(lat_vm *vm, hash_map *l);

char lat_get_char_value(lat_object *o);
int lat_get_int_value(lat_object *o);
double lat_get_double_value(lat_object *o);
char *lat_get_str_value(lat_object *o);
bool lat_get_bool_value(lat_object *o);
list_node *lat_get_list_value(lat_object *o);
void *lat_get_struct_value(lat_object *o);

#endif // !_OBJECT_H_
