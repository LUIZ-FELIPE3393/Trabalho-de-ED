#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 512

int variComProfissao = 0; //variavel de comando da profiss�o
int tamVetProfissao = 0; //tamanho atual do vetor de profissao
int variComProfissional=1; //variavel de comando de medico
int variComAten=1; //variavel de comando de atendimento

const long codBaseProfissao = 2023000000;

const char* OUT_PROFISSAO_FORMAT =
    "%d{nome:\"%s\",sigla:%s}\n";

const char* IN_PROFISSAO_FORMAT =
    "%d{nome:\"%[^\"]\",sigla:%[^}]}";

FILE* arquivo_profissao = NULL;
FILE* arquivo_log = NULL;

const char ARQUIVO_MODO_ESCREVER = 0;
const char ARQUIVO_MODO_LER = 1;


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

int abrirArquivo(FILE** arquivo, const char* caminho, const char modo);
void gerarProf(Profissao* profissao);
void alocarRegistrosProfissao(Profissao* p);
int lerRegistroProfissao(Profissao* p, long* pos);
void registrarProfissao(Profissao *p);
void atualizarRegistroProfissao(Profissao* p);


int main(){

    Profissao profissoes [TAM_MAX];
    Profissional profissionais [TAM_MAX];
    Atendimento atendimento [TAM_MAX];

    setlocale(LC_ALL,"Portuguese");

    abrirArquivo(&arquivo_profissao, "regProfissao.txt", ARQUIVO_MODO_LER);
    if((arquivo_log = fopen("log.txt", "w")) == NULL)
    {
        printf("Não foi possível criar o arquivo \"log.txt\" \n");
        return 0;
    }
    alocarRegistrosProfissao(profissoes);

    int i, op, a=0;

    do{
        printf("varComProfissao: %d\n", variComProfissao); //REMOVA-ME
        printf("tamVetProfissao: %d\n", tamVetProfissao); //REMOVA-ME
        for (i = 0; i < tamVetProfissao; i++)
        {
            printf("\n%d %s %s",profissoes[i].codProf, profissoes[i].nomeProf, profissoes[i].siglaProf);
        }
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
    int i, op=1;

    while(1){
        system("cls");
        printf("\n---------------------------------------------------INSIRIR PROFISSÃO---------------------------------------------------\n");
        printf("\nCodigo = %d\n", codBaseProfissao+variComProfissao);
        printf("\nInserir o nome da profissão: ");
        scanf("%s", profissao[tamVetProfissao].nomeProf);

        printf("\nInserir o sigla da profissão: ");
        scanf("%s", profissao[tamVetProfissao].siglaProf);

        profissao[tamVetProfissao].codProf = codBaseProfissao+variComProfissao;
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
                variComProfissao = profissao[i].codProf - codBaseProfissao;
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
                alocarRegistrosProfissao(profissao);
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
                alocarRegistrosProfissao(profissao);
                
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

/*
======Módulo Arquivos======
*/

void atualizarRegistroProfissao(Profissao* p)
{
    int i = 0, c;
    int codProf;
    char lbuffer[256];
    char nome[50], sigla[10];

    fclose(arquivo_profissao);
    abrirArquivo(&arquivo_profissao, "regProfissao.txt", ARQUIVO_MODO_ESCREVER);

    for (i = 0; i < tamVetProfissao; i++)
    {
        if (p[i].codProf != 0)
        {
            registrarProfissao(&p[i]);
            printf("Profissao %d %s %s foi registrada!\n", p[i].codProf, p[i].nomeProf, p[i].siglaProf);
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

int lerRegistroProfissao(Profissao* p, long* pos)
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
        return 0;
    }
    do
    {
        fscanf(arquivo_profissao, IN_PROFISSAO_FORMAT, &p[tamVetProfissao].codProf, p[tamVetProfissao].nomeProf, p[tamVetProfissao].siglaProf);
        if(p[tamVetProfissao].codProf == 0)
            break;
        if (variComProfissao <= p[tamVetProfissao].codProf - codBaseProfissao)
        {
            variComProfissao = (p[tamVetProfissao].codProf - codBaseProfissao) + 1;
        }   
        tamVetProfissao++;
    } while (1);
    return 0;
}

void alocarRegistrosProfissao(Profissao* p)
{
    long pos = 0;
    memset(p, 0, sizeof(p));
    printf("\n====================================\n");
    lerRegistroProfissao(p, &pos);
}

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

void gerarProf(Profissao* profissao)
{
    int i;
    system("cls");
    for(i=0; i < tamVetProfissao; i++)
    {
        printf(OUT_PROFISSAO_FORMAT, profissao[i].codProf, profissao[i].nomeProf, profissao[i].siglaProf);
    }
}
