#define MAX_FILA_PRIO 999

typedef struct user {
  char nome[100];
  int prio;
} User;

struct no1 {
    struct user user[MAX_FILA_PRIO];
    int qtd;
};

typedef struct no1 *fila_prio;

fila_prio cria_fila_prio();
int fila_prio_vazia(fila_prio f);
int fila_prio_cheia(fila_prio f);
int arruma_heap_insere(fila_prio f, int filho);
int arruma_heap_remove(fila_prio f, int pai);
int insere_prio(fila_prio f, char *elem, int prio);
int remove_prio(fila_prio f, char *var, int *prio);
int crime(fila_prio f, char *nome, int prio);
void printa_fila(fila_prio f);
