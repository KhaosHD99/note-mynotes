#ifndef PROMPTER_MODULE_DEF
#define PROMPTER_MODULE_DEF

#include <stdio.h>

#include "Vial.hpp"
#include "AbstractModule.hpp"
#include "CodeConvert.hpp"
#include "VialType_Common.hpp"
#include "LogMsg.hpp"

const char STATE_INFO[5][32]=
{	
	"ON_HOOK",
	"DIALING",
	"RINGING",
	"NOVIDEO",
	"VIDEO",
};

/********************************************************************
					     Play Advertisement Module
*********************************************************************/
class MyClass : public IVialReceiver
{	
	public:
		virtual bool OnReceive(Vial *vial);
};


class AdverModule : public AbstractModule
{
#define __CLASS__ "AdverModule"
#define VIAL_PHONECODE_LEN	32
	struct
	{	
		int nPhoneMode;
		int nCallType;
		int nCodelen;
		char cPhoneCode[VIAL_PHONECODE_LEN];
	}PhoneCode;
	
	private:
		VialSystem *vialSys;
		static AdverModule *adverModule_instance;
		
	private:
		AdverModule(VialSystem *vialSys);
		virtual ~AdverModule(){};
		bool on_on_hook(StateChangeVial *vial);
		bool on_dialing(StateChangeVial *vial);
		bool on_ringing(StateChangeVial *vial);
		bool on_novideoconn(StateChangeVial *vial);
		bool on_videoconn(StateChangeVial *vial);

	protected:
		bool on_vial_state_change(StateChangeVial *vial);
		
	public:
		void run();
	 	static AdverModule *get_instance(VialSystem *vialSys);
		virtual bool localInit();
		virtual bool onExit();
		virtual bool OnReceive(Vial *vial);
		
		bool post_vial(Vial *vial, NodeID dstID);
};
#endif
