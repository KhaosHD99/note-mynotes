/*
* Copyright ���ݷ�����Ѷ���޹�˾
* All rights reserved.
* 
* �ļ����ƣ�TimeListResolver.cpp
* 
* ժ    Ҫ����ʱ�����н���
* 
* ��    �ߣ���ҫȪ
*
* �޸���:   �����
* 
* ����޸����ڣ�2010��11��19��
*/

#include <stdlib.h>
#include <string.h>
#include "LogMsg.hpp"
#include "TimeListResolver.hpp"

GetActName *GetActName::instance = NULL;
GetActName* GetActName::get_instance(void)
{
	if (instance == NULL)
		instance = new GetActName();
	return instance;
}

#if 1
bool GetActName::get_current_act_name(int area_type, int status, ACTINFO_AND_STOPTIME* get_info)
{
   	if (get_info == NULL)
	{
		showWarning("Memory allocate error\n");
		return false;
	}
	
	TERMINAL_ACT_INFO* act_info = NULL;		

	if (pNextName == NULL)
	{
		showWarning("Create TimeList Instance Error\n");
		delete act_info;
		act_info = NULL;
		return false;
	}
	act_info = pNextName->get_next_name(area_type, status);

	//��ȡʱ�����Ϣ���ɹ�
	if (act_info == NULL)
	{
		showWarning("Window %d Get Act Error,State: %d \n", area_type, status);
		return false;
	}

	//�жϽ�Ŀ���Ƿ�Ϊ��
	if (act_info->sActInfo.dwActID == 0)
	{
		get_info->szActName = 0;
	}
	else
	{
		get_info->szActName = act_info->sActInfo.dwActID;
	}
	
	if (act_info->sActInfo.cURL == 0)
	{
		get_info->szURL[0] = 0;
	}
	else
	{
		sprintf(get_info->szURL,
				"%s", act_info->sActInfo.cURL);
	}
	
	if (act_info->sActInfo.cPhoneCode == 0)
	{
		get_info->szPhoneCode[0] = 0;
	}
	else
	{
		sprintf(get_info->szPhoneCode,
				"%s", act_info->sActInfo.cPhoneCode);
	}
	if (act_info->sActInfo.dwAddImageFileID == 0)
	{
		get_info->szAddImageFileName[0] = 0;
	}
	else
	{
		sprintf(get_info->szAddImageFileName,
				"%s/image/%u.jpg", DIRPATH, act_info->sActInfo.dwAddImageFileID);
	}
	
	if(act_info->sActInfo.dwMusicFileID == 0)
	{
		get_info->szMusicFileName[0] = 0;
	}
	else
	{
		sprintf(get_info->szMusicFileName,
				"%s/audio/%u.mp3", DIRPATH, act_info->sActInfo.dwMusicFileID);
	}
	
	get_info->PlayTime = (int)act_info->sActInfo.dwPlayTime;
	get_info->endTime = pNextName->getActEndTime();
	
	//��ȡ��Ŀ����
	int nType = act_info->sActInfo.dwMainFileID / FN_TYPE_BASE_VALUE;
	
	//�ж��ļ��Ƿ�ΪH264�ļ�
	if (nType == FN_FILE_TYPE_VIDEO)
	{
		get_info->filetype = actFtH264;

		#if 1
		sprintf(get_info->szMainFileName,
	     		"%u.avi", act_info->sActInfo.dwMainFileID);
		#endif

		#if 0
		sprintf(get_info->szMainFileName,
	    		"%s", "infinity.avi");
		#endif

		#if 0
		sprintf(get_info->szMainFileName,
	    		"%s", "wen.avi");
		#endif
	}
	//�ж��ļ��Ƿ�ΪͼƬ�ļ�
	else if (nType == FN_FILE_TYPE_IMAGE)
	{
		get_info->filetype = actFtJpeg;
		sprintf(get_info->szMainFileName,
			    "%u.jpg", act_info->sActInfo.dwMainFileID);
	}
	//�ж��ļ��Ƿ�Ϊ���߹��
	else if ((int)act_info->sActInfo.dwMainFileID == -1)
	{
		get_info->filetype = actAdOnLine;
		get_info->szMainFileName[0] = 0;
	}
	else
	{
		showWarning("MainField Error\n");
		return false;
	}
	return true;
} 
#endif

/******************************************************************************************
		                       	   Read TimeList To Buffer From File 
*******************************************************************************************/
bool GetActName::read_play_act()
{
	if (pNextName == NULL)
	{
		showWarning("Create timeList instance fail\n");
		return false;
	}
	char szFileName[64];
	char szFileNamebk[64];
	
	int update_flag = pNextName->update_time_act(AD_PLAY_SCHEME_FILE, AD_PLAY_SCHEME_FILE);
	
	if (update_flag == 0)
	{
		pNextName->InitFlagData();
	}
	else if (update_flag == -1)
	{
		showWarning("Open time list file fail\n");
		return false;
	}
	
    /*
	sprintf(szFileName,"%s/scheme/800000000.xml", DIRPATH);
	sprintf(szFileNamebk,"%s/scheme/800000001.xml", DIRPATH);
	
	int update_flag = pNextName->UpdateTimeAct(szFileName, szFileNamebk);
	
	if (update_flag == 0)
	{
		pNextName->InitFlagData();
	}
	else if (update_flag == -1)
	{
		showWarning("��ʱ����ļ�ʧ��\n");
		return false;
	}
*/
	return true;
}
