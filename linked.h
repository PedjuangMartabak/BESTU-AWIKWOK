/* File        : linked.h */
/* Deskripsi   : header file ADT linked list dengan representasi fisik pointer */

#ifndef LINKED_H
#define LINKED_H
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "boolean.h"

typedef struct Pesanan { 
    char namaMenu[50];
    char kategori[20]; //"appetizer"/"main"/"dessert"
    int jumlah;
    int hargaSatuan;
} Pesanan;

typedef struct tNodePesanan *adr_pesanan;
typedef struct tNodePesanan {
    Pesanan data;
    adr_pesanan next;
} NodePesanan;

typedef struct Pelanggan {
	char namaPelanggan[50];
    int noTelp;
    int jmlOrang;
    struct tm waktu;
	adr_pesanan listPesanan;
}Pelanggan;

typedef struct tElmtlist *address;
typedef struct tElmtlist {
    adr_pesanan dataPesanan;
	Pelanggan dataPelanggan;
	address next;
} NodeQueue;

extern address First;

boolean isEmpty(address p);
void Create_Node (address *p);
void Isi_Node (address *p , Pelanggan data);
void Print_List (address p);
void Insert_AtFirst (address *First, Pelanggan data);
void Insert_AtLast (address *First, Pelanggan data);

void Delete_AtFirst(address *First);
void Delete_AtLast(address *First);
void Delete_All(address *First);

#endif
