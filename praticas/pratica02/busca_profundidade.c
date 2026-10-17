#include "busca_profundidade.h"
#include <stdio.h>
#include <stdlib.h>

Pilha* inicializar_pilha(int capacidade){
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->dados = (int *)malloc(capacidade * sizeof(int));
    p->capacidade = capacidade;
    p->topo = -1;
    return p;
}

void empilhar(Pilha *p, int valor){
    if(p->topo < p->capacidade - 1){
        (p->topo)++;
        p->dados[p->topo] = valor;
    }
}

int desempilhar(Pilha *p){
    if(p->topo >= 0){
        int valor = p->dados[p->topo];
        (p->topo)--;
        return valor;
    }
    return -1;
}

void liberar_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo_entrada, int *tempo_saida, int *tempo_global, Pilha *p){
    visitado[u] = 1;
    empilhar(p, u);
    (*tempo_global)++;
    tempo_entrada[u] = *tempo_global;
    No *atual = g->adj[u];
    while(atual != NULL){
        int v = atual->vertice;
        if(!visitado[v]){
            dfs_recursiva(g, v, visitado, tempo_entrada, tempo_saida, tempo_global, p);
        }
        atual = atual->prox;
    }
    (*tempo_global)++;
    tempo_saida[u] = *tempo_global;
}

int dfs_ciclo(GrafoLista *g, int u, int *visitado, int pai){
    visitado[u] = 1;
    No *atual = g->adj[u];
    while(atual != NULL){
        int v = atual->vertice;
        if(!visitado[v]){
            if (dfs_ciclo(g, v, visitado, u)) return 1;
        }else if(v != pai){
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = (int *)calloc(g->num_vertices, sizeof(int));
    for(int i = 0; i < g->num_vertices; i++) {
        if(visitado[i] == 0){
            if(dfs_ciclo(g, i, visitado, -1)){
                free(visitado);
                return 1;
            }
        }
    }
    free(visitado);
    return 0;
}
