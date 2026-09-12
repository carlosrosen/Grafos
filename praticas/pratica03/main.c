#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

int main() {
    GrafoLista *g1 = inicializar_grafo(6);
    inserir_aresta(g1, 5, 2);
    inserir_aresta(g1, 5, 0);
    inserir_aresta(g1, 4, 0);
    inserir_aresta(g1, 4, 1);
    inserir_aresta(g1, 2, 3);
    inserir_aresta(g1, 3, 1);

    printf("g1 e DAG? %d\n", eh_dag(g1));

    int t1;
    int *ordem_kahn = ordenacao_topologica_kahn(g1, &t1);
    
    printf("Kahn: ");
    if (ordem_kahn){
        for(int i = 0; i < t1; i++){
            printf("%d ", ordem_kahn[i]);
        };
        printf("\n");
        free(ordem_kahn);
    } else {
        printf("ciclo detectado\n");
    }

    int t2;
    int *ordem_dfs = ordenacao_topologica_dfs(g1, &t2);
    
    printf("DFS: ");
    if (ordem_dfs){
        for(int i = 0; i < t2; i++){
            printf("%d ", ordem_dfs[i]);
        };
        printf("\n");
        free(ordem_dfs);
    } else {
        printf("ciclo detectado\n");
    }

    liberar_grafo(g1);
    printf("\n");

    // outro grafo para testar o dag com ciclo
    GrafoLista *g2 = inicializar_grafo(3);
    inserir_aresta(g2, 0, 1);
    inserir_aresta(g2, 1, 2);
    inserir_aresta(g2, 2, 0);

    printf("g2 e DAG? %d\n", eh_dag(g2));

    int t3;
    int *kahn_ciclo = ordenacao_topologica_kahn(g2, &t3);
 
    printf("Kahn: ");
    if (kahn_ciclo){
        for(int i = 0; i < t3; i++){
            printf("%d ", kahn_ciclo[i]);
        };
        printf("\n");
        free(kahn_ciclo);
    } else {
        printf("ciclo detectado\n");
    }

    int t4;
    int *dfs_ciclo = ordenacao_topologica_dfs(g2, &t4);
    
    printf("DFS: ");
    if(dfs_ciclo){
        for(int i = 0; i < t4; i++){
            printf("%d ", dfs_ciclo[i]);
        };
        printf("\n");
        free(dfs_ciclo);
    } else {
        printf("ciclo detectado\n");
    }
    liberar_grafo(g2);

    return 0;
}