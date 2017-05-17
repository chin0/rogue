//
// Created by kafuuchin0 on 16.05.17.
//
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "../include/map.h"
#include "../include/findpath.h"
#include "../include/vector.h"


PriorityQueue* pq_create(int init_size)
{
    PriorityQueue* NewPQ = malloc(sizeof(NewPQ));
    NewPQ->Capacity = init_size;
    NewPQ->UsedSize = 0;
    NewPQ->Nodes = malloc(sizeof(PQNode) * NewPQ->Capacity);

    return NewPQ;
}

void pq_destroy(PriorityQueue *pq)
{
    free(pq->Nodes);
    free(pq);
}

void pq_enqueue(PriorityQueue* pq, PQNode NewData)
{
    int current_position = pq->UsedSize;
    int parent_position = pq_get_parent(current_position);

    if(pq->UsedSize == pq->Capacity){
        if(pq->Capacity == 0)
            pq->Capacity = 1;

        pq->Capacity *= 2;
        pq->Nodes = realloc(pq->Nodes, sizeof(PQNode) * pq->Capacity);
    }

    pq->Nodes[current_position] = NewData;

    //현재 노드가 루트가 되거나 현재 노드가 부모노드보다 클때까지
    while(current_position > 0
          && pq->Nodes[current_position].priority < pq->Nodes[parent_position].priority)
    {
        pq_swap_nodes(pq,current_position,parent_position);

        current_position = parent_position;
        parent_position = pq_get_parent(current_position);
    }

    pq->UsedSize++;
}

void pq_swap_nodes(PriorityQueue *pq, int index1, int index2)
{
    int copy_size = sizeof(PQNode);
    PQNode* temp = malloc(copy_size);

    memcpy(temp, &pq->Nodes[index1], copy_size);
    memcpy(&pq->Nodes[index1], &pq->Nodes[index2], copy_size);
    memcpy(&pq->Nodes[index2], temp, copy_size);

    free(temp);
}

void pq_dequeue(PriorityQueue *pq, PQNode* Root)
{
    int parent_position = 0;
    int left_position = 0;
    int right_position = 0;

    memcpy(Root, &pq->Nodes[0], sizeof(PQNode));
    memset(&pq->Nodes[0],0, sizeof(PQNode));

    pq->UsedSize--;
    pq_swap_nodes(pq,0,pq->UsedSize); //힙의 첫번째 요소와 맨 마지막(최대 깊이 최우측 노드)을 서로 위치바꾼다.

    left_position = pq_get_left_child(0);
    right_position = left_position + 1;

    while(1){ //힙속성 만족까지.
        int selected_child = 0;

        //구한 현재 왼쪽 자식노드가 현재 힙 트리 크기보다 클때(존재하지 않을때)
        if(left_position >= pq->UsedSize)
            break;

        //현재 오른쪽 자식노드가 현재 힙 트리 크기보다 클때(존재하지 않을때)
        if(right_position >= pq->UsedSize){
            selected_child = left_position; //현재 노드를 왼쪽으로 바꾼다.
        } else {
            if(pq->Nodes[left_position].priority > pq->Nodes[right_position].priority) //양쪽노드 비교
                selected_child = right_position;
            else
                selected_child = left_position;
        }

        //양쪽 자식중 작은 노드와 부모노드를 비교해서 부모노드가 크다면
        if(pq->Nodes[selected_child].priority < pq->Nodes[parent_position].priority){
            pq_swap_nodes(pq,parent_position, selected_child);
            parent_position = selected_child;
        }
        else
            break;

        left_position = pq_get_left_child(parent_position);
        right_position = left_position + 1;
    }
    if(pq->UsedSize < (pq->Capacity / 2))
    {
        pq->Capacity /= 2;
        pq->Nodes = realloc(pq->Nodes, sizeof(PQNode) * pq->Capacity);
    }
}

int pq_get_parent(int index)
{
    return ((index-1)/2);
}

int pq_get_left_child(int index)
{
    return (2 * index) + 1;
}
int pq_isEmpty(PriorityQueue* PQ)
{
    return (PQ->UsedSize == 0);
}

static int huristic(int x, int y, door door)
{
    //맨해튼거리
    return abs(x - door.x) + abs(y - door.y);
}

void findpath(int target)
{
    int cur_x,cur_y,f,cnt;
    int min = 0x100;
    door src = door_info[target];
    door *dest;
    PQNode popped;

    if(src.is_connected)
        return;

    door_info[target].is_connected = 1;


    int is_find = 0;
    for(int i = 0; i < max_room_number; i++){
        if(target / 4 == i)
            continue;

        int door_index = get_first_door(i);

        for(int j = 0; j < 4; j++) {
            door *current = &door_info[j + door_index];
            if (current->x && current->y && !current->is_connected) {
                is_find = 1;
                int h = huristic(src.x,src.y, *current);
                min = h;
                dest = current;
                break;
            }
        }
    }

    if(!is_find)
        return;

    cur_x = src.x;
    cur_y = src.y;



    dest->is_connected = 1;

    PriorityQueue* open_list = pq_create(3);
    f = huristic(cur_x+1,cur_y,*dest);


    pq_enqueue(open_list,(PQNode){f,cur_x,cur_y});
    int i = 0;
    while(1){
        if(i > 100)
            break;
        pq_dequeue(open_list,&popped);

        cur_x = popped.x;
        cur_y = popped.y;

        if(cur_x == dest->x && cur_y == dest->y)
            break;

        if(cur_x+1 < MAX_X && maps[cur_y][cur_x+1] <= 2){
            f = huristic(cur_x+1,cur_y,*dest);
            pq_enqueue(open_list,(PQNode){f,cur_x+1,cur_y});

        }
        if(cur_y+1 < MAX_Y && maps[cur_y+1][cur_x] <= 2){
            f = huristic(cur_x,cur_y+1,*dest);
            pq_enqueue(open_list,(PQNode){f,cur_x,cur_y+1});

        }
        if(cur_x-1 > 0 && maps[cur_y][cur_x-1] <= 2){
            f = huristic(cur_x-1,cur_y,*dest);
            pq_enqueue(open_list,(PQNode){f,cur_x-1,cur_y});
        }
        if(cur_y-1 > 0 && maps[cur_y-1][cur_x] <= 2){
            f = huristic(cur_x,cur_y-1,*dest);
            pq_enqueue(open_list,(PQNode){f,cur_x,cur_y-1});
        }
        maps[cur_y][cur_x] = 2;
        i++;
    }
    maps[src.y][src.x] = 1;
    pq_destroy(open_list);
}
