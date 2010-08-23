#include "client.hpp"
#include  <ctype.h>

int main()
{
   int server_fifo_fd, client_fifo_fd;
   struct data_to_pass_st my_data;
   int read_res;
   char client_fifo[256];
   char *filename;
   char buffer[BUFFER_SIZE];
   char *tmp_char_ptr;
   int ctrTag = 1;                // 1 means buffer have something ,2 mean nothing
   int num = 0;

   mkfifo(SERVER_FIFO_NAME, 0777);
   server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);                             //wait for client
   if(server_fifo_fd == -1)
   {
      fprintf(stderr, "Server fifo failure \n");
	  exit(EXIT_FAILURE);
   }
   else
   	  printf("serv_fifo is created,pid: %d \n",getpid());

   sleep(2);

  
   read_res = read(server_fifo_fd,&my_data, sizeof(my_data));
   if(read_res > 0)
   {  
   
      printf("receive request from client,pid is: %d\n",my_data.client_pid);
	  FILE *fp = fopen(my_data.file_name,"r");
      if(fp == NULL)
      {
         printf("Open file error,maybe no such file or directory!\n");
	     exit(1);
      }
	  else
	     printf("Open file successfully!\n");
		 
      sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
	                                
      while(1)
      {  
         int ret;
		 if(num != 0)                                 
		 	read(server_fifo_fd,&ctrTag, sizeof(ctrTag));
         if((ret = fread(buffer,BUFFER_SIZE,1,fp)) != 0)
         {
            num++;
            client_fifo_fd = open(client_fifo, O_WRONLY);
 		    if(client_fifo_fd != -1)
 		    {
 		       write(client_fifo_fd, &ctrTag, sizeof(ctrTag)); 
               write(client_fifo_fd, &buffer, sizeof(buffer));           //write back to client
 		    }
 		    else
 		    {
 		       printf("client_fifo_fd == -1");
		       break;
 		    }
         }
		 else
		 {
		    ctrTag = 2;
		    write(client_fifo_fd, &ctrTag, sizeof(ctrTag)); 
            printf("no data ,readed %d\n",num);
			break;
		 }
         
      }
	  fclose(fp);                
	  close(client_fifo_fd);
   	}
    sleep(5);
    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
	
    exit(EXIT_SUCCESS);
}
