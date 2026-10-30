#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

static const char *nomes[] = {"A", "B", "C", "D", "E", "F"};

// passa as arestas do grafo pra um vetor, sem duplicar, pro Kruskal ordenar.
static Aresta *coletar_arestas(GrafoListaPonderado *g, int *num_arestas){
    int total = 0;
    // cada aresta nao direcionada aparece duas vezes na lista de adjacencia
    for (int u = 0; u < g->num_vertices; u++){
        for (No *no = g->adj[u]; no != NULL; no = no->prox){
            if (u < no->vertice){
                total++;
            }
        }
    }
    Aresta *arestas = (Aresta *)malloc(total * sizeof(Aresta));
    int indice = 0;
    for (int u = 0; u < g->num_vertices; u++){
        for (No *no = g->adj[u]; no != NULL; no = no->prox){
            if (u < no->vertice){
                arestas[indice].u = u;
                arestas[indice].v = no->vertice;
                arestas[indice].peso = no->peso;
                indice++;
            }
        }
    }
    *num_arestas = total;
    return arestas;
}

static void imprimir_agm(const char *titulo, Aresta *agm, int qtd_arestas){
    int peso_total = 0;
    printf("%s\n", titulo);
    for (int i = 0; i < qtd_arestas; i++){
        printf("  %s - %s (peso %d)\n", nomes[agm[i].u], nomes[agm[i].v], agm[i].peso);
        peso_total += agm[i].peso;
    }
    printf("Peso total: %d\n\n", peso_total);
}

int main(){
    int n1 = 6;

    // grafo solicitado em sala pra ser utilizado para teste
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

    int num_arestas;
    Aresta *arestas = coletar_arestas(g1, &num_arestas);
    Aresta *agm_kruskal = (Aresta *)malloc(n1 * sizeof(Aresta));
    Aresta *agm_prim = (Aresta *)malloc(n1 * sizeof(Aresta));

    int qtd_kruskal = kruskal(n1, arestas, num_arestas, agm_kruskal);
    int qtd_prim = prim(g1, 0, agm_prim);

    printf("=========================================\n");
    printf("Arvore Geradora Minima - Kruskal\n");
    printf("=========================================\n\n");
    imprimir_agm("Arestas selecionadas:", agm_kruskal, qtd_kruskal);

    printf("=========================================\n");
    printf("Arvore Geradora Minima - Prim\n");
    printf("=========================================\n\n");
    imprimir_agm("Arestas selecionadas:", agm_prim, qtd_prim);

    free(arestas);
    free(agm_kruskal);
    free(agm_prim);
    liberar_grafo(g1);
    return 0;
}
