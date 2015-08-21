#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdbool.h>
// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);

typedef struct _listNode {
    void *data;
    struct _listNode *next;
} listNode;

typedef struct {
    int logicalLength;
    int elementSize;
    listNode *first;
    listNode *last;
    freeFunction freeFn;
} list;

void list_new(list *list, int elementSize, freeFunction freeFn);
void list_destroy(list *list);

int list_length(list *list);
void list_nth(list *list, int nth, void *element);
void list_append(list *list, void *element);
void list_push(list *list, void *element);

void list_first(list *list, void *element, bool removeFromList);
void list_last(list *list, void *element);

void list_rest(list *lst, list *rest);
#endif /*_LLIST_H_*/

