#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "grafo_lista_ponderado.h"
#include <limits.h>

#define INF INT_MAX

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred);

#endif
