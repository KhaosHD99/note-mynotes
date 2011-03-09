#include "Advertisement.hpp"

#ifdef __cplusplus
extern "C" 
{
#endif

void *play_adver_thread(void *p_data)
{	
	AdverManager *adverManager = AdverManager::get_instance();
	adverManager->play_adver_thread(NULL);
}	
	
void *simulate_change_state(void *pData)
{	
    AdverManager *adverManager = AdverManager::get_instance();
	adverManager->simulateChangeState(NULL);
}

int change_state(int state_val)
{
	
}
#ifdef __cplusplus 
}
#endif

