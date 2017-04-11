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

#define BUF_SIZE 1024
#define LIB_SISTEMA_NAME "sis"
volatile sig_atomic_t senial;

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

void lat_sis_ejecutar(lat_mv * mv) {
	lat_objeto *cmd = lat_desapilar(mv);
	system(__cadena(cmd));
}

void lat_sis_dormir(lat_mv * mv) {
	lat_objeto *mili_segundos = lat_desapilar(mv);
	__lat_sleep(__numerico(mili_segundos));
}

void lat_sis_pipe(lat_mv * mv) {
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

char *__analizar_formato_fecha(char *str) {
	if (!str) {
		return NULL;
	};
	time_t raw;
	struct tm *tiempo;
	time(&raw);
	tiempo = localtime(&raw);
	long int buf_str = strlen(str)+1;
	char *fmt = malloc(buf_str);
	sprintf(fmt, "%c", 0);
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '%' && str[i - 1] != '\\') {
			switch (str[i + 1]) {
			case 'a':
				buf_str = buf_str+4;
				fmt = realloc(fmt, buf_str);
				sprintf(fmt, "%s%i", fmt, (tiempo->tm_year + 1900));
				i++;
				break;
			case 'm':
				if (str[i + 2] == 'm') {
					buf_str = buf_str+2;
					fmt = realloc(fmt, buf_str);
					sprintf(fmt, "%s%i", fmt, (tiempo->tm_mon + 1));
					i = i + 2;
					break;
				} else if (str[i + 2] == 'n') {
					buf_str = buf_str+2;
					fmt = realloc(fmt, buf_str);
					sprintf(fmt, "%s%i", fmt, tiempo->tm_min);
					i = i + 2;
					break;
				} else {
					sprintf(fmt, "%s%c", fmt, str[i]);
					break;
				}
			case 'h':
				buf_str = buf_str+2;
				fmt = realloc(fmt, buf_str);
				sprintf(fmt, "%s%i", fmt, tiempo->tm_hour);
				i++;
				break;
			case 's':
				buf_str = buf_str+2;
				fmt = realloc(fmt, buf_str);
				sprintf(fmt, "%s%i", fmt, tiempo->tm_sec);
				i++;
				break;
			case 'd':
				if (str[i + 2] == 'm') {
					buf_str = buf_str+2;
					fmt = realloc(fmt, buf_str);
					sprintf(fmt, "%s%i", fmt, tiempo->tm_mday);
					i = i + 2;
					break;
				} else if (str[i + 2] == 's') {
					buf_str = buf_str+1;
					fmt = realloc(fmt, buf_str);
					sprintf(fmt, "%s%i", fmt, (tiempo->tm_wday));
					i = i + 2;
					break;
				} else if (str[i + 2] == 'a') {
					buf_str = buf_str+3;
					fmt = realloc(fmt, buf_str);
					sprintf(fmt, "%s%i", fmt, tiempo->tm_yday);
					i = i + 2;
					break;
				} else {
					sprintf(fmt, "%s%c", fmt, str[i]);
					break;
				}
			case 'e':
				sprintf(fmt, "%s%i", fmt, tiempo->tm_isdst);
				i++;
				break;
			default:
				sprintf(fmt, "%s%c", fmt, str[i]);
				break;
			}
		} else {
			if (str[i] == '\\') {
				sprintf(fmt, "%s%c", fmt, str[i + 1]);
				i++;
			} else {
				sprintf(fmt, "%s%c", fmt, str[i]);
			}
		}
	}
	return fmt;
}

void lat_sis_fecha(lat_mv * mv) {
	lat_objeto *_formato_str = lat_desapilar(mv);
	lat_objeto *tmp;
	char *formato = "%dm/%mm/%a";
	if (_formato_str->tipo != T_NULL) {
		formato = __cadena(_formato_str);
	}
	char *fecha = __analizar_formato_fecha(formato);
	if (!fecha) {
		tmp = mv->objeto_nulo;
	} else {
		tmp = lat_cadena_nueva(mv, strdup(fecha));
	}
	lat_apilar(mv, tmp);
	free(fecha);
}

void proceso_al_activarse(int sig) {
	senial = sig;
}

void lat_sis_sig(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	signal(__numerico(a), proceso_al_activarse);
	if (!senial) {
		lat_apilar(mv, mv->objeto_falso);
	} else {
		lat_apilar(mv, lat_numerico_nuevo(mv, senial));
	};
}

void lat_sis_cwd(lat_mv * mv) {
	char dir[BUF_SIZE];
	getcwd(dir, sizeof(dir));
	if (dir != NULL) {
		lat_apilar(mv, lat_cadena_nueva(mv, strdup(dir)));
	} else {
		lat_apilar(mv, mv->objeto_nulo);
	};
}

void lat_sis_iraxy(lat_mv * mv) {
	lat_objeto *x = lat_desapilar(mv);
	lat_objeto *y = lat_desapilar(mv);
	int yx = __numerico(y), xx = __numerico(x);
	printf("%c[%d;%df", 0x1B, yx, xx);
	fflush(stdout);
}

void lat_sis_usuario(lat_mv * mv) {
	char *user = getenv("USER");
	lat_objeto *tmp;
	if (user != NULL || user) {
		tmp = lat_cadena_nueva(mv, user);
	} else {
		tmp = mv->objeto_nulo;
	}
	lat_apilar(mv, tmp);
}

void lat_sis_obtent(lat_mv * mv) {
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

void lat_sis_nvent(lat_mv * mv) {
	lat_objeto *c = lat_desapilar(mv);
	lat_objeto *b = lat_desapilar(mv);
	lat_objeto *a = lat_desapilar(mv);
	bool nvenv = setenv(__cadena(a), __cadena(b), lat_obj2bool(c));
	lat_objeto *tmp;
	if (nvenv == false) {
		tmp = mv->objeto_verdadero;
	} else {
		tmp = mv->objeto_falso;
	}
	lat_apilar(mv, tmp);
}

void lat_sis_rement(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	bool elmenv = unsetenv(__cadena(a));
	lat_objeto *tmp;
	if (elmenv == 0) {
		tmp = mv->objeto_verdadero;
	} else {
		tmp = mv->objeto_falso;
	}
	lat_apilar(mv, tmp);
}

void lat_sis_ponent(lat_mv * mv) {
	lat_objeto *a = lat_desapilar(mv);
	bool ponent = putenv(__cadena(a));
	lat_objeto *tmp;
	if (ponent == 0) {
		tmp = mv->objeto_verdadero;
	} else {
		tmp = mv->objeto_falso;
	}
	lat_apilar(mv, tmp);
}

void lat_sis_stdin(lat_mv * mv) {
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	if (!select(1, &readfds, NULL, NULL, &timeout)) {
		lat_apilar(mv, mv->objeto_nulo);
		return;
	}
	lat_objeto *var = NULL;
	char buffer[BUF_SIZE];
	size_t contenidoTamanio = 1;
	char *contenido = malloc(sizeof(char) * BUF_SIZE);
	if (contenido == NULL) {
		lat_error("Linea %d, %d: %s", var->num_linea, var->num_columna,
				  "error al asignar memoria.");
	}
	contenido[0] = '\0';

	if (fgets(buffer, BUF_SIZE, stdin)) {
		contenidoTamanio += strlen(buffer);
		contenido = realloc(contenido, contenidoTamanio);
		if (contenido == NULL) {
			free(contenido);
			lat_error("Linea %d, %d: %s", var->num_linea, var->num_columna,
					  "error al reasignar memoria.");
		}
		strcat(contenido, buffer);
	}

	if (ferror(stdin)) {
		free(contenido);
		lat_error("Linea %d, %d: %s", var->num_linea, var->num_columna,
				  "error al leer stdin.");
	}
	var = lat_cadena_nueva(mv, strdup(contenido));
	lat_apilar(mv, var);
	free(contenido);
}

void lat_sis_fork(lat_mv *mv) {
	lat_objeto *error = NULL;
	bool pid_ok = false;
	pid_t pid = fork();
    if (pid == 0) {
        pid_ok = true;
	} else if (pid > 0) {
		pid_ok = true;
	}
	if (!pid_ok) {
		lat_error("Linea %d, %d: %s", error->num_linea, error->num_columna,
				  "error en fork.");
	} else {
		lat_objeto *datos = lat_lista_nueva(mv, __lista_crear());
		__lista_agregar(__lista(datos), lat_numerico_nuevo(mv, pid));
		__lista_agregar(__lista(datos), lat_numerico_nuevo(mv, getpid()));
		lat_apilar(mv, datos);
	}
}

void lat_sis_tiempo(lat_mv *mv) {
	lat_objeto *unixt = lat_desapilar(mv);
	lat_objeto *_formato_str = lat_desapilar(mv);
	time_t unix_time = time(NULL);
	if (_formato_str->tipo == T_NULL) {
		lat_apilar(mv, lat_numerico_nuevo(mv, unix_time));
	} else {
		const char *ftmstr = __cadena(_formato_str);
		if (unixt->tipo != T_NULL) {
			unix_time = __numerico(unixt);
		};
		struct tm estructura;
		long unsigned int buf = strlen(ftmstr)*15;
		char res[buf];
		localtime_r(&unix_time, &estructura);
		if (!strftime(res, sizeof(res), ftmstr, &estructura)) {
			lat_apilar(mv, mv->objeto_nulo);
		} else {
			lat_apilar(mv, lat_cadena_nueva(mv, strdup(res)));
		}
	}
}

static const lat_CReg libsistema[] = {
	{"dormir", lat_sis_dormir, 1},
	{"ejecutar", lat_sis_ejecutar, 1},
	{"pipe", lat_sis_pipe, 1},
    {"tiempo", lat_sis_tiempo, 2},
	{"fecha", lat_sis_fecha, 1},
	{"sig", lat_sis_sig, 1},
	{"cwd", lat_sis_cwd, 0},
	{"ruta", lat_sis_cwd, 0},
	{"iraxy", lat_sis_iraxy, 2},
	{"usuario", lat_sis_usuario, 0},
	{"obtent", lat_sis_obtent, 1},
	{"nvent", lat_sis_nvent, 3},
	{"rement", lat_sis_rement, 1},
	{"ponent", lat_sis_ponent, 1},
	{"stdin", lat_sis_stdin, 0},
	{"fork", lat_sis_fork, 0},
	{NULL, NULL}
};

void lat_importar_lib_sistema(lat_mv * mv) {
	lat_importar_lib(mv, LIB_SISTEMA_NAME, libsistema);
}
