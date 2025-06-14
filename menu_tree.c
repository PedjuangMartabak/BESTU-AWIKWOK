#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu_tree.h"
#include "boolean.h"

treeAddress CreateNode (const char* name, int isItem, float price) {
	treeAddress newNode = (treeAddress)malloc(sizeof(MenuNode));
	strcpy(newNode->name, name);
    newNode->isItem = isItem;
    newNode->price = price;
    newNode->fs = Nil;
    newNode->nb = Nil;
    newNode->pr = Nil;
    return newNode;
}

treeAddress SearchMenu (treeAddress root, const char *name) {
	if (root == Nil) return Nil;
	if (strcmp(root->name, name) == 0) return root;
	treeAddress found = SearchMenu(root->fs, name);
    if (found != Nil) return found;
    return SearchMenu(root->nb, name);
}

void PreOrder(treeAddress node) {
    if (node == Nil) return;
    printf("%s\n", node->name);
    PreOrder(node->fs);
    PreOrder(node->nb);
}

void PostOrder(treeAddress node) {
    if (node == Nil) return;
    PostOrder(node->fs);
    PostOrder(node->nb);
    printf("%s\n", node->name);
}

void PrintTree(treeAddress node, int level) {
    if (node == Nil) return;
    for (int i = 0; i < level; i++) printf("  ");
    if (node->isItem)
        printf("- %s (Rp%.2f)\n", node->name, node->price);
    else
        printf("%s:\n", node->name);
    PrintTree(node->fs, level + 1);
    PrintTree(node->nb, level);
}

void InsertMenu(treeAddress *root) {
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
            treeAddress newNode = CreateNode(name, isItem, price);
            newNode->nb = (*root)->fs;
            newNode->pr = *root;
            (*root)->fs = newNode;
            printf("Input telah dimasukkan di bawah root.\n");
        }
    } else {
        treeAddress parent = SearchMenu(*root, category);
        if (parent == Nil) {
            printf("Kategori tidak ditemukan.\n");
            return;
        }

        treeAddress newNode = CreateNode(name, isItem, price);
        newNode->nb = parent->fs;
        newNode->pr = parent;
        parent->fs = newNode;
        printf("Input telah dimasukkan di bawah %s.\n", category);
    }
    FILE *fp = fopen("menu.txt", "w");
    if (fp != Nil) {
        File_SaveTree(*root, fp);
        fclose(fp);
    } else {
        printf("Gagal menyimpan menu ke file.\n");
    }
}

void DeleteSubtree(treeAddress node) {
    if (node == Nil) return;
    DeleteSubtree(node->fs);
    DeleteSubtree(node->nb);
    free(node);
}

void DeleteMenu(treeAddress *root, const char *name) {
    if (root == Nil || *root == Nil) return;
    treeAddress target = SearchMenu(*root, name);
    if (target == Nil || target == *root) {
        printf("Tidak bisa menghapus root atau node yang tidak ada.\n");
        return;
    }
    treeAddress parent = target->pr;
    treeAddress *ptr = &(parent->fs);
    while (*ptr != Nil && *ptr != target) {
        ptr = &((*ptr)->nb);
    }
    if (*ptr == target) {
        *ptr = target->nb;
    }
    DeleteSubtree(target->fs);
    free(target);
    printf("Telah menghapus %s.\n", name);
    
    FILE *fp = fopen("menu.txt", "w");
    if (fp != Nil) {
        File_SaveTree(*root, fp); 
        fclose(fp);
    } else {
        printf("Gagal menyimpan menu ke file.\n");
    }
}

void File_SaveTree(treeAddress root, FILE *fp) {
    if (root == Nil || fp == Nil) return;
    
    fprintf(fp, "%s|%d|%.2f\n", root->name, root->isItem, root->price);
    
    if (root->fs != Nil) {
        File_SaveTree(root->fs, fp);
        fprintf(fp, "END\n");
    }

    File_SaveTree(root->nb, fp);
}

treeAddress File_LoadTreeHelper(FILE *fp, treeAddress parent) {
    char line[100];
    treeAddress head = Nil, prev = Nil;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, "END") == 0) {
            return head;
        }
        char name[50];
        int isItem;
        float price;
        if (sscanf(line, " %[^|]|%d|%f", name, &isItem, &price) != 3) {
            printf("Invalid line: %s\n", line);
            continue;
        }
        treeAddress newNode = CreateNode(name, isItem, price);
        newNode->pr = parent;
        if (head == Nil) {
            head = newNode;
        } else {
            prev->nb = newNode;
        }
        if (!isItem) {
            newNode->fs = File_LoadTreeHelper(fp, newNode);
        }
        prev = newNode;
    }
    return head;
}

treeAddress File_LoadTree(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == Nil) {
        printf("File tidak ditemukan.\n");
        return Nil;
    }
    treeAddress root = File_LoadTreeHelper(fp, Nil);
    fclose(fp);
    return root;
}