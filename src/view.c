//
// Created by kafuuchin0 on 21.05.17.
//

#include "../include/util.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/monster.h"

void print_map()
{
    for(int i = 0; i < MAX_Y; i++){
        for(int j = 0; j < MAX_X; j++){
            switch(maps[i][j]){
                case PLAYER:
                    printf("@");
                    break;
                case DOOR:
                    printf("\u2592");
                    break;
                case TUNNEL:
                    printf("\u2591");
                    break;
                case WALL:
                    printf("\u2588");
                    break;
                case ROOM_TILE:
                    printf("\u2593");
                    break;
                case MON_MEGUMI:
                    printf("M");
                    break;
                case MON_ERIRI:
                    printf("E");
                    break;
                case MON_UTAHA:
                    printf("U");
                    break;
                case MON_MITCHIRU:
                    printf("m");
                    break;
                case MON_CHINO:
                    printf("C");
                    break;
                case MON_RIKKA:
                    printf("R");
                    break;
                case MON_TOMORI:
                    printf("T");
                    break;
                case GOLD:
                    printf("%%");
                    break;
                case EXIT:
                    printf("^");
                    break;
                default:
                    printf(" ");
                    break;
            }
        }
        printf("\n");
    }
}