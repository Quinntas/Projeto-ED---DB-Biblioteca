#ifndef ESSENTIALS_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define ESSENTIALS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void limparbuffer();
void pausa();
bool checkDia(int dia, int mes, int ano);
int random_int(int min, int max);
float random_float(float a, float b);

#endif // ESSENTIALS_H_INCLUDED
