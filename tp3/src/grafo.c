#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "lista.h"

grafo_t *cria_grafo(int quant_vert){

	grafo_t *grafo = (grafo_t *) malloc(sizeof(grafo_t));
	if (grafo == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}

    grafo->quant_vert = quant_vert;
	grafo->lista_adj = (lista_t **) malloc(sizeof(lista_t) * quant_vert);
    for(int i = 0; i < quant_vert; i++){
        grafo->lista_adj[i] = cria_lista();
    }

    grafo->quant_arestas = 0;

	return grafo;
}

int max_vertice(grafo_t *grafo){
    lista_t **lista_adj = grafo->lista_adj;
    int id_max = 0;
    int quant_max = lista_adj[0]->num_elementos;

    for(int i = 1; i<grafo->quant_vert; i++){
        if(quant_max < lista_adj[i]->num_elementos){
            id_max = i;
            quant_max = lista_adj[i]->num_elementos;
        }
    }

    return id_max;
}

int max_vertice_conect(grafo_t *grafo, int id_v1){
    lista_t **lista_adj = grafo->lista_adj;
    lista_t *lista_v1 = lista_adj[id_v1];
    int id_max = lista_v1->inicio->id;
    int quant_max = lista_adj[id_max]->num_elementos;
    node_t *toVisit = lista_v1->inicio->prox;

    while(toVisit != NULL){
        int id = toVisit->id;
        int num_elementos = lista_adj[id]->num_elementos;
        if(quant_max < num_elementos){
            id_max = id;
            quant_max = num_elementos;
        }
        toVisit = toVisit->prox;
    }

    return id_max;
}

void insere_aresta(grafo_t *grafo, int id_1, int id_2, int peso){

    lista_t *lista1 = grafo->lista_adj[id_1];
    lista_t *lista2 = grafo->lista_adj[id_2];

	insere_no(lista1, id_2, peso);
    insere_no(lista2, id_1, peso);

    grafo->quant_arestas++;

}

void remove_vertice(grafo_t *grafo, int id){
    lista_t **lista_adj = grafo->lista_adj;
    lista_t *lista_id = grafo->lista_adj[id];

    while(lista_id->num_elementos != 0){
        int id2 = lista_id->inicio->id;
        remove_no(lista_adj[id2],id);
        remove_inicio(lista_id);
        grafo->quant_arestas--;
    }
}

void print_grafo(grafo_t *grafo){
    for(int i = 0; i < grafo->quant_vert; i++){
        printf("Vertice %d conecta com:\n",i);
        print_lista(grafo->lista_adj[i]);
        printf("\n");
    }
}

void destroi_grafo (grafo_t *grafo){
	for(int i = 0; i < grafo->quant_vert; i++){
        destroi_lista(grafo->lista_adj[i]);
    }
    free(grafo->lista_adj);
    free(grafo);
}