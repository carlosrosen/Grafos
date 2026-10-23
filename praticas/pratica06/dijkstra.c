#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

MinHeap *criar_min_heap(int capacidade){
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->dados = (NoHeap *)malloc(capacidade * sizeof(NoHeap));
    h->capacidade = capacidade;
    h->tamanho = 0;
    h->posicao = (int *)malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++){
        h->posicao[i] = -1;
    }
    return h;
}

void liberar_min_heap(MinHeap *h){
    free(h->dados);
    free(h->posicao);
    free(h);
}

static void trocar(MinHeap *h, int i, int j){
    NoHeap temp = h->dados[i];
    h->dados[i] = h->dados[j];
    h->dados[j] = temp;
    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

static void subir(MinHeap *h, int i){
    while (i > 0){
        int pai = (i - 1) / 2;
        if (h->dados[pai].distancia <= h->dados[i].distancia){
            break;
        }
        trocar(h, pai, i);
        i = pai;
    }
}

static void descer(MinHeap *h, int i){
    while (1){
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;
        int menor = i;

        if (esquerda < h->tamanho && h->dados[esquerda].distancia < h->dados[menor].distancia){
            menor = esquerda;
        }
        if (direita < h->tamanho && h->dados[direita].distancia < h->dados[menor].distancia){
            menor = direita;
        }
        if (menor == i){
            break;
        }
        trocar(h, i, menor);
        i = menor;
    }
}

void inserir_min_heap(MinHeap *h, int vertice, int distancia){
    if (h->tamanho == h->capacidade){
        return;
    }
    h->dados[h->tamanho].vertice = vertice;
    h->dados[h->tamanho].distancia = distancia;
    h->posicao[vertice] = h->tamanho;
    h->tamanho++;
    subir(h, h->tamanho - 1);
}

NoHeap extrair_minimo(MinHeap *h){
    NoHeap minimo = {-1, INF};

    if (h->tamanho == 0){
        return minimo;
    }

    minimo = h->dados[0];
    h->posicao[minimo.vertice] = -1;
    h->tamanho--;

    if (h->tamanho > 0){
        h->dados[0] = h->dados[h->tamanho];
        h->posicao[h->dados[0].vertice] = 0;
        descer(h, 0);
    }

    return minimo;
}

void diminuir_chave(MinHeap *h, int vertice, int nova_distancia){
    int i = h->posicao[vertice];

    if (i == -1){
        inserir_min_heap(h, vertice, nova_distancia);
        return;
    }
    if (nova_distancia >= h->dados[i].distancia){
        return;
    }

    h->dados[i].distancia = nova_distancia;
    subir(h, i);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred){
    int n = g->num_vertices;

    for (int i = 0; i < n; i++){
        dist[i] = INF;
        pred[i] = -1;
    }

    MinHeap *h = criar_min_heap(n);
    dist[origem] = 0;
    inserir_min_heap(h, origem, 0);

    while (h->tamanho > 0){
        NoHeap u = extrair_minimo(h);

        if (u.distancia > dist[u.vertice]){
            continue;
        }

        No *no = g->adj[u.vertice];
        while (no != NULL){
            int v = no->vertice;
            int nova_distancia = dist[u.vertice] + no->peso;

            if (nova_distancia < dist[v]){
                dist[v] = nova_distancia;
                pred[v] = u.vertice;
                diminuir_chave(h, v, nova_distancia);
            }
            no = no->prox;
        }
    }

    liberar_min_heap(h);
}

void reconstruir_caminho(int origem, int destino, int *pred){
    int passos = 0;
    int atual = destino;

    while (atual != origem && atual != -1){
        atual = pred[atual];
        passos++;
    }

    if (atual != origem){
        printf("Nao existe caminho de %d para %d.\n", origem, destino);
        return;
    }

    int *caminho = (int *)malloc((passos + 1) * sizeof(int));
    atual = destino;
    for (int i = passos; i >= 0; i--){
        caminho[i] = atual;
        atual = pred[atual];
    }

    printf("Caminho de %d para %d: ", origem, destino);
    for (int i = 0; i <= passos; i++){
        printf("%d", caminho[i]);
        if (i < passos){
            printf(" -> ");
        }
    }
    printf("\n");

    free(caminho);
}
