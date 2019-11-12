#include "syscall.h"

void dummyFunc(int dum){
    char *buffer="foooork";
    ConsoleWrite(buffer,6);
}

int
main()
{

    char *buffer="aaaaaaaa";
    int size=7;
    int tid=0;
    int i;
    ConsoleRead(buffer,size);
    ThreadFork(dummyFunc);

    for (i=0; i<10; i++)
        Exec("../test/amintest2");
    ConsoleWrite(buffer,size);

}