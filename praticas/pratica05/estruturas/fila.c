#include "fila.h"
#include <stdlib.h>

Fila* inicializar_fila(int capacidade){
    Fila *f = (Fila*)malloc(sizeof(Fila));
    f->dados = (int *)malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, int valor){
    if(f->tamanho == f->capacidade) return;
    f->dados[f->fim++] = valor;
    if (f->fim == f->capacidade) f->fim = 0;
    f->tamanho++;
}

int desenfileirar(Fila *f){
    if(f->tamanho == 0) return -1;
    int valor = f->dados[f->inicio++];
    if(f->inicio == f->capacidade) f->inicio = 0;
    f->tamanho--;
    return valor;
}

void liberar_fila(Fila *f){
    free(f->dados);
    free(f);
}
