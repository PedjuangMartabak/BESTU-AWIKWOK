#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "queue.h"

typedef struct {
    char namaMenu[50];
    int qty;
}Menu;

typedef struct tNodeMenu *adr_menu;
typedef struct tNodeMenu {
    Menu info;
    adr_menu next;
}MenuStack;

typedef struct {
    adr_menu top;
}Kategori;

typedef struct tNodeStack *adr_stack;
typedef struct tNodeStack {
    Kategori data;
    char kategoriNama[20];
    adr_stack next;
} NodeStack;

//STACK MENU (KATEGORI)
void CreateKategori(Kategori *S);
boolean isKategoriEmpty(Kategori S);
void pushMenu(Kategori *S, Menu info);
MenuStack popMenu(Kategori *S);
void printStackKategori (Kategori S, const char *judulKategori);

//STACK UTAMA
void CreateStack (adr_stack *P);
boolean is_Empty (adr_stack P);
void copyListPesanan(adr_pesanan head, adr_stack *S);
void push(adr_stack *top, Kategori data, const char *kategoriNama);
Kategori Pop (adr_stack *top);
void printAllPesanan (adr_stack P);

#endif