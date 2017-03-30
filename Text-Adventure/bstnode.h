#pragma once

typedef struct bstnode
{
	char* key;
	struct bstnode *left, *right, *parent;
	void* object;
	int objtype;
} bstnode;

bstnode* bstnode_init(char*, void*, int);
bstnode* bstnode_insert(bstnode*, bstnode*);
bstnode* bstnode_remove(bstnode*);
bstnode* bstnode_getleft(bstnode*);
bstnode* bstnode_getright(bstnode*);
void bstnode_destroy(bstnode*);
void bstnode_destroy_tree(bstnode*);
void bstnode_getwidth(bstnode*, int*);
void bstnode_print(bstnode*);
bstnode* bstnode_search(bstnode*,char*);