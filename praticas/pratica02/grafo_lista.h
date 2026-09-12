#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

typedef struct No{
    int vertice;
    struct No *prox;
}No;

typedef struct{
    int num_vertices;
    No **adj;
}GrafoLista;

GrafoLista* inicializar_grafo(int num_vertices);
void inserir_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

#endif 
