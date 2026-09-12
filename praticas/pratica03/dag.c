#include "dag.h"
#include <stdlib.h>
#include <string.h>

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

void liberar_pilha(Pilha *p){
    free(p->dados);
    free(p);
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho){
    int n = g->num_vertices;
    int *grau_entrada = (int *)calloc(n, sizeof(int));
    int *resultado = (int *)malloc(n * sizeof(int));
    Fila *f = inicializar_fila(n); 
    int pos = 0;
    for(int u = 0; u < n; u++){
        for (No *p = g->adj[u]; p != NULL; p = p->prox){
            grau_entrada[p->vertice]++;
        }
    }
    for (int i = 0; i < n; i++){
        if (grau_entrada[i] == 0){
            enfileirar(f, i);
        }
    }
    while (f->tamanho > 0){
        int u = desenfileirar(f);
        resultado[pos++] = u;
        for (No *p = g->adj[u]; p != NULL; p = p->prox){
            grau_entrada[p->vertice]--;
            if (grau_entrada[p->vertice] == 0){
                enfileirar(f, p->vertice);
            }
        }
    }
    free(grau_entrada);
    liberar_fila(f); 
    // deteccao de ciclos
    if (pos != n){
        free(resultado);
        *tamanho = 0;
        return NULL; 
    }
    *tamanho = n;
    return resultado;
}

int dfs_topologica(GrafoLista *g, int u, int *cor, Pilha *p){
    cor[u] = 1;
    No *atual = g->adj[u];
    while(atual != NULL){
        int v = atual->vertice;
        if(cor[v] == 1){ 
            return 0; 
        }
        if(cor[v] == 0){ 
            if(!dfs_topologica(g, v, cor, p)){
                return 0; 
            }
        }
        atual = atual->prox;
    }
    cor[u] = 2; 
    empilhar(p, u); 
    return 1;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho){
    int n = g->num_vertices;
    int *cor = (int *)calloc(n, sizeof(int)); 
    Pilha *p = inicializar_pilha(n);
    for (int i = 0; i < n; i++){
        if (cor[i] == 0){
            if (!dfs_topologica(g, i, cor, p)){
                free(cor);
                liberar_pilha(p);
                *tamanho = 0;
                return NULL; 
            }
        }
    }
    int *resultado = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        resultado[i] = desempilhar(p); 
    }
    free(cor);
    liberar_pilha(p);
    *tamanho = n;
    return resultado;
}

int eh_dag(GrafoLista *g){
    int tamanho;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if(ordem != NULL){
        free(ordem);
        return 1;
    }
    return 0;
}
