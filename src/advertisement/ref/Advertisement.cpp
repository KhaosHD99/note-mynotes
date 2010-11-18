#include "PlayHead.h"
#include "Advertisement.h"
#include "TimeListResolver.hpp"
#include "jpegDec.h"
#include "jpegEnc.h"
#include "AppConfigDef.h"
#include "PlayerReceiver.h"

char cDefaultJPEG[] = 
{
	#include "defaultJPEG.txt"
};

//******************************广告窗口************************//
AdvertisementWnd::AdvertisementWnd(int x, int y, int width, int height):GuiWnd(x, y, width, height)
{
	bgDefaultImg = new TJpegXMLImage(this, 0, 0);
	bgImage = new TJpegBgImage(this, 0, 0);
	//this->setColor(RGB565(0, 0, 1));
	this->show();
}

AdvertisementWnd::~AdvertisementWnd()
{

}

//******************************广告区域************************//
Advertisement::Advertisement()
{
	currentProgramID = 0;
	memset(&actInfo, 0, sizeof(actInfo));
}

Advertisement::~Advertisement()
{
	wnd->close();				//关闭窗口
	delete []imageBuf;
	imageBuf = NULL;
}

bool Advertisement::init(int x, int y, int width, int height, int wintype)
{
	this->windowType = wintype;
	currentEndTime = 0;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	imageBufIsDirty = false;
	wnd = new AdvertisementWnd(x, y, width, height);
	wnd->bgImage->width = width;
	wnd->bgImage->height = height;

	if (!wnd)
	{
		showWarning("init Advertisement error.\n");
		return false;
	}
	imageBuf = new unsigned short[width * height + 8];
	if (!imageBuf)
	{
		showWarning("alloc imageBuf memory error.\r\n");
	}
	return true;
}

AdvertisementMan *AdvertisementMan::instance = NULL;
bool AdvertisementMan::bReadPlayFile = false;
bool AdvertisementMan::bReadDefaultJpeg = false;

bool AdvertisementMan::initInstance(int adCount, Area *areas)
{
	if (instance == NULL)
	{
		instance = new AdvertisementMan(adCount, areas);
		if (!instance)
		{
			return false;
		}
	}
	return true;
}

bool AdvertisementMan::uninitInstance()
{
	delete instance;
	instance = NULL;
	return true;
}

AdvertisementMan *AdvertisementMan::getInstance()
{
	return instance;
}

AdvertisementMan::AdvertisementMan(int adCount, Area *areas)
{
	m_nNotice = 0;
	adverObjs = NULL;
	pthread_mutex_init (&m_mutex, NULL);               //初始化锁
	phoneState = -1;
	m_mediaCall.mCallPlayArea = AREA_A;
	m_mediaCall.mCallPlayType = PIC_ONLY;
	m_mediaCall.mCallState = ACTION_STOP;

	this->adverCount = adCount;
	adverObjs = new Advertisement[adCount];
	
	CMediaPlayerMng::initInstance(PlayerRect(areas[0].x, areas[0].y, areas[0].width, areas[0].height),
		PlayerRect(areas[2].x, areas[2].y, areas[2].width, areas[2].height),CAdvPlayClient::getInstance()->getVialSys(), FN_ADVPLAY_MODULE_ID);

	for (int i = 0; i < adCount; i++)
	{
		// 初始化adver
		adverObjs[i].init(areas[i].x, areas[i].y, areas[i].width, areas[i].height, i);
	}
}

AdvertisementMan::~AdvertisementMan()
{
	CMediaPlayerMng::uninitInstance();
	pthread_mutex_destroy(&m_mutex);
	delete []adverObjs;
	adverObjs = NULL;
}

bool AdvertisementMan::setPhoneState(int state, unsigned int majorState, unsigned int minorState)
{
	int nRet = 0;
	showInfo("处理状态.广告状态：[%d] 主状态：[%08X]\n",state, majorState);
	pthread_mutex_lock(&m_mutex);
	if (cPhoneState.uCurMajorState == majorState)
	{
		pthread_mutex_unlock(&m_mutex);
		showInfo("处理状态失败，状态和现有状态相同 %08X.\n", cPhoneState.uCurMajorState);
		return true;
	}
	phoneState = state;
	
	//if (!CMediaPlayerMng::getInstance()->stopMajorVNAply(FN_ADVPLAY_MODULE_ID))
	//{
	//	showWarning("关闭主播放区音视频失败.\n");
	//}
	cPhoneState.uCurMajorState = majorState;
	//cPhoneState.uCurMinorState = minorState;
	stopMajorPlayer();
	
	//关闭彩call 
	m_mediaCall.mCallState = ACTION_STOP;
	
	for (int i = 0; i < adverCount; i++)
	{
		adverObjs[i].currentEndTime = 0;
	}

	if (majorState & FNC_STATE_RING)
	{
		showDebug("开始处理来电...\n");

		LOCALAPPCONFIG *localConfig = new LOCALAPPCONFIG;
		
		nRet = readAppConfig(localConfig, sizeof(LOCALAPPCONFIG));
		if (nRet != 0)
		{
			showWarning("读取系统配置失败.\n");
		}
		char ringFile[64] = {0};
		sprintf(ringFile, "%s", localConfig->szRingFile);
		//调整音量为响铃音量
		CMediaPlayerMng::getInstance()->setVolumeValue(localConfig->nRingVolumn, localConfig->nRingVolumn);

		delete localConfig;
		CMediaPlayerMng::getInstance()->startAply(ringFile, FN_ADVPLAY_MODULE_ID);
		AudioType = 2;
		showInfo("------------------------------------startAply来电铃声.\n");
	}
	pthread_mutex_unlock(&m_mutex);
	m_nNotice = 1;
	sem_post(&timeSem);
	return true;
}

bool AdvertisementMan::mediaCallNotic(MediaCall mCall)
{
	pthread_mutex_lock(&m_mutex);
	m_mediaCall = mCall;

	for (int i = 0; i < adverCount; i++)
	{
		adverObjs[i].currentEndTime += 1;
	}
	if (mCall.mCallState == 0)
	{
		adverObjs[mCall.mCallPlayArea].currentEndTime = 0;
	}
	pthread_mutex_unlock(&m_mutex);
	sem_post(&timeSem);
	return true;
}

bool AdvertisementMan::disposeF2()
{
	if (!(cPhoneState.uCurMajorState & ~(FNC_STATE_NORMAL | FNC_STATE_ONHOOK)))
	{
		if (adverObjs[0].actInfo.szAddImageFileName[0] != 0)
		{
			adverObjs[0].wnd->bgImage->loadBgImage(adverObjs[0].actInfo.szAddImageFileName, adverObjs[0].width, adverObjs[0].height);
			//CMediaPlayerMng::getInstance()->stopMajorVNAply(FN_ADVPLAY_MODULE_ID);
			stopMajorPlayer();
			adverObjs[0].wnd->show();
			adverObjs[0].actInfo.szAddImageFileName[0] = 0;
		}
		return true;
	}
	return false;
}

bool AdvertisementMan::stopMajorPlayer()
{
	showInfo("当前节目类型 majorVideoType %d AudioType %d\r\n", majorVideoType, AudioType);
	if (majorVideoType == 1 && AudioType == 1)
	{
		if(!CMediaPlayerMng::getInstance()->stopMajorVNAply(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("关闭主播放区音视频失败.(音视频同步播放)\n");
			return false;
		}
		majorVideoType = 0;
		AudioType = 0;
		showWarning("关闭主播放区音视频成功.(音视频同步播放)\n");
	}
	else if (majorVideoType == 2 && AudioType == 2)
	{
		if(!CMediaPlayerMng::getInstance()->stopMajorVPly(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("关闭主播放区视频失败.(音视频异步播放)\n");
			return false;
		}
		showWarning("关闭主播放区视频成功.(音视频异步播放)\n");
		if(!CMediaPlayerMng::getInstance()->stopAply(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("关闭主播放区音频失败.(音视频异步播放)\n");
			return false;
		}
		showWarning("关闭主播放区音频成功.(音视频异步播放)\n");
		majorVideoType = 0;
		AudioType = 0;
	}
	else if (majorVideoType == 2 && AudioType == 0)
	{
		if(!CMediaPlayerMng::getInstance()->stopMajorVPly(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("关闭主播放区音视频失败.(单视频播放)\n");
			return false;
		}
		showWarning("关闭主播放区音视频成功.(单视频播放)\n");
		majorVideoType = 0;
	}
	else if (majorVideoType == 0 && AudioType == 2)
	{
		if(!CMediaPlayerMng::getInstance()->stopAply(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("关闭主播放区音视频失败.(单音频播放)\n");
			return false;
		}
		showWarning("关闭主播放区音视频成功.(单音频播放)\n");
		AudioType = 0;
	}
	return true;
}

//这个线程是一秒钟一次的
void *AdvertisementMan::playerTimeThread(void *pData)
{
	AdvertisementMan *pObj = (AdvertisementMan*)pData;
	sem_init(&pObj->timeSem, 0, 0);
	pObj->playTimeRunSign = 1;
	
	pObj->doplayerTimethd();
	
	sem_destroy(&pObj->timeSem);
	return NULL;
}

void AdvertisementMan::doplayerTimethd()
{
	int i , j;
	time_t  timep;
	struct  tm  *p;

	char *pImage = NULL;

	struct timeval tv;
	struct timezone tz;
	timespec sp;
	int nYieldArea[4] = {0};

	while(playTimeRunSign)
	{
		memset(nYieldArea, 0, sizeof(nYieldArea)); 
		if(m_nNotice)
		{
			showInfo("广告状态 %d 处理.\n", phoneState);
		}
		gettimeofday (&tv , &tz);
		pthread_mutex_lock(&m_mutex);
		if (!AdvertisementMan::bReadPlayFile)
		{
			if (!GetActName::getInstance()->readPlayAct())
			{
				showInfo("读取时间表文失败.\n");
				if (!bReadDefaultJpeg)
				{
					//读取在代码里的图片
					showDebug("打开default 图片.\n");
					int nLen = sizeof(cDefaultJPEG);
					for (i = 0; i< adverCount; i++)//指广告区域数量
					{
						if (adverObjs[i].wnd->bgDefaultImg->loadXMLImage(cDefaultJPEG, 
							nLen, 
							adverObjs[i].wnd->getWidth(), 
							adverObjs[i].wnd->getHeight()) == -1)
						{
							showDebug("loadXMLImage default image  error.area:[%d] cDefaultJPEG:[%08x] widht:[%d] height:[%d] len:[%d] \n"
								, i, (unsigned int)cDefaultJPEG, adverObjs[i].wnd->getWidth(), adverObjs[i].wnd->getHeight(), nLen);
						}
					}
					for (i = 0; i<adverCount; i++)
					{
						//adverObjs[i].wnd->bringToFront();
						adverObjs[i].wnd->bgDefaultImg->repaint();
						adverObjs[i].wnd->show();
					}
					bReadDefaultJpeg = true;
				}
				AdvertisementMan::bReadPlayFile = false;
				goto CONTINUE;
			}
			else
			{
				showInfo("读取时间表文件成功.\n");
				AdvertisementMan::bReadPlayFile = true;
				bReadDefaultJpeg = true;
			}
		}
		if (phoneState != -1)
		{
			for (i = 0; i<adverCount; i++)
			{
				//获取当前时间
				time(&timep);
				p = localtime(&timep);

				//showInfo("开始节目处理 %d.\n", i);

				//指的是彩CALL
				//////////////////////////////////////让出播放区////////////////////////////
				if (cPhoneState.uCurMajorState & FNC_STATE_RING
					&& m_mediaCall.mCallPlayArea == i 
					&& m_mediaCall.mCallState == ACTION_START
					&& m_mediaCall.mCallPlayType != AUD_ONLY)
				{
					if (i == 0)
					{
						//关闭 1 号窗口的视频播放
						CMediaPlayerMng::getInstance()->stopMajorVPly(FN_VIDEOCONN_MODULE_ID);
						majorVideoType = 0;
					}
					else if (i == 2)
					{
						//关闭 3 号窗口的视频播放
						CMediaPlayerMng::getInstance()->stopMinorVply(FN_VIDEOCONN_MODULE_ID);
					}
					continue;
				}

				//让出主窗口和音频播放
				if (i == 0)
				{
					//if ((cPhoneState.uCurMajorState == FNC_STATE_APP) 
					//	|| (cPhoneState.uCurMajorState == FNC_STATE_CONN 
					//		&& cPhoneState.uCurMinorState == FNC_SUB_STATE_VIDEOCONN))

					if ((cPhoneState.uCurMajorState & FNC_STATE_APP) 
						&& ((cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_MEDIA) != FNCOM_STATE_STREAMING_AUDIO)
						|| (cPhoneState.uCurMajorState & FNC_STATE_APP) 
						&& !(cPhoneState.uCurMajorState & FNCOM_STATE_NORMAL) 
						&& ((cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_MEDIA) == FNCOM_STATE_STREAMING_AUDIO)
						|| (cPhoneState.uCurMajorState & FNCOM_STATE_VIDEO_CONN)
						|| ((cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_MEDIA) == FNCOM_STATE_STREAMING_MEDIA)
						|| (cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_VIDEO)
						)
					{
						nYieldArea[i] = 1;
						//showInfo("进入了应用处理 %d. %08X\n", i, cPhoneState.uCurMajorState);
						//关闭音、视频
						if(adverObjs[i].actInfo.filetype == actAdOnLine)
						{
							adverObjs[i].actInfo.filetype = actFtJpeg;
						}
						if (adverObjs[i].actInfo.filetype == actFtH264 &&
							adverObjs[i].actInfo.szMainFileName[0] != 0)
						{
							if (stopMajorPlayer())
							{
								adverObjs[i].actInfo.filetype = actFtJpeg;
							}
						}
						continue;
					}
					//lnj update
					if(m_nNotice)
					{
						showInfo("主播放区广告状态 %d 处理.\n", phoneState);			
					}
					if(cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_AUDIO)
					{	
						adverObjs[i].actInfo.szMusicFileName[0] = 0;
						//CMediaPlayerMng::getInstance()->stopAply();
					}
				}
				/////////////////////////////////////////////////////////////////////////////////////

				//待机类广告播放
				adverObjs[i].currentEndTime--;

				if ((adverObjs[i].actInfo.endTime < p->tm_hour * 3600 + p->tm_min * 60 +  p->tm_sec) ||
					(adverObjs[i].currentEndTime < 1))
				{
					if (i == 0)
					{
						if (!(cPhoneState.uCurMajorState & FNC_STATE_RING))
						{
							stopMajorPlayer();
						}
						else
						{
							//if (CMediaPlayerMng::getInstance()->stopMajorVPly(FN_ADVPLAY_MODULE_ID))
							//{
							//	showDebug("关闭主窗口视频成功.\n");
							//}
							//else
							//{
							//	showDebug("关闭主窗口视频失败.\n");
							//}
						}
					}
					else if (i == 2)
					{
						if (CMediaPlayerMng::getInstance()->stopMinorVply(FN_ADVPLAY_MODULE_ID))
						{
							showDebug("关闭副窗口视频成功.\n");
						}
						else
						{
							showDebug("关闭副窗口视频失败.\n");
						}
					}
					if (!(GetActName::getInstance()->getActName(i, phoneState, &adverObjs[i].actInfo)))
					{
						continue;
					}
					
					adverObjs[i].currentEndTime = adverObjs[i].actInfo.PlayTime;
					
					//如果是响铃状态，把广告音频去掉
					if (cPhoneState.uCurMajorState & FNC_STATE_CONN
						|| cPhoneState.uCurMajorState & FNC_STATE_OFFHOOK
						|| cPhoneState.uCurMajorState & FNC_STATE_RING
						|| cPhoneState.uCurMajorState & FNC_STATE_APP
						|| cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_MEDIA
						)
					{
						adverObjs[i].actInfo.szMusicFileName[0] = 0;
					}

					//showInfo("在主播放区播放新节目 %d\n", i);
					if (adverObjs[i].actInfo.filetype == actAdOnLine)//在线广告
					{
						//激活流媒体应用,但浏览器应用继续保留,在退出流媒体时重回浏览器应用
						if((cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_MEDIA))
						{
							adverObjs[i].actInfo.filetype = actFtJpeg;
							memcpy(adverObjs[i].actInfo.szMainFileName, 
								adverObjs[i].actInfo.szAddImageFileName, 
								sizeof(adverObjs[i].actInfo.szMainFileName));
						}
						else
						{
							CAdvPlayClient *pAdvPlayClient = CAdvPlayClient::getInstance();
							PlayNetMediaReqVial Vial;
							Vial.uSrcModule = FN_ADVPLAY_MODULE_ID;
							Vial.nType = PLAY_NET_MEDIA_TYPE_ADONLINE;
							adverObjs[i].actInfo.szURL[sizeof(adverObjs[i].actInfo.szURL) - 1] = 0;
							strcpy(Vial.szURL, adverObjs[i].actInfo.szURL);							
							adverObjs[i].actInfo.szAddImageFileName[sizeof(adverObjs[i].actInfo.szAddImageFileName) - 1] = 0;
							strcpy(Vial.szAddFile, adverObjs[i].actInfo.szAddImageFileName);
							Vial.nParameter = adverObjs[i].actInfo.PlayTime;
							showInfo("send PlayAdOnLine %d %s\r\n", Vial.nParameter, Vial.szURL);
							pAdvPlayClient->postPlayNetMediaReq(&Vial, FN_COMM_CENTER_MODULE_ID);
							//showInfo("send PlayAdOnLine return %d\r\n", pRetVial->nResult);

							adverObjs[i].actInfo.filetype = actFtJpeg;
							memcpy(adverObjs[i].actInfo.szMainFileName, 
								adverObjs[i].actInfo.szAddImageFileName, 
								sizeof(adverObjs[i].actInfo.szMainFileName));
							continue;
						}
					}
					if (adverObjs[i].actInfo.filetype == actFtJpeg)
					{
						pImage = LoadWithStretchImage(adverObjs[i].actInfo.szMainFileName, adverObjs[i].wnd->getWidth(), adverObjs[i].wnd->getHeight());
						if (!pImage)
						{
							showWarning("LoadWithStretchImage error.\n");
						}
						else
						{
							memcpy(adverObjs[i].imageBuf, pImage, adverObjs[i].wnd->getWidth() * adverObjs[i].wnd->getHeight() * 2 + 16);
							free(pImage);
							pImage = NULL;

							adverObjs[i].wnd->bgImage->loadImage((char *)adverObjs[i].imageBuf, true);
							adverObjs[i].imageBufIsDirty = true;
						}

						//带音频播放的图片文件
						if (i == 0)
						{
							if (adverObjs[i].actInfo.szMusicFileName[0] != 0)
							{
								//带音频的视频播放
								if (!CMediaPlayerMng::getInstance()->startAply(adverObjs[i].actInfo.szMusicFileName, FN_ADVPLAY_MODULE_ID))
								{
									showWarning("打开音频播放失败.\n");
								}
								AudioType = 2;
								showInfo("------------------------------------startAply i:[%d].\n", i);
							}
						}
					}
					else
					{
						//
						//要多加读取失败时就应该读取下一个节目
						//
						if (i == 0)
						{
							if(m_nNotice)
							{
								showInfo("lnj主播放区播放处理 %s\n", adverObjs[i].actInfo.szMusicFileName);			
							}

							if (adverObjs[i].actInfo.szMusicFileName[0] != 0)
							{
								showInfo("lnj主播放区播放处理 %s\n", adverObjs[i].actInfo.szMainFileName);			
								showInfo("-------------------------------enter startMajorVNAply i:[%d].\n", i);
								//带音频的视频播放
								if (!CMediaPlayerMng::getInstance()->startMajorVNAply(
									adverObjs[i].actInfo.szMainFileName,
									adverObjs[i].actInfo.szMusicFileName,
									FN_ADVPLAY_MODULE_ID))
								{
									showWarning("打开带音频的视频播放失败.\n");
								}
								majorVideoType = 1;
								AudioType = 1;
								showInfo("------------------------------------startMajorVNAply i:[%d].\n", i);
							}
							else
							{
								//不带音频的视频播放
								if (!CMediaPlayerMng::getInstance()->startMajorVPly(adverObjs[i].actInfo.szMainFileName, FN_ADVPLAY_MODULE_ID))
								{
									showWarning("打开不带音频的视频播放失败.\n");
								}
								majorVideoType = 2;
								showInfo("------------------------------------startMajorVPly i:[%d].\n", i);
							}
						}
						else if (i == 2)
						{
							showWarning("打开副视频播放.\n");
							if (!CMediaPlayerMng::getInstance()->startMinorVply(adverObjs[i].actInfo.szMainFileName, FN_ADVPLAY_MODULE_ID))
							{
								showWarning("打开副视频播放不成功.\n");
							}
						}						
						adverObjs[i].wnd->hide();
					}
				}
			}
		}

		for (j = 0; j < adverCount; j++)
		{
			if (adverObjs[j].imageBufIsDirty)
			{
				adverObjs[j].wnd->bgImage->repaint();
				if(j == 0)
				{
					//adverObjs[j].wnd->bringToFront();
				}
				adverObjs[j].wnd->show();
				adverObjs[j].imageBufIsDirty = false;
			}
			if(nYieldArea[j])
			{
				adverObjs[j].wnd->hide();
			}
		}
		
CONTINUE:
		pthread_mutex_unlock(&m_mutex);
		
		m_nNotice = 0;
		
		sp.tv_nsec = tv.tv_usec * 1000;
		sp.tv_sec = tv.tv_sec + 1;
		sem_timedwait(&timeSem, &sp);
	}
}

