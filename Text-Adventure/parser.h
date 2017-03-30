#pragma once
#include "gamedata.h"

#define PARSE_TYPE_VERB 0
#define PARSE_TYPE_NOUN 1

/*
this is where the real meat of the engine comes in
a brief outline:
[verb] is the most basic format: 'look' - which can unfold to a variety of things but means 'LOOK at my LOCATION and CONTENTS OF LOCATION'
VERBs determine much of the meaning of many of their following formats
[verb] [noun] is also possible: 'look box' - i.e. perform verb LOOK on the noun BOX
[verb] [determinant] [noun] works too 'look at box' - i.e. perform verb 
[verb] [determinant] [number/abstract designation] [noun] gets more complex: 'look at the box'
*/

typedef struct {
	void(*function)(gamedata*,gameobj*);
} verb;

typedef struct {
	gameobj** objects;
} noun;

typedef struct {
	char* name;
	int type;
	void* object;
} parsetoken;

parsetoken* parsetoken_init(int type, void* object);
parsetoken** lex(gamedata*, char*);
void parse(gamedata*, parsetoken**);