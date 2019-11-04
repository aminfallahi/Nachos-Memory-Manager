/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int
main()
{
  int result;
  char* buffer="salam";
  
  result = Add(42, 23);
  //while (1==1)
  ConsoleWrite(buffer,5);
  //Halt();
  /* not reached */
}
