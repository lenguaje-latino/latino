#include "liblist.h"
#include "latino.h"
#include "libmem.h"

lista *__lista_crear()
{ 
    //printf("__lista_crear\n");
    return __memoria_asignar(sizeof(lista));
}

void __lista_destruir(lista *list)
{
    LIST_FOREACH(list, primero, siguiente, cur) {
        if(cur->anterior) {
            __memoria_liberar(cur->anterior);
        }
    }
    __memoria_liberar(list->ultimo);
    __memoria_liberar(list);
}

void __lista_limpiar(lista *list)
{
    LIST_FOREACH(list, primero, siguiente, cur) {
        __memoria_liberar(cur->valor);
    }
}

void __lista_limpiar_destruir(lista *list)
{
    __lista_limpiar(list);
    __lista_destruir(list);
}

void __lista_apilar(lista *list, void *value)
{    
    lista_nodo *node = __memoria_asignar(sizeof(lista_nodo));
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
}

void *__lista_desapilar(lista *list)
{
    lista_nodo *node = list->ultimo;
    return node != NULL ? __lista_eliminar_elemento(list, node) : NULL;
}

void __lista_insertar_inicio(lista *list, void *value)
{
    lista_nodo *node = __memoria_asignar(sizeof(lista_nodo));
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
    __memoria_liberar(node);
    return result;
}

int __lista_contiene_valor(lista* list, void* data)
{
    LIST_FOREACH(list, primero, siguiente, cur) {
        //if (memcmp(cur->valor, data, sizeof(cur->valor)) == 0)
        if (memcmp(cur->valor, data, __memoria_tamanio(cur->valor)) == 0)
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
        char* str = __objeto_a_cadena(o);
        if(o->tipo == T_LIST && !__str_termina_con(valor, "[")){
            strcat(valor, "\n");
        }            
        strcat(valor, str);
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

int __objeto_comparar(lat_objeto* lhs, lat_objeto* rhs){
    int res = 1;
    if(lhs->tipo != rhs->tipo){
        res = strcmp(__objeto_a_cadena(lhs), __objeto_a_cadena(rhs));
        goto RESPUESTA;
    }
    if(lhs->tipo == T_BOOL){
        res = lat_obtener_logico(lhs) - lat_obtener_logico(rhs);
        goto RESPUESTA;
    }
    if(lhs->tipo == T_NUMERIC){
        res = lat_obtener_decimal(lhs) - lat_obtener_decimal(rhs);
        goto RESPUESTA;
    }
    if(lhs->tipo == T_STR){
        res = strcmp(lat_obtener_cadena(lhs), lat_obtener_cadena(rhs));
        goto RESPUESTA;
    }
    if(lhs->tipo == T_LIST){
        res = __lista_comparar(lat_obtener_lista(lhs), lat_obtener_lista(rhs));
        goto RESPUESTA;
    }   
RESPUESTA:    
    if(res < 0){
        return -1;
    }
    if(res > 0){
        return 1;
    }
    return res;
}

int __lista_comparar(lista* lhs, lista*rhs){
    int res = 0;
    int len1 = __lista_longitud(lhs);
    int len2 = __lista_longitud(rhs);
    if(len1 < len2){
        return -1;
    }
    if(len1 > len2){
        return 1;
    }
    int i;    
    for(i=0; i < len1; i++){
        lat_objeto* tmp1 =  __lista_obtener_elemento(lhs, i);
        lat_objeto* tmp2 =  __lista_obtener_elemento(rhs, i);
        res = __objeto_comparar(tmp1, tmp2);
        if(res < 0){
            return -1;
        }
        if(res > 0){
            return 1;
        }
    }
    return res;
}

void __lista_extender(lista* list1, lista* list2){
    LIST_FOREACH(list2, primero, siguiente, cur) {
        __lista_apilar(list1, cur->valor);
    } 
}