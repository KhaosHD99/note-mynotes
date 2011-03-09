#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "AdverModule.h"
#include "ModuleID.hpp"

VialSystem *sendVialSys = NULL;
AdverModule *adver_send_test = NULL;

/**************************************************************
                             thread_adv_play_module
**************************************************************/
static void *thread_adv_play_module(void *data)
{
#ifdef APP_ONE
#if 1  /* Require CC */
	VialSystem vialSys(FN_ADVPLAY_MODULE_ID);
	//VialSystem vialSys(FN_PHONE_BOOK_MODULE_ID);
	AdverModule *adver = AdverModule::get_instance(&vialSys);
																
	if(adver)
	{
		adver->init();
		adver->run();
	}
	else
		return NULL;
#endif

#if 0 /* No Require CC */
	VialSystem *vialSys = NULL;
	VialSystem vialSystem(FN_ADVPLAY_MODULE_ID);

	vialSys = &vialSystem;
    MyClass myReceiver;
	vialSys->addReceiver(&myReceiver);
	vialSys->run();
#endif

#elif defined(APP_TWO)     /* Post Test */
	#if 0
	VialSystem vialSys(FN_PHONE_BOOK_MODULE_ID);
	AdverModule *adver = AdverModule::get_instance(&vialSys);
																
	if(adver)
	{
		adver->init();
		adver->run();
	}
	else
		return NULL;
	#endif
	
	#if 1
	printf("APP_TWO: Just A Send Test Thread\n");
	char inputString[64];
	
	for (;;)
	{	
		scanf("%s", inputString);
		if (strcasecmp("on_hook", inputString) == 0)
		{	
			StateChangeVial vial;
			CCST ccst;
			
			ccst.st = CCST::ON_HOOK;
			vial.curState = ccst;
			
			ccst.st = CCST::DIALING;
			vial.oldState = ccst;
			/* No Require CC */
			//sendVialSys->postVial(&vial, FN_ADVPLAY_MODULE_ID);

			adver_send_test->post_vial(&vial, FN_ADVPLAY_MODULE_ID);

			/* Send to CC */           
			//adver_send_test->post_vial(&vial, FN_COMM_CENTER_MODULE_ID);
		}
		else if (strcasecmp("off_hook", inputString) == 0)
		{	
			StateChangeVial vial;
			CCST ccst;
			
			ccst.st = CCST::DIALING;
			vial.curState = ccst;
			
			ccst.st = CCST::DIALING;
			vial.oldState = ccst;
			/* No Require CC */
			//sendVialSys->postVial(&vial, FN_ADVPLAY_MODULE_ID);
			
			adver_send_test->post_vial(&vial, FN_ADVPLAY_MODULE_ID);
			
			/* Send to CC */           
			//adver_send_test->post_vial(&vial, FN_COMM_CENTER_MODULE_ID);
		}
		else if (strcasecmp("ringing", inputString) == 0)
		{	
			StateChangeVial vial;
			CCST ccst;
			
			ccst.st = CCST::RINGING;
			vial.curState = ccst;
			
			ccst.st = CCST::DIALING;
			vial.oldState = ccst;
			/* No Require CC */
			//sendVialSys->postVial(&vial, FN_ADVPLAY_MODULE_ID);
			
			adver_send_test->post_vial(&vial, FN_ADVPLAY_MODULE_ID);

			/* Send to CC */           
			//adver_send_test->post_vial(&vial, FN_COMM_CENTER_MODULE_ID);
		}
		else if (strcasecmp("novideo", inputString) == 0)
		{	
			StateChangeVial vial;
			CCST ccst;
			
			ccst.st = CCST::NOVIDEO_CONN;
			vial.curState = ccst;
			
			ccst.st = CCST::DIALING;
			vial.oldState = ccst;
			/* No Require CC */
			//sendVialSys->postVial(&vial, FN_ADVPLAY_MODULE_ID);
		
			adver_send_test->post_vial(&vial, FN_ADVPLAY_MODULE_ID);

			/* Send to CC */           
			//adver_send_test->post_vial(&vial, FN_COMM_CENTER_MODULE_ID);
		}
		else if (strcasecmp("video", inputString) == 0)
		{	
			StateChangeVial vial;
			CCST ccst;
			
			ccst.st = CCST::VIDEO_CONN;
			vial.curState = ccst;
			
			ccst.st = CCST::DIALING;
			vial.oldState = ccst;
			/* No Require CC */
			//sendVialSys->postVial(&vial, FN_ADVPLAY_MODULE_ID);
			
			adver_send_test->post_vial(&vial, FN_COMM_CENTER_MODULE_ID);
			
			/* Send to CC */           
			//adver_send_test->post_vial(&vial, FN_COMM_CENTER_MODULE_ID);
		}
		else
		{
			printf("Wrong input\n");
		}
	}	
 	#endif
	
#else
#error no def APP_ONE or APP_TWO
#endif
}

/***********************************************************************************************
                                                             creat_and_run_prompter_module
***********************************************************************************************/
#ifdef __cplusplus
extern"C"
{
#endif
int creat_and_run_adv_play_module()
{	
	pthread_t adv_play_module_thread;
	
#ifdef APP_ONE
	if(pthread_create(&adv_play_module_thread, NULL, thread_adv_play_module, NULL) == 0)
	{
		printf("thread create Ok, promptermodule thread start \n");
		return 0;
	}
	else
	{
		printf("thread promptermodule create Err\n");
		return -1;
	}
#elif defined(APP_TWO)   /* Post Test */
	#if 0
	if(pthread_create(&adv_play_module_thread, NULL, thread_adv_play_module, NULL) == 0)
	{
		printf("thread create Ok, promptermodule thread start \n");
		return 0;
	}
	else
	{
		printf("thread promptermodule create Err\n");
		return -1;
	}
	#endif
	
	#if 1 /* Require CC */
	VialSystem vialSys(FN_PHONE_BOOK_MODULE_ID);
	
	adver_send_test = AdverModule::get_instance(&vialSys);
	
	if(adver_send_test)
		adver_send_test->init();
	else
		return -1;
	
	if(pthread_create(&adv_play_module_thread, NULL, thread_adv_play_module, NULL) == 0)
	{
		printf("thread create Ok, promptermodule thread start \n");
	}
	else
	{
		printf("thread promptermodule create Err\n");
	}
	
	adver_send_test->run();
	#endif
#else
	#error no def APP_ONE or APP_TWO
#endif
}
#ifdef __cplusplus
}
#endif

