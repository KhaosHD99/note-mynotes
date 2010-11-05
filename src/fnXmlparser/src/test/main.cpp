#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "LogMsg.hpp"
//#include "XMLInterface.h"
#include "TimeListResolver.hpp"
#include "push_file_define.h"

#define AD_PLAY_CONFIG_FILE "play_window.xml"
#define AD_PLAY_SCHEME_FILE "myplaylist.xml"

bool loadDefaultConfig();
void showWindowConfig();
bool initConfig();
int ReadPlayInfo(const char *szFileName);
int showPlayInfo();

int main()
{
	printf("this the fnxmlparser libs test : %s\r\n", AD_PLAY_CONFIG_FILE);

	// 初始化广告播放列表
	if (!GetActName::getInstance()->readPlayAct())
	{
		showWarning("读取时间表文件失败.\n");

	}
	else
	{
		showDebug("读取时间表文件成功.\n");

	}

	return 0;
}

#if 0

#define MAX_SCHEME_BUF_LEN 	512 * 1024
char g_PlaySchemeBuf[MAX_SCHEME_BUF_LEN];

static FN_STATE_ACT_LIST* m_pStateActList[3][FN_STATE_NUM];
static TERMINAL_ACT_LIST* m_pActResource;
static TERMINAL_MEDIA_PLAY_INFO_FILE* m_pPlayInfo;
static int act_endtime;

int ReadPlayInfo(const char *szFileName)
{
	showWarning("Fun : %s, %s\r\n", __FUNCTION__, szFileName);
	
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
	for( i = 0; i < 5; i++ )//区域循环,最多3个区域
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
		if(nAreaPos < 0 || nAreaPos >= 5)//最多3个区域
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

int	showPlayInfo()
{
	showWarning("Fun : %s\r\n", __FUNCTION__);
	
}

#endif
