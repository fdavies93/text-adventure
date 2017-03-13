#include "stdafx.h"
#include "core.h"
#include "settings.h"
#include "gamedata.h"
#include "gameobj.h"

char* strlower(char* lowerThis, int strLen)
{
	char* returnStr = calloc(strLen,sizeof(char));
	for (int i = 0; lowerThis[i] != '\0'; ++i)
	{
		returnStr[i] = tolower(lowerThis[i]);
	}
}

char** splitLine(const char* toSplit, int* tokenNum)
{

	//seem to be issues relating to what's actually in the returned string of tokens
	char* curStr = strtok(toSplit, " \n");
	char* wordBuffer[WORD_BUFFER];
	char** returnWords;
	int wordCount = 0;

	while (curStr != NULL)
	{
		wordBuffer[wordCount] = malloc((strlen(curStr) + 1) * sizeof(char));
		memcpy(wordBuffer[wordCount], curStr, strlen(curStr) + 1);
		//necessary because strtok doesn't create a new string but creates a pointer in the original string
		for (int i = 0; wordBuffer[wordCount][i] != '\0'; ++i)
		{
			wordBuffer[wordCount][i] = tolower(wordBuffer[wordCount][i]);
		}
#ifdef DEBUG
		printf("Word %d: %s\n", wordCount, wordBuffer[wordCount]);
#endif
		++wordCount;
		curStr = strtok(NULL, " \n");
	}

	*tokenNum = wordCount;
	returnWords = malloc(sizeof(char*) * wordCount);
	memcpy(returnWords, wordBuffer, sizeof(char*) * wordCount);
	//a cute way of making sure you only get an array of the size you want / need; inspired by approach to strings
	return returnWords;
}

void processInput(const char** tokens, int tokenNum, gamedata* const state)
{
	//validation that pointers are non-null plz
	gameobj* parent = state->player->parent;
	if (tokenNum > 0)
	{
		if (strcmp(tokens[0], "look") == 0)
		{
			if (tokenNum == 1)
			{
				print(state->player->parent->name);
				print("\n\n");
				print(state->player->parent->description);
				print("\n\n");
				print("You can see here: ");
				for (int i = 0; i < state->player->parent->childNum; ++i)
				{
					if (state->player != state->player->parent->children[i])
					{
						print(state->player->parent->children[i]->name);
						if (i < state->player->parent->childNum - 1) print(", ");
					}
				}
				print("\n\n");
			}
			else
			{
				for (int i = 0; i < parent->childNum; ++i)
				{
					if (strcmp(strlower(parent->children[i]->name,strlen(parent->children[i]->name)), tokens[1]) == 0)
					{
						print(parent->children[i]->description);
						print("\n\n");
					}
				}
			}
		}

		else if (strcmp(tokens[0], "!quit") == 0)
		{
			state->quit = 1;
		}
		else if (strcmp(tokens[0], "!help") == 0)
		{
			print("------------HELP------------\n");
			print("!help for help\n");
			print("!quit to quit \n");
#ifdef DEBUG
			print("-----------DEBUG------------\n");
			print("!objects to show all objects\n");
#endif
			print("----------------------------\n");
		}
		//magic godmode commands below
#ifdef DEBUG
		else if (strcmp(tokens[0], "!objects") == 0)
		{
			char* tempstr;
			for (int i = 0; i < state->objectNum; ++i)
			{
				print("[");
				tempstr = calloc(10, sizeof(char));
				sprintf(tempstr, "%d", i);
				print(tempstr);
				print("] ");
				print(state->objects[i]->name);
				print("\n");
			}
		}
#endif
		else 
		{
			print("I don't know what you mean.\n");
		}
	}
}