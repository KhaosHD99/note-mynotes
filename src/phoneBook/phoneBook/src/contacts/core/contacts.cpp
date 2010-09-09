#include <stdio.h>
#include "contacts.hpp"
#include "lpconfig.h"
#include "iostream"
using namespace std;

    void CContactsManager::init()
    {
    	contactLink = NULL;
    }
    void CContactsManager::uninit()
    {
    	
	}

    CContactsManager* CContactsManager::contacts_instance = NULL;
	
	CContactsManager *CContactsManager::get_instance()
	{
		contacts_instance = new CContactsManager;
    	return contacts_instance;
	}

    void CContactsManager::contacts_read(LpConfig *config)
    {
		int i;
		GList *contactsList;
		Contact* mi;
		if(config == NULL)
		{
			g_error("_LpConfig = (null)");
			return ;
		}
		delete_mcallink();
		for (i=0;(mi = mcallitem_new_from_config_file(config,i)) != NULL;i++)
		{
			contactLink = g_list_append(contactLink,(gpointer)mi);
    	}
	}

    
	Contact* CContactsManager::mcallitem_new_from_config_file(LpConfig *config, int index)
	{
		gint mcallindex;
		const gchar *tmp;
		//const char *tmp;
		gchar section_title[50];
		Contact *contact;
		
		sprintf(section_title,"mcall_%i",index);
		
		if (!lp_config_has_section(config, section_title))
		{
			g_error("find %s error\r\n", section_title);
			return NULL;
		}
		contact = g_new0(Contact,1);
		memset(contact, 0, sizeof(Contact));
	
		tmp = lp_config_get_string(config,section_title,"family_name",NULL);
		if(tmp != NULL && strlen(tmp) <= MAX_NAME_LEN)
			strcpy(contact->name.szfamily_name,tmp);

		tmp = lp_config_get_string(config,section_title,"given_name",NULL);
		if(tmp != NULL && strlen(tmp) <= MAX_NAME_LEN)
			strcpy(contact->name.szgiven_name,tmp);

		
		cout << contact->name.szfamily_name << endl;
		cout << contact->name.szgiven_name << endl;
       // g_message("\n%s", tmp);
		
      //  tmp = lp_config_get_string(config,section_title,"given_name",NULL);
	  //  strcpy(contact->name.szfamily_name,tmp);
	  //	g_message("\n%s", tmp);

		
		//tmp=lp_config_get_string(config,item,"name",NULL);
		//g_message("name   : %s", tmp);
	
		/*obj->mPlayArea = __playarea_str_to_enum(tmp);
		if((int)(obj->mPlayArea) == -1)
		{
			free(obj);
			return NULL;
		}
		tmp=lp_config_get_string(config,item,"playtype",NULL);
		g_message("playtype   : %s", tmp);
	
		obj->nMCallType = __playtype_str_to_enum(tmp);*/
	
		/*if((int)(obj->nMCallType) == -1)
		{
			free(obj);
			return NULL;
		}
	
		switch(obj->nMCallType)
		{
			case PIC_ONLY:
			case GIF_ONLY:
				if(get_mcall_file_define(config, item, obj, PIC_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
				break;
			case VID_ONLY:
				if(get_mcall_file_define(config, item, obj, VID_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
				break;
			case AUD_ONLY:
				if(get_mcall_file_define(config, item, obj, AUD_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
				break;
			case PIC_AUD:
			case GIF_AUD:
				if(get_mcall_file_define(config, item, obj, PIC_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
	
				if(get_mcall_file_define(config, item, obj, AUD_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
				break;
			case VID_AUD:
				if(get_mcall_file_define(config, item, obj, VID_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
				if(get_mcall_file_define(config, item, obj, AUD_ONLY) != 0)
				{
					free(obj);
					return NULL;
				}
				break;
			default:
				g_warning("Invalid playtype enum value. %d", obj->nMCallType);
				free(obj);
				return NULL;
		}
	*/
		return contact;
	}

    int CContactsManager::write_mcall_item(LpConfig *config, Contact *item, int index)
    {
        /* GroupTpye type;					                   //×é±ð
	      Phone phones[MAX_PHONE_COUNT];
	      Email emails[MAX_EMAIL_COUNT];
	      char szvoip[MAX_VOIP_LEN];
	      char szim[MAX_IM_LEN];
	      char szaddress[MAX_ADDRESS_LEN];*/
		gchar key[50];
		gchar phone_index[20];
		gchar *tmp;
		int a = 5;
        
		sprintf(key,"mcall_%i",index);
	
		lp_config_set_string(config, key, "family_name",item->name.szfamily_name);
        lp_config_set_string(config, key, "given_name", item->name.szgiven_name);
        lp_config_set_string(config, key, "grouptype", __grouptype_enum_to_str(item->type));
        lp_config_set_int(config, key, "phonecount",
			              sizeof(item->phones)/sizeof(item->phones[0]));
				             
		for(int i=0;i<(sizeof(item->phones)/sizeof(item->phones[0]));i++)
		{
		    sprintf(phone_index,"phone_%d",i + 1);
			lp_config_set_string(config, key, phone_index, 
				                 __phonetype_enum_to_str(item->phones[i].type));
        }
		lp_config_set_string(config, key, "emailtype", __emailtype_enum_to_str(item->phones[0].type));
        lp_config_set_string(config, key, "voip", item->szvoip);
		lp_config_set_string(config, key, "im", item->szim);
		lp_config_set_string(config, key, "address", item->szaddress);
        
		//lp_config_set_string(config, key, "jpegfile", item->szJpegFile);
		//lp_config_set_string(config, key, "videofile", item->szVideoFile);
		//lp_config_set_string(config, key, "audiofile", item->szAudioFile);
		return 0;
	}

    int CContactsManager::save_mcall_configs(LpConfig *config)
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
		
	int CContactsManager::get_contact_count()
    {	
    	return curCount;
	}
	
	int CContactsManager::get_contact_by_index(Contact *contact,	int index)
	{
    	
	}
	
	int CContactsManager::get_contact_by_name(Contact **contact,	const char *szname)
	{
    	
	}
	
	int CContactsManager::get_contact_by_letter(Contact **contact, const char *szletter)
	{
    	
	}
	
	int CContactsManager::get_contact_by_phone(Contact **contact,	const char *szphone)
	{
    	
	}
	
	int CContactsManager::update_contact(Contact *contact)
	{
		
	}

	int CContactsManager::update_contact_by_index(Contact *contact, int index)	
	{
    	
	}
	
	int CContactsManager::add_contact(Contact *contact)
	{
    	
	}
	
	int CContactsManager::add_contact_by_index(Contact *contact, int index)
	{
    	
	}
	
	int CContactsManager::delete_contact_by_index(int index)
	{
    	
	}
	
	int CContactsManager::delete_contact_all()
	{
    	
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


	const gchar* CContactsManager::__grouptype_enum_to_str(int enum_val)
    {
		switch(enum_val)
		{
			case GT_FAMILY:
				return "family";
				break;
			case GT_RELATIVES:
				return "relatives";
				break;
			case GT_COLLEAGUES:
				return "colleagues";
				break;
			case GT_FRIENDS:
				return "friend";
				break;
			case GT_MANUFACTURERS:
				return "manufacturers";
				break;
			case GT_OTHER:
				return "other";
				break;
			case GT_CUSTOM:
				return "custom";
				break;
		}
		g_warning("Invalid playtype enum value.");
		return "NULL";
	}

	
	const gchar* CContactsManager::__phonetype_enum_to_str(int enum_val)
	{
		switch(enum_val)
		{
		    case PT_HOME:
				return "home";
				break;
			case PT_MOBILE:
				return "mobile";
				break;
			case PT_WORK:
				return "work";
				break;
			case PT_WORK_FAX:
				return "work_fax";
				break;
			case PT_HOME_FAX:
				return "home_fax";
				break;
			case PT_OTHER:
				return "other";
				break;
			case PT_CUSTOM:
				return "customer";
				break;
			}
			g_warning("Invalid playtype enum value.");
			return "NULL";
	}

	const gchar* CContactsManager::__emailtype_enum_to_str(int enum_val)
	{
		switch(enum_val)
		{
		    case EMT_HOME:
				return "home";
				break;
			case EMT_WORK:
				return "work";
				break;
			case EMT_OTHER:
				return "other";
				break;
			case EMT_CUSTOM:
				return "custom";
				break;
		}
		g_warning("Invalid playtype enum value.");
		return "NULL";
	}
	
	/*PlayArea __playarea_str_to_enum(const gchar *enum_str)
	{
		if(strcmp(enum_str, "AREA_A") == 0)
			return AREA_A;

		if(strcmp(enum_str, "AREA_B") == 0)
			return AREA_B;

		if(strcmp(enum_str, "AREA_C") == 0)
			return AREA_C;

		if(strcmp(enum_str, "AREA_D") == 0)
			return AREA_D;
		
		g_warning("Invalid playarea enum value %s", enum_str);
		return (PlayArea)-1;
	}*/
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

	void CContactsManager::test()
	{
    	printf("\ntest\n");
	}
		

