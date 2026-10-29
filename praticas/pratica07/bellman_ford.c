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

    // n - 1 iteracoes de relaxacao de todas as arestas
    for (int iteracao = 0; iteracao < n - 1; iteracao++){
        for (int u = 0; u < n; u++){
            if (dist[u] == INF) continue;
            for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
                int v = aresta->vertice;
                int novo_custo = dist[u] + aresta->peso;
                if (novo_custo < dist[v]){
                    dist[v] = novo_custo;
                    pred[v] = u;
                }
            }
        }
    }

    // n-esima iteracao: se ainda for possivel relaxar, existe ciclo negativo alcancavel
    for (int u = 0; u < n; u++){
        if (dist[u] == INF) continue;
        for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
            int v = aresta->vertice;
            int novo_custo = dist[u] + aresta->peso;
            if (novo_custo < dist[v]){
                // registra a relaxacao para permitir reconstruir o ciclo,
                // inclusive no caso de um laco negativo com n = 1
                dist[v] = novo_custo;
                pred[v] = u;
                return 0;
            }
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred){
    int n = g->num_vertices;
    int vertice = -1;

    // localiza um vertice que ainda pode ser relaxado na n-esima iteracao
    for (int u = 0; u < n && vertice == -1; u++){
        if (dist[u] == INF) continue;
        for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
            int v = aresta->vertice;
            int novo_custo = dist[u] + aresta->peso;
            if (novo_custo < dist[v]){
                vertice = v;
                break;
            }
        }
    }

    if (vertice == -1){
        printf("Nenhum ciclo negativo alcancavel a partir da origem.\n");
        return;
    }

    // retrocede n vezes para garantir que o vertice esteja dentro do ciclo
    for (int i = 0; i < n && vertice != -1; i++){
        vertice = pred[vertice];
    }

    if (vertice == -1){
        printf("Nao foi possivel reconstruir o ciclo negativo.\n");
        return;
    }

    int *ciclo = (int *)malloc((n + 1) * sizeof(int));
    if (ciclo == NULL){
        printf("Nao foi possivel alocar memoria para o ciclo negativo.\n");
        return;
    }

    int tamanho = 0;
    int atual = vertice;
    do {
        ciclo[tamanho++] = atual;
        atual = pred[atual];
    } while (atual != vertice && atual != -1 && tamanho <= n);

    if (atual != vertice){
        free(ciclo);
        printf("Nao foi possivel reconstruir o ciclo negativo.\n");
        return;
    }

    printf("Ciclo negativo: ");
    for (int i = tamanho - 1; i >= 0; i--){
        printf("%d -> ", ciclo[i]);
    }
    printf("%d\n", ciclo[tamanho - 1]);

    free(ciclo);
}
