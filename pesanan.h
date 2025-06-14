/* File        : linked.h */
/* Deskripsi   : header file ADT linked list dengan representasi fisik pointer */

#ifndef LINKED_H
#define LINKED_H
#include<stdlib.h>
#include<stdio.h>
#include "boolean.h"
#include "queue.h"

extern adr_pesanan First;

boolean isEmpty(adr_pesanan p);
void Create_Node (adr_pesanan *p);
void Isi_Node (adr_pesanan *p , Pesanan nilai);
void printPesananList (adr_pesanan p);
void addPesanan (adr_pesanan *First, Pesanan nilai);

void deletePesanan(adr_pesanan *First, char namaMenu[]);
void deleteAll(adr_pesanan *First);
adr_pesanan findPesanan(adr_pesanan p, char namaMenu[]);
void updateQtyPesanan(adr_pesanan First, char namaMenu[], int jumlahBaru);
int countTotalHarga(adr_pesanan p);

#endif
