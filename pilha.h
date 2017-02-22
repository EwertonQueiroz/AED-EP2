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

// Tipo de dado respons�vel pelas coordenadas.
typedef struct {int x; int y;} Ponto;

// Fun��o respons�vel por iniciar a pilha est�tica.
// Esta fun��o atribui -1 ao topo da pilha.
void pilha_iniciar ();

// Fun��o respons�vel por informar se a pilha est� vazia, para impedir stack underflow.
// Esta fun��o verifica se o topo da pilha � -1, se for, devolve 1 informando que sim, a pilha est� vazia.
// Caso contr�rio devolve 0.
static int pilha_vazia ();

// Fun��o respons�vel por informar se a pilha est� cheia, para impedir stack overflow.
// Esta fun��o verifica se o topo da pilha � 999 (MAX - 1), se for, devolve 1 informando que sim, a pilha est� cheia.
// Caso contr�rio devolve 0.
static int pilha_cheia ();

// Fun��o que informa o tamanho da pilha.
// Esta fun��o verificar o valor do topo da pilha, soma 1 e devolve o mesmo.
int pilha_tamanho ();

// Fun��o respons�vel por empilhar os pontos.
// Esta fun��o recebe um dado do tipo Ponto e verifica se a pilha est� cheia.
// Se estiver, ela imprime uma mensagem informando que a pilha est� cheia.
// Se n�o estiver, ela empilha o ponto recebido nos par�metros e incrementa o valor do topo em uma unidade.
void push (Ponto p);

// Fun��o respons�vel por desempilhar os pontos.
// Esta fun��o verifica se a pilha est� vazia.
// Se estiver, ela imprime uma mensagem informando que a pilha est� vazia.
// Se n�o estiver, ela diminui o valor do topo em uma unidade e devolve o elemento Ponto que est� nessa posi��o.
Ponto pop ();

#endif // _PILHA_H

