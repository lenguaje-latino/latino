#include <gtk/gtk.h>
#include <string.h>

#include "latgc.h"
#include "latino.h"
#include "latmem.h"
#include "latmv.h"

#define LIB_GTK_NAME "gtk"

struct string {
	char *ptr;
	size_t len;
};

// toda funcion de latino necesita esta firma -> void nombre_funcion(lat_mv *mv)
void lat_gtk_iniciar(lat_mv * mv) {
	// le paso nulos los parametros requeridos
	gtk_init(NULL, NULL);
}

void lat_gtk_ventana(lat_mv * mv) {
	GtkWidget *ventana;
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	lat_objeto *cref = lat_cdato_nuevo(mv, ventana);
	lat_apilar(mv, cref);
}

void lat_gtk_titulo(lat_mv * mv) {
	lat_objeto *b = lat_desapilar(mv);
	lat_objeto *a = lat_desapilar(mv);
	gtk_window_set_title((GtkWindow *) __cdato(a), __cadena(b));
}

void lat_gtk_redimensionar(lat_mv * mv) {
	lat_objeto *y = lat_desapilar(mv);
	lat_objeto *x = lat_desapilar(mv);
	lat_objeto *ventana = lat_desapilar(mv);
	gtk_window_set_default_size(GTK_WINDOW(__cdato(ventana)), __numerico(x),
								__numerico(y));
}

void lat_gtk_mostrar_todo(lat_mv * mv) {
	lat_objeto *ventana = lat_desapilar(mv);
	gtk_widget_show_all(__cdato(ventana));
}

void lat_gtk_menu(lat_mv * mv) {
	gtk_main();
}

void lat_gtk_nueva_caja(lat_mv * mv) {
	GtkWidget *caja_boton;
	caja_boton = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	lat_objeto *cref = lat_cdato_nuevo(mv, caja_boton);
	lat_apilar(mv, cref);
}

void lat_gtk_boton_texto(lat_mv * mv) {
	lat_objeto *texto = lat_desapilar(mv);
	lat_objeto *caja_boton = lat_desapilar(mv);
	lat_objeto *ventana = lat_desapilar(mv);
	UNUSED(caja_boton);
	UNUSED(ventana);
	GtkWidget *boton;
	boton = gtk_button_new_with_label(__cadena(texto));
	lat_objeto *cref = lat_cdato_nuevo(mv, boton);
	lat_apilar(mv, cref);
}

void lat_gtk_agregar(lat_mv * mv) {
	lat_objeto *b = lat_desapilar(mv);
	lat_objeto *a = lat_desapilar(mv);
	gtk_container_add(GTK_CONTAINER(__cdato(a)), __cdato(b));
}

void lat_gtk_boton_destruir(lat_mv * mv) {
	lat_objeto *boton = lat_desapilar(mv);
	lat_objeto *ventana = lat_desapilar(mv);
	g_signal_connect_swapped(__cdato(boton), "clicked",
							 G_CALLBACK(gtk_widget_destroy), __cdato(ventana));
}

void lat_gtk_llamar_funcion(lat_mv * mv) {
	lat_objeto *funcion = lat_desapilar(mv);
	lat_objeto *boton = lat_desapilar(mv);
	g_signal_connect_swapped(__cdato(boton), "clicked",
							 G_CALLBACK(__cdato(funcion)), NULL);
}

static const lat_CReg lib_gtk[] = {
	{"iniciar", lat_gtk_iniciar, 0},
	{"menu", lat_gtk_menu, 0},
	{"ventanaNueva", lat_gtk_ventana, 1},
	{"titulo", lat_gtk_titulo, 2},
	{"mostrarTodo", lat_gtk_mostrar_todo, 1},
	{"cajaNueva", lat_gtk_nueva_caja, 0},
	{"agregar", lat_gtk_agregar, 2},
	{"ventanaMagnitud", lat_gtk_redimensionar, 3},
	{"botonTexto", lat_gtk_boton_texto, 3},
	{"botonDestruir", lat_gtk_boton_destruir, 2},
	{"llamarFuncion", lat_gtk_llamar_funcion, 2},
	{NULL, NULL}
};

void lat_importar_lib_gtk(lat_mv * mv) {
	lat_importar_lib(mv, LIB_GTK_NAME, lib_gtk);
}
