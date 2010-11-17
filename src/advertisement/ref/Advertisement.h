#ifndef _ADVERTISEMENT_H_
#define _ADVERTISEMENT_H_
#include "GuiWnd.hpp"
#include "StdCtrl.hpp"
#include "TimeListResolver.hpp"
#include "Config.h"
#include "AppIMediaPlayerMng.h"


const int phoneStateNum			= 7;


class Advertisement;

//�߳��õĽṹ
struct PlayTimeThreadData
{
	Advertisement *pAdvertisement;
	int num;
};


//������ʾͼƬ�Ĵ���
class AdvertisementWnd: public GuiWnd
{
	public:
		TJpegBgImage *bgImage;
		TJpegXMLImage *bgDefaultImg;
	public:
		AdvertisementWnd(int x, int y, int width, int height);
		virtual ~AdvertisementWnd();
	int onKey(int key)
	{
		showInfo("AdvertisementWnd::onKey %d\r\n", key);
		return false;
	}
};


class Advertisement
{
	public:
		int x, y;
		int width, height;
		int windowType;
		pthread_t adPthreadID;				//�߳�ID

		AdvertisementWnd *wnd;				//ͼƬ��ʾ����
		unsigned short *imageBuf;
		bool imageBufIsDirty;

		unsigned int currentProgramID;		//��ǰ���ڲ��ŵĽ�ĿID
		int currentEndTime;					//��ǰ���ڲ��ŵĽ�ĿҪ������ʱ��
		ACTINFO_AND_STOPTIME actInfo;

	public:
		Advertisement();
		~Advertisement();

		bool init(int x, int y, int width, int height, int wintype);
};


struct CPhoneState
{
	unsigned int uCurMajorState;//��״̬
	//unsigned int uCurMinorState;//��״̬
};


struct MediaCall
{
	MCALL_TYPE			mCallPlayType;	//��call������
	PLAY_AREA			mCallPlayArea;	//��callҪռ�õ�����
	MCALLPLAY_ACTION	mCallState;		//��call�ĵ�״̬,0��ʾ�ر�,1��ʾ��
};

class AdvertisementMan
{
	private:
		int m_nNotice;
		static AdvertisementMan *instance;
	public:
		//��ʱ���߳�����ʱ�Ž��г�ʼ��
		sem_t timeSem;				                 
		//��ʱ���߳�����ʱ�Ž��г�ʼ��
		int playTimeRunSign;						
		//��ʱ���߳�����ʱ�Ž��г�ʼ��
		int timeRunSign;
		//�߳�ID
		pthread_t playTimePthreadID;
		//�߳�ID
		pthread_t timePthreadID;	
		int adverCount;
		//����״̬
		int phoneState;				
		//�绰�����״̬
		CPhoneState cPhoneState;	
		Advertisement *adverObjs;

        //��call
		MediaCall	m_mediaCall;	
		/*
			majorVideoType �Ƕ������������Ե�,����ֵ����
			
			0: �ر�����Ƶ�Ĳ���
			1: ��ͬ���ķ�ʽ������Ƶ����
			2: ���첽�ķ�ʽ������Ƶ����
		*/
		int majorVideoType;
		/*
			AudioType �Ƕ���Ƶ���Ե�,����ֵ����

			0: �ر�����Ƶ�Ĳ���
			1: ��ͬ���ķ�ʽ������Ƶ����
			2: ���첽�ķ�ʽ������Ƶ����
		*/
		int AudioType;

		char buf[100];

		pthread_mutex_t m_mutex;	//����Ŀ�ֲ���

		static bool bReadPlayFile;
		static bool bReadDefaultJpeg;

	public:
		AdvertisementMan(int adCount, Area *areas);
		~AdvertisementMan();

		static bool initInstance(int adCount, Area *areas);
		static bool uninitInstance();
		static AdvertisementMan *getInstance();

		bool setPhoneState(int state, unsigned int majorState, unsigned int minorState);	//״̬�ı�֪ͨ
		bool mediaCallNotic(MediaCall mCall);
		bool disposeF2();

		//���ݲ�ͬ��majorVideoTypeֵ����Ӧ��ͣ������, �˺���������Ƶ����stop, ���ֻͣһ����Ҫ�ر���
		bool stopMajorPlayer();

		void doplayerTimethd();

		static void *playerTimeThread(void *pData);		//ʱ���߳�(ֻ��һ�������߳�)
};


#endif
