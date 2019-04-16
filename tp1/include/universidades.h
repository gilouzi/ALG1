#ifndef UNIVERSIDADES_H
#define UNIVERSIDADES_H

#include "preferencia.h"

//cada universidade tem vagas, nota minima e uma lista de candidatos de tamanho max = vagas
typedef struct { 
  int vagas;
  int nota_min;
  lista_pref_t *lista_cand;
} univ_t;

#endif