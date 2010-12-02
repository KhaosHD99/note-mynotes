#ifndef PROMPTER_GUI_DEF
#define PROMPTER_GUI_DEF
#ifdef __cplusplus
extern"C"
{
#endif
	typedef enum ST_PP
	{
		ON_HOOK,	//待机
		OFF_HOOK,	//拨号... + 号码
		RINGING,	//来电... + 号码
		CONNECT,	//通话中... + 号码
		MESSAGE
	}ST_PP
	//GUI Interface
	GtkWidget* creat_prompter_gtkarea(GtkWidget *fixed);
	
	int update_prompter_info(ST_PP states, const char*info);
	
	ST_PP get_prompter_info();
	
#ifdef __cplusplus
}
#endif
	
#endif
