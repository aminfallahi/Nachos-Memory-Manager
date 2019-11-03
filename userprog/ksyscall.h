/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"




void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

void SysRead(int addr, int size){
    printf("SysRead called\n");
    char* toRead="dummyread";
    int i;
    for (i=0; i<size; i++){
        kernel->machine->WriteMem(addr,1,toRead[i]);
        addr++;
    }
}

void SysWrite(int addr, int size){
    printf("SysWrite called\n");
    int i;
    int temp;
    for (i=0; i<size; i++){
        kernel->machine->ReadMem(addr,1,&temp);
        printf("%c",temp);
        addr++;
    }
    printf("\n");
}



#endif /* ! __USERPROG_KSYSCALL_H__ */
