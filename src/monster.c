#include "../include/monster.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/findpath.h"


#define MAX(x,y) (((x) > (y)) ? (x) : (y))

static char overwritten = 0;

char* mon_namespace[7] = {
        "Megumi",
        "Utaha",
        "Eriri",
        "Michiru",
        "Chino",
        "Tomori",
        "Rikka"
};

monster *monster_arr[9];
int count=0;

static int is_block(int block)
{
    return ((block >= MON_MEGUMI && block < GOLD)|| block == WALL || block == 0 || block == PLAYER);
}

static int huristic(int x, int y, player _player)
{
    //맨해튼거리
    return abs(_player.x-x) + abs(_player.y-y);
}

void create_monster()
{
    int mon_name_num = get_random_number(0,6);
    monster* new_mon = malloc(sizeof(monster));
    room* monster_room = room_array[get_random_number(0,8)];
    new_mon = malloc(sizeof(monster));
    new_mon->hp = get_random_number(6,20);
    new_mon->attack = get_random_number(3,6);
    new_mon->att_rate = get_random_number(0,3);
    new_mon->drop_exp = get_random_number(1,4);
    new_mon->drop_gold = get_random_number(4,10);
    new_mon->is_chase = 0;
    new_mon->name = mon_namespace[mon_name_num];
    new_mon->map_initialis = 6 + mon_name_num;

    new_mon->x = monster_room->x + get_random_number(1, monster_room->width-2);
    new_mon->y = monster_room->y + get_random_number(1, monster_room->height-2);

    monster_arr[count++] = new_mon;
    overwritten = maps[new_mon->y][new_mon->x];
    maps[new_mon->y][new_mon->x] = new_mon->map_initialis;
}

int deal(int i)
{
    monster* tar = monster_arr[i];

    if(get_random_number(0,2) == 1) {
        printf("%s에게 %d데미지를 입힘\n.", tar->name,_player.attack);
        getch();
        tar->hp -= _player.attack;
    }
    if(monster_death(i)) {
        printf("%s를 이겼습니다!\n");
        getch();
        maps[tar->y][tar->x] = overwritten;
        free(tar);
        monster_arr[i] = NULL;
    }
}

int attack()
{
    for(int i = 0; i < count; i++){
        if(monster_arr[i] == NULL)
            return -1;
        if(is_player_near(i,7)) {
            monster_findpath(i);
        }
        if(is_player_near(i,1)){
            deal(i);
        }
    }
}

void monster_findpath(int target)
{
    int cur_x,cur_y,f,cnt;
    int min = 0x100;
    PQNode popped;
    if(is_player_near(target,1))
        return;
    monster* src = monster_arr[target];

    cur_x = src->x;
    cur_y = src->y;


    PriorityQueue* open_list = pq_create(3);
    f = huristic(cur_x,cur_y,_player);


    pq_enqueue(open_list,(PQNode){f,cur_x,cur_y});

    pq_dequeue(open_list,&popped);

    cur_x = popped.x;
    cur_y = popped.y;

    maps[cur_y][cur_x] = overwritten;

    if(!is_block(maps[cur_y][cur_x+1])){
        f = huristic(cur_x+1,cur_y,_player);
        pq_enqueue(open_list,(PQNode){f,cur_x+1,cur_y});

    }
    if(!is_block(maps[cur_y+1][cur_x])){
        f = huristic(cur_x,cur_y+1,_player);
        pq_enqueue(open_list,(PQNode){f,cur_x,cur_y+1});
    }
    if(!is_block(maps[cur_y][cur_x-1])){
        f = huristic(cur_x-1,cur_y,_player);
        pq_enqueue(open_list,(PQNode){f,cur_x-1,cur_y});
    }
    if(!is_block(maps[cur_y-1][cur_x])) {
        f = huristic(cur_x, cur_y - 1, _player);
        pq_enqueue(open_list, (PQNode) {f, cur_x, cur_y - 1});
    }
    if(!is_block(maps[cur_y-1][cur_x+1])) {
        f = huristic(cur_x+1, cur_y - 1, _player);
        pq_enqueue(open_list, (PQNode) {f, cur_x+1, cur_y - 1});
    }
    if(!is_block(maps[cur_y-1][cur_x-1])) {
        f = huristic(cur_x-1, cur_y - 1, _player);
        pq_enqueue(open_list, (PQNode) {f, cur_x-1, cur_y - 1});
    }
    if(!is_block(maps[cur_y+1][cur_x-1])) {
        f = huristic(cur_x-1, cur_y + 1, _player);
        pq_enqueue(open_list, (PQNode) {f, cur_x-1, cur_y + 1});
    }
    if(!is_block(maps[cur_y+1][cur_x+1])) {
        f = huristic(cur_x+1, cur_y + 1, _player);
        pq_enqueue(open_list, (PQNode) {f, cur_x+1, cur_y + 1});
    }
    pq_dequeue(open_list,&popped);

    cur_x = popped.x;
    cur_y = popped.y;
    if(maps[cur_y][cur_x] == WALL)
        return;
    overwritten = maps[cur_y][cur_x];
    maps[cur_y][cur_x] = src->map_initialis;

    src->y = cur_y;
    src->x = cur_x;
    pq_destroy(open_list);
}

int monster_death(int index){
    return (monster_arr[index]->hp <= 0);
}

int is_player_near(int index,int range)
{
    monster* mon = monster_arr[index];
    return range >= MAX(abs(mon->x -_player.x), abs(mon->y - _player.y));
}