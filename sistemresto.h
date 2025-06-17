#ifndef SISTEMRESTO_H
#define SISTEMRESTO_H
#include "menu_tree.h"
#include "stack.h"
#include "pesanan.h"
#include "queue.h"
#include "meja.h"
#include "boolean.h"

void clearInputBuffer();
void toLowercase (char *hasil, const char *input);
boolean cekIsiKata (const char* kalimat, const char *kataIsi);
void findMatch (treeAddress node, const char* input, treeAddress hasil[], int *count, int maxCount);
treeAddress inputItem (treeAddress root);
void PushCategory (adr_stack *orders, treeAddress menuItem, int qty);
void getOrder (treeAddress root, adr_pesanan *listPesanan);
void inputReservasi (treeAddress root, PriorityQueue *Q, Meja meja[], adr_pesanan *ListP);
void masukkanListKeStack (adr_pesanan listP, adr_stack *stackP);
void printAllQueue(PriorityQueue Q);
Kategori clonePesananStack (Kategori original);
adr_stack cloneStack (adr_stack src);
void prosesKedatangan(PriorityQueue *Q, adr_stack *stackP, Meja meja[]);
void printSemuaStackMeja(Meja meja[], PriorityQueue Q);
void prosesPengantaran (Meja meja [], PriorityQueue Q);

#endif