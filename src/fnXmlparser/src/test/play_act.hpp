#ifndef _PLAY_ACT_HPP_
#define _PLAY_ACT_HPP_

#include <stdio.h>
#include "LogMsg.hpp"
#include "push_file_define.h"


extern int g_nfnp_update_flag;//时间表更新标志，为0表表示没有更新,非0表示有更新
/*******************************************************************************************/
#define EXPIRE_TIME                             2 //时间段切换临界时间
/*******************************************************************************************/


class GetNextNameClass
{

	private:
		FN_STATE_ACT_LIST* m_pStateActList[3][FN_STATE_NUM];
	 	TERMINAL_ACT_LIST* m_pActResource;
		TERMINAL_MEDIA_PLAY_INFO_FILE* m_pPlayInfo;
		int act_endtime;

	protected:
		void init()
		{
			m_pStateActList[3][FN_STATE_NUM] = NULL;
	 		m_pActResource = NULL;
			m_pPlayInfo = NULL;
			act_endtime = 0;
		}
	protected:
		//返回当前播放文件所在的时间段，要求播放序列必须为主窗口的普通播放方案
		TERMINAL_ACT_INFO*  GetSlotTime(const FN_STATE_ACT_LIST*,TERMINAL_ACT_LIST*, int &k);
		
		//获取校验值函数
		FNDWORD GetCheckValue(void *pBuf, int nLen);
		
	public:
		//获取下一个播放文件信息，需要的参数为窗口类型和播放模式
		TERMINAL_ACT_INFO* GetNextName(int window_type,int paly_mod);
		static GetNextNameClass *instance;

	public:
		int getActEndTime(){return act_endtime;}
		
	public:
		static GetNextNameClass *getInstance(void) ;
		//根据传入的参数获取相应播放队列的相关信息
		TERMINAL_ACT_INFO* GetName(const FN_STATE_ACT_LIST*,TERMINAL_ACT_LIST*,int &current_pos,int time_pos);
		FNDWORD ReadPlayInfo(const char *szFileName);
		int UpdateTimeAct(const char* szFileName, const char* szFileNamebk);//更新时间表
		void InitFlagData(void);  //用于更新时间表后初始化播放标志位
		
	public:
		GetNextNameClass(){ init();}
		~GetNextNameClass(){}
};

#endif

