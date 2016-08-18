#include "liblist.h"
#include "libdict.h"
#include "libmem.h"

hash_map* __dic_nuevo()
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
	  list_node* cur = m->buckets[__dic_hash(key)];
    if (cur == NULL)
        return NULL;
    for (; cur->next != NULL; cur = cur->next)
    {
        if (cur->data != NULL)
        {
            if (strcmp(key, ((hash_val *)cur->data)->key) == 0)
            {
                return ((hash_val *)cur->data)->val;
            }
        }
    }
    return NULL;
}

void __dic_asignar(hash_map *m, char *key, void *val)
{
    hash_val *hv = (hash_val *)__memoria_asignar(sizeof(hash_val));
    strncpy(hv->key, key, (strlen(key) + 1));
    hv->val = val;
	int hk = __dic_hash(key);
    if (m->buckets[hk] == NULL)
    {
        m->buckets[hk] = __lista_nuevo();
    }
    else
    {
        list_node *c;
        for (c = m->buckets[hk]; c->next != NULL; c = c->next)
        {
            if (c->data != NULL)
            {
                if (strcmp(((hash_val *)c->data)->key, key) == 0)
                {
                    free(c->data);
                    c->data = (void *)hv;
                    return;
                }
            }
        }
    }
    __lista_agregar(m->buckets[hk], (void *)hv);
}

hash_map* __dic_clonar(hash_map *m)
{
    hash_map *ret = __dic_nuevo();
    int i;
    for (i = 0; i < 256; i++)
    {
        list_node *c = m->buckets[i];
        if (c != NULL)
        {
            for (; c->next != NULL; c = c->next)
            {
                if (c->data != NULL)
                {
					__dic_asignar(ret, ((hash_val *) c->data)->key, ((hash_val *) c->data)->val);
                }
            }
        }
    }
    return ret;
}
