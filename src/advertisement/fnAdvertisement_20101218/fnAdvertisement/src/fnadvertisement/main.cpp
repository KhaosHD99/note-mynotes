/*
* Copyright 广州泛网视讯有限公司
* All rights reserved.
* 
* 文件名称：Main.cpp
* 
* 摘    要：广告应用主函数
* 
* 作    者：吴耀泉
*
* 修改者:   徐镇杰
* 
* 最后修改日期：2010年11月20日
*/

#if 1
#include "AdvertisementInterface.hpp"
#include "AdverCcInterface.h"
#include "Vial.hpp"
#include "VialType_Common.hpp"

pthread_t player_thread_id;
pthread_t play_adver_thread_id;
pthread_t simulate_change_state_thd_id;

typedef struct st_argvs
{
	int argc;
	char **argv;
}st_argvs;

st_argvs argvs;
	
/* Init Time List */
int initTimelist()
{
	if (!GetActName::get_instance()->read_play_act())
		showWarning("read timeList fail.\n");
	else
		showDebug("read timeList suc.\n\n");
}
	
/* Vial Test  */
#define APP_ONE_ID 88
#define APP_TWO_ID 89
	
#ifdef APP_ONE
const NodeID nodeID = APP_ONE_ID;
#elif defined(APP_TWO)
const NodeID nodeID = APP_TWO_ID;
#else
#error no def APP_ONE or APP_TWO
#endif

int main(int argc, char *argv[])
{	
#if 0
	#ifdef APP_ONE
	printf("app_one\n");
	#elif defined(APP_TWO)
	printf("app_two\n");
	#else
	#error no def APP_ONE or APP_TWO
	#endif
	
	
	int ret = creat_and_run_adv_play_module();
	if(ret != 0)
	{
		printf("run adver module error : %d....\r\n", ret);
	}
	else
		printf("run adver module scuess...\r\n");

	while(1)
	{
		sleep(5);
		//printf("wait for exit!\r\n");
	}
	 
	return 0;
#endif

#ifdef APP_ONE
	int ret = 0;
	sem_t timeSem;
	char img_path[128];
	struct timeval tv;
	struct timespec sp;
	
	/* Initial Advertisment Time List */
	initTimelist();
    sem_init(&timeSem, 0, 0);
	
    /* Init Playe Window */
	sprintf(img_path, "%s%s", IMAGE_PATH_PREFIX, INIT_IMAGE);	
	if(init_adver_play(img_path))
	{
		showError("Init adver play window fail\n");
		return 0;
	}
	
	#if 1
	/* Create Play Advertisement Thread */
    ret = pthread_create(&play_adver_thread_id,
			              NULL,
	                      play_adver_thread,
	                      NULL);
	if(ret != 0)
	{
		showWarning("Create playTimeThread %d fail\n", ret);
		return -1;
	}
    #endif
	
#if 1 /* Wait CC Vial */
	#ifdef APP_ONE
	printf("app_one\n");
	#elif defined(APP_TWO)
	printf("app_two\n");
	#else
	#error no def APP_ONE or APP_TWO
	#endif
	
	ret = creat_and_run_adv_play_module();
	if(ret != 0)
	{
		printf("run adver module error : %d....\r\n", ret);
	}
	else
		printf("run adver module scuess...\r\n");


	/*
	ret = creat_and_run_prompter_module();
	if(ret != 0)
	{
	  printf("run prompter module error : %d....\r\n", ret);
	}
	else
		printf("run prompter module scuess....\r\n");
	*/
	#if 0
    /* Create Play Change State Thread */
	ret = pthread_create(&simulate_change_state_thd_id,
						  NULL,
						  simulate_change_state,
						  NULL);
    if(ret != 0)
	{
		showWarning("Create SimulateChangeStateThread %d fail\n", ret);
		return -1;
	}
	#endif
#endif
	
	/* wait */
	while(1)
	{
	    gettimeofday (&tv , NULL);
		sp.tv_sec = tv.tv_sec + 1;
		sp.tv_nsec = tv.tv_usec;
		sem_timedwait(&timeSem, &sp);
	}
	
	return 0;
#elif defined(APP_TWO)
	int ret = 0;
	ret = creat_and_run_adv_play_module();
#else
#error no def APP_ONE or APP_TWO
#endif

}
#endif

