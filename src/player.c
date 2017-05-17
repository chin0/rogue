#include "../include/map.h"
#include "../include/player.h"

#define KEY_LEFT 'h'
#define KEY_RIGHT 'l'
#define KEY_UP 'j'
#define KEY_DOWN 'k'

static char overwritten = 0;
player _player;

void player_init(int hp,int hungry,
                int attack, int exp)
{
    _player.attack = attack;
    _player.hungry = hungry;
    _player.hp     = hp;
    _player.exp    = exp;
    _player.level = 1;
    room *_room = room_array[get_random_number(0,8)];

    _player.x = _room->x + get_random_number(1, _room->width-2);
    _player.y = _room->y + get_random_number(1, _room->height-2);

    overwritten = maps[_player.y][_player.x];
    maps[_player.y][_player.x] = PLAYER;
}

void player_info()
{
    printf("[Level]: %d\t[hp]: %d,[hungry]: %d,[exp]: %d, [atr]: %d\n",
           _player.level,_player.hp,_player.hungry,_player.exp,_player.attack);
}
static int is_block(int block)
{
    return ((block >= MON_MEGUMI && block < GOLD)|| block == WALL || block == 0);
}

int in_exit = 0;
int collect()
{
    if(maps[_player.y][_player.x] == GOLD){
        int collected_gold = get_random_number(1,10);
        _player.gold += collected_gold;
        printf("you collect %d golds!(press any key..)\n",collected_gold);
        getch();
        return 1;
    }
    return 0;
}

void player_move(char key)
{
    in_exit = 0;
    maps[_player.y][_player.x] = overwritten;

    switch(key){
        case KEY_UP:
            if(!is_block(maps[_player.y+1][_player.x])) {
                overwritten = maps[_player.y+1][_player.x];
                _player.y += 1;
            }
            break;
        case KEY_DOWN:
            if(!is_block(maps[_player.y-1][_player.x])) {
                overwritten = maps[_player.y - 1][_player.x];
                _player.y -= 1;
            }
            break;
        case KEY_RIGHT:
            if(!is_block(maps[_player.y][_player.x+1])) {
                overwritten = maps[_player.y][_player.x+1];
                _player.x += 1;
            }
            break;
        case KEY_LEFT:
            if(!is_block(maps[_player.y][_player.x-1])) {
                overwritten = maps[_player.y][_player.x-1];
                _player.x -= 1;
            }
            break;
    }
    if(collect())
        overwritten = ROOM_TILE;
    if(maps[_player.y][_player.x] == EXIT)
        in_exit = 1;
    maps[_player.y][_player.x] = PLAYER;
}
int player_death()
{
    return (_player.hp <= 0);
}
