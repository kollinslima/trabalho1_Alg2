#include<stdio.h>
#include"graph.h"

int hasAdj(tGraph *graph, unsigned int u){
    
    if(graph->graphType == MATRIX){
        if(u >= graph->tStruct.tMatrixAdj.max_vertices) {
             //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph,u)){
            
            int i;
            
            for (i = 0; i < graph->tStruct.tMatrixAdj.max_vertices; i += 1){
                if(graph->tStruct.tMatrixAdj.graph[u][i].tVertexMatrix.key)
                    return 1;
            }
            
            return 0;
            
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            return VERTEX_INVALID;   
        }
    }
    else if(graph->graphType == VECTOR_LIST){
        if((u >= graph->tStruct.tVListAdj.max_vertices)) {
             //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph,u)){
            
            return !isEmptyStack(graph->tStruct.tVListAdj.graph[u].tVertexVList.stackKey);
                
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            return VERTEX_INVALID;   
        }
    }
}