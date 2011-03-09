#ifndef PROMPTER_GUI_DEF
#define PROMPTER_GUI_DEF

//#include <gtk/gtk.h>

#define MESSAGE_MAX_LEN	64

typedef enum ST_PP
{
	PP_ON_HOOK,	//����	 + (ʱ��)
	PP_OFF_HOOK,	//����... + (��ʱ) + ����
	PP_RINGING,	//����... + (��ʱ) + ����
	PP_CONNECT,	//ͨ����... + (��ʱ) + ����
	PP_UNCATCH_PHONE_MESSAGE,	//δ������ + ����
	PP_UNCATCH_SMS_MESSAGE,		//δ�鿴����  + ����
	PP_UNCATCH_EMAIL_MESSAGE,	//δ�鿴�ʼ�  + ����
	PP_OTHER_MESSAGE	// δ����
}ST_PP;

const char ST_PP_INFO[PP_OTHER_MESSAGE+1][MESSAGE_MAX_LEN] = 
{
	"",
	"����...",
	"����...",
	"ͨ����...",
	"δ������",
	"δ�鿴����",
	"δ�鿴�ʼ�",
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
