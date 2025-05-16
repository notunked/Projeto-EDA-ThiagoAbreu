/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */

/**
 * @file grafo.h
 * @author Thiago Abreu
 * @brief Definições de estruturas e protótipos de funções para grafos baseados em listas ligadas.
 *
 * Este cabeçalho define os tipos e as operações para representação de um grafo dinâmico,
 * onde cada vértice representa uma antena e as arestas representam ligações com frequências iguais.
 * São fornecidas funcionalidades de inserção, conexão, percursos em profundidade e largura,
 * e identificação de caminhos e intersecções.
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>
#include "antenas.h"

struct Vertice;

/**
 * @struct Aresta
 * @brief Representa uma ligação entre dois vértices com mesma frequência.
 */

 typedef struct Aresta {
    struct Vertice *destino; /**< Destino da aresta */
    struct Aresta *proximo;  /**< Próxima aresta na lista */
 } Aresta;

 /**
 * @struct Vertice
 * @brief Representa uma antena no grafo com a sua posição e conexões.
 */

 typedef struct Vertice {
    char frequencia;          /**< Frequência da antena */
    int x, y;                 /**< Coordenadas da antena */
    Aresta *arestas;          /**< Lista de arestas conectadas */
    struct Vertice *proximo;  /**< Próximo vértice na lista */
 } Vertice;

 /**
 * @struct FilaVertice
 * @brief Estrutura auxiliar para implementar fila na travessia em largura.
 */

 typedef struct FilaVertice {
   Vertice *v;                    /**< Vértice armazenado na fila */
   struct FilaVertice *proximo;   /**< Próximo elemento na fila */
 } FilaVertice;

Vertice *criarVertice (char frequencia, int x, int y);
Vertice *inserirVertice(Vertice *grafo, char frequencia, int x, int y);
bool conectarVertices(Vertice *grafo, int x1, int y1, int x2, int y2);
Vertice *libertarGrafo(Vertice *grafo);
Vertice *carregarGrafo(const char *nomeFicheiro, int *linhas, int *colunas);
FilaVertice *enfileirar(FilaVertice *fim, Vertice *v);
FilaVertice *desenfileirar(FilaVertice *inicio);
Vertice *primeiroFila(FilaVertice *inicio);
bool filaVazia(FilaVertice *inicio);
FilaVertice *libertarFila(FilaVertice *inicio);
Coordenada *procuraLargura(Vertice *grafo, int x, int y);
Coordenada *acumularCaminho(Coordenada *acumulador, Coordenada *caminho);
Coordenada *intersecoesFrequencias(Vertice *grafo, char freqA, char freqB);
Coordenada *procuraProfundidade(Vertice *grafo, int x, int y);
Coordenada *caminhosEntreAntenas(Vertice *grafo, int x1, int y1, int x2, int y2);

#endif