#include <stdio.h>
#include <stdlib.h>

#include "mediana.h"

int mom(aresta_t *arestas, int quant_arestas){
    int quant_med = quant_arestas/5;
    aresta_t vet_med[quant_med];
    aresta_t vet_5[5];
    //int pivot;


    /*aresta_t aresta_teste[quant_arestas];

    for(int i=0; i<quant_arestas;i++){
        aresta_teste[i] = arestas[i];
    }
    insertion_sort(aresta_teste,quant_arestas);
    printf("Vetor teste: \n");
    for (int i=0; i<quant_arestas; i++){
        printf("%d ",aresta_teste[i].peso);
    }
    printf("\n");*/



    //se tivermos um vetor de medianas com menos de 5 elementos, podemos pegar a mediana do vetor
    if(quant_arestas < 5){
        insertion_sort(arestas, quant_arestas);
        return arestas[quant_arestas/2].peso;
    }

    //o vetor original é dividido em vetores de tamanho 5 e encontrado a mediana de cada, guardados no vetor de medianas
    else{
        for (int i = 0; i < quant_med; i++){
            for(int j = 0; j < 5; j++){
                vet_5[j] = arestas[i*5+j];
            }
            insertion_sort(vet_5, 5);
            vet_med[i] = vet_5[2];
        }
        return mom(vet_med, quant_med);
    }
}

int mom_select(aresta_t *arestas, int k, int quant_arestas){
    
    int pivot = mom(arestas,quant_arestas);
    int pos_pivot;
    for(int i = 0; i < quant_arestas; i++){
        if(arestas[i].peso == pivot){
            pos_pivot = i;
            break;
        }
    }


    int pos_ultim_pivot = partition_3_way(&pos_pivot, arestas, quant_arestas);
    // for(int i = 0; i < quant_arestas; i++){
    //    printf("%d ", arestas[i].peso);
    // }
    // printf("\n");
    // printf("Pivot = %d na posicao %d\n", pivot, pos_pivot);
    // printf("k = %d\n", k);

    // getchar();

    //o pivot esta a direita do que deveria, vai tentar encontrar novo pivot pro restante a esquerda
    if(k < pos_pivot){
        int tam_vet_esq = pos_pivot;
        aresta_t vet_esq[tam_vet_esq];
        for(int i = 0; i < tam_vet_esq; i++){
            vet_esq[i] = arestas[i];
        }

        // printf("Chama funcao pra esquerda:\n");
        // for(int i = 0; i < tam_vet_esq; i++){
        //     printf("%d ",vet_esq[i].peso);
        // }
        // printf("\n");

        // getchar();


        return mom_select(vet_esq, k, tam_vet_esq);
    }
    //o pivot esta a esquerda do que deveria, vai tentar encontrar novo pivot pro restante a direita
    else if(k > pos_ultim_pivot){
        int tam_vet_dir = quant_arestas - pos_ultim_pivot - 1;
        aresta_t vet_dir[tam_vet_dir];
        for(int i = 0; i < tam_vet_dir; i++){
            vet_dir[i] = arestas[pos_ultim_pivot + i + 1];
        }

        // printf("Chama funcao pra direita:\n");
        // for(int i = 0; i < tam_vet_dir; i++){
        //     printf("%d ",vet_dir[i].peso);
        // }
        // printf("\n");

        // getchar();


        return mom_select(vet_dir, k - pos_ultim_pivot - 1, tam_vet_dir);
    }
    //k = k, o pivot esta na posicao certa, ou seja, é a mediana
    else{ 
        return arestas[pos_pivot].peso;
    }

}

void insertion_sort(aresta_t *arestas, int quant_arestas){
    for(int i = 0; i < quant_arestas; i++){
        for(int j = i; j > 0; j --){
            if(arestas[j].peso < arestas[j-1].peso){
                troca_elem(j, j-1, arestas);
            }
        }
    }
}

int partition_3_way(int *pos_pivot, aresta_t *arestas, int quant_arestas) {
    //pivot sera trocado com o elemento da primeira posicao
    troca_elem(0, *pos_pivot, arestas);
    *pos_pivot = 0;
    int pos_pivot_aux = 0;
    int quant_pivot = 0;
    int i = 1;
    int j = quant_arestas-1;

    while(j >= i) {
        //se o elemento comparado for menor vai pra tras do pivot
        if(arestas[i].peso < arestas[*pos_pivot].peso){
            troca_elem(i, *pos_pivot, arestas);
            *pos_pivot = i;
            i++;
        }

        //se o elemento comparado for maior vai pra direita do pivot
        else if(arestas[i].peso > arestas[*pos_pivot].peso){
            troca_elem(j, i, arestas);
            j--;
        }

        //se o elemento for igual vai permanecer junto ao pivot
        else if(arestas[i].peso == arestas[*pos_pivot].peso){
            if (pos_pivot_aux == 0){
                pos_pivot_aux = i;
            }
            quant_pivot ++;
            i++;
        }

        if(*pos_pivot > pos_pivot_aux && pos_pivot_aux != 0){
            *pos_pivot = pos_pivot_aux;
            pos_pivot_aux = *pos_pivot + 1;
        }
    }

    return *pos_pivot + quant_pivot;
}

void troca_elem(int pos1, int pos2, aresta_t *arestas) {

    aresta_t aux = arestas[pos1];
    arestas[pos1] = arestas[pos2];
    arestas[pos2] = aux;

}