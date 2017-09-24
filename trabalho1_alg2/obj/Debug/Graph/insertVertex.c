#include<stdio.h>
#include"graph.h"

int insertVertex(tGraph *graph, unsigned int vertex){
    
    int i;
  
    if(graph->graphType == MATRIX){  
        
        if(vertex >= graph->tStruct.tMatrixAdj.max_vertices){
            //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph, vertex)){
            //Vertex not valid (already exists)
            return VERTEX_INVALID;   
        }
        else{
            graph->num_vertices += 1;
            
            //set vertex as valid
            for(i = 0; i < graph->tStruct.tMatrixAdj.max_vertices; i += 1){
                
                graph->tStruct.tMatrixAdj.graph[vertex][i].tVertexMatrix.key = 0;
                graph->tStruct.tMatrixAdj.graph[i][vertex].tVertexMatrix.key = 0;
                
            }
    	
        }
    }
    else if(graph->graphType == VECTOR_LIST){  
        
        if(vertex >= graph->tStruct.tVListAdj.max_vertices){
            //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph, vertex)){
            //Vertex not valid (already exists)
            return VERTEX_INVALID;   
        }
        else{
            
            graph->tStruct.tVListAdj.graph[vertex].tVertexVList.instantiated = 1;
            graph->tStruct.tVListAdj.graph[vertex].tVertexVList.stackKey = newStack();
            graph->num_vertices += 1;
	
        }
        
    }
    
    return 0;

}