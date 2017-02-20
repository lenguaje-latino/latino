#include <stdio.h>

#include "latino.h"

#define LIB_LAT_NAME "lat"

char *__tipo(int tipo);

void lat_lat_mostrar(lat_mv * mv) {
	lat_objeto *o = lat_desapilar(mv);
	printf("Tipo : %s\n", __tipo(o->tipo));
	printf("Num. Referencias : %i\n", o->num_ref);
	printf("Tamanio : %zu\n", o->tamanio);
	printf("Direccion : %p\n", o);
	printf("------------------------------------\n");
}

static const lat_CReg liblat[] = {
	{"mostrar", lat_lat_mostrar, 1},
	{NULL, NULL}
};

void lat_importar_lib_lat(lat_mv * mv) {
	lat_importar_lib(mv, LIB_LAT_NAME, liblat);
}
