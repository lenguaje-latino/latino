/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gc.h"
#include "vm.h"
#include "object.h"
#include "liblist.h"
#include "libmem.h"

void __colector_agregar(lat_mv* vm, lat_objeto* o){
#if HABILITAR_GC
    //TIME_THIS(__colector_limpiar(vm));
    __colector_limpiar(vm);
    o->marca = 0;
    __lista_apilar(lat_obtener_lista(vm->gc_objetos), (void*)o);    
#endif
}

void __colector_limpiar(lat_mv* vm){        
    if(vm->memoria_usada > MAX_VIRTUAL_MEMORY 
            && (vm->memoria_usada / MAX_VIRTUAL_MEMORY > 0.25)){        
        //printf("recolectando basura:\t");
        lista* list = lat_obtener_lista(vm->gc_objetos);          
        /*clock_t t_ini, t_fin;
        double secs;
        t_ini = clock();*/
        //Simple garbage collector        
        int i;
        //printf("__lista_longitud: %i\n", __lista_longitud(list));
        for(i = 0; i < __lista_longitud(list); i++){
            //TIME_THIS(__lista_obtener_elemento(list, i))
            lat_objeto* tmp = __lista_obtener_elemento(list, i);    //FIX
            if(tmp->marca > 3){                                
                lista_nodo *nt = __lista_obtener_nodo(list, i);     //FIX
                //TIME_THIS(__lista_eliminar_elemento(list, nt))                
                lat_objeto *el = (lat_objeto *)__lista_eliminar_elemento(list, nt);
                vm->memoria_usada -= __memoria_tamanio(el);
                lat_eliminar_objeto(vm, el);        
                
            }else{
                tmp->marca++;
            }
        }
        /*t_fin = clock();
        secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
        printf("%.16g milisegundos\n", secs * 1000.0);*/
        //printf("__lista_longitud: %i\n", __lista_longitud(list));
    }
}