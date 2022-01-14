#ifndef LISTA_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 20   // Quantidade de livros que podem ser requisitados
#define MAX_S 81 // Tamanho maximo de uma string
#define MAX_STRING_AUX 201 // Tamanho maximo de uma string auxliar

// Estrutura auxliar para datas
typedef struct
{
    int dia, mes, ano;
} Data;

// Estrutura de dados para as freguesias
typedef struct
{
    char *idFreguesia;
    char *freguesia;
    char *idDistrito;
    char *distrito;
    char *idConcelho;
    char *concelho;
    char *idCidade;
    char *cidade;
} Freguesias;

// Estruta de dados dos livros
typedef struct
{
    int id;
    char *ISBN;
    char *titulo;
    char *area;
    Data dataDePublicacao;
} Livros;

// Estrutura de dados dos requisitantes
typedef struct
{
    int id;
    char *nome;
    Data idade;
    char *freguesia;
    int livrosRequisitados;
    Freguesias *infoFreguesias;
} Requisitantes;

// Estrutura da requisicao de um livro
typedef struct
{
    int idRequisicao, codR, codL;
    Livros *livros;
    Requisitantes *requisitante;
    Data inicioDaRequisicao;
    Data fimDaRequisicao;
} Requisicao;

// Estrutura de dados dos nos livros
typedef struct node
{
    Livros *infoLivros;
    struct node *next;
} Node;

// Estrutura de dados dos nos dos requisitantes
typedef struct nodeR
{
    Requisitantes *infoRequisitantes;
    struct nodeR *next;
} NodeR;

// Estrutura de dados dos nos das requisicoes
typedef struct nodeRC
{
    Requisicao *infoRequisicoes;
    struct nodeRC *next;
} NodeRC;

// Estrutura de dados da lista ligadad
typedef struct lista
{
    Node *head;
    NodeR *headR;
    NodeRC *headRC;
    long int NELL;
    long int NELR;
    long int NELRC;
} Lista;

// Estrutura de dados de auxilo, so alocada quando necessaria
typedef struct
{
    char aux[MAX_S];
} Aux;

#endif // LISTA_H_INCLUDED
