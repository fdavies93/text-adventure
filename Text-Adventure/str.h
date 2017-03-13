#pragma once

typedef struct str
{
	char* chars;
	unsigned int length;
} str;

str* str_init(const char*);
void str_destroy(str*);