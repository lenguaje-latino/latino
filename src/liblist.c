#include "liblist.h"
#include "latino.h"

void lat_agregar(lat_vm *vm){
    lat_objeto *elem = lat_desapilar(vm);
    lat_objeto *lst = lat_desapilar(vm);    
    insert_list(lst->data.lista, elem);
    //vm->registros[255] = lat_lista_nueva(vm, lat_clonar_lista(vm, lst->data.lista));
}
