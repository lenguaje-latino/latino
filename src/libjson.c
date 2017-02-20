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

#include <jansson.h>

#include "latgc.h"
#include "latino.h"
#include "latmv.h"

#define LIB_JSON_NAME "json"

static json_t *__json_cargar(const char *text) {
	json_t *root;
	json_error_t error;
	root = json_loads(text, 0, &error);
	if (root) {
		return root;
	} else {
		lat_error("Linea %d: %s", error.line, error.text);
		return (json_t *) 0;
	}
}

static lat_objeto *__json_a_latino(lat_mv * mv, json_t * element) {
	size_t i;
	size_t size;
	json_t *value = NULL;
	const char *key;
	switch (json_typeof(element)) {
	case JSON_OBJECT:{
			size = json_object_size(element);
			lat_objeto *dic = lat_dic_nuevo(mv, __dic_crear());
			json_object_foreach(element, key, value) {
				// printf("key: %s\n", key);
				__dic_asignar(__dic(dic), key, __json_a_latino(mv, value));
			}
			return dic;
		}
		break;
	case JSON_ARRAY:{
			size = json_array_size(element);
			lat_objeto *lst = lat_lista_nueva(mv, __lista_crear());
			for (i = 0; i < size; i++) {
				value = json_array_get(element, i);
				__lista_agregar(__lista(lst),
								(void *)__json_a_latino(mv, value));
			}
			return lst;
		}
		break;
	case JSON_STRING:{
			lat_objeto *str = lat_cadena_nueva(mv,
											   strdup(json_string_value
													  (element)));
			return str;
		}
		break;
	case JSON_INTEGER:{
			lat_objeto *dec = lat_numerico_nuevo(mv,
												 (double)
												 json_integer_value(element));
			return dec;
		}
		break;
	case JSON_REAL:{
			lat_objeto *dec = lat_numerico_nuevo(mv,
												 (double)
												 json_real_value(element));
			return dec;
		}
		break;
	case JSON_TRUE:
		return mv->objeto_verdadero;
		break;
	case JSON_FALSE:
		return mv->objeto_falso;
		break;
	case JSON_NULL:
		return mv->objeto_nulo;
		break;
	default:
		fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
	}
	return NULL;
}

static json_t *__latino_a_json(lat_mv * mv, lat_objeto * element) {
	json_t *value = NULL;
	switch (element->tipo) {
	case T_DICT:{
			value = json_object();
			int i;
			for (i = 0; i < 256; i++) {
				lista *list = __dic(element)->buckets[i];
				if (list != NULL) {
					LIST_FOREACH(list, primero, siguiente, cur) {
						if (cur->valor != NULL) {
							json_object_set(value,
											((hash_val *) cur->valor)->llave,
											__latino_a_json(mv,
															(lat_objeto
															 *) ((hash_val *)
																 cur->
																 valor)->valor));
						}
					}
				}
			}
			return value;
		}
		break;
	case T_LIST:{
			value = json_array();
			lista *list = __lista(element);
			LIST_FOREACH(list, primero, siguiente, cur) {
				if (cur->valor != NULL) {
					json_array_append_new(value,
										  __latino_a_json(mv, (lat_objeto *)
														  cur->valor));
				}
			}
			return value;
		}
		break;
	case T_STR:{
			value = json_string(strdup(__cadena(element)));
			return value;
		}
		break;
	case T_NUMERIC:{
			double d = __numerico(element);
			if (fmod(d, 1) == 0) {
				value = json_integer((int)__numerico(element));
			} else {
				value = json_real(__numerico(element));
			}
			return value;
		}
		break;
	case T_BOOL:{
			if (__logico(element)) {
				value = json_true();
			} else {
				value = json_false();
			}
			return value;
		}
		break;
	case T_NULL:{
			value = json_null();
			return value;
		}
		break;
	default:{
			value = json_null();
			return value;
		}
	}
}

void lat_json_decodificar(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	char *str = __cadena(a);
	json_t *root = __json_cargar(str);
	lat_objeto *tmp = mv->objeto_nulo;
	if (root) {
		tmp = __json_a_latino(mv, root);
		json_decref(root);
	}
	lat_apilar(mv, tmp);
	lat_gc_agregar(mv, tmp);
}

void lat_json_codificar(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	lat_objeto *tmp = mv->objeto_nulo;
	json_t *j = __latino_a_json(mv, a);
	char *s = json_dumps(j, JSON_ALLOW_NUL);
	tmp = lat_cadena_nueva(mv, strdup(s));
	lat_apilar(mv, tmp);
	lat_gc_agregar(mv, tmp);
}

void lat_json_formato(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	int spaces = 4;
	char *str = NULL;
	json_t *root = NULL;
	if (a->tipo != T_STR) {
		root = __latino_a_json(mv, a);
	} else {
		str = strdup(__cadena(a));
		root = __json_cargar(str);
	}
	lat_objeto *tmp = mv->objeto_nulo;
	if (root) {
		int flags = JSON_INDENT(spaces);
		char *buf = json_dumps(root, flags);
		tmp = lat_cadena_nueva(mv, buf);
		json_decref(root);
	}
	lat_apilar(mv, tmp);
	lat_gc_agregar(mv, tmp);
}

static const lat_CReg lib_json[] = {
	{"decodificar", lat_json_decodificar, 1},
	{"codificar", lat_json_codificar, 1},
	{"formato", lat_json_formato, 1},
	{NULL, NULL}
};

void lat_importar_lib_json(lat_mv * mv) {
	lat_importar_lib(mv, LIB_JSON_NAME, lib_json);
}
