#include <stdio.h>
#include <stdlib.h>

#include "mediana.h"
#include "grafo.h"
#include "distance.h"


int main(int argc, const char **argv) {

  //codigo tp
    FILE *arq = fopen(argv[1], "r");

    int quant_tel;
    fscanf(arq, "%d", &quant_tel);

    double vet_lat[quant_tel];
    double vet_long[quant_tel];

    for(int i=0; i<quant_tel; i++){
        fscanf(arq, "%lf %lf", &vet_lat[i], &vet_long[i]);
    }

    fclose(arq);

    grafo_t *telescopios = cria_grafo(quant_tel);
    int dist;

    for(int i=0; i<quant_tel; i++){
        for(int j=i+1; j<quant_tel; j++){
            dist = distanceEarthKm(vet_lat[i], vet_long[i], vet_lat[j], vet_long[j]);
            insere_aresta(telescopios,i,j,dist);
        }
    }

    printf("%d\n", carmerini(telescopios));
    
    destroi_grafo(telescopios); 


    //teste camerini
//    grafo_t *grafo = cria_grafo(7);
    /*for(int i = 0; i < 5; i++){
        for(int j = i+1; j < 4; j++){
            insere_aresta(grafo, i, j, (j+i)*10);
        }
    }
    //insere_aresta(grafo, 0, 4, 8*10); */
/*    insere_aresta(grafo, 0, 1, 5);
    insere_aresta(grafo, 1, 2, 9);
    insere_aresta(grafo, 0, 2, 7);
    insere_aresta(grafo, 1, 4, 15);
    insere_aresta(grafo, 1, 5, 6);
    insere_aresta(grafo, 2, 3, 8);
    insere_aresta(grafo, 2, 4, 7);
    insere_aresta(grafo, 3, 4, 5);
    insere_aresta(grafo, 5, 4, 8);
    insere_aresta(grafo, 6, 4, 7);
    insere_aresta(grafo, 5, 6, 11);
*/
    //teste partition
/*    printf("Vetor arestas: ");
    for(int i = 0; i < grafo->quant_arestas; i++){
        printf("%d ", grafo->arestas[i].peso);
    }
    printf("\n");

    int pos_pivo[] = {1};
    int ult_pivo = partition_3_way(pos_pivo,grafo->arestas,grafo->quant_arestas);
    printf("Pos primeiro pivo = %d\n",pos_pivo[0]);
    printf("Pos ultimo pivo = %d\n",ult_pivo);

    printf("Vetor arestas: ");
    for(int i = 0; i < grafo->quant_arestas; i++){
        printf("%d ", grafo->arestas[i].peso);
    }
    printf("\n");
*/
    //int c = carmerini(grafo);
    //printf("Resultado Camerini: %d\n", c);

/*    //teste mom_select para arestas

    int quant_arestas = grafo->quant_arestas;
    aresta_t aresta_teste[quant_arestas];

    for(int i=0; i<quant_arestas;i++){
        aresta_teste[i] = grafo->arestas[i];
    }

    int mediana = mom_select(grafo->arestas, quant_arestas/2, quant_arestas);
    insertion_sort(aresta_teste,quant_arestas);
    for (int i=0; i<quant_arestas; i++){
        printf("%d ",aresta_teste[i].peso);
    }
    printf("\n");
    printf("mediana: %d\n", mediana);
    printf("mediana esperada: %d\n", aresta_teste[quant_arestas/2].peso);
*/

//   destroi_grafo(grafo);  
    return 0;
}