#ifndef MCALLSTRUCTS_INCLUDE_H_
#define MCALLSTRUCTS_INCLUDE_H_

#define MAX_FILE_NAME	64

#define MEDIA_CALL_PATH				"/home/data/appfile/mcall/"

#define MCALL_JPEG_DATA_TYPE			0
#define MCALL_VIDEO_DATA_TYPE			1
#define MCALL_AUDIO_DATA_TYPE			2

/*******************************
��Ƶ��ͼ�񲻿���ͬʱ����
���ݴ��������:
//Լ��GIF��JPEG �ļ���
{ {ͼ��} ��{��Ƶ}��{GIF}��{����}��{ͼ��,����}��{��Ƶ,����}��{GIF ,����}}
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
	//ȫռ��
	AREA_A = 0,
	AREA_B,
	AREA_C,
	AREA_D,
	//����ռ��[��ͼƬ��GIF ����]
	AREA_ACHILD,
	AREA_BCHILD,
	AREA_CCHILD,
	AREA_DCHILD
}PlayArea;

typedef enum MCALLSTATUES
{
	MCALL_CLOSE = 0, 	//���ڹر�״̬
	MCALL_OPEN,		 //���з��Ѵ��ļ�,���з����ڿ�ʼ״̬��׼������״̬
	MCALL_SENDING, 	//���з������ļ���
	MCALL_RECVING		//���з������ļ���
}MCALLSTATUES;

typedef struct MediaCallStatues
{
	unsigned int mPlayerType;		//   1, ���з��� 0Ϊ���з�
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

//�������㹻�Ļ������������

#define MAX_MCALL_DATABUF_SIZE	1024*32*4

#define MAX_MCALL_DATASEND_LEN	512

#define MAX_MCALL_BUFS_COUNT		2


typedef struct MediaDataRecvInfo
{
	FILE *fdWrite;
	unsigned int nfileSize;
	unsigned int nOffSet;
//	void msqHandle;		//������Ϣ����������len : 32*4
	unsigned char* pMediaDataBuf;
}MediaDataRecvInfo;

typedef struct MediaCallRecvInfo
{
	MCALLSTATUES mCallRecverStatues;
//	unsigned int openfalg;	// 1Ϊʹ����,0Ϊ�ر���
	unsigned int nFileID;
	unsigned int nPlayArea;
	unsigned int nMCallType;
	char			cMachineCode[12];
	MediaDataRecvInfo stJpegRecvInfo;
	MediaDataRecvInfo stVideoRecvInfo;
	MediaDataRecvInfo stAudioRecvInfo;
}MediaCallRecvInfo;

#endif


