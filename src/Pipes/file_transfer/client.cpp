#include "client.hpp"
#include <ctype.h>

int main()
{
   int server_fifo_fd, client_fifo_fd;
   struct data_to_pass_st my_data;
   int times_to_send;
   char client_fifo[256];
   char buffer[BUFFER_SIZE];              
   int ctrTag = 0;                              // 1 means had readed buffer to file,2 is server passed no buffer
   int num = 0;

   server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);                          //server check
   if(server_fifo_fd == -1)
   {
      fprintf(stderr, "no server \n");
	  exit(EXIT_FAILURE);
   }

   my_data.client_pid = getpid();                                             //create client fifo     
   sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
   if(mkfifo(client_fifo, 0777) == -1)
   {
      fprintf(stderr, "can't make %s \n",client_fifo);
	  exit(EXIT_FAILURE);
   }
   else
      printf("client_fifo is created,pid: %d\n",getpid());

   FILE *fp = fopen("receive/testfile","wt");                           //put receive file to folder "recieve"
   if(fp==NULL)
   {
      printf("Open or create error!\n");
	  exit(1);
   }
   else
	  printf("Open or create successfully!\n");
	  
   sprintf(my_data.file_name, "testfile");                               //requst file "testfile"
   printf("%d request %s \n",my_data.client_pid,my_data.file_name);
   write(server_fifo_fd, &my_data, sizeof(my_data));                          //write to server

   while(1)
   {
	  num++;
	  if(ctrTag == 1)
         write(server_fifo_fd, &ctrTag, sizeof(ctrTag));
	  client_fifo_fd = open(client_fifo, O_RDONLY);
      read(client_fifo_fd,&ctrTag, sizeof(ctrTag));
	  if(ctrTag == 2)                                            //no buffer
	     break;
		 
	  if(client_fifo_fd != -1)
	  {
         if(read(client_fifo_fd, &buffer, sizeof(buffer)) > 0)
         {
            printf("received data \n");
			fwrite(buffer,BUFFER_SIZE,1,fp);
			printf("writed element %d\n",num);
			ctrTag = 1;
         }
		 close(client_fifo_fd);
			
      }
	  else
	  {
	  	 printf("client_fifo_fd == -1");
         break;
      }
   }
  
   fclose(fp);
   close(server_fifo_fd);
   unlink(client_fifo);
   exit(EXIT_SUCCESS);
}
