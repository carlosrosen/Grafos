#include "bellman_ford.h"
#include <stdio.h>
#include <stdlib.h>

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred){
    int n = g->num_vertices;

    for (int i = 0; i < n; i++){
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int iteracao = 0; iteracao < n - 1; iteracao++){
        for (int u = 0; u < n; u++){
            if (dist[u] == INF) continue;
            for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
                int v = aresta->vertice;
                long long novo_custo = (long long)dist[u] + aresta->peso;
                if (novo_custo < dist[v]){
                    dist[v] = (int)novo_custo;
                    pred[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; u++){
        if (dist[u] == INF) continue;
        for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
            int v = aresta->vertice;
            long long novo_custo = (long long)dist[u] + aresta->peso;
            if (novo_custo < dist[v]){
                return 0;
            }
        }
    }
    return 1;
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred){
    int n = g->num_vertices;
    int vertice = -1;

    for (int u = 0; u < n && vertice == -1; u++){
        if (dist[u] == INF) continue;
        for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
            long long novo_custo = (long long)dist[u] + aresta->peso;
            if (novo_custo < dist[aresta->vertice]){
                vertice = aresta->vertice;
                break;
            }
        }
    }

    if (vertice == -1){
        printf("nenhum ciclo negativo alcancavel a partir da origem.\n");
        return;
    }

    for (int i = 0; i < n; i++){
        vertice = pred[vertice];
    }

    if (vertice == -1){
        printf("n foi possivel reconstruir o ciclo negativo.\n");
        return;
    }

    int *ciclo = (int *)malloc((n + 1) * sizeof(int));
    int tamanho = 0;
    int atual = vertice;

    do {
        ciclo[tamanho++] = atual;
        atual = pred[atual];
    } while (atual != vertice && tamanho <= n);

    printf("Ciclo negativo: ");
    for (int i = tamanho - 1; i >= 0; i--){
        printf("%d -> ", ciclo[i]);
    }
    printf("%d\n", ciclo[tamanho - 1]);

    free(ciclo);
}
