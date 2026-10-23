#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista_ponderado.h"
#include "dijkstra.h"

static const char *nomes[] = {"A", "B", "C", "D", "E", "F"};

static void imprimir_distancias(int origem, int *dist, int n){
    printf("Distancias a partir de %s:\n", nomes[origem]);
    for (int i = 0; i < n; i++){
        if (dist[i] >= INF){
            printf("  %s: inalcancavel\n", nomes[i]);
        } else {
            printf("  %s: %d\n", nomes[i], dist[i]);
        }
    }
    printf("\n");
}

int main() {
    int n1 = 6;
    GrafoListaPonderado *g = inicializar_grafo(n1);

    // estrutura do grafo que foi solicitado pra ser usado nas issues na aula 
    // A=0, B=1, C=2, D=3, E=4, F=5
    inserir_aresta(g, 0, 1, 4);   // A - B
    inserir_aresta(g, 0, 2, 2);   // A - C
    inserir_aresta(g, 1, 2, 1);   // B - C
    inserir_aresta(g, 1, 3, 5);   // B - D
    inserir_aresta(g, 1, 4, 8);   // B - E
    inserir_aresta(g, 2, 3, 4);   // C - D
    inserir_aresta(g, 2, 4, 10);  // C - E
    inserir_aresta(g, 3, 4, 2);   // D - E
    inserir_aresta(g, 3, 5, 1);   // D - F
    inserir_aresta(g, 4, 5, 3);   // E - F

    int *dist = (int *)malloc(n1 * sizeof(int));
    int *pred = (int *)malloc(n1 * sizeof(int));

    printf("Vertices: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F\n\n");

    dijkstra(g, 0, dist, pred);
    imprimir_distancias(0, dist, n1);

    reconstruir_caminho(0, 5, pred);
    reconstruir_caminho(0, 3, pred);
    reconstruir_caminho(0, 4, pred);

    free(dist);
    free(pred);
    liberar_grafo(g);

    return 0;
}
