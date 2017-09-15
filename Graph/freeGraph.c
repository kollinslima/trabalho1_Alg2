#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

int freeGraph(tGraph **graph){
    
    int i;
    
    if((*graph)->graphType == MATRIX){
        
        for (i = 0; i < (*graph)->tStruct.tMatrixAdj.max_vertices; i += 1)
		{
			(*graph)->tStruct.tMatrixAdj.graph[i] = NULL;
			free((*graph)->tStruct.tMatrixAdj.graph[i]);
		}
		
		free((*graph)->tStruct.tMatrixAdj.graph);
		
		(*graph)->tStruct.tMatrixAdj.graph = NULL;
		
		free(*graph);
		
    }
    else if((*graph)->graphType == VECTOR_LIST){
        
        for(i = 0; i < (*graph)->tStruct.tVListAdj.max_vertices; i+=1){
        	if((*graph)->tStruct.tVListAdj.graph[i].tVertexVList.instantiated)
        		freeStack(&((*graph)->tStruct.tVListAdj.graph[i].tVertexVList.stackKey));
        }
        
        (*graph)->tStruct.tVListAdj.graph = NULL;
        
        free((*graph)->tStruct.tVListAdj.graph);
		
		*graph = NULL;
		
		free(*graph);
		
    }
    
    return 0;
    
}