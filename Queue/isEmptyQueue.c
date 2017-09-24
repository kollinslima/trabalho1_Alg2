#include <stdio.h>
#include "queue.h"

int isEmptyQueue(const tSimpleLinkedList *queue){

	return queue->front == NULL? 1 : 0;
}
