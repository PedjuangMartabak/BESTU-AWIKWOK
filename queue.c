#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <linked.h>

void CreatePriorityQueue(PriorityQueue *Q){
    Q->front = Nil;
}

boolean isQueueEmpty(PriorityQueue Q){
    return (Q.front == Nil);
}

void enqueue(PriorityQueue *Q, Pelanggan data) {
    address newNode;
    Create_Node(&newNode);
    Isi_Node(&newNode, data);

    if (isQueueEmpty(*Q)) {
        Q->front = newNode;
    } else {
        address current = Q->front;
        address prev = Nil;

        // Urutan berdasarkan jam kedatangan (ascending)
        while (current != Nil && strcmp(current->dataPelanggan.waktu, data.waktu) <= 0) {
            prev = current;
            current = next(current);
        }

        if (prev == Nil) {
            next(newNode) = Q->front;
            Q->front = newNode;
        } else {
            next(newNode) = current;
            next(prev) = newNode;
        }
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

void printQueue(PriorityQueue Q){
    address current =  Q.front;
    int i = 1;
    printf("\n==Daftar Antrian==\n");
    while (current != Nil)
    {
        printf("%d. %s (jam: %s, %d orang)\n"),
            i++, current->dataPelanggan.namaPelanggan,
            current->dataPelanggan.waktu,
            current->dataPelanggan.jmlOrang;
        
        current = next(current);

    }
    if (i == 1){
    printf("Antrian Kosong\n")
    }
}