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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LATINO_CORE

#include "latcompat.h"
#include "latdo.h"
#include "latgc.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"
#include "latobj.h"
#include "latparse.h"

static const char *const bycode_nombre[] = {
    "NOP", /* 0 */
    "HALT",
    "UNARY_MINUS",
    "BINARY_ADD",
    "BINARY_SUB",
    "BINARY_MUL", /* 5 */
    "BINARY_DIV",
    "BINARY_MOD",
    "OP_GT",
    "OP_GE",
    "OP_LT", /*10*/
    "OP_LE",
    "OP_EQ",
    "OP_NEQ",
    "OP_AND",
    "OP_OR", /*15*/
    "OP_NOT",
    "OP_INC",
    "OP_DEC",
    "CONCAT",
    "LOAD_CONST", /*20*/
    "LOAD_NAME",
    "STORE_NAME",
    "JUMP_ABSOLUTE",
    "POP_JUMP_IF_FALSE",
    "POP_JUMP_IF_TRUE", /*25*/
    "PUSH_CTX",
    "POP_CTX",
    "CALL_FUNCTION",
    "RETURN_VALUE",
    "MAKE_FUNCTION", /*30*/
    "LOAD_ATTR",
    "BUILD_LIST",
    "STORE_SUBSCR",
    "BINARY_SUBSCR",
    "BUILD_MAP", /*35*/
    "STORE_MAP",
    "STORE_ATTR",
    "SET_GLOBAL",
    "OP_REGEX",
    "BINARY_POW", /*40*/
    "OP_VAR_ARGS",
    "OP_PUSH",
    "OP_POP",
    "ADJUST_STACK",
    "LOAD_VAR_ARGS", /*45*/
    "SET_LOCAL",
    "POP_JUMP_IF_NEGATIVE",
    "JUMP_LABEL",
    "STORE_LABEL"
};

void str_concatenar(lat_mv *mv);

void latC_abrir_liblatino_baselib   (lat_mv *mv);
void latC_abrir_liblatino_listlib   (lat_mv *mv);
void latC_abrir_liblatino_strlib    (lat_mv *mv);
void latC_abrir_liblatino_diclib    (lat_mv *mv);
void latC_abrir_liblatino_paqlib    (lat_mv *mv);
void latC_abrir_liblatino_filelib   (lat_mv *mv);
void latC_abrir_liblatino_mathlib   (lat_mv *mv);
void latC_abrir_liblatino_syslib    (lat_mv *mv);
void latC_abrir_liblatino_devlib    (lat_mv *mv);

/*
void latC_abrir_liblatino_uilib     (lat_mv *mv);
void latC_abrir_liblatino_gc(lat_mv *mv);
void latC_abrir_liblatino_gtklib(lat_mv *mv);
 */

const char *latMV_bytecode_nombre(int inst) { return bycode_nombre[inst]; }

static void igualdad(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    char *buffer = NULL;
    char *buffer2 = NULL;
    switch (a->tipo) {
        case T_BOOL: {
            r = latC_checar_logico(mv, a) == latC_abool(mv, b) ? latO_verdadero
                                                               : latO_falso;
            latC_apilar(mv, r);
            return;
        } break;
        case T_NUMERIC: {
            r = (latC_checar_numerico(mv, a) == latC_adouble(mv, b))
                    ? latO_verdadero
                    : latO_falso;
            latC_apilar(mv, r);
            return;
        } break;
        case T_STR: {
            buffer = latC_astring(mv, b);
            r = strcmp(latC_checar_cadena(mv, a), buffer) == 0 ? latO_verdadero
                                                               : latO_falso;
            latC_apilar(mv, r);
            latM_liberar(mv, buffer);
            return;
        } break;
        default: {
            buffer = latC_astring(mv, a);
            buffer2 = latC_astring(mv, b);
            r = !strcmp(buffer, buffer2) ? latO_verdadero : latO_falso;
            latC_apilar(mv, r);
            latM_liberar(mv, buffer);
            latM_liberar(mv, buffer2);
            return;
        }
    }
}

void str_regex(lat_mv *mv);

static void diferente(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    char *buffer = NULL;
    char *buffer2 = NULL;
    switch (a->tipo) {
        case T_BOOL: {
            r = latC_checar_logico(mv, a) != latC_abool(mv, b) ? latO_verdadero
                                                               : latO_falso;
            latC_apilar(mv, r);
            return;
        } break;
        case T_NUMERIC: {
            r = (latC_checar_numerico(mv, a) != latC_adouble(mv, b))
                    ? latO_verdadero
                    : latO_falso;
            latC_apilar(mv, r);
            return;
        } break;
        case T_STR: {
            buffer = latC_astring(mv, b);
            r = strcmp(latC_checar_cadena(mv, a), buffer) ? latO_verdadero
                                                          : latO_falso;
            latC_apilar(mv, r);
            latM_liberar(mv, buffer);
            return;
        } break;
        default: {
            buffer = latC_astring(mv, a);
            buffer2 = latC_astring(mv, b);
            r = strcmp(buffer, buffer2) ? latO_verdadero : latO_falso;
            latC_apilar(mv, r);
            latM_liberar(mv, buffer);
            latM_liberar(mv, buffer2);
            return;
        }
    }
}

static void menor_que(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
        r = (latC_adouble(mv, a) < latC_adouble(mv, b)) ? latO_verdadero
                                                        : latO_falso;
        latC_apilar(mv, r);
        return;
    }
    r = latO_comparar(mv, a, b) < 0 ? latO_verdadero : latO_falso;
    latC_apilar(mv, r);
    return;
}

static void menor_igual(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
        r = (getNumerico(a) <= getNumerico(b)) ? latO_verdadero : latO_falso;
        latC_apilar(mv, r);
        return;
    }
    r = latO_comparar(mv, a, b) <= 0 ? latO_verdadero : latO_falso;
    latC_apilar(mv, r);
    return;
}

static void mayor_que(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
        r = (latC_adouble(mv, a) > latC_adouble(mv, b)) ? latO_verdadero
                                                        : latO_falso;
        latC_apilar(mv, r);
        return;
    }
    r = latO_comparar(mv, a, b) > 0 ? latO_verdadero : latO_falso;
    latC_apilar(mv, r);
    return;
}

static void mayor_igual(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    if (a->tipo == T_NUMERIC || b->tipo == T_NUMERIC) {
        r = (latC_adouble(mv, a) >= latC_adouble(mv, b)) ? latO_verdadero
                                                         : latO_falso;
        latC_apilar(mv, r);
        return;
    }
    r = latO_comparar(mv, a, b) >= 0 ? latO_verdadero : latO_falso;
    latC_apilar(mv, r);
    return;
}

static void y_logico(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    if (latC_abool(mv, a)) {
        r = b;
    } else {
        r = a;
    }
    latC_apilar(mv, latO_clonar(mv, r));
}

static void o_logico(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *r = NULL;
    if (latC_abool(mv, a)) {
        r = a;
    } else {
        r = b;
    }
    latC_apilar(mv, latO_clonar(mv, r));
}

static void no_logico(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    lat_objeto *r = (latC_abool(mv, o) == false) ? latO_verdadero : latO_falso;
    latC_apilar(mv, r);
}

static lat_objeto *obtener_contexto(lat_mv *mv) { return mv->contexto_actual; }

static lat_objeto *obtener_contexto_global(lat_mv *mv) {
    return mv->contexto[0];
}

static void apilar_contexto(lat_mv *mv, lat_objeto *ctx) {
    if (mv->ptrctx >= MAX_STACK_CONTEXT_SIZE) {
        printf(LAT_ERROR_FMT, mv->nombre_archivo, mv->nlin, mv->ncol,
               "Desborde de la pila de contextos");
        exit(EXIT_FAILURE);
    }
    mv->contexto[mv->ptrctx + 1] = latO_clonar(mv, mv->contexto[mv->ptrctx]);
    mv->ptrctx++;
    mv->contexto_actual = mv->contexto[mv->ptrctx];
}

static void desapilar_contexto(lat_mv *mv) {
    if (mv->ptrctx == 0) {
        printf(LAT_ERROR_FMT, mv->nombre_archivo, mv->nlin, mv->ncol,
               "Pila de contextos vacia");
        exit(EXIT_FAILURE);
    }
    latO_destruir(mv, mv->contexto[mv->ptrctx--]);
    mv->contexto_actual = mv->contexto[mv->ptrctx];
}

LATINO_API void latC_abrir_liblatino(lat_mv *mv, const char *nombre_lib,
                                     const lat_CReg *funs) {
    lat_objeto *ctx = obtener_contexto_global(mv);
    if (!strcmp(nombre_lib, "")) {
        // Alcance global o libreria base
        for (; funs->nombre; funs++) {
            lat_objeto *cfun = latC_crear_cfuncion(mv, funs->cfun);
            cfun->nombre = funs->nombre;
            cfun->nparams = funs->nparams;
            latO_asignar_ctx(mv, ctx, funs->nombre, cfun);
        }
    } else {
        lat_objeto *mod = latO_obtener_contexto(mv, ctx, nombre_lib);
        if (mod == NULL) {
            mod = latC_crear_dic(mv, latH_crear(mv));
            mod->marca = 0;
        }
        for (; funs->nombre; funs++) {
            lat_objeto *cfun = latC_crear_cfuncion(mv, funs->cfun);
            cfun->nombre = funs->nombre;
            cfun->nparams = funs->nparams;
            latH_asignar(mv, latC_checar_dic(mv, mod), funs->nombre, cfun);
        }
        latO_asignar_ctx(mv, ctx, nombre_lib, mod);
    }
}

LATINO_API lat_mv *latC_crear_mv() {
    lat_mv *mv = (lat_mv *)malloc(sizeof(lat_mv));
    mv->memoria_usada = 0;
#if DEPURAR_MEM
    printf("------------------------------------------------------------\n");
    printf("inicio latC_crear_mv.mv->memoria_usada: %zu\n", mv->memoria_usada);
    printf("------------------------------------------------------------\n");
#endif
    mv->global = (lat_global *)latM_asignar(mv, sizeof(lat_global));
#if DEPURAR_MEM
    printf("latC_crear_mv.mv->global: %p\n", mv->global);
#endif
#if HABILITAR_GC
    mv->global->gc_objetos = latC_crear_lista(mv, latL_crear(mv));
    mv->global->gc_objetos->marca = 0;
#endif
    mv->global->argv = latC_crear_lista(mv, latL_crear(mv));
    mv->global->argv->marca = 0;
    mv->global->strt.size = 0;
    mv->global->strt.nuse = 0;
    mv->global->strt.hash = NULL;
    latS_resize(mv, MIN_STRTABLE_SIZE);
    mv->pila = calloc(MAX_STACK_SIZE, sizeof(lat_objeto));
    mv->ptrpila = 0;
    mv->tope = mv->pila;
    mv->ptrprevio = 1;
    mv->prev_args = 0;
    mv->numejec = 0;
    memset(mv->contexto, 0, 256);
    mv->contexto[0] = latO_contexto_crear(mv);
    mv->contexto[0]->marca = 0;
    mv->ptrctx = 0;
    mv->contexto_actual = mv->contexto[mv->ptrctx];
    mv->error = NULL;
    mv->global->menu = false;
    mv->enBucle = 0;
    mv->goto_break;

    // cargar librerias de latino
    latC_abrir_liblatino_baselib(mv);
    latC_abrir_liblatino_strlib(mv);
    latC_abrir_liblatino_listlib(mv);
    latC_abrir_liblatino_diclib(mv);
    latC_abrir_liblatino_paqlib(mv);
    latC_abrir_liblatino_filelib(mv);
    latC_abrir_liblatino_mathlib(mv);
    latC_abrir_liblatino_syslib(mv);
    latC_abrir_liblatino_devlib(mv);

#if DEPURAR_MEM
    printf("------------------------------------------------------------\n");
    printf("fin latC_crear_mv.mv->memoria_usada: %zu\n", mv->memoria_usada);
    printf("------------------------------------------------------------\n");
#endif
    return mv;
}

LATINO_API void latC_destruir_mv(lat_mv *mv) {
#if DEPURAR_MEM
    printf("------------------------------------------------------------\n");
    printf("inicio latC_destruir_mv.mv->memoria_usada: %zu\n",
           mv->memoria_usada);
    printf("------------------------------------------------------------\n");
#endif
    latO_destruir(mv, mv->global->argv);
#if HABILITAR_GC
    latO_destruir(mv, mv->global->gc_objetos);
#endif
    latO_destruir(mv, mv->contexto[0]);
    latM_liberar(mv, mv->global->strt.hash);
    latM_liberar(mv, mv->global);
#if DEPURAR_MEM
    printf("------------------------------------------------------------\n");
    printf("fin latC_destruir_mv.mv->memoria_usada: %zu\n", mv->memoria_usada);
    printf("------------------------------------------------------------\n");
#endif
    free(mv->pila);
    free(mv);
}

void imprimir_pila(lat_mv *mv) {
    if (mv->ptrpila >= 0) {
        int n = (mv->ptrpila);
        printf("\tPILA(%i) = [", n);
        for (int i = 0; i < n; i++) {
            lat_objeto o = mv->pila[i];
            latO_imprimir(mv, &o, false);
            printf(", ");
        }
        printf("]");
    }
    printf("\n");
}

void checar_pila(lat_mv *mv) {
    if (mv->ptrpila >= MAX_STACK_SIZE) {
        printf(LAT_ERROR_FMT, mv->nombre_archivo, mv->nlin, mv->ncol,
               "Desborde de la pila");
        exit(EXIT_FAILURE);
    }
    if (mv->ptrpila <= 0) {
        printf(LAT_ERROR_FMT, mv->nombre_archivo, mv->nlin, mv->ncol,
               "Pila vacia");
        exit(EXIT_FAILURE);
    }
}

void inc_pila(lat_mv *mv) {
    mv->tope++;
    mv->ptrpila++;
}

void dec_pila(lat_mv *mv) {
    mv->tope--;
    mv->ptrpila--;
}

LATINO_API void latC_apilar(lat_mv *mv, lat_objeto *o) {
    switch (o->tipo) {
        case T_NULL:
            setNulo(mv->tope, o);
            break;
        case T_BOOL:
            setLogico(mv->tope, getLogico(o));
            break;
        case T_NUMERIC:
            setNumerico(mv->tope, getNumerico(o));
            break;
        case T_STR:
            setCadena(mv->tope, getCadena(o));
            break;
        case T_LIST:
            setLista(mv->tope, getLista(o));
            break;
        case T_DIC:
            setDic(mv->tope, getDic(o));
            break;
        case T_FUN:
            setobj(mv->tope, o);
            break;
        case T_CFUN:
            setobj(mv->tope, o);
            break;
        case T_CPTR:
            setobj(mv->tope, o);
            break;
        default:;
    }
    inc_pila(mv);
    checar_pila(mv);
}

LATINO_API lat_objeto *latC_desapilar(lat_mv *mv) {
    checar_pila(mv);
    dec_pila(mv);
    return mv->tope;
}

LATINO_API lat_objeto *latC_tope(lat_mv *mv) {
    lat_objeto *p = (lat_objeto *)&mv->pila[mv->ptrpila - 1];
    return p;
}

LATINO_API void latC_apilar_double(lat_mv *mv, double num) {
    setNumerico(mv->tope, num);
    inc_pila(mv);
    checar_pila(mv);
}

LATINO_API void latC_apilar_int(lat_mv *mv, int i) {
    setEntero(mv->tope, i);
    inc_pila(mv);
    checar_pila(mv);
}

LATINO_API void latC_apilar_char(lat_mv *mv, char c) {
    setCaracter(mv->tope, c);
    inc_pila(mv);
    checar_pila(mv);
}

LATINO_API void latC_apilar_string(lat_mv *mv, const char *str) {
    setCadena(mv->tope, getCadena(latC_crear_cadena(mv, str)));
    inc_pila(mv);
    checar_pila(mv);
}

LATINO_API lat_objeto *latC_crear_funcion(lat_mv *mv, lat_bytecode *inslist,
                                          int ninst) {
    lat_objeto *ret = latO_crear_funcion(mv);
    lat_funcion *fval = (lat_funcion *)latM_asignar(mv, sizeof(lat_funcion));
#if DEPURAR_MEM
    printf("latC_crear_funcion.fval: %p\n", fval);
#endif
    fval->codigo = inslist;
    setFun(ret, fval);
    ret->ninst = ninst;
    return ret;
}

LATINO_API lat_objeto *latC_crear_cfuncion(lat_mv *mv, lat_CFuncion func) {
    lat_objeto *ret = latO_crear_cfuncion(mv);
    setCfun(ret, func);
    return ret;
}

lat_bytecode latMV_bytecode_crear(int i, int a, int b, void *meta,
                                  long int nlin, long int ncol,
                                  char *nombre_archivo) {
    lat_bytecode ret;
    ret.ins = i;
    ret.a = a;
    ret.b = b;
    ret.meta = meta;
    ret.nlin = nlin;
    ret.ncol = ncol;
    ret.nombre_archivo = nombre_archivo;
    return ret;
}

static lat_objeto *latMV_get_symbol(lat_mv *mv, lat_objeto *name) {
    lat_objeto *ctx = obtener_contexto(mv);
    lat_objeto *val = (lat_objeto *)latO_obtener_contexto(
        mv, ctx, latC_checar_cadena(mv, name));
    if (val == NULL) {
        ctx = obtener_contexto_global(mv);
        val = (lat_objeto *)latO_obtener_contexto(mv, ctx,
                                                  latC_checar_cadena(mv, name));
        if (val == NULL) {
            latC_error(mv, "Variable '%s' indefinida",
                       latC_checar_cadena(mv, name));
        }
        latC_error(mv, "Variable '%s' indefinida",
                   latC_checar_cadena(mv, name));
    }
    return val;
}

static void latMV_set_symbol(lat_mv *mv, lat_objeto *name, lat_objeto *val) {
    char * str_name = latC_checar_cadena(mv, name);
    // printf("latMV_set_symbol.str_name: %s\n", str_name);
    // printf("latMV_set_symbol.val:");
    // latO_imprimir(mv, val, false);
    // printf("\n");
    lat_objeto *ctx = obtener_contexto(mv);
    // objeto anterior
    lat_objeto *tmp =
        latO_obtener_contexto(mv, ctx, str_name);
    if (name->esconst) {
        if (tmp != NULL) {
            latC_error(mv, "Intento de reasignar valor a constante '%s'",
                       str_name);
        }
    }
    latO_asignar_ctx(mv, ctx, str_name, val);
}

static void latMV_call_function(lat_mv *mv, lat_objeto *func, lat_bytecode cur,
                                lat_bytecode next) {
    int num_args = cur.a;
    lat_objeto *fun = latM_asignar(mv, sizeof(lat_objeto));
#if DEPURAR_MEM
    printf("latMV_call_function.fun: %p\n", fun);
#endif
    setobj2obj(fun, latC_desapilar(mv));
    if (!(fun->tipo == T_CFUN || fun->tipo == T_FUN)) {
        latC_error(mv, "El objeto no es una funcion");
    }
    int nparams = fun->nparams;
    while (mv->ptrpila < nparams) {
        latC_apilar(mv, latO_nulo);
        num_args++;
    }
    if (nparams == FUNCION_VAR_ARGS) {
        // T_CFUN y varargs
        fun->es_vararg = true;
        lat_objeto *ctx = obtener_contexto(mv);
        lat_objeto *varargs =
            (lat_objeto *)latO_obtener_contexto(mv, ctx, "varargs");
        if (varargs) {
            lista *lst = latC_checar_lista(mv, varargs);
            if (latL_longitud(lst)) {
                num_args = (num_args - 1) + latL_longitud(lst);
            }
        }
        latC_apilar_double(mv, (double)num_args);
    } else if (num_args != nparams && !fun->es_vararg) {
        if (num_args < nparams) {
            while (num_args < nparams) {
                latC_apilar(mv, latO_nulo);
                num_args++;
            }
        } else {
            // T_FUN y no varargs
            latC_error(mv,
                       "Numero invalido de argumentos en "
                       "funcion '%s'",
                       fun->nombre);
        }
    } else {
        if (mv->prev_args > 1) {
            while (mv->ptrpila > (mv->ptrprevio + nparams)) {
                latC_desapilar(mv);
            }
        }
    }
    mv->numejec++;
    if (mv->numejec >= MAX_CALL_FUNCTION) {
        latC_error(mv, "Llamadas a funciones recursivas excedido en '%s'",
                   fun->nombre);
    }
    bool apilar = next.ins == STORE_NAME || !strcmp(fun->nombre, "incluir") ||
                  (fun->nombre != NULL && func->nombre != NULL &&
                   !strcmp(func->nombre, fun->nombre));
    if (apilar) {
        apilar_contexto(mv, NULL);
        mv->ptrprevio = (mv->ptrpila);
    } else {
        mv->ptrprevio = 1; // restore stack
    }
    mv->prev_args = latMV_funcion_correr(mv, fun);
    mv->numejec--;
    if (fun->tipo != T_CFUN && mv->prev_args == 0 && next.ins == ADJUST_STACK) {
        latC_error(mv,
                   "La funcion '%s' no "
                   "retorna ningun valor\n",
                   fun->nombre);
    }
    if (fun->tipo == T_FUN && fun->es_vararg) {
        lat_objeto *ctx = obtener_contexto(mv);
        latO_asignar_ctx(mv, ctx, "varargs",
                         latC_crear_lista(mv, latL_crear(mv)));
    }
    latM_liberar(mv, fun);
    if (apilar) {
        desapilar_contexto(mv);
#if HABILITAR_GC
        gc_checar(mv);
#endif
    }
}

static void latMV_build_list(lat_mv *mv, lat_bytecode cur) {
    int num_elem = 0;
    if (cur.b) {
        lat_objeto *ctx = obtener_contexto(mv);
        lat_objeto *varargs =
            (lat_objeto *)latO_obtener_contexto(mv, ctx, "varargs");
        if (!varargs) {
            latC_error(mv, "varargs (...) no existe en este contexto");
        }
        lista *lst = latC_checar_lista(mv, varargs);
        num_elem = (cur.a - cur.b) + (cur.b * latL_longitud(lst));
    } else {
        num_elem = cur.a;
    }
    if (mv->prev_args) {
        num_elem += mv->prev_args - 1;
    }
#if DEPURAR_MV
    printf("%i\t%i\t", cur.a, cur.b);
#endif
    int i;
    lat_objeto *obj = latC_crear_lista(mv, latL_crear(mv));
    for (i = 0; i < num_elem; i++) {
        lat_objeto *tmp = latO_clonar(mv, latC_desapilar(mv));
        latL_insertar_inicio(mv, latC_checar_lista(mv, obj), tmp);
    }
    latC_apilar(mv, obj);
}

static void latMV_load_attr(lat_mv *mv, lat_bytecode cur, lat_bytecode next) {
    lat_objeto *obj = latC_desapilar(mv);
    lat_objeto *attr = (lat_objeto *)cur.meta;
    lat_objeto *val = NULL;
#if DEPURAR_MV
    latO_imprimir(mv, attr, false);
    printf("\t");
#endif
    if (obj->tipo == T_DIC) {
        val = (lat_objeto *)latH_obtener(latC_checar_dic(mv, obj),
                                         latC_checar_cadena(mv, attr));
        if (val != NULL) {
            latC_apilar(mv, val);
            return;
        } else {
            if (next.ins == CALL_FUNCTION) {
                latC_error(mv, "No se encontro la fun '%s'",
                           latC_checar_cadena(mv, attr));
            } else {
                val = latC_crear_cadena(mv, "");
                latC_apilar(mv, val);
                return;
            }
        }
    }
    lat_objeto *top = latC_tope(mv);
    if (top && (next.ins == BINARY_SUBSCR)) {
        if (top->tipo == T_STR) {
            if (obj->tipo != T_DIC) {
                obj = latC_crear_dic(mv, latH_crear(mv));
                latH_asignar(mv, latC_checar_dic(mv, obj),
                             latC_checar_cadena(mv, attr), val);
                latC_apilar(mv, obj);
                return;
            }
        }
        if (top->tipo == T_NUMERIC) {
            if (obj->tipo != T_LIST) {
                obj = latC_crear_lista(mv, latL_crear(mv));
                latC_apilar(mv, obj);
                return;
            }
        }
    }
    val = latC_crear_cadena(mv, "");
    latC_apilar(mv, val);
}

static void latMV_store_subscr(lat_mv *mv) {
    lat_objeto *pos = latC_desapilar(mv);
    lat_objeto *obj = latC_desapilar(mv);
    lat_objeto *exp = latC_desapilar(mv);
    if (!latO_comparar(mv, obj, exp)) {
        latC_error(mv, "Referencia circular detectada");
    }
    if (obj->tipo == T_DIC) {
        latH_asignar(mv, latC_checar_dic(mv, obj), latC_astring(mv, pos), exp);
        return;
    }
    int ipos = latC_checar_numerico(mv, pos);
    if (obj->tipo == T_LIST) {
        lista *ll = latC_checar_lista(mv, obj);
        int len = latL_longitud(ll);
        if (ipos < 0) {
            ipos = ipos + len;
            getNumerico(pos) = ipos;
        }
        if (ipos == len) {
            latL_agregar(mv, ll, latO_clonar(mv, exp));
            return;
        }
        latL_modificar_elemento(mv, latC_checar_lista(mv, obj),
                                latO_clonar(mv, exp), ipos);
    }
    if (obj->tipo == T_STR) {
        char *sobj = latC_checar_cadena(mv, obj);
        if (ipos < 0 || ipos >= strlen(sobj)) {
            latC_error(mv, "Indice fuera de rango");
        }
        char *sexp = latC_checar_cadena(mv, exp);
        if (strlen(sexp) == 0) {
            sexp = " ";
        }
        sobj[ipos] = sexp[0];
        setCadena(obj, sobj);
    }
}

static void binary_subscr(lat_mv *mv) {
    lat_objeto *obj = latC_desapilar(mv);
    lat_objeto *pos = latC_desapilar(mv);
    lat_objeto *o = NULL;
    if (obj->tipo == T_DIC) {
        o = latH_obtener(latC_checar_dic(mv, obj), latC_checar_cadena(mv, pos));
        if (o == NULL) {
            o = latC_crear_cadena(mv, "");
        }
        latC_apilar(mv, o);
        return;
    }
    int ipos = 0;
    if (pos->tipo == T_NUMERIC) {
        ipos = latC_checar_numerico(mv, pos);
    } else {
        o = latC_crear_cadena(mv, "");
        latC_apilar(mv, o);
        return;
    }
    if (obj->tipo == T_LIST) {
        lista *ll = latC_checar_lista(mv, obj);
        int len = latL_longitud(ll);
        if (ipos < 0) {
            ipos = ipos + len;
            getNumerico(pos) = ipos;
        }
        if (ipos < 0 || ipos >= len) {
            o = latC_crear_cadena(mv, "");
            latC_apilar(mv, o);
            return;
        }
        o = latL_obtener_elemento(mv, latC_checar_lista(mv, obj),
                                  latC_checar_numerico(mv, pos));
    }
    if (obj->tipo == T_NUMERIC) {
        char *sobj = latC_astring(mv, obj);
        if (ipos < 0 || ipos >= strlen(sobj)) {
            o = latO_nulo;
            latC_apilar(mv, o);
            return;
        }
        char c[2] = {sobj[ipos], '\0'};
        o = latC_crear_cadena(mv, c);
    }
    if (obj->tipo == T_STR) {
        char *sobj = latC_checar_cadena(mv, obj);
        if (ipos < 0 || ipos >= strlen(sobj)) {
            o = latO_nulo;
            latC_apilar(mv, o);
            return;
        }
        char c[2] = {sobj[ipos], '\0'};
        o = latC_crear_cadena(mv, c);
    }
    latC_apilar(mv, o);
}

static void latMV_store_map(lat_mv *mv) {
    lat_objeto *key = latC_desapilar(mv);
    lat_objeto *val = latC_desapilar(mv);
    lat_objeto *dic = latC_tope(mv);
    while (dic && dic->tipo != T_DIC) {
        latC_desapilar(mv);
        dic = latC_tope(mv);
    }
    if (!latO_comparar(mv, dic, val)) {
        latC_error(mv, "Referencia circular detectada");
    }
    char *_k = NULL;
    if (key->tipo == T_NUMERIC) {
        _k = latC_astring(mv, key);
    } else {
        _k = latC_checar_cadena(mv, key);
    }
    latH_asignar(mv, latC_checar_dic(mv, dic), _k, val);
}

static void latMV_store_attr(lat_mv *mv, lat_bytecode cur) {
    lat_objeto *attr = (lat_objeto *)cur.meta;
    lat_objeto *obj = latC_desapilar(mv);
    lat_objeto *val = latC_desapilar(mv);
    if (obj->tipo == T_DIC) {
        if (!latO_comparar(mv, obj, val)) {
            latC_error(mv, "Referencia circular detectada");
        }
        latH_asignar(mv, latC_checar_dic(mv, obj), latC_checar_cadena(mv, attr),
                     val);
    }
}

static void latMV_op_var_args(lat_mv *mv, lat_bytecode cur) {
    int num_elem = cur.a;
    lat_objeto *obj = latC_crear_lista(mv, latL_crear(mv));
    while (num_elem < mv->ptrpila) {
        lat_objeto *tmp = latO_clonar(mv, latC_desapilar(mv));
        if (tmp != NULL && tmp->tipo != T_NULL) {
            latL_insertar_inicio(mv, latC_checar_lista(mv, obj), tmp);
        }
    }
    lat_objeto *ctx = obtener_contexto(mv);
    latO_asignar_ctx(mv, ctx, "varargs", obj);
}

static void latMV_load_var_args(lat_mv *mv) {
    lat_objeto *ctx = obtener_contexto(mv);
    lat_objeto *val = (lat_objeto *)latO_obtener_contexto(mv, ctx, "varargs");
    if (!val) {
        latC_error(mv, "varargs (...) no existe en este contexto");
    }
    lista *list = latC_checar_lista(mv, val);
    LIST_FOREACH(list, primero, siguiente, cur) {
        lat_objeto *tmp = (lat_objeto *)cur->valor;
        if (tmp != NULL && tmp->tipo != T_NULL) {
            latC_apilar(mv, tmp);
        }
    }
}

int latMV_funcion_correr(lat_mv *mv, lat_objeto *func) {
    if (func->tipo == T_FUN) {
#if DEPURAR_MV
        printf("\n.::Ejecutando fun::.\n");
#endif
        if (func->nombre == NULL) {
            func->nombre = "dummy";
            latO_asignar_ctx(mv, obtener_contexto(mv), "dummy", func);
        }
        lat_bytecode *inslist = getFun(func)->codigo;
        lat_bytecode cur;
        int pc;
        for (pc = 0, cur = inslist[pc]; cur.ins != HALT; cur = inslist[++pc]) {
            lat_bytecode next = inslist[pc + 1];
            mv->nlin = cur.nlin;
            mv->ncol = cur.ncol;
            mv->nombre_archivo = cur.nombre_archivo;
#if DEPURAR_MV
            printf("%i\t", mv->nlin);
            printf("%i\t", pc);
            printf("%s\t", latMV_bytecode_nombre(cur.ins));
#endif
            switch (cur.ins) {
                case HALT:
                    return 0;
                case NOP:
                    continue;
                case UNARY_MINUS: {
                    lat_objeto *obj = latC_tope(mv);
                    setNumerico(obj, -(latC_adouble(mv, obj)));
                } break;
                case OP_INC: {
                    lat_objeto *name = (lat_objeto *)cur.meta;
                    lat_objeto *ctx = obtener_contexto(mv);
                    lat_objeto *val = latO_obtener_contexto(
                        mv, ctx, latC_checar_cadena(mv, name));
                    if (val == NULL) {
                        val = latC_crear_numerico(mv, 0);
                    }
                    getNumerico(val)++;
                    latO_asignar_ctx(mv, ctx, latC_checar_cadena(mv, name),
                                     val);
                } break;
                case OP_DEC: {
                    lat_objeto *name = (lat_objeto *)cur.meta;
                    lat_objeto *ctx = obtener_contexto(mv);
                    lat_objeto *val = latO_obtener_contexto(
                        mv, ctx, latC_checar_cadena(mv, name));
                    if (val == NULL) {
                        val = latC_crear_numerico(mv, 0);
                    }
                    getNumerico(val)--;
                    latO_asignar_ctx(mv, ctx, latC_checar_cadena(mv, name),
                                     val);
                } break;
                case BINARY_ADD: {
                    arith_op(lati_numAdd);
                } break;
                case BINARY_SUB: {
                    arith_op(lati_numSub);
                } break;
                case BINARY_POW: {
                    arith_op(lati_numPow);
                } break;
                case BINARY_MUL: {
                    arith_op(lati_numMul);
                } break;
                case BINARY_DIV: {
                    arith_op(lati_numDiv);
                } break;
                case BINARY_MOD: {
                    arith_op(lati_numMod);
                } break;
                case OP_GT: {
                    mayor_que(mv);
                } break;
                case OP_GE: {
                    mayor_igual(mv);
                } break;
                case OP_LT: {
                    menor_que(mv);
                } break;
                case OP_LE: {
                    menor_igual(mv);
                } break;
                case OP_EQ: {
                    igualdad(mv);
                } break;
                case OP_REGEX: {
                    str_regex(mv);
                } break;
                case OP_NEQ: {
                    diferente(mv);
                } break;
                case OP_AND: {
                    y_logico(mv);
                } break;
                case OP_OR: {
                    o_logico(mv);
                } break;
                case OP_NOT: {
                    no_logico(mv);
                } break;
                case CONCAT: {
                    str_concatenar(mv);
                } break;
                case LOAD_CONST: {
                    lat_objeto *o = (lat_objeto *)cur.meta;
#if DEPURAR_MV
                    latO_imprimir(mv, o, false);
                    printf("\t");
#endif
                    latC_apilar(mv, o);
                } break;
                case STORE_NAME: {
                    lat_objeto *val = NULL;
                    if (mv->ptrpila == 0) {
                        val = latO_nulo;
                    } else {
                        val = latC_desapilar(mv);
                    }
                    lat_objeto *name = (lat_objeto *)cur.meta;
                    latMV_set_symbol(mv, name, val);
#if DEPURAR_MV
                    latO_imprimir(mv, name, false);
                    printf("\t");
#endif
                } break;
                case STORE_LABEL: {
                    lat_objeto *name = (lat_objeto *)cur.meta;
                    lat_objeto *val = latO_clonar(mv, name);
                    latMV_set_symbol(mv, name, val);
#if DEPURAR_MV
                    latO_imprimir(mv, name, false);
                    printf("\t");
#endif
                } break;
                case SET_GLOBAL: {
                    mv->contexto_actual = obtener_contexto_global(mv);
                } break;
                case SET_LOCAL: {
                    mv->contexto_actual = mv->contexto[mv->ptrctx];
                } break;
                case LOAD_NAME: {
                    lat_objeto *name = (lat_objeto *)cur.meta;
#if DEPURAR_MV
                    latO_imprimir(mv, name, false);
                    printf("\t");
#endif
                    lat_objeto *val = latMV_get_symbol(mv, name);
                    latC_apilar(mv, val);
                } break;
                case POP_JUMP_IF_FALSE: {
#if DEPURAR_MV
                    printf("%i\t", cur.a + 1);
#endif
                    lat_objeto *o = latC_desapilar(mv);
                    if (latC_abool(mv, o) == false) {
                        pc = cur.a;
                    }
                } break;
                case POP_JUMP_IF_TRUE: {
                    // TODO: Unused bytecode
                    lat_objeto *o = latC_desapilar(mv);
                    if (latC_abool(mv, o) == true) {
                        pc = cur.a;
                    }
                } break;
                case JUMP_ABSOLUTE:
#if DEPURAR_MV
                    printf("%i\t", cur.a + 1);
#endif
                    pc = cur.a;
                    break;
                case JUMP_LABEL: {
                    lat_objeto *name = (lat_objeto *)cur.meta;
#if DEPURAR_MV
                    latO_imprimir(mv, name, false);
                    printf("\t");
#endif
                    lat_objeto *val = latMV_get_symbol(mv, name);
                    if(val->tipo != T_LABEL) {
                        char *nombre = latC_checar_cadena(mv, name);
                        latC_error(mv, "El identificador '%s' no es un tipo etiqueta", nombre);
                    }
                    pc = val->jump_label;  // saltamos hacia la instruccion de la etiqueta
                } break;
                case CALL_FUNCTION: {
#if DEPURAR_MV
                    printf("\n[RESULTADO] >>> ");
#endif
                    latMV_call_function(mv, func, cur, next);
                } break;
                case RETURN_VALUE: {
#if DEPURAR_MV
                    printf("%i\n", cur.a);
#endif
                    return cur.a;
                } break;
                case MAKE_FUNCTION: {
                    lat_objeto *fun = (lat_objeto *)cur.meta;
                    latC_apilar(mv, fun);
                } break;
                case PUSH_CTX:
                    apilar_contexto(mv, NULL);
                    break;
                case POP_CTX:
                    desapilar_contexto(mv);
                    break;
                case BUILD_LIST: {
                    latMV_build_list(mv, cur);
                } break;
                case LOAD_ATTR: {
                    latMV_load_attr(mv, cur, next);
                } break;
                case STORE_SUBSCR: {
                    latMV_store_subscr(mv);
                } break;
                case BINARY_SUBSCR: {
                    binary_subscr(mv);
                } break;
                case BUILD_MAP: {
                    lat_objeto *o = latC_crear_dic(mv, latH_crear(mv));
                    latC_apilar(mv, o);
                } break;
                case STORE_MAP: {
                    latMV_store_map(mv);
                } break;
                case STORE_ATTR: {
                    latMV_store_attr(mv, cur);
                } break;
                case OP_VAR_ARGS: {
                    latMV_op_var_args(mv, cur);
                } break;
                case LOAD_VAR_ARGS: {
                    latMV_load_var_args(mv);
                } break;
                case OP_PUSH: {
                    lat_objeto *obj = (lat_objeto *)cur.meta;
                    if (obj != NULL) {
                        latC_apilar(mv, obj);
                    } else {
                        latC_apilar(mv, latO_nulo);
                    }
                } break;
                case OP_POP: {
                    latC_desapilar(mv);
                } break;
                case ADJUST_STACK: {
#if DEPURAR_MV
                    printf("%i\t", cur.a);
#endif
                    while (cur.a > mv->ptrpila) {
                        latC_apilar(mv, latO_nulo);
                    }
                    while (mv->ptrpila >= (mv->ptrprevio + cur.a)) {
                        latC_desapilar(mv);
                    }
                } break;
                default:
                    continue;
            } // fin de switch

#if DEPURAR_MV
            imprimir_pila(mv);
#endif
        } // fin for
#if HABILITAR_GC
        gc_recolectar(mv);
#endif
    }     // fin if (T_FUN)
    else if (func->tipo == T_CFUN) {
        lat_CFuncion f = getCfun(func);
        (f)(mv);
        return 0;
    } else {
        latC_error(mv, "El objeto no es una funcion");
    }
    return 0;
}
