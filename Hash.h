#ifndef HASH_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define HASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "Essentials.h"
#include "Lista.h"
#include "Texto.h"

// Estrutura de dados dos nos dos hashs
typedef struct nodeH
{
    char *key;
    struct nodeH *nextkey;
    Lista *ListaH;
} NodeH;

// Estrutura de dados da cabeça de um hash
typedef struct
{
    NodeH *headH;
    int NEL;
} Hashtable;

#endif // HASH_H_INCLUDED
