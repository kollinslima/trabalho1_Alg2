#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

tSimpleLinkedList *newSimpleLinkedList(){

    tSimpleLinkedList *nSLL = (tSimpleLinkedList*)malloc(sizeof(tSimpleLinkedList));
    nSLL->front = NULL;
    nSLL->back = NULL;

//    void *sllPointer = nSLL;
    
    return nSLL;
}
