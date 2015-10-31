#ifndef _LIBSTACK_H_
#define _LIBSTACK_H_

#include "liblist.h"

typedef struct {
	list *list;
} stack;

void stack_new(stack *s, int elementSize, freeFunction freeFn);
void stack_destroy(stack *s);
void stack_push(stack *s, void *element);
void stack_pop(stack *s, void *element);
void stack_peek(stack *s, void *element);
int stack_length(stack *s);
#endif /*_LIBSTACK_H_*/
