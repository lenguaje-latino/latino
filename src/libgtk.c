#include <gtk/gtk.h>
#define LIB_GTK_NAME "gtk"

struct string {
  char *ptr;
  size_t len;
};

void lat_gtk(int argc, char * argv[])
{
	GtkWidget * ventana;
	gtk_init (&argc, &argv);
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow *) ventana, "Hola mundo");
	gtk_widget_show(ventana);

	gtk_main();
	return 0;
}

static const lat_CReg lib_gtk[] = {{"test", lat_gtk, 0},
                                    {NULL, NULL}};

void lat_importar_lib_gtk(lat_mv *mv) {
  lat_importar_lib(mv, LIB_GTK_NAME, lib_gtk);
}
