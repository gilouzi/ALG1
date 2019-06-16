#ifndef LISTA_H
#define LISTA_H

typedef struct node {
  int id;
  int peso;
  struct node *prev;
  struct node *prox;
} node_t;

typedef struct {
  int num_elementos;
  node_t *inicio;
  node_t *fim;
} lista_t;

lista_t *cria_lista();
void insere_no(lista_t *lista, int id, int peso);
void remove_inicio (lista_t *lista);
int remove_fim(lista_t *lista);
void print_lista(lista_t *lista);
void destroi_lista(lista_t *lista);

#endif