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

#include "khash.h"
#include "latino.h"
#include "object.h"
#include "libmem.h"
#include "libstring.h"
#include "liblist.h"

KHASH_MAP_INIT_INT64(env, lat_objeto);
typedef khash_t(env) lat_env;
lat_env* globals;

struct sym_key
{
    const char* ptr;
    size_t len;
};

static khint_t
sym_hash(struct sym_key key)
{
    const char* s = key.ptr;
    khint_t h;
    size_t len = key.len;
    h = *s++;
    while (len--)
    {
        h = (h << 5) - h + (khint_t)*s++;
    }
    return h;
}

static khint_t
sym_eq(struct sym_key a, struct sym_key b)
{
    if (a.len != b.len)
        return false;
    if (memcmp(a.ptr, b.ptr, a.len) == 0)
        return true;
    return false;
}

KHASH_INIT(sym, struct sym_key, lat_objeto*, 1, sym_hash, sym_eq);
static khash_t(sym) * sym_table;

static lat_objeto* str_new(const char* p, size_t len)
{
    lat_objeto* str = (lat_objeto*)__memoria_asignar(sizeof(lat_objeto));
    str->type = T_STR;
    str->data_size = len;
    str->data.str = (char *)p;
    return str;
}

static lat_objeto* str_intern(const char* p, size_t len)
{
    khiter_t k;
    struct sym_key key;
    int ret;
    lat_objeto* str;
    if (!sym_table)
    {
        sym_table = kh_init(sym);
    }
    key.ptr = p;
    key.len = len;
    k = kh_put(sym, sym_table, key, &ret);
    if (ret == 0)
    {
        return kh_value(sym_table, k);
    }
    str = str_new(p, len);
    kh_key(sym_table, k).ptr = str->data.str;
    kh_value(sym_table, k) = str;
    return str;
}

lat_objeto* __str_cadena_hash(const char* p, size_t len)
{
    if (p && (len < MAX_STR_INTERN))
    {
        return str_intern(p, len);
    }
    return str_new(p, len);
}

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

char* __str_concatenar(char* s1, char* s2)
{
    char* s3 = __memoria_asignar(strlen(s1) + strlen(s2) + 1);
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

char* __str_entero_a_cadena(long i)
{
    char s[255];
    char* r = __memoria_asignar(strlen(s) + 1);
    snprintf(s, 255, "%ld", i);
    strcpy(r, s);
    return r;
}

char* __str_numerico_a_cadena(double d)
{
    char s[64];
    char* r = __memoria_asignar(strlen(s) + 1);
    snprintf(s, 64, "%g", (float)d);
    strcpy(r, s);
    return r;
}

char* __str_caracter_a_cadena(char c)
{
    char s[2];
    char* r = __memoria_asignar(2);
    snprintf(s, 2, "%c", c);
    strcpy(r, s);
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

int __str_posicion(char* base, char* str)
{
    return __str_intercambiar_posicion(base, str, 0);
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

/* Funciones publicas de cadena para Latino */
void lat_comparar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_entero_nuevo(vm, strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)));
}

void lat_concatenar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    lat_objeto* x = NULL;
    lat_objeto* y = NULL;
    switch (a->type)
    {
    case T_BOOL:
        x = lat_cadena_nueva(vm, __str_logico_a_cadena(a->data.b));
        break;
    case T_INT:
        x = lat_cadena_nueva(vm, __str_entero_a_cadena(a->data.i));
        break;
    case T_DOUBLE:
        x = lat_cadena_nueva(vm, __str_numerico_a_cadena(a->data.d));
        break;
    default:
        x = lat_cadena_nueva(vm, a->data.str);
        break;
    }
    switch (b->type)
    {
    case T_BOOL:
        y = lat_cadena_nueva(vm, __str_logico_a_cadena(b->data.b));
        break;
    case T_INT:
        y = lat_cadena_nueva(vm, __str_entero_a_cadena(b->data.i));
        break;
    case T_DOUBLE:
        y = lat_cadena_nueva(vm, __str_numerico_a_cadena(b->data.d));
        break;
    default:
        y = lat_cadena_nueva(vm, b->data.str);
        break;
    }
    vm->registros[255] = lat_cadena_nueva(vm, __str_concatenar(lat_obtener_cadena(x), lat_obtener_cadena(y)));
}

void lat_contiene(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    char *result = strstr(lat_obtener_cadena(a), lat_obtener_cadena(b));
    if (result != NULL)
    {
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

void lat_copiar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    vm->registros[255] = lat_clonar_objeto(vm, b);
}

void lat_termina_con(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (__str_termina_con(lat_obtener_cadena(a), lat_obtener_cadena(b)))
    {
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

void lat_es_igual(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)) == 0)
    {
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

/*
void lat_format(lat_vm* vm){
}
*/

void lat_indice(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_entero_nuevo(vm, __str_posicion(lat_obtener_cadena(a), lat_obtener_cadena(b)));
}

void lat_insertar(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_insertar(lat_obtener_cadena(a), lat_obtener_cadena(b), lat_obtener_entero(c)));
}

void lat_ultimo_indice(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_entero_nuevo(vm, __str_ultima_posicion(lat_obtener_cadena(a), lat_obtener_cadena(b)));
}

void lat_rellenar_izquierda(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_rellenar_izquierda(lat_obtener_cadena(a), lat_obtener_entero(b), lat_obtener_literal(c)));
}

void lat_rellenar_derecha(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_rellenar_derecha(lat_obtener_cadena(a), lat_obtener_entero(b), lat_obtener_literal(c)));
}

void lat_eliminar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(a->type == T_STR || a->type == T_LIT)
    {
        vm->registros[255] = lat_cadena_nueva(vm, __str_reemplazar(lat_obtener_cadena(a), lat_obtener_cadena(b), ""));
    }
    /*if(a->type == T_LIST)
    {
        remove_list(a->data.lista, b);
    }*/
}

void lat_esta_vacia(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (strcmp(lat_obtener_cadena(a), "") == 0)
    {
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

void lat_longitud(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (a->type == T_STR || a->type == T_LIT)
    {
        vm->registros[255] = lat_entero_nuevo(vm, strlen(lat_obtener_cadena(a)));
    }
    if (a->type == T_LIST)
    {
        vm->registros[255] = lat_entero_nuevo(vm, __lista_longitud(lat_obtener_lista(a)));
    }

}

void lat_reemplazar(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_reemplazar(lat_obtener_cadena(a), lat_obtener_cadena(b), lat_obtener_cadena(c)));
}

void lat_empieza_con(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (__str_empieza_con(lat_obtener_cadena(a), lat_obtener_cadena(b)))
    {
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

void lat_subcadena(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_subcadena(lat_obtener_cadena(a), lat_obtener_entero(b), lat_obtener_entero(c)));
}

void lat_minusculas(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_minusculas(lat_obtener_cadena(a)));
}

void lat_mayusculas(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_mayusculas(lat_obtener_cadena(a)));
}

void lat_quitar_espacios(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, __str_quitar_espacios(lat_obtener_cadena(a)));
}

void lat_es_numero(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if(a->type == T_INT || a->type == T_DOUBLE)
    {
        vm->registros[255] = vm->objeto_verdadero;
        return;
    }
    char* cad = lat_obtener_cadena(a);
    if(atoi(cad))
    {
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

void lat_es_alfanumerico(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (a->type != T_STR && a->type != T_LIT)
    {
        vm->registros[255] = vm->objeto_falso;
        return;
    }
    char* cad = lat_obtener_cadena(a);
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
        vm->registros[255] = vm->objeto_verdadero;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}
