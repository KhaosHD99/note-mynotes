#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calllog.hpp"
#include "lpconfig.h"
#include "iostream"
using namespace std;

CCalllogManager::CCalllogManager()     
{
    init();
}

void CCalllogManager::init()
{
	calllog_lpconfig = lp_config_new("CallLog.cfg");

	init_log(&calllog_missed);
	init_log(&calllog_received);
	init_log(&calllog_dailed);
}

void CCalllogManager::init_log(CallLog_Info *calllog_info)
{
	calllog_info->count = 0;
	calllog_info->calllog_buf = new CallLog*[MAX_CALLLOG_COUNT];

	for(int i = 0; i < MAX_CALLLOG_COUNT; i++)
	{
		calllog_info->calllog_buf[i] = NULL;
	}	
}

void CCalllogManager::uninit()
{
	uninit_log(&calllog_missed);
	uninit_log(&calllog_received);
	uninit_log(&calllog_dailed);
	
	//destory
	lp_config_destroy(calllog_lpconfig);
}

void CCalllogManager::uninit_log(CallLog_Info *calllog_info)
{
	for(int i = 0; i < calllog_info->count;	i++)
	{
		if(calllog_info->calllog_buf[i])
			delete calllog_info->calllog_buf[i];
		calllog_info->calllog_buf[i] = NULL;
	}
	delete calllog_info->calllog_buf;
	calllog_info->calllog_buf = NULL;
}

CCalllogManager* CCalllogManager::calllog_instance =  NULL;
CCalllogManager* CCalllogManager::get_instance()
{
	calllog_instance = new CCalllogManager;
	return calllog_instance;
}

void CCalllogManager::test()
{
	gchar section_index[50];
	CallLog *calllog;
	int index = 1;
	 	
	sprintf(section_index, "%s%i", CLOG_CALLLOG_INDEX, index);
	cout << section_index << endl;
}

CallLog* CCalllogManager::get_section_from_config_file(int index)
{
	gint calllogindex=-1,statusIndex=-1,duration=-1;
	const gchar *tmp;
	gchar section_index[50];
	CallLog *calllog;
	 	
	sprintf(section_index, "%s%i", CLOG_CALLLOG_INDEX, index);
	
	//check
	if (!lp_config_has_section(calllog_lpconfig, section_index))
	{
		g_error("find %s error\r\n", section_index);
		return NULL;
	}
	
	calllog = g_new0(CallLog,1);
	memset(calllog , 0, sizeof(CallLog));

	tmp = lp_config_get_string(calllog_lpconfig, section_index, CLOG_STATUS, NULL);

	if(tmp != NULL && __clstatus_str_to_enum(tmp) != CL_NON)
		calllog->status = __clstatus_str_to_enum(tmp);

	//判断日志类型，从配置文件中读出相应的数据
	if(calllog->status == CL_NON)           
	{
		free(calllog);
		return NULL;
	}
	else if(calllog->status == CL_MISSED)
	{
		statusIndex = lp_config_get_int(calllog_lpconfig,section_index,CLOG_MISSED_INDEX,NULL);
		if(statusIndex != -1)
		{
			calllog->status_index = statusIndex;
			statusIndex = -1;
		}
		tmp = lp_config_get_string(calllog_lpconfig,section_index,CLOG_REMOTE_FROM,NULL);
		if(tmp != NULL)
			strcpy(calllog->szremote, tmp);
	}
	else if(calllog->status == CL_RECEIVED)
	{
		statusIndex = lp_config_get_int(calllog_lpconfig,section_index,CLOG_RECEIVED_INDEX,NULL);
		if(statusIndex != -1)
		{
			calllog->status_index = statusIndex;
			statusIndex = -1;
		}
		tmp = lp_config_get_string(calllog_lpconfig,section_index,CLOG_REMOTE_FROM,NULL);
		if(tmp != NULL)
			strcpy(calllog->szremote, tmp);
	}
	else if(calllog->status == CL_DIALED)
	{
		statusIndex = lp_config_get_int(calllog_lpconfig,section_index,CLOG_DIALED_INDEX,NULL);
		if(statusIndex != -1)
		{
			calllog->status_index = statusIndex;
			statusIndex = -1;
		}
		tmp = lp_config_get_string(calllog_lpconfig,section_index,CLOG_REMOTE_TO,NULL);
		if(tmp != NULL)
			strcpy(calllog->szremote, tmp);
	}	
	
	tmp = lp_config_get_string(calllog_lpconfig,section_index,CLOG_START_DATE,NULL);

	//将const gchar 类型的时间数据放到char 中，便于分割
	char buff[100];	
	for(int i=0; tmp[i]!= '\0'; i++)
	{
		buff[i] = tmp[i];
	}
	printf("start_date :%s\n",buff);
	
	//先将时间分割成两段,例如:2010-8-11 14:48:33   --> 2010-8-11和14:48:33
    char *p,*q;	
	p = strtok(buff, " ");
	q = strtok(NULL, "");
	
	if(p) 
	{
		printf("first: %s\n", p);	
		
		p = strtok(p,"-");
		strcpy(calllog->date.year, p);
		printf("calllog->date.year: %s\n", calllog->date.year);
		
		p = strtok(NULL,"-");
		strcpy(calllog->date.month, p);
		printf("calllog->date.month: %s\n", p);
		
		p = strtok(NULL,"-");
		strcpy(calllog->date.day, p);
		printf("calllog->date.day: %s\n", p);
	}	
	else
	{	
		free(calllog);
		return NULL;
	}
	if(q) 
	{
		printf("second: %s\n", q);	
		
		q = strtok(q,":");
		strcpy(calllog->date.hour,q);
		printf("calllog->date.hour: %s\n", calllog->date.hour);
		
		q = strtok(NULL,":");
		strcpy(calllog->date.minute,q);
		printf("calllog->date.minute: %s\n", calllog->date.minute);
		
		q = strtok(NULL,":");
		strcpy(calllog->date.second,q);
		printf("calllog->date.second: %s\n", calllog->date.second);	

	}
	else
	{	
		free(calllog);
		return NULL;
	}
	
	duration = lp_config_get_int(calllog_lpconfig,section_index,CLOG_DURATION,NULL);
	if(duration == -1)
	{
		free(calllog);
		return NULL;
	}
	calllog->date.duration = duration;
		
	g_message("status       : %s", __clstatus_enum_to_str(calllog->status));
	g_message("status_index : %d", calllog->status_index);
	g_message("szremote     : %s", calllog->szremote);
	g_message("start_date   : %s", tmp);
	g_message("duration     : %d", calllog->date.duration);
	printf("\n\n");

	return calllog;
}

int CCalllogManager::read_calllog()
{
	CallLog *calllog = new CallLog;	
	
	if(calllog_lpconfig == NULL)
	{
		g_error("_LpConfig = (null)");
		return NULL;
	}
	
	for (int i=0;(calllog = get_section_from_config_file(i)) != NULL;i++)
	{
		if(calllog->status == CL_MISSED)
		{
			calllog_missed.status = CL_MISSED;
			calllog_missed.calllog_buf[miss_count] = calllog;
			calllog_missed.count = ++miss_count;
			//printf("calllog_missed.status    :%d \n",calllog_missed.status);
		}
		if(calllog->status == CL_RECEIVED)
		{
			calllog_received.status = CL_RECEIVED;
			calllog_received.calllog_buf[receive_count] = calllog;
			calllog_received.count = ++receive_count;
			//printf("calllog_received.status    :%d \n",calllog_received.status);
		}
		if(calllog->status == CL_DIALED)
		{
			calllog_dailed.status = CL_DIALED;
			calllog_dailed.calllog_buf[dail_count] = calllog;
			calllog_dailed.count = ++dail_count;
			//printf("calllog_dailed.status    :%d \n",calllog_dailed.status);
		}
		all_count++;
    }
}

int CCalllogManager::write_calllog_item(CallLog *item, int index, int status_index)
{
	gchar section_index[50];
	char str[10]; 	

    sprintf(section_index, "%s%i", CLOG_CALLLOG_INDEX, index);

	//status, status_index, szremote
	if(item->status == CL_MISSED)
	{
		lp_config_set_string(calllog_lpconfig, section_index, CLOG_STATUS, __clstatus_enum_to_str(item->status));
		lp_config_set_int(calllog_lpconfig, section_index, CLOG_MISSED_INDEX, status_index);
		lp_config_set_string(calllog_lpconfig, section_index, CLOG_REMOTE_FROM, item->szremote);
	}
	else if(item->status == CL_RECEIVED)
	{
		lp_config_set_string(calllog_lpconfig, section_index, CLOG_STATUS, __clstatus_enum_to_str(item->status));
		lp_config_set_int(calllog_lpconfig, section_index, CLOG_RECEIVED_INDEX, status_index);
		lp_config_set_string(calllog_lpconfig, section_index, CLOG_REMOTE_FROM, item->szremote);
	}
	else if(item->status == CL_DIALED)
	{
		lp_config_set_string(calllog_lpconfig, section_index, CLOG_STATUS, __clstatus_enum_to_str(item->status));
		lp_config_set_int(calllog_lpconfig, section_index, CLOG_DIALED_INDEX, status_index);
		lp_config_set_string(calllog_lpconfig, section_index, CLOG_REMOTE_TO, item->szremote);
	}

	//time
	char datetime[64] = "";

	sprintf(datetime, "%s-%s-%s %s:%s:%s",
		    item->date.year, item->date.month,
		    item->date.day, item->date.hour,
		    item->date.minute, item->date.second);
 
	printf("start_date    :%s\n", datetime);
	
	lp_config_set_string(calllog_lpconfig, section_index, CLOG_START_DATE, datetime);

	lp_config_set_int(calllog_lpconfig, section_index, CLOG_DURATION,item->date.duration);
				
	//sync
	return lp_config_sync(calllog_lpconfig);
}

int CCalllogManager::sync_contact_config()
{
    
	//sync
	
}

//CRUD
int CCalllogManager::get_calllog_count()
{	
	printf("all_count  : %d",all_count);
	if(all_count == 0)
	{
		//load_calllog_from_file();		
	}
    return all_count;
}

int CCalllogManager::get_calllog_count_by_type(CLSTATUS status)
{
	if(status == CL_MISSED)
	{	
		return miss_count;
	}
	if(status == CL_RECEIVED)
	{			
		return receive_count;
	}
	if(status == CL_DIALED)
	{			
		return dail_count;
	}
}

int CCalllogManager::get_calllog_by_index(CLSTATUS status,int index, CallLog *calllog)
{

}

int CCalllogManager::add_calllog(CLSTATUS status, CallLog *calllog)
{
	int section_index,result = -1;
	//先取得配置文件的长度
	if(all_count == 0)
	{
		read_calllog();
	}
	section_index = all_count;//g_list_length(gcalllogLink); 
	printf("section_index       :%d \n",section_index);	
		
	//写入配置文件中
	if(status == CL_MISSED)
	{			
		result = write_calllog_item(calllog, section_index, miss_count++); 
	}
	if(status == CL_RECEIVED)
	{			
		result = write_calllog_item(calllog, section_index, receive_count++);
	}
	if(status == CL_DIALED)
	{			
		result = write_calllog_item(calllog, section_index, dail_count++);
	}
    //result = write_calllog_item(calllog_lpconfig, calllog, section_index, ); 
	printf("result              :%d \n",result);

	if(result == 0)
	{	
		all_count++;
		if(status == CL_MISSED)
		{			
			calllog_missed.count = miss_count;
			calllog_missed.status = CL_MISSED;
			calllog_missed.calllog_buf[miss_count] = calllog;
			//printf("calllog_missed.status    :%d \n",calllog_missed.status);
		}
		if(status == CL_RECEIVED)
		{			
			calllog_received.count = receive_count;
			calllog_received.status = CL_RECEIVED;
			calllog_received.calllog_buf[receive_count] = calllog;
			//printf("calllog_received.status    :%d \n",calllog_received.status);
		}
		if(status == CL_DIALED)
		{			
			calllog_dailed.count = dail_count;
			calllog_dailed.status = CL_DIALED;
			calllog_dailed.calllog_buf[dail_count] = calllog;
			//printf("calllog_dailed.status    :%d \n",calllog_dailed.status);
		}
		printf("Successful write calllog section !\n");
	}
	else
		printf("Failed to write calllog section !\n");
}

int CCalllogManager::delete_calllog_by_index(CLSTATUS status, int index)
{
	gchar section_title[64];
	char str[10];

	if(status == CL_MISSED)
	{			
		sprintf(str,"%i",index);                                   //将int转化为char
		strcpy(section_title,CLOG_CALLLOG_INDEX);	               //
		strcat(section_title,str);                                 //构造calllg_index
		
		//处理内存中的数据
		for(int i=index;i<calllog_missed.count-1;i++)
		{//数组后面的往前推，覆盖删除的节点
			calllog_missed.calllog_buf[i] = calllog_missed.calllog_buf[i+1];
		}
		//清除数组最后面一个多余节点
		delete calllog_missed.calllog_buf[miss_count-1];
		calllog_missed.calllog_buf[miss_count-1] = NULL;
		
		miss_count--;              //相应项数减一	
		calllog_missed.count = miss_count;
		all_count--;		       //总数减一
	}
	if(status == CL_RECEIVED)
	{			
		sprintf(str,"%i",miss_count + index);                      //将int转化为char
		strcpy(section_title,CLOG_CALLLOG_INDEX);	               //
		strcat(section_title,str);                                 //构造calllg_index
		
		for(int i=index;i<calllog_received.count-1;i++)
		{
			calllog_received.calllog_buf[i] = calllog_received.calllog_buf[i+1];
		}
		delete calllog_received.calllog_buf[receive_count-1];
		calllog_received.calllog_buf[receive_count-1] = NULL;
		
		receive_count--;              
		calllog_received.count = receive_count;
		all_count--;		       
	}
	if(status == CL_DIALED)
	{			
		sprintf(str,"%i",miss_count + receive_count + index);      //将int转化为char
		strcpy(section_title,CLOG_CALLLOG_INDEX);				   //
		strcat(section_title,str);                                 //构造calllg_index

		//处理内存中的数据
		for(int i=index;i<calllog_dailed.count-1;i++)
		{//数组后面的往前推，覆盖删除的节点
			calllog_dailed.calllog_buf[i] = calllog_dailed.calllog_buf[i+1];
		}
		//清除数组最后面一个多余节点
		delete calllog_dailed.calllog_buf[dail_count-1];
		calllog_dailed.calllog_buf[dail_count-1] = NULL;
		
		dail_count--;              //相应项数减一	
		calllog_dailed.count = dail_count;
		all_count--;		       //总数减一
	}

	//检查配置文件中是否存在该节点
	if (!lp_config_has_section(calllog_lpconfig, section_title))
	{
		g_error("The section  %s not exit !\r\n", section_title);
		return NULL;
	}
	
	//根据结点头清除节点
	lp_config_clean_section(calllog_lpconfig,section_title);
	printf("clean section : %s \n",section_title);
	
	//同步回配置文件
	lp_config_sync(calllog_lpconfig);

	int result = -1;
	
	//写入配置文件中
	for(int i=0;i<miss_count;i++)
	{
		result = write_calllog_item(calllog_missed.calllog_buf[i], i, i); 
		if(result == 0)
			printf("Successful write calllog section : %d !\n",i);
		else
			printf("Failed to write calllog section  : %d !\n",i);
	}
	for(int i=0;i<receive_count;i++)
	{
		result = write_calllog_item(calllog_received.calllog_buf[i], miss_count + i, i); 
		if(result == 0)
			printf("Successful write calllog section : %d !\n",i);
		else
			printf("Failed to write calllog section  : %d !\n",i);
	}
	for(int i=0;i<dail_count;i++)
	{
		result = write_calllog_item(calllog_dailed.calllog_buf[i], miss_count + receive_count + i, i); 
		if(result == 0)
			printf("Successful write calllog section : %d !\n",i);
		else
			printf("Failed to write calllog section  : %d !\n",i);
	}
}

int CCalllogManager::delete_calllog_by_status(CLSTATUS status)
{

}

//sort
void CCalllogManager::sort_by_date()
{

}

const gchar* CCalllogManager::__clstatus_enum_to_str(int enum_val)
{
	switch(enum_val)
	{
		case CL_NON:
			return CL_NON_str;
			break;
		case CL_MISSED:
			return CL_MISSED_str;
			break;
		case CL_RECEIVED:
			return CL_RECEIVED_str;
			break;
		case CL_DIALED:
			return CL_DIALED_str;
			break;
	}
	g_warning("Invalid clstatus enum value.");
	return "NULL";
}

CLSTATUS CCalllogManager::__clstatus_str_to_enum(const char *enum_str)
{	

	if(strncmp(enum_str, CL_MISSED_str,strlen(CL_MISSED_str)) == 0)
		return CL_MISSED;

	if(strncmp(enum_str, CL_RECEIVED_str,strlen(CL_RECEIVED_str)) == 0)
		return CL_RECEIVED;

	if(strncmp(enum_str, CL_DIALED_str,strlen(CL_DIALED_str)) == 0)
		return CL_DIALED;

	g_warning("Invalid clstatus enum value %s", enum_str);
	return CL_NON;
}
