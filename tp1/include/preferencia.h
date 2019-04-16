#ifndef PREFERENCIA_H
#define PREFERENCIA_H

//lista de preferencia tera salvo o indice do objeto de interesse
typedef struct pref {
  int pref_id;
  int pref_pos;
  struct pref *prev;
  struct pref *prox;
} pref_t;

typedef struct {
  int num_elementos;
  pref_t *inicio;
  pref_t *fim;
} lista_pref_t;

lista_pref_t *cria_lista_pref();
void insere_pref(lista_pref_t *lista_pref, int id, int pos);
void remove_inicio (lista_pref_t *lista);
int remove_fim(lista_pref_t *lista);
void print_lista_pref(lista_pref_t *lista);
void destroi_lista_pref(lista_pref_t *lista_pref);

#endif