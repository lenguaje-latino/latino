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
#include "libio.h"
#include "libstring.h"
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

void lat_limpiar()
{
    system("@cls||clear");
}

void lat_reemplazar(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    FILE *__cadena(a);
    FILE *__cadena(b);
    char buffer[256];

    archivo1=fopen(__cadena(a), "r");
    archivo2=fopen(__cadena(b), "a");
    if(__cadena(a)==NULL) {
        perror("Error al ejecutar el archivo.");
        return 0;
        }
    else {
        while(fgets(buffer, sizeof(buffer), __cadena(a))) {
        fprintf(__cadena(b), "%s", buffer);
    }
}
fclose(__cadena(a));
fclose(__cadena(b));
}
