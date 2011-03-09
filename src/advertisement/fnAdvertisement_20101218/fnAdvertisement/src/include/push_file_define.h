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
Ӧ�ó�����λ��:/home/program /usr/local /usr/local/bin
Ӧ�������ļ����λ��:/home/data/appfile /usr/local
Ӧ�������ļ����λ��:/home/data/localfile

�������ݽṹ����,����ȷ���ļ�������������ҵϸ��

�ļ�ID����
�ļ����� �� �ļ������� �����ļ�ID
���ͺ�Ϊǧ��λ,��ID�ŵ�����100,000,000 - 1ʱ,Ӧ�ع�0.ǰ̨ҵ�����ƶ��ļ�IDʱ,��Ҫ�뵱ǰ��
ʹ�õ��ļ�ID��ͻ
�ն��ļ��洢Ŀ¼ 
��Ƶ�ļ� /d/localfile/video
��Ƶ�ļ� /d/localfile/audio
ͼ���ļ� /d/localfile/image
ͼ���ļ� /d/localfile/annex
ʱ����ļ� /d/localfile/scheme
ϵͳ�����ļ� /d/localfile/sys
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

#define FN_FILE_ID_MODULE_BASE					100000//ȡģ��ID

#define FN_FILE_COMM_CENTER_MODULE_ID 			0//ͨ������ģ��ID
#define FN_FILE_PHONE_CONTROL_MODULE_ID 		1//�绰����ģ��ID
#define FN_FILE_BROWSER_MODULE_ID 				2//�����ģ��ID
#define FN_FILE_NET_MEDIA_MODULE_ID 			3//��ý��ģ��ID
#define FN_FILE_ADVPLAY_MODULE_ID 				4//��沥��ģ��ID
#define FN_FILE_FILE_DOWNLOAD_MODULE_ID 		5//�ļ�����ģ��ID
#define FN_FILE_GUICORE_MODULE_ID 				6//GUI���Ĵ���ģ��ID
#define FN_FILE_MMS_MODULE_ID 					7//��ý�����ģ��ID
#define FN_FILE_PHONE_BOOK_MODULE_ID 			8//�绰��ģ��ID
#define FN_FILE_SYSCFG_MODULE_ID 				9//ϵͳ����ģ��ID
#define FN_FILE_VIDEOCONN_MODULE_ID 			10//��Ƶ��ͨģ��ID
#define FN_FILE_MEDIA_PLAY_MODULE_ID 			11//ý�岥��ģ��ID
#define FN_FILE_PPPOE_MODULE_ID 				12//PPPOE����ģ��ID
#define FN_FILE_TEST_MODULE_ID 					13//����ģ��ID
#define FN_FILE_PHOTOFRAME_MODULE_ID 			14//�������ģ��ID
#define FN_FILE_SIP_CONN_MODULE_ID 				15//SIPЭ�黥ͨģ��ID
#define FN_FILE_SIP_LINPHONE_COMM_MODULE_ID 	16//linphoneͨ��ģ��ID

#define FN_FILE_XML_LIB_MODULE_ID 				0
#define FN_FILE_GUI_LIB_MODULE_ID 				1
#define FN_FILE_VPU_LIB_MODULE_ID 				2
#define FN_FILE_MEDIA_LIB_MODULE_ID 			3
#define FN_FILE_CFG_LIB_MODULE_ID 				4
#define FN_FILE_IPC_LIB_MODULE_ID 				5
#define FN_FILE_GIF_LIB_MODULE_ID 				6

//״̬����
#define FN_STATE_NUM							6

/*************************************************************************************
����˳��Ϊ����1�Ų�����������ժ�������������Ƶͨ������,�ٰ���ͬ˳���ŷ�2�Ų���������,
����Ϊ��������ժ�������������Ƶͨ������,
���Ϊ����������ʱ������
��������ֻ��һ����Ƶ���������,���洰�ڲ���ͬʱ������Ƶ���
*************************************************************************************/
//�һ�״̬
//#define FN_ONHOOK_STATE							5

#define FN_MAX_FILE_NUM							4096

//����Ŀ����
#define FN_MAX_ACT_NUM							2048
//����Ŀ����
#define FN_ACTIDLIST_NUM						2000
//�ļ�������
#define FN_FILENAME_LEN							64
//�ļ�·������
#define FN_FILEPATH_LEN							256
//�汾ID����
#define FN_VERSIONID_LEN						28
//�������ʱ������
#define TIME_SECTION_NUM						17280	
#define SECTION_ACT_NUM							17280
#define SYSTEM_FILE_NUM							1024

#define MAX_ADVER_AREAS                         5
#define MAJOR_DISPLAY_AREA_NUM                  4
#define ROLL_TEXT_AREA_NUM                      5
												
//File Path
#define IMAGE_PATH_PREFIX                       "../share/data/appfile/advertisement/image/"
#define VIDEO_PATH_PREFIX                       "../share/data/localfile/video/"
#define INIT_IMAGE                              "../share/data/appfile/advertisement/image/300004008.jpg"
#define AD_PLAY_SCHEME_FILE 					"../share/data/appfile/advertisement/myplaylist.xml"
#define AD_ROLL_TEXT_SCHEME_FILE     			"../share/data/appfile/advertisement/rolltext.xml"

enum
{	
    PLAY_AREA_1,
    PLAY_AREA_2,
    PLAY_AREA_3,
    PLAY_AREA_4,
    PLAY_AREA_5,
};	

/*
enum
{
	FNC_STATE_ONHOOK,
	FNC_STATE_OFFHOOK,
	FNC_STATE_RING,
    FNC_STATE_CONN,
	FNC_STATE_APP
};
*/

struct FN_BREAK_FILE
{
	unsigned int uFileID;
	unsigned int nRecvLen;//�ѽ�����ɳ���
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
	FNDWORD			dwActNum;//��Ŀ����
	char			ActIDList[FN_ACTIDLIST_NUM];	//���ĿIDΪ10λ�� + 64����,����λ
};
struct TERMINAL_FILE_INFO
{
	FNDWORD			dwFileID;
	//�ļ�������(ID��).extģʽ�洢������ͬ���ļ���ͻ
	//���ַ�����ֹ��,��СдҪ������ʵ�ļ���һ��
	FNWORD			wRefCnt;
	FNWORD			wFlag;//Ϊ1��ʾ��Ҫ����,Ϊ0��ʾ����Ҫ����
};
struct SERVER_FILE_INFO
{
	FNDWORD			dwFileID;
	char			cFileName[FN_FILENAME_LEN];//���ַ�����ֹ��,��СдҪ������ʵ�ļ���һ��,�31���ַ�
	char			cFilePath[FN_FILEPATH_LEN];
	FNDWORD			dwFileSize;
};
//ϵͳ��������ļ���Ϣ
struct SYSTEM_FILE_INFO
{
	FNDWORD			dwFileID;
	int				nUpdateFlag;//�ھɵ�ϵͳ�ļ��б���δ�鵽���ļ�ID����ʾ���ļ���Ҫ����,��Ҫ����ֵΪ1,����Ϊ0
	char			cFileName[FN_FILENAME_LEN];//���ַ�����ֹ��,��СдҪ������ʵ�ļ���һ��,�31���ַ�
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
	//������Ƶ�ļ�
	FNDWORD			dwMusicFileID;
	//������ϸ��ϢͼƬ�ļ�
	FNDWORD			dwAddImageFileID;
	//���ų���ʱ�� ��λ:s
	FNDWORD			dwPlayTime;
	//������ϵ��Ϣ
	//����ֹ��
	char			cPhoneCode[FN_PHONE_CODE_LEN];
	//����ֹ��
	char			cURL[FN_URL_LEN];
};
struct TERMINAL_ACT_INFO
{
	SERVER_ACT_INFO sActInfo;
	FNWORD			wRefCnt;
	//Ϊ1��ʾ��Ҫ����,Ϊ0��ʾ����Ҫ����
	FNWORD			wFlag;
};
struct TERMINAL_ACT_LIST
{
	//��Ŀ����
	FNDWORD				dwActNum;
	//��Ŀ�б�
	TERMINAL_ACT_INFO	ActList[FN_MAX_ACT_NUM];
};

struct TERMINAL_FILE_LIST
{
	//�ļ�����
	FNDWORD				dwFileNum;	
	//�ļ��б�
	TERMINAL_FILE_INFO	FileList[FN_MAX_FILE_NUM];
};

struct TIME_SECTION_INFO
{
    //��ʱ�ν���ʱ�� ��sΪ��λ
	FNDWORD				dwEndTime;
	//��Ŀ���� �����������㱾ʱ����ռ�õĿռ�
	FNDWORD				dwActCnt;
	//��Ŀ�б� �߼��ж�������ֵ(24 * 60 * 60) / 5
	FNDWORD				dwActList[1];
};

struct FN_STATE_ACT_LIST
{
    //ʱ������ ����ʱ�����������б���ռ�ռ�
	FNDWORD				dwSectionCnt;
	//ʱ���б� 
	TIME_SECTION_INFO	SectionList[1];
};

struct TERMINAL_MEDIA_PLAY_INFO_FILE//����ʱ���洢ʾ��ṹ
{
	//�Ӵ����ļ�����ʱ��Ҫ���ݽ�Ŀ���������ļ��б�ActResourceռ�ô洢�ռ�
	//ActList[FN_PERIOD_OF_TIME_ACT_NUM]���岻ȷ������
	TERMINAL_ACT_LIST		ActResource;

	//0Ϊ����״̬
	//�����ڸ�״̬ʱ���б�
	FN_STATE_ACT_LIST		MainArea[FN_STATE_NUM];
	//1��(����)���ڸ�״̬ʱ���б�
	FN_STATE_ACT_LIST		NO1AreaActList[FN_STATE_NUM];
	//2��(����)���ڸ�״̬ʱ���б�
	FN_STATE_ACT_LIST		NO2AreaActList[FN_STATE_NUM];
	//��̬��λ�����4���ֽ�
	FNDWORD					dwCheckVal;
};

#endif
