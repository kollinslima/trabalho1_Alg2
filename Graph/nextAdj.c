#include<stdio.h>
#include"graph.h"

tNodeAdj nextAdj(tGraph *graph, unsigned int u, unsigned int lastAdj){
    
    tNodeAdj auxNode;
    
    if(graph->graphType == MATRIX){
        if(u >= graph->tStruct.tMatrixAdj.max_vertices) {
             //Vertex is out of bounds
            auxNode.key = OUT_OF_BOUND;
            return auxNode;
        }
        else if(isInstantiated(graph,u)){
            
            int i;
            
            for (i = lastAdj+1; i < graph->tStruct.tMatrixAdj.max_vertices; i += 1){
                if(graph->tStruct.tMatrixAdj.graph[u][i].tVertexMatrix.key){
                    auxNode.key = graph->tStruct.tMatrixAdj.graph[u][i].tVertexMatrix.key;
                    auxNode.adjVertex = i;
                    return auxNode;
                }
                    
            }
            
            auxNode.key = OP_ERROR;
            return auxNode;
            
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            auxNode.key = VERTEX_INVALID;
            return auxNode;   
        }
    }
    else if(graph->graphType == VECTOR_LIST){
        if((u >= graph->tStruct.tVListAdj.max_vertices)) {
             //Vertex is out of bounds
            auxNode.key = OUT_OF_BOUND;
            return auxNode;
        }
        else if(isInstantiated(graph,u)){
                
            tNodeS *auxNodeGraph = graph->tStruct.tVListAdj.graph[u].tVertexVList.stackKey->top;
            
            while(auxNodeGraph != NULL){
                
                if((*(tNodeVList*)auxNodeGraph->key).adjVertex == lastAdj){
                    
                    auxNodeGraph = auxNodeGraph->next;
                    
                    if(auxNodeGraph != NULL){
                        auxNode = (*(tNodeVList*)auxNodeGraph->key);
                        return auxNode;
                    }
                        //return (*(tNodeVList*)auxNodeGraph->key).adjVertex;
                    else{
                        auxNode.key = OP_ERROR;
                        return auxNode;
                    }
                }
                
                auxNodeGraph = auxNodeGraph->next;
            }
            
            auxNode.key = OP_ERROR;
            return auxNode;
                
        }
        else{
            //Vertex not valid (one or both vertex not instantiated)
            auxNode.key = VERTEX_INVALID;
            return auxNode;   
        }
    }
}