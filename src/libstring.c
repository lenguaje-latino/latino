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

#include <string.h>

#include "latino.h"
#include "object.h"
#include "libmem.h"
#include "libstring.h"
#include "liblist.h"
#include "gc.h"

char* __str_duplicar(const char* s)
{
    size_t len = strlen(s);
    char* p;
    p = __memoria_asignar(len + 1);
    if (p)
    {
        strncpy(p, s, len);
    }
    p[len] = '\0';
    return p;
}

char* __str_analizar(const char* s, size_t len)
{
    char* ret = __memoria_asignar(len + 1);
    int i = 0;
    int j = 0;
    int c = '@';
    for (i = 0; i < ((int)len); i++)
    {
        switch (s[i])
        {
        case '\\':
        {
            switch (s[i + 1])
            {
            case 'a':
                c = '\n';
                i++;
                goto save;
            case 'b':
                c = '\n';
                i++;
                goto save;
            case 'f':
                c = '\n';
                i++;
                goto save;
            case 'n':
                c = '\n';
                i++;
                goto save;
            case 'r':
                c = '\n';
                i++;
                goto save;
            case 't':
                c = '\t';
                i++;
                goto save;
            case 'v':
                c = '\n';
                i++;
                goto save;
            default:
                break;
            }
        }
        break;
        default:
            c = s[i];
            break;
        }
save:
        ret[j] = c;
        j++;
    }
    ret[j] = '\0';
    return ret;
}

char* __str_decimal_a_cadena(double d)
{
    char* r = __memoria_asignar(32);
    snprintf(r, 32, "%.14g", d);
    return r;
}

char* __str_logico_a_cadena(int i)
{
    char s[10];
    char* r = __memoria_asignar(11);
    if (i)
    {
        snprintf(s, 10, "%s", "verdadero");
        strcpy(r, s);
    }
    else
    {
        snprintf(s, 10, "%s", "falso");
        strcpy(r, s);
    }
    return r;
}

char* __str_concatenar(char* s1, char* s2)
{
    char* s3 = __memoria_asignar(strlen(s1) + strlen(s2) + 1);
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

void lat_concatenar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    char *tmp1 = NULL;
    char *tmp2 = NULL;
    lat_objeto* r = NULL;
    if(a->tipo == T_STR){
        tmp1 = __str_duplicar(lat_obtener_cadena(a));        
    }else{
        tmp1 = __objeto_a_cadena(a);
    }
    if(b->tipo == T_STR){
        tmp2 = __str_duplicar(lat_obtener_cadena(b));
    }else{
        tmp2 = __objeto_a_cadena(b);
    }    
    r = lat_cadena_nueva(vm, __str_concatenar(tmp1, tmp2));    
    __colector_agregar(vm, r);    
    __memoria_liberar(tmp1);
    __memoria_liberar(tmp2);
    lat_apilar(vm, r);
}