/*
* Copyright 广州泛网视讯有限公司
* All rights reserved.
* 
* 文件名称：Play_act.hpp
* 
* 摘    要：对时间表的读取与分析
* 
* 作    者：吴耀泉
*
* 修改者:   徐镇杰
* 
* 最后修改日期：2010年11月19日
*/

#ifndef _PLAY_ACT_HPP_
#define _PLAY_ACT_HPP_

#include <stdio.h>

#include "LogMsg.hpp"
#include "push_file_define.h"
#include "CCST.hpp"

//时间表更新标志，为0表表示没有更新,非0表示有更新
extern int g_nfnp_update_flag;
//时间段切换临界时间
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
		//返回当前播放文件所在的时间段，要求播放序列必须为主窗口的普通播放方案
		TERMINAL_ACT_INFO*  get_slot_time(const FN_STATE_ACT_LIST*,TERMINAL_ACT_LIST*, int &current_pos);
		
		//获取校验值函数
		FNDWORD GetCheckValue(void *pBuf, int nLen);
		
	public:
		//获取下一个播放文件信息，需要的参数为窗口类型和播放模式
		TERMINAL_ACT_INFO* get_next_name(int area_type,int state);
		static GetNextNameClass *instance;
		
	public:
		int getActEndTime(){return act_endtime;}
		
	public:
		static GetNextNameClass *get_instance(void) ;
		//根据传入的参数获取相应播放队列的相关信息
		TERMINAL_ACT_INFO* GetName(const FN_STATE_ACT_LIST*,TERMINAL_ACT_LIST*,int &current_pos,int time_pos);
		FNDWORD read_play_info(const char *szFileName);
		//更新时间表
		int update_time_act(const char* szFileName, const char* szFileNamebk);
		//用于更新时间表后初始化播放标志位
		void InitFlagData(void);  
		
	public:
		GetNextNameClass(){ init();}
		~GetNextNameClass(){}
		
};
#endif

