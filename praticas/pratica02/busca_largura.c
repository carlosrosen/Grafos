#include "busca_largura.h"
#include <stdio.h>
#include <stdlib.h>

Fila* inicializar_fila(int capacidade){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->dados = (int *)malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int valor){
    if(f->tamanho == f->capacidade) return;
    f->dados[f->fim++] = valor;
    if (f->fim == f->capacidade) f->fim = 0;
    f->tamanho++;
}

int desenfileirar(Fila *f){
    if(f->tamanho == 0) return -1;
    int valor = f->dados[f->inicio++];
    if(f->inicio == f->capacidade) f->inicio = 0;
    f->tamanho--;
    return valor;
}

void liberar_fila(Fila *f){
    free(f->dados);
    free(f);
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred){
    Fila *f = inicializar_fila(g->num_vertices);
    dist[origem] = 0;
    pred[origem] = -1; 
    enfileirar(f, origem);
    while(f->tamanho > 0){
        int u = desenfileirar(f);
        No *atual = g->adj[u];
        while(atual != NULL){
            int v = atual->vertice;
            if(dist[v] == -1){ 
                dist[v] = dist[u] + 1; 
                pred[v] = u;           
                enfileirar(f, v);
            }
            atual = atual->prox;
        }
    }
    liberar_fila(f);
}

int eh_bipartido(GrafoLista *g){
    int *cor = (int *)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++){
        cor[i] = -1; 
    }
    for (int start = 0; start < g->num_vertices; start++){
        if (cor[start] == -1) {
            Fila *f = inicializar_fila(g->num_vertices);
            cor[start] = 0;
            enfileirar(f, start);
            while (f->tamanho > 0){
                int u = desenfileirar(f);
                No *atual = g->adj[u];
                while (atual != NULL){
                    int v = atual->vertice;
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        enfileirar(f, v);
                    } else if (cor[v] == cor[u]){
                        liberar_fila(f);
                        free(cor);
                        return 0;
                    }
                    atual = atual->prox;
                }
            }
            liberar_fila(f);
        }
    }
    free(cor);
    return 1;
}

int contar_componentes(GrafoLista *g){
    int *dist = (int *)malloc(g->num_vertices * sizeof(int));
    int *pred = (int *)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++){
        dist[i] = -1;
        pred[i] = -1;
    }
    int componentes = 0;
    for (int i = 0; i < g->num_vertices; i++){
        if (dist[i] == -1) {
            bfs(g, i, dist, pred);
            componentes++;
        }
    }
    free(dist);
    free(pred);
    return componentes;
}
