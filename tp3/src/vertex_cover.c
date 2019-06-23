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
    lista_t *resultado = cria_lista();
    while(grafo->quant_arestas != 0){
        //vai calcular o vertice v1 que tem maior quantidade de arestas conectadas
        int id_v1 = max_vertice(grafo);

        //vai calcular o vertice v2 com maior quantidade de arestas dos que se conectam a v1
        int id_v2 = max_vertice_conect(grafo, id_v1);

        //vai remover todas as arestas que conectam com os vertices escolhidos
        remove_vertice(grafo,id_v1);
        remove_vertice(grafo,id_v2);

        //guarda o valor dos vertices escolhidos
        insere_no(resultado,id_v1,0);
        insere_no(resultado,id_v2,0);
    }
    //imprime quantidade de vertices escolhidos e quais foram escolhidos
    printf("%d\n",resultado->num_elementos);
    print_id_lista(resultado);

}