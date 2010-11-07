#ifndef _TIMELISTRESOLVER_HPP_
#define _TIMELISTRESOLVER_HPP_

#include "play_act.hpp"
#define DIRPATH            "/home/data/localfile"
#define FN_TYPE_BASE_VALUE 100000000  //使用的文件最长ID号
#define FULL_FILE_NAME_LEN		64

typedef enum { actFtH264,actFtJpeg,actAdOnLine } FileSwitch;//文件类型枚举


struct ACTINFO_AND_STOPTIME
{
	FileSwitch filetype;//主文件类型选择，要么是H264，要么是图片
	FNDWORD szActName; //节目编号名
	char szMainFileName[FULL_FILE_NAME_LEN];//主文件名
	char szMusicFileName[FULL_FILE_NAME_LEN];//音乐文件名
	char szAddImageFileName[FULL_FILE_NAME_LEN];//附加图片文件名
	char szURL[64];//附加URL
	char szPhoneCode[20];//附加电话号码
	int  PlayTime;//文件播放时间
	int endTime;//本节目必须完成的时间停止点	
};

/*----------------------------------------------------------------------------------------------
getActName

函数说明:
			供外界调用的接口函数,用于解析时间表，返回下一
			个播放节目的节目编号、主文件类型、主文件名及
			文件存放的绝对路径、音频文件名及文件存放的绝
			对路径、附加图片文件名及文件存放的绝对路径、
			节目播放时长、节目播放结束的时间截止点、节目
			附带的URL及电话号码等。假如函数正常运行，返回
			true;假如出现异常则返回false。            

参数说明: 
			window_type 指窗口的类型，如主窗口，右上角小窗口等。
			主窗口为0，右上窗口为1，右下窗口为2，如果传入其
			他参数，函数将提示错误。

			play_mode指窗口播放节目的方式，如响铃播放模式，默
			认播放模式等。话机响铃状态为0，挂机状态为1，非
			视频通话状态为2，普通播放状态为3。

			get_info用于装载函数返回的节目具体信息，其类型是一
			个结构体
                                                
特别说明:
			endTime为返回的时间段参数，如果这个返回值为-1，则
			说明本节目没有时间段的概念；如果为非-1值，那么
			这个值就是本节目播放必须结束的时间点。同时，当
			时间点到了当天最后的时间段，那么其结束点是24*3600
			这个点而并非是0。同时，主文件名不可为空字符串。
			如果其他文件不存在，则其文件名为空，文件名为空字
			符串。

-----------------------------------------------------------------------------------------------*/

class GetActName
{
	private:
		GetNextNameClass* pNextName;
		int actEndTime;
	static GetActName *instance;
		
	public:
		bool getActName(int window_type, int play_mode, ACTINFO_AND_STOPTIME* get_info);
		
		//该函数用于第一次获取节目时初始化使用，如果返回false则不必获取节目了，假如继续获取节目
		//那么将每获取一次节目则读一次时间表文件，这将导致系统瘫痪或消耗大量资源
		bool readPlayAct();

	public:
		static GetActName *getInstance(void) ;
		GetActName(){pNextName = GetNextNameClass::getInstance(); actEndTime = 0;}
		~GetActName(){}
};

#endif

