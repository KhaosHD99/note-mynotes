#include <stdlib.h>
#include <string.h>
#include "LogMsg.hpp"
#include "TimeListResolver.hpp"

GetActName *GetActName::instance = NULL;
GetActName* GetActName::getInstance(void)
{
	if (instance == NULL)
		instance = new GetActName();
	return instance;
}
	
bool GetActName::getActName(int window_type,int play_mode,ACTINFO_AND_STOPTIME* get_info)
{  
    TERMINAL_ACT_INFO* act_info = NULL;				// = new TERMINAL_ACT_INFO;
	//if (act_info == NULL || get_info == NULL)
	//{
	//	showWarning("申请内存失败\n");
	//	return false;
	//}
	if (pNextName == NULL)
	{
		showWarning("创建时间表实例不成功\n");
		delete act_info;
		act_info = NULL;
		return false;
	}
	act_info = pNextName->GetNextName(window_type, play_mode);
	
	if (act_info==NULL)//获取时间表信息不成功
	{
		showWarning("获取节目失败的窗口为:%d,播放模式为:%d",window_type,play_mode);
		return false;
	}
	
	if (act_info->sActInfo.dwActID == 0)//判断节目名是否为空
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
	
	//获取节目类型
	int nType = act_info->sActInfo.dwMainFileID / FN_TYPE_BASE_VALUE;
	if (nType == FN_FILE_TYPE_VIDEO)//判断文件是否为H264文件
	{
		get_info->filetype = actFtH264;
		sprintf(get_info->szMainFileName,
			"%s/video/%u.h264", DIRPATH, act_info->sActInfo.dwMainFileID);
	}
	else if (nType == FN_FILE_TYPE_IMAGE)//判断文件是否为图片文件
	{
		get_info->filetype = actFtJpeg;
		sprintf(get_info->szMainFileName,
			"%s/image/%u.jpg", DIRPATH, act_info->sActInfo.dwMainFileID);
	}
	else if ((int)act_info->sActInfo.dwMainFileID == -1)//判断文件是否为在线广告
	{
		get_info->filetype = actAdOnLine;
		get_info->szMainFileName[0] = 0;
	}
	else
	{
		showWarning("节目主文件类型出错\n");
		return false;
	}
	return true;
} 

#define AD_PLAY_SCHEME_FILE "myplaylist.xml"

bool GetActName::readPlayAct()
{
	if (pNextName == NULL)
	{
		showWarning("创建时间表实例不成功\n");
		return false;
	}
	char szFileName[64];
	char szFileNamebk[64];


	int update_flag = pNextName->UpdateTimeAct(AD_PLAY_SCHEME_FILE, AD_PLAY_SCHEME_FILE);

	if (update_flag == 0)
	{
		pNextName->InitFlagData();
	}
	else if (update_flag == -1)
	{
		showWarning("打开时间表文件失败\n");
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
		showWarning("打开时间表文件失败\n");
		return false;
	}
*/

	return true;
}
