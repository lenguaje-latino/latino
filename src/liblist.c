#include "liblist.h"
#include "latino.h"
#include "libmem.h"

list_node* __lista_nuevo()
{
    list_node* nodo = (list_node*)__memoria_asignar(sizeof(list_node));
    nodo->prev = NULL;
    nodo->next = NULL;
    nodo->data = NULL;
    return nodo;
}

void __lista_agregar(list_node* l, void* data)
{
    list_node *curr = l;
    /*inserta al final de la lista*/
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->data = data;
    curr->next = (list_node*)__memoria_asignar(sizeof(list_node));
    curr->next->prev = curr;
    curr->next->next = NULL;
    curr->next->data = NULL;
}

int __lista_longitud(list_node* l)
{
    int a = 0;    
    list_node* c;
    for (c = l; c->next != NULL; c = c->next)
    {
        if (c->data != NULL)
        {
            a++;
        }
    }
    return a;
}

int __lista_existe_dato(list_node* l, void* data)
{
    list_node* c;
    for (c = l; c->next != NULL; c = c->next)
    {
        if (c->data == data)
        {
            return 1;
        }
    }
    return 0;
}

char* __lista_a_cadena(list_node* l)
{
    char* valor = __memoria_asignar(MAX_STR_LENGTH);    
    strcat(valor, "[");
    if (l != NULL && __lista_longitud(l) > 0)
    {
        list_node* c;
        for (c = l; c != NULL; c = c->next)
        {
            if (c->data != NULL)
            {
                lat_objeto* o = ((lat_objeto*)c->data);
                strcat(valor, __objeto_a_cadena(o));
                if (c->next && c->next->data != NULL)
                {
                    //fprintf(stdout, "%s", ", ");
                    strcat(valor, ",");
                }                
            }
        }
    }    
    strcat(valor, "]");
    return valor;
}

void lat_agregar(lat_vm *vm)
{
    lat_objeto *elem = lat_desapilar(vm);
    lat_objeto *lst = lat_desapilar(vm);
    __lista_agregar(lst->data.lista, elem);
}
