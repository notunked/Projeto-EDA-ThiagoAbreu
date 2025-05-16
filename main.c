/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */
/**
 * @file main.c
 * @author Thiago Abreu
 * @brief Programa principal.
 */

#include <stdio.h>
#include <stdbool.h>
#include "funcoes.h"
#include "grafo.h"

int main() {

    int linhas = 0, colunas = 0;
    Vertice *grafo = NULL;
    
    // Fase 1: 1.
    // Struct da Antena presente em antenas.h

    // Fase 1: 2.
    Antena *lista = carregarAntenas("uploadantenas.txt", &linhas, &colunas);
    if (!lista) {
        printf("Erro ao carregar antenas do ficheiro.\n");
        return false;
    }
    // Fase 1: 3.A
    lista = inserirAntena(lista, 'Z', 2, 3);
    if (!lista) {
        printf("Erro: Antena não pôde ser inserida (duplicada ou falha de memória).\n");
    } else {
        printf("Antena 'Z' inserida em (2, 3).\n");
    }


    // Fase 1: 3.B
    bool removido = false;
    lista = removerAntena(lista, 3, 5, &removido);
    if (removido) {
        printf("Antena removida com sucesso.\n");
    } else {
        printf("Nenhuma antena encontrada em (3, 5).\n");
    }

    //Fase 1: 3.C
    Coordenada *nefastos = detectarLocaisNefastos(lista);
    while (nefastos) {
        printf("Efeito nefasto em (%d, %d)\n", nefastos->x, nefastos->y);
        nefastos = nefastos->proximo;
    }

    // Fase 1: 3.D
    printf("\n=======================\n");
    printf(" TABELA DE ANTENAS\n");
    printf("=======================\n");
    printf("| FREQ |  X  |  Y  |\n");
    printf("=======================\n");

    for (Antena *a = lista; a != NULL; a = a->proximo) {
        printf("|  %c   | %2d  | %2d  |\n", a->frequencia, a->x, a->y);
    }

    printf("\n===============================\n");
    printf(" LOCAIS COM EFEITO NEFASTO\n");
    printf("===============================\n");
    printf("|   X   |   Y   |\n");
    printf("===============================\n");

    for (Coordenada *n = nefastos; n != NULL; n = n->proximo) {
        printf("|  %2d   |  %2d   |\n", n->x, n->y);
    }

    // Fase 2: 1.
    grafo = inserirVertice(grafo, 'A', 1, 1);
    grafo = inserirVertice(grafo, 'A', 2, 2);
    grafo = inserirVertice(grafo, 'A', 3, 3);
    grafo = inserirVertice(grafo, 'B', 5, 5);

        // Apenas estas vão conectar:
    conectarVertices(grafo, 1, 1, 2, 2); // Frequência 'A'
    conectarVertices(grafo, 2, 2, 3, 3); // Frequência 'A'

        // Esta não conecta (frequência diferente)
    conectarVertices(grafo, 3, 3, 5, 5); // 'A' e 'B' → rejeitado

    // Fase 2: 2.
    grafo = carregarGrafo("uploadantenas.txt", &linhas, &colunas);

    if (!grafo) {
        printf("Erro ao carregar o grafo a partir do ficheiro.\n");
        return false;
    }

    printf("Grafo carregado com sucesso (%d linhas x %d colunas):\n", linhas, colunas);
    printf("===============================\n");
    printf("| FREQ |   X   |   Y   |\n");
    printf("===============================\n");

    for (Vertice *v = grafo; v != NULL; v = v->proximo) {
        printf("|  %c   |  %2d   |  %2d   |\n", v->frequencia, v->x, v->y);
    }

    // Fase 2: 3.A
    Coordenada *alcancados = procuraProfundidade(grafo, 5, 6);

    if (!alcancados) {
        printf("Nenhuma antena encontrada ou nenhum caminho a partir da posição (5, 6).\n");
    } else {
        printf("Antenas alcançadas a partir de (5, 6):\n");
        printf("=========================\n");
        printf("|   X   |   Y   |\n");
        printf("=========================\n");
        Coordenada *atual = alcancados;
        while (atual) {
            printf("|  %2d   |  %2d   |\n", atual->x, atual->y);
            atual = atual->proximo;
        }
        printf("=========================\n");
    }

    // Fase 2: 3.B
    int origemX = 5, origemY = 6;
    alcancados = procuraLargura(grafo, origemX, origemY);

    if (!alcancados) {
        printf("Antena inicial não encontrada ou nenhuma conexão em largura.\n");
    } else {
        printf("Antenas alcançadas em largura a partir de (%d, %d):\n", origemX, origemY);
        printf("=========================\n");
        printf("|   X   |   Y   |\n");
        printf("=========================\n");

        Coordenada *atual = alcancados;
        while (atual) {
            printf("|  %2d   |  %2d   |\n", atual->x, atual->y);
            atual = atual->proximo;
        }
        printf("=========================\n");
    }

    // Fase 2: 3.C
    Coordenada *todosCaminhos = caminhosEntreAntenas(grafo, 5, 6, 9, 9);
    if (!todosCaminhos) {
        printf("Nenhum caminho encontrado entre (5, 6) e (9, 9).\n");
        libertarGrafo(grafo);
        return 0;
    }

    printf("Caminhos encontrados entre (5, 6) e (9, 9):\n");

    Coordenada *atual = todosCaminhos;
    while (atual) {
        printf("(%d, %d)", atual->x, atual->y);
        if (atual->proximo && !(atual->proximo->x == 0 && atual->proximo->y == 0)) {
            printf(" -> ");
        } else {
            printf("\n");
        }
        atual = atual->proximo;
    }

    // Fase 2: 3.D
    char freqA = 'A';
    char freqB = 'O';

    Coordenada *pares = intersecoesFrequencias(grafo, freqA, freqB);

    if (!pares) {
        printf("Nenhuma interseção encontrada entre frequências %c e %c.\n", freqA, freqB);
    } else {
        printf("Pares de antenas com frequências %c e %c:\n", freqA, freqB);
        Coordenada *atual = pares;
        while (atual && atual->proximo) {
            printf("(%d, %d) ↔ (%d, %d)\n", atual->x, atual->y, atual->proximo->x, atual->proximo->y);
            atual = atual->proximo->proximo;
        }
    }

    // Limpeza de memória
    lista = libertarAntenas(lista);
    grafo = libertarGrafo(grafo);
    nefastos = libertarCoordenadas(nefastos);
    libertarCoordenadas(pares);
    libertarCoordenadas(alcancados);
    libertarGrafo(grafo);

    return 0;
}