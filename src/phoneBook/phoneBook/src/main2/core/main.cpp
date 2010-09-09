#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "lpconfig.h"
#include "contacts.hpp"

//#include "mcallconfig.h"

int main()
{
    CContactsManager *manager = CContactsManager::get_instance();
	int itemcounts, ret;
	struct _LpConfig *config = NULL;
	Contact * item = NULL;
	char pathname[64];

	sprintf(pathname, "%s", "Contacts.cfg");
    config = lp_config_new(pathname);
	printf("start read : %s\r\n", pathname);

	manager->contacts_read(config);
	
	printf("\n\n\n\n\n\n\n", itemcounts);

	//write
    Contact *section = new Contact;
	strcpy(section->name.szfamily_name,"xu");
	strcpy(section->name.szgiven_name,"jie");
    section->phones[0].type = PT_HOME;
	//section->phones[1].type = PT_HOME;
	
    manager->write_mcall_item(config, section, 15);
	manager->save_mcall_configs(config);
	return 0;
}

