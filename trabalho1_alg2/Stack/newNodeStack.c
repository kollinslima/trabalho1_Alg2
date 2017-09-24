#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

tNodeS *newNodeStack(){

    tNodeS *nNode = (tNodeS*)malloc(sizeof(tNodeS));
    nNode->key = NULL;
    nNode->type = NULL;
    
//    void *nodePointer = ntNodeS;
    
    return nNode;
}
