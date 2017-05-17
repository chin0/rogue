#include "../include/map.h"
#include "../include/findpath.h"


int maps[MAX_Y][MAX_X];
door door_info[36];
int door_count;
int max_room_number; //max room number
static int room_number = 0;

typedef enum{
    WEST=0,
    SOUTH,
    EAST,
    NORTH
};

room* room_array[100]; //contains room data

void updateParam(int room)
{
    max_room_number = room;
}

static room* allocate_room(int x, int y, int height,
                           int width, int door_number)
{
    room* ret = malloc(sizeof(room));
    ret->x = 0;
    ret->y = 0;
    for(int i = 0; i < 4; i++)
        ret->check[i] = 0;
    ret->height = 0;
    ret->width = 0;
    ret->door_number = 0;

    return ret;
}

void initRooms()
{
    door* directions;
    int* check;
    int door_num,width,height,x,y;

    width = get_random_number(ROOM_MIN_X,ROOM_MAX_X + 1);
    height = get_random_number(ROOM_MIN_Y, ROOM_MAX_Y + 1);
    x = get_random_number(2,MAX_X-1);
    y = get_random_number(2,MAX_Y-1);

    door_num = get_random_number(3,4);

    room* _room = allocate_room(x,y,height,width,door_num);

    directions = _room->direction;

    _room->width = width;
    _room->height = height;
    _room->x = x;
    _room->y = y;

    _room->door_number = door_num;

    check = _room->check;
    for(int i = 0; i < door_num; i++){
        int temp = get_random_number(1,4);

        if(check[temp])
            continue;

        switch(temp){
            case NORTH:
                directions[temp].x = x + get_random_number(1, width-2);
                directions[temp].y = y;
                break;
            case SOUTH:
                directions[temp].x = x + get_random_number(1, width-2);
                directions[temp].y = y + height-1;
                break;
            case EAST:
                directions[temp].x = x + width-1;
                directions[temp].y = y + get_random_number(1, height-2);
                break;
            case WEST:
                directions[temp].x = x;
                directions[temp].y = y + get_random_number(1,height-2);
                break;
        }
        check[temp] = 1;

    }

    _room->id = room_number;
    room_array[room_number] = _room;
}

int isBlock()
{
    room* cur_room = room_array[room_number];
    int cur_x      = cur_room->x;
    int cur_y      = cur_room->y;
    int cur_width  = cur_room->width;
    int cur_height = cur_room->height;

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
int get_first_door(int room)
{
    return (4 * room);
}
void drawRoom(room _room)
{
    int cur_id      = _room.id;
    int cur_x       = _room.x;
    int cur_y       = _room.y;
    int cur_width   = _room.width;
    int cur_height  = _room.height;
    door* doors     = _room.direction;
    int* check      = _room.check;

#ifdef DEBUG
    printf("[debug] cur_id: %d\n",cur_id);
    printf("[debug] cur_x: %d\n",cur_x);
    printf("[debug] cur_y: %d\n",cur_y);
    printf("[debug] cur_width: %d\n",cur_width);
    printf("[debug] cur_height: %d\n",cur_height);
#endif

    for(int i = cur_y; i < cur_y + cur_height; i++){
        for(int j = cur_x; j < cur_x + cur_width; j++){

            if(j == cur_x || i == cur_y || j == cur_x + cur_width - 1
               || i == cur_y + cur_height - 1)
                maps[i][j] = 3;
            else
                maps[i][j] = 4;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if(check[i]){
            door_info[get_first_door(cur_id)+i] = doors[i];
            maps[doors[i].y][doors[i].x] = 1;
        }
    }
}


void generate_map() {
    updateParam(8);
    while (room_number != max_room_number) {

        initRooms();
        while (isBlock()) {
            free(room_array[room_number]);
            initRooms();
        }
        drawRoom(*room_array[room_number]);
        room_number++;
    }
    for (int i = 0; i < 36; i++) {
        if (door_info[i].x && door_info[i].y)
            findpath(i);
    }
}

void print_map()
{
    for(int i = 0; i < MAX_Y; i++){
        for(int j = 0; j < MAX_X; j++){
            switch(maps[i][j]){
                case PLAYER:
                    printf("@");
                    break;
                case TUNNEL:
                    printf("\u2592");
                    break;
                case DOOR:
                    printf("\u2591");
                    break;
                case WALL:
                    printf("\u2588");
                    break;
                case ROOM_TILE:
                    printf("\u2593");
                    break;
                default:
                    printf(" ");
                    break;
            }
        }
        printf("\n");
    }
}