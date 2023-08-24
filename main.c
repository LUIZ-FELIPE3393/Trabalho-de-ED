#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int variComProf=1; //variavel de comando da profissão

typedef struct{
    int codProf;
    char nomeProf[50], siglaProf[10];
}Profissao;

void menuMedicos ();
void menuClientes ();
void menuAtendimentos ();
void menuProfissao (Profissao* profissao);
void inserirProf(Profissao* profissao);

int main(){
    Profissao profissao [variComProf];

    setlocale(LC_ALL,"");
    int op, a=0;

    do{
        printf("\n--------------------------------------------------------BEM VINDO-------------------------------------------------------\n");
        printf("\n Pesquisar por:\n [1]Médico\n [2]Cliente\n [3]Atendimento\n [4]Profissão\n\n [5]Sair \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            menuMedicos ();
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

void menuMedicos (){
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
            //Função para inserir médico
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

void menuAtendimentos (){
    int op, a;
    do{
        system("cls");
        printf("\n--------------------------------------------------MENU DE ATENDIMENTOS--------------------------------------------------\n");
        printf("\n [1]Pesquisar por atendimento\n [2]Inserir atendimento\n [3]Editar informações de um atendimento\n [4]Remover atendimento\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Função para pesquisar por atendimento
        break;

        case 2:
            //Função para inserir atendimento
        break;

        case 3:
            //Função para editar informações dos atendimentos
        break;

        case 4:
            //Função para remover atendimento
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
            //Função para pesquisar por profissão
        break;

        case 2:
            inserirProf(profissao);
            system("cls");
        break;

        case 3:
            //Função para editar informações dos profissão
        break;

        case 4:
            //Função para remover profissão
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
        printf("\n---------------------------------------------------INSIRA A PROFISSÃO---------------------------------------------------\n");
        printf("\nInserir o nome da profissão: ");
        scanf("%s", profissao[i].nomeProf);

        printf("\nInserir o sigla da profissão: ");
        scanf("%s", profissao[i].siglaProf);

        profissao[i].codProf = 2023100+i;
        printf("\nCódigo da profissão:%d", profissao[i].codProf);

        printf("\n [0]Inserir outra profisssão\n [1]Voltar\n\n ");
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
