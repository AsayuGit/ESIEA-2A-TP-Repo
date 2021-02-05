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
#include <time.h>

#include "types.h"

#include "function.h"

#endif