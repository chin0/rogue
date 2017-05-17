#ifndef _MONSTER_H
#define _MONSTER_H

typedef struct
{
    int hp;
    int attack;
    int att_rate;
    int drop_exp;
}monster;

int move(monster *mon);
int attack();
void create_monster(int hp, int attack,int att_rate,char* name);
int is_player_near(int range); //정해진범위안에 플레이어가 있는가?
#endif
