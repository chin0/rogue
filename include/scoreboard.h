//
// Created by kafuuchin0 on 22.05.17.
//

#ifndef ROGUE_SCOREBOARD_H
#define ROGUE_SCOREBOARD_H

typedef struct {
    int gold;
    int turn;
    int len;
    char* name;
}score_struct;

score_struct* create_score_struct(int gold,int turn,int len);
void remove_score_struct(score_struct* tar);
#endif //ROGUE_SCOREBOARD_H
