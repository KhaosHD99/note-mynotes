#ifndef PROMPTER_GUI_DEF
#define PROMPTER_GUI_DEF

#include <gtk/gtk.h>

#define MESSAGE_MAX_LEN	64

typedef enum ST_PP
{
	ON_HOOK,	
		//待机
	OFF_HOOK,	
	//拨号... + 号码
	RINGING,	
	//来电... + 号码
	CONNECT,	
	//通话中... + 号码
	UNCATCH_PHONE_MESSAGE,	
	//未接来电
	UNCATCH_SMS_MESSAGE,		
	//为查看短信
	UNCATCH_EMAIL_MESSAGE,	
	//未查看邮件
	OTHER_MESSAGE
}ST_PP;

typedef struct StatePrompterInfo
{
		ST_PP state;
		char message[MESSAGE_MAX_LEN];
}StatePrompterInfo;

#ifdef __cplusplus
extern"C"
{
#endif
	//GUI Interface
	GtkWidget* creat_prompter_gtkarea(GtkWidget *fixed);
	
	int update_prompter_info(StatePrompterInfo *stateinfo);
	
	ST_PP get_prompter_state();
	
	int get_prompter_stateinfo(StatePrompterInfo *stateinfo);
	
#ifdef __cplusplus
}
#endif
	
#endif
