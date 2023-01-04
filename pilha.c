#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void IniciaPilha(TipoPilha *pilha){
 pilha->topo = NULL;
 pilha->tamanho = 0;
}

int VaziaPilha(TipoPilha *pilha){
 return (pilha->topo == NULL);
}

int Topo (TipoPilha *pilha, char* c){
 TipoNo *aux;
 if (pilha==NULL) 
    return 0;
 strcpy(c, pilha->topo->valor);
 return 1;
}


void Empilha(char *c, TipoPilha *pilha){
 TipoNo *aux;
 if (pilha==NULL) 
    return;
 aux = (TipoNo *) malloc(sizeof(TipoNo));
 strcpy(aux->valor, c);
 aux->prox = pilha->topo;
 pilha->topo = aux;
 pilha->tamanho++;
}

int Desempilha(TipoPilha *pilha, char* c){
   TipoNo *no;
   if (pilha==NULL) 
      return 0;
   no = pilha->topo;
   strcpy(c, no->valor);
   pilha->topo = no->prox;
   pilha->tamanho--;
   free(no);
  return 1;
}