#include "stdio.h"
#include "signal.h"
#include "sys/types.h"
#include "unistd.h"
#include <stdlib.h>
#include <string.h>

void Operation(int sig,siginfo_t * info, void * myact) 
{ 
   printf("recive signal %d\n", sig);
   exit(1);
}

