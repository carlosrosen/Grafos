#include <stdlib.h>
#include "hamiltoniano.h"

static int existe_aresta(GrafoLista *g, int u, int v){
    for (No *no = g->adj[u]; no != NULL; no = no->prox){
        if (no->vertice == v){
            return 1;
        }
    }
    return 0;
}

static int hamiltoniano_bt(GrafoLista *g, int atual, int origem, int *caminho, int *visitado, int pos, int ciclo){
    if (pos == g->num_vertices){
        return !ciclo || existe_aresta(g, atual, origem);
    }

    for (No *no = g->adj[atual]; no != NULL; no = no->prox){
        int proximo = no->vertice;
        if (!visitado[proximo]){
            visitado[proximo] = 1;
            caminho[pos] = proximo;
            if (hamiltoniano_bt(g, proximo, origem, caminho, visitado, pos + 1, ciclo)){
                return 1;
            }
            visitado[proximo] = 0;
        }
    }

    return 0;
}

static int encontrar_hamiltoniano_bt(GrafoLista *g, int origem, int *caminho, int ciclo){
    int *visitado = (int *)calloc(g->num_vertices, sizeof(int));

    caminho[0] = origem;
    visitado[origem] = 1;

    int encontrado = hamiltoniano_bt(g, origem, origem, caminho, visitado, 1, ciclo);

    free(visitado);
    return encontrado;
}

int encontrar_caminho_hamiltoniano_bt(GrafoLista *g, int origem, int *caminho){
    return encontrar_hamiltoniano_bt(g, origem, caminho, 0);
}

int encontrar_ciclo_hamiltoniano_bt(GrafoLista *g, int origem, int *caminho){
    return encontrar_hamiltoniano_bt(g, origem, caminho, 1);
}
