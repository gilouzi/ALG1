#include <stdio.h>
#include <stdlib.h>

#include "universidades.h"
#include "candidato.h"
#include "preferencia.h"
#include "alocacao.h"



int main(void) {

    int u; //quant total universidades
    int c; //quant total candidatos
    int v; //vagas
    int n; //notas
    int a; //aplicacoes
    int id;

/*    cand_t vet_cand[3];
    univ_t vet_univ[1];

    vet_univ[0].vagas = 3;
    vet_univ[0].nota_min = 65;
    vet_univ[0].lista_cand = cria_lista_pref();

    vet_cand[0].nota = 70;
    vet_cand[0].aloc = 0;
    vet_cand[0].lista_univ = cria_lista_pref();

    vet_cand[1].nota = 60;
    vet_cand[1].aloc = 0;
    vet_cand[1].lista_univ = cria_lista_pref();

    vet_cand[2].nota = 80;
    vet_cand[2].aloc = 0;
    vet_cand[2].lista_univ = cria_lista_pref();

    //insere_cand_ordenado(0, vet_univ[0].lista_cand, vet_cand);
    //insere_cand_ordenado(1, vet_univ[0].lista_cand, vet_cand);
    //insere_cand_ordenado(2, vet_univ[0].lista_cand, vet_cand);
    
    insere_pref(vet_cand[0].lista_univ, 1);
    insere_pref(vet_cand[0].lista_univ, 2);
    insere_pref(vet_cand[0].lista_univ, 0);
    print_lista_pref(vet_cand[0].lista_univ);

    for (int i = 0; i < 3; i++){
        destroi_lista_pref(vet_cand[i].lista_univ);
    }

    for (int i = 0; i < 1; i++){
        destroi_lista_pref(vet_univ[i].lista_cand);
    }*/

    FILE *arq_uni = fopen("universidades.txt", "r");

    fscanf(arq_uni, "%d", &u);
    univ_t vet_univ[u];
    for(int i = 0; i < u; i ++){ //inicializacao do vetor de universidades
        fscanf(arq_uni, "%d %d", &v, &n);
        vet_univ[i].vagas = v;
        vet_univ[i].nota_min = n;
        vet_univ[i].lista_cand = cria_lista_pref();
    }

    fclose(arq_uni);

    FILE *arq_can = fopen("candidatos.txt", "r");

    fscanf(arq_can, "%d", &c);
    cand_t vet_cand[c];
    for(int i = 0; i < c; i++){ //inicializacao do vetor de candidatos
        fscanf(arq_can, "%d %d", &a, &n);
        vet_cand[i].nota = n;
        vet_cand[i].aloc = -1;
        vet_cand[i].lista_univ = cria_lista_pref();
        for(int j = 0; j < a; j++){
            fscanf(arq_can, "%d", &id);
            insere_pref(vet_cand[i].lista_univ, id-1, j); //tem q tirar 1 de id pra passar pro parametro de vetores
        }
    }

    fclose(arq_can); 

/*
3
2 70
1 80
1 80
3
3 66
2 3 1
2 95
2 3
3 88
1 2 3
*/
    //testando se os valores estao sendo atribuidos corretamente
    /*for(int i = 0; i < u; i++){
        printf("univ %d: %d vagas e %f nota min\n", i, vet_univ[i].vagas, vet_univ[i].nota_min);
    }

    for(int i = 0; i < c; i++){
        printf("cand %d: %f nota e %d aloc, num de pref = %d \n", i, vet_cand[i].nota, vet_cand[i].aloc, vet_cand[i].lista_univ->num_elementos);
        pref_t *aux = vet_cand[i].lista_univ->inicio;
        for(int j = 0; j < vet_cand[i].lista_univ->num_elementos; j++){
            printf("pref %d = %d, ", aux->pref_pos, aux->pref_id);
            aux = aux->prox;
        }
        printf("\n");
    }*/

    aloca(c, vet_univ, vet_cand);

    printf("Grupos com alocacao\n");
    for(int i = 0; i < c; i++){
        if(vet_cand[i].aloc != -1){
            printf("%d %d\n", i+1, (vet_cand[i].aloc)+1); //imprimir o candidato e a universidade q ta alocada
        }
    }

    printf("Candidatos nao alocados\n");
    for(int i = 0; i < c; i++){
        if(vet_cand[i].aloc == -1){
            printf("%d\n", i+1); //imprimir o candidato e a universidade q ta alocada
        }
    }


    for(int i = 0; i < u; i ++){ //finalizacao do vetor de universidades
        destroi_lista_pref(vet_univ[i].lista_cand);
    }
    for(int i = 0; i < c; i ++){ //finalizacao do vetor de candidatos
        destroi_lista_pref(vet_cand[i].lista_univ);
    } 

  return 0;
}