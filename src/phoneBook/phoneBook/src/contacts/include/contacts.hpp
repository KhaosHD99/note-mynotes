#ifndef CONTACTS_DEF
#define CONTACTS_DEF

#include "lpconfig.h"
#ifdef HAVE_GLIB
#include <glib.h>
#else
#include "uglib.h"
#endif

#define MAX_CONTACT_COUNT	1000
#define MAX_CALLLOG_COUNT	50
#define MAX_NAME_LEN		64	//姓名长度
#define MAX_PHONE_COUNT		10	//联系人可拥有的号码数
#define MAX_PHONENUM_LEN	64	//电话号码长度
#define MAX_EMAIL_COUNT		10	//联系人可拥有的帐号数
#define MAX_EMAIL_LEN		64	//帐号长度
#define MAX_VOIP_LEN		64	//voip帐号长度
#define MAX_IM_LEN			64	//IM帐号长度
#define MAX_ADDRESS_LEN		128	//地址长度

typedef enum PhoneType
{
    PT_NONE,
	PT_HOME,					//家庭
	PT_MOBILE,					//移动
	PT_WORK,					//单位
	PT_WORK_FAX,				//单位传真
	PT_HOME_FAX,				//住宅传真
	PT_OTHER,					//其他
	PT_CUSTOM					//自定义
}PhoneType;

typedef enum EMailType
{
    EMT_NONE,                   
	EMT_HOME,					//家庭
	EMT_WORK,					//单位
	EMT_OTHER,					//其他
	EMT_CUSTOM					//自定义
}EMailType;

typedef enum GroupType
{
	GT_FAMILY,					//家庭
	GT_RELATIVES,				//亲朋
	GT_COLLEAGUES,				//同事
	GT_FRIENDS,					//朋友
	GT_MANUFACTURERS,			//厂商
	GT_OTHER,					//其他
	GT_CUSTOM					//自定义
}GroupType;

typedef struct stName
{
	char szgiven_name[MAX_NAME_LEN];	//名
	char szfamily_name[MAX_NAME_LEN];	//姓
}Name;

typedef struct stPhone
{
	PhoneType type;
	char szphone[MAX_PHONENUM_LEN];
}Phone;

typedef struct stEmail
{
	EMailType type;
	char szemail[MAX_EMAIL_LEN];
}Email;

typedef struct stContact
{
    int index;
	Name name;
	GroupType type;					                   //组别
	Phone phones[MAX_PHONE_COUNT];
	Email emails[MAX_EMAIL_COUNT];
	char szvoip[MAX_VOIP_LEN];
	char szim[MAX_IM_LEN];
	char szaddress[MAX_ADDRESS_LEN];
}Contact;
/* demo
[contact_1]
name=耀泉:吴| :吴耀泉 | 吴耀泉:
group=family

phonecount=2
phone_1=home:34453620
phone_2=work:34453596

emailcount=2
email_1=work:34453620@finephon.com
email_2=custom:34453596@finphon.com

voip=sip:34453620@finephon.com
im=398639019
address=广州市X路Y大厦

[contact_2]
....
....
....

[contact_3]
....
....
....

*/
//日志类型
typedef enum CLSTATUS
{
	CL_MISSED,
	CL_RECEIVED,
	CL_DIALED
}CLSTATUS;

//时间与时长
typedef struct stCLDate
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int duration;		//时长
}CLDate;

//日志信息
typedef struct stCallLog
{
	CLSTATUS status;
	char szremote[MAX_PHONENUM_LEN];
	CLDate date;
}CallLog;

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

class CContactsManager
{
	private:
		LpConfig *contacts_lpconfig;
	 	int curCount;
	 	Contact **contact_buf;
		//GList *contactLink;
	 	static CContactsManager *contacts_instance;
		
    private:
		CContactsManager();
		~CContactsManager();
	 	void init();
	    void uninit();
 
	public:
	 	static CContactsManager *get_instance();
		void read_contact();
		Contact* get_section_from_config_file(int index);
		int write_contact_item(Contact *item, int index);
		int sync_contact_config();

		//test
		void test();
		//CRUD
		int get_contact_count();
		int get_contact_buf_count();
	 	int get_contact_by_index(Contact **contact,	int index);					 
	 	int get_contact_by_name(Contact **contact,	const char *szname);	
		int get_contact_by_name();
	 	int get_contact_by_letter(Contact **contact, const char *szletter);		 
	 	int get_contact_by_phone(Contact **contact,	const char *szphone);		 
	 									
	 	int update_contact_by_index(Contact *contact, int index);				
	 
	 	int add_contact(Contact *contact);
	 	int add_contact_by_index(Contact *contact, int index);
	 	int delete_contact_by_index(int index);
	 	int delete_contact_all();

		//help
		void Show_contact_buf();
		
		//validate
        int validate();
		
		//sort
	 	void sort_by_name();													 						
	 	void sort_by_letter();		 
	    
	 	int save_file();

		//enum
		const gchar* __grouptype_enum_to_str(int enum_val);
		const gchar* __phonetype_enum_to_str(int enum_val);
		const gchar* __emailtype_enum_to_str(int enum_val);

		GroupType __grouptype_str_to_enum(const gchar *enum_str);
		PhoneType __phonetype_str_to_enum(const gchar *enum_str);
		EMailType __emailtype_str_to_enum(const gchar *enum_str);
};
#endif




