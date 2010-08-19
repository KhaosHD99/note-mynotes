#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   pid_t pid1, pid2;
   int n;
   
   printf("fork program starting \n");
   if((pid1 = fork()) == -1)
   {
      perror("fork1 failed");
	  exit(1);
   }
   if(pid1 == 0)
   {
      printf("i am child1,pid: %d \n",getpid());
	  system("ls -l");
   }
   else
   {
      if((pid2 = fork()) == -1)
      {
	  	 perror("fork1 failed");
	     exit(1);
      }
	  if(pid2 == 0)
	  {
         printf("i am child2,pid: %d \n",getpid());
		 sleep(5);
	  }
	  else
	  {
	  	 printf("i am parent,pid: %d \n",getpid());
	     int stat_val;
	     pid_t child_pid;

         child_pid = waitpid(pid1,&stat_val,0);
		 printf("Child1 has finished: PID = %d \n",child_pid);
		 while(1)
		 {
	        child_pid = waitpid(pid2,&stat_val,WNOHANG);
		    if(child_pid == 0)
		       sleep(2);
			else
			   break;
		 }
		 printf("Child2 has finished: PID = %d \n",child_pid);
	  }
   	}
   
   exit(5);
}
