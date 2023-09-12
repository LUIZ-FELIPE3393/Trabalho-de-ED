#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 512

int variComProfissao = 0; //vari�vel de comando de profiss�o
int tamVetProfissao = 0; //tamanho atual do vetor de profiss�o

int variComProfissional=0; //vari�vel de comando de m�dico
int tamVetProfissional=0;

int variComAten = 0; //vari�vel de comando de atendimento
int tamVetAten = 0; //tamanho atual do vetor de atendimento

int variComCliente = 0; //vari�vel de comando de cliente
int tamVetCliente = 0;


const int codBaseProf = 2023000000;
const int numBaseAten = 2023100000;
const int codBaseProfissional = 2023200000;
const int codBaseCliente = 2023300000;

const char* OUT_PROFISSAO_FORMAT =
    "%d{nome:\"%s\",sigla:%s}\n";

const char* IN_PROFISSAO_FORMAT =
    "%d{nome:\"%[^\"]\",sigla:%[^}]}";

const char* OUT_ATENDIMENTO_FORMAT =
    "%d{matricula:\"%d\",cliente:\"%d\",data:%d/%d/%d,descricao:\"%s\"}\n";

const char* IN_ATENDIMENTO_FORMAT =
    "%d{matricula:\"%d\",cliente:\"%d\",data:%d/%d/%d,descricao:\"%[^\"]\"}\n";

const char* OUT_PROFISSIONAL_FORMAT =
    "%d{cpf:\"%s\",nome:\"%s\",codProf:\"%d\",numRegP:\"%d\",dataNasc:%d/%d/%d,email:\"%s\",fone:%s}\n";

const char* IN_PROFISSIONAL_FORMAT =
    "%d{cpf:\"%[^\"]\",nome:\"%[^\"]\",codProf:\"%d\",numRegP:\"%d\",dataNasc:%d/%d/%d,email:\"%[^\"]\",fone:%[^}]}\n";

const char* OUT_CLIENTE_FORMAT =
    "%d{nome:\"%s\",dataNasc:%d/%d/%d,idade:%d,email:\"%s\",fone:%s,celular:%s,logradouro:\"%s\",numero:%d,bairro:\"%s\",cidade:\"%s\","
    "estado:\"%s\",CEP:\"%s\"}\n";

const char* IN_CLIENTE_FORMAT =
    "%d{nome:\"%[^\"]\",dataNasc:%d/%d/%d,idade:%d,email:\"%[^\"]\",fone:%[^,],celular:%[^,],logradouro:\"%[^\"]\","
    "numero:%d,bairro:\"%[^\"]\",cidade:\"%[^\"]\",estado:\"%[^\"]\",CEP:\"%[^\"]\"}\n";


FILE* arquivo_cliente = NULL;
FILE* arquivo_profissao = NULL;
FILE* arquivo_atendimento = NULL;
FILE* arquivo_profissional = NULL;
FILE* arquivo_log = NULL;

const char ARQUIVO_MODO_ESCREVER = 0;
const char ARQUIVO_MODO_LER = 1;

typedef struct{
    int dia, mes, ano;
}Data;

typedef struct{
    char logradouro[30], bairro[30], cidade[30], estado[20], cep[10];
    unsigned int numEndereco;
}Endereco;

typedef struct{
    unsigned int codProf;
    char nomeProf[50], siglaProf[10];
}Profissao;

typedef struct{
    char cpf[11], nome[50], email[50], tipo[50], fone[15];
    unsigned int  numRegP, matricula, codProf;
    Data dataNasc;
}Profissional;

typedef struct{
    char nome[50], email[50], celular[15], fone[15];
    unsigned int idade, codigo;
    Data dataNasc;
    Endereco endereco;
}Cliente;

typedef struct{
    unsigned int numero, matAten, codClien;
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

void gerarProfissional(Profissional* p);
void alocarRegistroProfissional(Profissional* p);
void registrarProfissional(Profissional *p);
void atualizarRegistroProfissional(Profissional* p);

void gerarCliente(Cliente* c);
void alocarRegistroCliente(Cliente* c);
void registrarCliente(Cliente *c);
void atualizarRegistroCliente(Cliente* c);

int main(){

    Profissao profissoes [TAM_MAX];
    Profissional profissionais [TAM_MAX];
    Atendimento atendimento [TAM_MAX];
    Cliente cliente[TAM_MAX];

    setlocale(LC_ALL,"");

    abrirArquivo(&arquivo_profissao, "regProfissao.txt", ARQUIVO_MODO_LER);
    abrirArquivo(&arquivo_profissional, "regProfissional.txt", ARQUIVO_MODO_LER);
    abrirArquivo(&arquivo_atendimento, "regAtendimento.txt", ARQUIVO_MODO_LER);
    abrirArquivo(&arquivo_cliente, "regCliente.txt", ARQUIVO_MODO_LER);
    if((arquivo_log = fopen("log.txt", "w")) == NULL)
    {
        printf("N�o foi poss�vel criar o arquivo \"log.txt\" \n");
        return 0;
    }
    alocarRegistroProfissao(profissoes);
    alocarRegistroAtendimento(atendimento);
    alocarRegistroProfissional(profissionais);
    alocarRegistroCliente(cliente);

    int op, a=0;

    do{
        printf("\n--------------------------------------------------------BEM VINDO-------------------------------------------------------\n");
        printf("\nIr para o menu de:\n [1]Profissional\n [2]Cliente\n [3]Atendimento\n [4]Profiss�o\n\n [5]Sair \n\n :");
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
        printf("\n [1]Pesquisar por profissional\n [2]Inserir profissional\n [3]Editar informa��es de um profissional\n [4]Remover profissional\n\n [5]Voltar \n\n :");
        scanf("%d", &op);

        switch(op){
        case 1:
            pesquisarProfissional(profissional);
            break;

        case 2:
            inserirProfissional(profissional);
            break;

        case 3:
            editarProfissional(profissional);
            break;

        case 4:
            removerProfissional(profissional);
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
    int i, op=1;

    while(1){
        system("cls");
        printf("\n---------------------------------------------------INSERIR PROFISS�O---------------------------------------------------\n");
        printf("\nCodigo = %d\n", codBaseProf+variComProfissao);
        printf("\nInserir o nome da profiss�o: ");
        scanf("%s", profissao[tamVetProfissao].nomeProf);

        printf("\nInserir o sigla da profiss�o: ");
        scanf("%s", profissao[tamVetProfissao].siglaProf);

        profissao[tamVetProfissao].codProf = codBaseProf+variComProfissao;
        printf("\nC�digo da profiss�o:%d", profissao[tamVetProfissao].codProf);

        tamVetProfissao++;
        variComProfissao++;
        atualizarRegistroProfissao(profissao);
        printf("\n\n [0]Inserir outra profisss�o\n [1]Voltar\n: ");
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

void pesquisarProfissional(Profissional* profissional){
     int i, ii = 0, a=0;
    char op[50];
    int codigo, eNumero;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISA POR PROFISSIONAL-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (Nome, Cpf, Matrícula ou Registro do Profissional)\n:");
        scanf("%s", op);
        fflush(stdin);
        system("cls");
        eNumero = 1;


        //Verificando se op � n�mero
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

        for(i=0; i<tamVetProfissional; i++){
            //Voc� pode usar atoi para converter uma string para int
            if(codigo == profissional[i].numRegP || codigo == profissional[i].matricula || strcmp(op, profissional[i].nome) == 0 || strcmp(op, profissional[i].cpf) == 0){
                printf("\n Nome do profissional: %s", profissional[i].nome);
                printf("\n Data de nascimento do profissional: %d/%d/%d", profissional[i].dataNasc.dia, profissional[i].dataNasc.mes, profissional[i].dataNasc.ano);
                printf("\n Cpf do profissional: %s", profissional[i].cpf);
                printf("\n Email do profissional: %s", profissional[i].email);
                printf("\n Telefone do profissional: %s", profissional[i].fone);
                printf("\n Profissão do profissional: %s", profissional[i].tipo);
                printf("\n Código da profissão do profissional: %d", profissional[i].codProf);
                printf("\n Cpf do profissional: %s", profissional[i].cpf);
                printf("\n Matrícula do atendimento do profissional: %s", profissional[i].cpf);
                printf("\n Número de registro do profissional: %d", profissional[i].numRegP);
            }
        }

        printf("\n\n [0]Ver outro profissional\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}
void inserirProfissional(Profissional* profissional){
     int i, op=1;
    while(1){
        system("cls");
        printf("\n---------------------------------------------------INSERIR PROFISSIONAL---------------------------------------------------\n");

        //printf("\nCodigo = %d\n", codBaseProf+variComProfissao);

        printf("\nInserir o nome do profissional: ");
        fflush(stdin);
        gets(profissional[tamVetProfissional].nome);
        fflush(stdin);

        printf("\nInserir data de nascimento do profissional: ");
        printf("\nDia:");
        scanf("%d", &profissional[tamVetProfissional].dataNasc.dia);
        printf("\nMês:");
        scanf("%d", &profissional[tamVetProfissional].dataNasc.mes);
        printf("\nAno:");
        scanf("%d", &profissional[tamVetProfissional].dataNasc.ano);

        printf("\nInserir o cpf do profissional: ");
        scanf("%s", profissional[tamVetProfissional].cpf);

        printf("\nInserir o email do profissional: ");
        scanf("%s", profissional[tamVetProfissional].email);

        printf("\nInserir o telefone do profissional: ");
        scanf("%s", profissional[tamVetProfissional].fone);

        printf("\nInserir o tipo do profissional: ");
        scanf("%s", profissional[tamVetProfissional].tipo);

        printf("\nInserir o código da profissão do profisional: ");
        scanf("%d", &profissional[tamVetProfissional].codProf);

        printf("\nInserir o numero de registro profissional do profissional: ");
        scanf("%d", &profissional[tamVetProfissional].numRegP);

        profissional[tamVetProfissional].matricula = codBaseProfissional+variComProfissional;
        printf("\nNpumero de matrícula do profissional:%d", profissional[tamVetProfissional].matricula);

        tamVetProfissional++;
        variComProfissional++;

        atualizarRegistroProfissional(profissional);

        printf("\n\n [0]Inserir outro profissional\n [1]Voltar\n: ");
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
void removerProfissional(Profissional* profissional){
    //a
    int i, ii=0, a=0;
    char op[50], str[8];
    int codigo, eNumero;

    do{
        system("cls");
        printf("-------------------------------------------------REMOVER PROFISSIONAL-------------------------------------------------");
        printf("\nDigita algo para identificar o profissional que você deseja remover (Nome, Cpf, Matrícula ou Registro do Profissional):\n");
        scanf("%s", op);
        system("cls");

        eNumero = 1;

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

        for(i=0; i<tamVetProfissional; i++){
            //Voc� pode usar atoi para converter uma string para int
            if(codigo == profissional[i].numRegP || codigo == profissional[i].matricula || strcmp(op, profissional[i].nome) == 0 || strcmp(op, profissional[i].cpf) == 0){
                memset(profissional[i].cpf, 0, sizeof(char[11]));
                memset(profissional[i].nome, 0, sizeof(char[50]));
                memset(profissional[i].email, 0, sizeof(char[50]));
                memset(profissional[i].tipo, 0,sizeof(char[50]));
                memset(profissional[i].fone, 0,sizeof(char[15]));
                profissional[i].numRegP = 0;
                profissional[i].matricula = 0;
                profissional[i].codProf = 0;
                profissional[i].dataNasc.dia = 0;
                profissional[i].dataNasc.mes = 0;
                profissional[i].dataNasc.ano = 0;

                atualizarRegistroProfissional(profissional);
                tamVetProfissional--;
                alocarRegistroProfissional(profissional);
                break;
            }
        }
        printf("\n\n [0]Remover outro profissional\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void editarProfissional(Profissional* profissional){
    int i, ii = 0, a=0, opcao;
    char op[50], str[8];
    int codigo, eNumero;

    do{
        system("cls");
        printf("------------------------------------------------EDITAR PROFISSIONAL-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (Nome, Cpf, Matrícula ou Registro do Profissional)\n:");
        fflush(stdin);
        scanf("%s", op);
        system("cls");

        eNumero = 1;
        codigo = 0;

        //Verificando se op � n�mero
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

        for(i=0; i<tamVetProfissional; i++){
            if(codigo == profissional[i].numRegP || codigo == profissional[i].matricula || strcmp(op, profissional[i].nome) == 0 || strcmp(op, profissional[i].cpf) == 0){
                printf("\nInforme qual dado você deseja alterar \n[1]Nome \n[2]CPF \n[3]E-mail \n[4]Número de Telefone \n[5]Data de nascimento \n[6]Tipo de Profissão \n[7]Número de Registro \n[8]Código de profissão \n[9]Voltar\n:");
                scanf("%d", &opcao);

                switch(opcao){
                case 1:
                    system("cls");
                    printf("Digite o novo nome:");
                    scanf("%s", &profissional[i].nome);
                    printf("Esse � o nome j� alterado:%s", profissional[i].nome);
                    i = tamVetProfissional;
                    break;

                case 2:
                    system("cls");
                    printf("Digite o novo CPF:");
                    scanf("%s", &profissional[i].cpf);
                    printf("Esse é o novo CPF regsitrado:%s", profissional[i].cpf);
                    i = tamVetProfissional;
                    break;

                case 3:
                    system("cls");
                	printf("Digite novo e-mail:");
                	scanf("%s", &profissional[i].email);
                	printf("Esse � o novo e-mail registrado:%s", profissional[i].email);
                	i = tamVetProfissional;
                	break;

                case 4:
                    system("cls");
                	printf("Digite o novo n�mero de telefone:");
                	scanf("%s", &profissional[i].fone);
                	printf("Esse � o n�mero de celular novo:%s", profissional[i].fone);
                    i = tamVetProfissional;
                    break;

                case 5:
                    system("cls");
                    printf("\n Digite a nova data de nascimento:");
                
                    printf("\n Ano:");
                    scanf("%d", &profissional[i].dataNasc.ano);

                    printf("\nMês:");
                    scanf("%d", &profissional[i].dataNasc.mes);

                    printf("\n Dia:");
                    scanf("%d", &profissional[i].dataNasc.dia);

                    printf("\nEssa é a data de nascimento alterada:%d/%d/%d", profissional[i].dataNasc.dia, profissional[i].dataNasc.mes, profissional[i].dataNasc.ano);
                    break;

                case 6:
                    system("cls");
                    printf("Digite a nova profissão:");
                    scanf("%s", &profissional[i].tipo);
                    printf("\nEssa é a profissão alterada: %s", profissional[i].tipo);
                    break;
                
                case 7:
                system("cls");
                printf("Digite o novo número de registro:");
                scanf("%s", &profissional[i].numRegP);
                printf("\nEsse é o número de registro alterado:%s", profissional[i].numRegP);
                break;

                case 8:
                system("cls");
                printf("Digite o novo código de profissão:");
                scanf("%d", &profissional[i].codProf);
                printf("\nEsse é o novo código de profissão:%d", profissional[i].codProf);
                break;

                case 9:
                    break;
                default:
                    system("cls");
                    continue;
                }
                atualizarRegistroProfissional(profissional);

            }
        }

        printf("\n\n [0]Ver outra profisss�o\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void pesquisarProf(Profissao* profissao){
    int i, ii = 0, a=0;
    char op[50];
    int codigo, eNumero;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISA POR PROFISS�O-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (Nome, Sigla ou C�digo da Profiss�o)\n:");
        scanf("%s", op);
        fflush(stdin);
        system("cls");
        eNumero = 1;

        //Verificando se op � n�mero
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
            //Voc� pode usar atoi para converter uma string para int
            if(strcmp(op, profissao[i].nomeProf) == 0 || codigo == profissao[i].codProf || strcmp(op, profissao[i].siglaProf) == 0){
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
    int i, ii = 0, a=0;
    char op[50], str[8];
    int codigo, eNumero;

    do{
        system("cls");
        printf("-------------------------------------------------REMOVER PROFISS�O-------------------------------------------------");
        printf("\nDigita algo para a identificar a profiss�o que voc� deseja remover (Nome, Sigla ou C�digo da Profiss�o)\n:");
        scanf("%s", op);
        system("cls");

        eNumero = 1;

        //Verificando se op � n�mero
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
            //Voc� pode usar atoi para converter uma string para int
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
        printf("\n\n [0]Ver outra profisss�o\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void editarProf(Profissao* profissao){
   int i, ii = 0, a=0, opcao;
    char op[50], str[8];
    int codigo, eNumero;

    do{
        system("cls");
        printf("------------------------------------------------EDITAR PROFISS�O-------------------------------------------------");
        printf("\nDigita algo para a identificar a profiss�o que voc� deseja editar (Nome, Sigla ou C�digo da Profiss�o)\n:");
        fflush(stdin);
        scanf("%s", op);
        system("cls");

        eNumero = 1;
        codigo = 0;

        //Verificando se op � n�mero
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
                printf("\nInforme qual dado voc� deseja alterar \n[1]Nome \n[2]Sigla \n[3]Voltar\n:");
                scanf("%d", &opcao);

                switch(opcao){
                case 1:
                    printf("Digite o novo nome da profiss�o:");
                    scanf("%s", profissao[i].nomeProf);
                    printf("Esse � o nome j� alterado:%s", profissao[i].nomeProf);
                    i = tamVetProfissao;
                    break;
                case 2:
                    printf("Digite a nova sigla da profiss�o:");
                    scanf("%s", profissao[i].siglaProf);
                    printf("Esse � a sigla j� alterada:%s", profissao[i].siglaProf);
                    i = tamVetProfissao;
                    break;
                case 3:
                    break;
                default:
                    system("cls");
                    continue;
                }
                atualizarRegistroProfissao(profissao);

            }
        }

        printf("\n\n [0]Ver outra profisss�o\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

 void pesquisarAten(Atendimento* atendimento){
    int i, a=0, op;
    int eNumero, codigo;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISAR POR ATENDIMENTO-------------------------------------------------");

        printf("\nDigita algo para a pesquisa (Matr�cula ou n�mero do atendimento)\n:");
        scanf("%d", &op);

        system("cls");

        for(i = 0; i < tamVetAten; i++){
            if(op == atendimento[i].matAten || op == atendimento[i].numero){
                printf("\n Data do atendimento: %d/%d/%d", atendimento[i].dataAten.dia, atendimento[i].dataAten.mes, atendimento[i].dataAten.ano);
                printf("\n Atendimento:\n %s\n", atendimento[i].aten);
                printf("\n Matr�cula do atendimento: %d", atendimento[i].matAten);
                printf("\n N�mero do atendimento: %d", atendimento[i].numero);
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

        printf("\n M�s:");
        scanf("%d", &atendimento[tamVetAten].dataAten.mes);

        printf("\n Dia:");
        scanf("%d", &atendimento[tamVetAten].dataAten.dia);

        system("cls");

        printf("Sobre o atendimento (Max 500 caracteres)\n:");
        fflush(stdin);
        gets(atendimento[tamVetAten].aten);
        fflush(stdin);

        system("cls");

        printf("Matr�cula do profissional:");
        scanf("%ld", &atendimento[tamVetAten].matAten);

        printf("C�digo do cliente:");
        scanf("%ld", &atendimento[tamVetAten].codClien);

        atendimento[tamVetAten].numero = variComAten + numBaseAten;
        printf("\n N�mero do atendimento: %d", atendimento[tamVetAten].numero);

        tamVetAten++;
        variComAten++;
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

        for(i=0; i<tamVetAten; i++){
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
                    i = tamVetAten;
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
                    i = tamVetAten;
                    break;
                default:
                    system("cls");
                    continue;
                }
                atualizarRegistroAtendimento(atendimento);
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

        for(i=0; i<tamVetAten; i++){
            if(op==atendimento[i].matAten||op==atendimento[i].numero){
                memset(atendimento[i].aten, 0, sizeof(char[TAM_MAX]) );
                atendimento[i].matAten = 0;
                atendimento[i].numero = 0;
                atendimento[i].dataAten.ano = 0;
                atendimento[i].dataAten.dia = 0;
                atendimento[i].dataAten.mes = 0;
                atualizarRegistroAtendimento(atendimento);
                tamVetAten--;
                alocarRegistroAtendimento(atendimento);
                break;

            }
        }

        printf("\n [0]Remover outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
}

void inserirCliente(Cliente* cliente){
    int  i, op=1;

    do
    {
        system("cls");
        printf("\n--------------------------------------------------INSERIR CLIENTE--------------------------------------------------\n");

        printf("\n:-Cadastro do cliente-\n");

        printf("\n Nome:");
        fflush(stdin);
        gets(cliente[tamVetCliente].nome);
        fflush(stdin);

        printf("\n Idade:");
        scanf("%d", &cliente[tamVetCliente].idade);

        printf("\n Email:");
        fflush(stdin);
        gets(cliente[tamVetCliente].email);
        fflush(stdin);

        printf("\n Telefone para contato:");
        fflush(stdin);
        gets(cliente[tamVetCliente].fone);
        fflush(stdin);

        printf("\n Celular para contato:");
        fflush(stdin);
        gets(cliente[tamVetCliente].celular);
        fflush(stdin);

        system("cls");

        printf("-Data de nascimento-");
        printf("\n Ano:");
        scanf("%d", &cliente[tamVetCliente].dataNasc.ano);

        printf("\n M�s:");
        scanf("%d", &cliente[tamVetCliente].dataNasc.mes);

        printf("\n Dia:");
        scanf("%d", &cliente[tamVetCliente].dataNasc.dia);

        system("cls");

        printf("-Endere�o-");
        printf("\nEstado:");
        fflush(stdin);
        gets(cliente[tamVetCliente].endereco.estado);
        fflush(stdin);

        printf("\nCidade:");
        fflush(stdin);
        gets(cliente[tamVetCliente].endereco.cidade);
        fflush(stdin);

        printf("\nBairro:");
        fflush(stdin);
        gets(cliente[tamVetCliente].endereco.bairro);
        fflush(stdin);

        printf("\nRua:");
        fflush(stdin);
        gets(cliente[tamVetCliente].endereco.logradouro);
        fflush(stdin);

        printf("\nN�mero:");
        scanf("%d", &cliente[tamVetCliente].endereco.numEndereco);

        printf("\nCep:");
        fflush(stdin);
        gets(cliente[tamVetCliente].endereco.cep);
        fflush(stdin);

        system("cls");

        cliente[tamVetCliente].codigo = codBaseCliente+variComCliente;
        printf("\n C�digo do cliente: %d", cliente[tamVetCliente].codigo);

        tamVetCliente++;
        variComCliente++;
        atualizarRegistroCliente(cliente);

        printf("\n\n [0]Inserir outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &op);

        if(op==1){
            break;
        }
        else{
            system("cls");
            continue;
        }

    } while(1);
}

void pesquisarCliente(Cliente* cliente){
    int i, ii = 0, a=0;
    char op[50], str[9];
    int eNumero, codigo;

    do{
        system("cls");
        printf("-------------------------------------------------PESQUISAR POR CLIENTE-------------------------------------------------");

        printf("\nDigita algo para a pesquisa (C�digo, n�mero do celular, email ou nome do cliente)\n:");
        fflush(stdin);
        scanf("%[^\n]", op);
        fflush(stdin);
        system("cls");
        eNumero = 1;

        //Verificando se op � n�mero
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

        for(i=0; i<tamVetCliente; i++)
        {
            if(codigo == cliente[i].codigo || strcmp(op, cliente[i].nome) == 0 || strcmp(op, cliente[i].email) == 0 || strcmp(op, cliente[i].celular)  == 0)
            {
                printf("\nNome: %s", cliente[i].nome);
                printf("\nIdade: %d", cliente[i].idade);
                printf("\nData de nascimento: %d/%d/%d", cliente[i].dataNasc.dia, cliente[i].dataNasc.mes, cliente[i].dataNasc.ano);
                printf("\nTelefone de contato: %s", cliente[i].fone);
                printf("\nCelular de contato: %s", cliente[i].celular);
                printf("\nEmail: %s", cliente[i].email);
                printf("\n\nEstado: %s\nCidade: %s\nBairro: %s\nRua: %s\nN�mero da casa: %d\nCep: %s", cliente[i].endereco.estado,
                    cliente[i].endereco.cidade, cliente[i].endereco.bairro, cliente[i].endereco.logradouro, cliente[i].endereco.numEndereco,
                    cliente[i].endereco.cep);
            }
        }

        printf("\n\n [0]Ver outro cliente\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 void editarCliente(Cliente* cliente){
      int i, ii = 0, a=0, b;
      char op[50], str[8];
      int eNumero, codigo;

    do{

        system("cls");

        printf("-------------------------------------------------EDITAR  CLIENTE-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (C�digo, n�mero do celular, email ou nome do cliente)\n:");
        fflush(stdin);
        scanf("%[^\n]", op);
        fflush(stdin);
        system("cls");

        eNumero = 1;

        //Verificando se op � n�mero
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

        for(i=0; i<tamVetCliente; i++){
            if(codigo == cliente[i].codigo || strcmp(op, cliente[i].nome) == 0 || strcmp(op, cliente[i].email) == 0 || strcmp(op, cliente[i].celular) == 0) {

                printf("\n-Informe qual dado voc� deseja alterar- \n [1]Nome \n [2]Data de nascimento \n  [3]N�mero de celular \n [4]Email \n [5]Endere�o \n:");
                scanf("%d", &b);

                switch(b){
                case 1:
                    system("cls");
                    printf("\nDigite o novo nome:");
                    fflush(stdin);
                    gets(cliente[i].nome);
                    fflush(stdin);
                    break;

                case 2:
                    system("cls");
                    printf("\nDigite a nova data de nascimento:");

                    printf("\n Ano:");
                    scanf("%d", &cliente[i].dataNasc.ano);

                    printf("\n M�s:");
                    scanf("%d", &cliente[i].dataNasc.mes);

                    printf("\n Dia:");
                    scanf("%d", &cliente[i].dataNasc.dia);

                    printf(" Essa � a data de nascimento j� alterada:%d/%d/%d", cliente[i].dataNasc.dia, cliente[i].dataNasc.mes, cliente[i].dataNasc.ano);
                    break;

                case 3:
                    system("cls");

                    printf("\n Digite o novo n�mero de celular para contato:");
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
                    printf("\n Digite o novo endere�o:");
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
                atualizarRegistroCliente(cliente);
            }
        }

        printf("\n\n [0]Editar outro cliente\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 void removerCliente(Cliente* cliente){
        int i, ii = 0, a=0;
        char op[50];
        int codigo, eNumero;

        do{
        system("cls");
        printf("-------------------------------------------------REMOVER CLIENTE-------------------------------------------------");
        printf("\nDigita algo para a pesquisa (C�digo, n�mero do celular, email ou nome do cliente)\n:");
        fflush(stdin);
        scanf("%[^\n]", op);
        fflush(stdin);
        system("cls");

        eNumero = 1;

        //Verificando se op � n�mero
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

        for(i=0; i<tamVetCliente; i++){
            if(codigo == cliente[i].codigo || strcmp(op, cliente[i].nome) == 0 || strcmp(op, cliente[i].email) == 0|| strcmp(op, cliente[i].celular) == 0)
            {
                memset(cliente[i].celular, 0, sizeof(char[15]) );
                memset(cliente[i].fone, 0, sizeof(char[15]) );
                memset(cliente[i].email, 0, sizeof(char[50]) );
                memset(cliente[i].nome, 0, sizeof(char[50]) );
                memset(cliente[i].endereco.bairro, 0, sizeof(char[30]) );
                memset(cliente[i].endereco.cep, 0, sizeof(char[10]) );
                memset(cliente[i].endereco.cidade, 0, sizeof(char[30]) );
                memset(cliente[i].endereco.estado, 0, sizeof(char[20]) );
                memset(cliente[i].endereco.logradouro, 0, sizeof(char[30]) );
                cliente[i].endereco.numEndereco = 0;
                cliente[i].idade = 0;
                cliente[i].codigo = 0;
                cliente[i].dataNasc.ano = 0;
                cliente[i].dataNasc.dia = 0;
                cliente[i].dataNasc.mes = 0;

                atualizarRegistroCliente(cliente);
                tamVetCliente--;
                alocarRegistroCliente(cliente);
                break;
            }
        }

        printf("\n [0]Remover outro atendimento\n [1]Voltar\n: ");
        scanf("%d", &a);

    }while(a<1);
 }

 /*
======M�dulo Arquivos======
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
            printf("N�o foi poss�vel criar o arquivo \"%s\" \n", caminho);
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
                printf("N�o foi poss�vel abrir o arquivo \"%s\" \n", caminho);
                printf("Deseja criar um novo? (S/N)\n");
                char opcao;
                scanf("%c", &opcao);

                if (opcao == 's' || opcao == 'S')
                {
                    if((*arquivo = fopen(caminho, "w+")) == NULL)
                    {
                        printf("N�o foi poss�vel criar o arquivo \"%s\" \n", caminho);
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

    //Abrir arquivo no modo escrita
    fclose(arquivo_atendimento);
    abrirArquivo(&arquivo_atendimento, "regAtendimento.txt", ARQUIVO_MODO_ESCREVER);

    for (i = 0; i < tamVetAten; i++)
    {
        //Registrar todos os registros na mem�ria
        if (a[i].numero != 0)
        {
            registrarAtendimento(&a[i]);
        }

    }

    //De volta ao modo leitura
    fclose(arquivo_atendimento);
    abrirArquivo(&arquivo_atendimento, "regAtendimento.txt", ARQUIVO_MODO_LER);
}

void registrarAtendimento(Atendimento *a)
{
    //Inserir no fim do arquivo
    fseek(arquivo_atendimento, 0, SEEK_END);
    if (a->numero)
    {
        //Registra uma entrada no formato especificado
        fprintf(arquivo_atendimento, OUT_ATENDIMENTO_FORMAT, a->numero, a->matAten, a->codClien,
            a->dataAten.dia, a->dataAten.mes, a->dataAten.ano, a->aten );
    }
    //Ler a partir do in�cio do arquivo
    fseek(arquivo_atendimento, 0, SEEK_SET);
}

void alocarRegistroAtendimento(Atendimento* a)
{
    //Caso N�O seja a primeira vez que se aloca registros no tempo de execu��o
    if (tamVetAten != 0)
    {
        int i;
        for (i = 0; i < tamVetAten; i++)
        {
            //Insere os valores da entrada no arquivo para as vari�veis de um registro
            fscanf(arquivo_atendimento, IN_ATENDIMENTO_FORMAT, &a[i].numero, &a[i].matAten, &a[i].codClien,
                &a[i].dataAten.dia, &a[i].dataAten.mes, &a[i].dataAten.ano, a[i].aten);
            if(a[i].numero == 0)
            {
                i--;
                continue;
            }
        }
        return;
    }
    //Caso seja a primeira vez que se aloca registros no tempo de execu��o
    do
    {
        //Insere os valores da entrada no arquivo para as vari�veis de um registro
        fscanf(arquivo_atendimento, IN_ATENDIMENTO_FORMAT, &a[tamVetAten].numero, &a[tamVetAten].matAten, &a[tamVetAten].codClien,
            &a[tamVetAten].dataAten.dia, &a[tamVetAten].dataAten.mes, &a[tamVetAten].dataAten.ano, a[tamVetAten].aten);
        if(a[tamVetAten].numero == 0)
            break;
        if (variComAten <= a[tamVetAten].numero - numBaseAten)
        {
            //P�e a vari�vel de comando no valor correto
            variComAten = (a[tamVetAten].numero - numBaseAten) + 1;
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
ARQUIVO PROFISS�O
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


/*
ARQUIVO PROFISSIONAL
*/

void gerarProfissional(Profissional* p)
{
    /*int i;
    system("cls");
    for(i=0; i < tamVetProfissao; i++)
    {
        printf(OUT_PROFISSAO_FORMAT, p[i].codProf, p[i].nomeProf, p[i].siglaProf);
    }*/
}

void alocarRegistroProfissional(Profissional* p)
{
    if (tamVetProfissional != 0)
    {
        int i;
        for (i = 0; i < tamVetProfissional; i++)
        {
            fscanf(arquivo_profissional, IN_PROFISSIONAL_FORMAT, &p[i].matricula, p[i].cpf, p[i].nome, &p[i].codProf, &p[i].numRegP, &p[i].dataNasc.dia,
                &p[i].dataNasc.mes, &p[i].dataNasc.ano, p[i].email, p[i].fone);
            if(p[i].matricula == 0)
            {
                i--;
                continue;
            }
        }
        return;
    }
    do
    {
        //"%d{cpf:\"%[^\"]\",nome:\"%[^\"]\",codProf:\"%d\",numRegP:\"%d\",dataNasc:%d/%d/%d,email:\"%[^\"]\",fone:%[^}]}\n";
        fscanf(arquivo_profissional, IN_PROFISSIONAL_FORMAT, &p[tamVetProfissional].matricula, p[tamVetProfissional].cpf, p[tamVetProfissional].nome,
            &p[tamVetProfissional].codProf, &p[tamVetProfissional].numRegP, &p[tamVetProfissional].dataNasc.dia,
            &p[tamVetProfissional].dataNasc.mes, &p[tamVetProfissional].dataNasc.ano, p[tamVetProfissional].email, p[tamVetProfissional].fone);

        if(p[tamVetProfissional].matricula == 0)
            break;

        if (variComProfissional <= p[tamVetProfissional].matricula - codBaseProfissional)
        {
            variComProfissional = (p[tamVetProfissional].matricula - codBaseProfissional) + 1;
        }
        tamVetProfissional++;
    } while (1);
    return;
}

void registrarProfissional(Profissional *p)
{
    fseek(arquivo_profissional, 0, SEEK_END);
    if (p->matricula)
    {
        fprintf(arquivo_profissional, OUT_PROFISSIONAL_FORMAT, p->matricula, p->cpf, p->nome, p->codProf, p->numRegP, p->dataNasc.dia,
            p->dataNasc.mes, p->dataNasc.ano, p->email, p->fone);
    }
    fseek(arquivo_profissional, 0, SEEK_SET);
}

void atualizarRegistroProfissional(Profissional* p)
{
    int i = 0;

    fclose(arquivo_profissional);
    abrirArquivo(&arquivo_profissional, "regProfissional.txt", ARQUIVO_MODO_ESCREVER);

    for (i = 0; i < tamVetProfissional; i++)
    {
        if (p[i].matricula != 0)
        {
            registrarProfissional(&p[i]);
        }

    }

    fclose(arquivo_profissional);
    abrirArquivo(&arquivo_profissional, "regProfissional.txt", ARQUIVO_MODO_LER);
}

/*
ARQUIVO CLIENTE
*/

void gerarCliente(Cliente* c)
{

}

void alocarRegistroCliente(Cliente* c)
{
    if (tamVetCliente != 0)
    {
        int i;
        for (i = 0; i < tamVetCliente; i++)
        {
            //"%d{nome:\"%s\",dataNasc:%d/%d/%d,idade:%d,email:%s,fone:%s,celular:%s,logradouro:%s,numero:%d,bairro:%s,cidade:%s,estado:%s,CEP:%s}\n"
            fscanf(arquivo_cliente, IN_CLIENTE_FORMAT, &c[i].codigo, c[i].nome, &c[i].dataNasc.dia, &c[i].dataNasc.mes, &c[i].dataNasc.ano,
                &c[i].idade, c[i].email, c[i].fone, c[i].celular, c[i].endereco.logradouro, &c[i].endereco.numEndereco, c[i].endereco.bairro,
                c[i].endereco.cidade, c[i].endereco.estado, c[i].endereco.cep);
            if(c[i].codigo == 0)
            {
                i--;
                continue;
            }
        }
        return;
    }
    do
    {
        fscanf(arquivo_cliente, IN_CLIENTE_FORMAT, &c[tamVetCliente].codigo, c[tamVetCliente].nome, &c[tamVetCliente].dataNasc.dia,
                &c[tamVetCliente].dataNasc.mes, &c[tamVetCliente].dataNasc.ano, &c[tamVetCliente].idade, c[tamVetCliente].email,
                c[tamVetCliente].fone, c[tamVetCliente].celular, c[tamVetCliente].endereco.logradouro, &c[tamVetCliente].endereco.numEndereco,
                c[tamVetCliente].endereco.bairro, c[tamVetCliente].endereco.cidade, c[tamVetCliente].endereco.estado, c[tamVetCliente].endereco.cep);

        if(c[tamVetCliente].codigo == 0)
            break;

        if (variComCliente <= c[tamVetCliente].codigo - codBaseCliente)
        {
            variComCliente = (c[tamVetCliente].codigo - codBaseCliente) + 1;
        }
        tamVetCliente++;
    } while (1);
    return;
}

void registrarCliente(Cliente *c)
{
    fseek(arquivo_cliente, 0, SEEK_END);
    if (c->codigo)
    {
        fprintf(arquivo_cliente, OUT_CLIENTE_FORMAT, c->codigo, c->nome, c->dataNasc.dia, c->dataNasc.mes, c->dataNasc.ano,
                c->idade, c->email, c->fone, c->celular, c->endereco.logradouro, c->endereco.numEndereco, c->endereco.bairro,
                c->endereco.cidade, c->endereco.estado, c->endereco.cep);
    }
    fseek(arquivo_cliente, 0, SEEK_SET);
}

void atualizarRegistroCliente(Cliente* c)
{
    int i = 0;

    fclose(arquivo_cliente);
    abrirArquivo(&arquivo_cliente, "regCliente.txt", ARQUIVO_MODO_ESCREVER);

    for (i = 0; i < tamVetCliente; i++)
    {
        if (c[i].codigo != 0)
        {
            registrarCliente(&c[i]);
        }

    }

    fclose(arquivo_cliente);
    abrirArquivo(&arquivo_cliente, "regCliente.txt", ARQUIVO_MODO_LER);
}
