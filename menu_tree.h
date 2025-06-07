#ifndef MENU_TREE_H
#define MENU_TREE_H
#include "boolean.h"

typedef struct tElmtTree *address;
typedef struct tElmtTree {
	char name[50];
	int isItem;
	float price;
	address fs;
	address nb;
	address pr;
} MenuNode;

address CreateNode (const char* name, int isItem, float price);
address SearchMenu (address root, const char *name);
void PreOrder(address node);
void PostOrder(address node);
void PrintTree(address node, int level);
void InsertMenu(address *root);
void DeleteMenu(address *root, const char *name);
void File_SaveTree (address root, FILE *fp);
address File_LoadTreeHelper(FILE *fp, address parent);
address File_LoadTree(const char *filename);

#endif