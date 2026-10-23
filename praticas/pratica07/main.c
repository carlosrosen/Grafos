#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

static const char *nomes[] = {"A", "B", "C", "D", "E", "F"};

static void imprimir_caminho(int *pred, int vertice){
    if (pred[vertice] == -1){
        printf("%s", nomes[vertice]);
        return;
    }
    imprimir_caminho(pred, pred[vertice]);
    printf(" -> %s", nomes[vertice]);
}

int main(){
    printf("=========================================\n");
    printf("Grafo sem ciclo negativo\n");
    printf("=========================================\n\n");

    int n1 = 6;

    // utilizando a estrutura do grafo solicitado na aula
    GrafoListaPonderado *g1 = inicializar_grafo(n1); 
    inserir_aresta(g1, 0, 1, 4);  // A-B
    inserir_aresta(g1, 0, 2, 2);  // A-C
    inserir_aresta(g1, 1, 2, 1);  // B-C
    inserir_aresta(g1, 1, 3, 5);  // B-D
    inserir_aresta(g1, 1, 4, 8);  // B-E
    inserir_aresta(g1, 2, 3, 4);  // C-D
    inserir_aresta(g1, 2, 4, 10); // C-E
    inserir_aresta(g1, 3, 4, 2);  // D-E
    inserir_aresta(g1, 3, 5, 1);  // D-F
    inserir_aresta(g1, 4, 5, 3);  // E-F

    int *dist1 = (int *)malloc(n1 * sizeof(int));
    int *pred1 = (int *)malloc(n1 * sizeof(int));

    if (bellman_ford(g1, 0, dist1, pred1)){
        printf("%-8s %-10s %-12s %s\n", "Vertice", "Distancia", "Predecessor", "Caminho");
        for (int i = 0; i < n1; i++){
            printf("%-8s %-10d %-12s ", nomes[i], dist1[i], pred1[i] == -1 ? "-" : nomes[pred1[i]]);
            imprimir_caminho(pred1, i);
            printf("\n");
        }
    } else {
        printf("ciclo negativo detectado.\n");
        reconstruir_ciclo_negativo(g1, dist1, pred1);
    }

    free(dist1);
    free(pred1);
    liberar_grafo(g1);

    printf("\n=========================================\n");
    printf("Grafo com ciclo negativo\n");
    printf("=========================================\n\n");

    GrafoListaPonderado *g2 = inicializar_grafo(n1); 
    inserir_aresta(g2, 0, 1, 4);  
    inserir_aresta(g2, 0, 2, 2); 
    inserir_aresta(g2, 1, 2, 1);  
    inserir_aresta(g2, 1, 3, 5);  
    inserir_aresta(g2, 1, 4, 8);  
    inserir_aresta(g2, 2, 3, -4);  
    inserir_aresta(g2, 2, 4, 10); 
    inserir_aresta(g2, 3, 4, 2);  
    inserir_aresta(g2, 3, 5, 1);  
    inserir_aresta(g2, 4, 5, 3);  

    int *dist2 = (int *)malloc(n1 * sizeof(int));
    int *pred2 = (int *)malloc(n1* sizeof(int));

    if (bellman_ford(g2, 0, dist2, pred2)){
        printf("nenhum ciclo negativo alcancavel.\n");
    } else {
        printf("ciclo negativo detectado.\n");
        reconstruir_ciclo_negativo(g2, dist2, pred2);
    }

    free(dist2);
    free(pred2);
    liberar_grafo(g2);

    return 0;
}
