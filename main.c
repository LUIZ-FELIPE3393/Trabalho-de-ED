#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define OUT_FORMAT_PROFISSAO "%d-(%d, %s, %s)\n\0" // FORMATO PADRAO PARA REGISTRO DE PROFISSAO
#define REG_TAM_MAX 512 // TAMANHO MÁXIMO PADRÃO DOS REGISTROS

int variComProfissao=1; //variavel de comando da profiss�o
int variComProfissional=1; //variavel de comando de medico
int global_arquivo_index = 0;

FILE* arquivo_profissao = NULL;

typedef struct{
    int codProf;
    char nomeProf[50], siglaProf[10];
//Registro das profiss�es
}Profissao;

typedef struct{
    char cpf[11], nome[50], email[50], tipo[50];
    int codProf, numRegP, fone, matricula, dia, mes, ano;
//Registro dos Profissionais de sa�de
}Profissional;

typedef struct{
    char nome[50], email[50];
    int idade, fone, celular, dia, mes, ano;
//Registro dos clientes
}Cliente;

typedef struct{
    int numero, matricula, dia, mes, ano;
//Registro dos atendimentos
}Atendimento;

//Funções (Features do programa) (Declarar)
//Funções Leitura de Arquivos
int abrirArquivo(FILE** arquivo, const char* caminho);
int lerRegistroProfissao(Profissao *p, long* pos);

//Funções Escrita de Arquivos
void registrarProfissao(Profissao *p); // FUNCAO

//Funções Menu
void menuProfissionais ();
void menuClientes ();
void menuAtendimentos ();
void menuProfissao (Profissao* profissao);

//Funções Profissão
void inserirProf(Profissao* profissao);
void pesquisarProf(Profissao* profissao);
void removerProf(Profissao* profissao);
void editarProf(Profissao* profissao);

//Funções Profissional
void pesquisarProfissional(Profissional* profissional);
void inserirProfissional(Profissional* profissional);
void editarProfissional(Profissional* profissional);
void removerProfissional(Profissional* profissional);

int main(){
    Profissao profissoes [REG_TAM_MAX];
    Profissional profissionais [REG_TAM_MAX];
    setlocale(LC_ALL,"portuguese");

    abrirArquivo(&arquivo_profissao, "regProfissao.txt");
    alocarRegistrosProfissao(profissoes);

    int op, a=0;

    do{
        printf("\n--------------------------------------------------------BEM VINDO-------------------------------------------------------\n");
        printf("\n Pesquisar por:\n [1]M�dico\n [2]Cliente\n [3]Atendimento\n [4]Profiss�o\n\n [5]Sair \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            menuProfissionais (profissionais);
            system("cls");
        break;

        case 2:
            menuClientes ();
            system("cls");
        break;

        case 3:
            menuAtendimentos ();
            system("cls");
        break;

        case 4:
            menuProfissao (profissoes);
            system("cls");
        break;

        case 5:
            a=1;
        break;

        default:
            system("cls");
            continue;
        }
    }while(a<1);


    return 0;
}

void menuProfissionais (Profissional* profissional){
    int op, a;
    do{
        system("cls");
        printf("\n----------------------------------------------------MENU DE M�DICOS-----------------------------------------------------\n");
        printf("\n [1]Pesquisar por m�dico\n [2]Inserir m�dico\n [3]Editar informa��es de um m�dico\n [4]Remover m�dico\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Fun��o para pesquisar por m�dico
        break;

        case 2:
            inserirProfissional(profissional);
        break;

        case 3:
            //Fun��o para editar informa��es dos m�dicos
        break;

        case 4:
            //Fun��o para remover m�dico
        break;

        case 5:
            a=1;
        break;

        default:
            system("cls");
            continue;
        }
    }while(a<1);
}

void menuClientes (){
    int op, a;
    do{
        system("cls");
        printf("\n----------------------------------------------------MENU DE CLIENTES----------------------------------------------------\n");
        printf("\n [1]Pesquisar por cliente\n [2]Inserir cliente\n [3]Editar informa��es de um cliente\n [4]Remover cliente\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Fun��o para pesquisar por cliente
        break;

        case 2:
            //Fun��o para inserir cliente
        break;

        case 3:
            //Fun��o para editar informa��es dos cliente
        break;

        case 4:
            //Fun��o para remover cliente
        break;

        case 5:
            a=1;
        break;

        default:
            system("cls");
            continue;
        }
    }while(a<1);
}

void menuAtendimentos (){
    int op, a;
    do{
        system("cls");
        printf("\n--------------------------------------------------MENU DE ATENDIMENTOS--------------------------------------------------\n");
        printf("\n [1]Pesquisar por atendimento\n [2]Inserir atendimento\n [3]Editar informa��es de um atendimento\n [4]Remover atendimento\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Fun��o para pesquisar por atendimento
        break;

        case 2:
            //Fun��o para inserir atendimento
        break;

        case 3:
            //Fun��o para editar informa��es dos atendimentos
        break;

        case 4:
            //Fun��o para remover atendimento
        break;

        case 5:
            a=1;
        break;

        default:
            system("cls");
            continue;
        }
    }while(a<1);
}

void menuProfissao (Profissao* profissao){
    int op, a;
    do{
        system("cls");
        printf("\n----------------------------------------------------MENU DE PROFISSÃO---------------------------------------------------\n");
        printf("\n [1]Pesquisar por profissão\n [2]Inserir profissão\n [3]Editar informações de uma profiss�o\n [4]Remover profissão\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            pesquisarProf(profissao);
        break;

        case 2:
            inserirProf(profissao);
        break;

        case 3:
            editarProf(profissao);
        break;

        case 4:
           removerProf(profissao);
        break;

        case 5:
            a=1;
        break;

        default:
            system("cls");
            continue;
        }
    }while(a<1);
}

void inserirProf(Profissao* profissao){
    int  i, op=1;

    for(i=0; i < variComProfissao; i++){
        system("cls");
        printf("\n---------------------------------------------------INSIRA A PROFISSÃO---------------------------------------------------\n");
        printf("\nInserir o nome da profissão: ");
        scanf("%s", profissao[i].nomeProf);

        printf("\nInserir o sigla da profissão: ");
        scanf("%s", profissao[i].siglaProf);

        profissao[i].codProf = 2023100+variComProfissao;
        printf("\nCódigo da profissão:%d", profissao[i].codProf);

        registrarProfissao(&profissao[i]);
        printf("\n\n [0]Inserir outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &op);

        if(op==0){
            variComProfissao++;
        }
        else{
            system("cls");
            continue;
        }
    }
}

void pesquisarProf(Profissao* profissao){
    int i, a=0;
    char op[50], str[8];

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISA POR PROFISSÃO-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (Nome, Sigla ou Código da Profissão)\n:");
        scanf("%s", op);
        system("cls");



        printf("\n\n [0]Ver outra profisss�o\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void removerProf(Profissao* profissao){
    int i, a=0;
    char op[50], str[8];

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISA POR PROFISS�O-------------------------------------------------");
        printf("\nDigita algo para a identificar a profiss�o que voc� deseja remover (Nome, Sigla ou C�digo da Profiss�o)\n:");
        scanf("%s", op);
        system("cls");

        for(i=0; i<variComProfissao; i++){
            sprintf(str, "%d", profissao[i].codProf);
            if(strcmp(op, profissao[i].nomeProf) == 0 || strcmp(op, str) == 0 || strcmp(op, profissao[i].siglaProf) == 0){
                memset(profissao[i].nomeProf, 0, sizeof(char[50]) );
                memset(profissao[i].siglaProf, 0, sizeof(char[10]) );
                profissao[i].codProf = 0;
            }
        }

        printf("\n\n [0]Ver outra profisss�o\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void editarProf(Profissao* profissao){
   int i, a=0, b;
    char op[50], str[8];

    do{
        system("cls");
        printf("-------------------------------------------------EDITAR POR PROFISS�O-------------------------------------------------");
        printf("\nDigita algo para a identificar a profiss�o que voc� deseja editar (Nome, Sigla ou C�digo da Profiss�o)\n:");
        scanf("%s", op);
        system("cls");

        for(i=0; i<variComProfissao; i++){
            sprintf(str, "%d", profissao[i].codProf);
            if(strcmp(op, profissao[i].nomeProf) == 0 || strcmp(op, str) == 0 || strcmp(op, profissao[i].siglaProf) == 0){
                    printf("\nInforme qual dado voc� deseja alterar \n[1]Nome \n[2]Sigla\n:");
                    scanf("%d", &b);

                switch(b){
                case 1:
                    printf("Digite o novo nome da profiss�o:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse � o disciplina j� alterado:%s", profissao[i].nomeProf);
                break;
                case 2:
                    printf("Digite a nova sigla da profiss�o:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse � a sigla j� alterada:%s", profissao[i].siglaProf);
                break;
                default:
                    system("cls");
                    continue;
                }
            }
        }

        printf("\n\n [0]Ver outra profisss�o\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}


void inserirProfissional(Profissional* profissional){
    int i, op=1;

    for(i=0; i<variComProfissional; i++){
        system("cls");
        printf("\n---------------------------------------------------AREA DE CADASTRO---------------------------------------------------\n");
        printf("\nNome: ");
        scanf("%s", profissional[i].nome);

        printf("\n\n[0]Novo Cadastro\n[1]Voltar\n");
        scanf("%d", &op);

        if(op==0) {
            variComProfissional++;
        }
        else{
            system("cls");
            continue;
        }
    }
}

/*
MODULO ARQUIVOS
*/

int abrirArquivo(FILE** arquivo, const char* caminho)
{
    if((*arquivo = fopen(caminho, "r+")) == NULL)
    {
        while (1)
        {
            system("cls");
            printf("Não foi possível abrir o arquivo \"%s\" \n", caminho);
            printf("Deseja criar um novo? (S/N)\n");
            char opcao;
            scanf("%c", &opcao);

            if (opcao == 's' || opcao == 'S')
            {
                if((*arquivo = fopen(caminho, "w+")) == NULL)
                {
                    printf("Não foi possível criar o arquivo \"%s\" \n", caminho);
                    return 0;
                }
                printf("O arquivo foi criado com sucesso.\n");
                return 1;
            }
            else if (opcao == 'n' || opcao == 'N')
            {
                break;
            }
        }

        return 0;
    }

    return 1;
}

void alocarRegistrosProfissao(Profissao* p)
{
    long pos = 0;



    while (lerRegistroProfissao(p, &pos) > 0)
    {printf("A\n");}
}

int lerRegistroProfissao(Profissao* p, long* pos)
{
	char line_BUFFER[128], sub_BUFFER[16];
    char c;
    int lerRegistro, linha_completa; //bool
    int i = 0, ii = 0;
    int id_atual = 0;

    //Leitura de Arquivo
    fseek(arquivo_profissao, (*pos), SEEK_SET);
    printf("FORA\n");
    while ((c = fgetc(arquivo_profissao)) != EOF)
    {
	    if (c != '\n')
	    {
	    	line_BUFFER[i++] = c;
	    	(*pos)++;
	    }
		else
		{
			linha_completa = 1;
			line_BUFFER[i] = '\0';
		}

	    //printf("sub_BUFFER:%s\n", line_BUFFER);
	    printf("pos: %d c:%c\n", *pos, c);

	    if(!linha_completa)
        {
            continue;
        }

		printf("linhaCompleta: %s\n", line_BUFFER);
	    i = 0;
	    //printf("SUB:%s\n", sub_BUFFER);
	    memset(sub_BUFFER, 0, sizeof(sub_BUFFER));

	    int j = 0;
	    while ((c = line_BUFFER[j++] )!= '-')
	    {
	    	if (isdigit(c)) // Converte id do registro para inteiro
    		{
				//printf("SUB:%s", sub_BUFFER);
    			sub_BUFFER[ii++] = c;
				//printf("c:%c\n", c);
			}
		}
		// Verifica se � a id correta
		id_atual = atoi(sub_BUFFER);
		//printf("id_atual:%d\n", id_atual);
		lerRegistro = 1;

	    //Leitura de Registro
	    if (lerRegistro)
	    while ((c = line_BUFFER[i++] )!= '\0')
	    {
			if (lerRegistro)
			{
				//printf("c:%c\n", c);
				//printf("LerRegistro\n");
				if (line_BUFFER[i] == '(')
				{
					while (line_BUFFER[++i] != ')')
					{
						//Dentro do Par�nteses
						//printf("Dentro\n");

						ii = 0;
						while ( (c = line_BUFFER[++i] ) != ',')
						{
							//CODIGO
							if (isdigit(c))
						   	{
						   		sub_BUFFER[ii++] = c;
								//printf("c:%c\n", c);
							}
						}
						p->codProf = atoi(sub_BUFFER);
						memset(sub_BUFFER, 0, sizeof(sub_BUFFER));

						ii = 0;
						do
						{
							//NOME
							p->nomeProf[ii++] = line_BUFFER[i];
							i++;
						} while (line_BUFFER[i] != ',');

						p->nomeProf[ii] = '\0';
						//printf("NOME: %s\n", p->nome);
						memset(sub_BUFFER, 0, sizeof(sub_BUFFER));

						//printf("idade BUFFER:%s\n", sub_BUFFER);
                        ii = 0;
						while ((c = line_BUFFER[++i]) != ')') // Termina Leitura
						{
							//SIGLA
							if(!isspace(c))
							{
								p->siglaProf[ii++] = line_BUFFER[i];
							}
						}

						//p->siglaProf = sub_BUFFER;
						lerRegistro = 0;
						linha_completa = 0;
						printf("COMPLETO\n");
						return 1;
					}
				}
			}
		}
		memset(line_BUFFER, 0, sizeof(line_BUFFER));

	}

	printf("num_BUFFER:%s\n", sub_BUFFER);
    memset(sub_BUFFER, 0, sizeof(sub_BUFFER));
    //printf("%s\n", BUFFER);
    return 0;
}

//Funções Escrita de Arquivos (Implementar)
void registrarProfissao(Profissao *p) // FUNCAO TESTE
{
    fseek(arquivo_profissao, 0, SEEK_END);
    fprintf(arquivo_profissao, OUT_FORMAT_PROFISSAO, global_arquivo_index, p->codProf, p->nomeProf, p->siglaProf );
    fseek(arquivo_profissao, 0, SEEK_SET);
    global_arquivo_index++;
}
