#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "vertex_cover.h"

int main(int argc, const char **argv) {

  //codigo tp
    FILE *arq = fopen(argv[2], "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    int quant_vert;
    int quant_arestas;
    int id_1, id_2;
    fscanf(arq, "%d %d", &quant_vert, &quant_arestas);

    if(strcmp(argv[1], "tarefa1") == 0){
        arvore_t *arvore = cria_arvore(quant_vert);
        for(int i=0; i<quant_arestas; i++){
            fscanf(arq, "%d %d", &id_1, &id_2);
            insere_arvore(arvore,id_1,id_2);
        }

        int resultado = vertex_cover_arvore(0,arvore);
        printf("%d\n",resultado);

        destroi_arvore(arvore);
    }

    else{
        grafo_t *grafo = cria_grafo(quant_vert);
        for(int i=0; i<quant_arestas; i++){
            fscanf(arq, "%d %d", &id_1, &id_2);
            insere_aresta(grafo,id_1,id_2);
        }

        if (grafo->quant_arestas != quant_arestas) {
            printf("FUDEU");
            exit(1);
        }

        vertex_cover_grafo(grafo);
        destroi_grafo(grafo);
    }

    fclose(arq);
    

     
    return 0;
}