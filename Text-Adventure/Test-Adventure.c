// Text-Adventure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core.h"
#include "settings.h"
#include "gamedata.h"
#include "gameobj.h"
#include "bstnode.h"



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
	
	/*gamedata* state = gamedata_init();

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
	char** myWords;

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

	gamedata_destroy(state);//this destroys all objects; therefore it's the major clean-up function
	*/
	bstnode* root = bstnode_init("f", NULL, BST_NODE_TYPE_OBJECT);
	bstnode_insert(bstnode_init("k", NULL, BST_NODE_TYPE_OBJECT), root);
	bstnode_insert(bstnode_init("a",NULL,BST_NODE_TYPE_OBJECT) , root);
	bstnode_insert(bstnode_init("p", NULL, BST_NODE_TYPE_OBJECT), root);
	bstnode_insert(bstnode_init("d", NULL, BST_NODE_TYPE_OBJECT), root);
	bstnode_insert(bstnode_init("e", NULL, BST_NODE_TYPE_OBJECT), root);
	bstnode_insert(bstnode_init("b", NULL, BST_NODE_TYPE_OBJECT), root);
	
	//bstnode_remove(root->left);

	//bstnode_print(bstnode_search(root, "a"));
	//bstnode_remove(root);
	//print("\n");
	//bstnode_print(root);

	system("PAUSE");

	return 0;
}