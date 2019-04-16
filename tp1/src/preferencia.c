#include <stdio.h>
#include <stdlib.h>

#include "preferencia.h"

lista_pref_t *cria_lista_pref(){
	lista_pref_t *lista = (lista_pref_t *) malloc(sizeof(lista_pref_t));
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


void insere_pref(lista_pref_t *lista_pref, int id, int pos){

	pref_t *novo = (pref_t *) malloc(sizeof(pref_t));

	if (novo == NULL)
	{
		printf("Erro, sem memoria\n");
		exit(1);
	}

	novo->pref_id = id;
	novo->pref_pos = pos;
	novo->prox = NULL;

	if (lista_pref->inicio == NULL){
		novo->prev = NULL;
		lista_pref->inicio = novo;
	}

	if (lista_pref->inicio != NULL)	{
		novo->prev=lista_pref->fim;
	}

	if (lista_pref->fim != NULL)
	{
		lista_pref->fim->prox = novo; 
	}

	lista_pref->fim = novo;


	lista_pref->num_elementos++;

}

void remove_inicio (lista_pref_t *lista){
	pref_t *toFree = lista -> inicio;
	if(toFree -> prox != NULL){
		lista -> inicio = lista -> inicio -> prox;
		lista -> inicio -> prev = NULL;
	}
	else{
		lista -> fim = NULL;
		lista -> inicio = NULL;
	}
	free(toFree);
}

int remove_fim(lista_pref_t *lista) {
	pref_t *toFree = lista -> fim;
	if(toFree -> prev != NULL){
		lista -> fim = lista -> fim -> prev;
		lista -> fim -> prox = NULL;
	}
	else{
		lista -> fim = NULL;
		lista -> inicio = NULL;
	}
	int id = toFree->pref_id;
	free(toFree);
	return(id);
}

void print_lista_pref(lista_pref_t *lista){
	pref_t *toVisit = lista -> inicio;
	pref_t *toPrint;
	//printf("chamou printar preferencia\n");

	while (toVisit != NULL) {
		toPrint = toVisit;
		toVisit = toVisit->prox;
		printf("%d\n", toPrint->pref_id);
	}
}

void destroi_lista_pref (lista_pref_t *lista) {
	pref_t *toVisit = lista -> inicio;
	pref_t *toFree;

	while (toVisit != NULL) {
		toFree = toVisit;
		toVisit = toVisit->prox;
		free(toFree);
	}
	free(lista);
}