#ifndef MCALL_CONFIG_H_
#define MCALL_CONFIG_H_

#include "mcallstructs.h"

#define MAX_MCALL_COUNT 12

extern MediaFileInfo stLocalMediaCallInfo[];

#ifdef __cplusplus
extern "C" {
#endif

void mcall_config_read(struct _LpConfig *config);

int write_mcall_item(struct _LpConfig *config, MediaFileInfo *item, int index);

int save_mcall_configs(struct _LpConfig *config);

int get_mcallitem_counts();

MediaFileInfo *get_mcallitem_by_index(int index);

int delete_mcallink();

#ifdef __cplusplus
}
#endif


#endif
