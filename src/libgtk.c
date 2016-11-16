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
void lat_gtk(lat_mv *mv)
{
	GtkWidget * ventana;
	//le paso vacios los parametros requeridos
	int argc;
	char **argv;
	gtk_init (&argc, &argv);
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow *) ventana, "Hola mundo");
	gtk_widget_show(ventana);
	gtk_main();
}

static const lat_CReg lib_gtk[] = {{"test", lat_gtk, 0},
                                    {NULL, NULL}};

void lat_importar_lib_gtk(lat_mv *mv) {
  lat_importar_lib(mv, LIB_GTK_NAME, lib_gtk);
}
