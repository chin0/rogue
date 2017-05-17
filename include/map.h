#ifndef H_MAP
#define H_MAP

#include "util.h"

#define MAX_X 90
#define MAX_Y 30

#define ROOM_MAX_Y 9
#define ROOM_MAX_X 18
#define ROOM_MIN_Y 6
#define ROOM_MIN_X 9

enum {
    TUNNEL=1,
    DOOR,
    WALL,
    ROOM_TILE,
    PLAYER,
    MON_MEGUMI,
    MON_UTAHA,
    MON_ERIRI,
    MON_MITCHIRU,
    MON_CHINO,
    MON_TOMORI,
    MON_RIKKA,
    GOLD,
    EXIT
};

typedef struct {
    int x;
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
    int is_spawn_monster;
    int door_number;
    int check[4];
    door direction[4];
} room;

extern int maps[][MAX_X];
extern door door_info[];
extern int max_room_number;
extern room* room_array[];

void updateParam(int room);
void initRooms();
int isBlock();
void drawRoom(room _room);
void generate_map();
int get_first_door(int room);
void print_map();
#endif
