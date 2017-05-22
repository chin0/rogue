//
// Created by kafuuchin0 on 22.05.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scoreboard.h"
score_struct* create_score_struct(int gold,int turn,int len) {
    score_struct *ret = malloc(sizeof(score_struct));

    ret->gold = gold;
    ret->turn = turn;
    ret->len = len;

    ret->name = malloc(len + 1);
    printf("name: ");
    fgets(ret->name, len, stdin);
    for (int i = 0; i < len; i++)
        if (ret->name[i] == '\n') {
            ret->name[i] = '\0';
            break;
        }

    return ret;
}
void remove_score_struct(score_struct* tar){
    free(tar->name);
    free(tar);
}

void scan_scoreboard(FILE* fp){
    int line;

}

