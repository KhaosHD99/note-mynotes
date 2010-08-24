#include "stdio.h"
#include "signal.h"
#include "sys/types.h"
#include "unistd.h"
#include <stdlib.h>
#include <string.h>
#include "COperation.hpp"

int main(int argc, char**argv) 
{
    struct sigaction act; 
	struct sigaction old_act; 
	int sig; 
    sig = atoi(argv[1]);
	 
    sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = Operation; 
	 
   if(sigaction(sig, &act, &old_act) < 0) 
   	{
   	   printf("register sigal error\n");
	   return 1;
   	}
	 
     while(1) 
	 { 
	    printf("waiting for signal\n");
	    sleep(2);
		kill(getpid(),18);
	 }
}


