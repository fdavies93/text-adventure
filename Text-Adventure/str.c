#include "str.h"
#include "stdafx.h"

str* str_init(const char* toCreate)
{
	str* newStr = malloc(sizeof(str));
	newStr->length = strlen(toCreate) + 1;
	newStr->chars = malloc(newStr->length * sizeof(char));
	memcpy(newStr->chars, toCreate, newStr->length * sizeof(char));
	//no validation but eh
}

void str_destroy(str* toDestroy)
{
	free(toDestroy->chars);
	free(toDestroy);
}