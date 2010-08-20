#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

int main()
{
   pid_t pid1, pid2;
   int n;
   
   if((pid1 = fork()) == -1)
   {
      perror("fork1 failed");
	  exit(1);
   }
   if(pid1 == 0)                                                //child 1
   {
      printf("I am child 1,who is a deamon process, pid: %d \n",getpid());             
	  if((pid2 = fork()) == -1)
      {
	  	 perror("fork2 failed");
	     exit(1);
      }
	  if(pid2 == 0)                                             //child 2
	  {
	     printf("I am child 2,pid: %d \n",getpid());      
		 syslog(LOG_INFO|LOG_USER, "i am child2\n");            //when child 2 is created, write message to syslog
		 sleep(10);
	  }
	  else                                                      //child 1
	  {
	     int stat_val;
	     pid_t child_pid;
		 printf("I am child 1,waiting for the terminating of child 2\n",getpid());	 
         child_pid = waitpid(pid2,&stat_val,0);                  
		 printf("Child 2 has finished: PID = %d \n",child_pid);
		 syslog(LOG_INFO|LOG_USER, "child 2 is terminated \n");  //when child 2 is terminated, write message to syslog
		 sleep(10);                                             
	  }
   }
   else                                                          //parent
   {
      
   }
   
   exit(5);
}

