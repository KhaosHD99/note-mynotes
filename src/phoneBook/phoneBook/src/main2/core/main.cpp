#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "lpconfig.h"
#include "contacts.hpp"
#include "iostream"
using namespace std;

//#include "mcallconfig.h"

int main()//²âÊÔmain º¯Êý
{   
    CContactsManager *manager = CContactsManager::get_instance();

    

    //manager->read_contact();
	//manager->get_section_from_config_file(0);
	//manager->test();
	//manager->test();
	//manager->read_contact();
	//manager->read_contact();
    //cout << manager->get_contact_buf_count() << endl;
    
	//find
    /*Contact *contact = new Contact;
	//int ret = manager->get_contact_by_name(&contact, "chen");
	//int ret = manager->get_contact_by_phone(&contact, "135399858");
	//int ret = manager->get_contact_by_letter(&contact, "x");
	int ret = manager->get_contact_by_index(&contact, 0);
    if(ret == -1)
		cout << "\ncan not find any thing " << endl; 
	else
	{
		cout << "\nsame at: " << ret << endl; 
    	cout << "show: " << contact->name.szfamily_name << endl;
	}*/
    
	//add contact
   /* Contact *section = new Contact;
	memset(section, 0, sizeof(Contact));

	strcpy(section->name.szfamily_name,"xu");
	strcpy(section->name.szgiven_name,"jie");

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

    manager->add_contact(section);*/

    //update
    Contact *section = new Contact;
	memset(section, 0, sizeof(Contact));

	strcpy(section->name.szfamily_name,"cai");
	strcpy(section->name.szgiven_name,"chaoxi");

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

    int ret = manager->update_contact_by_index(section, 1);
	if(ret == -1)
		printf("fail");
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

