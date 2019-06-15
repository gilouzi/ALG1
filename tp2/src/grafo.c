#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "lista.h"
#include "mediana.h"

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

    grafo->arestas = (aresta_t *) malloc(sizeof(aresta_t));
    if (grafo->arestas == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}
    grafo->quant_arestas = 0;

    grafo->floresta = (floresta_t *) malloc(sizeof(floresta_t));
    grafo->floresta->vert = (int *) malloc(sizeof(int)*grafo->quant_vert);
    for(int i = 0; i < grafo->quant_vert; i++){
        grafo->floresta->vert[i] = -1;
    }
    grafo->floresta->quant_comp = 0;

	return grafo;
}


void insere_aresta(grafo_t *grafo, int id_1, int id_2, int peso){

    lista_t *lista1 = grafo->lista_adj[id_1];
    lista_t *lista2 = grafo->lista_adj[id_2];

	insere_no(lista1, id_2, peso);
    insere_no(lista2, id_1, peso);

    grafo->arestas[grafo->quant_arestas].v1 = id_1;
    grafo->arestas[grafo->quant_arestas].v2 = id_2;
    grafo->arestas[grafo->quant_arestas].peso = peso;
    grafo->quant_arestas++;

    aresta_t* aux = realloc(grafo->arestas, (grafo->quant_arestas + 1) * sizeof(aresta_t));
    if (aux == NULL) {
        printf("Erro, sem memoria!\n");
        exit(1);
    }

    grafo->arestas = aux;
}

void dfs_aux(grafo_t *grafo){

    for (int id = 0; id < grafo->quant_vert; id++){
        if(grafo->floresta->vert[id] == -1){
            DFS(grafo, grafo->lista_adj[id], grafo->floresta->vert, grafo->floresta->quant_comp, id);
            grafo->floresta->quant_comp++;
        }
    }
}

void DFS(grafo_t *grafo, lista_t *lista_adj, int *dfs, int i, int id){

    node_t *toVisit = lista_adj -> inicio;
    dfs[id] = i;
    while (toVisit != NULL) {
        id = toVisit->id;
        if(dfs[id] == -1){
            DFS(grafo, grafo->lista_adj[id],dfs,i, id);
        }
        toVisit = toVisit->prox;
    }
    
}

int carmerini(grafo_t *grafo){

    //se o grafo C so tem 1 aresta, esta sera retornada como a resposta
    if(grafo->quant_arestas == 1){
        int res = grafo->arestas[0].peso;
        return res;
    }

    //achar a mediana das arestas do grafo C
    int quant_arestas = grafo->quant_arestas;
    int cam;
    int mediana = mom_select(grafo->arestas, quant_arestas/2, quant_arestas);

    //montar o grafo B de forma a restar n/2 arestas de C
    grafo_t *grafo_B = cria_grafo(grafo->quant_vert);
    grafo_t *grafo_A = cria_grafo(grafo->quant_vert);
    for(int i = 0; i < quant_arestas; i++){
        if(grafo->arestas[i].peso <= mediana && grafo_B->quant_arestas < quant_arestas - (quant_arestas/2)){
            insere_aresta(grafo_B, grafo->arestas[i].v1,grafo->arestas[i].v2,grafo->arestas[i].peso);
        }
        else{
            insere_aresta(grafo_A, grafo->arestas[i].v1,grafo->arestas[i].v2,grafo->arestas[i].peso);
        }
    }

    //encontra os componentes conexos de B
    dfs_aux(grafo_B);

    //se o grafo B é conexo, chama recursivamente a funcao para o grafo B como novo C'
    if(grafo_B->floresta->quant_comp == 1){
        cam = carmerini(grafo_B);
    }

    else{
        //vai inserir no grafo C' as arestas que nao estavam em B que conectam diferentes componentes de B
        grafo_t *grafo_C = cria_grafo(grafo_B->floresta->quant_comp);
        for(int i = 0; i < grafo_A->quant_arestas; i++){
            int v1 = grafo_A->arestas[i].v1;
            int v2 = grafo_A->arestas[i].v2;
            int c1 = grafo_B->floresta->vert[v1];
            int c2 = grafo_B->floresta->vert[v2];
            if(c1 != c2){
                int peso = grafo_A->arestas[i].peso;
                insere_aresta(grafo_C,c1,c2,peso);
            }
        }

        //chama recursivamente a funcao para o novo grafo C'
        cam = carmerini(grafo_C);

        //free no grafo criado durante a funcao
        destroi_grafo(grafo_C);
    }

    destroi_grafo(grafo_B);
    destroi_grafo(grafo_A);
    return cam;
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
    free(grafo->floresta->vert);
    free(grafo->floresta);
    free(grafo->lista_adj);
    free(grafo->arestas);
    free(grafo);
}