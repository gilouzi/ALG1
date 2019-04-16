#include <stdio.h>
#include <stdlib.h>

#include "universidades.h"
#include "candidato.h"
#include "preferencia.h"
#include "alocacao.h"



int main(int argc, const char **argv) {

    int u; //quant total universidades
    int c; //quant total candidatos
    int v; //vagas
    int n; //notas
    int a; //aplicacoes
    int id;

//lendo os arquivos e inicializando as variaveis
    FILE *arq_uni = fopen(argv[1], "r");

    fscanf(arq_uni, "%d", &u);
    univ_t vet_univ[u];
    for(int i = 0; i < u; i ++){ //inicializacao do vetor de universidades
        fscanf(arq_uni, "%d %d", &v, &n);
        vet_univ[i].vagas = v;
        vet_univ[i].nota_min = n;
        vet_univ[i].lista_cand = cria_lista_pref();
    }

    fclose(arq_uni);

    FILE *arq_can = fopen(argv[2], "r");

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


//alocando os candidatos
    aloca(c, vet_univ, vet_cand);


//printando os resultados
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


//desalocando a memoria gasta
    for(int i = 0; i < u; i ++){ //finalizacao do vetor de universidades
        destroi_lista_pref(vet_univ[i].lista_cand);
    }
    for(int i = 0; i < c; i ++){ //finalizacao do vetor de candidatos
        destroi_lista_pref(vet_cand[i].lista_univ);
    } 

  return 0;
}