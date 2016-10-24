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

char* __str_analizar_fmt(const char* s, size_t len)
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
            case '/':
                c = '/';
                i++;
                goto save;
            case '"':
                c = '\"';
                i++;
                goto save;            
            case 'a':
                c = '\a';
                i++;
                goto save;
            case 'b':
                c = '\b';
                i++;
                goto save;
            case 'f':
                c = '\f';
                i++;
                goto save;
            case 'n':
                c = '\n';
                i++;
                goto save;
            case 'r':
                c = '\r';
                i++;
                goto save;
            case 't':
                c = '\t';
                i++;
                goto save;            
            case '\\':
                c = '\\';
                i++;
                goto save;            
            case 'u':
                c = s[i];
                ret[j] = c;
                j++;  
                i++;
                int k;
                for(k = 0; k <= 4; k++) {
                    c = s[i];
                    ret[j] = c;
                    j++;
                    i++;
                }                    
            default:                
                c = s[i];                
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
            /*case '/':
                c = '/';
                i++;
                goto save;*/            
            case '\\':
                c = '\\';
                i++;
                ret[j] = c;
                j++;
                c = '\\';
                i++;
                ret[j] = c;
                j++;
            case 'u':
                c = s[i];
                ret[j] = c;
                j++;  
                i++;
                int k;
                for(k = 0; k <= 4; k++) {
                    c = s[i];
                    ret[j] = c;
                    j++;
                    i++;
                }                    
            default:                
                c = s[i];                
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

bool __str_empieza_con(const char* base, const char* str)
{
    return (strstr(base, str) - base) == 0;
}

bool __str_termina_con(char* base, char* str)
{
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

int __str_intercambiar_posicion(char* base, char* str, int startIndex)
{
    int result;
    int baselen = strlen(base);
    if ((int)strlen(str) > baselen || startIndex > baselen)
    {
        result = -1;
    }
    else
    {
        if (startIndex < 0)
        {
            startIndex = 0;
        }
        char* pos = strstr(base + startIndex, str);
        if (pos == NULL)
        {
            result = -1;
        }
        else
        {
            result = pos - base;
        }
    }
    return result;
}

int __str_posicion(char* base, char* str)
{
    return __str_intercambiar_posicion(base, str, 0);
}

int __str_ultima_posicion(char* base, char* str)
{
    int result;
    if (strlen(str) > strlen(base))
    {
        result = -1;
    }
    else
    {
        int start = 0;
        int endinit = strlen(base) - strlen(str);
        int end = endinit;
        int endtmp = endinit;
        while (start != end)
        {
            start = __str_intercambiar_posicion(base, str, start);
            end = __str_intercambiar_posicion(base, str, end);
            if (start == -1)
            {
                end = -1;
            }
            else if (end == -1)
            {
                if (endtmp == (start + 1))
                {
                    end = start;
                }
                else
                {
                    end = endtmp - (endtmp - start) / 2;
                    if (end <= start)
                    {
                        end = start + 1;
                    }
                    endtmp = end;
                }
            }
            else
            {
                start = end;
                end = endinit;
            }
        }
        result = start;
    }
    return result;
}

char* __str_insertar(char *dest, char* src, int pos)
{
    int srclen = strlen(src);
    int dstlen = strlen(dest);
    if (pos < 0)
    {
        pos = dstlen + pos;
    }
    if (pos > dstlen)
    {
        pos = dstlen;
    }
    char *m = __memoria_asignar(srclen + dstlen + 1);
    memcpy(m, dest, pos);
    memcpy(m + pos, src, srclen);
    memcpy(m + pos + srclen, dest + pos, dstlen - pos + 1);
    return m;
}

char* __str_rellenar_izquierda(char* base, int n, char* c)
{
    int len = (int)strlen(base);
    char *ret = NULL;
    if (n <= len)
    {
        ret = __memoria_asignar(len + 1);
        strcpy(ret, base);
        return ret;
    }
    ret = __memoria_asignar(n + 1);
    ret = "";
    int i = 0;
    for (i = 0; i < (n - len); i++)
    {
        ret = __str_concatenar(ret, c);
    }
    ret = __str_concatenar(ret, base);
    return ret;
}

char* __str_rellenar_derecha(char *base, int n, char* c)
{
    int len = (int)strlen(base);
    char *ret = NULL;
    if (len >= n)
    {
        ret = __memoria_asignar(len + 1);
        strcpy(ret, base);
        return ret;
    }
    ret = __memoria_asignar(n + 1);
    ret = base;
    int i;
    for (i = 0; i < (n - len); i++)
    {
        ret = __str_concatenar(ret, c);
    }
    return ret;
}

char* __str_reemplazar(char *str, char *orig, char *rep)
{
    char *buffer = __memoria_asignar(MAX_STR_LENGTH);
    char *p;
    if (!(p = strstr(str, orig)))
    {
        return str;
    }
    strncpy(buffer, str, p - str);
    buffer[p - str] = '\0';
    sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
    //reemplazar todas las ocurrencias
    if (strstr(buffer, orig) != NULL)
    {
        strcpy(buffer, __str_reemplazar(buffer, orig, rep));
    }
    __memoria_reasignar(buffer, strlen(buffer)+1);
    return buffer;
}

char* __str_subcadena(const char* str, int beg, int n)
{
    char *ret = __memoria_asignar(n + 1);
    strncpy(ret, (str + beg), n);
    *(ret + n) = 0;
    return ret;
}

char* __str_minusculas(const char* str)
{
    int i = 0;
    int len = strlen(str);
    char *ret = (char*) __memoria_asignar(len + 1);
    for (i = 0; i < len; i++)
    {
        ret[i] = tolower(str[i]);
    }
    ret[len] = 0;
    return ret;
}

char* __str_mayusculas(const char* str)
{
    int i = 0;
    int len = strlen(str);
    char *ret = __memoria_asignar(len + 1);
    for (i = 0; i < len; i++)
    {
        ret[i] = toupper(str[i]);
    }
    ret[len] = 0;
    return ret;
}

char* __str_quitar_espacios(const char *str)
{
    char *start;
    char *end;
    for (start = (char*) str; *start; start++)
    {
        if (!isspace((unsigned char)start[0]))
            break;
    }
    for (end = start + strlen(start); end > start + 1; end--)
    {
        if (!isspace((unsigned char)end[-1]))
            break;
    }
    char *ret = __memoria_asignar((end - start) + 1);
    *end = 0;
    if (start > str)
    {
        memcpy(ret, start, (end - start) + 1);
    }
    else
    {
        memcpy(ret, str, strlen(str));
    }
    return ret;
}

void lat_concatenar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    //Lat_DECREF(b);
    //Lat_DECREF(a);
    char *tmp1 = NULL;
    char *tmp2 = NULL;
    lat_objeto* r = NULL;
    if(a->tipo == T_STR){
        tmp1 = strdup(__cadena(a));        
    }else{
        tmp1 = __objeto_a_cadena(a);
    }
    if(b->tipo == T_STR){
        tmp2 = strdup(__cadena(b));
    }else{
        tmp2 = __objeto_a_cadena(b);
    }    
    r = lat_cadena_nueva(vm, __str_concatenar(tmp1, tmp2));
    __memoria_liberar(tmp1);
    __memoria_liberar(tmp2);
    lat_apilar(vm, r);
    __colector_agregar(vm, r);
}

void lat_comparar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(a->tipo == T_STR && b->tipo == T_STR)
        lat_apilar(vm, lat_numerico_nuevo(vm, strcmp(__cadena(a), __cadena(b))));
    if(a->tipo == T_LIST && b->tipo == T_LIST){
        lat_apilar(vm, lat_numerico_nuevo(vm, __lista_comparar(__lista(a), __lista(b))));
    }
}

void lat_contiene(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    char *result = strstr(__cadena(a), __cadena(b));
    if (result != NULL)
    {
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

void lat_termina_con(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (__str_termina_con(__cadena(a), __cadena(b)))
    {
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

void lat_es_igual(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (strcmp(__cadena(a), __cadena(b)) == 0)
    {
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

/*
void lat_format(lat_mv* vm){
}
*/

void lat_indice(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);  
    if(a->tipo == T_STR && b->tipo == T_STR){
        lat_apilar(vm, lat_numerico_nuevo(vm, __str_posicion(__cadena(a), __cadena(b))));
        return;
    }
    if(a->tipo == T_LIST){
        lat_apilar(vm, lat_numerico_nuevo(vm, __lista_obtener_indice(__lista(a), (void*) b)));
        return;
    }
}

void lat_insertar(lat_mv* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(a->tipo == T_STR && b->tipo == T_STR){
        lat_apilar(vm, lat_cadena_nueva(vm, __str_insertar(__cadena(a), __cadena(b), __numerico(c))));
    }
    if(a->tipo == T_LIST){
        __lista_insertar_elemento(__lista(a), (void*)b, __numerico(c));
        return;
    }
}

void lat_ultimo_indice(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_numerico_nuevo(vm, __str_ultima_posicion(__cadena(a), __cadena(b))));
}

void lat_rellenar_izquierda(lat_mv* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_cadena_nueva(vm, __str_rellenar_izquierda(__cadena(a), __numerico(b), __cadena(c))));
}

void lat_rellenar_derecha(lat_mv* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_cadena_nueva(vm, __str_rellenar_derecha(__cadena(a), __numerico(b), __cadena(c))));
}

void lat_eliminar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(a->tipo == T_STR)
    {
        lat_apilar(vm, lat_cadena_nueva(vm, __str_reemplazar(__cadena(a), __cadena(b), "")));
    }
    if(a->tipo == T_LIST)
    {
        lista* lst = __lista(a);
        int i = __lista_obtener_indice(lst, (void*)b);
        if(i >= 0){
            lista_nodo *nt = __lista_obtener_nodo(lst, i);
            __lista_eliminar_elemento(lst, nt);
        }
    }
}

void lat_esta_vacia(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (strcmp(__cadena(a), "") == 0)
    {
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

void lat_longitud(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (a->tipo == T_STR)
    {
        lat_apilar(vm, lat_numerico_nuevo(vm, strlen(__cadena(a))));
    }
    if (a->tipo == T_LIST)
    {
        lat_apilar(vm, lat_numerico_nuevo(vm, __lista_longitud(__lista(a))));        
    }
    if (a->tipo == T_DICT)
    {
        lat_apilar(vm, lat_numerico_nuevo(vm, __dic_longitud(__dic(a))));
    }
    if (a->tipo == T_NUMERIC)
    {
        lat_apilar(vm, lat_numerico_nuevo(vm, strlen(__objeto_a_cadena(a))));
    }
}

void lat_reemplazar(lat_mv* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);  
    char *bf = __str_analizar_fmt(__cadena(b), strlen(__cadena(b)));
    char *cf = __str_analizar_fmt(__cadena(c), strlen(__cadena(c)));
    lat_apilar(vm, lat_cadena_nueva(vm, __str_reemplazar(__cadena(a), bf, cf)));
    __memoria_liberar(bf);
    __memoria_liberar(cf);
}

void lat_empieza_con(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (__str_empieza_con(__cadena(a), __cadena(b)))
    {
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

void lat_subcadena(lat_mv* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_cadena_nueva(vm, __str_subcadena(__cadena(a), __numerico(b), __numerico(c))));
}

void lat_minusculas(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_cadena_nueva(vm, __str_minusculas(__cadena(a))));
}

void lat_mayusculas(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_cadena_nueva(vm, __str_mayusculas(__cadena(a))));
}

void lat_quitar_espacios(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    lat_apilar(vm, lat_cadena_nueva(vm, __str_quitar_espacios(__cadena(a))));
}

void lat_es_numerico(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if(a->tipo == T_NUMERIC)
    {
        lat_apilar(vm, vm->objeto_verdadero);
        return;
    }    
    char *ptr;
    strtod(__cadena(a), &ptr);
    if (strcmp(ptr, "") == 0){
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

void lat_es_alfanumerico(lat_mv* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (a->tipo != T_STR)
    {
        lat_apilar(vm, vm->objeto_falso);
        return;
    }
    char* cad = __cadena(a);
    bool res = true;
    for (int i = 0; i < strlen(cad); i++)
    {
        if (!isalnum(cad[i]))
        {
            res = false;
            break;
        }
    }
    if (res)
    {
        lat_apilar(vm, vm->objeto_verdadero);
    }
    else
    {
        lat_apilar(vm, vm->objeto_falso);
    }
}

void lat_separar(lat_mv* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    char *sep = " ";    //separador default
    if (b->tipo != T_NULL){
        sep = __cadena(b);
        if(strlen(sep) == 0){
            sep = " ";
        }
    }
    char *str = strdup(__cadena(a));
    lista* lst = __lista_crear();    
    char *tok = strtok(str, sep);
    if(tok){
        __lista_apilar(lst, lat_cadena_nueva(vm, strdup(tok)));
    }
    while (tok != NULL){
        tok = strtok(NULL, sep);
        if(tok){
            __lista_apilar(lst, lat_cadena_nueva(vm, strdup(tok)));
        }
    }
    lat_apilar(vm, lat_lista_nueva(vm, lst));
}

void lat_invertir_cadena(lat_mv *vm)
{
    lat_objeto* a = lat_desapilar(vm);
    //parseamos la cadena por si tiene caracteres de escape(\n, \t, etc...)
    char* slst = __str_analizar(__cadena(a), strlen(__cadena(a)));
    int i=0;
    int p = 0;
    char *cad;
    lista *cads = __lista_crear();
    //separamos en una lista de caracteres
    char ch[8];
    for(p; p < strlen(slst); p++){
        i=0;
        if(slst[p] < 0){            
            while(slst[p] < 0){
                ch[i] = slst[p];
                p++;
                i++;                
            }
            p--;
        }else{
            i=0;
            ch[i] = slst[p];
            i++;
        }
        ch[i] = '\0';        
        cad = lat_cadena_nueva(vm, ch);
        __lista_apilar(cads, cad);
    }
    //unimos los caracteres
    char* res = __memoria_asignar(__cadena(a));
    for(i=__lista_longitud(cads)-1;i>=0; i--){
        char *elem = __cadena(__lista_obtener_elemento(cads, i));        
        res = strcat(res, elem);
    }
    int len = strlen(res);
    res[len+1] = '\0';  
    lat_objeto* obj = lat_cadena_nueva(vm, res);
    lat_apilar(vm, obj);    
    //liberamos los objetos temporales
    __lista_destruir(cads);
    __memoria_liberar(res);
    __memoria_liberar(slst);
}