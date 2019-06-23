#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct {
    int v1;
    int v2;
} aresta_t;

typedef struct {
    int quant_vert;
    int quant_arestas;
    aresta_t *arestas;
} grafo_t;

grafo_t *cria_grafo(int quant_vert);
//int max_vertice(grafo_t *grafo);
//int max_vertice_conect(grafo_t *grafo, int id_v1);
void insere_aresta(grafo_t *grafo, int id_1, int id_2);
//void remove_vertice(grafo_t *grafo, int id);
//void print_grafo(grafo_t *grafo);
void destroi_grafo (grafo_t *grafo);

#endif