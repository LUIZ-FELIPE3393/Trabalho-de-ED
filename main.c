#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 512

int variComProf=1; //variavel de comando da profissão
int variComMed=1; //variavel de comando de medico
int variComAten=1; //variavel de comando de atendimento

typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    char logradouro[30], bairro[30], cidade[20], estado[10];
    int numEndereco, cep;
}Endereco;

typedef struct{
    int codProf;
    char nomeProf[50], siglaProf[10];
}Profissao;

typedef struct{
    char cpf[11], nome[50], email[50], tipo[50];
    int  numRegP, fone, matricula;
    Profissao codProf;
    Data dataMed;
}Profissional;

typedef struct{
    char nome[50], email[50];
    int idade, fone, celular;
    Data dataCliente;
    Endereco endereco;
}Cliente;

typedef struct{
    int numero, matAten;
    char aten[TAM_MAX];
    Data dataAten;
}Atendimento;

void menuProfissionais ();
void menuClientes (Profissional* profissional);
void menuAtendimentos (Atendimento* atendimento);
void menuProfissao (Profissao* profissao);

void pesquisarAten(Atendimento* atendimento);
void inserirAten(Atendimento* atendimento);
void editarAten(Atendimento* atendimento);
void removerAten(Atendimento* atendimento);

void inserirProf(Profissao* profissao);
void pesquisarProf(Profissao* profissao);
void removerProf(Profissao* profissao);
void editarProf(Profissao* profissao);

void pesquisarProfissional(Profissional* profissional);
void inserirProfissional(Profissional* profissional);
void editarProfissional(Profissional* profissional);
void removerProfissional(Profissional* profissional);

int main(){

    Profissao profissao [TAM_MAX];
    Profissional profissionais [TAM_MAX];
    Atendimento atendimento [TAM_MAX];

    setlocale(LC_ALL,"");

    int op, a=0;

    do{
        printf("\n--------------------------------------------------------BEM VINDO-------------------------------------------------------\n");
        printf("\n Pesquisar por:\n [1]Médico\n [2]Cliente\n [3]Atendimento\n [4]Profissão\n\n [5]Sair \n\n :");
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
            menuAtendimentos (atendimento);
            system("cls");
        break;

        case 4:
            menuProfissao (profissao);
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

void menuProfissionais  (Profissional* profissional){
    int op, a;
    do{
        system("cls");
        printf("\n----------------------------------------------------MENU DE MÉDICOS-----------------------------------------------------\n");
        printf("\n [1]Pesquisar por médico\n [2]Inserir médico\n [3]Editar informações de um médico\n [4]Remover médico\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Função para pesquisar por médico
        break;

        case 2:
            inserirProfissional(profissional);
        break;

        case 3:
            //Função para editar informações dos médicos
        break;

        case 4:
            //Função para remover médico
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
        printf("\n [1]Pesquisar por cliente\n [2]Inserir cliente\n [3]Editar informações de um cliente\n [4]Remover cliente\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Função para pesquisar por cliente
        break;

        case 2:
            //Função para inserir cliente
        break;

        case 3:
            //Função para editar informações dos cliente
        break;

        case 4:
            //Função para remover cliente
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

void menuAtendimentos (Atendimento* atendimento){
    int op, a;
    do{
        system("cls");
        printf("\n--------------------------------------------------MENU DE ATENDIMENTOS--------------------------------------------------\n");
        printf("\n [1]Pesquisar por atendimento\n [2]Inserir atendimento\n [3]Editar informações de um atendimento\n [4]Remover atendimento\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            pesquisarAten(atendimento);
        break;

        case 2:
            inserirAten(atendimento);
        break;

        case 3:
            editarAten(atendimento);
        break;

        case 4:
            removerAten(atendimento);
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
        printf("\n [1]Pesquisar por profissão\n [2]Inserir profissão\n [3]Editar informações de uma profissão\n [4]Remover profissão\n\n [5]Voltar \n\n :");
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

    for(i=0; i<variComProf; i++){
        system("cls");
        printf("\n---------------------------------------------------INSIRIR PROFISSÃO---------------------------------------------------\n");
        printf("\nInserir o nome da profissão: ");
        scanf("%s", profissao[i].nomeProf);

        printf("\nInserir o sigla da profissão: ");
        scanf("%s", profissao[i].siglaProf);

        profissao[i].codProf = 2023100+variComProf;
        printf("\nCódigo da profissão:%d", profissao[i].codProf);

        printf("\n\n [0]Inserir outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &op);

        if(op==0){
            variComProf++;
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

        for(i=0; i<variComProf; i++){
            sprintf(str, "%d", profissao[i].codProf);
            if(strcmp(op, profissao[i].nomeProf) == 0 || strcmp(op, str) == 0 || strcmp(op, profissao[i].siglaProf) == 0){
                printf("\n Nome da profissão: %s", profissao[i].nomeProf);
                printf("\n Sigla da profissão: %s", profissao[i].siglaProf);
                printf("\n Código da profissão: %d", profissao[i].codProf);
            }
        }

        printf("\n\n [0]Ver outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void removerProf(Profissao* profissao){
    int i, a=0;
    char op[50], str[8];

    do{
        system("cls");
        printf("-------------------------------------------------REMOVER PROFISSÃO-------------------------------------------------");
        printf("\nDigita algo para a identificar a profissão que você deseja remover (Nome, Sigla ou Código da Profissão)\n:");
        scanf("%s", op);
        system("cls");

        for(i=0; i<variComProf; i++){
            sprintf(str, "%d", profissao[i].codProf);
            if(strcmp(op, profissao[i].nomeProf) == 0 || strcmp(op, str) == 0 || strcmp(op, profissao[i].siglaProf) == 0){
                memset(profissao[i].nomeProf, 0, sizeof(char[50]) );
                memset(profissao[i].siglaProf, 0, sizeof(char[10]) );
                profissao[i].codProf = 0;
            }
        }

        printf("\n\n [0]Ver outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void editarProf(Profissao* profissao){
   int i, a=0, b;
    char op[50], str[8];

    do{
        system("cls");
        printf("------------------------------------------------EDITAR PROFISSÃO-------------------------------------------------");
        printf("\nDigita algo para a identificar a profissão que você deseja editar (Nome, Sigla ou Código da Profissão)\n:");
        scanf("%s", op);
        system("cls");

        for(i=0; i<variComProf; i++){
            sprintf(str, "%d", profissao[i].codProf);
            if(strcmp(op, profissao[i].nomeProf) == 0 || strcmp(op, str) == 0 || strcmp(op, profissao[i].siglaProf) == 0){
                    printf("\nInforme qual dado você deseja alterar \n[1]Nome \n[2]Sigla\n:");
                    scanf("%d", &b);

                switch(b){
                case 1:
                    printf("Digite o novo nome da profissão:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse é o disciplina já alterado:%s", profissao[i].nomeProf);
                break;
                case 2:
                    printf("Digite a nova sigla da profissão:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse é a sigla já alterada:%s", profissao[i].siglaProf);
                break;
                default:
                    system("cls");
                    continue;
                }
            }
        }

        printf("\n\n [0]Ver outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}


void inserirProfissional(Profissional* profissional){
    int i, op=1;

    for(i=0; i<variComMed; i++){
        system("cls");
        printf("\n---------------------------------------------------AREA DE CADASTRO---------------------------------------------------\n");
        printf("\nNome: ");
        fflush(stdin);
        gets(profissional[i].nome);
        fflush(stdin);

        printf("\n\n[0]Novo Cadastro\n[1]Voltar\n");
        scanf("%d", &op);

        if(op==0) {
            variComMed++;
        }
        else{
            system("cls");
            continue;
        }
    }
}

 void pesquisarAten(Atendimento* atendimento){
    int i, a=0, op;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISAR POR ATENDIMENTO-------------------------------------------------");

        printf("\nDigita algo para a pesquisa (Matrícula ou número do atendimento)\n:");
        scanf("%d", &op);

        system("cls");

        for(i=0; i<variComAten; i++){
            if(op==atendimento[i].matAten||op==atendimento[i].numero){
                printf("\n Data do atendimento: %d/%d/%d", atendimento[i].dataAten.dia, atendimento[i].dataAten.mes, atendimento[i].dataAten.ano);
                printf("\n Atendimento:\n %s", atendimento[i].aten);
                printf("\n Matrícula do atendimento: %d", atendimento[i].matAten);
                printf("\n Número do atendimento: %d", atendimento[i].numero);
                i=variComAten;
            }
        }

        printf("\n\n [0]Ver outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 void inserirAten(Atendimento* atendimento){
     int  i, op=1;

    for(i=0; i<variComAten; i++){
        system("cls");
        printf("\n--------------------------------------------------INSERIR ATENDIMENTO--------------------------------------------------\n");

        printf("\n:-Data do atendimento-\n");

        printf("\n Ano:");
        scanf("%d", &atendimento[i].dataAten.ano);

        printf("\n Mês:");
        scanf("%d", &atendimento[i].dataAten.mes);

        printf("\n Dia:");
        scanf("%d", &atendimento[i].dataAten.dia);

        system("cls");

        printf("Sobre o atendimento (Max 500 caracteres)\n:");
        fflush(stdin);
        gets(atendimento[i].aten);
        fflush(stdin);

        system("cls");

        atendimento[i].matAten = 2023200+variComAten;
        printf("\n Matricula do atendimento: %d", atendimento[i].matAten);

        atendimento[i].numero = variComAten;
        printf("\n Número do atendimento: %d", atendimento[i].numero);

        printf("\n\n [0]Inserir outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &op);

        if(op==0){
            variComAten++;
        }
        else{
            system("cls");
            continue;
        }
    }
 }

void editarAten(Atendimento* atendimento){
    int i, a=0, b, op;

    do{
        system("cls");
        printf("-------------------------------------------------EDITAR  ATENDIMENTO-------------------------------------------------");
        printf("\nDigita algo para a identificar o atendimento que você deseja editar (matrícula ou número do atendimento)\n:");
        scanf("%d", &op);
        system("cls");

        for(i=0; i<variComAten; i++){
            if(op==atendimento[i].matAten||op==atendimento[i].numero){
                    printf("\nInforme qual dado você deseja alterar \n[1]O atendimento \n[2]A data\n:");
                    scanf("%d", &b);

                switch(b){
                case 1:
                    system("cls");
                    printf(" Digite as novas especificações do atendimento(Max 500 caracteres):\n:");
                    fflush(stdin);
                    gets(atendimento[i].aten);
                    fflush(stdin);
                    printf(" Esse é o atendimento já alterado:\n:%s", atendimento[i].aten);
                break;
                case 2:
                    system("cls");
                    printf(" Digite a nova data do atendimento:");
                    printf("\n Ano:");
                    scanf("%d", &atendimento[i].dataAten.ano);

                    printf("\n Mês:");
                    scanf("%d", &atendimento[i].dataAten.mes);

                    printf("\n Dia:");
                    scanf("%d", &atendimento[i].dataAten.dia);

                    printf(" Esse é a data já alterada:%d/%d/%d", atendimento[i].dataAten.dia, atendimento[i].dataAten.mes, atendimento[i].dataAten.ano);
                break;
                default:
                    system("cls");
                    continue;
                }
            }
        }

        printf("\n\n [0]Ver outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void removerAten(Atendimento* atendimento){
    int i, a=0, op;

    do{
        system("cls");
        printf("-------------------------------------------------REMOVER ATENDIMENTO-------------------------------------------------");
        printf("\nDigita algo para a identificar o atendimento que você deseja remover (matrícula ou número do atendimento)\n:");
        scanf("%d", &op);
        system("cls");

        for(i=0; i<variComProf; i++){
            if(op==atendimento[i].matAten||op==atendimento[i].numero){
                memset(atendimento[i].aten, 0, sizeof(char[TAM_MAX]) );
                atendimento[i].matAten = 0;
                atendimento[i].numero = 0;
                atendimento[i].dataAten.ano = 0;
                atendimento[i].dataAten.dia = 0;
                atendimento[i].dataAten.mes = 0;
            }
        }

        printf("\n [0]Remover outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}
