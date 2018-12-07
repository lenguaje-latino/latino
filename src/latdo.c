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

#define LATINO_CORE

#include "latdo.h"
#include "latast.h"
#include "latino.h"
#include "latmem.h"
#include "latmv.h"
#include "latobj.h"

#define dbc(I, A, B, M, L, C, F)                                               \
    codigo[i++] = latMV_bytecode_crear(I, A, B, M, L, C, F)
#define pn(vm, N) i = ast_analizar(vm, N, codigo, i)
#define fdbc(I, A, B, M, L, C, F)                                              \
    funcion_codigo[fi++] = latMV_bytecode_crear(I, A, B, M, L, C, F)
#define fpn(vm, N) fi = ast_analizar(vm, N, funcion_codigo, fi)

struct lat_longjmp {
    struct lat_longjmp *previo;
    lat_jmpbuf b;
    volatile int status;
};

// void str_formato(lat_mv *mv);
void str_concatenar(lat_mv *mv);

static ast *transformar_casos(ast *casos, ast *cond_izq) {
    if (casos == NULL) {
        return NULL;
    }
    ast *caso = casos->izq;
    ast *cond = NULL;
    if (caso->tipo == NODO_CASO) {
        cond = latA_nodo(NODO_IGUALDAD, cond_izq, caso->izq, cond_izq->nlin,
                         cond_izq->ncol);
    }
    if (caso->tipo == NODO_DEFECTO) {
        cond = latA_nodo(NODO_IGUALDAD, cond_izq, cond_izq, cond_izq->nlin,
                         cond_izq->ncol);
    }
    ast *nSi = latA_si(cond, caso->der,
                       ((ast *)transformar_casos(casos->der, cond_izq)));
    return nSi;
}

static ast *transformar_elegir(ast *nodo_elegir) {
    ast *cond_izq = nodo_elegir->izq;
    ast *casos = nodo_elegir->der;
    ast *nSi = NULL;
    nSi = transformar_casos(casos, cond_izq);
    return nSi;
}

static void liberar_elegir(ast *a) {
    if (a) {
        switch (a->tipo) {
            case NODO_SI: {
                nodo_si *nsi = (nodo_si *)a;
                free(nsi->cond);
                liberar_elegir(nsi->entonces);
                if (nsi->_sino) {
                    liberar_elegir(nsi->_sino);
                }
                free(a);
                break;
            }
            default: { ; }
        }
    }
}

static int contar_num_parargs(ast *nodo, nodo_tipo nt) {
    ast *tmp;
    int nparams = 0;
    if (nodo) {
        if (nodo->tipo == nt) {
            tmp = nodo;
            while (tmp->der != NULL && tmp->der->tipo == nt) {
                tmp = tmp->der;
                nparams++;
            }
            if (tmp->izq->tipo) {
                nparams++;
            }
        }
    }
    return nparams;
}

static bool encontrar_vararg(ast *nodo) {
    if (nodo && nodo->izq && nodo->izq->tipo == NODO_VAR_ARGS) {
        return true;
    }
    return false;
}

static int encontrar_load_vararg(ast *nodo) {
    int i = 0;
    if (nodo) {
        ast *tmp;
        tmp = nodo;
        while (tmp->der != NULL && tmp->der->tipo != NODO_LOAD_VAR_ARGS) {
            if (tmp->der != NULL && tmp->der->tipo == NODO_LOAD_VAR_ARGS) {
                i++;
            }
            tmp = tmp->der;
        }
        if (tmp->izq != NULL && tmp->izq->tipo == NODO_LOAD_VAR_ARGS) {
            i++;
        }
    }
    return i;
}

static int ast_analizar(lat_mv *mv, ast *nodo, lat_bytecode *codigo, int i) {
    int temp[4] = {0};
    lat_bytecode *funcion_codigo = NULL;
    int fi = 0;
    if (nodo->nlin > 0) {
        mv->nlin = nodo->nlin;
        mv->ncol = nodo->ncol;
    }
    switch (nodo->tipo) {
        case NODO_VALOR: {
            lat_objeto *o = NULL;
            if (nodo->valor->tipo == VALOR_LOGICO) {
                o = (nodo->valor->val.logico == true) ? latO_verdadero
                                                      : latO_falso;
            }
            if (nodo->valor->tipo == VALOR_NULO) {
                o = latO_nulo;
            }
            if (nodo->valor->tipo == VALOR_NUMERICO) {
                o = latC_crear_numerico(mv, nodo->valor->val.numerico);
                o->marca = 0;
            }
            if (nodo->valor->tipo == VALOR_CADENA) {
                o = latC_crear_cadena(mv, nodo->valor->val.cadena);
                o->marca = 0;
            }
            dbc(LOAD_CONST, 0, 0, o, nodo->nlin, nodo->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_IDENTIFICADOR: {
            lat_objeto *o = latC_crear_cadena(mv, nodo->valor->val.cadena);
            o->marca = 0;
            o->esconst = nodo->valor->esconst;
            dbc(LOAD_NAME, 0, 0, o, nodo->nlin, nodo->ncol, mv->nombre_archivo);
        } break;
        case NODO_ASIGNACION: {
            // printf("%s\n", "NODO_ASIGNACION");
            int num_params = 1;
            if (nodo->der->tipo == NODO_FUNCION_PARAMETROS) {
                num_params =
                    contar_num_parargs(nodo->der, NODO_FUNCION_PARAMETROS);
            }
            pn(mv, nodo->izq);
            if (num_params > 1 || nodo->izq->tipo == NODO_FUNCION_LLAMADA) {
                dbc(ADJUST_STACK, num_params, 0, NULL, mv->nlin, mv->ncol,
                    mv->nombre_archivo);
            }
            if (nodo->der->tipo == NODO_FUNCION_PARAMETROS) {
                pn(mv, nodo->der);
            } else if (nodo->der->tipo == NODO_ATRIBUTO) {
                pn(mv, nodo->der->izq);
                lat_objeto *o =
                    latC_crear_cadena(mv, nodo->der->der->valor->val.cadena);
                o->marca = 0;
                o->esconst = nodo->der->der->valor->esconst;
                dbc(STORE_ATTR, 0, 0, o, nodo->der->der->nlin,
                    nodo->der->der->ncol, mv->nombre_archivo);
            } else {
                lat_objeto *o =
                    latC_crear_cadena(mv, nodo->der->valor->val.cadena);
                o->marca = 0;
                o->esconst = nodo->der->valor->esconst;
                dbc(STORE_NAME, 0, 0, o, nodo->der->nlin, nodo->der->ncol,
                    mv->nombre_archivo);
            }
        } break;
        case NODO_GLOBAL: {
            dbc(SET_GLOBAL, 0, 0, NULL, mv->nlin, mv->ncol, mv->nombre_archivo);
            pn(mv, nodo->izq);
            dbc(SET_LOCAL, 0, 0, NULL, mv->nlin, mv->ncol, mv->nombre_archivo);
        } break;
        case NODO_MAS_UNARIO: {
            pn(mv, nodo->izq);
        } break;
        case NODO_MENOS_UNARIO: {
            pn(mv, nodo->izq);
            dbc(UNARY_MINUS, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_INC: {
            lat_objeto *o = latC_crear_cadena(mv, nodo->izq->valor->val.cadena);
            o->marca = 0;
            o->esconst = nodo->izq->valor->esconst;
            dbc(OP_INC, 0, 0, o, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_DEC: {
            lat_objeto *o = latC_crear_cadena(mv, nodo->izq->valor->val.cadena);
            o->marca = 0;
            o->esconst = nodo->izq->valor->esconst;
            dbc(OP_DEC, 0, 0, o, nodo->nlin, nodo->ncol, mv->nombre_archivo);
        } break;
        case NODO_SUMA: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_ADD, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_RESTA: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_SUB, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_POTENCIA: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_POW, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_MULTIPLICACION: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_MUL, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_DIVISION: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_DIV, 0, 0, NULL, nodo->der->nlin, nodo->der->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_MODULO: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_MOD, 0, 0, NULL, nodo->der->nlin, nodo->der->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_MAYOR_QUE: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_GT, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_MAYOR_IGUAL: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_GE, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_MENOR_QUE: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_LT, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_MENOR_IGUAL: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_LE, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_IGUALDAD: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_EQ, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_REGEX: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_REGEX, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_DESIGUALDAD: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_NEQ, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_Y: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_AND, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_O: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(OP_OR, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_NO: {
            pn(mv, nodo->izq);
            dbc(OP_NOT, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_CONCATENAR: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(CONCAT, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_SI: {
            nodo_si *nIf = ((nodo_si *)nodo);
            pn(mv, nIf->cond);
            temp[0] = i;
            dbc(NOP, 0, 0, NULL, 0, 0, mv->nombre_archivo);
            pn(mv, nIf->entonces);
            temp[1] = i;
            dbc(NOP, 0, 0, NULL, 0, 0, mv->nombre_archivo);
            temp[2] = i;
            if (nIf->_sino) {
                pn(mv, nIf->_sino);
            }
            temp[3] = i;
            codigo[temp[0]] = latMV_bytecode_crear(
                POP_JUMP_IF_FALSE, (temp[2] - 1), 0, NULL, nIf->cond->nlin,
                nIf->cond->ncol, mv->nombre_archivo);
            codigo[temp[1]] = latMV_bytecode_crear(
                JUMP_ABSOLUTE, (temp[3] - 1), 0, NULL, nIf->cond->nlin,
                nIf->cond->ncol, mv->nombre_archivo);
        } break;
        case NODO_ELEGIR: {
            ast *nSi = transformar_elegir(nodo);
            pn(mv, nSi);
            liberar_elegir(nSi);
        } break;
        case NODO_MIENTRAS: {
            temp[0] = i;
            pn(mv, nodo->izq);
            temp[1] = i;
            dbc(NOP, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
            pn(mv, nodo->der);
            dbc(JUMP_ABSOLUTE, (temp[0] - 1), 0, NULL, nodo->izq->nlin,
                nodo->izq->ncol, mv->nombre_archivo);
            codigo[temp[1]] = latMV_bytecode_crear(
                POP_JUMP_IF_FALSE, (i - 1), 0, NULL, nodo->izq->nlin,
                nodo->izq->ncol, mv->nombre_archivo);
        } break;
        case NODO_REPETIR: {
            temp[0] = i;
            pn(mv, nodo->der);
            pn(mv, nodo->izq);
            temp[1] = i;
            dbc(NOP, 0, 0, NULL, 0, 0, mv->nombre_archivo);
            codigo[temp[1]] = latMV_bytecode_crear(
                POP_JUMP_IF_FALSE, (temp[0] - 1), 0, NULL, nodo->izq->izq->nlin,
                nodo->izq->izq->ncol, mv->nombre_archivo);
        } break;
        case NODO_FUNCION_LLAMADA: {
            // argumentos
            if (nodo->der) {
                pn(mv, nodo->der);
            }
            // nombre fun
            pn(mv, nodo->izq);
            int num_args =
                contar_num_parargs(nodo->der, NODO_FUNCION_ARGUMENTOS);
            dbc(CALL_FUNCTION, num_args, 0, NULL, mv->nlin, mv->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_RETORNO: {
            pn(mv, nodo->izq);
            int num_args =
                contar_num_parargs(nodo->izq, NODO_FUNCION_ARGUMENTOS);
            dbc(RETURN_VALUE, num_args == 0 ? 1 : num_args, 0, NULL,
                nodo->izq->nlin, nodo->izq->ncol, mv->nombre_archivo);
        } break;
        case NODO_FUNCION_ARGUMENTOS: {
            if (nodo->izq) {
                pn(mv, nodo->izq);
            }
            if (nodo->der) {
                pn(mv, nodo->der);
            }
        } break;
        case NODO_ATRIBUTO: {
            pn(mv, nodo->izq);
            lat_objeto *o = latC_crear_cadena(mv, nodo->der->valor->val.cadena);
            o->marca = 0;
            o->esconst = nodo->der->valor->esconst;
            dbc(LOAD_ATTR, 0, 0, o, nodo->der->nlin, nodo->der->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_FUNCION_PARAMETROS: {
            if (nodo->izq) {
                if (nodo->izq->tipo == NODO_VAR_ARGS) {
                    int num_params =
                        contar_num_parargs(nodo, NODO_FUNCION_PARAMETROS);
                    dbc(OP_VAR_ARGS, (num_params - 1), 0, NULL, mv->nlin,
                        mv->ncol, mv->nombre_archivo);
                } else {
                    lat_objeto *o =
                        latC_crear_cadena(mv, nodo->izq->valor->val.cadena);
                    o->marca = 0;
                    o->esconst = nodo->izq->valor->esconst;
                    dbc(STORE_NAME, 0, 0, o, nodo->izq->nlin, nodo->izq->ncol,
                        mv->nombre_archivo);
                }
            }
            if (nodo->der) {
                pn(mv, nodo->der);
            }
        } break;
        case NODO_FUNCION_USUARIO: {
            // printf("%s\n", "NODO_FUNCION_USUARIO");
            nodo_funcion *fun = (nodo_funcion *)nodo;
            funcion_codigo = (lat_bytecode *)latM_asignar(
                mv, sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
            fi = 0;
            // procesar lista de params
            bool es_vararg = false;
            if (fun->params) {
                fpn(mv, fun->params);
                es_vararg = encontrar_vararg(fun->params);
            }
            // procesar instrucciones
            fpn(mv, fun->stmts);
            fdbc(RETURN_VALUE, 0, 0, latO_nulo, fun->nombre->nlin,
                 fun->nombre->ncol, mv->nombre_archivo);
            lat_objeto *f = latC_crear_funcion(mv, funcion_codigo, fi + 1);
            f->marca = 0;
            f->es_vararg = es_vararg;
            dbc(MAKE_FUNCTION, fi + 1, 0, f, fun->nombre->nlin,
                fun->nombre->ncol, mv->nombre_archivo);
            funcion_codigo = NULL;
            fi = 0;
            lat_objeto *o =
                latC_crear_cadena(mv, fun->nombre->valor->val.cadena);
            o->marca = 0;
            // printf("val.cadena: %s\n", fun->nombre->valor->val.cadena);
            f->nparams =
                contar_num_parargs(fun->params, NODO_FUNCION_PARAMETROS);
            f->nombre = strdup(fun->nombre->valor->val.cadena);
            dbc(STORE_NAME, 0, 0, o, nodo->nlin, nodo->ncol,
                mv->nombre_archivo);
            if (!strcmp(f->nombre, "anonima")) {
                lat_objeto *anon = latO_clonar(mv, o);
                anon->marca = 0;
                dbc(LOAD_NAME, 0, 0, anon, nodo->nlin, nodo->ncol,
                    mv->nombre_archivo);
            }
            if (!strcmp(getstr(getCadena(o)), "menu")) {
                mv->global->menu = true;
            }
        } break;
        case NODO_LISTA: {
            int es_vararg = 0;
            int nparams = 0;
            if (nodo->izq) {
                pn(mv, nodo->izq);
                nparams =
                    contar_num_parargs(nodo->izq, NODO_LISTA_AGREGAR_ELEMENTO);
                es_vararg = encontrar_load_vararg(nodo->izq);
            }
            dbc(BUILD_LIST, nparams, es_vararg, NULL, mv->nlin, mv->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_LISTA_AGREGAR_ELEMENTO: {
            if (nodo->izq) {
                pn(mv, nodo->izq);
            }
            if (nodo->der) {
                pn(mv, nodo->der);
            }
        } break;
        case NODO_LISTA_ASIGNAR_ELEMENTO: {
            nodo_lista_elem *nl = (nodo_lista_elem *)nodo;
            pn(mv, nl->exp);
            pn(mv, nl->id);
            pn(mv, nl->pos);
            dbc(STORE_SUBSCR, 0, 0, NULL, mv->nlin, mv->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_LISTA_OBTENER_ELEMENTO: {
            pn(mv, nodo->izq);
            pn(mv, nodo->der);
            dbc(BINARY_SUBSCR, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_DICCIONARIO: {
            int nparams = 0;
            if (nodo->izq) {
                nparams =
                    contar_num_parargs(nodo->izq, NODO_DICC_AGREGAR_ELEMENTO);
            }
            dbc(BUILD_MAP, nparams, 0, NULL, mv->nlin, mv->ncol,
                mv->nombre_archivo);
            if (nodo->izq) {
                pn(mv, nodo->izq);
            }
        } break;
        case NODO_DICC_AGREGAR_ELEMENTO: {
            if (nodo->der) {
                pn(mv, nodo->der);
            }
            if (nodo->izq) {
                pn(mv, nodo->izq);
            }
            dbc(STORE_MAP, 0, 0, NULL, nodo->izq->nlin, nodo->izq->ncol,
                mv->nombre_archivo);
        } break;
        case NODO_DICC_ELEMENTO: {
            if (nodo->der) {
                pn(mv, nodo->der);
            }
            if (nodo->izq) {
                pn(mv, nodo->izq);
            }
        } break;
        case NODO_BLOQUE: {
            if (nodo->izq) {
                pn(mv, nodo->izq);
            }
            if (nodo->der) {
                pn(mv, nodo->der);
            }
        } break;
        case NODO_NULO:
            break;
        case NODO_VAR_ARGS: {
            ;
        } break;
        case NODO_LOAD_VAR_ARGS: {
            dbc(LOAD_VAR_ARGS, 0, 0, NULL, mv->nlin, mv->ncol,
                mv->nombre_archivo);
        } break;
        default:
            printf("ERROR nodo->tipo:%i\n", nodo->tipo);
            return 0;
    }
    return i;
}

void mostrar_bytecode(lat_mv *mv, lat_bytecode *codigo) {
    lat_bytecode *inslist = codigo;
    lat_bytecode cur;
    lat_objeto *o = NULL;
    int pos;
    for (pos = 0, cur = inslist[pos]; cur.ins && cur.ins != HALT;
         cur = inslist[++pos]) {
        char *buffer = NULL;
        printf("%i\t%i\t", cur.nlin, pos);
        switch (cur.ins) {
            case HALT:
                return;
                break;
            case NOP:
            case UNARY_MINUS:
            case BINARY_ADD:
            case BINARY_SUB:
            case BINARY_POW:
            case BINARY_MUL:
            case BINARY_DIV:
            case BINARY_MOD:
            case OP_GT:
            case OP_GE:
            case OP_LT:
            case OP_LE:
            case OP_EQ:
            case OP_REGEX:
            case OP_NEQ:
            case OP_AND:
            case OP_OR:
            case OP_NOT:
            case CONCAT:
            case PUSH_CTX:
            case POP_CTX:
            case RETURN_VALUE:
            case STORE_SUBSCR:
            case BINARY_SUBSCR:
            case STORE_MAP:
            case STORE_ATTR:
            case SET_GLOBAL:
            case SET_LOCAL:
            case OP_POP:
                printf("%s\n", latMV_bytecode_nombre(cur.ins));
                break;
            case CALL_FUNCTION: {
                printf("CALL_FUNCTION\t%i\n", cur.a);
            } break;
            case LOAD_ATTR: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("LOAD_ATTR\t(%s)\n", buffer);
                free(buffer);
            } break;
            case LOAD_CONST: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("LOAD_CONST\t(%s)\n", buffer);
                free(buffer);
            } break;
            case LOAD_NAME: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("LOAD_NAME\t(%s)\n", buffer);
                free(buffer);
            } break;
            case STORE_NAME: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("STORE_NAME\t(%s)\n", buffer);
                free(buffer);
            } break;
            case JUMP_ABSOLUTE: {
                printf("JUMP_ABSOLUTE\t(%i)\n", (cur.a + 1));
            } break;
            case POP_JUMP_IF_FALSE: {
                printf("POP_JUMP_IF_FALSE\t(%i)\n", (cur.a + 1));
            } break;
            case POP_JUMP_IF_TRUE: {
                printf("POP_JUMP_IF_TRUE\t(%i)\n", (cur.a + 1));
            } break;
            case OP_INC: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("OP_INC\t(%s)\n", buffer);
                free(buffer);
            } break;
            case OP_DEC: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("OP_DEC\t(%s)\n", buffer);
                free(buffer);
            } break;
            case BUILD_LIST: {
                printf("BUILD_LIST\t%i\t%i\n", cur.a, cur.b);
            } break;
            case BUILD_MAP: {
                printf("BUILD_MAP\t%i\n", cur.a);
            } break;
            case MAKE_FUNCTION: {
                printf("MAKE_FUNCTION\n");
                printf("-------------------------------\n");
                o = (lat_objeto *)cur.meta;
                lat_funcion *fun = getFun(o);
                mostrar_bytecode(mv, fun->codigo);
            } break;
            case OP_VAR_ARGS: {
                printf("OP_VAR_ARGS\t%i\n", cur.a);
            } break;
            case LOAD_VAR_ARGS: {
                printf("LOAD_VAR_ARGS\n");
            } break;
            case OP_PUSH: {
                o = (lat_objeto *)cur.meta;
                buffer = latC_astring(mv, o);
                printf("OP_PUSH\t(%s)\n", buffer);
                free(buffer);
            } break;
            case ADJUST_STACK: {
                printf("ADJUST_STACK\t%i\n", cur.a);
            } break;
        }
    }
    printf("-------------------------------\n");
}

void latD_lanzar(lat_mv *mv, int errcode) {
    if (mv->error) {
        mv->error->status = errcode;
        LAT_THROW(mv, mv->error);
    } else {
        mv->status = errcode;
        mv->error = NULL;
        exit(EXIT_FAILURE);
    }
}

LATINO_API void latC_error(lat_mv *mv, const char *fmt, ...) {
    char buffer[MAX_INPUT_SIZE];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    char *info = malloc(MAX_INPUT_SIZE);
    snprintf(info, MAX_INPUT_SIZE, LAT_ERROR_FMT, mv->nombre_archivo, mv->nlin,
             mv->ncol);
    latC_apilar(mv, latC_crear_cadena(mv, info));
    latC_apilar(mv, latC_crear_cadena(mv, buffer));
    str_concatenar(mv);
    lat_objeto *err = latC_desapilar(mv);
    fprintf(stderr, "%s\n", latC_astring(mv, err));
    latD_lanzar(mv, LAT_ERRRUN);
}

LATINO_API int latC_llamar_funcion(lat_mv *mv, lat_objeto *func) {
    // printf("%s\n", func->nombre);
    struct lat_longjmp lj;
    lj.status = 0;
    lj.previo = mv->error;
    mv->error = &lj;
    LAT_TRY(mv, &lj, latMV_funcion_correr(mv, func););
    mv->error = lj.previo;
    return lj.status;
}

LATINO_API lat_objeto *latC_analizar(lat_mv *mv, ast *nodo) {
    // printf("%s\n", ">>> latC_analizar");
    // FIXME: Much memory allocation
    lat_bytecode *codigo =
        latM_asignar(mv, sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    int i = ast_analizar(mv, nodo, codigo, 0);
    dbc(HALT, 0, 0, NULL, 0, 0, mv->nombre_archivo);
#if DEPURAR_AST
    mostrar_bytecode(mv, codigo);
#endif
    lat_objeto *fun = latC_crear_funcion(mv, codigo, i);
    fun->marca = 0;
    fun->nombre = "dummy";
    return fun;
}
