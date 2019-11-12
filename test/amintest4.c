#include "syscall.h"
//#include <stdio.h>

/*void forkedFunc(){
    Exec("../test/amintest2");
}*/

int
main()
{

    char *buffer="bbbbbb";
    int i; 
    
    ConsoleWrite(buffer,5);
    for (i=0; i<100; i++)
        Exec("../test/amintest3");
    
    Exit(1);
}