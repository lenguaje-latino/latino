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
    lat_objeto* str = (lat_objeto*)lat_asignar_memoria(sizeof(lat_objeto));
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

char* strdup0(const char* s)
{
    size_t len = strlen(s);
    char* p;
    p = lat_asignar_memoria(len + 1);
    if (p)
    {
        strncpy(p, s, len);
    }
    p[len] = '\0';
    return p;
}

char* parse_string(const char* s, size_t len)
{
    char* ret = lat_asignar_memoria(len + 1);
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

char* concat(char* s1, char* s2)
{
    char* s3 = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

char* int2str(long i)
{
    char s[255];
    char* r = malloc(strlen(s) + 1);
    snprintf(s, 255, "%ld", i);
    strcpy(r, s);
    return r;
}

char* double2str(double d)
{
    char s[64];
    char* r = malloc(strlen(s) + 1);
    snprintf(s, 64, "%g", (float)d);
    strcpy(r, s);
    return r;
}

char* char2str(char c)
{
    char s[2];
    char* r = malloc(2);
    snprintf(s, 2, "%c", c);
    strcpy(r, s);
    return r;
}

char* bool2str(int i)
{
    char s[10];
    char* r = malloc(11);
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

bool startsWith(const char* base, const char* str)
{
    return (strstr(base, str) - base) == 0;
}

bool endsWith(char* base, char* str)
{
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

int indexOf(char* base, char* str)
{
    return indexOf_shift(base, str, 0);
}

int indexOf_shift(char* base, char* str, int startIndex)
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

int lastIndexOf(char* base, char* str)
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
            start = indexOf_shift(base, str, start);
            end = indexOf_shift(base, str, end);
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

char* insert(char *dest, char* src, int pos)
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
    char *m = malloc(srclen + dstlen + 1);
    memcpy(m, dest, pos);
    memcpy(m + pos, src, srclen);
    memcpy(m + pos + srclen, dest + pos, dstlen - pos + 1);
    return m;
}

char* padLeft(char* base, int n, char* c)
{
    int len = (int)strlen(base);
    char *ret = NULL;
    if (n <= len)
    {
        ret = malloc(len + 1);
        strcpy(ret, base);
        return ret;
    }
    ret = malloc(n + 1);
    ret = "";
    int i = 0;
    for (i = 0; i < (n - len); i++)
    {
        ret = concat(ret, c);
    }
    ret = concat(ret, base);
    return ret;
}

char* padRight(char *base, int n, char* c)
{
    int len = (int)strlen(base);
    char *ret = NULL;
    if (len >= n)
    {
        ret = malloc(len + 1);
        strcpy(ret, base);
        return ret;
    }
    ret = malloc(n + 1);
    ret = base;
    int i;
    for (i = 0; i < (n - len); i++)
    {
        ret = concat(ret, c);
    }
    return ret;
}

char *replace(char *str, char *orig, char *rep)
{
    char *buffer = lat_asignar_memoria(MAX_STR_LENGTH);
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
        strcpy(buffer, replace(buffer, orig, rep));
    }
    return buffer;
}

char *substring(const char* str, int beg, int n)
{
    char *ret = malloc(n + 1);
    strncpy(ret, (str + beg), n);
    *(ret + n) = 0;

    return ret;
}

char *toLower(const char* str)
{
    int i = 0;
    int len = strlen(str);
    char *ret = (char*)malloc(len + 1);
    for (i = 0; i < len; i++)
    {
        ret[i] = tolower(str[i]);
    }
    ret[len] = 0;
    return ret;
}

char *toUpper(const char* str)
{
    int i = 0;
    int len = strlen(str);
    char *ret = malloc(len + 1);
    for (i = 0; i < len; i++)
    {
        ret[i] = toupper(str[i]);
    }
    ret[len] = 0;
    return ret;
}

char* trim(const char *str)
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
    char *ret = malloc((end - start) + 1);
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
lat_objeto* lat_cadena_hash(const char* p, size_t len)
{
    if (p && (len < MAX_STR_INTERN))
    {
        return str_intern(p, len);
    }
    return str_new(p, len);
}

void lat_comparar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_entero_nuevo(vm, strcmp(lat_obtener_cadena(a), lat_obtener_cadena(b)));
}

void lat_concatenar(lat_vm* vm)
{
    //lat_imprimir_lista(vm, vm->pila);
    //printf("%s\n", "antes de concatenando\n");
    lat_objeto* b = lat_desapilar(vm);
    //lat_imprimir_lista(vm, vm->pila);
    lat_objeto* a = lat_desapilar(vm);
    //lat_imprimir_lista(vm, vm->pila);

    lat_objeto* x = NULL;
    lat_objeto* y = NULL;
    switch (a->type)
    {
    case T_BOOL:
        x = lat_cadena_nueva(vm, bool2str(a->data.b));
        break;
    case T_INT:
        x = lat_cadena_nueva(vm, int2str(a->data.i));
        break;
    case T_DOUBLE:
        x = lat_cadena_nueva(vm, double2str(a->data.d));
        break;
    default:
        x = lat_cadena_nueva(vm, a->data.str);
        break;
    }

    switch (b->type)
    {
    case T_BOOL:
        y = lat_cadena_nueva(vm, bool2str(b->data.b));
        break;
    case T_INT:
        y = lat_cadena_nueva(vm, int2str(b->data.i));
        break;
    case T_DOUBLE:
        y = lat_cadena_nueva(vm, double2str(b->data.d));
        break;
    default:
        y = lat_cadena_nueva(vm, b->data.str);
        break;
    }
    //lat_imprimir_lista(vm, vm->pila);
    vm->registros[255] = lat_cadena_nueva(vm, concat(lat_obtener_cadena(x), lat_obtener_cadena(y)));
    //printf("%s\n", "despues de concatenando\n");
}

void lat_contiene(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    char *result = strstr(lat_obtener_cadena(a), lat_obtener_cadena(b));
    if (result != NULL)
    {
        vm->registros[255] = vm->objeto_cierto;
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
    if (endsWith(lat_obtener_cadena(a), lat_obtener_cadena(b)))
    {
        vm->registros[255] = vm->objeto_cierto;
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
        vm->registros[255] = vm->objeto_cierto;
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
    vm->registros[255] = lat_entero_nuevo(vm, indexOf(lat_obtener_cadena(a), lat_obtener_cadena(b)));
}

void lat_insertar(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, insert(lat_obtener_cadena(a), lat_obtener_cadena(b), lat_obtener_entero(c)));
}

void lat_ultimo_indice(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_entero_nuevo(vm, lastIndexOf(lat_obtener_cadena(a), lat_obtener_cadena(b)));
}

void lat_rellenar_izquierda(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, padLeft(lat_obtener_cadena(a), lat_obtener_entero(b), lat_obtener_literal(c)));
}

void lat_rellenar_derecha(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, padRight(lat_obtener_cadena(a), lat_obtener_entero(b), lat_obtener_literal(c)));
}

void lat_eliminar(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if(a->type == T_STR || a->type == T_LIT)
    {
        vm->registros[255] = lat_cadena_nueva(vm, replace(lat_obtener_cadena(a), lat_obtener_cadena(b), ""));
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
        vm->registros[255] = vm->objeto_cierto;
    }
    else
    {
        vm->registros[255] = vm->objeto_falso;
    }
}

void lat_longitud(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if (a->type == T_STR || a->type == T_LIT){
        vm->registros[255] = lat_entero_nuevo(vm, strlen(lat_obtener_cadena(a)));
    }
    if (a->type == T_LIST){
        vm->registros[255] = lat_entero_nuevo(vm, length_list(lat_obtener_lista(a)));
    }

}

void lat_reemplazar(lat_vm* vm)
{
    lat_objeto* c = lat_desapilar(vm);
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, replace(lat_obtener_cadena(a), lat_obtener_cadena(b), lat_obtener_cadena(c)));
}

void lat_empieza_con(lat_vm* vm)
{
    lat_objeto* b = lat_desapilar(vm);
    lat_objeto* a = lat_desapilar(vm);
    if (startsWith(lat_obtener_cadena(a), lat_obtener_cadena(b)))
    {
        vm->registros[255] = vm->objeto_cierto;
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
    vm->registros[255] = lat_cadena_nueva(vm, substring(lat_obtener_cadena(a), lat_obtener_entero(b), lat_obtener_entero(c)));
}

void lat_minusculas(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, toLower(lat_obtener_cadena(a)));
}

void lat_mayusculas(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, toUpper(lat_obtener_cadena(a)));
}

void lat_quitar_espacios(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    vm->registros[255] = lat_cadena_nueva(vm, trim(lat_obtener_cadena(a)));
}

void lat_es_numero(lat_vm* vm)
{
    lat_objeto* a = lat_desapilar(vm);
    if(a->type == T_INT || a->type == T_DOUBLE){
        vm->registros[255] = vm->objeto_cierto;
        return;
    }
    if(a->type != T_STR && a->type != T_LIT){
        lat_error("El parametro debe de ser una cadena");
        return;
    }
    char* cad = lat_obtener_cadena(a);
    if(atoi(cad)){
        vm->registros[255] = vm->objeto_cierto;
    }else{
        vm->registros[255] = vm->objeto_falso;
    }       
}
