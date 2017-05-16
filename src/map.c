#include "../include/map.h"

int maps[MAX_Y][MAX_X];

static int max_room_number; //max room number
static int room_number = 0;

room* room_array; //contains room data

void updateParam(int room)
{
    max_room_number = room;
    room_array = malloc(sizeof(room) * room_number);
}

static void initDoor()
{

}

void initRooms()
{
    int door_num;
    room_array[room_number].width = get_random_number(ROOM_MIN_X,ROOM_MAX_X + 1);
    room_array[room_number].height = get_random_number(ROOM_MIN_Y, ROOM_MAX_Y + 1);
    room_array[room_number].x = get_random_number(0,MAX_X);
    room_array[room_number].y = get_random_number(0,MAX_Y);
    
    door_num = get_random_number(1,5);

    room_array[room_number].door_number = door_num;

    room_array[room_number].id = room_number;
}

bool isBlock()
{
    int cur_x = room_array[room_number].x;
    int cur_y = room_array[room_number].y;
    int cur_width = room_array[room_number].width;
    int cur_height = room_array[room_number].height;

    if(cur_x < 0 || cur_x >= MAX_X || cur_y < 0 || cur_y >= MAX_Y 
            || cur_x + cur_width >= MAX_X || cur_y + cur_height >= MAX_Y)
        return TRUE;

    for(int i = cur_y; i < cur_y + cur_height; i++){
        for(int j = cur_x; j < cur_x + cur_width; j++){
            if(maps[i][j+1] || maps[i][j-1] || maps[i][j] || 
                    maps[i+1][j] || maps[i-1][j])
                return TRUE;
        }
    }

    return FALSE;
}

void drawRoom(room _room)
{
    int cur_id = _room.id + 1;
    int cur_x = _room.x;
    int cur_y = _room.y;
    int cur_width = _room.width;
    int cur_height = _room.height;

#ifdef DEBUG
    printf("[debug] cur_id: %d\n",cur_id);
    printf("[debug] cur_x: %d\n",cur_x);
    printf("[debug] cur_y: %d\n",cur_y);
    printf("[debug] cur_width: %d\n",cur_width);
    printf("[debug] cur_height: %d\n",cur_height);
#endif

    for(int i = cur_y; i < cur_y + cur_height; i++){
        for(int j = cur_x; j < cur_x + cur_width; j++){
            maps[i][j] = cur_id;
        }
    }
}

void generate_map()
{
    updateParam(9);
    if(max_room_number + 1 == room_number ){
        printf("\nnope!!\nnope!!\nnope!!\nnope!!\nnope!!\n");
        return;
    }
    initRooms();
    while(isBlock())
        initRooms();
    drawRoom(room_array[room_number]);
    room_number++;
}

