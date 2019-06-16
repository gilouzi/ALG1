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

int min(int valor1, int valor2){
    if(valor1 < valor2)
        return valor1;
    else
        return valor2;
}

int vertex_cover(int pos_node, arvore_t *arvore){
    lista_t *lista_node = arvore->lista_adj[pos_node];
    node_t *node = lista_node->inicio;

    //se o peso do cover ja foi avaliado, retorna ele pra evitar ser recomputado
    if(node->peso != -1){
        return node->peso;
    }

    //se nao tem filhos, o peso do vertex cover é 0
    if(lista_node->num_elementos <= 1){
        node->peso = 0;
        return node->peso;
    }

    //calcula o peso do cover quando o no faz parte da resposta
    int peso1 = 1; //contagem da participacao do no
    node_t *filho = node->prox;
    while (filho != NULL){ //contagem da participacao dos filhos
        peso1 += vertex_cover(filho->id, arvore);
        filho = filho->prox;
    }

    //calcula o peso do cover quando o no nao faz parte da resposta
    int peso2 = 0;
    filho = node->prox;
    while (filho != NULL){ //contagem da participacao dos filhos (todos participam) e dos netos
        lista_t *lista_filho = arvore->lista_adj[filho->id];
        node_t *neto =  lista_filho->inicio->prox;
        peso2 += 1; //participacao do filho
        while(neto != NULL){ //participacao dos netos
            peso2+= vertex_cover(neto->id, arvore);
            neto = neto->prox;
        }
        filho = filho->prox;
    }

    //guarda o menor valor calculado dos covers como o peso do no
    node->peso = min(peso1,peso2);

    return node->peso;
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