#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "conectividade.h"
#include "planaridade.h"

int main() {
    int n = 11;
    GrafoLista *g = inicializar_grafo(n);

    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 1, 2);
    inserir_aresta(g, 2, 0);
    inserir_aresta(g, 2, 3);
    inserir_aresta(g, 3, 4);
    inserir_aresta(g, 4, 5);
    inserir_aresta(g, 5, 3);
    inserir_aresta(g, 5, 6);
    inserir_aresta(g, 6, 7);
    inserir_aresta(g, 7, 8);
    inserir_aresta(g, 8, 6);
    inserir_aresta(g, 8, 9);
    inserir_aresta(g, 9, 10);

    int *descoberta = calloc(n, sizeof(int));
    int *low = calloc(n, sizeof(int));
    int *visitado = calloc(n, sizeof(int));
    int tempo = 0;

    printf("Articulacoes:\n");
    dfs_articulacoes(g, 0, -1, descoberta, low, visitado, &tempo);

    tempo = 0;
    for (int i = 0; i < n; i++) {
        descoberta[i] = 0;
        low[i] = 0;
        visitado[i] = 0;
    }

    printf("\nPontes: \n");
    detectar_pontes(g, 0, -1, descoberta, low, visitado, &tempo);

    printf("\nPlanaridade: \n");
    int planar = eh_planar_euler(g);
    if(planar){
      printf("grafo planar\n");
    } else{
      printf("grafo nao planar\n");
    }

    free(descoberta);
    free(low);
    free(visitado);
    liberar_grafo(g);

    return 0;
}