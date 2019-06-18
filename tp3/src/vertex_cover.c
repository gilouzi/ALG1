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

int vertex_cover_arvore(int pos_node, arvore_t *arvore){
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
        peso1 += vertex_cover_arvore(filho->id, arvore);
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
            peso2+= vertex_cover_arvore(neto->id, arvore);
            neto = neto->prox;
        }
        filho = filho->prox;
    }

    //guarda o menor valor calculado dos covers como o peso do no
    node->peso = min(peso1,peso2);

    return node->peso;
}

void vertex_cover_grafo(grafo_t *grafo){

    while(grafo->quant_arestas != 0){
        //vai calcular o vertice que tem maior quantidade de arestas conectadas
        int id_max = max_vertice(grafo);

        //vai remover todas as arestas que conectam com o vertice escolhido
        remove_vertice(grafo,id_max);

        //imprime o valor do vertice escolhido
        printf("%d\n", id_max);
    }

}