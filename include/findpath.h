//
// Created by kafuuchin0 on 16.05.17.
//

#ifndef ROGUE_FINDPATH_H
#define ROGUE_FINDPATH_H

#include "../include/map.h"

typedef struct tagPQNode{
    int priority;
    int x;
    int y;
} PQNode;

typedef struct tagHeap{
    PQNode* Nodes;
    int Capacity;
    int UsedSize;
} PriorityQueue;

PriorityQueue* pq_create(int init_size);
void pq_destroy(PriorityQueue *pq);
void pq_enqueue(PriorityQueue* pq, PQNode NewData);
void pq_swap_nodes(PriorityQueue *pq, int index1, int index2);
void pq_dequeue(PriorityQueue *pq, PQNode* Root);
int pq_get_parent(int index);
int pq_get_left_child(int index);
int pq_isEmpty(PriorityQueue* PQ);


void findpath(int);

#endif //ROGUE_FINDPATH_H
