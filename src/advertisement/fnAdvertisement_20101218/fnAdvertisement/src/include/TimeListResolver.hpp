/*
* Copyright ���ݷ�����Ѷ���޹�˾
* All rights reserved.
* 
* �ļ����ƣ�TimeListResolver.hpp
* 
* ժ    Ҫ����ʱ�����н���
* 
* ��    �ߣ���ҫȪ
*
* �޸���:   �����
* 
* ����޸����ڣ�2010��11��19��
*/

#ifndef _TIMELISTRESOLVER_HPP_
#define _TIMELISTRESOLVER_HPP_

#include "PlayAct.hpp"
#define DIRPATH            "/home/data/localfile"
#define FN_TYPE_BASE_VALUE 100000000  //ʹ�õ��ļ��ID��
#define FULL_FILE_NAME_LEN		64

//�ļ�����ö��
typedef enum 
{ 
	actFtH264,
	actFtJpeg,
	actAdOnLine 
} FileSwitch;

const char FILE_TYPE_INFO[3][64] 
{ 
	"H264",
	"Jpeg",
	"OnLine"
};

struct ACTINFO_AND_STOPTIME
{
	//���ļ�����ѡ��Ҫô��H264��Ҫô��ͼƬ
	FileSwitch filetype;
	//��Ŀ�����
	FNDWORD szActName; 
	//���ļ���
	char szMainFileName[FULL_FILE_NAME_LEN];
	
	//�����ļ���
	char szMusicFileName[FULL_FILE_NAME_LEN];	
	//����ͼƬ�ļ���
	char szAddImageFileName[FULL_FILE_NAME_LEN];
	//����URL
	char szURL[64];
	//���ӵ绰����
	char szPhoneCode[20];
	//�ļ�����ʱ��
	int  PlayTime;
	//����Ŀ������ɵ�ʱ��ֹͣ��	
	int endTime;
};

/*******************************************************************************************************
getActName

����˵��:
			�������õĽӿں���,���ڽ���ʱ���������һ
			�����Ž�Ŀ�Ľ�Ŀ��š����ļ����͡����ļ�����
			�ļ���ŵľ���·������Ƶ�ļ������ļ���ŵľ�
			��·��������ͼƬ�ļ������ļ���ŵľ���·����
			��Ŀ����ʱ������Ŀ���Ž�����ʱ���ֹ�㡢��Ŀ
			������URL���绰����ȡ����纯���������У�����
			true;��������쳣�򷵻�false��            

����˵��: 
			window_type ָ���ڵ����ͣ��������ڣ����Ͻ�С���ڵȡ�
			������Ϊ0�����ϴ���Ϊ1�����´���Ϊ2�����������
			����������������ʾ����

			play_modeָ���ڲ��Ž�Ŀ�ķ�ʽ�������岥��ģʽ��Ĭ
			�ϲ���ģʽ�ȡ���������״̬Ϊ0���һ�״̬Ϊ1����
			��Ƶͨ��״̬Ϊ2����ͨ����״̬Ϊ3��

			get_info����װ�غ������صĽ�Ŀ������Ϣ����������һ
			���ṹ��
                                                
�ر�˵��:
			endTimeΪ���ص�ʱ��β���������������ֵΪ-1����
			˵������Ŀû��ʱ��εĸ�����Ϊ��-1ֵ����ô
			���ֵ���Ǳ���Ŀ���ű��������ʱ��㡣ͬʱ����
			ʱ��㵽�˵�������ʱ��Σ���ô���������24*3600
			������������0��ͬʱ�����ļ�������Ϊ���ַ�����
			��������ļ������ڣ������ļ���Ϊ�գ��ļ���Ϊ����
			������
*******************************************************************************************************/

class GetActName
{
	private:
		GetNextNameClass* pNextName;
		int actEndTime;
		static GetActName *instance;
		
	public:
		bool get_current_act_name(int area_type, int state, ACTINFO_AND_STOPTIME* get_info);
		
		//�ú������ڵ�һ�λ�ȡ��Ŀʱ��ʼ��ʹ�ã��������false�򲻱ػ�ȡ��Ŀ�ˣ����������ȡ��Ŀ
		//��ô��ÿ��ȡһ�ν�Ŀ���һ��ʱ����ļ����⽫����ϵͳ̱�������Ĵ�����Դ
		bool read_play_act();
		
	public:
		static GetActName *get_instance(void);
		GetActName(){pNextName = GetNextNameClass::get_instance(); actEndTime = 0;}
		~GetActName(){}
};

#endif

