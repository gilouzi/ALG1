#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main(int argc, const char **argv) {

  //codigo tp
    FILE *arq = fopen(argv[1], "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    int quant_vert;
    int quant_arestas;
    int id_1, id_2;
    fscanf(arq, "%d %d", &quant_vert, &quant_arestas);
    arvore_t *arvore = cria_arvore(quant_vert);
    for(int i=0; i<quant_arestas; i++){
        fscanf(arq, "%d %d", &id_1, &id_2);
        //sempre o vertice menor vai apontar para os vertices maiores
        if(id_1 < id_2){
            lista_t *lista_id1 = arvore->lista_adj[id_1];
            insere_no(lista_id1,id_2,-1);
        }
        else{
            lista_t *lista_id2 = arvore->lista_adj[id_2];
            insere_no(lista_id2,id_1,-1);
        }
    }
    fclose(arq);

    print_arvore(arvore);
    int resultado = vertex_cover(0,arvore);
    print_arvore(arvore);
    printf("%d\n",resultado);

    destroi_arvore(arvore);

     
    return 0;
}