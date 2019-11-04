// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------

void userForkFunction(int dum){
    kernel->currentThread->RestoreUserState();
    kernel->machine->Run();
}

void userExecFunction(Thread* thread){
    thread->space->Execute();
}

void
ExceptionHandler(ExceptionType which) {
    int type = kernel->machine->ReadRegister(2);

    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which) {
        case SyscallException:
            switch (type) {
                case SC_Halt:
                    DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

                    SysHalt();

                    ASSERTNOTREACHED();
                    break;

                case SC_Add:
                    DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

                    /* Process SysAdd Systemcall*/
                    int result;
                    result = SysAdd(/* int op1 */(int) kernel->machine->ReadRegister(4),
                            /* int op2 */(int) kernel->machine->ReadRegister(5));

                    DEBUG(dbgSys, "Add returning with " << result << "\n");
                    /* Prepare Result */
                    kernel->machine->WriteRegister(2, (int) result);

                    /* Modify return point */
                {
                    /* set previous program counter (debugging only)*/
                    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

                    /* set program counter to next instruction (all Instructions are 4 byte wide)*/
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

                    /* set next program counter for brach execution */
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                }

                    return;

                    ASSERTNOTREACHED();

                    break;

                case SC_ConsoleRead:
                {
                    int addr = kernel->machine->ReadRegister(4);
                    int size = kernel->machine->ReadRegister(5);
                    SysRead(addr, size);
                    /* set program counter to next instruction (all Instructions are 4 byte wide)*/
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    /* set next program counter for brach execution */
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                }

                    return;
                    ASSERTNOTREACHED();
                    break;

                case SC_ConsoleWrite:
                {
                    int addr = kernel->machine->ReadRegister(4);
                    int size = kernel->machine->ReadRegister(5);
                    SysWrite(addr, size);
                    /* set program counter to next instruction (all Instructions are 4 byte wide)*/
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    /* set next program counter for brach execution */
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                }

                    return;
                    ASSERTNOTREACHED();
                    break;

                case SC_ThreadFork:
                {
                    int funcAddr = kernel->machine->ReadRegister(4);
                    Thread *child = new Thread("");
                    child->space = new AddrSpace(kernel->currentThread->space);
                    child->SaveUserState();
                    child->setUserRegister(PCReg, funcAddr);
                    child->setUserRegister(NextPCReg, funcAddr + 4);
                    child->Fork((VoidFunctionPtr) userForkFunction, 0);
                    kernel->machine->WriteRegister(2,child->getId());
                    /* set program counter to next instruction (all Instructions are 4 byte wide)*/
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    /* set next program counter for brach execution */
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                }

                    return;
                    ASSERTNOTREACHED();
                    break;
        
                case SC_Exec:
                {
                    int prog = kernel->machine->ReadRegister(4);
                    int i;

                    //reading file name from memory
                    char* progFile=(char*)malloc(100*sizeof(char));                
                    for (i=0; ; i++){
                        kernel->machine->ReadMem(prog+i,1,(int*)&progFile[i]);
                        if (progFile[i]=='\0')
                            break;
                    }
                    Thread *th = new Thread("");
                    th->space = new AddrSpace();
                    th->space->Load(progFile);
                    th->Fork((VoidFunctionPtr) userExecFunction, th);
                    kernel->machine->WriteRegister(2,th->space->getId());
                    /* set program counter to next instruction (all Instructions are 4 byte wide)*/
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    /* set next program counter for brach execution */
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                }

                    return;
                    ASSERTNOTREACHED();
                    break;
                    
                default:
                    cerr << "Unexpected system call " << type << "\n";
                    break;
            }
            break;
        default:
            cerr << "Unexpected user mode exception" << (int) which << "\n";
            break;
    }
    ASSERTNOTREACHED();
}
