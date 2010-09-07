/**********************************************************************************
一 : 配置文件读写库
**********************************************************************************/
LIB: linconfig.so
extern "C" {
#endif
/**********************************************************************************
创建读写文件filename的实例,NULL 为异常
**********************************************************************************/
LpConfig * lp_config_new(const char *filename);
/**********************************************************************************
获取section节，key对应的值(字符串)
若获取成功，则返回key字段的值，否则返回default_string
**********************************************************************************/
const char *lp_config_get_string(LpConfig *lpconfig, const char *section, const char *key, const char *default_string);
/**********************************************************************************
获取section节，key对应的值(整型)
若获取成功，则返回key字段的值，否则返回default_value
**********************************************************************************/
int lp_config_get_int(LpConfig *lpconfig,const char *section, const char *key, int default_value);
/**********************************************************************************
设置section节，key对应的值(字符串)
若section或key不存在，则自动创建新的section或key
**********************************************************************************/
void lp_config_set_string(LpConfig *lpconfig,const char *section, const char *key, const char *value);
/**********************************************************************************
设置section段，key对应的值(整型)
若section或key不存在，则自动创建新的section或key
**********************************************************************************/
void lp_config_set_int(LpConfig *lpconfig,const char *section, const char *key, int value);
/**********************************************************************************
同步配置文件(保存),返回0正常
**********************************************************************************/
int lp_config_sync(LpConfig *lpconfig);
/**********************************************************************************
检查是否有section节,返回0正常
**********************************************************************************/
int lp_config_has_section(LpConfig *lpconfig, const char *section);
/**********************************************************************************
清除section节
**********************************************************************************/
void lp_config_clean_section(LpConfig *lpconfig, const char *section);
/**********************************************************************************
消亡config实例
**********************************************************************************/
void lp_config_destroy(LpConfig *cfg);
#ifdef __cplusplus
}
#endif

/**********************************************************************************
二 :  存储应用模块
**********************************************************************************/
static GList *contacts_links = NULL;

a. 读写contacts.dat
/**********************************************************************************
通过Lpconfig加载联系人存储文件
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
读取指定为session的节内容，返回联系人信息
返回非NULL正常
**********************************************************************************/
Contacts * contactitem_new_from_config_file(struct _LpConfig *config, const char* section)
{
	...
	
}

/**********************************************************************************
保存单一联系人信息到文件内，非零异常
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
保存所有联系人信息到文件内，非零异常
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
b. 读写call.log
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
三 :  联系人应用模块()
**********************************************************************************/
class CContactsManager{
private:
	LpConfig * contacts_lpconfig;
	int curCount;
	Contact **contact_buf;													//动态数组
	static CContactsManager *contacts_instance;
	
private:
	void init(){
		
		curCount = 0;

		contact_buf = new Contact*[MAX_CONTACT_COUNT];
		//必须初始化.否则很容易出现野指针
		for(int i = 0; i < MAX_CONTACT_COUNT; i++)
		{
			contact_buf[i] = NULL;											//动态申请内存， 如int add(Contact contact)
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
	static CContactsManager *get_Instance();										//获最CContacts对象，单一模式(全局只有一个对象)
	
	int get_contact_count(){	return curCount;}							//获取联系人总量
	int get_contact_by_index(Contact *contact,	int index);					//
	int get_contact_by_name(Contact **contact,	const char *szname);		//根据姓名返回整一个contact对象,返回值是当前的位置(index)
	int get_contact_by_letter(Contact **contact, const char *szletter);		//根据首字母,返回值是当前的位置(index)
	int get_contact_by_phone(Contact **contact,	const char *szphone);		//根据电话号码返回整一个contact对象,返回值是当前的位置(index)
	
	int update_contact(Contact *contact);									//
	int update_contact_by_index(Contact *contact, int index);				//

	int add_contact(Contact *contact);
	int add_contact_by_index(Contact *contact, int index);
	int delete_contact_by_index(int index);
	int delete_contact_all();
	//sort
	void sort_by_name();													//根据姓名排序											
	void sort_by_letter();													//根据字母排序

	int save_file();														//
};

/**********************************************************************************
四 : 通话记录应用模块(必须考虑异步操作，如操作通信过程中，发送来电等)
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
			clInfo->calllog_buf[i] = NULL;											//动态申请内存， 如int add(Contact contact)
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
	static CCalllogManager *get_Instance();												//获最CCalllogManager对象，单一模式(全局只有一个对象)

	int load_logs_from_file();															//

	int get_calllog_count_by_type(CLSTATUS status);										//获取对应记录总量

	int get_calllog_by_index(CLSTATUS status, int index, CallLog *calllog);				//获取记录条目
	
	int add_calllog(CLSTATUS status, CallLog *calllog);

	int delete_calllog_by_index(CLSTATUS status, int index);

	int delete_calllog_all(CLSTATUS status);
	
	//sort
	void sort_by_date();																//有新往旧排

	int save_file();																	//

};
