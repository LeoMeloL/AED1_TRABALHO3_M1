#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50


void IncluirNome(void **pBuffer, int *count);
void DeletarNome(void **pBuffer, int *count);
void BuscarNome(void *pBuffer, int count);
void ListarDados(void *pBuffer, int count);

int main() {
    
    void* pBuffer = NULL;
    int count = 0;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Incluir registro\n");
        printf("2 - Deletar registro\n");
        printf("3 - Buscar registro\n");
        printf("4 - Imprimir dados\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                IncluirNome(&pBuffer, &count);
                break;
            case 2:
                DeletarNome(&pBuffer, &count);
                break;
            case 3:
                BuscarNome(pBuffer, count);
                break;
            case 4:
                ListarDados(pBuffer, count);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    if (pBuffer != NULL) {
        free(pBuffer);
    }

    return 0;
}


void IncluirNome(void **pBuffer, int *count) {
    char **info = (char **)*pBuffer;

    // aloca mais uma linha para armazenar os dados da nova pessoa
    *pBuffer = realloc(*pBuffer, (*count + 1) * sizeof(char *));
    info = (char **)*pBuffer;

    // aloca espaço para armazenar o nome, idade e telefone da nova pessoa
    info[*count] = malloc((MAX + 1) * sizeof(char));

    printf("\nDigite o nome: ");
    scanf("%s", info[*count]);
    printf("Digite a idade: ");
    scanf("%s", info[*count] + strlen(info[*count]) + 1);
    printf("Digite o telefone: ");
    scanf("%s", info[*count] + strlen(info[*count]) + strlen(info[*count] + strlen(info[*count]) + 1) + 2);

    (*count)++;
}

void DeletarNome(void **pBuffer, int *count) {
    char *info = (char *)*pBuffer;
    char nome[MAX + 1];
    int i, j, pos, linha;

    printf("\nDigite o nome a ser removido: ");
    scanf("%s", nome);

    // percorre a string procurando pelo nome
    pos = 0;
    linha = -1;
    for (i = 0; i < *count; i++) {
        // encontra o início da linha
        while (info[pos] != '\0' && info[pos] != '|') pos++;
        if (info[pos] == '\0') break;

        // compara o nome com a linha atual
        if (strncmp(info + pos + 1, nome, strlen(nome)) == 0) {
            linha = i;
            break;
        }

        // avança para o início da próxima linha
        while (info[pos] != '\0' && info[pos] == '|') pos++;
    }

    if (linha != -1) {
        // encontra o início da linha a ser deletada
        for (i = 0, j = 0; i < linha; i++) {
            while (info[j] != '\0' && info[j] == '|') j++;
            while (info[j] != '\0' && info[j] != '|') j++;
        }

        // desaloca a memória da linha a ser deletada
        free(info + j + 1);
        info = realloc(info, strlen(info) - strlen(info + j + 1) - 1);

        // atualiza o contador de linhas
        (*count)--;
    } else {
        printf("Nome nao encontrado\n");
    }

    *pBuffer = info;
}

void buscarPessoa(void* pBuffer, int count) {
    char nome[10];

    printf("Digite o nome da pessoa que deseja buscar: ");
    scanf("%s", nome);

    int i;
    for (i = 0; i < count; i++) {
        char* nomeAtual = (char*) pBuffer + i * (sizeof(int) + 10 + 15); // desloca o ponteiro para o nome da pessoa atual
        if (strcmp(nomeAtual, nome) == 0) {
            printf("\nDados da pessoa %s:\n", nome);
            int* idadeAtual = (int*) (nomeAtual + 10); // desloca o ponteiro para a idade da pessoa atual
            printf("Idade: %d\n", *idadeAtual);
            char* telefoneAtual = (char*) (idadeAtual + 1); // desloca o ponteiro para o telefone da pessoa atual
            printf("Telefone: %s\n", telefoneAtual);
            return;
        }
    }

    printf("Pessoa nao encontrada na agenda.\n");
}

void imprimirDados(void* pBuffer, int count) {
    if (count == 0) {
        printf("Agenda vazia.\n");
        return;
    }

    printf("\nDados dos %d registros na agenda:\n", count);
    int i;
    for (i = 0; i < count; i++) {
        char* nomeAtual = (char*) pBuffer + i * (sizeof(int) + 10 + 15); // desloca o ponteiro para o nome da pessoa atual
        printf("\nNome: %s\n", nomeAtual);
        int* idadeAtual = (int*) (nomeAtual + 10); // desloca o ponteiro para a idade da pessoa atual
        printf("Idade: %d\n", *idadeAtual);
        char* telefoneAtual = (char*) (idadeAtual + 1); // desloca o ponteiro para o telefone da pessoa atual
        printf("Telefone: %s\n", telefoneAtual);
    }
}