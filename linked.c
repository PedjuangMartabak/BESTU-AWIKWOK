#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "linked.h"
#include "stack.h"

address First;

boolean isEmpty(address p) {
	return (p == Nil);
}
void Create_Node (address *p) {
	*p = (address) malloc(sizeof(NodeQueue));
    if (*p != Nil) {
        next(*p) = Nil;
    }
}

void Isi_Node (address *p , Pelanggan data) {
	if (*p != Nil) {
        strcpy((*p)->dataPelanggan.namaPelanggan, data.namaPelanggan);
        (*p)->dataPelanggan.listPesanan = data.listPesanan;
        (*p)->next = Nil;
    }
}

void Print_List (address p) {
    int i = 1;
	while (p != Nil){
        printf("%d. %s\n", i, p->dataPelanggan.namaPelanggan);
        printPesananList(p->dataPelanggan.listPesanan);
        printf("\n");
        p = p->next;
        i++;
    }
    if (i == 1) {
        printf("Antrian kosong.\n");
    }
}

void Insert_AtFirst (address *First, Pelanggan data) {
	address P;
    Create_Node(&P);
    Isi_Node(&P, data); 
    if (P != Nil) {
        next(P) = *First;
        *First = P;
    }
}

void Insert_AtLast (address *First, Pelanggan data) {
	address P, Q;
    Create_Node(&P);
    Isi_Node(&P, data);
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

void Delete_AtFirst(address *First) {
	address P;
    if (!isEmpty(*First)) {
        P = *First;
        *First = next(*First);
        free(P);
    }
}

void Delete_AtLast(address *First) {
	address P, Q;
    if (!isEmpty(*First)) {
        Q = *First;
        if (next(Q) == Nil) {
            *First = Nil;
        } else {
            while (next(next(Q)) != Nil) {
                Q = next(Q);
            }
            P = next(Q);
            next(Q) = Nil;
        }
        free(P);
    }
}

void Delete_All(address *First) {
	address P;
	while (*First != Nil) {
		P = *First;
		*First = (*First)->next;
		free(P);
	}
}
