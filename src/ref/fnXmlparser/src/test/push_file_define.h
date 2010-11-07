#ifndef _PUSH_FILE_DEFINE__H_
#define _PUSH_FILE_DEFINE__H_


#ifndef FNTYPEDEF 
#define FNTYPEDEF 

typedef unsigned int FNDWORD;
typedef unsigned short FNWORD;
typedef unsigned char FNBYTE;
union U_DWORD
{
	FNDWORD	dwVal;
	char	cVal[4];
	FNBYTE	btVal[4];
};
#endif

/**************************************************************************
应用程序存放位置:/home/program /usr/local /usr/local/bin
应用配置文件存放位置:/home/data/appfile /usr/local
应用数据文件存放位置:/home/data/localfile

下推数据结构定义,用于确定文件服务器下推作业细则。

文件ID定义
文件分类 加 文件索引号 构成文件ID
类型号为千万位,当ID号递增到100,000,000 - 1时,应回归0.前台业务在制定文件ID时,不要与当前在
使用的文件ID冲突
终端文件存储目录 
视频文件 /d/localfile/video
音频文件 /d/localfile/audio
图像文件 /d/localfile/image
图像文件 /d/localfile/annex
时间表文件 /d/localfile/scheme
系统程序文件 /d/localfile/sys
**********************************************************************************/
#define FN_FILE_TYPE_BASE						100000000
#define FN_FILE_TYPE_VIDEO						1
#define FN_FILE_TYPE_AUDIO						2
#define FN_FILE_TYPE_IMAGE						3
#define FN_FILE_TYPE_TXT						4

#define FN_FILE_TYPE_SCHEME						8
#define FN_FILE_TYPE_SYS						9

#define FN_FILE_SUB_TYPE_BASE					10000000
#define FN_FILE_SUB_TYPE_SYS_CORE				1
#define FN_FILE_SUB_TYPE_SYS_MODULE				2
#define FN_FILE_SUB_TYPE_SYS_ANNEX				3
#define FN_FILE_SUB_TYPE_SYS_DLL				4
#define FN_FILE_SUB_TYPE_SYS_FILE_LIST			9

#define FN_FILE_ID_MODULE_BASE					100000//取模块ID

#define FN_FILE_COMM_CENTER_MODULE_ID 			0//通信中心模块ID
#define FN_FILE_PHONE_CONTROL_MODULE_ID 		1//电话控制模块ID
#define FN_FILE_BROWSER_MODULE_ID 				2//浏览器模块ID
#define FN_FILE_NET_MEDIA_MODULE_ID 			3//流媒体模块ID
#define FN_FILE_ADVPLAY_MODULE_ID 				4//广告播放模块ID
#define FN_FILE_FILE_DOWNLOAD_MODULE_ID 		5//文件下载模块ID
#define FN_FILE_GUICORE_MODULE_ID 				6//GUI中心处理模块ID
#define FN_FILE_MMS_MODULE_ID 					7//多媒体短信模块ID
#define FN_FILE_PHONE_BOOK_MODULE_ID 			8//电话本模块ID
#define FN_FILE_SYSCFG_MODULE_ID 				9//系统配置模块ID
#define FN_FILE_VIDEOCONN_MODULE_ID 			10//视频互通模块ID
#define FN_FILE_MEDIA_PLAY_MODULE_ID 			11//媒体播放模块ID
#define FN_FILE_PPPOE_MODULE_ID 				12//PPPOE拨号模块ID
#define FN_FILE_TEST_MODULE_ID 					13//测试模块ID
#define FN_FILE_PHOTOFRAME_MODULE_ID 			14//数码相框模块ID
#define FN_FILE_SIP_CONN_MODULE_ID 				15//SIP协议互通模块ID
#define FN_FILE_SIP_LINPHONE_COMM_MODULE_ID 	16//linphone通信模块ID


#define FN_FILE_XML_LIB_MODULE_ID 				0
#define FN_FILE_GUI_LIB_MODULE_ID 				1
#define FN_FILE_VPU_LIB_MODULE_ID 				2
#define FN_FILE_MEDIA_LIB_MODULE_ID 			3
#define FN_FILE_CFG_LIB_MODULE_ID 				4
#define FN_FILE_IPC_LIB_MODULE_ID 				5
#define FN_FILE_GIF_LIB_MODULE_ID 				6



#define FN_STATE_NUM							6//状态数量

/*************************************************************************************
排列顺序为先排1号播放区待机、摘机、振铃与非视频通话序列,再按相同顺序排放2号播放区序列,
后续为主播放区摘机、振铃与非视频通话序列,
最后为主播放区各时段序列
由于现在只有一个视频编解码引擎,多广告窗口不能同时存在视频广告
*************************************************************************************/
#define FN_RING_STATE							0
#define FN_OFFHOOK_STATE						1
#define FN_NOVIDEOCONN_STATE					2
#define FN_NORMAL_STATE							3
#define FN_APP_STATE							4
#define FN_ONHOOK_STATE							5//挂机状态


#define FN_ONHOOK_TIME							15//挂机状态持续时间(s)

#define PLAY_REGION_MAIN						0
#define PLAY_REGION_1							1
#define PLAY_REGION_2							2

#define FN_MAX_FILE_NUM							4096
#define FN_MAX_ACT_NUM							2048//最多节目个数

#define FN_ACTIDLIST_NUM						2000//最大节目数量
#define FN_FILENAME_LEN							64//文件名长度
#define FN_FILEPATH_LEN							256//文件路径长度
#define FN_VERSIONID_LEN						28//版本ID长度
#define TIME_SECTION_NUM						17280//允许最大时段数量	
#define SECTION_ACT_NUM							17280
#define SYSTEM_FILE_NUM							1024
struct FN_BREAK_FILE
{
	unsigned int uFileID;
	unsigned int nRecvLen;//已接收完成长度
};
struct FN_BREAK_LIST
{
	unsigned int nNum;
	FN_BREAK_FILE	List[FN_MAX_FILE_NUM];
};

struct VERSION_TERMINAL_INFO
{
	char			cMachineCode[12];
	char			cCurrentVersion[FN_VERSIONID_LEN];
	char			cNewVersion[FN_VERSIONID_LEN];
};
struct SERVER_TIMEPERIOD_INFO
{
	FNDWORD TimePeriodID;
	FNDWORD TimeBegin;
	FNDWORD TimeEnd;
};
struct SERVER_TERMINAL_TIME
{
	char			cMachineCode[12];
	FNDWORD			dwActNum;//节目数量
	char			ActIDList[FN_ACTIDLIST_NUM];	//算节目ID为10位数 + 64个“,”号位
};
struct TERMINAL_FILE_INFO
{
	FNDWORD			dwFileID;
	//文件名采用(ID串).ext模式存储，避免同名文件冲突
	//带字符串终止符,大小写要求与真实文件名一致
	FNWORD			wRefCnt;
	FNWORD			wFlag;//为1表示需要更新,为0表示不需要更新
};
struct SERVER_FILE_INFO
{
	FNDWORD			dwFileID;
	char			cFileName[FN_FILENAME_LEN];//带字符串终止符,大小写要求与真实文件名一致,最长31个字符
	char			cFilePath[FN_FILEPATH_LEN];
	FNDWORD			dwFileSize;
};
//系统软件更新文件信息
struct SYSTEM_FILE_INFO
{
	FNDWORD			dwFileID;
	int				nUpdateFlag;//在旧的系统文件列表中未查到该文件ID即表示该文件需要下载,需要下载值为1,否则为0
	char			cFileName[FN_FILENAME_LEN];//带字符串终止符,大小写要求与真实文件名一致,最长31个字符
	char			cFilePath[FN_FILEPATH_LEN];
};
struct SYSTEM_FILE_LIST
{
	FNDWORD				dwFileNum;
	SYSTEM_FILE_INFO	FileList[SYSTEM_FILE_NUM];
};


#define FN_PHONE_CODE_LEN		20
#define FN_URL_LEN				64
struct SERVER_ACT_INFO
{
	FNDWORD			dwActID;
	FNDWORD			dwMainFileID;
	FNDWORD			dwMusicFileID;//关联音频文件
	FNDWORD			dwAddImageFileID;//附属详细信息图片文件
	FNDWORD			dwPlayTime;//播放持续时间 单位:s
	//附属联系信息
	char			cPhoneCode[FN_PHONE_CODE_LEN];//加终止符
	char			cURL[FN_URL_LEN];//加终止符
};
struct TERMINAL_ACT_INFO
{
	SERVER_ACT_INFO sActInfo;
	FNWORD			wRefCnt;
	FNWORD			wFlag;//为1表示需要更新,为0表示不需要更新
};
struct TERMINAL_ACT_LIST
{
	FNDWORD				dwActNum;//节目数量
	TERMINAL_ACT_INFO	ActList[FN_MAX_ACT_NUM];//节目列表
};
struct TERMINAL_FILE_LIST
{
	FNDWORD				dwFileNum;//文件数量
	TERMINAL_FILE_INFO	FileList[FN_MAX_FILE_NUM];//文件列表
};

struct TIME_SECTION_INFO
{
	FNDWORD				dwEndTime;//本时段结束时间 以s为单位
	FNDWORD				dwActCnt;//节目数量 依据数量计算本时段所占用的空间
	FNDWORD				dwActList[1];//节目列表 逻辑判断最大充许值(24 * 60 * 60) / 5
};
struct FN_STATE_ACT_LIST
{
	FNDWORD				dwSectionCnt;//时段数量 依据时段数量计算列表所占空间
	TIME_SECTION_INFO	SectionList[1];//时段列表 
};

struct TERMINAL_MEDIA_PLAY_INFO_FILE//这是时间表存储示意结构
{
	//从磁盘文件读出时需要依据节目数量计算文件列表ActResource占用存储空间
	//ActList[FN_PERIOD_OF_TIME_ACT_NUM]定义不确定长度
	TERMINAL_ACT_LIST		ActResource;

	//0为待机状态
	FN_STATE_ACT_LIST		MainArea[FN_STATE_NUM];//主窗口各状态时段列表
	FN_STATE_ACT_LIST		NO1AreaActList[FN_STATE_NUM];//1号(左上)窗口各状态时段列表
	FN_STATE_ACT_LIST		NO2AreaActList[FN_STATE_NUM];//2号(左下)窗口各状态时段列表

	FNDWORD					dwCheckVal;//动态定位在最后4个字节
};

#endif
