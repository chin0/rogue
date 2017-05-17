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


void findpath(int);

#endif //ROGUE_FINDPATH_H
