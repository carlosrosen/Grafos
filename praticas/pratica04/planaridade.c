#include "planaridade.h"
#include <stdlib.h>

// para resolver o erro de declaracao implicita
int tentar_caminhos(GrafoLista *g, int pares[][2], int num_pares, int par_atual, int usado[], int principais[], int num_princ);


// busca via dfs um caminho entre dois vertices principais, sem usar vertices principais como intermediarios e sem compartilhar vertices com caminhos ja escolhidos

// ao achar o destino, bloqueia os vertices usados e avanca o backtracking para ligar o proximo par
int dfs_caminho(GrafoLista *g, int atual, int destino, int usado[], int no_caminho[], int principais[], int num_princ, int pares[][2], int num_pares, int par_atual){
    int i, v, pular;
    if(atual == destino){
        for(i = 0; i < g->num_vertices; i++){
            if(no_caminho[i]) usado[i] = 1;
        }
        if(tentar_caminhos(g, pares, num_pares, par_atual + 1, usado, principais, num_princ)) return 1;
        for(i = 0; i < g->num_vertices; i++){
            if(no_caminho[i]) usado[i] = 0;
        }
        return 0;
    }
    No *aux = g->adj[atual];
    while(aux != NULL){
        v = aux->vertice;
        if(usado[v] == 0 && no_caminho[v] == 0){
            pular = 0;
            if(v != destino) {
                for(i = 0; i < num_princ; i++){
                    if(principais[i] == v) pular = 1;
                }
            }
            if(pular == 0){
                if(v != destino) no_caminho[v] = 1;
                if(dfs_caminho(g, v, destino, usado, no_caminho, principais, num_princ, pares, num_pares, par_atual)) return 1;
                if(v != destino) no_caminho[v] = 0;
            }
        }
        aux = aux->prox;
    }
    return 0;
}

// coordena o backtracking para iterar sobre os pares do subgrafo k5 ou k3,3
// retorna 1 apenas se a dfs conseguir traçar caminhos disjuntos para todos eles
int tentar_caminhos(GrafoLista *g, int pares[][2], int num_pares, int par_atual, int usado[], int principais[], int num_princ){
    if(par_atual >= num_pares) return 1;
    int *no_caminho = (int *)calloc(g->num_vertices, sizeof(int));
    int resultado = dfs_caminho(g, pares[par_atual][0], pares[par_atual][1], usado, no_caminho, principais, num_princ, pares, num_pares, par_atual);
    free(no_caminho);
    return resultado;
}

// função recebe a combinacao pronta e testa se ela forma um k5 ou k3,3
int testar_subgrafo(GrafoLista *g, int arr[], int eh_k5){
    int n = g->num_vertices;
    int idx = 0;
    
    if(eh_k5){
        // gera 10 pares do k5
        int pares[10][2];
        for(int i = 0; i < 5; i++){
            for(int j = i + 1; j < 5; j++){
                pares[idx][0] = arr[i];
                pares[idx][1] = arr[j];
                idx++;
            }
        }
        int *usado = (int *)calloc(n, sizeof(int));
        int resposta = tentar_caminhos(g, pares, 10, 0, usado, arr, 5);
        free(usado);
        return resposta;
    } else {
        // gera permutacoes bipartidas do k3,3
        for(int i = 1; i < 6; i++) {
            for (int j = i + 1; j < 6; j++){
                int a[3] = {arr[0], arr[i], arr[j]};
                int b[3];
                int bi = 0;
                // preenche o grupo B com os 3 restantes
                for(int k_idx = 1; k_idx < 6; k_idx++){
                    if(k_idx != i && k_idx != j) b[bi++] = arr[k_idx];
                }
                // gera as 9 arestas cruzadas entre A e B
                int pares[9][2];
                idx = 0;
                for(int ai = 0; ai < 3; ai++){
                    for(int bj = 0; bj < 3; bj++){
                        pares[idx][0] = a[ai];
                        pares[idx][1] = b[bj];
                        idx++;
                    }
                }
                int *usado = (int *)calloc(n, sizeof(int));
                int resposta = tentar_caminhos(g, pares, 9, 0, usado, arr, 6);
                free(usado);
                if(resposta) return 1;
            }
        }
        return 0;
    }
}

// usa recursividade para gerar todas as combinacoes possiveis de k vertices
// ao completar uma combinacao, ele testa o subgrafo e interrompe a procura se o encontrar
int gerar_combinacoes(GrafoLista *g, int arr[], int k, int indice_atual, int inicio, int eh_k5){
    if(indice_atual == k){
        return testar_subgrafo(g, arr, eh_k5);
    }
    for(int i = inicio; i <= g->num_vertices - (k - indice_atual); i++){
        arr[indice_atual] = i;
        if(gerar_combinacoes(g, arr, k, indice_atual + 1, i + 1, eh_k5)){
            return 1; // se ja achou o subgrafo
        }
    }
    return 0; // testou todas as ramificacoes e nao achou
}


// k5 = 1
// k3,3 = 0

// gera combinacoes de 5 vertices e testa se formam k5
int contem_k5(GrafoLista *g){
    if(g->num_vertices < 5) return 0;
    int arr[5];
    return gerar_combinacoes(g, arr, 5, 0, 0, 1); 
}

// gera combinacoes de 6 vertices e testa se formam k3,3
int contem_k33(GrafoLista *g){
    if(g->num_vertices < 6) return 0;
    int arr[6];
    return gerar_combinacoes(g, arr, 6, 0, 0, 0); 
}

int eh_planar_euler(GrafoLista *g){
    int n = g->num_vertices;
    int m = 0;
    if(n < 3) return 1;
    for(int i = 0; i < n; i++){
        No *atual = g->adj[i];
        while(atual != NULL){
            m++;
            atual = atual->prox;
        }
    }
    m = m / 2;
    if(n <= 10){
        if(contem_k5(g) || contem_k33(g)){
            return 0;
        }
        return 1;
    }
    if(m <= 3 * n - 6){
        return 1;
    }
    return 0;
}