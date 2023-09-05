#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 512

int variComProfissao = 0; //variável de comando de profissão
int tamVetProfissao = 0; //tamanho atual do vetor de profissão

int variComProfissional=0; //variável de comando de médico

int variComAten = 0; //variável de comando de atendimento
int tamVetAten = 0; //tamanho atual do vetor de atendimento

int variComCliente = 0; //variável de comando de cliente


const long codBaseProf = 2023000000;
const long codBaseAten = 2023100000;
const long codBaseProfissional = 2023200000;
const long codBaseCliente = 2023300000;

const char* OUT_PROFISSAO_FORMAT =
    "%d{nome:\"%s\",sigla:%s}\n";

const char* IN_PROFISSAO_FORMAT =
    "%d{nome:\"%[^\"]\",sigla:%[^}]}";

const char* OUT_ATENDIMENTO_FORMAT =
    "%d{numero:\"%s\",data:%d/%d/%d,descricao:\"%s\"}\n";

const char* IN_ATENDIMENTO_FORMAT =
    "%d{numero:\"%[^\"]\",data:%d/%d/%d,descricao:\"%[^\"]\"}\n";

FILE* arquivo_profissao = NULL;
FILE* arquivo_atendimento = NULL;
FILE* arquivo_log = NULL;

const char ARQUIVO_MODO_ESCREVER = 0;
const char ARQUIVO_MODO_LER = 1;

typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    char logradouro[30], bairro[30], cidade[20], estado[10], cep[9];
    int numEndereco;
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
    char nome[50], email[50], celular[11];
    int idade, fone, codigo;
    Data dataCliente;
    Endereco endereco;
}Cliente;

typedef struct{
    int numero, matAten;
    char aten[TAM_MAX];
    Data dataAten;
    //Cliente codigoInAten;
}Atendimento;

void menuProfissionais (Profissional* profissional);
void menuClientes ();
void menuProfissao (Profissao* profissao);
void menuAtendimentos (Atendimento* atendimento);

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

void inserirCliente(Cliente* cliente);
void pesquisarCliente(Cliente* cliente);
void editarCliente(Cliente* cliente);
void removerCliente(Cliente* cliente);

int abrirArquivo(FILE** arquivo, const char* caminho, const char modo);

void gerarProf(Profissao* p);
void alocarRegistroProfissao(Profissao* p);
void registrarProfissao(Profissao *p);
void atualizarRegistroProfissao(Profissao* p);

void gerarAtendimento(Atendimento* a);
void alocarRegistroAtendimento(Atendimento* a);
void registrarAtendimento(Atendimento *a);
void atualizarRegistroAtendimento(Atendimento* a);

int main(){

    Profissao profissoes [TAM_MAX];
    Profissional profissionais [TAM_MAX];
    Atendimento atendimento [TAM_MAX];
    Cliente cliente[TAM_MAX];

    setlocale(LC_ALL,"");

    abrirArquivo(&arquivo_profissao, "regProfissao.txt", ARQUIVO_MODO_LER);
    abrirArquivo(&arquivo_atendimento, "regAtendimento.txt", ARQUIVO_MODO_LER);
    if((arquivo_log = fopen("log.txt", "w")) == NULL)
    {
        printf("Não foi possível criar o arquivo \"log.txt\" \n");
        return 0;
    }
    alocarRegistroProfissao(profissoes);
    alocarRegistroAtendimento(atendimento);

    int op, a=0;

    do{
        printf("\n--------------------------------------------------------BEM VINDO-------------------------------------------------------\n");
        printf("\nIr para o menu de:\n [1]Profissional\n [2]Cliente\n [3]Atendimento\n [4]Profissão\n\n [5]Sair \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            menuProfissionais (profissionais);
            system("cls");
            break;

        case 2:
            menuClientes (cliente);
            system("cls");
            break;

        case 3:
            menuAtendimentos (atendimento);
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

void menuProfissionais  (Profissional* profissional){
    int op, a;
    do{
        system("cls");
        printf("\n----------------------------------------------------MENU DE PROFISSIONAIS-----------------------------------------------------\n");
        printf("\n [1]Pesquisar por profissional\n [2]Inserir profissional\n [3]Editar informações de um profissional\n [4]Remover profissional\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            //Função para pesquisar por m�dico
            break;

        case 2:
            inserirProfissional(profissional);
            break;

        case 3:
            //Função para editar informa��es dos m�dicos
            break;

        case 4:
            //Função para remover m�dico
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

void menuClientes (Cliente* cliente){
    int op, a;
    do{
        system("cls");
        printf("\n----------------------------------------------------MENU DE CLIENTES----------------------------------------------------\n");
        printf("\n [1]Pesquisar por cliente\n [2]Inserir cliente\n [3]Editar informa��es de um cliente\n [4]Remover cliente\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            pesquisarCliente(cliente);
            break;

        case 2:
            inserirCliente(cliente);
            break;

        case 3:
            editarCliente(cliente);
            break;

        case 4:
            removerCliente(cliente);
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
        printf("\n [1]Pesquisar por atendimento\n [2]Inserir atendimento\n [3]Editar informa��es de um atendimento\n [4]Remover atendimento\n\n [5]Voltar \n\n :");
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
    int i, op=1;

    while(1){
        system("cls");
        printf("\n---------------------------------------------------INSIRIR PROFISSÃO---------------------------------------------------\n");
        printf("\nCodigo = %d\n", codBaseProf+variComProfissao);
        printf("\nInserir o nome da profissão: ");
        scanf("%s", profissao[tamVetProfissao].nomeProf);

        printf("\nInserir o sigla da profissão: ");
        scanf("%s", profissao[tamVetProfissao].siglaProf);

        profissao[tamVetProfissao].codProf = codBaseProf+variComProfissao;
        printf("\nCódigo da profissão:%d", profissao[tamVetProfissao].codProf);

        tamVetProfissao++;
        variComProfissao++;
        for (i = 0; i < tamVetProfissao; i++)
        {
            printf("\n%d %s %s",profissao[i].codProf, profissao[i].nomeProf, profissao[i].siglaProf);
        }
        atualizarRegistroProfissao(profissao);
        printf("\n\n [0]Inserir outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &op);

        if(op==1){
            break;
        }
        else{
            system("cls");
            continue;
        }
    }
}

void pesquisarProf(Profissao* profissao){
    int i, ii = 0, a=0;
    char op[50];
    int codigo, eNumero;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISA POR PROFISSÃO-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (Nome, Sigla ou Código da Profissão)\n:");
        scanf("%s", op);
        fflush(stdin);
        system("cls");
        eNumero = 1;

        //Verificando se op é número
        while(ii < strlen(op))
        {
            if(!(op[ii] >= '0' && op[ii] < '9'))
            {
                eNumero = 0;
            }
            ii++;
        }

        if(eNumero)
        {
            codigo = atoi(op);
        }

        for(i=0; i<tamVetProfissao; i++){
            //Você pode usar atoi para converter uma string para int
            if(strcmp(op, profissao[i].nomeProf) == 0 || codigo == profissao[i].codProf || strcmp(op, profissao[i].siglaProf) == 0){
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
    int i, ii = 0, a=0;
    char op[50], str[8];
    int codigo, eNumero;

    do{
        system("cls");
        printf("-------------------------------------------------REMOVER PROFISSÃO-------------------------------------------------");
        printf("\nDigita algo para a identificar a profissão que você deseja remover (Nome, Sigla ou Código da Profissão)\n:");
        scanf("%s", op);
        system("cls");

        eNumero = 1;

        //Verificando se op é número
        while(ii < strlen(op))
        {
            if(!(op[ii] >= '0' && op[ii] < '9'))
            {
                eNumero = 0;
            }
            ii++;
        }

        if(eNumero)
        {
            codigo = atoi(op);
        }

        for(i=0; i<tamVetProfissao; i++){
            //Você pode usar atoi para converter uma string para int
            if(strcmp(op, profissao[i].nomeProf) == 0 || codigo == profissao[i].codProf || strcmp(op, profissao[i].siglaProf) == 0){
                printf("\nRemovendo\n%d\n%s\n%s\n", profissao[i].codProf, profissao[i].nomeProf, profissao[i].siglaProf);
                memset(profissao[i].nomeProf, 0, sizeof(char[50]) );
                memset(profissao[i].siglaProf, 0, sizeof(char[10]) );
                profissao[i].codProf = 0;
                atualizarRegistroProfissao(profissao);
                tamVetProfissao--;
                alocarRegistroProfissao(profissao);
                break;
            }
        }
        printf("\n\n [0]Ver outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void editarProf(Profissao* profissao){
   int i, ii = 0, a=0, opcao;
    char op[50], str[8];
    int codigo, eNumero;

    do{
        system("cls");
        printf("------------------------------------------------EDITAR PROFISSÃO-------------------------------------------------");
        printf("\nDigita algo para a identificar a profissão que você deseja editar (Nome, Sigla ou Código da Profissão)\n:");
        fflush(stdin);
        scanf("%s", op);
        system("cls");

        eNumero = 1;
        codigo = 0;

        //Verificando se op é número
        ii = 0;
        while(ii < strlen(op))
        {
            if(!(op[ii] >= '0' && op[ii] < '9'))
            {
                eNumero = 0;
            }
            ii++;
        }

        if(eNumero)
        {
            codigo = atoi(op);
        }

        for(i=0; i<tamVetProfissao; i++){
            if(strcmp(op, profissao[i].nomeProf) == 0 || codigo == profissao[i].codProf || strcmp(op, profissao[i].siglaProf) == 0){
                printf("\nEditando\n%d\n%s\n%s\n", profissao[i].codProf, profissao[i].nomeProf, profissao[i].siglaProf);
                printf("\nInforme qual dado você deseja alterar \n[1]Nome \n[2]Sigla \n[3]Voltar\n:");
                scanf("%d", &opcao);

                switch(opcao){
                case 1:
                    printf("Digite o novo nome da profissão:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse é o nome já alterado:%s", profissao[i].nomeProf);
                    i = tamVetProfissao;
                    break;
                case 2:
                    printf("Digite a nova sigla da profissão:");
                    scanf("%s", profissao[i].siglaProf);
                    printf("Esse é a sigla já alterada:%s", profissao[i].siglaProf);
                    i = tamVetProfissao;
                    break;
                case 3:
                    break;
                default:
                    system("cls");
                    continue;
                }
                atualizarRegistroProfissao(profissao);
                alocarRegistroProfissao(profissao);

            }
        }

        printf("\n\n [0]Ver outra profisssão\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}


void inserirProfissional(Profissional* profissional){
    int i, op=1;

    for(i=0; i<variComProfissional; i++){
        system("cls");
        printf("\n---------------------------------------------------AREA DE CADASTRO---------------------------------------------------\n");
        printf("\nNome: ");
        fflush(stdin);
        gets(profissional[i].nome);
        fflush(stdin);

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

 void pesquisarAten(Atendimento* atendimento){
    int i, a=0, op;
    int eNumero, codigo;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISAR POR ATENDIMENTO-------------------------------------------------");

        printf("\nDigita algo para a pesquisa (Matrícula ou número do atendimento)\n:");
        scanf("%d", &op);

        system("cls");

        for(i = 0; i < tamVetAten; i++){
            if(op == atendimento[i].matAten||op == atendimento[i].numero){
                printf("\n Data do atendimento: %d/%d/%d", atendimento[i].dataAten.dia, atendimento[i].dataAten.mes, atendimento[i].dataAten.ano);
                printf("\n Atendimento:\n %s", atendimento[i].aten);
                printf("\n Matrícula do atendimento: %d", atendimento[i].matAten);
                printf("\n Número do atendimento: %d", atendimento[i].numero);
                break;
            }
        }

        printf("\n\n [0]Ver outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 void inserirAten(Atendimento* atendimento){
     int  i, op=1;

    while(1) {
        system("cls");
        printf("\n--------------------------------------------------INSERIR ATENDIMENTO--------------------------------------------------\n");

        printf("\n:-Data do atendimento-\n");

        printf("\n Ano:");
        scanf("%d", &atendimento[tamVetAten].dataAten.ano);

        printf("\n Mês:");
        scanf("%d", &atendimento[tamVetAten].dataAten.mes);

        printf("\n Dia:");
        scanf("%d", &atendimento[tamVetAten].dataAten.dia);

        system("cls");

        printf("Sobre o atendimento (Max 500 caracteres)\n:");
        fflush(stdin);
        gets(atendimento[tamVetAten].aten);
        fflush(stdin);

        system("cls");

        printf("Matrícula do profissional:");
        scanf("%d", &atendimento[tamVetAten].matAten);

        ///TODO Integração com Profissional

        atendimento[i].numero = variComAten;
        printf("\n Número do atendimento: %d", atendimento[tamVetAten].numero);

        tamVetAten++;
        variComAten++;
        for (i = 0; i < tamVetProfissao; i++)
        {
            printf("\nnumero:%d\nmatAten:%d\ndescricao:%s",atendimento[i].numero, atendimento[i].matAten, atendimento[i].aten);
        }

        atualizarRegistroAtendimento(atendimento);

        printf("\n\n [0]Inserir outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &op);

        if(op==1){
            break;
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
        printf("\nDigita algo para a identificar o atendimento que voc� deseja editar (matr�cula ou n�mero do atendimento)\n:");
        scanf("%d", &op);
        system("cls");

        for(i=0; i<variComAten; i++){
            if(op==atendimento[i].matAten||op==atendimento[i].numero){
                    printf("\nInforme qual dado voc� deseja alterar \n[1]O atendimento \n[2]A data\n:");
                    scanf("%d", &b);

                switch(b){
                case 1:
                    system("cls");
                    printf(" Digite as novas especifica��es do atendimento(Max 500 caracteres):\n:");
                    fflush(stdin);
                    gets(atendimento[i].aten);
                    fflush(stdin);
                    printf(" Esse � o atendimento j� alterado:\n:%s", atendimento[i].aten);
                    break;
                case 2:
                    system("cls");
                    printf(" Digite a nova data do atendimento:");
                    printf("\n Ano:");
                    scanf("%d", &atendimento[i].dataAten.ano);

                    printf("\n M�s:");
                    scanf("%d", &atendimento[i].dataAten.mes);

                    printf("\n Dia:");
                    scanf("%d", &atendimento[i].dataAten.dia);

                    printf(" Esse � a data j� alterada:%d/%d/%d", atendimento[i].dataAten.dia, atendimento[i].dataAten.mes, atendimento[i].dataAten.ano);
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

void removerAten(Atendimento* atendimento){
    int i, a=0, op;

    do{
        system("cls");
        printf("-------------------------------------------------REMOVER ATENDIMENTO-------------------------------------------------");
        printf("\nDigita algo para a identificar o atendimento que voc� deseja remover (matr�cula ou n�mero do atendimento)\n:");
        scanf("%d", &op);
        system("cls");

        for(i=0; i<variComAten; i++){
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

void inserirCliente(Cliente* cliente){
    int  i, op=1;

    for(i=0; i<variComCliente; i++){
        system("cls");
        printf("\n--------------------------------------------------INSERIR CLIENTE--------------------------------------------------\n");

        printf("\n:-Cadastro do cliente-\n");

        printf("\n Nome:");
        fflush(stdin);
        gets(cliente[i].nome);
        fflush(stdin);

        printf("\n Idade:");
        scanf("%d", &cliente[i].idade);

        printf("\n Email:");
        fflush(stdin);
        gets(cliente[i].email);
        fflush(stdin);

        printf("\n Celular para contato:");
        fflush(stdin);
        gets(cliente[i].celular);
        fflush(stdin);

        system("cls");

        printf("-Data de nascimento-");
        printf("\n Ano:");
        scanf("%d", &cliente[i].dataCliente.ano);

        printf("\n M�s:");
        scanf("%d", &cliente[i].dataCliente.mes);

        printf("\n Dia:");
        scanf("%d", &cliente[i].dataCliente.dia);

        system("cls");

        printf("-Endere�o-");
        printf("\nEstado:");
        fflush(stdin);
        gets(cliente[i].endereco.estado);
        fflush(stdin);

        printf("\nCidade:");
        fflush(stdin);
        gets(cliente[i].endereco.cidade);
        fflush(stdin);

        printf("\nBairro:");
        fflush(stdin);
        gets(cliente[i].endereco.bairro);
        fflush(stdin);

        printf("\nRua:");
        fflush(stdin);
        gets(cliente[i].endereco.logradouro);
        fflush(stdin);

        printf("\nN�mero:");
        scanf("%d", &cliente[i].endereco.numEndereco);

        printf("\nCep:");
        fflush(stdin);
        gets(cliente[i].endereco.cep);
        fflush(stdin);

        system("cls");

        cliente[i].codigo = 2023300+variComCliente;
        printf("\n C�digo do cliente: %d", cliente[i].codigo);

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

void pesquisarCliente(Cliente* cliente){
    int i, a=0;
    char op[50], str[9];

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISAR POR CLIENTE-------------------------------------------------");

        printf("\nDigita algo para a pesquisa (C�digo, n�mero do celular, email ou nome do cliente)\n:");
        scanf("%s", op);

        system("cls");

        for(i=0; i<variComCliente; i++){
            sprintf(str, "%d", cliente[i].codigo);
            if(strcmp(op,str) == 0 || strcmp(op, cliente[i].nome) == 0 || strcmp(op, cliente[i].email) || strcmp(op, cliente[i].celular)  == 0){
               printf("\nNome: %s", cliente[i].nome);
               printf("\nData de nascimento: %d/%d/%d", cliente[i].dataCliente.dia, cliente[i].dataCliente.mes, cliente[i].dataCliente.ano);
               printf("\nCelular de contato: %s", cliente[i].celular);
               printf("\nEmail: %s", cliente[i].email);
               printf("\n\nEstado: %s\nCidade: %s\nBairro: %s\nRua: %s\nN�mero da casa: %d\nCep: %s", cliente[i].endereco.estado, cliente[i].endereco.cidade, cliente[i].endereco.bairro, cliente[i].endereco.logradouro, cliente[i].endereco.numEndereco, cliente[i].endereco.cep);
            }
        }

        printf("\n\n [0]Ver outro cliente\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 void editarCliente(Cliente* cliente){
      int i, a=0, b;
      char op[50], str[8];

    do{

        system("cls");

        printf("-------------------------------------------------EDITAR  CLIENTE-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (C�digo, n�mero do celular, email ou nome do cliente)\n:");
        scanf("%s", op);

        system("cls");
        for(i=0; i<variComCliente; i++){
            sprintf(str, "%d", cliente[i].codigo);
            if(strcmp(op,str) == 0 || strcmp(op, cliente[i].nome) == 0 || strcmp(op, cliente[i].email) || strcmp(op, cliente[i].celular)  == 0){

                printf("\n-Informe qual dado voc� deseja alterar- \n [1]Nome \n [2]Data e nascimento \n  [3]N�mero de celular \n [4]Email \n [5]Endere�o \n:");
                scanf("%d", &b);

                switch(b){
                case 1:
                    system("cls");
                    printf(" Digite o novo nome: ");
                    fflush(stdin);
                    gets(cliente[i].nome);
                    fflush(stdin);
                    break;

                case 2:
                    system("cls");
                    printf("-Digite a nova data de nascimento-");

                    printf("\n Ano:");
                    scanf("%d", &cliente[i].dataCliente.ano);

                    printf("\n M�s:");
                    scanf("%d", &cliente[i].dataCliente.mes);

                    printf("\n Dia:");
                    scanf("%d", &cliente[i].dataCliente.dia);

                    printf(" Esse � a data de nascimento j� alterada:%d/%d/%d", cliente[i].dataCliente.dia, cliente[i].dataCliente.mes, cliente[i].dataCliente.ano);
                    break;

                case 3:
                    system("cls");

                    printf(" DIgite o novo n�mero de celular para contato:");
                    fflush(stdin);
                    gets(cliente[i].celular);
                    fflush(stdin);

                    printf(" Esse � o n�mero de celular para contato j� altearado: %s", cliente[i].celular);
                    break;

                case 4:
                    printf("\n Digite o novo Email:");
                    fflush(stdin);
                    gets(cliente[i].email);
                    fflush(stdin);
                    break;

                case 5:
                    printf("-Digite o novo endere�o-");
                    printf("\nEstado:");
                    fflush(stdin);
                    gets(cliente[i].endereco.estado);
                    fflush(stdin);

                    printf("\nCidade:");
                    fflush(stdin);
                    gets(cliente[i].endereco.cidade);
                    fflush(stdin);

                    printf("\nBairro:");
                    fflush(stdin);
                    gets(cliente[i].endereco.bairro);
                    fflush(stdin);

                    printf("\nRua:");
                    fflush(stdin);
                    gets(cliente[i].endereco.logradouro);
                    fflush(stdin);

                    printf("\nN�mero:");
                    scanf("%d", &cliente[i].endereco.numEndereco);

                    printf("\nCep:");
                    fflush(stdin);
                    gets(cliente[i].endereco.cep);
                    fflush(stdin);

                    system("cls");
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

 void removerCliente(Cliente* cliente){
        int i, a=0;
        char op[50], str[8];

        do{
        system("cls");
        printf("-------------------------------------------------REMOVER CLIENTE-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (C�digo, n�mero do celular, email ou nome do cliente)\n:");
        scanf("%s", op);
        system("cls");

        for(i=0; i<variComAten; i++){
            if(strcmp(op,str) == 0 || strcmp(op, cliente[i].nome) == 0 || strcmp(op, cliente[i].email) || strcmp(op, cliente[i].celular)  == 0){
                memset(cliente[i].celular, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].email, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].nome, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].endereco.bairro, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].endereco.cep, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].endereco.cidade, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].endereco.estado, 0, sizeof(char[TAM_MAX]) );
                memset(cliente[i].endereco.logradouro, 0, sizeof(char[TAM_MAX]) );
                cliente[i].endereco.numEndereco = 0;
                cliente[i].idade = 0;
                cliente[i].codigo = 0;
                cliente[i].dataCliente.ano = 0;
                cliente[i].dataCliente.dia = 0;
                cliente[i].dataCliente.mes = 0;
            }
        }

        printf("\n [0]Remover outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 /*
======Módulo Arquivos======
*/
int abrirArquivo(FILE** arquivo, const char* caminho, const char modo)
{
    if (!(*arquivo))
    {
        fclose(*arquivo);
    }

    if (modo == ARQUIVO_MODO_ESCREVER)
    {
        if((*arquivo = fopen(caminho, "w+")) == NULL)
        {
            printf("Não foi possível criar o arquivo \"%s\" \n", caminho);
            return 0;
        }
        printf("\nO arquivo foi criado com sucesso.\n");
        return 1;
    }
    else
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
    }
    return 1;
}

/*
ARQUIVO ATENDIMENTO
*/

void atualizarRegistroAtendimento(Atendimento* a)
{
    int i = 0;

    fclose(arquivo_atendimento);
    abrirArquivo(&arquivo_atendimento, "regAtendimento.txt", ARQUIVO_MODO_ESCREVER);

    for (i = 0; i < tamVetAten; i++)
    {
        if (a[i].numero != 0)
        {
            registrarAtendimento(&a[i]);
        }

    }

    fclose(arquivo_atendimento);
    abrirArquivo(&arquivo_atendimento, "regAtendimento.txt", ARQUIVO_MODO_LER);
}

void registrarAtendimento(Atendimento *a)
{
    fseek(arquivo_atendimento, 0, SEEK_END);
    if (a->numero)
    {
        fprintf(arquivo_profissao, OUT_ATENDIMENTO_FORMAT, a->matAten, a->numero, a->dataAten.dia, a->dataAten.mes, a->dataAten.ano, a->aten );
    }
    fseek(arquivo_atendimento, 0, SEEK_SET);
}

void alocarRegistroAtendimento(Atendimento* a)
{
    if (tamVetAten != 0)
    {
        int i;
        for (i = 0; i < tamVetAten; i++)
        {
            fscanf(arquivo_profissao, IN_ATENDIMENTO_FORMAT, &a[i].matAten, &a[i].numero, &a[i].dataAten.dia, &a[i].dataAten.mes, &a[i].dataAten.ano, a[i].aten);
            if(a[i].numero == 0)
            {
                i--;
                continue;
            }
        }
    }
    do
    {
        fscanf(arquivo_profissao, IN_ATENDIMENTO_FORMAT, &a[tamVetAten].matAten, &a[tamVetAten].numero, &a[tamVetAten].dataAten.dia,
               &a[tamVetAten].dataAten.mes, &a[tamVetAten].dataAten.ano, a[tamVetAten].aten);
        if(a[tamVetAten].numero == 0)
            break;
        if (variComAten <= a[tamVetAten].numero)
        {
            variComAten = (a[tamVetAten].numero) + 1;
        }
        tamVetAten++;
    } while (1);
}

void gerarAtendimento(Atendimento* a)
{
    int i;
    system("cls");
    for(i=0; i < tamVetProfissao; i++)
    {
        //printf(OUT_PROFISSAO_FORMAT, a[i].codProf, a[i].nomeProf, a[i].siglaProf);
    }
}

/*
ARQUIVO PROFISSÃO
*/

void atualizarRegistroProfissao(Profissao* p)
{
    int i = 0;

    fclose(arquivo_profissao);
    abrirArquivo(&arquivo_profissao, "regProfissao.txt", ARQUIVO_MODO_ESCREVER);

    for (i = 0; i < tamVetProfissao; i++)
    {
        if (p[i].codProf != 0)
        {
            registrarProfissao(&p[i]);
        }

    }

    fclose(arquivo_profissao);
    abrirArquivo(&arquivo_profissao, "regProfissao.txt", ARQUIVO_MODO_LER);
}

void registrarProfissao(Profissao *p)
{
    fseek(arquivo_profissao, 0, SEEK_END);
    if (p->codProf)
    {
        fprintf(arquivo_profissao, OUT_PROFISSAO_FORMAT, p->codProf, p->nomeProf, p->siglaProf );
    }
    fseek(arquivo_profissao, 0, SEEK_SET);
}

void alocarRegistroProfissao(Profissao* p)
{
    if (tamVetProfissao != 0)
    {
        int i;
        for (i = 0; i < tamVetProfissao; i++)
        {
            fscanf(arquivo_profissao, IN_PROFISSAO_FORMAT, &p[i].codProf, p[i].nomeProf, p[i].siglaProf);
            if(p[i].codProf == 0)
            {
                i--;
                continue;
            }
        }
        return;
    }
    do
    {
        fscanf(arquivo_profissao, IN_PROFISSAO_FORMAT, &p[tamVetProfissao].codProf, p[tamVetProfissao].nomeProf, p[tamVetProfissao].siglaProf);
        if(p[tamVetProfissao].codProf == 0)
            break;
        if (variComProfissao <= p[tamVetProfissao].codProf - codBaseProf)
        {
            variComProfissao = (p[tamVetProfissao].codProf - codBaseProf) + 1;
        }
        tamVetProfissao++;
    } while (1);
    return;
}

void gerarProf(Profissao* p)
{
    int i;
    system("cls");
    for(i=0; i < tamVetProfissao; i++)
    {
        printf(OUT_PROFISSAO_FORMAT, p[i].codProf, p[i].nomeProf, p[i].siglaProf);
    }
}
