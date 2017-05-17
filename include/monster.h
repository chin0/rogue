#ifndef _MONSTER_H
#define _MONSTER_H

typedef struct
{
    int x;
    int y;
    int f;
}movement;
typedef struct
{
    int x;
    int y;
    int hp;
    int attack;
    int att_rate;
    int drop_exp;
    int is_chase;
    int drop_gold;
    char *name;
    char map_initialis;
} monster;

extern int in_exit;
void create_monster();
int monster_move(const monster *mon);
int attack();
int is_player_near(int index,int range); //정해진범위안에 플레이어가 있는가?
#endif
