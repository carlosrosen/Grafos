#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    printf("matriz de adjacencia:\n");
    GrafoMatriz *gm = criar_grafo_matriz(5);
    inserir_aresta_matriz(gm, 0, 1);
    inserir_aresta_matriz(gm, 0, 4);
    inserir_aresta_matriz(gm, 1, 2);
    inserir_aresta_matriz(gm, 1, 3);
    inserir_aresta_matriz(gm, 1, 4);
    inserir_aresta_matriz(gm, 2, 3);
    inserir_aresta_matriz(gm, 3, 4);
    printf("grau do vertice 1: %d\n", grau_matriz(gm, 1));
    printf("0 e 1 sao adjacentes? %d\n", sao_adjacentes_matriz(gm, 0, 1)); 
    printf("0 e 2 sao adjacentes? %d\n", sao_adjacentes_matriz(gm, 0, 2)); 
    remover_aresta_matriz(gm, 0, 1);
    printf("0 e 1 ainda sao adjacentes apos a remocao? %d\n", sao_adjacentes_matriz(gm, 0, 1));
    liberar_grafo_matriz(gm);

    printf("\nlista de adjacencia:\n");
    GrafoLista *gl = criar_grafo_lista(5);
    inserir_aresta_lista(gl, 0, 1);
    inserir_aresta_lista(gl, 0, 4);
    inserir_aresta_lista(gl, 1, 2);
    inserir_aresta_lista(gl, 1, 3);
    inserir_aresta_lista(gl, 1, 4);
    inserir_aresta_lista(gl, 2, 3);
    inserir_aresta_lista(gl, 3, 4);
    printf("grau do vertice 1: %d\n", grau_lista(gl, 1));
    printf("0 e 1 sao adjacentes? %d\n", sao_adjacentes_lista(gl, 0, 1));
    printf("0 e 2 sao adjacentes? %d\n", sao_adjacentes_lista(gl, 0, 2));
    remover_aresta_lista(gl, 0, 1);
    printf("0 e 1 ainda sao adjacentes apos a remocao? %d\n", sao_adjacentes_lista(gl, 0, 1));
    liberar_grafo_lista(gl);
    return 0;
}
