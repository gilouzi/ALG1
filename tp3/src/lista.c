#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

lista_t *cria_lista(){
	lista_t *lista = (lista_t *) malloc(sizeof(lista_t));
	if (lista == NULL)
	{
		printf("Erro, sem memoria!\n");
		exit(1);
	}
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->num_elementos=0;
	return lista;
}


void insere_no(lista_t *lista, int id, int peso){

	node_t *novo = (node_t *) malloc(sizeof(node_t));

	if (novo == NULL)
	{
		printf("Erro, sem memoria\n");
		exit(1);
	}

	novo->id = id;
	novo->peso = peso;
	novo->prox = NULL;

	if (lista->inicio == NULL){
		novo->prev = NULL;
		lista->inicio = novo;
	}

	if (lista->inicio != NULL)	{
		novo->prev=lista->fim;
	}

	if (lista->fim != NULL)
	{
		lista->fim->prox = novo; 
	}

	lista->fim = novo;


	lista->num_elementos++;

}

void remove_inicio (lista_t *lista){
	node_t *toFree = lista -> inicio;
	if(toFree -> prox != NULL){
		lista -> inicio = lista -> inicio -> prox;
		lista -> inicio -> prev = NULL;
	}
	else{
		lista -> fim = NULL;
		lista -> inicio = NULL;
	}
	lista->num_elementos--;
	free(toFree);
}

void remove_no(lista_t *lista, int id){
	node_t *toFree = lista -> inicio;

	while(toFree != NULL){
		if(toFree->id == id){
			if(toFree->prev == NULL && toFree->prox != NULL){
				lista->inicio = toFree->prox;
				toFree->prox->prev = NULL;
			}
			else if(toFree->prev == NULL && toFree->prox == NULL){
				lista->inicio = NULL;
				lista->fim = NULL;
			}
			else if(toFree->prev != NULL && toFree->prox == NULL){
				lista->fim = toFree->prev;
				toFree->prev->prox = NULL;
			}
			else{
				toFree->prox->prev = toFree->prev;
				toFree->prev->prox = toFree->prox;
			}
			lista->num_elementos--;
			free(toFree);
			return;
		}
		else{
			toFree = toFree->prox;
		}
	}
}

int remove_fim(lista_t *lista) {
	node_t *toFree = lista -> fim;
	if(toFree -> prev != NULL){
		lista -> fim = lista -> fim -> prev;
		lista -> fim -> prox = NULL;
	}
	else{
		lista -> fim = NULL;
		lista -> inicio = NULL;
	}
	lista->num_elementos--;
	int id = toFree->id;
	free(toFree);
	return(id);
}

void print_lista(lista_t *lista){
	node_t *toVisit = lista -> inicio;
	node_t *toPrint;

	while (toVisit != NULL) {
		toPrint = toVisit;
		toVisit = toVisit->prox;
		printf("id: %d, peso: %d\n", toPrint->id, toPrint->peso);
	}
}

void destroi_lista (lista_t *lista) {
	node_t *toVisit = lista -> inicio;
	node_t *toFree;

	while (toVisit != NULL) {
		toFree = toVisit;
		toVisit = toVisit->prox;
		free(toFree);
	}
	free(lista);
}