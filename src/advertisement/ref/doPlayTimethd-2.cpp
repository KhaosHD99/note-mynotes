#define MAJOR_DISPLAY_AREA_NUM 4

//�����������
void doPlayTimethd()
{
    //����״̬��Ч
	if (phoneState < 0)	
	{
		error;
	}
	else
	{
		//����ÿһ������
		for(i = 0; i < MAX_ADVER_AREAS; i++)
		{
			//��ȡϵͳ��ǰʱ��
			time(&timep);
			p = localtime(&timep);
			//��������򲥷�Ȩ��
			if((i + 1) == MAJOR_DISPLAY_AREA_NUM)
			{
				if(phoneState == Ӧ��״̬ || ��ý��״̬ || ��Ƶ��ͨ״̬)
				{
					if(actInfo.filetype == actAdOnLine)
						chang to actFtJpeg;
					if(actInfo.filetype == actFtH264 &&
						actInfo.szMainFileName[0] != 0)
					{
						if(ֹͣ��������)
							chang to actFtJpeg;
					}
					
					continue;
				}
			}
			
			//�������򵹼�ʱ
			//adverObjs[i].currentEndTime--;
			
			//������ϻ��߸տ�ʼ����ʱ����ȡ��һ���������ݲ�����
			if ((adverObjs[i].actInfo.endTime < p->tm_hour * 3600 + p->tm_min * 60 +  p->tm_sec) ||
				(adverObjs[i].currentEndTime < 1))
			{

				//������Ƶ��ͨ��ժ�������塢Ӧ�á���ý��ʱ������������
				if(phoneState == FNC_STATE_CONN 
						|| FNC_STATE_OFFHOOK || FNC_STATE_RING || FNC_STATE_APP || FNCOM_STATE_STREAMING_MEDIA)

				{
					//��������
					adverObjs[i].actInfo.szMusicFileName[0] = 0;
				}
				
				if (actInfo.filetype == actAdOnLine)//���߹��
				{
					//�������߹�棬������ý��Ӧ��
					.....
				}
						
				if (actInfo.filetype == actFtJpeg)
				{
					
				
				}
			
				if (actInfo.filetype == actFtH264)
				{
	
						if(actInfo.szMainFileName[0] != 0)
							//��������Ƶ
						else
							//������Ƶ
				}
			}	
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
ԭ���ų�������߼�
///////////////////////////////////////////////////////////////////////////////////////////////
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
					//ָ�����������
					for (i = 0; i< adverCount; i++)
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






