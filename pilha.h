typedef struct No{
   char valor[100];
   struct No *prox;
} TipoNo;

typedef struct Pilha{
 TipoNo *topo;
 int tamanho;
} TipoPilha;

void IniciaPilha(TipoPilha *pilha);
int VaziaPilha(TipoPilha *pilha);
void Empilha(char* x, TipoPilha *pilha);
int Desempilha(TipoPilha *pilha, char *);
int Topo (TipoPilha *pilha, char*);