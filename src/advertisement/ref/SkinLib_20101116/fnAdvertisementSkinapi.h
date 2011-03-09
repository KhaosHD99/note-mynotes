#ifndef FNADVERTISEMENTSKINAPI_DEF_H
#define FNADVERTISEMENTSKINAPI_DEF_H

#define MAX_IMAGE_NAME_LEN		64
#define MAX_SUB_SIZE			1024
#define ADVER_PLAYER_NUM		5

//滚动字符串的行数
int row_count;

typedef struct AdverPlayerInfo
{
    //播放时长
	int advert_time;						
	//广告图片名称
	char image_name[MAX_IMAGE_NAME_LEN];		
	//滚动字符串
	char message[MAX_SUB_SIZE];				
}AdverPlayerInfo;

struct st_argvs
{
	int argc;
	char **argv;
	AdverPlayerInfo adver_info[ADVER_PLAYER_NUM];
};

#ifdef __cplusplus 
extern "C" 
{ 
#endif 
	
	/*************************************************************************************/
	/* 创建播放界面																		 */
	/*************************************************************************************/
	int init_play_window(struct st_argvs *argvs);				

	/*************************************************************************************/
	/* 驱动广告																			 */
	/*************************************************************************************/
	int Driving_Adver(int index, char *path, const char *message);		

	/*************************************************************************************/
	/* 判断创建播放界面是否完成															 */
	/*************************************************************************************/
	int Is_Create_Success();										

	/*************************************************************************************/
	/* 停止广告播放																		 */
	/*************************************************************************************/
	int Stop_Adver(int index);									

#ifdef __cplusplus 
} 
#endif

#endif
