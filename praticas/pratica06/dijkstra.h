#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo_lista_ponderado.h"

#define INF 1000000000

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; 
} MinHeap;

MinHeap *criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap *h);
void inserir_min_heap(MinHeap *h, int vertice, int distancia);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int nova_distancia);
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif
