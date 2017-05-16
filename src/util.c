#include "../include/util.h"

int get_random_number(int min,int max)
{
    int ret;

    srand(time(NULL));

    ret = rand() % max;

    while(ret < min || ret > max)
        ret = rand() % max;

    return ret;
}
