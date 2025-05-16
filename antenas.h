/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */

/**
 * @file antenas.h
 * @author Thiago Abreu
 * @brief Definições das estruturas para representação e manipulação de antenas em lista ligada.
 *
 * Este cabeçalho fornece as definições das estruturas de dados Antena e Coordenada,
 * utilizadas em operações com listas ligadas dinâmicas, bem como a declaração da função
 * de inserção de antenas na lista.
 */

#ifndef ANTENAS_H
#define ANTENAS_H

#include <stdbool.h>

/** 
 * @struct Antena
 * @brief Representa uma antena com frequência e posição (x,y) no mapa.
 * 
 * Cada nó da lista ligada representa uma antena. A estrutura inclui a frequência
 * da antena (caractere) e as coordenadas x e y onde a antena está localizada.
 */

typedef struct Antena {
    char frequencia;        /**< Frequência da antena */
    int x, y;               /**< Coordenadas (x,y) da antena no mapa. */
    struct Antena *proximo; /**< Apontador para a próxima antena na lista */
} Antena;

/**
 * @struct Coordenada
 * @brief Representa uma posição genérica (x, y) na lista ligada.
 *
 * Esta estrutura é usada para armazenar localizações dinâmicas como resultados
 * de operações de procura, locais com efeito nefasto ou caminhos no grafo.
 */

typedef struct Coordenada {
    int x;                      /**< Coordenada X */
    int y;                      /**< Coordenada Y */
    struct Coordenada *proximo; /**< Próxima coordenada na lista ligada*/
} Coordenada;

/**
 * @brief Insere uma nova antena na lista ligada de forma ordenada.
 *
 * A antena é inserida mantendo a ordem crescente das coordenadas (x, y).
 * Se já existir uma antena na mesma posição, a inserção é ignorada.
 *
 * @param lista Apontador para o início da lista ligada de antenas.
 * @param frequencia Letra que identifica a frequência da nova antena.
 * @param x Coordenada X da nova antena.
 * @param y Coordenada Y da nova antena.
 * @return Apontador para o novo início da lista ou NULL em caso de erro ou duplicada.
 */

Antena *inserirAntena(Antena *lista, char frequencia, int x, int y);

#endif
