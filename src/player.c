#include "../include/map.h"
#include "../include/player.h"

#define KEY_LEFT 'h'
#define KEY_RIGHT 'l'
#define KEY_UP 'j'
#define KEY_DOWN 'k'

int overwritten = 0;
player _player;

void player_init(int hp,int hungry,
                int attack, int exp)
{
    _player.attack = attack;
    _player.hungry = hungry;
    _player.hp     = hp;
    _player.exp    = exp;
    _player.level = 1;
    room *_room = room_array[get_random_number(0,9)];

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
int is_block(int block)
{
    return (block == WALL || block == 0);
}
void player_move(char key)
{
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
    maps[_player.y][_player.x] = PLAYER;
}
int player_death()
{
    return (_player.hp <= 0);
}
