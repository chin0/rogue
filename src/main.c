#include <unistd.h>
#include <time.h>
#include "../include/util.h"
#include "../include/map.h"
#include "../include/player.h"
#define SET_TERM_SIZE(x,y) system("mode con:cols="#x " lines="#y)

extern int maps[][MAX_X];

char getch()
{
    system("/bin/stty raw");
    char a = getchar();
    system("/bin/stty cooked");
    return a;
}

int main(void)
{
    char input;
    generate_map();
    player_init(12,20,3,0);
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
        } else {
            player_move(input);
        }
    }
    return 0;
}
