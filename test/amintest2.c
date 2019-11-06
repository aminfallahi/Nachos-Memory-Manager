#include "syscall.h"
//#include <stdio.h>

void dummyFunc(int dum){
    char *buffer="foooork";
    //ConsoleWrite(buffer,6);
}

int
main()
{

    char *buffer="bbbbbb";
    int size=7;
    int tid;
    //ConsoleRead(buffer,size);
    //while(1==1)
    ConsoleWrite(buffer,size);
    //tid=ThreadFork(dummyFunc);
    //while(1==1)
    //ConsoleWrite(buffer,size);
    //Exec("/home/amin/Documents/Nachos-Memory-Manager/test/add");
    //ThreadFork((void*)dummyFunc);
    //ConsoleWrite(buffer,size);
    //while(1==1);
    //Exit(1);
    //ConsoleWrite(buffer,size);
}