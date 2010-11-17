#ifndef _ADVERTISEMENT_H_
#define _ADVERTISEMENT_H_
#include "GuiWnd.hpp"
#include "StdCtrl.hpp"
#include "TimeListResolver.hpp"
#include "Config.h"
#include "AppIMediaPlayerMng.h"


const int phoneStateNum			= 7;


class Advertisement;

//线程用的结构
struct PlayTimeThreadData
{
	Advertisement *pAdvertisement;
	int num;
};


//用来显示图片的窗口
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
		pthread_t adPthreadID;				//线程ID

		AdvertisementWnd *wnd;				//图片显示窗口
		unsigned short *imageBuf;
		bool imageBufIsDirty;

		unsigned int currentProgramID;		//当前正在播放的节目ID
		int currentEndTime;					//当前正在播放的节目要结束的时间
		ACTINFO_AND_STOPTIME actInfo;

	public:
		Advertisement();
		~Advertisement();

		bool init(int x, int y, int width, int height, int wintype);
};


struct CPhoneState
{
	unsigned int uCurMajorState;//主状态
	//unsigned int uCurMinorState;//副状态
};


struct MediaCall
{
	MCALL_TYPE			mCallPlayType;	//彩call的内容
	PLAY_AREA			mCallPlayArea;	//彩call要占用的区域
	MCALLPLAY_ACTION	mCallState;		//彩call的的状态,0表示关闭,1表示打开
};

class AdvertisementMan
{
	private:
		int m_nNotice;
		static AdvertisementMan *instance;
	public:
		//在时间线程启动时才进行初始化
		sem_t timeSem;				                 
		//在时间线程启动时才进行初始化
		int playTimeRunSign;						
		//在时间线程启动时才进行初始化
		int timeRunSign;
		//线程ID
		pthread_t playTimePthreadID;
		//线程ID
		pthread_t timePthreadID;	
		int adverCount;
		//广告的状态
		int phoneState;				
		//电话本身的状态
		CPhoneState cPhoneState;	
		Advertisement *adverObjs;

        //彩call
		MediaCall	m_mediaCall;	
		/*
			majorVideoType 是对主播放区而言的,具体值如下
			
			0: 关闭了视频的播放
			1: 以同步的方式打开了视频播放
			2: 以异步的方式打开了视频播放
		*/
		int majorVideoType;
		/*
			AudioType 是对音频而言的,具体值如下

			0: 关闭了音频的播放
			1: 以同步的方式打开了音频播放
			2: 以异步的方式打开了音频播放
		*/
		int AudioType;

		char buf[100];

		pthread_mutex_t m_mutex;	//读节目分步锁

		static bool bReadPlayFile;
		static bool bReadDefaultJpeg;

	public:
		AdvertisementMan(int adCount, Area *areas);
		~AdvertisementMan();

		static bool initInstance(int adCount, Area *areas);
		static bool uninitInstance();
		static AdvertisementMan *getInstance();

		bool setPhoneState(int state, unsigned int majorState, unsigned int minorState);	//状态改变通知
		bool mediaCallNotic(MediaCall mCall);
		bool disposeF2();

		//根据不同的majorVideoType值来相应地停播放器, 此函数是音视频都会stop, 如果只停一个就要特别处理
		bool stopMajorPlayer();

		void doplayerTimethd();

		static void *playerTimeThread(void *pData);		//时间线程(只有一个这种线程)
};


#endif
