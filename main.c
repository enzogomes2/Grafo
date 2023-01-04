#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "fila-prio.h"


int main () {
    FILE* reader = fopen("dados.txt", "r");
    char* conteudo_linha = malloc(999);
    char* palavra = malloc(MAX_NOME);
    grafo g = cria_grafo();

    while (fscanf(reader, "%[^\n] ", conteudo_linha) != EOF) {
        palavra = strtok(conteudo_linha, " ");
        char nome1[MAX_NOME];
        char nome2[MAX_NOME];
        int peso = 0, i = 0;

        while (palavra != NULL) {
            switch(i) {
                case 0 : 
                strcpy(nome1, palavra);
                break;

                case 1 : 
                strcpy(nome2, palavra);
                break;
                
                case 2 : 
                peso = atoi(palavra);
                break;
            }
            palavra = strtok(NULL, " ");
            i++;
        }       
        if (eh_vertice(g, nome1) == 0) 
            insere_novo_vertice(g, nome1);
        
        if (eh_vertice(g, nome2) == 0) 
            insere_novo_vertice(g, nome2);
 
        insere_arco(g, nome1, nome2, peso);
    }

    int opt = 0; 
    printf("[1] Mostrar lista de adjacências\n");
    printf("[2] Mostrar as interações que se iniciam em U com até D passos de distância\n");
    printf("[3] Gerar lista de todos os usuários diretamente relacionados a U, com pelo menos K interações\n");
    printf("[4] Mostrar usuários fortemente conectados a U\n");
    printf("[5] Encontrar o caminho mínimo entre U1 e U2\n");
    printf("[6] Encerrar programa\n");
    do {
        printf("\nDigite a opção: ");
        scanf("%d", &opt);
        int k = -1;
        char temp1[100];
        char temp2[100];

        switch(opt) {
            case 1 : 
                mostra_lista(g); break;
            
            case 2 :
                printf("Digite o nome do usuário: ");
                scanf("%s", temp1);
                printf("Digite a distância: ");
                scanf("%d", &k);
                printf("soon..\n");
                break;

            case 3 :
                printf("Digite o nome do usuário: ");
                scanf("%s", temp1);
                printf("Digite a quantidade mínima de interações: ");
                scanf("%d", &k);
                lista rel = letraC(g, temp1, k);
                printf("Relacionados:\n");  
                for (int i = 1; get_elem_pos(rel, i, temp1) != 0; i++)
                    printf("- %s\n", temp1);
                break;

            case 4 :
                ;
                lista conectados = cria_lista();
                printf("Digite o usuário: ");   
                scanf("%s", temp1);
                letraD(temp1, g, &conectados); 
                printf("Fortemente conectados:\n");  
                for (int i = 1; get_elem_pos(conectados, i, temp1) != 0; i++)
                    printf("- %s\n", temp1);
                break;


            case 5 :
                printf("Digite o usuário de origem: ");
                scanf("%s", temp1);
                printf("Digite o usuário de origem: ");
                scanf("%s", temp2);
                letraE(g, temp1, temp2); 
                break;
        }
    } while (opt != 6);
    printf("Encerrando programa...\n");
    return 0;
}