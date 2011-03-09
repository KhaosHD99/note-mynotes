#include "AdverModule.h"
//#include "PrompterGui.h"
#include "CCST.hpp"
#include "Advertisement.hpp"
	
/********************************************************************************
                                      					get instance
********************************************************************************/
AdverModule* AdverModule::adverModule_instance = NULL;
AdverModule *AdverModule::get_instance(VialSystem *vialSys)
{	
	if(vialSys == NULL)
	{	
		showWarning("vialSys null, creat prompter module failed!\r\n");
		return NULL;	
	}	
	
	if(!adverModule_instance)
			adverModule_instance = new AdverModule(vialSys);
		
	return adverModule_instance;
}	
	
/**************************************************************
**PrompterModule
**(电话状态)提示模块
**
**************************************************************/
AdverModule::AdverModule(VialSystem *vialSys) : AbstractModule(vialSys)
{
	this->vialSys = vialSys;
}

/**************************************************************
**run
**启动run循环
**
**************************************************************/
void AdverModule::run()
{
	vialSys->run();
}

/**************************************************************
**localInit
**模块内部初始化
**该函数被init()调用
**************************************************************/
bool AdverModule::localInit()
{
	showInfo("%s localInit\n", __CLASS__);
	return true;
}

/**************************************************************
**onExit
**接收状态改变消息
**内部自行处理状态
**************************************************************/
bool AdverModule::onExit()
{
	showInfo("%s onExit\n", __CLASS__);
	return false;
}

bool AdverModule::post_vial(Vial *vial, NodeID dstID)
{
	vialSys->postVial(vial, dstID);
}

/**************************************************************
1.	待机  			[ON_HOOK, NON_PHONE] 				: StateChangeVial
2.	摘机  			[OFF_HOOK, V_PHONE] 				: StateChangeVial
3.	拨出号码		[OFF_HOOK, V_PHONE, 号码] 	: StateDailVial
4.	振铃状态		[RRINGING， V_PHONE]				: StateChangeVial
5.	接听状态		[NOVIDEO_CONN， V_PHONE]		: StateChangeVial

6. 振铃号码			[RINGING, V_PHONE, 号码]		: CallerIDVial 
7. 挂机					[ON_HOOK, NON_PHONE]				: StateChangeVial
8. 互通..  			[VIDEO_CONN, NON_PHONE]			: StateChangeVial
**************************************************************/
bool AdverModule::OnReceive(Vial *vial)
{	
	if (AbstractModule::OnReceive(vial))
	{
		showInfo("%s onReceive , return true\n", __CLASS__);
		return true;
	}
		
	#if 1
	switch (vial->vialType)
	{
		case GETVT(StateChangeVial):		
			return on_vial_state_change((StateChangeVial *)vial);
			
		default:
			showWarning("Can not distiguish vial\n");
			return false;
	}
	#endif
	
	return false;
}

/**************************************************************
						onVialStateChang
**************************************************************/
#if 1
bool AdverModule::on_vial_state_change(StateChangeVial *vial)
{
	if(vial == NULL)
	{	
		printf("Vial is Null\n");
		return false;
	}
	else
	{	
	    #if 1
		AdverManager *adverManager = AdverManager::get_instance();
		
		switch(vial->curState.st)
		{		
			case CCST::ON_HOOK:
				showDebug("curState State: %s\n", STATE_INFO[CCST::ON_HOOK]);
				if(adverManager->phoneState == CCST::ON_HOOK)
				{
					showDebug("Invalid State: ON_HOOK\n");
					return -1;
				}
				return on_on_hook(vial);

			case CCST::DIALING:
				showDebug("curState State: %s\n", STATE_INFO[CCST::DIALING]);
				if(adverManager->phoneState == CCST::DIALING||
				   adverManager->phoneState == CCST::RINGING||
				   adverManager->phoneState == CCST::NOVIDEO_CONN||  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				   adverManager->phoneState == CCST::VIDEO_CONN)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				{
					showDebug("Invalid State: DIALING\n");
					return -1;
				}
				return on_dialing(vial);
				
			case CCST::RINGING:
				showDebug("curState State: %s\n", STATE_INFO[CCST::RINGING]);
				if(adverManager->phoneState == CCST::RINGING ||
				   adverManager->phoneState == CCST::DIALING ||
				   adverManager->phoneState == CCST::NOVIDEO_CONN ||
				   adverManager->phoneState == CCST::VIDEO_CONN)
				{
					showDebug("Invalid State : RINGING\n");
					return -1;
				}
				return on_ringing(vial);
				
			case CCST::NOVIDEO_CONN:
			    showDebug("curState State: %s\n", STATE_INFO[CCST::NOVIDEO_CONN]);
				if( adverManager->phoneState == CCST::NOVIDEO_CONN ||
					adverManager->phoneState == CCST::ON_HOOK ||
					adverManager->phoneState == CCST::VIDEO_CONN)
				{
					showDebug("Invalid State : NOVIDEO_CONN\n");
					return -1;
				}
				return on_novideoconn(vial);
				
			case CCST::VIDEO_CONN:
				showDebug("curState State: %s\n", STATE_INFO[CCST::VIDEO_CONN]);
				if( adverManager->phoneState == CCST::VIDEO_CONN||
					adverManager->phoneState == CCST::ON_HOOK ||
					adverManager->phoneState == CCST::NOVIDEO_CONN)
				{
					showDebug("Invalid State : VIDEO_CONN\n");
					return -1;
				}
				return on_videoconn(vial);
				
			default:
				return false;
		}
	    #endif
	}
}
#endif

/************************************************************************************
									onOnHook 
*************************************************************************************/
bool AdverModule::on_on_hook(StateChangeVial *vial)
{	
	showDebug("%s, stateVal: %d\n", __FUNCTION__, vial->curState);
	AdverManager *adverManager = AdverManager::get_instance();
	
	pthread_mutex_lock(&(adverManager->mutex));
	//adverManager->phoneState = vial->curState.st;
	//adverManager->phoneStateDirty = vial->oldState.st;
	adverManager->chage_state(vial->curState.st, vial->oldState.st);
	pthread_mutex_unlock(&(adverManager->mutex));
	
	sem_post(&(adverManager->timeSem));	
	return true; 
	
    #if 0
	if(vial == NULL)
		return false;
	StateChangeVial *stateChangVial = (StateChangeVial*)vial;	
	
	if(stateChangVial->curState.st != CCST::ON_HOOK)
	{
		showWarning("%s::%s, not on_hook state, stateVal : %d\n", __CLASS__, __FUNCTION__, stateChangVial->curState);
		return false;
	}
	
	PhoneCode.nCallType = 0;
	PhoneCode.nCodelen = 0;
	memset(PhoneCode.cPhoneCode, 0, sizeof(PhoneCode.cPhoneCode));

	showWarning("%s::%s\n", __CLASS__, __FUNCTION__);

    #if 0
	StatePrompterInfo stateinfo;
	memset(&stateinfo, 0, sizeof(stateinfo));
	stateinfo.state = PP_ON_HOOK;
	showInfo("update_prompter_info : %d, %s\r\n", stateinfo.state, stateinfo.message);
	update_prompter_info(&stateinfo);
	#endif
	
	switch(stateChangVial->oldState.st)
	{
	    case CCST::DIALING:
			//结束主叫
			showWarning("%s::%s, end of dail\n", __CLASS__, __FUNCTION__);
			return true;
		case CCST::RINGING:						
			//结束来电振铃
			showWarning("%s::%s, end of ringing\n", __CLASS__, __FUNCTION__);
			return true;
		case CCST::NOVIDEO_CONN:			
			//结束来电接听
			showWarning("%s::%s, end of recv a call\n", __CLASS__, __FUNCTION__);
			return true;
		case CCST::VIDEO_CONN:				
			//结束视频互通(不分主被方)
			showWarning("%s::%s, end of a vphone\n", __CLASS__, __FUNCTION__);
			return true;
		default:
			showWarning("%s::%s, not on_hook state, unprocess oldstate : %d\n", __CLASS__, __FUNCTION__, stateChangVial->oldState);
			return false;
	}
	#endif
}

/**************************************************************
							on_dialing
**************************************************************/
bool AdverModule::on_dialing(StateChangeVial *vial)
{
	showDebug("%s, stateVal: %d\n", __FUNCTION__, vial->curState);
	AdverManager *adverManager = AdverManager::get_instance();

	pthread_mutex_lock(&(adverManager->mutex));
	//adverManager->phoneState = vial->curState.st;
	adverManager->chage_state(vial->curState.st, vial->oldState.st);
	pthread_mutex_unlock(&(adverManager->mutex));
	
	sem_post(&(adverManager->timeSem));	
	return true; 
}

/**********************************************************************************************
						               	onRinging
***********************************************************************************************/
bool AdverModule::on_ringing(StateChangeVial *vial)
{
	showDebug("%s, stateVal: %d\n", __FUNCTION__, vial->curState);

	AdverManager *adverManager = AdverManager::get_instance();
	pthread_mutex_lock(&(adverManager->mutex));
	//adverManager->phoneState = vial->curState.st;
	adverManager->chage_state(vial->curState.st, vial->oldState.st);
	pthread_mutex_unlock(&(adverManager->mutex));
	
	sem_post(&(adverManager->timeSem));	
	return true; 
}

/************************************************************************************************
					                               	onNoVideoConn
*************************************************************************************************/
bool AdverModule::on_novideoconn(StateChangeVial *vial)
{	
	showDebug("%s, stateVal: %d\n", __FUNCTION__, vial->curState);
	AdverManager *adverManager = AdverManager::get_instance();

	pthread_mutex_lock(&(adverManager->mutex));
	//adverManager->phoneState = vial->curState.st;
	adverManager->chage_state(vial->curState.st, vial->oldState.st);
	pthread_mutex_unlock(&(adverManager->mutex));
	
	sem_post(&(adverManager->timeSem)); 
	return true; 
}

/************************************************************************************************
                                                                         onVideoConn
************************************************************************************************/
bool AdverModule::on_videoconn(StateChangeVial *vial)
{	
	showDebug("%s, stateVal: %d\n", __FUNCTION__, vial->curState);
	AdverManager *adverManager = AdverManager::get_instance();

	pthread_mutex_lock(&(adverManager->mutex));
	//adverManager->phoneState = vial->curState.st;
	adverManager->chage_state(vial->curState.st, vial->oldState.st);
	pthread_mutex_unlock(&(adverManager->mutex));
	
	sem_post(&(adverManager->timeSem));	
	return true; 
}

#if 0

#endif
/**************************************************************
**onVialStateDail
**拨号消息
**当且仅当上一状态为OFF_HOOK时，才收到拨号消息
**************************************************************/
#if 0
bool AdverModule::onVialDialNotify(DialNotifyVial *vial)
{
	if(vial)
	{
		PhoneCode.cPhoneCode[PhoneCode.nCodelen] = vial->code;
		if(PhoneCode.nCodelen >= (VIAL_PHONECODE_LEN-1))
		{
			showWarning("phoneCode too long [%d:%d%s]\n", PhoneCode.nCodelen, VIAL_PHONECODE_LEN-1, PhoneCode.cPhoneCode);
			return true;
		}
		PhoneCode.nCodelen++;
		PhoneCode.cPhoneCode[PhoneCode.nCodelen]= '\0';	
		showWarning("%s::%s, phoneCode : %d -> %s\n", __CLASS__, __FUNCTION__, vial->code-'0', PhoneCode.cPhoneCode);
		
        #if 0
		StatePrompterInfo stateinfo;
		memset(&stateinfo, 0, sizeof(stateinfo));
		
		stateinfo.state = PP_OFF_HOOK;
		strncpy(stateinfo.message, PhoneCode.cPhoneCode, PhoneCode.nCodelen);
		stateinfo.message[PhoneCode.nCodelen]= '\0';
		showInfo("update_prompter_info : %d, %s\r\n", stateinfo.state, stateinfo.message);
		update_prompter_info(&stateinfo);
		#endif
		
	}
	else
		showWarning("%s::%s, vial null\n", __CLASS__, __FUNCTION__);
	
	return true;	
}
#endif

/**************************************************************
**onVialCallerID
**来电号码消息
**当且仅当上一状态为RINGRING时，才收到来电号码消息
**************************************************************/
#if 0
bool AdverModule::onVialCallerPhoneCode(CallerPhoneCodeVial *vial)
{
	if(vial)
	{
		showWarning("%s::%s\n", __CLASS__, __FUNCTION__);
		PhoneCode.nCallType = 0;
		//strncpy(PhoneCode.cPhoneCode, vial->cPhoneCode, vial->nLen);
		strncpy(PhoneCode.cPhoneCode, vial->cPhoneCode, VIAL_PHONECODE_LEN-1);
		PhoneCode.nCodelen = vial->nLen;
		PhoneCode.cPhoneCode[PhoneCode.nCodelen]= '\0';	

        #if 0
		StatePrompterInfo stateinfo;
		memset(&stateinfo, 0, sizeof(stateinfo));

		stateinfo.state = PP_RINGING;
		strncpy(stateinfo.message, vial->cPhoneCode, vial->nLen);
		stateinfo.message[vial->nLen]= '\0';
		showInfo("update_prompter_info : %d, %s\r\n", stateinfo.state, stateinfo.message);
		update_prompter_info(&stateinfo);
		#endif

		showWarning("%s::%s, phoneCode : %s\n", __CLASS__, __FUNCTION__, PhoneCode.cPhoneCode);

		
	}
	else
		showWarning("%s::%s, vial null\n", __CLASS__, __FUNCTION__);
	
	return true;
}
#endif

