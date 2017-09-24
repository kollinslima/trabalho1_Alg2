#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int freeStack(tStack **stack){

	while((*stack)->top != NULL){

		tNodeS *auxNode = (*stack)->top;
		(*stack)->top = (*stack)->top->next;

		if(auxNode->key != NULL){
			auxNode->key = NULL;
			free(auxNode->key);	
		} 
		if(auxNode->type != NULL){
			auxNode->type = NULL;
			free(auxNode->type);	
		} 
		free(auxNode);
	}

	free(*stack);

	return 0;
}
