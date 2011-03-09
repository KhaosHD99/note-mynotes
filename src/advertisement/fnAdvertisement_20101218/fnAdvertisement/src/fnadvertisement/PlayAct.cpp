/*
* Copyright 广州泛网视讯有限公司
* All rights reserved.
* 
* 文件名称：Play_act.cpp
* 
* 摘    要：对时间表的读取与分析
* 
* 作    者：吴耀泉
*
* 修改者:   徐镇杰
* 
* 最后修改日期：2010年11月19日
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "PlayAct.hpp"
#include "XMLInterface.h"

/****************************************************************************************
					全局变量
*****************************************************************************************/
//下面的静态变量用于保存相应播放队列的当前播放位置
//设置为-1的原因是第一次取文件名时，其不存在取下一个文件的概念，
//但在函数里面，所以第一次的时候来个虚拟取下一个
static int area_1_normal_pos = -1;
static int area_1_offhook_pos = -1;
static int area_1_ring_pos = -1;
static int area_1_novideoconn_pos = -1;
static int area_1_videoconn_pos = -1;

static int area_2_normal_pos = -1;
static int area_2_offhook_pos = -1;
static int area_2_ring_pos = -1;
static int area_2_novideoconn_pos = -1;
static int area_2_videoconn_pos= -1;

static int area_3_ring_pos = -1;
static int area_3_offhook_pos = -1;
static int area_3_novideoconn_pos = -1;
static int area_3_normal_pos = -1;
static int area_3_videoconn_pos = -1;

static int area_4_ring_pos = -1;
static int area_4_offhook_pos = -1;
static int area_4_novideoconn_pos = -1;
static int area_4_normal_pos = -1;
static int area_4_videoconn_pos = -1;

static int area_5_ring_pos = -1;
static int area_5_offhook_pos = -1;
static int area_5_novideoconn_pos = -1;
static int area_5_normal_pos = -1;
static int area_5_videoconn_pos = -1;

/*--------------------------------------------------------------------------------------
							改版简要修改注意---写给修改者

		时间函数部分已经变更  OK
		所有部分，包括与外部接口用类封装
		当读取时间表失败时，要防止系统每次取时间表都读失败的问题，这将造成系统的瘫痪
		应该与调用模块沟通如何去避免这个问题
--------------------------------------------------------------------------------------*/
/****************************************************************************************
								节目信息获取显示部分具体代码
****************************************************************************************/
//#define VER101XXX

GetNextNameClass *GetNextNameClass::instance = NULL;
GetNextNameClass* GetNextNameClass::get_instance(void)
{
	if (instance == NULL)
		instance = new GetNextNameClass();
	return instance;
}

/****************************************************************************************
			更新成功则返回0，否则返回其他参数
****************************************************************************************/
int  GetNextNameClass::update_time_act(const char* szFileName, const char* szFileNamebk)
{	
	int fFxml = 0;
	//TERMINAL_ACT_INFO *curActInfo;
	
	fFxml = read_play_info(szFileName);
	
	//curActInfo = GetNextName(PLAY_REGION_MAIN, FN_RING_STATE);
	//printf("curActInfo: %d \n", curActInfo->sActInfo.dwActID);
	
	if(fFxml == 0)
	{
		fFxml = read_play_info(szFileNamebk);
		
		if(fFxml==0)
		{
			//1.0.0.XXXX过度到1.0.1.XXXX时 因避免没有新的节目表，临时读取C盘下的XML文件
			/*#ifdef VER101XXX
				strcpy(szFileName, "/c/appfile/800000000.xml");
				strcpy(szFileNamebk, "/c/appfile/800000001.xml");
				
				fFxml = ReadPlayInfo(szFileName);
				if(fFxml==0)
				{
					fFxml = ReadPlayInfo(szFileNamebk);
					if(fFxml==0)
					{
						return -1;
					}
				}
				return 0;
			#endif*/
			return -1;
		}
	}
	
	return 0;
}

/****************************************************************************************
			     用于更新时间表后初始化播放标志位
****************************************************************************************/
void GetNextNameClass::InitFlagData()
{	
	area_1_normal_pos = -1;
	area_1_offhook_pos = -1;
	area_1_ring_pos = -1;
	area_1_novideoconn_pos = -1;
	area_1_videoconn_pos = -1;

	area_2_normal_pos = -1;
	area_2_offhook_pos = -1;
	area_2_ring_pos = -1;
	area_2_novideoconn_pos = -1;
	area_2_videoconn_pos = -1;

	area_3_normal_pos = -1;
	area_3_offhook_pos = -1;
	area_3_ring_pos = -1;
	area_3_novideoconn_pos = -1;
	area_3_videoconn_pos = -1;

	area_4_normal_pos = -1;
	area_4_offhook_pos = -1;
	area_4_ring_pos = -1;
	area_4_novideoconn_pos = -1;
	area_4_videoconn_pos = -1;

	area_5_normal_pos = -1;
	area_5_offhook_pos = -1;
	area_5_ring_pos = -1;
	area_5_novideoconn_pos = -1;
	area_5_videoconn_pos = -1;
}

/******************************************************************************************
     获取下一个播放文件信息，需要的参数为窗口类型和播放模式
*******************************************************************************************/
TERMINAL_ACT_INFO* GetNextNameClass::get_next_name(int area_type,int state)
{	
	switch (area_type)
	{
		// Area 1
		case PLAY_AREA_1:
		switch (state)
		{
			case CCST::ON_HOOK:
				 return get_slot_time(m_pStateActList[PLAY_AREA_1][state], m_pActResource, area_1_normal_pos);
			case CCST::DIALING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_1][state], m_pActResource, area_1_offhook_pos);
			case CCST::RINGING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_1][state], m_pActResource, area_1_ring_pos);
			case CCST::NOVIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_1][state], m_pActResource, area_1_novideoconn_pos);
			case CCST::VIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_1][state], m_pActResource, area_1_videoconn_pos);
			
			default:
				showWarning("Main window play mode args error\n");
			return NULL;
		}
		
		//Area 2
		case PLAY_AREA_2:
		switch (state)
		{
			case CCST::ON_HOOK:
				return get_slot_time(m_pStateActList[PLAY_AREA_2][state], m_pActResource, area_2_normal_pos);
			case CCST::DIALING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_2][state], m_pActResource, area_2_offhook_pos);
			case CCST::RINGING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_2][state], m_pActResource, area_2_ring_pos);
			case CCST::NOVIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_2][state], m_pActResource, area_2_novideoconn_pos);
			case CCST::VIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_2][state], m_pActResource, area_2_videoconn_pos );
			
			default:
				showWarning("Main window play mode args error\n");
			return NULL;
		}
		
        //Low Left Area
		case PLAY_AREA_3:
		switch (state)
		{
			case CCST::ON_HOOK:
				 return get_slot_time(m_pStateActList[PLAY_AREA_3][state], m_pActResource, area_3_normal_pos);
			case CCST::DIALING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_3][state], m_pActResource, area_3_offhook_pos);
			case CCST::RINGING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_3][state], m_pActResource, area_3_ring_pos);
			case CCST::NOVIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_3][state], m_pActResource, area_3_novideoconn_pos);
			case CCST::VIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_3][state], m_pActResource, area_3_videoconn_pos);
			
			default:
				showWarning("Main window play mode args error\n");
			return NULL;
		}
		
        //Roll Text  Area
		case PLAY_AREA_4:
		switch (state)
		{			
			case CCST::ON_HOOK:
				 return get_slot_time(m_pStateActList[PLAY_AREA_4][state], m_pActResource, area_4_normal_pos);
			case CCST::DIALING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_4][state], m_pActResource, area_4_offhook_pos);
			case CCST::RINGING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_4][state], m_pActResource, area_4_ring_pos);
			case CCST::NOVIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_4][state], m_pActResource, area_4_novideoconn_pos);
			case CCST::VIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_4][state], m_pActResource, area_4_videoconn_pos);
			
			default:
				showWarning("Main window play mode args error\n");
			return NULL;
		}
		
        //Area 5
		case PLAY_AREA_5 :
		switch (state)
		{			
			case CCST::ON_HOOK:
				 return get_slot_time(m_pStateActList[PLAY_AREA_5][state], m_pActResource, area_5_normal_pos);
			case CCST::DIALING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_5][state], m_pActResource, area_5_offhook_pos);
			case CCST::RINGING:
				 return get_slot_time(m_pStateActList[PLAY_AREA_5][state], m_pActResource, area_5_ring_pos);
   		    case CCST::NOVIDEO_CONN:
			     return get_slot_time(m_pStateActList[PLAY_AREA_5][state], m_pActResource, area_5_novideoconn_pos);
			case CCST::VIDEO_CONN:
				 return get_slot_time(m_pStateActList[PLAY_AREA_5][state], m_pActResource, area_5_videoconn_pos);
					 
			default:
			showWarning("Main window play mode args error\n");
			return NULL;
		}
		
		default:
			showWarning("window args error [%d]\n",area_type);
			return NULL;
	}
}

/*************************************************************************************************************
    返回当前播放文件所在的时间段，  要求播放序列必须为主窗口的普通播放方案
**************************************************************************************************************/
TERMINAL_ACT_INFO* GetNextNameClass::get_slot_time(const FN_STATE_ACT_LIST* act_list,
											       TERMINAL_ACT_LIST* act_res,
											       int &current_pos)
{
	FNDWORD i = 0;
	TIME_SECTION_INFO* pNextPos = NULL;
	TIME_SECTION_INFO* pPrvPos = NULL;
	
    /*get time code have to test */
	time_t timep;
	struct tm *t;
	
	time(&timep);
	t = gmtime(&timep);
	if (t == NULL)
	{
		showWarning("Get time error\n");
		return NULL;
	}
	
	FNDWORD systime = (FNDWORD)(3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec);
	
	int nPLen = 0;
	int POffSet = 0;
 	if (act_list == NULL)
	{
		showWarning("Act list is empty\n");
		return NULL;
	}
	if (act_res == NULL)
	{
		showWarning("Resource list is empty\n");
		return NULL;
	}
	
	/* Time section loop */
	for(i = 0; i < act_list->dwSectionCnt; i++)
	{   
		pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList) + POffSet);
		nPLen = pNextPos->dwActCnt * 4 + 8;
		POffSet += nPLen;
		
		//时段判断
		if((systime < pNextPos->dwEndTime) && (i == 0))
		{	
			//假如已经进入播放时间段临界区，则切换
			if((int)(pNextPos->dwEndTime - systime) <= EXPIRE_TIME)
			{	
				pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList) + POffSet);
				current_pos = -1;
				current_pos = current_pos + 1;
				
				//Loop Play
				if(current_pos >= (int)pNextPos->dwActCnt)
				{
					current_pos = 0;
				}
				
				FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos * 4);
				
				for(int j = 0;j < (int)act_res->dwActNum; j++)
				{   
					if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
					{
						act_endtime = pNextPos->dwEndTime;
						return &act_res->ActList[j];
					}
				}
				showWarning("Resource list not exit program %d \n",*nAct_Id );
				
				return NULL;
			}/* End if((int)(pNextPos->dwEndTime - systime) <= EXPIRE_TIME) */
			else
			{
				current_pos = current_pos + 1;
				
				//Loop Play
				if(current_pos >= (int)pNextPos->dwActCnt)
				{
					current_pos = 0;
				}

				FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos * 4);
				
				for(int j = 0;j < (int)act_res->dwActNum;j++)
				{
				   // showDebug("act_res->ActList[%d].sActInfo.dwActID: %d, nAct_Id: %d\n",
                   //           j,
                   //           act_res->ActList[j].sActInfo.dwActID,
                   //           *nAct_Id);

					if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
					{	
						act_endtime = pNextPos->dwEndTime;
						return &act_res->ActList[j];
					}
				}
				showWarning ("Resource list not exit program %d \n", *nAct_Id);
				
				return NULL;
			}
		}/*  End if((systime < pNextPos->dwEndTime) && (i == 0)) */
		else if( (!pPrvPos || pPrvPos->dwEndTime <= systime) && ((pNextPos->dwEndTime >= systime)))
		{					            							    //              i-1 currenttime i  
			if((int)(pNextPos->dwEndTime - systime) <= EXPIRE_TIME)	    // |_____________|______________|
			{
				if((int)pNextPos->dwEndTime == 24 * 3600)
				{
					//k = 0;
					POffSet = 0;
					pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList)+POffSet);
					current_pos = -1;
					current_pos = current_pos + 1;
					
					//Loop Plays
					if(current_pos >= (int)pNextPos->dwActCnt)
					{
						current_pos = 0;
					}

					FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos * 4);
					
					for(int j = 0;j < (int)act_res->dwActNum;j++)
					{
						if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
						{
							act_endtime = pNextPos->dwEndTime;
							return &act_res->ActList[j];
						}
					}
					showWarning("Resource list not exit program %d \n",*nAct_Id );
					
					return NULL;
				}/* End if((int)pNextPos->dwEndTime == 24 * 3600) */
				else
				{
					//k=i+1;
					pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList) + POffSet);
					current_pos = -1;
					current_pos = current_pos + 1;
					
					//Loop Play
					if(current_pos >= (int)pNextPos->dwActCnt)
					{
						current_pos = 0;
					}

					FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos * 4);

					for(int j = 0;j < (int)act_res->dwActNum;j++)
					{
						if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
						{
							act_endtime = pNextPos->dwEndTime;
							return &act_res->ActList[j];
						}
					}
					showWarning("Resource list not exit program %d \n",*nAct_Id );
					
					return NULL;
				}
			}/* End if((int)(pNextPos->dwEndTime - systime) <= EXPIRE_TIME) */
			else
			{
				current_pos = current_pos + 1;
				
				//Loop Play
				if(current_pos >= (int)pNextPos->dwActCnt)
				{
					current_pos = 0;
				}
				
				FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos * 4);
				
				for(int j = 0;j < (int)act_res->dwActNum;j++)
				{
					if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
					{
						act_endtime = pNextPos->dwEndTime;
						return &act_res->ActList[j];
					}
				}
				showWarning("Resource list not exit program %d \n",*nAct_Id );
				
				return NULL;
			}
		}/* End if( (!pPrvPos || pPrvPos->dwEndTime <= systime) && ((pNextPos->dwEndTime >= systime))) */
		pPrvPos = pNextPos;
	}
	/* End Time section loop */

	showDebug("i: %d\n", i);
	showWarning("Time section error!!!\n");
	
	return NULL;
}

/**********************************************************************************
		     根据传入的参数获取相应播放队列的相关信息
***********************************************************************************/
TERMINAL_ACT_INFO* GetNextNameClass::GetName(const FN_STATE_ACT_LIST* period_info,
										        TERMINAL_ACT_LIST* act_list,
										        int &current_pos,
										        int time_pos)
{
	FNDWORD k = 0;
	
	if (period_info == NULL)
	{
		showWarning("时间表为空，请检查时间表\n");
		return NULL;
	}
	
	if (act_list == NULL)
	{
		showWarning("节目表为空，请检查节目表\n");
		return NULL;
	}
	
	if(period_info->dwSectionCnt == 0)
	{
		showWarning("节目表时段数量为0\n");
		return NULL;
	}
	
	if(time_pos >= (int)period_info->dwSectionCnt && time_pos < 0)
	{
		showWarning("当前时间在时间表时段内越界 \n");
		return NULL;
	}
	
	current_pos = current_pos + 1;
	
	//循环播放
	if(current_pos >= (int)period_info->SectionList[time_pos].dwActCnt)
	{
		current_pos = 0;
	}
	showDebug("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-40\n");
		
	//获取到一个播放的节目号，还要通过这个号码在节目表中找到具体的节目
	k = period_info->SectionList[time_pos].dwActList[current_pos];

	for(FNDWORD i = 0;i < act_list->dwActNum; i++)
	{
		if(act_list->ActList[i].sActInfo.dwActID == k)
		{
			act_endtime = period_info->SectionList[time_pos].dwEndTime;
			return &act_list->ActList[i];
		}
	}
	
	showWarning("获取节目%u失败，当前时段为%u\n", k, time_pos);
	act_endtime = 0;
	
	return NULL;
}

#define MAX_SCHEME_BUF_LEN 	512 * 1024
char g_PlaySchemeBuf[MAX_SCHEME_BUF_LEN];
	
/**********************************************************************************
                                                Read Act Resource And Timelist 
***********************************************************************************/
FNDWORD GetNextNameClass::read_play_info(const char *szFileName)
{	
	int i = 0, j = 0, k = 0, m = 0, n = 0;
	int nOffset = 0, nDataLen = 0, nSectionLen = 0;
	int nAreaPos = 0, nStatePos = 0;
	memset(m_pStateActList, 0, sizeof(m_pStateActList));
	memset(g_PlaySchemeBuf, 0, sizeof(g_PlaySchemeBuf));
	TIME_SECTION_INFO *pSectionInfo = NULL;
	
	xmlChar *pAttribute = NULL;
	xmlNodePtr pProgramList = NULL;
	xmlNodePtr pProgramIDList = NULL;
	xmlNodePtr pProgramInfo = NULL;
	xmlNodePtr pAreaInfo = NULL;
	xmlNodePtr pStateList = NULL;
	xmlNodePtr pStateInfo = NULL;
	xmlNodePtr pTimePosList = NULL;
	xmlNodePtr pTimePosInfo = NULL;
	xmlNodePtr pRootElement = NULL;
	int nNum = 0, nProgramNum = 0;
	int nSuccess = 0;
    
	m_pActResource = (TERMINAL_ACT_LIST *)g_PlaySchemeBuf;
	
	//create a xml doc
	//int nRet = xml_load_file((char*)szFileName);
	
	//get root element
	pRootElement = xml_read_root_node((char*)szFileName);
	if(NULL == pRootElement)
	{
		showWarning("load timeList file fail\r\n");
		goto ERETURN;
	}
	
	if(!pRootElement)
	{
		showWarning("read timeList root node fail\r\n");
		goto ERETURN;
	}
		
	//get program list
	pProgramList = xml_read_child_node(pRootElement);
	if(!pProgramList)
	{
		showWarning("get pProgramList fail\r\n");
		goto ERETURN;
	}
	
	pAttribute = xml_read_attribute_value(pProgramList, BAD_CAST "NUM");
	if(!pAttribute)
	{
		showWarning("get pProgramList count fail\r\n");
		goto ERETURN;
	}
	
	//nNum = atoi(pAttribute);
	sscanf((const char *)pAttribute, "%d", &nNum);
	if(nNum <= 0 || nNum > FN_MAX_ACT_NUM)
	{
		showWarning("get pProgramList count fail %d\r\n", nNum);
		goto ERETURN;
	}

	/*  
	      ProgramList detail item  
	*/
	pProgramInfo = xml_read_child_node(pProgramList);
	m_pActResource->dwActNum = 0;
	for( i = 0; i < nNum; i++ )
	{
	    //ACTID
	    if(!pProgramInfo)
	    {
	    	showWarning("pProgramList count not enough %d %d\r\n", nNum, i);
	    	goto ERETURN;
	    }
	    pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "ACTID");
        if(!pAttribute || !pAttribute[0])
	    {
	    	showWarning("pProgram %d no ID\r\n", i + 1);
	    	goto ERETURN;		    
	    }
	    sscanf((const char *)pAttribute, "%u", &m_pActResource->ActList[i].sActInfo.dwActID);
		//showDebug("ACTID: %s\n", pAttribute);
		
		//MAINFILEID
	    pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "MAINFILEID");
		if(!pAttribute || !pAttribute[0])
	    {
	    	showWarning("pProgram %d no ID\r\n", i + 1);
	    	goto ERETURN;
	    }
	  	sscanf((const char *)pAttribute, "%u", &m_pActResource->ActList[i].sActInfo.dwMainFileID);
		if((pAttribute[0] - '0') != FN_FILE_TYPE_VIDEO && (pAttribute[0] - '0') != FN_FILE_TYPE_IMAGE
			&& (int)m_pActResource->ActList[i].sActInfo.dwMainFileID != -1)
	    {
	    	showWarning("pProgram %d main ID %c %u error\r\n", 
	  		i + 1,
	  		pAttribute[0],
	  		m_pActResource->ActList[i].sActInfo.dwMainFileID);
	    	goto ERETURN;
	    }
		
		//MUSICFILEID
		pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "MUSICFILEID");
		if(pAttribute)
		{
			sscanf((const char *)pAttribute, "%09u", &m_pActResource->ActList[i].sActInfo.dwMusicFileID);
			if(pAttribute[0] != '0' && (pAttribute[0] - '0') != FN_FILE_TYPE_AUDIO)
			{
				showWarning("pProgram %d no music ID %c %u error\r\n", 
				i + 1, 
				pAttribute[0],
				m_pActResource->ActList[i].sActInfo.dwMusicFileID);
	    	    goto ERETURN;
	        }	    	
        }

		//ADDIMAGEFILEID
	    pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "ADDIMAGEFILEID");
		
	    if(pAttribute)
		{
			sscanf((const char *)pAttribute, "%09u", &m_pActResource->ActList[i].sActInfo.dwAddImageFileID);
			if(pAttribute[0] != '0' && (pAttribute[0] - '0') != FN_FILE_TYPE_IMAGE)
			{
				showWarning("pProgram %d img ID %c %u error\r\n", 
							i + 1, 
							pAttribute[0],
							m_pActResource->ActList[i].sActInfo.dwAddImageFileID);
				goto ERETURN;
			}
		}

		//PLAYTIME
        pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "PLAYTIME");
		if(!pAttribute)
		{
			showWarning("pProgram %d no playtime\r\n", i + 1);
			goto ERETURN;
		}
        sscanf((const char *)pAttribute, "%09u", &m_pActResource->ActList[i].sActInfo.dwPlayTime);
		
	    if(m_pActResource->ActList[i].sActInfo.dwPlayTime > (24 * 60 * 60))
	    {
			showWarning("pProgram %d playtime %u error\r\n", 
						i + 1, 
						m_pActResource->ActList[i].sActInfo.dwPlayTime);
	    	goto ERETURN;
	    }
		
        //PHONECODE
		pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "PHONECODE");
		if(pAttribute)
		{
			strncpy(m_pActResource->ActList[i].sActInfo.cPhoneCode, (const char *)pAttribute, FN_PHONE_CODE_LEN);
			m_pActResource->ActList[i].sActInfo.cPhoneCode[FN_PHONE_CODE_LEN - 1] = 0;
		}
		
        //URL
		pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "URL");
		if(pAttribute)
		{
			strncpy(m_pActResource->ActList[i].sActInfo.cURL, (const char *)pAttribute, FN_URL_LEN);
			m_pActResource->ActList[i].sActInfo.cURL[FN_URL_LEN - 1] = 0;
	    }
		
		pProgramInfo = xml_read_brother_node(pProgramInfo);
	}  
    m_pActResource->dwActNum = nNum;//填写节目资源量  
   
	//定位主区域第一个状态
	//节目资源表所占存储空间
	nOffset = nNum * sizeof(TERMINAL_ACT_INFO) + 4;
	m_pStateActList[0][0] = (FN_STATE_ACT_LIST*)(g_PlaySchemeBuf + nOffset);
	pAreaInfo = xml_read_brother_node(pProgramList);
	
	/* Area Loop */
	for( i = 0; i < 5; i++ )
	{
		if(!pAreaInfo)
		{
			showWarning("area count define not enough %d\r\n", i);
			goto ERETURN;
		}  
		
		nAreaPos = 0;	
		pAttribute = xml_read_attribute_value(pAreaInfo, BAD_CAST "ID");
		if(pAttribute)
		{
			sscanf((const char *)pAttribute, "%d", &nAreaPos);
		}
		nAreaPos--;
		if(nAreaPos < 0 || nAreaPos >= 5)
	    {
		  	showWarning("area id define error %d\r\n", nAreaPos + 1);
		  	goto ERETURN;
	    }
		
		//State List
		pStateList = xml_read_child_node(pAreaInfo);
		if(!pStateList)
		{
			showWarning("区域 %d 无状态列表定义错误\r\n", nAreaPos + 1);
			goto ERETURN;
		}  		    
		pStateInfo = xml_read_child_node(pStateList);
		
		/* State Loop */
		for( j = 0; j < FN_STATE_NUM; j++ )
		{	
			nDataLen = 0;
			nSectionLen = 0;
			if(!pStateInfo)
			{
			    showDebug("not enough state define\n");
				if(j == 0)
				{
					showWarning("区域 %d 未定义状态轴\r\n", nAreaPos + 1);
					goto ERETURN;
				}
				break;
			}
			nStatePos = -1; 	
			pAttribute = xml_read_attribute_value(pStateInfo, BAD_CAST "ID");
			if(pAttribute)
			{
			    //当前区域定位
				sscanf((const char *)pAttribute, "%d", &nStatePos);
			}
			
			//最多FN_STATE_NUM个状态
			if(nStatePos < 0 || nStatePos >= FN_STATE_NUM)			
			{
				showWarning("状态ID %d 定义错误\r\n", nStatePos);
				goto ERETURN;
			}
			m_pStateActList[nAreaPos][nStatePos] = (FN_STATE_ACT_LIST*)(g_PlaySchemeBuf + nOffset);	
			
			//Time Pos List
			pTimePosList = xml_read_child_node(pStateInfo);
			if(!pTimePosList)
			{
				showWarning("%d %d 无时段列表错误\r\n", nAreaPos, j);
				goto ERETURN;
			}
			
			nNum = 0;
			n++;
			pTimePosInfo = xml_read_child_node(pTimePosList);

			/* Time Section Loop */
			for( k = 0; k < TIME_SECTION_NUM; k++)
			{
				if(!pTimePosInfo)
				{
					break;
				}
				
				//偏移定位
				pSectionInfo = (TIME_SECTION_INFO*)
							       ((char*)(m_pStateActList[nAreaPos][nStatePos]->SectionList) + nSectionLen);
				
				pAttribute = xml_read_attribute_value(pTimePosInfo, BAD_CAST "ENDTIME");
				if(!pAttribute || !pAttribute[0])
				{
					showWarning("no time over define\r\n");
					goto ERETURN;
				}
				sscanf((const char *)pAttribute, "%u", &pSectionInfo->dwEndTime);
				//showDebug("m_pStateActList[%d][%d]->SectionList->dwEndTime: %d\n",
				//	      i,
				//	      j,
				//	      m_pStateActList[nAreaPos][nStatePos]->SectionList->dwEndTime);
				
				//Program ID List
				pProgramIDList = xml_read_child_node(pTimePosInfo);
				if(!pProgramIDList)
				{
					goto ERETURN;
				}
				m = 0;
				pProgramInfo = xml_read_child_node(pProgramIDList);
				
				/* Section Act Loop */
				while( m < SECTION_ACT_NUM)
				{
					if(!pProgramInfo)
				    {
				    	break;
				    }
					
				    pAttribute = xml_read_attribute_value(pProgramInfo, BAD_CAST "ACTID");
				    if(!pAttribute || !pAttribute[0])
				    {
				    	showWarning("no act ID define\r\n");
				    	goto ERETURN;
				    }
				    sscanf((const char *)pAttribute, "%u", &pSectionInfo->dwActList[m]);
					//showWarning("节目号%d\r\n",pSectionInfo->dwActList[m]);
					m++;
					pProgramInfo = xml_read_brother_node(pProgramInfo);					
					//TSK_sleep(2);
					//TSK_yield();
				}
				/* End Section Act Loop */
				
				nProgramNum = m;
				//最多SECTION_ACT_NUM个数量
				if(nProgramNum <= 0 || nProgramNum > SECTION_ACT_NUM)
				{
					showWarning("time interval act count %d error\r\n", nProgramNum);
					goto ERETURN;
				}
				
				//时段内节目数量
				pSectionInfo->dwActCnt = nProgramNum;
				//showDebug("ProgramNum in %d section: %d\n",
				//		  k,
				//	      m_pStateActList[nAreaPos][nStatePos]->SectionList->dwActCnt);
				nDataLen = nProgramNum * 4 + 8;
				nSectionLen += nDataLen;
				pTimePosInfo = xml_read_brother_node(pTimePosInfo);
			}
			/* End Time Section Loop */
			
			nNum = k;
			if(nNum <= 0)
			{
			    showWarning("time interval count %d error\r\n", nNum);
			    goto ERETURN;
			}
			
			//时段数量  
			m_pStateActList[nAreaPos][nStatePos]->dwSectionCnt = nNum; 
			//showDebug("Time section count in %d state: %d\n",
			//	      j,
			//	      m_pStateActList[nAreaPos][nStatePos]->dwSectionCnt);
			nOffset += nSectionLen + 4;
			pStateInfo = xml_read_brother_node(pStateInfo);
		}
		/* End State Loop */
				
		pAreaInfo = xml_read_brother_node(pAreaInfo);
	}  
	/* End Area Loop */

	showDebug("timeList amount: %d\r\n", n);
	nSuccess = 1;
	//free_resource();

ERETURN:
	if(pRootElement)
	{
	    free_xml_parser();
  		//XMLReleaseResource();
  	}
	if(!nSuccess) 
	{
		showWarning("timeList file is invalid\r\n");
	}
	
	return nSuccess;
}

