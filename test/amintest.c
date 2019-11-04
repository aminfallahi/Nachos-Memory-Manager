#include "syscall.h"
//#include <stdio.h>

void dummyFunc(int dum){
    char *buffer="foooork";
    while(1==1)
    ConsoleWrite(buffer,6);
}

int
main()
{

    char *buffer;
    int size=7;
    int tid;
    ConsoleRead(buffer,size);
    ConsoleWrite(buffer,size);
    //tid=ThreadFork(dummyFunc);
    //while(1==1)
    //ConsoleWrite(buffer,size);
    Exec("/home/amin/Documents/Nachos-Memory-Manager/test/add");
    while(1==1);
    Halt();
}