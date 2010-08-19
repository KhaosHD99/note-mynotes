#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   pid_t pid;
   char *message;
   int n;
   int exit_code;

   printf("fork program starting \n");
   pid = fork();
   printf("fork return id: %d \n",pid);
   switch(pid)
   {
      case -1:
	  	 perror("fork failed");
		 exit(1);
	  case 0:
	  	 message = "This is the child";
		 printf("i am child,pid: %d \n",getpid());
		 n = 4;
		// exit_code = 37;
		 break;
	  default:
	  	 message = "this is the Parent";
		 printf("i am parent,pid: %d \n",getpid());
		 n = 2;
	//	 exit_code = 0;
		 break;
   }

   for(;n > 0; n--)
   {
      puts(message);
      sleep(1);
   }

   if(pid != 0)
   {
      int stat_val;
	  pid_t child_pid;

	  child_pid = wait(&stat_val);

	  printf("Child has finished: PID = %d \n",child_pid);
	  if(WIFEXITED(stat_val))
	  	 printf("Child exited with code %d \n",WEXITSTATUS(stat_val));
      else
	     printf("Child terminated abnormally \n");
   }

   exit(5);
}
