#ifndef CANDIDATO_H
#define CANDIDATO_H

#include "preferencia.h"

//candidato possui nota e uma lista de interesse de universidades ordenada por preferencia
typedef struct {
  int nota;
  int aloc;
  lista_pref_t *lista_univ;
} cand_t;

#endif