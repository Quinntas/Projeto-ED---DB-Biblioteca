#ifndef CSSC_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define CSSC_H_INCLUDED

#ifdef __WIN32
#define OS_Windows
#include <Windows.h>
#elif __unix__
#define OS_Linux
#include <unistd.h>
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Lista.h"

#endif // CSSC_H_INCLUDED
