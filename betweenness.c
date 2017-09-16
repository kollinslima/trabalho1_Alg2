#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
#include"stack.h"
#include"queue.h"

#define INFINITE -1

//Entrada: Grafo(V,A)
//Saída: Centralidade de todos vértices

void pushVertexStack(tStack *stack,int vertex){
    tNodeS *auxNode = newNodeStack();
	int *aux = (int*) malloc(sizeof(int));
	*aux = vertex;
	auxNode->key = aux;
	pushStack(stack, auxNode, "VERTEX");
	return;
}

void pushVertexQueue(tSimpleLinkedList *queue, int vertex){
    tNodeQ *auxNode = newNodeQueue();
	int *aux = (int*) malloc(sizeof(int));
	*aux = vertex;
	auxNode->key = aux;
	pushSimpleLinkedList(queue, auxNode, "VERTEX");
	return;
}

double *betweenness(tGraph *graph){
    
//**************Inicialização das estruturas******************
    
    int i,j;
    
    int maxVertex = getMaxVertex(graph);
    
    tSimpleLinkedList *queue = newSimpleLinkedList();
    tStack *stack = newStack();
    
    double dist[maxVertex][maxVertex];
    double sigma[maxVertex][maxVertex];
    double delta[maxVertex][maxVertex];
    
    tSimpleLinkedList *pred[maxVertex][maxVertex];
    //tSimpleLinkedList ***pred = (tSimpleLinkedList***)malloc(sizeof(tSimpleLinkedList**)*maxVertex);
    
    double *centrality = (double*)malloc(sizeof(double)*maxVertex);
    
//**************Início do algoritmo******************
	
    for(i = 0; i < maxVertex; i++){
    	
    	if(isInstantiated(graph,i)){
	        
	        for(j = 0; j<maxVertex; j++){
	            
	            pred[i][j] = newSimpleLinkedList();
	            dist[i][j] = INFINITE; 
	            sigma[i][j] = 0;
	        }
	        
	        dist[i][i] = 0;
	        sigma[i][i] = 1;
	        
	        pushVertexQueue(queue,i);
			
			while(!isEmptyQueue(queue)){
			    int vertex = *((int*)popSimpleLinkedList(queue));
			    pushVertexStack(stack,vertex);
			    
			    int adjVertex = (int)firstAdj(graph,vertex);
			    
			    while(adjVertex != OP_ERROR){
			        if(dist[i][adjVertex] == INFINITE){
			            dist[i][adjVertex] = dist[i][vertex] + 1;
			            pushVertexQueue(queue,adjVertex);
			        }
			
			        if(dist[i][adjVertex] == dist[i][vertex] + 1){
			            sigma[i][adjVertex] = sigma[i][adjVertex] + sigma[i][vertex];
			            pushVertexQueue(pred[i][adjVertex],vertex);
			        }
			
			        adjVertex = (int)nextAdj(graph,vertex,adjVertex);
			    }
			}
			
			
			for (j = 0; j < maxVertex; j++){
				delta[i][j] = 0;
			}
			
			while(!isEmptyStack(stack)){
				int vertexAcumulation = *((int*)popStack(stack));
				
				while(!isEmptyQueue(pred[i][vertexAcumulation])){
					int auxVertex = *((int*)popSimpleLinkedList(pred[i][vertexAcumulation]));	
					delta[i][auxVertex] = delta[i][auxVertex] + (sigma[i][auxVertex]/sigma[i][vertexAcumulation])*(1 + delta[i][vertexAcumulation]);
				}
				
				if(vertexAcumulation != i){
					centrality[vertexAcumulation] += delta[i][vertexAcumulation];
				}
				
			}

    	}
    }
    
    freeStack(&stack);
    freeSimpleLinkedList(&queue);
    
    return centrality;
}


//******************Teste da Função********************
int main(){
	
	int i;
	
	tGraph *graph = newGraph(VECTOR_LIST,10);
	
	/*
	insertVertex(graph, 0);
	insertVertex(graph, 1);
	insertVertex(graph, 7);
	insertVertex(graph, 9);
	insertVertex(graph, 8);
	 
	insertArc(graph,0,1,1);
	insertArc(graph,1,0,1);
	 
	insertArc(graph,1,7,1);
	insertArc(graph,7,1,1);
	 
	insertArc(graph,1,8,1);
	insertArc(graph,8,1,1);
	 
	insertArc(graph,7,9,1);
	insertArc(graph,9,7,1);
	 
	insertArc(graph,8,9,1);
	insertArc(graph,9,8,1);
	*/
	
	insertVertex(graph,1);
	insertVertex(graph,2);
	insertVertex(graph,3);
	insertVertex(graph,4);
	insertVertex(graph,5);
	insertVertex(graph,6);
	insertVertex(graph,7);
	
	insertArc(graph,1,2,1);
	insertArc(graph,2,1,1);
	
	insertArc(graph,1,3,1);
	insertArc(graph,3,1,1);
	
	insertArc(graph,2,3,1);
	insertArc(graph,3,2,1);
	
	insertArc(graph,2,5,1);
	insertArc(graph,5,2,1);
	
	insertArc(graph,3,4,1);
	insertArc(graph,4,3,1);
	
	insertArc(graph,3,5,1);
	insertArc(graph,5,3,1);
	
	insertArc(graph,5,6,1);
	insertArc(graph,6,5,1);
	
	insertArc(graph,5,7,1);
	insertArc(graph,7,5,1);
	
	 
	double *result = betweenness(graph);
	 
	for(i = 0; i < getMaxVertex(graph); i++){
	 	printf("%d - %f\n", i, result[i]);
	}
	 
    return 0;
}