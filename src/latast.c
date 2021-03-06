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

#include "latast.h"
#include "latino.h"
#include "latlex.h"
#include "latmem.h"

int yyparse(ast **root, yyscan_t scanner);
char *analizar_fmt(const char *s, size_t len);

ast *latA_nodo(nodo_tipo nt, ast *l, ast *r, int nlin, int ncol) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = nt;
    a->izq = l;
    a->der = r;
    a->valor = NULL;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_logico(int b, int nlin, int ncol) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor *)malloc(sizeof(nodo_valor));
    val->tipo = VALOR_LOGICO;
    val->val.logico = b;
    a->valor = val;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_nulo(void *nulo, int nlin, int ncol) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor *)malloc(sizeof(nodo_valor));
    val->tipo = VALOR_NULO;
    val->val.cadena = nulo;
    a->valor = val;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_numerico(double d, int nlin, int ncol) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor *)malloc(sizeof(nodo_valor));
    val->tipo = VALOR_NUMERICO;
    val->val.numerico = d;
    a->valor = val;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_cadena(const char *s, int nlin, int ncol) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor *)malloc(sizeof(nodo_valor));
    val->tipo = VALOR_CADENA;
    val->val.cadena = analizar_fmt(s, strlen(s));
    a->valor = val;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_literal(const char *s, int nlin, int ncol) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor *)malloc(sizeof(nodo_valor));
    val->tipo = VALOR_CADENA;
    val->val.cadena = analizar_fmt(s, strlen(s));
    a->valor = val;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_var(const char *s, int nlin, int ncol, bool esconst) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_IDENTIFICADOR;
    nodo_valor *val = (nodo_valor *)malloc(sizeof(nodo_valor));
    val->tipo = VALOR_CADENA;
    val->val.cadena = strdup(s);
    val->esconst = esconst;
    a->valor = val;
    a->nlin = nlin;
    a->ncol = ncol;
    return a;
}

ast *latA_asign(ast *val, ast *sim) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_ASIGNACION;
    a->izq = val;
    a->der = sim;
    a->valor = NULL;
    return a;
}

ast *latA_asign_le(ast *exp, ast *id, ast *pos) {
    nodo_lista_elem *a = (nodo_lista_elem *)malloc(sizeof(nodo_lista_elem));
    a->tipo = NODO_LISTA_ASIGNAR_ELEMENTO;
    a->exp = exp;
    a->id = id;
    a->pos = pos;
    return (ast *)a;
}

ast *latA_si(ast *cond, ast *th, ast *el) {
    nodo_si *a = (nodo_si *)malloc(sizeof(nodo_si));
    a->tipo = NODO_SI;
    a->cond = cond;
    a->entonces = th;
    a->_sino = el;
    return (ast *)a;
}

ast *latA_mientras(ast *cond, ast *stmts) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_MIENTRAS;
    a->izq = cond;
    a->der = stmts;
    a->valor = NULL;
    return a;
}

ast *latA_hacer(ast *cond, ast *stmts) {
    ast *a = (ast *)malloc(sizeof(ast));
    a->tipo = NODO_REPETIR;
    a->izq = cond;
    a->der = stmts;
    a->valor = NULL;
    return a;
}

ast *latA_desde(ast *dec, ast *cond, ast *inc, ast *stmts) {
    ast *a = (ast *)malloc(sizeof(ast));
    ast *tmp = stmts;
    while(tmp->der != NULL) {
        tmp = tmp->der;
    }
    tmp->der = inc;
    a->tipo = NODO_BLOQUE;
    a->izq = dec;
    a->der = latA_mientras(cond, stmts);
    a->valor = NULL;
    return a;
}

ast *latA_para(ast *identificador, ast* inicio, ast* fin, ast* incremento, ast *sentencias) {
    if (inicio == NULL) {
        inicio = latA_numerico(0, identificador->nlin, identificador->ncol);
    }
    if (incremento == NULL) {
        incremento = latA_numerico(1, identificador->nlin, identificador->ncol);
    }
    if (inicio->tipo == NODO_MENOS_UNARIO) {
        inicio = latA_numerico(-(inicio->izq->valor->val.numerico), identificador->nlin, identificador->ncol);
    }
    if (fin->tipo == NODO_MENOS_UNARIO) {
        fin = latA_numerico(-(fin->izq->valor->val.numerico), identificador->nlin, identificador->ncol);
    }
    ast *a = (ast *)malloc(sizeof(ast));
    /* asign -> (i = 3) */
    ast *asign = latA_asign(inicio, identificador);
    /* i  < 10 */
    ast *cond = NULL;
    if (incremento->tipo == NODO_MENOS_UNARIO) {
        // cuando es decremento
        if (inicio->valor->val.numerico > fin->valor->val.numerico) {
            cond = latA_nodo(NODO_MAYOR_QUE, identificador, fin, identificador->nlin, identificador->ncol);
            incremento = latA_numerico(-(incremento->izq->valor->val.numerico), identificador->nlin, identificador->ncol);
        }
    } else {
        if (inicio->valor->val.numerico < fin->valor->val.numerico) {
            cond = latA_nodo(NODO_MENOR_QUE, identificador, fin, identificador->nlin, identificador->ncol);
        }
    }
    /* suma -> (i + inc) */
    ast *suma = latA_nodo(NODO_SUMA, identificador, incremento, identificador->nlin, identificador->ncol);
    /*inc -> (i = suma) -> i = i + 3 */
    ast *inc = latA_asign(suma, identificador);
    ast *tmp = sentencias;
    while(tmp->der != NULL) {
        tmp = tmp->der;
    }
    tmp->der = inc;
    a->tipo = NODO_BLOQUE;
    a->izq = asign;
    a->der = latA_mientras(cond, sentencias);
    a->valor = NULL;
    return a;
}

ast *latA_funcion(ast *nombre, ast *params, ast *stmts, int nlin, int ncol) {
    nodo_funcion *a = (nodo_funcion *)malloc(sizeof(ast));
    a->tipo = NODO_FUNCION_USUARIO;
    a->nombre = nombre;
    a->params = params;
    a->stmts = stmts;
    a->nlin = nlin;
    a->ncol = ncol;
    return (ast *)a;
}

void latA_destruir(ast *a) {
    if (a) {
        if(a->tipo < 51) { // a->tipo <= 50
            switch (a->tipo) {
                case NODO_SI: {
                    nodo_si *nsi = (nodo_si *)a;
                    latA_destruir(nsi->cond);
                    latA_destruir(nsi->entonces);
                    if (nsi->_sino)
                        latA_destruir(nsi->_sino);
                    break;
                }
                case NODO_FUNCION_USUARIO: {
                    nodo_funcion *fun = (nodo_funcion *)a;
                    if (fun->params)
                        latA_destruir(fun->params);
                    if (fun->stmts)
                        latA_destruir(fun->stmts);
                    latA_destruir(fun->nombre);
                    break;
                }
                case NODO_LISTA_ASIGNAR_ELEMENTO: {
                    nodo_lista_elem *nelem = (nodo_lista_elem *)a;
                    latA_destruir(nelem->exp);
                    latA_destruir(nelem->id);
                    latA_destruir(nelem->pos);
                    break;
                }
                case NODO_IDENTIFICADOR:
                case NODO_VALOR:
                    if(a->valor) {
                        if (a->valor->tipo == VALOR_CADENA) {
                            free(a->valor->val.cadena);
                        }
                        free(a->valor);
                    }
                    break;
                // TODO: liberar nuevo nodo rango
                default:
                    if (a->izq)
                        latA_destruir(a->izq);
                    if (a->der)
                        latA_destruir(a->der);
            }
            free(a);
        }
    }
}

/**
 * latA_analizar_exp: Esta funcion crea el arbol abstracto de sintaxis a partir
 *de una cadena REM: liberar el nodo cuando se deje de ocupar
 **/
ast *latA_analizar_exp(char *expr, int *status) {
    ast *nodo = NULL;
    yyscan_t scanner;
    YY_BUFFER_STATE state;
    lex_state scan_state = {.insert = 0};
    yylex_init_extra(&scan_state, &scanner);
    state = yy_scan_string(expr, scanner);
    *status = yyparse(&nodo, scanner);
    yy_delete_buffer(state, scanner);
    yylex_destroy(scanner);
    return nodo;
}

/**
 * latA_analizar_exp: Esta funcion crea el arbol abstracto de sintaxis a partir
 *de un archivo REM: liberar el nodo cuando se deje de ocupar
 **/
ast *latA_analizar_arch(char *infile, int *status) {
    if (infile == NULL) {
        printf("Especifique un archivo\n");
        return NULL;
    }
    char *dot = strrchr(infile, '.');
    char *extension;
    if (!dot || dot == infile) {
        extension = "";
    } else {
        extension = dot + 1;
        if (strcmp(extension, "lat")) {
            printf("El archivo '%s' no contiene la extension .lat\n", infile);
            return NULL;
        }
    }
    FILE *file = fopen(infile, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo: %s\n", infile);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(fsize + 1);
    size_t newSize = fread(buffer, sizeof(char), fsize, file);
    if (buffer == NULL) {
        printf("No se pudo asignar %d bytes de memoria\n", fsize);
        return NULL;
    }
    if (file != NULL) {
        fclose(file);
    }
    buffer[newSize] = '\0';
    filename = infile;
    ast *nodo = latA_analizar_exp(buffer, status);
    free(buffer);
    return nodo;
}
