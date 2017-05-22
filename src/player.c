#include "../include/map.h"
#include "../include/player.h"

#define KEY_LEFT 'h'
#define KEY_RIGHT 'l'
#define KEY_UP 'j'
#define KEY_DOWN 'k'

int kill = 0;
char p_overwritten = 0;
player _player;

int lv_exp[5] = {10,20,30,40,50};
void player_init(int hp,int hungry,
                int attack_min, int attack_max,int exp)
{
    _player.attack_min = attack_min;
    _player.attack_max = attack_max;
    _player.hungry = hungry;
    _player.max_hungry = hungry;
    _player.hp     = hp;
    _player.exp    = exp;
    _player.max_exp = lv_exp[0];
    _player.max_hp = hp;
    _player.level = 1;
    room *_room = room_array[get_random_number(0,8)];

    _player.x = _room->x + get_random_number(1, _room->width-2);
    _player.y = _room->y + get_random_number(1, _room->height-2);

    p_overwritten = maps[_player.y][_player.x];
    maps[_player.y][_player.x] = PLAYER;
}

void player_info()
{
    printf("[Level]: %d\t[hp]: %d/%d,[hungry]: %d/%d,[exp]: %d/%d, [atr]: %d-%d\n",
           _player.level,_player.hp,_player.max_hp,_player.hungry,_player.max_hungry,_player.exp,_player.max_exp,
           _player.attack_min,_player.attack_max);
}
void level_up()
{
    int c = 0;
    int max = 2;
    int attack_min,attack_max,max_hp,hungry;


    _player.level++;
    _player.max_exp = lv_exp[_player.level];
    _player.exp = 0;


    while(c != max) {
        system("clear");
        printf( "   ########### level %d로 레벨업하셨습니다!      ############\n",_player.level);
        printf("   #         랜덤으로 증가시킬 능력치를 2가지 선택하세요!      #\n");
        printf("  #         a) 최대&최소공격력                            #\n");
        printf(" #         h) 최대체력                                  #\n");
        printf("#         s) 허 기                                    #\n");
        printf("######################################################\n");
        int select = getch();
        switch(select) {
            case 'a':
                attack_min = get_random_number(0, 3);
                sleep(0.1);
                attack_max = get_random_number(0,3);
                printf("최대 공격력이 %d,최소 공격력이 %d증가했습니다.(아무키나 누르세요.)",attack_max,attack_min);
                getch();
                _player.attack_max += attack_max;
                _player.attack_min += attack_min;
                break;
            case 'h':
                max_hp = get_random_number(1,4);
                printf("최대 체력이 %d 증가했습니다.(아무키나 누르세요.)",max_hp);
                getch();
                _player.max_hp += max_hp;
                break;
            case 's':
                hungry = get_random_number(2,5);
                printf("최대 공복도가 %d 증가했습니다.(아무키나 누르세요.)",hungry);
                getch();
                _player.hungry += hungry;
                break;
            default:
                select = 0xff;
                printf("다시 입력하세요.(아무키나 누르세요.)");
                getch();
                break;
        }
        if(select != 0xff)
            c++;
    }
    _player.hp = _player.max_hp;
    _player.hungry = _player.max_hungry;

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
        printf("%d개의 금을 얻었습니다!(press any key..)\n",collected_gold);
        getch();
        return 1;
    }
    return 0;
}

void player_move(char key)
{
    if(turn % 20 == 0 && _player.hp < _player.max_hp && _player.hungry) {
        _player.hungry -= 4;
        _player.hp++;
    }
    in_exit = 0;
    maps[_player.y][_player.x] = p_overwritten;

    switch(key){
        case KEY_UP:
            if(!is_block(maps[_player.y+1][_player.x])) {
                p_overwritten = maps[_player.y+1][_player.x];
                _player.y += 1;
            }
            break;
        case KEY_DOWN:
            if(!is_block(maps[_player.y-1][_player.x])) {
                p_overwritten = maps[_player.y - 1][_player.x];
                _player.y -= 1;
            }
            break;
        case KEY_RIGHT:
            if(!is_block(maps[_player.y][_player.x+1])) {
                p_overwritten = maps[_player.y][_player.x+1];
                _player.x += 1;
            }
            break;
        case KEY_LEFT:
            if(!is_block(maps[_player.y][_player.x-1])) {
                p_overwritten = maps[_player.y][_player.x-1];
                _player.x -= 1;
            }
            break;
    }
    if(collect())
        p_overwritten = ROOM_TILE;
    if(maps[_player.y][_player.x] == EXIT)
        in_exit = 1;
    maps[_player.y][_player.x] = PLAYER;
}
int player_death()
{
    return (_player.hp <= 0);
}
