#include "syscall.h"

int
main()
{

    int i;
    char* buffer="00000";
    for (i=0; i<10; i++){
        ConsoleRead(buffer,5);
        ConsoleWrite(buffer,5);
    }

}