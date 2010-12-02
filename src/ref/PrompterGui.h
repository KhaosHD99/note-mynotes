#ifndef PROMPTER_GUI_DEF
#define PROMPTER_GUI_DEF
#ifdef __cplusplus
extern"C"
{
#endif
	typedef enum ST_PP
	{
		ON_HOOK,	//����
		OFF_HOOK,	//����... + ����
		RINGING,	//����... + ����
		CONNECT,	//ͨ����... + ����
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
