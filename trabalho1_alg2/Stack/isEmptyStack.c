#include <stdio.h>
#include "stack.h"

int isEmptyStack(const tStack *stack){

	return stack->top == NULL;
}
