#include "latino.h"
#include "ast.h"
#include "utils.h"

char *strdup0(char *s)
{
    size_t len = strlen(s);
    char *p;
    p = (char *)malloc(len + 1);
    if (p) {
        strncpy(p, s, len);
    }
    p[len] = '\0';
    return p;
}

char *strndup0(const unsigned char *s, size_t n)
{
    size_t i;
    char *p = s;
    char *new;
    for (i = 0; i < n && *p; i++, p++)
        ;
    new = (char *) malloc(i + 1);
    if (new) {
        memcpy(new, s, i);
        new[i] = '\0';
    }
    return new;
}

char *concat(char *s1, char *s2)
{
    char *s3 = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

char *int2str(long i)
{
    char s[255];
    char *r = malloc(strlen(s) + 1);
    lnsprintf(s, 255, "%ld", i);
    strcpy(r, s);
    return r;
}

char *double2str(double d)
{
    char s[64];
    char *r = malloc(strlen(s) + 1);
    lnsprintf(s, 64, "%g", (float)d);
    strcpy(r, s);
    return r;
}

char *char2str(char c)
{
    char s[2];
    char *r = malloc(2);
    lnsprintf(s, 2, "%c", c);
    strcpy(r, s);
    return r;
}

char *bool2str(int i)
{
    char s[10];
    char *r = malloc(11);
    if (i) {
        lnsprintf(s, 10, "%s", "verdadero");
        strcpy(r, s);
    } else {
        lnsprintf(s, 10, "%s", "falso");
        strcpy(r, s);
    }
    return r;
}

list_node *make_list_node(void *d)
{
	list_node *ret = (list_node *)malloc(sizeof(list_node));
	ret->data = d;
	return ret;
}

list_node *make_list()
{
	list_node *start = (list_node *)malloc(sizeof(list_node));
	list_node *end = (list_node *)malloc(sizeof(list_node));
	start->prev = NULL;
	start->next = end;
	start->data = NULL;
	end->prev = start;
	end->next = NULL;
	end->data = NULL;
	return start;
}

int find_list(list_node *l, void *data)
{
	list_node *c;
	for (c = l; c->next != NULL; c = c->next) {
		if (c->data == data) {
			return 1;
		}
	}
	return 0;
}

void insert_list(list_node *l, void *data)
{
	list_node *ins = (list_node *)malloc(sizeof(list_node));
	ins->data = data;
	ins->next = l->next;
	l->next = ins;
	ins->next->prev = ins;
	ins->prev = l;
}

void remove_list(list_node *l, void *data)
{
	list_node *c;
	for (c = l; c->next != NULL; c = c->next) {
		if (c->data == data) {
			c->prev->next = c->next;
			c->next->prev = c->prev;
		}
	}
}

int length_list(list_node *l)
{
	int a = 0;
	list_node *c;
	for (c = l; c->next != NULL; c = c->next) {
		if (c->data != NULL) {
			a++;
		}
	}
	return a;
}

hash_map *make_hash_map()
{
	hash_map *ret = (hash_map *)malloc(sizeof(hash_map));
	int c;
	for (c = 0; c < 256; c++) {
		ret->buckets[c] = NULL;
	}
	return ret;
}

int hash(char *key)
{
	int h = 5381;

	unsigned char c;
	for (c = *key; c != '\0'; c = *++key)
		h = h * 33 + c;

	return abs(h % 256);
}

void *get_hash(hash_map *m, char *key)
{
	list_node *cur = m->buckets[hash(key)];
	if (cur == NULL) return NULL;
	for (; cur->next != NULL; cur = cur->next) {
		if (cur->data != NULL) {
			if (strcmp(key, ((hash_val *)cur->data)->key) == 0) {
				return ((hash_val *)cur->data)->val;
			}
		}
	}
	return NULL;
}

void set_hash(hash_map *m, char *key, void *val)
{
	hash_val *hv = (hash_val *)malloc(sizeof(hash_val));
	strcpy(hv->key, key);
	hv->val = val;
	int hk = hash(key);
	if (m->buckets[hk] == NULL) {
		m->buckets[hk] = make_list();
	}
	else {
		list_node *c;
		for (c = m->buckets[hk]; c->next != NULL; c = c->next) {
			if (c->data != NULL) {
				if (strcmp(((hash_val *)c->data)->key, key) == 0) {
					free(c->data);
					c->data = (void *)hv;
					return;
				}
			}
		}
	}
	insert_list(m->buckets[hk], (void *)hv);
}

hash_map *copy_hash(hash_map *m)
{
	hash_map *ret = make_hash_map();
	int i;
	for (i = 0; i < 256; i++) {
		list_node *c = m->buckets[i];
		if (c != NULL) {
			for (; c->next != NULL; c = c->next) {
				if (c->data != NULL) {
					set_hash(ret, ((hash_val *)c->data)->key, ((hash_val *)c->data)->val);
				}
			}
		}
	}
	return ret;
}