#include <stdlib.h>
#include <string.h>
#include "lista.h"

lista cria_lista () {
    return NULL;
}

int lista_vazia (lista lst) {
    if (lst == NULL)
        return 1;
    else 
        return 0;
}

int insere_elem (lista* lst, char* elem) {
    lista n = (lista)malloc(sizeof(struct no));
    if (n == NULL)
        return 0;
    strcpy(n->info, elem);    
    n->prox = *lst;
    *lst = n;
    
    return 1;
}

int remove_elem (lista* lst, char* elem) {
    if (lista_vazia(*lst) == 1)
        return 0;
    
    lista aux = *lst;

    // trata do elemento ser o primeiro da lista
    if (strcmp(elem,(*lst)->info) == 0) {
        *lst = aux->prox;
        free(aux);
        return 1;
    }

    // percorre até achar o elemento ou final de lista 
    while (aux->prox != NULL && strcmp(aux->prox->info,elem) != 0)
        aux = aux->prox;

    // trata final de lista
    if (aux->prox == NULL) 
        return 0;
    
    lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return 1;
}

int get_elem_pos (lista lst, int pos, char* var) {
    if (lista_vazia(lst) == 1)
        return 0;
    
    int i;
    lista aux = lst; 
    for (i = 1; i != pos; i++) {
        if (aux->prox == NULL) {
            return 0;
        }
        aux = aux->prox;
    }

    strcpy(var, aux->info);
    return 1;
}

void apaga_lista (lista* lst) {
    lista aux;
    while (*lst != NULL) {
        aux = *lst;
        *lst = (*lst)->prox;
        free(aux);
    }
}

void esvazia_lista (lista* lst) {
    apaga_lista(lst);
}

int JaInseridoLista (char* n, lista l){
    int i;
    char v[MAX_NOME];
    for(i = 1; get_elem_pos(l, i, v) != 0; i++)
        if(strcmp(v, n) == 0)
            return 1;

    return 0;
}