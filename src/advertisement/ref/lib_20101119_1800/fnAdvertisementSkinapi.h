#ifndef FNADVERTISEMENTSKINAPI_DEF_H
#define FNADVERTISEMENTSKINAPI_DEF_H


enum{
	IAMGE = 0,					//图片
	VIDEO,						//视频
	STREAMING_MEDIA				//流媒体
};

typedef struct st_argvs
{
	int argc;
	char **argv;
}st_argvs;

#ifdef __cplusplus 
extern "C" 
{ 
#endif 

	/*******************************************************************************************/
	/* 创建广告时间线程,成功返回0，异常返回非零											       */
	/*******************************************************************************************/
	int init_play_window(struct st_argvs *argvs);	

	/*******************************************************************************************/
	/* 更改广告内容,成功返回0，异常返回非0 											           */
	/* 参数说明：区域，文件名，文件类型，滚动字符											   */
	/*******************************************************************************************/
	int change_area_player_info(int index, const char *filename, int advert_type, const char *message);

	/*******************************************************************************************/
	/*释放播放区													    					   */
	/*******************************************************************************************/
	void delete_playarea();

#ifdef __cplusplus 
} 
#endif

#endif
