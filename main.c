/**
	Código produzido por:
        Gustavo Jose Pereira Leite
        Nº USP: 9051741

        Isabele Neves de Oliveira
        Nº USP: 9847686

        Kollins Gabriel Lima
        Nº USP: 9012931

    Trabalho 1 – Grafos
	Universidade de São Paulo
	SCC0603 - Algoritmos e Estruturas de Dados II
	Docente: Elaine	Parros M. de Sousa

	Setembro/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "stack.h"

#define ARQUIVO "Entrada.txt"
/*
OBS: O nome do arquivo de entrada deve ser exatamente "Entrada.txt", salvo na mesma pasta que seu programa original.
*/

int main() {
    printf("...Ano 2020...\n");
    printf("ACABOOOOOOU!!! Enfim formados!\n\n");
    printf("10 anos depois... Festa do Reencontro da EngComp 016...\n");


/** Abertura do Arquivo de Entrada **/
    FILE *arq = fopen(ARQUIVO, "r");
    if (arq == NULL) {
        return EXIT_FAILURE;
    }


/** Leitura das características do grafo **/
    printf("...Lendo características do grafo...\n\n");

    // Leitura da LINHA 1 do arquivo txt - número de cidades e de estradas do grafo
    // (formato: "N" e "M")
	int n, m;
	fscanf(arq, "%d %d", &n, &m);
    if (n < 2 || n > 50) { // restrição de no mínimo duas cidades e no máximo 50 cidades no grafo
        printf("Erro: N = %d", n);
        exit(0);
	} else if (m < 1 || m > pow(n,2)) { // restrição de no mínimo uma estrada e no máximo N²
        printf("Erro: M = %d", m);
        exit(0);
	}
    printf(" GRAFO COM: %d cidades e %d estradas\n\n", n, m);


    // Cria um grafo com N cidades
    tGraph *graph = newGraph(VECTOR_LIST,n);
    for (i = 0; i < getMaxVertex(graph); i++) { // insere os vértices/cidades no grafo
        insertVertex(graph, i);
    }


    // Leitura da LINHA 2 em diante do arquivo txt - quantidade egressos em cada cidade
    int *qtdEgressos;
    qtdEgressos = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(arq, "%d", &qtdEgressos[i]);
        if (qtdEgressos[i] < 0 || qtdEgressos[i] > 50) { // restrição de no mínimo 0 egressos por cidade e no máximo 50
            printf("Erro: E = %d", qtdEgressos[i]);
            exit(0);
        }
        printf(" Cidade %d: %d egressos\n", i, qtdEgressos[i]);
    }
    printf("\n");


    // Leitura das próximas linhas - estradas
    // (formato: "cidade1" "cidade2" "distância")
    int id1, id2, d;
    for (int i = 0; i < m; i++) {
        fscanf(arq, "%d %d %d", &id1, &id2, &d);
        if (id1 < 0 || id1 > n ) { // restrição de existência da cidade/vértice id1 - possível de 0 a 50
            printf("Erro: ID1 = %d", id1);
            exit(0);
        } else if (id2 < 0 || id2 > n) { // restrição de existência da cidade/vértice id2 - possível de 0 a 50
            printf("Erro: ID2 = %d", id2);
            exit(0);
        } else if (d < 0 || d > 100) { // restrição da distância entre id1 e id2 ser entre 0km a 100km
            printf("Erro: D = %d", d);
            exit(0);
        }
        insertArc(graph, id1, id2, d); // insere a estrada/aresta no grafo
        d = d * qtdEgressos[id1]; // peso da aresta é o cálculo da distância entre duas cidades em função da
                                  // quantidade de egressos que irão se deslocar da cidade id1 para a cidade id2
        printf(" %d >>>>> %dkm >>>>> %d\n", id1, id2, d);
    }
    printf("\n");

    free(qtdEgressos); // libera a memória alocada pela variável
    fclose(arq); // final de uso do arquivo txt


/** Cálculo da cidade mais adequada para Festa **/
    // Critério 1: menor distância e menor deslocamento de egressos
    printf(" CRITÉRIO 1: \n\n");
    criterio1(graph);

    // Critério 2: cidade intermediária
    printf(" CRITÉRIO 2: \n\n");
    //criterio2(graph);

    return EXIT_SUCCESS;
}
