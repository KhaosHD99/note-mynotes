/*
* Copyright 广州泛网视讯有限公司
* All rights reserved.
* 
* 文件名称：Advertisement.cpp
* 
* 摘    要：对时间表的读取与分析
* 
* 作    者：吴耀泉
*
* 修改者:   徐镇杰
* 
* 最后修改日期：2010年11月11日
*/
#include "Advertisement.hpp"

const char ROLL_TEXT[3][128] = 
{
	"珠江经济台24周年台庆",
	"粤韵珠江中国广播最有价值声音",
	"风华正茂廿四载 声音铸造力量 创新成就未来"
};

#if 1
const char STATE_INFO[5][32]=
{	
	"ON_HOOK",
	"DIALING",
	"RINGING",
	"NOVIDEO",
	"VIDEO",
};
#endif

const char FLIE_TYPE[3][32]=
{	
	"H264",
	"JPG",
	"ONLINE"
};

/* ************************************************************************************************
                                                                            Advertisement
**************************************************************************************************/
Advertisement::Advertisement()
{
	
}

Advertisement::~Advertisement()
{
	
}

int Advertisement::init_advertisement()
{	
	currentEndTime = 0;
	memset(&actInfo, 0, sizeof(ACTINFO_AND_STOPTIME));
	
	return 0;
}

/* ************************************************************************************************
                                                                 Advertisement Manager
**************************************************************************************************/
AdverManager::AdverManager()
{
	if(init_adver_manager())
		showWarning("Init Class AdverManager Error\n");
}

AdverManager::~AdverManager()
{
    pthread_mutex_destroy(&mutex);
	uninit_adver_manager();
}

int AdverManager::init_adver_manager()
{	
    phoneState = CCST::ON_HOOK;
	phoneStateDirty = -1;
	roll_text_play_pos = 0;
	cur_play_type = (FileSwitch)-1;
	pthread_mutex_init (&mutex, NULL);
			
	/* Init Adver Obj */
	adverObjs = new Advertisement*[MAX_ADVER_AREAS];
	for(int i = 0; i < MAX_ADVER_AREAS; i++)
		adverObjs[i] = new Advertisement;
	
    /* Roll Text */
	int i = 0;
	xmlChar *roll_text = NULL;
	xmlNodePtr roll_text_element = NULL;
	xmlNodePtr root_element = NULL;
	
	memset(ROLL_TEXT_LIST, 0, sizeof(ROLL_TEXT_LIST));
	root_element = xml_read_root_node(AD_ROLL_TEXT_SCHEME_FILE);
	if(!root_element)
	{
		showWarning("Read Root Element Fail\r\n");
		return -1;
	}
	
	roll_text_element = xml_read_child_node(root_element);
	if(!roll_text_element)
	{	
		showWarning("Read Element Fail\r\n");
		return -1;
	}
		
    i = 0;
	while(roll_text_element)
	{	
		roll_text = xml_read_attribute_value(roll_text_element, BAD_CAST "text");
		strcpy(ROLL_TEXT_LIST[i], (char *)roll_text);
		
		if(MAX_ROLL_TEXT_COUNT - 1 == i)
			break;
		
		i++;
		roll_text_element = xml_read_brother_node(roll_text_element);
	}	
	
	i = 0;
	while(ROLL_TEXT_LIST[i][0] != 0)
	{	
		showInfo("ROLL_TEXT_LIST %d, text: %s, strlen: %d\n", i, ROLL_TEXT_LIST[i], strlen((char *)ROLL_TEXT_LIST[i]));
		if(MAX_ROLL_TEXT_COUNT - 1 == i)
			break;
		i++;
	}
	free_xml_parser();

	return 0;
}

void AdverManager::uninit_adver_manager()
{
	for(int i = 0; i < MAX_ADVER_AREAS; i++)
	{
		if(adverObjs[i])
			delete(adverObjs[i]);
		adverObjs[i] = NULL;
	}
	delete adverObjs;
	adverObjs = NULL;
}

/* ************************************************************************************************
				                           			       Single Instance
**************************************************************************************************/
AdverManager* AdverManager::adver_manager_instance = NULL;
AdverManager* AdverManager::get_instance()
{
	if(!adver_manager_instance)
		adver_manager_instance = new AdverManager;
	
	return adver_manager_instance;
}

FileSwitch AdverManager::get_current_play_type()
{
	return cur_play_type;
}

/* ************************************************************************************************
                  Desc:  Play Adver Thread
**************************************************************************************************/
void* AdverManager::play_adver_thread(void *p_data)
{
    sem_init(&timeSem, 0, 0);
	run_sign = 1;
	play_adver();
}

void AdverManager::play_adver()
{
    struct timeval tv;
	timespec sp;
	char img_path[128];
	char video_path[128];
	
	#if 1
	/* Play Adver Loop */
    while(run_sign)
    {
	    gettimeofday (&tv , NULL);
		
		/* Check State Change*/
		if(phoneStateDirty != phoneState)
  		{		
			/*phoneStateDirty = phoneState;
			for(int i = 0; i < MAX_ADVER_AREAS; i++)
				memset(adverObjs[i], 0, sizeof(Advertisement));*/
		}
		
		/* Validate Phone State*/
		pthread_mutex_lock(&mutex);
		if(phoneState < 0)
		{
			showDebug("Invalid Phone State\n");
			return;
        }
		else
		{
			showDebug("Phone State: %s\n", state_enum_to_str(phoneState));
			gettimeofday (&tv , NULL);
			
			/* Area Loop */
			for(int i = 0; i < MAX_ADVER_AREAS; i++)
			{
	            //初始化adver 对象
				if(adverObjs[i]->actInfo.szActName == 0)
					is_new_fish = YES;
				else
					is_new_fish = NO;

				
				/* Get System Time*/
				time_t timep;
				struct tm *t;
				
				time(&timep);
				t = localtime(&timep);
				if (t == NULL)
				{
					showWarning("Get time error\n");
					return;
				}
				int systime = (3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec);

				adverObjs[i]->currentEndTime--;
				//showDebug("Phone Area: %s, Adver Main File: %s: Current End Time: %d\n", area_enum_to_str(i), 
				//                                                                         adverObjs[i]->actInfo.szMainFileName,
				// 												                         adverObjs[i]->currentEndTime);
				
                /* ************************************************************************************************
                                                                                                   Real Time Detect
				**************************************************************************************************/
				if((i + 1) == MAJOR_DISPLAY_AREA_NUM)
				{	
					if(phoneState == CCST::VIDEO_CONN)
					{
						showDebug("Stop Main Area\n");
						is_main_area_available = NO;
					}
					else
						is_main_area_available = YES;
				}
				
				#if 1
				if((i + 1) == MAJOR_DISPLAY_AREA_NUM
					&& phoneState != CCST::ON_HOOK
					&& (get_current_play_type() == actFtH264))
				{
					is_has_change_privi = YES;
				}
				else
					is_has_change_privi = NO;
				#endif
				
				/* ************************************************************************************************
                                                                                                 Change Adver Area
				**************************************************************************************************/
				if ((adverObjs[i]->actInfo.endTime < systime)
					 ||(adverObjs[i]->currentEndTime < PLAY_ADVER_EXPIRE_TIME) 
					 ||is_new_fish == YES 
					 || is_has_change_privi == YES
					)
				{
					#if 1
					while(1)
					{
						if (!GetActName::get_instance()->get_current_act_name(i, phoneState, &(adverObjs[i]->actInfo)))
						{
							showWarning("Get Act Error\n");
							continue;
						}
						
						/*showInfo("%s curState: %s, oldState: %s, File Type: %s, Hot State: %d\n", __FUNCTION__, 
																						  STATE_INFO[phoneState], 
																						  STATE_INFO[phoneStateDirty],
																						  FLIE_TYPE[adverObjs[i]->actInfo.filetype],
																						  is_hot_state);*/
						
						if(phoneState != CCST::ON_HOOK &&
						   adverObjs[i]->actInfo.filetype == actFtH264)
						{	
							showInfo("Not Suitable Play Type: %s\n", FILE_TYPE_INFO[adverObjs[i]->actInfo.filetype]);
							continue;
						}
						
						if(phoneState == CCST::ON_HOOK &&
						   adverObjs[i]->actInfo.filetype == actFtH264 &&
						   is_hot_state == YES)
						{
							if(phoneStateDirty == CCST::NOVIDEO_CONN ||
    						   phoneStateDirty == CCST::VIDEO_CONN ||
    						   phoneStateDirty == CCST::DIALING)
							{
								/*showInfo("%s CONN to ON_HOOK, Not Suitable Play Type: %s\n", __FUNCTION__, 
																						 	 FILE_TYPE_INFO[adverObjs[i]->actInfo.filetype]);
								*/
								continue;
							}
							
						}

						if((i + 1) == MAJOR_DISPLAY_AREA_NUM)
							is_hot_state = NO;
						break;
					}
					#endif
					
					adverObjs[i]->currentEndTime = adverObjs[i]->actInfo.PlayTime;
					showDebug("Phone Area: %s, Adver Main File: %s: Current End Time: %d\n", area_enum_to_str(i), 
				                                                                       		 adverObjs[i]->actInfo.szMainFileName,
				 										                                     adverObjs[i]->currentEndTime);
					
					#if 1
					/*Main Area */
					if((i + 1) == MAJOR_DISPLAY_AREA_NUM && is_main_area_available == YES)
					{		
						if(phoneState == CCST::ON_HOOK ||
						   phoneState == CCST::DIALING ||
						   phoneState == CCST::RINGING ||
						   phoneState == CCST::NOVIDEO_CONN)
						{	
							switch(adverObjs[i]->actInfo.filetype)
							{		
								case actAdOnLine:
									showDebug("Main area is actAdOnLine \n");
									break;
									
								case actFtJpeg:
									sprintf(img_path, "%s%s", IMAGE_PATH_PREFIX, adverObjs[i]->actInfo.szMainFileName);
		                            if(change_area_player_info(i, 
																img_path, 
																IMAGE, 
																NULL, 
																adverObjs[i]->actInfo.PlayTime * 1000))
										showError("State: %s, Change Area %d Error\n", state_enum_to_str(phoneState), 
																					   i+1);
									
									break;
										
								case actFtH264:
									if(adverObjs[i]->actInfo.szMainFileName[0] != 0)
									{	
									 	sprintf(video_path, "%s%s", VIDEO_PATH_PREFIX, adverObjs[i]->actInfo.szMainFileName);
										if(change_area_player_info(i, 
																video_path, 
																VIDEO, 
																NULL, 
																adverObjs[i]->actInfo.PlayTime * 1000))
											showError("State: %s, Change Area %d Error\n", state_enum_to_str(phoneState), 
																					   i+1);
									}
									break;

								default:
									showWarning("State: %s, Area %d, Invalid play file type\n", state_enum_to_str(phoneState), 
																					 			i + 1);
							}
	                        continue;
						}
					}
					
					//Roll Text
					if((i + 1) == ROLL_TEXT_AREA_NUM)
					{	
						//chang to actFtJpeg
						if(adverObjs[i]->actInfo.filetype == actFtJpeg)
						{
							sprintf(img_path, "%s%s", IMAGE_PATH_PREFIX, adverObjs[i]->actInfo.szMainFileName);
                      		if(change_area_player_info(i,
													   img_path,
													   IMAGE,
													   ROLL_TEXT_LIST[roll_text_play_pos],
													   adverObjs[i]->actInfo.PlayTime * 1000))
													
								showError("State: %s, Change Area %d Error\n", state_enum_to_str(phoneState), 
																			   i+1);

							if(roll_text_play_pos == MAX_ROLL_TEXT_COUNT - 1)
						  		roll_text_play_pos = 0;
							
							roll_text_play_pos++;
						  	
						}
            			continue;
					}
					
					switch(adverObjs[i]->actInfo.filetype)
					{		
						case actAdOnLine:
							break;
						
						case actFtJpeg:
							sprintf(img_path, "%s%s", IMAGE_PATH_PREFIX, adverObjs[i]->actInfo.szMainFileName);
					    	if(change_area_player_info(i, 
													   img_path, 
													   IMAGE, 
													   NULL, 
													   adverObjs[i]->actInfo.PlayTime * 1000))
								showError("State: %s, Change Area %d Error\n", state_enum_to_str(phoneState), 
																			   i+1);
							break;
								
						case actFtH264:
							break;

						default:
							showWarning("State: %s, Area %d, Invalid play file type\n", state_enum_to_str(phoneState), 
																					 	i + 1);
					}
					#endif
				}	
				
			}
			/* End Area Loop */
		}
		/* End Validate Phone State*/
		pthread_mutex_unlock(&mutex);
		
		printf("\n");
	    sp.tv_sec = tv.tv_sec + 1;
		sp.tv_nsec = tv.tv_usec * 1000;
		sem_timedwait(&timeSem, &sp);
	}
	/* End Play Adver Loop */
	#endif
}

int AdverManager::chage_state(int current_state, int old_state)
{
	for(int i = 0; i < MAX_ADVER_AREAS; i++)
		memset(adverObjs[i], 0, sizeof(Advertisement));
	
	phoneState = current_state;
	phoneStateDirty = old_state;
	is_hot_state = YES;

	sem_post(&timeSem);
}


/* ************************************************************************************************
				                                     Simulate Change State
**************************************************************************************************/
void *AdverManager::simulateChangeState(void *pData)
{
    #if 0
    int i = 0;
    int state[5];
	
	state[0] = FNC_STATE_RING;
	state[1] = FNC_STATE_OFFHOOK;
	state[2] = FNC_STATE_ONHOOK;
	state[3] = FNC_STATE_APP;
	state[4] = FNC_STATE_CONN;
	
    while(1)
    {
		usleep(2000 * 1000);
		
		pthread_mutex_lock(&mutex);
        phoneState = state[i];
        if(i == 4)
			i = 0;
		
		i++;
		pthread_mutex_unlock(&mutex);

		sem_post(&timeSem);
	}
	#endif
}

/* ************************************************************************************************
				                                        enum
**************************************************************************************************/
const char* AdverManager::state_enum_to_str(int enum_val)
{
    switch(enum_val)
	{
	    case CCST::ON_HOOK:
			return "ON_HOOK";
			break;
		case CCST::DIALING:
			return "DIALING";
			break;
		case CCST::RINGING:
			return "RINGING";
			break;
		case CCST::NOVIDEO_CONN:
			return "NOVIDEO_CONN";
			break;
		case CCST::VIDEO_CONN:
			return "VIDEO_CONN";
			break;
	}
	showWarning("Invalid Stete Type Enum Value.\n");
	
	return "NULL";
}
const char* AdverManager::area_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
		case PLAY_AREA_1:
			return "PLAY_AREA_1";
			break;
		case PLAY_AREA_2:
			return "PLAY_AREA_2";
			break;
		case PLAY_AREA_3:
			return "PLAY_AREA_3";
			break;
		case PLAY_AREA_4:
			return "PLAY_AREA_4";
			break;
		case PLAY_AREA_5:
			return "PLAY_AREA_5";
			break;
	}
	showWarning("Invalid Area Type Enum Value.\n");
	
	return "NULL";
}

