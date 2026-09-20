#ifndef FILA_H
#define FILA_H

// Estrutura de fila que montei para utilizar na função eh_bipartido

typedef struct{
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila* inicializar_fila(int capacidade);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
void liberar_fila(Fila *f);

#endif
