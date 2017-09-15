#ifndef _graph_h
#define _graph_h

#include "stack.h"

#define OUT_OF_BOUND -1
#define VERTEX_INVALID -2
#define OP_ERROR -3

typedef int tDefaultType;

typedef enum typeStruct {MATRIX, VECTOR_LIST, LIST_LIST} eGraphType;

typedef struct{
	tDefaultType key;
	unsigned int adjVertex;
}tNodeVList;

typedef union{
    
    struct{
        tDefaultType key;
    }tVertexMatrix;
    
    struct{
    	int instantiated;
        tStack *stackKey;
    }tVertexVList;
    
}tVertex;

typedef struct{
	unsigned int num_vertices;
	eGraphType graphType;
	
	union{
	    
	    struct{
	        unsigned int max_vertices;
	        tVertex *graph;
	    }tVListAdj;
	    
	    struct{
	        unsigned int max_vertices;
	        tVertex **graph;
	    }tMatrixAdj;
	    
	}tStruct;
	
}tGraph;

unsigned int firstAdj(tGraph *graph, unsigned int u);

int freeGraph(tGraph **graph);

unsigned int getMaxVertex(tGraph *graph);

int hasAdj(tGraph *graph, unsigned int u);

int insertArc(tGraph *graph, unsigned int u, unsigned int v, double weight);

int insertVertex(tGraph *graph, unsigned int vertex);

int isAdj(tGraph *graph, unsigned int u, unsigned int v);

int isInstantiated(tGraph *graph, unsigned int u);

tGraph *newGraph(eGraphType type, unsigned int max_vertices);

unsigned int nextAdj(tGraph *graph, unsigned int u, unsigned int lastAdj);

double removeArc(tGraph *graph, unsigned int u, unsigned int v);

int removeVertex(tGraph *graph, unsigned int vertex);

#endif
