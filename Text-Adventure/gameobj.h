#pragma once

typedef struct gameobj
{
	char* name;
	char* description;
	struct gameobj* parent;
	struct gameobj** children;
	int childNum;
} gameobj;

gameobj* gameobj_init();
void gameobj_destroy(gameobj*);
void gameobj_add_parent(gameobj*, gameobj*);
void gameobj_add_child(gameobj*, gameobj*);