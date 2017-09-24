#include<stdio.h>
#include"graph.h"

//(u,v) exist?
int isAdj(tGraph *graph, unsigned int u, unsigned int v){
    
    if(graph->graphType == MATRIX){
        if((u >= graph->tStruct.tMatrixAdj.max_vertices) || (v >= graph->tStruct.tMatrixAdj.max_vertices)) {
             //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph,u) && isInstantiated(graph,v)){
            return graph->tStruct.tMatrixAdj.graph[u][v].tVertexMatrix.key == 0? 0: 1;
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            return VERTEX_INVALID;   
        }
    }
    else if(graph->graphType == VECTOR_LIST){
        if((u >= graph->tStruct.tVListAdj.max_vertices) || (v >= graph->tStruct.tVListAdj.max_vertices)) {
             //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph,u) && isInstantiated(graph,v)){
            
            tStack *auxStack = graph->tStruct.tVListAdj.graph[u].tVertexVList.stackKey;
            tNodeS *auxNode = auxStack->top;

        	while(auxNode != NULL){
        		if((*(tNodeVList*)auxNode->key).adjVertex == v)
        		    return 1;
        		    
        		auxNode = auxNode->next;
        	}
        	
        	return 0;
                
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            return VERTEX_INVALID;   
        }
    }
    
}