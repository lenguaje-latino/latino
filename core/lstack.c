#include <stdlib.h>

#include "latino.h"
#include "lstack.h"

void stack_new(stack *s, int elementSize, freeFunction freeFn)
{
    s->list = malloc(sizeof(list));
    list_new(s->list, elementSize, freeFn);
}

void stack_destroy(stack *s)
{
    list_destroy(s->list);
    free(s->list);
}

void stack_push(stack *s, void *element)
{
    list_push(s->list, element);
}

void stack_pop(stack *s, void *element)
{
    // don't pop an empty stack!
    lassert(stack_length(s) > 0);

    list_first(s->list, element, true);
}

void stack_peek(stack *s, void *element)
{
    lassert(stack_size(s) > 0);
    list_first(s->list, element, false);
}

int stack_length(stack *s)
{
    return list_length(s->list);
}

