#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#define MAX_BUFFER_SIZE 128

FILE* arquivo = NULL;

//Funções Leitura de Arquivos (Declarar)
bool abrirArquivo(const char* caminho);
int consulta(int id);

//Funções Escrita de Arquivos (Declarar)
void registrarPessoa(); // FUNCAO TESTE

//Enumerações
typedef enum { PADEIRO, MEDICO, DENTISTA, SAPATEIRO } Profissao; // ENUM TESTE

//Registros (Estruturas)
struct Pessoa  // REGISTRO TESTE
{
    /* data */
    int idade;
    char nome[32];
    Profissao prof;
};


//Funções (Features do programa)


int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("Olá Mundo\n");

    if (!abrirArquivo("registroOUT.txt"))
    {
        return -1;
    }

    char BUFFER [MAX_BUFFER_SIZE];

    consulta(0);

    return 0;
}

//Funções Leitura de Arquivos (Implementar)
bool abrirArquivo(const char* caminho)
{
    if((arquivo = fopen(caminho, "r")) == NULL)
    {
        printf("Não foi possível abrir o arquivo \"%s\" \n", caminho);
        return false;
    }

    return true;
}

int consulta(int id)
{
    char c;
    while (c = getc(arquivo) != EOF)
    {
        printf("%c", c);
    }
}