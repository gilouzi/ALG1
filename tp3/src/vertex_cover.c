#include <stdio.h>
#include <stdlib.h>

#include "vertex_cover.h"
#include "arvore.h"
#include "grafo.h"

int min(int valor1, int valor2){
    if(valor1 < valor2)
        return valor1;
    else
        return valor2;
}

int vertex_cover_arvore(int pos_pai, arvore_t *arvore){
    lista_t *lista_node = arvore->lista_adj[pos_pai];
    node_t *pai = lista_node->inicio;

    //se o peso do cover ja foi avaliado, retorna ele pra evitar ser recomputado
    if(pai->peso != -1){
        return pai->peso;
    }

    //se nao tem filhos, o peso do vertex cover é 0
    if(lista_node->num_elementos <= 1){
        pai->peso = 0;
        return pai->peso;
    }

    //atualiza a lista dos filhos pra que eles nao tenham o pai como nó filho
    node_t *filho = pai->prox;
    while(filho != NULL){
        remove_no(arvore->lista_adj[filho->id], pos_pai);
        filho = filho->prox;
    }

    //calcula o peso do cover quando o no faz parte da resposta
    int peso1 = 1; //contagem da participacao do no
    filho = pai->prox;
    while (filho != NULL){ //contagem da participacao dos filhos
        peso1 += vertex_cover_arvore(filho->id, arvore);
        filho = filho->prox;
    }

    //calcula o peso do cover quando o no nao faz parte da resposta
    int peso2 = 0;
    filho = pai->prox;
    while (filho != NULL){ //contagem da participacao dos filhos (todos participam) e dos netos
        lista_t *lista_filho = arvore->lista_adj[filho->id];
        node_t *neto =  lista_filho->inicio->prox;
        peso2 += 1; //participacao do filho
        while(neto != NULL){ //participacao dos netos
            peso2+= vertex_cover_arvore(neto->id, arvore);
            neto = neto->prox;
        }
        filho = filho->prox;
    }

    //guarda o menor valor calculado dos covers como o peso do no
    pai->peso = min(peso1,peso2);

    return pai->peso;
}

void vertex_cover_grafo(grafo_t *grafo){
    int vert[grafo->quant_vert];
    lista_t *resultado = cria_lista();

    //inicializacao dos vertices como nao visitados
    for(int i=0; i<grafo->quant_vert; i++){
        vert[i] = 0;
    }

    //vai andar por todas as arestas olhando se os vertices foram ou nao visitados
    for(int i=0; i<grafo->quant_arestas; i++){
        int id_v1 = grafo->arestas[i].v1;
        int id_v2 = grafo->arestas[i].v2;
        //se ambos nao tiverem sido visitados ainda serao escolhidos como parte da resposta
        if(vert[id_v1] == 0 && vert[id_v2] == 0){
            //guarda o valor dos vertices escolhidos
            insere_no(resultado,id_v1,0);
            insere_no(resultado,id_v2,0);
            //coloca os vertices como visitados
            vert[id_v1] = 1;
            vert[id_v2] = 1;
        }
    }

    //imprime quantidade de vertices escolhidos e quais foram escolhidos
    printf("%d\n",resultado->num_elementos);
    print_id_lista(resultado);
    destroi_lista(resultado);

}