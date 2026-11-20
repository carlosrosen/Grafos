#ifndef TPS_H
#define TPS_H

#include "grafo_lista.h"

typedef struct {
    int num_vertices;
    int **distancias;
} GrafoTSP;

GrafoTSP *grafo_para_tsp(GrafoLista *g);
void liberar_grafo_tsp(GrafoTSP *g);

int tsp_forca_bruta(GrafoTSP *g, int origem, int *rota);
int tsp_vizinho_mais_proximo(GrafoTSP *g, int origem, int *rota);
int tsp_insercao(GrafoTSP *g, int origem, int *rota);

#endif
