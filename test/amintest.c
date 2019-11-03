#include "syscall.h"
//#include <stdio.h>
int
main()
{

    char *buffer;
    int size=7;
    ConsoleRead(buffer,size);
    ConsoleWrite(buffer,size);
    //printf("%s\n",buffer);
    Halt();
}
