#ifndef _queue_h
#define _queue_h

typedef struct nodeQueue{
    void *key;
    char *type;
    struct nodeQueue *next;
}tNodeQ;

typedef struct{
    tNodeQ *front;
    tNodeQ *back;
}tSimpleLinkedList;

//********************SIMPLE LINKED LIST***************************//

int freeSimpleLinkedList(tSimpleLinkedList **queue);

int isEmptyQueue(const tSimpleLinkedList *queue);

tNodeQ *newNodeQueue();

tSimpleLinkedList *newSimpleLinkedList();

void *popSimpleLinkedList(tSimpleLinkedList *queue);

int pushSimpleLinkedList(tSimpleLinkedList *queue, tNodeQ *node, char *type);

int printSimpleLinkedList(const tSimpleLinkedList *queue, void (*printKey)(tNodeQ *node));

#endif
