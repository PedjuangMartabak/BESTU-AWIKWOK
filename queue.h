#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"
#include "linked.h"

typedef struct {
    address front;
} PriorityQueue;

void CreatePriorityQueue(PriorityQueue *Q);
boolean isQueueEmpty(PriorityQueue Q);
void enqueue(PriorityQueue *Q, Pelanggan data);
void dequeue(PriorityQueue *Q, Pelanggan *data);
void printQueue(PriorityQueue Q);

#endif