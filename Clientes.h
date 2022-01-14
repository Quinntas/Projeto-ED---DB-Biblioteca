#ifndef CLIENTES_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define CLIENTES_H_INCLUDED

#include "Lista.h"
#include "Essentials.h"
#include "Texto.h"

// Estrutura da dados para a Avaliacao
typedef struct
{
    float valor;
    char *descricao;
    char *nomeDoAvaliador;
    Data diaDaAvaliacao;
}Avaliacao;

#endif // CLIENTES_H_INCLUDED
