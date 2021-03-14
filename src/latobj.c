/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

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

#include <stdlib.h>
#include <string.h>

#define LATINO_CORE

#include "latdic.h"
#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latobj.h"

lat_objeto latO_nulo_ = {{NULL}, T_NULL};
lat_objeto latO_verdadero_ = {.val.logico = 1, .tipo = T_BOOL};
lat_objeto latO_falso_ = {.val.logico = 0, T_BOOL};

char *minusculas(const char *str);
char *logico_acadena(int i);
char *decimal_acadena(double d);
char *entero_acadena(int i);
char *reemplazar(char *str, const char *orig, const char *rep);
char *analizar_fmt(const char *s, size_t len);
char *analizar(const char *s, size_t len);

void latO_asignar_ctx(lat_mv *mv, lat_objeto *ns, const char *name,
                      lat_objeto *o) {
    if (ns->tipo != T_CONTEXT) {
        latC_error(mv, "Objeto no es un contexto");
    } else {
        hash_map *h = getCtx(ns);
        if (strlen(name) > MAX_ID_LENGTH) {
            latC_error(mv, "Nombre de id mayor a %i caracteres", MAX_ID_LENGTH);
        }
        latH_asignar(mv, h, name, o);
    }
}

lat_objeto *latO_obtener_contexto(lat_mv *mv, lat_objeto *ns,
                                  const char *name) {
    if (ns->tipo != T_CONTEXT) {
        latC_error(mv, "Objeto no es un contexto");
    } else {
        hash_map *h = getCtx(ns);
        lat_objeto *ret = (lat_objeto *)latH_obtener(h, name);
        return ret;
    }
    return NULL;
}

lat_objeto *latO_crear(lat_mv *mv) {
    lat_objeto *ret = (lat_objeto *)latM_asignar(mv, sizeof(lat_objeto));
#if DEPURAR_MEM
    printf("latO_crear.ret: %p\n", ret);
#endif
    ret->tipo = T_NULL;
    ret->tam = sizeof(lat_objeto);
    ret->nref = 0;
    ret->es_vararg = 0;
    ret->esconst = 0;
#ifdef HABILITAR_GC
    gc_agregar(mv, ret);
#endif // HABILITAR_GC
    return ret;
}

lat_objeto *latO_contexto_crear(lat_mv *mv) {
    lat_objeto *ret = latO_crear(mv);
    ret->tipo = T_CONTEXT;
    ret->tam += sizeof(hash_map);
    setCtx(ret, latH_crear(mv));
    return ret;
}

static lat_cadena *nuevaCad(lat_mv *mv, const char *str, size_t l,
                            unsigned int h) {
    lat_cadena *ts;
    stringtable *tb;
    if (l + 1 > LAT_SIZE_MAX - sizeof(lat_cadena)) {
        latC_error(mv, "Cadena muy larga");
    }
    ts = (lat_cadena *)latM_asignar(mv, (l + 1) + sizeof(lat_cadena));
#if DEPURAR_MEM
    printf("nuevaCad.ts: %p\n", ts);
#endif
    ts->tsv.len = l;
    ts->tsv.hash = h;
    ts->tsv.marked = 0;
    ts->tsv.tipo = T_STR;
    ts->tsv.reserved = 0;
    memcpy(ts + 1, str, l);
    ((char *)(ts + 1))[l] = '\0';
    tb = &mv->global->strt;
    h = lmod(h, tb->size);
    ts->tsv.next = tb->hash[h];
    tb->hash[h] = (lat_gcobjeto *)ts;
    tb->nuse++;
    if (tb->nuse > tb->size && tb->size <= INT_MAX / 2) {
        latS_resize(mv, tb->size * 2);
    }
    return ts;
}

static lat_cadena *latO_cadenaNueva(lat_mv *mv, const char *str, size_t l) {
    lat_gcobjeto *o;
    unsigned int h = (unsigned int)l;
    size_t step = (l >> 5) + 1;
    size_t l1;
    for (l1 = l; l1 >= step; l1 -= step) {
        h = h ^ ((h << 5) + (h >> 2) + (unsigned char)str[l1 - 1]);
    }
    for (o = mv->global->strt.hash[lmod(h, mv->global->strt.size)]; o != NULL;
         o = o->gch.next) {
        lat_cadena *ts = &(o->cadena);
        if (ts->tsv.len == l && (0 == memcmp(str, getstr(ts), l))) {
            return ts;
        }
    }
    return nuevaCad(mv, str, l, h);
}

lat_objeto *latO_crear_funcion(lat_mv *mv) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latO_crear_funcion: %p\n", ret);
#endif
    ret->tipo = T_FUN;
    return ret; // We don't do anything here: all bytecode will be added
                // later
}

lat_objeto *latO_crear_cfuncion(lat_mv *mv) {
    lat_objeto *ret = latO_crear(mv);
    ret->tipo = T_CFUN;
    ret->marca = 0;
    return ret;
}

void latO_destruir(lat_mv *mv, lat_objeto *o) {
    if (o == NULL)
        return;
    switch (o->tipo) {
        case T_CONTEXT:
            latH_limpiar(mv, getCtx(o));
            break;
        case T_LIST: {
            lista *list = latC_checar_lista(mv, o);
            if (list->longitud > 0) {
                LIST_FOREACH(list, primero, siguiente, cur) {

                    lat_objeto *tmp = (lat_objeto *)cur->valor;
                    if (tmp != NULL) {
                        latO_destruir(mv, tmp);
                    }
                }
            }
            latL_destruir(mv, list);
        } break;
        case T_DIC:
            latH_destruir(mv, latC_checar_dic(mv, o));
            break;
        case T_STR: {
            lat_cadena *str = (lat_cadena *)getCadena(o);
            latM_liberar(mv, str);
        } break;
        case T_FUN: {
            lat_funcion *fun = getFun(o);
            lat_bytecode *inslist = fun->codigo;
            latM_liberar(mv, inslist);
            latM_liberar(mv, fun);
        } break;
        case T_CFUN: {
            ;
        } break;
        case T_NUMERIC: {
            ;
        } break;
        case T_NULL:
        case T_BOOL:
            // Nunca colectar nulo y booleano.
            return;
        default:
            return;
    }
    latM_liberar(mv, o);
}

static lista *latL_clonar(lat_mv *mv, lista *list) {
    lista *ret = latL_crear(mv);

    LIST_FOREACH(list, primero, siguiente, cur) {
        lat_objeto *tmp = (lat_objeto *)cur->valor;
        latL_agregar(mv, ret, tmp);
    }
    return ret;
}

lat_objeto *latO_clonar(lat_mv *mv, lat_objeto *obj) {
    lat_objeto *ret = NULL;
    switch (obj->tipo) {
        case T_CONTEXT:
            ret = latO_crear(mv);
            ret->tipo = T_CONTEXT;
            ret->tam = sizeof(hash_map *);
            setCtx(ret, latH_clonar(mv, getCtx(obj)));
            break;
        case T_LIST:
            ret = latC_crear_lista(mv,
                                   latL_clonar(mv, latC_checar_lista(mv, obj)));
            break;
        case T_DIC:
            ret = latC_crear_dic(mv, latH_clonar(mv, latC_checar_dic(mv, obj)));
            break;
        case T_FUN:
            ret = latO_crear(mv);
            ret->tipo = obj->tipo;
            ret->nombre = obj->nombre;
            setFun(ret, getFun(obj));
            ret->nparams = obj->nparams;
            break;
        case T_CFUN:
            ret = latO_crear(mv);
            ret->tipo = obj->tipo;
            ret->nombre = obj->nombre;
            setCfun(ret, getCfun(obj));
            ret->nparams = obj->nparams;
            break;
        case T_STR: {
            ret = latC_crear_cadena(mv, latC_checar_cadena(mv, obj));
        } break;
        case T_NUMERIC:
            ret = latC_crear_numerico(mv, latC_checar_numerico(mv, obj));
            break;
        case T_LABEL: {
            ret = latC_crear_cadena(mv, latC_checar_cadena(mv, obj));
            ret->nombre = obj->nombre;
            ret->tipo = obj->tipo;
            ret->jump_label = obj->jump_label;
        } break;
        default:
            ret = latO_crear(mv);
            ret->tipo = obj->tipo;
            ret->val = obj->val;
            break;
    }
    ret->nref = obj->nref;
    ret->marca = obj->marca;
    ret->tam = obj->tam;
    ret->es_vararg = obj->es_vararg;
    ret->esconst = obj->esconst;
    return ret;
}

bool latO_es_igual(lat_mv *mv, lat_objeto *lhs, lat_objeto *rhs) {
    if (lhs->tipo != rhs->tipo) {
        return false;
    }
    if (lhs->tipo == T_NUMERIC) {
        return latC_checar_numerico(mv, lhs) == latC_checar_numerico(mv, rhs);
    }
    if (lhs->tipo == T_STR) {
        return !strcmp(latC_checar_cadena(mv, lhs), latC_checar_cadena(mv, rhs))
                   ? true
                   : false;
    }
    if (lhs->tipo == T_LIST) {
        return latL_comparar(mv, latC_checar_lista(mv, lhs),
                             latC_checar_lista(mv, rhs)) == 0
                   ? true
                   : false;
    }
    return false;
}

int latO_comparar(lat_mv *mv, lat_objeto *lhs, lat_objeto *rhs) {
    int res = 1;
    if (lhs->tipo != rhs->tipo || lhs->tipo == T_DIC || rhs->tipo == T_DIC) {
        char *buffer = latC_astring(mv, lhs);
        char *buffer2 = latC_astring(mv, rhs);
        res = strcmp(buffer, buffer2);
        free(buffer);
        free(buffer2);
        goto RESPUESTA;
    }
    if (lhs->tipo == T_BOOL) {
        res = latC_checar_logico(mv, lhs) - latC_checar_logico(mv, rhs);
        goto RESPUESTA;
    }
    if (lhs->tipo == T_NUMERIC) {
        res = latC_checar_numerico(mv, lhs) - latC_checar_numerico(mv, rhs);
        goto RESPUESTA;
    }
    if (lhs->tipo == T_STR) {
        res = strcmp(latC_checar_cadena(mv, lhs), latC_checar_cadena(mv, rhs));
        goto RESPUESTA;
    }
    if (lhs->tipo == T_LIST) {
        res = latL_comparar(mv, latC_checar_lista(mv, lhs),
                            latC_checar_lista(mv, rhs));
        goto RESPUESTA;
    }
RESPUESTA:
    if (res < 0) {
        return -1;
    }
    if (res > 0) {
        return 1;
    }
    return res;
}

char *latL_acadena(lat_mv *mv, lista *list) {
    // return strdup("latL_acadena");
    char *valor = calloc(1, MAX_STR_LENGTH);
    strcat(valor, "[");
    if (list->longitud > 0) {
        LIST_FOREACH(list, primero, siguiente, cur) {
            if (cur->valor != NULL) {
                lat_objeto *o = ((lat_objeto *)cur->valor);
                if (o != NULL) {
                    char *tmp = latC_astring(mv, o);
                    if (o->tipo == T_STR) {
                        if (strstr(latC_checar_cadena(mv, o), "\"") != NULL) {
                            strcat(valor, "'");
                        } else {
                            strcat(valor, "\"");
                        }
                    }
                    strcat(valor, tmp);
                    // free(tmp);
                    if (o->tipo == T_STR) {
                        if (strstr(latC_checar_cadena(mv, o), "\"") != NULL) {
                            strcat(valor, "'");
                        } else {
                            strcat(valor, "\"");
                        }
                    }
                    if (cur != list->ultimo) {
                        strcat(valor, ", ");
                    }
                }
            }
        }
    }
    strcat(valor, "]");
    valor[strlen(valor)] = '\0';
    return valor;
}

char *latH_acadena(lat_mv *mv, hash_map *m) {
    char *valor = calloc(1, MAX_STR_LENGTH);
    strcat(valor, "{");
    int i;
    for (i = 0; i < 256; i++) {
        lista *list = m->buckets[i];
        if (list != NULL) {

            LIST_FOREACH(list, primero, siguiente, cur) {
                if (cur->valor != NULL) {
                    strcat(valor, "\"");
                    strcat(valor, ((hash_val *)cur->valor)->llave);
                    strcat(valor, "\"");
                    lat_objeto *val =
                        (lat_objeto *)((hash_val *)cur->valor)->valor;
                    strcat(valor, ": ");
                    if (val == NULL) {
                        strcat(valor, "\"nulo\"");
                    } else {
                        if (val->tipo == T_STR) {
                            if (strstr(latC_checar_cadena(mv, val), "\"") !=
                                NULL) {
                                strcat(valor, "'");
                            } else {
                                strcat(valor, "\"");
                            }
                        }
                        char *tmp = latC_astring(mv, val);
                        strcat(valor, tmp);
                        free(tmp);
                        if (val->tipo == T_STR) {
                            if (strstr(latC_checar_cadena(mv, val), "\"") !=
                                NULL) {
                                strcat(valor, "'");
                            } else {
                                strcat(valor, "\"");
                            }
                        }
                    }
                    strcat(valor, ", ");
                }
            }
        }
    }
    strcat(valor, "}");
    char *tmp = reemplazar(valor, ", }", "}"); // elimina la ultima coma
    tmp[strlen(tmp)] = '\0';
    free(valor);
    return tmp;
}

void latL_modificar_elemento(lat_mv *mv, lista *list, void *data, int pos) {
    int i = 0;
    if (pos < 0 || pos >= latL_longitud(list)) {
        latC_error(mv, "Indice fuera de rango");
    }

    LIST_FOREACH(list, primero, siguiente, cur) {
        if (i == pos) {
            cur->valor = data;
        }
        i++;
    }
}

int latL_comparar(lat_mv *mv, lista *lhs, lista *rhs) {
    int res = 0;
    int len1 = latL_longitud(lhs);
    int len2 = latL_longitud(rhs);
    if (len1 < len2) {
        return -1;
    }
    if (len1 > len2) {
        return 1;
    }
    int i;
    for (i = 0; i < len1; i++) {
        lat_objeto *tmp1 = latL_obtener_elemento(mv, lhs, i);
        lat_objeto *tmp2 = latL_obtener_elemento(mv, rhs, i);
        res = latO_comparar(mv, tmp1, tmp2);
        if (res < 0) {
            return -1;
        }
        if (res > 0) {
            return 1;
        }
    }
    return res;
}

int latL_obtener_indice(lat_mv *mv, lista *list, void *data) {
    int i = 0;
    lat_objeto *find = (lat_objeto *)data;

    LIST_FOREACH(list, primero, siguiente, cur) {
        // if (memcmp(cur->valor, data, sizeof(cur->valor)) == 0)
        lat_objeto *tmp = (lat_objeto *)cur->valor;
        if (latO_es_igual(mv, find, tmp)) {
            return i;
        }
        i++;
    }
    return -1;
}

void latO_imprimir(lat_mv *mv, lat_objeto *o, bool fmt) {
    char *tmp = latC_astring(mv, o);
    char *tmp2 = NULL;
    if (fmt) {
        tmp2 = analizar_fmt(tmp, strlen(tmp));
        printf("%s", tmp2);
    } else {
        tmp2 = analizar(tmp, strlen(tmp));
        printf("%s", tmp2);
    }
    latM_liberar(mv, tmp);
    latM_liberar(mv, tmp2);
}

void latS_resize(lat_mv *mv, int newsize) {
    lat_gcobjeto **newhash;
    stringtable *tb;
    int i;
    newhash = latM_asignar(mv, newsize * sizeof(lat_gcobjeto *));
#if DEPURAR_MEM
    printf("latS_resize.newhash: %p\n", newhash);
#endif
    tb = &mv->global->strt;
    for (i = 0; i < newsize; i++) {
        newhash[i] = NULL;
    }
    for (i = 0; i < tb->size; i++) {
        lat_gcobjeto *p = tb->hash[i];
        while (p) {
            lat_gcobjeto *next = p->gch.next;
            unsigned int h = (&p->cadena)->tsv.hash;
            int h1 = lmod(h, newsize);
            p->gch.next = newhash[h1];
            newhash[h1] = p;
            p = next;
        }
    }
    latM_liberar(mv, tb->hash);
    tb->size = newsize;
    tb->hash = newhash;
}

LATINO_API lat_objeto *latC_crear_logico(lat_mv *mv, bool val) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_logico: %p\n", ret);
#endif
    ret->tam += sizeof(bool);
    setLogico(ret, val);
    return ret;
}

LATINO_API lat_objeto *latC_crear_numerico(lat_mv *mv, double val) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_numerico: %p\n", ret);
#endif
    ret->tam += sizeof(double);
    setNumerico(ret, val);
    return ret;
}

LATINO_API lat_objeto *latC_crear_entero(lat_mv *mv, int val) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_entero: %p\n", ret);
#endif
    ret->tam += sizeof(int);
    setEntero(ret, val);
    return ret;
}

LATINO_API lat_objeto *latC_crear_caracter(lat_mv *mv, char val) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_caracter: %p\n", ret);
#endif
    ret->tam += sizeof(int);
    setCaracter(ret, val);
    return ret;
}

LATINO_API lat_objeto *latC_crear_cadena(lat_mv *mv, const char *p) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_cadena: %p\n", ret);
#endif
    ret->tam += strlen(p);
    setCadena(ret, latO_cadenaNueva(mv, p, strlen(p)));
    return ret;
}

LATINO_API lat_objeto *latC_crear_lista(lat_mv *mv, lista *l) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_lista: %p\n", ret);
#endif
    ret->tam += sizeof(lista);
    setLista(ret, l);
    return ret;
}

LATINO_API lat_objeto *latC_crear_dic(lat_mv *mv, hash_map *dic) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_dic: %p\n", ret);
#endif
    ret->tam += sizeof(hash_map);
    setDic(ret, dic);
    return ret;
}

LATINO_API lat_objeto *latC_crear_cdato(lat_mv *mv, void *ptr) {
    lat_objeto *ret = latO_crear(mv);
#if DEPURAR_MEM
    printf("latC_crear_cdato: %p\n", ret);
#endif
    setPtr(ret, ptr);
    return ret;
}

LATINO_API bool latC_checar_logico(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_BOOL) {
        return getLogico(o);
    }
    latC_error(mv, "El parametro debe de ser un valor logico");
    return false;
}

LATINO_API double latC_checar_numerico(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_NUMERIC) {
        return getNumerico(o);
    }
    latC_error(mv, "El parametro debe de ser un decimal");
    return 0;
}

LATINO_API int latC_checar_entero(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_INTEGER) {
        return getEntero(o);
    }
    latC_error(mv, "El parametro debe de ser un entero");
    return 0;
}

LATINO_API char latC_checar_caracter(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_CHAR) {
        return getCaracter(o);
    }
    latC_error(mv, "El parametro debe de ser un caracter");
    return 0;
}

LATINO_API char *latC_checar_cadena(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_STR || o->tipo == T_LABEL) {
        return getstr(getCadena(o));
    }
    latC_error(mv, "El parametro debe de ser una cadena");
    return 0;
}

LATINO_API lista *latC_checar_lista(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_LIST) {
        return getLista(o);
    }
    latC_error(mv, "El parametro debe de ser una lista");
    return NULL;
}

LATINO_API hash_map *latC_checar_dic(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_DIC) {
        return getDic(o);
    }
    latC_error(mv, "El parametro debe de ser un diccionario");
    return NULL;
}

LATINO_API void *latC_checar_cptr(lat_mv *mv, lat_objeto *o) {
    if (o->tipo == T_CPTR) {
        return getPtr(o);
    }
    latC_error(mv, "El parametro debe de ser un dato de c (void *)");
    return NULL;
}

LATINO_API bool latC_abool(lat_mv *mv, lat_objeto *o) {
    switch (o->tipo) {
        case T_NULL:
            return false;
            break;
        case T_BOOL:
            return latC_checar_logico(mv, o);
            break;
        case T_NUMERIC:
            return latC_checar_numerico(mv, o) == 0 ? false : true;
            break;
        case T_STR:
            return !strcmp(latC_checar_cadena(mv, o), "") ||
                           !strcmp(latC_checar_cadena(mv, o), "0") ||
                           !strcmp(minusculas(latC_astring(mv, o)), "falso") ||
                           !strcmp(minusculas(latC_astring(mv, o)), "false")
                       ? false
                       : true;
            break;
        case T_LIST:
            return latL_longitud(latC_checar_lista(mv, o)) == 0 ? false : true;
        case T_DIC:
            return latH_longitud(latC_checar_dic(mv, o)) == 0 ? false : true;
        default:
            latC_error(mv, "Conversion de tipo de dato incompatible");
            break;
    }
    return false;
}

LATINO_API double latC_adouble(lat_mv *mv, lat_objeto *o) {
    switch (o->tipo) {
        case T_NULL:
            return 0;
            break;
        case T_BOOL:
            return latC_checar_logico(mv, o) == false ? 0 : 1;
            break;
        case T_NUMERIC:
            return latC_checar_numerico(mv, o);
            break;
        case T_STR: {
            char *ptr;
            double ret;
            ret = strtod(latC_checar_cadena(mv, o), &ptr);
            if (!strcmp(ptr, "")) {
                return ret;
            } else {
                ret = (int)(latC_checar_cadena(mv, o)[0]);
                return ret;
            }
        } break;
        case T_LIST:
            return latL_longitud(latC_checar_lista(mv, o));
            break;
        case T_DIC:
            return latH_longitud(latC_checar_dic(mv, o));
            break;
        default:
            latC_error(mv, "Conversion de tipo de dato incompatible");
            break;
    }
    return 0;
}

// FIXME:
LATINO_API int latC_aint(lat_mv *mv, lat_objeto *o) {
    switch (o->tipo) {
        case T_NULL:
            return 0;
            break;
        case T_BOOL:
            return latC_checar_logico(mv, o) == false ? 0 : 1;
            break;
        case T_NUMERIC:
            return latC_checar_entero(mv, o);
            break;
        case T_CHAR:
            return latC_checar_caracter(mv, o);
            break;
        case T_STR: {
            char *ptr;
            double ret;
            ret = strtod(latC_checar_cadena(mv, o), &ptr);
            if (!strcmp(ptr, "")) {
                return ret;
            } else {
                ret = (int)(latC_checar_cadena(mv, o)[0]);
                return ret;
            }
        } break;
        case T_LIST:
            return latL_longitud(latC_checar_lista(mv, o));
            break;
        case T_DIC:
            return latH_longitud(latC_checar_dic(mv, o));
            break;
        default:
            latC_error(mv, "Conversion de tipo de dato incompatible");
            break;
    }
    return 0;
}

// FIXME:
LATINO_API char latC_achar(lat_mv *mv, lat_objeto *o) {
    switch (o->tipo) {
        case T_NULL:
            return 0;
            break;
        case T_BOOL:
            return latC_checar_logico(mv, o) == false ? 0 : 1;
            break;
        case T_NUMERIC:
            return latC_checar_entero(mv, o);
            break;
        case T_INTEGER:
            return latC_checar_entero(mv, o);
            break;
        case T_CHAR:
            return latC_checar_caracter(mv, o);
            break;
        case T_STR: {
            char *ptr;
            double ret;
            ret = strtod(latC_checar_cadena(mv, o), &ptr);
            if (!strcmp(ptr, "")) {
                return ret;
            } else {
                ret = (int)(latC_checar_cadena(mv, o)[0]);
                return ret;
            }
        } break;
        case T_LIST:
            return latL_longitud(latC_checar_lista(mv, o));
            break;
        case T_DIC:
            return latH_longitud(latC_checar_dic(mv, o));
            break;
        default:
            latC_error(mv, "Conversion de tipo de dato incompatible");
            break;
    }
    return 0;
}

LATINO_API char *latC_astring(lat_mv *mv, lat_objeto *o) {
    if (o == NULL || o->tipo == T_NULL) {
        return strdup("nulo");
    } else if (o->tipo == T_BOOL) {
        return logico_acadena(latC_checar_logico(mv, o));
    } else if (o->tipo == T_CONTEXT) {
        return strdup("contexto");
    } else if (o->tipo == T_NUMERIC) {
        return decimal_acadena(getNumerico(o));
    } else if (o->tipo == T_INTEGER) {
        return entero_acadena(getEntero(o));
    } else if (o->tipo == T_CHAR) {
        return (char)getCaracter(o);
    } else if (o->tipo == T_STR) {
        return strdup(latC_checar_cadena(mv, o));
    } else if (o->tipo == T_LABEL) {
        return strdup(latC_checar_cadena(mv, o));
    } else if (o->tipo == T_FUN) {
        return strdup("fun");
    } else if (o->tipo == T_CFUN) {
        return strdup("cfun");
    } else if (o->tipo == T_CLASS) {
        return strdup("clase");
    } else if (o->tipo == T_LIST) {
        return latL_acadena(mv, latC_checar_lista(mv, o));
    } else if (o->tipo == T_DIC) {
        return latH_acadena(mv, latC_checar_dic(mv, o));
    }
    return strdup("");
}
