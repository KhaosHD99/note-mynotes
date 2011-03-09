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
* ����޸����ڣ�2010��11��19��
*/

#ifndef _PLAY_ACT_HPP_
#define _PLAY_ACT_HPP_

#include <stdio.h>

#include "LogMsg.hpp"
#include "push_file_define.h"
#include "CCST.hpp"

//ʱ�����±�־��Ϊ0���ʾû�и���,��0��ʾ�и���
extern int g_nfnp_update_flag;
//ʱ����л��ٽ�ʱ��
#define EXPIRE_TIME 2
#define PLAY_ADVER_EXPIRE_TIME 1

class GetNextNameClass
{
	private:
		FN_STATE_ACT_LIST* m_pStateActList[5][FN_STATE_NUM];
	 	TERMINAL_ACT_LIST* m_pActResource;
		TERMINAL_MEDIA_PLAY_INFO_FILE* m_pPlayInfo;
		int act_endtime;
	
	protected:
		void init()
		{	
			m_pStateActList[5][FN_STATE_NUM] = NULL;
			m_pActResource = NULL;
			m_pPlayInfo = NULL;
			act_endtime = 0;
		}
		
	protected:
		//���ص�ǰ�����ļ����ڵ�ʱ��Σ�Ҫ�󲥷����б���Ϊ�����ڵ���ͨ���ŷ���
		TERMINAL_ACT_INFO*  get_slot_time(const FN_STATE_ACT_LIST*,TERMINAL_ACT_LIST*, int &current_pos);
		
		//��ȡУ��ֵ����
		FNDWORD GetCheckValue(void *pBuf, int nLen);
		
	public:
		//��ȡ��һ�������ļ���Ϣ����Ҫ�Ĳ���Ϊ�������ͺͲ���ģʽ
		TERMINAL_ACT_INFO* get_next_name(int area_type,int state);
		static GetNextNameClass *instance;
		
	public:
		int getActEndTime(){return act_endtime;}
		
	public:
		static GetNextNameClass *get_instance(void) ;
		//���ݴ���Ĳ�����ȡ��Ӧ���Ŷ��е������Ϣ
		TERMINAL_ACT_INFO* GetName(const FN_STATE_ACT_LIST*,TERMINAL_ACT_LIST*,int &current_pos,int time_pos);
		FNDWORD read_play_info(const char *szFileName);
		//����ʱ���
		int update_time_act(const char* szFileName, const char* szFileNamebk);
		//���ڸ���ʱ�����ʼ�����ű�־λ
		void InitFlagData(void);  
		
	public:
		GetNextNameClass(){ init();}
		~GetNextNameClass(){}
		
};
#endif

