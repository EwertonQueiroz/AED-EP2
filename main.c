/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 *
 * ADICIONAR O SEGUINTE ARGUMENTO AO COMPILAR: -std = c99
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int aux[100];
int tamanho;
int inicio[2];
int fim[2];
int z;

void ler_arquivo (char url[]);
void preencher_matriz (int v[], int matriz[][tamanho]);
void imprimir_labirinto (int matriz[][tamanho]);
int posicao_valida (int x, int y, int matriz [][tamanho]);
void imprimir_pilha (Ponto *ponto);

int main () {
    // Mudar o nome do arquivo
    char url[] = "labirinto.dat";
    ler_arquivo (url);

    int labirinto[tamanho][tamanho];

    preencher_matriz (aux, labirinto);

    Ponto pilha[MAX];

    pilha[0].x = inicio[0];
    pilha[0].y = inicio[1];

    pilha_iniciar();

    push(pilha[0]);

    teste(pilha[0].x, pilha[0].y, fim[0], fim[1], labirinto, pilha);

    printf("Tamanho da Pilha: %d\n\n", pilha_tamanho());

    imprimir_labirinto(labirinto);

    printf("\n");

    imprimir_pilha(pilha);

    return 0;
}

// Esta função recebe o endereço do arquivo .dat nos parâmetros, atribui o primeiro valor lido à variável tamanho,
// os próximos dois valores lidos que são correspondentes à posição inicial são atribuidos ao vetor início,
// depois, os próximos dois valores lidos que são correspondentes à posição final são atribuidos ao vetor fim.
// Posteriormente, com um laço de repetição iniciando em 0 e indo até o dobro do tamanho, todos os valores lidos
// que correspondem às posições do labirinto são atribuidos ao vetor aux e a leitura do arquivo é encerrada.
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

// Esta função recebe o vetor contendo as posições do labirinto e a matriz que será o labirinto em si e
// atribui os valores do vetor à matriz por meio de um laço de repetição.
void preencher_matriz (int v[], int matriz[][tamanho]) {
    int a = 0;
    for (int i = 0; i < sizeof (matriz[i]) / sizeof (int); i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = v[a++];
        }
    }
}

// Esta função é exclusiva para observar se a matriz do labirinto está igual à matriz lida no arquivo.
void imprimir_labirinto (int matriz[][tamanho]) {
    for (int i = 0; i < sizeof (matriz[i]) / sizeof (int); i++) {
        for (int j = 0; j < sizeof (matriz[j]) / sizeof (int); j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

// Esta função recebe por parâmetros os índices de linha e coluna da matriz do labirinto e recebe também a própria matriz do labirinto.
// Ela verifica se a posição da matriz nos índices informados é uma posição válida para movimentação ou não e retorna 1 se for e 0 não for.
int posicao_valida (int x, int y, int matriz [][tamanho]) {
    if (matriz[x][y] == 0)
        return 1;

    else
        return 0;
}

void teste (int comeco_linha, int comeco_coluna, int termino_linha, int termino_coluna, int matriz[][tamanho], Ponto *p) {
    z = pilha_tamanho();

    if (comeco_linha == termino_linha && comeco_coluna == termino_coluna) {
        p[z].x = comeco_linha;
        p[z].y = comeco_coluna;
        push(p[z++]);
        return;
    }

    if (comeco_linha == -1 || comeco_coluna == -1) {
        pop();
        z--;
        return;
    }

    // Cima
    if (posicao_valida (p[z - 1].x, p[z - 1].y, matriz)) {
        p[z].x = comeco_linha - 1;
        p[z].y = comeco_coluna;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);
        teste (comeco_linha - 1, comeco_coluna, termino_linha, termino_coluna, matriz, p);
    }

    // Direita
    if (posicao_valida (p[z - 1].x, p[z - 1].y, matriz)) {
        p[z].x = comeco_linha;
        p[z].y = comeco_coluna + 1;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);
        teste (comeco_linha, comeco_coluna + 1, termino_linha, termino_coluna, matriz, p);
    }

    // Baixo
    if (posicao_valida (p[z - 1].x, p[z - 1].y, matriz)) {
        p[z].x = comeco_linha + 1;
        p[z].y = comeco_coluna;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);
        teste (comeco_linha + 1, comeco_coluna, termino_linha, termino_coluna, matriz, p);
    }

    // Esquerda
    if (posicao_valida (p[z - 1].x, p[z - 1].y, matriz)) {
        p[z].x = comeco_linha;
        p[z].y = comeco_coluna - 1;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);
        teste (comeco_linha, comeco_coluna - 1, termino_linha, termino_coluna, matriz, p);
    }
    //matriz[comeco_linha][comeco_coluna] = 0;
    z--;
}

// Esta função recebe o endereço da pilha, desempilha os valores que estão empilhados e os imprime.
void imprimir_pilha (Ponto *ponto) {
    for (int i = pilha_tamanho(); i > 0; i--) {
        ponto[i] = pop();
        printf("(%d, %d)\n", ponto[i].x, ponto[i].y);
    }
}
