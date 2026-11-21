#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo_lista.h"
#include "cobertura.h"

const int repeticoes = 1000;

static double tempo_ms(struct timespec inicio, struct timespec fim){
    return (fim.tv_sec - inicio.tv_sec) * 1000.0 + (fim.tv_nsec - inicio.tv_nsec) / 1000000.0;
}

// cria o grafo com os 5 vertices iniciais, ja alocando o tamanho maximo do experimento
static GrafoLista *criar_grafo_inicial(int max_vertices){
    GrafoLista *g = inicializar_grafo(max_vertices);
    g->num_vertices = 5;

    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 0, 2);
    inserir_aresta(g, 1, 4);
    inserir_aresta(g, 2, 3);

    return g;
}

// adiciona os novos vertices e suas arestas ate o grafo atingir n vertices
static void expandir_grafo(GrafoLista *g, int n){
    int anterior = g->num_vertices;

    for (int v = anterior; v < n; v++){
        // liga o novo vertice ao primeiro vertice da etapa, ao anterior e a um intermediario
        inserir_aresta(g, v, v - anterior);
        inserir_aresta(g, v, v - 1);
        inserir_aresta(g, v, v / 2);
    }

    g->num_vertices = n;
}

static int contar_arestas(GrafoLista *g){
    int total = 0;

    for (int u = 0; u < g->num_vertices; u++){
        for (No *no = g->adj[u]; no != NULL; no = no->prox){
            total++;
        }
    }

    return total / 2;
}

static void executar_experimento(void){
    int tamanhos[] = {5, 8, 10, 12, 15};
    int quantidade = sizeof(tamanhos) / sizeof(tamanhos[0]);
    GrafoLista *g = criar_grafo_inicial(tamanhos[quantidade - 1]);

    printf("=========================================\n");
    printf("Experimento: forca bruta x gulosa\n");
    printf("=========================================\n\n");
    printf("%5s %10s %10s %14s %12s %16s\n", "n", "arestas", "BT tam.", "BT tempo (ms)", "Gul. tam.", "Gul. tempo (ms)");

    for (int i = 0; i < quantidade; i++){
        int n = tamanhos[i];

        if (n > g->num_vertices){
            expandir_grafo(g, n);
        }

        int *cobertura = (int *)calloc(n, sizeof(int));
        int tamanho_bt = 0, tamanho_gulosa = 0;
        double tempo_bt, tempo_gulosa;
        struct timespec inicio, fim;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        for (int r = 0; r < repeticoes; r++){
            tamanho_bt = cobertura_minima_bt(g, cobertura);
        }
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo_bt = tempo_ms(inicio, fim) / repeticoes;

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        for (int r = 0; r < repeticoes; r++){
            tamanho_gulosa = cobertura_gulosa(g, cobertura);
        }
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo_gulosa = tempo_ms(inicio, fim) / repeticoes;

        printf("%5d %10d %10d %14.6f %12d %16.6f\n", n, contar_arestas(g), tamanho_bt, tempo_bt, tamanho_gulosa, tempo_gulosa);

        free(cobertura);
    }

    liberar_grafo(g);
    printf("\n");
}

int main(){
    executar_experimento();
    return 0;
}
