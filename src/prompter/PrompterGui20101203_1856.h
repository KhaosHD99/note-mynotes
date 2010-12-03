#ifndef PROMPTER_GUI_DEF
#define PROMPTER_GUI_DEF

#include <gtk/gtk.h>

#define MESSAGE_MAX_LEN	64

typedef enum ST_PP
{
	ON_HOOK,	
		//����
	OFF_HOOK,	
	//����... + ����
	RINGING,	
	//����... + ����
	CONNECT,	
	//ͨ����... + ����
	UNCATCH_PHONE_MESSAGE,	
	//δ������
	UNCATCH_SMS_MESSAGE,		
	//Ϊ�鿴����
	UNCATCH_EMAIL_MESSAGE,	
	//δ�鿴�ʼ�
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
