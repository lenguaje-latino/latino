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

#ifndef _LATINO_MV_H_
#define _LATINO_MV_H_

#include <math.h>

#include "latdic.h"
#include "latlist.h"
#include "latobj.h"

#include "latino.h"

typedef struct lat_bytecode lat_bytecode;
typedef struct lat_funcion lat_funcion;
typedef struct lat_CReg lat_CReg;
typedef void (*lat_CFuncion)(lat_mv *mv);

/**\brief Muestra las instrucciones que se van ejecutando con la Maquina Virtual
 */
#define DEPURAR_MV 0

/**\brief op_codes de la maquina virtual */
#define NOP 0
#define HALT 1
#define UNARY_MINUS 2
#define BINARY_ADD 3
#define BINARY_SUB 4
#define BINARY_MUL 5
#define BINARY_DIV 6
#define BINARY_MOD 7
#define OP_GT 8
#define OP_GE 9
#define OP_LT 10
#define OP_LE 11
#define OP_EQ 12
#define OP_NEQ 13
#define OP_AND 14
#define OP_OR 15
#define OP_NOT 16
#define OP_INC 17
#define OP_DEC 18
#define CONCAT 19
#define LOAD_CONST 20
#define LOAD_NAME 21
#define STORE_NAME 22
#define JUMP_ABSOLUTE 23
#define POP_JUMP_IF_FALSE 24
#define POP_JUMP_IF_TRUE 25 // Unused
#define PUSH_CTX 26
#define POP_CTX 27
#define CALL_FUNCTION 28
#define RETURN_VALUE 29
#define MAKE_FUNCTION 30
#define LOAD_ATTR 31
#define BUILD_LIST 32
#define STORE_SUBSCR 33
#define BINARY_SUBSCR 34
#define BUILD_MAP 35
#define STORE_MAP 36
#define STORE_ATTR 37
#define SET_GLOBAL 38
#define OP_REGEX 39
#define BINARY_POW 40
#define OP_VAR_ARGS 41
#define OP_PUSH 42 // Unused
#define OP_POP 43  // Unused
#define ADJUST_STACK 44
#define LOAD_VAR_ARGS 45
#define SET_LOCAL 46
#define POP_JUMP_IF_NEGATIVE 47
#define JUMP_LABEL 48
#define STORE_LABEL 49

union lat_gcobjeto {
    lat_gcheader gch;
    union lat_cadena cadena;
    struct lista lista;
    struct hash_map dic;
    struct lat_funcion fun;
    lat_CFuncion *cfun;
    void *ptr;
};

typedef struct lat_proto {
    int nparams;
    int ninst;
    char *nombre;
    lat_bytecode *codigo;
    lista *locals;
} lat_proto;

typedef struct stringtable {
    lat_gcobjeto **hash;
    unsigned int nuse;
    int size;
} stringtable;

typedef struct lat_global {
    int argc;
    lat_objeto *argv;
    lat_objeto *gc_objetos;
    stringtable strt;
    bool menu;
    bool REPL;
} lat_global;

/**\brief Define la maquina virtual (MV) */
typedef struct lat_mv {
    lat_global *global;
    lat_objeto *pila;
    lat_objeto *tope;
    lat_objeto *base;
    lat_objeto *actfun;
    lat_objeto *contexto[256];
    lat_objeto *contexto_actual;
    int ptrctx;
    int ptrpila;
    int ptrprevio;
    int prev_args;
    int numejec;
    size_t memoria_usada;
    size_t gc_limite;
    char *nombre_archivo;
    int nlin;
    int ncol;
    int status;
    struct lat_longjmp *error;
    int enBucle;
    int goto_break[256];    // FIXME: Validar memoria utilizada
    int goto_continue[256]; // FIXME: Validar memoria utilizada
    int goto_goto[256];
} lat_mv;

#define lati_numUmin(a) (-(a))
#define lati_numAdd(a, b) ((a) + (b))
#define lati_numSub(a, b) ((a) - (b))
#define lati_numMul(a, b) ((a) * (b))
#define lati_numDiv(a, b) ((a) / (b))
#define lati_numMod(a, b) (fmod((a), (b)))
#define lati_numPow(a, b) (pow((a), (b)))
#define lati_numNq(a, b) ((a) == (b))
#define lati_numLt(a, b) ((a) < (b))
#define lati_numLe(a, b) ((a) <= (b))

#define arith_op(op)                                                           \
    {                                                                          \
        lat_objeto *b = latC_desapilar(mv);                                    \
        lat_objeto *a = latC_desapilar(mv);                                    \
        setNumerico(mv->tope, op(latC_adouble(mv, a), latC_adouble(mv, b)));   \
        inc_pila(mv);                                                          \
    }

const char *latMV_bytecode_nombre(int inst);

void lat_es_decimal(lat_mv *mv);
void lat_formato_numero(lat_mv *mv);
lat_bytecode latMV_bytecode_crear(int i, int a, int b, void *meta,
                                  long int nlin, long int ncol,
                                  char *nombre_archivo);
int latMV_funcion_correr(lat_mv *mv, lat_objeto *func);

#endif // _LATINO_MV_H_
