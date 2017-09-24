#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

tNodeQ *newNodeQueue(){

    tNodeQ *nNode = (tNodeQ*)malloc(sizeof(tNodeQ));
    nNode->key = NULL;
    nNode->type = NULL;
    
    //    void *nodePointer = nNode;
    
    return nNode;
}
