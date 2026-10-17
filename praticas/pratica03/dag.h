#ifndef DAG_H
#define DAG_H

#include "grafo_lista.h"

typedef struct{
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

// estrutura da pilha
typedef struct{
    int *dados;
    int topo, capacidade;
} Pilha;

// Funcoes da fila
Fila* inicializar_fila(int capacidade);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void liberar_fila(Fila *f);

// Funcoes da pilha
Pilha* inicializar_pilha(int capacidade);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
void liberar_pilha(Pilha *p);

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int eh_dag(GrafoLista *g);

#endif
