#include "aval_exp.h"
#include <math.h>

float calc_taxa_aloc (univ_t univ){
    float vagas_aloc = univ.lista_cand->num_elementos;
    float total_vagas = univ.vagas;
    return vagas_aloc/total_vagas;
}

float media_preenc_vagas (univ_t *univ, int u){
    float media = 0;
    for(int i = 0; i < u; i++){
        media = media + calc_taxa_aloc(univ[i]);
    }
    return media/u;
}

float satisf_cand (cand_t cand, univ_t *vet_univ){
    int aloc = cand.aloc;
    if (aloc == -1){
        return 0;
    }
    univ_t univ = vet_univ[aloc];
    lista_pref_t *listaCand = univ.lista_cand;
    float pi;
    for (int i = 0; i < listaCand->num_elementos; i++){
        if (listaCand->fim->pref_id == aloc) {
            pi = remove_fim(listaCand);
        }
        float x = remove_fim(listaCand);
    }
    return 1/log2(pi+1);
}