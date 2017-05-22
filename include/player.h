#ifndef _PLAYER_H
#define _PLAYER_H

typedef struct{
    int hp;
    int max_hp;
    int hungry;
    int max_hungry;
    int attack_min;
    int attack_max;
    int exp;
    int max_exp;
    int level;
    int gold;
    int x;
    int y;
} player;

extern player _player;
extern int kill;
void player_init(int hp,int hungry, int attack_min,int attack_max,int exp);
void player_move(char key);
void player_info();
int player_death();
int destroy_player();
void level_up();
int collect();


#endif