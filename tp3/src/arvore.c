#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"
#include "lista.h"

arvore_t *cria_arvore(int quant_vert){
    arvore_t *arvore = (arvore_t *) malloc(sizeof(arvore_t));
	if (arvore == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}

    arvore->quant_vert = quant_vert;
	arvore->lista_adj = (lista_t **) malloc(sizeof(lista_t) * quant_vert);
    for(int i = 0; i < quant_vert; i++){
        arvore->lista_adj[i] = cria_lista();
        insere_no(arvore->lista_adj[i], i, -1);
    }
    return arvore;
}

void insere_arvore(arvore_t *arvore, int id_1, int id_2){
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

void print_arvore(arvore_t *arvore){
    for(int i = 0; i < arvore->quant_vert; i++){
        printf("Vertice %d conecta com:\n",i);
        print_lista(arvore->lista_adj[i]);
        printf("\n");
    }
}

void destroi_arvore (arvore_t *arvore){
    for(int i = 0; i < arvore->quant_vert; i++){
        destroi_lista(arvore->lista_adj[i]);
    }
    free(arvore->lista_adj);
    free(arvore);
}