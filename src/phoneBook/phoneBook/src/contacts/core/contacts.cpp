#include <stdio.h>
#include "contacts.hpp"
#include "lpconfig.h"
#include "iostream"
#include "stdlib.h"
using namespace std;

CContactsManager::CContactsManager()
{
    init();
}


CContactsManager::~CContactsManager()
{
	uninit();
}

void CContactsManager::init()
{
    char pathname[64];
	contact_buf = new Contact*[MAX_CONTACT_COUNT];;
	
	sprintf(pathname, "%s", "Contacts.cfg");
	contacts_lpconfig = lp_config_new(pathname); 
	
	for(int i = 0; i < MAX_CONTACT_COUNT; i++)
	{
		contact_buf[i] = NULL;
	}
}

void CContactsManager::uninit()
{
	lp_config_destroy(contacts_lpconfig);

	for(int i = 0; i < curCount;	i++)
		{
			delete contact_buf[i];
			contact_buf[i] = NULL;
		}
		delete contact_buf;
		contact_buf = NULL;
}

CContactsManager* CContactsManager::contacts_instance = NULL;

CContactsManager *CContactsManager::get_instance()
{
	contacts_instance = new CContactsManager;
	return contacts_instance;
}

void CContactsManager::test()
{
    const char *tmp;
	int phone_count;
	gchar phone_index[20];
	gchar section_index[50];
	char *part_str;
	const char *split = "x"; 

    sprintf(section_index,"contact_%i",1);
	
	phone_count = lp_config_get_int(contacts_lpconfig,section_index,"phonecount",NULL);	
	for(int i=0; i<phone_count; i++)
    {
        sprintf(phone_index,"phone_%d",i + 1);
    	tmp = lp_config_get_string(contacts_lpconfig,section_index,phone_index,NULL);
        char *tmpcopy = (char *)malloc(sizeof(tmp));

		//strcpy(tmpcopy, tmp);
		cout << "phone tmp: " << tmp << endl;

		char *str;
		strcmp(str, tmp);
		part_str = strtok ((char *)tmp, split); 
		if(__phonetype_str_to_enum((const char*)part_str) != NULL)
		{
			//contact->phones[i].type = __phonetype_str_to_enum((const char*)part_str);
		}
		
		//szphone
		part_str = strtok(NULL,split);
		if((const char*)part_str != NULL)
		{
			//strcpy(contact->phones[i].szphone, (const char*)part_str);
		}
	}
}

void CContactsManager::read_contact()
{
	Contact *contact = new Contact;
	//contact_buf = new Contact*[MAX_CONTACT_COUNT];
	
	if(contacts_lpconfig == NULL)
	{
		g_error("_LpConfig = (null)");
		return ;
	}
	for (int i=0; (contact = get_section_from_config_file(i)) != NULL; i++)
	{
	    contact_buf[i] = contact;
	}
}

Contact* CContactsManager::get_section_from_config_file(int index)
{
    Contact *contact;
	const gchar *tmp;
    char *tmpcpy;
	int phone_count;
	int email_count;
	gchar phone_index[20];
	gchar email_index[20];
	gchar section_index[50];
	char *part_str;
	const char * split = ":"; 
	
	sprintf(section_index,"contact_%i",index);

	if (!lp_config_has_section(contacts_lpconfig, section_index))
	{
		//g_error("find %s error\r\n", section_index);
		return NULL;
	}
	contact = g_new0(Contact,1);
	memset(contact, 0, sizeof(Contact));

	//name, group
	tmp = lp_config_get_string(contacts_lpconfig,section_index,"family_name",NULL);
    if(tmp != NULL && strlen(tmp) <= MAX_NAME_LEN)
		strcpy(contact->name.szfamily_name, tmp);

	tmp = lp_config_get_string(contacts_lpconfig,section_index,"given_name",NULL);
	if(tmp != NULL && strlen(tmp) <= MAX_NAME_LEN)
		strcpy(contact->name.szgiven_name, tmp);

    tmp = lp_config_get_string(contacts_lpconfig,section_index,"group",NULL);
	if(tmp != NULL)
		contact->type = __grouptype_str_to_enum(tmp);

    //phone
    phone_count = lp_config_get_int(contacts_lpconfig,section_index,"phonecount",NULL);
    
    for(int i=0; i<phone_count; i++)
    {
        sprintf(phone_index,"phone_%d",i + 1);
    	tmp = lp_config_get_string(contacts_lpconfig,section_index,phone_index,NULL);
        tmpcpy = (char *)malloc(strlen(tmp));
		strcpy(tmpcpy, tmp);
	    //cout << "phone tmp: " << tmp << endl;
		
		//type
		part_str = strtok (tmpcpy, split);
		if(__phonetype_str_to_enum((const char*)part_str) != NULL)
		{
			contact->phones[i].type = __phonetype_str_to_enum((const char*)part_str);
		}
		
		//szphone
		part_str = strtok(NULL,split);
		if((const char*)part_str != NULL)
		{
			strcpy(contact->phones[i].szphone, (const char*)part_str);
		}
		
		free(tmpcpy);
	}
    
	//email
	email_count = lp_config_get_int(contacts_lpconfig,section_index,"phonecount",NULL);
 
	for(int j=0;j<email_count;j++)
    {
        sprintf(email_index,"email_%d",j + 1);
    	tmp = lp_config_get_string(contacts_lpconfig,section_index,email_index,NULL);
        tmpcpy = (char *)malloc(strlen(tmp));
		strcpy(tmpcpy, tmp);

		//type
		part_str = strtok (tmpcpy, split); 
		if(__emailtype_str_to_enum((const char*)part_str) != NULL)
			contact->emails[j].type = __emailtype_str_to_enum((const char*)part_str);

		//szemail
		part_str = strtok(NULL,split);
		if((const char*)part_str != NULL)
			strcpy(contact->emails[j].szemail, (const char*)part_str);
			
		free(tmpcpy);
	}

	//voip, im, address
	tmp = lp_config_get_string(contacts_lpconfig,section_index,"voip",NULL);
	if(tmp != NULL && strlen(tmp) <= MAX_VOIP_LEN)
		strcpy(contact->szvoip, tmp);
	
	tmp = lp_config_get_string(contacts_lpconfig,section_index,"im",NULL);
	if(tmp != NULL && strlen(tmp) <= MAX_IM_LEN)
		strcpy(contact->szim, tmp);

	tmp = lp_config_get_string(contacts_lpconfig,section_index,"address",NULL);
	if(tmp != NULL && strlen(tmp) <= MAX_ADDRESS_LEN)
		strcpy(contact->szaddress, tmp);
	
	return contact;
}

int CContactsManager::write_contact_item(Contact *item, int index)
{
    gchar section[50];
	gchar phone_index[20];
	gchar email_index[20];
	gchar phone_mix_info[30];
	gchar email_mix_info[30];
	int phone_count;
	int email_count;
	
	gchar *tmp;
	int a = 5;
    
	sprintf(section,"contact_%i",index);

	//name, group
    lp_config_set_string(contacts_lpconfig, section, "family_name",item->name.szfamily_name);
    lp_config_set_string(contacts_lpconfig, section, "given_name", item->name.szgiven_name);
    lp_config_set_string(contacts_lpconfig, section, "group", __grouptype_enum_to_str(item->type));

    //phone
    phone_count = 0;
	
	while(item->phones[phone_count].szphone[0] != '\0')
    {
       phone_count++;
	   if(phone_count == MAX_PHONE_COUNT)
	      break;
    }
	
    lp_config_set_int(contacts_lpconfig, section, "phonecount", phone_count);
			             
	for(int i=0; i<phone_count; i++)
	{
	    sprintf(phone_index,"phone_%d",i + 1);
		if(__phonetype_enum_to_str(item->phones[i].type) != NULL)
			sprintf(phone_mix_info, "%s:%s", 
			        __phonetype_enum_to_str(item->phones[i].type), 
			        item->phones[i].szphone);
		else
			sprintf(phone_mix_info, "%s", item->phones[i].szphone);

		lp_config_set_string(contacts_lpconfig, section, phone_index, phone_mix_info);
    }
	
	//email
    email_count = 0;
    while(*item->emails[email_count].szemail != 0)
    {
       email_count++;
	   if(email_count == MAX_EMAIL_COUNT)
	      break;
    }
	
    lp_config_set_int(contacts_lpconfig, section, "emailcount", email_count);
			             
	for(int i=0;i<email_count;i++)
	{
	    sprintf(email_index,"email_%d",i + 1);
		if(__emailtype_enum_to_str(item->emails[i].type) != NULL)
			sprintf(email_mix_info, "%s:%s", 
			        __emailtype_enum_to_str(item->emails[i].type), 
			        item->emails[i].szemail);
		else
			sprintf(email_mix_info, "%s", item->emails[i].szemail);

		lp_config_set_string(contacts_lpconfig, section, email_index, email_mix_info);
    }
	
	//voip, im, address
    lp_config_set_string(contacts_lpconfig, section, "voip", item->szvoip);
	lp_config_set_string(contacts_lpconfig, section, "im", item->szim);
	lp_config_set_string(contacts_lpconfig, section, "address", item->szaddress);

	//lp_config_sync(contacts_lpconfig);
	return 0;
}

int CContactsManager::sync_contact_config()
{ 
	int i;
	int counts;
	int writeindex = 0;
	char section[30];

	if(contacts_lpconfig == NULL)
	{
		g_error("_LpConfig = (null)");
		return -1;
	}

	if(contact_buf== NULL)
	{
		g_error("no contact_buf, save contact error!");
		return -1;
	}
	
	counts = get_contact_buf_count();
	cout << "\nbuf len: " << counts << endl;

	if(counts <= 0)
	{
		g_warning("empty mcall link!");
		return -1;
	}
	
	for(i = 0; i < counts; i++)
		write_contact_item(contact_buf[i], i);

    
	cout << "\n index: " << i << endl;
	sprintf(section, "contact_%i", i);
	while(i < MAX_CONTACT_COUNT)
	{
	    if(lp_config_has_section(contacts_lpconfig, section))
	    {
			lp_config_clean_section(contacts_lpconfig, section);
            cout << "\nclear index: " << i << endl;
		}
		
		i++;
	}
	
	return lp_config_sync(contacts_lpconfig);
}


int CContactsManager::get_contact_buf_count()
{	
    curCount= 0;
	
    for(int i=0;contact_buf[i] != NULL;i++)
	{
		curCount++;
	}
	
	return curCount;
}


int CContactsManager::get_contact_count()
{	
    curCount= 0;

	read_contact();
    for(int i=0;contact_buf[i] != NULL;i++)
	{
		curCount++;
	}
	
	return curCount;
}

int CContactsManager::get_contact_by_index(Contact **contact, int index)
{
	int len;
	Contact *_contact;
	
    read_contact();
    if(contact_buf == NULL)
		return -1;
	
	len = get_contact_count();
    if(index >= len)
		return -1;
	
	_contact = contact_buf[index];
	*contact = _contact;
	
	return 0;
}

int CContactsManager::get_contact_by_name(Contact **contact, const char *szname)
{
    int len;
	Contact *_contact;
	
    read_contact();
    if(contact_buf == NULL)
		return -1;
	
	len = get_contact_count();
	for(int i = 0;i < len; i++)
	{
    	_contact = contact_buf[i];
	 	if(strcmp(_contact->name.szfamily_name, szname) == 0)
	 	{
            cout << _contact->name.szfamily_name << endl;
			*contact = _contact;
			return i;
	 	}
    }

    return -1;
}

int CContactsManager::get_contact_by_letter(Contact **contact, const char *szletter)
{
    int len;
	Contact *_contact;

	read_contact();
    if(contact_buf == NULL)
		return -1;

	len = get_contact_count();
	for(int i = 0;i < len; i++)
	{
    	_contact = contact_buf[i];
        const char str[] = {_contact->name.szfamily_name[0], '\0'};
		         
	    if(strcmp(str, szletter) == 0)
	 	{
	 	   *contact = _contact;
		   return i;
	 	}
		else
		   cout << "not same:" << endl;
    }

    return -1;
}

int CContactsManager::get_contact_by_phone(Contact **contact,	const char *szphone)
{
    int len;
	int phone_count;
    gchar phone_index[20];
	gchar section_index[20];
	Contact *_contact;
	
	read_contact();
    if(contact_buf == NULL)
		return -1;
 
	len = get_contact_count();
	for(int i = 0;i < len; i++)
	{
	    sprintf(section_index,"contact_%i",i);
    	_contact = contact_buf[i];
        phone_count = lp_config_get_int(contacts_lpconfig,section_index,"phonecount",NULL);

		for(int j = 0; j < phone_count; j++)
		{
        	if(strcmp(_contact->phones[j].szphone, szphone) == 0)
	 	    {
            	*contact = _contact;
				return i;
	 	    }
			else
			{
				cout << "not same"<< endl;
			}
		}
	}

    return -1;
}

int CContactsManager::update_contact_by_index(Contact *contact, int index)
{
	int len;
	Contact *_contact;

	len = get_contact_count();
	if(index >= len)
		return -1;
	
	_contact = contact_buf[index];

	//name, group
	strcpy(_contact->name.szfamily_name, contact->name.szfamily_name);
	strcpy(_contact->name.szgiven_name, contact->name.szgiven_name);
	_contact->type = contact->type;

	//phone
	for(int i=0; i<MAX_PHONE_COUNT; i++)
	{
        strcpy(_contact->phones[i].szphone, contact->phones[i].szphone);
		_contact->phones[i].type = contact->phones[i].type;
	}

    //email
	for(int i=0; i<MAX_EMAIL_COUNT; i++)
	{
		strcpy(_contact->emails[i].szemail, contact->emails[i].szemail);
    	_contact->emails[i].type = contact->emails[i].type;
	}

	//im, voip, address
	strcpy(_contact->szim, contact->szim);
	strcpy(_contact->szvoip, contact->szvoip);
	strcpy(_contact->szaddress, contact->szaddress);

	//sync
	sync_contact_config();
	
    return 0;
}

int CContactsManager::add_contact(Contact *contact)
{
	int section_index;
	int len;
	
	read_contact();
	section_index = get_contact_count();
	
	//write
	len = get_contact_buf_count();
	contact_buf[len] = contact;

	//sync
	sync_contact_config();
}

int CContactsManager::add_contact_by_index(Contact *contact, int index)
{
	
}

int CContactsManager::delete_contact_by_index(int index)
{
	int section_index;
	int len;

	len = get_contact_count();
	cout << "len: " << len << endl;
	if(len == 0)
		return -1;

	if(len <= index)
		return -1;

    while(1)
    {
    	if(index + 1 == len)
    	{
			contact_buf[index] = NULL;
	        cout << "index: " << index << endl;		
    		break;
		}    
		contact_buf[index] = contact_buf[index + 1];
        index++;
    }
	
	//sync
	sync_contact_config();
}

int CContactsManager::delete_contact_all()
{
	
}

//help
void CContactsManager::Show_contact_buf()
{
    read_contact();
	for(int i=0;contact_buf[i] != NULL;i++)
		cout << "show " << i << ": " << contact_buf[i]->name.szfamily_name << endl;
}

//validate
int CContactsManager::validate()
{
    
}

//sort
void CContactsManager::sort_by_name()	
{
	
}

void CContactsManager::sort_by_letter()		
{
	
}

int CContactsManager::save_file()
{
	
}

//enum
const gchar* CContactsManager::__grouptype_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
		case GT_FAMILY:
			return "GT_FAMILY";
			break;
		case GT_RELATIVES:
			return "GT_RELATIVES";
			break;
		case GT_COLLEAGUES:
			return "GT_COLLEAGUES";
			break;
		case GT_FRIENDS:
			return "GT_FRIENDS";
			break;
		case GT_MANUFACTURERS:
			return "GT_MANUFACTURERS";
			break;
		case GT_OTHER:
			return "GT_OTHER";
			break;
		case GT_CUSTOM:
			return "GT_CUSTOM";
			break;
	}
	g_warning("Invalid grouptype enum value.");
	return "NULL";
}

const gchar* CContactsManager::__phonetype_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
	    case PT_HOME:
			return "PT_HOME";
			break;
		case PT_MOBILE:
			return "PT_MOBILE";
			break;
		case PT_WORK:
			return "PT_WORK";
			break;
		case PT_WORK_FAX:
			return "PT_WORK_FAX";
			break;
		case PT_HOME_FAX:
			return "PT_HOME_FAX";
			break;
		case PT_OTHER:
			return "PT_OTHER";
			break;
		case PT_CUSTOM:
			return "PT_CUSTOM";
			break;
		}
		g_warning("Invalid phonetype enum value.");
		return "NULL";
}

const gchar* CContactsManager::__emailtype_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
	    case EMT_HOME:
			return "EMT_HOME";
			break;
		case EMT_WORK:
			return "EMT_WORK";
			break;
		case EMT_OTHER:
			return "EMT_OTHER";
			break;
		case EMT_CUSTOM:
			return "EMT_CUSTOM";
			break;
	}
	g_warning("Invalid emailtype enum value.");
	return "NULL";
}

GroupType CContactsManager::__grouptype_str_to_enum(const gchar *enum_str)
{
	if(strcmp(enum_str, "GT_FAMILY") == 0)
		 return GT_FAMILY;
  
	if(strcmp(enum_str, "GT_RELATIVES") == 0)
		 return GT_RELATIVES;
  
	if(strcmp(enum_str, "GT_COLLEAGUES") == 0)
		  return GT_COLLEAGUES;
  
	if(strcmp(enum_str, "GT_FRIENDS") == 0)
		  return GT_FRIENDS;
     
	if(strcmp(enum_str, "GT_MANUFACTURERS") == 0)
		  return GT_MANUFACTURERS;

	if(strcmp(enum_str, "GT_OTHER") == 0)
		  return GT_OTHER;

	if(strcmp(enum_str, "GT_CUSTOM") == 0)
		  return GT_CUSTOM;
	
	g_warning("Invalid grouptype enum value %s", enum_str);
	return (GroupType)-1;
 }

PhoneType CContactsManager::__phonetype_str_to_enum(const gchar *enum_str)
{
	if(strcmp(enum_str, "PT_HOME") == 0)
		return PT_HOME;

	if(strcmp(enum_str, "PT_MOBILE") == 0)
		return PT_MOBILE;

	if(strcmp(enum_str, "PT_WORK") == 0)
		return PT_WORK;

	if(strcmp(enum_str, "PT_WORK_FAX") == 0)
		return PT_WORK_FAX;

	if(strcmp(enum_str, "PT_HOME_FAX") == 0)
		return PT_HOME_FAX;
	
	if(strcmp(enum_str, "PT_OTHER") == 0)
		return PT_OTHER;
	
	if(strcmp(enum_str, "PT_CUSTOM") == 0)
		return PT_CUSTOM;
	
	g_warning("Invalid phonetype enum value %s", enum_str);
	return (PhoneType)-1;
}

EMailType CContactsManager::__emailtype_str_to_enum(const gchar *enum_str)
{
	if(strcmp(enum_str, "EMT_HOME") == 0)
		return EMT_HOME;

	if(strcmp(enum_str, "EMT_WORK") == 0)
		return EMT_WORK;

	if(strcmp(enum_str, "EMT_OTHER") == 0)
		return EMT_OTHER;

	if(strcmp(enum_str, "EMT_CUSTOM") == 0);
		return EMT_CUSTOM;
	
	g_warning("Invalid emailtype enum value %s", enum_str);
	return (EMailType)-1;
}
/*int CContactsManager::save_mcall_configs(LpConfig *config)
   { 
	int i;
	int counts;
	int writeindex = 0;

	if(config == NULL)
	{
		g_error("_LpConfig = (null)");
		return -1;
	}

	if(contactLink== NULL)
	{
		g_error("no mcall links, save mcalls error!");
		return -1;
	}
	
	counts = g_list_length(contactLink);

	if(counts <= 0)
	{
		g_warning("empty mcall link!");
		return -1;
	}
		
	for(i = 0; i < counts; i++)
	{
		write_mcall_item(config, (Contact *)g_list_nth_data(contactLink, i), i);
	}
	return lp_config_sync(config);
}

   int CContactsManager::delete_mcallink()
{
	int i = 0;
	int counts = 0;
	if(contactLink == NULL)
    {
		g_error("no mcall links");
		return -1;
	}
	else
	{
		counts = g_list_length(contactLink);
		for(i = 0; i < counts; i++)
		{
			g_message("delete mcall items : %d", i);
			g_free((Contact *)g_list_nth_data(contactLink, i));
		}
		g_list_free(contactLink);
		contactLink = NULL;
	}
}
*/
		

