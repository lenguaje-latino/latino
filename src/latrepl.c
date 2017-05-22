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

#include "latrepl.h"
#include "latino.h"

bool inicia_con(const char *base, const char *str);
char *reemplazar(char *str, const char *orig, const char *rep);

//void base_poner(lat_mv *mv);

static void completion(const char *buf, linenoiseCompletions *lc) {
    if (inicia_con(buf, "pon")) {
        linenoiseAddCompletion(lc, "poner");
    }
}

int leer_linea(char *buffer) {
    char *prompt = "latino> ";
    char *input;
    char *tmp = malloc(MAX_INPUT_SIZE);
REP:
    input = linenoise(prompt);
    // printf("input: %s\n", input);
    if (input == NULL) {
        return -1;
    }
    for (;;) {
        int len = strlen(input);
        memcpy(tmp, input, len);
        tmp[len] = '\0';
        int estatus;
        // printf("tmp: %s\n", tmp);
        latA_analizar_exp(tmp, &estatus);
        if (estatus == 1) {
            tmp = strcat(tmp, "\n");
            prompt = "    >>> ";
            goto REP;
        } else {
            prompt = "latino> ";
            strcpy(buffer, tmp);
            free(tmp);
            return 0;
        }
    }
}

void latR_REPL(lat_mv *mv) {
    parse_silent = 1;
    mv->global->REPL = true;
    mv->nombre_archivo = "REPL";
    char *buf = malloc(MAX_INPUT_SIZE);
    char *dir_history = getenv("HOME");
    if (!dir_history || dir_history == NULL) {
        dir_history = HISTORY_FILE;
    } else {
        strcat(dir_history, "/");
        strcat(dir_history, HISTORY_FILE);
    }
    ast *nodo = NULL;
    int status;
    linenoiseHistoryLoad(dir_history);
    linenoiseSetCompletionCallback(completion);
    while (leer_linea(buf) != -1) {
        nodo = latA_analizar_exp(buf, &status);
        if (nodo != NULL) {
            lat_objeto *curexpr = latC_analizar(mv, nodo);
            status = latC_llamar_funcion(mv, curexpr);
            /*lat_objeto *o = latC_tope(mv);
            if (strstr(buf, "imprimirf") != NULL) {
                printf("\n");
            } else if (o != NULL && o->tipo != T_NULL &&
                       strstr(buf, "poner") == NULL &&
                       strstr(buf, "escribir") == NULL &&
                       strstr(buf, "imprimir") == NULL &&
                       strstr(buf, "imprimirf") == NULL) {
                base_poner(mv);
            }*/
        }
        /* se guarda el comando al historial aunque haya error */
        char *tmp = reemplazar(buf, "\n", "");
        // printf("guardando en HISTORY_FILE: %s\n", buf);
        linenoiseHistoryAdd(tmp);
        linenoiseHistorySave(dir_history);
        free(tmp);
    }
    free(buf);
}
