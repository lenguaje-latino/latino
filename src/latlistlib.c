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

#include "latino.h"

#define LIB_LISTA_NAME "lista"

static void lista_agregar(lat_mv *mv) {
    lat_objeto *elem = latC_desapilar(mv);
    lat_objeto *lst = latC_desapilar(mv);
    if (!latO_comparar(mv, lst, elem)) {
        latC_error(mv, "Referencia circular detectada");
    }
    latL_agregar(mv, latC_checar_lista(mv, lst), latO_clonar(mv, elem));
}

static void lista_extender(lat_mv *mv) {
    lat_objeto *l2 = latC_desapilar(mv);
    lat_objeto *lst = latC_desapilar(mv);
    if (lst->tipo != T_LIST) {
        latC_error(mv, "El objeto no es una lista");
    }
    if (l2->tipo != T_LIST) {
        latC_error(mv, "El objeto no es una lista");
    }
    lista *_lst2 = latC_checar_lista(mv, l2);
    lista *_lst = latC_checar_lista(mv, lst);
    latL_extender(mv, _lst, _lst2);
}

static void lista_eliminar_indice(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    int pos = latC_checar_numerico(mv, b);
    if (pos < 0 || pos >= latL_longitud(lst)) {
        latC_error(mv, "Indice fuera de rango");
    }
    if (pos >= 0) {
        nodo_lista *nt = latL_obtener_nodo(mv, lst, pos);
        latL_eliminar_nodo(mv, lst, nt);
    }
}

static void lista_invertir(lat_mv *mv) {
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    lista *nl = latL_crear(mv);
    // FIXME: For performance
    int i;
    int len = latL_longitud(lst) - 1;
    for (i = len; i >= 0; i--) {
        latL_agregar(mv, nl, latL_obtener_elemento(mv, lst, i));
    }
    lat_objeto *tmp = latC_crear_lista(mv, nl);
    latC_apilar(mv, tmp);
}

static void lista_longitud(lat_mv *mv) {
    lat_objeto *o = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, latL_longitud(latC_checar_lista(mv, o)));
    latC_apilar(mv, tmp);
}

static void lista_comparar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lat_objeto *tmp =
        latC_crear_numerico(mv, latL_comparar(mv, latC_checar_lista(mv, a),
                                              latC_checar_lista(mv, b)));
    latC_apilar(mv, tmp);
}

static void lista_insertar(lat_mv *mv) {
    lat_objeto *c = latC_desapilar(mv);
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    latL_insertar_elemento(mv, latC_checar_lista(mv, a), latO_clonar(mv, b),
                           latC_checar_numerico(mv, c));
}

static void lista_eliminar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    int i = latL_obtener_indice(mv, lst, b);
    if (i >= 0) {
        nodo_lista *nt = latL_obtener_nodo(mv, lst, i);
        latL_eliminar_nodo(mv, lst, nt);
    }
}

static void lista_indice(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    int i = latL_obtener_indice(mv, lst, b);
    lat_objeto *tmp = latC_crear_numerico(mv, (double)i);
    latC_apilar(mv, tmp);
}

static void lista_contiene(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    lista *lst = latC_checar_lista(mv, a);
    bool contiene = latL_contiene_valor(mv, lst, b);
    if (contiene) {
        latC_apilar(mv, latO_verdadero);
    } else {
        latC_apilar(mv, latO_falso);
    }
}

static void lista_crear(lat_mv *mv) {
    lat_objeto *num = latC_desapilar(mv);
    int i = 0;
    int cant = latC_checar_numerico(mv, num);
    lista *lst = latL_crear(mv);
    if (cant > 0) {
        while (i < cant) {
            latL_agregar(mv, lst, latO_nulo);
            i++;
        }
    }
    latC_apilar(mv, latC_crear_lista(mv, lst));
}

void lista_concatenar(lat_mv *mv) {
    lat_objeto *l2 = latC_desapilar(mv);
    lat_objeto *l1 = latC_desapilar(mv);

    lista *nl = latL_crear(mv);
    lista *lt1 = latC_checar_lista(mv, l1);
    lista *lt2 = latC_checar_lista(mv, l2);

    int i;
    int len1 = latL_longitud(lt1), len2 = latL_longitud(lt2);

    for (i = 0; i < len1; i++) {
        latL_agregar(mv, nl, latL_obtener_elemento(mv, lt1, i));
    }
    for (i = 0; i < len2; i++) {
        latL_agregar(mv, nl, latL_obtener_elemento(mv, lt2, i));
    }

    lat_objeto *tmp = latC_crear_lista(mv, nl);
    latC_apilar(mv, tmp);
}

void lista_separar(lat_mv *mv) {
    lat_objeto *separador = latC_desapilar(mv);
    lat_objeto *list_ = latC_desapilar(mv);
    long int mem = 64; // incluyo en el valor de la memoria 64 espacios por si
                       // acaso son númericos
    char *texto = malloc(mem); // inicio la asignación de memoria
    char *sep = " "; // el separador por defecto será " " (un espacio)
    if (separador->tipo != T_NULL) {
        sep = latC_checar_cadena(mv, separador); // si no es nulo, ponemos el
                                                 // separador que indique el
                                                 // usuario en el segundo
                                                 // argumento
    };
    char *sep_elegido = sep;
    lista *lst = latC_checar_lista(mv, list_); // creamos la lista
    texto[0] = '\0'; // iniciamos el valor 0 de texto como nulo
    long int lng = latL_longitud(lst); // creo la longitud de la lista para no
                                       // tener que llamarla a cada ciclo
    for (long int i = 0; i < lng; i++) {
        sep_elegido =
            i == 0 ? ""
                   : sep; // si i es igual a 0, no ingresará nada, en cambio,
        lat_objeto *tmp1 =
            latL_obtener_elemento(mv, lst, i); // obtengo el elemento
        if (tmp1->tipo == T_STR) {             // si es cadena...
            mem += strlen(latC_checar_cadena(mv, tmp1)) +
                   1; // aumentaré el valor de la memoria a la longitud de la
                      // cadena + 1
            texto = realloc(
                texto, mem); // asigno la memoria nuevamente sin borrar su valor
            sprintf(texto, "%s%s%s", texto, sep_elegido,
                    latC_checar_cadena(
                        mv, tmp1)); // imprimo el contenido que ya tiene texto
                                    // en su misma variable con el separador
        } else if (tmp1->tipo == T_NUMERIC) {
            sprintf(texto, "%s%s%.16g", texto, sep_elegido,
                    latC_checar_numerico(
                        mv, tmp1)); // si es número, no reservo más memoria y
                                    // sigo metiendo el valor
        }
    }
    if (*texto == '\0') { // ahora regreso al valor de texto, y lo comparo con
                          // el primer valor que asigne, si es nulo...
        latC_apilar(mv, latO_nulo); // retorna nulo.
    } else {
        latC_apilar_string(mv, texto); // sino, la lista concatenada
    }
    free(texto);
}

static const lat_CReg liblist[] = {
    {"invertir", lista_invertir, 1},
    {"agregar", lista_agregar, 2},
    {"extender", lista_extender, 2},
    {"eliminar_indice", lista_eliminar_indice, 2},
    {"longitud", lista_longitud, 1},
    {"indice", lista_indice, 2},
    {"encontrar", lista_indice, 2},
    {"comparar", lista_comparar, 2},
    {"insertar", lista_insertar, 3},
    {"eliminar", lista_eliminar, 2},
    {"contiene", lista_contiene, 2},
    {"concatenar", lista_concatenar, 2},
    {"crear", lista_crear, 1},
    {"separar", lista_separar, 2},
    {NULL, NULL}};

void latC_abrir_liblatino_listlib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_LISTA_NAME, liblist);
}
