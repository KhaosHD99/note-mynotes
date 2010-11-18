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

//******************************��洰��************************//
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

//******************************�������************************//
Advertisement::Advertisement()
{
	currentProgramID = 0;
	memset(&actInfo, 0, sizeof(actInfo));
}

Advertisement::~Advertisement()
{
	wnd->close();				//�رմ���
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
	pthread_mutex_init (&m_mutex, NULL);               //��ʼ����
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
		// ��ʼ��adver
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
	showInfo("����״̬.���״̬��[%d] ��״̬��[%08X]\n",state, majorState);
	pthread_mutex_lock(&m_mutex);
	if (cPhoneState.uCurMajorState == majorState)
	{
		pthread_mutex_unlock(&m_mutex);
		showInfo("����״̬ʧ�ܣ�״̬������״̬��ͬ %08X.\n", cPhoneState.uCurMajorState);
		return true;
	}
	phoneState = state;
	
	//if (!CMediaPlayerMng::getInstance()->stopMajorVNAply(FN_ADVPLAY_MODULE_ID))
	//{
	//	showWarning("�ر�������������Ƶʧ��.\n");
	//}
	cPhoneState.uCurMajorState = majorState;
	//cPhoneState.uCurMinorState = minorState;
	stopMajorPlayer();
	
	//�رղ�call 
	m_mediaCall.mCallState = ACTION_STOP;
	
	for (int i = 0; i < adverCount; i++)
	{
		adverObjs[i].currentEndTime = 0;
	}

	if (majorState & FNC_STATE_RING)
	{
		showDebug("��ʼ��������...\n");

		LOCALAPPCONFIG *localConfig = new LOCALAPPCONFIG;
		
		nRet = readAppConfig(localConfig, sizeof(LOCALAPPCONFIG));
		if (nRet != 0)
		{
			showWarning("��ȡϵͳ����ʧ��.\n");
		}
		char ringFile[64] = {0};
		sprintf(ringFile, "%s", localConfig->szRingFile);
		//��������Ϊ��������
		CMediaPlayerMng::getInstance()->setVolumeValue(localConfig->nRingVolumn, localConfig->nRingVolumn);

		delete localConfig;
		CMediaPlayerMng::getInstance()->startAply(ringFile, FN_ADVPLAY_MODULE_ID);
		AudioType = 2;
		showInfo("------------------------------------startAply��������.\n");
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
	showInfo("��ǰ��Ŀ���� majorVideoType %d AudioType %d\r\n", majorVideoType, AudioType);
	if (majorVideoType == 1 && AudioType == 1)
	{
		if(!CMediaPlayerMng::getInstance()->stopMajorVNAply(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("�ر�������������Ƶʧ��.(����Ƶͬ������)\n");
			return false;
		}
		majorVideoType = 0;
		AudioType = 0;
		showWarning("�ر�������������Ƶ�ɹ�.(����Ƶͬ������)\n");
	}
	else if (majorVideoType == 2 && AudioType == 2)
	{
		if(!CMediaPlayerMng::getInstance()->stopMajorVPly(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("�ر�����������Ƶʧ��.(����Ƶ�첽����)\n");
			return false;
		}
		showWarning("�ر�����������Ƶ�ɹ�.(����Ƶ�첽����)\n");
		if(!CMediaPlayerMng::getInstance()->stopAply(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("�ر�����������Ƶʧ��.(����Ƶ�첽����)\n");
			return false;
		}
		showWarning("�ر�����������Ƶ�ɹ�.(����Ƶ�첽����)\n");
		majorVideoType = 0;
		AudioType = 0;
	}
	else if (majorVideoType == 2 && AudioType == 0)
	{
		if(!CMediaPlayerMng::getInstance()->stopMajorVPly(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("�ر�������������Ƶʧ��.(����Ƶ����)\n");
			return false;
		}
		showWarning("�ر�������������Ƶ�ɹ�.(����Ƶ����)\n");
		majorVideoType = 0;
	}
	else if (majorVideoType == 0 && AudioType == 2)
	{
		if(!CMediaPlayerMng::getInstance()->stopAply(FN_ADVPLAY_MODULE_ID))
		{
			showWarning("�ر�������������Ƶʧ��.(����Ƶ����)\n");
			return false;
		}
		showWarning("�ر�������������Ƶ�ɹ�.(����Ƶ����)\n");
		AudioType = 0;
	}
	return true;
}

//����߳���һ����һ�ε�
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
			showInfo("���״̬ %d ����.\n", phoneState);
		}
		gettimeofday (&tv , &tz);
		pthread_mutex_lock(&m_mutex);
		if (!AdvertisementMan::bReadPlayFile)
		{
			if (!GetActName::getInstance()->readPlayAct())
			{
				showInfo("��ȡʱ�����ʧ��.\n");
				if (!bReadDefaultJpeg)
				{
					//��ȡ�ڴ������ͼƬ
					showDebug("��default ͼƬ.\n");
					int nLen = sizeof(cDefaultJPEG);
					for (i = 0; i< adverCount; i++)//ָ�����������
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
				showInfo("��ȡʱ����ļ��ɹ�.\n");
				AdvertisementMan::bReadPlayFile = true;
				bReadDefaultJpeg = true;
			}
		}
		if (phoneState != -1)
		{
			for (i = 0; i<adverCount; i++)
			{
				//��ȡ��ǰʱ��
				time(&timep);
				p = localtime(&timep);

				//showInfo("��ʼ��Ŀ���� %d.\n", i);

				//ָ���ǲ�CALL
				//////////////////////////////////////�ó�������////////////////////////////
				if (cPhoneState.uCurMajorState & FNC_STATE_RING
					&& m_mediaCall.mCallPlayArea == i 
					&& m_mediaCall.mCallState == ACTION_START
					&& m_mediaCall.mCallPlayType != AUD_ONLY)
				{
					if (i == 0)
					{
						//�ر� 1 �Ŵ��ڵ���Ƶ����
						CMediaPlayerMng::getInstance()->stopMajorVPly(FN_VIDEOCONN_MODULE_ID);
						majorVideoType = 0;
					}
					else if (i == 2)
					{
						//�ر� 3 �Ŵ��ڵ���Ƶ����
						CMediaPlayerMng::getInstance()->stopMinorVply(FN_VIDEOCONN_MODULE_ID);
					}
					continue;
				}

				//�ó������ں���Ƶ����
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
						//showInfo("������Ӧ�ô��� %d. %08X\n", i, cPhoneState.uCurMajorState);
						//�ر�������Ƶ
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
						showInfo("�����������״̬ %d ����.\n", phoneState);			
					}
					if(cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_AUDIO)
					{	
						adverObjs[i].actInfo.szMusicFileName[0] = 0;
						//CMediaPlayerMng::getInstance()->stopAply();
					}
				}
				/////////////////////////////////////////////////////////////////////////////////////

				//�������沥��
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
							//	showDebug("�ر���������Ƶ�ɹ�.\n");
							//}
							//else
							//{
							//	showDebug("�ر���������Ƶʧ��.\n");
							//}
						}
					}
					else if (i == 2)
					{
						if (CMediaPlayerMng::getInstance()->stopMinorVply(FN_ADVPLAY_MODULE_ID))
						{
							showDebug("�رո�������Ƶ�ɹ�.\n");
						}
						else
						{
							showDebug("�رո�������Ƶʧ��.\n");
						}
					}
					if (!(GetActName::getInstance()->getActName(i, phoneState, &adverObjs[i].actInfo)))
					{
						continue;
					}
					
					adverObjs[i].currentEndTime = adverObjs[i].actInfo.PlayTime;
					
					//���������״̬���ѹ����Ƶȥ��
					if (cPhoneState.uCurMajorState & FNC_STATE_CONN
						|| cPhoneState.uCurMajorState & FNC_STATE_OFFHOOK
						|| cPhoneState.uCurMajorState & FNC_STATE_RING
						|| cPhoneState.uCurMajorState & FNC_STATE_APP
						|| cPhoneState.uCurMajorState & FNCOM_STATE_STREAMING_MEDIA
						)
					{
						adverObjs[i].actInfo.szMusicFileName[0] = 0;
					}

					//showInfo("���������������½�Ŀ %d\n", i);
					if (adverObjs[i].actInfo.filetype == actAdOnLine)//���߹��
					{
						//������ý��Ӧ��,�������Ӧ�ü�������,���˳���ý��ʱ�ػ������Ӧ��
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

						//����Ƶ���ŵ�ͼƬ�ļ�
						if (i == 0)
						{
							if (adverObjs[i].actInfo.szMusicFileName[0] != 0)
							{
								//����Ƶ����Ƶ����
								if (!CMediaPlayerMng::getInstance()->startAply(adverObjs[i].actInfo.szMusicFileName, FN_ADVPLAY_MODULE_ID))
								{
									showWarning("����Ƶ����ʧ��.\n");
								}
								AudioType = 2;
								showInfo("------------------------------------startAply i:[%d].\n", i);
							}
						}
					}
					else
					{
						//
						//Ҫ��Ӷ�ȡʧ��ʱ��Ӧ�ö�ȡ��һ����Ŀ
						//
						if (i == 0)
						{
							if(m_nNotice)
							{
								showInfo("lnj�����������Ŵ��� %s\n", adverObjs[i].actInfo.szMusicFileName);			
							}

							if (adverObjs[i].actInfo.szMusicFileName[0] != 0)
							{
								showInfo("lnj�����������Ŵ��� %s\n", adverObjs[i].actInfo.szMainFileName);			
								showInfo("-------------------------------enter startMajorVNAply i:[%d].\n", i);
								//����Ƶ����Ƶ����
								if (!CMediaPlayerMng::getInstance()->startMajorVNAply(
									adverObjs[i].actInfo.szMainFileName,
									adverObjs[i].actInfo.szMusicFileName,
									FN_ADVPLAY_MODULE_ID))
								{
									showWarning("�򿪴���Ƶ����Ƶ����ʧ��.\n");
								}
								majorVideoType = 1;
								AudioType = 1;
								showInfo("------------------------------------startMajorVNAply i:[%d].\n", i);
							}
							else
							{
								//������Ƶ����Ƶ����
								if (!CMediaPlayerMng::getInstance()->startMajorVPly(adverObjs[i].actInfo.szMainFileName, FN_ADVPLAY_MODULE_ID))
								{
									showWarning("�򿪲�����Ƶ����Ƶ����ʧ��.\n");
								}
								majorVideoType = 2;
								showInfo("------------------------------------startMajorVPly i:[%d].\n", i);
							}
						}
						else if (i == 2)
						{
							showWarning("�򿪸���Ƶ����.\n");
							if (!CMediaPlayerMng::getInstance()->startMinorVply(adverObjs[i].actInfo.szMainFileName, FN_ADVPLAY_MODULE_ID))
							{
								showWarning("�򿪸���Ƶ���Ų��ɹ�.\n");
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

