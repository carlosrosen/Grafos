#ifndef AGM_H
#define AGM_H

#include "grafo_lista_ponderado.h"

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

DSU *inicializar_dsu(int n);
void liberar_dsu(DSU *d);
int find(DSU *d, int x);
int unir(DSU *d, int x, int y);

int kruskal(int num_vertices, Aresta *arestas, int num_arestas, Aresta *agm);
int prim(GrafoListaPonderado *g, int origem, Aresta *agm);

#endif
