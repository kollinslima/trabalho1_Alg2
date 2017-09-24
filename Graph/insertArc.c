#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"graph.h"

int insertArc(tGraph *graph, unsigned int u, unsigned int v, double weight){
    
    if(graph->graphType == MATRIX){  
        
        if((u >= graph->tStruct.tMatrixAdj.max_vertices) || (v >= graph->tStruct.tMatrixAdj.max_vertices)) {
             //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph,u) && isInstantiated(graph,v)){
            graph->tStruct.tMatrixAdj.graph[u][v].tVertexMatrix.key = weight;
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
            
            tNodeS *auxNode = newNodeStack();
            auxNode->key = (void*)malloc(sizeof(tNodeVList));
	        (*(tNodeVList*)auxNode->key).key = weight;
	        (*(tNodeVList*)auxNode->key).adjVertex = v;
	        
            pushStack(graph->tStruct.tVListAdj.graph[u].tVertexVList.stackKey, auxNode,"GRAPH_VERTEX");
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            return VERTEX_INVALID;   
        }
    }
}