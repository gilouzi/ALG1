#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct {
    int peso;
    int v1;
    int v2;
} aresta_t;

typedef struct {
    int quant_comp;
    int *vert;
} floresta_t;

typedef struct {
    int quant_vert;
    int quant_arestas;
    floresta_t *floresta;
    aresta_t *arestas;
    lista_t **lista_adj;
} grafo_t;

grafo_t *cria_grafo(int quant_vert);
void insere_aresta(grafo_t *grafo, int id_1, int id_2, int peso);
void dfs_aux(grafo_t *grafo);
void DFS(grafo_t *grafo, lista_t *lista_adj, int *dfs, int i, int id);
int carmerini(grafo_t *grafo);
void print_grafo(grafo_t *grafo);
void destroi_grafo (grafo_t *grafo);

#endif