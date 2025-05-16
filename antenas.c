/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */

/**
 * @file antenas.c
 * @author Thiago Abreu
 * @brief Implementação das funções para manipulação da lista ligada de antenas.
 *
 * Este módulo define uma função principal para inserir antenas em uma lista ligada simples,
 * garantindo que a lista permaneça ordenada com base nas coordenadas (x, y) e evitando duplicadas.
 */

#include <stdio.h>
#include <stdlib.h>
#include "antenas.h"

/**
 * @brief Insere uma nova antena na lista ligada em ordem crescente (x, depois y).
 *
 * A função verifica se já existe uma antena na posição especificada. Caso contrário, aloca memória
 * para um novo nó e insere-o mantendo a ordem da lista baseada nas coordenadas.
 *
 * @param lista Apontador para o início da lista ligada de antenas.
 * @param frequencia Caractere que representa a frequência da antena.
 * @param x Posição X da antena.
 * @param y Posição Y da antena.
 * @return Novo apontador para o novo início da lista, ou NULL em caso de erro ou duplicada.
 */

Antena *inserirAntena(Antena *lista, char frequencia, int x, int y) {

    // Verifica se já existe uma antena na posição (x,y)
    Antena *verifica = lista;
    while (verifica) {

        if (verifica -> x == x && verifica->y == y) {
            // Erro, Ja existe uma antena na posicao
            return false; // Mantém a lista sem alterações
        }

        verifica = verifica-> proximo;
    }

    // Aloca memória para a nova antena
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (!nova) {
        return false;
        // Erro ao alocar memória para nova antena.
    }

    // Inicializa os dados da antena
    nova -> frequencia = frequencia;
    nova -> x = x;
    nova -> y = y;
    nova -> proximo = NULL;

    // Insere no início se a lista estiver vazia ou o novo elemento for menor
    if (!lista || x < lista->x || (x == lista ->x && y < lista->y)){
        nova -> proximo = lista;
        return nova;
    }
    
    // Encontra a posição correta para inserção ordenada
    Antena *atual = lista;
    while (atual -> proximo != NULL) {
        int cx = atual -> proximo ->x;
        int cy = atual -> proximo ->y;

        // Parar se a próxima antena tiver coordenadas maiores ou iguais
        if (cx > x || (cx == x && cy >= y)) {
            break;
        }

        atual = atual -> proximo;

    }

    // Insere nova antena entre atual e atual->proximo
    nova->proximo = atual->proximo;
    atual->proximo = nova;

    return lista;
}
