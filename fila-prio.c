#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fila-prio.h"

fila_prio cria_fila_prio () {
    fila_prio f = (fila_prio)malloc(sizeof(struct no1));
    if (f != NULL) 
        f->qtd = 0;
    
    return f;
}

int fila_prio_vazia (fila_prio f) {
    if (f->qtd == 0)
        return 1;
    else    
        return 0;
}

int fila_prio_cheia (fila_prio f) {
    if (f->qtd == MAX_FILA_PRIO)
        return 1;
    else    
        return 0;
}

int arruma_heap_insere (fila_prio f, int filho) {
    int pai;
    struct user temp;
    pai = (filho - 1) / 2;
    while ((filho > 0) && (f->user[pai].prio >= f->user[filho].prio)) {
        temp = f->user[filho];
        f->user[filho] = f->user[pai];
        f->user[pai] = temp;

        filho = pai;
        pai = (pai - 1) / 2;
    }
}

int arruma_heap_remove (fila_prio f, int pai) {
    struct user temp;
    int filho = (2 * pai) + 1;
    while (filho < f->qtd) {
        if (filho < f->qtd - 1) 
            if (f->user[filho].prio < f->user[filho + 1].prio)
                filho++;

        if (f->user[pai].prio <= f->user[filho].prio)
            break;

        temp = f->user[pai];
        f->user[pai] = f->user[filho];
        f->user[filho] = temp;

        pai = filho;
        filho = (2 * pai) + 1;
    } 
}

int insere_prio (fila_prio f, char* elem, int prio) {
    if (f == NULL || fila_prio_cheia(f)) 
        return 0;

    strcpy(f->user[f->qtd].nome, elem);  // insere no fim do array
    f->user[f->qtd].prio = prio;
    arruma_heap_insere(f, f->qtd);
    f->qtd++;
    return 1;
}

int remove_prio (fila_prio f, char* var, int* prio) {
    if (f == NULL || fila_prio_vazia(f)) 
        return 0;

    strcpy(var, f->user[0].nome);
    *prio = f->user[0].prio;
    f->qtd--;
    f->user[0] = f->user[f->qtd];
    arruma_heap_remove(f, 0);
    return 1;
}

void printa_fila (fila_prio f) {
    for (int i = 0; i < f->qtd; i++) 
        printf("nome: %s\nprio: %d\n", f->user[i].nome, f->user[i].prio);
}

int esta_na_fila_prio (fila_prio f, char* elem) {
    for (int i = 0; i < f->qtd; i++) 
        if (strcmp(f->user[i].nome, elem) == 0)
            return 1;
    return 0;
}

int crime (fila_prio f, char* nome, int prio) {
    if (f == NULL || fila_prio_vazia(f))
        return 0;
    
    for (int i = 0; i < f->qtd; i++) {
        if (strcmp(f->user[i].nome, nome) == 0) {
            f->user[i].prio = prio;
            break;
        }
    }
    arruma_heap_insere(f, f->qtd);
    return 1;
}


