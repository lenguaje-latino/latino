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

#include <gtk/gtk.h>

#include "latino.h"

#define LIB_GTK_NAME "gtk"

struct string {
    char *ptr;
    size_t len;
};

// toda fun de latino necesita esta firma -> void nombrefuncion(lat_mv *mv)

static void gtkiniciar(lat_mv *mv) {
    // le paso nulos los params requeridos
    gtk_init(NULL, NULL);
}

static void gtkventana(lat_mv *mv) {
    GtkWidget *ventana;
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    lat_objeto *cref = latC_crear_cdato(mv, ventana);
    latC_apilar(mv, cref);
}

static void gtktitulo(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    gtk_window_set_title((GtkWindow *)latC_checar_cptr(mv, a),
                         latC_checar_cadena(mv, b));
}

static void gtkredimensionar(lat_mv *mv) {
    lat_objeto *y = latC_desapilar(mv);
    lat_objeto *x = latC_desapilar(mv);
    lat_objeto *ventana = latC_desapilar(mv);
    gtk_window_set_default_size(GTK_WINDOW(latC_checar_cptr(ventana)),
                                latC_checar_numerico(mv, x),
                                latC_checar_numerico(mv, y));
}

static void gtkmostrar_todo(lat_mv *mv) {
    lat_objeto *ventana = latC_desapilar(mv);
    gtk_widget_show_all(latC_checar_cptr(ventana));
}

static void gtkmenu(lat_mv *mv) { gtk_main(); }

static void gtkcrear_caja(lat_mv *mv) {
    GtkWidget *caja_boton;
    caja_boton = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    lat_objeto *cref = latC_crear_cdato(mv, caja_boton);
    latC_apilar(mv, cref);
}

static void gtkboton_texto(lat_mv *mv) {
    lat_objeto *texto = latC_desapilar(mv);
    lat_objeto *caja_boton = latC_desapilar(mv);
    lat_objeto *ventana = latC_desapilar(mv);
    UNUSED(caja_boton);
    UNUSED(ventana);
    GtkWidget *boton;
    boton = gtk_button_new_with_label(latC_checar_cadena(mv, texto));
    lat_objeto *cref = latC_crear_cdato(mv, boton);
    latC_apilar(mv, cref);
}

static void gtkagregar(lat_mv *mv) {
    lat_objeto *b = latC_desapilar(mv);
    lat_objeto *a = latC_desapilar(mv);
    gtk_container_add(GTK_CONTAINER(latC_checar_cptr(a)),
                      latC_checar_cptr(b));
}

static void gtkboton_destruir(lat_mv *mv) {
    lat_objeto *boton = latC_desapilar(mv);
    lat_objeto *ventana = latC_desapilar(mv);
    g_signal_connect_swapped(latC_checar_cptr(boton), "clicked",
                             G_CALLBACK(gtk_widget_destroy),
                             latC_checar_cptr(ventana));
}

static void gtkllamar_funcion(lat_mv *mv) {
    lat_objeto *fun = latC_desapilar(mv);
    lat_objeto *boton = latC_desapilar(mv);
    g_signal_connect_swapped(latC_checar_cptr(boton), "clicked",
                             G_CALLBACK(latC_checar_cptr(fun)), NULL);
}

static const lat_CReg libgtk[] = {{"iniciar", gtkiniciar, 0},
                                  {"menu", gtkmenu, 0},
                                  {"ventanaNueva", gtkventana, 1},
                                  {"titulo", gtktitulo, 2},
                                  {"mostrarTodo", gtkmostrar_todo, 1},
                                  {"cajaNueva", gtkcrear_caja, 0},
                                  {"agregar", gtkagregar, 2},
                                  {"ventanaMagnitud", gtkredimensionar, 3},
                                  {"botonTexto", gtkboton_texto, 3},
                                  {"botonDestruir", gtkboton_destruir, 2},
                                  {"llamarFuncion", gtkllamar_funcion, 2},
                                  {NULL, NULL}};

void latC_abrir_liblatino_gtklib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_GTK_NAME, libgtk);
}
