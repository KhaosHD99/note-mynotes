/**********************************************************************************
һ : �����ļ���д��
**********************************************************************************/
LIB: linconfig.so
extern "C" {
#endif
/**********************************************************************************
������д�ļ�filename��ʵ��,NULL Ϊ�쳣
**********************************************************************************/
LpConfig * lp_config_new(const char *filename);
/**********************************************************************************
��ȡsection�ڣ�key��Ӧ��ֵ(�ַ���)
����ȡ�ɹ����򷵻�key�ֶε�ֵ�����򷵻�default_string
**********************************************************************************/
const char *lp_config_get_string(LpConfig *lpconfig, const char *section, const char *key, const char *default_string);
/**********************************************************************************
��ȡsection�ڣ�key��Ӧ��ֵ(����)
����ȡ�ɹ����򷵻�key�ֶε�ֵ�����򷵻�default_value
**********************************************************************************/
int lp_config_get_int(LpConfig *lpconfig,const char *section, const char *key, int default_value);
/**********************************************************************************
����section�ڣ�key��Ӧ��ֵ(�ַ���)
��section��key�����ڣ����Զ������µ�section��key
**********************************************************************************/
void lp_config_set_string(LpConfig *lpconfig,const char *section, const char *key, const char *value);
/**********************************************************************************
����section�Σ�key��Ӧ��ֵ(����)
��section��key�����ڣ����Զ������µ�section��key
**********************************************************************************/
void lp_config_set_int(LpConfig *lpconfig,const char *section, const char *key, int value);
/**********************************************************************************
ͬ�������ļ�(����),����0����
**********************************************************************************/
int lp_config_sync(LpConfig *lpconfig);
/**********************************************************************************
����Ƿ���section��,����0����
**********************************************************************************/
int lp_config_has_section(LpConfig *lpconfig, const char *section);
/**********************************************************************************
���section��
**********************************************************************************/
void lp_config_clean_section(LpConfig *lpconfig, const char *section);
/**********************************************************************************
����configʵ��
**********************************************************************************/
void lp_config_destroy(LpConfig *cfg);
#ifdef __cplusplus
}
#endif

/**********************************************************************************
�� :  �洢Ӧ��ģ��
**********************************************************************************/
static GList *contacts_links = NULL;

a. ��дcontacts.dat
/**********************************************************************************
ͨ��Lpconfig������ϵ�˴洢�ļ�
**********************************************************************************/
void contacts_read(struct _LpConfig *config)
{
	Contacts* item
	
	...
	
	for (i=0;(item = contactitem_new_from_config_file(config,i)) != NULL;i++)
	{
		mcallinks = g_list_append(mcallinks,(gpointer)mi);
	}
	
}

/**********************************************************************************
��ȡָ��Ϊsession�Ľ����ݣ�������ϵ����Ϣ
���ط�NULL����
**********************************************************************************/
Contacts * contactitem_new_from_config_file(struct _LpConfig *config, const char* section)
{
	...
	
}

/**********************************************************************************
���浥һ��ϵ����Ϣ���ļ��ڣ������쳣
**********************************************************************************/
int save_contacts_session(struct _LPConfig *config, Contacts * constact)
{
	int ret = 0;
	....
	ret = lp_config_set_XXX(...);
	...
	
	ret = lp_config_sync(config);

	return ret;
}

/**********************************************************************************
����������ϵ����Ϣ���ļ��ڣ������쳣
**********************************************************************************/
int save_contacts(struct _LPConfig *config, ....)
{
	int ret = 0;
	for(...,...,...)
	{
		ret = save_contacts_session(....)
	}
	return ret;
}

/**********************************************************************************
b. ��дcall.log
**********************************************************************************/
void calllog_read(struct _LpConfig *config)
{
					
}

int save_calllog_session(struct _LPConfig *config, Contacts * constact)
{
	int ret = 0;
	....
	ret = lp_config_set_XXX(...);
	...
	
	ret = lp_config_sync(config);

	return ret;
}

int save_calllog(struct _LPConfig *config, ....)
{
	int ret = 0;
	for(...,...,...)
	{
		ret = save_calllog_session(....)
	}
	return ret;
}

/**********************************************************************************
�� :  ��ϵ��Ӧ��ģ��()
**********************************************************************************/
class CContactsManager{
private:
	LpConfig * contacts_lpconfig;
	int curCount;
	Contact **contact_buf;													//��̬����
	static CContactsManager *contacts_instance;
	
private:
	void init(){
		
		curCount = 0;

		contact_buf = new Contact*[MAX_CONTACT_COUNT];
		//�����ʼ��.��������׳���Ұָ��
		for(int i = 0; i < MAX_CONTACT_COUNT; i++)
		{
			contact_buf[i] = NULL;											//��̬�����ڴ棬 ��int add(Contact contact)
		}
	}
	
	void uninit()
	{
		for(int i = 0; i < curCount;	i++)
		{
			delete contact_buf[i];
			contact_buf[i] = NULL;
		}
		delete contact_buf;
		contact_buf = NULL;
	}

	
	/*
		int add(Contact contact)
		{
			if(curCount < MAX_CONTACT_COUNT)
			{
				Contact *ptmp = new Contact();
				if(NULL == ptmp)
					return -1;
				contact_buf[curCount] = ptmp;
			}
			return 0;
		}
	*/

public:
	static CContactsManager *get_Instance();										//����CContacts���󣬵�һģʽ(ȫ��ֻ��һ������)
	
	int get_contact_count(){	return curCount;}							//��ȡ��ϵ������
	int get_contact_by_index(Contact *contact,	int index);					//
	int get_contact_by_name(Contact **contact,	const char *szname);		//��������������һ��contact����,����ֵ�ǵ�ǰ��λ��(index)
	int get_contact_by_letter(Contact **contact, const char *szletter);		//��������ĸ,����ֵ�ǵ�ǰ��λ��(index)
	int get_contact_by_phone(Contact **contact,	const char *szphone);		//���ݵ绰���뷵����һ��contact����,����ֵ�ǵ�ǰ��λ��(index)
	
	int update_contact(Contact *contact);									//
	int update_contact_by_index(Contact *contact, int index);				//

	int add_contact(Contact *contact);
	int add_contact_by_index(Contact *contact, int index);
	int delete_contact_by_index(int index);
	int delete_contact_all();
	//sort
	void sort_by_name();													//������������											
	void sort_by_letter();													//������ĸ����

	int save_file();														//
};

/**********************************************************************************
�� : ͨ����¼Ӧ��ģ��(���뿼���첽�����������ͨ�Ź����У����������)
**********************************************************************************/
class CCalllogManager{
typedef struct CallLog_Info
{
	int count;
	CL_STATUS status;
	CallLog **calllog_buffs;
}CallLog_Info;

private:
	LpConfig * calllog_lpconfig;

	CallLog_Info calllog_missed, calllog_received, calllog_dailed;
	static CCalllogManager *calllog_instance;
	
private:
	void init()
	{
		init_logs(&calllog_missed);
		init_logs(&calllog_received);
		init_logs(&calllog_dailed);
	}
	
	void init_log(CallLog_Info *clInfo){
		
		clInfo->count = 0;

		clInfo->calllog_buf = new CallLog*[MAX_CALLLOG_COUNT];

		for(int i = 0; i < MAX_CALLLOG_COUNT; i++)
		{
			clInfo->calllog_buf[i] = NULL;											//��̬�����ڴ棬 ��int add(Contact contact)
		}
	}
	
	void uninit()
	{
		uninit_log(&calllog_missed);
		uninit_log(&calllog_received);
		uninit_log(&calllog_dailed);
	}

	void uninit_log(CallLog_Info *clInfo)
	{
		for(int i = 0; i < clInfo->count;	i++)
		{
			delete clInfo->calllog_buf[i];
			clInfo->calllog_buf[i] = NULL;
		}
		delete clInfo->calllog_buf;
		clInfo->calllog_buf = NULL;
	}
	
public:
	static CCalllogManager *get_Instance();												//����CCalllogManager���󣬵�һģʽ(ȫ��ֻ��һ������)

	int load_logs_from_file();															//

	int get_calllog_count_by_type(CLSTATUS status);										//��ȡ��Ӧ��¼����

	int get_calllog_by_index(CLSTATUS status, int index, CallLog *calllog);				//��ȡ��¼��Ŀ
	
	int add_calllog(CLSTATUS status, CallLog *calllog);

	int delete_calllog_by_index(CLSTATUS status, int index);

	int delete_calllog_all(CLSTATUS status);
	
	//sort
	void sort_by_date();																//����������

	int save_file();																	//

};
