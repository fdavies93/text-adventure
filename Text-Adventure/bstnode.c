#include "stdafx.h"
#include "settings.h"
#include "bstnode.h"

bstnode* bstnode_init(char* key, void* object, int objtype)
{
	bstnode* returnNode = malloc(sizeof(bstnode));
	returnNode->key = malloc( sizeof(char) * (strlen(key)+1) );
	strcpy(returnNode->key,key);
	returnNode->left = NULL;
	returnNode->right = NULL;
	returnNode->parent = NULL;
	returnNode->object = object;
	returnNode->objtype = objtype;
	return returnNode;
}

//returns dest node after insert's been... inserted
//super useful for root nodes
bstnode* bstnode_insert(bstnode* insert, bstnode* dest)
{
	int comp;
	if (dest != NULL)
	{
#ifdef DEBUG
		//printf("%s\n",dest->key);
#endif
		comp = strcmp(insert->key, dest->key);
		if (comp < 0)
		{
			//dest is larger; go left
			if (dest->left == NULL)
			{
				dest->left = insert;
				insert->parent = dest;
			}
			else bstnode_insert(insert,dest->left);
		}
		else if (comp > 0)
		{
			//dest is smaller; go right
			if (dest->right == NULL)
			{
				dest->right = insert;
				insert->parent = dest;
			}
			else bstnode_insert(insert,dest->right);
		}
	}
	return dest;
}

//destroys self, promoting rightmost entry in left-hand tree
//if possible, or leftmost entry in right-hand tree if not

bstnode* bstnode_remove(bstnode* toRemove)
{
	bstnode* replacement = NULL;
	if (toRemove->left == NULL && toRemove->right == NULL)
	{
		if (toRemove->parent != NULL)
		{
			if (toRemove->parent->left == toRemove) toRemove->parent->left = NULL;
			else if (toRemove->parent->right == toRemove) toRemove->parent->right = NULL;
		}
		free(toRemove->key);
		free(toRemove);
	}
	else
	{
		if (toRemove->left != NULL)
		{
			replacement = bstnode_getright(toRemove->left);
		}
		else if (toRemove->right != NULL)
		{
			replacement = bstnode_getleft(toRemove->right);
		}
		toRemove->key = realloc(toRemove->key,sizeof(char)*(strlen(replacement->key)+1));
		strcpy(toRemove->key,replacement->key);
		toRemove->object = replacement->object;
		toRemove->objtype = replacement->objtype;
		bstnode_remove(replacement);
	}
	return toRemove;
}

//gets the leftmost node in the BST where this is the root
bstnode* bstnode_getleft(bstnode* base)
{
	if (base->left != NULL)
	{
		base = bstnode_getleft(base->left);
	}
	return base;
}

//gets the rightmost node in the BST where this is the root
bstnode* bstnode_getright(bstnode* base)
{
	if (base->right != NULL)
	{
		 base = bstnode_getright(base->right);
	}
	return base;
}

void bstnode_destroy(bstnode* toDestroy)
{
	free(toDestroy->key);
	free(toDestroy);
}

//destroys all children then self; implemented recursively
void bstnode_destroy_tree(bstnode* toDestroy)
{
	if (toDestroy->left != NULL) bstnode_destroy(toDestroy->left);
	if (toDestroy->right != NULL) bstnode_destroy(toDestroy->right);
	free(toDestroy->key);
	free(toDestroy);
}

//gets width of tree
void bstnode_getwidth(bstnode* toGet, int* carry)
{
	if (toGet->left != NULL) bstnode_getwidth(toGet->left, carry);
	
	if (toGet->right != NULL) bstnode_getwidth(toGet->right, carry);

	if (toGet->right == NULL && toGet->left == NULL) carry++;
}

void bstnode_print(bstnode* toPrint)
{
	printf("%s\n",toPrint->key);
	if (toPrint->left != NULL)
	{
		printf("LEFT> ");
		bstnode_print(toPrint->left);
		printf("UP>");
	}
	if (toPrint->right != NULL)
	{
		printf("RIGHT> ");
		bstnode_print(toPrint->right);
		printf("UP>");
	}
}