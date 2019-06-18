#ifndef ARVORE_H
#define ARVORE_H

#include "lista.h"

typedef struct {
    int quant_vert;
    lista_t **lista_adj;
} arvore_t;

arvore_t *cria_arvore(int quant_vert);
int min(int valor1, int valor2);
void print_arvore(arvore_t *arvore);
void insere_arvore(arvore_t *arvore, int id_1, int id_2);
void destroi_arvore (arvore_t *arvore);

#endif