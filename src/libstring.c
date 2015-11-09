#include "khash.h"
#include "latino.h"
#include "object.h"

KHASH_MAP_INIT_INT64(env, lat_object);
typedef khash_t(env) lat_env;
lat_env *globals;

struct sym_key {
	const char *ptr;
	size_t len;
};

static khint_t
sym_hash(struct sym_key key)
{
	const char *s = key.ptr;
	khint_t h;
	size_t len = key.len;

	h = *s++;
	while (len--) {
		h = (h << 5) - h + (khint_t)*s++;
	}
	return h;
}

static khint_t
sym_eq(struct sym_key a, struct sym_key b)
{
	if (a.len != b.len) return false;
	if (memcmp(a.ptr, b.ptr, a.len) == 0) return true;
	return false;
}

KHASH_INIT(sym, struct sym_key, lat_object*, 1, sym_hash, sym_eq);
static khash_t(sym) *sym_table;

static lat_object* str_new(const char *p, size_t len){
	lat_object *str =  malloc(sizeof(lat_object));
	str->type = T_STR;
	str->data_size = len;
    str->data.str = p;
	return str;
}

static lat_object* str_intern(const char *p, size_t len){
	khiter_t k;
	struct sym_key key;
	int ret;
	lat_object *str;

	if(!sym_table){
		sym_table = kh_init(sym);
	}
	key.ptr = p;
	key.len = len;
	k = kh_put(sym, sym_table, key, &ret);
	if(ret == 0){
		return kh_value(sym_table, k);
	}
	str = str_new(p, len);
	kh_key(sym_table, k).ptr = str->data.str;
	kh_value(sym_table, k) = str;

	return str;
}

lat_object * lat_str_new(const char* p, size_t len){
	if(p && (len < MAX_STR_INTERN)){
		return str_intern(p, len);
	}
	return str_new(p, len);
}

void lat_concat(lat_vm *vm){

}

void lat_init(lat_vm *vm){
	lat_set_ctx(lat_get_current_ctx(vm), lat_str(vm, "concatenar"), lat_define_c_function(vm, lat_concat));
}
