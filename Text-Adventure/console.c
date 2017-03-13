#include "stdafx.h"
#include "settings.h"
#include "console.h"

void print(const char* toPrint)
{
	printf(toPrint);
}

char* getLine()
{
	char buffer[CHAR_BUFFER];
	char* returnStr;

	fgets(buffer, 256, stdin);

	returnStr = malloc((strlen(buffer) + 1) * sizeof(char));

	memcpy(returnStr, buffer, (strlen(buffer) + 1) * sizeof(char));

	return returnStr;
}