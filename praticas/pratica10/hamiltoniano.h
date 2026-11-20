#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#include "grafo_lista.h"

int encontrar_caminho_hamiltoniano_bt(GrafoLista *g, int origem, int *caminho);
int encontrar_ciclo_hamiltoniano_bt(GrafoLista *g, int origem, int *caminho);

#endif
