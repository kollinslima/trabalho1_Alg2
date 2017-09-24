#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void *popSimpleLinkedList(tSimpleLinkedList *queue){

	if(isEmptyQueue(queue)){
		return NULL;
	}
	
	tNodeQ *auxNode = queue->front;
	void *auxKey = queue->front->key;

	queue->front = queue->front->next;
	
	if(queue->front == NULL) queue->back = NULL;

	//if(auxNode->key != NULL) free(auxNode->key);
	if(auxNode->type != NULL){
		auxNode->type = NULL;
		free(auxNode->type);	
	} 
	free(auxNode);	

	return auxKey;
}
