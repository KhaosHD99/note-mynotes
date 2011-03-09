#ifndef PROMPTER_GUI_DEF
#define PROMPTER_GUI_DEF

//#include <gtk/gtk.h>

#define MESSAGE_MAX_LEN	64

typedef enum ST_PP
{
	PP_ON_HOOK,	//待机	 + (时间)
	PP_OFF_HOOK,	//拨号... + (计时) + 号码
	PP_RINGING,	//来电... + (计时) + 号码
	PP_CONNECT,	//通话中... + (计时) + 号码
	PP_UNCATCH_PHONE_MESSAGE,	//未接来电 + 号码
	PP_UNCATCH_SMS_MESSAGE,		//未查看短信  + 号码
	PP_UNCATCH_EMAIL_MESSAGE,	//未查看邮件  + 邮箱
	PP_OTHER_MESSAGE	// 未定义
}ST_PP;

const char ST_PP_INFO[PP_OTHER_MESSAGE+1][MESSAGE_MAX_LEN] = 
{
	"",
	"拨号...",
	"来电...",
	"通话中...",
	"未接来电",
	"未查看短信",
	"未查看邮件",
	""
};

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
	//GtkWidget* creat_prompter_gtkarea(unsigned int width, unsigned int hight);	
	int update_prompter_info(StatePrompterInfo *stateinfo);
	
	ST_PP get_prompter_state();
	
	int get_prompter_stateinfo(StatePrompterInfo *stateinfo);
	
#ifdef __cplusplus
}
#endif
	
#endif
