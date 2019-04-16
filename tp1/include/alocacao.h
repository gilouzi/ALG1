#ifndef ALOCACAO_H
#define ALOCACAO_H

#include "universidades.h"
#include "candidato.h"
#include "preferencia.h"

void aloca(int c, univ_t *vet_univ, cand_t *vet_cand);
void aloca_cand_i(univ_t *vet_univ, cand_t *vet_cand, int i);
void insere_cand_ordenado(int id, lista_pref_t *lista_cand, cand_t *vet_cand, int pos);
void delay();

#endif