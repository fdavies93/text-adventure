#pragma once
#include "settings.h"
#include "gamedata.h"
#if OUTPUT_MODE == OUTPUT_CONSOLE
#include "console.h"
#endif
char** splitLine(const char*, int*);
void processInput(const char**, int, gamedata* const);

//these are defined in console.c, not core.c, breaking with usual standards
//this is deliberate; in future releases it'd be cool to add various output modes 
void print(const char*);
char* getLine();