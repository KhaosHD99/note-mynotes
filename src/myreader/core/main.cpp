#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "lpconfig.h"
#include "mcallconfig.h"

int main()
{
	int itemcounts, ret;
	struct _LpConfig *config = NULL;
	MediaFileInfo * item = NULL;
	char pathname[64];

	sprintf(pathname, "%s", "MCallConfig");

	config = lp_config_new(pathname);
	printf("start read : %s\r\n", pathname);

	mcall_config_read(config);
	//delete_mcallink();
	printf("\n\n\n\n\n\n\n", itemcounts);
	
    itemcounts = get_mcallitem_counts();
	printf("get_mcallitem_counts : %d\r\n", itemcounts);

    
    MediaFileInfo *section = new MediaFileInfo;
    section->nFileID = 13;
	section->mPlayArea = AREA_B;
	section->nMCallType = VID_ONLY;
	//section->szJpegFile = {'j','z'};
	//section->szVideoFile = {'j','z'};
	//section->szAudioFile = {'j','z'};
	printf("%d\r\n", section->nFileID);
	write_mcall_item(config, section, 13);
	save_mcall_configs(config);
	//delete_mcallink();
	//if(config != NULL)
//		lp_config_destroy(config);
	
//	config = NULL;
	return 0;
}

