#ifndef ARVORE_H
#define ARVORE_H

#include "lista.h"

typedef struct {
    int quant_vert;
    lista_t **lista_adj;
} arvore_t;

arvore_t *cria_arvore(int quant_vert);
int min(int valor1, int valor2);
int vertex_cover(int pos_node, arvore_t *arvore);
void print_arvore(arvore_t *arvore);
void destroi_arvore (arvore_t *arvore);

#endif