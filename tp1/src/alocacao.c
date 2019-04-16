#include <stdio.h>
#include <stdlib.h>

#include "alocacao.h"

void aloca(int c, univ_t *vet_univ, cand_t *vet_cand) {
    for (int i = 0; i < c; i++){ //vai andar por todo o vetor candidatos alocando o candidato i
        //printf("1.alocando candidato %d\n", i+1);
        aloca_cand_i(vet_univ, vet_cand, i);
    }
}

void aloca_cand_i(univ_t *vet_univ, cand_t *vet_cand, int i){
    //printf("2.alocando candidato %d\n", i+1);
    if(vet_cand[i].lista_univ->inicio == NULL){ //nao tem universidades de interesse
        //printf("cand %d nao tem interesse\n", i+1);
        return;
    }
    else{

        int pref = vet_cand[i].lista_univ->inicio->pref_id; //a universidade pra qual o candidato quer ir eh a primeira da lista
        univ_t *uni_pref = &vet_univ[pref]; //universidade de preferencia do candidato 
        lista_pref_t *lista_c = uni_pref->lista_cand; //lista de candidatos da universidade de preferencia
        cand_t *cand = &vet_cand[i]; //candidato que esta tentando entrar na universidade

        if(uni_pref->nota_min > cand->nota){ //aluno nao tem nota pra entrar na universidade
            remove_inicio(cand->lista_univ); //remove a primeira opcao do candidato ja q n sera possivel
            //printf("cand %d nao tem nota pra entrar na universidade %d\n", i+1, pref+1);
            aloca_cand_i(vet_univ, vet_cand, i); //tenta alocar novamente o candidato
            return;
        }

        else{ //aluno tem nota pra entrar na universidade
            int pos_pref = cand->lista_univ->inicio->pref_pos;

            if(uni_pref->vagas > lista_c->num_elementos){ //ainda nao tem todas vagas preenchidas
                insere_cand_ordenado(i, lista_c, vet_cand, pos_pref); //inserir o candidato em ordem decrescente de nota
                cand->aloc = pref; //esta alocado na univ de preferencia
                //printf("cand %d tem nota pra entrar na universidade %d e as vagas nao estao todas preenchidas\n", i+1, pref+1);
                return;
            }

            else{ //todas as vagas da universidade foram preenchidas

                int id_ultimo = lista_c->fim->pref_id; //ultimo candidato colocado na univ de interesse
                cand_t *ultimo = &vet_cand[id_ultimo];
                int pos_pref_ult = lista_c->fim->pref_pos;

                if(ultimo->nota == cand->nota){ //a nota do candidato eh igual do q a menor nota inserida, tera q preferenciar ou oq tem maior preferencia, ou o q tem menor id
                    //printf("pref_pos cand %d eh %d e o do ultimo %d eh %d \n",cand->lista_univ->inicio->pref_id, pos_pref, lista_c->fim->pref_id, pos_pref_ult);
                    if(pos_pref < pos_pref_ult ){ //o candidato sendo analisado prefere a universidade mais doq o q estava inserido
                        int new_i = remove_fim(lista_c);
                        insere_cand_ordenado(i, lista_c, vet_cand, pos_pref);
                        cand->aloc = pref; //esta alocado na univ de preferencia
                        vet_cand[new_i].aloc = -1; //foi desalocado
                        //printf("cand %d tem nota pra entrar na universidade %d e as vagas estavam todas preenchidas\n", i+1, pref+1);
                        //printf("cand %d era o ultimo alocado e tinha mesma nota mas menos preferencia\n", new_i+1);
                        aloca_cand_i(vet_univ, vet_cand, new_i); //o aluno que foi desalocado precisa ir pra uma nova universidade
                    }
                    else{ //o candidato de mesma nota que ja estava alocado tem preferencia
                        remove_inicio(cand->lista_univ);
                        //printf("cand %d tem nota igual pra entrar na universidade %d mas n tem preferencia\n", i+1, pref+1);
                        aloca_cand_i(vet_univ, vet_cand, i); //tentar alocar de novo o candidato pra nova lista de preferencia
                    }
                }
                else if(ultimo->nota < cand->nota){ //a nota do candidato eh maior do que a menor nota ja na universidade, pode entrar
                    int new_i = remove_fim(lista_c);
                    insere_cand_ordenado(i, lista_c, vet_cand, pos_pref);
                    cand->aloc = pref; //esta alocado na univ de preferencia
                    vet_cand[new_i].aloc = -1; //foi desalocado
                    //printf("cand %d tem nota pra entrar na universidade %d e as vagas estavam todas preenchidas\n", i+1, pref+1);
                    //printf("cand %d era o ultimo alocado\n", new_i+1);
                    aloca_cand_i(vet_univ, vet_cand, new_i); //o aluno que foi desalocado precisa ir pra uma nova universidade
                }
                else{ //a menor nota da universidade eh maior q a do candidato, entao nao pode escolher essa opcao
                    //printf("4 ");
                    remove_inicio(cand->lista_univ);
                    //printf("cand %d nao tem nota pra entrar na universidade %d\n", i+1, pref+1);
                    aloca_cand_i(vet_univ, vet_cand, i); //tentar alocar de novo o candidato pra nova lista de preferencia
                }
            }
        }
    }
    return;
}

void insere_cand_ordenado(int id_cand, lista_pref_t *lista_cand, cand_t *vet_cand, int pos){

    int nota_cand = vet_cand[id_cand].nota;
	pref_t *novo = (pref_t *) malloc(sizeof(pref_t));

	if (novo == NULL)
	{
		printf("Erro, sem memoria\n");
		exit(1);
	}

	novo->pref_id = id_cand;
    novo->pref_pos = pos;

	if (lista_cand->inicio == NULL){ //lista vazia vai ser o primeiro da lista
        //printf("inserindo primeira preferencia\n");
		novo->prev = NULL;
        novo->prox = NULL;
		lista_cand->inicio = novo;
        lista_cand->fim = novo;
	}

	else{ //lista nao vazia, caminhar ate achar uma nota menor
        pref_t *toVisit = lista_cand -> inicio;
        pref_t *toCompare;
        //printf("inserindo mais uma preferencia\n");

        while (toVisit != NULL) {
            toCompare = toVisit;
            if(vet_cand[toCompare->pref_id].nota < nota_cand){ //vai inserir o candidato antes do candidato comparado
                novo->prev = toCompare->prev;
                novo->prox = toCompare;
                toCompare->prev = novo;
                if(lista_cand->inicio == toCompare){
                    lista_cand->inicio = novo;
                }
                return;
            }
            toVisit = toVisit->prox;
        }
        //chegou no fim da lista sem nenhuma nota menor que ele, insere no final da lista
        novo->prev = toCompare;
        toCompare->prox = novo;
        novo->prox = NULL;
        lista_cand->fim = novo;
	}

	lista_cand->num_elementos++;

}