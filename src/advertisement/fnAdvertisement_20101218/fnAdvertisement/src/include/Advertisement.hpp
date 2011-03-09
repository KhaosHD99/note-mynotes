/*
* Copyright ���ݷ�����Ѷ���޹�˾
* All rights reserved.
* 
* �ļ����ƣ�Play_act.hpp
* 
* ժ    Ҫ����ʱ���Ķ�ȡ�����
* 
* ��    �ߣ���ҫȪ
*
* �޸���:   �����
* 
* ����޸����ڣ�2010��11��10��
*/

#ifndef _ADVERTISEMENT_HPP_
#define _ADVERTISEMENT_HPP_

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>

#include "LogMsg.hpp"
#include "TimeListResolver.hpp"
#include "fnAdvertisementSkinApi.h"
#include "AdverCcInterface.h"
#include "XMLInterface.h"

#define MAX_ROLL_TEXT_COUNT 5

enum
{
	YES,
	NO
};

class Advertisement
{	
	public:	
		//��ǰ���ڲ��ŵĽ�ĿҪ������ʱ��
		int currentEndTime;
		ACTINFO_AND_STOPTIME actInfo;
		
	public:
		Advertisement();
		~Advertisement();
		
		int init_advertisement();
};

class AdverManager
{		
	public:
		int phoneState;
		int phoneStateDirty;
		pthread_mutex_t mutex;
		sem_t timeSem;
		FileSwitch cur_play_type;
		char ROLL_TEXT_LIST[MAX_ROLL_TEXT_COUNT][256];
		int roll_text_play_pos;
		
	private:			
		int run_sign;
		int is_new_fish;
		int is_has_change_privi;
		int is_hot_state;
		Advertisement **adverObjs;
		int is_main_area_available;
        static AdverManager *adver_manager_instance;
		
	private:
		AdverManager();
		~AdverManager();
		int init_adver_manager();
		void uninit_adver_manager();
		
	public:
		static AdverManager *get_instance();	 
		void play_adver();
		void* play_adver_thread(void *pData);
		int chage_state(int current_state, int old_state);
		void *simulateChangeState(void *pData);
		FileSwitch get_current_play_type();
		
    	//enum
		const char* state_enum_to_str(int enum_val);
		const char* area_enum_to_str(int enum_val);
};

#endif

