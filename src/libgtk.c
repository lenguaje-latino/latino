#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
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

//toda funcion de latino necesita esta firma -> void nombre_funcion(lat_mv *mv)
void lat_gtk_iniciar(lat_mv *mv)
{
	//le paso vacios los parametros requeridos
	int argc;
	char **argv;
	gtk_init (&argc, &argv);
}

void lat_gtk_ventana(lat_mv *mv)
{
	GtkWidget * ventana;
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	lat_objeto *cref = lat_cdato_nuevo(mv, ventana);
  	lat_apilar(mv, cref);
}

void lat_gtk_titulo(lat_mv *mv)
{
	lat_objeto *b = lat_desapilar(mv);
	lat_objeto *a = lat_desapilar(mv);
	gtk_window_set_title((GtkWindow *) __cdato(a), __cadena(b));
}

void lat_gtk_redimensionar(lat_mv *mv)
{
	lat_objeto *y = lat_desapilar(mv);
	lat_objeto *x = lat_desapilar(mv);
	lat_objeto *ventana = lat_desapilar(mv);
	gtk_window_set_default_size (GTK_WINDOW (__cdato(ventana)), __numerico(x), __numerico(y));
}

void lat_gtk_mostrar(lat_mv *mv)
{
	lat_objeto *ventana = lat_desapilar(mv);
	gtk_widget_show_all (__cdato(ventana));
}

void lat_gtk_menu(lat_mv *mv)
{
	gtk_main();
}

void lat_gtk_boton_texto(lat_mv *mv)
{
	lat_objeto *texto = lat_desapilar(mv);
	lat_objeto *ventana = lat_desapilar(mv);
	GtkWidget *boton, *caja_boton;
	caja_boton = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	gtk_container_add (GTK_CONTAINER (__cdato(ventana)), caja_boton);
	boton = gtk_button_new_with_label (__cadena(texto));
	gtk_container_add (GTK_CONTAINER (caja_boton), boton);
	lat_objeto *cref = lat_cdato_nuevo(mv, boton);
  	lat_apilar(mv, cref);
	
	
}

void lat_gtk_boton_destruir(lat_mv *mv)
{
	lat_objeto *boton = lat_desapilar(mv);
	lat_objeto *ventana = lat_desapilar(mv);
	g_signal_connect_swapped (__cdato(boton), "clicked", G_CALLBACK (gtk_widget_destroy), __cdato(ventana));
}

void lat_gtk_llamar_funcion(lat_mv *mv)
{
	lat_objeto *funcion = lat_desapilar(mv);
	lat_objeto *boton = lat_desapilar(mv);
	g_signal_connect_swapped (__cdato(boton), "clicked", G_CALLBACK (__cdato(funcion)), NULL);
}

static const lat_CReg lib_gtk[] = {{"iniciar", lat_gtk_iniciar, 0},
				   {"menu", lat_gtk_menu, 0},
				   {"ventana", lat_gtk_ventana, 1},
				   {"titulo", lat_gtk_titulo, 2},
				   {"mostrar", lat_gtk_mostrar, 1},
				   {"redimensionar", lat_gtk_redimensionar, 3},
				   {"boton_texto", lat_gtk_boton_texto, 2},
				   {"boton_destruir", lat_gtk_boton_destruir, 2},
				   {"llamar_funcion", lat_gtk_llamar_funcion, 2},
                                    {NULL, NULL}};

void lat_importar_lib_gtk(lat_mv *mv) {
  lat_importar_lib(mv, LIB_GTK_NAME, lib_gtk);
}
