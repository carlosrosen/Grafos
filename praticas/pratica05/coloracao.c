#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

void coloracao_gulosa(GrafoLista *g, int *num_cores){
    int n = g->num_vertices;
    int *cor = (int *)malloc(n * sizeof(int));
    int *cor_usada = (int *)malloc(n * sizeof(int));
    
    for(int i = 0; i < n; i++){
        cor[i] = -1;
    }
    for (int i = 0; i < n; i++){
        for(int c = 0; c < n; c++){
            cor_usada[c] = 0;
        }
        No *no = g->adj[i];
        while(no != NULL){
            int v = no->vertice;
            if(cor[v] != -1){
                cor_usada[cor[v]] = 1;
            }
            no = no->prox;
        }
        int c = 0;
        while(cor_usada[c]){
            c++;
        }
        cor[i] = c;
    }

    int max_cor = 0;

    printf("Coloracao gulosa:\n");
    for (int i = 0; i < n; i++){
        printf("Vertice %d: Cor %d\n", i, cor[i]); // debug
        if (cor[i] > max_cor) max_cor = cor[i];
    }

    *num_cores = max_cor + 1;
    free(cor);
    free(cor_usada);
}

void coloracao_welsh_powell(GrafoLista *g, int *num_cores){
    int n = g->num_vertices;
    int *cor = (int *)malloc(n * sizeof(int));
    int *cor_usada = (int *)malloc(n * sizeof(int));
    int *grau = (int *)malloc(n * sizeof(int));
    int *ordem = (int *)malloc(n * sizeof(int));

    //calculo do grau de cada vértice
    for (int i = 0; i < n; i++){
        cor[i] = -1;
        ordem[i] = i;
        grau[i] = 0;
        No *no = g->adj[i];
        while (no != NULL) {
            grau[i]++;
            no = no->prox;
        }
    }

    //ordena os vertices pelo grau em ordem decrescente
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (grau[ordem[i]] < grau[ordem[j]]){
                int temp = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = temp;
            }
        }
    }

    // coloracao na ordem definida
    for (int i = 0; i < n; i++){
        int u = ordem[i];
        for (int c = 0; c < n; c++){
            cor_usada[c] = 0;
        }
        No *no = g->adj[u];
        while (no != NULL){
            int v = no->vertice;
            if (cor[v] != -1){
                cor_usada[cor[v]] = 1;
            }
            no = no->prox;
        }
        int c = 0;
        while (cor_usada[c]){
            c++;
        }
        cor[u] = c;
    }

    int max_cor = 0;
    printf("Coloracao welsh-powell:\n");
    for (int i = 0; i < n; i++){
        printf("Vertice %d: Cor %d\n", i, cor[i]); // debug
        if (cor[i] > max_cor) max_cor = cor[i];
    }
    *num_cores = max_cor + 1;
    free(grau);
    free(ordem);
    free(cor);
    free(cor_usada);
}

int eh_bipartido(GrafoLista *g){
    int *cor = (int *)malloc(g->num_vertices * sizeof(int));
    for(int i = 0; i < g->num_vertices; i++){
        cor[i] = -1; 
    }
    for(int origem = 0; origem < g->num_vertices; origem++){
        if(cor[origem] == -1) {
            Fila *f = inicializar_fila(g->num_vertices);
            cor[origem] = 0;
            enfileirar(f, origem);
            while(f->tamanho > 0){
                int u = desenfileirar(f);
                No *atual = g->adj[u];
                while (atual != NULL){
                    int v = atual->vertice;
                    if(cor[v] == -1){
                        cor[v] = 1 - cor[u];
                        enfileirar(f, v);
                    } else if (cor[v] == cor[u]){
                        liberar_fila(f);
                        free(cor);
                        return 0;
                    }
                    atual = atual->prox;
                }
            }
            liberar_fila(f);
        }
    }
    free(cor);
    return 1;
}