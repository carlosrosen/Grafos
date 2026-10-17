#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H
#include "grafo_lista.h"

// Estrutura de fila
typedef struct{
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

// Funçoes da fila
Fila* inicializar_fila(int capacidade);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void liberar_fila(Fila *f);

// Funcoes da BFS
void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);
int contar_componentes(GrafoLista *g);

#endif 
