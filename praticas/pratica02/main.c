#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main() {
    int qtd_vertices = 5;
    GrafoLista *g = inicializar_grafo(qtd_vertices);

    // grafo simples para teste
    inserir_aresta(g, 0, 1);
    inserir_aresta(g, 0, 2);
    inserir_aresta(g, 1, 3);
    inserir_aresta(g, 2, 4);

    printf("Componentes conexos: %d\n", contar_componentes(g));
    printf("Bipartido: %d\n", eh_bipartido(g));
    printf("Tem ciclo: %d\n\n", tem_ciclo(g));

    // BFS
    int *dist = malloc(qtd_vertices * sizeof(int));
    int *pred = malloc(qtd_vertices * sizeof(int));
    for (int i = 0; i < qtd_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    bfs(g, 0, dist, pred);
    printf("Teste BFS:\n");
    for (int i = 0; i < qtd_vertices; i++) {
        printf("v: %d, dist: %d, pred: %d\n", i, dist[i], pred[i]);
    }

    // DFS
    int *visitado = calloc(qtd_vertices, sizeof(int));
    int *t_in = calloc(qtd_vertices, sizeof(int));
    int *t_out = calloc(qtd_vertices, sizeof(int));
    int tempo = 0;
    Pilha *p = inicializar_pilha(qtd_vertices);

    dfs_recursiva(g, 0, visitado, t_in, t_out, &tempo, p);
    printf("\nTeste DFS:\n");
    for (int i = 0; i < qtd_vertices; i++) {
        printf("v: %d, in: %d, out: %d\n", i, t_in[i], t_out[i]);
    }

    // forcando um ciclo pra ver se as funcoes atualizam certo
    printf("\nAdicionando aresta (3,4) para criar um ciclo\n");
    inserir_aresta(g, 3, 4);

    printf("Bipartido: %d\n", eh_bipartido(g));
    printf("Tem ciclo: %d\n", tem_ciclo(g));

    free(dist);
    free(pred);
    free(visitado);
    free(t_in);
    free(t_out);
    liberar_pilha(p);
    liberar_grafo(g);
    return 0;
}