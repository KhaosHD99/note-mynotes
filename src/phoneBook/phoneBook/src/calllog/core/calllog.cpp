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
	init_log(&calllog_dialed);
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
	uninit_log(&calllog_dialed);
	
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
	gint calllogindex = -1, 
		 statusIndex = -1, 
		 duration = -1;
	const gchar *tmp = NULL;
	gchar *tmpcpy;
	gchar section_index[50];
	CallLog *calllog;
	 	
	sprintf(section_index, "%s%i", CLOG_CALLLOG_INDEX, index);
	
	//check status
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

	//missed, received, dailed
	if(calllog->status == CL_NON)           
	{
		free(calllog);
		return NULL;
	}
	else if(calllog->status == CL_MISSED)
	{
	    //status_index, remote
		statusIndex = lp_config_get_int(calllog_lpconfig, section_index, CLOG_MISSED_INDEX, NULL);
		if(statusIndex != -1)
		{
			calllog->status_index = statusIndex;
			statusIndex = -1;
		}
		
		tmp = lp_config_get_string(calllog_lpconfig, section_index, CLOG_REMOTE_FROM, NULL);
		if(tmp != NULL)
			strcpy(calllog->szremote, tmp);
	}
	else if(calllog->status == CL_RECEIVED)
	{
	    //status_index, remote
		statusIndex = lp_config_get_int(calllog_lpconfig, section_index, CLOG_RECEIVED_INDEX, NULL);
		if(statusIndex != -1)
		{
			calllog->status_index = statusIndex;
			statusIndex = -1;
		}
		
		tmp = lp_config_get_string(calllog_lpconfig, section_index, CLOG_REMOTE_FROM, NULL);
		if(tmp != NULL)
			strcpy(calllog->szremote, tmp);
	}
	else if(calllog->status == CL_DIALED)
	{
	    //status_index, remote
		statusIndex = lp_config_get_int(calllog_lpconfig, section_index, CLOG_DIALED_INDEX, NULL);
		if(statusIndex != -1) 
		{
			calllog->status_index = statusIndex;
			statusIndex = -1;
		}
		
		tmp = lp_config_get_string(calllog_lpconfig,section_index, CLOG_REMOTE_TO, NULL);
		if(tmp != NULL)
			strcpy(calllog->szremote, tmp);
	}	

	//date
	tmp = lp_config_get_string(calllog_lpconfig, section_index, CLOG_START_DATE, NULL);
    tmpcpy = (char*)malloc(strlen(tmp)); 
	strcpy(tmpcpy, tmp);
	
    char *p_date, *p_time;	
	p_date = strtok(tmpcpy, " ");
	p_time = strtok(NULL, "");
	
	if(p_date) 
	{
		p_date = strtok(p_date, "-");
		strcpy(calllog->date.year, p_date);
		
		p_date = strtok(NULL, "-");
		strcpy(calllog->date.month, p_date);
		
		p_date = strtok(NULL, "-");
		strcpy(calllog->date.day, p_date);
	}	
	
	if(p_time) 
	{
		p_time = strtok(p_time, ":");
		strcpy(calllog->date.hour, p_time);
		
		p_time = strtok(NULL, ":");
		strcpy(calllog->date.minute, p_time);
		
	    p_time = strtok(NULL, ":");
		strcpy(calllog->date.second, p_time);
		//printf("calllog->date.second: %s\n", calllog->date.second);	
	}

	//duration
	duration = lp_config_get_int(calllog_lpconfig, section_index, CLOG_DURATION, NULL);
	if(duration > 0)
		calllog->date.duration = duration;
	
	return calllog;
}

int CCalllogManager::read_calllog()
{
    //int all_count = 0, miss_count = 0, receive_count = 0, dail_count = 0;
	CallLog *calllog = new CallLog;	
	
	if(calllog_lpconfig == NULL)
	{
		g_error("_LpConfig = (null)");
		return NULL;
	}
	
	for (int i=0; (calllog = get_section_from_config_file(i)) != NULL; i++)
	{
		if(calllog->status == CL_MISSED)
		{
			calllog_missed.status = CL_MISSED;
			calllog_missed.calllog_buf[calllog_missed.count] = calllog;
			calllog_missed.count++;
		}
		
		if(calllog->status == CL_RECEIVED)
		{
			calllog_received.status = CL_RECEIVED;
			calllog_received.calllog_buf[calllog_received.count] = calllog;
			calllog_received.count++;
		}
		
		if(calllog->status == CL_DIALED)
		{
			calllog_dialed.status = CL_DIALED;
			calllog_dialed.calllog_buf[calllog_dialed.count] = calllog;
			calllog_dialed.count++;
		}
    }

	cout << "calllog_missed.count: " << calllog_missed.count << endl;
	cout << "calllog_received.count: " << calllog_received.count << endl;
	cout << "calllog_dailed.count: " << calllog_dialed.count << endl;
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

	sprintf(datetime, "%s-%s-%s %s:%s:%s", item->date.year, item->date.month,
		                                   item->date.day, item->date.hour, 
		                                   item->date.minute, item->date.second);
 
	lp_config_set_string(calllog_lpconfig, section_index, CLOG_START_DATE, datetime);

	//duration
    lp_config_set_int(calllog_lpconfig, section_index, CLOG_DURATION, item->date.duration);

	return 0;
}

int CCalllogManager::sync_calllog_config()
{
    int writeindex = 0;
	char section[30];

	if(calllog_lpconfig == NULL)
	{
		g_error("_LpConfig = (null)");
		return -1;
	}

    cout << "\nlen: " << get_calllog_buf_count()<< endl;
	
	for(int i = 0; i < calllog_missed.count; i++)
		write_calllog_item(calllog_missed.calllog_buf[i], i, i);

	for(int i = 0; i < calllog_received.count; i++)
		write_calllog_item(calllog_received.calllog_buf[i], i + calllog_missed.count, i);
	
	for(int i = 0; i < calllog_dialed.count; i++)
		write_calllog_item(calllog_dialed.calllog_buf[i], i + calllog_received.count, i);

	//clear
	for(int i = get_calllog_buf_count(); i < MAX_CALLLOG_COUNT; i++)
	{
	    sprintf(section, "%s%i", CLOG_CALLLOG_INDEX, i);
	    if(lp_config_has_section(calllog_lpconfig, section))
	    {
			lp_config_clean_section(calllog_lpconfig, section);
            cout << "\nclear index: " << i << endl;
		}
	}
	
	//sync
	return lp_config_sync(calllog_lpconfig);
}

//CRUD
int CCalllogManager::get_calllog_count()
{	
	read_calllog();
	
    return calllog_missed.count + calllog_received.count + calllog_dialed.count;
}

int CCalllogManager::get_calllog_buf_count()
{	
    int i;
	calllog_missed.count = 0;
	calllog_received.count = 0;
	calllog_dialed.count = 0;

	i = 0;
    while(calllog_missed.calllog_buf[i++] != NULL)
    {
		calllog_missed.count++;
		cout << "\ncalllog_missed: " << calllog_missed.count<< endl;
    }    
    i = 0;
	while(calllog_received.calllog_buf[i++] != NULL)
	{
		calllog_received.count++;
		cout << "\ncalllog_received: " << calllog_received.count << endl;
	}
    i = 0;
	while(calllog_dialed.calllog_buf[i++] != NULL)
	{
		calllog_dialed.count++;
		
		if(calllog_dialed.calllog_buf[0] == NULL)
			cout << "\n==" << endl;
		else
			cout << "\n!= " << endl;
		cout << "\ncalllog_dialed: " << calllog_dialed.count << endl;
	}
	cout << "\nlen: " << calllog_missed.count + calllog_received.count + calllog_dialed.count<< endl;
    return calllog_missed.count + calllog_received.count + calllog_dialed.count;
}


int CCalllogManager::get_calllog_count_by_type(CLSTATUS status)
{
    read_calllog();
	if(status == CL_MISSED)
		return calllog_missed.count;
	
	if(status == CL_RECEIVED)
		return calllog_received.count;
	
	if(status == CL_DIALED)
		return calllog_dialed.count;
	
	return 0;
}

int CCalllogManager::get_calllog_by_index(CLSTATUS status,int index, CallLog *calllog)
{
	
}

int CCalllogManager::add_calllog(CLSTATUS status, CallLog *calllog)
{
	int len;
	int i = 0;
	
	len = get_calllog_count();
	cout << "\nlen: " << len << endl;
	
	if(status == CL_MISSED)
	{
	    while(1)
	    {
	        if(calllog_missed.calllog_buf[i] == NULL)
	        {
	            cout << "\ni: " << i << endl;
			    calllog_missed.calllog_buf[i] = calllog;
				break;
	        }
			i++;
		}
	   //calllog_missed.calllog_buf[2] = calllog;
		cout << "\nadd CL_MISSED: " << endl;
		if(calllog_missed.calllog_buf[i] == NULL)
			cout << "\n== " << endl;
		else
			cout << "\n!= " << endl;
	}
	if(status == CL_RECEIVED)
	{
		while(calllog_received.calllog_buf[i++] == NULL)
			calllog_received.calllog_buf[--i] = calllog;
		cout << "\nCL_RECEIVED: " << endl;
	}
	if(status == CL_DIALED)
	{
	    while(calllog_dialed.calllog_buf[i++] == NULL)
			calllog_dialed.calllog_buf[--i] = calllog;
		cout << "\nCL_DIALED: " << endl;
	}
	//sync
    sync_calllog_config();
	
    //result = write_calllog_item(calllog_lpconfig, calllog, section_index, ); 
	/*printf("result: %d \n",result);

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
		printf("Failed to write calllog section !\n");*/
}

int CCalllogManager::delete_calllog_by_index(CLSTATUS status, int index)
{
	/*gchar section_title[64];
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
	}*/
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
