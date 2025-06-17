#ifndef QUEUE_H
#define QUEUE_H

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
    int noTelp[15];
    int total_orang;
    char jam_kedatangan[6];
    int no_meja[3];
    int jmlMeja;
	adr_pesanan listPesanan;
}Pelanggan;

typedef struct tElmtlist *address;
typedef struct tElmtlist {
	Pelanggan dataPelanggan;
	address next;
} NodeQueue;

typedef struct {
    address front;
} PriorityQueue;

void CreatePriorityQueue(PriorityQueue *Q);
boolean isQueueEmpty(PriorityQueue Q);
void enqueue(PriorityQueue *Q, Pelanggan data);
void dequeue(PriorityQueue *Q, Pelanggan *data);
void printQueue(PriorityQueue Q);

#endif