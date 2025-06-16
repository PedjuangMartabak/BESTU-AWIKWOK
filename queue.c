#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void CreatePriorityQueue(PriorityQueue *Q){
    Q->front = NULL;
}

boolean isQueueEmpty(PriorityQueue Q){
    return (Q.front == Nil);
}

void enqueue(PriorityQueue *Q, Pelanggan data) {
    address newNode = (address)malloc(sizeof(NodeQueue));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    newNode->dataPelanggan = data;
    newNode->next = NULL;

    if (isQueueEmpty(*Q) || 
        strcmp(data.jam_kedatangan, Q->front->dataPelanggan.jam_kedatangan) < 0) {
        newNode->next = Q->front;
        Q->front = newNode;
    } else {
        address current = Q->front;
        while (current->next != NULL && 
               strcmp(data.jam_kedatangan, current->next->dataPelanggan.jam_kedatangan) >= 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void dequeue(PriorityQueue *Q, Pelanggan *data){
    if (!isQueueEmpty(*Q))
    {
        address temp = Q->front;
        *data = temp->dataPelanggan;
        Q->front = next(temp);
        free(temp);
    }
    
}

void printQueue(PriorityQueue Q) {
    address current = Q.front;
    int i = 1;
    printf("\n=== Daftar Antrian ===\n");
    while (current != NULL) {
        printf("%d. %s (Jam: %s, %d orang)\n",
            i++, current->dataPelanggan.namaPelanggan,
            current->dataPelanggan.jam_kedatangan,
            current->dataPelanggan.total_orang);
        current = current->next;
    }
    if (i == 1) {
        printf("Antrian kosong.\n");
    }
}