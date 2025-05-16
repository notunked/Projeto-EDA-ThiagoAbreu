/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */
/**
 * @file grafo.c
 * @author Thiago Abreu
 * @brief Implementação de um grafo dinâmico com vértices representando antenas.
 *
 * Este módulo implementa um grafo com inserção ordenada de vértices (antenas), conexões por arestas,
 * procuras em profundidade e largura, descoberta de caminhos entre dois pontos e intersecções entre frequências distintas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"
#include "funcoes.h"

/**
 * @brief Carrega uma matriz de antenas de um ficheiro de texto para um grafo dinâmico.
 *
 * Lê o ficheiro linha por linha, caractere por caractere, ignorando os pontos ('.')
 * e transformando os restantes caracteres em vértices do grafo. Cada caractere é
 * interpretado como uma antena com frequência (char) e coordenadas (x, y) calculadas
 * com base na posição no ficheiro.
 *
 * A função também atualiza os valores apontados por `linhas` e `colunas`, correspondendo
 * às dimensões da matriz lida. A matriz pode ter qualquer tamanho retangular válido.
 *
 * @param nomeFicheiro Caminho para o ficheiro de entrada contendo a matriz textual.
 * @param linhas Apontador para armazenar a quantidade de linhas da matriz carregada.
 * @param colunas Apontador para armazenar a quantidade de colunas da matriz carregada.
 * @return Apontador para a cabeça do grafo construído ou false em caso de erro.
 */

Vertice *carregarGrafo(const char *nomeFicheiro, int *linhas, int *colunas) {
    
    FILE *ficheiro = fopen(nomeFicheiro, "r");

    if (!ficheiro) {

        return false;
    }

    Vertice *grafo = NULL;
    char c;
    int x = 0, y = 0;
    *linhas = 0;
    *colunas = 0;

    while ((c = fgetc(ficheiro)) != EOF) {
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
                grafo = inserirVertice(grafo, c, x, y);
            }
            y++;
        }
    }

    *linhas = x + 1;
    fclose(ficheiro);
    return grafo;
}

/**
 * @brief Insere um novo vértice no grafo em ordem crescente pelas coordenadas (x, y).
 *
 * A função cria um novo vértice com a frequência e coordenadas fornecidas, e insere-o
 * na posição correta na lista ligada que representa o grafo. A ordenação é feita
 * primeiro por coordenada X e, em caso de empate (ser igual), por coordenada Y.
 *
 * Se já existir um vértice nas mesmas coordenadas (x, y), a inserção é ignorada.
 *
 * @param grafo Apontador para o início da lista de vértices.
 * @param frequencia Caractere que representa a frequência da antena.
 * @param x Coordenada X do novo vértice.
 * @param y Coordenada Y do novo vértice.
 * @return Apontador para o início atualizado da lista, ou false em caso de erro ou duplicada.
 */

Vertice *inserirVertice(Vertice *grafo, char frequencia, int x, int y) {

    // Verificar duplicados

    Vertice *v = grafo;
    while (v) {

        if (v->x == x && v->y == y) {

            return false;

        }

        v = v -> proximo;

    }

    Vertice *novo = criarVertice(frequencia, x, y);
    if (!novo) {

        return false;

    }

    if (!grafo || x < grafo -> x || (x == grafo -> x && y < grafo -> y)) {

        novo -> proximo = grafo;
        return novo;

    }

    Vertice *atual = grafo;

    while (atual -> proximo != NULL) {

        int cx = atual -> proximo -> x;
        int cy = atual -> proximo -> y;

        if (cx > x || (cx == x && cy >= y)) {
            break;
        }

        atual = atual -> proximo;

    }

    novo -> proximo = atual -> proximo;
    atual -> proximo = novo;

    return grafo;
}

/**
 * @brief Cria dinamicamente um novo vértice que representa uma antena no grafo.
 *
 * Aloca memória para um vértice, inicia os seus campos com a frequência fornecida
 * e as coordenadas (x, y), e define os apontadores de ligação (`arestas` e `proximo`) como NULL.
 *
 * Esta função não insere o vértice diretamente no grafo — ela apenas o cria. 
 * A inserção ordenada é feita posteriormente pela função `inserirVertice`.
 *
 * @param frequencia Letra que identifica a frequência de ressonância da antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Apontador para o novo vértice criado ou false se a alocação falhar.
 */

Vertice *criarVertice(char frequencia, int x, int y) {

    Vertice *novo = (Vertice *)malloc(sizeof(Vertice));

    if (!novo) {

        return false;

    }

    novo -> frequencia = frequencia;
    novo -> x = x;
    novo -> y = y;
    novo -> arestas = NULL;
    novo -> proximo = NULL;

    return novo;

}

/**
 * @brief Conecta dois vértices do grafo por arestas bidirecionais, se tiverem a mesma frequência.
 *
 * Esta função procura dois vértices localizados nas coordenadas fornecidas.
 * Se ambos forem encontrados e tiverem a mesma frequência de ressonância,
 * cria-se uma conexão entre eles por meio de arestas em ambas as direções.
 *
 * A conexão é válida apenas entre vértices com frequências iguais.
 *
 * @param grafo Apontador para o início da lista de vértices do grafo.
 * @param x1 Coordenada X do primeiro vértice.
 * @param y1 Coordenada Y do primeiro vértice.
 * @param x2 Coordenada X do segundo vértice.
 * @param y2 Coordenada Y do segundo vértice.
 * @return true se a ligação foi criada com sucesso, false caso contrário.
 */

bool conectarVertices(Vertice *grafo, int x1, int y1, int x2, int y2) {
    
    Vertice *v1 = NULL, *v2 = NULL;
    for (Vertice *v = grafo; v; v = v -> proximo) {
        if (v -> x == x1 && v -> y == y1) {
            v1 = v;
        }
        if (v-> x == x2 && v->y == y2) {
            v2 = v;
        }
    }

    if (!v1 || !v2 || v1 -> frequencia != v2 -> frequencia) {
        return false;
    }

    Aresta *a1 = (Aresta *)malloc(sizeof(Aresta));
    Aresta *a2 = (Aresta *)malloc(sizeof(Aresta));

    if (!a1 || !a2) {
        return false;
    }

    a1 -> destino = v2;
    a1 -> proximo = v1 -> arestas;
    v1 -> arestas = a1;

    a2 -> destino = v1;
    a2 -> proximo = v2 -> arestas;
    v2 -> arestas = a2;

    return true;

}

/**
 * @brief Liberta toda a memória associada ao grafo.
 *
 * Esta função percorre a lista de vértices do grafo e, para cada vértice,
 * desaloca todas as arestas associadas. Em seguida, remove o próprio vértice.
 *
 * Ao final da execução, nenhum espaço de memória alocado para o grafo permanece ocupado.
 *
 * @param grafo Apontador para o início da lista de vértices do grafo.
 * @return false após a liberação completa dos vértices e arestas.
 */

Vertice *libertarGrafo(Vertice *grafo) {

    while (grafo) {
        
        Aresta *a = grafo -> arestas;

        while (a) {

            Aresta *tmp = a;
            a = a -> proximo;
            free (tmp);

        }

        Vertice *tmp = grafo;
        grafo = grafo -> proximo;
        free(tmp);

    }
    
    return false;

}

/**
 * @brief Percorre o grafo em profundidade a partir de um vértice, acumulando as posições visitadas.
 *
 * A função realiza uma procura em profundidade recursiva, começa a partir do vértice dado.
 * Ela adiciona cada vértice visitado às listas `visitados` e `resultado`, evitando revisitar vértices já percorridos.
 *
 * A procura segue todas as arestas conectadas ao vértice atual.
 *
 * @param v Apontador para o vértice atual a ser visitado.
 * @param visitados Lista de coordenadas já visitadas.
 * @param resultado Lista que acumula os vértices alcançados pela procura.
 * @return Lista `resultado` atualizada com os vértices alcançados.
 */

Coordenada *buscaProfundidadeRecursiva(Vertice *v, Coordenada *visitados, Coordenada *resultado) {

    if (!v || existePosicao(visitados, v->x, v->y)) {
        return resultado;
    }

    visitados = adicionarPosicao(visitados, v->x, v->y);
    resultado = adicionarPosicao(resultado, v->x, v->y);

    Aresta *a = v->arestas;
    while (a) {

        resultado = buscaProfundidadeRecursiva(a->destino, visitados, resultado);
        a = a -> proximo;

    }

    return resultado;

}

/**
 * @brief Executa uma procura em profundidade no grafo a partir de uma antena específica.
 *
 * Localiza o vértice com as coordenadas fornecidas e inicia a procura em profundidade
 * a partir dele. Todos os vértices alcançáveis por arestas são acumulados em uma lista
 * de coordenadas, retornada ao final da operação.
 *
 * A função ignora vértices não conectados ao ponto de origem.
 *
 * @param grafo Apontador para o início da lista de vértices do grafo.
 * @param x Coordenada X do vértice de partida.
 * @param y Coordenada Y do vértice de partida.
 * @return Lista de coordenadas visitadas a partir do vértice de origem, ou false se não encontrado.
 */

Coordenada *procuraProfundidade(Vertice *grafo, int x, int y) {
    
    Vertice *inicio = NULL;
    
    for (Vertice *v = grafo; v; v = v -> proximo) {

        if (v -> x == x && v -> y == y) {

            inicio = v;
            break;

        }
    }

    if (!inicio) {
        return false;
    }

    Coordenada *visitados = NULL;
    Coordenada *resultado = NULL;
    resultado = buscaProfundidadeRecursiva(inicio, visitados, resultado);
    libertarCoordenadas(visitados);

    return resultado;
}

/**
 * @brief Adiciona um vértice ao final da fila de procura em largura.
 *
 * Esta função aloca um novo nó de fila contendo o vértice especificado
 * e conecta-o ao final da fila atual, caso ela não esteja vazia.
 *
 * Utilizada na implementação da procura em largura.
 *
 * @param fim Apontador para o último elemento atual da fila.
 * @param v Apontador para o vértice a ser enfileirado.
 * @return Apontador para o novo último elemento da fila, ou false em caso de falha.
 */

FilaVertice *enfileirar(FilaVertice *fim, Vertice *v) {
    
    FilaVertice *novo = (FilaVertice *)malloc(sizeof(FilaVertice));
    
    if (!novo) {
        return false;
    }

    novo -> v = v;
    novo -> proximo = NULL;

    if (fim) {
        fim -> proximo = novo;
    }

    return novo;
    
}

/**
 * @brief Remove o primeiro elemento da fila de vértices.
 *
 * Liberta a memória do primeiro nó da fila e retorna o próximo,
 * permitindo o avanço da procura em largura.
 *
 * Caso a fila esteja vazia, retorna false.
 *
 * @param inicio Apontador para o primeiro elemento atual da fila.
 * @return Apontador para o novo primeiro elemento da fila, ou false se a fila estava vazia.
 */

FilaVertice *desenfileirar(FilaVertice *inicio) {

    if (!inicio) {
        return false;
    }

    FilaVertice *seguinte = inicio -> proximo;
    free (inicio);
    return seguinte;

}

/**
 * @brief Obtém o vértice armazenado no início da fila.
 *
 * Retorna o vértice associado ao primeiro nó da fila, sem removê-lo.
 * Útil para consultar o próximo vértice a ser processado durante a procura em largura.
 *
 * @param inicio Apontador para o primeiro nó da fila.
 * @return Apontador para o vértice armazenado, ou false se a fila estiver vazia.
 */

Vertice *primeiroFila (FilaVertice *inicio) {

    if (!inicio) {
        return false;
    }

    return inicio -> v;

}

/**
 * @brief Verifica se a fila está vazia.
 *
 * Retorna true se o ponteiro de início for NULL, indicando que
 * não há elementos na fila.
 *
 * @param inicio Apontador para o primeiro nó da fila.
 * @return true se a fila estiver vazia, false caso contrário.
 */

bool filaVazia(FilaVertice *inicio) {
    
    return inicio == NULL;

}

/**
 * @brief Liberta toda a memória alocada para a fila de vértices.
 *
 * Percorre a lista de nós da fila, desalocando cada elemento.
 * Após a execução, nenhum nó da fila permanece na memória.
 *
 * @param inicio Apontador para o primeiro nó da fila.
 * @return false após libertação completa da fila.
 */

FilaVertice *libertarFila(FilaVertice *inicio) {

    while (inicio) {

        FilaVertice *tmp = inicio;
        inicio = inicio->proximo;
        free(tmp);

    }

    return false;
}

/**
 * @brief Executa uma procura em largura no grafo a partir de uma antena específica.
 *
 * Localiza o vértice correspondente às coordenadas (x, y) e inicia uma procura em largura.
 * A procura percorre todos os vértices alcançáveis por conexões (arestas), utilizando
 * uma fila para controlar a ordem de visita.
 *
 * Cada vértice visitado é registado na lista `resultado`, que é retornada ao final.
 *
 * @param grafo Apontador para o início da lista de vértices.
 * @param x Coordenada X do vértice de origem.
 * @param y Coordenada Y do vértice de origem.
 * @return Lista de coordenadas de todos os vértices alcançados a partir do ponto de origem, ou false se não for encontrado.
 */

Coordenada *procuraLargura(Vertice *grafo, int x, int y) {

    Vertice *inicio = NULL;

    for (Vertice *v = grafo; v; v = v->proximo) {

        if (v->x == x && v->y == y) {
            inicio = v;
            break;

        }

    }

    if (!inicio) {

        return false;

    }

    Coordenada *visitados = NULL;
    Coordenada *resultado = NULL;

    FilaVertice *filaInicio = NULL;
    FilaVertice *filaFim = NULL;

    if (!existePosicao(visitados, inicio->x, inicio->y)) {

        visitados = adicionarPosicao(visitados, inicio->x, inicio->y);
        resultado = adicionarPosicao(resultado, inicio->x, inicio->y);
        filaInicio = filaFim = enfileirar(NULL, inicio);

    }

    while (!filaVazia(filaInicio)) {

        Vertice *vAtual = primeiroFila(filaInicio);
        filaInicio = desenfileirar(filaInicio);

        for (Aresta *a = vAtual->arestas; a; a = a->proximo) {

            Vertice *vizinho = a->destino;

            if (!existePosicao(visitados, vizinho->x, vizinho->y)) {
                
                visitados = adicionarPosicao(visitados, vizinho->x, vizinho->y);
                resultado = adicionarPosicao(resultado, vizinho->x, vizinho->y);
                filaFim = enfileirar(filaFim, vizinho);
                if (!filaInicio) filaInicio = filaFim;

            }

        }

    }

    libertarFila(filaInicio);
    libertarCoordenadas(visitados);
    return resultado;

}

/**
 * @brief Copia os elementos de um caminho e acumula-os em uma lista de resultado.
 *
 * Percorre a lista `caminho` e adiciona cada coordenada à lista `acumulador`.
 * Usada para registrar trajetos completos entre vértices em procuras que identificam caminhos múltiplos.
 *
 * @param acumulador Lista onde as coordenadas serão acumuladas.
 * @param caminho Lista de coordenadas representando um caminho a ser adicionado.
 * @return Lista de coordenadas atualizada com os dados acumulados.
 */

Coordenada *acumularCaminho(Coordenada *acumulador, Coordenada *caminho) {
    
    Coordenada *aux = caminho;
    Coordenada *resultado = acumulador;

    while (aux) {

        resultado = adicionarPosicao(resultado, aux -> x, aux -> y);
        aux = aux -> proximo;

    }

    return resultado;

}

/**
 * @brief Cria uma cópia de um caminho, iniciando com uma coordenada adicional.
 *
 * Aloca uma nova lista de coordenadas, começando pela coordenada (x, y),
 * e copia em seguida todas as coordenadas da lista `origem`.
 * Utilizada para guardar uma cópia de um trajeto completo durante a descoberta de caminhos.
 *
 * @param origem Lista de coordenadas representando o caminho original.
 * @param x Coordenada X a ser adicionada no início da nova lista.
 * @param y Coordenada Y a ser adicionada no início da nova lista.
 * @return Nova lista de coordenadas iniciada por (x, y) seguida das coordenadas de `origem`.
 */

Coordenada *copiarCaminho(Coordenada *origem, int x, int y) {

    Coordenada *novo = adicionarPosicao(NULL, x, y);
    Coordenada *resultado = NULL;
    Coordenada *aux = origem;

    while (aux) {

        resultado = adicionarPosicao(resultado, aux-> x, aux -> y);
        aux = aux -> proximo;

    }

    novo -> proximo = resultado;
    return novo;

}

/**
 * @brief Percorre recursivamente todos os caminhos entre um vértice e um destino no grafo.
 *
 * Esta função implementa uma procura recursiva para identificar todos os caminhos
 * possíveis entre o vértice atual e o destino especificado pelas coordenadas (xDestino, yDestino).
 * Cada caminho completo encontrado é copiado e acumulado na lista `resultado`.
 *
 * A função evita ciclos verificando se um vértice já foi visitado.
 *
 * @param atual Vértice atual da travessia.
 * @param xDestino Coordenada X do vértice de destino.
 * @param yDestino Coordenada Y do vértice de destino.
 * @param visitados Lista de coordenadas já visitadas.
 * @param caminho Caminho atual em construção.
 * @param resultado Lista acumulada com todos os caminhos encontrados.
 * @return Lista atualizada com os caminhos completos encontrados até o momento.
 */

Coordenada *buscarCaminhos(Vertice *atual, int xDestino, int yDestino, Coordenada *visitados, Coordenada *caminho, Coordenada *resultado) {

    if (!atual || existePosicao(visitados, atual -> x, atual -> y)) {
        return resultado;
    }

    Coordenada *novoVisitado = adicionarPosicao(visitados, atual -> x, atual ->y);
    Coordenada *novoCaminho = adicionarPosicao(caminho, atual->x, atual->y);

    if (atual->x == xDestino && atual ->y == yDestino) {

        Coordenada *copiado = copiarCaminho(novoCaminho, 0, 0);
        resultado = acumularCaminho(resultado, copiado);

        libertarCoordenadas(copiado);
        libertarCoordenadas(novoVisitado);
        libertarCoordenadas(novoCaminho);

        return resultado;

    }

    Aresta *a = atual -> arestas;
    
    while (a) {
        
        resultado = buscarCaminhos(a->destino, xDestino, yDestino, novoVisitado, novoCaminho, resultado);
        a = a -> proximo;

    }

    libertarCoordenadas(novoVisitado);
    libertarCoordenadas(novoCaminho);

    return resultado;
}

/**
 * @brief Encontra todas as combinações de pares de antenas com frequências distintas.
 *
 * Para cada antena com frequência `freqA`, a função procura todas as antenas com frequência `freqB`
 * e adiciona as coordenadas de ambos à lista `resultado`. Cada par é representado por dois nós consecutivos
 * na lista resultante.
 *
 * Útil para analisar possíveis intersecções ou interações entre diferentes tipos de antenas no grafo.
 *
 * @param grafo Apontador para o início da lista de vértices do grafo.
 * @param freqA Frequência do primeiro grupo de antenas.
 * @param freqB Frequência do segundo grupo de antenas.
 * @return Lista de coordenadas dos pares de intersecções encontradas.
 */

Coordenada *intersecoesFrequencias(Vertice *grafo, char freqA,char freqB) {

    Coordenada *resultado = NULL;

    for (Vertice *a = grafo; a !=NULL; a = a->proximo) {

        if (a->frequencia != freqA) {
            continue;
        }

        for (Vertice *b = grafo; b != NULL; b = b->proximo) {

            if (b->frequencia != freqB) {
                continue;
            }

            resultado = adicionarPosicao(resultado, a->x, a->y);
            resultado = adicionarPosicao(resultado, b->x, b->y);

        }

    }

    return resultado;
}

/**
 * @brief Encontra todos os caminhos possíveis entre duas antenas no grafo.
 *
 * Esta função procura todos os percursos válidos entre as antenas localizadas
 * em (x1, y1) e (x2, y2), considerando apenas conexões entre vértices com
 * a mesma frequência. Cada caminho é acumulado como uma lista ligada de coordenadas.
 *
 * Usa uma procura recursiva (`buscarCaminhos`) para explorar múltiplos ramos,
 * e armazena todas as sequências encontradas na lista de resultados.
 *
 * @param grafo Lista ligada de vértices que representam o grafo.
 * @param x1 Coordenada X da antena de origem.
 * @param y1 Coordenada Y da antena de origem.
 * @param x2 Coordenada X da antena de destino.
 * @param y2 Coordenada Y da antena de destino.
 * @return Lista de coordenadas que representa os caminhos encontrados (em sequência), ou false se não houver caminho.
 */

Coordenada *caminhosEntreAntenas(Vertice *grafo, int x1, int y1, int x2, int y2) {
    Vertice *inicio = NULL;
    for (Vertice *v = grafo; v; v = v->proximo) {
        if (v->x == x1 && v->y == y1) {
            inicio = v;
            break;
        }
    }

    if (!inicio) return NULL;

    Coordenada *visitados = NULL;
    Coordenada *caminho = NULL;
    Coordenada *resultado = NULL;

    resultado = buscarCaminhos(inicio, x2, y2, visitados, caminho, resultado);
    libertarCoordenadas(visitados);
    return resultado;
}
