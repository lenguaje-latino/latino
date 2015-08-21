#include <stdlib.h>
#include <string.h>
#include "latino.h"

#include "lmem.h"
#include "llist.h"

#include <stdio.h>

void list_new(list *list, int elementSize, freeFunction freeFn)
{
    lassert(elementSize > 0);
    list->logicalLength = 0;
    list->elementSize = elementSize;
    list->first = list->last = NULL;
    list->freeFn = freeFn;
}

void list_destroy(list *list)
{
    /*printf("%s\n", "begin list destroy");*/
    listNode *current;
    while (list->first != NULL) {
        current = list->first;
        list->first = current->next;
        if (list->freeFn) {
            list->freeFn(current->data);
        }
        lfree(current->data);
        lfree(current);
    }
    /*printf("%s\n", "end list destroy");*/
}

void list_append(list *list, void *element)
{
    listNode *node = lmalloc(sizeof(listNode));
    node->data = lmalloc(list->elementSize);
    node->next = NULL;
    memcpy(node->data, element, list->elementSize);
    if (list->logicalLength == 0) {
        list->first = list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    list->logicalLength++;
}

void list_push(list *list, void *element)
{
    listNode *node = lmalloc(sizeof(listNode));
    node->data = lmalloc(list->elementSize);
    memcpy(node->data, element, list->elementSize);
    node->next = list->first;
    list->first = node;
    // first node?
    if (!list->last) {
        list->last = list->first;
    }
    list->logicalLength++;
}

void list_nth(list *list, int nth, void *element)
{
    /*printf("%s\n", "begin list nth");*/
    lassert(list->logicalLength > 0);
    if (nth < 0) {
        if ((list->logicalLength + nth - 1) > 0)
            nth = list->logicalLength + nth - 1;
    }
    if (nth >= list->logicalLength) {
        nth = list->logicalLength - 1;
    }
    if (nth >= 0) {
        listNode *current = list->first;
        int i;
        for (i = 0; i < nth; i++) {
            current = current->next;
        }
        memcpy(element, current->data, list->elementSize);
    }
    /*printf("%s\n", "end list nth");*/
}

void list_first(list *list, void *element, bool removeFromList)
{
    lassert(list->first != NULL);
    listNode *node = list->first;
    memcpy(element, node->data, list->elementSize);
    if (removeFromList) {
        list->first = node->next;
        list->logicalLength--;
        lfree(node->data);
        lfree(node);
    }
}

void list_last(list *list, void *element)
{
    lassert(list->last != NULL);
    listNode *node = list->last;
    memcpy(element, node->data, list->elementSize);
}

void list_rest(list *lst, list *rest)
{
    lassert(lst != NULL);
    lassert(rest != NULL);
    listNode *node = lst->first;
    memcpy(rest, lst, sizeof(list));
    rest->first = node->next;
    /*rest->freeFn = lst->freeFn;*/
    rest->logicalLength--;
}

int list_length(list *list)
{
    return list->logicalLength;
}

