/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int aux[100];
int tamanho;
int inicio[2];
int fim[2];

void ler_arquivo (char url[]);
void preencher_matriz (int v[], int matriz[][tamanho]);
void imprimir_labirinto (int matriz[][tamanho]);

int main () {
    // Mudar o nome do arquivo
    char url[] = "labirinto.dat";
    ler_arquivo (url);

    int labirinto[tamanho][tamanho];

    preencher_matriz (aux, labirinto);

    imprimir_labirinto (labirinto);

    Pilha *pi;

    pi = criar_pilha ();

    int x = verificar_tamanho_pilha(pi);

    return 0;
}

void ler_arquivo (char url[]) {
    FILE *arquivo;

    arquivo = fopen (url, "r");

    fscanf (arquivo, "%d", &tamanho);

    fscanf (arquivo, "%d %d", &inicio[0], &inicio[1]);
    fscanf (arquivo, "%d %d", &fim[0], &fim[1]);

    for (int i = 0; i < tamanho * tamanho; i++) {
        fscanf (arquivo, "%d", &aux[i]);
    }

    fclose (arquivo);
}

void preencher_matriz (int v[], int matriz[][tamanho]) {
    int a = 0;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = v[a++];
        }
    }
}

void imprimir_labirinto (int matriz[][tamanho]) {
    for (int i = 0; i < sizeof(matriz[i])/sizeof(int); i++) {
        for (int j = 0; j < sizeof(matriz[j])/sizeof(int); j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}
