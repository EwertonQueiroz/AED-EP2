/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 */

#ifndef _PILHA_H
#define _PILHA_H
#define MAX 100

typedef struct {
    int x;
    int y;
} Coordenada;

typedef struct pilha Pilha;

Pilha * criar_pilha ();

void liberar_pilha (Pilha *pi);

int verificar_tamanho_pilha (Pilha *pi);

#endif // _PILHA_H

