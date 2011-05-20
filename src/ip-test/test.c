#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <sys/wait.h> 

#if 0
main()
{
	
	#if 1
	int sockfd,client_fd; /**//*sock_fd：监听socket；client_fd：数据传输socket */
	struct sockaddr_in my_addr; /**//* 本机地址信息 */
	struct sockaddr_in remote_addr; /**//* 客户端地址信息 */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	
	　　perror("socket Error\n");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;
　	my_addr.sin_port = htons(SERVPORT);
　	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero),8);
　	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind出错！");
		exit(1);
	}
　	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen出错！");
		exit(1);
	}
	
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &sin_size)) == -1)
		{	
			perror("accept出错");
			continue;
    	}
	　　printf("received a connection from %s ", inet_ntoa(remote_addr.sin_addr));
		if (!fork())
		{
			/**//* 子进程代码段 */
			if (send(client_fd, "Hello, you are connected! ", 26, 0) == -1)
				perror("send出错！");
			close(client_fd);
			exit(0);
		}
	　　close(client_fd);
	}	
	#endif
}
#endif

#if 1
#include <ifaddrs.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>

int main(int	argc,
    	  char **argv)
{	
	char hostname[64];

	gethostname(hostname, sizeof(hostname));
	printf("%s\n", hostname);
	
	struct hostent *hp;
	struct in_addr in;
		
	hp = gethostbyname(hostname);
	
	//printf("%s\n", inet_ntop(*(hp->h_addr_list)));
	
	*(struct in_addr*)(hp->h_addr);
	memcpy(&in,hp->h_addr,sizeof(in));
	printf("%s\n",inet_ntoa(*(struct in_addr*)(hp->h_addr)));
	//memcpy(&in.s_addr, *(hp->h_addr_list), sizeof(in.s_addr));
	//printf("%s\n", inet_ntoa(in));
	//printf("%s\n", inet_ntoa(in.s_addr));
	
	/*struct ifaddrs *id;

	int val;
	
	val = getifaddrs(&id);

	printf("Network Interface Name: %s\n",id->ifa_name);
	printf("Network Address of %s: %d\n",id->ifa_name,id->ifa_addr);
	printf("Network Data: %d \n",id->ifa_data);
	//printf("%s\n",(id->ifa_next)->ifa_name);
	//printf("%d \n",(id->ifa_next)->ifa_addr);


	printf("Socket Data : -%c\n",id->ifa_addr->sa_data);
	*/
	return 0;
}
#endif

