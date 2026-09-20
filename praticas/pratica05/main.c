#include <stdio.h>
#include "grafo_lista.h"
#include "coloracao.h"

int main() {
    int num_cores_gulosa, num_cores_wp;
    
    printf("Teste do grafo bipartido (Grafo 1)\n\n");
    GrafoLista *g1 = inicializar_grafo(4);
    inserir_aresta(g1, 0, 1);
    inserir_aresta(g1, 1, 0);
    inserir_aresta(g1, 1, 2);
    inserir_aresta(g1, 2, 1);
    inserir_aresta(g1, 2, 3);
    inserir_aresta(g1, 3, 2);
    inserir_aresta(g1, 3, 0);
    inserir_aresta(g1, 0, 3);

    coloracao_gulosa(g1, &num_cores_gulosa);
    printf("Total de cores: %d\n\n", num_cores_gulosa);

    coloracao_welsh_powell(g1, &num_cores_wp);
    printf("Total de cores: %d\n\n", num_cores_wp);

    if(eh_bipartido(g1)){
        printf("O grafo e bipartido.\n");
    } else{
        printf("O grafo nao e bipartido.\n");
    }
    liberar_grafo(g1);

    printf("\n===================================================\n");

    // Teste com um segundo grafo
    printf("\nTeste do grafo nao bipartido (Grafo 2)\n\n");
    GrafoLista *g2 = inicializar_grafo(3);
    inserir_aresta(g2, 0, 1);
    inserir_aresta(g2, 1, 0);
    inserir_aresta(g2, 1, 2);
    inserir_aresta(g2, 2, 1);
    inserir_aresta(g2, 2, 0);
    inserir_aresta(g2, 0, 2);

    coloracao_gulosa(g2, &num_cores_gulosa);
    printf("Total de cores: %d\n\n", num_cores_gulosa);

    coloracao_welsh_powell(g2, &num_cores_wp);
    printf("Total de cores: %d\n\n", num_cores_wp);

    if(eh_bipartido(g2)){
        printf("O grafo e bipartido.\n");
    } else{
        printf("O grafo nao e bipartido.\n");
    }
    liberar_grafo(g2);
    return 0;
}
