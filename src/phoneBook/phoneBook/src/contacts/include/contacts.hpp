#ifndef CONTACTS_DEF
#define CONTACTS_DEF

#include "lpconfig.h"

#define MAX_CONTACT_COUNT	1000
#define MAX_CALLLOG_COUNT	50
#define MAX_NAME_LEN		64	//��������
#define MAX_PHONE_COUNT		10	//��ϵ�˿�ӵ�еĺ�����
#define MAX_PHONENUM_LEN	64	//�绰���볤��
#define MAX_EMAIL_COUNT		10	//��ϵ�˿�ӵ�е��ʺ���
#define MAX_EMAIL_LEN		64	//�ʺų���
#define MAX_VOIP_LEN		64	//voip�ʺų���
#define MAX_IM_LEN			64	//IM�ʺų���
#define MAX_ADDRESS_LEN		128	//��ַ����

typedef enum PhoneType
{
	PT_HOME,					//��ͥ
	PT_MOBILE,					//�ƶ�
	PT_WORK,					//��λ
	PT_WORK_FAX,				//��λ����
	PT_HOME_FAX,				//סլ����
	PT_OTHER,					//����
	PT_CUSTOM					//�Զ���
}PhoneType;

typedef enum EMailType
{
	EMT_HOME,					//��ͥ
	EMT_WORK,					//��λ
	EMT_OTHER,					//����
	EMT_CUSTOM					//�Զ���
}EMailType;

typedef enum GroupTpye
{
	GT_FAMILY,					//��ͥ
	GT_RELATIVES,				//����
	GT_COLLEAGUES,				//ͬ��
	GT_FRIENDS,					//����
	GT_MANUFACTURERS,			//����
	GT_OTHER,					//����
	GT_CUSTOM					//�Զ���
}GroupTpye;

typedef struct stName
{
	char szgiven_name[MAX_NAME_LEN];	//��
	char szfamily_name[MAX_NAME_LEN];	//��
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
	Name name;
	GroupTpye type;						//���
	Phone phones[MAX_PHONE_COUNT];
	Email emails[MAX_EMAIL_COUNT];
	char szvoip[MAX_VOIP_LEN];
	char szim[MAX_IM_LEN];
	char szaddress[MAX_ADDRESS_LEN];
}Contact;
/* demo
[contact_1]
name=ҫȪ:��| :��ҫȪ | ��ҫȪ:
group=family

phonecount=2
phone_1=home:34453620
phone_2=work:34453596

emailcount=2
email_1=work:34453620@finephon.com
email_2=custom:34453596@finphon.com

voip=sip:34453620@finephon.com
im=398639019
address=������X·Y����

[contact_2]
....
....
....

[contact_3]
....
....
....

*/
//��־����
typedef enum CLSTATUS
{
	CL_MISSED,
	CL_RECEIVED,
	CL_DIALED
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
	 	Contact **contact_buf;													//��̬����
	 	static CContactsManager *contacts_instance;
 	 
	private:
	 	void init();
	    void uninit();
 
	public:
	 	static CContactsManager *get_instance()
		{
		    contacts_instance = new CContactsManager;
		    return contacts_instance;
		}
	 	int get_contact_count();						 
	 	int get_contact_by_index(Contact *contact,	int index);					 
	 	int get_contact_by_name(Contact **contact,	const char *szname);		 
	 	int get_contact_by_letter(Contact **contact, const char *szletter);		 
	 	int get_contact_by_phone(Contact **contact,	const char *szphone);		 
	 	
	 	int update_contact(Contact *contact);									
	 	int update_contact_by_index(Contact *contact, int index);				
	 
	 	int add_contact(Contact *contact);
	 	int add_contact_by_index(Contact *contact, int index);
	 	int delete_contact_by_index(int index);
	 	int delete_contact_all();
	 	//sort
	 	void sort_by_name();													 						
	 	void sort_by_letter();		 
	 
	 	int save_file();	
		void test();
 };

#endif




