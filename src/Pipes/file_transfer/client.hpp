#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

#define SERVER_FIFO_NAME "serv_fifo"
#define CLIENT_FIFO_NAME "cli_%d_fifo"

#define FILE_NAME_SIZE 20
#define BUFFER_SIZE 1

struct data_to_pass_st
{
   pid_t client_pid;
   char file_name[FILE_NAME_SIZE];
};
