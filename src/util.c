#include "../include/util.h"

int get_random_number(int min,int max)
{
    unsigned int ret;

    int fd = open("/dev/urandom",O_RDONLY);


    read(fd,&ret,sizeof(unsigned int));
    ret = ret % max;

    while(ret < min || ret > max){
        read(fd,&ret,sizeof(unsigned int));
        ret = ret % max;
    }

    return ret;
}
char getch()
{
    system("/bin/stty raw");
    char a = getchar();
    system("/bin/stty cooked");
    return a;
}
