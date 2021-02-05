// Main include file
#ifndef _INCLUDE
#define _INCLUDE

#define _LINUX

#ifdef _WINDOWS
#define CLEAR "cls"
#elif defined(_LINUX)
#define CLEAR "clear"
#endif

#include <stdio.h>
#include <stdlib.h> // system
#include <unistd.h>

typedef struct{
    int Hours;
    int Minutes;
    int Seconds;
} time;

#endif