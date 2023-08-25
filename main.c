#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#define MAX_FILE_SIZE 128

FILE* arquivo = NULL;

//Funções Leitura de Arquivos (Declarar)
bool abrirArquivo(const char* caminho);

//Funções Escrita de Arquivos (Declarar)
void registrarPessoa(); // FUNCAO TESTE

//Enumerações
typedef enum { PADEIRO, MEDICO, DENTISTA, SAPATEIRO } Profissao; // ENUM TESTE

//Registros (Estruturas)
typedef struct  // REGISTRO TESTE
{
    /* data */
    int idade;
    char nome[32];
    Profissao prof;
} Pessoa;

void lerRegistroPessoa(Pessoa* p, int id); 


//Funções (Features do programa)


int main()
{
    setlocale(LC_ALL, "");
    printf("Ol� Mundo\n");
    
    Pessoa p1;

    if (!abrirArquivo("registroOUT.txt"))
    {
        return -1;
    }

	lerRegistroPessoa(&p1, 0);

    return 0;
}

//Funções Leitura de Arquivos (Implementar)
bool abrirArquivo(const char* caminho)
{
    if((arquivo = fopen(caminho, "r")) == NULL)
    {
        printf("N�o foi poss�vel abrir o arquivo \"%s\" \n", caminho);
        return false;
    }

    return true;
    
}

void lerRegistroPessoa(Pessoa* p, int id_registro)
{
	char BUFFER [MAX_BUFFER_SIZE];
	char *sub_BUFFER, num_BUFFER[16];
    char c;
    bool lerRegistro;
    int i = 0, ii = 0;
    int id_atual = 0;
    while ((c = fgetc(arquivo)) != EOF)
    {
    	BUFFER[i++] = c;   
    }
    BUFFER[i] = '\0';
    
    sub_BUFFER = BUFFER;
    
    i = 0;
    while ((c = sub_BUFFER[i++] )!= '\0')
    {
		if (lerRegistro)
		{
			if (sub_BUFFER[i] == '(')
			{
				while (sub_BUFFER[++i] != ')')
			}
		}
    	
    	if (isdigit(c))
    	{
    		num_BUFFER[ii++] = c;
			printf("c:%c\n", c);	
		}
		else
		{
			id_atual = atoi(num_BUFFER);
			printf("id_atual:%d\n", id_atual);
			if(id_atual == id_registro)	
			{
				lerRegistro = true;
			}
		}	
	}
	
	printf("num_BUFFER:%s\n", num_BUFFER);
    
    printf("%s\n", BUFFER);
}














