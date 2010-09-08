#ifndef CONTACTS_DEF
#define CONTACTS_DEF

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

typedef struct stContacts
{
	Name name;
	GroupTpye type;						//���
	Phone phones[MAX_PHONE_COUNT];
	Email emails[MAX_EMAIL_COUNT];
	char szvoip[MAX_VOIP_LEN];
	char szim[MAX_IM_LEN];
	char szaddress[MAX_ADDRESS_LEN];
}Contacts;
/* demo
[contact_1]
name=��:ҫȪ | :��ҫȪ | ��ҫȪ:
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
#endif
