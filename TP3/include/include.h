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
#include <string.h>

#include "type.h"
#include "function.h"

#endif