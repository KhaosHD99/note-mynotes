#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int write_lock(int fd, short whence)
{	
	static struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_start = 0;
	lock.l_whence = whence;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(fd, F_SETLKW, &lock);
		
	return fcntl(fd, F_SETLKW, &lock);
}	
	
int unlock(int fd, short whence)
{	
	static struct flock lock;
	lock.l_type = F_UNLCK;
	lock.l_start = 0;
	lock.l_whence = whence;
	lock.l_len = 0;
	lock.l_pid = getpid();
		
	return fcntl(fd, F_SETLKW, &lock);
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
		//fcntl(fd, F_SETLKW, file_lock(F_WRLCK, SEEK_SET));
		if(write_lock(fd, SEEK_SET) == -1)
		{	
			printf("XXXXXXXXXXXXXX Write Lock Fail\n");
			return -1;
		}	
		else
			printf("Write Lock Suc\n");
		
		sprintf(buf, "hello world %d\n", i);
		len = strlen(buf);
		printf("Buf: %s, Len: %d\n", buf, strlen(buf));
		
		write(fd, buf, len);
		sleep(1);
		//fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
		if(unlock(fd, SEEK_SET) == -1)
		{
			printf("XXXXXXXXXXXXXX UnLock Fail\n\n");
			return -1;
		}
		else
			printf("UnLock Suc\n");
	}	
	
	if(close(fd) == -1)
	{	
		printf("Close File Fail!!!!\n");
		return -1;
	}	
	
	return 0;
}

