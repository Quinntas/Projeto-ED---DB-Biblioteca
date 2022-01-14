#define _CRT_SECURE_NO_WARNINGS

#include "Hash.h"

// ------------------------------------------------------------
extern Lista *criarLista();
extern void freeListaLivros(Lista *L);
extern void mostrarLivrosAll(Lista *L);
extern void freeListaRequisitantes(Lista *L);
extern void pushListaLivros(Lista *L, Livros *X);
extern void pushListaRequisitantes(Lista *L, Requisitantes *X);
extern void mostrarRequisitantesAll(Lista *l);
// ------------------------------------------------------------
const char *pegarSobrenomeGererico(const char *nome);
// ------------------------------------------------------------
extern void logIT(const char *logs);
// ------------------------------------------------------------

// Funcao que cria a hash table
Hashtable *hash_create()
{
    Hashtable *H = (Hashtable *)malloc(sizeof(Hashtable));
    if (!H)
        return NULL;
    H->headH = NULL;
    H->NEL = 0;
    return H;
}

// Funcao que procura um vetor da Hashtable
NodeH *hash_criarvetor(Hashtable *H, const char *key)
{
    if (!H)
        return NULL;
    NodeH *P = H->headH;
    while (P)
    {
        if (strcmp(P->key, key) == 0)
            return P;
        P = P->nextkey;
    }
    return NULL;
}

// Funcao que adcionar um elemento a lista das areas ordenadas
void hash_add_areaO(Hashtable *H, Livros *X)
{
    if (!H)
        return;
    NodeH *P = hash_criarvetor(H, X->area);
    if (P == NULL)
    {
        P = (NodeH *)malloc(sizeof(NodeH));
        P->key = (char *)malloc(sizeof(char) * (strlen(X->area) + 1));
        strcpy(P->key, X->area);
        P->ListaH = criarLista();
        P->nextkey = H->headH;
        H->headH = P;
        H->NEL++;
    }
    pushListaLivros(P->ListaH, X);
}

// Funcao que inici o hash dos Requisitantes por ordem alfabetica
void iniciarHashAL(Hashtable *H)
{
    if (!H)
        return;
    NodeH *P = NULL;
    char *Y = (char *)malloc(sizeof(char) * 2);
    Y[1] = '\0';
    short int i = 65;
    while (i < 91)
    {
        Y[0] = i;
        P = (NodeH *)malloc(sizeof(NodeH));
        P->key = (char *)malloc(sizeof(char) * (strlen(Y) + 1));
        strcpy(P->key, Y);
        P->ListaH = criarLista();
        P->nextkey = H->headH;
        H->headH = P;
        H->NEL++;
        i++;
    }
    free(Y);
}

// Funcao que adcionar um elemento a lista dos Requisitantes por ordem alfabetica
void hash_add_requisitanteAL(Hashtable *H, Requisitantes *X)
{
    if (!H)
        return;
    char *Y = (char *)malloc(sizeof(char) * 2);
    Y[0] = X->nome[0];
    Y[1] = '\0';
    NodeH *P = hash_criarvetor(H, Y);
    if (P == NULL)
    {
        P = (NodeH *)malloc(sizeof(NodeH));
        P->key = (char *)malloc(sizeof(char) * (strlen(Y) + 1));
        strcpy(P->key, Y);
        P->ListaH = criarLista();
        P->nextkey = H->headH;
        H->headH = P;
        H->NEL++;
    }
    pushListaRequisitantes(P->ListaH, X);
    free(Y);
}

// Funcao que adcionar um elemento a lista dos Requisitantes por freguesia
void hash_add_requisitanteFR(Hashtable *H, Requisitantes *X)
{
    if (!H)
        return;
    NodeH *P = hash_criarvetor(H, X->freguesia);
    if (P == NULL)
    {
        P = (NodeH *)malloc(sizeof(NodeH));
        P->key = (char *)malloc(sizeof(char) * (strlen(X->freguesia) + 1));
        strcpy(P->key, X->freguesia);
        P->ListaH = criarLista();
        P->nextkey = H->headH;
        H->headH = P;
        H->NEL++;
    }
    pushListaRequisitantes(P->ListaH, X);
}

// Funcao que adcionar um elemento a lista dos Requisitantes por apelido
void hash_add_requisitanteAP(Hashtable *H, Requisitantes *X)
{
    if (!H)
        return;
    const char *sobrenome = pegarSobrenomeGererico(X->nome);
    NodeH *P = hash_criarvetor(H, sobrenome);
    if (P == NULL)
    {
        P = (NodeH *)malloc(sizeof(NodeH));
        P->key = (char *)malloc(sizeof(char) * (strlen(sobrenome) + 1));
        strcpy(P->key, sobrenome);
        P->ListaH = criarLista();
        P->nextkey = H->headH;
        H->headH = P;
        H->NEL++;
    }
    pushListaRequisitantes(P->ListaH, X);
}

// Funcao que mostra as areas ordenadas
void mostrarAreasOrdenadas(Hashtable *H)
{
    if (!H)
        return;
    NodeH *P = H->headH;
    while (P != NULL)
    {
        printf("\n|| Para a area %s\n", P->key);
        pausa();
        printf("\n");
        mostrarLivrosAll(P->ListaH);
        P = P->nextkey;
    }
}

// Funcao que mostra os Requisitantes por ordem alfabetica
void mostrarRequisitantesAL(Hashtable *H)
{
    if (!H)
        return;
    NodeH *P = H->headH;
    while (P)
    {
        printf("\n|| Para a letra %s\n", P->key);
        pausa();
        printf("\n");
        mostrarRequisitantesAll(P->ListaH);
        P = P->nextkey;
    }
}

// Funcao que mostra os Requisitantes por freguesia
void mostrarRequisitantesFR(Hashtable *H)
{
    if (!H)
        return;
    NodeH *P = H->headH;
    while (P)
    {
        printf("\n|| Para a freguesia %s\n", P->key);
        pausa();
        printf("\n");
        mostrarRequisitantesAll(P->ListaH);
        P = P->nextkey;
    }
}

// Funcao que mostra os Requisitantes por apelido
void mostrarRequisitantesAP(Hashtable *H)
{
    if (!H)
        return;
    NodeH *P = H->headH;
    while (P)
    {
        printf("\n|| Para o apelido %s\n", P->key);
        pausa();
        printf("\n");
        mostrarRequisitantesAll(P->ListaH);
        P = P->nextkey;
    }
}

// Funcao que atualiza os hashs
void atualizarHash(Lista *L, Hashtable *H1, Hashtable *H2, Hashtable *H3)
{
    NodeR *P = L->headR;
    while (P)
    {
        hash_add_requisitanteAL(H1, P->infoRequisitantes);
        hash_add_requisitanteAP(H3, P->infoRequisitantes);
        hash_add_requisitanteFR(H2, P->infoRequisitantes);
        P = P->next;
    }
}

// Funcao que libera a memoria do hash
void hash_destruir(Hashtable *H, void (*func)(Lista *L))
{
    if (!H)
        return;
    NodeH *auxA = NULL;
    NodeH *P = H->headH;
    while (P)
    {
        auxA = P->nextkey;
        (*func)(H->headH->ListaH);
        free(P->ListaH);
        free(P->key);
        free(P);
        P = auxA;
    }
}

// Funcao que libera a memoria dos hash
void hash_free(Hashtable *H, int mani)
{
    if (!H)
        return;
    switch (mani)
    {
    case 1:
        hash_destruir(H, freeListaLivros);
        break;
    case 2:
        hash_destruir(H, freeListaRequisitantes);
        break;
    default:
        logIT("ERROR 21 - Hash nao destruido devido ao mani nao existir");
        break;
    }
    free(H);
}

// Funcao que libera a memoria de todos os hashs
void hash_free_all(Hashtable *H1, Hashtable *H2, Hashtable *H3, Hashtable *H4)
{
    printf("\n");
    hash_free(H1, 1);
    printf("\n");
    logIT("Hash 1 destruido");
    printf("\n");
    hash_free(H2, 2);
    printf("\n");
    logIT("Hash 2 destruido");
    printf("\n");
    hash_free(H3, 2);
    printf("\n");
    logIT("Hash 3 destruido");
    printf("\n");
    hash_free(H4, 2);
    printf("\n");
    logIT("Hash 4 destruido");
}
