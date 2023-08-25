#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#define MAX_FILE_SIZE 4096

FILE* arquivo = NULL;
char BUFFER [MAX_FILE_SIZE];

//FunÃ§Ãµes Leitura de Arquivos (Declarar)
bool abrirArquivo(const char* caminho);

//FunÃ§Ãµes Escrita de Arquivos (Declarar)
void registrarPessoa(); // FUNCAO TESTE

//EnumeraÃ§Ãµes
typedef enum { PR_NULL, PADEIRO, MEDICO, DENTISTA, SAPATEIRO } Profissao; // ENUM TESTE
Profissao retornaProfPorNome(const char* nome_prof);

//Registros (Estruturas)
typedef struct  // REGISTRO TESTE
{
    /* data */
    int idade;
    char nome[32];
    Profissao prof;
} Pessoa;

void lerRegistroPessoa(Pessoa* p, int id); 


//FunÃ§Ãµes (Features do programa)


int main()
{
    setlocale(LC_ALL, "");
    printf("Olá Mundo\n");
    
    Pessoa p1;

    if (!abrirArquivo("registroOUT.txt"))
    {
        return -1;
    }

	lerRegistroPessoa(&p1, 0);
	
	printf("X_NOME: %s\n", p1.nome);
	printf("X_IDADE: %d\n", p1.idade);
	printf("X_PROF: %d\n", p1.prof);

    return 0;
}

//FunÃ§Ãµes Leitura de Arquivos (Implementar)
bool abrirArquivo(const char* caminho)
{
    if((arquivo = fopen(caminho, "r")) == NULL)
    {
        printf("Não foi possível abrir o arquivo \"%s\" \n", caminho);
        return false;
    }

    return true;
    
}

Profissao retornaProfPorNome(const char* nome_prof)
{
	if (strcmp(nome_prof, "MEDI") == 0)
	{
		return MEDICO;
	}
	else if (strcmp(nome_prof, "PADE") == 0)
	{
		return PADEIRO;
	}
	else if (strcmp(nome_prof, "SAPA") == 0)
	{
		return SAPATEIRO;
	}
	else if (strcmp(nome_prof, "DENT") == 0)
	{
		return DENTISTA;
	}
	else 
	{
		return PR_NULL;
	}
}

void lerRegistroPessoa(Pessoa* p, int id_registro)
{
	char line_BUFFER[128], sub_BUFFER[16];
    char c;
    bool lerRegistro, linha_completa;
    int i = 0, ii = 0, fase = 0;
    int id_atual = 0;
    
    //Leitura de Arquivo
    while ((c = fgetc(arquivo)) != EOF)
    {
	    if (c != '\n')
	    {
	    	line_BUFFER[i++] = c;  	
	    } 
		else 
		{
			linha_completa = true; 
			line_BUFFER[i] = '\0';
		}
	    
	    printf("sub_BUFFER:%s\n", line_BUFFER);
	    
	    if(!linha_completa)
	    	continue;
	    i = 0;
	    //Leitura de Registro
	    while ((c = line_BUFFER[i++] )!= '\0') 
	    {
			if (lerRegistro)
			{
				printf("LerRegistro\n");
				if (line_BUFFER[i] == '(')
				{
					while (line_BUFFER[++i] != ')')
					{
						//Dentro do Parênteses
						printf("Dentro\n");
						ii = 0;
						do
						{
							//NOME
							p->nome[ii++] = line_BUFFER[i];
							i++;
						} while (line_BUFFER[i] != ',');
						
						p->nome[ii] = '\0';
						printf("NOME: %s\n", p->nome);
						memset(sub_BUFFER, 0, sizeof(sub_BUFFER));
						
						ii = 0;
						while ( (c = line_BUFFER[++i] ) != ',')
						{
							//IDADE
							if (isdigit(c))
						   	{
						   		sub_BUFFER[ii++] = c;
								printf("c:%c\n", c);	
							}
						}
						
						printf("idade BUFFER:%s\n", sub_BUFFER);
						p->idade = atoi(sub_BUFFER);
						
						ii = 0;
						while ((c = line_BUFFER[++i]) != ')') // Termina Leitura
						{
							printf("PROF: ");
							//PROFISSÃO
							if(!isspace(c))
							{
								sub_BUFFER[ii++] = c;
							}
							
							printf("sub_buffer i:%c\n", line_BUFFER[i]);
						}
						
						p->prof = retornaProfPorNome(sub_BUFFER);
						lerRegistro = false;
						return;
					}
				}
			}
	    	
	    	if (isdigit(c)) // Converte id do registro para inteiro
	    	{
	    		sub_BUFFER[ii++] = c;
				printf("c:%c\n", c);	
			}
			else
			{
				// Verifica se é a id correta
				id_atual = atoi(sub_BUFFER);
				printf("id_atual:%d\n", id_atual);
				if(id_atual == id_registro)	
				{
					printf("id_atual:%d == id:%d\n", id_atual, id_registro);
					lerRegistro = true;
				}
			}	
		}
		memset(line_BUFFER, 0, sizeof(line_BUFFER));
	}
	
	printf("num_BUFFER:%s\n", sub_BUFFER);
    
    //printf("%s\n", BUFFER);
}














