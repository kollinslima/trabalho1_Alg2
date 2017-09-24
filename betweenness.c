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

double **floyd_warshall(tGraph *graph){
    
    tStack *stack = newStack();
    int maxVertex = getMaxVertex(graph);
    int i,j,k;
    
    double **matrix = (double**)malloc(maxVertex*sizeof(double*));
    
    for(i = 0; i < maxVertex; i++){
        matrix[i] = (double*) malloc(maxVertex*sizeof(double));
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
			    		//	printf("VALOR MIN:%lf\n",matrix[i][j] );
							}
		    			}
		    		}
		    	}
			}
		}

	}
    
    return matrix;
}


int walk_graph_total(tGraph *graph, double pathLengh, double minPath, int beginVertex,int endVertex,int *forbidenVertex,int maxVertex){
        
 //   printf("Analise: %d\n", beginVertex);
    int hasPath = 0;
    int totalPath = 0;
    
    tNodeAdj adjacencias = firstAdj(graph,beginVertex);    
    
    if(beginVertex ==  endVertex)
        return 0;
    
    while(adjacencias.key > 0){
        
     //   printf("Adj: %d\n", adjacencias.adjVertex);
        
        if(!forbidenVertex[adjacencias.adjVertex]){
            
            //printf("Vertex %d is free\n", adjacencias.adjVertex);
            
            pathLengh += adjacencias.key;
            
        //    printf("pathLengh: %lf - MinPath: %lf\n",pathLengh, minPath);
            
            //Chegou no destino e é o caminho mínimo
            if(adjacencias.adjVertex == endVertex && pathLengh == minPath){
                
                totalPath += 1;
                pathLengh -= adjacencias.key;
                
            }else{
                
                forbidenVertex[beginVertex] = 1;
                hasPath = walk_graph_total(graph, pathLengh, minPath,adjacencias.adjVertex, endVertex, forbidenVertex,maxVertex);
                forbidenVertex[beginVertex] = 0;
                
                pathLengh -= adjacencias.key;
                
                
                totalPath += hasPath;
            }
        }
        adjacencias = nextAdj(graph,beginVertex,adjacencias.adjVertex);        
    }
    
  //  printf("Fim Analise: %d\n", beginVertex);
    return totalPath;
    
}

int walk_graph_totalVertex(tGraph *graph, double pathLengh, double minPath, int beginVertex,int endVertex,int *forbidenVertex,int maxVertex,int vertex,int hasVertex){
        
  //  printf("Analise: %d\n", beginVertex);
    int hasPath = 0;
    int totalPath = 0;
    
    tNodeAdj adjacencias = firstAdj(graph,beginVertex);    
    
    if(beginVertex ==  endVertex)
        return 0;
        
    if(beginVertex == vertex)
        hasVertex = 1;
    
    while(adjacencias.key > 0){
        
    //    printf("Adj: %d\n", adjacencias.adjVertex);
        
        if(!forbidenVertex[adjacencias.adjVertex]){
            
            //printf("Vertex %d is free\n", adjacencias.adjVertex);
            
            pathLengh += adjacencias.key;
            
       //     printf("pathLengh: %lf - MinPath: %lf\n",pathLengh, minPath);
            
            //Chegou no destino e é o caminho mínimo
            if(adjacencias.adjVertex == endVertex && pathLengh == minPath){
                
                totalPath += 1*hasVertex;
                pathLengh -= adjacencias.key;
                
            }else{
                
                forbidenVertex[beginVertex] = 1;
                hasPath = walk_graph_totalVertex(graph, pathLengh, minPath,adjacencias.adjVertex, endVertex, forbidenVertex,maxVertex,vertex,hasVertex);
                forbidenVertex[beginVertex] = 0;
                
                pathLengh -= adjacencias.key;
                
                totalPath += hasPath;
            }
        }
        adjacencias = nextAdj(graph,beginVertex,adjacencias.adjVertex);        
    }
    
  //  printf("Fim Analise: %d\n", beginVertex);
    return totalPath;
    
}

double betweenness(tGraph *graph, unsigned int vertex){
    
    double **matrix = floyd_warshall(graph);
    int i,j,maxVertex = getMaxVertex(graph);
    
    double centrality = 0;
    
    //Procura por todos os caminhos utilizando busca em profundidade.
    for(i = 0; i < maxVertex; i++){
        for(j = 0; j < maxVertex; j++){
            
            //Verifica condições para iniciar busca (nó analisado não pode ser nem inicio nem fim)
            if(i != vertex && j != vertex && i!=j){
                
                int forbidenVertex[maxVertex];
                int k;
                    
                for(k = 0; k < maxVertex; k++){
                    forbidenVertex[k] = 0;
                }
              //  printf("Inicio: %d - Fim: %d\n ", i,j);
                int totalPath = walk_graph_total(graph,0,matrix[i][j],i,j,forbidenVertex,maxVertex);
                
                int totalPathVertex = walk_graph_totalVertex(graph,0,matrix[i][j],i,j,forbidenVertex,maxVertex,vertex,0);
               // printf("Total: %d\n",totalPathVertex);    
               
                if(totalPath != 0)
                    centrality += ((float)totalPathVertex)/totalPath;
                    
                
            }
        }
    }
    
    
    return centrality;
}


//******************Teste da Função********************
int main(){
	
	int i;
	int MAX_VERTEX = 6;
	
	tGraph *graph = newGraph(VECTOR_LIST,MAX_VERTEX);
	
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
	
	/*
	insertVertex(graph,1);
	insertVertex(graph,2);
	insertVertex(graph,3);
	insertVertex(graph,4);
	insertVertex(graph,5);
	
	
	insertArc(graph,1,2,10);
	insertArc(graph,1,3,5);
	insertArc(graph,1,5,7);
	
	insertArc(graph,2,3,2);
	
	insertArc(graph,3,2,3);
	insertArc(graph,3,4,9);
	insertArc(graph,3,5,2);
	
	insertArc(graph,4,2,1);
	insertArc(graph,4,5,4);
	
	insertArc(graph,5,4,6);
	insertArc(graph,5,1,7);
	*/
	
	
	insertVertex(graph,0);
	insertVertex(graph,1);
	insertVertex(graph,2);
	insertVertex(graph,3);
	insertVertex(graph,4);
	insertVertex(graph,5);
	
	insertArc(graph,0,1,2);
	insertArc(graph,1,0,2);
	
	insertArc(graph,0,2,4);
	insertArc(graph,2,0,4);
	
	insertArc(graph,1,2,1);
	insertArc(graph,2,1,1);
	
	insertArc(graph,2,3,4);
	insertArc(graph,3,2,4);
	
	insertArc(graph,2,4,2);
	insertArc(graph,4,2,2);
	
	insertArc(graph,4,5,1);
	insertArc(graph,5,4,1);
	
	
/*	
	insertVertex(graph,0);
	insertVertex(graph,1);
	insertVertex(graph,2);
	insertVertex(graph,3);
	insertVertex(graph,4);
	
	insertArc(graph,0,1,60);
	insertArc(graph,0,2,20);
	insertArc(graph,0,4,40);
	insertArc(graph,1,0,50);
	insertArc(graph,1,4,100);
	insertArc(graph,1,2,60);
	insertArc(graph,2,3,10);
	insertArc(graph,3,4,20);
*/	
	
	double result[MAX_VERTEX];
	
	for(i = 0; i < MAX_VERTEX; i++){
	    result[i] = betweenness(graph, i);    
	}
	
	 
	for(i = 0; i < getMaxVertex(graph); i++){
	 	printf("%d - %f\n", i, result[i]);
	}
	 
    return 0;
}