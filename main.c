/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 *
 * ADICIONAR O SEGUINTE ARGUMENTO AO COMPILAR: -std = c99
 *
 * O arquivo lido � no seguinte formato:
 *      Primeira linha: tamanho do labirinto
 *      Segunda linha: dois inteiros que determinar�o a posi��o inicial
 *      Terceira linha: dois inteiros que determinar�o a posi��o final
 *      Quarta linha at� o final do arquivo: linhas correspondentes ao labirinto, essas linhas devem conter a quantidade de 0 ou 1
 *                                           informada pela primeira linha.
 *
 * Caso queira verificar o formato o arquivo utilizado nos testes, verifique o reposit�rio do projeto no GitHub:
 *      https://github.com/EwertonQueiroz/AED-EP2/
 *
 * Atentar para o fato de que n�o h� verifica��o da integridade do arquivo, ou seja, se as linhas correspondentes a matriz estiverem
 * erradas, o programa funcionar� de maneira inesperada.
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

// Esta fun��o recebe o endere�o do arquivo .dat nos par�metros, atribui o primeiro valor lido � vari�vel tamanho,
// os pr�ximos dois valores lidos que s�o correspondentes � posi��o inicial s�o atribuidos ao vetor in�cio,
// depois, os pr�ximos dois valores lidos que s�o correspondentes � posi��o final s�o atribuidos ao vetor fim.
// Posteriormente, com um la�o de repeti��o iniciando em 0 e indo at� o dobro do tamanho, todos os valores lidos
// que correspondem �s posi��es do labirinto s�o atribuidos ao vetor aux e a leitura do arquivo � encerrada.
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

// Esta fun��o recebe o vetor contendo as posi��es do labirinto e a matriz que ser� o labirinto em si e
// atribui os valores do vetor � matriz por meio de um la�o de repeti��o.
void preencher_matriz (int v[], int matriz[][tamanho]) {
    int a = 0;
    for (int i = 0; i < sizeof (matriz[i]) / sizeof (int); i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = v[a++];
        }
    }
}

// Esta fun��o � exclusiva para observar se a matriz do labirinto est� igual � matriz lida no arquivo.
void imprimir_labirinto (int matriz[][tamanho]) {
    for (int i = 0; i < sizeof (matriz[i]) / sizeof (int); i++) {
        for (int j = 0; j < sizeof (matriz[j]) / sizeof (int); j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

// Esta fun��o recebe por par�metros os �ndices de linha e coluna da matriz do labirinto e recebe tamb�m a pr�pria matriz do labirinto.
// Ela verifica se a posi��o da matriz nos �ndices informados � uma posi��o v�lida para movimenta��o ou n�o e retorna 1 se for e 0 n�o for.
int posicao_valida (int x, int y, int matriz [][tamanho]) {
    if (matriz[x][y] == 0 && x >= 0 && x < tamanho && y >= 0 && y < tamanho)
        return 1;

    else
        return 0;
}

// Esta fun��o resolve o labirinto de forma recursiva. Ela recebe por par�metros a posi��o atual em x, a posi��o atual em y, a posi��o final em x,
// a posi��o final em y, o vetor contendo as posi��es iniciais, vetor este que foi preenchido na leitura do arquivo, a matriz que cont�m o labirinto
// e a pilha de pontos.
// Ela cont�m uma vari�vel de controle da pilha chamada "z", esta vari�vel serve para saber o tamanho da pilha para empilhar os pontos corretamente.
// A fun��o verifica primeiramente se a posi��o atual � igual a posi��o final, se for, ela marca -1 na posi��o atual e devolve 1.
// Caso contr�rio, ela passa a verificar se as posi��es adjacentes a atual s�o v�lidas, se sim, a posi��o adjacente � empilhada, � marcado -1 naquela
// posi��o e � feita uma chamada recursiva para esta posi��o adjancente, se n�o, ela desempilha o �ltimo ponto adicionado e devolve 0.
// Se ap�s todas as chamadas recursivas, o valor devolvido for 1, significa que o labirinto tem solu��o, caso contr�rio, n�o h� solu��o dispon�vel para
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

// Esta fun��o recebe o endere�o da pilha, desempilha os valores que est�o empilhados e os imprime.
void imprimir_pilha (Ponto *ponto) {
    for (int i = pilha_tamanho(); i > 0; i--) {
        ponto[i] = pop();
        printf("(%d, %d)\n", ponto[i].x, ponto[i].y);
    }
}
