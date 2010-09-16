#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "lpconfig.h"
#include "calllog.hpp"

//#include "mcallconfig.h"

int main()
{
	CCalllogManager *manager = CCalllogManager::get_instance();
	manager->test();


	/*CContactsManager *manager = CContactsManager::get_instance();
	manager->test();*/
	
	int itemcounts, ret;
	struct _LpConfig *config = NULL;
	CallLog * item = NULL;
	char pathname[64];
	sprintf(pathname, "%s", "CallLog.cfg");

	config = lp_config_new(pathname);
	printf("start read : %s\r\n", pathname);

	manager->calllog_read(config);
	
	itemcounts = manager->get_calllogitem_count();
	printf("get_calllogitem_counts : %d \n", itemcounts);

	CallLog *section = new CallLog;	
	section->status = CL_DIALED;
	//section->szremote = ;
	section->date.duration = 13;
	
	manager->write_calllog_item(config, section, 5);
	manager->save_calllog_configs(config);

	
	return 0;
}

