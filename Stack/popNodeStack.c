#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void *popNodeStack(tStack *stack, tNodeS *node, int (*compareNode)(tNodeS *node1, tNodeS *node2)){

	if(isEmptyStack(stack)){
		return NULL;
	}
	
	tNodeS *auxNode = stack->top;
	tNodeS *auxLastNodeS;

	while (auxNode != NULL && !compareNode(auxNode, node)){
		auxLastNodeS = auxNode;
		auxNode = auxNode->next;
	}

	if(auxNode == NULL){
		return NULL;
	}
	else{
		if(compareNode(auxNode, stack->top)){
			return popStack(stack);
		}
		else{
			auxLastNodeS->next = auxNode->next;
			auxNode->next = NULL;
		}
	}

	void *auxKey = auxNode->key;

	//if(auxNode->key != NULL) free(auxNode->key);
	if(auxNode->type != NULL){ 
		auxNode->type = NULL;
		free(auxNode->type);
	}
	free(auxNode);	

	return auxKey;
}
