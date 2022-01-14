#define _CRT_SECURE_NO_WARNINGS

#include "Clientes.h"

// ------------------------------------------------------------
extern void limparbuffer();
extern void pausa();
// ------------------------------------------------------------
void logIT(const char *logs);
// ------------------------------------------------------------
extern NodeR *idRequisitante(Lista *L);
extern Freguesias *atualizarFreguesias(Freguesias *info, Requisitantes *infoR);
// ------------------------------------------------------------
extern void removerElementoR(Lista *L, NodeR *P_REMOVER);
// ------------------------------------------------------------
extern void mostrarCriadores();
// ------------------------------------------------------------

// Funcao que mostra o menu dos clientes
int menuDeClientes()
{
    int mani = 0;
    printf("\n|| Bem Vindo ao menu do Cliente | Voce deseja:");
    printf("\n|| 1 - Fazer uma avaliacao (Sao gravadas automaticamente em um ficheiro)");
    printf("\n|| 2 - Mudar dados de um requisitante");
    printf("\n|| Digite aqui sua opcao (0 para voltar ao menu principal): ");
    scanf("%d", &mani);
    return mani;
}

// Funcao que grava em um ficheiro a avaliacao feita
void gravarAvaliacao(Avaliacao *info)
{
    FILE *file = fopen("Avaliacoes.txt", "a");
    if (!file)
    {
        logIT("ERROR 22 - File avaliacoes nao existe, criando novo");
        fclose(file);
        file = fopen("Avaliacoes.txt", "w");
        if (!file)
        {
            logIT("ERROR 23 - File avaliacoes nao criado, abortando operacao");
            return;
        }
    }
    fprintf(file, "\n|| Avaliacao do dia %d/%d/%d", info->diaDaAvaliacao.dia, info->diaDaAvaliacao.mes, info->diaDaAvaliacao.ano);
    fprintf(file, "\n|| Nome do avaliador: %s", info->nomeDoAvaliador);
    fprintf(file, "\n|| Avaliacao %f", info->valor);
    fprintf(file, "\n|| Descricao da avaliacao: %s", info->descricao);
    fclose(file);
}

// Funcao que libera a avaliacao
void freeAvaliacao(Avaliacao *info)
{
    free(info->descricao);
    free(info->nomeDoAvaliador);
    free(info);
}

// Funcao onde o utilizador faz a avaliacao
void fazerAvaliacao()
{
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    Avaliacao *info = (Avaliacao *)malloc(sizeof(Avaliacao));
    if (info)
    {
        char linha[251];
        printf("\n|| Para o agrado do grupo, se possivel enviar o arquivo txt para algum dos criadores do programa");
        mostrarCriadores();
        printf("\n|| Email 1: caioquintassantiago@gmail.com ");
        printf("\n|| Digite o nome do avaliador: ");
        limparbuffer();
        fgets(linha, sizeof(linha), stdin);
        info->nomeDoAvaliador = (char *)malloc(sizeof(char) * (strlen(linha) + 1));
        strcpy(info->nomeDoAvaliador, linha);
        do
        {
            printf("|| Digite sua avaliacao (1.0 - 5.0): ");
            scanf("%f", &info->valor);
        } while (info->valor < 1.0 || info->valor > 5.0);
        printf("|| Digite um comentario para a avaliacao(250 caracters maximo): ");
        limparbuffer();
        fgets(linha, sizeof(linha), stdin);
        info->descricao = (char *)malloc(sizeof(char) * (strlen(linha) + 1));
        strcpy(info->descricao, linha);
        info->diaDaAvaliacao.dia = hr.tm_mday;
        info->diaDaAvaliacao.mes = hr.tm_mon + 1;
        info->diaDaAvaliacao.ano = hr.tm_year + 1900;
        gravarAvaliacao(info);
        freeAvaliacao(info);
        printf("\n|| Sua avaliacao foi feita e gravada, muito obrigado!");
        pausa();
    }
}

// Funcao que o cliente pode mudar seus dados
void mudarDadosRequisitante(Lista *L, Freguesias *F)
{
    if (!L)
        return;
    NodeR *P = idRequisitante(L);
    if (!P)
        return;
    int mani = 0;
    char c = 's';
    char *linha = NULL;
    do
    {
        system("cls");
        printf("\n|| Qual dado voce deseja mudar ?");
        printf("\n|| 1 - Nome do Requisitante");
        printf("\n|| 2 - Freguesia");
        printf("\n|| 3 - Remover Requisitante");
        printf("\n|| Digite sua opcao (0 para o menu de clientes): ");
        scanf("%d", &mani);
        switch (mani)
        {
        case 1:
            linha = (char *)malloc(sizeof(char) * MAX_STRING_AUX);
            printf("\n|| Seu nome atual e: %s", P->infoRequisitantes->nome);
            printf("\n|| Digite o novo nome: ");
            limparbuffer();
            fgets(linha, sizeof(linha), stdin);
            P->infoRequisitantes->nome = (char *)realloc(P->infoRequisitantes->nome, (sizeof(char) * (strlen(linha) + 1)));
            strcpy(P->infoRequisitantes->nome, linha);
            free(linha);
            printf("\n|| Nome mudado com sucesso");
            break;
        case 2:
            printf("\n|| Sua freguesia atual e: %s", P->infoRequisitantes->freguesia);
            printf("\n|| Ira perguntar ate ser adcionado uma freguesia valida");
            do
            {
                printf("\n|| Digite o novo id da sua freguesia: ");
                linha = (char *)malloc(sizeof(char) * 7);
                limparbuffer();
                fgets(linha, sizeof(linha), stdin);
                P->infoRequisitantes->freguesia = (char *)realloc(P->infoRequisitantes->freguesia, (sizeof(char) * (strlen(linha) + 1)));
                strcpy(P->infoRequisitantes->freguesia, linha);
                free(linha);
            }while(atualizarFreguesias(F, P->infoRequisitantes)!=NULL);
            printf("\n|| Freguesia mudada com sucesso");
            break;
        case 3:
            printf("\n|| Voce realmente deseja remover esse requisitante (s/n)? ");
            // limparbuffer();
            scanf("%c", &c);
            if (c == 'S' || c == 's')
            {
                removerElementoR(L, P);
                printf("\n|| Requisitante removido com sucesso");
                pausa();
            }
            break;
        }
    } while (mani > 0);
}
