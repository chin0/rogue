#ifndef H_MAP
#define H_MAP

#include "util.h"

#define MAX_X 90
#define MAX_Y 30

#define ROOM_MAX_Y 7
#define ROOM_MAX_X 18
#define ROOM_MIN_Y 4
#define ROOM_MIN_X 5

extern int maps[][MAX_X];

typedef struct
{
    int direction;
    int y;
    int is_connected;
} door;

typedef struct
{
    int id;
    int width;
    int height;
    int x;
    int y;
    door* opening; //array
    int door_number;
} room;

void updateParam(int room);
void initRooms();
bool isBlock();
void initCorridors();
void tunnelRandom();
void drawRoom(room _room);
void generate_map();

#endif
