#include "Advertisement.hpp"

#ifdef __cplusplus
extern "C" 
{
#endif

void *play_adver_thread(void *p_data);

void *simulate_change_state(void *pData);

int change_state(int state_val);

#ifdef __cplusplus 
}
#endif

