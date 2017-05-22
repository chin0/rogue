#include <termios.h>
#include "../include/util.h"

int get_random_number(int min,int max)
{
    unsigned int ret;

    int fd = open("/dev/urandom",O_RDONLY);


    read(fd,&ret,sizeof(unsigned int));
    ret = ret % (max+1);

    while(ret < min || ret > max){
        read(fd,&ret,sizeof(unsigned int));
        ret = ret % max;
    }

    return ret;
}
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}