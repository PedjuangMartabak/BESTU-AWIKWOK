#ifndef MENU_TREE_H
#define MENU_TREE_H

typedef struct tElmtTree *address;
typedef struct tElmtTree {
	char name[50];
	int isItem;
	float price;
	address MenuNode *fs;
	address MenuNode *nb;
	address MenuNode *pr;
} MenuNode;

#endif