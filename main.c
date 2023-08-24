#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int variComProf=1; //variavel de comando da profiss�o

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
        printf("\n Pesquisar por:\n [1]M�dico\n [2]Cliente\n [3]Atendimento\n [4]Profiss�o\n\n [5]Sair \n\n :");
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
        printf("\n----------------------------------------------------MENU DE M�DICOS-----------------------------------------------------\n");
        printf("\n [1]Pesquisar por m�dico\n [2]Inserir m�dico\n [3]Editar informa��es de um m�dico\n [4]Remover m�dico\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Fun��o para pesquisar por m�dico
        break;

        case 2:
            //Fun��o para inserir m�dico
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
        printf("\n----------------------------------------------------MENU DE PROFISS�O---------------------------------------------------\n");
        printf("\n [1]Pesquisar por profiss�o\n [2]Inserir profiss�o\n [3]Editar informa��es de uma profiss�o\n [4]Remover profiss�o\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Fun��o para pesquisar por profiss�o
        break;

        case 2:
            inserirProf(profissao);
            system("cls");
        break;

        case 3:
            //Fun��o para editar informa��es dos profiss�o
        break;

        case 4:
            //Fun��o para remover profiss�o
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
        printf("\n---------------------------------------------------INSIRA A PROFISS�O---------------------------------------------------\n");
        printf("\nInserir o nome da profiss�o: ");
        scanf("%s", profissao[i].nomeProf);

        printf("\nInserir o sigla da profiss�o: ");
        scanf("%s", profissao[i].siglaProf);

        profissao[i].codProf = 2023100+i;
        printf("\nC�digo da profiss�o:%d", profissao[i].codProf);

        printf("\n [0]Inserir outra profisss�o\n [1]Voltar\n\n ");
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
