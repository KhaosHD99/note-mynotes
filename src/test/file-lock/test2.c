#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct flock* file_lock(short type, short whence)
{		
	static struct flock lock;
	lock.l_type = type;
	lock.l_start = 0;
	lock.l_whence = whence;
	lock.l_len = 0;
	lock.l_pid = getpid();
	return &lock;
}
		
int main()
{
	int i;	
	char buf[1024] = {0};
	int len;
	
	int fd = open("1.txt", O_WRONLY|O_APPEND);
	if(fd == -1)
	{	
		printf("Open File Fail!!!!\n");
		return -1;
	}
	else
		printf("Open File Suc\n");
			
	for(i=0; i<10; ++i) 
	{		
		fcntl(fd, F_SETLKW, file_lock(F_WRLCK, SEEK_SET));
		sprintf(buf, "hello world %d\n", i);
		len = strlen(buf);
		printf("XXXXXXXXXXXXXXXXXXXXXX Buf: %s, Len: %d\n", buf, strlen(buf));
		
		write(fd, buf, len);
		fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
		sleep(1);
	}	
	
	if(close(fd) == -1)
	{	
		printf("Close File Fail!!!!\n");
		return -1;
	}	
	
	return 0;
}

