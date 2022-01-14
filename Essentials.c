#define _CRT_SECURE_NO_WARNINGS

#include "Essentials.h"

// Limpeza de buffer
void limparbuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Funcao auxiliar de pausa
void pausa()
{
    printf("\n|| ");
    system("pause");
}

// Funcao que verifica se e um ano leap
bool isLeapYear(int ano)
{
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
        return true;
    else
        return false;
}

// Checar se o dia dado esta certo
bool checkDia(int dia, int mes, int ano)
{
    /*
    time_t mytime;
    mytime = time(NULL);
    struct tm hr = *localtime(&mytime);
    if (ano > hr.tm_year + 1898)
    {
        return false;
    }
    */
    if (mes < 1 || mes > 12)
    {
        return false;
    }
    int bxt = 0;
    if (isLeapYear(ano) == true)
    {
        bxt = 1;
    }
    if (bxt == 1 && mes == 2)
    {
        if (dia > 29 || dia < 1)
        {
            return false;
        }
    }
    else if (bxt == 0 && mes == 2)
    {
        if (dia > 28 || dia < 1)
        {
            return false;
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia > 30 || dia < 1)
        {
            return false;
        }
    }
    else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
    {
        if (dia > 31 || dia < 1)
        {
            return false;
        }
    }
    return true;
}

// Funcao que retorna um numero aleatorio inteiro
int random_int(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

// Funcao que retorna um numero aleatorio real
float random_float(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX) + a);
}

// Funcao que apartir de um contador, devolve um nome depois de um espaco (GENERICO)
const char *pegarSobrenomeGererico(const char *nome)
{
    int stringSize = strlen(nome);
    const char *returnValue = nome;
    int count = 1; // Valor que pode ser mudado para pegar qualquer parte de uma string, separado por ' '
    while (count != 0)
    {
        if (nome[stringSize] == ' ')
            count--;
        stringSize--;
    }
    return returnValue += stringSize + 2;
}
