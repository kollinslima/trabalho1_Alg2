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
    int i;

    printf("...Ano 2020...\n");
    printf("ACABOOOOOOU!!! Formados!\n\n");
    printf("10 anos depois... Festa da EngComp 016...\n");


/** Abertura do Arquivo de Entrada **/
    FILE *arq = fopen(ARQUIVO, "r");
    if (arq == NULL) {
        return EXIT_FAILURE;
    }


/** Leitura das características do grafo **/
    printf("...Lendo características do grafo...\n\n");



    // Linha 1 - N e M - número de cidades/vértices e número de estradas/arestas
	int n, m;
	fscanf(arq, "%d %d", &n, &m);
    if (n < 2 || n> 50) {
        printf("Erro: N = %d", n);
        exit(0);
	} else if (m < 1 || m > pow(n,2)) {
        printf("Erro: M = %d", m);
        exit(0);
	}
    printf(" %d cidades e %d estradas\n\n", n, m);


    // Cria um grafo
    tGraph *graph = newGraph(VECTOR_LIST,n);

    // Insere os vértices no grafo
    for (i = 0; i < getMaxVertex(graph); i++) {
        insertVertex(graph, i);
    }


    // (Como vai fazer esse controle? Qual variável?)
    // Linha 2 em diante - quantidade egressos em cada cidade
    int qtdEgressos[n];
    for (i = 0; i < getMaxVertex(graph); i++) {
        fscanf(arq, "%d", &qtdEgressos[i]);
        if (qtdEgressos[i] < 0 || qtdEgressos[i] > 50) {
            printf("Erro: E = %d", qtdEgressos[i]);
            exit(0);
        }
        printf(" Cidade %d: %d egressos\n", i, qtdEgressos[i]);
    }
    printf("\n");


    // Linhas depois - estradas (cidade1 cidade2 distância)
    int id1, id2, d;
    for (i = 0; i < m; i++) {
        fscanf(arq, "%d %d %d", &id1, &id2, &d);
        if (id1 < 0 || id1 > getMaxVertex(graph)) {
            printf("Erro: ID1 = %d", id1);
            exit(0);
        } else if (id2 < 0 || id2 > getMaxVertex(graph)) {
            printf("Erro: ID2 = %d", id2);
            exit(0);
        } else if (d < 0 || d > 100) {
            printf("Erro: D = %d", d);
            exit(0);
        }
        insertArc(graph, id1, id2, d);
        printf(" %d >>>>> %dkm >>>>> %d\n", id1, id2, d);
    }
    printf("\n");

    fclose(arq);


/** Cálculo da cidade mais adequada para Festa **/
    // Critério 1: menor distância e menor deslocamento de egressos
    printf(" CRITÉRIO 1: \n\n");
    criterio1(graph);

    // Critério 2: cidade intermediária
    printf(" CRITÉRIO 2: \n\n");
  //criterio2(graph);

    return EXIT_SUCCESS;
}
