#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "lpconfig.h"
#include "contacts.hpp"
#include "calllog.hpp"
#include "iostream"
using namespace std;

//#include "mcallconfig.h"

int main()//²âÊÔmain º¯Êý
{   
    //CContactsManager *manager = CContactsManager::get_instance();
    CCalllogManager *manager = CCalllogManager::get_instance();

	//add calllog
    CallLog *calllog = new CallLog;
	
	calllog->status = CL_DIALED;
	const char *str = "8";
	const char *str2 = "31325203";
	
	strcpy(calllog->szremote, str2); 
	strcpy(calllog->date.year, str); 
    strcpy(calllog->date.month, str);
    strcpy(calllog->date.day, str);
    strcpy(calllog->date.hour, str);
    strcpy(calllog->date.minute,str);
    strcpy(calllog->date.second, str);

	manager->add_calllog(CL_DIALED, calllog);
	manager->add_calllog(CL_MISSED, calllog);
	manager->add_calllog(CL_DIALED, calllog);
	manager->add_calllog(CL_RECEIVED, calllog);

	//manager->delete_calllog_by_status(CL_DIALED);
	//manager->delete_calllog_by_status(CL_MISSED);
	//manager->delete_calllog_by_index(CL_MISSED, 0);
	
	//manager->delete_contact_all();
    //manager->delete_contact_by_index(0);
    //manager->sort_by_letter();
    //manager->read_contact();
	//manager->get_section_from_config_file(0);
	//manager->test();
	//manager->test();
	//manager->read_contact();
	//manager->read_contact();
    //cout << manager->get_contact_buf_count() << endl;
    
	//find
    /*Contact *contact = new Contact;
	int ret = manager->get_contact_by_name(&contact, "li");
	//int ret = manager->get_contact_by_phone(&contact, "135399858");
	//int ret = manager->get_contact_by_letter(&contact, "x");
	//int ret = manager->get_contact_by_index(&contact, 0);
    if(ret == -1)
		cout << "\ncan not find any thing " << endl; 
	else
	{
		cout << "\nsame at: " << ret << endl; 
    	cout << "show: " << contact->name.szfamily_name << endl;
	}*/
    
	//add contact
    /*Contact *section = new Contact;
	memset(section, 0, sizeof(Contact));

	strcpy(section->name.szfamily_name,"xu");
	strcpy(section->name.szgiven_name,"zhenjie");

	section->phones[0].type = PT_HOME;
	strcpy(section->phones[0].szphone, "31325201");
	section->phones[1].type = PT_MOBILE;
	strcpy(section->phones[1].szphone, "13539982758");
	section->phones[2].type = PT_WORK;
	strcpy(section->phones[2].szphone, "12345678");

	section->emails[0].type = EMT_WORK;
	strcpy(section->emails[0].szemail, "xujiekoo@qq.com");
    section->emails[1].type = EMT_HOME;
	strcpy(section->emails[1].szemail, "163.com");
    
	strcpy(section->szvoip,"172.17");
	strcpy(section->szim,"466795229");
	strcpy(section->szaddress,"yuexu");

    manager->add_contact(section);
	manager->add_contact(section);
	manager->add_contact(section);*/
	//manager->add_contact(section);

    //update
    /*Contact *section = new Contact;
	memset(section, 0, sizeof(Contact));

	strcpy(section->name.szfamily_name,"wu");
	strcpy(section->name.szgiven_name,"yaoquan");

	section->phones[0].type = PT_HOME;
	strcpy(section->phones[0].szphone, "31325201");
	section->phones[1].type = PT_MOBILE;
	strcpy(section->phones[1].szphone, "13539982758");
    
	section->emails[0].type = EMT_WORK;
	strcpy(section->emails[0].szemail, "xujiekoo@qq.com");
    section->emails[1].type = EMT_HOME;
	strcpy(section->emails[1].szemail, "163.com");
    
	strcpy(section->szvoip,"172.17");
	strcpy(section->szim,"466795229");
	strcpy(section->szaddress,"yuexu");

    int ret = manager->update_contact_by_index(section, 2);
	if(ret == -1)
		printf("fail");*/
	//show
	//manager->Show_contact_buf();

    //compare
   /* Contact *section = new Contact;
	memset(section, 0, sizeof(Contact));

	strcpy(section->name.szfamily_name,"xu");
	strcpy(section->name.szgiven_name,"jie");

	const char *szname = "xu";
	if(strcmp(section->name.szfamily_name, szname) == 0)
	{
    	cout << "\n  same   " << endl; 
	}
	else
	{
        cout << "\n  not same   " << endl; 
	}*/
	
    return 0;
}

