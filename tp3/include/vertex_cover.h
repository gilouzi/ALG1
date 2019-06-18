#ifndef VERTEX_COVER_H
#define VERTEX_COVER_H

#include "arvore.h"
#include "grafo.h" 

int min(int valor1, int valor2);
int vertex_cover_arvore(int pos_node, arvore_t *arvore);
void vertex_cover_grafo(grafo_t *grafo);

#endif