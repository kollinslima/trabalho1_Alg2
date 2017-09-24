#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

int compareVertex(tNodeS *node1, tNodeS *node2){
    return ((*(tNodeVList*)node1->key).adjVertex == (*(tNodeVList*)node2->key).adjVertex);
}

double removeArc(tGraph *graph, unsigned int u, unsigned int v){
    
    if(graph->graphType == MATRIX){  
        if((u >= graph->tStruct.tMatrixAdj.max_vertices) || (v >= graph->tStruct.tMatrixAdj.max_vertices)) {
             //Vertex is out of bounds
            return OUT_OF_BOUND;
        }
        else if(isInstantiated(graph,u) && isInstantiated(graph,v)){
            double aux = graph->tStruct.tMatrixAdj.graph[u][v].tVertexMatrix.key;
            graph->tStruct.tMatrixAdj.graph[u][v].tVertexMatrix.key = 0;
            return aux;
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
	        (*(tNodeVList*)auxNode->key).adjVertex = v;
	        
            void *auxWeight = popNodeStack(graph->tStruct.tVListAdj.graph[u].tVertexVList.stackKey, auxNode, &compareVertex);
            
            return (double)(((tNodeVList*)auxWeight)->key);
                
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            return VERTEX_INVALID;   
        }
    }
    
}