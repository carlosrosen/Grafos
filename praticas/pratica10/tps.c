#include <stdlib.h>
#include "tps.h"

#define INF 1000000000

GrafoTSP *grafo_para_tsp(GrafoLista *g){
    int n = g->num_vertices;
    GrafoTSP *tsp = (GrafoTSP *)malloc(sizeof(GrafoTSP));
    tsp->num_vertices = n;
    tsp->distancias = (int **)malloc(n * sizeof(int *));

    // grafo completo: peso 1 para arestas existentes e 2 para as inexistentes
    for (int i = 0; i < n; i++){
        tsp->distancias[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++){
            tsp->distancias[i][j] = (i == j) ? 0 : 2;
        }
    }

    for (int u = 0; u < n; u++){
        for (No *no = g->adj[u]; no != NULL; no = no->prox){
            tsp->distancias[u][no->vertice] = 1;
        }
    }

    return tsp;
}

void liberar_grafo_tsp(GrafoTSP *g){
    for (int i = 0; i < g->num_vertices; i++){
        free(g->distancias[i]);
    }
    free(g->distancias);
    free(g);
}

static void tsp_forca_bruta_rec(GrafoTSP *g, int origem, int *rota, int *visitado, int pos, int custo_atual, int *melhor_custo, int *melhor_rota){
    if (pos == g->num_vertices){
        int custo = custo_atual + g->distancias[rota[pos - 1]][origem];
        if (custo < *melhor_custo){
            *melhor_custo = custo;
            for (int i = 0; i < g->num_vertices; i++){
                melhor_rota[i] = rota[i];
            }
        }
        return;
    }

    for (int v = 0; v < g->num_vertices; v++){
        if (!visitado[v]){
            int novo_custo = custo_atual + g->distancias[rota[pos - 1]][v];
            visitado[v] = 1;
            rota[pos] = v;
            tsp_forca_bruta_rec(g, origem, rota, visitado, pos + 1, novo_custo, melhor_custo, melhor_rota);
            visitado[v] = 0;
        }
    }
}

int tsp_forca_bruta(GrafoTSP *g, int origem, int *rota){
    int n = g->num_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    int *rota_atual = (int *)malloc(n * sizeof(int));
    int *melhor_rota = (int *)malloc(n * sizeof(int));
    int melhor_custo = INF;

    rota_atual[0] = origem;
    visitado[origem] = 1;
    tsp_forca_bruta_rec(g, origem, rota_atual, visitado, 1, 0, &melhor_custo, melhor_rota);

    for (int i = 0; i < n; i++){
        rota[i] = melhor_rota[i];
    }

    free(visitado);
    free(rota_atual);
    free(melhor_rota);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(GrafoTSP *g, int origem, int *rota){
    int n = g->num_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    int atual = origem;
    int custo = 0;

    rota[0] = origem;
    visitado[origem] = 1;

    for (int i = 1; i < n; i++){
        int proximo = -1;
        for (int v = 0; v < n; v++){
            if (!visitado[v] && (proximo == -1 || g->distancias[atual][v] < g->distancias[atual][proximo])){
                proximo = v;
            }
        }
        visitado[proximo] = 1;
        rota[i] = proximo;
        custo += g->distancias[atual][proximo];
        atual = proximo;
    }

    custo += g->distancias[atual][origem];
    free(visitado);
    return custo;
}

int tsp_insercao(GrafoTSP *g, int origem, int *rota){
    int n = g->num_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    int tamanho = 1;

    rota[0] = origem;
    visitado[origem] = 1;

    while (tamanho < n){
        // escolhe o vertice mais proximo de qualquer vertice ja presente na rota
        int mais_proximo = -1;
        int menor_distancia = INF;
        for (int v = 0; v < n; v++){
            if (visitado[v]){
                continue;
            }
            for (int i = 0; i < tamanho; i++){
                int distancia = g->distancias[v][rota[i]];
                if (distancia < menor_distancia){
                    menor_distancia = distancia;
                    mais_proximo = v;
                }
            }
        }

        // insere o vertice na aresta de menor custo adicional
        int melhor_posicao = 0;
        int melhor_custo = INF;
        for (int i = 0; i < tamanho; i++){
            int a = rota[i];
            int b = rota[(i + 1) % tamanho];
            int custo = g->distancias[a][mais_proximo] + g->distancias[mais_proximo][b] - g->distancias[a][b];
            if (custo < melhor_custo){
                melhor_custo = custo;
                melhor_posicao = i;
            }
        }

        for (int i = tamanho; i > melhor_posicao + 1; i--){
            rota[i] = rota[i - 1];
        }
        rota[melhor_posicao + 1] = mais_proximo;
        visitado[mais_proximo] = 1;
        tamanho++;
    }

    int custo = 0;
    for (int i = 0; i < n; i++){
        custo += g->distancias[rota[i]][rota[(i + 1) % n]];
    }

    free(visitado);
    return custo;
}
