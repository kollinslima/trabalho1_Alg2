#include<stdio.h>
#include"graph.h"

unsigned int getMaxVertex(tGraph *graph){
    
    if(graph->graphType == MATRIX){
        return graph->tStruct.tMatrixAdj.max_vertices;
    }
    else if(graph->graphType == VECTOR_LIST){
        return graph->tStruct.tVListAdj.max_vertices;
    }
    else{
        return OP_ERROR;
    }
}