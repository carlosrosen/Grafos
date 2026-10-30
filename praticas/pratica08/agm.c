#include "agm.h"
#include <limits.h>
#include <stdlib.h>

// estruturas do min-heap utilizado pelo prim
typedef struct {
    int vertice;
    int chave;
} ItemHeap;

typedef struct {
    ItemHeap *itens;
    int *posicao;
    int tamanho;
} MinHeap;

static MinHeap *inicializar_heap(int capacidade){
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->itens = (ItemHeap *)malloc(capacidade * sizeof(ItemHeap));
    h->posicao = (int *)malloc(capacidade * sizeof(int));
    h->tamanho = 0;
    for (int i = 0; i < capacidade; i++){
        h->posicao[i] = -1;
    }
    return h;
}

static void liberar_heap(MinHeap *h){
    free(h->itens);
    free(h->posicao);
    free(h);
}

static void trocar(MinHeap *h, int i, int j){
    ItemHeap temp = h->itens[i];
    h->itens[i] = h->itens[j];
    h->itens[j] = temp;
    h->posicao[h->itens[i].vertice] = i;
    h->posicao[h->itens[j].vertice] = j;
}

static void subir(MinHeap *h, int i){
    while (i > 0){
        int pai = (i - 1) / 2;
        if (h->itens[pai].chave <= h->itens[i].chave) break;
        trocar(h, i, pai);
        i = pai;
    }
}

static void descer(MinHeap *h, int i){
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;
    int menor = i;

    if (esquerda < h->tamanho && h->itens[esquerda].chave < h->itens[menor].chave){
        menor = esquerda;
    }
    if (direita < h->tamanho && h->itens[direita].chave < h->itens[menor].chave){
        menor = direita;
    }

    if (menor != i){
        trocar(h, i, menor);
        descer(h, menor);
    }
}

static void inserir_heap(MinHeap *h, int vertice, int chave){
    h->itens[h->tamanho].vertice = vertice;
    h->itens[h->tamanho].chave = chave;
    h->posicao[vertice] = h->tamanho;
    h->tamanho++;
    subir(h, h->tamanho - 1);
}

static ItemHeap extrair_min(MinHeap *h){
    ItemHeap raiz = h->itens[0];
    h->posicao[raiz.vertice] = -1;
    h->tamanho--;

    if (h->tamanho > 0){
        h->itens[0] = h->itens[h->tamanho];
        h->posicao[h->itens[0].vertice] = 0;
        descer(h, 0);
    }

    return raiz;
}

static void diminuir_chave(MinHeap *h, int vertice, int nova_chave){
    int i = h->posicao[vertice];
    if (i < 0 || nova_chave >= h->itens[i].chave) return;

    h->itens[i].chave = nova_chave;
    subir(h, i);
}

// funcoes do union-find
DSU *inicializar_dsu(int n){
    DSU *d = (DSU *)malloc(sizeof(DSU));
    d->pai = (int *)malloc(n * sizeof(int));
    d->rank = (int *)malloc(n * sizeof(int));
    d->n = n;

    for (int i = 0; i < n; i++){
        d->pai[i] = i;
        d->rank[i] = 0;
    }

    return d;
}

void liberar_dsu(DSU *d){
    free(d->pai);
    free(d->rank);
    free(d);
}

int find(DSU *d, int x){
    // compressao de caminho
    if (d->pai[x] != x){
        d->pai[x] = find(d, d->pai[x]);
    }
    return d->pai[x];
}

int unir(DSU *d, int x, int y){
    int raiz_x = find(d, x);
    int raiz_y = find(d, y);

    if (raiz_x == raiz_y) return 0;

    // uniao por rank
    if (d->rank[raiz_x] < d->rank[raiz_y]){
        int temp = raiz_x;
        raiz_x = raiz_y;
        raiz_y = temp;
    }

    d->pai[raiz_y] = raiz_x;
    if (d->rank[raiz_x] == d->rank[raiz_y]){
        d->rank[raiz_x]++;
    }

    return 1;
}

static int comparar_arestas(const void *a, const void *b){
    const Aresta *aresta_a = (const Aresta *)a;
    const Aresta *aresta_b = (const Aresta *)b;

    if (aresta_a->peso < aresta_b->peso) return -1;
    if (aresta_a->peso > aresta_b->peso) return 1;
    return 0;
}

int kruskal(int num_vertices, Aresta *arestas, int num_arestas, Aresta *agm){
    if (num_vertices <= 0 || num_arestas <= 0) return 0;

    Aresta *ordenadas = (Aresta *)malloc(num_arestas * sizeof(Aresta));
    for (int i = 0; i < num_arestas; i++){
        ordenadas[i] = arestas[i];
    }

    qsort(ordenadas, num_arestas, sizeof(Aresta), comparar_arestas);

    DSU *d = inicializar_dsu(num_vertices);
    int qtd_arestas = 0;

    for (int i = 0; i < num_arestas && qtd_arestas < num_vertices - 1; i++){
        if (unir(d, ordenadas[i].u, ordenadas[i].v)){
            agm[qtd_arestas] = ordenadas[i];
            qtd_arestas++;
        }
    }

    liberar_dsu(d);
    free(ordenadas);
    return qtd_arestas;
}

int prim(GrafoListaPonderado *g, int origem, Aresta *agm){
    if (g == NULL || g->num_vertices <= 0) return 0;
    if (origem < 0 || origem >= g->num_vertices) return 0;

    int n = g->num_vertices;
    int *chave = (int *)malloc(n * sizeof(int));
    int *pai = (int *)malloc(n * sizeof(int));
    MinHeap *h = inicializar_heap(n);

    for (int i = 0; i < n; i++){
        chave[i] = INT_MAX;
        pai[i] = -1;
    }
    chave[origem] = 0;

    for (int i = 0; i < n; i++){
        inserir_heap(h, i, chave[i]);
    }

    int qtd_arestas = 0;

    while (h->tamanho > 0){
        ItemHeap item = extrair_min(h);
        int u = item.vertice;

        // vertices inalcancaveis a partir da origem encerram a AGM
        if (item.chave == INT_MAX) break;

        if (pai[u] != -1){
            agm[qtd_arestas].u = pai[u];
            agm[qtd_arestas].v = u;
            agm[qtd_arestas].peso = item.chave;
            qtd_arestas++;
        }

        for (No *aresta = g->adj[u]; aresta != NULL; aresta = aresta->prox){
            int v = aresta->vertice;

            // apenas vertices que ainda estao no heap podem ter a chave reduzida
            if (h->posicao[v] >= 0 && aresta->peso < chave[v]){
                chave[v] = aresta->peso;
                pai[v] = u;
                diminuir_chave(h, v, aresta->peso);
            }
        }
    }

    liberar_heap(h);
    free(chave);
    free(pai);
    return qtd_arestas;
}
