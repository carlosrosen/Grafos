#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H
#include "grafo_lista.h"

// Estrutura de pilha
typedef struct{
    int *dados;
    int topo, capacidade;
} Pilha;


// Funcoes da pilha
Pilha* inicializar_pilha(int capacidade);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
void liberar_pilha(Pilha *p);

// Funcoes da DFS
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo_entrada, int *tempo_saida, int *tempo_global, Pilha *p);
int tem_ciclo(GrafoLista *g);

#endif
