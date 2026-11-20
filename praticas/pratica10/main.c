#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo_lista.h"
#include "hamiltoniano.h"
#include "tps.h"

static void imprimir_rota(int *rota, int n, int fechar){
    for (int i = 0; i < n; i++){
        printf("%d", rota[i]);
        if (i < n - 1 || fechar){
            printf(" -> ");
        }
    }
    if (fechar){
        printf("%d", rota[0]);
    }
    printf("\n");
}

static void testar_hamiltoniano(void){
    printf("=========================================\n");
    printf("Caminho e Ciclo Hamiltoniano\n");
    printf("=========================================\n\n");

    GrafoLista *g = inicializar_grafo(5);
    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 1, 2);
    inserir_aresta(g, 2, 3);
    inserir_aresta(g, 3, 4);
    inserir_aresta(g, 4, 0);
    inserir_aresta(g, 0, 2);

    int *caminho = (int *)malloc(g->num_vertices * sizeof(int));

    if (encontrar_caminho_hamiltoniano_bt(g, 0, caminho)){
        printf("Caminho hamiltoniano a partir de 0: ");
        imprimir_rota(caminho, g->num_vertices, 0);
    } else {
        printf("Nao existe caminho hamiltoniano a partir de 0.\n");
    }

    if (encontrar_ciclo_hamiltoniano_bt(g, 0, caminho)){
        printf("Ciclo hamiltoniano a partir de 0: ");
        imprimir_rota(caminho, g->num_vertices, 1);
    } else {
        printf("Nao existe ciclo hamiltoniano a partir de 0.\n");
    }

    free(caminho);
    liberar_grafo(g);
}

static void testar_tsp(GrafoLista *g){
    int n = g->num_vertices;
    GrafoTSP *tsp = grafo_para_tsp(g);
    int *rota = (int *)malloc(n * sizeof(int));
    clock_t inicio, fim;
    int custo;

    printf("n = %d\n", n);

    inicio = clock();
    custo = tsp_forca_bruta(tsp, 0, rota);
    fim = clock();
    printf("  Forca bruta:          custo %d, tempo %.10f s\n", custo, (double)(fim - inicio) / CLOCKS_PER_SEC);

    inicio = clock();
    custo = tsp_vizinho_mais_proximo(tsp, 0, rota);
    fim = clock();
    printf("  Vizinho mais proximo: custo %d, tempo %.10f s\n", custo, (double)(fim - inicio) / CLOCKS_PER_SEC);

    inicio = clock();
    custo = tsp_insercao(tsp, 0, rota);
    fim = clock();
    printf("  Insercao:             custo %d, tempo %.10f s\n", custo, (double)(fim - inicio) / CLOCKS_PER_SEC);

    printf("\n");
    free(rota);
    liberar_grafo_tsp(tsp);
    liberar_grafo(g);
}

int main(){
    testar_hamiltoniano();

    printf("\n=========================================\n");
    printf("TSP: forca bruta e heuristicas\n");
    printf("=========================================\n\n");

    GrafoLista *g5 = inicializar_grafo(5);
    inserir_aresta(g5, 0, 1);
    inserir_aresta(g5, 1, 2);
    inserir_aresta(g5, 2, 3);
    inserir_aresta(g5, 3, 4);
    inserir_aresta(g5, 4, 0);
    inserir_aresta(g5, 0, 2);
    inserir_aresta(g5, 0, 3);
    testar_tsp(g5);

    GrafoLista *g8 = inicializar_grafo(8);
    inserir_aresta(g8, 0, 1);
    inserir_aresta(g8, 1, 2);
    inserir_aresta(g8, 2, 3);
    inserir_aresta(g8, 3, 4);
    inserir_aresta(g8, 4, 5);
    inserir_aresta(g8, 5, 6);
    inserir_aresta(g8, 6, 7);
    inserir_aresta(g8, 7, 0);
    inserir_aresta(g8, 0, 2);
    inserir_aresta(g8, 3, 5);
    inserir_aresta(g8, 6, 0);
    testar_tsp(g8);

    GrafoLista *g10 = inicializar_grafo(10);
    inserir_aresta(g10, 0, 1);
    inserir_aresta(g10, 1, 2);
    inserir_aresta(g10, 2, 3);
    inserir_aresta(g10, 3, 4);
    inserir_aresta(g10, 4, 5);
    inserir_aresta(g10, 5, 6);
    inserir_aresta(g10, 6, 7);
    inserir_aresta(g10, 7, 8);
    inserir_aresta(g10, 8, 9);
    inserir_aresta(g10, 9, 0);
    inserir_aresta(g10, 0, 2);
    inserir_aresta(g10, 3, 5);
    inserir_aresta(g10, 6, 8);
    inserir_aresta(g10, 9, 1);
    testar_tsp(g10);

    GrafoLista *g12 = inicializar_grafo(12);
    inserir_aresta(g12, 0, 1);
    inserir_aresta(g12, 1, 2);
    inserir_aresta(g12, 2, 3);
    inserir_aresta(g12, 3, 4);
    inserir_aresta(g12, 4, 5);
    inserir_aresta(g12, 5, 6);
    inserir_aresta(g12, 6, 7);
    inserir_aresta(g12, 7, 8);
    inserir_aresta(g12, 8, 9);
    inserir_aresta(g12, 9, 10);
    inserir_aresta(g12, 10, 11);
    inserir_aresta(g12, 11, 0);
    inserir_aresta(g12, 0, 2);
    inserir_aresta(g12, 3, 5);
    inserir_aresta(g12, 6, 8);
    inserir_aresta(g12, 9, 11);
    testar_tsp(g12);

    return 0;
}
