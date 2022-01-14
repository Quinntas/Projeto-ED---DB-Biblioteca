#ifndef TEXTO_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define TEXTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "Lista.h"
#include "Lista.h"
#include "Essentials.h"
#include "Hash.h"

//	Logs
void logIT(const char *logs);
void limparLogs();
//	Inicializacao
void gravarAreas(Lista *L);
void ordenarAreas(Lista *L);
void gravarAreasDesordenadas(Lista *L);
void gravarSobrenomes(Lista *L);
void preCarregaFuncoes(Lista *L);

//	Read Arqs
void lerArqRequisitantes(Lista *L, Freguesias *infoF);
int tamFreg();

// Write Arqs
void gravarArquivos(Lista *L, Freguesias *F);

#endif
