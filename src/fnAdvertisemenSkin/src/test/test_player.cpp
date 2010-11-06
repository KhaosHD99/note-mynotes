/* Compile me with: 
*   gcc -o tut tut.c $(pkg-config --cflags --libs gtk+-2.0 gmodule-2.0) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "LogMsg.hpp"

struct st_argvs
{
	int argc;
	char **argv;	
};

//extern "C" int initWindow(int argc, char *argv[]);
extern "C" int init_play_window(struct st_argvs *argvs);
extern "C" int tick_adver_simulation();

pthread_t playTimePthreadID;	//线程ID

static void *playerTimeThread(void *pData)		//时间线程(只有一个这种线程)
{
	if(pData == NULL)
		return (void*)NULL;

	st_argvs *argvs = (st_argvs *)pData;
		
	return (void*)init_play_window(argvs);
}


int main(int argc, char *argv[])
{
	int ret = 0;
	st_argvs argvs;
	
	argvs.argc = argc;
	argvs.argv = argv;

	//创建广告时间线程
	ret = pthread_create(&playTimePthreadID, 
							NULL, 
							playerTimeThread, 
							(void *)&argvs);
	if(ret != 0)
	{
		showWarning("Create playerTimeThread %d fail\n", ret);
	}
	else
		showWarning("Create playerTimeThread %d Success\n", ret);

	static int count = 0;
	while(true)
	{
		usleep(1500*1000);
		count++;
		showWarning("waiting for exit : %d\r\n", count);
//		tick_adver_simulation();
	}

	//return initWindow(argc, argv);
}
