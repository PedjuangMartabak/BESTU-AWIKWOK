#ifndef MENU_TREE_H
#define MENU_TREE_H
#include "boolean.h"
#include <stdio.h>

typedef struct tElmtTree *treeAddress;
typedef struct tElmtTree {
	char name[50];
	int isItem;
	float price;
	treeAddress fs;
	treeAddress nb;
	treeAddress pr;
} MenuNode;

treeAddress CreateNode (const char* name, int isItem, float price);
treeAddress SearchMenu (treeAddress root, const char *name);
void PreOrder(treeAddress node);
void PostOrder(treeAddress node);
void PrintTree(treeAddress node, int level);
void InsertMenu(treeAddress *root);
void DeleteSubtree(treeAddress node);
void DeleteMenu(treeAddress *root, const char *name);
void File_SaveTree (treeAddress root, FILE *fp);
treeAddress File_LoadTreeHelper(FILE *fp, treeAddress parent);
treeAddress File_LoadTree(const char *filename);
const char* getParentCategory(treeAddress item);

void displayManageMenu();
void CariMenu (treeAddress root);
void ManageMenu (treeAddress root);

#endif