#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int variComProf=1; //variavel de comando da profiss�o
int variComMed=1; //variavel de comando de medico

typedef struct{
    int codProf;
    char nomeProf[50], siglaProf[10];
//Registro das profiss�es
}Profissao;

typedef struct{
    char cpf[11], nome[50], email[50], tipo[50];
    int codProf, numRegP, fone, matricula, dia, mes, ano;
//Registro dos Profissionais de sa�de
} Medico;

typedef struct{
    char nome[50], email[50];
    int idade, fone, celular, dia, mes, ano;
//Registro dos clientes
}cliente;

typedef struct{
    int numero, matricula, dia, mes, ano;
//Registro dos atendimentos
}atendimento;

void menuMedicos ();
void menuClientes ();
void menuAtendimentos ();
void menuProfissao (Profissao* profissao);
void inserirProf(Profissao* profissao);
void pesquisarProf(Profissao* profissao);
void removerProf(Profissao* profissao);
void editarProf(Profissao* profissao);
void pesquisarMedico(Medico* medico);
void inserirMedico(Medico* medico);
void editarMedico(Medico* medico);
void removerMedico(Medico* medico);

int main(){
    Profissao profissao [variComProf];
    Medico medico [variComMed];
    setlocale(LC_ALL,"");

    int op, a=0;

    do{
        printf("\n--------------------------------------------------------BEM VINDO-------------------------------------------------------\n");
        printf("\n Pesquisar por:\n [1]M�dico\n [2]Cliente\n [3]Atendimento\n [4]Profiss�o\n\n [5]Sair \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            menuMedicos (medico);
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

void menuMedicos (Medico* medico){
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
            inserirMedico(medico);
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
        printf("\n---------------------------------------------------INSIRA A PROFISS�O---------------------------------------------------\n");
        printf("\nInserir o nome da profiss�o: ");
        scanf("%s", profissao[i].nomeProf);

        printf("\nInserir o sigla da profiss�o: ");
        scanf("%s", profissao[i].siglaProf);

        profissao[i].codProf = 2023100+variComProf;
        printf("\nC�digo da profiss�o:%d", profissao[i].codProf);

        printf("\n\n [0]Inserir outra profisss�o\n [1]Voltar\n: ");
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
        printf("-------------------------------------------------PESQUISA POR PROFISS�O-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (Nome, Sigla ou C�digo da Profiss�o)\n:");
        scanf("%s", op);
        system("cls");

        for(i=0; i<variComProf; i++){
            //if(op==(((profissao[i].codProf)||profissao[i].nomeProf)||profissao[i].siglaProf)){
            sprintf(str, "%d", profissao[i].codProf);
            if(strcmp(op, profissao[i].nomeProf) == 0 || strcmp(op, str) == 0 || strcmp(op, profissao[i].siglaProf) == 0){
                printf("\n Nome da profiss�o: %s", profissao[i].nomeProf);
                printf("\n Sigla da profiss�o: %s", profissao[i].siglaProf);
                printf("\n C�digo da profiss�o: %d", profissao[i].codProf);
            }
        }

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

        for(i=0; i<variComProf; i++){
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

        for(i=0; i<variComProf; i++){
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
                    printf("Digite o novo nome da profiss�o:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse � o disciplina j� alterado:%s", profissao[i].nomeProf);
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


void inserirMedico(Medico* medico){
    int i, op=1;

    for(i=0; i<variComMed; i++){
        system("cls");
        printf("\n---------------------------------------------------AREA DE CADASTRO---------------------------------------------------\n");
        printf("\nNome: ");
        scanf("%s", medico[i].nome);



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

