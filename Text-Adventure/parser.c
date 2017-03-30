#include "stdafx.h"
#include "parser.h"

#define TOKEN_BUFFER_SIZE 256

parsetoken* parsetoken_init(int type, void* object)
{
	parsetoken* myToken = malloc(sizeof(parsetoken));
	myToken->type = type;
	myToken->object = object;
}

parsetoken** lex(gamedata* world, char* strin)
{
	char* prev = strin;
	char prevChar;
	char* pos = strin;
	bstnode* wordnode;
	parsetoken* curtoken = NULL;
	parsetoken* buffer[TOKEN_BUFFER_SIZE];
	int tokenindex = 0;
	while (*pos != '\0')
	{
		if (*pos == ' ' || *pos == '\n')
		{
			prevChar = *pos;
			*pos = '\0';
			wordnode = bstnode_search(world->words, prev);
			if (wordnode != NULL)
			{
				curtoken = parsetoken_init(wordnode->objtype, wordnode->object);
				buffer[tokenindex] = curtoken;
				++tokenindex;
				++pos;
				prev = pos;
			}
			else 
			{
				*pos = prevChar;
			}
		}
		pos += sizeof(char);
	}
}

void parse(gamedata* world, parsetoken** tokens)
{

}