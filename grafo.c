#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"
#include "fila-prio.h"
#include "pilha.h"

struct grafo {
    int num_vertices;                   // qtd de vertices do grafo
    int num_arcos;                      // qtd de arcos do grafo
    struct vertice* lista_vertices;     // lista de vertices do garfo
};

struct vertice {
    char valor_vert[MAX_NOME];          // valor do vertice
    struct vertice* prox;               // proximo vertice do lista
    struct arco* lista_adj;             // lista de vertices adjacentes a este vertice              
};

struct arco {
    char valor_vert[MAX_NOME];           // valor do vertice adjacente
    int peso_arco;
    struct arco* prox;                   // endereço do proximo vertice adjacente 
};

struct vertice* insere_vertice (struct vertice* ini, char* valor_vert) {
    struct vertice* novo_vertice = (struct vertice*)malloc(sizeof(struct vertice));
    strcpy(novo_vertice->valor_vert, valor_vert);
    novo_vertice->prox = ini;   // inserção no inicio da lista
    novo_vertice->lista_adj = NULL;
    return novo_vertice;
}

grafo cria_grafo () {
    grafo gf = (grafo)malloc(sizeof(struct grafo));
    if (gf != NULL) {
        gf->num_vertices = 0;
        gf->num_arcos = 0;
    }

    return gf;
}

struct arco* insere_adjacencia (struct arco* ini, char* vert_dest, int peso) {
    struct arco* novo = (struct arco*)malloc(sizeof(struct arco));
    strcpy(novo->valor_vert, vert_dest);
    novo->peso_arco = peso;
    novo->prox = ini;     // inserção no inicio da lista
    return novo;
}

int insere_arco (grafo gf, char* vert1, char* vert2, int peso) {
    if (gf == NULL) 
        return 0;

    struct vertice* v;
    struct arco* a;

    for (v = gf->lista_vertices; v != NULL; v = v->prox) 
        if (strcmp(v->valor_vert, vert1) == 0) {
            for (a = v->lista_adj; a != NULL; a = a->prox)
                if (strcmp(a->valor_vert, vert2) == 0)
                    return 0;   // arco ja existe
            v->lista_adj = insere_adjacencia(v->lista_adj, vert2, peso);
            gf->num_arcos++;
        }
}

void insere_novo_vertice (grafo gf, char* val) {
    gf->lista_vertices = insere_vertice(gf->lista_vertices, val);
    gf->num_vertices++;
}

// retorna 1 se o vertice existe no grafo, 0 caso contrário
int eh_vertice (grafo gf, char* vert) {
    if (gf == NULL) 
        return -1;

    struct vertice* v;

    for (v = gf->lista_vertices; v != NULL; v = v->prox) 
        if (strcmp(v->valor_vert, vert) == 0) 
            return 1;
    
    return 0;
}

void mostra_lista (grafo gf) {
    if (gf == NULL)
        return;

    struct vertice* v;
    struct arco* a; 
    printf("\n\n=== LISTA DE ADJACÊNCIA ===\n");
    for (v = gf->lista_vertices; v != NULL; v = v->prox) {
        printf("\nVértice %s:", v->valor_vert);
        for (a = v->lista_adj; a != NULL; a = a->prox) 
            printf(" (%s, %d)", a->valor_vert, a->peso_arco);
    }
}

lista letraC (grafo g, char* vert_origem, int K) {
    struct vertice* vert_aux;   // ponteiro para percorrimento do grafo  
    struct arco* arco_aux;      // ponteiro para percorrimento do grafo
    lista relacionados = cria_lista(); // lista que será retornada       

    for (vert_aux = g->lista_vertices; vert_aux != NULL; vert_aux = vert_aux->prox) {
        // se for o vértice de origem, olhamos as adjacências do vértice de origem
        if (strcmp(vert_origem, vert_aux->valor_vert) == 0) 
            for (arco_aux = vert_aux->lista_adj; arco_aux != NULL; arco_aux = arco_aux->prox) 
                if (arco_aux->peso_arco >= K  && JaInseridoLista(arco_aux->valor_vert, relacionados) == 0) 
                    insere_elem(&relacionados, arco_aux->valor_vert);      
            
        // se não for o vértice de origem, se o vértice de origem é adjancência do vértice
        if (strcmp(vert_origem, vert_aux->valor_vert) != 0)
            for (arco_aux = vert_aux->lista_adj; arco_aux != NULL; arco_aux = arco_aux->prox) 
                if (strcmp(arco_aux->valor_vert, vert_origem) == 0 && arco_aux->peso_arco >= K && JaInseridoLista(vert_aux->valor_vert, relacionados) == 0)
                    insere_elem(&relacionados, vert_aux->valor_vert);    
    }

    return relacionados;
}
void BuscaEmProfundidade (grafo G, char* v, lista *l) {
   struct vertice *nv;
   struct arco *na;
   lista visitados = cria_lista();
   char vt[MAX_NOME];
   TipoPilha *pilha;
   int i=0;
   pilha = (TipoPilha *) malloc (sizeof(TipoPilha));
   IniciaPilha(pilha);
   Empilha(v,pilha);
   while(!VaziaPilha(pilha)){
       Desempilha(pilha, vt);
       //printf("\nDesempilhou: %s",vt);
       if (JaInseridoLista(vt, visitados) == 0){
          insere_elem(&visitados, vt);
          for (nv = G->lista_vertices; nv!=NULL; nv = nv->prox) 
              if(strcmp(vt, nv->valor_vert) == 0)
                 for (na = nv->lista_adj; na != NULL; na = na->prox)
                      if (JaInseridoLista(na->valor_vert, visitados)==0){
                           Empilha(na->valor_vert,pilha);
                           //printf("\nEmpilhou: %s",na->valor_vert);
                      }
       }
   }
   remove_elem(&visitados, v);
   *l = visitados;
   free(pilha);
}

void letraD(char *nome, grafo g, lista *l){
    lista lista1 = cria_lista();
    lista lista2 = cria_lista();
    lista lista_final = cria_lista();
    char nome2[MAX_NOME];
    BuscaEmProfundidade(g, nome, &lista1);
    if(lista_vazia(lista1))
        return;
    int i;
    for(i = 1; get_elem_pos(lista1, i, nome2) != 0; i++){
        BuscaEmProfundidade(g, nome2, &lista2);
        if(JaInseridoLista(nome, lista2))
            insere_elem(&lista_final, nome2);
        esvazia_lista(&lista2);
    }
    *l = lista_final;
    apaga_lista(&lista1);
    apaga_lista(&lista2);
    return;
}

void letraE (grafo g, char* origem, char* destino) {
    Pred predecessores[g->num_vertices];
    struct dist distancia[g->num_vertices];
    int i;
    char nome_val[MAX_NOME];       // variável para recuperar o nome do heap
    int peso_val;                 // variável para recuperar o peso do heap
    struct vertice* vert_aux;
    struct arco* arco_aux;
    fila_prio f = cria_fila_prio();

    for (vert_aux = g->lista_vertices, i = 0; vert_aux != NULL; vert_aux = vert_aux->prox, i++) {
        strcpy(distancia[i].nome, vert_aux->valor_vert);
        if (strcmp(vert_aux->valor_vert, origem) == 0) 
            distancia[i].dist = 0;
        else
            distancia[i].dist = 99999;
        strcpy(predecessores[i].nome, vert_aux->valor_vert);
        strcpy(predecessores[i].antecessor, "vazio");
        insere_prio(f, vert_aux->valor_vert, distancia[i].dist);
    }

    while (!fila_prio_vazia(f)) {
        remove_prio(f, nome_val, &peso_val);
        for (vert_aux = g->lista_vertices; vert_aux != NULL; vert_aux = vert_aux->prox) {
            if (strcmp(vert_aux->valor_vert, nome_val) == 0) 
                break;
        }

        if (vert_aux == NULL)
            return; // não tem o vértice, deu ruim

        for (arco_aux = vert_aux->lista_adj; arco_aux != NULL; arco_aux = arco_aux->prox) {
            int x, y;

            for (x = 0; x < g->num_vertices; x++) 
                if (strcmp(distancia[x].nome, arco_aux->valor_vert) == 0) 
                    break;
            
            for (y = 0; y < g->num_vertices; y++) 
                if (strcmp(distancia[y].nome, nome_val) == 0) 
                    break;
            
            if (distancia[x].dist > distancia[y].dist + arco_aux->peso_arco) {
                distancia[x].dist = distancia[y].dist + arco_aux->peso_arco;
                strcpy(predecessores[x].antecessor, nome_val);
                char aux1[MAX_NOME]; 
                strcpy(aux1, distancia[x].nome);
                int aux2 = distancia[x].dist;
                crime(f, aux1, aux2);                
            }
        }
    }

    int id;
    for (id = 0; id < g->num_vertices; id++) 
        if (strcmp(predecessores[id].nome, destino) == 0)
            break;
    
    printf("\n");
    while(strcmp(predecessores[id].nome, origem) != 0 && strcmp(predecessores[id].antecessor, "vazio") != 0) {
        printf("%s <- %s ", predecessores[id].nome, predecessores[id].antecessor);
        
        for (int j = 0; j < g->num_vertices; j++) 
            if (strcmp(predecessores[j].nome, predecessores[id].antecessor) == 0) {
                id = j;
                break;
            }
    }
    printf("\n");
}

/*
Letra B
recebe um nome e uma profundidade
*/

void letraB(grafo g, char* nome, int prf){

}
