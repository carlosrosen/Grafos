#ifndef GRAFO_LISTA_PONDERADO_H
#define GRAFO_LISTA_PONDERADO_H

typedef struct No {
    int vertice;
    int peso;
    struct No *prox;
} No;

typedef struct {
    int num_vertices;
    No **adj;
} GrafoListaPonderado;

GrafoListaPonderado *inicializar_grafo(int num_vertices);
void inserir_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void inserir_aresta_direcionada(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

#endif
