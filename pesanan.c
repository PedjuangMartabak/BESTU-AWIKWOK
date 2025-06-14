#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesanan.h"

adr_pesanan First;

boolean isEmpty(adr_pesanan p) {
	return (p == Nil);
}

void Create_Node (adr_pesanan *p) {
	*p = (adr_pesanan) malloc(sizeof(NodePesanan));
    if (*p != Nil) {
        next(*p) = Nil;
    }
}

void Isi_Node (adr_pesanan *p , Pesanan nilai) {
	if (*p != Nil) {
        strcpy((*p)->data.namaMenu, nilai.namaMenu);
        strcpy((*p)->data.kategori, nilai.kategori);
        (*p)->data.jumlah = nilai.jumlah;
        (*p)->data.hargaSatuan = nilai.hargaSatuan;
        (*p)->next = Nil;
    } 
}

void printPesananList (adr_pesanan p) {
    if (p == Nil) {
        printf("(Belum ada pesanan)\n");
        return;
    }
	while (p != Nil){
        printf("%s\n%d x %d\t\tRp%d\n", p->data.namaMenu,p->data.jumlah,p->data.hargaSatuan,p->data.jumlah*p->data.hargaSatuan);
        p = p->next;
    }
}

void addPesanan (adr_pesanan *First, Pesanan nilai) {
	//menambahkan satu node di akhir
	adr_pesanan P, Q;
    Create_Node(&P);
    Isi_Node(&P, nilai);
    if (P != Nil) {
        if (isEmpty(*First)) {
            *First = P;
        } else {
            Q = *First;
            while (next(Q) != Nil) {
                Q = next(Q);
            }
            next(Q) = P;
        }
    }
}

void deletePesanan(adr_pesanan *First, char namaMenu[]) {
     adr_pesanan p = *First, prev = Nil;

    // Jika node pertama adalah yang ingin dihapus
    if (p != Nil && strcmp(p->data.namaMenu, namaMenu) == 0) {
        *First = p->next;
        free(p);
        return;
    }

    while (p != Nil && strcmp(p->data.namaMenu, namaMenu) != 0) {
        prev = p;
        p = p->next;
    }

    if (p == Nil) return;    
    prev->next = p->next;
    free(p);
}

void deleteAll(adr_pesanan *First) {
	adr_pesanan P;
	while (*First != Nil) {
		P = *First;
		*First = (*First)->next;
		free(P);
	}
}

//Find Pesanan berdasarkan nama menu
adr_pesanan findPesanan(adr_pesanan p, char namaMenu[]) {
    while (p != Nil) {
        if (strcmp(p->data.namaMenu, namaMenu) == 0) {
            return p;
        }
        p = p->next;
    }
    return Nil;
}

//Update quantity pesanan
void updateQtyPesanan(adr_pesanan First, char namaMenu[], int jumlahBaru) {
    adr_pesanan p = findPesanan(First, namaMenu);
    if (p != Nil) {
        p->data.jumlah = jumlahBaru;
    }
}

// Hitung total harga semua pesanan
int countTotalHarga(adr_pesanan p) {
    int total = 0;
    while (p != Nil) {
        total += p->data.jumlah * p->data.hargaSatuan;
        p = p->next;
    }
    return total;
}