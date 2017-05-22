#include "../include/monster.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/findpath.h"


#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int stage_level = 1;
//static char mon_overwritten = 0;

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

static void monster_findpath(int target)
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

    maps[cur_y][cur_x] = src->overwritten;

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
    src->overwritten = maps[cur_y][cur_x];
    maps[cur_y][cur_x] = src->map_initialis;

    src->y = cur_y;
    src->x = cur_x;
    pq_destroy(open_list);
}
void create_monster()
{
    int mon_name_num = get_random_number(0,6);
    monster* new_mon = malloc(sizeof(monster));
    room* monster_room = room_array[get_random_number(0,8)];
    new_mon = malloc(sizeof(monster));
    new_mon->hp = get_random_number(6,15);
    new_mon->attack = get_random_number(3,5);
    new_mon->att_rate = get_random_number(1,4);
    new_mon->drop_exp = get_random_number(2,6);
    new_mon->drop_gold = get_random_number(4,8);
    new_mon->is_chase = 0;
    new_mon->name = mon_namespace[mon_name_num];
    new_mon->map_initialis = 6 + mon_name_num;

    new_mon->x = monster_room->x + get_random_number(1, monster_room->width-2);
    new_mon->y = monster_room->y + get_random_number(1, monster_room->height-2);


    monster_arr[count++] = new_mon;

    new_mon->overwritten = maps[new_mon->y][new_mon->x];
    maps[new_mon->y][new_mon->x] = new_mon->map_initialis;
}

int deal(int i)
{
    monster* tar = monster_arr[i];

    if(get_random_number(0,2) == 1) {
        int attack = get_random_number(_player.attack_min,_player.attack_max);
        printf("%s에게 %d데미지를 입힘.\n", tar->name,attack);
        getch();
        tar->hp -= attack;
    } else {
        printf("당신의 공격이 빗나갔습니다!\n");
        getch();
    }
    if(monster_death(i)) {
        printf("%s를 이겼습니다!\n%d골드와 %d경험치를 얻었습니다.\n",tar->name,tar->drop_gold,tar->drop_exp);
        getch();
        _player.gold += tar->drop_gold;
        _player.exp += tar->drop_exp;
        if(_player.exp >= _player.max_exp)
            level_up();
        maps[tar->y][tar->x] = tar->overwritten;
        kill++;
        free(tar);
        monster_arr[i] = NULL;
    } else {
        if (get_random_number(0, tar->att_rate) == 1) {
            _player.hp -= monster_arr[i]->attack;
            printf("%s에게 %d데미지를 입음.\n", tar->name, tar->attack);
            getch();
            if (player_death()) {
                system("clear");
                printf("죽었습니다!\n");
                getch();
            }
        } else {
            printf("%s의 공격이 빗나갔습니다.\n",tar->name);
            getch();
        }
    }
}

int attack()
{
    for(int i = 0; i < count; i++){
        if(monster_arr[i] == NULL)
            continue;
        if(is_player_near(i,7)) {
            monster_findpath(i);
        }
        if(is_player_near(i,1)){
            deal(i);
        }
    }
}


int monster_death(int index){
    return (monster_arr[index]->hp <= 0);
}

int is_player_near(int index,int range)
{
    monster* mon = monster_arr[index];
    return range >= MAX(abs(mon->x -_player.x), abs(mon->y - _player.y));
}