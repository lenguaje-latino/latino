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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
//#include <pthread.h> // en prueba

#include "latcompat.h"
#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"

#define LIB_SISTEMA_NAME "sis"
volatile sig_atomic_t proceso_detenido;

void sleep_ms(int milliseconds)	// cross-platform sleep function
{
#ifdef WIN32
	Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
#else
	usleep(milliseconds * 1000);
#endif
}

void lat_sistema_ejecutar(lat_mv * mv) {
	lat_objeto *cmd = lat_desapilar(mv);
	system(__cadena(cmd));
}

void lat_sistema_dormir(lat_mv * mv) {
	lat_objeto *mili_segundos = lat_desapilar(mv);
	__lat_sleep(__numerico(mili_segundos));
}

void lat_sistema_pipe(lat_mv * mv) {
	lat_objeto *cmd = lat_desapilar(mv);
	FILE *fp = __lat_popen(mv, __cadena(cmd), "r");
	size_t rlen = MAX_BUFFERSIZE;
	char *p = __memoria_asignar(NULL, rlen);
	fread(p, sizeof(char), rlen, fp);
	rlen = strlen(p);
	p[rlen - 1] = '\0';			// elimina el ultimo '\n'
	lat_objeto *tmp = lat_cadena_nueva(mv, strdup(p));
	lat_apilar(mv, tmp);
	__lat_pclose(mv, fp);
	__memoria_liberar(mv, p);
	lat_gc_agregar(mv, tmp);
}

char *__analizar_formato_fecha(char *str, char *mem) {
    time_t raw;
    struct tm *tiempo;
    time(&raw);
    tiempo = localtime(&raw);
    char *fmt = mem;
    for (int i=0; i<strlen(str); i++) {
        if (str[i] == '%' && str[i-1] != '\\') {
            switch(str[i+1]) {
                case 'a':
                    sprintf(fmt, "%s%i", fmt, (tiempo->tm_year+1900));
                    i++;
                    break;
                case 'm':
                    if (str[i+2] == 'm') {
                        sprintf(fmt, "%s%i", fmt, (tiempo->tm_mon+1));
                        i=i+2;
                        break;
                    } else if (str[i+2] == 'n') {
                        sprintf(fmt, "%s%i", fmt, tiempo->tm_min);
                        i=i+2;
                        break;
                    } else {
                        sprintf(fmt, "%s%c", fmt, str[i]);
                    }
                case 'h':
                    sprintf(fmt, "%s%i", fmt, tiempo->tm_hour);
                    i++;
                    break;
                case 's':
                    sprintf(fmt, "%s%i", fmt, tiempo->tm_sec);
                    i++;
                    break;
                case 'd':
                    if (str[i+2] == 'm') {
                        sprintf(fmt, "%s%i", fmt, tiempo->tm_mday);
                        i=i+2;
                        break;
                    } else if (str[i+2] == 's') {
                        sprintf(fmt, "%s%i", fmt, (tiempo->tm_wday+1));
                        i=i+2;
                        break;
                    } else if (str[i+2] == 'a') {
                        sprintf(fmt, "%s%i", fmt, tiempo->tm_yday);
                        i=i+2;
                        break;
                    } else {
                        sprintf(fmt, "%s%c", fmt, str[i]);
                    }
                case 'e':
                    sprintf(fmt, "%s%i", fmt, tiempo->tm_isdst);
                    i++;
                    break;
                default:
                    sprintf(fmt, "%s%c", fmt, str[i]);
                }
            } else {
                if (str[i] == '\\') {
                    sprintf(fmt, "%s%c", fmt, str[i+1]);
                    i++;
                } else {
                    sprintf(fmt, "%s%c", fmt, str[i]);
                }
            }
    }
    return fmt;
}

void lat_sistema_fecha(lat_mv * mv) {
	lat_objeto *tiempo = lat_desapilar(mv);
    char *mem = malloc(strlen(__cadena(tiempo) + 1));
    char *fecha = __analizar_formato_fecha(__cadena(tiempo), mem);
	lat_apilar(mv, lat_cadena_nueva(mv, fecha));
	free(mem);
}

void proceso_al_activarse(int sig) {
	proceso_detenido = 1;
}

void lat_sistema_avisar(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	signal(__numerico(a), proceso_al_activarse);
	if (!proceso_detenido) {
		lat_apilar(mv, mv->objeto_falso);
		return;
	} else {
		lat_apilar(mv, mv->objeto_verdadero);
	};
}

void lat_sistema_cwd(lat_mv * mv) {
	char dir[1024];
	getcwd(dir, sizeof(dir));
	if (dir != NULL) {
		lat_apilar(mv, lat_cadena_nueva(mv, strdup(dir)));
	} else {
		lat_apilar(mv, mv->objeto_nulo);
	};
}

void lat_sistema_iraxy(lat_mv * mv) {
	lat_objeto *x = lat_desapilar(mv);
	lat_objeto *y = lat_desapilar(mv);
	int yx = __numerico(y), xx = __numerico(x);
	printf("%c[%d;%df", 0x1B, yx, xx);
	fflush(stdout);
}

void lat_sistema_usuario(lat_mv * mv) {
	char *user = getenv("USER");
	lat_objeto *tmp;
	if (user != NULL || user) {
		tmp = lat_cadena_nueva(mv, user);
	} else {
		tmp = mv->objeto_nulo;
	}
	lat_apilar(mv, tmp);
}

void lat_sistema_entorno(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	char *env = getenv(__cadena(a));
	lat_objeto *tmp;
	if (env) {
		tmp = lat_cadena_nueva(mv, env);
	} else {
		tmp = mv->objeto_nulo;
	}
	lat_apilar(mv, tmp);
}

/* en prueba
void *tarea1() {
        int i;
        scanf("%i", &i);
	printf("\nTAREA 1: Escribiste el número %i\n", i);
	return NULL;
}

void lat_sistema_tarea_nueva(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        pthread_t proceso = __numerico(a);
        pthread_create(&proceso, NULL, tarea1, NULL);
        lat_objeto *cref = lat_numerico_nuevo(mv, proceso);
        lat_apilar(mv, cref);
}

void lat_sistema_tarea_iniciar(lat_mv *mv) {
        lat_objeto *a = lat_desapilar(mv);
        pthread_t proceso = __numerico(a);
        pthread_join(proceso, NULL);
}
*/

static const lat_CReg libsistema[] = {
	{"dormir", lat_sistema_dormir, 1},
	{"ejecutar", lat_sistema_ejecutar, 1},
	{"pipe", lat_sistema_pipe, 1},
	{"fecha", lat_sistema_fecha, 1},
	{"avisar", lat_sistema_avisar, 1},
	{"cwd", lat_sistema_cwd, 0},
	{"iraxy", lat_sistema_iraxy, 2},
	{"usuario", lat_sistema_usuario, 0},
	{"entorno", lat_sistema_entorno, 1},
	/*{"tarea_nueva", lat_sistema_tarea_nueva, 1},
	   {"tarea_iniciar", lat_sistema_tarea_iniciar, 1}, */
	{NULL, NULL}
};

void lat_importar_lib_sistema(lat_mv * mv) {
	lat_importar_lib(mv, LIB_SISTEMA_NAME, libsistema);
}
