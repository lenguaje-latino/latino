#include "liblist.h"
#include "latino.h"
#include "libmem.h"

lista *__lista_crear()
{
    return calloc(1, sizeof(lista));
}

void __lista_destruir(lista *list)
{
    LIST_FOREACH(list, primero, siguiente, cur) {
        if(cur->anterior) {
            free(cur->anterior);
        }
    }
    free(list->ultimo);
    free(list);
}

void __lista_limpiar(lista *list)
{
    LIST_FOREACH(list, primero, siguiente, cur) {
        free(cur->valor);
    }
}

void __lista_limpiar_destruir(lista *list)
{
    __lista_limpiar(list);
    __lista_destruir(list);
}

void __lista_apilar(lista *list, void *value)
{
    lista_nodo *node = calloc(1, sizeof(lista_nodo));
    //check_mem(node);
    node->valor = value;
    if(list->ultimo == NULL) {
        list->primero = node;
        list->ultimo = node;
    } else {
        list->ultimo->siguiente = node;
        node->anterior = list->ultimo;
        list->ultimo = node;
    }
    list->longitud++;
//error:
//    return;
}

void *__lista_desapilar(lista *list)
{
    lista_nodo *node = list->ultimo;
    return node != NULL ? __lista_eliminar_elemento(list, node) : NULL;
}

void __lista_insertar_inicio(lista *list, void *value)
{
    lista_nodo *node = calloc(1, sizeof(lista_nodo));
    //check_mem(node);
    node->valor = value;
    if(list->primero == NULL) {
        list->primero = node;
        list->ultimo = node;
    } else {
        node->siguiente = list->primero;
        list->primero->anterior = node;
        list->primero = node;
    }
    list->longitud++;
//error:
//    return;
}

void *__lista_extraer_inicio(lista *list)
{
    lista_nodo *node = list->primero;
    return node != NULL ? __lista_eliminar_elemento(list, node) : NULL;
}

void *__lista_eliminar_elemento(lista *list, lista_nodo *node)
{
    void *result = NULL;
    if(node == list->primero && node == list->ultimo) {
        list->primero = NULL;
        list->ultimo = NULL;
    } else if(node == list->primero) {
        list->primero = node->siguiente;
        list->primero->anterior = NULL;
    } else if (node == list->ultimo) {
        list->ultimo = node->anterior;
        list->ultimo->siguiente = NULL;
    } else {
        lista_nodo *after = node->siguiente;
        lista_nodo *before = node->anterior;
        after->anterior = before;
        before->siguiente = after;
    }
    list->longitud--;
    result = node->valor;
    free(node);

//error:
    return result;
}

int __lista_contiene_valor(lista* list, void* data)
{
    LIST_FOREACH(list, primero, siguiente, cur) {
        if (memcmp(cur->valor, data, sizeof(data)) == 0)
        {
            return 1;
        }
    }
    return 0;
}

char* __lista_a_cadena(lista* list)
{
    char* valor = __memoria_asignar(MAX_STR_LENGTH);    
    strcat(valor, "[");
    LIST_FOREACH(list, primero, siguiente, cur) {
        lat_objeto* o = ((lat_objeto*)cur->valor);
        strcat(valor, __objeto_a_cadena(o));
        if(cur != list->ultimo){
            strcat(valor, ",");
        }
    }
    strcat(valor, "]");
    __memoria_reasignar(valor, strlen(valor));
    return valor;
}

void __lista_modificar_elemento(lista* list, void* data, int pos)
{
    int i = 0;
    if (pos < 0 || pos >= __lista_longitud(list))
    {
        lat_fatal_error("Indice fuera de rango");
    }
    LIST_FOREACH(list, primero, siguiente, cur) {
        if (i == pos)
        {
            cur->valor = data;
        }
        i++;
    }    
}
