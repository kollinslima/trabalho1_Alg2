#include<stdio.h>
#include"graph.h"

int isInstantiated(tGraph *graph, unsigned int vertex){
  
    if(graph->graphType == MATRIX){  
        return !(graph->tStruct.tMatrixAdj.graph[vertex][vertex].tVertexMatrix.key == -1);
    }
    else if(graph->graphType == VECTOR_LIST){  
        return (graph->tStruct.tVListAdj.graph[vertex].tVertexVList.instantiated);
    }
  
}