/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 *
 * ADICIONAR O SEGUINTE ARGUMENTO AO COMPILAR: -std = c99
 *
 * O arquivo lido é no seguinte formato:
 *      Primeira linha: tamanho do labirinto
 *      Segunda linha: dois inteiros que determinarão a posição inicial
 *      Terceira linha: dois inteiros que determinarão a posição final
 *      Quarta linha até o final do arquivo: linhas correspondentes ao labirinto, essas linhas devem conter a quantidade de 0 ou 1
 *                                           informada pela primeira linha.
 *
 * Caso queira verificar o formato o arquivo utilizado nos testes, verifique o repositório do projeto no GitHub:
 *      https://github.com/EwertonQueiroz/AED-EP2/
 *
 * Atentar para o fato de que não há verificação da integridade do arquivo, ou seja, se as linhas correspondentes a matriz estiverem
 * erradas, o programa funcionará de maneira inesperada.
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
int resolver_labirinto (int comeco_linha, int comeco_coluna, int termino_linha, int termino_coluna, int p_inicial[], int matriz[][tamanho], Ponto *p);

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

    // Estado do labirinto antes de ser resolvido.
    //imprimir_labirinto(labirinto);

    if (resolver_labirinto (pilha[0].x, pilha[0].y, fim[0], fim[1], inicio, labirinto, pilha) == 1)
        imprimir_pilha(pilha);
    else
        printf("\nNao ha solucoes.\n");

    // Estado do labirinto depois de ser resolvido.
    //imprimir_labirinto(labirinto);

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
    if (matriz[x][y] == 0 && x >= 0 && x < tamanho && y >= 0 && y < tamanho)
        return 1;

    else
        return 0;
}

// Esta função resolve o labirinto de forma recursiva. Ela recebe por parâmetros a posição atual em x, a posição atual em y, a posição final em x,
// a posição final em y, o vetor contendo as posições iniciais, vetor este que foi preenchido na leitura do arquivo, a matriz que contém o labirinto
// e a pilha de pontos.
// Ela contém uma variável de controle da pilha chamada "z", esta variável serve para saber o tamanho da pilha para empilhar os pontos corretamente.
// A função verifica primeiramente se a posição atual é igual a posição final, se for, ela marca -1 na posição atual e devolve 1.
// Caso contrário, ela passa a verificar se as posições adjacentes a atual são válidas, se sim, a posição adjacente é empilhada, é marcado -1 naquela
// posição e é feita uma chamada recursiva para esta posição adjancente, se não, ela desempilha o último ponto adicionado e devolve 0.
// Se após todas as chamadas recursivas, o valor devolvido for 1, significa que o labirinto tem solução, caso contrário, não há solução disponível para
// o labirinto informado.
int resolver_labirinto (int comeco_linha, int comeco_coluna, int termino_linha, int termino_coluna, int p_inicial[], int matriz[][tamanho], Ponto *p) {
    z = pilha_tamanho();

    if (comeco_linha == termino_linha && comeco_coluna == termino_coluna) {
        matriz[comeco_linha][comeco_coluna] = -1;
        return 1;
    }

    if (comeco_linha == -1 || comeco_coluna == -1) {
        pop();
        z--;
        return 0;
    }

    // Cima
    if (posicao_valida (comeco_linha - 1, comeco_coluna, matriz)) {
        p[z].x = comeco_linha - 1;
        p[z].y = comeco_coluna;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);

        if (resolver_labirinto (comeco_linha - 1, comeco_coluna, termino_linha, termino_coluna, p_inicial, matriz, p) == 1)
            return 1;
    }

    // Direita
    if (posicao_valida (comeco_linha, comeco_coluna + 1, matriz)) {
        p[z].x = comeco_linha;
        p[z].y = comeco_coluna + 1;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);

        if (resolver_labirinto (comeco_linha, comeco_coluna + 1, termino_linha, termino_coluna, p_inicial, matriz, p) == 1)
            return 1;
    }

    // Baixo
    if (posicao_valida (comeco_linha + 1, comeco_coluna, matriz)) {
        p[z].x = comeco_linha + 1;
        p[z].y = comeco_coluna;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);

        if (resolver_labirinto (comeco_linha + 1, comeco_coluna, termino_linha, termino_coluna, p_inicial, matriz, p) == 1)
            return 1;
    }

    // Esquerda
    if (posicao_valida (comeco_linha, comeco_coluna - 1, matriz)) {
        p[z].x = comeco_linha;
        p[z].y = comeco_coluna - 1;
        matriz[comeco_linha][comeco_coluna] = -1;
        push(p[z++]);

        if (resolver_labirinto (comeco_linha, comeco_coluna - 1, termino_linha, termino_coluna, p_inicial, matriz, p))
            return 1;
    }

    if (comeco_linha == p_inicial[0] && comeco_coluna == p_inicial[1]) {
        matriz[comeco_linha][comeco_coluna] = 0;
    }

    pop();

    return 0;
}

// Esta função recebe o endereço da pilha, desempilha os valores que estão empilhados e os imprime.
void imprimir_pilha (Ponto *ponto) {
    for (int i = pilha_tamanho(); i > 0; i--) {
        ponto[i] = pop();
        printf("(%d, %d)\n", ponto[i].x, ponto[i].y);
    }
}
