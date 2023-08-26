#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#define MAX_FILE_SIZE 4096

#define OUT_FORMAT_PESSOA "%d-P(%s, %d, %s)\n\0" // FORMATO PADRÃO PARA REGISTRO DE PESSOA /TESTE

FILE* arquivo = NULL;
char BUFFER [MAX_FILE_SIZE];
int global_arquivo_index = 0;

//Enumerações
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

//Funções (Features do programa)
//Funções Leitura de Arquivos (Declarar)
bool abrirArquivo(const char* caminho);
void lerRegistroPessoa(Pessoa *p, int id);

//Funções Escrita de Arquivos (Declarar)
void registrarPessoa(Pessoa *p); // FUNCAO TESTE

int main()
{
    setlocale(LC_ALL, "");
    printf("Ol� Mundo\n");

	Pessoa p0, p1;

    if (!abrirArquivo("registroOUT.txt"))
    {
        return -1;
    }

	lerRegistroPessoa(&p0, 0);
	lerRegistroPessoa(&p1, 1);
	
	printf("X_NOME: %s\n", p0.nome);
	printf("X_IDADE: %d\n", p0.idade);
	printf("X_PROF: %d\n", p0.prof);
	
	printf("X_NOME: %s\n", p1.nome);
	printf("X_IDADE: %d\n", p1.idade);
	printf("X_PROF: %d\n", p1.prof);

    return 0;
}

//Funções Features (Implementar)
//Funções Leitura de Arquivos (Implementar)
bool abrirArquivo(const char* caminho)
{
    if((arquivo = fopen(caminho, "r+")) == NULL)
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
	    
	    //printf("sub_BUFFER:%s\n", line_BUFFER);
	    //printf("c:%c\n", c);
	    
	    if(!linha_completa)
	    	continue;
		printf("linhaCompleta\n");
	    i = 0;
	    printf("SUB:%s\n", sub_BUFFER);
	    memset(sub_BUFFER, 0, sizeof(sub_BUFFER));
	    
	    int j = 0;
	    while ((c = line_BUFFER[j++] )!= '-')
	    {
	    	if (isdigit(c)) // Converte id do registro para inteiro
    		{
				printf("SUB:%s", sub_BUFFER);
    			sub_BUFFER[ii++] = c;
				//printf("c:%c\n", c);	
			}
		}
		// Verifica se � a id correta
		id_atual = atoi(sub_BUFFER);
		printf("id_atual:%d\n", id_atual);
		if(id_atual == id_registro)	
		{
			printf("id_atual:%d == id:%d\n", id_atual, id_registro);
			lerRegistro = true;
		}

	    //Leitura de Registro
	    if (lerRegistro)
	    while ((c = line_BUFFER[i++] )!= '\0') 
	    {
			if (lerRegistro)
			{
				//printf("c:%c\n", c);
				printf("LerRegistro\n");
				if (line_BUFFER[i] == '(')
				{
					while (line_BUFFER[++i] != ')')
					{
						//Dentro do Par�nteses
						printf("Dentro\n");
						ii = 0;
						do
						{
							//NOME
							p->nome[ii++] = line_BUFFER[i];
							i++;
						} while (line_BUFFER[i] != ',');
						
						p->nome[ii] = '\0';
						//printf("NOME: %s\n", p->nome);
						memset(sub_BUFFER, 0, sizeof(sub_BUFFER));
						
						ii = 0;
						while ( (c = line_BUFFER[++i] ) != ',')
						{
							//IDADE
							if (isdigit(c))
						   	{
						   		sub_BUFFER[ii++] = c;
								//printf("c:%c\n", c);	
							}
						}
						
						//printf("idade BUFFER:%s\n", sub_BUFFER);
						p->idade = atoi(sub_BUFFER);
						
						ii = 0;
						while ((c = line_BUFFER[++i]) != ')') // Termina Leitura
						{
							//PROFISS�O
							if(!isspace(c))
							{
								sub_BUFFER[ii++] = c;
							}
						}
						
						p->prof = retornaProfPorNome(sub_BUFFER);
						lerRegistro = false;
						linha_completa = false;
						return;
					}
				}
			}
		}
		memset(line_BUFFER, 0, sizeof(line_BUFFER));
	}
	
	printf("num_BUFFER:%s\n", sub_BUFFER);
    memset(sub_BUFFER, 0, sizeof(sub_BUFFER));
    //printf("%s\n", BUFFER);
}

//Funções Escrita de Arquivos (Implementar)
void registrarPessoa(Pessoa *p) // FUNCAO TESTE
{
    char* sigla_prof[5];

    switch (p->prof)
    {
    case PADEIRO:
        *sigla_prof = "PADE";
        break;
    case DENTISTA:
        *sigla_prof = "DENT";
        break;
	case SAPATEIRO:
        *sigla_prof = "SAPA";
        break;
	case MEDICO:
        *sigla_prof = "MEDI";
        break;
    default:
        *sigla_prof = "NULL";
        break;
    }
    fseek(arquivo, 0, SEEK_END);
    fprintf(arquivo, OUT_FORMAT_PESSOA, global_arquivo_index, p->nome, p->idade, *sigla_prof);
    fseek(arquivo, 0, SEEK_SET);
    global_arquivo_index++;
}














