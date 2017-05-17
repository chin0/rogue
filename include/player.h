#ifndef _PLAYER_H
#define _PLAYER_H

typedef struct{
    int hp;
    int hungry;
    int attack;
    int exp;
    int level;
    int x;
    int y;
} player;

extern player _player;

void player_init(int hp,int hungry, int attack, int exp);
void player_move(char key);
void player_info();
int is_death();
int destroy_player();


#endif