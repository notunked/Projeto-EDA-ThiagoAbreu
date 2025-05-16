/**
 * ╔══════════════════════════════════════════════╗
 * ║   Projeto | Estruturas de Dados Avançadas    ║
 * ║   Código desenvolvido por Thiago Abreu       ║
 * ║   EST-IPCA, Barcelos — 2025                  ║
 * ╚══════════════════════════════════════════════╝
 */
/**
 * @file nefastos.h
 * @author Thiago Abreu
 * @brief Declaração da função para detectar locais com efeito nefasto.
 *
 * Um local tem efeito nefasto quando está perfeitamente alinhado com duas antenas
 * da mesma frequência e uma delas está exatamente o dobro da distância da outra.
 */

#ifndef NEFASTOS_H
#define NEFASTOS_H

#include "antenas.h"

Coordenada *detectarLocaisNefastos(Antena *lista);

#endif