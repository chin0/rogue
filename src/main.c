#include <unistd.h>
#include <time.h>
#include "../include/util.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/monster.h"

extern int maps[][MAX_X];



int main(void)
{
    char input;
    int success=0;
    generate_map();
    player_init(get_random_number(20,28),20,get_random_number(3,4),get_random_number(5,8),0);
    for(int i = 0; i < 6; i++)
        create_monster();
    while(1)
    {
        system("clear");
        player_info();
#ifdef DEBUG
        printf("[debug]_player.x:%d, _player.y:%d\n",_player.x,_player.y);
#endif
        print_map();
        input = getch();

        if(input == 'q'){
            system("clear");
            printf("really?? (y/n): ");
            input = getch();
            if(input == 'y'){
                printf("bye!\n");
                break;
            }
            continue;
        }
        if(input == 'e') {
            if(in_exit && kill > 3 && _player.gold > 20){
                success = 1;
                break;
            } else {
                printf("몬스터를 더 처리하거나 금을 더 모으세요..!(아무키나 누르세요.)");
                getch();
            }
        } else {
            turn++;
            player_move(input);
            attack();
        }
        if(player_death())
            break;
    }
    if(success) {
        system("clear\n");
        printf("%d턴만에 성공적으로 탈출했습니다!\n",turn);
        printf("모은금:%d\n", _player.gold);
    } else {
        printf("모은금:%d\n", _player.gold);
    }

    return 0;
}
