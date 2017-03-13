#include "stdafx.h"
#include "gamedata.h"

gamedata* gamedata_init()
{
	gamedata* data;
	data = malloc(sizeof(gamedata));
	data->quit = 0;
	data->objectNum = 0;
	return data;
}

void gamedata_destroy(gamedata* toDestroy)
{
	for (int i = 0; i < toDestroy->objectNum; ++i)
	{
		gameobj_destroy(toDestroy->objects[i]);
	}
	printf("objects destroyed\n");
	free(toDestroy->objects);
	free(toDestroy);
}

/*
Ensure gameobj is dynamically allocated!
Adds gameobj pointed by toAdd to this data set's central array.
From this point on gamedata is considered to 'own' the gameobj.
*/
void gamedata_add_object(gamedata* data, gameobj* toAdd)
{
	if (data->objectNum == 0)
	{
		data->objects = malloc(sizeof(gameobj*));
	}
	else {
		data->objects = realloc(data->objects, sizeof(gameobj*) * (data->objectNum + 1));//expand or create array; not too efficient but eh
	}
	data->objects[data->objectNum] = toAdd;
	data->objectNum += 1;
}

void gamedata_set_player(gamedata* data, gameobj* player)
{
	data->player = player;
}