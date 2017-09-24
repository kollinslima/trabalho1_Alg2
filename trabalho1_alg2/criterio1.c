#include<stdio.h>
#include<stdlib.h>
#include"graph.h"
#include"stack.h"
#include"queue.h"

#define INFINITE -1


//Entrada: Grafo(V,A)
//Saída: Centralidade de todos vértices

int valorMin(int a,int b){
	//printf("%d %d\n",a,b );
    if(a>b){
    	return b;
    }
    else if(a<b){
    	return a;
    }
    else{
    	return a;
    }
}

double *criterio1(tGraph *graph){

//**************Inicialização das estruturas******************
    int i,j,k;
    int maxVertex = getMaxVertex(graph);
    int matrix[maxVertex][maxVertex];
 	int minVector[maxVertex];
 	tStack *stack = newStack();

 	//Inicia vetor de minimos com zero
	for (i = 0; i < maxVertex; ++i)
	{
		if(isInstantiated(graph,i)){
			minVector[i]=0;
		}
	}

	//Inicia matriz de distâncias com zero nos selfs-loops e infinito(-1) nas demais posições
 	for (i = 0; i < maxVertex; i += 1){
 		if(isInstantiated(graph,i)){
			for (j = 0; j < maxVertex; j += 1)
			{
				if(isInstantiated(graph,j)){
					if(i==j){
						matrix[i][i]=0;
					}
					else{
						matrix[i][j] = -1;
					}
				}
			}
		}

	}

	//Constroi matriz de distancias inicial
    for (i = 0; i < maxVertex; ++i)
    {
    	if(isInstantiated(graph,i)){
	    	stack = graph->tStruct.tVListAdj.graph[i].tVertexVList.stackKey;
	    	tNodeS *auxNode = stack->top;
			while(auxNode != NULL){
				j = (*(tNodeVList*)auxNode->key).adjVertex;
				matrix[i][j] = (*(tNodeVList*)auxNode->key).key;
				//printf("GRAFO %d : %d ",i,(*(tNodeVList*)auxNode->key).key);
				auxNode = auxNode->next;
			}
		}

	}

	//Algoritmo de Floyd-Warshall
	for (k = 0; k < maxVertex; ++k)
    {
    	if(isInstantiated(graph,k)){
	    	for (i = 0; i < maxVertex; ++i)
	    	{
	    		if(isInstantiated(graph,i)){
		    		for (j = 0 ; j < maxVertex; ++j)
		    		{
		    			if(isInstantiated(graph,j)){
			    			//printf("MATRIZ[%d][%d]=%d\n", i,j,matrix[i][j]);
			    			if(matrix[i][j] == -1){
			    				if(matrix[i][k] == -1 || matrix[k][j] ==-1)
			    				{
			    					matrix[i][j] = -1;
			    				}
			    				else{
			    					matrix[i][j]=matrix[i][k]+matrix[k][j];
			    				}
			    			}
			    			else if(matrix[i][k] == -1 || matrix[k][j] ==-1)
			    			{
			    				matrix[i][j]=matrix[i][j];
			    			}
			    			else{//	printf("SOMA:%d\n",  matrix[i][k]+matrix[k][j]);
			    				matrix[i][j] = valorMin(matrix[i][j], matrix[i][k]+matrix[k][j]);
			    			//printf("VALOR MIN:%d\n",matrix[i][j] );
							}
		    			}
		    		}
		    	}
			}
		}

	}

	//Constroi vetor de minimas distancias
	for (i = 0; i < maxVertex; ++i)
	{
		if(isInstantiated(graph,i)){
			for (j = 0; j < maxVertex; ++j)
			{
				if(isInstantiated(graph,j)){
					int aux;
					aux = matrix[j][i];
					if(minVector[i]<aux){
						minVector[i]=aux;
					}
				}
			}
		}
	}

	//Identifica elemento central
	int menorElem = -1;
	int cont = 0;
	int vertCentral;
	while(menorElem == -1)
	{
		if(isInstantiated(graph,cont)){
			menorElem = minVector[cont];
			vertCentral=cont;
		}
		cont++;
	}
	for (i = 0; i < maxVertex; ++i)
	{
		if(isInstantiated(graph,i)){
			if(menorElem > minVector[i]){
				menorElem = minVector[i];
				vertCentral = i;
			}
			printf("Distancia[%d]: %d\n",i,minVector[i]);
		}
	}
	printf("Vértice Central:%d , Menor Elemento: %d\n", vertCentral,menorElem);
}


//******************Teste da Função********************
//int main(){
//
//	int i;
//
//	tGraph *graph = newGraph(VECTOR_LIST,5);
//
//	//EXEMPLO SLIDE AULA
//	/*
//	insertVertex(graph, 1);
//	insertVertex(graph, 2);
//	insertVertex(graph, 3);
//
//	insertArc(graph,1,1,2);
//	insertArc(graph,1,2,8);
//	insertArc(graph,1,3,5);
//
//	insertArc(graph,2,1,3);
//	insertArc(graph,3,2,2);
//	*/
//
//	//EXEMPLO TRABALHO
//	insertVertex(graph,0);
//	insertVertex(graph,1);
//	insertVertex(graph,2);
//	insertVertex(graph,3);
//	insertVertex(graph,4);
//	//insertVertex(graph,6);
//	//insertVertex(graph,7);
//
//	insertArc(graph,0,1,600);
//	insertArc(graph,0,2,200);
//	insertArc(graph,0,4,400);
//
//	insertArc(graph,1,0,250);
//	insertArc(graph,1,4,500);
//	insertArc(graph,1,2,300);
//
//	insertArc(graph,2,3,150);
//
//	insertArc(graph,3,4,100);
//
//	//EXEMPLO YOUTUBE
//	/*
//	insertVertex(graph,1);
//	insertVertex(graph,2);
//	insertVertex(graph,3);
//	insertVertex(graph,4);
//
//	insertArc(graph,1,2,8);
//	insertArc(graph,1,4,1);
//
//	insertArc(graph,2,3,1);
//
//	insertArc(graph,3,1,4);
//
//	insertArc(graph,4,2,2);
//	insertArc(graph,4,3,9);
//	*/
//	/*
//	//EXEMPLO2
//	insertVertex(graph,1);
//	insertVertex(graph,2);
//	insertVertex(graph,3);
//	insertVertex(graph,4);
//
//	insertArc(graph,1,2,8);
//	insertArc(graph,2,3,1);
//	insertArc(graph,3,1,4);
//	insertArc(graph,1,4,1);
//	insertArc(graph,4,3,9);
//	insertArc(graph,4,2,2);
//	*/
//	criterio1(graph);
//
//
//    return 0;
//}
