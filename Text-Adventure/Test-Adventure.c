// Text-Adventure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console.h"
#include "settings.h"
#include "gamedata.h"
#include "gameobj.h"

char** splitLine(const char* toSplit, int* tokenNum)
{
	char* curStr = strtok(toSplit, " \n");
	char* wordBuffer[WORD_BUFFER];
	char** returnWords;
	int wordCount = 0;

	while (curStr != NULL)
	{
		wordBuffer[wordCount] = malloc((strlen(curStr) + 1) * sizeof(char));
		memcpy(wordBuffer[wordCount], curStr, strlen(curStr) + 1);
		//necessary because strtok doesn't create a new string but creates a pointer in the original string
		++wordCount;
#ifdef DEBUG
		printf("Word %d: %s\n", wordCount, curStr);
#endif
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

	if (strcmp(tokens[0],"look") == 0)
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
				if (strcmp(parent->children[i]->name, tokens[1]) == 0)
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
			sprintf(tempstr,"%d",i);
			print(tempstr);
			print("] ");
			print(state->objects[i]->name);
			print("\n");
		}
	}
#endif
}


int main()
{
#if OS_PLATFORM == OS_WINDOWS
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= 0x0004;//ENABLE_VIRTUAL_TERMINAL_PROCESSING
					 //note above is equivalent to dwMode = dwMode | 0x0004
					 //i.e. it sets the flag at 0x0004 to true while retaining other settings
					 //the reverse would be an xor allocation (^=)
	SetConsoleMode(hOut, dwMode);
#endif
	gamedata* state = gamedata_init();
	gameobj* player = gameobj_init();
	player->name = "You";
	player->description = "What a handsome devil!";
	gamedata_add_object(state, player);

	
	gameobj* room = gameobj_init();
	room->name = "Dark Room";
	room->description = "A dark and dingy room. It stinks of mildew.";
	gamedata_add_object(state, room);
	
	gameobj* box = gameobj_init();
	box->name = "Box";
	box->description = "A roughly-constructed wooden box.";
	gamedata_add_object(state, box);

	gameobj_add_parent(player, room);
	gameobj_add_parent(box, room);
	gamedata_set_player(state, player);
	
	int wordNum = 0;
	char* myStr;
	char** myWords = malloc(sizeof(char*));
	myWords[0] = calloc(1, sizeof(char));//makes a dummy string; probably bad practice
	printf(" ------------------ \r\n");
	printf("| Welcome to TEXT! |\r\n");
	printf("|------------------|\r\n");
	printf("|  !help for help  |\r\n");
	printf("| or !quit to quit |\r\n");
	printf(" ------------------ \r\n");
	
	while (state->quit == 0)
	{
		printf("> ");
		myStr = getLine();
		myWords = splitLine(myStr, &wordNum);
		processInput(myWords, wordNum, state);
	}
	return 0;
}