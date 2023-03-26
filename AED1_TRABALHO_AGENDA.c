#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 11

void Imprimir_Contato( void *pBuffer );
char *Buscar_Contato( void *pBuffer, int *n, char *nome, char *pInicio );
void Deletar_Contato( void *pBuffer, int *n, char *nome, char *pInicio );
void Adicionar_Contato( void **pBuffer, int *n, char *pInicio, char *pFim );
void Buscar_Contato_e_Imprimir( void *pBuffer, int *n, char *pInicio );
void Ordenar_Contatos( void **pBuffer, int *n, char *pInicio, char *pFim );

int main() {

    void *pBuffer = malloc(0);
    int *n = ( int * )malloc( sizeof ( int ) );
    *n = 0;
    int *opcao = ( int * )malloc( sizeof ( int ) );
    char *pInicio = NULL;
    char *pFim = NULL;

    while (1) {
        printf("1 - Adicionar contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato\n");
        printf("4 - Deletar contato\n");
        printf("0 - Sair\n");
        printf("Sua escolha: ");

        scanf("%d", opcao);

        switch ( *opcao ) {
            case 1:
                Adicionar_Contato( &pBuffer, n, pInicio, pFim );
                pInicio = ( char * )pBuffer;
                pFim = ( char * )pBuffer + ( *n - 1 ) * ( MAX_NOME + sizeof ( int ) * 2 );
                break;
            case 2:
                printf("Lista de contatos:\n");
                char *pContato = pInicio;
                while ( pContato <= pFim ) {
                    Imprimir_Contato( pContato );
                    pContato += MAX_NOME + sizeof( int ) * 2;
                }
                break;
            case 3:
                Buscar_Contato_e_Imprimir( pBuffer, n, pInicio );
                break;
            case 4:
                char nome[MAX_NOME];
                printf("Digite o nome do contato que deseja deletar: ");
                scanf("%s", nome);
                Deletar_Contato( pInicio, n, nome, pFim );
                pInicio = ( char * )pBuffer;
                pFim = ( char * )pBuffer + ( *n - 1 ) * ( MAX_NOME + sizeof(int) * 2 );
                break;
            case 0:
                free( pBuffer );
                free( n );
                free( opcao );
                return 0;
            default:
                printf("Opcao invalida\n");
        }
    }
}

void Adicionar_Contato( void **pBuffer, int *n, char *pInicio, char *pFim ) {
    ( *n )++;
    *pBuffer = realloc( *pBuffer, ( *n ) * ( MAX_NOME + sizeof ( int ) * 2 ) );

    char *nome = ( char * ) ( *pBuffer + ( ( *n ) - 1 ) * ( MAX_NOME + sizeof ( int ) * 2 ) );
    int *idade = ( int * ) ( nome + MAX_NOME );
    int *telefone = ( int * ) ( idade + 1 );

    printf("Digite o nome (max 10 caracteres): ");
    scanf("%s", nome);

    printf("Digite a idade: ");
    scanf("%d", idade);

    printf("Digite o telefone: ");
    scanf("%d", telefone);


    Ordenar_Contatos( pBuffer, n, pInicio, pFim );
}

void Ordenar_Contatos( void **pBuffer, int *n, char *pInicio, char *pFim ) {

    char *ponteiro1 = ( char * )*pBuffer;
    char *ponteiro2 = NULL;
    char *ponteiroAux = NULL;
    for ( ; ponteiro1 < ( char* )*pBuffer + ( *n - 1 ) * ( MAX_NOME + sizeof ( int ) * 2 ); ponteiro1 += MAX_NOME + sizeof( int ) * 2 ) {
        for ( ponteiro2 = ponteiro1 + MAX_NOME + sizeof( int ) * 2; ponteiro2 < ( char * )*pBuffer + ( *n ) * ( MAX_NOME + sizeof ( int ) * 2 ); ponteiro2 += MAX_NOME + sizeof( int ) * 2 ) {
            if ( strcmp ( ponteiro1, ponteiro2 ) > 0 ) {

                ponteiroAux = ( char* )malloc( MAX_NOME + sizeof ( int ) * 2 );
                memcpy( ponteiroAux, ponteiro1, MAX_NOME + sizeof ( int ) * 2 );
                memcpy( ponteiro1, ponteiro2, MAX_NOME + sizeof ( int ) * 2 );
                memcpy( ponteiro2, ponteiroAux, MAX_NOME + sizeof ( int ) * 2 );
                free( ponteiroAux );
            }

        }
    }
}


void Imprimir_Contato( void *pBuffer ) {
    char *pNome =( char * )pBuffer;
    int *pIdade = ( int* ) ( pNome + MAX_NOME );
    int *pTelefone = ( int* ) ( pIdade + 1 );

    printf("%s, %d anos, telefone %d\n", pNome, *pIdade, *pTelefone);
}

char *Buscar_Contato( void *pBuffer, int *n, char *nome, char *pInicio ) {
    char *pContato = pInicio;
    while ( pContato <= ( char * )pBuffer + ( *n - 1 ) * ( MAX_NOME + sizeof ( int ) * 2 ) ) {
        if ( strcmp( nome, pContato ) == 0 ) {
            return pContato;
        }
        pContato += MAX_NOME + sizeof( int ) * 2;
    }
    printf("Contato nao encontrado.\n");
    return NULL;
}

void Buscar_Contato_e_Imprimir( void *pBuffer, int *n, char *pInicio ) {
    void *start = pInicio;
    void *check = pInicio;
    char *nome = pBuffer;

    printf("Digite o nome do contato: ");
    scanf("%s", nome);

    while ( start != NULL ){
        check += MAX_NOME * sizeof( char );
        if (strcmp( nome,start ) == 0){
            printf("\nNome: %s", ( char * )start);
            start += MAX_NOME * sizeof( char );
            printf("\nIdade: %d", *( int *  )start);
            start += sizeof( int );
            printf("\nTelefone: %d", *( int * )start);
            start += sizeof( int );
            printf("\n");
            return;
        }
        start += ( MAX_NOME * 10 ) + ( sizeof( int ) * 2 );
        check = start;
    }
    printf("Nome nao encontrado");
    return;
}

void Deletar_Contato( void *pBuffer, int *n, char *nome, char *pInicio ) {
    char *index = Buscar_Contato( pBuffer, n, nome, pInicio );

    if ( index == NULL ) {
        return;
    }

    char *pProximoContato = index + ( MAX_NOME * sizeof( char ) + sizeof( int ) * 2 );
    char *pUltimoContato = ( char * )pBuffer + ( *n - 1 ) * ( MAX_NOME + sizeof( int ) * 2 );

    memmove( index, pProximoContato, ( pUltimoContato - pProximoContato ) + MAX_NOME + sizeof( int ) * 2 );

    ( *n )--;
    pBuffer = realloc( pBuffer, ( *n ) * ( MAX_NOME + sizeof( int ) * 2 ) );
    printf("Contato deletado\n");
}
