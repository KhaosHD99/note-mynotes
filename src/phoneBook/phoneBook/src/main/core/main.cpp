#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "lpconfig.h"
#include "contacts.hpp"

//#include "mcallconfig.h"

int main()
{
    CContactsManager *manager = CContactsManager.get_instance;
	manager->test();
	//printf("%d",manager.testInt);
	/*int itemcounts, ret;
	struct _LpConfig *config = NULL;
	MediaFileInfo * item = NULL;
	char pathname[64];

	sprintf(pathname, "%s", "MCallConfig");

	config = lp_config_new(pathname);
	printf("start read : %s\r\n", pathname);

	mcall_config_read(config);
	
	printf("\n\n\n\n\n\n\n", itemcounts);
	
    itemcounts = get_mcallitem_counts();
	printf("get_mcallitem_counts : %d\r\n", itemcounts);

    
    MediaFileInfo *section = new MediaFileInfo;
    section->nFileID = 13;
	section->mPlayArea = AREA_B;
	section->nMCallType = VID_ONLY;
	
	printf("%d\r\n", section->nFileID);
	write_mcall_item(config, section, 13);
	save_mcall_configs(config);*/
	
	return 0;
}

