#ifndef CONTACTS_DEF
#define CONTACTS_DEF

#include "lpconfig.h"
#ifdef HAVE_GLIB
#include <glib.h>
#else
#include "uglib.h"
#endif

#define MAX_PHONENUM_LEN	64	//�绰���볤��
#define MAX_CALLLOG_COUNT  100    //��־��¼����


//��־����
typedef enum CLSTATUS
{
	CL_MISSED,              //δ��
	CL_RECEIVED,            //�ѽ�
	CL_DIALED               //�Ѳ�
}CLSTATUS;

//ʱ����ʱ��
typedef struct stCLDate
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int duration;		//ʱ��
}CLDate;

//��־��Ϣ
typedef struct stCallLog
{
	CLSTATUS status;
	char szremote[MAX_PHONENUM_LEN];
	CLDate date;
}CallLog;


class CCalllogManager
{
	typedef struct CallLog_Info
	{
		int count;
		CLSTATUS status;
		CallLog **calllog_buff;
	}CallLog_Info;

	private:
		LpConfig *calllog_lpconfig;
		int curCount;
		GList *calllogLink;
		CallLog_Info calllog_missed, calllog_received, calllog_dailed;
		static CCalllogManager *calllog_instance;
	
	private:
		void init();	
		void init_log(CallLog_Info *clInfo);
		void uninit();
		void uninit_log(CallLog_Info *clInfo);
	
	public:
		static CCalllogManager *get_instance();	//����CCalllogManager���󣬵�һģʽ(ȫ��ֻ��һ������)

		void calllog_read(LpConfig *config);
		CallLog* calllogitem_new_from_config_file(LpConfig *config, int index);
		int write_calllog_item(LpConfig *config, CallLog *item, int index);
   		int save_calllog_configs(LpConfig *config);
		int get_calllogitem_count();
		

		//int load_logs_from_file();				//

		int get_calllog_count_by_type(CLSTATUS status);	//��ȡ��Ӧ��¼����

		int get_calllog_by_index(CLSTATUS status, int index, CallLog *calllog);  //��ȡ��¼��Ŀ
		
		int add_calllog(CLSTATUS status, CallLog *calllog);

		int delete_calllog_by_index(CLSTATUS status, int index);

		int delete_calllog_all(CLSTATUS status);
	
		int delete_calllogLink();
		
		//sort
		void sort_by_date();	//����������

		int save_file();		//

		void test();

		CLSTATUS __clstatus_str_to_enum(const gchar *enum_str);
		const gchar* __clstatus_enum_to_str(int enum_val);

};

#endif

/*
[call_log_1]
status = missed|received
from = 34453596
start_date=2010-8-16 14:48:33
duration=16

[call_log_2]
status = dialed
to = 34453596
start_date=2010-8-16 15:48:33
duration=16

*/

