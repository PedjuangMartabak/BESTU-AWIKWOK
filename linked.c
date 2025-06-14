#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked.h"

adr_pesanan First;

boolean isEmpty(adr_pesanan p) {
	return (p == Nil);
}

void Create_Node (adr_pesanan *p) {
	*p = (adr_pesanan) malloc(sizeof(ElmtList));
    if (*p != Nil) {
        next_elmt(*p) = Nil;
    }
}

void Isi_Node (adr_pesanan *p , Pesanan nilai) {
	if (*p != Nil) {
        strncpy((*p)->nm, nilai, sizeof((*p)->nm) - 1);
        (*p)->nm[sizeof((*p)->nm) - 1] = '\0';
    }
}

void Print_List (adr_pesanan p) {
	while (p != Nil){
        printf("   %s -> ", p->nm);
        p = p->next;
    }
    printf("NULL\n");
}

void Insert_AtFirst (adr_pesanan *First, Pesanan nilai) {
	//menambahkan satu node di awal
	adr_pesanan P;
    Create_Node(&P);
    Isi_Node(&P, nilai); 
    if (P != Nil) {
        next_elmt(P) = *First;
        *First = P;
    }
}

void Insert_AtLast (adr_pesanan *First, Pesanan nilai) {
	//menambahkan satu node di akhir
	adr_pesanan P, Q;
    Create_Node(&P);
    Isi_Node(&P, nilai);
    if (P != Nil) {
        if (isEmpty(*First)) {
            *First = P;
        } else {
            Q = *First;
            while (next_elmt(Q) != Nil) {
                Q = next_elmt(Q);
            }
            next_elmt(Q) = P;
        }
    }
}

void Delete_AtFirst(adr_pesanan *First) {
	//menghapus satu node di awal
	adr_pesanan P;
    if (!isEmpty(*First)) {
        P = *First;
        *First = next_elmt(*First);
        free(P);
    }
}

void Delete_AtLast(adr_pesanan *First) {
	//menghapus satu node di akhir
	adr_pesanan P, Q;
    if (!isEmpty(*First)) {
        Q = *First;
        if (next_elmt(Q) == Nil) {
            *First = Nil;
        } else {
            while (next_elmt(next_elmt(Q)) != Nil) {
                Q = next_elmt(Q);
            }
            P = next_elmt(Q);
            next_elmt(Q) = Nil;
        }
        free(P);
    }
}

void Delete_Value(adr_pesanan *First, Pesanan target) {

}

void Delete_All(adr_pesanan *First) {
	adr_pesanan P;
	while (*First != Nil) {
		P = *First;
		*First = (*First)->next;
		free(P);
	}
}
