#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void CreateStack (adr_riwayat *P) {
	*P = Nil;
}

boolean is_Empty (adr_riwayat P) {
	return (P == Nil);
}

boolean is_Full (adr_riwayat P) {
	return 0;
}

adr_pesanan copyListPesanan(adr_pesanan head) {
    if (head == Nil) {
        return Nil;
    }
    adr_pesanan newHead = (adr_pesanan)malloc(sizeof(NodePesanan));
    if (newHead == Nil) {
        return Nil;
    }

    newHead->data = head->data;
    newHead->next = Nil;

    adr_pesanan tempSrc = head->next;
    adr_pesanan tempDest = newHead;

    while (tempSrc != Nil) {
        adr_pesanan newNode = (adr_pesanan) malloc(sizeof(NodePesanan));
        if (newNode == Nil) break;
        newNode->data = tempSrc->data;
        newNode->next = Nil;
        tempDest->next = newNode;
        tempDest = newNode;
        tempSrc = tempSrc->next;
    }

    return newHead;
}

void push(adr_riwayat *top, Riwayat data) {
	adr_riwayat newNode = (adr_riwayat) malloc(sizeof(NodeStack));
    if (newNode != Nil) {
        newNode->data = data;
        newNode->data.daftarPesanan = copyListPesanan(data.daftarPesanan);
        newNode->next = *top;
        *top = newNode;
    }
}

Riwayat Pop (adr_riwayat *top) {
	Riwayat result;

    if (!is_Empty(*top)) {
        adr_riwayat temp = *top;
        result = temp->data;
        *top = temp->next;
        free(temp);
    } else {
        printf("Tidak ada riwayat transaksi.\n");
        strcpy(result.namaPelanggan, "-");
        strcpy(result.layanan, "-");
        result.nomorMeja = -1;
    }

    return result;
}

void printPesananList (adr_pesanan p) {
	while (p != Nil){
        printf("%dx\t", p->data.jumlah);
        printf("Rp%d\n", p->data.hargaSatuan);
        printf("%s\n", p->data.namaMenu);
        p = p->next;
    }
    printf("NULL\n");
}

void printRiwayatUser(adr_riwayat Top, char namaCari[]) {
    printf("\nRiwayat Peminjaman untuk pelanggan %s:\n", namaCari);
    int found = 0;
    while (Top != Nil) {
        if (strcmp(Top->data.namaPelanggan, namaCari) == 0) {
            printf("Layanan: %s\n", Top->data.layanan);
            if (strcmp(Top->data.layanan, "DineIn") == 0)
                printf("Nomor Meja: %d\n", Top->data.nomorMeja);
            printf("Pesanan:\n");
            printPesananList(Top->data.daftarPesanan);
            found = 1;
        }
        Top = Top->next;
    }
    if (!found) {
        printf("Tidak ada riwayat pemesanan.\n");
    }
}


