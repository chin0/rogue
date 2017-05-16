#include "../include/util.h"
#include "../include/map.h"

extern int maps[][MAX_X];

int main(void)
{
    printf("press any key to generate map!!(q is quit..)");

    for(int i = 0; i < 9; i++)
        generate_map();

    for(int i = 0; i < MAX_Y; i++){
        for(int j = 0; j < MAX_X; j++){
            if(maps[i][j])
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}
