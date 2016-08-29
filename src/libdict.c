#include <string.h>

#include "liblist.h"
#include "libdict.h"
#include "libmem.h"

hash_map* __dic_crear()
{
    hash_map* ret = (hash_map*)__memoria_asignar(sizeof(hash_map));
    int c;
    for (c = 0; c < 256; c++)
    {
        ret->buckets[c] = NULL;
    }
    return ret;
}

int __dic_hash(char* key)
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
        if (strcmp(key, ((hash_val *)cur->valor)->key) == 0){
            return ((hash_val *)cur->valor)->val;
        }
    }
    return NULL;
}

void __dic_asignar(hash_map *m, char *key, void *val)
{
    //printf("__dic_asignar\n");
    hash_val *hv = (hash_val *)__memoria_asignar(sizeof(hash_val));
    strncpy(hv->key, key, (strlen(key) + 1));
    hv->val = val;    
    int hk = __dic_hash(key);
    if (m->buckets[hk] == NULL)
    {        
        m->buckets[hk] = __lista_crear();                
    }
    else
    {
        lista *list = m->buckets[hk];
        LIST_FOREACH(list, primero, siguiente, cur) {
            if (strcmp(((hash_val *)cur->valor)->key, key) == 0)
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
                __dic_asignar(ret, ((hash_val *) cur->valor)->key, ((hash_val *) cur->valor)->val);
            }
        }        
        }
    }
    return ret;
}