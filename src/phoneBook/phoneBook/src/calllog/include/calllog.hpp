#ifndef CALLLOG_DEF
#define CALLLOG_DEF

#include "lpconfig.h"
#ifdef HAVE_GLIB
#include <glib.h>
#else
#include "uglib.h"
#endif

#define MAX_PHONENUM_LEN	64	   //电话号码长度
#define MAX_REMOTE_LEN	    64	   //remote 长度
#define MAX_CALLLOG_COUNT   100    //日志记录条数(未确定)
#define MAX_DATE_YEAR_LEN   5     //年的长度
#define MAX_DATE_LEN        3     //月、日、时、分、秒的长度

#define CL_NON_str          "NULL"
#define CL_MISSED_str       "missed"
#define CL_RECEIVED_str     "received"
#define CL_DIALED_str       "dialed"

#define PATHNAME               "CallLog.cfg"
#define CLOG_CALLLOG_INDEX     "calllog_"
#define CLOG_INDEX             "index"
#define CLOG_STATUS            "status"
#define CLOG_MISSED_INDEX      "missed_index"
#define CLOG_RECEIVED_INDEX    "received_index"
#define CLOG_DIALED_INDEX      "dialed_index"
#define CLOG_REMOTE_FROM       "from"
#define CLOG_REMOTE_TO         "to"
#define CLOG_START_DATE        "start_date"
#define CLOG_DURATION          "duration"



//日志类型
typedef enum CLSTATUS
{
	CL_NON,
	CL_MISSED,              //未接
	CL_RECEIVED,            //已接
	CL_DIALED               //已拨
}CLSTATUS;

//时间与时长
typedef struct stCLDate
{
	char year[MAX_DATE_YEAR_LEN];
	char month[MAX_DATE_LEN];
	char day[MAX_DATE_LEN];
	char hour[MAX_DATE_LEN];
	char minute[MAX_DATE_LEN];       //已将时间的int类型改成char
	char second[MAX_DATE_LEN];       //是为了方便后门的时间分割和合成
	int duration;		//时长
}CLDate;

//日志信息
typedef struct stCallLog
{
	int index;
	CLSTATUS status;
	int status_index;
	char szremote[MAX_REMOTE_LEN];
	CLDate date;
}CallLog;

typedef struct CallLog_Info
{	
	int count;
	CLSTATUS status;
	CallLog **calllog_buf;  //指针数组 ,动态申请一组 new CallLog*
}CallLog_Info;

class CCalllogManager
{
	
	private:
		LpConfig *calllog_lpconfig;
		//int all_count, miss_count, receive_count, dail_count;
		CallLog_Info calllog_missed, calllog_received, calllog_dialed;
		static CCalllogManager *calllog_instance;
	
	private:
		CCalllogManager();
		void init();	
		void init_log(CallLog_Info *calllog_info);
		void uninit();
		void uninit_log(CallLog_Info *calllog_info);
	
	public:
		static CCalllogManager *get_instance();
        //int load_calllog_from_file();
	    int read_calllog();		
        CallLog* get_section_from_config_file(int index);
       	int write_calllog_item(CallLog *item, int index, int status_index);
		int sync_calllog_config();

		//CRUD
		int get_calllog_count();
		int get_calllog_buf_count();
	    int get_calllog_count_by_type(CLSTATUS status);	 
        int get_calllog_by_index(CLSTATUS status, int index, CallLog *calllog); 
		int add_calllog(CLSTATUS status, CallLog *calllog);
        int delete_calllog_by_index(CLSTATUS status, int index);
        int delete_calllog_by_status(CLSTATUS status);
			
		//sort
		void sort_by_date();	//有新往旧排

		void test();

		CLSTATUS __clstatus_str_to_enum(const gchar *enum_str);
		const gchar* __clstatus_enum_to_str(int enum_val);

};

#endif

/*
[calllog_0]
status=received
received_index=0
from=34453596
start_date=2010-8-11 14:48:33
duration=10

[calllog_1]
status=dialed
dialed_index=0
to=34453596
start_date=2010-8-11 14:48:33
duration=16


*/

