#include "liblist.h"
#include "latino.h"

void lat_agregar(lat_vm *vm){
    lat_objeto *elem = lat_desapilar(vm);
    lat_objeto *lst = lat_desapilar(vm);
    list_node *actual = lst->data.lista;
    /*vamos al nodo final para agregar el elemento*/
    while(actual->next != NULL){
        actual = actual->next;
    }
    insert_list(actual, elem);
}
