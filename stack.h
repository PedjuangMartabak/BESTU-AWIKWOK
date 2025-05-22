#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

typedef struct Pesanan { 
    char namaMenu[50];
    int jumlah;
    int hargaSatuan;
} Pesanan;

typedef struct tNodePesanan *adr_pesanan;
typedef struct tNodePesanan {
    Pesanan data;
    adr_pesanan next;
} NodePesanan;

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
void push(adr_riwayat *top, Riwayat data);
Riwayat Pop (adr_riwayat *top);
void printRiwayatUser(adr_riwayat Top, char namaCari[]);

#endif