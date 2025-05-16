/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */

/**
 * @file funcoes.h
 * @author Thiago Abreu
 * @brief Declarações de funções auxiliares para manipulação de listas de antenas e coordenadas.
 *
 * Este cabeçalho fornece as assinaturas das funções que suportam operações sobre listas ligadas,
 * incluindo inserção, remoção, verificação de presença e liberação de memória.
 */

#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdbool.h>
#include "antenas.h"
#include "nefastos.h"
#include "grafo.h"

/**
 * @brief Carrega uma lista de antenas a partir de um ficheiro de texto.
 *
 * Lê uma matriz de caracteres do ficheiro especificado e converte em uma lista ligada
 * de antenas, ignorando os pontos '.' e mantendo o formato textual.
 *
 * @param nomeFicheiro Caminho do ficheiro de entrada.
 * @param linhas Ponteiro para armazenar o número total de linhas.
 * @param colunas Ponteiro para armazenar o número total de colunas.
 * @return Lista ligada de antenas carregadas, ou false em caso de erro.
 */
Antena *carregarAntenas(const char *nomeFicheiro, int *linhas, int *colunas);

/**
 * @brief Remove uma antena localizada nas coordenadas (x, y).
 *
 * Remove a antena da lista, se existir, e atualiza o apontador booleano.
 *
 * @param lista Lista original.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @param removido Ponteiro booleano que indica se a antena foi removida.
 * @return Nova cabeça da lista.
 */

Antena *removerAntena(Antena *lista, int x, int y, bool *removido);


/**
 * @brief Liberta a memória de uma lista de antenas.
 *
 * Percorre toda a lista e desaloca cada nó.
 *
 * @param lista Cabeça da lista.
 * @return false após limpeza.
 */

Antena *libertarAntenas(Antena *lista);

/**
 * @brief Verifica se a coordenada (x,y) já está na lista.
 *
 * @param lista Lista ligada de coordenadas.
 * @param x Valor X.
 * @param y Valor Y.
 * @return true se existir, false caso contrário.
 */

bool existePosicao(Coordenada *lista, int x, int y);

/**
 * @brief Adiciona uma nova coordenada à lista se ainda não estiver presente.
 *
 * @param lista Lista atual.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Nova cabeça da lista.
 */

Coordenada *adicionarPosicao(Coordenada *lista, int x, int y);

/**
 * @brief Liberta a memória de uma lista de coordenadas.
 *
 * @param lista Lista de coordenadas.
 * @return false após limpeza.
 */

Coordenada *libertarCoordenadas(Coordenada *lista);

#endif