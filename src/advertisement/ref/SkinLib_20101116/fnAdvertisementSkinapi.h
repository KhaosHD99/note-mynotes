#ifndef FNADVERTISEMENTSKINAPI_DEF_H
#define FNADVERTISEMENTSKINAPI_DEF_H

#define MAX_IMAGE_NAME_LEN		64
#define MAX_SUB_SIZE			1024
#define ADVER_PLAYER_NUM		5

//�����ַ���������
int row_count;

typedef struct AdverPlayerInfo
{
    //����ʱ��
	int advert_time;						
	//���ͼƬ����
	char image_name[MAX_IMAGE_NAME_LEN];		
	//�����ַ���
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
	/* �������Ž���																		 */
	/*************************************************************************************/
	int init_play_window(struct st_argvs *argvs);				

	/*************************************************************************************/
	/* �������																			 */
	/*************************************************************************************/
	int Driving_Adver(int index, char *path, const char *message);		

	/*************************************************************************************/
	/* �жϴ������Ž����Ƿ����															 */
	/*************************************************************************************/
	int Is_Create_Success();										

	/*************************************************************************************/
	/* ֹͣ��沥��																		 */
	/*************************************************************************************/
	int Stop_Adver(int index);									

#ifdef __cplusplus 
} 
#endif

#endif
