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
   if(pid1 == 0)                                             //child 1
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
	  if(pid2 == 0)                                          //child 2
	  {
         printf("i am child2,pid: %d \n",getpid());
		 sleep(5);
	  }
	  else                                                   //parent
	  {
	  	 printf("i am parent,pid: %d \n",getpid());
	     int stat_val;
	     pid_t child_pid;

         child_pid = waitpid(pid1,&stat_val,0);              //wait child 1 with block
		 printf("Child1 has finished: PID = %d \n",child_pid);
		 while(1)
		 {
	        child_pid = waitpid(pid2,&stat_val,WNOHANG);     //wait child 2 without block    
		    if(child_pid == 0)
		       sleep(2);                                     //if child 2 hasn't terminated,sleep for a while
			else
			   break;
		 }
		 printf("Child2 has finished: PID = %d \n",child_pid);
	  }
   	}
   
   exit(5);
}
