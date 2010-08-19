#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   char *filename;

   if(argc !=2)
   {
      fprintf(stderr,"usage: userupper file \n");
	  exit(1);
   }
   filename = argv[1];

   if(!freopen(filename, "r", stdin))
   {
      fprintf(stderr, "could not redirect stdin from file %s \n",filename);
	  exit(2);
   }

   exec("./upper","upper",0);
   perror("could not exec ./upper");
   exit(3);
}

