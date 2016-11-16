/*
The MIT License (MIT)

Copyright (c) 2015 - 2016. Latino

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

#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latmv.h"
#include "latobj.h"

void lat_gc_agregar(lat_mv *mv, lat_objeto *o) {
#if HABILITAR_GC
  // TIME_THIS(__colector_limpiar(vm));
  lat_gc_limpiar(mv);
#endif
  o->marca = 1;
  __lista_agregar(__lista(mv->gc_objetos), o);
}

// Simple garbage collector
void lat_gc_limpiar(lat_mv *mv) {
  if (mv->memoria_usada > MAX_VIRTUAL_MEMORY &&
      (mv->memoria_usada / MAX_VIRTUAL_MEMORY > 0.25)) {    
    lista *list = __lista(mv->gc_objetos);
    /*
    printf("recolectando basura:\t");
    clock_t t_ini, t_fin;
    double secs;
    t_ini = clock();*/
    int i;
    // printf("__lista_longitud: %i\n", __lista_longitud(list));
    for (i = 0; i < __lista_longitud(list); i++) {
      // TIME_THIS(__lista_obtener_elemento(list, i))
      lat_objeto *tmp = __lista_obtener_elemento(list, i);
      if (tmp->marca && tmp->num_ref <= 0) {
        lista_nodo *nt = __lista_obtener_nodo(list, i);
        // TIME_THIS(__lista_eliminar_elemento(list, nt))
        lat_objeto *el = (lat_objeto *)__lista_eliminar_elemento(list, nt);
        // vm->memoria_usada -= __memoria_tamanio(el);
        /*printf("collectando objeto:\t");
        __imprimir_objeto(vm, el, false);
        printf("\n");*/
        __obj_eliminar(mv, el);
      }
    }
    /*t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    printf("%.2g milisegundos\n", secs * 1000.0);
    */
    // printf("__lista_longitud: %i\n", __lista_longitud(list));
  }
}
