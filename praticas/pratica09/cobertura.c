#include <stdlib.h>
#include "cobertura.h"

// verifica se toda aresta tem pelo menos um dos extremos na cobertura
int eh_cobertura(GrafoLista *g, int *cobertura){
    for (int u = 0; u < g->num_vertices; u++){
        for (No *no = g->adj[u]; no != NULL; no = no->prox){
            if (!cobertura[u] && !cobertura[no->vertice]){
                return 0;
            }
        }
    }
    return 1;
}

// procura a primeira aresta com os dois extremos fora da cobertura atual
static int encontrar_aresta_descoberta(GrafoLista *g, int *cobertura, int *u, int *v){
    for (int i = 0; i < g->num_vertices; i++){
        if (cobertura[i]){
            continue;
        }
        for (No *no = g->adj[i]; no != NULL; no = no->prox){
            if (!cobertura[no->vertice]){
                *u = i;
                *v = no->vertice;
                return 1;
            }
        }
    }
    return 0;
}

// inclui um dos extremos da aresta descoberta e poda quando o tamanho atual alcanca o melhor
static void cobertura_bt_rec(GrafoLista *g, int *atual, int tamanho, int *melhor, int *melhor_tamanho){
    if (tamanho >= *melhor_tamanho){
        return;
    }

    int u, v;
    if (!encontrar_aresta_descoberta(g, atual, &u, &v)){
        *melhor_tamanho = tamanho;
        for (int i = 0; i < g->num_vertices; i++){
            melhor[i] = atual[i];
        }
        return;
    }

    atual[u] = 1;
    cobertura_bt_rec(g, atual, tamanho + 1, melhor, melhor_tamanho);
    atual[u] = 0;

    atual[v] = 1;
    cobertura_bt_rec(g, atual, tamanho + 1, melhor, melhor_tamanho);
    atual[v] = 0;
}

int cobertura_minima_bt(GrafoLista *g, int *cobertura){
    int n = g->num_vertices;
    int *atual = (int *)calloc(n, sizeof(int));
    int *melhor = (int *)calloc(n, sizeof(int));
    int melhor_tamanho = n;

    cobertura_bt_rec(g, atual, 0, melhor, &melhor_tamanho);

    for (int i = 0; i < n; i++){
        cobertura[i] = melhor[i];
    }

    free(atual);
    free(melhor);
    return melhor_tamanho;
}

// heuristica gulosa: sempre escolhe o vertice de maior grau no grafo restante
int cobertura_gulosa(GrafoLista *g, int *cobertura){
    int n = g->num_vertices;
    int *grau = (int *)calloc(n, sizeof(int));
    int tamanho = 0;

    for (int u = 0; u < n; u++){
        cobertura[u] = 0;
        for (No *no = g->adj[u]; no != NULL; no = no->prox){
            grau[u]++;
        }
    }

    while (!eh_cobertura(g, cobertura)){
        int escolhido = -1;
        for (int u = 0; u < n; u++){
            if (!cobertura[u] && grau[u] > 0 && (escolhido == -1 || grau[u] > grau[escolhido])){
                escolhido = u;
            }
        }

        if (escolhido == -1){
            break;
        }

        cobertura[escolhido] = 1;
        tamanho++;
        grau[escolhido] = 0;

        for (No *no = g->adj[escolhido]; no != NULL; no = no->prox){
            int v = no->vertice;
            if (!cobertura[v] && grau[v] > 0){
                grau[v]--;
            }
        }
    }

    free(grau);
    return tamanho;
}
