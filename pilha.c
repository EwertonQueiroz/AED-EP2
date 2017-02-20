/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 */

#include <stdlib.h>
#include "pilha.h"

struct Pilha {
    int qtd;
    struct Coordenada coords[MAX];
};

Pilha * criar_pilha () {
    Pilha *pi;

    pi = (Pilha *) malloc(sizeof (struct Pilha));

    if (pi != NULL) {
        pi->qtd = 0;
    }

    return pi;
}

void liberar_pilha (Pilha *pi) {
    free(pi);
}

int verificar_tamanho_pilha (Pilha *pi) {
    if (pi == NULL) {
        return -1;
    }
    else {
        return pi->qtd;
    }
}

int verificar_pilha_cheia (Pilha *pi) {
    if (pilha->valor == )
}

void push (TNo *pilha) {
    pilha[t++] = y;
}
