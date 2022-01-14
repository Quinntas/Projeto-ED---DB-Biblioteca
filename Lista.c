#define _CRT_SECURE_NO_WARNINGS

#include "Lista.h"
#include "Essentials.h"
#include "Hash.h"
#include "Texto.h"

// ------------------------------------------------------------
extern void limparbuffer();
extern void pausa();
extern bool checkDia(int dia, int mes, int ano);
// ------------------------------------------------------------
extern void logIT(const char *logs);
extern long int funcaoGerarNovoId(Lista *L);
// ------------------------------------------------------------
extern void hash_destruir_area(Hashtable *H);
extern void hash_add_areaO(Hashtable *H, Livros *X);
// ------------------------------------------------------------
extern int tamFreg();
// ------------------------------------------------------------

// Criacao de um lista
Lista *criarLista()
{
    Lista *l = (Lista *)malloc(sizeof(Lista));
    if (!l)
        return NULL;
    l->head = NULL;
    l->headR = NULL;
    l->headRC = NULL;
    l->NELL = 0;
    l->NELR = 0;
    l->NELRC = 0;
    return l;
}

// Funcao de push para livros
void pushListaLivros(Lista *L, Livros *X)
{
    if (!L)
        return;
    Node *no = (Node *)malloc(sizeof(Node));
    no->infoLivros = X;
    no->next = L->head;
    L->head = no;
    L->NELL++;
}

// Funcao de push para requisitantes
void pushListaRequisitantes(Lista *L, Requisitantes *X)
{
    if (!L)
        return;
    NodeR *no = (NodeR *)malloc(sizeof(NodeR));
    no->infoRequisitantes = X;
    no->next = L->headR;
    L->headR = no;
    L->NELR++;
}

// Funcao de push para requisicoes
void pushListaRequisicoes(Lista *L, Requisicao *X)
{
    if (!L)
        return;
    NodeRC *no = (NodeRC *)malloc(sizeof(NodeRC));
    no->infoRequisicoes = X;
    no->next = L->headRC;
    L->headRC = no;
    L->NELRC++;
}

// Funcao de auxilio de push para livros
Livros *auxPushLivros(Lista *L, Hashtable *H)
{
    if (!L)
        return NULL;
    Livros *aux = (Livros *)malloc(sizeof(Livros));
    bool check;
    char linha[MAX_STRING_AUX * 2];
    printf("\n|| Digite o titulo do livro: ");
    limparbuffer();
    fgets(linha, sizeof(linha), stdin);
    aux->titulo = (char *)malloc((strlen(linha) + 1) * sizeof(char));
    strcpy(aux->titulo, linha);
    printf("|| Digite a area do livro: ");
    //limparbuffer();
    fgets(linha, sizeof(linha), stdin);
    aux->area = (char *)malloc((strlen(linha) + 1) * sizeof(char));
    strcpy(aux->area, linha);
    do
    {
        printf("|| Digite a data de publicacao do livro (dd/mm/yyyy): ");
        scanf("%i/%i/%i", &aux->dataDePublicacao.dia, &aux->dataDePublicacao.mes, &aux->dataDePublicacao.ano);
        check = checkDia(aux->dataDePublicacao.dia, aux->dataDePublicacao.mes, aux->dataDePublicacao.ano);
        if (check == false)
            printf("\n|| Data errada tente novamente\n");
    } while (check == false);
    printf("|| Digite o ISBN do livro: ");
    limparbuffer();
    fgets(linha, sizeof(linha), stdin);
    aux->ISBN = (char *)malloc((strlen(linha) + 1) * sizeof(char));
    strcpy(aux->ISBN, linha);
    aux->id = L->NELL + 1;
    logIT("Livro adcionado");
    hash_add_areaO(H, aux);
    return aux;
}

// Funcao que atualiza as freguesias para os requisitantes
Freguesias *atualizarFreguesias(Freguesias *info, Requisitantes *infoR)
{
    if (!info || !infoR)
        return NULL;
    while (info)
    {
        if (strcmp(info->idFreguesia, infoR->freguesia) == 0)
        {
            return info;
        }
        info++;
    }
    return NULL;
}

// Funcao de auxilio de push para requisitantes
Requisitantes *auxPushRequisitantes(Lista *L, Freguesias *F)
{
    if (!L)
        return NULL;
    Requisitantes *aux = (Requisitantes *)malloc(sizeof(Requisitantes));
    bool check = false;
    char linha[MAX_STRING_AUX];
    printf("\n|| Digite o nome do requisitante: ");
    fgets(linha, sizeof(linha), stdin);
    aux->nome = (char *)malloc(sizeof(char) * (strlen(linha) + 1));
    strcpy(aux->nome, linha);
    limparbuffer();
    do
    {
        check = false;
        printf("|| Digite o nome da freguesia do requisitante: ");
        limparbuffer();
        fgets(linha, sizeof(linha), stdin);
        aux->freguesia = (char *)malloc(sizeof(char) * (strlen(linha) + 1));
        strcpy(aux->freguesia, linha);
        aux->infoFreguesias = atualizarFreguesias(F, aux);
        if (aux->infoFreguesias == NULL)
        {
            printf("\n|| Freguesia errada, tente novamente");
            check = false;
        }
    } while (check == false);
    do
    {
        printf("|| Digite a idade do requisitante (dd/mm/yyyy): ");
        scanf("%i/%i/%i", &aux->idade.dia, &aux->idade.mes, &aux->idade.ano);
        check = checkDia(aux->idade.dia, aux->idade.mes, aux->idade.ano);
        if (check == false)
            printf("\n|| Data errada, tente novamente\n");
    } while (check == false);
    aux->id = funcaoGerarNovoId(L);
    logIT("Requisitante adcionado");
    return aux;
}

// Funcao que printa no ecra as informacoes de um livro
void mostrarLivrosSingle(Node *P, int i)
{
    printf("\n|| Para o livro #%i", i + 1);
    printf("\n|| Titulo: %s", P->infoLivros->titulo);
    printf("\n|| Id: %d", P->infoLivros->id);
    printf("\n|| Area: %s", P->infoLivros->area);
    printf("\n|| Dia da publicacao: %i/%i/%i", P->infoLivros->dataDePublicacao.dia, P->infoLivros->dataDePublicacao.mes, P->infoLivros->dataDePublicacao.ano);
    printf("\n|| ISBN: %s", P->infoLivros->ISBN);
    printf("\n");
}

// Funcao que mostra no ecra a informacao de varios livros
void mostrarLivrosAll(Lista *l)
{
    if (!l)
        return;
    Node *P = l->head;
    int i = 1;
    while (P)
    {
        mostrarLivrosSingle(P, i);
        if (i % 500 == 0)
        {
            printf("\n|| Aperte enter para prosseguir");
            pausa();
        }
        i++;
        P = P->next;
    }
}

// Funcao que no ecra mostra uma requisicao
void mostrarRequisicaoSingle(Requisicao *P, int i)
{
    if (P->codR == 0 || P->codL == 0)
    {
        printf("\n|| Essa requisicao nao existe");
        return;
    }
    printf("\n|| Requisicao: #%d - %d (ID)", i + 1, P->idRequisicao);
    printf("\n|| Id do livro requisitado: %d", P->codL);
    printf("\n|| Id do requisitante: %d", P->codR);
    printf("\n|| Dia do inicio da requisicao: %d/%d/%d", P->inicioDaRequisicao.dia, P->inicioDaRequisicao.mes, P->inicioDaRequisicao.ano);
    printf("\n|| Dia do Fim da requisicao: %d/%d/%d", P->fimDaRequisicao.dia, P->fimDaRequisicao.mes, P->fimDaRequisicao.ano);
    printf("\n");
}

// Funcao que mostra no ecra todas as requisicoes
void mostrarRequisicaoALL(Lista *L)
{
    if (!L)
        return;
    int i = 0;
    NodeRC *P = L->headRC;
    while (P)
    {
        mostrarRequisicaoSingle(P->infoRequisicoes, i + 1);
        i++;
        if (i % 500 == 0)
        {
            printf("\n|| Aperte enter para prosseguir");
            pausa();
        }
        P = P->next;
    }
}

// Funcao que mostra um requisitante
void mostrarRequisitantesSingle(NodeR *P, int i)
{
    printf("\n|| Para o requisitante #%i", i);
    printf("\n|| Id: %i", P->infoRequisitantes->id);
    printf("\n|| Nome: %s", P->infoRequisitantes->nome);
    printf("\n|| Freguesia ID: %s", P->infoRequisitantes->infoFreguesias->idFreguesia);
    printf("\n|| Cidade: %s", P->infoRequisitantes->infoFreguesias->cidade);
    printf("\n|| Concelho: %s", P->infoRequisitantes->infoFreguesias->concelho);
    printf("\n|| Distrito: %s", P->infoRequisitantes->infoFreguesias->distrito);
    printf("\n|| Freguesia: %s", P->infoRequisitantes->infoFreguesias->freguesia);
    printf("\n|| Nascido em: %i/%i/%i", P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
    printf("\n");
}

// Funcao que mostra varios requisitantes
void mostrarRequisitantesAll(Lista *l)
{
    if (!l)
        return;
    NodeR *P = l->headR;
    int i = 1;
    while (P)
    {
        mostrarRequisitantesSingle(P, i);
        i++;
        if (i % 500 == 0)
        {
            printf("\n|| Aperte enter para prosseguir");
            pausa();
        }
        P = P->next;
    }
}

// Funcao que mostra os livros organizador por area
void mostrarLivros(Lista *L)
{
    if (!L)
        return;
    Node *P = L->head;
    FILE *file = fopen("Livros_Ordenados.txt", "r");
    int temp;
    char aux[MAX_S];
    int i = 1;
    while (!feof(file))
    {
        fscanf(file, "%d", &temp);
        if (temp != -2)
        {
            while (P)
            {
                if (strcmp(aux, P->infoLivros->area) != 0 && P->infoLivros->id == temp)
                {
                    strcpy(aux, P->infoLivros->area);
                    printf("\n|| Para a area %s", aux);
                    pausa();
                    printf("\n");
                }
                if (P->infoLivros->id == temp)
                {
                    mostrarLivrosSingle(P, i);
                    i++;
                    break;
                }
                P = P->next;
            }
        }
        P = L->head;
    }
    fclose(file);
}

// Funcao que devolve um string com o valor real do id de uma freguesia
const char *mostrarIdFreguesia(const char *info)
{
    char *id = (char*)malloc(sizeof(char)*3);
    id[0] = info[4];
    id[1] = info[5];
    id[2] = '\0';
    return id;
}

// Funcao para mostrar uma freguesia
void mostrarFreguesiasSingle(Freguesias *info)
{
    if (!info)
        return;
    printf("\n|| ID da freguesia: %s", mostrarIdFreguesia(info->idFreguesia));
    printf("\n|| Nome da freguesia: %s", info->freguesia);
    printf("\n|| Id do distrito: %s", info->idDistrito);
    printf("\n|| Nome do distrito: %s", info->distrito);
    printf("\n|| Id do concelho: %s", info->idConcelho);
    printf("\n|| Nome do concelho: %s", info->concelho);
    printf("\n|| Id da cidade: %s", info->idCidade);
    printf("\n|| Nome da cidade: %s", info->cidade);
    printf("\n");
}

// Funcao para mostrar todas as freguesias
void mostrarFreguesiasALL(Freguesias *info)
{
    if (!info)
        return;
    int i = 0, size = tamFreg();
    while (i != size)
    {
        if(info->idFreguesia)
            mostrarFreguesiasSingle(info);
        i++;
        if (i % 500 == 0)
        {
            printf("\n|| Aperte enter para prosseguir");
            pausa();
        }
        info++;
    }
    pausa();
}

// Funcao que destroi a lista de livros
void freeListaLivros(Lista *L)
{
    if (!L)
        return;
    Node *P = L->head;
    Node *auxLivros = NULL;
    while (P)
    {
        auxLivros = P->next;
        free(P->infoLivros->ISBN);
        free(P->infoLivros->area);
        free(P->infoLivros->titulo);
        free(P);
        P = auxLivros;
    }
}

// Funca que destroi a estrutura de freguesiass
void freeFreg(Freguesias *F)
{
    free(F->cidade);
    free(F->concelho);
    free(F->distrito);
    free(F->freguesia);
    free(F->idCidade);
    free(F->idConcelho);
    free(F->idDistrito);
    free(F->idFreguesia);
}

// Funcao que remove um requisitante da lista
void removerElementoR(Lista *L, NodeR *P_REMOVER)
{
    if (!L)
        return;
    int av = 1;
    NodeR *ant, *act;
    ant = act = L->headR;
    while (av)
    {
        while (av)
            if (act == NULL)
                av = 0;
            else if (act->infoRequisitantes->id == P_REMOVER->infoRequisitantes->id)
                av = 0;
            else
            {
                ant = act;
                act = act->next;
            }
        if (act != NULL)
        {
            if (L->headR == act)
                L->headR = act->next;
            else
                ant->next = act->next;
            L->NELR--;
            return;
        }
    }
}

// Destroi apenas um requisitante
void freeRequisitanteSingle(NodeR *P2)
{
    free(P2->infoRequisitantes->nome);
    free(P2->infoRequisitantes->freguesia);
    // freeFreg(P2->infoRequisitantes->infoFreguesias);
    free(P2);
}

// Funcao que destroi a lista de requisitantes
void freeListaRequisitantes(Lista *L)
{
    if (!L)
        return;
    NodeR *P2 = L->headR;
    NodeR *auxRequisitantes = NULL;
    while (P2)
    {
        auxRequisitantes = P2->next;
        freeRequisitanteSingle(P2);
        P2 = auxRequisitantes;
    }
}

// Funca que destroi a estrutura de freguesiass
void freeFregAll(Freguesias *F)
{
    int i = 0;
    int size = tamFreg();
    while (i != size)
    {
        free(F->cidade);
        free(F->concelho);
        free(F->distrito);
        free(F->freguesia);
        free(F->idCidade);
        free(F->idConcelho);
        free(F->idDistrito);
        free(F->idFreguesia);
        i++;
        F++;
    }
}

// Funcao que remove uma requisicao da lista
void removerElementoRC(Lista *L, NodeRC *P_REMOVER)
{
    if (!L)
        return;
    int av = 1;
    NodeRC *ant, *act;
    ant = act = L->headRC;
    while (av)
    {
        while (av)
            if (act == NULL)
                av = 0;
            else if (act->infoRequisicoes->idRequisicao == P_REMOVER->infoRequisicoes->idRequisicao)
                av = 0;
            else
            {
                ant = act;
                act = act->next;
            }
        if (act != NULL)
        {
            if (L->headRC == act)
                L->headRC = act->next;
            else
                ant->next = act->next;
            L->NELRC--;
            return;
        }
    }
}

// Funcao que destroi apenas umas requisicao
void freeRequisicaoSingle(NodeRC *P3)
{
    free(P3->infoRequisicoes->livros);
    free(P3->infoRequisicoes->requisitante);
    free(P3);
}

// Funcao que destroi a lista de requisicoes
void freeListaRequisicao(Lista *L)
{
    if (!L)
        return;
    NodeRC *P3 = L->headRC;
    NodeRC *auxRequisicao = NULL;
    while (P3)
    {
        auxRequisicao = P3->next;
        freeRequisicaoSingle(P3);
        P3 = auxRequisicao;
    }
}

// Funcao para destruir todos os dados
void freeData(Lista *L, Freguesias *F)
{
    if (!L)
        return;
    freeListaLivros(L);
    logIT("Livros destruidos");
    freeListaRequisicao(L);
    logIT("Requisicoes destruidas");
    freeListaRequisitantes(L);
    logIT("Requisitantes destruidas");
    freeFregAll(F);
    free(F);
    logIT("Freguesias destruidas");
    free(L);
    logIT("Lista destruidos");
}

// Funcao que retorna o tam da estrutura dos livros
long int tamLivros(Livros *infoLivros)
{
    int returnValue = 0;
    returnValue += sizeof(infoLivros->area);
    returnValue += sizeof(infoLivros->dataDePublicacao);
    returnValue += sizeof(infoLivros->ISBN);
    returnValue += sizeof(infoLivros->titulo);
    returnValue += sizeof(infoLivros->id);
    return returnValue;
}

// Funcao que retorna o tamanho os livros
long int tamLivrosALL(Lista *L)
{
    if (!L)
        return 0;
    Node *P = L->head;
    long int returnValue = 0;
    while (P)
    {
        returnValue += tamLivros(P->infoLivros);
        returnValue += sizeof(P);
        P = P->next;
    }
    return returnValue;
}

// Funcao que retorna o tam de uma freguesia
long int tamFreguesias(Freguesias *F)
{
    int returnValue = 0;
    returnValue += sizeof(F->cidade);
    returnValue += sizeof(F->concelho);
    returnValue += sizeof(F->distrito);
    returnValue += sizeof(F->freguesia);
    returnValue += sizeof(F->idCidade);
    returnValue += sizeof(F->idConcelho);
    returnValue += sizeof(F->idDistrito);
    returnValue += sizeof(F->idFreguesia);
    return returnValue;
}

// Funcao que retorna o tamanho de todas as freguesias
long int tamFreguesiasALL(Freguesias *F)
{
    if (!F)
        return 0;
    int i = 0;
    int size = tamFreg();
    long int returnValue = 0;
    while (i != size)
    {
        returnValue += tamFreguesias(F);
        F++;
        i++;
    }
    return returnValue;
}

// Funcao que retorna o tamanho dos requisitantes
long int tamRequisitantes(Requisitantes *infoRequisitantes)
{
    int returnValue = 0;
    returnValue += sizeof(infoRequisitantes->nome);
    returnValue += sizeof(infoRequisitantes->freguesia);
    returnValue += sizeof(infoRequisitantes->id);
    returnValue += sizeof(infoRequisitantes->livrosRequisitados);
    returnValue += tamFreguesias(infoRequisitantes->infoFreguesias);
    return returnValue;
}

// Funcao que retorna o tam da estrutura dos requisitantes
long int tamRequisitantesALL(Lista *L)
{
    if (!L)
        return 0;
    NodeR *P = L->headR;
    long int returnValue = 0;
    while (P)
    {
        returnValue += tamRequisitantes(P->infoRequisitantes);
        returnValue += sizeof(P);
        P = P->next;
    }
    return returnValue;
}

// Funcao que retorna o tam da estrura de uma requisicao
long int tamRequisicao(Requisicao *infoRequisicoes)
{
    long int returnValue = 0;
    returnValue += sizeof(infoRequisicoes->codL);
    returnValue += sizeof(infoRequisicoes->codR);
    returnValue += sizeof(infoRequisicoes->fimDaRequisicao);
    returnValue += sizeof(infoRequisicoes->inicioDaRequisicao);
    returnValue += sizeof(infoRequisicoes->idRequisicao);
    return returnValue;
}

// Funcao que retorna o tam da estrura de todas as requisicoes
long int tamRequisicaoALL(Lista *L)
{
    if (!L)
        return 0;
    NodeRC *P = L->headRC;
    long int returnValue = 0;
    while (P)
    {
        returnValue += tamRequisitantes(P->infoRequisicoes->requisitante);
        returnValue += tamLivros(P->infoRequisicoes->livros);
        returnValue += tamRequisicao(P->infoRequisicoes);
        returnValue += sizeof(P);
        P = P->next;
    }
    return returnValue;
}

// Funcao que retorna o tam de todos as estruturas
long int tamEstruturas(Lista *L, Freguesias *F)
{
    if (!L)
        return 0;
    return (tamLivrosALL(L) + tamRequisicaoALL(L) + tamRequisitantesALL(L) + tamFreguesiasALL(F) + sizeof(L));
}

// Funcao que cria as freguesias
Freguesias *criarFreguesia()
{
    int size = tamFreg();
    Freguesias *info = (Freguesias *)malloc(sizeof(Freguesias) * size);
    return info;
}
