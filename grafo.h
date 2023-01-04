#include "lista.h"

#define MAX_NOME 100
typedef struct grafo* grafo;

typedef struct dist {
  char nome[MAX_NOME];
  int dist;
} Dist;

typedef struct pred {
  char nome[MAX_NOME];
  char antecessor[MAX_NOME];
} Pred;

struct vertice *insere_vertice(struct vertice *ini, char *valor_vert);
grafo cria_grafo();
struct arco *insere_adjacencia(struct arco *ini, char *vert_dest, int peso);
int insere_arco(grafo gf, char *vert1, char *vert2, int peso);
void insere_novo_vertice(grafo gf, char *val);
int eh_vertice(grafo gf, char *vert);
void mostra_lista(grafo gf);
void busca_largura(grafo g, char *vert_origem);
lista letraC(grafo g, char *vert_origem, int K);
void letraD(char* nome, grafo g, lista* l);
void letraE(grafo g, char* origem, char* destino);