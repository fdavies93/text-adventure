#include "stdafx.h"
#include "gameobj.h"

gameobj* gameobj_init()
{
	gameobj* newObj = malloc(sizeof(gameobj));
	newObj->childNum = 0;
	newObj->name = "New Object";
	newObj->description = "<Your description here>";
	return newObj;
}

void gameobj_destroy(gameobj* toDestroy)
{
	//free(toDestroy->name);
	//free(toDestroy->description);
	//as names and descriptions aren't dynamically allocated, free()ing them does nothing but crash the application
	free(toDestroy);
}

//revise the below to mutually call one another after checking whether already called (to prevent infinite recurrence)

void gameobj_add_parent(gameobj* subject, gameobj* newParent)
{
	subject->parent = newParent;
	gameobj_add_child(newParent, subject);
}

void gameobj_add_child(gameobj* subject, gameobj* newChild)
{
	//printf("%d", subject->childNum);
	if (subject->childNum == 0)
	{
		subject->children = malloc(sizeof(gameobj*));
		subject->children[0] = newChild;
	}
	else
	{
		subject->children = realloc(subject->children, (subject->childNum + 1) * sizeof(gameobj*) );
		subject->children[subject->childNum] = newChild;
	}
	subject->childNum += 1;
}