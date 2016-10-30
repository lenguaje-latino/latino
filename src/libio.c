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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "compat.h"
#include "libio.h"
#include "libstring.h"
#include "liblist.h"
#include "vm.h"
#include "latino.h"
#include "libmem.h"

bool __io_es_legible(const char *archivo)
{
    FILE *f = fopen(archivo, "r");
    if(f == NULL)
    {
        return false;
    }
    fclose(f);
    return true;
}

void lat_leer(lat_mv *vm)
{
    char str[MAX_INPUT_SIZE];
    fgets(str, MAX_INPUT_SIZE, stdin);
    int i = strlen(str) - 1;
    if (str[i] == '\n')
        str[i] = '\0';

    //obtiene decimal
    char *ptr;
    double ret;
    ret =strtod(str, &ptr);
    if(strcmp(ptr, "") == 0)
    {
        lat_apilar(vm, lat_numerico_nuevo(vm, ret));
    }
    else
    {
        lat_apilar(vm, lat_cadena_nueva(vm, strdup(str)));
    }
}

void lat_leer_archivo(lat_mv *vm)
{
    lat_objeto* o = lat_desapilar(vm);

    if(o->tipo == T_STR)
    {
        FILE *fp;
        char *buf;
        fp = fopen(__cadena(o), "r");
        if (fp == NULL)
        {
            lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "No se pudo abrir el archivo\n");
        }
        fseek(fp, 0, SEEK_END);
        int fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        //buf = calloc(1, fsize);
        buf = __memoria_asignar(fsize+1);
        size_t newSize = fread(buf, sizeof(char), fsize, fp);
        if (buf == NULL)
        {
            printf("No se pudo asignar %d bytes de memoria\n", fsize);
        }
        buf[newSize - 1] = '\0';
        fclose(fp);
        lat_apilar(vm, lat_cadena_nueva(vm, buf));
    }
    else
    {
        lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "No se pudo abrir el archivo\n");
    }
}

void lat_escribir_archivo(lat_mv *vm)
{
    lat_objeto* s = lat_desapilar(vm);
    lat_objeto* o = lat_desapilar(vm);
    if(o->tipo == T_STR)
    {
        FILE* fp;
        fp = fopen(__cadena(o), "w");
        const char* cad = __cadena(s);
        size_t lon = strlen(cad);
        fwrite(cad, 1 , lon , fp);
        fclose(fp);
    }
    else
    {
        lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "No se pudo escribir en el archivo\n");
    }
}

void lat_sistema(lat_mv *vm)
{
    lat_objeto* cmd = lat_desapilar(vm);
    system(__cadena(cmd));
}

void lat_ejecutar_pipe(lat_mv *vm){
    lat_objeto* cmd = lat_desapilar(vm);
    FILE* fp = __lat_popen(vm, __cadena(cmd), "r");
    size_t rlen = MAX_BUFFERSIZE;
    char *p = __memoria_asignar(rlen);
    fread(p, sizeof(char), rlen, fp);
    rlen = strlen(p);
    p[rlen-1] = '\0';   //elimina el ultimo '\n'
    lat_objeto* res = lat_cadena_nueva(vm, strdup(p));
    lat_apilar(vm, res);
    __lat_pclose(vm, fp);
    __memoria_liberar(p);
}

void lat_limpiar(lat_mv *vm)
{
	system(__lat_clear);
}

void lat_copiar_texto(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    char buffer[MAX_BUFFERSIZE];
    FILE *archivo2 = fopen(__cadena(b), "a");
    fprintf(archivo2, "%s", __cadena(a));
    fclose(archivo2);
}

static size_t __leer_linea(char **lineptr, size_t *n, FILE *stream)
{
    static char line[256];
    char *ptr;
    size_t len;
    if (lineptr == NULL || n == NULL)
    {
       errno = EINVAL;
       return -1;
    }
    if (ferror (stream)){
       return -1;
    }
    if (feof(stream)){
       return -1;
    }
    fgets(line,256,stream);
    ptr = strchr(line,'\n');
    if (ptr){
       *ptr = '\0';
    }else{
        return -1;
    }
    len = strlen(line);
    if ((len+1) < 256)
    {
       ptr = __memoria_reasignar(*lineptr,  256);
       *lineptr = ptr;
       *n = 256;
    }
    strcpy(*lineptr,line);
    return(len);
}

void lat_leer_lineas(lat_mv *vm)
{
    lat_objeto* o = lat_desapilar(vm);
    FILE *fp;
    char *buf = NULL;
    size_t len = 0;
    char *path = __cadena(o);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna,  "No se pudo abrir el archivo\n");
    }
    lat_objeto* lineas = lat_lista_nueva(vm, __lista_crear());
    while((len = __leer_linea(&buf, &len, fp)) != -1){
        __lista_apilar(__lista(lineas), (void*)lat_cadena_nueva(vm, buf));
    }
    fclose(fp);
    lat_apilar(vm, lineas);
}

void lat_dormir(lat_mv *vm)
{
   lat_objeto* mili_segundos = lat_desapilar(vm);
   __lat_sleep(__numerico(mili_segundos));
}

void lat_aleatorio(lat_mv *vm)
{
   lat_objeto* secundario = lat_desapilar(vm);
   lat_objeto* primario = lat_desapilar(vm);
   int resultado, min, max;

   min=__numerico(primario);
   max=__numerico(secundario);

   if (min <= max) {
       max = max+1;
   } else {
       min =__numerico(secundario);
       max =__numerico(primario)+1;
   }

   srand(time(NULL));
   resultado = (rand()%(max-min))+min;
   lat_apilar(vm, lat_numerico_nuevo(vm, resultado));
}

void lat_fecha(lat_mv *vm)
{
    time_t raw, notiempo;
    struct tm * tipo;
    time (&raw);
    /* fix 1: Mostrar hora completa sin argumentos
    fix 2: soporte de la letra ñ al ejecutar comando latino sin argumentos
    notiempo = time(NULL); #fix 1
    char valor2[] = ctime(&notiempo); #fix 1
    */
    tipo = localtime (&raw);

    lat_objeto* tiempo = lat_desapilar(vm);
    int valor;
    char *num = __cadena(tiempo);
    if (!strcmp(num,"seg")) {
        valor = tipo->tm_sec; // segundos
    } else if (!strcmp(num,"min")) {
        valor = tipo->tm_min; // minutos
    } else if (!strcmp(num,"hora")) {
        valor = tipo->tm_hour; // horas
    } else if (!strcmp(num,"d_mes")) {
        valor = tipo->tm_mday; // día del mes
    } else if (!strcmp(num,"mes")) {
        valor = tipo->tm_mon; // mes
    } else if (!strcmp(num,"año")) { //fix 2
        valor = tipo->tm_year+1900; // año
    } else if (!strcmp(num,"d_sem")) {
        valor = tipo->tm_wday; // día de la sem.
    } else if (!strcmp(num,"d_año")) { // fix 2
        valor = tipo->tm_yday; // día del año
    } else if (!strcmp(num,"estacion")) {
        valor = tipo->tm_isdst; // verano/invierno   
    };
    if (valor) { lat_apilar(vm, lat_numerico_nuevo(vm, valor)); };
    //if (!valor) {  lat_apilar(vm, lat_cadena_nueva(vm, valor2)); }; fix 1
}
