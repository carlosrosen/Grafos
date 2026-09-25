#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "conectividade.h"
#include "planaridade.h"

int main() {
    int n1 = 11, n2 = 10, n3 = 5;

    printf("Grafo 1:\n\n");

    GrafoLista *g1 = inicializar_grafo(n1);
    inserir_aresta(g1, 0, 1);
    inserir_aresta(g1, 1, 2);
    inserir_aresta(g1, 2, 0);
    inserir_aresta(g1, 2, 3);
    inserir_aresta(g1, 3, 4);
    inserir_aresta(g1, 4, 5);
    inserir_aresta(g1, 5, 3);
    inserir_aresta(g1, 5, 6);
    inserir_aresta(g1, 6, 7);
    inserir_aresta(g1, 7, 8);
    inserir_aresta(g1, 8, 6);
    inserir_aresta(g1, 8, 9);
    inserir_aresta(g1, 9, 10);

    int *descoberta = calloc(n1, sizeof(int));
    int *low = calloc(n1, sizeof(int));
    int *visitado = calloc(n1, sizeof(int));
    int tempo = 0;

    printf("Articulacoes:\n");
    dfs_articulacoes(g1, 0, -1, descoberta, low, visitado, &tempo);

    tempo = 0;
    for(int i = 0; i < n1; i++){
        descoberta[i] = 0;
        low[i] = 0;
        visitado[i] = 0;
    }

    printf("\nPontes: \n");
    detectar_pontes(g1, 0, -1, descoberta, low, visitado, &tempo);

    printf("\nPlanaridade: \n");
    int planar = eh_planar_euler(g1);
    if(planar){
      printf("Grafo planar\n");
    } else{
      printf("Grafo nao planar\n");
    }

    free(descoberta);
    free(low);
    free(visitado);
    liberar_grafo(g1);

    printf("\n==============================\n");

    printf("\nGrafo 2 [Grafo de Petersen]:\n\n");

    GrafoLista *g2 = inicializar_grafo(n2);
    inserir_aresta(g2, 0, 1);
    inserir_aresta(g2, 1, 2);
    inserir_aresta(g2, 2, 3);
    inserir_aresta(g2, 3, 4);
    inserir_aresta(g2, 4, 0);
    inserir_aresta(g2, 5, 7);
    inserir_aresta(g2, 7, 9);
    inserir_aresta(g2, 9, 6);
    inserir_aresta(g2, 6, 8);
    inserir_aresta(g2, 8, 5);
    inserir_aresta(g2, 0, 5);
    inserir_aresta(g2, 1, 6);
    inserir_aresta(g2, 2, 7);
    inserir_aresta(g2, 3, 8);
    inserir_aresta(g2, 4, 9);

    descoberta = calloc(n2, sizeof(int));
    low = calloc(n2, sizeof(int));
    visitado = calloc(n2, sizeof(int));
    tempo = 0;

    printf("Articulacoes:\n");
    dfs_articulacoes(g2, 0, -1, descoberta, low, visitado, &tempo);

    tempo = 0;
    for(int i = 0; i < n2; i++){
        descoberta[i] = 0;
        low[i] = 0;
        visitado[i] = 0;
    }

    printf("\nPontes: \n");
    detectar_pontes(g2, 0, -1, descoberta, low, visitado, &tempo);

    printf("\nPlanaridade: \n");
    planar = eh_planar_euler(g2);
    if(planar){
      printf("Grafo planar\n");
    } else{
      printf("Grafo nao planar\n");
    }
    
    free(descoberta);
    free(low);
    free(visitado);
    liberar_grafo(g2);

    printf("\n==============================\n");
    printf("\nGrafo 3 [K5]:\n\n");

    GrafoLista *g3 = inicializar_grafo(n1);
    inserir_aresta(g3, 0, 1);
    inserir_aresta(g3, 0, 2);
    inserir_aresta(g3, 0, 3);
    inserir_aresta(g3, 0, 4);
    inserir_aresta(g3, 1, 2);
    inserir_aresta(g3, 1, 3);
    inserir_aresta(g3, 1, 4);
    inserir_aresta(g3, 2, 3);
    inserir_aresta(g3, 2, 4);
    inserir_aresta(g3, 3, 4);

    descoberta = calloc(n3, sizeof(int));
    low = calloc(n3, sizeof(int));
    visitado = calloc(n3, sizeof(int));
    tempo = 0;

    printf("Articulacoes:\n");
    dfs_articulacoes(g3, 0, -1, descoberta, low, visitado, &tempo);

    tempo = 0;
    for(int i = 0; i < n3; i++){
        descoberta[i] = 0;
        low[i] = 0;
        visitado[i] = 0;
    }

    printf("\nPontes: \n");
    detectar_pontes(g3, 0, -1, descoberta, low, visitado, &tempo);

    printf("\nPlanaridade: \n");
    planar = eh_planar_euler(g3);
    if(planar){
      printf("Grafo planar\n");
    } else{
      printf("Grafo nao planar\n");
    }
    
    free(descoberta);
    free(low);
    free(visitado);
    liberar_grafo(g3);

    return 0;
}