#define MAX_LISTA 999
#define MAX_NOME 100

struct no {
    char info[MAX_LISTA];
    struct no* prox;
};
typedef struct no* lista;

lista cria_lista ();
int lista_vazia (lista lst);
int insere_elem (lista* lst, char* elem);
int remove_elem (lista* lst, char* elem);
int get_elem_pos (lista lst, int pos, char* elem);
void apaga_lista (lista* lst);
void esvazia_lista (lista* lst);
//int esta_na_lista (lista lst, char* elem);
int JaInseridoLista (char* n, lista l);