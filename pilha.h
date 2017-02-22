/**
 * Universidade Federal Rural de Pernambuco
 * Discente: Ewerton Queiroz
 * Disciplina: Algoritmos e Estruturas de Dados
 * Data: 18/02/2016
 * Atividade: EP2
 */

#ifndef _PILHA_H
#define _PILHA_H
#define MAX 1000

// Tipo de dado responsável pelas coordenadas.
typedef struct {int x; int y;} Ponto;

// Função responsável por iniciar a pilha estática.
// Esta função atribui -1 ao topo da pilha.
void pilha_iniciar ();

// Função responsável por informar se a pilha está vazia, para impedir stack underflow.
// Esta função verifica se o topo da pilha é -1, se for, devolve 1 informando que sim, a pilha está vazia.
// Caso contrário devolve 0.
static int pilha_vazia ();

// Função responsável por informar se a pilha está cheia, para impedir stack overflow.
// Esta função verifica se o topo da pilha é 999 (MAX - 1), se for, devolve 1 informando que sim, a pilha está cheia.
// Caso contrário devolve 0.
static int pilha_cheia ();

// Função que informa o tamanho da pilha.
// Esta função verificar o valor do topo da pilha, soma 1 e devolve o mesmo.
int pilha_tamanho ();

// Função responsável por empilhar os pontos.
// Esta função recebe um dado do tipo Ponto e verifica se a pilha está cheia.
// Se estiver, ela imprime uma mensagem informando que a pilha está cheia.
// Se não estiver, ela empilha o ponto recebido nos parâmetros e incrementa o valor do topo em uma unidade.
void push (Ponto p);

// Função responsável por desempilhar os pontos.
// Esta função verifica se a pilha está vazia.
// Se estiver, ela imprime uma mensagem informando que a pilha está vazia.
// Se não estiver, ela diminui o valor do topo em uma unidade e devolve o elemento Ponto que está nessa posição.
Ponto pop ();

#endif // _PILHA_H

