#include <stdio.h>
#include <string.h>

#include "liblist.h"
#include "libdict.h"
#include "libmem.h"
#include "latino.h"

hash_map* __dic_crear()
{
    //printf("__dic_crear\n");
    hash_map* ret = (hash_map*)__memoria_asignar(sizeof(hash_map));
    int c;
    for (c = 0; c < 256; c++)
    {
        ret->buckets[c] = NULL;
    }
    return ret;
}

void __dic_destruir(hash_map *dic)
{    
    int i;
    for (i = 0; i < 256; i++)
    {
        lista *list = dic->buckets[i];
        if(list != NULL){
            __lista_limpiar_destruir(list);
        }
    }
    __memoria_liberar(dic);
}

int __dic_hash(const char* key)
{
    int h = 5381;
    unsigned char c;
    for (c = *key; c != '\0'; c = *++key)
        h = h * 33 + c;
    return abs(h % 256);
}

void* __dic_obtener(hash_map* m, char* key)
{
    lista* list = m->buckets[__dic_hash(key)];
    if (list == NULL)
        return NULL;
    LIST_FOREACH(list, primero, siguiente, cur) {
        if (strcmp(key, ((hash_val *)cur->valor)->llave) == 0){
            return ((hash_val *)cur->valor)->valor;
        }
    }
    return NULL;
}

void __dic_asignar(hash_map *m, const char *key, void *val)
{    
    //printf("__dic_asignar\n");
    hash_val *hv = (hash_val *)__memoria_asignar(sizeof(hash_val));
    strncpy(hv->llave, key, (strlen(key) + 1));
    hv->valor = val;    
    int hk = __dic_hash(key);
    if (m->buckets[hk] == NULL)
    {        
        m->buckets[hk] = __lista_crear();                
    }
    else
    {
        lista *list = m->buckets[hk];
        LIST_FOREACH(list, primero, siguiente, cur) {
            if (strcmp(((hash_val *)cur->valor)->llave, key) == 0)
            {
                __memoria_liberar(cur->valor);
                cur->valor = (void *)hv;
                return;
            }
        }
    }    
    __lista_apilar(m->buckets[hk], (void *)hv);
}

hash_map* __dic_clonar(hash_map *m)
{
    hash_map *ret = __dic_crear();
    int i;
    for (i = 0; i < 256; i++)
    {
        lista *list = m->buckets[i];
        if(list != NULL){
            LIST_FOREACH(list, primero, siguiente, cur) {
                if (cur->valor != NULL)
                {
                    __dic_asignar(ret, ((hash_val *) cur->valor)->llave, ((hash_val *) cur->valor)->valor);
                }
            }        
        }
    }
    return ret;
}

char* __dic_a_cadena(hash_map* m){
    char* valor = __memoria_asignar(MAX_STR_LENGTH);    
    strcat(valor, "{\n");
    int i;
    for (i = 0; i < 256; i++)
    {
        lista *list = m->buckets[i];
        if(list != NULL){
            LIST_FOREACH(list, primero, siguiente, cur) {
                if (cur->valor != NULL)
                {                    
                    strcat(valor, "\t\"");
                    strcat(valor, ((hash_val *) cur->valor)->llave);
                    strcat(valor, "\"");
                    lat_objeto* val = (lat_objeto*)((hash_val *) cur->valor)->valor;                    
                    strcat(valor, ": "); 
                    if (val == NULL){
                            strcat(valor, "\"nulo\"");
                    }
                    else {
                            if (val->tipo == T_STR){
                                    if (strstr(__cadena(val), "\"") != NULL){
                                            strcat(valor, "'");
                                    }
                                    else{
                                            strcat(valor, "\"");
                                    }
                            }
                            strcat(valor, __objeto_a_cadena(val));
                            if (val->tipo == T_STR){
                                    if (strstr(__cadena(val), "\"") != NULL){
                                            strcat(valor, "'");
                                    }
                                    else{
                                            strcat(valor, "\"");
                                    }
                            }
                    }
                    strcat(valor, ",\n");
                }
            }
        }
    }
    strcat(valor, "}");
    valor = __str_reemplazar(valor, ",\n}", "\n}\n");    //elimina la ultima coma
	valor[strlen(valor)] = '\0';
    __memoria_reasignar(valor, strlen(valor)+1);
    return valor;
}

int __dic_longitud(hash_map* m){
    int cant = 0;
    int i;
    for (i = 0; i < 256; i++){
        lista *list = m->buckets[i];
        if(list != NULL){
            LIST_FOREACH(list, primero, siguiente, cur) {
                if (cur->valor != NULL)
                {
                    cant++;                    
                }
            }
        }        
    }    
    return cant;
}