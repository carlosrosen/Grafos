#include "grafo_lista.h"
#include <stdlib.h>

GrafoLista* inicializar_grafo(int num_vertices){
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->adj = (No **)malloc(num_vertices * sizeof(No *));
    for (int i = 0; i < num_vertices; i++){
        g->adj[i] = NULL;
    }
    return g;
}

void inserir_aresta(GrafoLista *g, int u, int v){
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
    novo = (No *)malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = g->adj[v];
    g->adj[v] = novo;
}

void liberar_grafo(GrafoLista *g){
    for (int i = 0; i < g->num_vertices; i++){
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
}
