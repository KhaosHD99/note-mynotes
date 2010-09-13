#ifndef MCALLSTRUCTS_INCLUDE_H_
#define MCALLSTRUCTS_INCLUDE_H_

#define MAX_FILE_NAME	64

#define MEDIA_CALL_PATH				"/home/data/appfile/mcall/"

#define MCALL_JPEG_DATA_TYPE			0
#define MCALL_VIDEO_DATA_TYPE			1
#define MCALL_AUDIO_DATA_TYPE			2

/*******************************
视频与图像不可能同时存在
数据传输组合有:
//约定GIF是JPEG 的集合
{ {图像} 、{视频}、{GIF}、{音乐}、{图像,音乐}、{视频,音乐}、{GIF ,音乐}}
*******************************/
typedef enum Media_Call_TYPE
{
	PIC_ONLY = 0,
	VID_ONLY,
	GIF_ONLY,
	AUD_ONLY,
	PIC_AUD,
	VID_AUD,
	GIF_AUD
}MediaCallType;

typedef enum PLAY_AREA
{
	//全占用
	AREA_A = 0,
	AREA_B,
	AREA_C,
	AREA_D,
	//部分占用[仅图片或GIF 可行]
	AREA_ACHILD,
	AREA_BCHILD,
	AREA_CCHILD,
	AREA_DCHILD
}PlayArea;

typedef enum MCALLSTATUES
{
	MCALL_CLOSE = 0, 	//处于关闭状态
	MCALL_OPEN,		 //主叫方已打开文件,被叫方处于开始状态或准备结束状态
	MCALL_SENDING, 	//主叫方发送文件中
	MCALL_RECVING		//被叫方接收文件中
}MCALLSTATUES;

typedef struct MediaCallStatues
{
	unsigned int mPlayerType;		//   1, 主叫方， 0为被叫方
	MCALLSTATUES mStatue;
	unsigned int mSecTimeOut;		//
	unsigned int mTimeKeeper;	//
	unsigned int mTimeCounter;
}MediaCallStatues;


typedef struct MEDIA_FILE_INFO
{
	unsigned int nFileID;
	PlayArea	mPlayArea;
	MediaCallType nMCallType;	
	char szJpegFile[MAX_FILE_NAME];
	char szVideoFile[MAX_FILE_NAME];
	char szAudioFile[MAX_FILE_NAME];
}MediaFileInfo;

typedef struct MEDIA_FILE_OPEN
{
	MCALLSTATUES mCallSenderStatues;
	unsigned int nFileID;
	PlayArea	mPlayArea;
	MediaCallType nMCallType;	
	FILE *hJpegFile;
	unsigned int nJpegSize;
	FILE *hVideoFile;
	unsigned int nVideoSize;
	FILE *hAudioFile;
	unsigned int nAudioSize;
}MediaFileOpen;

//必须有足够的缓冲区存放数据

#define MAX_MCALL_DATABUF_SIZE	1024*32*4

#define MAX_MCALL_DATASEND_LEN	512

#define MAX_MCALL_BUFS_COUNT		2


typedef struct MediaDataRecvInfo
{
	FILE *fdWrite;
	unsigned int nfileSize;
	unsigned int nOffSet;
//	void msqHandle;		//利用消息对列做缓冲len : 32*4
	unsigned char* pMediaDataBuf;
}MediaDataRecvInfo;

typedef struct MediaCallRecvInfo
{
	MCALLSTATUES mCallRecverStatues;
//	unsigned int openfalg;	// 1为使用中,0为关闭中
	unsigned int nFileID;
	unsigned int nPlayArea;
	unsigned int nMCallType;
	char			cMachineCode[12];
	MediaDataRecvInfo stJpegRecvInfo;
	MediaDataRecvInfo stVideoRecvInfo;
	MediaDataRecvInfo stAudioRecvInfo;
}MediaCallRecvInfo;

#endif


