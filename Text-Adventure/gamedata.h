#pragma once
#include "gameobj.h"
#include "bstnode.h"
#include "parser.h"

typedef struct
{
	int quit;//0 is false, 1 is true
	gameobj** objects;
	int objectNum;
	gameobj* player;
	bstnode* words;
	verb** verbs;
	noun** nouns;
} gamedata;

gamedata* gamedata_init();
void gamedata_destroy(gamedata*);

void gamedata_add_object(gamedata*, gameobj*);

void gamedata_set_player(gamedata*, gameobj*);