#ifndef COBERTURA_H
#define COBERTURA_H

#include "grafo_lista.h"

int eh_cobertura(GrafoLista *g, int *cobertura);
int cobertura_minima_bt(GrafoLista *g, int *cobertura);
int cobertura_gulosa(GrafoLista *g, int *cobertura);

#endif
