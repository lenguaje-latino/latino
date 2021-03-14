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

#ifndef _LATINO_OBJ_H_
#define _LATINO_OBJ_H_

#include <stdbool.h>
#include <stdlib.h>

#include "latino.h"

typedef unsigned char lat_byte;

/** \file object.h
 *
 * Contiene las funciones para el manejo de objetos
 *
 */

/**< Incrementa y decrementa las referencias de un objeto */
#define Lat_INCREF(o)                                                          \
    if (o != NULL && o->marca)                                                 \
    o->nref++

#define Lat_DECREF(o)                                                          \
    if (o != NULL && o->marca)                                                 \
    o->nref--

/** \brief Tipo de dato
 *
 * Tipo de dato que maneja la maquina virtual
 */
typedef enum lat_tipo {
    T_NULL, // 0
    T_BOOL,
    T_NUMERIC,
    T_STR,
    T_CONTEXT,
    T_LIST, // 5
    T_DIC,
    T_FUN,
    T_CFUN,
    T_CPTR,
    T_CLASS, // 10
    T_INTEGER,
    T_CHAR,
    T_LABEL,
} lat_tipo;

typedef void (*lat_CFuncion)(lat_mv *mv);

/**\brief Estructura que almacena las instrucciones bytecode de la MV */
typedef struct lat_bytecode {
    lat_byte ins;   /**< Instruccion */
    unsigned int a; /**< registro a */
    unsigned int b; /**< registro b */
    unsigned int nlin;
    unsigned int ncol;
    char *nombre_archivo;
    void *meta;
} lat_bytecode;

typedef union lat_gcobjeto lat_gcobjeto;

#define lat_commonheader                                                       \
    lat_gcobjeto *next;                                                        \
    lat_byte tipo;                                                             \
    lat_byte marked

typedef struct lat_gcheader {
    lat_commonheader;
} lat_gcheader;

#define LAT_USER_ALIGNMENT                                                     \
    union {                                                                    \
        double u;                                                              \
        void *s;                                                               \
        long l;                                                                \
    }

typedef LAT_USER_ALIGNMENT L_Umaxalign;

typedef union lat_cadena {
    L_Umaxalign dummy;
    struct {
        lat_commonheader;
        lat_byte reserved;
        unsigned int hash;
        size_t len;
    } tsv;
} lat_cadena;

typedef union {
    lat_gcobjeto *gc;
    void *cpointer;
    double numerico;
    bool logico;
    int entero;
    char caracter;
} lat_valor;

/** \brief Objeto
 *
 * Almacena toda la informacion del objeto
 */
typedef struct _lat_objeto {
    lat_valor val;
    lat_tipo tipo;
    int nref;
    bool esconst;
    int marca;
    const char *nombre;
    int nparams;
    int ninst;
    size_t tam;
    bool es_vararg;
    int jump_label;
} lat_objeto;

/**\brief Define una fun de usuario */
typedef struct lat_funcion {
    int nparams;
    int ninst;
    char *nombre;
    lat_bytecode *codigo;
} lat_funcion;

#ifdef WIN32
__declspec(dllexport) lat_objeto latO_nulo_;
__declspec(dllexport) lat_objeto latO_verdadero_;
__declspec(dllexport) lat_objeto latO_falso_;
#else
extern lat_objeto latO_nulo_;
extern lat_objeto latO_verdadero_;
extern lat_objeto latO_falso_;
#endif

/* macros para asignar valores */
#define setNulo(obj, v)                                                        \
    { (obj)->tipo = T_NULL; }
#define setLogico(obj, v)                                                      \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.logico = (v);                                                 \
        i_o->tipo = T_BOOL;                                                    \
    }
#define setNumerico(obj, v)                                                    \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.numerico = (v);                                               \
        i_o->tipo = T_NUMERIC;                                                 \
    }
#define setEntero(obj, v)                                                      \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.numerico = (v);                                               \
        i_o->tipo = T_INTEGER;                                                 \
    }
#define setCaracter(obj, v)                                                    \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.caracter = (v);                                               \
        i_o->tipo = T_CHAR;                                                    \
    }
#define setCadena(obj, v)                                                      \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_STR;                                                     \
    }
#define setLista(obj, v)                                                       \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_LIST;                                                    \
    }
#define setDic(obj, v)                                                         \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_DIC;                                                     \
    }
#define setCtx(obj, v)                                                         \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_CONTEXT;                                                 \
    }

#define setFun(obj, v)                                                         \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_FUN;                                                     \
    }
#define setCfun(obj, v)                                                        \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_CFUN;                                                    \
    }
#define setPtr(obj, v)                                                         \
    {                                                                          \
        lat_objeto *i_o = (obj);                                               \
        i_o->val.gc = (lat_gcobjeto *)(v);                                     \
        i_o->tipo = T_CPTR;                                                    \
    }

#define setobj(obj1, obj2)                                                     \
    {                                                                          \
        const lat_objeto *o2 = (obj2);                                         \
        lat_objeto *o1 = (obj1);                                               \
        o1->val = o2->val;                                                     \
        o1->tipo = o2->tipo;                                                   \
        o1->nombre = o2->nombre;                                               \
        o1->nparams = o2->nparams;                                             \
        o1->es_vararg = o2->es_vararg;                                         \
        o1->esconst = o2->esconst;                                             \
        o1->jump_label = o2->jump_label;                                       \
    }

#define setobj2s setobj

#define setobj2obj(obj1, obj2)                                                 \
    {                                                                          \
        const lat_objeto *oo2 = (obj2);                                        \
        lat_objeto *oo1 = (obj1);                                              \
        switch (getTipo(oo2)) {                                                \
            case T_NULL:                                                       \
                setNulo(oo1, NULL);                                            \
                break;                                                         \
            case T_BOOL:                                                       \
                setLogico(oo1, getLogico(oo2));                                \
                break;                                                         \
            case T_NUMERIC:                                                    \
                setNumerico(oo1, getNumerico(oo2));                            \
                break;                                                         \
            case T_INTEGER:                                                    \
                setEntero(oo1, getEntero(oo2));                                \
                break;                                                         \
            case T_CHAR:                                                       \
                setCaracter(oo1, getCaracter(oo2));                            \
                break;                                                         \
            case T_STR:                                                        \
            case T_LABEL:                                                      \
            case T_LIST:                                                       \
            case T_DIC:                                                        \
            case T_CONTEXT:                                                    \
            case T_FUN:                                                        \
            case T_CFUN:                                                       \
            case T_CPTR:                                                       \
                setobj(oo1, oo2);                                              \
                break;                                                         \
            default:                                                           \
                break;                                                         \
        }                                                                      \
    }

#define isNulo(o) (getTipo(o) == T_NULL)
#define isLogico(o) (getTipo(o) == T_BOOL)
#define isNumerico(o) (getTipo(o) == T_NUMERIC)
#define isEntero(o) (getTipo(o) == T_INTEGER)
#define isCaracter(o) (getTipo(o) == T_CHAR)
#define isCadena(o) (getTipo(o) == T_STR)
#define isLista(o) (getTipo(o) == T_LIST)
#define isDic(o) (getTipo(o) == T_DIC)
#define isFun(o) (getTipo(o) == T_FUN)
#define isCfun(o) (getTipo(o) == T_CFUN)

/* macros para obtener valores */
#define getTipo(o) ((o)->tipo)
#define getLogico(o) ((o)->val.logico)
#define getNumerico(o) ((o)->val.numerico)
#define getEntero(o) ((o)->val.numerico)
#define getCaracter(o) ((o)->val.caracter)
#define getCadena(o) ((lat_cadena *)(o)->val.gc)
#define getLista(o) ((lista *)(o)->val.gc)
#define getDic(o) ((hash_map *)(o)->val.gc)
#define getCtx(o) ((hash_map *)(o)->val.gc)
#define getFun(o) ((lat_funcion *)(o)->val.gc)
#define getCfun(o) ((lat_CFuncion)(o)->val.gc)
#define getPtr(o) ((void *)(o)->val.gc)

#define lmod(s, size) ((int)s & ((size)-1))
#define getstr(ts) ((char *)((ts) + 1))

lat_objeto *latO_crear(lat_mv *mv);
void latO_asignar_ctx(lat_mv *mv, lat_objeto *ns, const char *name,
                      lat_objeto *o);
lat_objeto *latO_obtener_contexto(lat_mv *mv, lat_objeto *ns, const char *name);
lat_objeto *latO_contexto_crear(lat_mv *mv);

void latO_destruir(lat_mv *mv, lat_objeto *o);
lat_objeto *latO_clonar(lat_mv *mv, lat_objeto *o);
int latO_comparar(lat_mv *mv, lat_objeto *lhs, lat_objeto *rhs);
void latO_imprimir(lat_mv *mv, lat_objeto *in, bool fmt);

lat_objeto *latO_crear_funcion(lat_mv *mv);
lat_objeto *latO_crear_cfuncion(lat_mv *mv);

void latL_modificar_elemento(lat_mv *mv, lista *list, void *data, int pos);
int latL_comparar(lat_mv *mv, lista *lhs, lista *rhs);
int latL_obtener_indice(lat_mv *mv, lista *list, void *data);

void latS_resize(lat_mv *mv, int newsize);

#endif // _LATINO_OBJ_H_
