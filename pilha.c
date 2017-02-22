/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 */

#include <stdlib.h>
#include "pilha.h"

// Pilha indexada de 0 a 999 (MAX - 1).
Ponto pilha[MAX];

// Variável estática para que não possa ser acessada e/ou modificada fora deste módulo.
static int topo;

void pilha_iniciar () {
    topo = -1;
}

// Função estática para que não seja acessada fora deste módulo.
static int pilha_vazia () {
    if (topo == -1)
        return 1;

    else
        return 0;
}

// Função estática para que não seja acessada fora deste módulo.
static int pilha_cheia () {
    if (topo == MAX - 1)
        return 1;

    else
        return 0;
}

int pilha_tamanho () {
    return topo + 1;
}

void push (Ponto p) {
    if (!pilha_cheia ())
        pilha[topo++] = p;

    else
        printf("\nPilha cheia.\n");
}

Ponto pop () {
    if (!pilha_vazia ())
        return pilha[--topo];

    else
        printf("\nPilha vazia.\n");
}
