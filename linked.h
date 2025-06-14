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
void Print_List (adr_pesanan p);

void Insert_AtFirst (adr_pesanan *First, Pesanan nilai);
void Insert_AtLast (adr_pesanan *First, Pesanan nilai);

void Delete_Value(adr_pesanan *First, Pesanan target);
void Delete_All(adr_pesanan *First);

#endif
