#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

//STACK MENU (KATEGORI)
void CreateKategori(Kategori *S){
    S->top = Nil;
}

boolean isKategoriEmpty(Kategori S) {
    return (S.top == Nil);
}

void pushMenu(Kategori *S, Menu info) {
    adr_menu newNode = (adr_menu) malloc(sizeof(MenuStack));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->info.namaMenu, info.namaMenu);
    newNode->info.qty = info.qty;
    newNode->next = S->top;
    S->top = newNode;
}

MenuStack popMenu(Kategori *S) {
    MenuStack result = {"", 0, Nil};
    if (!isKategoriEmpty(*S)) {
        adr_menu temp = S->top;
        result = *temp;
        S->top = temp->next;
        free(temp);
    }
    return result;
}

void printStackKategori (Kategori S, const char *judulKategori) {
    adr_menu P = S.top;
    printf("%s\n", judulKategori);
    while (P != Nil) {
        printf("- %s (%d)\n", P->info.namaMenu, P->info.qty);
        P = P->next;
    }
}

//STACK UTAMA
void CreateStack (adr_stack *P) {
	*P = Nil;
}

boolean is_Empty (adr_stack P) {
	return (P == Nil);
}

void copyListPesanan(adr_pesanan head, Kategori *S) {
    CreateStack(S);

    Kategori appetizerStack;
    Kategori mainStack;
    Kategori dessertStack;

    CreateKategori(&appetizerStack);
    CreateKategori(&mainStack);
    CreateKategori(&dessertStack);

    adr_pesanan curr = head;
    while (curr != Nil) {
        if (strcmp(curr->data.kategori, "appetizer") == 0) {
            pushKategori(&appetizerStack, curr->data.namaMenu, curr->data.jumlah);
        } else if (strcmp(curr->data.kategori, "main") == 0) {
            pushKategori(&mainStack, curr->data.namaMenu, curr->data.jumlah);
        } else if (strcmp(curr->data.kategori, "dessert") == 0) {
            pushKategori(&dessertStack, curr->data.namaMenu, curr->data.jumlah);
        }
        curr = curr->next;
    }

    // Push ke stack utama dengan urutan APPETIZER -> MAIN -> DESSERT
    push(S, dessertStack, "DESSERT");
    push(S, mainStack, "MAIN COURSE");
    push(S, appetizerStack, "APPETIZER");
}

void push(adr_stack *top, Kategori data, const char *kategoriNama) {
	adr_stack newNode = (adr_stack) malloc(sizeof(NodeStack));
    if (newNode != Nil) {
        newNode->data = data;
        strcpy(newNode->kategoriNama, kategoriNama);
        newNode->next = *top;
        *top = newNode;
    }
}

Kategori Pop (adr_stack *top) {
	Kategori result;
    CreateKategori(&result);
    if (!is_Empty(*top)) {
        adr_stack temp = *top;
        result = temp->data;
        *top = temp->next;
        free(temp);
    } 
    return result;
}

void printAllPesanan (adr_stack P) {
    while (P != Nil){
        printStackKategori(P->data, P->kategoriNama);
        P = P->next;
    }
}