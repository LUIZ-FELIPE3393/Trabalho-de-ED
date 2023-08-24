<<<<<<< HEAD
#include <stdio.h>
#include <stdbool.h>
#define MAX_BUFFER_SIZE 128

FILE* arquivo = NULL;

//Funções Leitura de Arquivos (Declarar)
bool abrirArquivo(const char* caminho);
int consulta(int id);

//Registros (Estruturas)

//Funções (Features do programa)


int main()
{
    printf("Olá Mundo\n");

    if (!abrirArquivo("registros2.txt"))
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
    if((arquivo = fopen(caminho, "w")) == NULL)
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
    return c;
}
=======
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_BUFFER_SIZE 128

FILE *arquivo;

// Funções Leitura de Arquivos (Declarar)
bool abrirArquivo(const char *caminho);
int consulta(int id);

// Registros (Estruturas)

// Funções (Features do programa)

int main()
{
    printf("Olá Mundo\n");
    printf("Olá Mundo\n");

    if (!abrirArquivo("registros.txt"))
    {
        return 0;
    }

    char BUFFER[MAX_BUFFER_SIZE];

    consulta(0);

    return 0;
}

// Funções Leitura de Arquivos (Implementar)
bool abrirArquivo(const char *caminho)
{
    if ((arquivo = fopen(caminho, "r+")) == NULL)
    {
        fprintf(stderr, "Não foi possível abrir o arquivo\n");
        return false;
    }
    fprintf(arquivo, "Foi criado!\n");

    return true;
}

int consulta(int id)
{
    char c;
    while (c = getc(arquivo) != EOF)
    {
        printf("%c", c);
    }
    return c;
}
>>>>>>> 40d5f05260f64eb75bb67e3fb7e547fc807205db
