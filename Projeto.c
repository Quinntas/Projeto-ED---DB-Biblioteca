// Bibliotecas Publicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Bibliotecas Pessoasis
#include "Essentials.h" // Biblioteca para funcoes genericas
#include "Lista.h"      // Biblioteca para a lista ligada
#include "Texto.h"      // Biblioteca para leitura e gravacao de arquivos
#include "CssC.h"       // Biblioteca para estilizacao do programa
#include "Hash.h"       // Biblioteca para hash functions
#include "Clientes.h"   // Biblioteca para as funcoes de clientes (EXTRA)

// Essentials.h
extern void limparbuffer();
extern void pausa();
extern bool checkDia(int dia, int mes, int ano);
extern int random_int(int min, int max);
extern bool isLeapYear(int ano);

// Texto.h
extern void logIT(const char *logs);
extern void limparLogs();
extern const char *pegarSobrenome(NodeR *P);
extern void lerArqLocais(Lista *L, Hashtable *H, Freguesias *F);
extern void freeFiles();
extern void lerArqFDCC(Freguesias *info);
extern void gravarArquivos(Lista *L, Freguesias *F);
extern void lerArqLivros(Lista *L, Hashtable *H);

// Lista.h
extern Lista *criarLista();
extern void pushListaLivros(Lista *L, Livros *X);
extern void pushListaRequisitantes(Lista *L, Requisitantes *X);
extern void pushListaRequisicoes(Lista *L, Requisicao *X);
extern Livros *auxPushLivros(Lista *L, Hashtable *H);
extern Requisitantes *auxPushRequisitantes(Lista *L, Freguesias *F);
extern void mostrarLivrosSingle(Node *P, int i);
extern void mostrarLivrosAll(Lista *l);
extern void mostrarRequisitantesSingle(NodeR *P, int i);
extern void mostrarRequisitantesAll(Lista *l);
extern void mostrarRequisicaoSingle(Requisicao *P, int i);
extern void mostrarFreguesiasALL(Freguesias *info);
extern void mostrarRequisicaoALL(Lista *L);
extern void freeData(Lista *L, Freguesias *F);
extern long int tamLivrosALL(Lista *L);
extern long int tamRequisitantesALL(Lista *L);
extern long int tamFreguesiasALL(Freguesias *F);
extern long int tamRequisicaoALL(Lista *L);
extern long int tamEstruturas(Lista *L, Freguesias *F);
extern Freguesias *criarFreguesia();
extern void freeRequisicaoSingle(NodeRC *P3);
extern void removerElementoRC(Lista *L, NodeRC *P_REMOVER);

// CssC.h
extern int menuPrincipalEstilizado();
extern int menuEstatisticaEstilizado();
extern int menuEstatistica2Estilizado();
extern int menuMostrarEstilizado();
extern int menuManejoEstilizado();
extern void mensagem();

// Hash.h
extern void mostrarAreasOrdenadas(Hashtable *H);
extern Hashtable *hash_create();
extern void hash_destruir_area(Hashtable *H);
extern void atualizarHash(Lista *L, Hashtable *H1, Hashtable *H2, Hashtable *H3);
extern void mostrarRequisitantesAL(Hashtable *H);
extern void mostrarRequisitantesFR(Hashtable *H);
extern void mostrarRequisitantesAP(Hashtable *H);
extern void iniciarHashAL(Hashtable *H);
extern void iniciarHashAL(Hashtable *H);
extern void hash_free_all(Hashtable *H1, Hashtable *H2, Hashtable *H3, Hashtable *H4);

// Clientes.h
extern int menuDeClientes();
extern void fazerAvaliacao();
extern void mudarDadosRequisitante(Lista *L);

// Funcao que verifica se ha uma lista
bool errorCheck(Lista *L)
{
    if (!L)
    {
        logIT("Lista nao existe");
        return true;
    }
    return false;
}

// Funcao que mostra os criadores do programa
void mostrarCriadores()
{
    printf("\n|| Caio Quintas 18433");
    printf("\n|| David de Almeida 18707");
    printf("\n|| Mónica Teixeira 16300");
}

// Funcao que retorna um ponteiro baseado em um id
NodeR *idRequisitante(Lista *L)
{
    if (errorCheck(L) == true)
        return NULL;
    int temp;
    char c = 'n';
    NodeR *P = L->headR;
    printf("\n|| Qual o seu id de cliente ? ");
    scanf("%d", &temp);
    while (P)
    {
        if (P->infoRequisitantes->id == temp)
        {
            printf("|| Seu nome e %s (s/n)? ", P->infoRequisitantes->nome);
            limparbuffer();
            scanf("%c", &c);
            if (c == 's' || c == 'S')
            {
                return P;
            }
            else
            {
                return NULL;
            }
        }
        P = P->next;
    }
    printf("\n|| Id de requisitante nao encontrado");
    pausa();
    return NULL;
}

// Funcao que mostra as requisicoes de um certo cliente
void mostrarRequisicoesCliente(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    NodeR *P = idRequisitante(L);
    if (!P)
        return;
    NodeRC *P2 = L->headRC;
    int i = 0;
    if (P->infoRequisitantes->livrosRequisitados > 0)
    {
        printf("\n|| Esse requisitante tem %d requisicoes", P->infoRequisitantes->livrosRequisitados);
        while (P2)
        {
            if (P2->infoRequisicoes->codR == P->infoRequisitantes->id)
            {
                mostrarRequisicaoSingle(P2->infoRequisicoes, i);
                i++;
            }
            P2 = P2->next;
        }
    }
    else
        printf("\n|| Esse requisitante nunca requisitou nada");
}

// Mostrar um requisitante que nunca pediu nada
void mostrarRequisitroesSemReq(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    NodeR *P = L->headR;
    int count = 0;
    while (P)
    {
        if (P->infoRequisitantes->livrosRequisitados == 0)
        {
            printf("\n|| O requisitante %d nunca requisitou nada", P->infoRequisitantes->id);
            count++;
        }
        P = P->next;
    }
    if (count == 0)
        printf("\n|| Todos os requisitantes requisitaram um livro");
}

// Funcao que retorna a idade atual do requisitante
int idadeAtual(NodeR *P)
{
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    if(hr.tm_mon+1 > P->infoRequisitantes->idade.mes || (hr.tm_mon+1 == P->infoRequisitantes->idade.mes && hr.tm_mday >= P->infoRequisitantes->idade.dia))
        return ((1900 + hr.tm_year) - P->infoRequisitantes->idade.ano);
    else
        return (((1900 + hr.tm_year) - P->infoRequisitantes->idade.ano) - 1);
}

// Funcao que devolve um novo id para as requisicoes
int criarIdRequisicao(Lista *L)
{
    NodeRC *P = L->headRC;
    int returnValue = 0;
    while(P)
    {
        returnValue = P->infoRequisicoes->idRequisicao;
        P = P->next;
    }
    return returnValue+1;
}

// Funcao para requisitar um livro por parte do cliente
void requisitarLivrosCliente(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    NodeR *P = idRequisitante(L);
    if (!P)
        return;
    Requisicao *P2 = (Requisicao *)malloc(sizeof(Requisicao));
    Node *P3 = L->head;
    int temp = 0;
    bool sucesso = false;
    if (!P)
        return;
    P2->requisitante = P->infoRequisitantes;
    P2->codR = P->infoRequisitantes->id;
    P2->inicioDaRequisicao.dia = hr.tm_mday;
    P2->inicioDaRequisicao.mes = hr.tm_mon + 1;
    P2->inicioDaRequisicao.ano = hr.tm_yday + 1900;
    do
    {
        printf("\n|| Digite o id do livro que voce esta requisitando: ");
        scanf("%d", &temp);
        while (P3)
        {
            if (temp == P3->infoLivros->id)
            {
                P2->livros = P3->infoLivros;
                P2->codL = P3->infoLivros->id;
                sucesso = true;
                break;
            }
            P3 = P3->next;
        }
        if (sucesso == false)
            printf("\n|| Livro nao encontrado, tente novamente");
    } while (sucesso == false);
    printf("|| O dia de entrega so pode ser um mes longo");
    do
    {
        printf("\n|| Digite o dia da entrega (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &P2->fimDaRequisicao.dia, &P2->fimDaRequisicao.mes, &P2->fimDaRequisicao.ano);
        if (checkDia(P2->fimDaRequisicao.dia, P2->fimDaRequisicao.mes, P2->fimDaRequisicao.ano) == true)
            sucesso = true;
        if (P2->fimDaRequisicao.mes > P2->inicioDaRequisicao.mes && P2->fimDaRequisicao.dia > P2->inicioDaRequisicao.mes)
            sucesso = false;
        else
            sucesso = true;
        if (sucesso == false)
            printf("\n|| Data errada, tente novamente ");
    } while (sucesso == false);
    P2->idRequisicao = criarIdRequisicao(L);
    pushListaRequisicoes(L, P2);
    printf("\n|| Livro requisitado com sucesso (O dia de entrega so pode ser um mes longo)");
}

// Funcao que devolve os livros
void devolverLivrosCliente(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    NodeR *P = idRequisitante(L);
    if (!P)
        return;
    NodeRC *P2 = L->headRC;
    char c = 'n';
    printf("\n|| Voce tem %d requisicoes", P->infoRequisitantes->livrosRequisitados);
    pausa();
    if (P->infoRequisitantes->livrosRequisitados > 0)
    {
        while (P2)
        {
            if (P2->infoRequisicoes->codL == P->infoRequisitantes->id)
            {
                printf("\n|| voce deseja devolver o livro %s (%d) (s/n): ", P2->infoRequisicoes->livros->titulo, P2->infoRequisicoes->livros->id);
                limparbuffer();
                scanf("%c", &c);
                if (c == 's' || c == 'S')
                {
                    removerElementoRC(L, P2);
                }
            }
            P2 = P2->next;
        }
        P->infoRequisitantes->livrosRequisitados -= 1;
        if (P->infoRequisitantes->livrosRequisitados < 0)
            P->infoRequisitantes->livrosRequisitados = 0;
    }
}

// Mostra uma pessoa na lista baseado em um id
void pessoaNaListaPorId(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    int temp;
    printf("\n|| Qual o id que voce deseja busar ? ");
    scanf("%d", &temp);
    NodeR *P = L->headR;
    int i = 0;
    while (P)
    {
        if (P->infoRequisitantes->id == temp)
        {
            mostrarRequisitantesSingle(P, i);
            return;
        }
        P = P->next;
        i++;
    }
    printf("\n|| Essa pessoa nao existe na lista");
}

// Mostra um livro na lista baseado em um id
void livroNaListaPorId(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    int temp;
    printf("\n|| Qual o id que voce deseja busar ? ");
    scanf("%d", &temp);
    Node *P = L->head;
    int i = 0;
    while (P)
    {
        if (P->infoLivros->id == temp)
        {
            mostrarLivrosSingle(P, i);
            return;
        }
        P = P->next;
        i++;
    }
    printf("\n|| Esse livro nao existe na lista");
}

// Funcao que determina a maior idade do requisitantes
NodeR *idadeMaxima(Lista *L)
{
    if (errorCheck(L) == true)
        return NULL;
    NodeR *P = L->headR;
    NodeR *P2 = L->headR;
    int maior = 0;
    int n;
    while (P)
    {
        n = idadeAtual(P);
        if (n > maior)
        {
            maior = n;
            P2 = P;
        }
        P = P->next;
    }
    return P2;
}

// Funcao que determina a idade media dos requisitantes
float idadeMedia(Lista *L)
{
    if (errorCheck(L) == true)
        return 0.0;
    NodeR *P = L->headR;
    float media = 0.0;
    while (P)
    {
        media += idadeAtual(P);
        P = P->next;
    }
    media = media / L->NELR;
    return media;
}

// Funcao que determina a quantidad de idades acima de um valor
int idadeValor(Lista *L)
{
    if (errorCheck(L) == true)
        return 0;
    ;
    int count = 0, temp = 0;
    NodeR *P = L->headR;
    printf("\n|| Digite um numero: ");
    scanf("%d", &temp);
    while (P)
    {
        if (idadeAtual(P) > temp)
            count++;
        P = P->next;
    }
    return count;
}

// Funcao que Verifica se uma pessoa esta na lista por NOME
bool pessoaNaLista(Lista *L, const char *nome)
{
    if (errorCheck(L) == true)
        return false;
    NodeR *P = L->headR;
    while (P)
    {
        if (strcmp(P->infoRequisitantes->nome, nome) == 0)
        {
            return true;
        }
        P = P->next;
    }
    return false;
}

// Funcao que Verifica se um livro esta na lista por ISBN
void livroNaLista(Lista *L, const char *isbn)
{
    if (errorCheck(L) == true)
        return;
    Node *P = L->head;
    while (P)
    {
        if (strcmp(P->infoLivros->ISBN, isbn) == 0)
        {
            printf("\n|| O livro existe na lista");
            printf("\n|| Sua area e: %s", P->infoLivros->area);
            return;
        }
        P = P->next;
    }
    printf("\n|| O livro nao existe na lista");
}

// Funcao que determina os livros mais recentes
void livrosMaisRecentes(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    Node *P = L->head;
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    int count = 0;
    while (P)
    {
        if (P->infoLivros->dataDePublicacao.ano >= hr.tm_year + 1898)
        {
            printf("\n|| O livro #%d (Id: %d) de %d e recente", count, P->infoLivros->id, P->infoLivros->dataDePublicacao.ano);
        }
        P = P->next;
        count++;
    }
}

// Funcao que devolte o requisitante com mais livros
NodeR *requisitanteComMaislivros(Lista *L)
{
    if (errorCheck(L) == true)
        return NULL;
    NodeR *P = L->headR;
    NodeR *P2 = NULL;
    int maior = 0;

    while (P)
    {
        if (P->infoRequisitantes->livrosRequisitados > maior)
        {
            maior = P->infoRequisitantes->livrosRequisitados;
            P2 = P;
        }
        P = P->next;
    }
    return P2;
}

// Funcao retorna a idade com mais pessoas
int idadeComMaisPessoas(Lista *L)
{
    if (errorCheck(L) == true)
        return 0;
    NodeR *P = L->headR;
    int size = L->NELR + 50;
    int *aux = (int *)malloc(size * sizeof(int));
    int auxTroca = 0;
    int i = 0, j = 0, count = 1, maiorNum = 0, maior = 0;
    while (P)
    {
        aux[i] = idadeAtual(P);
        i++;
        P = P->next;
    }
    for (i = 0; i < size; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (aux[i] > aux[j])
            {
                auxTroca = aux[i];
                aux[i] = aux[j];
                aux[j] = auxTroca;
            }
        }
    }
    for (i = 0; i < size; i++)
    {
        if (aux[i] != 0)
        {
            if (aux[i] == aux[i - 1])
            {
                count++;
            }
            else
            {
                if (count > maior)
                {
                    maior = count;
                    maiorNum = aux[i - 1];
                }
                count = 1;
            }
        }
    }
    free(aux);
    return maiorNum;
}

// Funcao que retorna o sobrenome mais usado
const char *sobrenomeMaisUsado(Lista *L)
{
    if (errorCheck(L) == true)
        return NULL;
    NodeR *P = L->headR;
    int size = L->NELR + 50;
    Aux *infonome = (Aux *)malloc(size * sizeof(Aux));
    char *maiorNome = (char *)malloc(MAX_S * sizeof(char));
    char *tempNome = (char *)malloc(MAX_S * sizeof(char));
    int i = 1, count = 1, maior = 0, j = 0;
    while (P)
    {
        strcpy(infonome[i].aux, pegarSobrenome(P));
        i++;
        P = P->next;
    }
    for (i = 1; i < size; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (strcmp(infonome[i].aux, infonome[j].aux) > 0)
            {
                strcpy(tempNome, infonome[i].aux);
                strcpy(infonome[i].aux, infonome[j].aux);
                strcpy(infonome[j].aux, tempNome);
            }
        }
    }
    for (i = 1; i < size; i++)
    {
        if (infonome[i].aux != NULL)
        {
            if (strcmp(infonome[i].aux, infonome[i - 1].aux) == 0)
            {
                count++;
            }
            else
            {
                if (count > maior)
                {
                    maior = count;
                    strcpy(maiorNome, infonome[i - 1].aux);
                }
                count = 1;
            }
        }
    }
    free(infonome);
    free(tempNome);
    return maiorNome;
}

// Funcao que retorna a area mais usada
const char *areaMaisUsada(Lista *L, Hashtable *H)
{
    if (!H || errorCheck(L) == true)
        return NULL;
    NodeH *P = H->headH;
    int count = 0, maior = 0;
    char *area = NULL;
    Node *P2 = P->ListaH->head;
    while (P)
    {
        while (P2)
        {
            count++;
            P2 = P2->next;
        }
        if (count > maior)
        {
            maior = count;
            area = (char *)malloc((strlen(P->key) + 1) * sizeof(char));
            strcpy(area, P->key);
        }
        P = P->nextkey;
    }
    return area;
}

// Funcao que devolve a area com mais livros
const char *areaComMaisLivros(Lista *L, Hashtable *H)
{
    if (!H || errorCheck(L) == true)
        return NULL;
    NodeH *P = H->headH;
    int count = 0, maior = 0;
    char *area = NULL;
    Node *P2 = P->ListaH->head;
    while (P)
    {
        while (P2)
        {
            count++;
            P2 = P2->next;
        }
        if (count > maior)
        {
            maior = count;
            area = (char *)malloc((strlen(P->key) + 1) * sizeof(char));
            strcpy(area, P->key);
        }
        P = P->nextkey;
    }
    return area;
}

// Funcao que mostra o livro mais requisitado
int livroMaisRequisitado(Lista *L)
{
    if (errorCheck(L) == true)
        return 0;
    int size = L->NELRC + 50;
    int *aux = (int *)malloc(size * sizeof(int));
    NodeRC *P = L->headRC;
    int i = 0, temp = 0, count = 0, maior = 0, maiorNum = 0;
    while (P)
    {
        aux[i] = P->infoRequisicoes->codL;
        i++;
        P = P->next;
    }
    for (i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
        {
            if (aux[i] > aux[j])
            {
                temp = aux[i];
                aux[i] = aux[j];
                aux[j] = temp;
            }
        }
    for (i = 0; i < size; i++)
    {
        if (aux[i] != 0)
        {
            if (aux[i] == aux[i - 1])
            {
                count++;
            }
            else
            {
                if (count > maior)
                {
                    maior = count;
                    maiorNum = aux[i - 1];
                }
                count = 1;
            }
        }
    }
    free(aux);
    return maiorNum;
}

// Funcao que retorna quantos de um sobrenome existem em uma cidade
void nomePopularEmUmaCidade(Lista *L)
{
    if (!L)
        return;
    NodeR *P = L->headR;
    char cidade[MAX_S], nome[MAX_S];
    int count = 0;
    printf("\n|| Digite o nome de uma cidade no sistema: ");
    limparbuffer();
    // fgets(cidade, sizeof(cidade), stdin); - Esse metodo nao funciona
    scanf("%[^\n]", cidade);
    printf("|| Digite um sobrenome a buscar: ");
    limparbuffer();
    // fgets(nome, sizeof(nome), stdin);     - Esse metodo nao funciona
    scanf("%[^\n]", nome);
    while (P)
    {
        if (strcmp(P->infoRequisitantes->infoFreguesias->cidade, cidade) == 0)
        {
            if (strcmp(pegarSobrenome(P), nome) == 0)
                count++;
        }
        P = P->next;
    }
    printf("\n|| Em %s existem %d pessoas com %s", cidade, count, nome);
}

// Funcao que mostra o usuario quais requisitantes fazem aniversario em um ano
void listaAniversarioDomingo(Lista *L, int mani)
{
    if (errorCheck(L) == true)
        return;
    NodeR *P = L->headR;
    int k = 0, j = 0, m = 0, y = 0, d = 0, result = 0;
    while (P)
    {
        m = P->infoRequisitantes->idade.mes;
        y = P->infoRequisitantes->idade.ano;
        if (mani == 0)
            d = P->infoRequisitantes->idade.dia;
        else
            d = mani;
        if (m < 3)
        {
            m += 12;
            y -= 1;
        }
        k = y % 100;
        j = y / 100;
        result = ((d + ((m + 1) * 26) / 10) + k + (k / 4) + (j / 4) + (5 * 3)) % 7;
        if (result == 1 && mani == 0)
        {
            printf("\n|| O requisitante %d, nasceu em um domingo (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
        }
        else if (result == 1 && mani != 0)
        {
            printf("\n|| O requisitante %d, faz aniversario em um domingo (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
        }
        P = P->next;
    }
    printf("\n");
}

// Funcao que retorna o dia da pascoa em um ano n
int calculaPascoa(int y)
{
    int g = 0, c = 0, x = 0, z = 0, e = 0, n = 0, d = 0;
    g = (y % 19) + 1;
    c = (y / 100) + 1;
    x = ((3 * c) / 4) - 12;
    z = (((8 * c) + 5) / 25) - 5;
    e = ((11 * g) + 20 + z - x) % 30;
    if ((e == 25 && g > 11) || (e == 24))
        e++;
    n = (44 - e);
    if (n < 21)
        n = n + 30;
    d = ((5 * y) / 4) - (x + 10);
    n = (n + 7) - ((d + n) % 7);
    return n;
}

// Funcao que verifica se a pessoa faz aniversario na quaresma em abril
int verificarAniversariosABRIL(int quaresma, NodeR *P, int mani)
{
    if(P->infoRequisitantes->idade.mes ==  4 && P->infoRequisitantes->idade.dia <= quaresma && mani == 0)
        return 0;
    else if(P->infoRequisitantes->idade.mes ==  4 && P->infoRequisitantes->idade.dia <= quaresma && mani != 0)
        return 1;
    else if(P->infoRequisitantes->idade.mes ==  3 && P->infoRequisitantes->idade.dia >= quaresma && mani == 0)
        return 0;
    else if(P->infoRequisitantes->idade.mes ==  3 && P->infoRequisitantes->idade.dia >= quaresma && mani != 0)
        return 1;
    else if(P->infoRequisitantes->idade.mes ==  2 && P->infoRequisitantes->idade.dia >= quaresma && mani == 0)
        return 0;
    else if(P->infoRequisitantes->idade.mes ==  2 && P->infoRequisitantes->idade.dia >= quaresma && mani != 0)
        return 1;
    return 2;
}

// Funcao que verifica se a pessoa faz aniversario na quaresma em marco
int verificarAniversariosMARCO(int quaresma, NodeR *P, int mani)
{
    if(P->infoRequisitantes->idade.mes ==  3 && P->infoRequisitantes->idade.dia <= quaresma && mani == 0)
        return 0;
    else if(P->infoRequisitantes->idade.mes ==  3 && P->infoRequisitantes->idade.dia <= quaresma && mani != 0)
        return 1;
    else if(P->infoRequisitantes->idade.mes ==  2 && P->infoRequisitantes->idade.dia >= quaresma && mani == 0)
        return 0;
    else if(P->infoRequisitantes->idade.mes ==  2 && P->infoRequisitantes->idade.dia >= quaresma && mani != 0)
        return 1;
    else if(P->infoRequisitantes->idade.mes ==  1 && P->infoRequisitantes->idade.dia >= quaresma && mani == 0)
        return 0;
    else if(P->infoRequisitantes->idade.mes ==  1 && P->infoRequisitantes->idade.dia >= quaresma && mani != 0)
        return 1;
    return 2;
}

// Funcao que mostra ao usuario as pessoas que fazem aniversario na quaresma
void listaAniversarioQuaresma(Lista *L, int mani)
{
    if (errorCheck(L) == true)
        return;
    NodeR *P = L->headR;
    int quaresma = 0;
    while(P)
    {
        if (mani == 0)
            quaresma = calculaPascoa(P->infoRequisitantes->idade.ano);
        else if (mani > 0)
            quaresma = calculaPascoa(mani);
        if (quaresma > 31) // ABRIL
        {
            quaresma -= 30;
            switch(verificarAniversariosABRIL(quaresma, P, mani))
            {
                case 0:
                    printf("\n|| O requisitante %d, nasceu em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
                break;
                case 1:
                    printf("\n|| O requisitante %d, faz aniversario em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
                break;
            }
        }
        else // MARCO
        {
            switch(verificarAniversariosMARCO(quaresma, P, mani))
            {
                case 0:
                    printf("\n|| O requisitante %d, nasceu em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
                break;
                case 1:
                    printf("\n|| O requisitante %d, faz aniversario em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
                break;
            }
        }
        P = P->next;
    }
    printf("\n");
}
/* Funcao antiga, ela foi removida pois o programador pensou que a quaresma fosse um dia unico (40 dias antes da pascoa)
void listaAniversarioQuaresma(Lista *L, int mani)
{
    if (errorCheck(L) == true)
        return;
    NodeR *P = L->headR;
    int diasDaQuaresma = 40;
    int quaresma = 0;
    int dif = 0;
    while (P)
    {
        if (mani == 0)
            quaresma = calculaPascoa(P->infoRequisitantes->idade.ano);
        else if (mani > 0)
            quaresma = calculaPascoa(mani);
        if (quaresma > 31) // ABRIL (Quaresma em marco)
        {
            quaresma -= 30;
            dif = 30 - quaresma;
            quaresma -= dif;
            if (31 > (diasDaQuaresma - dif))
                quaresma = 31 - (diasDaQuaresma - dif);
            else
                quaresma = (diasDaQuaresma - dif) - 31;
            if (mani == 0 && P->infoRequisitantes->idade.dia == quaresma && P->infoRequisitantes->idade.mes == 3 )
                printf("\n|| O requisitante %d, nasceu em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
            else if (mani != 0 && P->infoRequisitantes->idade.dia >= quaresma && P->infoRequisitantes->idade.mes == 3)
                printf("\n|| O requisitante %d, faz aniversario em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
        }
        else // MARCO (Quaresma em fevereiro)
        {
            dif = 31 - quaresma;
            quaresma -= dif;
            if (isLeapYear(P->infoRequisitantes->idade.ano) == true)
            {
                if (29 > (diasDaQuaresma - dif))
                    quaresma = 29 - (diasDaQuaresma - dif);
                else
                    quaresma = (diasDaQuaresma - dif) - 29;
            }
            else
            {
                if (28 > (diasDaQuaresma - dif))
                    quaresma = 28 - (diasDaQuaresma - dif);
                else
                    quaresma = (diasDaQuaresma - dif) - 28;
            }
            if (mani == 0 && P->infoRequisitantes->idade.dia == quaresma && P->infoRequisitantes->idade.mes == 2)
                printf("\n|| O requisitante %d, nasceu em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
            else if (mani != 0 && P->infoRequisitantes->idade.dia >= quaresma && P->infoRequisitantes->idade.mes == 2)
                printf("\n|| O requisitante %d, faz aniversario em uma quaresma (%d/%d/%d)", P->infoRequisitantes->id, P->infoRequisitantes->idade.dia, P->infoRequisitantes->idade.mes, P->infoRequisitantes->idade.ano);
        }
        P = P->next;
    }
    printf("\n");
}
*/

// Funcao de controle para o menu estatiticas 2 (7 - Aniversarios em dias especiais)
void aniversarios(Lista *L)
{
    if (errorCheck(L) == true)
        return;
    int mani, mani2;
    printf("\n|| Escolha uma opcao: ");
    printf("\n|| 1 - Voce deseja ver uma lista de requisitantes que o aniversario de ano n e domingo");
    printf("\n|| 2 - Listar requisitantes cujo aniversario, num determinado ano, e na quaresma");
    printf("\n|| Digite a sua opcao: ");
    scanf("%i", &mani);
    switch (mani)
    {
    case 1:
        printf("\n|| 1 - Listar requisitantes que nasceram domingo");
        printf("\n|| 2 - Lista requisitantes que o aniversario de um ano n e domingo");
        printf("\n|| Digite a sua opcao: ");
        scanf("%d", &mani2);
        switch (mani2)
        {
        case 1:
            listaAniversarioDomingo(L, 0);
            break;
        case 2:
            printf("\n|| Digite o ano: ");
            scanf("%d", &mani2);
            if (mani2 > 0)
                listaAniversarioDomingo(L, mani2);
            break;
        }
        break;
    case 2:
        printf("\n|| 1 - Listar requisitantes que nasceram na quaresma");
        printf("\n|| 2 - Lista requisitantes que o aniversario de um ano n e na quaresma");
        printf("\n|| Digite sua opacao: ");
        scanf("%d", &mani2);
        switch (mani2)
        {
        case 1:
            listaAniversarioQuaresma(L, 0);
            break;
        case 2:
            printf("\n|| Digite o ano: ");
            scanf("%d", &mani2);
            if (mani2 > 0)
                listaAniversarioQuaresma(L, mani2);
            break;
        }
        break;
    }
}

// Funcao que mostra no ecra um menu para ver os dados os requisitantes
void menuParaMostrarRequisitantes(Lista *L, Hashtable *H1, Hashtable *H2, Hashtable *H3)
{
    int mani = 0;
    printf("\n|| Menu de visualizacao dos requisitantes");
    printf("\n|| 1 - Mostrar requisitantes sem filtros");
    printf("\n|| 2 - Mostrar requisitantes por ordem alfabetica");
    printf("\n|| 3 - Mostrar requisitantes por freguesia");
    printf("\n|| 4 - Mostrar requisitantes por apelidos");
    printf("\n|| Digite aqui sua opcao: ");
    scanf("%d", &mani);
    switch (mani)
    {
    case 1:
        mostrarRequisitantesAll(L);
        break;
    case 2:
        mostrarRequisitantesAL(H1);
        break;
    case 3:
        mostrarRequisitantesFR(H2);
        break;
    case 4:
        mostrarRequisitantesAP(H3);
        break;
    }
}

// Funcao que somente todos os arquivos
void lerArquivos(Lista *L, Freguesias *F, Hashtable *H1, Hashtable *H2, Hashtable *H3, Hashtable *H4)
{
    if (errorCheck(L) == true || !F)
        return;
    lerArqFDCC(F);
    lerArqLocais(L, H1, F);
    iniciarHashAL(H2);
    atualizarHash(L, H2, H3, H4);
}

// Funcao que inicia com o progrma
void inicio(Lista *L, Freguesias *F, Hashtable *H1, Hashtable *H2, Hashtable *H3, Hashtable *H4)
{
    // leitura e carregamento de arquivos
    lerArquivos(L, F, H1, H2, H3, H4);
    // logs
    limparLogs();
    logIT("Programa Iniciado");
}

// Funcao que checka todos as hash tables do programa para saber se elas foram propiamente alocadas
bool checkHashs(Hashtable *H1, Hashtable *H2, Hashtable *H3, Hashtable *H4)
{
    if(!H1||!H2 ||!H3 ||!H4)
        return false;
    return true;
}

// Funcao main do programa
int main()
{
    system("color F"); // Define a cor do ecra para branco muito CLARO

    Lista *l = criarLista();
    Freguesias *f = criarFreguesia();

    Hashtable *areasOrdenadas = hash_create();
    Hashtable *requisitantesAL = hash_create();
    iniciarHashAL(requisitantesAL);
    Hashtable *requisitantesFR = hash_create();
    Hashtable *requisitantesAP = hash_create();

    if (!l || !f)
        return 0;

    if(checkHashs(areasOrdenadas, requisitantesAL, requisitantesFR, requisitantesAP) == false)
        logIT("ERROR 13 - Hash Tables nao alocadas corretamente");

    srand(time(NULL));                                                               // Seed para a funcao rand
    inicio(l, f, areasOrdenadas, requisitantesAL, requisitantesFR, requisitantesAP); // Inicializa as estruturas e registra uma entrada no log
    mensagem(); // Comente para tirar a mensagem de carregando no arranque              Funcao que mostra a menssagem de inicio (Carregando programa)

    NodeR *P = l->headR; // Para o aparo de algumas informacoes

    int mani = 0;     // Para os menus
    int mani2 = 0;    // Para o sub menu de Estatistica
    char temp[MAX_S]; // Para o aparo de algumas informacoes

    do
    {
        mani = menuPrincipalEstilizado();
        switch (mani)
        {
        // Menu de manejo
        case 1:
            do
            {
                mani2 = menuManejoEstilizado();
                switch (mani2)
                {
                case 1:
                    lerArquivos(l, f, areasOrdenadas, requisitantesAL, requisitantesFR, requisitantesAP);
                    printf("\n|| Arquivos lidos com sucesso\n");
                    pausa();
                    break;
                case 2:
                    gravarArquivos(l, f);
                    break;
                case 3:
                    pushListaLivros(l, auxPushLivros(l, areasOrdenadas));
                    printf("\n|| Livro adcionado com sucesso");
                    pausa();
                    break;
                case 4:
                    pushListaRequisitantes(l, auxPushRequisitantes(l, f));
                    printf("\n|| Requisitante adcionado com sucesso");
                    pausa();
                    break;
                case 5:
                    requisitarLivrosCliente(l);
                    pausa();
                    break;
                case 6:
                    devolverLivrosCliente(l);
                    pausa();
                    break;
                case 7:
                    // Modificar valores
                    break;
                }
            } while (mani2 > 0);
            break;
        // Menu de mostrar
        case 2:
            do
            {
                mani2 = menuMostrarEstilizado();
                switch (mani2)
                {
                case 1:
                    mostrarAreasOrdenadas(areasOrdenadas);
                    pausa();
                    break;
                case 2:
                    menuParaMostrarRequisitantes(l, requisitantesAL, requisitantesFR, requisitantesAP);
                    pausa();
                    break;
                case 3:
                    mostrarRequisicoesCliente(l);
                    pausa();
                    break;
                case 4:
                    mostrarRequisitroesSemReq(l);
                    printf("\n");
                    pausa();
                    break;
                case 5:
                    pessoaNaListaPorId(l);
                    printf("\n");
                    pausa();
                    break;
                case 6:
                    livroNaListaPorId(l);
                    printf("\n");
                    pausa();
                    break;
                case 7:
                    mostrarFreguesiasALL(f);
                    printf("\n");
                    pausa();
                    break;
                case 8:
                    mostrarRequisicaoALL(l);
                    printf("\n");
                    pausa();
                    break;
                }
            } while (mani2 > 0);
            break;
        // Menu de estatisticas
        case 3:
            do
            {
                mani2 = menuEstatisticaEstilizado();
                switch (mani2)
                {
                case 1:
                    P = idadeMaxima(l);
                    printf("\n|| A pessoa com a idade maxima e #%d ", P->infoRequisitantes->id);
                    printf("\n|| Nome: %s", P->infoRequisitantes->nome);
                    printf("\n|| Esse requisitante tem %d anos\n", idadeAtual(P));
                    pausa();
                    break;
                case 2:
                    printf("\n|| A idade media dos requisitantes e: %.2f\n", idadeMedia(l));
                    pausa();
                    break;
                case 3:
                    printf("\n|| A area com mais livros e: %s", areaComMaisLivros(l, areasOrdenadas));
                    printf("\n");
                    pausa();
                    break;
                case 4:
                    printf("\n|| Existem %d pessoas com a idade maior a esse numero\n", idadeValor(l));
                    pausa();
                    break;
                case 5:
                    nomePopularEmUmaCidade(l);
                    printf("\n");
                    pausa();
                    break;
                case 6:
                    printf("\n|| Digite o nome a buscar: ");
                    limparbuffer();
                    // fgets(temp, sizeof(temp), stdin);
                    scanf("%[^\n]", temp);
                    if (pessoaNaLista(l, temp) == true)
                        printf("\n|| Essa pessoa existe na lista");
                    else
                        printf("\n|| Essa pessoa nao existe na lista");
                    printf("\n");
                    pausa();
                    break;
                case 7:
                    printf("\n|| Digite o ISBN a buscar: ");
                    limparbuffer();
                    // fgets(temp, sizeof(temp), stdin);
                    scanf("%[^\n]", temp);
                    livroNaLista(l, temp);
                    printf("\n");
                    pausa();
                    break;
                case 8:
                    printf("\n|| A idade com mais requisitantes e: %d", idadeComMaisPessoas(l));
                    printf("\n");
                    pausa();
                    break;
                // Sub-menu de estatisticas
                case 9:
                    mani2 = menuEstatistica2Estilizado();
                    switch (mani2)
                    {
                    case 1:
                        livrosMaisRecentes(l);
                        printf("\n");
                        pausa();
                        break;
                    case 2:
                        printf("\n|| O livro mais requisitado e o (id): %d ", livroMaisRequisitado(l));
                        printf("\n");
                        pausa();
                        break;
                    case 3:
                        printf("\n|| O tamanho da listas juntas e: %ld", tamEstruturas(l, f));
                        printf("\n|| O tamanho da lista dos livros e: %ld", tamLivrosALL(l));
                        printf("\n|| O tamanho da lista dos requisitantes e: %ld", tamRequisitantesALL(l));
                        printf("\n|| O tamanho da lista de requisicoes e: %ld", tamRequisicaoALL(l));
                        printf("\n|| O tamanho da estrutura de freguesias e: %ld", tamFreguesiasALL(f));
                        printf("\n");
                        pausa();
                        break;
                    case 4:
                        printf("\n|| A area mais requisitada e: %s ", areaMaisUsada(l, areasOrdenadas));
                        printf("\n");
                        pausa();
                        break;
                    case 5:
                        P = requisitanteComMaislivros(l);
                        printf("\n|| A pessoa com mais livros requisitados e: #%d ", P->infoRequisitantes->id);
                        printf("\n|| Nome: %s", P->infoRequisitantes->nome);
                        printf("\n|| Com %d livros requisitados\n", P->infoRequisitantes->livrosRequisitados);
                        pausa();
                        break;
                    case 6:
                        printf("\n|| O sobrenome mais usado e: %s", sobrenomeMaisUsado(l));
                        printf("\n");
                        pausa();
                        break;
                    case 7:
                        aniversarios(l);
                        pausa();
                        break;
                    }
                    break;
                }
            } while (mani2 > 0);
            break;
        // Menu de Clientes
        case 4:
            do
            {
                mani2 = menuDeClientes();
                switch (mani2)
                {
                case 1:
                    fazerAvaliacao();
                    break;
                case 2:
                    mudarDadosRequisitante(l);
                    break;
                }
            } while (mani2 > 0);
            break;
        }
    } while (mani > 0);

    logIT("Programa finalizado pelo usuario");

    // Liberacao de Memorias
    printf("\n");
    freeData(l, f);
    printf("\n");
    hash_free_all(areasOrdenadas, requisitantesAL, requisitantesFR, requisitantesAP);
    // freeFiles();
    logIT("Todos os dados foram apagados");

    return 0;
}
