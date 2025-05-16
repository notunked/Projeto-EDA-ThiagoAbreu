/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */
/**
 * @file nefastos.c
 * @author Thiago Abreu
 * @brief Implementação da lógica para detectar locais com efeito nefasto.
 *
 * Um local tem efeito nefasto quando está perfeitamente alinhado com duas antenas
 * da mesma frequência e uma delas está exatamente o dobro da distância da outra.
 * A função identifica esses pontos com base nas regras de geometria entre pares.
 */

#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.h"
#include "antenas.h"
#include "nefastos.h"

/**
 * @brief Detecta locais nefastos com base na regra de alinhamento e distância.
 *
 * Para cada par de antenas com mesma frequência, verifica se uma está
 * a exatamente o dobro da distância da outra, e marca a posição intermediária.
 * A posição central é considerada "nefasta" e adicionada à lista.
 *
 * @param lista Lista ligada de antenas.
 * @return Lista de coordenadas com efeito nefasto.
 */

 Coordenada *detectarLocaisNefastos(Antena *lista) {
    Coordenada *nefastos = NULL;

    for (Antena *a1 = lista; a1 != NULL; a1 = a1->proximo) {

        for (Antena *a2 = a1 -> proximo; a2 != NULL; a2 = a2 -> proximo) {

            if (a1 -> frequencia != a2 -> frequencia) continue;

            int dx = a2 -> x - a1 -> x;
            int dy = a2 -> y - a1 -> y;

            // a2 está o dobro da distância de a1
            if(dx % 2 == 0 && dy % 2 == 0) {
                int mx = a1 -> x + dx / 2;
                int my = a1 -> y + dy / 2;
                nefastos = adicionarPosicao(nefastos, mx, my);

            }
        }
    }

    return nefastos;
    
 }