#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 11

void imprimir_contato(void *pBuffer, int *index);
int *buscar_contato(void *pBuffer, int *n, char *nome);
void deletar_contato(void *pBuffer, int *n, char *nome);
void adicionar_contato(void **pBuffer, int *n);
void buscar_contato_e_imprimir(void *pBuffer, int *n);



void imprimir_contato(void *pBuffer, int *index) {
    char *pNome = (char *)pBuffer + (*index) * (MAX_NOME + sizeof(int) * 2);
    int *pIdade = (int*) (pNome + MAX_NOME);
    int *pTelefone = (int*) (pIdade + 1);

    printf("%s, %d anos, telefone %d\n", pNome, *pIdade, *pTelefone);
}

int *buscar_contato(void *pBuffer, int *n, char *nome) {

    int *i = (int *)malloc(sizeof(int));

    for (*i = 0; *i < *n; (*i)++) {
        char *pNome =(char *)pBuffer + (*i) * (MAX_NOME + sizeof(int) * 2);
        if (strcmp(pNome, nome) == 0) {
            return i;
        }
    }
    return NULL;
}

void deletar_contato(void *pBuffer, int *n, char *nome) {
    int *index = buscar_contato(pBuffer, n, nome);

    if (index == NULL) {
        return;
    }

    char *pContato =(char *) pBuffer + *index * (MAX_NOME + sizeof(int) * 2);
    char *pProximoContato =(char *) pBuffer + (*index + 1) * (MAX_NOME + sizeof(int) * 2);

    memmove(pContato, pProximoContato, (*n - *index - 1) * (MAX_NOME + sizeof(int) * 2));

    (*n)--;
    pBuffer = realloc(pBuffer, (*n) * (MAX_NOME + sizeof(int) * 2));
    printf("Contato deletado\n");
}

void adicionar_contato(void **pBuffer, int *n) {
    (*n)++;
    *pBuffer = realloc(*pBuffer, (*n) * (MAX_NOME + sizeof(int) * 2));

    char *nome = (char *) (*pBuffer + ((*n) - 1) * (MAX_NOME + sizeof(int) * 2));
    int *idade = (int *) (nome + MAX_NOME);
    int *telefone = (int *) (idade + 1);


    printf("Digite o nome (max 10 caracteres): ");
    scanf("%s", nome);

    printf("Digite a idade: ");
    scanf("%d", idade);

    printf("Digite o telefone: ");
    scanf("%d", telefone);

    // Ordenar os contatos por ordem alfabética usando uma heap
    
    int *i = (int *)malloc(sizeof(int));
    *i = *n - 1;
    while (*i > 0) {
        int *pai = (int *)malloc(sizeof(int));
        *pai = (*i - 1) / 2;
        char *pContato = *pBuffer + (*i) * (MAX_NOME + sizeof(int) * 2);
        char *pPai = *pBuffer + (*pai) * (MAX_NOME + sizeof(int) * 2);

        if (strncmp(pContato, pPai, MAX_NOME) > 0) {
            break;
        }

        // Trocar o contato atual com o pai
        char *tmp = (char *)malloc((MAX_NOME + sizeof(int) * 2) * sizeof(char));
        memcpy(tmp, pContato, MAX_NOME + sizeof(int) * 2);
        memcpy(pContato, pPai, MAX_NOME + sizeof(int) * 2);
        memcpy(pPai, tmp, MAX_NOME + sizeof(int) * 2);

        *i = *pai;
    }
}

void buscar_contato_e_imprimir(void *pBuffer, int *n) {
    char *nome = (char *)malloc(MAX_NOME * sizeof(char));

    printf("Digite o nome do contato: ");
    scanf("%s", nome);

    int *index = buscar_contato(pBuffer, n, nome);
    if (index == NULL) {
        printf("Contato nao encontrado\n");
    } else {
        printf("Contato encontrado: ");
        imprimir_contato(pBuffer, index);
    }
}

int main() {
    void *pBuffer = malloc(0);
    int *n = (int *)malloc(sizeof(int));
    *n = 0;
    int *opcao = (int *)malloc(sizeof(int));
    int *i = (int *)malloc(sizeof(int));

    while (1) {
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato\n");
        printf("4 - Deletar contato\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", opcao);

        switch (*opcao) {
            case 1:
            adicionar_contato(&pBuffer, n);
            break;

            case 2:

                printf("Contatos:\n");
                for (*i = 0; *i < *n; (*i)++) {
                    printf("%d - ", *i + 1);
                    imprimir_contato(pBuffer, i);
                }
                break;

            case 3:
            buscar_contato_e_imprimir(pBuffer, n);
            break;

            case 4:
            char *nome = (char *)malloc(MAX_NOME * sizeof(char));
            printf("Digite o nome a ser deletado: ");
            scanf("%s", nome);
            deletar_contato(pBuffer, n, nome);
            break;

            case 5:
                free(pBuffer);
                return 0;
                
           default:
           printf("Opcao invalida\n");

        }
    }
}
