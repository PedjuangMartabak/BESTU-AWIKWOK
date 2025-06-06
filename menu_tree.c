#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu_tree.h"
#include "boolean.h"

address CreateNode (const char* name, int isItem, float price) {
	address newNode = (address)malloc(sizeof(MenuNode));
	strcpy(newNode->name, name);
    newNode->isItem = isItem;
    newNode->price = price;
    newNode->fs = newNode->nb = newNode->pr = Nil;
    return newNode;
}

address SearchMenu (address root, const char *name) {
	if (root == Nil) return Nil;
	if (strcmp(root->name, name) == 0) return root;
	address found = SearchMenu(root->fs, name);
    if (found != Nil) return found;
    return SearchMenu(root->nb, name);
}

void PreOrder(address node) {
    if (node == Nil) return;
    printf("%s\n", node->name);
    PreOrder(node->fs);
    PreOrder(node->nb);
}

void PostOrder(address node) {
    if (node == Nil) return;
    PostOrder(node->fs);
    PostOrder(node->nb);
    printf("%s\n", node->name);
}

void PrintTree(address node, int level) {
    if (node == Nil) return;
    for (int i = 0; i < level; i++) printf("  ");
    if (node->isItem)
        printf("- %s (Rp%.2f)\n", node->name, node->price);
    else
        printf("%s:\n", node->name);
    PrintTree(node->fs, level + 1);
    PrintTree(node->nb, level);
}

void InsertMenu(address *root) {
    char name[50], category[50];
    int isItem;
    float price = 0.0;

    printf("Masukkan nama untuk item/kategori baru: ");
    scanf(" %[^\n]", name);
    printf("Keterangan input [1 = Menu, 0 = Kategori]: ");
    scanf("%d", &isItem);
    if (isItem) {
        printf("Masukkan harga dalam Rp: ");
        scanf("%f", &price);
    }
    printf("Masukkan kategori yang akan menampung input (masukkan 'root' untuk root/menu): ");
    scanf(" %[^\n]", category);
    if (strcmp(category, "root") == 0) {
        if (*root == Nil) {
            *root = CreateNode(name, isItem, price);
            printf("Menu telah dibuat sebagai root.\n");
        } else {
            address newNode = CreateNode(name, isItem, price);
            newNode->nb = (*root)->fs;
            newNode->pr = *root;
            (*root)->fs = newNode;
            printf("Input telah dimasukkan di bawah root.\n");
        }
    } else {
        address parent = SearchMenu(*root, category);
        if (parent == Nil) {
            printf("Kategori tidak ditemukan.\n");
            return;
        }

        address newNode = CreateNode(name, isItem, price);
        newNode->nb = parent->fs;
        newNode->pr = parent;
        parent->fs = newNode;
        printf("Input telah dimasukkan di bawah %s.\n", category);
    }
}

void DeleteMenu(address *root, const char *name) {
    if (root == Nil || *root == Nil) return;
    address target = SearchMenu(*root, name);
    if (target == Nil || target == *root) {
        printf("Tidak bisa menghapus root atau node yang tidak ada.\n");
        return;
    }
    address parent = target->pr;
    address *ptr = &(parent->fs);
    while (*ptr != Nil && *ptr != target) {
        ptr = &((*ptr)->nb);
    }
    if (*ptr == target) {
        *ptr = target->nb;
    }
    while (target->fs != Nil) {
        DeleteMenu(&(target->fs), target->fs->name);
    }
    free(target);
    printf("Telah menghapus %s.\n", name);
}

/*      == FILING SING PUSINKK ==    tba    */
