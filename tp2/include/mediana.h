#ifndef MEDIANA_H
#define MEDIANA_H

#include "grafo.h"

int mom(aresta_t *arestas, int quant_arestas);
int mom_select(aresta_t *arestas, int k, int quant_arestas);
void insertion_sort(aresta_t *arestas, int quant_arestas);
int partition_3_way(int *pos_pivot, aresta_t *arestas, int quant_arestas);
void troca_elem(int pos1, int pos2, aresta_t *arestas);

#endif