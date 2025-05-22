#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "linked.h"

typedef struct Riwayat {
    char namaPelanggan[50];
    char layanan[10]; // "DineIn atau TakeAway"
    int nomorMeja; // -1 jika TakeAway
    adr_pesanan daftarPesanan;
} Riwayat;

typedef struct tNodeStack *adr_riwayat;
typedef struct tNodeStack {
    Riwayat data;
    adr_riwayat next;
} NodeStack;

void CreateStack (adr_riwayat *P);
boolean is_Empty (adr_riwayat P);
boolean is_Full (adr_riwayat P);
adr_pesanan copyListPesanan(adr_pesanan head);
void push(adr_riwayat *top, Riwayat data);
Riwayat Pop (adr_riwayat *top);
void printPesananList (adr_pesanan p);
void printRiwayatUser(adr_riwayat Top, char namaCari[]);

#endif