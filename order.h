#ifndef ORDER_H
#define ORDER_H
#include "menu_tree.h"
#include "stack.h"
#include "boolean.h"

void toLowercase (char *hasil, const char *input);
boolean cekIsiKata (const char* kalimat, const char *kataIsi);
void findMatch (treeAddress node, const char* input, treeAddress hasil[], int *count, int maxCount);
treeAddress inputItem (treeAddress root);
void PushCategory (adr_stack *orders, treeAddress menuItem, int qty);
void getOrder (treeAddress root, adr_stack orders);

#endif