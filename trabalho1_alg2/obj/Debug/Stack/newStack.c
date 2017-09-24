#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

tStack *newStack(){

    tStack *nStack = (tStack*)malloc(sizeof(tStack));
    nStack->top = NULL;

//    void *stackPointer = ntStack;
    
    return nStack;
}
