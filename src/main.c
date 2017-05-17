#include <unistd.h>
#include <time.h>
#include "../include/util.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/monster.h"
#define SET_TERM_SIZE(x,y) system("mode con:cols="#x " lines="#y)

extern int maps[][MAX_X];



int main(void)
{
    char input;
    int success;
    generate_map();
    player_init(12,20,3,0);
    create_monster();
    create_monster();
    create_monster();
    while(1)
    {
        int collected = 0;
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
        }
        if(input == 'e') {
            if(in_exit){
                success = 1;
                break;
            }
        } else {
            player_move(input);
            collected = 0;
        }
        attack();
    }
    if(success) {
        system("clear");
        printf("성공적으로 탈출했습니다!\n");
        printf("모은금:%d\n", _player.gold);
    }

    return 0;
}
