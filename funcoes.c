/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */

/**
 * @file funcoes.c
 * @author Thiago Abreu
 * @brief Implementação de funções auxiliares para manipulação de antenas e coordenadas. 
 *
 * Este módulo fornece funcionalidades para:
 * - Carregar uma lista de antenas a partir de ficheiro
 * - Remover antenas da lista ligada
 * - Verificar e adicionar posições 
 * - Libertar memória de listas de antenas ou coordenadas
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"
#include "antenas.h"

/**
 * @brief Carrega antenas a partir de um ficheiro de texto.
 *
 * Lê caractere a caractere e converte o conteúdo em uma lista ligada de antenas.
 * Cada antena é representada por um caractere diferente de '.' na matriz textual.
 *
 * @param nomeFicheiro Caminho para o ficheiro de entrada.
 * @param linhas Apontador para armazenar o número de linhas.
 * @param colunas Apontador para armazenar o número de colunas.
 * @return Apontador para o início da lista ligada de antenas.
 */
Antena *carregarAntenas(const char *nomeFicheiro, int *linhas, int *colunas) {
    
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    
    if (!ficheiro) {
        // Erro ao abrir o ficheiro
        return false;
    }

    Antena *lista = NULL;
    char c;
    int x=0, y=0;
    *linhas = 0;
    *colunas = 0;

    while ((c =fgetc(ficheiro)) !=EOF) {
        
        if (c == '\n') {
            if (*colunas == 0) *colunas = y;
            else if (y != *colunas) {
                fclose(ficheiro);
                return false;
            }
            x++;
            y = 0;
        } else {
            if (c != '.') {
                lista = inserirAntena(lista,c,x,y);
                if (!lista) {
                    fclose(ficheiro);
                    // Erro ao inserir
                    return false;
                }
            }
            y++;
        }

    }

    *linhas = x + 1;
    fclose(ficheiro);
    return lista;

}

/**
 * @brief Remove uma antena localizada nas coordenadas (x, y).
 *
 * Caso a antena exista, ela é removida da lista e a memória é libertada.
 * O apontador booleano é atualizado para indicar sucesso ou fracasso.
 *
 * @param lista Lista de antenas.
 * @param x Coordenada X da antena a remover.
 * @param y Coordenada Y da antena a remover.
 * @param removido Ponteiro booleano para status de remoção.
 * @return Lista atualizada após a operação.
 */

Antena *removerAntena(Antena *lista, int x, int y, bool *removido) {
    Antena *atual = lista;
    Antena *anterior = NULL;
    *removido = false;

    while (atual) {
        if (atual-> x == x && atual -> y == y ) { // Se encontrou a antena na posicao desejada

            if (anterior) {

                anterior -> proximo = atual -> proximo; // Ajusta o apontador do elemento anterior

            } else {

                lista = atual -> proximo; // Remover primeiro elemento

            }

            free(atual);
            // Antena removida nas coordenadas especificas

            *removido = true;

            return lista;

        }

        anterior = atual;
        atual = atual -> proximo;

    }

    // Nenhuma antena encontrada nas coordenadas específicas
    return lista;

}

/**
 * @brief Verifica se uma posição já existe em uma lista de coordenadas.
 *
 * @param lista Lista ligada de coordenadas.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return true se a posição existir, false caso contrário.
 */

bool existePosicao(Coordenada *lista, int x, int y) {

    while (lista) {

        if (lista -> x == x && lista -> y == y) return true;
        lista = lista -> proximo;

    }

    return false;

}

/**
 * @brief Adiciona uma posição à lista se ela ainda não existir.
 *
 * @param lista Lista de coordenadas.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Nova lista com a posição inserida (ou a mesma lista se já existir).
 */

Coordenada *adicionarPosicao(Coordenada *lista, int x, int y) {

    if (existePosicao(lista, x, y)) {

        return lista;

    }

    Coordenada *nova = (Coordenada *)malloc(sizeof(Coordenada));
    if (!nova) return false;

    nova -> x = x;
    nova -> y = y;
    nova -> proximo = lista;
    return nova;
    
}

/**
 * @brief Liberta a memória ocupada por uma lista de coordenadas.
 *
 * @param lista Lista de coordenadas.
 * @return false após a libertação completa.
 */

Coordenada *libertarCoordenadas(Coordenada *lista) {

    while (lista) {
        Coordenada *temp = lista;
        lista = lista -> proximo;
        free(temp);

    }

    return false;

}

/**
 * @brief Liberta a memória ocupada por uma lista de antenas.
 *
 * @param lista Lista de antenas.
 * @return false após a libertação completa.
 */

Antena *libertarAntenas(Antena *lista) {

    while (lista) {

        Antena *temp = lista;
        lista = lista -> proximo;
        free(temp);

    }

    return false;

}
