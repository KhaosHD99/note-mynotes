#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "play_act.hpp"
#include "XMLInterface.h"


/****************************************************************************************
					全局变量
*****************************************************************************************/
//下面的静态变量用于保存相应播放队列的当前播放位置
//设置为-1的原因是第一次取文件名时，其不存在取下一个文件的概念，
//但在函数里面，所以第一次的时候来个虚拟取下一个
static int main_ring_pos = -1;
static int main_offhook_pos = -1;
static int main_novideoconn_pos = -1;
static int main_normal_pos = -1;
static int main_app_pos = -1;
static int main_onhook_pos = -1;//新加挂机状态参数
static int main_videoapp_pos = -1;   //新版增加状态

static int up_ring_pos = -1;
static int up_offhook_pos = -1;
static int up_novideoconn_pos = -1;
static int up_normal_pos = -1;
static int up_app_pos = -1;
static int up_onhook_pos = -1;
static int up_videoapp_pos = -1;

static int down_ring_pos = -1;
static int down_offhook_pos = -1;
static int down_novideoconn_pos = -1;
static int down_normal_pos = -1;
static int down_app_pos = -1;
static int down_onhook_pos = -1;
static int down_videoapp_pos = -1;

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
GetNextNameClass* GetNextNameClass::getInstance(void)
{
	if (instance == NULL)
		instance = new GetNextNameClass();
	return instance;
}


int  GetNextNameClass::UpdateTimeAct(const char* szFileName, const char* szFileNamebk)//更新成功则返回0，否则返回其他参数
{
	int fFxml = 0;
	
	fFxml = ReadPlayInfo(szFileName);
	
	if(fFxml==0)
	{
		fFxml = ReadPlayInfo(szFileNamebk);
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


void GetNextNameClass::InitFlagData()
{
	main_ring_pos = -1;
	main_offhook_pos = -1;
	main_novideoconn_pos = -1;
	main_normal_pos = -1;
	main_app_pos = -1;
	main_onhook_pos = -1;//新加挂机状态参数
	main_videoapp_pos = -1;   //新版增加状态

	up_ring_pos = -1;
	up_offhook_pos = -1;
	up_novideoconn_pos = -1;
	up_normal_pos = -1;
	up_app_pos = -1;
	up_onhook_pos = -1;
	up_videoapp_pos = -1;

	down_ring_pos = -1;
	down_offhook_pos = -1;
	down_novideoconn_pos = -1;
	down_normal_pos = -1;
	down_app_pos = -1;
	down_onhook_pos = -1;
	down_videoapp_pos = -1;
}


TERMINAL_ACT_INFO* GetNextNameClass::GetNextName(int window_type,int play_mode)
{
	switch (window_type)
	{
	
	case PLAY_REGION_MAIN ://主窗口播放区域
		switch (play_mode)
		{
			case FN_RING_STATE:
				 return GetSlotTime(m_pStateActList[0][FN_RING_STATE], m_pActResource, main_ring_pos);
			case FN_OFFHOOK_STATE:
				 return GetSlotTime(m_pStateActList[0][FN_OFFHOOK_STATE], m_pActResource, main_offhook_pos);
			case FN_NOVIDEOCONN_STATE:
				 return GetSlotTime(m_pStateActList[0][FN_NOVIDEOCONN_STATE], m_pActResource, main_novideoconn_pos);
			case FN_NORMAL_STATE:
				 return GetSlotTime(m_pStateActList[0][FN_NORMAL_STATE], m_pActResource, main_normal_pos);
			case FN_APP_STATE:
				 return GetSlotTime(m_pStateActList[0][FN_APP_STATE], m_pActResource, main_app_pos);
			case FN_ONHOOK_STATE:
				 return GetSlotTime(m_pStateActList[0][FN_ONHOOK_STATE], m_pActResource, main_onhook_pos);
			//case FN_VIDEO_APP_STATE:
				 //return GetSlotTime(m_pStateActList[0][FN_VIDEO_APP_STATE], m_pActResource, main_videoapp_pos);
			default:
			showWarning("主窗口播放模式参数错误\n");
			return NULL;
		}

	case PLAY_REGION_1 ://右上窗口播放区域
		switch (play_mode)
		{
			case FN_RING_STATE:
				 return GetSlotTime(m_pStateActList[1][FN_RING_STATE], m_pActResource, up_ring_pos);
			case FN_OFFHOOK_STATE:
				 return GetSlotTime(m_pStateActList[1][FN_OFFHOOK_STATE], m_pActResource, up_offhook_pos);
			case FN_NOVIDEOCONN_STATE:
				 return GetSlotTime(m_pStateActList[1][FN_NOVIDEOCONN_STATE], m_pActResource, up_novideoconn_pos);
			case FN_NORMAL_STATE:
				 return GetSlotTime(m_pStateActList[1][FN_NORMAL_STATE], m_pActResource, up_normal_pos);
			case FN_APP_STATE:
				 return GetSlotTime(m_pStateActList[1][FN_APP_STATE], m_pActResource, up_app_pos);
			case FN_ONHOOK_STATE:
				 return GetSlotTime(m_pStateActList[1][FN_ONHOOK_STATE], m_pActResource, up_onhook_pos);
			//case FN_VIDEO_APP_STATE:
				 //return GetSlotTime(m_pStateActList[1][FN_VIDEO_APP_STATE], m_pActResource, up_videoapp_pos);
			default:
			showWarning("主窗口播放模式参数错误\n");
			return NULL;
		}
	case PLAY_REGION_2 ://右下窗口播放区域
		switch (play_mode)
		{
			case FN_RING_STATE:
				 return GetSlotTime(m_pStateActList[2][FN_RING_STATE], m_pActResource, down_ring_pos);
			case FN_OFFHOOK_STATE:
				 return GetSlotTime(m_pStateActList[2][FN_OFFHOOK_STATE], m_pActResource, down_offhook_pos);
			case FN_NOVIDEOCONN_STATE:
				 return GetSlotTime(m_pStateActList[2][FN_NOVIDEOCONN_STATE], m_pActResource, down_novideoconn_pos);
			case FN_NORMAL_STATE:
				 return GetSlotTime(m_pStateActList[2][FN_NORMAL_STATE], m_pActResource, down_normal_pos);
			case FN_APP_STATE:
				return GetSlotTime(m_pStateActList[2][FN_APP_STATE], m_pActResource, down_app_pos);
			case FN_ONHOOK_STATE:
				 return GetSlotTime(m_pStateActList[2][FN_ONHOOK_STATE], m_pActResource, down_onhook_pos);
			//case FN_VIDEO_APP_STATE:
				 //return GetSlotTime(m_pStateActList[2][FN_VIDEO_APP_STATE], m_pActResource, down_videoapp_pos);			
		
			default:
			showWarning("主窗口播放模式参数错误\n");
			return NULL;
		}

	default:
		showWarning("窗口参数错误 [%d]\n",window_type);
		return NULL;
	}
}


TERMINAL_ACT_INFO* GetNextNameClass::GetSlotTime(const FN_STATE_ACT_LIST* act_list,
											TERMINAL_ACT_LIST* act_res, int &current_pos)  
{
	FNDWORD i = 0;
	TIME_SECTION_INFO* pNextPos = NULL;
	TIME_SECTION_INFO* pPrvPos = NULL;	
/*------------------------------------------------------------------------------*/
/*-------------------------get time code have to test---------------------------*/
	time_t timep;
	struct tm *t;
	
	time(&timep);
	t = gmtime(&timep);
	if (t == NULL)
	{
		showWarning("获取时间错误\n");
		return NULL;
	}
	//showDebug("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-[hour = %d]\n", t->tm_hour);
	//showDebug("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-[min = %d]\n", t->tm_min);
	//showDebug("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-[sec = %d]\n", t->tm_sec);
	
	FNDWORD systime = (FNDWORD)(3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec);
/*------------------------------------------------------------------------------*/	
	// showDebug("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-24\n");

	int nPLen = 0;
	int POffSet = 0;
 	if (act_list == NULL)
	{
		showWarning("节目表为空，请检查节目表\n");
		return NULL;
	}
	 if (act_res == NULL)
	{
		showWarning("节目资源表为空，请检查节目表\n");
		return NULL;
	}
	for(i=0;i<act_list->dwSectionCnt;i++)//时段循环查询时间
	{	
		pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList)+POffSet);
		nPLen = pNextPos->dwActCnt*4 + 8;
		POffSet += nPLen;
			
		if((systime < pNextPos->dwEndTime) && (i==0))//时段判断
		{
		  if((int)(pNextPos->dwEndTime - systime) <= EXPIRE_TIME) //假如已经进入播放时间段临界区，则切换
		  {
			 pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList)+POffSet);
			 current_pos = -1;
			 current_pos = current_pos + 1;
			 
			 if(current_pos >= (int)pNextPos->dwActCnt)//循环播放
			{
				current_pos=0;
			}

			FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos*4);
			
			for(int j = 0;j < (int)act_res->dwActNum;j++)
			{

				if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
				{
					act_endtime = pNextPos->dwEndTime;
					return &act_res->ActList[j];

				}

			}
			showWarning("节目列表中不存在%d节目\n",*nAct_Id );
			return NULL;
		  }
		  else
		  {
			 current_pos = current_pos + 1;
			 if(current_pos >= (int)pNextPos->dwActCnt)//循环播放
			{
				current_pos=0;
			}

			FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos*4);
			
			for(int j = 0;j < (int)act_res->dwActNum;j++)
			{

				if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
				{
					act_endtime = pNextPos->dwEndTime;
					return &act_res->ActList[j];

				}

			}
			showWarning("节目列表中不存在%d节目\n",*nAct_Id );
			return NULL;
		  }
		}
		else if( (!pPrvPos || pPrvPos->dwEndTime <= systime) && ((pNextPos->dwEndTime >= systime)))		    
		 {															//              i-1 currenttime i  
			if((int)(pNextPos->dwEndTime - systime) <= EXPIRE_TIME)	// |_____________|______________|
			{
				if((int)pNextPos->dwEndTime == 24*3600)
				{
					//k = 0;
					POffSet = 0;
					pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList)+POffSet);
					current_pos = -1;
					current_pos = current_pos + 1;
					if(current_pos >= (int)pNextPos->dwActCnt)//循环播放
					{
						current_pos=0;
					}

					FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos*4);
					
					for(int j = 0;j < (int)act_res->dwActNum;j++)
					{

						if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
						{
							act_endtime = pNextPos->dwEndTime;
							return &act_res->ActList[j];

						}

					}
					showWarning("节目列表中不存在%d节目\n",*nAct_Id );
					return NULL;
				}
				else
				{
					//k=i+1;
					 pNextPos = (TIME_SECTION_INFO*)((char*)(act_list->SectionList)+POffSet);
					 current_pos = -1;
					 current_pos = current_pos + 1;
					 if(current_pos >= (int)pNextPos->dwActCnt)//循环播放
					{
						current_pos=0;
					}

					FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos*4);
					
					for(int j = 0;j < (int)act_res->dwActNum;j++)
					{

						if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
						{
							act_endtime = pNextPos->dwEndTime;
							return &act_res->ActList[j];

						}

					}
					showWarning("节目列表中不存在%d节目\n",*nAct_Id );
					return NULL;
				}
			}
			 else
			 {
				 current_pos = current_pos + 1;
				 if(current_pos >= (int)pNextPos->dwActCnt)//循环播放
				{
					current_pos=0;
				}

				FNDWORD *nAct_Id = (FNDWORD*)((char*)(pNextPos->dwActList) + current_pos*4);
				
				for(int j = 0;j < (int)act_res->dwActNum;j++)
				{

					if(act_res->ActList[j].sActInfo.dwActID == *nAct_Id)
					{
						act_endtime = pNextPos->dwEndTime;
						return &act_res->ActList[j];

					}

				}
				showWarning("节目列表中不存在%d节目\n",*nAct_Id );
				return NULL;
			 }
		}
		pPrvPos = pNextPos;
	}
	showWarning("时段出错，请检查时段!!!\n");
	return NULL;
}


TERMINAL_ACT_INFO* GetNextNameClass::GetName(const FN_STATE_ACT_LIST* period_info,
										TERMINAL_ACT_LIST* act_list,int &current_pos,int time_pos)
{
	FNDWORD k = 0;//
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
		showWarning("当前时间在时间表时段内越界\n");
		return NULL;
	}

	current_pos = current_pos + 1;
	if(current_pos >= (int)period_info->SectionList[time_pos].dwActCnt)//循环播放
	{
		current_pos=0;
	}
	 showDebug("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-40\n");
	//获取到一个播放的节目号，还要通过这个号码在节目表中找到具体的节目
	k = period_info->SectionList[time_pos].dwActList[current_pos];

	for(FNDWORD i=0;i<act_list->dwActNum;i++)
	{
	
		if(act_list->ActList[i].sActInfo.dwActID == k)
		{
			act_endtime = period_info->SectionList[time_pos].dwEndTime;
			return &act_list->ActList[i];
		
		}

	}
	
	showWarning("获取节目%u失败，当前时段为%u\n",k,time_pos );
	act_endtime = 0;
	return NULL;
}

	
#define MAX_SCHEME_BUF_LEN 	512 * 1024
char g_PlaySchemeBuf[MAX_SCHEME_BUF_LEN];

FNDWORD GetNextNameClass::ReadPlayInfo(const char *szFileName)
{
	int i = 0, j = 0, k = 0, m = 0, n = 0;
	int nOffset = 0, nDataLen = 0, nSectionLen = 0;
	int nAreaPos = 0, nStatePos = 0;
	memset(m_pStateActList, 0, sizeof(m_pStateActList));
	memset(g_PlaySchemeBuf, 0, sizeof(g_PlaySchemeBuf));
	TIME_SECTION_INFO *pSectionInfo = NULL;
	
	const char *pAttribute = NULL;
	XMLHandle pProgramList = NULL;
	XMLHandle pProgramIDList = NULL;
	XMLHandle pProgramInfo = NULL;
	XMLHandle pAreaInfo = NULL;
	XMLHandle pStateList = NULL;    
	XMLHandle pStateInfo = NULL;
	XMLHandle pTimePosList = NULL;    
	XMLHandle pTimePosInfo = NULL;
	XMLHandle pRootElement = NULL;
	int nNum = 0, nProgramNum = 0;
	int nSuccess = 0;
    
	m_pActResource = (TERMINAL_ACT_LIST*)g_PlaySchemeBuf;

	if (XMLInitLib(16 * 1024) < 0)
	{
		showWarning("初始化Xml库失败.\n");
		return false;
	}	

	//创建一个XML的文档对象
	int nRet = XMLLoadFile((char*)szFileName);
  if(nRet < 0)
  {
  	showWarning("装入时间表文件失败\r\n");
  	goto ERETURN;
  }

	//获得根元素
	pRootElement = XMLReadRootNode();
  if(!pRootElement)
  {
  	showWarning("读取时间表根节点错误\r\n");
  	goto ERETURN;
  }

	//取节目列表
  pProgramList = XMLReadChildNode(pRootElement);
  if(!pProgramList)
  {
  	showWarning("取节目列表失败\r\n");
  	goto ERETURN;
  }

	pAttribute = XMLReadAttributeValue(pProgramList, (char*)"NUM");
	if(!pAttribute)
	{
		showWarning("取节目列表数量错误\r\n");
  	goto ERETURN;
  }

	nNum = atoi(pAttribute);
  if(nNum <= 0 || nNum > FN_MAX_ACT_NUM)
  {
  	showWarning("取节目列表数量错误 %d\r\n", nNum);
  	goto ERETURN;
  }

	pProgramInfo = XMLReadChildNode(pProgramList);
	m_pActResource->dwActNum = 0;    
	for( i = 0; i < nNum; i++ )
	{
    if(!pProgramInfo)
    {
    	showWarning("节目列表数量不足 %d %d\r\n", nNum, i);
    	goto ERETURN;
    }
    pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"ACTID");
    if(!pAttribute || !pAttribute[0])
    {
    	showWarning("第%d个节目无ID\r\n", i + 1);
    	goto ERETURN;		    
    }
    sscanf(pAttribute, "%u", &m_pActResource->ActList[i].sActInfo.dwActID);
    pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"MAINFILEID");
    if(!pAttribute || !pAttribute[0])
    {
    	showWarning("第%d个节目无主文件ID\r\n", i + 1);
    	goto ERETURN;
    }
  	sscanf(pAttribute, "%u", &m_pActResource->ActList[i].sActInfo.dwMainFileID);
    if((pAttribute[0] - '0') != FN_FILE_TYPE_VIDEO && (pAttribute[0] - '0') != FN_FILE_TYPE_IMAGE
		&& (int)m_pActResource->ActList[i].sActInfo.dwMainFileID != -1)
    {
    	showWarning("第%d个节目主文件ID %c %u错误\r\n", 
  		i + 1, 
  		pAttribute[0],
  		m_pActResource->ActList[i].sActInfo.dwMainFileID);
    	goto ERETURN;
    }

		pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"MUSICFILEID");
		if(pAttribute)
		{
			sscanf(pAttribute, "%09u", &m_pActResource->ActList[i].sActInfo.dwMusicFileID);
			if(pAttribute[0] != '0' && (pAttribute[0] - '0') != FN_FILE_TYPE_AUDIO)
			{
				showWarning("第%d个节目音频文件ID %c %u错误\r\n", 
				i + 1, 
				pAttribute[0],
				m_pActResource->ActList[i].sActInfo.dwMusicFileID);
	    	goto ERETURN;
	    }	    	
    }
    pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"ADDIMAGEFILEID");
    if(pAttribute)
	  {
	  	sscanf(pAttribute, "%09u", &m_pActResource->ActList[i].sActInfo.dwAddImageFileID);
	    if(pAttribute[0] != '0' && (pAttribute[0] - '0') != FN_FILE_TYPE_IMAGE)
	    {
	    	showWarning("第%d个节目附属图像文件ID %c %u错误\r\n", 
	    		i + 1, 
	    		pAttribute[0],
	    		m_pActResource->ActList[i].sActInfo.dwAddImageFileID);
	    	goto ERETURN;
	    }
    }

		pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"PLAYTIME");
		if(!pAttribute)
		{
			showWarning("第%d个节目无播放时间\r\n", i + 1);
			goto ERETURN;
		}

		sscanf(pAttribute, "%09u", &m_pActResource->ActList[i].sActInfo.dwPlayTime);
    if(m_pActResource->ActList[i].sActInfo.dwPlayTime > (24 * 60 * 60))
    {
			showWarning("第%d个节目播放时间 %u错误\r\n", 
			i + 1, 
			m_pActResource->ActList[i].sActInfo.dwPlayTime);
    	goto ERETURN;
    }

		pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"PHONECODE");
		if(pAttribute)
		{
			strncpy(m_pActResource->ActList[i].sActInfo.cPhoneCode, pAttribute, FN_PHONE_CODE_LEN);
			m_pActResource->ActList[i].sActInfo.cPhoneCode[FN_PHONE_CODE_LEN - 1] = 0;
		}

		pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"URL");
		if(pAttribute)
		{
				strncpy(m_pActResource->ActList[i].sActInfo.cURL, pAttribute, FN_URL_LEN);
				m_pActResource->ActList[i].sActInfo.cURL[FN_URL_LEN - 1] = 0;
    }
		pProgramInfo = XMLReadBrotherNode(pProgramInfo);
	}  

	m_pActResource->dwActNum = nNum;//填写节目资源量  
	//定位主区域第一个状态
	nOffset = nNum * sizeof(TERMINAL_ACT_INFO) + 4;//节目资源表所占存储空间
	m_pStateActList[0][0] = (FN_STATE_ACT_LIST*)(g_PlaySchemeBuf + nOffset);
	pAreaInfo = XMLReadBrotherNode(pProgramList);
	for( i = 0; i < 5; i++ )//区域循环，最多5个区域
	{
		if(!pAreaInfo)
		{
			showWarning("区域数量定义不够 %d\r\n", i);
			goto ERETURN;
		}  
		    
		nAreaPos = 0;    	
		pAttribute = XMLReadAttributeValue(pAreaInfo, (char*)"ID");
		if(pAttribute)
		{
			nAreaPos = atoi(pAttribute);//当前区域定位
		}
		nAreaPos--;
		if(nAreaPos < 0 || nAreaPos >= 5)//最多5个区域
	  {
	  	showWarning("区域id定义错误 %d\r\n", nAreaPos + 1);
	  	goto ERETURN;
	  } 
		pStateList = XMLReadChildNode(pAreaInfo);
		if(!pStateList)
		{
			showWarning("区域 %d 无状态列表定义错误\r\n", nAreaPos + 1);
			goto ERETURN;
		}  		    
		pStateInfo = XMLReadChildNode(pStateList);
		for( j = 0; j < FN_STATE_NUM; j++ )//状态循环
		{
		  nDataLen = 0;
		  nSectionLen = 0;		
		  if(!pStateInfo)
		  {
	    	if(j == 0)
	    	{
		    	showWarning("区域 %d 未定义状态轴\r\n", nAreaPos + 1);
		    	goto ERETURN;		    	
	    	}
	    	break;
	    }  		    
			nStatePos = -1; 	
			pAttribute = XMLReadAttributeValue(pStateInfo, (char*)"ID");
	  	if(pAttribute)
	  	{
	    	nStatePos = atoi(pAttribute);//当前区域定位
	    }
	    if(nStatePos < 0 || nStatePos >= FN_STATE_NUM)//最多FN_STATE_NUM个状态
	    {
	    	showWarning("状态ID %d 定义错误\r\n", nStatePos);
	    	goto ERETURN;
	    } 
	    m_pStateActList[nAreaPos][nStatePos] = (FN_STATE_ACT_LIST*)(g_PlaySchemeBuf + nOffset);	
	
			pTimePosList = XMLReadChildNode(pStateInfo);
	 		if(!pTimePosList)
			{
				showWarning("%d %d 无时段列表错误\r\n", nAreaPos, j);
				goto ERETURN;
			}							    		    
	    nNum = 0;		    
	    n++;
	    pTimePosInfo = XMLReadChildNode(pTimePosList);
	  	for( k = 0; k < TIME_SECTION_NUM; k++ )//时间段循环
	  	{
	 	    if(!pTimePosInfo)
		    {
		    	break;
		    } 
		    //偏移定位
		    pSectionInfo = (TIME_SECTION_INFO*)
											((char*)(m_pStateActList[nAreaPos][nStatePos]->SectionList) + nSectionLen);	
				pAttribute = XMLReadAttributeValue(pTimePosInfo, (char*)"ENDTIME");			    
		    if(!pAttribute || !pAttribute[0])
		    {
		    	showWarning("无结束时间定义\r\n");
		    	goto ERETURN;
		    }
		    sscanf(pAttribute, "%u", &pSectionInfo->dwEndTime);
		    pProgramIDList = XMLReadChildNode(pTimePosInfo);			    
		    if(!pProgramIDList)
		    {
		    	goto ERETURN;
		    }
				m = 0;
				pProgramInfo = XMLReadChildNode(pProgramIDList);
				while( m < SECTION_ACT_NUM)//段内节目循环
				{
		 	    if(!pProgramInfo)
			    {
			    	break;
			    }   	
			    pAttribute = XMLReadAttributeValue(pProgramInfo, (char*)"ACTID");
			    if(!pAttribute || !pAttribute[0])
			    {
			    	showWarning("无节目ID定义\r\n");
			    	goto ERETURN;
			    }
					sscanf(pAttribute, "%u", &pSectionInfo->dwActList[m]);
					//showWarning("节目号%d\r\n",pSectionInfo->dwActList[m]);
					m++;
					pProgramInfo = XMLReadBrotherNode(pProgramInfo);						
					//TSK_sleep(2);
					//TSK_yield();
	    	} 
				nProgramNum = m;
		    if(nProgramNum <= 0 || nProgramNum > SECTION_ACT_NUM)//最多SECTION_ACT_NUM个数量
		    {
		    	showWarning("时段节目数量 %d 错误\r\n", nProgramNum);
		    	goto ERETURN;
		    }
				pSectionInfo->dwActCnt = nProgramNum;//时段内节目数量
	    	nDataLen = nProgramNum * 4 + 8;  
	    	nSectionLen += nDataLen;	
	  		pTimePosInfo = XMLReadBrotherNode(pTimePosInfo);  	    	
	  	} 
			nNum = k;		    
			if(nNum <= 0)
			{
		    showWarning("时段数量 %d 错误\r\n", nNum);
		    goto ERETURN;
			}	    	
	    m_pStateActList[nAreaPos][nStatePos]->dwSectionCnt = nNum; //时段数量  
	  	nOffset += nSectionLen + 4;
	  	pStateInfo = XMLReadBrotherNode(pStateInfo);    	
		}
		pAreaInfo = XMLReadBrotherNode(pAreaInfo);
  }  
	showDebug("时间表内序列总数%d\r\n", n);
	nSuccess = 1;

ERETURN:
	if(pRootElement)
  {
  	XMLReleaseResource();
  }
  if(!nSuccess) 
  {
  	showWarning("时间表文件错误\r\n");
  }
  return nSuccess;	
}



