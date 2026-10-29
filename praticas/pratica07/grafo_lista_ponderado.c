#include "grafo_lista_ponderado.h"
#include <stdlib.h>

GrafoListaPonderado *inicializar_grafo(int num_vertices){
    GrafoListaPonderado *g = (GrafoListaPonderado *)malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->adj = (No **)malloc(num_vertices * sizeof(No *));
    for (int i = 0; i < num_vertices; i++){
        g->adj[i] = NULL;
    }
    return g;
}

void inserir_aresta_direcionada(GrafoListaPonderado *g, int u, int v, int peso){
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = v;
    novo->peso = peso;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void inserir_aresta(GrafoListaPonderado *g, int u, int v, int peso){
    inserir_aresta_direcionada(g, u, v, peso);
    inserir_aresta_direcionada(g, v, u, peso);
}

void liberar_grafo(GrafoListaPonderado *g){
    for (int i = 0; i < g->num_vertices; i++){
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}
